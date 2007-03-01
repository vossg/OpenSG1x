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

#include <OSGGL.h>

#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>
#include <OSGRenderAction.h>

#include <OSGIntersectActor.h>

#include "OSGTransform.h"

OSG_USING_NAMESPACE

/*! \class osg::Transform

  The basic Transformation class. Just keeps a single matrix. For more complex
  behaviour, see its descendents.

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Transform::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & MatrixFieldMask)
    {
        invalidateVolume();
    }

    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void Transform::accumulateMatrix(Matrix &result)
{
    result.mult(getMatrix());
}

void Transform::adjustVolume(Volume &volume)
{
    volume.transform(_sfMatrix.getValue());
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Transform::dump(      UInt32    uiIndent,
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Transform::Transform(void) :
    Inherited()
{
}

Transform::Transform(const Transform &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Transform::~Transform(void)
{
}


/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE Transform::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    // should use the chunk, but it's not updated yet
    glPushMatrix ();
    glMultMatrixf(getMatrix().getValues());

    da->selectVisibles();

    return Action::Continue;
}

Action::ResultE Transform::drawLeave(Action *)
{
    glPopMatrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

Action::ResultE Transform::intersectEnter(Action *action)
{
    // Use parent class for trivial reject
    if(Inherited::intersect(action) == Action::Skip)
        return Action::Skip;
    
    // Need to check children
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

Action::ResultE Transform::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

NewActionTypes::ResultE
Transform::intersectActorEnter(ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA        = dynamic_cast<IntersectActor *>(funcArg.getActor());
    Matrix          matrix     = this->getMatrix();
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

    matrix.invert();

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    transLine.setValue(pos, dir);

    pIA->beginEditState();
    {
        pIA->setRay        (transLine                           );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
Transform::intersectActorLeave(ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(funcArg.getActor());
    const Matrix   &matrix = this->getMatrix();
          Pnt3f     pos;
          Vec3f     dir;

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    pIA->beginEditState();
    {
        pIA->setRay        (Line(pos, dir)                      );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    return NewActionTypes::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE Transform::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pushVisibility();

    pAction->push_matrix(this->getMatrix());

    return Action::Continue;
}

Action::ResultE Transform::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->pop_matrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Transform::initMethod (void)
{
    DrawAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::drawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::drawLeave));


    IntersectAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::intersectEnter));

    IntersectAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::intersectLeave));


    RenderAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            TransformPtr    ,
            CNodePtr        ,
            Action         *>(&Transform::renderLeave));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Transform::intersectActorEnter),
        getClassType());

    IntersectActor::regClassLeave(
        osgTypedMethodFunctor2BaseCPtr<
          NewActionTypes::ResultE,
          TransformPtr           ,
          NodeCorePtr            ,
          ActorBase::FunctorArgumentType &>(&Transform::intersectActorLeave),
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
    static Char8 cvsid_hpp[] = OSGTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGTRANSFORM_INLINE_CVSID;
}
