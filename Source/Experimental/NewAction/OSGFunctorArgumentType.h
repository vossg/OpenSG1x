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

#ifndef _OSGFUNCTORARGUMENTTYPE_H_
#define _OSGFUNCTORARGUMENTTYPE_H_
#ifdef __sgi
#pragma once
#endif

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGTypedFunctors.h>
#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

class ActorBase;

namespace NewActionTypes
{
    class OSG_SYSTEMLIB_DLLMAPPING FunctorArgumentType
    {
        /*==== PUBLIC =======================================================*/
      public:
        /*-------------------------------------------------------------------*/
        /*! \name    Constructors                                            */
        /*! \{                                                               */

        inline FunctorArgumentType(      ActorBase           *pActor,
                                   const NodePtr             &pNode,
                                   UInt32     pass                   );

        /*! \}                                                               */
        /*-------------------------------------------------------------------*/
        /*! \name    Get/Set                                                 */
        /*! \{                                                               */

        inline ActorBase *getActor(      void             ) const;
        inline void       setActor(      ActorBase *pActor);
        
        inline NodePtr    getNode (      void             ) const;
        inline void       setNode (const NodePtr   &pNode );
        
        inline UInt32     getPass (      void             ) const;
        inline void       setPass (      UInt32     pass  );

        /*! \}                                                               */
        /*==== PRIVATE ======================================================*/
      private:
        ActorBase *_pActor;
        NodePtr    _pNode;
        UInt32     _pass;
    };
}

OSG_END_NAMESPACE

#include "OSGFunctorArgumentType.inl"

#define OSGFUNCTORARGUMENTTYPE_HEADER_CVSID "@(#)$Id: OSGFunctorArgumentType.h,v 1.1 2004/09/17 14:09:43 neumannc Exp $"

#endif /* _OSGFUNCTORARGUMENTTYPE_H_ */
