/*
 * libexplain - Explain errno values returned by libc functions
 * Copyright (C) 2009-2013 Peter Miller
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty
 * ofMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNULesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <libexplain/ac/errno.h>
#include <libexplain/ac/stdarg.h>
#include <libexplain/ac/stdlib.h>
#include <libexplain/ac/unistd.h>

#include <libexplain/buffer/errno/execlp.h>
#include <libexplain/common_message_buffer.h>
#include <libexplain/execlp.h>
#include <libexplain/sizeof.h>
#include <libexplain/string_buffer.h>
#include <libexplain/output.h>


void
explain_execlp_or_die(const char *pathname, const char *arg, ...)
{
    va_list         ap;
    va_list         ap1;
    va_list         ap2;
    int             argc;
    int             argc2;
    const char      **argv;
    explain_string_buffer_t sb;
    int             errnum;
    const char      *dummy[100];

    /*
     * count the number of arguments
     */
    va_start(ap, arg);
    va_copy(ap1, ap);
    argc = 1;
    for (;;)
    {
        const char *p = va_arg(ap1, const char *);
        if (!p)
            break;
        ++argc;
    }

    /*
     * create an array to store the arguments in.
     */
    if (argc < (int)SIZEOF(dummy))
    {
        argv = dummy;
    }
    else
    {
        argv = malloc((argc + 1) * sizeof(const char *));
        if (!argv)
        {
            argv = dummy;
            argc = SIZEOF(dummy) - 1;
        }
    }

    /*
     * Now slurp the arguments into the array.
     */
    va_copy(ap2, ap);
    argv[0] = arg;
    for (argc2 = 1; argc2 < argc; ++argc2)
    {
        argv[argc2] = va_arg(ap2, const char *);
    }
    argv[argc] = NULL;

    /* for ANSI C compliance */
    va_end(ap1);

    /* Note: if it returns at all, it has failed */
    errno = 0;
    if (execvp(pathname, (char *const *)argv))
    {
        /*
         * Ordinarily, the warning "ignoring return value of function"
         * is a great way of discovering bugs.  In this case, however,
         * we aren't concerned with the actual return value, but with
         * the error that results from the call.
         */
    }

    errnum = errno;
    /* assert(errnum != 0); */

    explain_string_buffer_init
    (
        &sb,
        explain_common_message_buffer,
        explain_common_message_buffer_size
    );
    explain_buffer_errno_execlpv(&sb, errnum, pathname, argc, argv);
    explain_output_error_and_die("%s", explain_common_message_buffer);
}


/* vim: set ts=8 sw=4 et : */
