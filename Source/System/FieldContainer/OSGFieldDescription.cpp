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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldDescription.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGFieldDescription.h"

OSG_USING_NAMESPACE

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

