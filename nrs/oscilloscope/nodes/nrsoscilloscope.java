/*
 * Copyright (C) 2006 Edinburgh University
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
package nrs.oscilloscope.nodes;

/** Application entry-point for Oscilloscope component.
 *
 * @author Theophile Gonos
 *
*/

public class nrsoscilloscope
{

  /**
   * The main method for invoking the Oscilloscope component. This class
   * creates an instance of {@link AppManager} which is responsible for
   * managing the application.
   *
   * @param args a <code>String[]</code> holding all the command line
   * arguments.
   */
  public static void main(String[] args)
  {
    PackageLogger.log.info(AppManager.NAME
                           + " started. Version " + AppManager.VERSION);

    AppManager appManager = AppManager.getInstance();
    appManager.startup(args);
  }
}
