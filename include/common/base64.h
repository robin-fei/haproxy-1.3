/*
 * include/common/base64.h
 * Ascii to Base64 conversion as described in RFC1421.
 *
 * Copyright 2006 Willy Tarreau <w@1wt.eu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 */

#ifndef _COMMON_BASE64_H
#define _COMMON_BASE64_H

#include <common/config.h>

int a2base64(char *in, int ilen, char *out, int olen);
extern const char base64tab[];

#endif /* _COMMON_BASE64_H */
