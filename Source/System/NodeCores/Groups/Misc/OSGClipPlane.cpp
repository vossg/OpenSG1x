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
#include <OSGRenderAction.h>
#include "OSGClipPlane.h"

OSG_USING_NAMESPACE

/*! \class osg::ClipPlane
    \ingroup GrpSystemNodeCoresClipPlanes
    
*/

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

SClipPlaneChunkPtr ClipPlane::getChunk(void)
{
    return _pChunk;
}

void ClipPlane::makeChunk(void)
{
    if(_pChunk == NullFC)
    {
        _pChunk = SClipPlaneChunk::create();
    }

    _pChunk->setEquation(getEquation());
}

/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void ClipPlane::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void ClipPlane::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ClipPlane::ClipPlane(void) :
     Inherited(),
    _pChunk   (NullFC)
{
}

ClipPlane::ClipPlane(const ClipPlane &source) :
     Inherited(source),
    _pChunk   (source._pChunk)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ClipPlane::~ClipPlane(void)
{
    if(_pChunk != NullFC)
        subRefCP(_pChunk);
}

/*-------------------------------------------------------------------------*/
/*                               Drawing                                   */

#if 0
Action::ResultE ClipPlane::drawEnter(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    DrawAction *da    = dynamic_cast<DrawAction *>(action);
    GLenum      clipplane = GL_CLIP_PLANE0 + da->getClipPlaneCount();

    da->incClipPlaneCount();

    // add the matrix to get into the beacon's coordinate system onto the stack

    Matrix fromworld;
    Matrix tobeacon;

    action->getActNode()->getToWorld(fromworld);
    fromworld.invert();

    NodePtr beacon = getBeacon();

    if(beacon == NullFC)
    {
        SINFO << "draw: no beacon set!" << std::endl;

        glPushMatrix();
    }
    else
    {
        getBeacon()->getToWorld(tobeacon);
    
        tobeacon.mult(fromworld);
    
        glPushMatrix();
        glMultMatrixf(tobeacon.getValues());
    }

    GLdouble glEq[4];
    Vec4f   & eq = getEquation();
    glEq[0] = eq[0];
    glEq[1] = eq[1];
    glEq[2] = eq[2];
    glEq[3] = eq[3];

    glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
    glEnable (clipplane);

    da->selectVisibles();

    return Action::Continue;
}

Action::ResultE ClipPlane::drawLeave(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    DrawAction *da = dynamic_cast<DrawAction *>(action);

    da->decClipPlaneCount();

    GLenum clipplane = GL_CLIP_PLANE0 + da->getClipPlaneCount();

    glDisable(clipplane);

    return Action::Continue;
}
#endif

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE ClipPlane::renderEnter(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    // ok we can cull the clipping plane only when it is invisible.
    if (pAction->pushVisibility())
    {
        if(pAction->selectVisibles() == 0)
        {
            pAction->popVisibility();
            return Action::Skip;
        }
    }

    pAction->dropClipPlane(this);

    return Action::Continue;
}

Action::ResultE ClipPlane::renderLeave(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->undropClipPlane(this);

    pAction->popVisibility();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

//! initialize the static features of the class, e.g. action callbacks

void ClipPlane::initMethod(void)
{
    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ClipPlanePtr  , 
            CNodePtr             ,  
            Action              *>(&ClipPlane::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            OSG::Action::ResultE,
            ClipPlanePtr  , 
            CNodePtr             ,  
            Action              *>(&ClipPlane::renderLeave));
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGClipPlane.cpp,v 1.1 2007/04/26 15:22:01 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGCLIPPLANE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCLIPPLANE_INLINE_CVSID;
}

