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

// Position 3f

struct GeoPosition3fPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoPosition3f";         }
	static const Char8 *getClassName(void) { return "GeoPosition3fProperty"; }
	static const Char8 *getFieldName(void) { return "positions";             }
	static const Char8 *getGroupName(void) { return "GeoPosition";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)  { return GL_FLOAT;        }
	static UInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static UInt32 getDimension (void)  { return 3;               }
	static UInt32 getStride    (void)  { return 0;               }

	typedef GeoPosition              Inherit;
	typedef GeoPosition::PtrType     InheritPtr;
    typedef GeoPositionPropertyDesc  InheritDesc;
	typedef MFPnt3f                  FieldType;

    typedef InheritDesc::GenericType GenericType;
 
    typedef GeoPropertyInterface<GeoPositionPropertyDesc> Interface;
};

typedef GeoProperty<GeoPosition3fPropertyDesc> GeoPosition3f;

#ifndef OSG_COMPILEGEOPROPPOSITIONINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoPosition3fPropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoPosition3fPropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoPosition3fPropertyDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPOSITIONS_H_ */









