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

#ifndef _OSGGEOPROPFIELDS_H_
#define _OSGGEOPROPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeoPropertyBase.h>

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

typedef GeoPosition::PtrType GeoPositionPtr;

template <>
struct FieldDataTraits<GeoPositionPtr> : 
    public FieldTraitsRecurseMapper<GeoPositionPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00   };
    enum                             { bHasParent        = 0x01   };

    static DataType &getType  (void) { return _type;              }
    static Char8    *getSName (void) { return "SFGeoPositionPtr"; }
    static Char8    *getMName (void) { return "MFGeoPositionPtr"; }
};

typedef SField<GeoPositionPtr> SFGeoPositionPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPositionPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPositionPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif




typedef GeoNormal::PtrType GeoNormalPtr;

template <>
struct FieldDataTraits<GeoNormalPtr> :
    public FieldTraitsRecurseMapper<GeoNormalPtr>
{
    static DataType                  _type;
    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x01  };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoNormalPtr"; }
    static Char8    *getMName (void) { return "MFGeoNormalPtr"; }
};

typedef SField<GeoNormalPtr> SFGeoNormalPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoNormalPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoNormalPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif



typedef GeoColor::PtrType GeoColorPtr;

template <>
struct FieldDataTraits<GeoColorPtr> : 
    public FieldTraitsRecurseMapper<GeoColorPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoColorPtr";  }
    static Char8    *getMName (void) { return "MFGeoColorPtr";  }
};

typedef SField<GeoColorPtr> SFGeoColorPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoColorPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoColorPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif




typedef GeoTexCoords::PtrType GeoTexCoordsPtr;

template <>
struct FieldDataTraits<GeoTexCoordsPtr> : 
    public FieldTraitsRecurseMapper<GeoTexCoordsPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00    };
    enum                             { bHasParent        = 0x01    };

    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFGeoTexCoordsPtr"; }
    static Char8    *getMName (void) { return "MFGeoTexCoordsPtr"; }
};

typedef SField<GeoTexCoordsPtr> SFGeoTexCoordsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoTexCoordsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif



typedef GeoIndex::PtrType GeoIndexPtr;

template <>
struct FieldDataTraits<GeoIndexPtr> : 
    public FieldTraitsRecurseMapper<GeoIndexPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoIndexPtr";  }
    static Char8    *getMName (void) { return "MFGeoIndexPtr";  }
};

typedef SField<GeoIndexPtr> SFGeoIndexPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoIndexPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoIndexPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif




typedef GeoPType::PtrType GeoPTypePtr;

template <>
struct FieldDataTraits<GeoPTypePtr> : 
    public FieldTraitsRecurseMapper<GeoPTypePtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoPTypePtr";  }
    static Char8    *getMName (void) { return "MFGeoPTypePtr";  }
};

typedef SField<GeoPTypePtr> SFGeoPTypePtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPTypePtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPTypePtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif



typedef GeoPLength::PtrType GeoPLengthPtr;

template <>
struct FieldDataTraits<GeoPLengthPtr> :
    public FieldTraitsRecurseMapper<GeoPLengthPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00  };
    enum                             { bHasParent        = 0x01  };

    static DataType &getType  (void) { return _type;             }
    static char     *getSName (void) { return "SFGeoPLengthPtr"; }
    static char     *getMName (void) { return "MFGeoPLengthPtr"; }
};

typedef SField<GeoPLengthPtr> SFGeoPLengthPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPLengthPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPLengthPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPFIELDS_H_ */


