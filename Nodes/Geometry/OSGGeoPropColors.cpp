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

#define OSG_COMPILEGEOPROPCOLORINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropColors.h"

OSG_USING_NAMESPACE

FieldDescription *GeoColors3fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoColors3fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoColors3fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoColors3fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoColors4fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoColors4fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoColors4fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoColors4fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoColors3ubPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoColors3ubPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoColors3ubPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoColors3ubPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoColors4ubPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoColors4ubPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        (FieldAccessMethod) NULL)
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoColors4ubPropertyDesc>::getFieldPtr)
#endif
};

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate GeoProperty        <GeoColors3fPropertyDesc   >::_type
#pragma instantiate GeoProperty        <GeoColors4fPropertyDesc   >::_type
#pragma instantiate GeoProperty        <GeoColors3ubPropertyDesc  >::_type
#pragma instantiate GeoProperty        <GeoColors4ubPropertyDesc  >::_type

#else

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoColors3fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoColors4fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoColors3ubPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoColors4ubPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE
