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

#ifndef _OSGSTATEUNAWAREITERATOR_H_
#define _OSGSTATEUNAWAREITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGIteratorBase.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING StateUnawareIterator : public IteratorBase
{
  public:
    virtual ~StateUnawareIterator(void) = 0;
    
    virtual void receiveActorAdd   (ActorBase *pActor,   UInt32 uiActorId) = 0;
    virtual void receiveActorSub   (ActorBase *pActor,   UInt32 uiActorId) = 0;
    virtual void receiveActorsClear(void                                 ) = 0;

    virtual void receiveStateRead  (UInt32     uiActorId                 ) = 0;
    virtual void receiveStateWrite (UInt32     uiActorId                 ) = 0;

  protected:
    StateUnawareIterator(void);

  private:
    typedef IteratorBase Inherited;
};

OSG_END_NAMESPACE

#include "OSGStateUnawareIterator.inl"

#define OSGSTATEUNAWAREITERATOR_HEADER_CVSID "@(#)$Id: OSGStateUnawareIterator.h,v 1.2 2003/10/10 14:27:44 neumannc Exp $"

#endif /* _OSGSTATEUNAWAREITERATOR_H_ */
