/*
 * Copyright (C) 2004 Edinburgh University
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
package nrs.ga.mutation;

import nrs.core.base.Node;
import nrs.core.base.VariableManager;
import nrs.core.base.Message;

import nrs.ga.rng.*;
import nrs.ga.base.PackageLogger;
import nrs.ga.base.DependencyException;

import java.util.ArrayList;

public abstract class MutationNode extends Node
{
  private int m_rate;
  
  protected RNGNode m_rng; 
  
  /** Constructor. 
   * Use {@link VariableManager} to suggest vnid and register node. 
   *
   * @param vmMan VariableManager to register with.
   * @param vnName vnName of this node.
   */
  public MutationNode(VariableManager vmMan, String vnName, String type){
    super(vmMan, vnName, type);
    
    m_rate = 0;
  }
    
  //---------------------------------------------------------------------//
  
  /** {@link Message} to deliver to this Node. */
  public void deliver(Message m){
    PackageLogger.log.fine("Received message at MutationNode!");
    
    //need to extract attributes - rate
    Integer rate = new Integer(Integer.parseInt(m.getField("rate")));
    
    if ( rate != null ){
      if ( rate.intValue() < 0 )
        m_rate = 0;
      else if ( rate.intValue() > 100 )
        m_rate = 100;
      else
        m_rate = rate.intValue();
      
      PackageLogger.log.fine("Mutation rate set at: " + m_rate);
    }
    else{
      PackageLogger.log.warning("Mutation rate not supplied!");
	}
  }
  //----------------------------------------------------------------------//

  /** Get mutation rate value. 
   * @return mutation rate.
   */
  protected final int getRate(){
    return m_rate;
  }
  
  public final void setRNGNode(RNGNode rng){
    m_rng = rng;
  }
  
  protected final RNGNode getRNGNode(){
    return m_rng;
  }
  
  /** Mutate - implemented by subclass.
   *
   * @param population list of Chromosomes in population.
   * @param index for elite (only with generational GA).
   */
  public abstract void mutate(ArrayList population, int index);
  
  /** Check dependencies for this node and all the nodes it contains. 
   *
   * @throws DependencyException thrown if any dependencies are not satisfied
   */
  public void checkDependencies() throws DependencyException {
    return; //has no dependencies
  }
}
