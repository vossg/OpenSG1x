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

#define OSG_COMPILEMATERIAL

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>

#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SimpleMaterial
    \ingroup MaterialLib

The simple material class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char SimpleMaterial::cvsid[] = "@(#)$Id: OSGSimpleMaterial.cpp,v 1.11 2001/04/23 18:33:14 dirk Exp $";

const SimpleMaterialPtr SimpleMaterial::NullPtr;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

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

void SimpleMaterial::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

SimpleMaterial::SimpleMaterial(void) :
    Inherited()
{
	_materialChunk = MaterialChunk::create();
}

/** \brief Copy Constructor
 */

SimpleMaterial::SimpleMaterial(const SimpleMaterial &source) :
    Inherited(source)
{
	_materialChunk = MaterialChunk::create();
}

/** \brief Destructor
 */

SimpleMaterial::~SimpleMaterial(void)
{
}


/** \brief react to field changes
 */

void SimpleMaterial::changed(BitVector, ChangeMode)
{
}

/*-------------------------- your_category---------------------------------*/
	
	
void SimpleMaterial::draw( Geometry* geo, DrawAction * action )
{
	StatePtr state = State::create();
	
	Color3f v3;
	Color4f v4;
	float alpha = 1.f - getTransparency();
	
	beginEditCP( _materialChunk );
	
	v3 = getAmbient(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setAmbient( v4 );
	v3 = getDiffuse(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setDiffuse( v4 );
	v3 = getSpecular(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setSpecular( v4 );
	_materialChunk->setShininess( getShininess() );
	v3 = getEmission(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setEmission( v4 );
	
	endEditCP( _materialChunk );

	state->addChunk( _materialChunk );
	
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		state->addChunk( *i );
	
	state->activate( action );
	
	geo->draw( action );

	state->deactivate( action );

	subRefCP( state );
}
	
void SimpleMaterial::activate( void )
{
	Color3f v3;
	Color4f v4;
	float alpha = 1.f - getTransparency();
	
	beginEditCP( _materialChunk );
	
	v3 = getAmbient(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setAmbient( v4 );
	v3 = getDiffuse(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setDiffuse( v4 );
	v3 = getSpecular(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setSpecular( v4 );
	_materialChunk->setShininess( getShininess() );
	v3 = getEmission(); v4.setValuesRGBA( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setEmission( v4 );
	
	endEditCP( _materialChunk );

	_materialChunk->activate();
	
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		i->activate();
}
	
void SimpleMaterial::deactivate( void )
{
	_materialChunk->deactivate();

	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		i->deactivate();
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void SimpleMaterial::dump(      UInt32     uiIndent, 
                          const BitVector &bvFlags) const
{
    SLOG << "SimpleMaterial at " << this << endl;
	PLOG << "\tambient: " << getAmbient() << endl;
	PLOG << "\tdiffuse: " << getDiffuse()  << endl;
	PLOG << "\tspecular: " << getSpecular()  << endl;
	PLOG << "\tshininess: " << getShininess()  << endl;
	PLOG << "\temission: " << getEmission()  << endl;
	PLOG << "\ttransparency: " << getTransparency()  << endl;
    PLOG << "\tChunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		PLOG << "\t" << *i << endl;	
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

