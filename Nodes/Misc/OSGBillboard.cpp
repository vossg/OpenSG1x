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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <GL/gl.h>

#include "OSGBillboard.h"
#include "OSGDrawAction.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGCamera.h"
#include "OSGNode.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGBILLBOARD_HEADER_CVSID;
    static char cvsid_inl[] = OSGBILLBOARD_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Billboard

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Billboard::Billboard(void) :
    Inherited()
{
}

//! Copy Constructor

Billboard::Billboard(const Billboard &source) :
    Inherited(source)
{
}

//! Destructor

Billboard::~Billboard(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Billboard::initMethod (void)
{
#ifndef OSG_NOFUNCTORS

    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::drawEnter));
    
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::drawLeave));


    IntersectAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::intersectEnter));

    IntersectAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::intersectLeave));


    RenderAction::registerEnterDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  BillboardPtr, 
                                  Action *>(&Billboard::renderLeave));

#endif
}

//! react to field changes

void Billboard::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void Billboard::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Billboard NI" << endl;
}

void Billboard::calcMatrix(DrawActionBase *pAction, Matrix &mResult)
{
    Pnt3f eyepos(0.f, 0.f, 0.f);
    Pnt3f objpos(0.f, 0.f, 0.f);

    Vec3f vDir;
    Vec3f n(0.f, 0.f, 1.f);

    Quaternion q1;

    Matrix mCamToWorld = pAction->getCamera()->getBeacon()->getToWorld();
    Matrix mToWorld    = pAction->getActNode()->getToWorld();

    mResult.invertFrom(mToWorld);
    
    mToWorld.mult(n);

    if(getAxisOfRotation() == Vec3f::Null)
    {
        if(true)
        {
            Vec3f u  (0.f, 1.f, 0.f);
            Vec3f vUp;
            Vec3f uW;
            
            mCamToWorld.mult(eyepos);
            mToWorld   .mult(objpos);

            vDir = eyepos - objpos;

//            vDir.setValue(mCamToWorld[2]);
            
            vUp.setValue (mCamToWorld[1]);
            
            Quaternion qN(n, vDir);
            
            mToWorld.mult(u);
            
            qN.multVec(u, uW);
            
            q1.setValue(uW, vUp);
            
            q1.mult(qN);
        }
        else
        {
            Vec3f u  (0.f, 1.f, 0.f);
            Vec3f vUp;
            Vec3f uW;
            
            vDir.setValue(mCamToWorld[2]);
            
            vUp.setValue (mCamToWorld[1]);
            
            Quaternion qN(n, vDir);
            
            mToWorld.mult(u);
            
            qN.multVec(u, uW);
            
            q1.setValue(uW, vUp);
            
            q1.mult(qN);
        }
    }
    else
    {
        Vec3f wUp;
        Vec3f s;
        Vec3f tDir;

        mCamToWorld.mult(eyepos);

        mToWorld.mult(objpos);

        mToWorld.mult(getAxisOfRotation(), wUp);

        vDir = eyepos - objpos;

        s    = vDir.cross(wUp);
        tDir = wUp .cross(s  );
        
        q1.setValue(n, tDir);
    }

    Matrix mTrans;
    Matrix mMat;
    
    mTrans[3][0] = mToWorld[3][0];
    mTrans[3][1] = mToWorld[3][1];
    mTrans[3][2] = mToWorld[3][2];

    mMat.setTransform(q1);

    mResult.mult(mTrans);
    mResult.mult(mMat  );

    mTrans[3][0] = -mToWorld[3][0];
    mTrans[3][1] = -mToWorld[3][1];
    mTrans[3][2] = -mToWorld[3][2];

    mResult.mult(mTrans);
    mResult.mult(mToWorld);
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE Billboard::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    Matrix mMat;

    calcMatrix(da, mMat);

    // should use the chunk, but it's not updated yet
    glPushMatrix ();
    glMultMatrixf(mMat.getValues());

    da->selectVisibles();

    return Action::Continue;
}

Action::ResultE Billboard::drawLeave(Action *)
{
    glPopMatrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

Action::ResultE Billboard::intersectEnter(Action *)
{
    return Action::Continue; 
}

Action::ResultE Billboard::intersectLeave(Action *)
{
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE Billboard::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    Matrix mMat;

    calcMatrix(pAction, mMat);

    pAction->push_matrix(mMat);

    pAction->selectVisibles();

    return Action::Continue;
}

Action::ResultE Billboard::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->pop_matrix();

    return Action::Continue;
}

