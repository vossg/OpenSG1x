/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGVRMLNODEATTACHMENTMAP_HPP_
#define _OSGVRMLNODEATTACHMENTMAP_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGVRMLBase.h>
#include <OSGBaseTypes.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include <OSGVRMLNodeAttachment.h>

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef std::map<UInt32, VRMLNodeAttachment *> VRMLNodeAttachmentMap;

template <>
struct OSG_VRML_DLLMAPPING FieldDataTraits<VRMLNodeAttachmentMap>// : 
//    public TypeTraits
{
    typedef VRMLNodeAttachmentMap &ArgumentType;

    enum
    {
        StringConvertable = 0x00
    };

    static       DataType            _type;

    static const Char8              *getSName(void) 
    {
        return "SFVRMLNodeAttachmentMap"; 
    }

    static const Char8              *getMName(void) 
    { 
        return "MFVRMLNodeAttachmentMap"; 
    }

    static const Char8 *getPName(void) 
    { 
        return "Field"; 
    }

    static const DataType           &getType(void)   { return _type; }
};

typedef SField<VRMLNodeAttachmentMap> SFVRMLNodeAttachmentMap;
typedef MField<VRMLNodeAttachmentMap> MFVRMLNodeAttachmentMap;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEVRMLNODEATTMAPINST
OSG_DLLEXPORT_DECL1(SField, 
                    VRMLNodeAttachmentMap, 
                    OSG_VRML_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, 
                    VRMLNodeAttachmentMap, 
                    OSG_VRML_DLLTMPLMAPPING)
#endif

#endif

OSG_END_NAMESPACE

#define OSGVRMLNODEATTACHMENTMAP_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODEATTACHMENTMAP_HPP_ */




