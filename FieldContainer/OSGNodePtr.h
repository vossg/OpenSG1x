/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSGNODEPTR_H_
#define _OSGNODEPTR_H_
#ifdef __sgi
#pragma once
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

//! Pointer to a node
//! \ingroup FieldContainerLib

#ifdef __sgi
#pragma set woff 1375,1424
#endif

class OSG_SYSTEMLIB_DLLMAPPING NodePtr : public AttachmentContainerPtr
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef Node                   StoredObjectType;
//    typedef NodePtr                ObjectType;

    typedef AttachmentContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> inline
    static NodePtr dcast(const InTypeT oIn)
    {
        return NodePtr(
            (dynamic_cast<const Node *>(oIn.getCPtr())),
             oIn.getContainerSize(),
             oIn.getParentFieldPos());
    }

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

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Pointer to a node
//! \ingroup FieldContainerLib

class OSG_SYSTEMLIB_DLLMAPPING CNodePtr : public AttachmentContainerPtr
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef NodeCore               StoredObjectType;
//    typedef CNodePtr                   ObjectType;

    typedef AttachmentContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             CNodePtr(void);
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

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

OSG_SYSTEMLIB_DLLMAPPING
ostream &operator <<(      ostream  &os,
                     const NodePtr  &fc);
OSG_SYSTEMLIB_DLLMAPPING
ostream &operator <<(      ostream  &os,
                     const CNodePtr &fc);

OSG_END_NAMESPACE

#define OSGNODEPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGNODEPTR_H_ */
