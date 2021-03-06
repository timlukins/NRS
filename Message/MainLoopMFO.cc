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

#include "MainLoopMFO.hh"
#include "Variable.hh"

NRS::Message::MainLoopMFO::MainLoopMFO( std::string sourceName,
					Base::Variable *targetPtr ) :
  MessageFunctionObject( sourceName, targetPtr )
{
}

NRS::Message::MainLoopMFO::~MainLoopMFO()
{
}

void NRS::Message::MainLoopMFO::operator()()
{
  iTargetPtr->forceSend( true, true );
}

NRS::Message::MainLoopMFOGenerator::MainLoopMFOGenerator() :
  MFOGenerator()
{
}

NRS::Message::MainLoopMFOGenerator::~MainLoopMFOGenerator()
{
}

NRS::Base::MessageFunctionObject *
NRS::Message::MainLoopMFOGenerator::createMFO( std::string sourceName, 
					       Base::Variable *targetPtr )
{
  return new MainLoopMFO( sourceName, targetPtr );
}
