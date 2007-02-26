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


#ifndef _OSGQTWINDOWDATAFIELDS_H_
#define _OSGQTWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGConfig.h>

#include "OSGWindowQT4Def.h"

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include "OSGQ4GLWidget_qt.h"


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


/*! \ingroup GrpWindowQTFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

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

    static void      putToString  (const      OSGQGLWidgetP &,
                                         std::string        &outStr)
    {
        outStr.assign("OSGQGLWidgetP");
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<OSGQGLWidgetP> */
/*! \hideinhierarchy                              */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowQTFieldSingle */

typedef SField<OSGQGLWidgetP> SFOSGQGLWidgetP;

/*! \ingroup GrpWindowQTFieldMulti */

typedef MField<OSGQGLWidgetP> MFOSGQGLWidgetP;
#endif

// Instantiations

#ifndef OSG_COMPILEWINDOWQTINST
OSG_DLLEXPORT_DECL1(SField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DECL1(MField, OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGQTWINDOWDATAFIELDS_HEADER_CVSID "@(#)$Id: OSGQT4WindowDataFields.h,v 1.2 2007/02/26 13:37:38 yjung Exp $"

#endif /* _OSGQTWINDOWDATAFIELDS_H_ */
