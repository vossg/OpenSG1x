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

#include "OSGLightChunk.h"

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

OSG_FC_FIRST_FIELD_IDM_DEF(OSGLightChunk, OSGDiffuseField)

OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGAmbientField,  
                           OSGDiffuseField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGSpecularField,  
                           OSGAmbientField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGPositionField,  
                           OSGSpecularField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGDirectionField,  
                           OSGPositionField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGExponentField,  
                           OSGDirectionField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGCutoffField,  
                           OSGExponentField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGConstantAttenuationField,  
                           OSGCutoffField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGLinearAttenuationField,  
                           OSGConstantAttenuationField)
OSG_FC_FIELD_IDM_DEF      (OSGLightChunk, 
                           OSGQuadraticAttenuationField,  
                           OSGLinearAttenuationField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGLightChunk, OSGQuadraticAttenuationField)

char OSGLightChunk::cvsid[] = "@(#)$Id: $";

OSGStateChunkClass OSGLightChunk::_class("Light",8);


OSGFieldDescription OSGLightChunk::_desc[] = 
{
        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(OSGDiffuseField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFDiffuse,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(OSGAmbientField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFAmbient,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "specular", 
        OSG_FC_FIELD_IDM_DESC(OSGSpecularField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFSpecular,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "position", 
        OSG_FC_FIELD_IDM_DESC(OSGPositionField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFPosition,
        ""),

        OSGFieldDescription(
        OSGSFVec3f::getClassType(), 
        "direction", 
        OSG_FC_FIELD_IDM_DESC(OSGDirectionField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFDirection,
        ""),

        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "exponent", 
        OSG_FC_FIELD_IDM_DESC(OSGExponentField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFExponent,
        ""),

        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "cutoff", 
        OSG_FC_FIELD_IDM_DESC(OSGCutoffField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFCutoff,
        ""),

        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "constantAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGConstantAttenuationField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFConstantAttenuation,
        ""),

        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "linearAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGLinearAttenuationField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFLinearAttenuation,
        ""),
        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "quadraticAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGQuadraticAttenuationField),
        false,
        (OSGFieldAccessMethod) &OSGLightChunk::getSFQuadraticAttenuation,
        "")
};

OSGFieldContainerType OSGLightChunk::_type(
	"LightChunk", 
	"StateChunk", 
	NULL,
	(OSGPrototypeCreateF) OSGLightChunk::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGLightChunk, OSGLightChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGLightChunk::OSGLightChunk(void) :
	Inherited(), 
	_diffuse( OSGVec4f(1,1,1,0 ) ), _ambient( OSGVec4f(.1,.1,.1,0 ) ), 
	_specular( OSGVec4f(1,1,1,0 ) ), 
	_position( OSGVec4f(0,-1,0,0 ) ), _direction( OSGVec3f(0,0,1,0 ) ),
	_exponent( 2 ),_cutoff( 180 ),
	_constantAttenuation( 1 ), _linearAttenuation( 0 ), _quadraticAttenuation( 0 )
{
	_ownClass = _class.getID();
}


OSGLightChunk::OSGLightChunk( const OSGLightChunk& source ) :
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

OSGLightChunk::~OSGLightChunk(void)
{
}

/*---------------------------- properties ---------------------------------*/

// Diffuse Color

OSGSFVec4f *OSGLightChunk::getSFDiffuse(void)
{
	return &_diffuse;
}

OSGVec4f &OSGLightChunk::getDiffuse(void)
{
	return _diffuse.getValue();
}

const OSGVec4f &OSGLightChunk::getDiffuse(void) const
{
	return _diffuse.getValue();
}

void OSGLightChunk::setDiffuse( const OSGVec4f & color )
{
	_diffuse.setValue( color );
}


// Ambient Color

OSGSFVec4f *OSGLightChunk::getSFAmbient(void)
{
	return &_ambient;
}

OSGVec4f &OSGLightChunk::getAmbient(void)
{
	return _ambient.getValue();
}

const OSGVec4f &OSGLightChunk::getAmbient(void) const
{
	return _ambient.getValue();
}

void OSGLightChunk::setAmbient( const OSGVec4f & color )
{
	_ambient.setValue( color );
}


// Specular Color

OSGSFVec4f *OSGLightChunk::getSFSpecular(void)
{
	return &_specular;
}

OSGVec4f &OSGLightChunk::getSpecular(void)
{
	return _specular.getValue();
}

const OSGVec4f &OSGLightChunk::getSpecular(void) const
{
	return _specular.getValue();
}

void OSGLightChunk::setSpecular( const OSGVec4f & color )
{
	_specular.setValue( color );
}

// Position

OSGSFVec4f   *OSGLightChunk::getSFPosition( void )
{
	return &_position;
}
OSGVec4f   &OSGLightChunk::getPosition  ( void )
{
	return _position.getValue();
}
const OSGVec4f &OSGLightChunk::getPosition  ( void ) const
{
	return _position.getValue();
}
void OSGLightChunk::setPosition  ( const OSGVec4f & pos )
{
	_position.setValue( pos );
}


// Direction

OSGSFVec3f *OSGLightChunk::getSFDirection( void )
{
	return &_direction;
}
OSGVec3f &OSGLightChunk::getDirection  ( void )
{
	return _direction.getValue();
}
const OSGVec3f   &OSGLightChunk::getDirection  ( void ) const
{
	return _direction.getValue();
}
void OSGLightChunk::setDirection  ( const OSGVec3f & dir )
{
	_direction.setValue( dir );
}

// Exponent

OSGSFReal32 *OSGLightChunk::getSFExponent( void )
{
	return &_exponent;
}
OSGReal32 OSGLightChunk::getExponent( void )
{
	return _exponent.getValue();
}
OSGReal32 OSGLightChunk::getExponent  ( void ) const
{
	return _exponent.getValue();
}
void OSGLightChunk::setExponent( const OSGReal32 exponent )
{
	_exponent.setValue( exponent );
}

// Cutoff

OSGSFReal32 *OSGLightChunk::getSFCutoff( void )
{
	return &_cutoff;
}
OSGReal32 OSGLightChunk::getCutoff( void )
{
	return _cutoff.getValue();
}
OSGReal32 OSGLightChunk::getCutoff( void ) const
{
	return _cutoff.getValue();
}
void OSGLightChunk::setCutoff( const OSGReal32 cutoff )
{
	_cutoff.setValue( cutoff );
}

// Constant Attenuation


OSGSFReal32 *OSGLightChunk::getSFConstantAttenuation( void )
{
	return &_constantAttenuation;
}
OSGReal32 OSGLightChunk::getConstantAttenuation( void )
{
	return _constantAttenuation.getValue();
}
OSGReal32 OSGLightChunk::getConstantAttenuation( void ) const
{
	return _constantAttenuation.getValue();
}
void OSGLightChunk::setConstantAttenuation( const OSGReal32 constantAttenuation )
{
	_constantAttenuation.setValue( constantAttenuation );
}

// Linear Attenuation

OSGSFReal32 *OSGLightChunk::getSFLinearAttenuation( void )
{
	return &_linearAttenuation;
}
OSGReal32 OSGLightChunk::getLinearAttenuation( void )
{
	return _linearAttenuation.getValue();
}
OSGReal32 OSGLightChunk::getLinearAttenuation( void ) const
{
	return _linearAttenuation.getValue();
}
void OSGLightChunk::setLinearAttenuation( const OSGReal32 linearAttenuation )
{
	_linearAttenuation.setValue( linearAttenuation );
}

// Quadratic Attenuation

OSGSFReal32 *OSGLightChunk::getSFQuadraticAttenuation( void )
{
	return &_quadraticAttenuation;
}
OSGReal32 OSGLightChunk::getQuadraticAttenuation( void )
{
	return _quadraticAttenuation.getValue();
}
OSGReal32 OSGLightChunk::getQuadraticAttenuation( void ) const
{
	return _quadraticAttenuation.getValue();
}
void OSGLightChunk::setQuadraticAttenuation( const OSGReal32 quadraticAttenuation )
{
	_quadraticAttenuation.setValue( quadraticAttenuation );
}




/*-------------------------- your_category---------------------------------*/

void OSGLightChunk::activate( OSGUInt32 index )
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

void OSGLightChunk::changeFrom( OSGStateChunk * old_chunk, OSGUInt32 index )
{
	OSGLightChunk const *old = dynamic_cast<OSGLightChunk const*>(old_chunk);

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

void OSGLightChunk::deactivate( OSGUInt32 index )
{
	glDisable( GL_LIGHT0 + index );
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGLightChunk::dump(void) const
{
    SDEBUG << "Dump OSGLightChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

OSGReal32 OSGLightChunk::switchCost( OSGStateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

OSGBool OSGLightChunk::operator < (const OSGStateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGLightChunk::operator == (const OSGStateChunk &other) const
{
	OSGLightChunk const *tother = dynamic_cast<OSGLightChunk const*>(&other);

	if ( !tother )
		return false;

	if ( ! getDiffuse().equals( tother->getDiffuse(), osgEps )
	   )
		return false;
		
	return true;
}

/** \brief unequal
 */

OSGBool OSGLightChunk::operator != (const OSGStateChunk &other) const
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

