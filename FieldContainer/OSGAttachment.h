/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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


#ifndef _OSGATTACHMENT_H_
#define _OSGATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainerBase.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainer.h>
#include <OSGFieldDescription.h>
#include <OSGFieldContainerType.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSFFieldContainerTypes.h>
#include <OSGMFFieldContainerTypes.h>
#include <OSGSFBaseTypes.h>

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Attachment is the base class for sharable thread safe data 
 *  stores,
 *  which could be attached to other fieldcontainers than Attachments.
 */

class OSG_FIELDCONTAINER_DLLMAPPING Attachment : public FieldContainer 
{
  private:

    typedef FieldContainer Inherited;

  public:

    OSG_FC_FIRST_FIELD_IDM_DECL(ParentsField)

    OSG_FC_LAST_FIELD_IDM_DECL (ParentsField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Attachment"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(AttachmentPtr)

    /*------------------------------ parents -------------------------------*/

          MFFieldContainerPtr &getParents  (void);
    const MFFieldContainerPtr &getParents  (void) const;
    
          MFFieldContainerPtr *getMFParents(void);

	void                       addParent   (FieldContainerPtr parent);
	void                       subParent   (FieldContainerPtr parent);

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

	static FieldDescription   _desc[];
	static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    MFFieldContainerPtr _parents;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Attachment(void);
    Attachment(const Attachment &obj);

    virtual ~Attachment(void);

    virtual void finalize(void);

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

    void operator =(const Attachment &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Template to build simple attachment classes which store only one 
 *  field.
 */

template <class AttachmentDescT>
class OSG_FIELDCONTAINER_DLLMAPPING SimpleAttachment : public Attachment
{
  private:

    typedef Attachment Inherited;

  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename AttachmentDescT::FieldTypeT  FieldType;

    typedef SimpleAttachment<AttachmentDescT>     SimpleAttType;

    typedef FCPtr<AttachmentPtr,  SimpleAttType>  PtrType;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(SimpleField)

    OSG_FC_LAST_FIELD_IDM_DECL (SimpleField)

    static const PtrType NullPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return AttachmentDescT::getClassName(); }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*----------------------------- access ----------------------------------*/

          FieldType *getFieldPtr(void);

          FieldType &getField   (void);
    const FieldType &getField   (void) const;

    /*------------------------- assignment ----------------------------------*/

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    FieldType _field;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SimpleAttachment(void);
    SimpleAttachment(const SimpleAttachment &source);
    virtual ~SimpleAttachment(void); 

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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldDescription   _desc[];

	static FieldContainerType _type;

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

    SimpleAttachment &operator =(const SimpleAttachment &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

struct NameAttachmentDesc
{
    typedef SFString FieldTypeT;

    static const Char8 *getTypeName (void) { return "Name"; }
    static const Char8 *getFieldName(void) { return "name"; }
    static const Char8 *getGroupName(void) { return "name"; }
    static const Char8 *getClassName(void) { return "NameAttachment"; }

    static InitContainerF getInitMethod(void) { return NULL; }
};

typedef SimpleAttachment<NameAttachmentDesc> Name;

typedef FCPtr<AttachmentPtr,  Name> NamePtr;

#ifndef OSG_COMPILEATTACHMENTINST
#if defined(__sgi)

#pragma do_not_instantiate SimpleAttachment<NameAttachmentDesc>::_type
#pragma do_not_instantiate SimpleAttachment<NameAttachmentDesc>::_desc

#else

OSG_FC_DLLEXPORT_DECL(SimpleAttachment, 
                      NameAttachmentDesc,
                      OSG_FIELDCONTAINER_TMPLDLLMAPPING)

#endif
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

template <class AttachmentDescT>
class OSG_FIELDCONTAINER_DLLMAPPING DynFieldAttachment : 
    public AttachmentDescT::Parent
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef DynFieldAttachment<AttachmentDescT   > DynFieldAttType;

    typedef typename AttachmentDescT::ParentPtr    ParentPtrType;

    typedef FCPtr<ParentPtrType,  DynFieldAttType> PtrType;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const PtrType NullPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "DynFieldAttachment"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*------------------------- your_category -------------------------------*/

    UInt32 addField       (const FieldDescription &fieldDesc);
    void   subField       (      UInt32            fieldId);

    Field *getDynamicField(UInt32 index);

    /*------------------------- your_operators ------------------------------*/

    FieldContainerPtr emptyCopy(void);

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*--------------------------- dump --------------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

    DynFieldAttachment(void);

    virtual ~DynFieldAttachment(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename AttachmentDescT::Parent Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldContainerType _type;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    FieldContainerType _localType;

    vector<Field *>    _dynFieldsV;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    DynFieldAttachment(const DynFieldAttachment &source);
    void operator =(const DynFieldAttachment &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief AttachmentP
 */

typedef Attachment                          *AttachmentP;

typedef FCPtr<FieldContainerPtr, Attachment> AttachmentPtr;

extern OSG_FIELDCONTAINER_DLLMAPPING const AttachmentPtr NullAttachment;


typedef map<UInt32, AttachmentPtr>  AttachmentMap;

OSG_FIELDCONTAINER_DLLMAPPING
ostream &operator <<(      ostream       &stream,
                     const AttachmentMap &map);

OSG_END_NAMESPACE

#include <OSGAttachment.inl>

#endif /* _OSGATTACHMENT_H_ */
