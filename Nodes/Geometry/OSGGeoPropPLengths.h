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

struct GeoPLengthsUI32PropertyDesc
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

typedef GeoProperty<GeoPLengthsUI32PropertyDesc> GeoPLengthsUI32;


#ifndef OSG_COMPILEGEOPROPPLENGTHINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPLengthsUI32PropertyDesc>::_type

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty,
                      GeoPLengthsUI32PropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPLENGTHS_H_ */
