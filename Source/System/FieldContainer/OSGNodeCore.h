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

#ifndef _OSGNODECORE_H_
#define _OSGNODECORE_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodeCore.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <map>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGAttachmentContainerPtr.h>
#include <OSGAttachmentContainer.h>
#include <OSGNodeFields.h>
#include <OSGDynamicVolume.h>

OSG_BEGIN_NAMESPACE

class BinaryDataHandler;
class NodeCore;

// created as a dummy class, remove to prevent doubles
#if !defined(OSG_DO_DOC)   
typedef FCPtr<AttachmentContainerPtr, NodeCore> NodeCorePtr;
#endif

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING NodeCore : public AttachmentContainer
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef AttachmentContainer Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    enum 
    { 
        ParentsFieldId     = Inherited::NextFieldId, 
        NextFieldId        = ParentsFieldId + 1
    };

    static const BitVector ParentsFieldMask;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_ABSTR_FIELD_CONTAINER_DECL(NodeCorePtr)

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Parents                                  */
    /*! \{                                                                 */

          MFNodePtr &getParents  (void);
    const MFNodePtr &getParents  (void) const;
 
          MFNodePtr *getMFParents(void);

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
    /*---------------------------------------------------------------------*/
    /*! \name                       Volume                                 */
    /*! \{                                                                 */

    virtual void invalidateVolume(void);

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

    MFNodePtr _parents;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NodeCore(void);
    NodeCore(const NodeCore &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~NodeCore(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Destruction                                */
    /*! \{                                                                 */

    virtual void onDestroy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Set / Get Parents                             */
    /*! \{                                                                 */

    void addParent(const NodePtr &parent);
    void subParent(const NodePtr &parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Pointer                                  */
    /*! \{                                                                 */

    NodeCorePtr getPtr(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      NodeCore  *pOther,
                                 const BitVector &whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrix &result);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                CoredNodePtr helper                           */
    /*! \{                                                                 */
    
    static const bool isNodeCore = true;

    /*! \}                                                                 */    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class Node;
    friend class Attachment;
    friend class FieldContainer;

    /* prohibit default function (move to 'public' if needed) */
    void operator =(const NodeCore &source);
};

OSG_END_NAMESPACE

#include <OSGNodeCore.inl>

#define OSGNODECORE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGNODECORE_H_ */
