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

#define OSG_COMPILESTATE
#define OSG_COMPILESTATECHUNKINST

#include "OSGStateChunk.h"

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

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<StateChunkPtr>::_fieldType
#pragma instantiate MField<StateChunkPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, StateChunkPtr, OSG_STATE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, StateChunkPtr, OSG_STATE_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

// StateChunkClass code

vector<String>* StateChunkClass::_classNames = NULL;
vector<UInt32>* StateChunkClass::_numslots = NULL;

StateChunkClass::StateChunkClass( String name, UInt32 numslots )
{
	if ( ! _classNames )
	{
		_classNames = new vector<String>(0);
		_numslots   = new vector<UInt32>(0);
	}

	_classId = _classNames->size();
	
	for ( int i = 0; i < numslots; i++ )
	{
		_classNames->push_back( name );
		_numslots->push_back( numslots );
	}
}

StateChunkClass::iterator StateChunkClass::begin( void )
{
	return _classNames->begin();
}

StateChunkClass::iterator StateChunkClass::end( void )
{
	return _classNames->end();
}

// instance access

UInt32 StateChunkClass::getID( void ) const
{
	return _classId;
}

UInt32 StateChunkClass::getNumSlots( void ) const
{
	return (*_numslots)[_classId];
}

const String StateChunkClass::getName( void ) const
{
	return (*_classNames)[_classId];
}

// static access

UInt32 StateChunkClass::getNumSlots( UInt32 index ) 
{
	if ( index >= (*_numslots).size() )
		return -1;

	return (*_numslots)[index];
}

const String StateChunkClass::getName( UInt32 index ) 
{
	if ( index >= (*_classNames).size() )
			return String();

	return (*_classNames)[index];
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StateChunk::cvsid[] = "@(#)$Id: $";

FieldContainerType StateChunk::_type("StateChunk", 
                                     "FieldContainer");

OSG_STATE_DLLMAPPING StateChunkPtr OSG::NullStateChunk;

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

OSG_ABSTR_FIELD_CONTAINER_DEF(StateChunk, StateChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

StateChunk::StateChunk(void) :
	Inherited(), _ownClass()
{
}


StateChunk::StateChunk( const StateChunk & source ) :
	Inherited(source), _ownClass(source._ownClass)
{
}

/** \brief Destructor
 */

StateChunk::~StateChunk(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

const StateChunkClass *  StateChunk::getClass( void ) const
{
	return NULL;
}

/*-------------------------- your_category---------------------------------*/

void StateChunk::activate ( DrawAction * action, UInt32 index )
{
}

void StateChunk::changeFrom( DrawAction * action, StateChunk * old, UInt32 index )
{
}

void StateChunk::deactivate ( DrawAction * action, UInt32 index )
{
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void StateChunk::dump(void) const
{
    SDEBUG << "Dump StateChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/


Real32 StateChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

Bool StateChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool StateChunk::operator == (const StateChunk &other) const
{
	return false;
}

/** \brief unequal
 */

Bool StateChunk::operator != (const StateChunk &other) const
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

