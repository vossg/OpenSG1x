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

#include "OSGRotateManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RotateManipulator
The MoveHandle is used for moving objects. It consist of three axis which can be picked and translated and one center box to translate freely in 3D. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotateManipulator::initMethod (void)
{
	
	DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&RotateManipulator::drawEnter));
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&RotateManipulator::drawLeave));

    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&RotateManipulator::renderEnter));

    RenderAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&RotateManipulator::renderLeave));

    IntersectAction::registerEnterDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&RotateManipulator::intersectEnter));
										  
    IntersectAction::registerLeaveDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          RotateManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&RotateManipulator::intersectLeave));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RotateManipulator::RotateManipulator(void) :
    Inherited()
{
}

RotateManipulator::RotateManipulator(const RotateManipulator &source) :
    Inherited(source)
{
}

RotateManipulator::~RotateManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RotateManipulator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RotateManipulator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RotateManipulator NI" << std::endl;
}

NodePtr RotateManipulator::makeHandleGeo()
{
	return makeSphere(2, 0.2);
}

void  RotateManipulator::doMovement(TransformPtr t,
								  Int32 coord,
								  Real32 value,
								  const Vec3f		&translation,
								  const Quaternion	&rotation,
								  const Vec3f		&scaleFactor,
								  const Quaternion	&scaleOrientation )
{
	Vec3f axis(0.0f, 0.0f, 0.0f);
	axis[coord] = 1.0;
	Quaternion rot(axis, value);
	
	Matrix ma, mb, mc, md, me;
	
	ma.setTranslate( -translation        );
	mb.setRotate   (  rotation.inverse() );
	mc.setRotate   (  rot                );
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGRotateManipulator.cpp,v 1.3 2005/12/19 12:04:26 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGROTATEMANIPULATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGROTATEMANIPULATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGROTATEMANIPULATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

