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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGFieldFactory.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDTYPE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::FieldType
 */


/*! \typedef Field *(*FieldType::CreateFieldMethod)(void)
    \brief Field create method
 */

/*! \var FieldType::_createMethod
    \brief Field create method
 */

/*! \var FieldType::_contentType
    \brief Type stored within fields of this type
 */

/*! \var FieldType::_cardinality
    \brief Cardinality of fields of this type
 */

/*! \var FieldType::Cardinality FieldType::SINGLE_FIELD
    \brief Single field
 */

/*! \var FieldType::Cardinality FieldType::MULTI_FIELD
    \brief Mulit field
 */

/*! \fn FieldType::FieldType(const FieldType &source)
    Only declared public if MSVS is used
 */

/*! \fn void FieldType::operator =(const FieldType &source)
    Only declared public if MSVS is used
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldType::FieldType(const Char8             *szName,
                     const Char8             *szParentName,
                     const DataType          &contentType,
                           CreateFieldMethod  createMethod,
                           Cardinality        cardinality) :
     Inherited   (szName, szParentName),
    _cardinality (cardinality         ),
    _contentType (contentType         ),
    _createMethod(createMethod        )
{
    FieldFactory::addType(this);
    FDEBUG (("Initialized FieldType : %s\n", getCName()));
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldType::~FieldType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

const DataType &FieldType::getContentType(void) const
{
    return _contentType;
}

FieldType::Cardinality FieldType::getCardinality(void) const
{
    return _cardinality;
}



