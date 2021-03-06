/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2010, 2013 Peter Miller
 * Written by Peter Miller <pmiller@opensource.org.au>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBEXPLAIN_AC_LINUX_NET_TSTAMP_H
#define LIBEXPLAIN_AC_LINUX_NET_TSTAMP_H

/**
  * @file
  * @brief Insulate <linux/net_tstamp.h> differences
  */

#include <libexplain/config.h>

#ifdef HAVE_LINUX_NET_TSTAMP_H
#include <sys/types.h> /* clockid_t */
#include <linux/net_tstamp.h>
#endif

#endif /* LIBEXPLAIN_AC_LINUX_NET_TSTAMP_H */
/* vim: set ts=8 sw=4 et : */
