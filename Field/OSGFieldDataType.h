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


#ifndef _OSG_FIELDDATATYPE_H_
#define _OSG_FIELDDATATYPE_H_

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>

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

struct OSG_SYSTEMLIB_DLLMAPPING Traits
{
    enum 
    {
        ToStringConvertable   = 0x01,
        FromStringConvertable = 0x02
    };

    enum                        
    { 
        bHasParent        = 0x00      
    };
};

template<class FieldTypeT>
struct FieldDataTraits;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template<class FieldTypeT>
struct FieldTraitsRecurseBase : public Traits
{
    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase<FieldTypeT>\n");
    }
};

template<class FieldTypeT>
struct FieldTraitsRecurseBase1 : public Traits
{
    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase1<FieldTypeT>\n");
    }
};

template<class FieldTypeT>
struct FieldTraitsRecurseBase2 : public Traits
{
    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase2<FieldTypeT>\n");
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper : public FieldTraitsRecurseBase<FieldTypeT>
{
    static void putToBin(void)
    {
        typedef typename osgIF<FieldDataTraits<FieldTypeT>::bHasParent == 1,
                               FieldDataTraits<FieldTypeT::Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        MappedTrait::putToBin();
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper1 : public FieldTraitsRecurseBase1<FieldTypeT>
{
    static void putToBin(void)
    {
        typedef typename osgIF<FieldDataTraits<FieldTypeT>::bHasParent == 1,
                               FieldDataTraits<FieldTypeT::Inherited>, 
                               FieldTraitsRecurseBase1<FieldTypeT>  >::_IRet 
            MappedTrait;

        MappedTrait::putToBin();
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper2 : public FieldTraitsRecurseBase2<FieldTypeT>
{
    static void putToBin(void)
    {
        typedef typename osgIF<FieldDataTraits<FieldTypeT>::bHasParent == 1,
                               FieldDataTraits<FieldTypeT::Inherited>, 
                               FieldTraitsRecurseBase2<FieldTypeT>  >::_IRet 
            MappedTrait;

        MappedTrait::putToBin();
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct FieldDataTraits : public FieldTraitsRecurseMapper<FieldTypeT>
{
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct FieldDataTraits1 : public FieldTraitsRecurseMapper1<FieldTypeT>
{
};

template <class FieldTypeT>
struct FieldDataTraits2 : public FieldTraitsRecurseMapper2<FieldTypeT>
{
};

OSG_END_NAMESPACE

#endif /* _OSG_FIELDDATATYPE_H_ */


