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


#ifndef _OSGATTACHMENTCONTAINER_H_
#define _OSGATTACHMENTCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGFieldDescription.h>
#include <OSGFieldContainer.h>
#include <OSGAttachmentContainerPtr.h>
#include <OSGSFAttachmentMap.h>
#include <OSGAttachmentPtr.h>

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
 *  \brief Node
 */

class OSG_SYSTEMLIB_DLLMAPPING AttachmentContainer : public FieldContainer 
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

	enum 
	{ 
		AttachmentsFieldId = Inherited::NextFieldId, 
		NextFieldId        = AttachmentsFieldId + 1
	};

	static const BitVector AttachmentsFieldMask;

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

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(AttachmentContainerPtr)

    /*------------------------------ attachments ---------------------------*/

    void addAttachment(const AttachmentPtr &fieldContainerP, 
                             UInt16         binding = 0);

    void subAttachment(const AttachmentPtr &fieldContainerP,
                             UInt16         binding = 0);

    AttachmentPtr findAttachment(UInt32 groupId,
                                 UInt16 binding = 0);

    /*--------------------------- access fields ----------------------------*/

    SFAttachmentMap *getSFAttachments(void);

    /*------------------------------ changed -------------------------------*/

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);

    /*--------------------------To / From Bin ------------------------------*/

    virtual UInt32       getBinSize (const BitVector    &whichField);

    virtual MemoryHandle copyToBin  (      MemoryHandle  pMem, 
                                     const BitVector    &whichField);
    virtual MemoryHandle copyFromBin(      MemoryHandle  pMem, 
                                     const BitVector    &whichField);
    
    /*------------------------------ dump ----------------------------------*/

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
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class FieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static FieldDescription   *_desc[];
    static FieldContainerType  _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SFAttachmentMap _attachmentMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    AttachmentContainer(void);
    AttachmentContainer(const AttachmentContainer &source);
    virtual ~AttachmentContainer (void);

    virtual void executeSync    (      FieldContainer      &other,
                                 const BitVector           &whichField);

            void executeSyncImpl(      AttachmentContainer *pOther,
                                 const BitVector           &whichField);

    /*------------------------------ pointer -------------------------------*/

    AttachmentContainerPtr getPtr(void);

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

typedef AttachmentContainer *AttachmentContainerP;

OSG_END_NAMESPACE

#include <OSGAttachmentContainer.inl>

#endif /* _OSGATTACHMENTCONTAINER_H_ */
