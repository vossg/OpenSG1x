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

#ifndef _OSGGEOPROPINTERFACEFIELDS_H_
#define _OSGGEOPROPINTERFACEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeoPropertyInterface.h>

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

typedef GeoPositionInterface::PtrType GeoPositionInterfacePtr;

template <>
struct FieldDataTraits<GeoPositionInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoPositionInterfacePtr>
{
    enum                           { StringConvertable = 0x00            };
    enum                           { bHasParent        = 0x01            };

    static Char8 *getSName (void)  { return "SFGeoPositionInterfacePtr"; }
    static Char8 *getMName (void)  { return "MFGeoPositionInterfacePtr"; }
};

#if 0
typedef SField<GeoPositionPtr> SFGeoPositionPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPositionPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPositionPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoNormalInterface::PtrType GeoNormalInterfacePtr;

template <>
struct FieldDataTraits<GeoNormalInterfacePtr> :
    public FieldTraitsRecurseMapper<GeoNormalInterfacePtr>
{
    enum                            { StringConvertable = 0x00          };
    enum                            { bHasParent        = 0x01          };

    static Char8  *getSName  (void) { return "SFGeoNormalInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoNormalInterfacePtr"; }
};

#if 0
typedef SField<GeoNormalPtr> SFGeoNormalPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoNormalPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoNormalPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif


typedef GeoColorInterface::PtrType GeoColorInterfacePtr;

template <>
struct FieldDataTraits<GeoColorInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoColorInterfacePtr>
{
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    static Char8  *getSName  (void) { return "SFGeoColorInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoColorInterfacePtr"; }
};

#if 0
typedef SField<GeoColorPtr> SFGeoColorPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoColorPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoColorPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoTexCoordsInterface::PtrType GeoTexCoordsInterfacePtr;

template <>
struct FieldDataTraits<GeoTexCoordsInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoTexCoordsInterfacePtr>
{
    enum                            { StringConvertable = 0x00             };
    enum                            { bHasParent        = 0x01             };

    static Char8  *getSName  (void) { return "SFGeoTexCoordsInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoTexCoordsInterfacePtr"; }
};

#if 0
typedef SField<GeoTexCoordsPtr> SFGeoTexCoordsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoTexCoordsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif


typedef GeoIndexInterface::PtrType GeoIndexInterfacePtr;

template <>
struct FieldDataTraits<GeoIndexInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoIndexInterfacePtr>
{
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    static Char8  *getSName  (void) { return "SFGeoIndexInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoIndexInterfacePtr"; }
};

#if 0
typedef SField<GeoIndexPtr> SFGeoIndexPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoIndexPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoIndexPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoPTypeInterface::PtrType GeoPTypeInterfacePtr;

template <>
struct FieldDataTraits<GeoPTypeInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoPTypeInterfacePtr>
{
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    static Char8  *getSName  (void) { return "SFGeoPTypeInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoPTypeInterfacePtr"; }
};

#if 0
typedef SField<GeoPTypePtr> SFGeoPTypePtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPTypePtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPTypePtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif


typedef GeoPLengthInterface::PtrType GeoPLengthInterfacePtr;

template <>
struct FieldDataTraits<GeoPLengthInterfacePtr> :
    public FieldTraitsRecurseMapper<GeoPLengthInterfacePtr>
{
    enum                            { StringConvertable = 0x00           };
    enum                            { bHasParent        = 0x01           };

    static char   *getSName  (void) { return "SFGeoPLengthInterfacePtr"; }
    static char   *getMName  (void) { return "MFGeoPLengthInterfacePtr"; }
};

#if 0
typedef SField<GeoPLengthPtr> SFGeoPLengthPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPLengthPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPLengthPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPFIELDS_H_ */


