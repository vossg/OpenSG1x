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


#ifndef _OSGFIELDCONTAINERTYPE_H_
#define _OSGFIELDCONTAINERTYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainerBase.h>
#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGFieldContainerPtr.h>
#include <OSGTypeBase.h>

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FieldDescription;

class NodePtr;

class NodeCore;
typedef FCPtr<FieldContainerPtr, NodeCore  > NodeCorePtr;

class Attachment;
typedef FCPtr<FieldContainerPtr, Attachment> AttachmentPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void            (*InitContainerF)  (void);
typedef FieldContainerPtr (*PrototypeCreateF)(void);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerType
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldContainerType : public TypeBase
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

    typedef TypeBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainerFactory;

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

    FieldContainerType(const FieldContainerType &source);
    void operator =(const FieldContainerType &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum BaseType
    {
        IsFieldContainer,
        IsNode,
        IsNodeCore,
        IsAttachment
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map   <StringLink, FieldDescription *> DescMap;
    typedef vector<            FieldDescription *> DescVec;

    typedef DescMap::iterator DescMapIt;
    typedef DescVec::iterator DescVecIt;

    typedef DescMap::const_iterator DescMapConstIt;
    typedef DescVec::const_iterator DescVecConstIt;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt16              _uiGroupId;

    Bool                _bInitialized;
    Bool                _bDescsAddable;

    BaseType            _baseType;

    FieldContainerType *_pParent;
    String              _szParentName;
    String              _szGroupName;

    FieldContainerPtr   _pPrototype;
    PrototypeCreateF    _fPrototypeCreate;

    FieldDescription   *_pDesc;
    UInt32              _uiDescByteCounter;

	DescMap             _mDescMap;
    DescVec             _vDescVec;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void registerType(const Char8 *szGroupName);

    Bool initPrototype   (void);
    Bool initBaseType    (void);
    Bool initFields      (void);
    Bool initParentFields(void);

	Bool initialize     (void);
    void    terminate   (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
    
    FieldContainerType(const Char8            *szName,
                       const Char8            *szParentName      = NULL,
                       const Char8            *szGroupName       = NULL,
                       PrototypeCreateF        fPrototypeCreate  = NULL,
                       InitContainerF          fInitMethod       = NULL,
                       FieldDescription       *pDesc             = NULL,
                       UInt32                  uiDescByteCounter = 0,
                       Bool                    bDescsAddable     = false);
    virtual ~FieldContainerType(void); 

    /*----------------------------- id --------------------------------------*/

    UInt16         getGroupId(void) const;

    /*-------------------------- parent -------------------------------------*/

    FieldContainerType *getParent (void) const;

    /*------------------------- description ---------------------------------*/

          FieldDescription *getFieldDescription(UInt32 uiFieldId);
    const FieldDescription *getFieldDescription(UInt32 uiFieldId) const;

          FieldDescription *findFieldDescription(
              const Char8 *szFieldName);

    const FieldDescription *findFieldDescription(
              const Char8 *szFieldName) const; 

    UInt32                 getNumFieldDescs(void) const;

    UInt32                 addDescription(const FieldDescription   &desc);
    Bool                   subDescription(      UInt32        uiFieldId);

    /*------------------------- prototye ------------------------------------*/

    FieldContainerPtr getPrototype(void) const;
    Bool              setPrototype(FieldContainerPtr pPrototype);

    /*-------------------------- properties ---------------------------------*/

    Bool isInitialized(void) const;

	Bool isAbstract   (void) const;

    Bool isDerivedFrom(const TypeBase      &other) const;
    Bool isDerivedFrom(const FieldContainerType &other) const;    

    /*----------------------------- create ----------------------------------*/

    FieldContainerPtr createFieldContainer(void) const;
    NodePtr           createNode          (void) const;
	NodeCorePtr       createNodeCore      (void) const;
	AttachmentPtr     createAttachment    (void) const;

    /*-------------------------- properties ---------------------------------*/

    Bool isNode          (void) const;
    Bool isNodeCore      (void) const;
    Bool isAttachment    (void) const;

    /*------------------------- your_operators ------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef FieldContainerType *FieldContainerTypeP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERP_H_ */
