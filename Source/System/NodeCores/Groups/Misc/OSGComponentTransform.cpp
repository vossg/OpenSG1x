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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGComponentTransform.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include <OSGIntersectActor.h>

OSG_USING_NAMESPACE

/*! \class osg::ComponentTransform
*/


/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void ComponentTransform::changed(BitVector whichField, UInt32 origin)
{
    ComponentTransformPtr ptr(*this);

    if((whichField & CenterFieldMask          ) ||
       (whichField & RotationFieldMask        ) ||
       (whichField & ScaleFieldMask           ) ||
       (whichField & ScaleOrientationFieldMask) ||
       (whichField & TranslationFieldMask     )  )
    {
        beginEditCP(ptr, MatrixFieldMask);
        {
            getMatrix().setTransform(getTranslation     (),
                                     getRotation        (),
                                     getScale           (),
                                     getScaleOrientation(),
                                     getCenter          ());
        }
        endEditCP  (ptr, MatrixFieldMask);
    }

    Inherited::changed(whichField, origin);
}

void ComponentTransform::dump(      UInt32    uiIndent,
                              const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ComponentTransform::ComponentTransform(void) :
    Inherited()
{
    _sfScale.getValue().setValues(1.f, 1.f, 1.f);
}

ComponentTransform::ComponentTransform(const ComponentTransform &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ComponentTransform::~ComponentTransform(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void ComponentTransform::initMethod (void)
{
    DrawAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::drawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::drawLeave));


    RenderAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::renderLeave));

    IntersectAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::intersectEnter));

    IntersectAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ComponentTransformPtr  ,
            CNodePtr               ,
            Action                *>(&ComponentTransform::intersectLeave));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            ComponentTransformPtr  ,
            NodeCorePtr            ,
            ActorBase::FunctorArgumentType &>(&ComponentTransform::intersectActorEnter),
        getClassType());

    IntersectActor::regClassLeave(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            ComponentTransformPtr  ,
            NodeCorePtr            ,
            ActorBase::FunctorArgumentType &>(&ComponentTransform::intersectActorLeave),
        getClassType());
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGCOMPONENTTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCOMPONENTTRANSFORM_INLINE_CVSID;
}


