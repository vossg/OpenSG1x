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

#include <map>
#include <vector>

#include "OSGStringLink.h"
#include "OSGBaseTypes.h"
#include <OSGFieldContainerBase.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FieldContainer;
class FieldDescription;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void              (*InitContainerF)  (void);

typedef FieldContainerPtr (*PrototypeCreateF)(void);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainer type
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldContainerType 
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

    static const char *getClassname(void) { return "FieldContainerType"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	FieldContainerType(const Char8      *name,  
                       const Char8      *parentName       = NULL,
                       const Char8      *group            = NULL,
                       PrototypeCreateF  prototypeCreateF = NULL,
                       InitContainerF    initMethod       = NULL,
                       FieldDescription *desc             = NULL,
                       UInt32            descByteCounter  = 0,
                       Bool              descsAddable     = false);
    FieldContainerType(const FieldContainerType &obj);

    virtual ~FieldContainerType (void);

    /*----------------------------- id --------------------------------------*/

    UInt32 getId      (void) const;
    UInt16 getGroupId (void) const;

    /*------------------------ general info ---------------------------------*/

    FieldContainerType *getParent(void) const;

    const Char8        *getName  (void) const;

    /*------------------------- prototye ------------------------------------*/

    FieldContainerPtr getPrototype(void) const;
    Bool              setPrototype(FieldContainerPtr prototype);

    /*----------------------------- create ----------------------------------*/

    FieldContainerPtr createFieldContainer(void) const;
    NodePtr           createNode          (void) const;
	NodeCorePtr       createNodeCore      (void) const;
	AttachmentPtr     createAttachment    (void) const;

    /*-------------------------- properties ---------------------------------*/

	Bool isAbstract      (void) const;

    Bool isNode          (void) const;
    Bool isNodeCore      (void) const;
    Bool isAttachment    (void) const;

    Bool isDerivedFrom(const FieldContainerType &other) const;
        
    /*------------------------- description ---------------------------------*/

	const FieldDescription *findFieldDescription(
        const Char8 *fieldName) const;

          FieldDescription *getFieldDescription (
              UInt32 index) ;
    const FieldDescription *getFieldDescription (
              UInt32 index) const;

    UInt32            getNumFieldDescriptions(void) const;

    UInt32            addDescription(const FieldDescription &desc);
    Bool              subDescription(      UInt32            fieldId);

    /*----------------------------- dump ------------------------------------*/

	void print(void) const;

    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    Bool operator ==(const FieldContainerType &other);
    Bool operator !=(const FieldContainerType &other);

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
    
    typedef map   <StringLink,       FieldDescription *> DescMap;
    typedef vector<FieldDescription *>                   DescVec;

    typedef DescMap::iterator DescMapIt;
    typedef DescVec::iterator DescVecIt;

    typedef DescMap::const_iterator DescMapConstIt;
    typedef DescVec::const_iterator DescVecConstIt;

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

	const String        _name;
          String        _parentName;

    Bool                _initialized;
    Bool                _descsAddable;

	UInt32              _Id;
	UInt16              _groupId;

    FieldContainerPtr   _prototypeP;

    PrototypeCreateF    _prototypeCreateF;

	FieldContainerType *_parentP;

    BaseType            _baseType;

	DescMap             _descriptionMap;
    DescVec             _descriptionVec;

    FieldDescription   *_descA;
    UInt32              _byteSizeOfDescA;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void registerType(const Char8 *group);

    void initPrototype   (void);
    void initBaseType    (void);
    void initFields      (void);
    void initParentFields(void);

	void initialize  (void);
    void terminate   (void);

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const FieldContainerType &source);
};

typedef FieldContainerType* FieldContainerTypeP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERTYPE_H_ */
