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

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>

#include "OSGQGLWidget_qt.h"


/*! The field types for the local types needed by the QTWindow class */

OSG_BEGIN_NAMESPACE


template <>
struct FieldDataTraits<OSGQGLWidgetP> : 
    public FieldTraitsRecurseBase<OSGQGLWidgetP>
{
    static DataType             _type;                       

    enum                        { StringConvertable = ToStringConvertable };
    enum                        { bHasParent        = 0x00 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFOSGQGLWidgetP"; }
    static char     *getMName(void) { return "MFOSGQGLWidgetP"; }

    static void      putToString  (const OSGQGLWidgetP &,
                                         string   &outVal)
    {
        outVal.assign("OSGQGLWidgetP");
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
#if defined(__sgi)

#pragma do_not_instantiate SField<OSGQGLWidgetP>::_fieldType
#pragma do_not_instantiate MField<OSGQGLWidgetP>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#define OSGQTWINDOWDATAFIELDS_HEADER_CVSID "@(#)$Id: OSGQTWindowDataFields.h,v 1.1 2002/02/05 20:39:34 dirk Exp $"

#endif /* _OSGQTWINDOWDATAFIELDS_H_ */
