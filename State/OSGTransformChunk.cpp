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

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILESTATE

#include "OSGTransformChunk.h"

OSG_USING_NAMESPACE

/** \enum VecBase::VectorSizeE
 *  \brief 
 */

/** \var VecBase::VectorSizeE VecBase::_iSize
 * 
 */

/** \fn const char *VecBase::getClassname(void)
 *  \brief Classname
 */

/** \var ValueTypeT VecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(TransformChunk, MatrixField)
OSG_FC_LAST_FIELD_IDM_DEF (TransformChunk, MatrixField)

char TransformChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass TransformChunk::_class(String("Transform"));


FieldDescription TransformChunk::_desc[] = 
{
        FieldDescription(
        SFMatrix::getClassType(), 
        "matrix", 
        OSG_FC_FIELD_IDM_DESC(MatrixField),
        false,
        (FieldAccessMethod) &TransformChunk::getSFMatrix,
        "")
};

FieldContainerType TransformChunk::_type(
	"TransformChunk", 
	"StateChunk", 
	NULL,
	(PrototypeCreateF) &TransformChunk::createEmpty,
	NULL,
	_desc, 
	sizeof(_desc));

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(TransformChunk, TransformChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

TransformChunk::TransformChunk(void) :
	Inherited()
{
	_ownClass = _class.getID();
}


TransformChunk::TransformChunk( const TransformChunk& source ) :
	Inherited(source), _matrix( source.getMatrix() )
{
}


/** \brief Destructor
 */

TransformChunk::~TransformChunk(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

SFMatrix *TransformChunk::getSFMatrix(void)
{
	return &_matrix;
}

Matrix &TransformChunk::getMatrix(void)
{
	return _matrix.getValue();
}

const Matrix &TransformChunk::getMatrix(void) const
{
	return _matrix.getValue();
}

void TransformChunk::setMatrix( const Matrix & matrix )
{
	_matrix.setValue( matrix );
}


/*-------------------------- your_category---------------------------------*/

void TransformChunk::activate ( DrawAction *,  UInt32 )
{
	glPushMatrix();
	glMultMatrixf( getMatrix().getValues() );
}

void TransformChunk::changeFrom( DrawAction *,  StateChunk * old, UInt32 )
{
	// change from me to me?
	// this assumes I haven't changed in the meantime. is that a valid assumption?
	if ( old == this )
		return;

	glPopMatrix();
	glPushMatrix();
	glMultMatrixf( getMatrix().getValues() );	
}

void TransformChunk::deactivate ( DrawAction *,  UInt32 )
{
	glPopMatrix();
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void TransformChunk::dump(void) const
{
    SDEBUG << "Dump TransformChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

Real32 TransformChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

Bool TransformChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool TransformChunk::operator == (const StateChunk &other) const
{
	TransformChunk const *tother = dynamic_cast<TransformChunk const*>(&other);

	if ( !tother )
		return false;

	return getMatrix().equals( tother->getMatrix(), Eps );
}

/** \brief unequal
 */

Bool TransformChunk::operator != (const StateChunk &other) const
{
	return ! (*this == other);
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

