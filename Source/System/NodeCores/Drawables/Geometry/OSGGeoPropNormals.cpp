/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#define OSG_COMPILEGEOPROPNORMALINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropNormals.h"

OSG_USING_NAMESPACE

FieldDescription *GeoNormals3fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                  GeoNormals3fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoNormals3fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                  GeoNormals3fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoNormals3sPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                  GeoNormals3sPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoNormals3sPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                  GeoNormals3sPropertyDesc>::getFieldPtr)
#endif
};

#ifndef OSG_NO_INT8_PNT
FieldDescription *GeoNormals3bPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                  GeoNormals3bPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoNormals3sPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                  GeoNormals3bPropertyDesc>::getFieldPtr)
#endif
};
#endif

OSG_GEO_PROP_TYPE_TMPL_DEF(GeoProperty, GeoPropertyDesc, PtrType)

OSG_BEGIN_NAMESPACE

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        ,
                           GeoNormals3fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        ,
                           GeoNormals3sPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

#ifndef OSG_NO_INT8_PNT
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        ,
                           GeoNormals3bPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
#endif

OSG_END_NAMESPACE
