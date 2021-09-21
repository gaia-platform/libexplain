/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2008, 2009, 2013 Peter Miller
 * Written by Peter Miller <pmiller@opensource.org.au>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBEXPLAIN_BUFFER_ERRNO_ACCESS_H
#define LIBEXPLAIN_BUFFER_ERRNO_ACCESS_H

#include <libexplain/string_buffer.h>

/**
  * The explain_buffer_errno_access function is used to obtain an
  * explanation of an error returned by the access(2) system call.  The
  * least the message will contain is the value of strerror(errnum), but
  * usually it will do much better, and indicate the underlying cause in
  * more detail.
  *
  * @param sb
  *     The string buffer in which the message is being constructed.
  *     If a safe buffer is specified, this function is
  *     thread safe.
  * @param errnum
  *     The error value to be decoded, usually obtain from the errno
  *     global variable just before this function is called.  This
  *     is necessary if you need to call <b>any</b> code between the
  *     system call to be explained and this function, because many libc
  *     functions will alter the value of errno.
  * @param pathname
  *     The original pathname, exactly has passed to the access(2) system call.
  * @param mode
  *     The original mode, exactly has passed to the access(2) system call.
  */
void explain_buffer_errno_access(explain_string_buffer_t *sb, int errnum,
    const char *pathname, int mode);

/**
  * The explain_buffer_errno_access_explanation function is used by
  * the explain_buffer_errno_access function (and others) to explain
  * an error.
  *
  * @param sb
  *     The string buffer in which the message is being constructed.
  * @param errnum
  *     The error value to be decoded.
  * @param syscall_name
  *     The name of the offending system call.
  * @param pathname
  *     The original pathname, exactly has passed to the access(2) system call.
  * @param mode
  *     The original mode, exactly has passed to the access(2) system call.
  */
void explain_buffer_errno_access_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, const char *pathname, int mode);

#endif /* LIBEXPLAIN_BUFFER_ERRNO_ACCESS_H */
/* vim: set ts=8 sw=4 et : */
