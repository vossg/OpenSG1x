/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/


#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <string>
#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBinaryDataHandler.h>
#include <OSGTime.h>

OSG_BEGIN_NAMESPACE

class ConnectionType;

class OSG_BASE_DLLMAPPING Connection:public BinaryDataHandler
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             Connection ( int zeroCopyThreshold );
    virtual ~Connection ( void                  ); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Connection functionaliy                    */
    /*! \{                                                                 */

    virtual std::string    bind           (const std::string &address) = 0;
    virtual void           accept         (      void                ) = 0;
    virtual void           connect        (const std::string &address) = 0;
    virtual void           wait           (      void                );
    virtual void           signal         (      void                );
    virtual UInt32         getChannelCount(      void                ) = 0;
    virtual void           selectChannel  (      void                ) = 0;
    virtual 
     const ConnectionType *getType        (      void                ) = 0;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BinaryDataHandler Inherited;

	// prohibit default functions (move to 'public' if you need one)
    Connection(const Connection &source);
    Connection& operator =(const Connection &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Connection *ConnectionP;

OSG_END_NAMESPACE

#include "OSGConnection.inl"

#define OSG_CONNECTION_HEADER_CVSID "@(#)$Id: $"

#endif /* _CONNECTION_H_ */
