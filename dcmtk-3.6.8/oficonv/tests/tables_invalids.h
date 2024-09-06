/*
 *
 *  Copyright (C) 2022, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  oficonv
 *
 *  Author:  Marco Eichelberg
 *
 *  Purpose: UTF-8 byte sequences containing characters that cannot be
 *    converted and illegal byte sequences
 *
 */

#ifndef TABLES_INVALIDS_H
#define TABLES_INVALIDS_H

unsigned char OF__iconv_test_sequence[] = {
  // some ISO Latin 1 characters, these can be converted
  0xc3, 0x8f, 0xc3, 0x90, 0xc3, 0x91, 0xc3, 0x92, 0xc3, 0x93, 0xc3, 0x94,
  0xc3, 0x95, 0xc3, 0x96, 0xc3, 0x97, 0xc3, 0x98, 0xc3, 0x99, 0xc3, 0x9a,
  0xc3, 0x9b, 0xc3, 0x9c, 0xc3, 0x9d, 0xc3, 0x9e,

  // four Japanese characters, these cannot be converted to Latin-1
  0xe5, 0x92, 0x81, 0xe5, 0x92, 0x83, 0xe5, 0x92, 0x85, 0xe5, 0x92, 0x88,

  // some ASCII characters, these can be converted
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,

  // an illegal UTF-8 sequence
  0xff, 0xff, 0xff, 0xff,

  // some ASCII characters, these can be converted
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50
};

unsigned char test_sequence_converted_to_latin_1[] = {
  // 16 printable Latin-1 characters
  0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde,

  // four question marks for the four Japanese letters
  0x3f, 0x3f, 0x3f, 0x3f,

  // 16 printable ASCII characters
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50

  // conversion stops here because of the illegal UTF-8 sequence
};

unsigned char test_sequence_converted_to_latin_1_invalids_hidden[] = {
  // 16 printable Latin-1 characters
  0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde,

  // no question marks for the four Japanese letters, these are simply ignored

  // 16 printable ASCII characters
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50

  // conversion stops here because of the illegal UTF-8 sequence
};

unsigned char test_sequence_converted_to_latin_1_invalids_stopped[] = {
  // 16 printable Latin-1 characters
  0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde,

  // conversion stops here because of the Japanese letters that cannot be mapped to Latin-1
};

unsigned char OFiconvctl_test_sequence[] = {
  // some ISO Latin 1 characters, these can be converted
  0xc3, 0x8f, 0xc3, 0x90, 0xc3, 0x91, 0xc3, 0x92, 0xc3, 0x93, 0xc3, 0x94,
  0xc3, 0x95, 0xc3, 0x96, 0xc3, 0x97, 0xc3, 0x98, 0xc3, 0x99, 0xc3, 0x9a,
  0xc3, 0x9b, 0xc3, 0x9c, 0xc3, 0x9d, 0xc3, 0x9e,

  // four Japanese characters, these cannot be converted to Latin-1
  0xe5, 0x92, 0x81, 0xe5, 0x92, 0x83, 0xe5, 0x92, 0x85, 0xe5, 0x92, 0x88,

  // some ASCII characters, these can be converted
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50
};

#endif
