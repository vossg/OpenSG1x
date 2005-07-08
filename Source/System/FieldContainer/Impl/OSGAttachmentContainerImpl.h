/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef _OSGATTACHMENTCONTAINERIMPL_H_
#define _OSGATTACHMENTCONTAINERIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentContainerImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGFieldContainer.h>
#include <OSGSFAttachmentMap.h>
#include <OSGAttachmentPtr.h>

OSG_BEGIN_NAMESPACE

class BinaryDataHandler;

/*! \ingroup GrpSystemFieldContainer
    AttachmentContainer provides the functionality to store
    attachments for derived FieldContainer classes.
    
*/

class OSG_SYSTEMLIB_DLLMAPPING AttachmentContainer : public FieldContainer 
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef FieldContainer Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    enum 
    { 
        AttachmentsFieldId = Inherited::NextFieldId, 
        NextFieldId        = AttachmentsFieldId + 1
    };

    static const BitVector AttachmentsFieldMask;


    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_ABSTR_FIELD_CONTAINER_DECL(AttachmentContainerPtr)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Handle Attachments                        */
    /*! \{                                                                 */

    void          addAttachment (const AttachmentPtr &fieldContainerP, 
                                       UInt16         binding        = 0);

    void          subAttachment (const AttachmentPtr &fieldContainerP,
                                       UInt16         binding        = 0);

    AttachmentPtr findAttachment(      UInt32         groupId,
                                       UInt16         binding        = 0);

    AttachmentPtr findAttachment(const FieldContainerType &type,
                                       UInt16              binding   = 0);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                                                              */
    /*! \{                        Field Access                             */

    SFAttachmentMap *getSFAttachments(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Changed                               */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

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

    SFAttachmentMap _attachmentMap;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AttachmentContainer(void);
    AttachmentContainer(const AttachmentContainer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~AttachmentContainer (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    virtual void executeSync    (      FieldContainer      &other,
                                 const BitVector           &whichField);

            void executeSyncImpl(      AttachmentContainer *pOther,
                                 const BitVector           &whichField);
#else
    virtual void executeSync    (      FieldContainer      &other,
                                 const BitVector           &whichField,
                                 const SyncInfo            &sInfo     );

            void executeSyncImpl(      AttachmentContainer *pOther,
                                 const BitVector           &whichField,
                                 const SyncInfo            &sInfo     );
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Pointer                                  */
    /*! \{                                                                 */

    AttachmentContainerPtr getPtr(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldContainerType;

    /*!\brief prohibit default functions (move to 'public' if needed) */
    void operator =(const AttachmentContainer &source);
};

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTCONTAINERIMPL_H_ */
