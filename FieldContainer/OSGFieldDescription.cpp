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

#include <OSGString.h>

#include "OSGFieldContainer.h"
#include "OSGFieldDescription.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldDescription::cvsid[] = "@(#)$Id: $";

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

/*------------- constructors & destructors --------------------------------*/

/*! \brief Default Constructor 
 */

OSGFieldDescription::OSGFieldDescription(
    const OSGFieldType         &fieldType, 
    const OSGChar8             *name, 
    const OSGUInt32             fieldId,
    const OSGBitVector          fieldMask,
    const OSGBool               internal,
          OSGFieldAccessMethod  accessMethod,
    const OSGChar8             *defaultValue) :
    _fieldType(fieldType), 
    _name(name),
    _fieldId(fieldId),
    _fieldMask(fieldMask),
    _internal(internal),
    _accessMethod(accessMethod),
    _defaultValue(defaultValue) 
{
}

/*! \brief Destructor 
 */

OSGFieldDescription::~OSGFieldDescription(void) 
{
}



/*------------------------------ access -----------------------------------*/

/*! \brief get method for attribute name 
 */

const OSGChar8 *OSGFieldDescription::getName(void) const
{
    return _name.str(); 
}

/*! \brief get method for attribute defaultValue 
*/

const OSGChar8 *OSGFieldDescription::getDefaultValue(void) const
{
    return _defaultValue.str(); 
}

/*! \brief get method for attribute dataType 
 */

OSGUInt32 OSGFieldDescription::getTypeId(void) const
{
    return _fieldType.getTypeId(); 
}

OSGBitVector OSGFieldDescription::getFieldMask(void) const
{
    return _fieldMask;
}

OSGUInt32 OSGFieldDescription::getFieldId(void) const
{
    return _fieldId;
}

OSGBool OSGFieldDescription::isValid(void)  const
{
    return (_name.length()) ? true : false; 
} 

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

void OSGFieldDescription::print(void) const
{
	cerr << "OSGFieldDescription: type: " << _fieldType.getName() << "("
		 << _fieldType.getTypeId() << "), name: " 
         << _name << ", " << _accessMethod
         << ", defaultValue: " 
         << (_defaultValue.str() ? _defaultValue.str() : "NONE") 
         << ", Id : " << _fieldId
         << ", Mask : " << _fieldMask
         << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGField *OSGFieldDescription::getField(OSGFieldContainer &fc) const
{
	OSGField *field = NULL;

	if(_accessMethod != NULL)
    {
		field = ( (&fc)->*_accessMethod) ();
    }
	else 
    {
		SWARNING << "No accessMethod for " << _name << endl;
	}

	return field;
}

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

