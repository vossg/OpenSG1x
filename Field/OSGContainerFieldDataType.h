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

#ifndef _OSG_CONTAINERFIELDDATATYPE_H_
#define _OSG_CONTAINERFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGNodePtr.h>
#include <map>
OSG_BEGIN_NAMESPACE


class NodeCore;
typedef FCPtr<FieldContainerPtr, NodeCore> NodeCorePtr;

class Attachment;
typedef FCPtr<FieldContainerPtr, Attachment> AttachmentPtr;

typedef map<UInt32, AttachmentPtr>  AttachmentMap;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief FieldContainerPtr field traits 
 */

template <>
struct FieldTraitsRecurseMapper<FieldContainerPtr> : 
    public FieldTraitsRecurseBase<FieldContainerPtr>
{
    enum                        { bHasParent        = 0x00      };

    static void putToBin (void) 
    { 
        fprintf(stderr, "FieldTraitsToBin<FieldContainerPtr>\n");
    }
};

template <>
struct FieldDataTraits<FieldContainerPtr> : 
    public FieldTraitsRecurseMapper<FieldContainerPtr>
{
    enum                        { StringConvertable = 0x00      };
 
    static char *getSName(void) { return "SFFieldContainerPtr"; }
    static char *getMName(void) { return "MFFieldContainerPtr"; }

/*
    static void putToBin (void) 
    { 
        fprintf(stderr, "FieldTraitsToBin<FieldContainerPtr>\n");
    }
*/
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief NodePtr field traits 
 */

template <>
struct FieldDataTraits<NodePtr> : public FieldTraitsRecurseMapper<NodePtr>
{
    enum                        { StringConvertable = 0x00      };
    enum                        { bHasParent        = 0x01      };

    static char *getSName(void) { return "SFNodePtr"; }
    static char *getMName(void) { return "MFNodePtr"; }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief NodeCorePtr field traits 
 */

template <>
struct FieldDataTraits<NodeCorePtr> : 
    public FieldTraitsRecurseMapper<NodeCorePtr>
{
    enum                        { StringConvertable = 0x00      };
    enum                        { bHasParent        = 0x01      };

    static char *getSName(void) { return "SFNodeCorePtr"; }
    static char *getMName(void) { return "MFNodeCorePtr"; }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief PropertyPtr field traits 
 */

template <>
struct FieldDataTraits<AttachmentMap> : 
    public FieldTraitsRecurseMapper<AttachmentMap>
{
    enum                        { StringConvertable = 0x00      };
    enum                        { bHasParent        = 0x01      };

    static char *getSName(void) { return "SFAttachmentMap"; }
    static char *getMName(void) { return "MFAttachmentMap"; }
};

OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */







