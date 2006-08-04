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


#ifndef _OSGCARBONWINDOWDATAFIELDS_H_
#define _OSGCARBONWINDOWDATAFIELDS_H_
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
#include <OSGWindowCarbonDef.h>

#include <AGL/agl.h>

/*! The field types for the local types needed by the CarbonWindow class */

OSG_BEGIN_NAMESPACE

template <>
struct OSG_WINDOWCARBONLIB_DLLMAPPING FieldDataTraits<AGLContext> :
    public FieldTraitsRecurseBase<AGLContext>
{
    static DataType             _type;

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00                };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFAGLContext"; }
    static char     *getMName(void) { return "MFAGLContext"; }

    static bool      getFromString(      AGLContext    &context,
                                   const Char8         *)
    {
        context=NULL;
        return true;
    }

    static void      putToString  (const AGLContext  &,
                                         std::string &outStr)
    {
        outStr.assign("AGLContext");
    }
};

//! SFAGLContext
//! \ingroup GrpBaseFieldSingle

typedef SField<AGLContext> SFAGLContext;

//! MFAGLContext
//! \ingroup GrpBaseFieldMulti

typedef MField<AGLContext> MFAGLContext;

// Instantiations

#ifndef OSG_COMPILEWINDOWCARBONINST

OSG_DLLEXPORT_DECL1(SField, AGLContext, OSG_WINDOWCARBONLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, AGLContext, OSG_WINDOWCARBONLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

#define OSGWINDOWCARBONDATAFIELDS_HEADER_CVSID "@(#)$Id: OSGCarbonWindowDataFields.h,v 1.1 2006/08/04 09:18:19 pdaehne Exp $"

#endif /* __APPLE__ */

#endif /* _OSGCARBONWINDOWDATAFIELDS_H_ */
