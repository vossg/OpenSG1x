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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEWIN32WINDOWINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGWIN32WindowDataFields.h"

#include "OSGMFieldTypeDef.inl"
#include "OSGSFieldTypeDef.inl"

OSG_USING_NAMESPACE

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGWINDOWWIN32DATAFIELDS_HEADER_CVSID;
}

OSG_BEGIN_NAMESPACE

// doxygen can't find these
#ifndef OSG_DO_DOC 

DataType FieldDataTraits<HWND>::_type("HWND",
                                      NULL);

DataType FieldDataTraits<HDC>::_type("HDC",
                                     NULL);

DataType FieldDataTraits<HGLRC>::_type("HGLRC",
                                       NULL);

DataType FieldDataTraits<PAINTSTRUCT>::_type("PAINTSTRUCT",
                                             NULL);

#endif

OSG_DLLEXPORT_SFIELD_DEF1(HWND,        OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(HDC,         OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(HGLRC,       OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(PAINTSTRUCT, OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(HWND,        OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(HDC,         OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(HGLRC,       OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);

#ifndef OSG_MICROSOFT_COMPILER_HACKS
OSG_DLLEXPORT_MFIELD_DEF1(PAINTSTRUCT, OSG_WINDOWWIN32LIB_DLLTMPLMAPPING);
#endif

OSG_END_NAMESPACE
