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


#ifndef _OSGNODECORE_H_
#define _OSGNODECORE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGAttachmentContainerPtr.h>
#include <OSGAttachmentContainer.h>
#include <OSGMFNodePtr.h>
#include <OSGDynamicVolume.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class NodeCore;
typedef FCPtr<AttachmentContainerPtr, NodeCore> NodeCorePtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief NodeCore
 */

class OSG_SYSTEMLIB_DLLMAPPING NodeCore : public AttachmentContainer
{
  private:

    typedef AttachmentContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    enum 
    { 
        ParentsFieldId     = Inherited::NextFieldId, 
        NextFieldId        = ParentsFieldId + 1
    };

    static const BitVector ParentsFieldMask;

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

    OSG_ABSTR_FIELD_CONTAINER_DECL(NodeCorePtr)

    /*------------------------------ parents -------------------------------*/

          MFNodePtr       &getParents      (void);
    const MFNodePtr       &getParents      (void) const;
 
          MFNodePtr       *getMFParents    (void);

    /*------------------------------ pointer -------------------------------*/
    
    /*--------------------------To / From Bin ------------------------------*/

    virtual UInt32       getBinSize (const BitVector    &whichField);

    virtual MemoryHandle copyToBin  (      MemoryHandle  pMem, 
                                     const BitVector    &whichField);
    virtual MemoryHandle copyFromBin(      MemoryHandle  pMem, 
                                     const BitVector    &whichField);

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    MFNodePtr       _parents;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    NodeCore(void);
    NodeCore(const NodeCore &obj);
    virtual ~NodeCore(void);

    virtual void onDestroy(void);

    void addParent(const NodePtr &parent);
    void subParent(const NodePtr &parent);

    NodeCorePtr getPtr(void);

    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      NodeCore  *pOther,
                                 const BitVector &whichField);

    /*-------------------------- transformation ----------------------------*/

    virtual void accumulateMatrix(Matrix &result);

    /*------------------------------ volume -------------------------------*/

    virtual void adjustVolume    (Volume &volume);

    virtual void invalidateVolume( void );

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

    friend class Node;
    friend class Attachment;
    friend class FieldContainer;

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
};


//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

extern OSG_SYSTEMLIB_DLLMAPPING const NodeCorePtr         NullNodeCore;

typedef NodeCore *NodeCoreP;

OSG_END_NAMESPACE

#include <OSGNodeCore.inl>

#endif /* _OSGNODECORE_H_ */
