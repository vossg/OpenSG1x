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


#ifndef _OSGSFIELD_H_
#define _OSGSFIELD_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include <vector>
#include <string>

#include <OSGField.h>

OSG_BEGIN_NAMESPACE

/** \defgroup SingleFields SingleFields
 *  \brief OpenSG Single Fields
 */

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief Base class for all single fields, for example ::SFMatrix.
 */

template <class FieldTypeT, Int32 fieldNameSpace = 0>
class OSG_BASE_DLLMAPPING SField : public Field 
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

    typedef typename osgIF<fieldNameSpace == 1,
                           FieldDataTraits1<FieldTypeT>, 
                           FieldDataTraits2<FieldTypeT> >::_IRet SF1Trait;

    typedef typename osgIF<fieldNameSpace == 0, 
                           FieldDataTraits <FieldTypeT>, 
                           SF1Trait>::_IRet SFieldTraits;

    typedef          SField<FieldTypeT, fieldNameSpace> Self;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const Char8     *getClassname(void) { return "SField"; };
    static const FieldType &getClassType(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SField         (void);
    SField         (const SField  &obj);
    explicit SField(const FieldTypeT &value);

    virtual ~SField(void); 

    /*------------------------------ access ---------------------------------*/

          FieldTypeT &getValue(void);
	const FieldTypeT &getValue(void) const;

    void setAbstrValue(const Field &obj);

    void setValue(const FieldTypeT &value);
	void setValue(const Self       &obj  );

    /*----------------------- field information -----------------------------*/

	virtual FieldType::Cardinality getCardinality (void) const;

    virtual UInt32                 size           (void) const;

    /*-------------------------- field type ---------------------------------*/

	virtual const FieldType  &getType        (void) const;

    /*-------------------------- string io ----------------------------------*/

	virtual void    pushValueByStr(const Char8 *str);
    virtual std::string &getValueByStr (std::string &string) const;

    /*------------------------------- sync ----------------------------------*/

    void syncWith(Self &source);

    /*---------------------------- To / From Bin ----------------------------*/

    UInt32       getBinSize (void);
    
    MemoryHandle copyToBin  (MemoryHandle  pMem);
    MemoryHandle copyFromBin(MemoryHandle  pMem);

    /*----------------------------- assign ----------------------------------*/

    void operator =(const SField &source);

    /*------------------------------- dump ----------------------------------*/

    virtual void dump(void) const;

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

    static const FieldType _fieldType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    FieldTypeT _value;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Field Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

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

	static Field *create(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGSField.inl>

#endif /* _OSGSFIELD_H_ */

