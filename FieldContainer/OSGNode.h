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


#ifndef _OSGNODE_H_
#define _OSGNODE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainerBase.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGFieldDescription.h>
#include <OSGFieldContainer.h>
#include <OSGSFSysTypes.h>
#include <OSGSFBaseTypes.h>
#include <OSGSFFieldContainerTypes.h>
#include <OSGMFFieldContainerTypes.h>
#include <OSGAttachment.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class NodeCore;
class NodePtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Node
 */

class OSG_FIELDCONTAINER_DLLMAPPING Node : public FieldContainer 
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(VolumeField                    )

    OSG_FC_FIELD_IDM_DECL      (ParentField,      VolumeField  )
    OSG_FC_FIELD_IDM_DECL      (ChildrenField,    ParentField  )

    OSG_FC_FIELD_IDM_DECL      (CoreField,        ChildrenField)

    OSG_FC_FIELD_IDM_DECL      (AttachmentsField, CoreField    )

    OSG_FC_LAST_FIELD_IDM_DECL (AttachmentsField               )

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef NodePtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(NodePtr)

    /*------------------------------ attachments ---------------------------*/

    virtual void addAttachment(const AttachmentPtr &fieldContainerP);

    virtual void subAttachment(const AttachmentPtr &fieldContainerP);

    virtual AttachmentPtr findAttachment(UInt32 typeID);

    /*-------------------------------- core --------------------------------*/

    NodeCorePtr getCore(void);
    NodeCorePtr getCore(void) const;
    void        setCore(const NodeCorePtr &core);

    /*------------------------------ parent --------------------------------*/

    NodePtr    getParent  (void);

    /*------------------------------ children ------------------------------*/

    UInt32  getNChildren  (void) const;
    
    void    addChild      (const NodePtr &childP);

    void    insertChild   (      UInt32   childIndex, 
                           const NodePtr &childP);

    void    replaceChild  (      UInt32   childIndex,    
                           const NodePtr &childP);

    void    replaceChildBy(const NodePtr &childP, 
                           const NodePtr &newChildP);

    void    subChild      (const NodePtr &childP);
    void    subChild      (      UInt32   childIndex);

    NodePtr getChild      (      UInt32   childIndex);

    /*--------------------------- access fields ----------------------------*/

    SFVolume        *getSFVolume     (void);

    SFNodePtr       *getSFParent     (void);
    SFNodeCorePtr   *getSFCore       (void);
    MFNodePtr       *getMFChildren   (void);

    SFAttachmentMap *getSFAttachments(void);

    /*------------------------------ pointer -------------------------------*/

    NodePtr        getPtr       (void);

    /*-------------------------- transformation ----------------------------*/

    Matrix getToWorld(void);
    
    void   getToWorld(Matrix & result);
    
    /*------------------------------ volume -------------------------------*/
    
    const Volume &getVolume       (void)             const;
    
          void    getWorldVolume  (Volume &result);
    
          void    updateVolume    (void);

          void    invalidateVolume(void);

    /*------------------------------ changed -------------------------------*/

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
    
    /*------------------------------ dump ----------------------------------*/

            void print(UInt32 indent = 0) const;

    virtual void dump (void)                 const;

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

    Node(void);
    Node(const Node &source);
    virtual ~Node (void);

    void setParent(const NodePtr &_parent);

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

    SFVolume        _volume;

    SFNodePtr       _parent;
    MFNodePtr       _children;

    SFNodeCorePtr   _core;

    SFAttachmentMap _attachmentMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

typedef Node *NodeP;

OSG_END_NAMESPACE

#include <OSGNode.inl>

#endif /* _OSGNODE_H_ */
