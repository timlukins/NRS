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

#ifndef _QUERY_VNID_HH
#define _QUERY_VNID_HH

#include <string>

#include "Target.hh"
#include "Types.hh"
#include "Variable.hh"

namespace NRS
{
  namespace Message
  {
    class ReplyVNID;

    /// A special variable type to handle QueryVNID messages.
    /**
     *
     * The QueryVNID class represents all message senders and receivers
     * which deal with QueryVNID messages
     *
     **/
    class QueryVNID : public Base::Variable

    {
    public:
      /// Constructor for QueryVNID Variables.
      /**
       *
       * \param aName the name of the QueryVNID Variable being built.
       *
       **/
      QueryVNID( std::string aName );
      
      /// Destructor.
      virtual ~QueryVNID();

      /// Request a VNID from a VNName
      /**
       *
       * This method requests the QueryVNID variable to give the
       * VNID of another variable
       *
       * \param theTarget the variable to be queried
       * \param aMessageID id representing message, 0 if no data
       * \param aVNName name of variable whose ID we want
       *
       **/
      void request( Base::Target &theTarget,
		    unsigned_t aMessageID,
		    std::string aVNName );

    protected:
      /// New data is available to observe from a source
      /**
       *
       * \param aRef the reference the Observable was given to return
       *
       **/
      virtual void doObserve( integer_t aRef );

      /// resolve any dependency issues
      /**
       *
       * \returns whether all dependencies are resolved
       *
       **/
      virtual bool resolveComplexDependencies();

      /// Pointer to ReplyVNID variable, with which QueryVNID communicates
      ReplyVNID *iReplyVNIDPtr;

      /// Inbound return route
      const route_t &iInReturnRoute;

      /// Inbound return VNID
      const integer_t &iInReturnVNID;

      /// Inbound message id
      const integer_t &iInMsgID;

      /// Inbound vnname
      const std::string &iInVNName;

      /// Outbound return route
      route_t &iOutReturnRoute;

      /// Outbound return VNID
      integer_t &iOutReturnVNID;

      /// Outbound message id
      integer_t &iOutMsgID;

      /// Outbound vnname
      std::string &iOutVNName;
    };
  }
}

#endif //ndef _QUERY_VNID_HH
