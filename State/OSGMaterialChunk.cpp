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

#include "OSGMaterialChunk.h"

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

OSG_FC_FIRST_FIELD_IDM_DEF(MaterialChunk, DiffuseField)

OSG_FC_FIELD_IDM_DEF      (MaterialChunk, 
                           AmbientField,  
                           DiffuseField)
OSG_FC_FIELD_IDM_DEF      (MaterialChunk, 
                           SpecularField,  
                           AmbientField)
OSG_FC_FIELD_IDM_DEF      (MaterialChunk, 
                           EmissionField,  
                           SpecularField)
OSG_FC_FIELD_IDM_DEF      (MaterialChunk, 
                           ShininessField,  
                           EmissionField)

OSG_FC_LAST_FIELD_IDM_DEF (MaterialChunk, ShininessField)


char MaterialChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass MaterialChunk::_class(String("Material"));


FieldDescription MaterialChunk::_desc[] = 
{
        FieldDescription(
        SFColor4f::getClassType(), 
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(DiffuseField),
        false,
        (FieldAccessMethod) &MaterialChunk::getSFDiffuse,
        ""),

        FieldDescription(
        SFColor4f::getClassType(), 
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(AmbientField),
        false,
        (FieldAccessMethod) &MaterialChunk::getSFAmbient,
        ""),

        FieldDescription(
        SFColor4f::getClassType(), 
        "specular", 
        OSG_FC_FIELD_IDM_DESC(SpecularField),
        false,
        (FieldAccessMethod) &MaterialChunk::getSFSpecular,
        ""),

        FieldDescription(
        SFColor4f::getClassType(), 
        "emission", 
        OSG_FC_FIELD_IDM_DESC(EmissionField),
        false,
        (FieldAccessMethod) &MaterialChunk::getSFEmission,
        ""),

        FieldDescription(
        SFReal32::getClassType(), 
        "shininess", 
        OSG_FC_FIELD_IDM_DESC(ShininessField),
        false,
        (FieldAccessMethod) &MaterialChunk::getSFShininess,
        "")
};

FieldContainerType MaterialChunk::_type(
	"MaterialChunk", 
	"StateChunk", 
	NULL,
	(PrototypeCreateF) &MaterialChunk::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(MaterialChunk, MaterialChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

MaterialChunk::MaterialChunk(void) :
	Inherited(), 
	_diffuse( Color4f(1,1,1,0 ) ), _ambient( Color4f(.2,.2,.2,0 ) ), 
	_specular( Color4f(.5,.5,.5,0 ) ), _emission( Color4f(0,0,0,0 ) ), 
	_shininess( 10 )
{
	_ownClass = _class.getID();
}


MaterialChunk::MaterialChunk( const MaterialChunk& source ) :
	Inherited(source),
	_diffuse( source._diffuse ), _ambient( source._ambient ), 
	_specular( source._specular ), _emission( source._emission ), 
	_shininess( source._shininess )
{
}


/** \brief Destructor
 */

MaterialChunk::~MaterialChunk(void)
{
}

/*---------------------------- properties ---------------------------------*/

// Diffuse Color

SFColor4f *MaterialChunk::getSFDiffuse(void)
{
	return &_diffuse;
}

Color4f &MaterialChunk::getDiffuse(void)
{
	return _diffuse.getValue();
}

const Color4f &MaterialChunk::getDiffuse(void) const
{
	return _diffuse.getValue();
}

void MaterialChunk::setDiffuse( const Color4f & color )
{
	_diffuse.setValue( color );
}


// Ambient Color

SFColor4f *MaterialChunk::getSFAmbient(void)
{
	return &_ambient;
}

Color4f &MaterialChunk::getAmbient(void)
{
	return _ambient.getValue();
}

const Color4f &MaterialChunk::getAmbient(void) const
{
	return _ambient.getValue();
}

void MaterialChunk::setAmbient( const Color4f & color )
{
	_ambient.setValue( color );
}


// Specular Color

SFColor4f *MaterialChunk::getSFSpecular(void)
{
	return &_specular;
}

Color4f &MaterialChunk::getSpecular(void)
{
	return _specular.getValue();
}

const Color4f &MaterialChunk::getSpecular(void) const
{
	return _specular.getValue();
}

void MaterialChunk::setSpecular( const Color4f & color )
{
	_specular.setValue( color );
}


// Emission Color

SFColor4f *MaterialChunk::getSFEmission(void)
{
	return &_emission;
}

Color4f &MaterialChunk::getEmission(void)
{
	return _emission.getValue();
}

const Color4f &MaterialChunk::getEmission(void) const
{
	return _emission.getValue();
}

void MaterialChunk::setEmission( const Color4f & color )
{
	_emission.setValue( color );
}


// Shininess Color

SFReal32 *MaterialChunk::getSFShininess(void)
{
	return &_shininess;
}

Real32 MaterialChunk::getShininess(void)
{
	return _shininess.getValue();
}

Real32 MaterialChunk::getShininess(void) const
{
	return _shininess.getValue();
}

void MaterialChunk::setShininess( const Real32 color )
{
	_shininess.setValue( color );
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
	if ( abs( _shininess.getValue() - old->getShininess() ) > 1e-4 )
		glMaterialf(  GL_FRONT_AND_BACK, GL_SHININESS, _shininess.getValue() );
}

void MaterialChunk::deactivate ( DrawAction *, UInt32 )
{
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void MaterialChunk::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
    SDEBUG << "Dump MaterialChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

Real32 MaterialChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

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

