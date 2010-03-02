/** @file  positioniterator.h
 *  @brief Class for iterating over term positions.
 */
/* Copyright (C) 2008,2009,2010 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef XAPIAN_INCLUDED_POSITIONITERATOR_H
#define XAPIAN_INCLUDED_POSITIONITERATOR_H

#include <iterator>
#include <string>

#include <xapian/base.h>
#include <xapian/derefwrapper.h>
#include <xapian/types.h>
#include <xapian/visibility.h>

namespace Xapian {

/// @private @internal A proxy class for an end PositionIterator.
class PositionIteratorEnd_ { };

/// Class for iterating over term positions.
class XAPIAN_VISIBILITY_DEFAULT PositionIterator {
  public:
    /// Class representing the PositionIterator internals.
    class Internal;
    /// @private @internal Reference counted internals.
    Xapian::Internal::RefCntPtr<Internal> internal;

    /// @private @internal Construct given internals.
    explicit PositionIterator(Internal *internal_);

    /// Copy constructor.
    PositionIterator(const PositionIterator & o);

    /// @internal Copy from an end iterator proxy.
    PositionIterator(const PositionIteratorEnd_ &);

    /// Assignment.
    PositionIterator & operator=(const PositionIterator & o);

    /// @internal Assignment of an end iterator proxy.
    PositionIterator & operator=(const PositionIteratorEnd_ &);

    /** Default constructor.
     *
     *  Creates an uninitialised iterator, which can't be used before being
     *  assigned to, but is sometimes syntactically convenient.
     */
    PositionIterator();

    /// Destructor.
    ~PositionIterator();

    /// Return the term position at the current iterator position.
    Xapian::termpos operator*() const;

    /// Advance the iterator to the next position.
    PositionIterator & operator++();

    /// Advance the iterator to the next position (postfix version).
    DerefWrapper_<Xapian::termpos> operator++(int) {
	Xapian::termpos termpos(**this);
	operator++();
	return DerefWrapper_<Xapian::termpos>(termpos);
    }

    /** Advance the iterator to term position @a termpos.
     *
     *  If the specified position isn't in the stream being iterated, then
     *  the iterator is moved to the next term position after @a termpos.
     */
    void skip_to(Xapian::termpos termpos);

    /// Return a string describing this object.
    std::string get_description() const;

    /** @private @internal PositionIterator is what the C++ STL calls an
     *  input_iterator.
     *
     *  The following typedefs allow std::iterator_traits<> to work so that
     *  this iterator can be used with with STL.
     *
     *  These are deliberately hidden from the Doxygen-generated docs, as the
     *  machinery here isn't interesting to API users.  They just need to know
     *  that Xapian iterator classes are compatible with the STL.
     */
    // @{
    /// @private
    typedef std::input_iterator_tag iterator_category;
    /// @private
    typedef Xapian::termpos value_type;
    /// @private
    typedef Xapian::termpos_diff difference_type;
    /// @private
    typedef Xapian::termpos * pointer;
    /// @private
    typedef Xapian::termpos & reference;
    // @}
};

/// Equality test for PositionIterator objects.
inline bool
operator==(const PositionIterator &a, const PositionIterator &b)
{
    // Use a pointer comparison - this ensures both that (a == a) and correct
    // handling of end iterators (which we ensure have NULL internals).
    return a.internal.get() == b.internal.get();
}

/// @internal Equality test for PositionIterator object and end iterator.
inline bool
operator==(const PositionIterator &a, const PositionIteratorEnd_ &)
{
    return a.internal.get() == NULL;
}

/// @internal Equality test for PositionIterator object and end iterator.
inline bool
operator==(const PositionIteratorEnd_ &a, const PositionIterator &b)
{
    return b == a;
}

/// @internal Equality test for end iterators.
inline bool
operator==(const PositionIteratorEnd_ &, const PositionIteratorEnd_ &)
{
    return true;
}

/// Inequality test for PositionIterator objects.
inline bool
operator!=(const PositionIterator &a, const PositionIterator &b)
{
    return !(a == b);
}

/// @internal Inequality test for PositionIterator object and end iterator.
inline bool
operator!=(const PositionIterator &a, const PositionIteratorEnd_ &b)
{
    return !(a == b);
}

/// @internal Inequality test for PositionIterator object and end iterator.
inline bool
operator!=(const PositionIteratorEnd_ &a, const PositionIterator &b)
{
    return !(a == b);
}

/// @internal Inequality test for end iterators.
inline bool
operator!=(const PositionIteratorEnd_ &a, const PositionIteratorEnd_ &b)
{
    return !(a == b);
}

}

#endif // XAPIAN_INCLUDED_POSITIONITERATOR_H
