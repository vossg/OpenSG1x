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


#ifndef _OSGCOREGLWINDOWDATAFIELDS_H_
#define _OSGCOREGLWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

// Forget everything if we're not doing a Mac OS X compile
#ifdef __APPLE__

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGWindowCoreGLDef.h>

#include <OpenGL/OpenGL.h>

/*! The field types for the local types needed by the CoreGLWindow class */

OSG_BEGIN_NAMESPACE

template <>
struct OSG_WINDOWCOREGLLIB_DLLMAPPING FieldDataTraits<CGLContextObj> :
    public FieldTraitsRecurseBase<CGLContextObj>
{
    static DataType             _type;

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00                };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFCGLContextObj"; }
    static char     *getMName(void) { return "MFCGLContextObj"; }

    static bool      getFromString(      CGLContextObj &context,
                                   const Char8         *)
    {
        context=NULL;
        return true;
    }

    static void      putToString  (const CGLContextObj &,
                                         std::string   &outStr)
    {
        outStr.assign("CGLContextObj");
    }
};

//! SFCGLContextObj
//! \ingroup GrpBaseFieldSingle

typedef SField<CGLContextObj> SFCGLContextObj;

//! MFCGLContextObj
//! \ingroup GrpBaseFieldMulti

typedef MField<CGLContextObj> MFCGLContextObj;

// Instantiations

#ifndef OSG_COMPILEWINDOWCOREGLINST

OSG_DLLEXPORT_DECL1(SField, CGLContextObj, OSG_WINDOWCOREGLLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, CGLContextObj, OSG_WINDOWCOREGLLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

#define OSGWINDOWCOREGLDATAFIELDS_HEADER_CVSID "@(#)$Id: OSGCoreGLWindowDataFields.h,v 1.1 2006/09/08 10:09:06 pdaehne Exp $"

#endif /* __APPLE__ */

#endif /* _OSGCOREGLWINDOWDATAFIELDS_H_ */
