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

#ifndef _OSGGEOPROPTEXCOORDS_H_
#define _OSGGEOPROPTEXCOORDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief The descriptor trait for osg::GeoTexCoords1f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords1fPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords1f";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords1fProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 1;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFReal32                    StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords1fPropertyDesc> GeoTexCoords1f;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords1fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoTexCoords2f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords2fPropertyDesc : public GeoTexCoordsPropertyDesc
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

    typedef MFVec2f                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords2fPropertyDesc> GeoTexCoords2f;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords2fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoTexCoords3f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords3fPropertyDesc : public GeoTexCoordsPropertyDesc
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

    typedef MFVec3f                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords3fPropertyDesc> GeoTexCoords3f;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief The descriptor trait for osg::GeoTexCoords4f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords4fPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords4f";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords4fProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_FLOAT;        }
    static UInt32             getFormatSize(void) { return sizeof(GLfloat); }
    static UInt32             getDimension (void) { return 4;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFVec4f                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords4fPropertyDesc> GeoTexCoords4f;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords4fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoTexCoords1d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords1dPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords1d";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords1dProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_DOUBLE;       }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble);}
    static UInt32             getDimension (void) { return 1;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFReal64                    StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords1dPropertyDesc> GeoTexCoords1d;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords1dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoTexCoords2d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords2dPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords2d";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords2dProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_DOUBLE;       }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble);}
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

    typedef MFVec2d                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords2dPropertyDesc> GeoTexCoords2d;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords2dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoTexCoords3d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords3dPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords3d";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords3dProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_DOUBLE;       }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble);}
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

    typedef MFVec3d                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords3dPropertyDesc> GeoTexCoords3d;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords3dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief The descriptor trait for osg::GeoTexCoords4d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoTexCoords4dPropertyDesc : public GeoTexCoordsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */

    static const Char8 *getTypeName (void) { return "GeoTexCoords4d";         }
    static const Char8 *getClassName(void) { return "GeoTexCoords4dProperty"; }
    static const Char8 *getFieldName(void) { return "TexCoords";              }
    static const Char8 *getGroupName(void) { return "GeoTexCoords";           }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_DOUBLE;       }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble);}
    static UInt32             getDimension (void) { return 4;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */

    typedef GeoTexCoords                Inherited;
    typedef GeoTexCoords::PtrType       InheritedPtr;

    typedef GeoTexCoordsPropertyDesc    InheritedDesc;

    typedef MFVec4d                     StoredFieldType;
    typedef InheritedDesc::GenericType  GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoTexCoordsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoTexCoords4dPropertyDesc> GeoTexCoords4d;
#endif

#if !defined(OSG_COMPILEGEOPROPTEXCOORDSINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoTexCoords4dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


OSG_END_NAMESPACE

#include <OSGGeoPropTexCoords.inl>

#endif /* _OSGGEOPROPTEXCOORDS_H_ */
