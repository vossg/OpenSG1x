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

#ifndef _OSGPROPGEOCOLORS_H_
#define _OSGPROPGEOCOLORS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief GeoColors3fPropertyDesc
 *  \ingroup GrpSystemDrawablesGeometryProperties
 */

struct GeoColors3fPropertyDesc : public GeoColorsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoColors3f";         }
    static const Char8 *getClassName(void) { return "GeoColors3fProperty"; }
    static const Char8 *getFieldName(void) { return "colors";              }
    static const Char8 *getGroupName(void) { return "GeoColors";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 3;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
  
    typedef GeoColors                  Inherited;
    typedef GeoColors::PtrType         InheritedPtr;

    typedef GeoColorsPropertyDesc      InheritedDesc;

    typedef MFColor3f                  StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoColorsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoColors3fPropertyDesc> GeoColors3f;
#endif

#ifndef OSG_COMPILEGEOPROPCOLORINST
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoColors3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief GeoColors4fPropertyDesc
 *  \ingroup GrpSystemDrawablesGeometryProperties
 */

struct GeoColors4fPropertyDesc : public GeoColorsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoColors4f";         }
    static const Char8 *getClassName(void) { return "GeoColors4fProperty"; }
    static const Char8 *getFieldName(void) { return "Colors";              }
    static const Char8 *getGroupName(void) { return "GeoColors";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 4;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
  
    typedef GeoColors                  Inherited;
    typedef GeoColors::PtrType         InheritedPtr;

    typedef GeoColorsPropertyDesc      InheritedDesc;

    typedef MFColor4f                  StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoColorsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoColors4fPropertyDesc> GeoColors4f;
#endif

#ifndef OSG_COMPILEGEOPROPCOLORINST
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoColors4fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief GeoColors3ubPropertyDesc
 *  \ingroup GrpSystemDrawablesGeometryProperties
 */

struct GeoColors3ubPropertyDesc : public GeoColorsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoColors3ub";         }
    static const Char8 *getClassName(void) { return "GeoColors3ubProperty"; }
    static const Char8 *getFieldName(void) { return "Colors";               }
    static const Char8 *getGroupName(void) { return "GeoColors";            }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 3;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */

    typedef GeoColors                  Inherited;
    typedef GeoColors::PtrType         InheritedPtr;

    typedef GeoColorsPropertyDesc      InheritedDesc;

    typedef MFColor3ub                 StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoColorsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoColors3ubPropertyDesc> GeoColors3ub;
#endif

#ifndef OSG_COMPILEGEOPROPCOLORINST
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoColors3ubPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief GeoColors4ubPropertyDesc
 *  \ingroup GrpSystemDrawablesGeometryProperties
 */

struct GeoColors4ubPropertyDesc : public GeoColorsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName  (void) { return "GeoColors4ub";         }
    static const Char8 *getClassName (void) { return "GeoColors4ubProperty"; }
    static const Char8 *getFieldName (void) { return "Colors";               }
    static const Char8 *getGroupName (void) { return "GeoColors";            }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_BYTE; }
    static UInt32             getFormatSize(void) { return sizeof(GLubyte);  }
    static UInt32             getDimension (void) { return 4;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Typedefs                                   */
    /*! \{                                                                 */
    
    typedef GeoColors                  Inherited;
    typedef GeoColors::PtrType         InheritedPtr;

    typedef GeoColorsPropertyDesc      InheritedDesc;

    typedef MFColor4ub                 StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoColorsPropertyDesc> Interface;
#endif
    
    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoColors4ubPropertyDesc> GeoColors4ub;
#endif

#ifndef OSG_COMPILEGEOPROPCOLORINST
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoColors4ubPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropColors.inl>

#endif /* _OSGGEOPROPCOLORS_H_ */






