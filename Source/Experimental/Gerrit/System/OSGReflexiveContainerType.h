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

#ifndef _OSGREFLEXIVECONTAINERTYPE_HPP_
#define _OSGREFLEXIVECONTAINERTYPE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGIDStringLink.h>
#include <OSGIDString.h>
//#include <OSGDataStorePtr.h>
#include <OSGDataType.h>

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DataElementDesc;
class ReflexiveContainerType;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void (*InitalInsertDescFunc)(ReflexiveContainerType *);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ReflexiveContainerType
//! \ingroup DataStoreLib

class OSG_SYSTEMLIB_DLLMAPPING ReflexiveContainerType : public DataType
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

    typedef DataType Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class VSCDataStoreFactory;

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
    ReflexiveContainerType(const ReflexiveContainerType &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const ReflexiveContainerType &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef std::map   <IDStringLink, DataElementDesc *> DescMap;
    typedef std::vector<              DataElementDesc *> DescVec;

    typedef DescMap::iterator                            DescMapIt;
    typedef DescVec::iterator                            DescVecIt;

    typedef DescMap::const_iterator                      DescMapConstIt;
    typedef DescVec::const_iterator                      DescVecConstIt;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt16                    _uiGroupId;

    bool                      _bReflexTypeInitialized;
    bool                      _bDescsAddable;

    ReflexiveContainerType   *_pReflexParent;
    IDString                  _szParentName;
    IDString                  _szGroupName;

    DescVec                   _vDesc;

	DescMap                   _mDescMap;
    DescVec                   _vDescVec;

    InitalInsertDescFunc      _descInsertFunc;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    bool initBaseType      (void);
    bool initFields        (void);
    bool initParentFields  (void);

	virtual bool initialize(void);
    virtual void terminate (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
    
    ReflexiveContainerType(const Char8                *szName,
                           const Char8                *szParentName   = NULL,
                           const Char8                *szGroupName    = NULL,
                           const UInt32                uiNameSpace    =    0,
                                 InitalInsertDescFunc  descInsertFunc = NULL,
                                 bool                  bDescsAddable  = false);
    
    virtual ~ReflexiveContainerType(void); 

    /*----------------------------- id --------------------------------------*/

    UInt16 getGroupId(void) const;

    /*-------------------------- parent -------------------------------------*/

    ReflexiveContainerType *getParent (void) const;

    /*------------------------- description ---------------------------------*/

          DataElementDesc *getElementDesc (      UInt32 uiElemId );
    const DataElementDesc *getElementDesc (      UInt32 uiElemId ) const;


          DataElementDesc *findElementDesc(const Char8 *szElement);
    const DataElementDesc *findElementDesc(const Char8 *szElement) const;

          UInt32           getNumElemDescs(      void               ) const;


    UInt32 addDescription(const DataElementDesc   &desc);
    bool   subDescription(      UInt32             uiFieldId);


    /*-------------------------- properties ---------------------------------*/

    virtual bool isInitialized(void) const;

    /*------------------------- your_operators ------------------------------*/

    void addInitialDesc(DataElementDesc *pDesc);

    /*------------------------- your_operators ------------------------------*/

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
};

OSG_END_NAMESPACE

#define OSGREFLEXIVECONTAINERTYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDATASTOREP_HPP_ */
