/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef _OSGGEOPROPINDICES_H_
#define _OSGGEOPROPINDICES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// Index uint32

struct GeoIndexUI32PropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoIndexUI32";         }
	static const Char8 *getClassName(void) { return "GeoIndexUI32Property"; }
	static const Char8 *getFieldName(void) { return "Indices";              }
	static const Char8 *getGroupName(void) { return "GeoIndex";             }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void) { return GL_UNSIGNED_INT; }
	static UInt32 getFormatSize(void) { return sizeof(GLuint);  }
	static UInt32 getDimension (void) { return 1;               }
	static UInt32 getStride    (void) { return 0;               }

	typedef GeoIndex                 Inherit;
	typedef GeoIndex::PtrType        InheritPtr;
    typedef GeoIndexPropertyDesc     InheritDesc;
	typedef MFUInt32                 FieldType;

	typedef InheritDesc::GenericType GenericType;
};

typedef GeoProperty<GeoIndexUI32PropertyDesc> GeoIndexUI32;


#ifndef OSG_COMPILEGEOPROPINDEXINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoIndexUI32PropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoIndexUI32PropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoIndexUI32PropertyDesc, 
                      OSG_GEOMETRY_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPINDICES_H_ */
