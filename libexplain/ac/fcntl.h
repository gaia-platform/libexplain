/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2008-2013 Peter Miller
 * Written by Peter Miller <pmiller@opensource.org.au>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBEXPLAIN_AC_FCNTL_H
#define LIBEXPLAIN_AC_FCNTL_H

/**
  * @file
  * @brief Insulate <fcntl.h> differences
  */

#include <libexplain/config.h>

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#else
#include <libexplain/ac/sys/file.h>
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifndef O_TEXT
#define O_TEXT 0
#endif

/*
 * Needed for explain_buffer_errno_path_resolution
 */
#ifndef O_DIRECTORY
#define O_DIRECTORY 0x40000000  /* or O_RDONLY */
#endif

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

/*
 * On 64-bit linux, fcntl(F_GETFL) always returns O_LARGEFILE even if we don't
 * request it. Unfortunately glibc does not expose this value so we have to
 * handle it ourselves. Also the value changes across arches *sigh*.
 *
 * These values were taken from the asm/fcntl.h kernel header for each arch.
 * We can't include this header because it conflicts with glibc's fcntl.h.
 */
#if defined(__linux__) && (O_LARGEFILE == 0)
# if defined(__aarch64__) || defined(__alpha__)
#  define O_LARGEFILE_HIDDEN 0400000
# elif defined(__mips64)
#  define O_LARGEFILE_HIDDEN 0x2000
# elif defined(__PPC64__)
#  define O_LARGEFILE_HIDDEN 0200000
# elif defined(__sparc__) && defined(__arch64__)
#  define O_LARGEFILE_HIDDEN 0x40000
# else
#  define O_LARGEFILE_HIDDEN 0100000
# endif
#endif


/*
 * From /usr/include/sharutils/fcntl.h ...
 *
 * Work around a bug in Solaris 9 and 10: AT_FDCWD is positive.
 * Its value exceeds INT_MAX, so its use as an int doesn't conform to
 * the C standard, and GCC and Sun C complain in some cases.  If the
 * bug is present, undef AT_FDCWD here, so it can be redefined.
 */
#if 0 < AT_FDCWD && AT_FDCWD == 0xffd19553
#undef AT_FDCWD

/*
 * Use the same bit pattern as Solaris 9, but with the proper signedness.
 * The bit pattern is important, in case this actually is Solaris with
 * the above workaround.
 */
#define AT_FDCWD (-3041965)
#endif


/* vim: set ts=8 sw=4 et : */
#endif /* LIBEXPLAIN_AC_FCNTL_H */
