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

#ifndef _OSGACTORSTATECHUNK_H_
#define _OSGACTORSTATECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include "OSGActorBase.h"


OSG_BEGIN_NAMESPACE

// Simple wrapper for a fixed size array of ActorStateBase *
class OSG_SYSTEMLIB_DLLMAPPING ActorStateChunk
{
public:
    typedef ActorBase::ActorStateBase ActorStateBase;

    inline explicit  ActorStateChunk (      UInt32           uiSize  );
    inline           ActorStateChunk (const ActorStateChunk &source  );
    inline          ~ActorStateChunk (      void                     );
     
    inline ActorStateBase *getEntry  (      UInt32           uiIndex ) const;
    inline void            setEntry  (      UInt32           uiIndex, 
                                            ActorStateBase  *pState  );

    inline UInt32          getSize   (      void                     ) const;

    inline void            freeEntry (      UInt32            uiIndex);
    inline void            freeAll   (      void                     );

    inline bool            operator==(const ActorStateChunk  &other ) const;

private:  
    /*!\brief prohibit default function (move to 'public' if needed) */
           void            operator= (const ActorStateChunk &source  );

    UInt32           _uiSize;
    ActorStateBase **_pStatePtrArray;
};

OSG_END_NAMESPACE

#include "OSGActorStateChunk.inl"

#define OSGACTORSTATECHUNK_HEADER_CVSID "@(#)$Id: OSGActorStateChunk.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGACTORSTATECHUNK_H_ */
