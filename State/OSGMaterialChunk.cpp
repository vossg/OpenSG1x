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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/gl.h>

#include "OSGMaterialChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MaterialChunk
	\ingroup StateChunks

The material chunk class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char MaterialChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass MaterialChunk::_class(String("Material"));

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

void MaterialChunk::initMethod (void)
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

MaterialChunk::MaterialChunk(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

MaterialChunk::MaterialChunk(const MaterialChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

MaterialChunk::~MaterialChunk(void)
{
}


/** \brief react to field changes
 */

void MaterialChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void MaterialChunk::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump MaterialChunk NI" << endl;
}

 

/*-------------------------- your_category---------------------------------*/

void MaterialChunk::activate ( DrawAction *, UInt32 )
{
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   
										_diffuse.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   
										_ambient.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,   
										_specular.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,   
										_emission.getValue().getValueRef() );
	glMaterialf(  GL_FRONT_AND_BACK, GL_SHININESS, _shininess.getValue() );
}

void MaterialChunk::changeFrom( DrawAction *, StateChunk * old_chunk, UInt32 )
{
	MaterialChunk const *old = dynamic_cast<MaterialChunk const*>(old_chunk);

	// change from me to me?
	// this assumes I haven't changed in the meantime. is that a valid assumption?
	if ( old == this )
		return;

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   
										_diffuse.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   
										_ambient.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,   
										_specular.getValue().getValueRef() );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,   
										_emission.getValue().getValueRef() );
	// adjust shininess only if it differs enough
	if ( osgabs( _shininess.getValue() - old->getShininess() ) > 1e-4 )
		glMaterialf(  GL_FRONT_AND_BACK, GL_SHININESS, _shininess.getValue() );
}

void MaterialChunk::deactivate ( DrawAction *, UInt32 )
{
}


/*-------------------------- comparison -----------------------------------*/

Real32 MaterialChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

Bool MaterialChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool MaterialChunk::operator == (const StateChunk &other) const
{
	MaterialChunk const *tother = dynamic_cast<MaterialChunk const*>(&other);

	if ( !tother )
		return false;

	if(getDiffuse() != tother->getDiffuse())
	   
		return false;
		
	return true;
}

/** \brief unequal
 */

Bool MaterialChunk::operator != (const StateChunk &other) const
{
	return ! (*this == other);
}
   

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

