/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
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


#ifndef _OSGNODECORE_H_
#define _OSGNODECORE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>

#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerType.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSFFieldContainerTypes.h>
#include <OSGMFFieldContainerTypes.h>
#include <OSGDynamicVolume.h>
#include <OSGAttachment.h>

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
 *  \brief OSGNodeCore
 */

class OSGNodeCore : public OSGFieldContainer 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGParentsField)
    
    OSG_FC_FIELD_IDM_DECL      (OSGAttachmentsField)

    OSG_FC_LAST_FIELD_IDM_DECL

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

    OSG_ABSTR_FIELD_CONTAINER_DECL(OSGNodeCorePtr)

    /*------------------------------ parents -------------------------------*/

    OSGMFNodePtr       *getMFParents    (void);
    OSGSFAttachmentMap *getSFAttachments(void);

    /*------------------------------ attachments ---------------------------*/

    void             addAttachment (OSGAttachmentPtr &fieldContainerP, 
                                    OSGUInt16         binding = 0);

    void             subAttachment (OSGAttachmentPtr &fieldContainerP,
                                    OSGUInt16         binding = 0);

    OSGAttachmentPtr findAttachment(OSGUInt16 groupId, 
                                    OSGUInt16 binding = 0);

    /*------------------------------ pointer -------------------------------*/

    OSGNodeCorePtr getPtr (void);

    /*-------------------------- transformation ----------------------------*/

    virtual void accumulateMatrix(OSGMatrix &result);

    /*------------------------------ volume -------------------------------*/

    virtual void adjustVolume(OSGVolume &volume);
    
    /*------------------------------ dump -----------------------------------*/

            void print(OSGUInt32 indent);
    virtual void dump (void) const;

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

    OSGMFNodePtr       _parents;
    OSGSFAttachmentMap _attachmentMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGNodeCore (void);
    OSGNodeCore (const OSGNodeCore &obj);
    virtual ~OSGNodeCore (void);

    void addParent(const OSGNodePtr &parent);
    void subParent(const OSGNodePtr &parent);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainer Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGNode;
    friend class OSGAttachment;
    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static OSGFieldDescription   _desc[];
    static OSGFieldContainerType _type;

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

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGNodeCore *OSGNodeCoreP;

OSG_END_NAMESPACE

#include <OSGNodeCore.inl>

#endif /* _OSG_NODECORE_H_ */
