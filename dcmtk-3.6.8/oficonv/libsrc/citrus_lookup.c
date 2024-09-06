/*-
 * Copyright (c)2003 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "dcmtk/config/osconfig.h"
#include "citrus_lookup.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif


#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "citrus_bcs.h"
#include "citrus_region.h"
#include "citrus_memstream.h"
#include "citrus_mmap.h"
#include "citrus_db.h"
#include "citrus_db_hash.h"
#include "citrus_lookup_file.h"

struct _citrus_lookup {
    union {
        struct {
            struct _citrus_db *db;
            struct _citrus_region file;
            int num, idx;
            struct _citrus_db_locator locator;
        } db;
        struct {
            struct _citrus_region r;
            struct _citrus_memory_stream ms;
        } plain;
    } u;
#define cl_db       u.db.db
#define cl_dbidx    u.db.idx
#define cl_dbfile   u.db.file
#define cl_dbnum    u.db.num
#define cl_dblocator    u.db.locator
#define cl_plainr   u.plain.r
#define cl_plainms  u.plain.ms
    int cl_ignore_case;
    int cl_rewind;
    char *cl_key;
    size_t cl_keylen;
    int (*cl_next)(struct _citrus_lookup *, struct _citrus_region *,
               struct _citrus_region *);
    int (*cl_lookup)(struct _citrus_lookup *, const char *,
             struct _citrus_region *);
    int (*cl_num_entries)(struct _citrus_lookup *);
    void (*cl_close)(struct _citrus_lookup *);
};

static int
seq_get_num_entries_db(struct _citrus_lookup *cl)
{

    return (cl->cl_dbnum);
}

static int
seq_next_db(struct _citrus_lookup *cl, struct _citrus_region *key,
    struct _citrus_region *data)
{

    if (cl->cl_key) {
        if (key)
            _citrus_region_init(key, cl->cl_key, cl->cl_keylen);
        return (_citrus_db_lookup_by_string(cl->cl_db, cl->cl_key, data,
            &cl->cl_dblocator));
    }

    if (cl->cl_rewind) {
        cl->cl_dbidx = 0;
    }
    cl->cl_rewind = 0;
    if (cl->cl_dbidx >= cl->cl_dbnum)
        return (ENOENT);

    return (_citrus_db_get_entry(cl->cl_db, cl->cl_dbidx++, key, data));
}

static int
seq_lookup_db(struct _citrus_lookup *cl, const char *key, struct _citrus_region *data)
{

    cl->cl_rewind = 0;
    free(cl->cl_key);
    cl->cl_key = strdup(key);
    if (cl->cl_ignore_case)
        _citrus_bcs_convert_to_lower(cl->cl_key);
    cl->cl_keylen = strlen(cl->cl_key);
    _citrus_db_locator_init(&cl->cl_dblocator);
    return (_citrus_db_lookup_by_string(cl->cl_db, cl->cl_key, data,
        &cl->cl_dblocator));
}

static void
seq_close_db(struct _citrus_lookup *cl)
{

    _citrus_db_close(cl->cl_db);
    _citrus_unmap_file(&cl->cl_dbfile);
}

static int
seq_open_db(struct _citrus_lookup *cl, const char *name)
{
    struct _citrus_region r;
    char path[OFICONV_PATH_MAX];
    int ret;

    snprintf(path, sizeof(path), "%s.db", name);
    ret = _citrus_map_file(&r, path);
    if (ret)
        return (ret);

    ret = _citrus_db_open(&cl->cl_db, &r, _CITRUS_LOOKUP_MAGIC,
        _citrus_db_hash_std, NULL);
    if (ret) {
        _citrus_unmap_file(&r);
        return (ret);
    }

    cl->cl_dbfile = r;
    cl->cl_dbnum = _citrus_db_get_number_of_entries(cl->cl_db);
    cl->cl_dbidx = 0;
    cl->cl_rewind = 1;
    cl->cl_lookup = &seq_lookup_db;
    cl->cl_next = &seq_next_db;
    cl->cl_num_entries = &seq_get_num_entries_db;
    cl->cl_close = &seq_close_db;

    return (0);
}

#define T_COMM '#'
static int
seq_next_plain(struct _citrus_lookup *cl, struct _citrus_region *key,
           struct _citrus_region *data)
{
    const char *p, *q;
    size_t len;

    if (cl->cl_rewind)
        _citrus_memory_stream_bind(&cl->cl_plainms, &cl->cl_plainr);
    cl->cl_rewind = 0;

retry:
    p = _citrus_memory_stream_getln(&cl->cl_plainms, &len);
    if (p == NULL)
        return (ENOENT);
    /* ignore comment */
    q = memchr(p, T_COMM, len);
    if (q) {
        len = q - p;
    }
    /* ignore trailing spaces */
    _citrus_bcs_trunc_rws_len(p, &len);
    p = _citrus_bcs_skip_ws_len(p, &len);
    q = _citrus_bcs_skip_nonws_len(p, &len);
    if (p == q)
        goto retry;
    if (cl->cl_key && ((size_t)(q - p) != cl->cl_keylen ||
        memcmp(p, cl->cl_key, (size_t)(q - p)) != 0))
        goto retry;

    /* found a entry */
    if (key)
        _citrus_region_init(key, CITRUS_DECONST(void *, p), (size_t)(q - p));
    p = _citrus_bcs_skip_ws_len(q, &len);
    if (data)
        _citrus_region_init(data, len ? CITRUS_DECONST(void *, p) : NULL, len);

    return (0);
}

static int
seq_get_num_entries_plain(struct _citrus_lookup *cl)
{
    int num;

    num = 0;
    while (seq_next_plain(cl, NULL, NULL) == 0)
        num++;

    return (num);
}

static int
seq_lookup_plain(struct _citrus_lookup *cl, const char *key,
    struct _citrus_region *data)
{
    size_t len;
    const char *p;

    cl->cl_rewind = 0;
    free(cl->cl_key);
    cl->cl_key = strdup(key);
    if (cl->cl_ignore_case)
        _citrus_bcs_convert_to_lower(cl->cl_key);
    cl->cl_keylen = strlen(cl->cl_key);
    _citrus_memory_stream_bind(&cl->cl_plainms, &cl->cl_plainr);
    p = _citrus_memory_stream_matchline(&cl->cl_plainms, cl->cl_key, &len, 0);
    if (p == NULL)
        return (ENOENT);
    if (data)
        _citrus_region_init(data, CITRUS_DECONST(void *, p), len);

    return (0);
}

static void
seq_close_plain(struct _citrus_lookup *cl)
{

    _citrus_unmap_file(&cl->cl_plainr);
}

static int
seq_open_plain(struct _citrus_lookup *cl, const char *name)
{
    int ret;

    /* open read stream */
    ret = _citrus_map_file(&cl->cl_plainr, name);
    if (ret)
        return (ret);

    cl->cl_rewind = 1;
    cl->cl_next = &seq_next_plain;
    cl->cl_lookup = &seq_lookup_plain;
    cl->cl_num_entries = &seq_get_num_entries_plain;
    cl->cl_close = &seq_close_plain;

    return (0);
}

int
_citrus_lookup_seq_open(struct _citrus_lookup **rcl, const char *name,
    int ignore_case)
{
    int ret;
    struct _citrus_lookup *cl;

    cl = malloc(sizeof(*cl));
    if (cl == NULL)
        return (errno);

    cl->cl_key = NULL;
    cl->cl_keylen = 0;
    cl->cl_ignore_case = ignore_case;
    ret = seq_open_db(cl, name);
    if (ret == ENOENT)
        ret = seq_open_plain(cl, name);
    if (!ret)
        *rcl = cl;
    else
        free(cl);

    return (ret);
}

void
_citrus_lookup_seq_rewind(struct _citrus_lookup *cl)
{

    cl->cl_rewind = 1;
    free(cl->cl_key);
    cl->cl_key = NULL;
    cl->cl_keylen = 0;
}

int
_citrus_lookup_seq_next(struct _citrus_lookup *cl,
    struct _citrus_region *key, struct _citrus_region *data)
{

    return ((*cl->cl_next)(cl, key, data));
}

int
_citrus_lookup_seq_lookup(struct _citrus_lookup *cl, const char *key,
    struct _citrus_region *data)
{
    return ((*cl->cl_lookup)(cl, key, data));
}

int
_citrus_lookup_get_number_of_entries(struct _citrus_lookup *cl)
{

    return ((*cl->cl_num_entries)(cl));
}

void
_citrus_lookup_seq_close(struct _citrus_lookup *cl)
{

    free(cl->cl_key);
    (*cl->cl_close)(cl);
    free(cl);
}

char *
_citrus_lookup_simple(const char *name, const char *key,
    char *linebuf, size_t linebufsize, int ignore_case)
{
    struct _citrus_lookup *cl;
    struct _citrus_region data;
    int ret;
    cl = NULL;

    ret = _citrus_lookup_seq_open(&cl, name, ignore_case);
    if (ret)
        return (NULL);

    ret = _citrus_lookup_seq_lookup(cl, key, &data);
    if (ret) {
        _citrus_lookup_seq_close(cl);
        return (NULL);
    }

    snprintf(linebuf, linebufsize, "%.*s", (int)_citrus_region_size(&data),
        (const char *)_citrus_region_head(&data));

    _citrus_lookup_seq_close(cl);

    return (linebuf);
}
