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

#include "OSGMoveManipulator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MoveManipulator
The MoveHandle is used for moving objects. It consist of three axis which can be picked and translated and one center box to translate freely in 3D.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MoveManipulator::initMethod (void)
{
	
	DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&MoveManipulator::drawEnter));
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&MoveManipulator::drawLeave));

    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&MoveManipulator::renderEnter));

    RenderAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&MoveManipulator::renderLeave));
   
    IntersectAction::registerEnterDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&MoveManipulator::intersectEnter));
										  
    IntersectAction::registerLeaveDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MoveManipulatorPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&MoveManipulator::intersectLeave));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MoveManipulator::MoveManipulator(void) :
    Inherited()
{
}

MoveManipulator::MoveManipulator(const MoveManipulator &source) :
    Inherited(source)
{
}

MoveManipulator::~MoveManipulator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MoveManipulator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MoveManipulator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MoveManipulator NI" << std::endl;
}

NodePtr MoveManipulator::makeHandleGeo()
{
	return makeCone(0.75, 0.1, 12, true, true);
}

void  MoveManipulator::doMovement(TransformPtr t,
								  Int32 coord,
								  Real32 value,
								  const Vec3f		&translation,
								  const Quaternion	&rotation,
								  const Vec3f		&scaleFactor,
								  const Quaternion	&scaleOrientation )
{
	Vec3f trans(0.0f, 0.0f, 0.0f);
	trans[coord] = value;

	Matrix ma, mb, mc, md, me;
	
	ma.setTranslate( -translation        );
	mb.setRotate   (  rotation.inverse() );
	mc.setTransform(  trans              );
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGMoveManipulator.cpp,v 1.3 2005/12/19 12:04:26 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGMOVEMANIPULATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMOVEMANIPULATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMOVEMANIPULATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

