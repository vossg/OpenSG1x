/*---------------------------------------------------------------------------*\
 *       Scientific Visualization, Simulation and Computation Library        *
 *                                                                           *
 *                                                                           *
 *                                Copyright                                  *
 *                                2000,2001                                  *
 *                            by Fraunhofer IGD                              *
 *                                                                           *
 *                       contact: vossg@igd.fhg.de                           *
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

#define OSG_COMPILEDATASTORE

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGDataElementDesc.h"
#include "OSGDataType.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGDATAELEMENTDESC_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

AnonObjectP DataElementDesc::getElement(
    ReflexiveContainer &dataStore) const
{
	AnonObjectP pElement = NULL;

	if(_fGetMethod != NULL)
    {
		pElement = ( (&dataStore)->*_fGetMethod) ();
    }
    else if(_fIndexedGetMethod != NULL)
    {
        pElement = ( (&dataStore)->*_fIndexedGetMethod)(_uiElementId);
    }
	else 
    {
		SWARNING << "No accessMethod for " << _szName.str() << endl;
	}

	return pElement;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

DataElementDesc::DataElementDesc(
    const DataType              &elementType,
    const Char8                 *szName,
    const UInt32                 uiElementId,
    const BitVector              vElementMask,
    const bool                   bInternal,
          DataElemGetMethod      fGetMethod,
          DataElemSetMethod      fSetMethod,
          DataElemSpezSetMethod  fSpezSetMethod) :
    
    _szName           (szName),

    _elementType      (elementType),
    _uiElementId      (uiElementId),
    _vElementMask     (vElementMask),

    _bInternal        (bInternal),

    _fGetMethod       (fGetMethod),
    _fIndexedGetMethod(NULL      ),

    _fSetMethod       (fSetMethod    ),
    _fSpezSetMethod   (fSpezSetMethod)
{
}

DataElementDesc::DataElementDesc(
    const DataType                 &elementType,
    const Char8                    *szName,
    const UInt32                    uiElementId,
    const BitVector                 vElementMask,
    const bool                      bInternal,
          DataElemIndexedGetMethod  fIndexedGetMethod,
          DataElemSetMethod         fSetMethod,
          DataElemSpezSetMethod     fSpezSetMethod) :
    
    _szName           (szName),

    _elementType      (elementType),
    _uiElementId      (uiElementId),
    _vElementMask     (vElementMask),

    _bInternal        (bInternal),

    _fGetMethod       (NULL             ),
    _fIndexedGetMethod(fIndexedGetMethod),

    _fSetMethod       (fSetMethod    ),
    _fSpezSetMethod   (fSpezSetMethod)
{
}

DataElementDesc::DataElementDesc(const DataElementDesc &source) :

    _szName           (source._szName),

    _elementType      (source._elementType),
    _uiElementId      (source._uiElementId),
    _vElementMask     (source._vElementMask),

    _bInternal        (source._bInternal),

    _fGetMethod       (source._fGetMethod),
    _fIndexedGetMethod(source._fIndexedGetMethod),

    _fSetMethod       (source._fSetMethod    ),
    _fSpezSetMethod   (source._fSpezSetMethod)
{
}

DataElementDesc::~DataElementDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

/*! \brief get method for attribute name 
 */

const Char8 *DataElementDesc::getCName(void) const
{
    return _szName.str(); 
}

const IDString &DataElementDesc::getName(void) const
{
    return _szName;
}

/*! \brief get method for attribute dataType 
 */

UInt32 DataElementDesc::getTypeId(void) const
{
    return _elementType.getId(); 
}

BitVector DataElementDesc::getElementMask(void) const
{
    return _vElementMask;
}
     
void DataElementDesc::setElementMask(BitVector vElementMask)
{
    _vElementMask = vElementMask;
}

UInt32 DataElementDesc::getElementId(void) const
{
    return _uiElementId;
}

void DataElementDesc::setElementId(UInt32 uiElementId)
{
    _uiElementId = uiElementId;
}

bool DataElementDesc::isValid(void)  const
{
    return (_szName.getLength()) ? true : false; 
} 


void DataElementDesc::setGetMethod(DataElemGetMethod fGetMethod)
{
    _fGetMethod = fGetMethod;
}

void DataElementDesc::setIndexGetMethod(
    DataElemIndexedGetMethod  fIndexedGetMethod)
{
    _fIndexedGetMethod = fIndexedGetMethod;
}

/*-------------------------- comparison -----------------------------------*/

void DataElementDesc::dump(      UInt32     uiIndent, 
                           const BitVector &        ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "Desc : " 
            << _szName.str() 
            << " ("      
            << _uiElementId 
            << " | "
            << _vElementMask 
            << ") ["
            << _elementType.getCName() 
            << " | "
            << _elementType.getId()
            << "]"
            << endl;
}

