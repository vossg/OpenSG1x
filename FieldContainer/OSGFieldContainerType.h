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

#ifndef _OSGFIELDCONTAINERTYPE_H_
#define _OSGFIELDCONTAINERTYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGIDStringLink.h>
#include <OSGDataType.h>
#include <OSGFieldContainerPtrForward.h>

#include <map>

OSG_BEGIN_NAMESPACE

class FieldDescription;

typedef void              (*InitContainerF)  (void);
typedef FieldContainerPtr (*PrototypeCreateF)(void);

//! FieldContainerType
//! \ingroup FieldContainerLib

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
                       Bool               bDescsAddable     = false);

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
    Bool                   subDescription  (      UInt32            uiFieldId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Prototype                                    */
    /*! \{                                                                 */

    FieldContainerPtr getPrototype(void                        ) const;
    Bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Query Properties                              */
    /*! \{                                                                 */

    Bool isInitialized(void                           ) const;

    Bool isAbstract   (void                           ) const;

    Bool isDerivedFrom(const TypeBase           &other) const;
    Bool isDerivedFrom(const FieldContainerType &other) const;    

    Bool isNode       (void                           ) const;
    Bool isNodeCore   (void                           ) const;
    Bool isAttachment (void                           ) const;

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

    typedef map   <IDStringLink, FieldDescription *> DescMap;
    typedef vector<              FieldDescription *> DescVec;

    typedef DescMap::iterator                        DescMapIt;
    typedef DescVec::iterator                        DescVecIt;

    typedef DescMap::const_iterator                  DescMapConstIt;
    typedef DescVec::const_iterator                  DescVecConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16              _uiGroupId;

    Bool                _bInitialized;
    Bool                _bDescsAddable;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType(const Char8 *szGroupName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    Bool initPrototype   (void);
    Bool initBaseType    (void);
    Bool initFields      (void);
    Bool initParentFields(void);

    Bool initialize      (void);
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
