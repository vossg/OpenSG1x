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

#ifndef _OSG_NODEFIELDDATATYPE_H_
#define _OSG_NODEFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGFieldContainerFieldDataType.h>
#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

/*! \file OSGNodeFieldDataType.h
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
    \brief OpenSG Node Field Data Types  
*/

/*! \brief NodePtr field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits<NodePtr> : public FieldTraitsRecurseMapper<NodePtr>
{
    static DataType                  _type;

    enum                            { StringConvertable = 0x00 };
    enum                            { bHasParent        = 0x01 };

    static DataType &getType (void) { return _type;            }
    static char     *getSName(void) { return "SFNodePtr";      }
    static char     *getMName(void) { return "MFNodePtr";      }
};

OSG_END_NAMESPACE

#define OSGNODEFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_NODEFIELDDATATYPE_H_ */







