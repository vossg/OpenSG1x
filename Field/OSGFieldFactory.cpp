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

#include "OSGFieldFactory.h"

#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGFieldFactory::getClassname(void)
 *  \brief Classname
 */

/** \fn OSGFieldFactory::OSGFieldFactory(const OSGFieldFactory &source)
 *  \brief Not implemented.
 */

/** \fn void OSGFieldFactory::operator =(const OSGFieldFactory &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldFactory::cvsid[] = "@(#)$Id: $";

/** \brief Factory instance
 */

OSGFieldFactory   OSGFieldFactory::_the;

/** \brief Field type storage
 */

vector<OSGFieldType *> *OSGFieldFactory::_fieldTypeV  = NULL;

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

/** \brief Destructor
 */

OSGFieldFactory::~OSGFieldFactory(void )
{
	SINFO << "INFO: Destroy Singleton OSGFieldFactory" << endl;
}

/*------------------------------ create ------------------------------------*/

/** \brief Create a field of the given type
 */

OSGField * OSGFieldFactory::createField(OSGUInt32 typeId)
{
	if((  _fieldTypeV          != NULL) &&
       ((*_fieldTypeV)[typeId] != NULL) && 
       ((*_fieldTypeV)[typeId]->_createMethod))
    {
		return (*_fieldTypeV)[typeId]->_createMethod();
    }
	else
    {
		return NULL;
    }
}

/** \brief Create a field of the type given by the type name
 */

OSGField * OSGFieldFactory::createField(const char *szName)
{
	OSGFieldType *type = getFieldType(szName);

	return type ? type->_createMethod() : NULL;
}

/*---------------------------------- type -----------------------------------*/

/** \Brief Get type by name
 */

OSGFieldType * OSGFieldFactory::getFieldType (const char *szName)
{
	OSGFieldType *type = 0;
	OSGUInt32 i;
	
	if(_fieldTypeV != NULL) 
    {
		for(i = 0; i < _fieldTypeV->size(); i++)
        {
			if( ((*_fieldTypeV)[i]  != NULL              ) && 
                (! strcmp(szName, (*_fieldTypeV)[i]->_szName)) ) 
            {
				type = (*_fieldTypeV)[i];
				break;
			}
        }
	}

	return type;
}

/** \brief Get type by data type
 */

OSGFieldType * OSGFieldFactory::getFieldType(OSGUInt32 typeId)
{
	return _fieldTypeV ? (*_fieldTypeV)[typeId] : NULL;
}


/*---------------------------------- name -----------------------------------*/

/** \brief Get the name of the given data type
 */

const char *OSGFieldFactory::getFieldTypeName(OSGUInt32 typeId)
{
	OSGFieldType *fieldType = 
        _fieldTypeV ? (*_fieldTypeV)[typeId] : NULL;

	return fieldType ? fieldType->_szName : NULL;
}

/*---------------------------------- instance -------------------------------*/

/** \brief Returns a reference to the global factory
 */

OSGFieldFactory &OSGFieldFactory::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

OSGFieldFactory::OSGFieldFactory(void)
{
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

