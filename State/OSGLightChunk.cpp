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

#include "OSGLightChunk.h"

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

OSG_FC_FIRST_FIELD_IDM_DEF(LightChunk, DiffuseField)

OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           AmbientField,  
                           DiffuseField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           SpecularField,  
                           AmbientField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           PositionField,  
                           SpecularField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           DirectionField,  
                           PositionField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           ExponentField,  
                           DirectionField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           CutoffField,  
                           ExponentField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           ConstantAttenuationField,  
                           CutoffField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           LinearAttenuationField,  
                           ConstantAttenuationField)
OSG_FC_FIELD_IDM_DEF      (LightChunk, 
                           QuadraticAttenuationField,  
                           LinearAttenuationField)

OSG_FC_LAST_FIELD_IDM_DEF (LightChunk, QuadraticAttenuationField)

char LightChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass LightChunk::_class(String("Light"), 8);


FieldDescription LightChunk::_desc[] = 
{
        FieldDescription(
        SFVec4f::getClassType(), 
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(DiffuseField),
        false,
        (FieldAccessMethod) &LightChunk::getSFDiffuse,
        ""),

        FieldDescription(
        SFVec4f::getClassType(), 
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(AmbientField),
        false,
        (FieldAccessMethod) &LightChunk::getSFAmbient,
        ""),

        FieldDescription(
        SFVec4f::getClassType(), 
        "specular", 
        OSG_FC_FIELD_IDM_DESC(SpecularField),
        false,
        (FieldAccessMethod) &LightChunk::getSFSpecular,
        ""),

        FieldDescription(
        SFVec4f::getClassType(), 
        "position", 
        OSG_FC_FIELD_IDM_DESC(PositionField),
        false,
        (FieldAccessMethod) &LightChunk::getSFPosition,
        ""),

        FieldDescription(
        SFVec3f::getClassType(), 
        "direction", 
        OSG_FC_FIELD_IDM_DESC(DirectionField),
        false,
        (FieldAccessMethod) &LightChunk::getSFDirection,
        ""),

        FieldDescription(
        SFReal32::getClassType(), 
        "exponent", 
        OSG_FC_FIELD_IDM_DESC(ExponentField),
        false,
        (FieldAccessMethod) &LightChunk::getSFExponent,
        ""),

        FieldDescription(
        SFReal32::getClassType(), 
        "cutoff", 
        OSG_FC_FIELD_IDM_DESC(CutoffField),
        false,
        (FieldAccessMethod) &LightChunk::getSFCutoff,
        ""),

        FieldDescription(
        SFReal32::getClassType(), 
        "constantAttenuation", 
        OSG_FC_FIELD_IDM_DESC(ConstantAttenuationField),
        false,
        (FieldAccessMethod) &LightChunk::getSFConstantAttenuation,
        ""),

        FieldDescription(
        SFReal32::getClassType(), 
        "linearAttenuation", 
        OSG_FC_FIELD_IDM_DESC(LinearAttenuationField),
        false,
        (FieldAccessMethod) &LightChunk::getSFLinearAttenuation,
        ""),
        FieldDescription(
        SFReal32::getClassType(), 
        "quadraticAttenuation", 
        OSG_FC_FIELD_IDM_DESC(QuadraticAttenuationField),
        false,
        (FieldAccessMethod) &LightChunk::getSFQuadraticAttenuation,
        "")
};

FieldContainerType LightChunk::_type(
	"LightChunk", 
	"StateChunk", 
	NULL,
	(PrototypeCreateF) LightChunk::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(LightChunk, LightChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

LightChunk::LightChunk(void) :
	Inherited(), 
	_diffuse( Vec4f(1,1,1,0 ) ), _ambient( Vec4f(.1,.1,.1,0 ) ), 
	_specular( Vec4f(1,1,1,0 ) ), 
	_position( Vec4f(0,-1,0,0 ) ), _direction( Vec3f(0,0,1,0 ) ),
	_exponent( 2 ),_cutoff( 180 ),
	_constantAttenuation( 1 ), _linearAttenuation( 0 ), _quadraticAttenuation( 0 )
{
	_ownClass = _class.getID();
}


LightChunk::LightChunk( const LightChunk& source ) :
	Inherited(source),
	_diffuse( source._diffuse ), _ambient( source._ambient ), 
	_specular( source._specular ), 
	_position( source._position ), _direction( source._direction ), 
	_exponent( source._exponent ), _cutoff( source._cutoff ),
	_constantAttenuation( source._constantAttenuation ), 
	_linearAttenuation( source._linearAttenuation ), 
	_quadraticAttenuation( source._quadraticAttenuation )
{
}


/** \brief Destructor
 */

LightChunk::~LightChunk(void)
{
}

/*---------------------------- properties ---------------------------------*/

// Diffuse Color

SFVec4f *LightChunk::getSFDiffuse(void)
{
	return &_diffuse;
}

Vec4f &LightChunk::getDiffuse(void)
{
	return _diffuse.getValue();
}

const Vec4f &LightChunk::getDiffuse(void) const
{
	return _diffuse.getValue();
}

void LightChunk::setDiffuse( const Vec4f & color )
{
	_diffuse.setValue( color );
}


// Ambient Color

SFVec4f *LightChunk::getSFAmbient(void)
{
	return &_ambient;
}

Vec4f &LightChunk::getAmbient(void)
{
	return _ambient.getValue();
}

const Vec4f &LightChunk::getAmbient(void) const
{
	return _ambient.getValue();
}

void LightChunk::setAmbient( const Vec4f & color )
{
	_ambient.setValue( color );
}


// Specular Color

SFVec4f *LightChunk::getSFSpecular(void)
{
	return &_specular;
}

Vec4f &LightChunk::getSpecular(void)
{
	return _specular.getValue();
}

const Vec4f &LightChunk::getSpecular(void) const
{
	return _specular.getValue();
}

void LightChunk::setSpecular( const Vec4f & color )
{
	_specular.setValue( color );
}

// Position

SFVec4f   *LightChunk::getSFPosition( void )
{
	return &_position;
}
Vec4f   &LightChunk::getPosition  ( void )
{
	return _position.getValue();
}
const Vec4f &LightChunk::getPosition  ( void ) const
{
	return _position.getValue();
}
void LightChunk::setPosition  ( const Vec4f & pos )
{
	_position.setValue( pos );
}


// Direction

SFVec3f *LightChunk::getSFDirection( void )
{
	return &_direction;
}
Vec3f &LightChunk::getDirection  ( void )
{
	return _direction.getValue();
}
const Vec3f   &LightChunk::getDirection  ( void ) const
{
	return _direction.getValue();
}
void LightChunk::setDirection  ( const Vec3f & dir )
{
	_direction.setValue( dir );
}

// Exponent

SFReal32 *LightChunk::getSFExponent( void )
{
	return &_exponent;
}
Real32 LightChunk::getExponent( void )
{
	return _exponent.getValue();
}
Real32 LightChunk::getExponent  ( void ) const
{
	return _exponent.getValue();
}
void LightChunk::setExponent( const Real32 exponent )
{
	_exponent.setValue( exponent );
}

// Cutoff

SFReal32 *LightChunk::getSFCutoff( void )
{
	return &_cutoff;
}
Real32 LightChunk::getCutoff( void )
{
	return _cutoff.getValue();
}
Real32 LightChunk::getCutoff( void ) const
{
	return _cutoff.getValue();
}
void LightChunk::setCutoff( const Real32 cutoff )
{
	_cutoff.setValue( cutoff );
}

// Constant Attenuation


SFReal32 *LightChunk::getSFConstantAttenuation( void )
{
	return &_constantAttenuation;
}
Real32 LightChunk::getConstantAttenuation( void )
{
	return _constantAttenuation.getValue();
}
Real32 LightChunk::getConstantAttenuation( void ) const
{
	return _constantAttenuation.getValue();
}
void LightChunk::setConstantAttenuation( const Real32 constantAttenuation )
{
	_constantAttenuation.setValue( constantAttenuation );
}

// Linear Attenuation

SFReal32 *LightChunk::getSFLinearAttenuation( void )
{
	return &_linearAttenuation;
}
Real32 LightChunk::getLinearAttenuation( void )
{
	return _linearAttenuation.getValue();
}
Real32 LightChunk::getLinearAttenuation( void ) const
{
	return _linearAttenuation.getValue();
}
void LightChunk::setLinearAttenuation( const Real32 linearAttenuation )
{
	_linearAttenuation.setValue( linearAttenuation );
}

// Quadratic Attenuation

SFReal32 *LightChunk::getSFQuadraticAttenuation( void )
{
	return &_quadraticAttenuation;
}
Real32 LightChunk::getQuadraticAttenuation( void )
{
	return _quadraticAttenuation.getValue();
}
Real32 LightChunk::getQuadraticAttenuation( void ) const
{
	return _quadraticAttenuation.getValue();
}
void LightChunk::setQuadraticAttenuation( const Real32 quadraticAttenuation )
{
	_quadraticAttenuation.setValue( quadraticAttenuation );
}




/*-------------------------- your_category---------------------------------*/

void LightChunk::activate( DrawAction *, UInt32 index )
{
	glLightfv( GL_LIGHT0 + index, GL_DIFFUSE,   
										_diffuse.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_AMBIENT,   
										_ambient.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_SPECULAR,   
										_specular.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_POSITION,   
										_position.getValue().getValueRef() );

	glLightf(  GL_LIGHT0 + index, GL_SPOT_CUTOFF, _cutoff.getValue() );
	if ( _cutoff.getValue() < 180 )
	{
		glLightfv( GL_LIGHT0 + index, GL_SPOT_DIRECTION,   
										_direction.getValue().getValueRef() );
		glLightf(  GL_LIGHT0 + index, GL_SPOT_EXPONENT, _exponent.getValue() );
	}
	glEnable( GL_LIGHT0 + index );
}

void LightChunk::changeFrom( DrawAction *, StateChunk * old_chunk, UInt32 index )
{
	LightChunk const *old = dynamic_cast<LightChunk const*>(old_chunk);

	// change from me to me?
	// this assumes I haven't changed in the meantime. is that a valid assumption?
	if ( old == this )
		return;

	// it could theoretically be more efficient to turn the light off before 
	// changing its parameters, have to try that sometime
	glLightfv( GL_LIGHT0 + index, GL_DIFFUSE,   
										_diffuse.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_AMBIENT,   
										_ambient.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_SPECULAR,   
										_specular.getValue().getValueRef() );
	glLightfv( GL_LIGHT0 + index, GL_POSITION,   
										_position.getValue().getValueRef() );

	glLightf(  GL_LIGHT0 + index, GL_SPOT_CUTOFF, _cutoff.getValue() );
	if ( _cutoff.getValue() < 180 )
	{
		glLightfv( GL_LIGHT0 + index, GL_SPOT_DIRECTION,   
										_direction.getValue().getValueRef() );
		glLightf(  GL_LIGHT0 + index, GL_SPOT_EXPONENT, _exponent.getValue() );
	}
}

void LightChunk::deactivate( DrawAction *, UInt32 index )
{
	glDisable( GL_LIGHT0 + index );
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void LightChunk::dump(      UInt32     uiIndent, 
                      const BitVector &bvFlags) const
{
    SDEBUG << "Dump LightChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

Real32 LightChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

Bool LightChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool LightChunk::operator == (const StateChunk &other) const
{
	LightChunk const *tother = dynamic_cast<LightChunk const*>(&other);

	if ( !tother )
		return false;

	if ( ! getDiffuse().equals( tother->getDiffuse(), Eps )
	   )
		return false;
		
	return true;
}

/** \brief unequal
 */

Bool LightChunk::operator != (const StateChunk &other) const
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

