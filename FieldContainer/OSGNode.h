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

class NodeCore;
class BinaryDataHandler;

//! Node
//! \ingroup FieldContainerLib

class OSG_SYSTEMLIB_DLLMAPPING Node : public AttachmentContainer 
{
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef AttachmentContainer Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum 
    { 
        VolumeFieldId      = Inherited::NextFieldId, 
        ActiveFieldId      = VolumeFieldId         + 1,
        ParentFieldId      = ActiveFieldId         + 1,
        ChildrenFieldId    = ParentFieldId         + 1,
        CoreFieldId        = ChildrenFieldId       + 1,
        NextFieldId        = CoreFieldId           + 1
    };

    static const BitVector VolumeFieldMask;
    static const BitVector ActiveFieldMask;
    static const BitVector ParentFieldMask;
    static const BitVector ChildrenFieldMask;
    static const BitVector CoreFieldMask;

    typedef NodePtr Ptr;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_DECL(NodePtr)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Core                                  */
    /*! \{                                                                 */

    NodeCorePtr getCore(      void             );
    NodeCorePtr getCore(      void             ) const;

    void        setCore(const NodeCorePtr &core);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Unlink                                 */
    /*! \{                                                                 */

    void unlink       (void);
    void unlinkSubTree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Parent                                 */
    /*! \{                                                                 */

    NodePtr getParent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Children                               */
    /*! \{                                                                 */

    UInt32  getNChildren  (void                     ) const;
    
    void    addChild      (const NodePtr &childP    );

    void    insertChild   (      UInt32   childIndex, 
                           const NodePtr &childP    );

    void    replaceChild  (      UInt32   childIndex,    
                           const NodePtr &childP    );

    bool    replaceChildBy(const NodePtr &childP, 
                           const NodePtr &newChildP );

    Int32   findChild     (const NodePtr &childP    ) const;

    void    subChild      (const NodePtr &childP    );
    void    subChild      (      UInt32   childIndex);

    NodePtr getChild      (      UInt32   childIndex);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Active                                 */
    /*! \{                                                                 */

          bool &getActive(void     );
    const bool &getActive(void     ) const;

          void  setActive(bool val);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Children                               */
    /*! \{                                                                 */

    NodePtr clone(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Access Fields                            */
    /*! \{                                                                 */

    SFDynamicVolume *getSFVolume  (void);
    SFBool          *getSFActive  (void);
    SFNodePtr       *getSFParent  (void);
    SFNodeCorePtr   *getSFCore    (void);
    MFNodePtr       *getMFChildren(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Transformation                            */
    /*! \{                                                                 */

    Matrix getToWorld(void          );
    
    void   getToWorld(Matrix &result);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Volume                                 */
    /*! \{                                                                 */
    
           DynamicVolume &getVolume       (bool update = true   );
    
    const  DynamicVolume &getVolume       (void                 ) const;
    
           void           getWorldVolume  (DynamicVolume &result);
    
           void           updateVolume    (void                 );

           void           invalidateVolume(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Changed                               */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);

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

    friend class FieldContainer;
    friend class FieldContainerType;

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static       FieldDescription   *_desc[];
    static       FieldContainerType  _type;

    static const NodePtr              NullNode;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    SFDynamicVolume _sfVolume;
    
    SFBool          _sfActive;
    
    SFNodePtr       _sfParent;
    MFNodePtr       _mfChildren;

    SFNodeCorePtr   _sfCore;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Node(void);
    Node(const Node &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Node (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    void setParent(const NodePtr &parent);

    void onCreate (const Node    *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      Node           *pOther,
                                 const BitVector      &whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Pointer                                  */
    /*! \{                                                                 */

    NodePtr getPtr(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const Node &source);
};

OSG_SYSTEMLIB_DLLMAPPING
NodePtr cloneTree(NodePtr pRootNode);

OSG_END_NAMESPACE

#include <OSGNode.inl>

#define OSGNODE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGNODE_H_ */
