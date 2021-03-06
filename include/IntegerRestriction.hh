/*
 * Copyright (C) 2005 Richard Reeve and Edinburgh University
 *
 *    This program is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU General Public License as
 *    published by the Free Software Foundation; either version 2 of
 *    the License, or (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public
 *    License along with this program; if not, write to the Free
 *    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA 02111-1307 USA
 *
 * For further information in the first instance contact:
 * Richard Reeve <richardr@inf.ed.ac.uk>
 *
 */

#ifndef _INTEGER_RESTRICTION_HH
#define _INTEGER_RESTRICTION_HH

#include <memory>
#include <iostream>
#include <string>

#include "Exception.hh"
#include "Types.hh"
#include "Restriction.hh"
#include "Limit.hh"

namespace NRS
{
  namespace Type
  {
    /// This is the base class for restrictions
    class IntegerRestriction : public Base::Restriction
    {
    public:
      /// Default constructor
      IntegerRestriction() : Restriction( Enum::Integer )
      {
      }

      /// Full constructor
      /**
       *
       * \param minRef minimum limit
       * \param maxRef maximum limit
       *
       **/
      IntegerRestriction( const Base::Limit< integer_t > &minRef,
			  const Base::Limit< integer_t > &maxRef ) :
	Restriction( Enum::Integer ), iMin( minRef ), iMax( maxRef )
      {
      }

      /// Destructor
      ~IntegerRestriction()
      {
      }
      
      /// Set min limit
      /**
       *
       * \param limit the minimum limit
       *
       **/
      void setMin( integer_t limit )
      {
	iMin.set( limit );

      }

      /// Clear min limit
      void clearMin()
      {
	iMin.clear();
      }

      /// Does it have a min limit?
      /**
       *
       * \return whether there is a minimum
       *
       **/
      bool hasMin() const
      {
	return iMin.hasLimit();
      }

      /// Get min limit if present
      /**
       *
       * \return the minimum limit if present
       *
       **/
      integer_t getMin() const
      {
	return iMin.get();

      }

      /// Set max limit
      /**
       *
       * \param limit the maximum limit
       *
       **/
      void setMax( integer_t limit )
      {
	iMax.set( limit );
      }

      /// Clear max limit
      void clearMax()
      {
	iMax.clear();
      }

      /// Does it have a max limit?
      /**
       *
       * \return whether there is a maximum
       *
       **/
      bool hasMax() const
      {
	return iMax.hasLimit();
      }

      /// Get max limit if present
      /**
       *
       * \return the maximum limit if present
       *
       **/
      integer_t getMax() const
      {
	return iMax.get();

      }

      /// Clone the restriction, pass over ownership to caller
      /**
       *
       * \return a copy of the restriction (not necessarily the base
       * class, otherwise we could just use the copy constructor)
       *
       **/
      virtual Restriction *clone() const
      {
	return new IntegerRestriction( *this );
      }

      /// get CSL for restriction
      /**
       *
       * \param csl the output stream to which the CSL description
       * should be output.
       *
       * \return the output stream to which the CSL description was
       * output.
       *
       **/
      virtual std::ostream &getCSL( std::ostream& csl ) const
      {
	if ( iMin.hasLimit() || iMax.hasLimit() )
	  {
	    csl << "<IntegerInfo ";

	    if (iMin.hasLimit())
	      csl << "minVal='" << iMin.get() << "' ";

	    if (iMax.hasLimit())
	      csl << "maxVal='" << iMax.get() << "' ";

	    csl << "/>" << std::endl;
	  }
	return csl;
      }

    private:
      /// Minimum limit
      Base::Limit< integer_t > iMin;

      /// Maximum limit
      Base::Limit< integer_t > iMax;
    };
  }
}

#endif //ndef _INTEGER_RESTRICTION_HH
