/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGSHADINGGROUPFIELDS_H_
#define _OSGSHADINGGROUPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGShaderBase.h>
#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGSField.h>
#include <OSGMField.h>

OSG_BEGIN_NAMESPACE

class ShadingGroup;

template <>
struct FieldDataTraits<ShadingGroup *> : 
    public FieldTraitsRecurseBase<ShadingGroup *>
{
    static  DataType                        _type;
    typedef FieldDataTraits<ShadingGroup *>  Self;
    typedef ShadingGroup                 *   ArgumentType;
    typedef ShadingGroup                 *   FieldTypeT;

    enum                 { StringConvertable = 0x00                      };

    static DataType     &getType      (void) { return _type;             }

    static Char8        *getSName     (void) { return "SFShadingGroupP"; }
    static Char8        *getMName     (void) { return "MFShadingGroupP"; }

    static ShadingGroup *getDefault   (void) { return NULL;              }
};

typedef SField<ShadingGroup *> SFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPFIELDINST
OSG_DLLEXPORT_DECL1(SField, ShadingGroup *, OSG_SHADER_DLLMAPPING)
#endif

typedef MField<ShadingGroup *> MFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPFIELDINST
OSG_DLLEXPORT_DECL1(MField, ShadingGroup *, OSG_SHADER_DLLMAPPING)
#endif


template <>
struct FieldDataTraits<MFShadingGroupP> : 
    public FieldTraitsRecurseBase<MFShadingGroupP>
{
    static  DataType                         _type;
    typedef FieldDataTraits<MFShadingGroupP>  Self;
    typedef MFShadingGroupP                   ArgumentType;
    typedef MFShadingGroupP                   FieldTypeT;

    enum             { StringConvertable = 0x00                      };

    static DataType        &getType      (void) { return _type;             }

    static Char8           *getSName     (void) { return "SFMFShadingGroupP"; }
    static Char8           *getMName     (void) { return "MFMFShadingGroupP"; }

    static MFShadingGroupP  getDefault   (void) { return MFShadingGroupP();   }
};

typedef SField<MFShadingGroupP> SFMFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPFIELDINST
OSG_DLLEXPORT_DECL1(SField, MFShadingGroupP, OSG_SHADER_DLLMAPPING)
#endif

typedef MField<MFShadingGroupP> MFMFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPFIELDINST
OSG_DLLEXPORT_DECL1(MField, MFShadingGroupP, OSG_SHADER_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSHADINGGROUPFIELDS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSHADINGGROUPFIELDS_H_ */
