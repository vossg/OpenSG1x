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

#ifndef _OSGGEOPROPTEXCOORDS_H_
#define _OSGGEOPROPTEXCOORDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

struct GeoTexCoords2fPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords2f";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords2fProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 2;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFVec2f                     FieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

typedef GeoProperty<GeoTexCoords2fPropertyDesc> GeoTexCoords2f;

#ifndef OSG_COMPILEGEOPROPTEXCOORDSINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoTexCoords2fPropertyDesc>::_type

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords2fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


struct GeoTexCoords3fPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords3f";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords3fProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

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

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFVec3f                     FieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

typedef GeoProperty<GeoTexCoords3fPropertyDesc> GeoTexCoords3f;

#ifndef OSG_COMPILEGEOPROPTEXCOORDSINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoTexCoords3fPropertyDesc>::_type

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


OSG_END_NAMESPACE

#include <OSGGeoPropTexCoords.inl>

#endif /* _OSGGEOPROPTEXCOORDS_H_ */
