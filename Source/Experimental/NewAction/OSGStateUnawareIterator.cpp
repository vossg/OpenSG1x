/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include "OSGStateUnawareIterator.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

StateUnawareIterator::~StateUnawareIterator(void)
{
}

void
StateUnawareIterator::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorAdd(pActor, uiActorId);
}
void
StateUnawareIterator::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorSub(pActor, uiActorId);
}

void
StateUnawareIterator::receiveActorsClear(void)
{
    Inherited::receiveActorsClear();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

StateUnawareIterator::StateUnawareIterator(void)
    : Inherited()
{
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGStateUnawareIterator.cpp,v 1.2 2003/10/10 14:27:44 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGSTATEUNAWAREITERATOR_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTATEUNAWAREITERATOR_INLINE_CVSID;
}
