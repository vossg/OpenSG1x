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


#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGFieldFactory.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGFieldType::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGField * (*OSGFieldType::OSGCreateFieldMethod)(void)
 *  Field create method
 */

/** \var OSGFieldDataType OSGFieldType::_typeId
 *  \brief Field data type
 */

/** \var char *OSGFieldType::_szName
 *  \brief Field type name
 */

/** \var OSGFieldType::_createMethod
 *  \brief Field create method
 */

/** \fn OSGFieldType::OSGFieldType(const OSGFieldType &source)
 *  \brief Not implemented.
 */

/** \fn void OSGFieldType::operator =(const OSGFieldType &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldType::cvsid[] = "@(#)$Id: $";

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

/** \brief Constructor
 */

OSGFieldType::OSGFieldType(const char           *szName,
                           OSGCreateFieldMethod  createMethod) :
    _typeId(0), 
    _szName(NULL), 
    _createMethod(createMethod)
{	
	if((szName       != NULL        ) && 
       (*szName      != '\0'        ) && 
       (createMethod != NULL))
    {
		if(OSGFieldFactory::_fieldTypeV == NULL) 
        {
			OSGFieldFactory::_fieldTypeV = new vector<OSGFieldType *>;
		}
        
		OSGFieldFactory::_fieldTypeV->push_back(this);
		_typeId = OSGFieldFactory::_fieldTypeV->size();

        stringDup(szName, _szName);		
	}
	else
		cerr << "ERROR: Invalid OSGField::OSGField() parameter" << endl;

    SLOG << "Initialized FieldType : " << _szName << endl;
}


/** \brief Destructor
 */

OSGFieldType::~OSGFieldType(void)
{
	(*OSGFieldFactory::_fieldTypeV)[_typeId] = 0;

	delete [] _szName;
}

/*--------------------------------- access ----------------------------------*/

/** \brief Get field data type. \sa OSGFieldDataType
 */

OSGUInt32 OSGFieldType::getTypeId(void) const
{
    return _typeId;
}

/** \brief Get type name
 */

const char *OSGFieldType::getName(void) const
{
    return _szName;
}

/*-------------------------------- comparision ------------------------------*/

OSGBool OSGFieldType::operator ==(const OSGFieldType &source) const
{
    return _typeId == source._typeId;
}

OSGBool OSGFieldType::operator !=(const OSGFieldType &source) const
{
    return ! (*this == source);
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




