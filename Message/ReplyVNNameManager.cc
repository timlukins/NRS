/*
 * Copyright (C) 2004-5 Richard Reeve, Matthew Szenher and Edinburgh University
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

#include "AttributeLiterals.hh"
#include "Executive.hh"
#include "ReplyVNName.hh"
#include "ReplyVNNameManager.hh"
#include "Target.hh"
#include "TokenManager.hh"
#include "VariableNodeDirector.hh"

namespace
{
  NRS::Message::ReplyVNNameManager sRVNNameM;
}

NRS::Message::ReplyVNNameManager::ReplyVNNameManager() : 
  VariableManager( Literals::Object::REPLYVNNAME_VARIABLE(), "", 2 )
{
  Base::Executive::getExecutive().addStartupVariable( getMessageName(),
						      getMessageName() );
  iDescription = "The built-in message type for replies to requests "
    "for VNNames of variables or nodes from their VNIDs.";
}

void NRS::Message::ReplyVNNameManager::doConfigure()
{
  Base::VariableNodeDirector &theVND =
    Base::VariableNodeDirector::getDirector();

  iSegmentDescription[0] =
    theVND.getVariableManager( Literals::Type::INTEGER() ).
    getSegmentDescription( 0 );
  iSegmentDescription[0].setAttributeName( Literals::Attribute::REPLYMSGID(),
					   "Reply Message ID" );

  iSegmentDescription[1] =
    theVND.getVariableManager( Literals::String::TOKEN() ).
    getSegmentDescription( 0 );
  iSegmentDescription[1].setAttributeName( Literals::Attribute::VNNAME(),
					   "VNName reply" );
}

void
NRS::Message::ReplyVNNameManager::createVariable( const std::string &aName )
  const
{
  new ReplyVNName ( aName );
}
