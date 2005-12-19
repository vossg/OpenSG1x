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

#define OSG_COMPILEMANIPULATORSLIB

#include <OSGConfig.h>
#include <OSGRenderAction.h>
#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>

#include "OSGScaleManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ScaleManipulator
The ScaleHandle is used for scaleing objects. It consist of three axis which can be picked and scaled and one center box to scale freely in 3D. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScaleManipulator::initMethod (void)
{
	
	DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&ScaleManipulator::drawEnter));
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&ScaleManipulator::drawLeave));

    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&ScaleManipulator::renderEnter));

    RenderAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&ScaleManipulator::renderLeave));

    IntersectAction::registerEnterDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&ScaleManipulator::intersectEnter));
										  
    IntersectAction::registerLeaveDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          ScaleManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&ScaleManipulator::intersectLeave));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScaleManipulator::ScaleManipulator(void) :
    Inherited()
{
}

ScaleManipulator::ScaleManipulator(const ScaleManipulator &source) :
    Inherited(source)
{
}

ScaleManipulator::~ScaleManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScaleManipulator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ScaleManipulator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScaleManipulator NI" << std::endl;
}

NodePtr ScaleManipulator::makeHandleGeo()
{
	return makeCylinder(0.75, 0.1, 12, true, true, true);
}

void  ScaleManipulator::doMovement(TransformPtr t,
								   Int32 coord,
								   Real32 value,
								   const Vec3f		&translation,
								   const Quaternion	&rotation,
								   const Vec3f		&scaleFactor,
								   const Quaternion	&scaleOrientation )
{
	Vec3f scale(1.0f, 1.0f, 1.0f);
	scale[coord] += value;
	
	Matrix ma, mb, mc, md, me;
	
	ma.setTranslate( -translation        );
	mb.setRotate   (  rotation.inverse() );
	mc.setScale    (  scale              );
	md.setRotate   (  rotation           );
	me.setTranslate(  translation        );
	beginEditCP(t, Transform::MatrixFieldMask);
	{
		t->getMatrix().multLeft(ma);
		t->getMatrix().multLeft(mb);
		t->getMatrix().multLeft(mc);
		t->getMatrix().multLeft(md);
		t->getMatrix().multLeft(me);
	}	
	endEditCP(t, Transform::MatrixFieldMask);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGScaleManipulator.cpp,v 1.3 2005/12/19 12:04:26 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGSCALEMANIPULATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCALEMANIPULATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCALEMANIPULATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

