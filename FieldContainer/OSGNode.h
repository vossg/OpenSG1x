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


#ifndef _OSGNODE_H_
#define _OSGNODE_H_
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
#include <OSGSFSysTypes.h>
#include <OSGSFBaseTypes.h>

#include <OSGAttachmentContainer.h>
#include <OSGSFNodeCorePtr.h>
#include <OSGSFNodePtr.h>
#include <OSGMFNodePtr.h>

#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class NodeCore;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Node
 */

class OSG_SYSTEMLIB_DLLMAPPING Node : public AttachmentContainer 
{
  private:

    typedef AttachmentContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

	enum 
	{ 
		VolumeFieldId      = Inherited::NextFieldId, 
		ParentFieldId      = VolumeFieldId      + 1,
		ChildrenFieldId    = ParentFieldId      + 1,
		CoreFieldId        = ChildrenFieldId    + 1,
		NextFieldId        = CoreFieldId + 1
	};

	static const BitVector VolumeFieldMask;
	static const BitVector ParentFieldMask;
	static const BitVector ChildrenFieldMask;
	static const BitVector CoreFieldMask;

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

    Bool    replaceChildBy(const NodePtr &childP, 
                           const NodePtr &newChildP);

    Int32   findChild     (const NodePtr &childP) const;

    void    subChild      (const NodePtr &childP);
    void    subChild      (      UInt32   childIndex);

    NodePtr getChild      (      UInt32   childIndex);

    /*--------------------------- access fields ----------------------------*/

    SFDynamicVolume	*getSFVolume     (void);

    SFNodePtr       *getSFParent     (void);
    SFNodeCorePtr   *getSFCore       (void);
    MFNodePtr       *getMFChildren   (void);

    /*-------------------------- transformation ----------------------------*/

    Matrix getToWorld(void);
    
    void   getToWorld(Matrix & result);
    
    /*------------------------------ volume -------------------------------*/
    
    const DynamicVolume &getVolume       ( bool update = true );
    
    const DynamicVolume &getVolume       (void) const;
    
          void			 getWorldVolume  (DynamicVolume &result);
    
          void			 updateVolume    (void);

          void			 invalidateVolume(void);

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Node(void);
    Node(const Node &source);
    virtual ~Node (void);

    void setParent(const NodePtr &_parent);

    void onCreate (void);
    void onCreate (const Node &source);

    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      Node      *pOther,
                                 const BitVector &whichField);

    /*------------------------------ pointer -------------------------------*/

    NodePtr getPtr(void);

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

    SFDynamicVolume	_volume;

    SFNodePtr       _parent;
    MFNodePtr       _children;

    SFNodeCorePtr   _core;

    SFAttachmentMap _attachmentMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

extern OSG_SYSTEMLIB_DLLMAPPING const NodePtr             NullNode;

typedef Node *NodeP;



OSG_END_NAMESPACE

#include <OSGNode.inl>

#endif /* _OSGNODE_H_ */
