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
#include "Boolean.hh"
#include "PoissonNeuron.hh"
#include "Time.hh"

NRS::Simulator::PoissonNeuron::PoissonNeuron( std::string aName,
					      const Base::NodeFactory *aNF ) :
  Unit::Time( aName, Base::VariableNodeDirector::getDirector().
	      getVariableManager( aNF->getType() ) ),
  Base::Node( aName, Base::Variable::getVNID(), aNF )
{
}

NRS::Simulator::PoissonNeuron::~PoissonNeuron()
{
}

void NRS::Simulator::PoissonNeuron::doReset()
{
  if (iVariableMap.find( "MeanSG" ) != iVariableMap.end())
    {
      dynamic_cast< Unit::Time* >( iVariableMap[ "MeanSG" ] )->
	setDefault( iValue );
    }
  if (iVariableMap.find( "enable" ) != iVariableMap.end())
    {
      dynamic_cast< Type::Boolean* >( iVariableMap[ "enable" ] )->
	setDefault( true );
    }
}

void NRS::Simulator::PoissonNeuron::doObserve( integer_t aRef )
{
  iSendMessage = true;
  iValue = *iInput[aRef];
  reset();
}
