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


#ifndef _OSGGEOPROPPOSITIONS_H_
#define _OSGGEOPROPPOSITIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief The descriptor trait for osg::GeoPositions2f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions2fPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions2f";         }
    static const Char8 *getClassName(void) { return "GeoPositions2fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

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
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt2f                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions2fPropertyDesc> GeoPositions2f;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions2fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions3f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions3fPropertyDesc : public GeoPositionsPropertyDesc
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

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions3fPropertyDesc> GeoPositions3f;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions4f.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions4fPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions4f";         }
    static const Char8 *getClassName(void) { return "GeoPositions4fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

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
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt4f                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions4fPropertyDesc> GeoPositions4f;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions4fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions2d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions2dPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions2d";         }
    static const Char8 *getClassName(void) { return "GeoPositions2dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_DOUBLE;        }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble); }
    static UInt32             getDimension (void) { return 2;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt2d                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions2dPropertyDesc> GeoPositions2d;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions2dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions3d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions3dPropertyDesc : public GeoPositionsPropertyDesc
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

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions3dPropertyDesc> GeoPositions3d;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions3dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions4d.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions4dPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions4d";         }
    static const Char8 *getClassName(void) { return "GeoPositions4dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_DOUBLE;        }
    static UInt32             getFormatSize(void) { return sizeof(GLdouble); }
    static UInt32             getDimension (void) { return 4;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt4d                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPositions4dPropertyDesc> GeoPositions4d;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions4dPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif



/*! \brief The descriptor trait for osg::GeoPositions2s.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions2sPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions2s";         }
    static const Char8 *getClassName(void) { return "GeoPositions2sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_SHORT;         }
    static UInt32             getFormatSize(void) { return sizeof(GLshort);  }
    static UInt32             getDimension (void) { return 2;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt2s                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent shorts
typedef GeoProperty<GeoPositions2sPropertyDesc> GeoPositions2s;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions2sPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions3s.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions3sPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions3s";         }
    static const Char8 *getClassName(void) { return "GeoPositions3sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_SHORT;         }
    static UInt32             getFormatSize(void) { return sizeof(GLshort);  }
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

    typedef MFPnt3s                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent shorts
typedef GeoProperty<GeoPositions3sPropertyDesc> GeoPositions3s;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions3sPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


/*! \brief The descriptor trait for osg::GeoPositions4s.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPositions4sPropertyDesc : public GeoPositionsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPositions4s";         }
    static const Char8 *getClassName(void) { return "GeoPositions4sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "GeoPositions";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_SHORT;         }
    static UInt32             getFormatSize(void) { return sizeof(GLshort);  }
    static UInt32             getDimension (void) { return 4;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    
    typedef GeoPositions               Inherited;
    typedef GeoPositions::PtrType      InheritedPtr;

    typedef GeoPositionsPropertyDesc   InheritedDesc;

    typedef MFPnt4s                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPositionsPropertyDesc> Interface;
#endif

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent shorts
typedef GeoProperty<GeoPositions4sPropertyDesc> GeoPositions4s;
#endif

#if !defined(OSG_COMPILEGEOPROPPOSITIONINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPositions4sPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropPositions.inl>

#endif /* _OSGGEOPROPPOSITIONS_H_ */
