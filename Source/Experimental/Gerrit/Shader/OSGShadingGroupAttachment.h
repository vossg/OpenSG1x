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

#ifndef _OSGSHADINGGROUPATTACHMENT_H_
#define _OSGSHADINGGROUPATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGAttachment.h>

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

    enum             { StringConvertable = 0x00                      };

    static DataType &getType      (void) { return _type;             }

    static Char8    *getSName     (void) { return "SFShadingGroupP"; }
    static Char8    *getMName     (void) { return "MFShadingGroupP"; }

    static void     *getDefault   (void) { return NULL;              }
};

typedef SField<ShadingGroup *> SFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPATTACHMENTFIELDINST
OSG_DLLEXPORT_DECL1(SField, ShadingGroup *, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

typedef MField<ShadingGroup *> MFShadingGroupP;

#ifndef OSG_COMPILESHADINGGROUPATTACHMENTFIELDINST
OSG_DLLEXPORT_DECL1(MField, ShadingGroup *, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


struct ShadingGroupPAttachmentDesc
{
    static  FieldDescription *_desc[];

    typedef MFShadingGroupP    FieldTypeT;


    static const Char8 *getTypeName  (void) 
    {
        return "ShadingGroupPAttachment";          
    }

    static const Char8 *getFieldName (void) 
    {
        return "data";          
    }

    static const Char8 *getGroupName (void) 
    { 
        return "shadinggroupp";          
    }

    static const Char8 *getParentTypeName(void) 
    {
        return "Attachment";    
    }


    static InitContainerF     getInitMethod(void) { return NULL;  }

    static FieldDescription **getDesc      (void) { return _desc; }
};

typedef SimpleAttachment<
    ShadingGroupPAttachmentDesc> ShadingGroupPAttachment;

typedef FCPtr           <
    AttachmentPtr,  
    ShadingGroupPAttachment    > ShadingGroupPAttachmentPtr;

OSG_END_NAMESPACE

#define OSGSHADINGGROUPATTACHMENT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSHADINGGROUPATTACHMENT_H_ */
