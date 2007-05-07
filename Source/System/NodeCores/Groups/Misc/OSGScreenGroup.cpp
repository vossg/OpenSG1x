/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGScreenGroup.h"
#include "OSGDrawAction.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGViewport.h"
#include "OSGCamera.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ScreenGroup

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScreenGroup::initMethod (void)
{
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,  
            Action         *>(&ScreenGroup::drawEnter));
    
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,  
            Action         *>(&ScreenGroup::drawLeave));


    IntersectAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,  
            Action         *>(&ScreenGroup::intersectEnter));

    IntersectAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,   
            Action         *>(&ScreenGroup::intersectLeave));


    RenderAction::registerEnterDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,  
            Action         *>(&ScreenGroup::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            ScreenGroupPtr  , 
            CNodePtr        ,  
            Action         *>(&ScreenGroup::renderLeave));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScreenGroup::ScreenGroup(void) :
    Inherited()
{
}

ScreenGroup::ScreenGroup(const ScreenGroup &source) :
    Inherited(source)
{
}

ScreenGroup::~ScreenGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScreenGroup::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ScreenGroup::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScreenGroup NI" << std::endl;
}


/*------------------------- volume update -------------------------------*/

void ScreenGroup::adjustVolume( Volume & volume )
{
    Matrix m;
    m.setScale(0, 0, 1);
    volume.transform(m);
}

void ScreenGroup::accumulateMatrix(Matrix &result)
{
    result.mult(_camTransform);
}

void ScreenGroup::calcMatrix(      DrawActionBase *pAction,
                           const Matrix         &mToWorld,
                                 Matrix         &mResult)
{
    Viewport *viewport = pAction->getViewport();
    Matrix mToScreen;
    pAction->getCamera()->getWorldToScreen(mToScreen, *viewport);
    mToScreen.mult(mToWorld);

    Pnt3f origin(0.f, 0.f, 0.f);
    mToScreen.multFullMatrixPnt(origin);

    Pnt3f xAxis(1.f, 0.f, 0.f);
    mToScreen.multFullMatrixPnt(xAxis);
    Real32 scaleX =  2.f / viewport->getPixelWidth() / (xAxis - origin).length();

    Pnt3f yAxis(0.f, 1.f, 0.f);
    mToScreen.multFullMatrixPnt(yAxis);
    Real32 scaleY = 2.f / viewport->getPixelHeight() / (yAxis - origin).length();

    mResult.setScale(scaleX, scaleY, 1.f);
    mResult.setTranslate(0.375 * scaleX, 0.375 * scaleY, 0.f);
    _camTransform = mResult;
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE ScreenGroup::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    Matrix mMat;

    calcMatrix(da,     
               da->getActNode()->getToWorld(),
               mMat);

    // should use the chunk, but it's not updated yet
    glPushMatrix ();
    glMultMatrixf(mMat.getValues());

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    da->selectVisibles();

    return Action::Continue;
}

Action::ResultE ScreenGroup::drawLeave(Action *)
{
    glPopMatrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

Action::ResultE ScreenGroup::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

Action::ResultE ScreenGroup::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_camTransform);

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(ia->getLine().getPosition (), pos);
    m.multMatrixVec    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE ScreenGroup::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    Matrix mMat;

    calcMatrix(pAction, pAction->top_matrix(), mMat);

    pAction->push_matrix(mMat);

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    pAction->selectVisibles();

    return Action::Continue;
}

Action::ResultE ScreenGroup::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pop_matrix();

    return Action::Continue;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGScreenGroup.cpp,v 1.1 2007/05/07 11:50:36 pdaehne Exp $";
    static Char8 cvsid_hpp       [] = OSGSCREENGROUPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCREENGROUPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCREENGROUPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

