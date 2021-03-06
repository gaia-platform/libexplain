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

#include <libexplain/parse_bits.h>
#include <libexplain/string_buffer.h>


void
explain_parse_bits_print(explain_string_buffer_t *sb, int value,
    const explain_parse_bits_table_t *table, int table_size)
{
    int             first;
    int             i;

    if (value == 0)
    {
        explain_string_buffer_puts(sb, "0");
        return;
    }
    first = 1;

    // Iterate over entire table checking value against each flag
    for (i = 0; i < table_size && value != 0; i++)
    {
        int flag = table[i].value;
        if (flag != 0 && (flag & value) == flag)
        {
            value -= flag;

            if (!first)
                explain_string_buffer_puts(sb, " | ");
            explain_string_buffer_puts(sb, table[i].name);
            first = 0;
        }
    }
    if (value != 0)
    {
        if (!first)
            explain_string_buffer_puts(sb, " | ");
        explain_string_buffer_printf(sb, "0x%X", value);
    }
}


/* vim: set ts=8 sw=4 et : */
