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

#ifndef _OSGPROPGEOCOLORS_H_
#define _OSGPROPGEOCOLORS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeoPropertyBase.h>

OSG_BEGIN_NAMESPACE

/*! @name Color GeoProperty specializations
 */

//@{
	
//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// Color 3f

/*! \brief GeoColor3fPropertyDesc
 *  \ingroup GeoProperties
 */

struct GeoColor3fPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoColor3f";         }
	static const Char8 *getClassName(void) { return "GeoColor3fProperty"; }
	static const Char8 *getFieldName(void) { return "Colors";             }
	static const Char8 *getGroupName(void) { return "GeoColor";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)  { return GL_FLOAT;        }
	static UInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static UInt32 getDimension (void)  { return 3;               }
	static UInt32 getStride    (void)  { return 0;               }

	typedef GeoColor                 Inherit;
	typedef GeoColor::PtrType        InheritPtr;
    typedef GeoColorPropertyDesc     InheritDesc;
	typedef MFColor3f                FieldType;

    typedef InheritDesc::GenericType GenericType;
};

typedef GeoProperty<GeoColor3fPropertyDesc> GeoColor3f;

#ifndef OSG_COMPILEGEOPROPCOLORINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoColor3fPropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoColor3fPropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoColor3fPropertyDesc, 
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif



//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// Color 3ub

/*! \brief GeoColor3ubPropertyDesc
 *  \ingroup GeoProperties
 */

struct GeoColor3ubPropertyDesc
{
	static const Char8 *getTypeName (void) { return "GeoColor3ub";         }
	static const Char8 *getClassName(void) { return "GeoColor3ubProperty"; }
	static const Char8 *getFieldName(void) { return "Colors";             }
	static const Char8 *getGroupName(void) { return "GeoColor";           }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)  { return GL_FLOAT;        }
	static UInt32 getFormatSize(void)  { return sizeof(GLfloat); }
	static UInt32 getDimension (void)  { return 3;               }
	static UInt32 getStride    (void)  { return 0;               }

	typedef GeoColor                 Inherit;
	typedef GeoColor::PtrType        InheritPtr;
    typedef GeoColorPropertyDesc     InheritDesc;
	typedef MFColor3ub               FieldType;

	typedef InheritDesc::GenericType GenericType;
};

typedef GeoProperty<GeoColor3ubPropertyDesc> GeoColor3ub;

#ifndef OSG_COMPILEGEOPROPCOLORINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoColor3ubPropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoColor3ubPropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoColor3ubPropertyDesc, 
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


//---------------------------------------------------------------------------
//   Specialized Types
//---------------------------------------------------------------------------

// Color 4ub


/*! \brief GeoColor4ubPropertyDesc
 *  \ingroup GeoProperties
 */

struct GeoColor4ubPropertyDesc
{
	static const Char8 *getTypeName  (void) { return "GeoColor4ub";         }
	static const Char8 *getClassName (void) { return "GeoColor4ubProperty"; }
	static const Char8 *getFieldName (void) { return "Colors";              }
	static const Char8 *getGroupName (void) { return "GeoColor";            }

	static InitContainerF getInitMethod(void) { return NULL; }

	static UInt32 getFormat    (void)   { return GL_UNSIGNED_BYTE; }
	static UInt32 getFormatSize(void)   { return sizeof(GLubyte);  }
	static UInt32 getDimension (void)   { return 4;                }
	static UInt32 getStride    (void)   { return 0;                }

	typedef GeoColor                 Inherit;
	typedef GeoColor::PtrType        InheritPtr;
    typedef GeoColorPropertyDesc     InheritDesc;
	typedef MFColor4ub               FieldType;

    typedef InheritDesc::GenericType GenericType;
};

typedef GeoProperty<GeoColor4ubPropertyDesc> GeoColor4ub;

#ifndef OSG_COMPILEGEOPROPCOLORINST
#if defined(__sgi)

#pragma do_not_instantiate GeoProperty<GeoColor4ubPropertyDesc>::_type
#pragma do_not_instantiate GeoProperty<GeoColor4ubPropertyDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(GeoProperty, 
                      GeoColor4ubPropertyDesc, 
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

//@}

OSG_END_NAMESPACE

#include <OSGGeoPropColors.inl>

#endif /* _OSGGEOPROPCOLORS_H_ */
