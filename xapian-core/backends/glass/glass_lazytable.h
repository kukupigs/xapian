/** @file glass_lazytable.h
 * @brief Subclass of GlassTable for deriving lazy tables from.
 */
/* Copyright (C) 2009,2013,2014 Olly Betts
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef XAPIAN_INCLUDED_GLASS_LAZYTABLE_H
#define XAPIAN_INCLUDED_GLASS_LAZYTABLE_H

#include "glass_table.h"

class GlassLazyTable : public GlassTable {
  public:
    /** Create a new lazy table.
     *
     *  @param name_		The table's name.
     *  @param path		The path for the table.
     *  @param readonly		true if the table is read-only, else false.
     *  @param z_strategy	zlib strategy.
     */
    GlassLazyTable(const char * name_, const std::string & path, bool readonly,
		   int z_strategy)
	: GlassTable(name_, path, readonly, z_strategy, true) { }

    /** Lazy version of GlassTable::create_and_open().
     *
     *  This method isn't virtual, but we never call it such that it needs to
     *  be.
     */
    void create_and_open(int flags_, unsigned blocksize_) {
	// This table is created lazily, so erase it in case we're overwriting
	// an existing database which has this table.
	GlassTable::erase();
	GlassTable::set_flags(flags_);
	GlassTable::set_blocksize(blocksize_);
    }
};

#endif // XAPIAN_INCLUDED_GLASS_LAZYTABLE_H
