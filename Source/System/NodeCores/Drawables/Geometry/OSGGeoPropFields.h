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

#ifndef _OSGGEOPROPFIELDS_H_
#define _OSGGEOPROPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \file OSGGeoPropFields.h
    \ingroup GrpSystemField
    \ingroup GrpSystemFieldTraits
 */

typedef GeoPositions::PtrType GeoPositionsPtr;
typedef GeoNormals  ::PtrType GeoNormalsPtr;
typedef GeoColors   ::PtrType GeoColorsPtr;
typedef GeoTexCoords::PtrType GeoTexCoordsPtr;
typedef GeoIndices  ::PtrType GeoIndicesPtr;
typedef GeoPTypes   ::PtrType GeoPTypesPtr;
typedef GeoPLengths ::PtrType GeoPLengthsPtr;


typedef RefPtr<GeoPositionsPtr> GeoPositionsRefPtr;
typedef RefPtr<GeoNormalsPtr>   GeoNormalsRefPtr;
typedef RefPtr<GeoColorsPtr>    GeoColorsRefPtr;
typedef RefPtr<GeoTexCoordsPtr> GeoTexCoordsRefPtr;
typedef RefPtr<GeoIndicesPtr>   GeoIndicesRefPtr;
typedef RefPtr<GeoPTypesPtr>    GeoPTypesRefPtr;
typedef RefPtr<GeoPLengthsPtr>  GeoPLengthsRefPtr;


#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoPositionsPtr> :
    public FieldTraitsRecurseMapper<GeoPositionsPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoPositionsPtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFGeoPositionsPtr"; }
    static Char8    *getMName (void) { return "MFGeoPositionsPtr"; }

    /*! \}                                                                 */
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoPositionsPtr, true> */
/*! \hideinhierarchy                                        */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoPositionsPtr> SFGeoPositionsPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoPositionsPtr> MFGeoPositionsPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPositionsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoPositionsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoNormalsPtr> :
    public FieldTraitsRecurseMapper<GeoNormalsPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoNormalsPtr>  Self;
    static  DataType                       _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;             }
    static Char8    *getSName (void) { return "SFGeoNormalsPtr"; }
    static Char8    *getMName (void) { return "MFGeoNormalsPtr"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoNormalsPtr, true> */
/*! \hideinhierarchy                                      */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoNormalsPtr> SFGeoNormalsPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoNormalsPtr> MFGeoNormalsPtr;

#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoNormalsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoNormalsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoColorsPtr> :
    public FieldTraitsRecurseMapper<GeoColorsPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoColorsPtr>  Self;
    static  DataType                      _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;             }
    static Char8    *getSName (void) { return "SFGeoColorsPtr";  }
    static Char8    *getMName (void) { return "MFGeoColorsPtr";  }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoColorsPtr, true> */
/*! \hideinhierarchy                                     */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoColorsPtr> SFGeoColorsPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoColorsPtr> MFGeoColorsPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoColorsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoColorsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoTexCoordsPtr> :
    public FieldTraitsRecurseMapper<GeoTexCoordsPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoTexCoordsPtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFGeoTexCoordsPtr"; }
    static Char8    *getMName (void) { return "MFGeoTexCoordsPtr"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoTexCoordsPtr, true> */
/*! \hideinhierarchy                                        */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoTexCoordsPtr> SFGeoTexCoordsPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoTexCoordsPtr> MFGeoTexCoordsPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoIndicesPtr> :
    public FieldTraitsRecurseMapper<GeoIndicesPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    typedef FieldDataTraits<GeoIndicesPtr>  Self;
    static  DataType                       _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;              }
    static Char8    *getSName (void) { return "SFGeoIndicesPtr";  }
    static Char8    *getMName (void) { return "MFGeoIndicesPtr";  }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoIndicesPtr, true> */
/*! \hideinhierarchy                                      */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)  
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoIndicesPtr> SFGeoIndicesPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoIndicesPtr> MFGeoIndicesPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoIndicesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoIndicesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoPTypesPtr> :
    public FieldTraitsRecurseMapper<GeoPTypesPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoPTypesPtr>  Self;
    static  DataType                      _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;             }
    static Char8    *getSName (void) { return "SFGeoPTypesPtr";  }
    static Char8    *getMName (void) { return "MFGeoPTypesPtr";  }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoPTypesPtr, true> */
/*! \hideinhierarchy                                     */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoPTypesPtr> SFGeoPTypesPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoPTypesPtr> MFGeoPTypesPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPTypesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoPTypesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<GeoPLengthsPtr> :
    public FieldTraitsRecurseMapper<GeoPLengthsPtr, true>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */

    typedef FieldDataTraits<GeoPLengthsPtr>  Self;
    static  DataType                        _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

    static DataType &getType  (void) { return _type;              }
    static char     *getSName (void) { return "SFGeoPLengthsPtr"; }
    static char     *getMName (void) { return "MFGeoPLengthsPtr"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<GeoPLengthsPtr, true> */
/*! \hideinhierarchy                                       */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldSingle */
typedef SField<GeoPLengthsPtr> SFGeoPLengthsPtr;

/*! \ingroup GrpSystemFieldMulti */
typedef MField<GeoPLengthsPtr> MFGeoPLengthsPtr;
#endif

#ifndef OSG_COMPILEGEOPROPFIELDINST
OSG_DLLEXPORT_DECL1(SField, GeoPLengthsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GeoPLengthsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPFIELDS_H_ */


