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

#include <OSGFieldDescription.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>

#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


OSG_FC_FIRST_FIELD_IDM_DEF(SimpleMaterial, AmbientField)

OSG_FC_FIELD_IDM_DEF      (SimpleMaterial,
						   DiffuseField, 
                           AmbientField)

OSG_FC_FIELD_IDM_DEF      (SimpleMaterial,
						   SpecularField,
						   DiffuseField)

OSG_FC_FIELD_IDM_DEF      (SimpleMaterial,
						   ShininessField,
						   SpecularField)

OSG_FC_FIELD_IDM_DEF      (SimpleMaterial,
						   EmissionField,
						   ShininessField)

OSG_FC_FIELD_IDM_DEF      (SimpleMaterial,
						   TransparencyField,
						   EmissionField)

OSG_FC_LAST_FIELD_IDM_DEF(SimpleMaterial, TransparencyField)



char SimpleMaterial::cvsid[] = "@(#)$Id: OSGSimpleMaterial.cpp,v 1.1 2000/12/17 23:46:51 dirk Exp $";


FieldDescription SimpleMaterial::_desc[] = 
{
	FieldDescription(
        SFVec3f::getClassType(),
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(AmbientField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFAmbient),
	FieldDescription(
        SFVec3f::getClassType(),
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(DiffuseField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFDiffuse),
	FieldDescription(
        SFVec3f::getClassType(),
        "specular", 
        OSG_FC_FIELD_IDM_DESC(SpecularField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFSpecular),
	FieldDescription(
        SFReal32::getClassType(),
        "shininess", 
        OSG_FC_FIELD_IDM_DESC(ShininessField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFShininess),
	FieldDescription(
        SFVec3f::getClassType(),
        "emission", 
        OSG_FC_FIELD_IDM_DESC(EmissionField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFEmission),
	FieldDescription(
        SFReal32::getClassType(),
        "transparency", 
        OSG_FC_FIELD_IDM_DESC(TransparencyField),
        false,
        (FieldAccessMethod) &SimpleMaterial::getSFTransparency)
};

FieldContainerType SimpleMaterial::_type(
	"SimpleMaterial", 
	"ChunkMaterial", 
	NULL,
    (PrototypeCreateF) &SimpleMaterial::createEmpty,
    NULL,
	_desc, 
	sizeof(_desc)
	);

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

OSG_FIELD_CONTAINER_DEF(SimpleMaterial, SimpleMaterialPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

SimpleMaterial::SimpleMaterial(void) :
	Inherited(),
	_ambient( Vec3f(0,0,0,1) ), _diffuse( Vec3f(0,0,0,1) ), 
	_specular( Vec3f(0,0,0,1) ), _shininess( 1 ), _emission( Vec3f(0,0,0,1) ),
	_transparency( 0 )
{
	_materialChunk = MaterialChunk::create();
}

SimpleMaterial::SimpleMaterial( const SimpleMaterial& source ) :
	Inherited(source),
	_ambient( source._ambient ), _diffuse( source._diffuse ), 
	_specular( source._specular ), _shininess( source._shininess ), 
	_emission( source._emission ), _transparency( source._transparency )
{
	_materialChunk = MaterialChunk::create();
}

/** \brief Destructor
 */

SimpleMaterial::~SimpleMaterial(void)
{
	// need to destroy the _materialChunk here
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- pointer ------------------------------------*/

/*---------------------------- properties ---------------------------------*/

/* field access */

SFVec3f		*SimpleMaterial::getSFAmbient( void )
{
	return &_ambient;
}

SFVec3f		*SimpleMaterial::getSFDiffuse( void )
{
	return &_diffuse;
}

SFVec3f		*SimpleMaterial::getSFSpecular( void )
{
	return &_specular;
}

SFReal32		*SimpleMaterial::getSFShininess( void )
{
	return &_shininess;
}

SFVec3f		*SimpleMaterial::getSFEmission( void )
{
	return &_emission;
}

SFReal32		*SimpleMaterial::getSFTransparency( void )
{
	return &_transparency;
}


/* value access */

Vec3f	&SimpleMaterial::getAmbient  ( void )
{
	return _ambient.getValue();
}

const Vec3f &SimpleMaterial::getAmbient  ( void ) const
{
	return _ambient.getValue();
}

void	SimpleMaterial::setAmbient  ( const Vec3f & color )
{
	_ambient.setValue( color );
}


Vec3f	&SimpleMaterial::getDiffuse  ( void )
{
	return _diffuse.getValue();
}

const Vec3f &SimpleMaterial::getDiffuse  ( void ) const
{
	return _diffuse.getValue();
}

void	SimpleMaterial::setDiffuse  ( const Vec3f & color )
{
	_diffuse.setValue( color );
}


Vec3f	&SimpleMaterial::getSpecular  ( void )
{
	return _specular.getValue();
}

const Vec3f &SimpleMaterial::getSpecular  ( void ) const
{
	return _specular.getValue();
}

void	SimpleMaterial::setSpecular  ( const Vec3f & color )
{
	_specular.setValue( color );
}


Real32	SimpleMaterial::getShininess  ( void )
{
	return _shininess.getValue();
}

Real32 SimpleMaterial::getShininess  ( void ) const
{
	return _shininess.getValue();
}

void	SimpleMaterial::setShininess  ( const Real32 color )
{
	_shininess.setValue( color );
}


Vec3f	&SimpleMaterial::getEmission  ( void )
{
	return _emission.getValue();
}

const Vec3f &SimpleMaterial::getEmission  ( void ) const
{
	return _emission.getValue();
}

void	SimpleMaterial::setEmission ( const Vec3f & color )
{
	_emission.setValue( color );
}


Real32	SimpleMaterial::getTransparency  ( void )
{
	return _transparency.getValue();
}

Real32 SimpleMaterial::getTransparency  ( void ) const
{
	return _transparency.getValue();
}

void	SimpleMaterial::setTransparency  ( const Real32 color )
{
	_transparency.setValue( color );
}


/*-------------------------- your_category---------------------------------*/
	
	
void SimpleMaterial::draw( Geometry* geo, Action * action )
{
	StatePtr state = State::create();
	
	Vec3f v3;
	Vec4f v4;
	float alpha = 1.f - getTransparency();
	
	osgBeginEditCP( _materialChunk );
	
	v3 = getAmbient(); v4.setValues( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setAmbient( v4 );
	v3 = getDiffuse(); v4.setValues( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setDiffuse( v4 );
	v3 = getSpecular(); v4.setValues( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setSpecular( v4 );
	_materialChunk->setShininess( getShininess() );
	v3 = getEmission(); v4.setValues( v3[0], v3[1], v3[2], alpha ); 
	_materialChunk->setEmission( v4 );
	
	osgEndEditCP( _materialChunk );

	state->addChunk( _materialChunk );
	
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		state->addChunk( *i );
	
	state->activate();
	
	geo->draw( action );

	state->deactivate();
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void SimpleMaterial::dump(void) const
{
    SDEBUG << "SimpleMaterial at " << this << endl;
	PDEBUG << "\tambient: " << getAmbient() << endl;
	PDEBUG << "\tdiffuse: " << getDiffuse()  << endl;
	PDEBUG << "\tspecular: " << getSpecular()  << endl;
	PDEBUG << "\tshininess: " << getShininess()  << endl;
	PDEBUG << "\temission: " << getEmission()  << endl;
	PDEBUG << "\ttransparency: " << getTransparency()  << endl;
    PDEBUG << "\tChunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		PDEBUG << "\t" << *i << endl;
	
}

/*-------------------------- comparison -----------------------------------*/

#if 0

/** \brief assignment
 */

Bool SimpleMaterial::operator < (const SimpleMaterial &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool SimpleMaterial::operator == (const SimpleMaterial &other) const
{
	return false;
}

/** \brief unequal
 */

Bool SimpleMaterial::operator != (const SimpleMaterial &other) const
{
	return ! (*this == other);
}

#endif

/*------------------------- debug ----------------------------------*/

void SimpleMaterial::print( void )
{
    cerr << "SimpleMaterial at " << this << endl;
    cerr << "Chunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		cerr << *i << endl;
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

