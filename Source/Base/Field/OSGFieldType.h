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

#ifndef _OSGFIELDTYPE_H_
#define _OSGFIELDTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <typeinfo>
#include "OSGBase.h"
#include "OSGBaseTypes.h"
#include "OSGFieldDataType.h"
#include "OSGDataType.h"

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldType.h
    \ingroup GrpBaseField
 */
#endif

class Field;

/*! \ingroup GrpBaseField
 */

class OSG_BASE_DLLMAPPING FieldType : public DataType
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Cardinality 
    { 
        SINGLE_FIELD, 
        MULTI_FIELD 
    };

    typedef Field *(*CreateFieldMethod)(void);

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldType(const Char8             *szName, 
              const Char8             *szParentName,
              const DataType          &contentType,
                    CreateFieldMethod  createMethod,
                    Cardinality        cardinality);

    FieldType(const Char8             *szName, 
              const Char8             *szParentName,
              const DataType          &contentType ,
                    CreateFieldMethod  createMethod,
                    Cardinality        cardinality ,
              const FieldType         &pScanAsType );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldType(void);

    /*! \}                                                                 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
    FieldType(const FieldType &source);
    FieldType &operator =(const FieldType &obj);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const DataType    &getContentType(void) const;
          Cardinality  getCardinality(void) const;

          UInt32       getScanTypeId (void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef DataType Inherited;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

          Cardinality        _cardinality;
          UInt32             _uiLoadTypeId;

    const DataType          &_contentType;
    const FieldType         *_pScanAsType;

    const CreateFieldMethod  _createMethod;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldFactory;

#if !defined(OSG_MICROSOFT_COMPILER_ALERT)
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType(const FieldType &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldType &operator =(const FieldType &obj);
#endif
};

OSG_END_NAMESPACE

#define OSGFIELDTYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDTYPE_H_ */



