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

#include <OSGFieldDataType.h>
#include <OSGString.h>
#include <OSGFieldContainer.h>
#include <OSGFieldType.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Field;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef Field * (FieldContainer::* FieldAccessMethod)     (void); 
typedef Field * (FieldContainer::* FieldIndexAccessMethod)(UInt32);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldDescription
 */

class OSG_DLLEXPORT FieldDescription 
{
  public:
    
    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldDescription(const FieldType         &fieldType, 
                     const Char8             *name, 
                     const UInt32             fieldId,
                     const BitVector          fieldMask,
                     const Bool               internal,
                           FieldAccessMethod  accessMethod,
                     const Char8             *defaultValue = 0);
    
    FieldDescription(const FieldType              &fieldType, 
                     const Char8                  *name, 
                     const UInt32                  fieldId,
                     const BitVector               fieldMask,
                     const Bool                    internal,
                           FieldIndexAccessMethod  indexAccessMethod,
                     const Char8                  *defaultValue = 0);

    FieldDescription(const FieldDescription &obj);
    
    ~FieldDescription (void);
    
    /*------------------------- your_category -------------------------------*/

	const Char8 *getName        (void) const;
    const Char8 *getDefaultValue(void) const;

    UInt32    getTypeId   (void)  const;  

    BitVector getFieldMask(void                  )  const;
    void      setFieldMask(BitVector fieldMask);

    UInt32    getFieldId  (void                  )  const;
    void      setFieldId  (UInt32    fieldId  );

	Bool      isValid     (void)  const;

    /*-------------------------            ----------------------------------*/

    void setAccessMethod     (FieldAccessMethod      accessMethod     );
    void setIndexAccessMethod(FieldIndexAccessMethod indexAccessMethod);

    /*------------------------- comparison ----------------------------------*/

	void print(void) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
     
	Field *getField(FieldContainer &fieldContainer) const;

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

    const FieldType  &_fieldType;

    UInt32            _fieldId;
    UInt32            _fieldMask;
    
    Bool              _internal;

	String            _name;

	FieldAccessMethod      _accessMethod;
    FieldIndexAccessMethod _indexAccessMethod;

	String                 _defaultValue;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //----------------------------------------------------------------------- 

    FieldDescription &operator = (const FieldDescription &other);
};

struct FieldDescriptionPLT
{
    bool operator()(const FieldDescription* fieldDesc1, 
                    const FieldDescription* fieldDesc2) const
    {
        return (fieldDesc1->getFieldId() < fieldDesc2->getFieldId());
    }
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef FieldDescription* FieldDescriptionP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDDESCRIPTION_H_ */
