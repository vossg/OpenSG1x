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


#ifndef _OSGFIELDDESCRIPTION_H_
#define _OSGFIELDDESCRIPTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainerDef.h>
#include <OSGBaseTypes.h>

#include <OSGString.h>
#include <OSGFieldContainer.h>
#include <OSGTypeBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef Field * (FieldContainer::*FieldAccessMethod)(void); 
typedef Field * (FieldContainer::*FieldIndexAccessMethod)(UInt32);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldDescription
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldDescription
{
  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

	friend class FieldContainer;
    friend class FieldContainerPtr;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const FieldDescription &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    String                   _szName;

    const TypeBase          &_fieldType;

    UInt32                   _uiFieldId;
    BitVector                _vFieldMask;

    Bool                     _bInternal;

    FieldAccessMethod        _fAccessMethod;
    FieldIndexAccessMethod   _fIndexedAccessMethod;

	String                   _defaultValue;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Field *getField(FieldContainer &dataStore) const;

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

     FieldDescription(const TypeBase          &elementType,
                      const Char8             *szName,
                      const UInt32             uiFieldId,
                      const BitVector          vFieldMask,
                      const Bool               bInternal,
                            FieldAccessMethod  fAccessMethod,
                      const Char8             *defaultValue = NULL);

     FieldDescription(const TypeBase               &elementType,
                      const Char8                  *szName,
                      const UInt32                  uiFieldId,
                      const BitVector               vFieldMask,
                      const Bool                    bInternal,
                            FieldIndexAccessMethod  fIndexedAccessMethod,
                      const Char8                  *defaultValue = NULL);

    FieldDescription(const FieldDescription &source);

    virtual ~FieldDescription(void); 

    /*------------------------- your_category -------------------------------*/

	const Char8     *getCName    (void) const;
    const String    &getName     (void) const;

          UInt32     getTypeId   (void) const;  

          BitVector  getFieldMask(void                ) const;
          void       setFieldMask(BitVector vFieldMask);

          UInt32     getFieldId  (void            ) const;
          void       setFieldId  (UInt32 uiFieldId);

	      Bool       isInternal  (void) const;

	      Bool       isValid     (void) const;

    /*-------------------------            ----------------------------------*/

    void setAccessMethod     (FieldAccessMethod         fAccessMethod);
    void setIndexAccessMethod(FieldIndexAccessMethod  fIndexedAccessMethod);

    /*------------------------- assignment ----------------------------------*/

    const Char8 *getDefaultValue(void) const;

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

struct FieldDescriptionPLT
{
    bool operator()(const FieldDescription *pElemDesc1, 
                    const FieldDescription *pElemDesc2) const
    {
        return (pElemDesc1->getFieldId() < pElemDesc2->getFieldId());
    }
};

// class pointer

typedef FieldDescription *FieldDescriptionP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDDESCRIPTION_H_ */
