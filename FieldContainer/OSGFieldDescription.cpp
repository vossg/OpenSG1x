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

OSG_USING_OSG_NAMESPACE

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

OSGFieldDescription::OSGFieldDescription(
    const OSGFieldType         &fieldType, 
    const char                 *name, 
    const OSGUInt32             fieldId,
    const OSGBitVector          fieldMask,
    const OSGBool               internal,
          OSGFieldAccessMethod  accessMethod,
    const char                 *defaultValue) :
    _fieldType(fieldType), 
    _name(name),
    _fieldId(fieldId),
    _fieldMask(fieldMask),
    _internal(internal),
    _accessMethod(accessMethod),
    _defaultValue(defaultValue) 
{
}

OSGFieldDescription::OSGFieldDescription(const OSGFieldDescription &obj) :
    _fieldType(obj._fieldType),
    _name(obj._name), 
    _fieldId(obj._fieldId),
    _fieldMask(obj._fieldMask),
    _internal(obj._internal),
    _accessMethod(obj._accessMethod), 
    _defaultValue(obj._defaultValue) 
{
}

OSGFieldDescription::~OSGFieldDescription(void) 
{
}

OSGField *OSGFieldDescription::getFieldValue (OSGFieldContainer &fc) 
{
	OSGField *field;

	if (_accessMethod)
		field = ( (&fc)->*_accessMethod) () ;
	else {
		field = 0;
		cerr << "No accessMethod for " << _name << endl;
	}

	return field;
}

OSGBitVector OSGFieldDescription::getFieldMask(void)
{
    return _fieldMask;
}

OSGUInt32 OSGFieldDescription::getFieldId  (void)
{
    return _fieldId;
}

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

/*------------------------------ access -----------------------------------*/

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

