/** @file  termiterator.h
 *  @brief Class for iterating over a list of terms
 */
/* Copyright (C) 2007,2008,2009,2010 Olly Betts
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

#ifndef XAPIAN_INCLUDED_TERMITERATOR_H
#define XAPIAN_INCLUDED_TERMITERATOR_H

#include <iterator>
#include <string>

#include <xapian/base.h>
#include <xapian/derefwrapper.h>
#include <xapian/positioniterator.h>
#include <xapian/types.h>
#include <xapian/visibility.h>

namespace Xapian {

/// @private @internal A proxy class for an end TermIterator.
class TermIteratorEnd_ { };

/// Class for iterating over a list of terms.
class XAPIAN_VISIBILITY_DEFAULT TermIterator {
  public:
    /// Class representing the TermIterator internals.
    class Internal;
    /// @private @internal Reference counted internals.
    Xapian::Internal::RefCntPtr<Internal> internal;

    /// @private @internal Construct given internals.
    explicit TermIterator(Internal *internal_);

    /// Copy constructor.
    TermIterator(const TermIterator & o);

    /// @internal Copy from an end iterator proxy.
    TermIterator(const TermIteratorEnd_ &);

    /// Assignment.
    TermIterator & operator=(const TermIterator & o);

    /// @internal Assignment of an end iterator proxy.
    TermIterator & operator=(const TermIteratorEnd_ &);

    /** Default constructor.
     *
     *  Creates an uninitialised iterator, which can't be used before being
     *  assigned to, but is sometimes syntactically convenient.
     */
    TermIterator();

    /// Destructor.
    ~TermIterator();

    /// Return the term at the current position.
    std::string operator*() const;

    /// Return the wdf for the term at the current position.
    Xapian::termcount get_wdf() const;

    /// Return the term frequency for the term at the current position.
    Xapian::doccount get_termfreq() const;

    /// Return the length of the position list for the current position.
    Xapian::termcount positionlist_count() const;

    /// Return a PositionIterator for the current term.
    PositionIterator positionlist_begin() const;

    /// Return an end PositionIterator for the current term.
    PositionIteratorEnd_ positionlist_end() const {
	return PositionIteratorEnd_();
    }

    /// Advance the iterator to the next position.
    TermIterator & operator++();

    /// Advance the iterator to the next position (postfix version).
    DerefWrapper_<std::string> operator++(int) {
	const std::string & term(**this);
	operator++();
	return DerefWrapper_<std::string>(term);
    }

    /** Advance the iterator to term @a term.
     *
     *  If the iteration is over an unsorted list of terms, then this method
     *  will throw Xapian::InvalidOperationError.
     *
     *  If the specified term isn't in the stream being iterated, then
     *  the iterator is moved to the next term after @a term.
     */
    void skip_to(const std::string &term);

    /// Return a string describing this object.
    std::string get_description() const;

    /** @private @internal TermIterator is what the C++ STL calls an
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
    typedef std::string value_type;
    /// @private
    typedef Xapian::termcount_diff difference_type;
    /// @private
    typedef std::string * pointer;
    /// @private
    typedef std::string & reference;
    // @}
};

/// Equality test for TermIterator objects.
inline bool
operator==(const TermIterator &a, const TermIterator &b)
{
    // Use a pointer comparison - this ensures both that (a == a) and correct
    // handling of end iterators (which we ensure have NULL internals).
    return a.internal.get() == b.internal.get();
}

/// @internal Equality test for TermIterator object and end iterator.
inline bool
operator==(const TermIterator &a, const TermIteratorEnd_ &)
{
    return a.internal.get() == NULL;
}

/// @internal Equality test for TermIterator object and end iterator.
inline bool
operator==(const TermIteratorEnd_ &a, const TermIterator &b)
{
    return b == a;
}

/// @internal Equality test for end iterators.
inline bool
operator==(const TermIteratorEnd_ &, const TermIteratorEnd_ &)
{
    return true;
}

/// Inequality test for TermIterator objects.
inline bool
operator!=(const TermIterator &a, const TermIterator &b)
{
    return !(a == b);
}

/// @internal Inequality test for TermIterator object and end iterator.
inline bool
operator!=(const TermIterator &a, const TermIteratorEnd_ &b)
{
    return !(a == b);
}

/// @internal Inequality test for TermIterator object and end iterator.
inline bool
operator!=(const TermIteratorEnd_ &a, const TermIterator &b)
{
    return !(a == b);
}

/// @internal Inequality test for end iterators.
inline bool
operator!=(const TermIteratorEnd_ &a, const TermIteratorEnd_ &b)
{
    return !(a == b);
}

}

#endif // XAPIAN_INCLUDED_TERMITERATOR_H
