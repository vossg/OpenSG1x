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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGStateChunk.h"

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

// OSGStateChunkClass code

vector<OSGString>* OSGStateChunkClass::_classNames = NULL;
vector<OSGUInt32>* OSGStateChunkClass::_numslots = NULL;

OSGStateChunkClass::OSGStateChunkClass( OSGString name, OSGUInt32 numslots )
{
	if ( ! _classNames )
	{
		_classNames = new vector<OSGString>;
		_numslots = new vector<OSGUInt32>;
	}

	_classId = _classNames->size();
	
	for ( int i = 0; i < numslots; i++ )
	{
		_classNames->push_back( name );
		_numslots->push_back( numslots );
	}
}

OSGStateChunkClass::iterator OSGStateChunkClass::begin( void )
{
	return _classNames->begin();
}

OSGStateChunkClass::iterator OSGStateChunkClass::end( void )
{
	return _classNames->end();
}

// instance access

OSGUInt32 OSGStateChunkClass::getID( void ) const
{
	return _classId;
}

OSGUInt32 OSGStateChunkClass::getNumSlots( void ) const
{
	return (*_numslots)[_classId];
}

const OSGString OSGStateChunkClass::getName( void ) const
{
	return (*_classNames)[_classId];
}

// static access

OSGUInt32 OSGStateChunkClass::getNumSlots( OSGUInt32 index ) 
{
	if ( index >= (*_numslots).size() )
		return -1;

	return (*_numslots)[index];
}

const OSGString OSGStateChunkClass::getName( OSGUInt32 index ) 
{
	if ( index >= (*_classNames).size() )
			return (char*)0;

	return (*_classNames)[index];
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGStateChunk::cvsid[] = "@(#)$Id: $";

OSGFieldContainerType OSGStateChunk::_type("StateChunk", 
                                     "FieldContainer");

OSGStateChunkPtr OSG::OSGNullStateChunk;

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

OSG_ABSTR_FIELD_CONTAINER_DEF(OSGStateChunk, OSGStateChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGStateChunk::OSGStateChunk(void) :
	Inherited(), _ownClass()
{
}


OSGStateChunk::OSGStateChunk( const OSGStateChunk & source ) :
	Inherited(source), _ownClass(source._ownClass)
{
}

/** \brief Destructor
 */

OSGStateChunk::~OSGStateChunk(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

const OSGStateChunkClass *  OSGStateChunk::getClass( void ) const
{
	return NULL;
}

/*-------------------------- your_category---------------------------------*/

void OSGStateChunk::activate ( OSGUInt32 index )
{
}

void OSGStateChunk::changeFrom( OSGStateChunk * old, OSGUInt32 index )
{
}

void OSGStateChunk::deactivate ( OSGUInt32 index )
{
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGStateChunk::dump(void) const
{
    SDEBUG << "Dump OSGStateChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/


OSGReal32 OSGStateChunk::switchCost( OSGStateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

OSGBool OSGStateChunk::operator < (const OSGStateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGStateChunk::operator == (const OSGStateChunk &other) const
{
	return false;
}

/** \brief unequal
 */

OSGBool OSGStateChunk::operator != (const OSGStateChunk &other) const
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

