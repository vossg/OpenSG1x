/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#ifndef _OSGNODEPTRIMPL_H_
#define _OSGNODEPTRIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodePtrImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>
#include <OSGAttachmentContainerPtr.h>

OSG_BEGIN_NAMESPACE

class Node;
class NodeCore;

class CNodePtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

#ifdef __sgi
#pragma set woff 1375,1424
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

class OSG_SYSTEMLIB_DLLMAPPING NodePtr : public AttachmentContainerPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef Node                   StoredObjectType;
    typedef NodePtr                ObjectType;

    typedef AttachmentContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> 
    static NodePtr dcast(const InTypeT oIn);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             NodePtr(void);
             NodePtr(const NodePtr               &source);
             NodePtr(const NullFieldContainerPtr &source);
    explicit NodePtr(const CNodePtr              &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~NodePtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Core                                  */
    /*! \{                                                                 */

    NodeCore *getCore(void);
    NodeCore *getCore(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    Node *operator->(void);
    Node *operator->(void) const;

    Node &operator *(void);
    Node &operator *(void) const;

    Node *getCPtr   (void);
    Node *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const CNodePtr              &source);
    void operator =(const NodePtr               &source);
    void operator =(const NullFieldContainerPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
     *  use them only if you really now what you are doing ;-)             */

    explicit NodePtr(const Node   &source);
    explicit NodePtr(const Node   *source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */
    
    NodePtr(const Node   *source,
            const UInt16  uiSize,
            const UInt16  uiParentPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
};

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &operator <<(      std::ostream &os,
                          const NodePtr      &fc);


/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
NodePtr makeNodeFor(NodeCorePtr core);


OSG_END_NAMESPACE

#define OSGNODEPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGNODEPTRIMPL_H_ */
