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


#ifndef _OSGWIN32WINDOWDATAFIELDS_H_
#define _OSGWIN32WINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

// Forget everything if we're not doing a windows compile
#ifdef WIN32

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>

#include <windows.h>

/*! The field types for the local types needed by the WIN32WINdow class */

OSG_BEGIN_NAMESPACE

template <>
struct FieldDataTraits<HWND> : public FieldTraitsRecurseBase<HWND>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFHWND"; }
    static char     *getMName(void) { return "MFHWND"; }

    static void      putToString  (const HWND &,
                                         string   &outVal)
    {
        outVal.assign("HWND");
    }
};

template <>
struct FieldDataTraits<HDC> : public FieldTraitsRecurseBase<HDC>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFHDC"; }
    static char     *getMName(void) { return "MFHDC"; }

    static void      putToString  (const HDC &,
                                         string    &outVal)
    {
        outVal.assign("HDC");
    }
};

template <>
struct FieldDataTraits<HGLRC> : public FieldTraitsRecurseBase<HGLRC>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFHGLRC"; }
    static char     *getMName(void) { return "MFHGLRC"; }

    static void      putToString  (const HGLRC &,
                                         string     &outVal)
    {
        outVal.assign("HGLRC");
    }
};

template <>
struct FieldDataTraits<PAINTSTRUCT> : public FieldTraitsRecurseBase<PAINTSTRUCT>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFPAINTSTRUCT"; }
    static char     *getMName(void) { return "MFPAINTSTRUCT"; }

    static void      putToString  (const PAINTSTRUCT &,
                                         string     &outVal)
    {
        outVal.assign("PAINTSTRUCT");
    }
};

//! SFHWND
//! \ingroup SingleFields

typedef SField<HWND> SFHWND;

//! MFHWND
//! \ingroup MultiFields

typedef MField<HWND> MFHWND;

//! SFHDC
//! \ingroup SingleFields

typedef SField<HDC> SFHDC;

//! MFHDC
//! \ingroup MultiFields

typedef MField<HDC> MFHDC;

//! SFHGLRC
//! \ingroup SingleFields

typedef SField<HGLRC> SFHGLRC;

//! MFHGLRC
//! \ingroup MultiFields

typedef MField<HGLRC> MFHGLRC;

//! SFPAINTSTRUCT
//! \ingroup SingleFields

typedef SField<PAINTSTRUCT> SFPAINTSTRUCT;

//! MFPAINTSTRUCT
//! \ingroup MultiFields

typedef MField<PAINTSTRUCT> MFPAINTSTRUCT;

// Instantiations

#ifndef OSG_COMPILEWINDOWXINST
#if defined(__sgi)

#pragma do_not_instantiate SField<HWND>       ::_fieldType
#pragma do_not_instantiate SField<HDC>        ::_fieldType
#pragma do_not_instantiate SField<HGLRC>      ::_fieldType
#pragma do_not_instantiate SField<PAINTSTRUCT>::_fieldType

#pragma do_not_instantiate MField<HWND>       ::_fieldType
#pragma do_not_instantiate MField<HDC>        ::_fieldType
#pragma do_not_instantiate MField<HGLRC>      ::_fieldType
#pragma do_not_instantiate MField<PAINTSTRUCT>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, HWND,        OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(SField, HDC,         OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(SField, HGLRC,       OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(SField, PAINTSTRUCT, OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, HWND,        OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, HDC,         OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, HGLRC,       OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, PAINTSTRUCT, OSG_WINDOWWIN32LIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#define OSGWINDOWWIN32DATAFIELDS_HEADER_CVSID "@(#)$Id: OSGWIN32WindowDataFields.h,v 1.1 2002/02/05 20:39:35 dirk Exp $"

#endif /* WIN32 */

#endif /* _OSGWIN32WINDOWDATAFIELDS_H_ */
