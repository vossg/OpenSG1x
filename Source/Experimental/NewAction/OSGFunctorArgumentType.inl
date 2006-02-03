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



OSG_BEGIN_NAMESPACE



//----------------------------------------------------------------------------

//    Constructors

//----------------------------------------------------------------------------



inline

NewActionTypes::FunctorArgumentType::FunctorArgumentType(

    ActorBase *pActor, const NodePtr &pNode, UInt32 pass)

    

    : _pActor(pActor),

      _pNode (pNode ),

      _pass  (pass  )

{

}



//----------------------------------------------------------------------------

//    Get/Set

//----------------------------------------------------------------------------



inline ActorBase *

NewActionTypes::FunctorArgumentType::getActor(void) const

{

    return _pActor;

}



inline void

NewActionTypes::FunctorArgumentType::setActor(ActorBase *pActor)

{

    _pActor = pActor;

}



inline NodePtr

NewActionTypes::FunctorArgumentType::getNode(void) const

{

    return _pNode;

}



inline void

NewActionTypes::FunctorArgumentType::setNode(const NodePtr &pNode)

{

    _pNode = pNode;

}



inline UInt32

NewActionTypes::FunctorArgumentType::getPass(void) const

{

    return _pass;

}



inline void

NewActionTypes::FunctorArgumentType::setPass(UInt32 pass)

{

    _pass = pass;

}



OSG_END_NAMESPACE



#define OSGFUNCTORARGUMENTTYPE_INLINE_CVSID "@(#)$Id: OSGFunctorArgumentType.inl,v 1.2 2006/02/03 15:28:47 tbeer Exp $"

