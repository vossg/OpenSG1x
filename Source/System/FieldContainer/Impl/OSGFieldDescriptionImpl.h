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

#ifndef _OSGFIELDDESCRIPTIONIMPL_H_
#define _OSGFIELDDESCRIPTIONIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldDescriptionImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGIDString.h>
#include <OSGTypeBase.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

class Field;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef Field * (FieldContainer::*FieldAccessMethod     )(void  ); 

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef Field * (FieldContainer::*FieldIndexAccessMethod)(UInt32);

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING FieldDescription
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

     FieldDescription(const TypeBase               &elementType,
                      const Char8                  *szName,
                      const UInt32                  uiFieldId,
                      const BitVector               vFieldMask,
                      const bool                    bInternal,
                            FieldAccessMethod       fAccessMethod,
                      const Char8                  *defaultValue = NULL );

     FieldDescription(const TypeBase               &elementType,
                      const Char8                  *szName,
                      const UInt32                  uiFieldId,
                      const BitVector               vFieldMask,
                      const bool                    bInternal,
                            FieldIndexAccessMethod  fIndexedAccessMethod,
                      const Char8                  *defaultValue = NULL );

    FieldDescription(const FieldDescription &source                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldDescription(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const Char8     *getCName       (void                ) const;
    const IDString  &getName        (void                ) const;

          UInt32     getTypeId      (void                ) const;  

          BitVector  getFieldMask   (void                ) const;
          void       setFieldMask   (BitVector vFieldMask);

          UInt32     getFieldId     (void                ) const;
          void       setFieldId     (UInt32 uiFieldId    );

    const Char8     *getDefaultValue(void                ) const;

    const TypeBase  &getFieldType   (void                ) const;

          bool       isInternal     (void                ) const;

          bool       isValid        (void                ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAccessMethod     (FieldAccessMethod       fAccessMethod       );
    void setIndexAccessMethod(FieldIndexAccessMethod  fIndexedAccessMethod);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    IDString                 _szName;

    const TypeBase          &_fieldType;

    UInt32                   _uiFieldId;
    BitVector                _vFieldMask;

    bool                     _bInternal;

    FieldAccessMethod        _fAccessMethod;
    FieldIndexAccessMethod   _fIndexedAccessMethod;

    IDString                 _defaultValue;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                                                              */
    /*! \{                  Generic Field Access                           */

    Field *getField(FieldContainer &dataStore) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FieldContainerPtr;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldDescription &source);
};

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! FieldDescription point less than
    \ingroup GrpSystemFieldContainerFuncs
    \hideinhierarchy
 */

struct FieldDescriptionPLT
{
    bool operator()(const FieldDescription *pElemDesc1, 
                    const FieldDescription *pElemDesc2) const;
};

OSG_END_NAMESPACE

#define OSGFIELDDESCRIPTION_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDDESCRIPTIONIMPL_H_ */
