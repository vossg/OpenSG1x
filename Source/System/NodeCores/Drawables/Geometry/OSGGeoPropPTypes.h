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


#ifndef _OSGGEOPROPPTYPES_H_
#define _OSGGEOPROPPTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief The descriptor trait for osg::GeoPTypesUI8.
    \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
*/
struct GeoPTypesUI8PropertyDesc : public GeoPTypesPropertyDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    /*! \name                          Get                                 */
    /*! \{                                                                 */
        
    static const Char8 *getTypeName (void) { return "GeoPTypesUI8";         }
    static const Char8 *getClassName(void) { return "GeoPTypesUI8Property"; }
    static const Char8 *getFieldName(void) { return "types";                }
    static const Char8 *getGroupName(void) { return "GeoPTypes";            }

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
    
    typedef GeoPTypes                  Inherited;
    typedef GeoPTypes::PtrType         InheritedPtr;

    typedef GeoPTypesPropertyDesc      InheritedDesc;

    typedef MFUInt8                    StoredFieldType;
    typedef InheritedDesc::GenericType GenericType;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef GeoPropertyInterface<GeoPTypesPropertyDesc> Interface;
#endif
    /*! \}                                                                 */
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef GeoProperty<GeoPTypesUI8PropertyDesc> GeoPTypesUI8;
#endif


#if !defined(OSG_COMPILEGEOPROPPTYPEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPTypesUI8PropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPTYPES_H_ */
