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

#define OSG_COMPILEGEOPROPPOSITIONINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropPositions.h"

OSG_USING_NAMESPACE

FieldDescription *GeoPositions2fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions2fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions2fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions2fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions3fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions3fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions3fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions3fPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions4fPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions4fPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions4fPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions4fPropertyDesc>::getFieldPtr)
#endif
};



FieldDescription *GeoPositions2dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions2dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions2dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions2dPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions3dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions3dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions3dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions3dPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions4dPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions4dPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions4dPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions4dPropertyDesc>::getFieldPtr)
#endif
};


FieldDescription *GeoPositions2sPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions2sPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions2sPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions2sPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions3sPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions3sPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions3sPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions3sPropertyDesc>::getFieldPtr)
#endif
};

FieldDescription *GeoPositions4sPropertyDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoProperty<
                                GeoPositions4sPropertyDesc>::GeoPropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoProperty<GeoPositions4sPropertyDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &GeoProperty<
                                GeoPositions4sPropertyDesc>::getFieldPtr)
#endif
};

OSG_GEO_PROP_TYPE_TMPL_DEF(GeoProperty, GeoPropertyDesc, PtrType)

OSG_BEGIN_NAMESPACE

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions2fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions3fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions4fPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions2dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions3dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions4dPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions2sPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions3sPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_GEOPROP_DLLEXPORT_DEF (GeoProperty        , 
                           GeoPositions4sPropertyDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

