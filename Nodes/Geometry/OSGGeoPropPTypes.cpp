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

#define OSG_COMPILEGEOPROPPTYPEINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropPTypes.h"

OSG_USING_NAMESPACE

FieldDescription *GeoPTypesUI8PropertyDesc::_desc[] =
{
    new FieldDescription(
        FieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                  GeoPTypesUI8PropertyDesc>::GeoPropDataField),
        false,
        (FieldAccessMethod) &GeoProperty<
                                  GeoPTypesUI8PropertyDesc>::getFieldPtr)
};

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate GeoProperty        <GeoPTypesUI8PropertyDesc >::_type

#else

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoPTypesUI8PropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif


OSG_END_NAMESPACE
