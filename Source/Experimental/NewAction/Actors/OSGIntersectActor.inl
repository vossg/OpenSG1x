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

#include <OSGTransform.h>


#include <OSGSimpleAttachments.h>

OSG_BEGIN_NAMESPACE

inline void
IntersectActor::reset(void)
{
    setHitDistance     (TypeTraits<Real32>::getMax());
    setHitObject       (NullFC                      );
    setHitTriangleIndex(-1                          );
    setHitNormal       (Vec3f(0.0, 0.0, 0.0)        );
    setScaleFactor     (1.0                         );
    Inherited::setHit  (false                       );
}

inline void
IntersectActor::setHit(Real32 hitDist,   NodePtr pHitObj, Int32 iTriIndex,
                       Vec3f  hitNormal                                   )
{
    if((hitDist < 0               ) ||
       (hitDist > getHitDistance()) ||
       (hitDist > getMaxDistance())   )
    {
        return;
    }

    beginEditState();
    {
        this->setHitDistance     (hitDist  );
        this->setHitObject       (pHitObj  );
        this->setHitTriangleIndex(iTriIndex);
        this->setHitNormal       (hitNormal);
        this->Inherited::setHit  (true     );
    }
    endEditState  ();
}

inline void
IntersectActor::prioritizeChildren(void)
{
    getAction()->setUseActiveChildrenList(true);

    ActiveChildrenList *pACL = getAction()->getActiveChildrenList();

    ActiveChildrenList::MFNodePtrIt itNodes  = pACL->beginChildren();
    ActiveChildrenList::MFNodePtrIt endNodes = pACL->endChildren  ();
    Real32                          bvEnter;
    Real32                          bvExit;

    for(; itNodes != endNodes; ++itNodes)
    {
        const DynamicVolume &dynVol = (*itNodes)->getVolume(true);

        if((dynVol.intersect(getRay(), bvEnter, bvExit) == true) &&
           (bvEnter * getScaleFactor() <  getHitDistance()     )    )
        {
            pACL->setPriority(itNodes, -bvEnter * getScaleFactor());
        }
        else
        {
            pACL->setActive(itNodes, false);
        }
    }
}

OSG_END_NAMESPACE

#define OSGINTERSECTACTOR_INLINE_CVSID "@(#)$Id:"

