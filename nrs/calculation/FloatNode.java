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

package nrs.calculation;

import nrs.core.base.Node;
import nrs.core.base.Variable;
import nrs.core.base.VariableManager;
import nrs.core.base.Message;

import nrs.core.type.FloatType;

/** Represents FloatNodes for the calculation component.  This class
 * inherits from {@link nrs.core.base.Node} to represent a node of the
 * NRS component.
 *
 * @author Thomas French
 * @author Sarah Cope
*/


public class FloatNode extends Node {
    

    // Inputs
    private FloatType m_varInput1, m_varInput2;

    // Output
    private FloatType m_varOut;
    
    // Names of inputs
    private String varName1, varName2;

    private int type;

    public FloatNode(VariableManager vm, String vnName, int type, String nodeType) {
        super(vm, vnName, nodeType);

        this.type = type;

        // Name must be the same as the one given in CSL file
        varName1 = vnName + ".Input1";

        m_varInput1 = new FloatType(vm, varName1, true, false){
                public void deliver(Message m)
                {
                    handleMessageAt_Input(m, this, checkType(m, this), varName1);
                }
                public void deliver(double d){
                    handleMessageAt_Input(d, varName1);
                }
                
            };


        // Add to the variable manager
        addVariable(varName1, m_varInput1);

        varName2 = vnName + ".Input2";

        m_varInput2 = new FloatType(vm, varName2, true, false){
                public void deliver(Message m)
                {
                    handleMessageAt_Input(m, this, checkType(m, this), varName2);
                }
                public void deliver(double d){
                    handleMessageAt_Input(d, varName2);
                }
                
            };

        // Add to the variable manager
        addVariable(varName2, m_varInput2);

        String varName = vnName + ".Output";

        m_varOut = new FloatType(vm, varName, true, false){
		public void deliver(Message m)
		{
		    handleMessageAt_Output();
		}
		public void deliver(double d){
                    
		    handleMessageAt_Output();
		}
		
	    };

        // Add to the variable manager
        addVariable(varName, m_varOut);

        
    }

   
    
     //----------------------------------------------------------------------//
     /** Deliver a {@link Message} to this <code>Node</code>.
     *
     * @param m Message to deliver to <code>Node</code>.
     */
    public void deliver(Message m){
	PackageLogger.log.fine("Received message at FloatNode: " 
			       + getVNName());
        
        if (m.hasField("Input1") && m.hasField("Input2")) {

            try {

                Double d = new Double(m.getField("Input1"));
                Double d2 = new Double(m.getField("Input2"));
                
                m_varInput1.setValue(d);
                m_varInput2.setValue(d2);

                setOutput();

            } 
            catch (NumberFormatException nfe){
                PackageLogger.log.warning("Error with message - not the right"
                                           + " format!");
            }
            
        }

    } 


    // Sets the output according to the node's type 
    private void setOutput() {
        double total = 0.0;
        

        
        switch(type) {
            
        case CalculationComponent.ADD:
            total = m_varInput1.getValue().doubleValue() + m_varInput2.getValue().doubleValue();
            break;

        case CalculationComponent.SUBTRACT:
            total = m_varInput1.getValue().doubleValue() - m_varInput2.getValue().doubleValue();
            break;

        case CalculationComponent.MULTIPLY:
            total = m_varInput1.getValue().doubleValue() * m_varInput2.getValue().doubleValue();
            break;

        case CalculationComponent.DIVIDE:
            total = m_varInput1.getValue().doubleValue() / m_varInput2.getValue().doubleValue();
        }

        // Set Add variable to the output
        m_varOut.setValue(total);

    }


    /**
     * Compares the {@link Message} type and the {@link Variable}
     * type. Returns true if they appear different (based on a
     * case-sensitive string comparison); returns false otherwise.
     */
    protected boolean checkType(Message m, Variable v){
      return !(m.getType().equals(v.getVNName()));
    }


   
     /**
     * Process the receipt of a message at the FloatNode Output variable.
     *
     *
     */
    public void handleMessageAt_Output(){
	PackageLogger.log.warning("Received message at Output variable."
				  +" This should not happen!");
    }



   //-----------------------------------------------------------------------//
    /**
     * Process the receipt of a message at the FloatNode Input variable.
     *
     * @param m the {@link Message} received
     * @param v the {@link Variable} receiving the message
     * @param diff true if <tt>m</tt> and <tt>v</tt> are of different
     * @param varName the name of the input variable the message was received on
     * types
     *
     */

    public void handleMessageAt_Input(Message m, Variable v, boolean diff, String varName) { 
	PackageLogger.log.fine("Received message at Input variable!"); 
        
	Double d;
        if (varName.equals(varName1)) {
             
            d = m_varInput1.extractData(m);
            
        } else {
            
            d = m_varInput2.extractData(m);
        }

        if (d != null ) {
            handleMessageAt_Input(d.doubleValue(), varName);
        } else {
            PackageLogger.log.warning("Null value received at " + varName);
        }	
    }

     /**
     * Process the receipt of a message at the FloatNode Input variable.
     *
     * @param d double value received
     * @param varName the name of the input variable the message was received on
     *
     */
    public void handleMessageAt_Input(double d, String varName){ 
	PackageLogger.log.fine("Received message at Input variable!");

        if (varName.equals(varName1)) {
             
            m_varInput1.setValue(d);

        } else {
            
            m_varInput2.setValue(d);
        }
       
        PackageLogger.log.fine("Set " + varName + " to " + d);

        setOutput();
    }
}
