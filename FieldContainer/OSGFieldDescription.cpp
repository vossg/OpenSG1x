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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGFieldDescription.h"

OSG_USING_NAMESPACE

/*! \class osg::FieldDescription
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldDescription::FieldDescription(const TypeBase          &elementType,
                                   const Char8             *szName,
                                   const UInt32             uiFieldId,
                                   const BitVector          vFieldMask,
                                   const bool               bInternal,
                                         FieldAccessMethod  fAccessMethod,
                                   const Char8             *defaultValue) :

    _szName              (szName       ),

    _fieldType           (elementType  ),
    _uiFieldId           (uiFieldId    ),
    _vFieldMask          (vFieldMask   ),

    _bInternal           (bInternal    ),

    _fAccessMethod       (fAccessMethod),
    _fIndexedAccessMethod(NULL         ),
    _defaultValue        (defaultValue )
{
}

FieldDescription::FieldDescription(
    const TypeBase               &elementType,
    const Char8                  *szName,
    const UInt32                  uiFieldId,
    const BitVector               vFieldMask,
    const bool                    bInternal,
          FieldIndexAccessMethod  fIndexedAccessMethod,
    const Char8                  *defaultValue) :

    _szName              (szName              ),

    _fieldType           (elementType         ),
    _uiFieldId           (uiFieldId           ),
    _vFieldMask          (vFieldMask          ),

    _bInternal           (bInternal           ),

    _fAccessMethod       (NULL                ),
    _fIndexedAccessMethod(fIndexedAccessMethod),

    _defaultValue        (defaultValue        )
{
}

FieldDescription::FieldDescription(const FieldDescription &source) :

    _szName              (source._szName              ),

    _fieldType           (source._fieldType           ),
    _uiFieldId           (source._uiFieldId           ),
    _vFieldMask          (source._vFieldMask          ),

    _bInternal           (source._bInternal           ),

    _fAccessMethod       (source._fAccessMethod       ),
    _fIndexedAccessMethod(source._fIndexedAccessMethod),

    _defaultValue        (source._defaultValue        )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldDescription::~FieldDescription(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

const Char8 *FieldDescription::getCName(void) const
{
    return _szName.str();
}

const IDString &FieldDescription::getName(void) const
{
    return _szName;
}

UInt32 FieldDescription::getTypeId(void) const
{
    return _fieldType.getId();
}

BitVector FieldDescription::getFieldMask(void) const
{
    return _vFieldMask;
}

void FieldDescription::setFieldMask(BitVector vFieldMask)
{
    _vFieldMask = vFieldMask;
}

UInt32 FieldDescription::getFieldId(void) const
{
    return _uiFieldId;
}

void FieldDescription::setFieldId(UInt32 uiFieldId)
{
    _uiFieldId = uiFieldId;
}

const Char8 *FieldDescription::getDefaultValue(void) const
{
    return _defaultValue.str();
}

const TypeBase &FieldDescription::getFieldType(void) const
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/*                                Is                                       */

bool FieldDescription::isInternal(void)  const
{
    return _bInternal;
}

bool FieldDescription::isValid(void)  const
{
    return (this != NULL && _szName.getLength()) ? true : false;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void FieldDescription::setAccessMethod(FieldAccessMethod fAccessMethod)
{
    _fAccessMethod = fAccessMethod;
}

void FieldDescription::setIndexAccessMethod(
    FieldIndexAccessMethod  fIndexedAccessMethod)
{
    _fIndexedAccessMethod = fIndexedAccessMethod;
}

/*-------------------------------------------------------------------------*/
/*                            Generic Field Access                         */

Field * FieldDescription::getField(FieldContainer &dataStore) const
{
    Field *pField = NULL;

    if(_fAccessMethod != NULL)
    {
        pField = ( (&dataStore)->*_fAccessMethod) ();
    }
    else if(_fIndexedAccessMethod != NULL)
    {
        pField = ( (&dataStore)->*_fIndexedAccessMethod)(_uiFieldId);
    }
    else
    {
        SWARNING << "No accessMethod for " << _szName.str() << endl;
    }

    return pField;
}


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
    static Char8 cvsid_hpp[] = OSGFIELDDESCRIPTION_HEADER_CVSID;
}

