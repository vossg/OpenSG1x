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

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

typedef GeoPositions::PtrType GeoPositionsPtr;

template <>
struct FieldDataTraits<GeoPositionsPtr> :
    public FieldTraitsRecurseMapper<GeoPositionsPtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                                 */
    /*! \{                                                                 */


    static DataType                  _type;
    enum                             { StringConvertable = 0x00   };
    enum                             { bHasParent        = 0x01   };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;              }
    static Char8    *getSName (void) { return "SFGeoPositionsPtr"; }
    static Char8    *getMName (void) { return "MFGeoPositionsPtr"; }

    /*! \}                                                                 */
};

typedef SField<GeoPositionsPtr> SFGeoPositionsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPositionsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




typedef GeoNormals::PtrType GeoNormalsPtr;

template <>
struct FieldDataTraits<GeoNormalsPtr> :
    public FieldTraitsRecurseMapper<GeoNormalsPtr>
{
    static DataType                  _type;
    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x01  };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoNormalsPtr"; }
    static Char8    *getMName (void) { return "MFGeoNormalsPtr"; }
};

typedef SField<GeoNormalsPtr> SFGeoNormalsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoNormalsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif



typedef GeoColors::PtrType GeoColorsPtr;

template <>
struct FieldDataTraits<GeoColorsPtr> :
    public FieldTraitsRecurseMapper<GeoColorsPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoColorsPtr";  }
    static Char8    *getMName (void) { return "MFGeoColorsPtr";  }
};

typedef SField<GeoColorsPtr> SFGeoColorsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoColorsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
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
OSG_DLLEXPORT_DECL1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif



typedef GeoIndices::PtrType GeoIndicesPtr;

template <>
struct FieldDataTraits<GeoIndicesPtr> :
    public FieldTraitsRecurseMapper<GeoIndicesPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoIndicesPtr";  }
    static Char8    *getMName (void) { return "MFGeoIndicesPtr";  }
};

typedef SField<GeoIndicesPtr> SFGeoIndicesPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoIndicesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




typedef GeoPTypes::PtrType GeoPTypesPtr;

template <>
struct FieldDataTraits<GeoPTypesPtr> :
    public FieldTraitsRecurseMapper<GeoPTypesPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00 };
    enum                             { bHasParent        = 0x01 };

    static DataType &getType  (void) { return _type;            }
    static Char8    *getSName (void) { return "SFGeoPTypesPtr";  }
    static Char8    *getMName (void) { return "MFGeoPTypesPtr";  }
};

typedef SField<GeoPTypesPtr> SFGeoPTypesPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPTypesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif



typedef GeoPLengths::PtrType GeoPLengthsPtr;

template <>
struct FieldDataTraits<GeoPLengthsPtr> :
    public FieldTraitsRecurseMapper<GeoPLengthsPtr>
{
    static DataType                  _type;
    enum                             { StringConvertable = 0x00  };
    enum                             { bHasParent        = 0x01  };

    static DataType &getType  (void) { return _type;             }
    static char     *getSName (void) { return "SFGeoPLengthsPtr"; }
    static char     *getMName (void) { return "MFGeoPLengthsPtr"; }
};

typedef SField<GeoPLengthsPtr> SFGeoPLengthsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPLengthsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPFIELDS_H_ */


