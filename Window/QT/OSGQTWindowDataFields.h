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


#ifndef _OSGQTWINDOWDATAFIELDS_H_
#define _OSGQTWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

#include <OSGWindowQTDef.h>

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include "OSGQGLWidget_qt.h"


/*! The field types for the local types needed by the QTWindow class */

OSG_BEGIN_NAMESPACE


template <>
struct OSG_WINDOWQTLIB_DLLMAPPING FieldDataTraits<OSGQGLWidgetP> : 
    public FieldTraitsRecurseBase<OSGQGLWidgetP>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFOSGQGLWidgetP"; }
    static char     *getMName(void) { return "MFOSGQGLWidgetP"; }

    static bool      getFromString(      OSGQGLWidgetP &widget,
                                   const Char8         *)
    {
        widget=NULL;
        return true;
    }

    static void      putToString  (const OSGQGLWidgetP &,
                                         string        &outStr)
    {
        outStr.assign("OSGQGLWidgetP");
    }
};

//! SFOSGQGLWidgetP
//! \ingroup SingleFields

typedef SField<OSGQGLWidgetP> SFOSGQGLWidgetP;

//! MFOSGQGLWidgetP
//! \ingroup MultiFields

typedef MField<OSGQGLWidgetP> MFOSGQGLWidgetP;

// Instantiations

#ifndef OSG_COMPILEWINDOWQTINST
OSG_DLLEXPORT_DECL1(SField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGQTWINDOWDATAFIELDS_HEADER_CVSID "@(#)$Id: OSGQTWindowDataFields.h,v 1.6 2002/06/18 08:17:57 vossg Exp $"

#endif /* _OSGQTWINDOWDATAFIELDS_H_ */
