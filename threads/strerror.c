/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 31-1 */

/* strerror.c

   An implementation of strerror() that is not thread-safe.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_ERROR_LEN 256

// Define a thread-local buffer for storing error messages
__thread char buf[MAX_ERROR_LEN];

char *
strerror(int err)
{
    int ret;

    // Use the GNU-specific version of strerror_r
    char *msg = strerror_r(err, buf, MAX_ERROR_LEN);
    ret = (msg == buf) ? 0 : -1;

    if (ret != 0) {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    }

    return buf;
}
