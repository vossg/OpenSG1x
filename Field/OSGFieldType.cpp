/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEBASELIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGFieldFactory.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: $";
    char cvsid_hpp[] = OSGFIELDTYPE_HEADER_CVSID;
}

/** \fn const char *FieldType::getClassname(void)
 *  \brief Classname
 */

/** \typedef Field * (*FieldType::CreateFieldMethod)(void)
 *  Field create method
 */

/** \var FieldDataType FieldType::_typeId
 *  \brief Field data type
 */

/** \var char *FieldType::_szName
 *  \brief Field type name
 */

/** \var FieldType::_createMethod
 *  \brief Field create method
 */

/** \fn FieldType::FieldType(const FieldType &source)
 *  \brief Not implemented.
 */

/** \fn void FieldType::operator =(const FieldType &source)
 *  \brief Not implemented.
 */

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

FieldType::FieldType(const Char8             *szName,
                     const Char8             *szParentName,
                     const DataType          &contentType,
                           CreateFieldMethod  createMethod,
                           Cardinality        cardinality) :
     Inherited   (szName, szParentName, true),
    _contentType (contentType               ),
    _createMethod(createMethod              ),
    _cardinality (cardinality               )
{	
    FieldFactory::addType(this);
    FDEBUG (("Initialized FieldType : %s\n", getCName()));
}


/** \brief Destructor
 */

FieldType::~FieldType(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

const DataType &FieldType::getContentType(void) const
{
    return _contentType;
}

FieldType::Cardinality FieldType::getCardinality(void) const
{
    return _cardinality;
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




