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

/** Example class of an derived FieldContainer.
	Defines a background FieldContainer which contains 3 Fields 
	a single Field of Real32 (_real), an other single Field (_single) 
	and a multi Field (_multi).
*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEWINDOW
#define OSG_COMPILEBACKGROUNDINST

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGDerivedBackground.h"


using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/** the following code is needed, just adjust it to your code
*/
	OSG_BEGIN_NAMESPACE

	#if defined(__sgi)

	#pragma instantiate SField<DerivedBackgroundPtr>::_fieldType
	#pragma instantiate MField<DerivedBackgroundPtr>::_fieldType

	#else

	OSG_DLLEXPORT_DEF1(SField, DerivedBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)
	OSG_DLLEXPORT_DEF1(MField, DerivedBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

	#endif

	OSG_END_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/** ID definition
*/ 
char DerivedBackground::cvsid[] = "@(#)$Id: OSGDerivedBackground.cpp,v 1.1 2001/02/15 12:48:17 dirk Exp $";

/** now you have to do the definition of the declarated fields
*/
	/** first Field
	*/
	OSG_FC_FIRST_FIELD_IDM_DEF(DerivedBackground, RealField)

	/** order of Fields
	*/
	OSG_FC_FIELD_IDM_DEF      (DerivedBackground, SingleField, RealField)
	OSG_FC_FIELD_IDM_DEF      (DerivedBackground, MultiField, SingleField)

	/** last Field
	*/
	OSG_FC_LAST_FIELD_IDM_DEF (DerivedBackground, MultiField)

/** now you have to make a description for each of the used fields 
	including:
		- Field access type
		- name
		- declaration of the field (field ID, field mask)
		- whether it is a internal field (normaly not)
		- Field access method
*/
FieldDescription DerivedBackground::_desc[] = 
{
        FieldDescription( SFReal32::getClassType(), 
                            "real", 
                            OSG_FC_FIELD_IDM_DESC(RealField),
                            false,
                            (FieldAccessMethod) &DerivedBackground::getSFReal),

		FieldDescription( SFValueTypeT::getClassType(), 
							"single", 
							OSG_FC_FIELD_IDM_DESC(SingleField),
							false,           
							(FieldAccessMethod) &DerivedBackground::getSFSingle),

		FieldDescription( MFValueTypeT::getClassType(), 
							"multi", 
							OSG_FC_FIELD_IDM_DESC(MultiField),
							false,           
							(FieldAccessMethod) &DerivedBackground::getMFMulti),
};

/** and the description of your FieldContainer including:
		- name
		- father class
		- group (not in use until now)
		- constructor of prototype
		- init method 
		- name of FieldDescription variable (here: _desc)
		- size of FieldDescription variable
*/
FieldContainerType DerivedBackground::_type(
    "DerivedBackground", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &DerivedBackground::createEmpty,
    0,
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

/** definition of the Field container pointer
*/
OSG_FIELD_CONTAINER_DEF(DerivedBackground, DerivedBackgroundPtr)

/*------------- constructors & destructors --------------------------------*/

/** constructor
 */
 DerivedBackground::DerivedBackground(void) : Inherited()
{
}

/** copy constructor
*/
DerivedBackground::DerivedBackground(const DerivedBackground &source) 
{
}

/** destructor
 */
DerivedBackground::~DerivedBackground(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/** implementation of the defined functions
*/
void DerivedBackground::clear(DrawAction *, ViewportP)
{
}

/*-------------------------- assignment -----------------------------------*/

/** assignment
*/

DerivedBackground &DerivedBackground::operator = (const DerivedBackground &source)
{
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

/** dump
*/
void DerivedBackground::dump(void) const
{
    SDEBUG << "Dump DerivedBackground NI" << endl;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

