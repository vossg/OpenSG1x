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


#ifndef _OSGGEOPROPPLENGTHS_H_
#define _OSGGEOPROPPLENGTHS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief The descriptor trait for osg::GeoPLengthsUI32.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPLengthsUI32PropertyDesc : public GeoPLengthsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPLengthsUI32";        }
    static const Char8 *getClassName(void) { return "GeoPLengthsUI32Property";}
    static const Char8 *getFieldName(void) { return "lengths";                }
    static const Char8 *getGroupName(void) { return "GeoPLengths";            }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_INT; }
    static UInt32             getFormatSize(void) { return sizeof(GLuint);  }
    static UInt32             getDimension (void) { return 1;               }
    static UInt32             getStride    (void) { return 0;               }

    static FieldDescription **getDesc      (void) { return _desc;           }
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    typedef GeoPLengths                Inherited;
    typedef GeoPLengths::PtrType       InheritedPtr;

    typedef GeoPLengthsPropertyDesc    InheritedDesc;

    typedef MFUInt32                   StoredFieldType;

    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc> Interface;
#endif    

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPLengthsUI32PropertyDesc> GeoPLengthsUI32;
#endif

#if !defined(OSG_COMPILEGEOPROPPLENGTHINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPLengthsUI32PropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief The descriptor trait for osg::GeoPLengthsUI16.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPLengthsUI16PropertyDesc : public GeoPLengthsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPLengthsUI16";        }
    static const Char8 *getClassName(void) { return "GeoPLengthsUI16Property";}
    static const Char8 *getFieldName(void) { return "lengths";                }
    static const Char8 *getGroupName(void) { return "GeoPLengths";            }

    static InitContainerF     getInitMethod(void) { return NULL;              }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_SHORT; }
    static UInt32             getFormatSize(void) { return sizeof(GLushort);  }
    static UInt32             getDimension (void) { return 1;                 }
    static UInt32             getStride    (void) { return 0;                 }

    static FieldDescription **getDesc      (void) { return _desc;             }
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    typedef GeoPLengths                Inherited;
    typedef GeoPLengths::PtrType       InheritedPtr;

    typedef GeoPLengthsPropertyDesc    InheritedDesc;

    typedef MFUInt16                   StoredFieldType;

    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc> Interface;
#endif    

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPLengthsUI16PropertyDesc> GeoPLengthsUI16;
#endif

#if !defined(OSG_COMPILEGEOPROPPLENGTHINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPLengthsUI16PropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

/*! \brief The descriptor trait for osg::GeoPLengthsUI8.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPLengthsUI8PropertyDesc : public GeoPLengthsPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
    
    static const Char8 *getTypeName (void) { return "GeoPLengthsUI8";        }
    static const Char8 *getClassName(void) { return "GeoPLengthsUI8Property";}
    static const Char8 *getFieldName(void) { return "lengths";               }
    static const Char8 *getGroupName(void) { return "GeoPLengths";           }

    static InitContainerF     getInitMethod(void) { return NULL;             }

    static UInt32             getFormat    (void) { return GL_UNSIGNED_BYTE; }
    static UInt32             getFormatSize(void) { return sizeof(GLubyte);  }
    static UInt32             getDimension (void) { return 1;                }
    static UInt32             getStride    (void) { return 0;                }

    static FieldDescription **getDesc      (void) { return _desc;            }
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Typedefs                                  */
    /*! \{                                                                 */
    typedef GeoPLengths                Inherited;
    typedef GeoPLengths::PtrType       InheritedPtr;

    typedef GeoPLengthsPropertyDesc    InheritedDesc;

    typedef MFUInt8                   StoredFieldType;

    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPLengthsPropertyDesc> Interface;
#endif    

    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPLengthsUI8PropertyDesc> GeoPLengthsUI8;
#endif

#if !defined(OSG_COMPILEGEOPROPPLENGTHINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPLengthsUI8PropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPLENGTHS_H_ */
