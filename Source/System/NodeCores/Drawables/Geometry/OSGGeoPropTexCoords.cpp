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

#define OSG_COMPILEGEOPROPTEXCOORDSINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropTexCoords.h"

OSG_USING_NAMESPACE

FieldDescription *GeoTexCoords1fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords1fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords1fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords1fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords2fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords2fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords2fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords2fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords3fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords3fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords3fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords3fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords4fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords4fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords4fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords4fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords1dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords1dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords1dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords1dPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords2dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords2dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords2dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords2dPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords3dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords3dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords3dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords3dPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoTexCoords4dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoTexCoords4dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoTexCoords4dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoTexCoords4dPropertyDesc>::getFieldPtr)
#endif
};

OSG_GEO_PROP_TYPE_TMPL_DEF(GeoProperty, GeoPropertyDesc, PtrType)

OSG_BEGIN_NAMESPACE

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords1fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords2fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords3fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords4fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords1dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords2dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords3dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty,
                           GeoTexCoords4dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
