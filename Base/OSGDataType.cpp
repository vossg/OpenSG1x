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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGDataType.h"
#include <OSGTypeFactory.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGDATATYPE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::DataType
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DataType::DataType(const Char8 *szName,
                   const Char8 *szParentName) :
    Inherited(szName, szParentName)
{
}

DataType::DataType(const DataType &source) :
    Inherited(source)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DataType::~DataType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool DataType::operator ==(const DataType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool DataType::operator !=(const DataType &other) const
{
    return ! (*this == other);
}
