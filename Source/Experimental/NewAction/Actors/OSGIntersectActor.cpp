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

#include "OSGIntersectActor.h"

OSG_USING_NAMESPACE

IntersectActor *
IntersectActor::create(void)
{
    IntersectActor *pActor = new IntersectActor();

    pActor->createState();
    
    return pActor;
}

IntersectActor::~IntersectActor(void)
{
}

IntersectActor::ResultE
IntersectActor::start(void)
{
    setHit        (false );
    setScaleFactor(1     );

    setHitDist    (Inf   );
    setHitObject  (NullFC);
    setHitTriangle(-1    );

    return NewActionBase::Continue;
}

IntersectActor::IntersectActor(void)
    : Inherited()
{
}

IntersectActor::ResultE
IntersectActor::defaultFunctor(NodeCorePtr &, ActorBase *pActor)
{
    FDEBUG(("IntersectActor::defaultFunctor: \n"));

          IntersectActor *pIA    = dynamic_cast<IntersectActor *>(pActor);
    const Line           &line   = pIA->getLine    ();
    const DynamicVolume  &dynVol = pIA->getCurrNode()->getVolume(true);

    pIA->setUseNodeList();

    ActiveNodeListIt itNodes = pIA->beginNodes();
    ActiveNodeListIt end     = pIA->endNodes  ();
    
    if(!dynVol.intersect(line))
    {
        for(; itNodes != end; ++itNodes)
        {
            itNodes.deactivate();
        }
    }
    else
    {
        pIA->priorizeChildren(itNodes, end);
    }

    return NewActionBase::Continue;
}

void
IntersectActor::priorizeChildren(ActiveNodeListIt  itNodes,
                                 ActiveNodeListIt  endNodes)
                                 
{
    const DynamicVolume *pDynVol     = NULL;
    const Line           line        = this->getLine       ();
          Real32         hitDist     = this->getHitDist    ();
          Real32         scaleFactor = this->getScaleFactor();
          Real32         bvEnter;
          Real32         bvExit; 

    for(; itNodes != endNodes; ++itNodes)
    {
        pDynVol = &(itNodes.getNode()->getVolume(true));

        if((pDynVol->intersect(line, bvEnter, bvExit)) &&
           ((bvEnter * scaleFactor) <= hitDist       )   )
        {
            itNodes.setPriority(-bvEnter * scaleFactor);
        }
        else
        {
            itNodes.deactivate();
        }
    }
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
    static Char8 cvsid_cpp     [] = "@(#)$Id: $";
    static Char8 cvsid_hpp     [] = OSGINTERSECTACTOR_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGINTERSECTACTOR_INLINE_CVSID;
}

