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


#ifndef _OSGXWINDOWDATAFIELDS_H_
#define _OSGXWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

#include <GL/glx.h>

#include <OSGWindowXDef.h>

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>


/*! The field types for the local types needed by the XWindow class */

OSG_BEGIN_NAMESPACE


typedef Display *DisplayP;
typedef ::Window X11Window;


template <>
struct OSG_WINDOWXLIB_DLLMAPPING FieldDataTraits<DisplayP> : 
    public FieldTraitsRecurseBase<DisplayP>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFDisplayP"; }
    static char     *getMName(void) { return "MFDisplayP"; }

    static bool      getFromString(      DisplayP      &display,
                                   const Char8         *)
    {
        display=NULL;
        return true;
    }

    static void      putToString  (const DisplayP &,
                                         string   &outStr)
    {
        outStr.assign("DisplayP");
    }
};

template <>
struct OSG_WINDOWXLIB_DLLMAPPING FieldDataTraits<X11Window> : 
    public FieldTraitsRecurseBase<X11Window>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFX11Window"; }
    static char     *getMName(void) { return "MFX11Window"; }

    static bool      getFromString(      X11Window     &window,
                                   const Char8         *)
    {
        window=0;
        return true;
    }

    static void      putToString  (const X11Window &,
                                         string    &outStr)
    {
        outStr.assign("X11Window");
    }
};

template <>
struct OSG_WINDOWXLIB_DLLMAPPING FieldDataTraits<GLXContext> : 
    public FieldTraitsRecurseBase<GLXContext>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFGLXContext"; }
    static char     *getMName(void) { return "MFGLXContext"; }

    static bool      getFromString(      GLXContext    &context,
                                   const Char8         *)
    {
        context=NULL;
        return true;
    }

    static void      putToString  (const GLXContext &,
                                         string     &outStr)
    {
        outStr.assign("GLXContext");
    }
};

//! SFDisplayP
//! \ingroup SingleFields

typedef SField<DisplayP> SFDisplayP;

//! MFDisplayP
//! \ingroup MultiFields

typedef MField<DisplayP> MFDisplayP;

//! SFX11Window
//! \ingroup SingleFields

typedef SField<X11Window> SFX11Window;

//! MFX11Window
//! \ingroup MultiFields

typedef MField<X11Window> MFX11Window;

//! SFGLXContext
//! \ingroup SingleFields

typedef SField<GLXContext> SFGLXContext;

//! MFGLXContext
//! \ingroup MultiFields

typedef MField<GLXContext> MFGLXContext;

// Instantiations

#ifndef OSG_COMPILEWINDOWXINST
OSG_DLLEXPORT_DECL1(SField, DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(SField, X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(SField, GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGWINDOWXFIELDS_HEADER_CVSID "@(#)$Id: OSGXWindowDataFields.h,v 1.7 2002/08/29 16:24:58 dirk Exp $"

#endif /* _OSGXWINDOWDATAFIELDS_H_ */
