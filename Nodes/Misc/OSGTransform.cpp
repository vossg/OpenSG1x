/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <GL/gl.h>

#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>
#include <OSGRenderAction.h>

#include "OSGTransform.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGTRANSFORM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGTRANSFORM_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Transform

  The basic Transformation class. Just keeps a single matrix. For more complex 
  behaviour, see its descendents.     

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Transform::changed(BitVector, ChangeMode)
{
    invalidateVolume();
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
/*                         Transform Draw                                  */

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE Transform::TransformDrawEnter(CNodePtr &cnode, 
                                                   Action   *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}

OSG::Action::ResultE Transform::TransformDrawLeave(CNodePtr &cnode, 
                                                   Action   *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}

OSG::Action::ResultE Transform::TransformIntEnter(CNodePtr &cnode, 
                                                  Action   *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRIE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersectEnter(pAction);
    }
}

OSG::Action::ResultE Transform::TransformIntLeave(CNodePtr &cnode, 
                                                  Action   *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRIL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersectLeave(pAction);
    }
}
#endif

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
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m  = this->getMatrix();

    m.invert();
    
    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);
    
    ia->setLine(Line(pos, dir), ia->getMaxDist());

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

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE Transform::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->push_matrix(this->getMatrix());

    pAction->selectVisibles();

    return Action::Continue;
}

Action::ResultE Transform::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pop_matrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Transform::initMethod (void)
{
#ifndef OSG_NOFUNCTORS

    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::drawEnter));
    
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::drawLeave));


    IntersectAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::intersectEnter));

    IntersectAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::intersectLeave));


    RenderAction::registerEnterDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  TransformPtr, 
                                  Action *>(&Transform::renderLeave));

#else

    DrawAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Transform::TransformDrawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Transform::TransformDrawLeave));

    IntersectAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Transform::TransformIntEnter));

    IntersectAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Transform::TransformIntLeave));

#endif
}
