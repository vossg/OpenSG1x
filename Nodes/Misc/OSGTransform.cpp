/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEMISC
#define OSG_COMPILETRANSFORMINST

#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>

#include "OSGTransform.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<TransformPtr>::_fieldType
#pragma instantiate MField<TransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, TransformPtr, OSG_MISC_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, TransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(Transform, MatrixField)
OSG_FC_LAST_FIELD_IDM_DEF (Transform, MatrixField)

char Transform::cvsid[] = "@(#)$Id: $";

/** \brief Group field description
 */

FieldDescription Transform::_desc[] = 
{
    FieldDescription(SFMatrix::getClassType(), 
                     "matrix", 
                     OSG_FC_FIELD_IDM_DESC(MatrixField),
                     false,
                     (FieldAccessMethod) &Transform::getSFMatrix)
};

/** \brief Transform type
 */

FieldContainerType Transform::_type(
    "Transform",
    "NodeCore",
    NULL,
    (PrototypeCreateF) &Transform::createEmpty,
    initMethod,
    _desc,
    sizeof(_desc));


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Transform::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::drawEnter));
    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::drawLeave));

    IntersectAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::intersectEnter));
    IntersectAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::intersectLeave));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(Transform, TransformPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Transform::Transform(void) :
    Inherited(),
    _matrix()
{
}

/** \brief Copy Constructor
 */

Transform::Transform(const Transform &source) :
    Inherited(source),
    _matrix(source._matrix)
{
}

/** \brief Destructor
 */

Transform::~Transform(void)
{
}

/*------------------------------ access -----------------------------------*/

/** Returns pointer to the stored matrix field.
 */

SFMatrix *Transform::getSFMatrix(void)
{
    return &_matrix;
}

/** Returns a reference to the stored field.
 */

Matrix &Transform::getMatrix(void)
{
    return _matrix.getValue();
}

/** Returns a reference to the stored field.
 */

const Matrix &Transform::getMatrix(void) const
{
    return _matrix.getValue();
}


void Transform::accumulateMatrix( Matrix & result )
{
    result.mult( getMatrix() );
}

void Transform::adjustVolume( Volume & volume )
{
    volume.transform( _matrix.getValue() );
}

/*------------------------------- dump ----------------------------------*/

void Transform::dump(      UInt32     uiIndent, 
                     const BitVector &bvFlags) const
{
    SDEBUG << "Dump Transform NI" << endl;
}

    
/** Actions */

// execute the OpenGL commands directly 
Action::ResultE Transform::drawEnter(Action *  )
{
    // should use the chunk, but it's not updated yet
    glPushMatrix();
    glMultMatrixf( getMatrix().getValues() );

    return Action::Continue;
}

Action::ResultE Transform::drawLeave(Action *  )
{
    glPopMatrix();

    return Action::Continue;
}

// test the ray 
// transform it into the local coordinate space
Action::ResultE Transform::intersectEnter( Action *action )
{
	IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
	Matrix m = this->getMatrix();
	m.invert();
	
	Pnt3f pos;
	Vec3f dir;
	m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
	m.multMatrixVec( ia->getLine().getDirection(), dir );
	
	ia->setLine( Line( pos, dir ), ia->getMaxDist() );

	return Action::Continue; 
}

Action::ResultE Transform::intersectLeave( Action *action )
{
	IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
	Matrix m = this->getMatrix();
	
	Pnt3f pos;
	Vec3f dir;
	m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
	m.multMatrixVec( ia->getLine().getDirection(), dir );
	
	ia->setLine( Line( pos, dir ), ia->getMaxDist() );

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

