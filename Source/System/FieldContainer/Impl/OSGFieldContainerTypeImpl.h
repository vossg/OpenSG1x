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

#ifndef _OSGFIELDCONTAINERTYPEIMPL_H_
#define _OSGFIELDCONTAINERTYPEIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerTypeImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGIDStringLink.h>
#include <OSGDataType.h>

#include <map>

OSG_BEGIN_NAMESPACE

class FieldDescription;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef void              (*InitContainerF)  (void);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef FieldContainerPtr (*PrototypeCreateF)(void);

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerType : public DataType
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
   
    FieldContainerType(const Char8       *szName,
                       const Char8       *szParentName      = NULL,
                       const Char8       *szGroupName       = NULL,
                       PrototypeCreateF   fPrototypeCreate  = NULL,
                       InitContainerF     fInitMethod       = NULL,
                       FieldDescription **pDesc             = NULL,
                       UInt32             uiDescByteCounter = 0,
                       bool               bDescsAddable     = false);

    FieldContainerType(const FieldContainerType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldContainerType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Information                            */
    /*! \{                                                                 */

    UInt16              getGroupId(void) const;
    FieldContainerType *getParent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Description                                  */
    /*! \{                                                                 */

          FieldDescription *getFieldDescription (UInt32 uiFieldId);
    const FieldDescription *getFieldDescription (UInt32 uiFieldId) const;

          FieldDescription *findFieldDescription(const Char8 *szFieldName);

    const FieldDescription *findFieldDescription(
        const Char8 *szFieldName) const; 

    UInt32                 getNumFieldDescs(void) const;

    UInt32                 addDescription  (const FieldDescription &desc     );
    bool                   subDescription  (      UInt32            uiFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Prototype                                    */
    /*! \{                                                                 */

    FieldContainerPtr getPrototype(void                        ) const;
    bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Query Properties                              */
    /*! \{                                                                 */

    bool isInitialized(void                           ) const;

    bool isAbstract   (void                           ) const;

    bool isDerivedFrom(const TypeBase           &other) const;
    bool isDerivedFrom(const FieldContainerType &other) const;    

    bool isNode       (void                           ) const;
    bool isNodeCore   (void                           ) const;
    bool isAttachment (void                           ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base FieldContainer                      */
    /*! \{                                                                 */

    FieldContainerPtr createFieldContainer(void) const;
    NodePtr           createNode          (void) const;
    NodeCorePtr       createNodeCore      (void) const;
    AttachmentPtr     createAttachment    (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    enum BaseType
    {
        IsFieldContainer,
        IsNode,
        IsNodeCore,
        IsAttachment
    };

    typedef std::map   <IDStringLink, FieldDescription *> DescMap;
    typedef std::vector<              FieldDescription *> DescVec;

    typedef DescMap::iterator                             DescMapIt;
    typedef DescVec::iterator                             DescVecIt;

    typedef DescMap::const_iterator                       DescMapConstIt;
    typedef DescVec::const_iterator                       DescVecConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16              _uiGroupId;

    bool                _bInitialized;
    bool                _bDescsAddable;

    BaseType            _baseType;

    FieldContainerType *_pParent;
    IDString            _szParentName;
    IDString            _szGroupName;

    FieldContainerPtr   _pPrototype;
    PrototypeCreateF    _fPrototypeCreate;

    FieldDescription  **_pDesc;
    UInt32              _uiDescByteCounter;

    DescMap             _mDescMap;
    DescVec             _vDescVec;

    bool                _bCopy;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType(const Char8 *szGroupName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    bool initPrototype   (void);
    bool initBaseType    (void);
    bool initFields      (void);
    bool initParentFields(void);

    bool initialize      (void);
    void terminate       (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef DataType Inherited;

    friend class FieldContainerFactory;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerType &source);
};

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERTYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERTYPE_H_ */
