/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGTransformChunk.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGTransformChunk, OSGMatrixField)
OSG_FC_LAST_FIELD_IDM_DEF (OSGTransformChunk, OSGMatrixField)

char OSGTransformChunk::cvsid[] = "@(#)$Id: $";

OSGStateChunkClass OSGTransformChunk::_class("Transform");


OSGFieldDescription OSGTransformChunk::_desc[] = 
{
        OSGFieldDescription(
        OSGSFMatrix::getClassType(), 
        "matrix", 
        OSG_FC_FIELD_IDM_DESC(OSGMatrixField),
        false,
        (OSGFieldAccessMethod) &OSGTransformChunk::getSFMatrix,
        "")
};

OSGFieldContainerType OSGTransformChunk::_type(
	"TransformChunk", 
	"StateChunk", 
	NULL,
	(OSGPrototypeCreateF) &OSGTransformChunk::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGTransformChunk, OSGTransformChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGTransformChunk::OSGTransformChunk(void) :
	Inherited()
{
	_ownClass = _class.getID();
}


OSGTransformChunk::OSGTransformChunk( const OSGTransformChunk& source ) :
	Inherited(source), _matrix( source.getMatrix() )
{
}


/** \brief Destructor
 */

OSGTransformChunk::~OSGTransformChunk(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

OSGSFMatrix *OSGTransformChunk::getSFMatrix(void)
{
	return &_matrix;
}

OSGMatrix &OSGTransformChunk::getMatrix(void)
{
	return _matrix.getValue();
}

const OSGMatrix &OSGTransformChunk::getMatrix(void) const
{
	return _matrix.getValue();
}

void OSGTransformChunk::setMatrix( const OSGMatrix & matrix )
{
	_matrix.setValue( matrix );
}


/*-------------------------- your_category---------------------------------*/

void OSGTransformChunk::activate ( OSGUInt32 )
{
	glPushMatrix();
	glMultMatrixf( getMatrix().getValues() );
}

void OSGTransformChunk::changeFrom( OSGStateChunk * old, OSGUInt32 )
{
	// change from me to me?
	// this assumes I haven't changed in the meantime. is that a valid assumption?
	if ( old == this )
		return;

	glPopMatrix();
	glPushMatrix();
	glMultMatrixf( getMatrix().getValues() );	
}

void OSGTransformChunk::deactivate ( OSGUInt32 )
{
	glPopMatrix();
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGTransformChunk::dump(void) const
{
    SDEBUG << "Dump OSGTransformChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

OSGReal32 OSGTransformChunk::switchCost( OSGStateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

OSGBool OSGTransformChunk::operator < (const OSGStateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGTransformChunk::operator == (const OSGStateChunk &other) const
{
	OSGTransformChunk const *tother = dynamic_cast<OSGTransformChunk const*>(&other);

	if ( !tother )
		return false;

	return getMatrix().equals( tother->getMatrix(), osgEps );
}

/** \brief unequal
 */

OSGBool OSGTransformChunk::operator != (const OSGStateChunk &other) const
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

