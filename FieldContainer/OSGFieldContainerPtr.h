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

#ifndef _OSGFIELDCONTAINERPTR_H_
#define _OSGFIELDCONTAINERPTR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConceptPropertyChecks.h>
#include <OSGFieldContainerProperties.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>


#include <utility>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FieldContainer;
class LockPool;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerPtr
 */

#ifdef __sgi
#pragma set woff 1424
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtrBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt16           InvalidParentEPos;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

    friend OSG_SYSTEMLIB_DLLMAPPING
    void addRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void subRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void setRefdCP  (      FieldContainerPtrBase &objectP,
                     const FieldContainerPtrBase &newObjectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void clearRefCP (      FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    class FieldContainerType;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static LockPool *_pRefCountLock;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

	static Bool initialize(int &argc, char **argv);
    static Bool terminate(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt16  _containerSize;
    UInt16  _uiParentEPos;
    UInt8  *_storeP;

#ifdef OSG_DEBUG_TYPED_FCPTR
    const Char8 *_szTypename;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

#ifdef OSG_DEBUG_TYPED_FCPTR
    void updateTypedStore(void);
#endif

    explicit FieldContainerPtrBase(const FieldContainer &source);
    explicit FieldContainerPtrBase(const FieldContainer *source);

             FieldContainerPtrBase(const FieldContainer *source,
                                   const UInt16          uiSize,
                                   const UInt16          uiParentEPos);

    /*-------------------------------- Sync --------------------------------*/

    void executeSync(UInt32    uiFromAspect,
                     UInt32    uiToAspect, 
                     BitVector whichField);

    /*-------------------------------- Mem ---------------------------------*/
    
    Int32  *getRefCountP (void);
    Int32  *getRefCountP (void) const;
    
    UInt32 *getIdP       (void);    
    UInt32 *getIdP       (void) const;    
    
    UInt8  *getFirstElemP(void);
    UInt8  *getFirstElemP(void) const;
    
    UInt8  *getElemP     (UInt32 uiElemNum);
    UInt8  *getElemP     (UInt32 uiElemNum) const;

    /*-------------------------------- Mem Off -----------------------------*/

    Int32  getRefCountOff (void) const;
    Int32  getIdOff       (void) const;
    Int32  getFirstElemOff(void) const;
    Int32  getElemOff     (UInt32 uiElemNum) const;

    /*------------------------- ReferenceCounting --------------------------*/

    void addRef(void) const;
    void subRef(void) const;

    void subRefUnlocked(void) const;
    void subRefUntraced(void) const;

    /*----------------------------- Edit -----------------------------------*/

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*----------------------------- casting ---------------------------------*/

    FieldContainerPtrBase(void);
    FieldContainerPtrBase(const FieldContainerPtrBase &source);

    ~FieldContainerPtrBase(void); 

    /*----------------------------- parent field pos -----------------------*/

    void   setParentFieldPos(UInt16 uiParentEPos);
    UInt16 getParentFieldPos(void) const;

    /*------------------------------ information ---------------------------*/

    UInt32 getFieldContainerId(void) const;

    /*------------------------- your_operators ------------------------------*/

    UInt16 getContainerSize(void) const;

    /*------------------------- assignment ----------------------------------*/

    void operator =(const FieldContainerPtrBase &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator <  (const FieldContainerPtrBase &other) const;
    
    Bool operator == (const FieldContainerPtrBase &other) const;
	Bool operator != (const FieldContainerPtrBase &other) const;

    Bool operator !(void) const;

    void dump      (      UInt32     uiIndent = 0, 
                    const BitVector &bvFlags  = 0) const;
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerPtr
 */

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtr : public FieldContainerPtrBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_PROPERTY_DECL(Pointer);

    static const FieldContainerPtr NullPtr;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainer        ObjectType;

    typedef FieldContainerPtrBase Inherited;

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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    friend OSG_SYSTEMLIB_DLLMAPPING
    void beginEditCP(const FieldContainerPtr &objectP, 
                           BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditCP  (const FieldContainerPtr &objectP, 
                           BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void changedCP  (const FieldContainerPtr &objectP, 
                           BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditNotChangedCP(const FieldContainerPtr &objectP, 
                                   BitVector          whichField);

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

    /*----------------------------- Edit -----------------------------------*/

    void beginEdit        (BitVector whichField) const;
    void endEdit          (BitVector whichField) const;
    void changed          (BitVector whichField) const;
    void endEditNotChanged(BitVector whichField) const;

    explicit FieldContainerPtr(const FieldContainer &source);
    explicit FieldContainerPtr(const FieldContainer *source);

             FieldContainerPtr(const FieldContainer *source,
                               const UInt16          uiSize,
                               const UInt16          uiParentEPos);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldContainerPtr(void);
    FieldContainerPtr(const FieldContainerPtr &source);

    ~FieldContainerPtr(void); 

    /*----------------------------- casting ---------------------------------*/

    /*------------------------- pointer operators --------------------------*/

    FieldContainer *operator->(void);
    FieldContainer *operator->(void) const;

    FieldContainer &operator *(void);
    FieldContainer &operator *(void) const;
 
    FieldContainer *getCPtr   (void);
    FieldContainer *getCPtr   (void) const;

   /*------------------------- your_operators ------------------------------*/

   /*------------------------- assignment ----------------------------------*/

    void operator =(const FieldContainerPtr &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief ConstFieldContainerPtr, read FieldContainer const *pFieldContainer not
 *  FieldContainer * const pFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING ConstFieldContainerPtr : 
    public FieldContainerPtrBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_PROPERTY_DECL(ConstPointer);

    static const ConstFieldContainerPtr NullPtr;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainer        ObjectType;

    typedef FieldContainerPtrBase Inherited;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

    explicit ConstFieldContainerPtr(const FieldContainer &source);
    explicit ConstFieldContainerPtr(const FieldContainer *source);

             ConstFieldContainerPtr(const FieldContainer *source,
                                    const UInt16          uiSize,
                                    const UInt16          uiParentEPos);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ConstFieldContainerPtr(void);
    ConstFieldContainerPtr(const FieldContainerPtr &source);
    ConstFieldContainerPtr(const ConstFieldContainerPtr &source);

    ~ConstFieldContainerPtr(void); 

    /*----------------------------- casting ---------------------------------*/

    /*------------------------- pointer operators --------------------------*/

    const FieldContainer *operator->(void);
    const FieldContainer *operator->(void) const;

    const FieldContainer &operator *(void);
    const FieldContainer &operator *(void) const;
 
    const FieldContainer *getCPtr   (void);
    const FieldContainer *getCPtr   (void) const;

   /*------------------------- your_operators ------------------------------*/

   /*------------------------- assignment ----------------------------------*/

    void operator =(const FieldContainerPtr &source);
    void operator =(const ConstFieldContainerPtr &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Template to construct custom data store pointers
 */

template <class BasePtrTypeT, class FieldContainerTypeT> 
class OSG_SYSTEMLIB_DLLMAPPING FCPtr : public BasePtrTypeT
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, Pointer);

    static const FCPtr NullPtr;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef FieldContainerTypeT ObjectType;

    typedef BasePtrTypeT   Inherited;

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

             FCPtr(const FieldContainerTypeT *source,
                   const UInt16               uiSize,
                   const UInt16               uiParentPos);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	template <class InTypeT> inline
	static FCPtr dcast(const InTypeT oIn)
	{
		return FCPtr(
			(dynamic_cast<const typename FCPtr::ObjectType *>(oIn.getCPtr())),
			oIn.getContainerSize(),
			oIn.getParentFieldPos());
	}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FCPtr(void); 
    FCPtr(const FCPtr &source);

    ~FCPtr(void); 

    /*------------------------- pointer operators ---------------------------*/

    FieldContainerTypeT *operator ->(void);
    FieldContainerTypeT *operator ->(void) const;

    FieldContainerTypeT &operator *(void);
    FieldContainerTypeT &operator *(void) const;

    FieldContainerTypeT *getCPtr   (void);
    FieldContainerTypeT *getCPtr   (void) const;

    /*------------------------- assignment ----------------------------------*/

    void operator =(const FCPtr &source);


	/* The next two Constructors are used to work around MS Bugs, use them
	   only if you realy now what you are doing ;-) */

    explicit FCPtr(const FieldContainerTypeT &source);
    explicit FCPtr(const FieldContainerTypeT *source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief Template to construct custom data store pointers
 */

template <class BasePtrTypeT, class FieldContainerTypeT> 
class OSG_SYSTEMLIB_DLLMAPPING ConstFCPtr : public BasePtrTypeT
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, ConstPointer);

    static const ConstFCPtr NullPtr;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef FieldContainerTypeT  ObjectType;

    typedef BasePtrTypeT    Inherited;

    typedef FCPtr<typename FieldContainerTypeT::Ptr::Inherited,
                     FieldContainerTypeT                            > NCFCPtr;
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

    explicit ConstFCPtr(const FieldContainerTypeT &source);
    explicit ConstFCPtr(const FieldContainerTypeT *source);

             ConstFCPtr(const FieldContainerTypeT *source,
                        const UInt16               uiSize,
                        const UInt16               uiParentPos);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ConstFCPtr(void); 
    ConstFCPtr(const NCFCPtr    &source);
    ConstFCPtr(const ConstFCPtr &source);

    ~ConstFCPtr(void); 

    /*------------------------- pointer operators ---------------------------*/

    const FieldContainerTypeT *operator ->(void);
    const FieldContainerTypeT *operator ->(void) const;

    const FieldContainerTypeT &operator *(void);
    const FieldContainerTypeT &operator *(void) const;

    const FieldContainerTypeT *getCPtr   (void);
    const FieldContainerTypeT *getCPtr   (void) const;

    /*------------------------- assignment ----------------------------------*/

    void operator =(const NCFCPtr    &source);
    void operator =(const ConstFCPtr &source);
};

#ifdef __sgi
#pragma reset woff 1375
#endif

#ifdef __sgi
#pragma reset woff 1424
#endif

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef FieldContainerPtr *FieldContainerPtrP;

extern OSG_SYSTEMLIB_DLLMAPPING const FieldContainerPtr NullFC;

OSG_END_NAMESPACE

#include <OSGFieldContainerPtr.inl>

#endif /* _OSGFIELDCONTAINERPTR_H_ */
