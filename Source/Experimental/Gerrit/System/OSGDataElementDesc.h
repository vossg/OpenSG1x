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

#ifndef _OSGDATAELEMENTDESC_HPP_
#define _OSGDATAELEMENTDESC_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGSupportTypes.h>
#include <OSGIDString.h>
#include <OSGReflexiveContainer.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Field;
class DataType;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef AnonObjectP 
    (ReflexiveContainer::*DataElemGetMethod       )(void      ); 

typedef AnonObjectP 
    (ReflexiveContainer::*DataElemIndexedGetMethod)(UInt32 );

typedef void 
    (ReflexiveContainer::*DataElemSetMethod       )(UInt32, Field *);

typedef void 
    (ReflexiveContainer::*DataElemSpezSetMethod   )(Field *);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! DataElementDesc
//! \ingroup DataStoreLib

class OSG_SYSTEMLIB_DLLMAPPING DataElementDesc
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

//    friend class DataStore;
//    friend class DataStorePtr;
    friend class ReflexiveContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
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

    //! prohibit default function (move to 'public' if needed) 
    void operator =(const DataElementDesc &source);

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

    IDString                 _szName;

    const DataType          &_elementType;

    UInt32                   _uiElementId;
    BitVector                _vElementMask;

    bool                     _bInternal;

    DataElemGetMethod        _fGetMethod;
    DataElemIndexedGetMethod _fIndexedGetMethod;

    DataElemSetMethod        _fSetMethod;
    DataElemSpezSetMethod    _fSpezSetMethod;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    AnonObjectP getElement(ReflexiveContainer &rContainer) const;

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    DataElementDesc(const DataType              &elementType,
                    const Char8                 *szName,
                    const UInt32                 uiElementId,
                    const BitVector              vElementMask,
                    const bool                   bInternal,
                          DataElemGetMethod      fGetMethod,
                          DataElemSetMethod      fSetMethod,
                          DataElemSpezSetMethod  fSpezSetMethod);

    DataElementDesc(const DataType                 &elementType,
                    const Char8                    *szName,
                    const UInt32                    uiElementId,
                    const BitVector                 vElementMask,
                    const bool                      bInternal,
                          DataElemIndexedGetMethod  fIndexedGetMethod,
                          DataElemSetMethod         fSetMethod,
                          DataElemSpezSetMethod     fSpezSetMethod);

    DataElementDesc(const DataElementDesc &source);

    virtual ~DataElementDesc(void); 

    /*------------------------- your_category -------------------------------*/

	const Char8     *getCName      (void) const;
    const IDString  &getName       (void) const;

          UInt32     getTypeId     (void) const;  

          BitVector  getElementMask(void                  ) const;
          void       setElementMask(BitVector vElementMask);

          UInt32     getElementId  (void              ) const;
          void       setElementId  (UInt32 uiElementId);

	      bool       isValid       (void) const;

    /*-------------------------            ----------------------------------*/

    void setGetMethod     (DataElemGetMethod         fGetMethod);
    void setIndexGetMethod(DataElemIndexedGetMethod  fIndexedGetMethod);

    /*------------------------- assignment ----------------------------------*/


    /*------------------------- comparison ----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

struct DataElementDescPLT
{
    bool operator()(const DataElementDesc *pElemDesc1, 
                    const DataElementDesc *pElemDesc2) const
    {
        return (pElemDesc1->getElementId() < pElemDesc2->getElementId());
    }
};

OSG_END_NAMESPACE

#define OSGDATAELEMENTDESC_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDATAELEMENTDESC_HPP_ */
