/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#ifndef _OSGATTACHMENTIMPL_H_
#define _OSGATTACHMENTIMPL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSFBaseTypes.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSFSysTypes.h>

#include <map>
#include <iostream>

OSG_BEGIN_NAMESPACE

class BinaryDataHandler;
class FieldDescription;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Attachment is the base class for sharable thread safe data stores,
//! which could be attached to other fieldcontainers than Attachments.
//! \ingroup FieldContainerLib

class OSG_SYSTEMLIB_DLLMAPPING Attachment : public FieldContainer 
{
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef FieldContainer Inherited;
    
    /*==========================  PUBLIC  =================================*/
  public:

    enum 
    { 
        ParentsFieldId     = Inherited::NextFieldId, 
        InternalFieldId    = ParentsFieldId + 1,
        NextFieldId        = InternalFieldId + 1
    };

    static const BitVector InternalFieldMask;
    static const BitVector ParentsFieldMask;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_DECL(AttachmentPtr)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Parents                               */
    /*! \{                                                                 */

          MFFieldContainerPtr &getParents  (void);
    const MFFieldContainerPtr &getParents  (void) const;
    
          MFFieldContainerPtr *getMFParents(void);

    void                       addParent   (FieldContainerPtr parent);
    void                       subParent   (FieldContainerPtr parent);

    Int32                      findParent  (FieldContainerPtr parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Parents                               */
    /*! \{                                                                 */

          SFBool &getInternal  (void);
    const SFBool &getInternal  (void) const;
          SFBool *getSFInternal(void);

          void    setInternal  (bool bVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32  getBinSize (const BitVector         &whichField);

    virtual void    copyToBin  (      BinaryDataHandler &pMem, 
                                const BitVector         &whichField);
    virtual void    copyFromBin(      BinaryDataHandler &pMem, 
                                const BitVector         &whichField);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static FieldDescription   *_desc[];
    static FieldContainerType  _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFBool              _sfInternal;
    MFFieldContainerPtr _parents;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Attachment(void);
    Attachment(const Attachment &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Attachment(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Destruction                                */
    /*! \{                                                                 */

    virtual void onDestroy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      Attachment     *pOther,
                                 const BitVector      &whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;

    /*! \brief prohibit default functions (move to 'public' if needed) */
    void operator =(const Attachment &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Template to build simple attachment classes which store only one field.
//! \ingroup FieldContainerLib

template <class AttachmentDescT>
class SimpleAttachment : public Attachment
{
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef Attachment Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef typename AttachmentDescT::FieldTypeT          StoredFieldType;

    typedef          SimpleAttachment<AttachmentDescT>    Self;

    typedef          FCPtr<AttachmentPtr,  Self      >    PtrType;
    
    enum 
    { 
        SimpleFieldId     = Inherited::NextFieldId, 
        NextFieldId       = SimpleFieldId + 1
    };

    static const BitVector SimpleFieldMask = 
                                       1 << static_cast<UInt32>(SimpleFieldId);

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

          StoredFieldType *getFieldPtr(void);

          StoredFieldType &getField   (void);
    const StoredFieldType &getField   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (const BitVector         &whichField);

    virtual void   copyToBin  (      BinaryDataHandler &pMem, 
                               const BitVector         &whichField);
    virtual void   copyFromBin(      BinaryDataHandler &pMem, 
                               const BitVector         &whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

#if 1 //defined(OSG_MICROSOFT_COMPILER_ALERT)
    static FieldDescription   *_desc[];
#endif

    static FieldContainerType  _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    StoredFieldType _field;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleAttachment(void);
    SimpleAttachment(const SimpleAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    virtual void executeSync    (      FieldContainer   &other,
                                 const BitVector        &whichField);

            void executeSyncImpl(      SimpleAttachment *pOther,
                                 const BitVector        &whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;

    /*! \brief prohibit default functions (move to 'public' if needed) */
    SimpleAttachment &operator =(const SimpleAttachment &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Name attachment
//! \ingroup FieldContainerLib

struct NameAttachmentDesc
{
    static  FieldDescription *_desc[];

    typedef SFString           FieldTypeT;

    static const Char8         *getTypeName  (void) 
    {
        return "Name";          
    }
    static const Char8         *getFieldName (void) 
    {
        return "name";          
    }
    static const Char8         *getGroupName (void) 
    { 
        return "name";          
    }
    static const Char8         *getClassName (void) 
    {
        return "NameAttachment";
    }
    static const Char8         *getParentTypeName(void) 
    {
        return "Attachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;            }

    static FieldDescription **getDesc      (void) { return _desc;           }
};

typedef SimpleAttachment<NameAttachmentDesc  > Name;

typedef FCPtr           <AttachmentPtr,  Name> NamePtr;


class AttachmentContainerPtr;

OSG_SYSTEMLIB_DLLMAPPING
const char   *getName(      AttachmentContainerPtr  container);

OSG_SYSTEMLIB_DLLMAPPING
      void    setName(      AttachmentContainerPtr  container, 
                      const std::string            &name     );
OSG_SYSTEMLIB_DLLMAPPING
      void    setName(      AttachmentContainerPtr  container, 
                      const char                   *name     );
 

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILEATTACHMENTINST
OSG_FC_DLLEXPORT_DECL(SimpleAttachment, 
                      NameAttachmentDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Template to build simple attachment classes which store an arbitrary
//! number of fields.
//! \ingroup FieldContainerLib

template <class AttachmentDescT>
class DynFieldAttachment : 
    public AttachmentDescT::Parent
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          DynFieldAttachment<AttachmentDescT> Self;

    typedef typename AttachmentDescT::ParentPtr          ParentPtrType;

    typedef          FCPtr<ParentPtrType,  Self        > PtrType;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    UInt32 addField       (const FieldDescription &fieldDesc);
    void   subField       (      UInt32            fieldId  );

    Field *getDynamicField(      UInt32            index    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Clone                                   */
    /*! \{                                                                 */

    FieldContainerPtr emptyCopy(void);
    FieldContainerPtr clone    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef typename AttachmentDescT::Parent Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static FieldContainerType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    FieldContainerType   _localType;

    std::vector<Field *> _dynFieldsV;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynFieldAttachment(void);
    DynFieldAttachment(const DynFieldAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynFieldAttachment(void); 

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    
    /*!\brief prohibit default functions (move to 'public' if needed) */
    void operator =(const DynFieldAttachment &source);
};

typedef std::map<UInt32, AttachmentPtr>  AttachmentMap;

OSG_SYSTEMLIB_DLLMAPPING

std::ostream &operator <<(      std::ostream  &stream,
                          const AttachmentMap &amap);

OSG_END_NAMESPACE

#define OSGATTACHMENT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTIMPL_H_ */
