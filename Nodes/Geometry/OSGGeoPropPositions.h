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


#ifndef _OSGGEOPROPPOSITIONS_H_
#define _OSGGEOPROPPOSITIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

struct GeoPositions3fPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions3f";         }
    static const Char8 *getClassName(void) { return "GeoPositions3fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 3;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt3f                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

typedef GeoProperty<GeoPositions3fPropertyDesc> GeoPositions3f;

#ifndef OSG_COMPILEGEOPROPPOSITIONINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPositions3fPropertyDesc>::_type

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

struct GeoPositions3dPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions3d";         }
    static const Char8 *getClassName(void) { return "GeoPositions3dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_DOUBLE;        }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble); }
    static UInt32             getDimension (void) { return 3;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt3d                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

typedef GeoProperty<GeoPositions3dPropertyDesc> GeoPositions3d;

#ifndef OSG_COMPILEGEOPROPPOSITIONINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPositions3dPropertyDesc>::_type

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions3dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropPositions.inl>

#endif /* _OSGGEOPROPPOSITIONS_H_ */
