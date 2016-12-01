/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000-2002 by the OpenSG Forum               *
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


#ifndef _OSGIMAGEGENERICATT_H_
#define _OSGIMAGEGENERICATT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include <vector>
#include <string>

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include "OSGFieldContainerPtr.h"
#include "OSGField.h"
#include "OSGFieldContainer.h"
#include "OSGAttachment.h"
#include "OSGSFSysTypes.h"
#include "OSGSFVecTypes.h"
#include "OSGSFFieldContainerPtr.h"
#include "OSGComponentTransform.h"
#include "OSGAttachmentFieldDataType.h"

OSG_BEGIN_NAMESPACE

/*! \hideinhierarchy */

struct ImageGenericAttDesc
{
    typedef Attachment    Parent;
    typedef AttachmentPtr ParentPtr;

    static const Char8 *getTypeName      (void) { return "ImageGenericAtt"; }
    static const Char8 *getParentTypeName(void) { return "Attachment"; }
    static const Char8 *getGroupName     (void) { return "ImageGenAtt"; }

    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return NULL; }
};

typedef DynFieldAttachment<ImageGenericAttDesc>  ImageGenericAtt;
typedef ImageGenericAtt::PtrType                 ImageGenericAttPtr;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_IMAGEGENERICATT
#if defined(OSG_WIN32_CL) && _MSC_VER > 1300
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment, 
                            ImageGenericAttDesc,
                            )
#else
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment, 
                            ImageGenericAttDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<ImageGenericAttPtr> : 
    public FieldTraitsRecurseMapper<ImageGenericAttPtr, true>
{
    static DataType                 _type;
    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x01  };

    static       DataType &getType (void) { return _type;             }
    static const Char8    *getSName(void) { return "SFImageGenericAttPtr"; }
    static const Char8    *getMName(void) { return "MFImageGenericAttPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseMapper<ImageGenericAttPtr, true> */
/*! \hideinhierarchy                                     */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldSingle */

typedef SField<ImageGenericAttPtr>       SFImageGenericAttPtr;
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_IMAGEGENERICATT
OSG_DLLEXPORT_DECL1(SField, ImageGenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldMulti */

typedef MField<ImageGenericAttPtr>       MFImageGenericAttPtr;
#endif

#ifndef OSG_IMAGEGENERICATT
OSG_DLLEXPORT_DECL1(MField, ImageGenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGIMAGEGENERICATT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGIMAGEGENERICATT_H_ */


