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

#include <OSGGeoPropertyInterface.h>

OSG_BEGIN_NAMESPACE

typedef GeoPositionsInterface::PtrType GeoPositionsInterfacePtr;

template <>
struct FieldDataTraits<GeoPositionsInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoPositionsInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                           { StringConvertable = 0x00            };
    enum                           { bHasParent        = 0x01            };

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */
    
    static Char8 *getSName (void)  { return "SFGeoPositionsInterfacePtr"; }
    static Char8 *getMName (void)  { return "MFGeoPositionsInterfacePtr"; }
    
    /*! \}                                                                 */        
};

#if 0
typedef SField<GeoPositionsPtr> SFGeoPositionsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPositionsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPositionsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoNormalsInterface::PtrType GeoNormalsInterfacePtr;

template <>
struct FieldDataTraits<GeoNormalsInterfacePtr> :
    public FieldTraitsRecurseMapper<GeoNormalsInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00          };
    enum                            { bHasParent        = 0x01          };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static Char8  *getSName  (void) { return "SFGeoNormalsInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoNormalsInterfacePtr"; }
    
    /*! \}                                                                 */    
};

#if 0
typedef SField<GeoNormalsPtr> SFGeoNormalsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoNormalsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoNormalsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif


typedef GeoColorsInterface::PtrType GeoColorsInterfacePtr;

template <>
struct FieldDataTraits<GeoColorsInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoColorsInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static Char8  *getSName  (void) { return "SFGeoColorsInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoColorsInterfacePtr"; }
    
    /*! \}                                                                 */        
};

#if 0
typedef SField<GeoColorsPtr> SFGeoColorsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoColorsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoColorsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoTexCoordsInterface::PtrType GeoTexCoordsInterfacePtr;

template <>
struct FieldDataTraits<GeoTexCoordsInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoTexCoordsInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00             };
    enum                            { bHasParent        = 0x01             };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static Char8  *getSName  (void) { return "SFGeoTexCoordsInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoTexCoordsInterfacePtr"; }
    
    /*! \}                                                                 */        
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


typedef GeoIndicesInterface::PtrType GeoIndicesInterfacePtr;

template <>
struct FieldDataTraits<GeoIndicesInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoIndicesInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static Char8  *getSName  (void) { return "SFGeoIndicesInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoIndicesInterfacePtr"; }
    
    /*! \}                                                                 */        
};

#if 0
typedef SField<GeoIndicesPtr> SFGeoIndicesPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoIndicesPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoIndicesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif



typedef GeoPTypesInterface::PtrType GeoPTypesInterfacePtr;

template <>
struct FieldDataTraits<GeoPTypesInterfacePtr> : 
    public FieldTraitsRecurseMapper<GeoPTypesInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00         };
    enum                            { bHasParent        = 0x01         };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static Char8  *getSName  (void) { return "SFGeoPTypesInterfacePtr"; }
    static Char8  *getMName  (void) { return "MFGeoPTypesInterfacePtr"; }
    
    /*! \}                                                                 */        
};

#if 0
typedef SField<GeoPTypesPtr> SFGeoPTypesPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPTypesPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPTypesPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif


typedef GeoPLengthsInterface::PtrType GeoPLengthsInterfacePtr;

template <>
struct FieldDataTraits<GeoPLengthsInterfacePtr> :
    public FieldTraitsRecurseMapper<GeoPLengthsInterfacePtr>
{
    /*---------------------------------------------------------------------*/
    /*! \name                    Struct Specific                           */
    /*! \{                                                                 */
    
    enum                            { StringConvertable = 0x00           };
    enum                            { bHasParent        = 0x01           };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static char   *getSName  (void) { return "SFGeoPLengthsInterfacePtr"; }
    static char   *getMName  (void) { return "MFGeoPLengthsInterfacePtr"; }
    
    /*! \}                                                                 */        
};

#if 0
typedef SField<GeoPLengthsPtr> SFGeoPLengthsPtr;

#ifndef OSG_COMPILEGEOPROPFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GeoPLengthsPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GeoPLengthsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPFIELDS_H_ */
