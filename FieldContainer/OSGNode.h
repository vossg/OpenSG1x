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


#ifndef _OSGNODE_H_
#define _OSGNODE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

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

class OSGNodeCore;
class OSGNodePtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief OSGNode
 */

class OSGNode : public OSGFieldContainer 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGNameField       )

    OSG_FC_FIELD_IDM_DECL      (OSGVolumeField     )

    OSG_FC_FIELD_IDM_DECL      (OSGParentField     )
    OSG_FC_FIELD_IDM_DECL      (OSGChildrenField   )

    OSG_FC_FIELD_IDM_DECL      (OSGCoreField       )

    OSG_FC_FIELD_IDM_DECL      (OSGAttachmentsField)

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNodePtr OSGPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGNodePtr)

    /*------------------------------ attachments ---------------------------*/

    virtual void addAttachment(const OSGAttachmentPtr &fieldContainerP);

    virtual void subAttachment(const OSGAttachmentPtr &fieldContainerP);

    virtual OSGAttachmentPtr findAttachment(int typeID);

    /*-------------------------------- core --------------------------------*/

    OSGNodeCorePtr getCore(void);
    void           setCore(const OSGNodeCorePtr &core);

    /*------------------------------ parent --------------------------------*/

    OSGNodePtr    getParent  (void);

    /*------------------------------ children ------------------------------*/

    OSGUInt32  getNChildren  (void) const;
    
    void       addChild      (const OSGNodePtr &childP);

    void       insertChild   (      OSGUInt32   childIndex, 
                              const OSGNodePtr &childP);

    void       replaceChild  (      OSGUInt32   childIndex,    
                              const OSGNodePtr &childP);

    void       replaceChildBy(const OSGNodePtr &childP, 
                              const OSGNodePtr &newChildP);

    void       subChild      (const OSGNodePtr &childP);
    void       subChild      (      OSGUInt32   childIndex);

    OSGNodePtr getChild      (      OSGUInt32   childIndex);

    /*--------------------------- access fields ----------------------------*/

    OSGSFString        *getSFName       (void);
    OSGSFVolume        *getSFVolume     (void);

    OSGSFNodePtr       *getSFParent     (void);
    OSGSFNodeCorePtr   *getSFCore       (void);
    OSGMFNodePtr       *getMFChildren   (void);

    OSGSFAttachmentMap *getSFAttachments(void);

    /*------------------------------ pointer -------------------------------*/

    OSGNodePtr        getPtr       (void);

    /*-------------------------- transformation ----------------------------*/

    OSGMatrix getToWorld(void);
    
    void      getToWorld(OSGMatrix & result);
    
    /*------------------------------ volume -------------------------------*/
    
    const OSGVolume &getVolume      (void)             const;
    
          void       getWorldVolume (OSGVolume &result);
    
          void       updateVolume    (void);

          void       invalidateVolume(void);

    /*------------------------------ changed -------------------------------*/

    virtual void changed(OSGBitVector  whichField, 
                         OSGChangeMode from);
    
    /*------------------------------ dump ----------------------------------*/

            void print(OSGUInt32 indent = 0) const;

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

    friend class OSGFieldContainer;
    friend class OSGFieldContainerType;

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

    OSGNode(void);
    OSGNode(const OSGNode &source);
    virtual ~OSGNode (void);

    void setParent(const OSGNodePtr &_parent);

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

    OSGSFString        _name;

    OSGSFVolume        _volume;

    OSGSFNodePtr       _parent;
    OSGMFNodePtr       _children;

    OSGSFNodeCorePtr   _core;

    OSGSFAttachmentMap _attachmentMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

typedef OSGNode *OSGNodeP;

OSG_END_NAMESPACE

#include <OSGNode.inl>

#endif /* _OSGNODE_H_ */
