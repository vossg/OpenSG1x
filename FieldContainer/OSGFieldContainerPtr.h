
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGFIELDCONTAINERPTR_H_
#define _OSGFIELDCONTAINERPTR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGFieldContainerBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FieldContainer;
class Node;
class NodeCore;
class Attachment;
class LockPool;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerPtr is the base class of all field container
 *  pointer. This and the derived classes form the base for the thread safe
 *  data store used by OSG.
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    static const UInt16 InvalidParentFPos;

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainer ObjectType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "FieldContainerPtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
    
    FieldContainerPtr(void);
    FieldContainerPtr(const FieldContainerPtr &source);
    virtual ~FieldContainerPtr(void); 

    /*------------------------------ cast ----------------------------------*/

    /** \brief Must do it this way because of MipsPro 7.2 support
     */

#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
#ifdef __sgi
#pragma set woff 1424
#endif

    template <class T>
    T dcast(void) const
	{
		return T(* ((T *) this));
	}

#ifdef __sgi
#pragma reset woff 1424
#endif

#else
    template <class T>
    T &dcast(T &result) const
	{
	    result = * ((T *) this);
		return result;
	}
#endif

    /*----------------------------- parent field pos -----------------------*/

    void      setParentFieldPos(UInt16 parentFPos);
    UInt16 getParentFieldPos(void) const;

    /*------------------------------ information ---------------------------*/

    UInt32 getContainerId(void) const;

    /*------------------------- pointer operators --------------------------*/

          FieldContainer *operator->(void);
    const FieldContainer *operator->(void) const;

          FieldContainer &operator *(void);
    const FieldContainer &operator *(void) const;

          FieldContainer *getCPtr   (void);
    const FieldContainer *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator FieldContainer *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    FieldContainerPtr &operator =(const FieldContainerPtr &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const FieldContainerPtr &other) const;
    
	Bool operator == (const FieldContainerPtr &other) const;
	Bool operator != (const FieldContainerPtr &other) const;

    Bool operator !(void) const;

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;

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

	static Bool initialize(int argc, char **argv);
    static Bool terminate(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt16  _containerSize;
    UInt16  _parentFPos;
    UInt8  *_storeP;

#ifdef OSG_DEBUG_TYPED_FCPTR
    const char        *_typename;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------------------------- Debug -------------------------------*/

#ifdef OSG_DEBUG_TYPED_FCPTR
    virtual void updateTypedStore(void);
#endif

    /*-------------------------------- Sync --------------------------------*/

    void executeSync(UInt32    fromAspect,
                     UInt32    toAspect, 
                     BitVector whichField);

    /*-------------------------------- Mem ---------------------------------*/
    
          Int32  *getRefCountP (void);
    const Int32  *getRefCountP (void) const;

          UInt32 *getIdP       (void);    
    const UInt32 *getIdP       (void) const;    

          UInt8  *getFirstElemP(void);
    const UInt8  *getFirstElemP(void) const;

          UInt8  *getElemP     (UInt32 elemNum);
    const UInt8  *getElemP     (UInt32 elemNum) const;

    Int32  getRefCountOff (void) const;
    Int32  getIdOff       (void) const;
    Int32  getFirstElemOff(void) const;
    Int32  getElemOff     (UInt32 elemNum) const;

    /*------------------------- ReferenceCounting --------------------------*/

    void addRef(void);
    void subRef(void);

    /*----------------------------- Edit -----------------------------------*/

    void beginEdit        (BitVector whichField);
    void endEdit          (BitVector whichField);
    void changed          (BitVector whichField);
    void endEditNotChanged(BitVector whichField);

    /*----------------------------- Dump -----------------------------------*/

    void dumpContent(void) const;

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

    friend class FieldContainer;
    friend class FieldContainerFactory;
    friend class ChangeList;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

	friend OSG_FIELDCONTAINER_DLLMAPPING 
           ostream &operator <<(ostream &os, const FieldContainerPtr &fc);

    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgAddRefCP   (FieldContainerPtr &pObject);
    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgSubRefCP   (FieldContainerPtr &pObject);
    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgBeginEditCP(FieldContainerPtr &pObject, 
                            BitVector          whichField);
    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgEndEditCP  (FieldContainerPtr &pObject,
                            BitVector          whichField);
    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgChangedCP  (FieldContainerPtr &objectP, 
                            BitVector          whichField);

    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgEndEditNotChangedCP(FieldContainerPtr &objectP, 
                                    BitVector          whichField);
        
    friend OSG_FIELDCONTAINER_DLLMAPPING 
        void osgSetRefdCP  (FieldContainerPtr &objectP,
                            FieldContainerPtr &newObjectP);

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static LockPool *_refCountLockP;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit FieldContainerPtr(const FieldContainer &source);
};

OSG_FIELDCONTAINER_DLLMAPPING ostream &operator <<(ostream &outStream,
                                   const FieldContainerPtr &color);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to a node
 */

class Node;
class NodeCore;
class CNodePtr;

class OSG_FIELDCONTAINER_DLLMAPPING NodePtr : public FieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Node ObjectType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "NodePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

             NodePtr(void);
             NodePtr(const NodePtr &source);
    explicit NodePtr(const CNodePtr &source);

    virtual ~NodePtr(void); 

    /*--------------------------- core access ------------------------------*/

    NodeCore *getCore(void);

    /*----------------------- pointer operators ----------------------------*/

          Node *operator->(void);
    const Node *operator->(void) const;

          Node &operator *(void);
    const Node &operator *(void) const;

          Node *getCPtr   (void);
    const Node *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator Node *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    NodePtr &operator =(const CNodePtr &source);
    NodePtr &operator =(const NodePtr  &source);

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;
    
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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class Node;
    friend class FieldContainer;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit NodePtr(const Node &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to a node
 */

class OSG_FIELDCONTAINER_DLLMAPPING CNodePtr : public FieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Node ObjectType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "CNodePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

             CNodePtr(void);
             CNodePtr(const CNodePtr &source);
    explicit CNodePtr(const NodePtr &source);

    virtual ~CNodePtr(void); 

    /*--------------------------- node access ------------------------------*/

    Node *getNode(void);

    /*----------------------- pointer operators ----------------------------*/

          NodeCore *operator->(void);
    const NodeCore *operator->(void) const;

          NodeCore &operator *(void);
    const NodeCore &operator *(void) const;

          NodeCore *getCPtr   (void);
    const NodeCore *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator NodeCore *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    CNodePtr &operator =(const NodePtr  &source);
    CNodePtr &operator =(const CNodePtr &source);

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;
    
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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class Node;
    friend class FieldContainer;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit CNodePtr(const Node &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to node cores
 *
 *  detailed
 */

class OSG_FIELDCONTAINER_DLLMAPPING NodeCorePtr : public FieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef NodeCore ObjectType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "NodeCorePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    NodeCorePtr(void);
    NodeCorePtr(const NodeCorePtr &source);
    virtual ~NodeCorePtr(void); 

    /*------------------------- pointer operators --------------------------*/

          NodeCore *operator->(void);
    const NodeCore *operator->(void) const;

          NodeCore &operator *(void);
    const NodeCore &operator *(void) const;

          NodeCore *getCPtr   (void);
    const NodeCore *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator NodeCore *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    NodeCorePtr &operator =(const NodeCorePtr &source);

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class NodeCore;
    friend class FieldContainer;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit NodeCorePtr(const NodeCore &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainterLib
 *  \brief Pointer to attachment
 */

class OSG_FIELDCONTAINER_DLLMAPPING AttachmentPtr : public FieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Attachment ObjectType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "AttachmentPtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    AttachmentPtr(void);
    AttachmentPtr(const AttachmentPtr &source);
    virtual ~AttachmentPtr(void); 

    /*---------------------- pointer operators -----------------------------*/

          Attachment *operator->(void);
    const Attachment *operator->(void) const;

          Attachment &operator *(void);
    const Attachment &operator *(void) const;

          Attachment *getCPtr   (void);
    const Attachment *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator Attachment *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    AttachmentPtr &operator =(const AttachmentPtr &source);

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    explicit AttachmentPtr(const Attachment &source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Template to construct custom field container pointer. A custom
 *  pointer is created by instantiating the template with type and the parent
 *  pointer type. For example :
 *  \code
 *  typedef FCPtr<NodeCorePtr, Transform> TransformPtr;
 *  \endcode
 */

template <class BasePtrTypeT, class FieldContainerTypeT> 
class OSG_FIELDCONTAINER_DLLMAPPING FCPtr : public BasePtrTypeT
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainerTypeT ContainerType;
	typedef FieldContainerTypeT ObjectType;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "FCPtr"; };

    static const FCPtr NullPtr;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FCPtr(void); 
    FCPtr(const FCPtr &source);
    explicit FCPtr(const FieldContainerTypeT &source);
    virtual ~FCPtr(void); 

    /*------------------------- pointer operators ---------------------------*/

          FieldContainerTypeT *operator ->(void);
    const FieldContainerTypeT *operator ->(void) const;

          FieldContainerTypeT &operator *(void);
    const FieldContainerTypeT &operator *(void) const;

          FieldContainerTypeT *getCPtr   (void);
    const FieldContainerTypeT *getCPtr   (void) const;

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
    operator FieldContainerTypeT *(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    FCPtr &operator =(const FCPtr &source);

    /*------------------------------ dump ----------------------------------*/

    virtual void dump(void) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef BasePtrTypeT Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

	template <class BasePtr, class ContainerType>
	friend inline ostream &operator 
			<<(ostream &os, const FCPtr<BasePtr, ContainerType> &fc);
				
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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

extern OSG_FIELDCONTAINER_DLLMAPPING const FieldContainerPtr   NullFC;
extern OSG_FIELDCONTAINER_DLLMAPPING const NodePtr             NullNode;
extern OSG_FIELDCONTAINER_DLLMAPPING const NodeCorePtr         NullNodeCore;
extern OSG_FIELDCONTAINER_DLLMAPPING const AttachmentPtr       NullAttachment;

OSG_END_NAMESPACE

#include <OSGFieldContainerPtr.inl>

#endif /* _OSGFIELDCONTAINERPTR_H_ */
