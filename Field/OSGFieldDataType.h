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


#ifndef _OSG_FIELDDATATYPE_H_
#define _OSG_FIELDDATATYPE_H_

#include <OSGBaseTypes.h>

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEFIELD
#       define OSG_FIELD_DLLMAPPING __declspec(dllexport)
#   else
#       define OSG_FIELD_DLLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_FIELD_DLLMAPPING
#endif

OSG_BEGIN_NAMESPACE

/** \file FieldDataType.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OpenSG Field Data Types  
*/

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Documentation dummy
 */

struct OSG_FIELD_DLLMAPPING Traits
{
    enum 
    {
        ToStringConvertable   = 0x01,
        FromStringConvertable = 0x02
    };
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct OSG_FIELD_DLLMAPPING FieldDataTraits : public Traits
{
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct OSG_FIELD_DLLMAPPING FieldDataTraits1 : public Traits
{
};

OSG_END_NAMESPACE

#endif /* _OSG_FIELDDATATYPE_H_ */
