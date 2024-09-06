/*-
 * Copyright (c)2002 Citrus Project,
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

/*-
 * Copyright (c) 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "dcmtk/config/osconfig.h"
#include "citrus_euc.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif


#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "citrus_bcs.h"
#include "citrus_types.h"
#include "citrus_module.h"
#include "citrus_stdenc.h"


/* ----------------------------------------------------------------------
 * private stuffs used by templates
 */

typedef struct {
    int  chlen;
    char     ch[3];
} _EUCState;

typedef struct {
    _citrus_wc_t      bits[4];
    _citrus_wc_t      mask;
    unsigned     count[4];
    unsigned     mb_cur_max;
} _EUCEncodingInfo;

#define _SS2    0x008e
#define _SS3    0x008f

#define _CEI_TO_EI(_cei_)       (&(_cei_)->ei)
#define _CEI_TO_STATE(_cei_, _func_)    (_cei_)->states.s_##_func_

#define _FUNCNAME(m)            _citrus_EUC_##m
#define _ENCODING_INFO          _EUCEncodingInfo
#define _ENCODING_STATE         _EUCState
#define _ENCODING_MB_CUR_MAX(_ei_)  (_ei_)->mb_cur_max
#define _ENCODING_IS_STATE_DEPENDENT    0
#define _STATE_NEEDS_EXPLICIT_INIT(_ps_)    0


static __inline int
_citrus_EUC_cs(unsigned int c)
{

    c &= 0xff;

    return ((c & 0x80) ? c == _SS3 ? 3 : c == _SS2 ? 2 : 1 : 0);
}

/* suppress MSVC 'assignment within conditional expression' warning  */
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4706)
#endif

static __inline int
_citrus_EUC_parse_variable(_EUCEncodingInfo *ei, const void *var,
    size_t lenvar )
{
    char *e;
    const char *v;
    int x;
    (void) lenvar;

    /* parse variable string */
    if (!var)
        return (EFTYPE);

    v = (const char *)var;

    while (*v == ' ' || *v == '\t')
        ++v;

    ei->mb_cur_max = 1;
    for (x = 0; x < 4; ++x) {
        ei->count[x] = (int)_citrus_bcs_strtol(v, (char **)&e, 0);
        if (v == e || !(v = e) || ei->count[x] < 1 || ei->count[x] > 4) {
            return (EFTYPE);
        }
        if (ei->mb_cur_max < ei->count[x])
            ei->mb_cur_max = ei->count[x];
        while (*v == ' ' || *v == '\t')
            ++v;
        ei->bits[x] = (int)_citrus_bcs_strtol(v, (char **)&e, 0);
        if (v == e || !(v = e)) {
            return (EFTYPE);
        }
        while (*v == ' ' || *v == '\t')
            ++v;
    }
    ei->mask = (int)_citrus_bcs_strtol(v, (char **)&e, 0);
    if (v == e || !(v = e)) {
        return (EFTYPE);
    }

    return (0);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

static __inline void
/*ARGSUSED*/
_citrus_EUC_init_state(_EUCEncodingInfo *ei , _EUCState *s)
{
    (void) ei;
    memset(s, 0, sizeof(*s));
}

static int
_citrus_EUC_mbrtowc_priv(_EUCEncodingInfo *ei, _citrus_wc_t *pwc, char **s,
    size_t n, _EUCState *psenc, size_t *nresult)
{
    _citrus_wc_t wchar;
    int c, chlenbak, cs, len;
    char *s0, *s1 = NULL;

    s0 = *s;

    if (s0 == NULL) {
        _citrus_EUC_init_state(ei, psenc);
        *nresult = 0; /* state independent */
        return (0);
    }

    chlenbak = psenc->chlen;

    /* make sure we have the first byte in the buffer */
    switch (psenc->chlen) {
    case 0:
        if (n < 1)
            goto restart;
        psenc->ch[0] = *s0++;
        psenc->chlen = 1;
        n--;
        break;
    case 1:
    case 2:
        break;
    default:
        /* illgeal state */
        goto encoding_error;
    }

    c = ei->count[cs = _citrus_EUC_cs(psenc->ch[0] & 0xff)];
    if (c == 0)
        goto encoding_error;
    while (psenc->chlen < c) {
        if (n < 1)
            goto restart;
        psenc->ch[psenc->chlen] = *s0++;
        psenc->chlen++;
        n--;
    }
    *s = s0;

    switch (cs) {
    case 3:
    case 2:
        /* skip SS2/SS3 */
        len = c - 1;
        s1 = &psenc->ch[1];
        break;
    case 1:
    case 0:
        len = c;
        s1 = &psenc->ch[0];
        break;
    default:
        goto encoding_error;
    }
    wchar = 0;
    while (len-- > 0)
        wchar = (wchar << 8) | (*s1++ & 0xff);
    wchar = (wchar & ~ei->mask) | ei->bits[cs];

    psenc->chlen = 0;
    if (pwc)
        *pwc = wchar;
    *nresult = wchar ? (size_t)(c - chlenbak) : 0;
    return (0);

encoding_error:
    psenc->chlen = 0;
    *nresult = (size_t)-1;
    return (EILSEQ);

restart:
    *nresult = (size_t)-2;
    *s = s0;
    return (0);
}

static int
_citrus_EUC_wcrtomb_priv(_EUCEncodingInfo *ei, char *s, size_t n, _citrus_wc_t wc,
    _EUCState *psenc , size_t *nresult)
{
    _citrus_wc_t m, nm;
    unsigned int cs;
    int ret;
    int i;

    (void) psenc;
    m = wc & ei->mask;
    nm = wc & ~m;

    for (cs = 0; cs < sizeof(ei->count) / sizeof(ei->count[0]); cs++)
        if (m == ei->bits[cs])
            break;
    /* fallback case - not sure if it is necessary */
    if (cs == sizeof(ei->count) / sizeof(ei->count[0]))
        cs = 1;

    i = ei->count[cs];
    if (n < (unsigned)i) {
        ret = E2BIG;
        goto err;
    }
    m = (cs) ? 0x80 : 0x00;
    switch (cs) {
    case 2:
        *s++ = _SS2;
        i--;
        break;
    case 3:
        *s++ = _SS3;
        i--;
        break;
    }

    while (i-- > 0)
        *s++ = (char)(((nm >> (i << 3)) & 0xff) | m);

    *nresult = (size_t)ei->count[cs];
    return (0);

err:
    *nresult = (size_t)-1;
    return (ret);
}

static __inline int
/*ARGSUSED*/
_citrus_EUC_stdenc_wctocs(_EUCEncodingInfo * ei,
    _citrus_csid_t * csid, _citrus_index_t * idx, _citrus_wc_t wc)
{
    _citrus_wc_t m, nm;

    m = wc & ei->mask;
    nm = wc & ~m;

    *csid = (_citrus_csid_t)m;
    *idx  = (_citrus_index_t)nm;

    return (0);
}

static __inline int
/*ARGSUSED*/
_citrus_EUC_stdenc_cstowc(_EUCEncodingInfo * ei,
    _citrus_wc_t * wc, _citrus_csid_t csid, _citrus_index_t idx)
{

    if ((csid & ~ei->mask) != 0 || (idx & ei->mask) != 0)
        return (EINVAL);

    *wc = (_citrus_wc_t)csid | (_citrus_wc_t)idx;

    return (0);
}

static __inline int
/*ARGSUSED*/
_citrus_EUC_stdenc_get_state_desc_generic(_EUCEncodingInfo * ei ,
    _EUCState * psenc, int * rstate)
{

    (void) ei;
    *rstate = (psenc->chlen == 0) ? _CITRUS_STDENC_SDGEN_INITIAL :
        _CITRUS_STDENC_SDGEN_INCOMPLETE_CHAR;
    return (0);
}

static int
/*ARGSUSED*/
_citrus_EUC_encoding_module_init(_EUCEncodingInfo * ei,
    const void * var, size_t lenvar)
{

    return (_citrus_EUC_parse_variable(ei, var, lenvar));
}

static void
/*ARGSUSED*/
_citrus_EUC_encoding_module_uninit(_EUCEncodingInfo * ei )
{
    (void) ei;
}

/* ----------------------------------------------------------------------
 * public interface for stdenc
 */

_CITRUS_STDENC_DECLS(EUC);
_CITRUS_STDENC_DEF_OPS(EUC);

#include "citrus_stdenc_template.h"
