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

#ifndef _OSGCNODEPTRIMPL_H_
#define _OSGCNODEPTRIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGCNodePtrImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>
#include <OSGAttachmentContainerPtr.h>

OSG_BEGIN_NAMESPACE

class Node;
class NodeCore;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef __sgi
#pragma set woff 1375,1424
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING CNodePtr : public AttachmentContainerPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef NodeCore               StoredObjectType;
    typedef CNodePtr               ObjectType;

    typedef AttachmentContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             CNodePtr(      void                         );
             CNodePtr(const CNodePtr              &source);
             CNodePtr(const NullFieldContainerPtr &source);
    explicit CNodePtr(const NodePtr               &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~CNodePtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    Node *getNode(void);
    Node *getNode(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    NodeCore *operator->(void);
    NodeCore *operator->(void) const;

    NodeCore &operator *(void);
    NodeCore &operator *(void) const;

    NodeCore *getCPtr   (void);
    NodeCore *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const NodePtr               &source);
    void operator =(const CNodePtr              &source);
    void operator =(const NullFieldContainerPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
     *  use them only if you really now what you are doing ;-)             */

    explicit CNodePtr(const Node &source);
    explicit CNodePtr(const Node *source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */

    CNodePtr(const Node   *source,
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
                          const CNodePtr     &fc);

OSG_END_NAMESPACE

#define OSGCNODEPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGCNODEPTRIMPL_H_ */
