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

#define OSG_IMAGEGENERICATT
        
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGImageGenericAtt.h"
#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>
#include <OSGComponentTransform.h>
#include <OSGGeometry.h>
#include <OSGMaterialGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGExtrusionGeometry.h>
#include <OSGTextureChunk.h>
#include <OSGGeoFunctions.h>
#include <OSGDistanceLOD.h>
#include <OSGSwitch.h>
#include <OSGInline.h>

OSG_USING_NAMESPACE

#ifdef WIN32
OSG_FC_ST_TYPE_FUNCTIONS_INL_TMPL_DEF(ImageGenericAttDesc,
                                      DynFieldAttachment)
#endif                           

OSG_DYNFIELD_FC_DLLEXPORT_DEF(DynFieldAttachment, 
                              ImageGenericAttDesc, 
                              OSG_SYSTEMLIB_DLLTMPLMAPPING);

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

#include <OSGMFieldTypeDef.inl>
#include <OSGSFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<ImageGenericAttPtr>::_type("ImageGenericAttPtr",
                                                    "AttachmentPtr");

#if defined(OSG_SGI_EXPLICIT_INSTANTIATION)

#pragma instantiate DynFieldAttachment<ImageGenericAttDesc>::_type

#pragma instantiate SField<ImageGenericAttPtr>::_fieldType
#pragma instantiate MField<ImageGenericAttPtr>::_fieldType

#else

OSG_DLLEXPORT_SFIELD_DEF1(ImageGenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(ImageGenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING);

#endif
OSG_END_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGIMAGEGENERICATT_HEADER_CVSID;
}
