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

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include "OSGIntersectActor.h"

OSG_USING_NAMESPACE

//----------------------------------------------------------------------------
//    Create
//----------------------------------------------------------------------------

/*! Create a new instance of this actor.
 */

IntersectActor *
IntersectActor::create(void)
{
    return new IntersectActor();
}

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

/*! Destructor.
 */

IntersectActor::~IntersectActor(void)
{
}

//----------------------------------------------------------------------------
//    Misc
//----------------------------------------------------------------------------

/*! Reset all information about the hit object to default values.
 */

void
IntersectActor::reset(void)
{
    setHitDistance     (TypeTraits<Real32>::getMax());
    setHitObject       (NullFC                      );
    setHitTriangleIndex(-1                          );
    setHitNormal       (Vec3f(0.0, 0.0, 0.0)        );
    setScaleFactor     (1.0                         );
    Inherited::setHit  (false                       );
}

/*! This is a helper method for implementing functors, do not use it otherwise.
    It sets all relevant data about a hit object with one call.
    \warning This method may only be called when the actor is attached to an
    action.
 */

void
IntersectActor::setHit(
    Real32 hitDist, NodePtr pHitObj, Int32 triIndex, Vec3f hitNormal)
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
        this->setHitTriangleIndex(triIndex );
        this->setHitNormal       (hitNormal);
        this->Inherited::setHit  (true     );
    }
    endEditState  ();
}

/*! This is a helper method for implementing functors, do not use it otherwise.
    It assigns priorities to all children and extra children, so that objects
    close to the starting point of the ray are tested first.
    \warning This method may only be called when the actor is attached to an
    action.
 */

void
IntersectActor::setupChildrenPriorities(void)
{
    UInt32 numChildren      = getNumChildren     ();
    UInt32 numExtraChildren = getNumExtraChildren();

    Real32 scaleFactor      = getScaleFactor();
    Real32 hitDist          = getHitDistance();
    Real32 bvEnter;
    Real32 bvExit;

    setChildrenListEnabled(true);

    for(UInt32 i = 0; i < numChildren; ++i)
    {
        const DynamicVolume &dynVol = getChild(i)->getVolume(true);

        if((dynVol.intersect(getRay(), bvEnter, bvExit) == true   ) &&
           (bvEnter * scaleFactor                       <  hitDist)   )
        {
            setChildPriority(i, -bvEnter * scaleFactor);
        }
        else
        {
            setChildActive  (i, false);
        }
    }

    for(UInt32 i = 0; i < numExtraChildren; ++i)
    {
        const DynamicVolume &dynVol = getExtraChild(i)->getVolume(true);

        if((dynVol.intersect(getRay(), bvEnter, bvExit) == true   ) &&
           (bvEnter * scaleFactor                       <  hitDist)   )
        {
            setExtraChildPriority(i, -bvEnter * scaleFactor);
        }
        else
        {
            setExtraChildActive  (i, false);
        }
    }
}

//----------------------------------------------------------------------------
//    Constructors
//----------------------------------------------------------------------------

/*! Constructor.
 */

IntersectActor::IntersectActor(void)
    : Inherited()
{
}

/*------------------------------------------------------------------------*/
/*    cvs id's                                                            */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id:";
    static Char8 cvsid_hpp     [] = OSGINTERSECTACTOR_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGINTERSECTACTOR_INLINE_CVSID;
}


#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
