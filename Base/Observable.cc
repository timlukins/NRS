/*
 * Copyright (C) 2004 Richard Reeve, Matthew Szenher and Edinburgh University
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

#pragma implementation
#include "Observable.hh"
#include "Types.hh"

NRS::Base::Observable::Observable()
{
}

NRS::Base::Observable::~Observable()
{
  while (!iObserverPtrList.empty())
    {
      iObserverPtrList.begin()->first->
	removeObservable( iObserverPtrList.begin()->second );
      iObserverPtrList.pop_front();
    }
}

void
NRS::Base::Observable::addObserver( Observer *anObserverPtr,
				    integer_t aReference )
{
  iObserverPtrList.
    push_back( std::pair< Observer*, integer_t >( anObserverPtr,
						   aReference ) );
}

void
NRS::Base::Observable::removeObserver( Observer *anObserverPtr,
				       integer_t aReference )
{
  typeof( iObserverPtrList.begin() ) anIter = iObserverPtrList.begin();
  while ((anIter != iObserverPtrList.end()) &&
	 ((anIter->first != anObserverPtr) || (anIter->second != aReference)))
    anIter++;
  if (anIter != iObserverPtrList.end())
    iObserverPtrList.erase( anIter );
}
