/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGFTGLFONTFIELDS_H_
#define _OSGFTGLFONTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGFieldContainerPtr.h>
#include <OSGNodeCoreFieldDataType.h>
#include <OSGContribDef.h>

#include <OSGFieldContainerFields.h>

OSG_BEGIN_NAMESPACE

class FTGLFont;

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
//! FTGLFontPtr

typedef FCPtr<FieldContainerPtr, FTGLFont> FTGLFontPtr;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpContribFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<FTGLFontPtr> : 
    public FieldTraitsRecurseMapper<FTGLFontPtr, true>
{
    static DataType             _type;                       

    enum                        { StringConvertable = 0x00 };
    enum                        { bHasParent        = 0x01 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFFTGLFontPtr"; }
    static char     *getMName(void) { return "MFFTGLFontPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<FTGLFontPtr, true>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpContribFieldSingle */

typedef SField<FTGLFontPtr> SFFTGLFontPtr;
#endif

#ifndef OSG_COMPILEFTGLFONTINST
OSG_DLLEXPORT_DECL1(SField, FTGLFontPtr, OSG_CONTRIBLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpContribFieldMulti */

typedef MField<FTGLFontPtr> MFFTGLFontPtr;
#endif

#ifndef OSG_COMPILEFTGLFONTINST
OSG_DLLEXPORT_DECL1(MField, FTGLFontPtr, OSG_CONTRIBLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGFTGLFONTFIELDS_HEADER_CVSID "@(#)$Id: OSGFTGLFontFields.h,v 1.1 2004/08/05 05:22:50 dirk Exp $"

#endif /* _OSGFTGLFONTFIELDS_H_ */