/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDDESCRIPTIONIMPL_INL_
#define _OSGFIELDDESCRIPTIONIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldDescriptionImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
const Char8 *FieldDescription::getCName(void) const
{
    return _szName.str();
}

inline
const IDString &FieldDescription::getName(void) const
{
    return _szName;
}

inline
UInt32 FieldDescription::getTypeId(void) const
{
    return _fieldType.getId();
}

inline
BitVector FieldDescription::getFieldMask(void) const
{
    return _vFieldMask;
}

inline
void FieldDescription::setFieldMask(BitVector vFieldMask)
{
    _vFieldMask = vFieldMask;
}

inline
UInt32 FieldDescription::getFieldId(void) const
{
    return _uiFieldId;
}

inline
void FieldDescription::setFieldId(UInt32 uiFieldId)
{
    _uiFieldId = uiFieldId;
}

inline
const Char8 *FieldDescription::getDefaultValue(void) const
{
    return _defaultValue.str();
}

inline
const TypeBase &FieldDescription::getFieldType(void) const
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/*                                Is                                       */

inline
bool FieldDescription::isInternal(void)  const
{
    return _bInternal;
}

inline
bool FieldDescription::isValid(void)  const
{
    return (this != NULL && _szName.getLength()) ? true : false;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

inline
void FieldDescription::setAccessMethod(FieldAccessMethod fAccessMethod)
{
    _fAccessMethod = fAccessMethod;
}

inline
void FieldDescription::setIndexAccessMethod(
    FieldIndexAccessMethod  fIndexedAccessMethod)
{
    _fIndexedAccessMethod = fIndexedAccessMethod;
}

/*-------------------------------------------------------------------------*/
/*                            Generic Field Access                         */

inline
Field * FieldDescription::getField(FieldContainer &dataStore) const
{
    Field *pField = NULL;

    if(_fAccessMethod != 0)
    {
        pField = ( (&dataStore)->*_fAccessMethod) ();
    }
    else if(_fIndexedAccessMethod != 0)
    {
        pField = ( (&dataStore)->*_fIndexedAccessMethod)(_uiFieldId);
    }
    else
    {
        SWARNING << "No accessMethod for " << _szName.str() << std::endl;
    }

    return pField;
}


inline
bool FieldDescriptionPLT::operator()(const FieldDescription *pElemDesc1, 
                                     const FieldDescription *pElemDesc2) const
{
    return (pElemDesc1->getFieldId() < pElemDesc2->getFieldId());
}


OSG_END_NAMESPACE

#define OSGFIELDDESCRIPTION_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDDESCRIPTIONIMPL_INL_ */
