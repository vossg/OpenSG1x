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

#include "OSGMaterialChunk.h"

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

OSG_FC_FIRST_FIELD_IDM_DEF(OSGMaterialChunk, OSGDiffuseField)

OSG_FC_FIELD_IDM_DEF      (OSGMaterialChunk, 
                           OSGAmbientField,  
                           OSGDiffuseField)
OSG_FC_FIELD_IDM_DEF      (OSGMaterialChunk, 
                           OSGSpecularField,  
                           OSGAmbientField)
OSG_FC_FIELD_IDM_DEF      (OSGMaterialChunk, 
                           OSGEmissionField,  
                           OSGSpecularField)
OSG_FC_FIELD_IDM_DEF      (OSGMaterialChunk, 
                           OSGShininessField,  
                           OSGEmissionField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGMaterialChunk, OSGShininessField)


char OSGMaterialChunk::cvsid[] = "@(#)$Id: $";

OSGStateChunkClass OSGMaterialChunk::_class(OSGString("Material"));


OSGFieldDescription OSGMaterialChunk::_desc[] = 
{
        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(OSGDiffuseField),
        false,
        (OSGFieldAccessMethod) &OSGMaterialChunk::getSFDiffuse,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(OSGAmbientField),
        false,
        (OSGFieldAccessMethod) &OSGMaterialChunk::getSFAmbient,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "specular", 
        OSG_FC_FIELD_IDM_DESC(OSGSpecularField),
        false,
        (OSGFieldAccessMethod) &OSGMaterialChunk::getSFSpecular,
        ""),

        OSGFieldDescription(
        OSGSFVec4f::getClassType(), 
        "emission", 
        OSG_FC_FIELD_IDM_DESC(OSGEmissionField),
        false,
        (OSGFieldAccessMethod) &OSGMaterialChunk::getSFEmission,
        ""),

        OSGFieldDescription(
        OSGSFReal32::getClassType(), 
        "shininess", 
        OSG_FC_FIELD_IDM_DESC(OSGShininessField),
        false,
        (OSGFieldAccessMethod) &OSGMaterialChunk::getSFShininess,
        "")
};

OSGFieldContainerType OSGMaterialChunk::_type(
	"MaterialChunk", 
	"StateChunk", 
	NULL,
	(OSGPrototypeCreateF) &OSGMaterialChunk::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGMaterialChunk, OSGMaterialChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGMaterialChunk::OSGMaterialChunk(void) :
	Inherited(), 
	_diffuse( OSGVec4f(1,1,1,0 ) ), _ambient( OSGVec4f(.2,.2,.2,0 ) ), 
	_specular( OSGVec4f(.5,.5,.5,0 ) ), _emission( OSGVec4f(0,0,0,0 ) ), 
	_shininess( 10 )
{
	_ownClass = _class.getID();
}


OSGMaterialChunk::OSGMaterialChunk( const OSGMaterialChunk& source ) :
	Inherited(source),
	_diffuse( source._diffuse ), _ambient( source._ambient ), 
	_specular( source._specular ), _emission( source._emission ), 
	_shininess( source._shininess )
{
}


/** \brief Destructor
 */

OSGMaterialChunk::~OSGMaterialChunk(void)
{
}

/*---------------------------- properties ---------------------------------*/

// Diffuse Color

OSGSFVec4f *OSGMaterialChunk::getSFDiffuse(void)
{
	return &_diffuse;
}

OSGVec4f &OSGMaterialChunk::getDiffuse(void)
{
	return _diffuse.getValue();
}

const OSGVec4f &OSGMaterialChunk::getDiffuse(void) const
{
	return _diffuse.getValue();
}

void OSGMaterialChunk::setDiffuse( const OSGVec4f & color )
{
	_diffuse.setValue( color );
}


// Ambient Color

OSGSFVec4f *OSGMaterialChunk::getSFAmbient(void)
{
	return &_ambient;
}

OSGVec4f &OSGMaterialChunk::getAmbient(void)
{
	return _ambient.getValue();
}

const OSGVec4f &OSGMaterialChunk::getAmbient(void) const
{
	return _ambient.getValue();
}

void OSGMaterialChunk::setAmbient( const OSGVec4f & color )
{
	_ambient.setValue( color );
}


// Specular Color

OSGSFVec4f *OSGMaterialChunk::getSFSpecular(void)
{
	return &_specular;
}

OSGVec4f &OSGMaterialChunk::getSpecular(void)
{
	return _specular.getValue();
}

const OSGVec4f &OSGMaterialChunk::getSpecular(void) const
{
	return _specular.getValue();
}

void OSGMaterialChunk::setSpecular( const OSGVec4f & color )
{
	_specular.setValue( color );
}


// Emission Color

OSGSFVec4f *OSGMaterialChunk::getSFEmission(void)
{
	return &_emission;
}

OSGVec4f &OSGMaterialChunk::getEmission(void)
{
	return _emission.getValue();
}

const OSGVec4f &OSGMaterialChunk::getEmission(void) const
{
	return _emission.getValue();
}

void OSGMaterialChunk::setEmission( const OSGVec4f & color )
{
	_emission.setValue( color );
}


// Shininess Color

OSGSFReal32 *OSGMaterialChunk::getSFShininess(void)
{
	return &_shininess;
}

OSGReal32 OSGMaterialChunk::getShininess(void)
{
	return _shininess.getValue();
}

OSGReal32 OSGMaterialChunk::getShininess(void) const
{
	return _shininess.getValue();
}

void OSGMaterialChunk::setShininess( const OSGReal32 color )
{
	_shininess.setValue( color );
}




/*-------------------------- your_category---------------------------------*/

void OSGMaterialChunk::activate ( OSGUInt32 index )
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

void OSGMaterialChunk::changeFrom( OSGStateChunk * old_chunk, OSGUInt32 index )
{
	OSGMaterialChunk const *old = dynamic_cast<OSGMaterialChunk const*>(old_chunk);

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

void OSGMaterialChunk::deactivate ( OSGUInt32 index )
{
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGMaterialChunk::dump(void) const
{
    SDEBUG << "Dump OSGMaterialChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

OSGReal32 OSGMaterialChunk::switchCost( OSGStateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

OSGBool OSGMaterialChunk::operator < (const OSGStateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGMaterialChunk::operator == (const OSGStateChunk &other) const
{
	OSGMaterialChunk const *tother = dynamic_cast<OSGMaterialChunk const*>(&other);

	if ( !tother )
		return false;

	if ( ! getDiffuse().equals( tother->getDiffuse(), osgEps )
	   )
		return false;
		
	return true;
}

/** \brief unequal
 */

OSGBool OSGMaterialChunk::operator != (const OSGStateChunk &other) const
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

