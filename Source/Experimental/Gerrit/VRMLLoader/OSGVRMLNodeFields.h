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

#ifndef _OSGVRMLNODEFIELDS_HPP_
#define _OSGVRMLNODEFIELDS_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLBase.h>
#include <OSGFieldType.h>
#include <OSGMField.h>
#include <OSGSField.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLNode;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef VRMLNode *VRMLNodeP;

template <>
struct OSG_VRML_DLLMAPPING FieldDataTraits<VRMLNode *>// : public TypeTraits
{
    typedef VRMLNode *ArgumentType;

    enum
    {
        StringConvertable = 0x00
    };

    static       DataType _type;

    static const Char8    *getSName(void) 
    {
        return "SFVRMLNode"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFVRMLNode"; 
    }

    static const Char8 *getPName(void) 
    { 
        return "Field"; 
    }

    // Needed for MS
    static UInt32 getBinSize(const VRMLNodeP &)
    {
        return 0;
    }

    static UInt32 getBinSize(const VRMLNodeP *,
                                   UInt32     )
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler &, 
                          const VRMLNodeP         &)
    {
    }

    static void copyToBin(      BinaryDataHandler &, 
                          const VRMLNodeP         *,
                                UInt32             )
    {
    }

    static void copyFromBin(BinaryDataHandler &, 
                            VRMLNodeP         &)
    {
    }

    static void copyFromBin(BinaryDataHandler &, 
                            VRMLNodeP         *,
                            UInt32             )
    {
    }

    static const DataType &getType(void)   { return _type; }
};

typedef SField<VRMLNode *> SFVRMLNode;
typedef MField<VRMLNode *> MFVRMLNode;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEVRMLNODEINST
OSG_DLLEXPORT_DECL1(SField, 
                    VRMLNode *, 
                    OSG_VRML_DLLTMPLMAPPING)

OSG_DLLEXPORT_DECL1(MField, 
                    VRMLNode *, 
                    OSG_VRML_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

#define OSGVRMLNODEFIELDS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODEFIELDS_HPP_ */
