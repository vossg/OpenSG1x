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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                             FieldType                                   */

#ifdef WIN32

#ifdef OSG_MICROSOFT_COMPILER_HACKS
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType = FieldType(
    SFieldTraits::getSName(), 
    SFieldTraits::getPName(),
    SFieldTraits::getType (),
    SField<FieldTypeT, fieldNameSpace>::create,
    FieldType::SINGLE_FIELD);
#else
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType(
    SFieldTraits::getSName(), 
    SFieldTraits::getPName(),
    SFieldTraits::getType (),
    SField<FieldTypeT, fieldNameSpace>::create,
    FieldType::SINGLE_FIELD);
#endif

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getClassType(void)
{
    return _fieldType;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}
#endif

OSG_END_NAMESPACE

#define OSGSFIELDTYPEDEF_INLINE_CVSID "@(#)$Id: $"
