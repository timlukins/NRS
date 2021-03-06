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

#include "FloatSegment.hh"
#include "Exception.hh"
#include "MessageFunctionObject.hh"
#include "VariableNodeDirector.hh"
#include "SpikingNeuronITotal.hh"

NRS::Simulator::SpikingNeuronITotal::SpikingNeuronITotal( std::string aName ) : 
  Unit::Current( aName ), 
  iBaseGReference(0), iBaseGValuePtr(NULL), iBaseGValue(0),
  iBaseVReference(0), iBaseVValuePtr(NULL), iBaseVValue(0)
{}

NRS::Simulator::SpikingNeuronITotal::~SpikingNeuronITotal()
{
}

void NRS::Simulator::SpikingNeuronITotal::addReaction( integer_t aReference )
{
  bool success = false;

  for (unsigned_t num = 0; num < iMFOPtr.size(); ++num )
    {
      if (aReference == iMFOPtr[num]->getReference())
	{
	  std::string aName = getParentName() + ".BaseG";
	  if (aName == iMFOPtr[num]->getSourceName())
	    {
	      iBaseGReference = aReference;
	      iBaseGValuePtr = &dynamic_cast< Type::FloatSegment& >
		( Base::VariableNodeDirector::getDirector().
		  getVariable( iParentName + ".BaseG" )->getOutputLink().
		  getSegment( 0 ) ).
		iValue;
	      _DEBUG_( "Added " << aName );
	      success = true;
	    }
	  aName = getParentName() + ".BaseV";
	  if (aName == iMFOPtr[num]->getSourceName())
	    {
	      iBaseVReference = aReference;
	      iBaseVValuePtr = &dynamic_cast< Type::FloatSegment& >
		( Base::VariableNodeDirector::getDirector().
		  getVariable( iParentName + ".BaseV" )->getOutputLink().
		  getSegment( 0 ) ).
		iValue;
	      _DEBUG_( "Added " << aName );
	      success = true;
	    }
	  aName = getParentName() + ".IIn";
	  if (aName == iMFOPtr[num]->getSourceName())
	    {
	      iIInReference = aReference;
	      iIInValuePtr = &dynamic_cast< Type::FloatSegment& >
		( Base::VariableNodeDirector::getDirector().
		  getVariable( iParentName + ".IIn" )->getOutputLink().
		  getSegment( 0 ) ).
		iValue;
	      _DEBUG_( "Added " << aName );
	      success = true;
	    }
	}
    }
  if (!success)
    _ERROR_( "Cannot identify reaction from " << aReference );
}


void NRS::Simulator::SpikingNeuronITotal::react( integer_t aReference )
{
  if (aReference == iBaseGReference)
    {
      _ASSERT_( iBaseGValuePtr != NULL, "illegal call from NULL" );
      iBaseGValue = *iBaseGValuePtr;
    }
  else if (aReference == iBaseVReference)
    {
      _ASSERT_( iBaseVValuePtr != NULL, "illegal call from NULL" );
      iBaseVValue = *iBaseVValuePtr;
    }
  else if (aReference == iIInReference)
    {
      _ASSERT_( iIInValuePtr != NULL, "illegal call from NULL" );
      iIInValue = *iIInValuePtr;
    }
  else
    _WARN_( "Unrecognised observable " << aReference );
}

void NRS::Simulator::SpikingNeuronITotal::doRemoveSource( integer_t aReference )
{
  if (aReference == iBaseGReference)
    {
      iBaseGValuePtr = NULL;
      iBaseGValue = 0;
      iBaseGReference = 0;
    }
  else if (aReference == iBaseVReference)
    {
      iBaseVValuePtr = NULL;
      iBaseVValue = 0;
      iBaseVReference = 0;
    }
  else if (aReference == iIInReference)
    {
      iIInValuePtr = NULL;
      iIInValue = 0;
      iIInReference = 0;
    }
  else
    Type::Float::doRemoveSource( aReference );
}

void NRS::Simulator::SpikingNeuronITotal::doUpdate()
{
  
  iValue = iBaseGValue * iBaseVValue + iIInValue;
  _DEBUG_( "ITotal updated to " << iValue);
  iSendMessage = true; //Don;t necessarily want to send message before syn update
}

