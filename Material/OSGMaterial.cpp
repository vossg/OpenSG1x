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

#define OSG_COMPILEMATERIAL
#define OSG_COMPILEMATERIALINST

#include "OSGFieldDescription.h"
#include "OSGMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup MaterialLib

The Material abstracts the surface characteristics that are used to render 
the renderable objects. 

*/

/*! \class osg::Material
    \ingroup MaterialLib

The material base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<MaterialPtr>::_fieldType
#pragma instantiate MField<MaterialPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, MaterialPtr, OSG_MATERIAL_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, MaterialPtr, OSG_MATERIAL_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


char Material::cvsid[] = "@(#)$Id: OSGMaterial.cpp,v 1.5 2001/02/13 15:47:40 dirk Exp $";

// FieldDescription Material::_desc[] = {};

FieldContainerType Material::_type(
	"Material", 
	"FieldContainer", 
	NULL,
	NULL,
	NULL,
	NULL, 	// _desc, 
	0 		// sizeof(_desc)
	);

OSG_MATERIAL_DLLMAPPING MaterialPtr OSG::NullMaterial;

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

OSG_ABSTR_FIELD_CONTAINER_DEF(Material, MaterialPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Material::Material(void) :
	Inherited()
{
}

Material::Material( const Material& source ) :
	Inherited(source)
{
}

/** \brief Destructor
 */

Material::~Material(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/


/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void Material::dump(      UInt32     uiIndent, 
                    const BitVector &bvFlags) const
{
    SDEBUG << "Dump Material NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool Material::operator < (const Material &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool Material::operator == (const Material &other) const
{
	return false;
}

/** \brief unequal
 */

Bool Material::operator != (const Material &other) const
{
	return ! (*this == other);
}

/*------------------------- debug ----------------------------------*/

void Material::print( void )
{
	cerr << "Material at " << this << endl;
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

