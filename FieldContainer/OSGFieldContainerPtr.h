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
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGFieldContainer;
class OSGNode;
class OSGNodeCore;
class OSGAttachment;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief OSGFieldContainerPtr is the base class of all field container
 *  pointer. This and the derived classes form the base for the thread safe
 *  data store used by OSG.
 */

class OSGFieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    static const OSGUInt16 OSGInvalidParentFPos;

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainer OSGContainerType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "OSGFieldContainerPtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
    
    OSGFieldContainerPtr(void);
    OSGFieldContainerPtr(const OSGFieldContainerPtr &source);
    OSGFieldContainerPtr(const OSGFieldContainer    &source);
    virtual ~OSGFieldContainerPtr(void); 

    /*------------------------------ cast ----------------------------------*/

    /** \brief Must do it this way because of MipsPro 7.2 support
     */

#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
#ifdef __sgi
#pragma set woff 1424
#endif

    template <class T>
    T dcast(void)
	{
		return T(* ((T *) this));
	}

#ifdef __sgi
#pragma reset woff 1424
#endif

#else
    template <class T>
    T &dcast(T &result)
	{
	    result = * ((T *) this);
		return result;
	}
#endif

    /*----------------------------- parent field pos -----------------------*/

    void      setParentFieldPos(OSGUInt16 parentFPos);
    OSGUInt16 getParentFieldPos(void);

    /*------------------------------ information ---------------------------*/

    OSGUInt32 getContainerId(void);

    /*------------------------- pointer operators --------------------------*/

          OSGFieldContainer *operator->(void);
    const OSGFieldContainer *operator->(void) const;

          OSGFieldContainer &operator *(void);
    const OSGFieldContainer &operator *(void) const;

    operator OSGFieldContainer *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGFieldContainerPtr &operator =(const OSGFieldContainerPtr &source);

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGFieldContainerPtr &other) const;
    
	OSGBool operator == (const OSGFieldContainerPtr &other) const;
	OSGBool operator != (const OSGFieldContainerPtr &other) const;

    OSGBool operator !(void) const;

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

	static OSGBool initialize(int argc, char **argv);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    OSGUInt16  _containerSize;
    OSGUInt16  _parentFPos;
    OSGUInt8  *_storeP;

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

    void executeSync(OSGUInt32    fromAspect,
                     OSGUInt32    toAspect, 
                     OSGBitVector whichField);

    /*-------------------------------- Mem ---------------------------------*/
    
          OSGInt32  *getRefCountP (void);
    const OSGInt32  *getRefCountP (void) const;

          OSGUInt32 *getIdP       (void);    
    const OSGUInt32 *getIdP       (void) const;    

          OSGUInt8  *getFirstElemP(void);
    const OSGUInt8  *getFirstElemP(void) const;

          OSGUInt8  *getElemP     (OSGUInt32 elemNum);
    const OSGUInt8  *getElemP     (OSGUInt32 elemNum) const;

    OSGInt32  getRefCountOff (void) const;
    OSGInt32  getIdOff       (void) const;
    OSGInt32  getFirstElemOff(void) const;
    OSGInt32  getElemOff     (OSGUInt32 elemNum) const;

    /*------------------------- ReferenceCounting --------------------------*/

    void addRef(void);
    void subRef(void);

    /*----------------------------- Edit -----------------------------------*/

    void beginEdit        (OSGBitVector whichField);
    void endEdit          (OSGBitVector whichField);
    void changed          (OSGBitVector whichField);
    void endEditNotChanged(OSGBitVector whichField);

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

    friend class OSGFieldContainer;
    friend class OSGFieldContainerFactory;
    friend class OSGChangeList;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

	friend ostream &operator <<(ostream &os, const OSGFieldContainerPtr &fc);

    friend void osgAddRefCP           (OSGFieldContainerPtr &pObject);
    friend void osgSubRefCP           (OSGFieldContainerPtr &pObject);
    friend void osgBeginEditCP        (OSGFieldContainerPtr &pObject, 
                                       OSGBitVector          whichField);
    friend void osgEndEditCP          (OSGFieldContainerPtr &pObject,
                                       OSGBitVector          whichField);
    friend void osgChangedCP          (OSGFieldContainerPtr &objectP, 
                                       OSGBitVector          whichField);

    friend void osgEndEditNotChangedCP(OSGFieldContainerPtr &objectP, 
                                       OSGBitVector          whichField);
        
    friend void osgSetRefdCP          (OSGFieldContainerPtr &objectP,
                                       OSGFieldContainerPtr &newObjectP);

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

	// prohibit default functions (move to 'public' if you need one)
};

ostream &operator <<(ostream &outStream,
                     const OSGFieldContainerPtr &color);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to a node
 */

class OSGNode;
class OSGNodeCore;
class OSGCNodePtr;

class OSGNodePtr : public OSGFieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNode OSGContainerType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "OSGNodePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGNodePtr(void);
    OSGNodePtr(const OSGNodePtr &source);
    explicit OSGNodePtr(const OSGCNodePtr &source);

    virtual ~OSGNodePtr(void); 

    /*--------------------------- core access ------------------------------*/

    OSGNodeCore *getCore(void);

    /*----------------------- pointer operators ----------------------------*/

          OSGNode *operator->(void);
    const OSGNode *operator->(void) const;

          OSGNode &operator *(void);
    const OSGNode &operator *(void) const;

    operator OSGNode *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGNodePtr &operator =(const OSGCNodePtr &source);

    OSGNodePtr &operator =(const OSGNodePtr &source);

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

#ifdef OSG_DEBUG_TYPED_FCPTR
    OSGNode    *_typedStoreP;
#endif
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

#ifdef OSG_DEBUG_TYPED_FCPTR
    virtual void updateTypedStore(void);
#endif

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGNode;
    friend class OSGFieldContainer;

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

    explicit OSGNodePtr(const OSGNode &source);
};

/*
ostream &operator <<(ostream &outStream,
                     const OSGNodePtr &vol);
*/

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to a node
 */

class OSGCNodePtr : public OSGFieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNode OSGContainerType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) 
        { return "OSGCNodePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGCNodePtr(void);
    OSGCNodePtr(const OSGCNodePtr &source);
    explicit OSGCNodePtr(const OSGNodePtr &source);

    virtual ~OSGCNodePtr(void); 

    /*--------------------------- node access ------------------------------*/

    OSGNode *getNode(void);

    /*----------------------- pointer operators ----------------------------*/

          OSGNodeCore *operator->(void);
    const OSGNodeCore *operator->(void) const;

          OSGNodeCore &operator *(void);
    const OSGNodeCore &operator *(void) const;

    operator OSGNodeCore *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGCNodePtr &operator =(const OSGNodePtr &source);
    OSGCNodePtr &operator =(const OSGCNodePtr &source);

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

#ifdef OSG_DEBUG_TYPED_FCPTR
    OSGNode    *_typedStoreP;
#endif
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

#ifdef OSG_DEBUG_TYPED_FCPTR
    virtual void updateTypedStore(void);
#endif

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGNode;
    friend class OSGFieldContainer;

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

    explicit OSGCNodePtr(const OSGNode &source);
};

/*
ostream &operator <<(ostream &outStream,
                     const OSGCNodePtr &vol);
*/

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Pointer to node cores
 *
 *  detailed
 */


class OSGNodeCorePtr : public OSGFieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNodeCore OSGContainerType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGNodeCorePtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGNodeCorePtr(void);
    OSGNodeCorePtr(const OSGNodeCorePtr &source);
    virtual ~OSGNodeCorePtr(void); 

    /*------------------------- pointer operators --------------------------*/

          OSGNodeCore *operator->(void);
    const OSGNodeCore *operator->(void) const;

          OSGNodeCore &operator *(void);
    const OSGNodeCore &operator *(void) const;

    operator OSGNodeCore *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGNodeCorePtr &operator =(const OSGNodeCorePtr &source);

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

#ifdef OSG_DEBUG_TYPED_FCPTR
    OSGNodeCore *_typedStoreP;
#endif
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

#ifdef OSG_DEBUG_TYPED_FCPTR
    virtual void updateTypedStore(void);
#endif

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGNodeCore;
    friend class OSGFieldContainer;

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

    explicit OSGNodeCorePtr(const OSGNodeCore &source);
};

/*
ostream &operator <<(ostream &outStream,
                     const OSGNodeCorePtr &vol);
*/

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainterLib
 *  \brief Pointer to attachment
 */

class OSGAttachmentPtr : public OSGFieldContainerPtr
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGAttachment OSGContainerType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGAttachmentPtr"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGAttachmentPtr(void);
    OSGAttachmentPtr(const OSGAttachmentPtr &source);
    explicit OSGAttachmentPtr(const OSGAttachment &source);
    virtual ~OSGAttachmentPtr(void); 

    /*---------------------- pointer operators -----------------------------*/

          OSGAttachment *operator->(void);
    const OSGAttachment *operator->(void) const;

          OSGAttachment &operator *(void);
    const OSGAttachment &operator *(void) const;

    operator OSGAttachment *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGAttachmentPtr &operator =(const OSGAttachmentPtr &source);

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

    typedef OSGFieldContainerPtr Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

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

	// prohibit default functions (move to 'public' if you need one)
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Template to construct custom field container pointer. A custom
 *  pointer is created by instantiating the template with type and the parent
 *  pointer type. For example :
 *  \code
 *  typedef OSGFCPtr<OSGNodeCorePtr, OSGTransform> OSGTransformPtr;
 *  \endcode
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> 
class OSGFCPtr : public OSGBasePtrTypeT
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainerTypeT OSGContainerType;
	typedef OSGFieldContainerTypeT OSGObjectType;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGFCPtr"; };

    static const OSGFCPtr NullPtr;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFCPtr(void); 
    OSGFCPtr(const OSGFCPtr &source);
    explicit OSGFCPtr(const OSGFieldContainerTypeT &source);
    virtual ~OSGFCPtr(void); 

    /*------------------------- pointer operators ---------------------------*/

          OSGFieldContainerTypeT *operator ->(void);
    const OSGFieldContainerTypeT *operator ->(void) const;

          OSGFieldContainerTypeT &operator *(void);
    const OSGFieldContainerTypeT &operator *(void) const;

    operator OSGFieldContainerTypeT *(void);

    /*------------------------- assignment ----------------------------------*/

    OSGFCPtr &operator =(const OSGFCPtr &source);

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

#ifdef OSG_DEBUG_TYPED_FCPTR
    OSGObjectType *_typedStoreP;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

#ifdef OSG_DEBUG_TYPED_FCPTR
    virtual void updateTypedStore(void);
#endif

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGBasePtrTypeT Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

	template <class BasePtr, class ContainerType>
	friend inline ostream &operator 
			<<(ostream &os, const OSGFCPtr<BasePtr, ContainerType> &fc);
				
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

extern const OSGFieldContainerPtr   OSGNullFC;
extern const OSGNodePtr             OSGNullNode;
extern const OSGNodeCorePtr         OSGNullNodeCore;
extern const OSGAttachmentPtr       OSGNullAttachment;

OSG_END_NAMESPACE

#include <OSGFieldContainerPtr.inl>

#endif /* _OSGFIELDCONTAINERPTR_H_ */
