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

#ifndef _OSGFIELDCONTAINERPTRIMPL_H_
#define _OSGFIELDCONTAINERPTRIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerPtrImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGConceptPropertyChecks.h>
#include <OSGFieldContainerProperties.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>

#include <OSGThread.h>
#include <OSGLock.h>
#include <OSGThreadManager.h>

#include <utility>
#include <iostream>

OSG_BEGIN_NAMESPACE

class FieldContainer;
class LockPool;
class NullFieldContainerPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

#ifdef __sgi
#pragma set woff 1424
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt16           InvalidParentEPos;
    typedef UInt8 * FieldContainerPtrBase::*unspecified_bool_type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtrBase(      void                         ); 
    FieldContainerPtrBase(const NullFieldContainerPtr &      );
    FieldContainerPtrBase(const FieldContainerPtrBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtrBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Parent Field Pos                         */
    /*! \{                                                                 */

    void   setParentFieldPos(UInt16 uiParentEPos);
    UInt16 getParentFieldPos(void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Get Container Information                       */
    /*! \{                                                                 */

    Int32  getRefCount        (void) const;
    UInt32 getFieldContainerId(void) const;
    UInt16 getContainerSize   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Get Container C++ Pointer                       */
    /*                 be sure you know what you are doing ;-)             */
    /*! \{                                                                 */

    FieldContainer *getBaseCPtr  (void             ) const;
    FieldContainer *getAspectCPtr(UInt32 uiAspectId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const NullFieldContainerPtr &);
    void operator =(const FieldContainerPtrBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator <  (const NullFieldContainerPtr &     ) const;
    
    bool operator == (const NullFieldContainerPtr &other) const;
    bool operator != (const NullFieldContainerPtr &other) const;


    bool operator <  (const FieldContainerPtrBase &) const;

    bool operator == (const FieldContainerPtrBase &other) const;
    bool operator != (const FieldContainerPtrBase &other) const;

    bool operator !  (void                              ) const;

    operator unspecified_bool_type() const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(      UInt32    uiIndent = 0, 
              const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    static bool initialize(void);
    static bool terminate (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16          _containerSize;
    UInt16          _uiParentEPos;
    UInt8          *_storeP;
#ifdef OSG_DEBUG_FCPTR
    FieldContainer *_typedStoreP;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit FieldContainerPtrBase(const FieldContainer &source      );
    explicit FieldContainerPtrBase(const FieldContainer *source      );

             FieldContainerPtrBase(const FieldContainer *source,
                                   const UInt16          uiSize,
                                   const UInt16          uiParentEPos);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    void executeSync(UInt32    uiFromAspect,
                     UInt32    uiToAspect, 
                     BitVector whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Get Memory Locations                            */
    /*! \{                                                                 */
    
    Int32  *getRefCountP (void            );
    Int32  *getRefCountP (void            ) const;
    
    UInt32 *getIdP       (void            );    
    UInt32 *getIdP       (void            ) const;    
    
    UInt8  *getFirstElemP(void            );
    UInt8  *getFirstElemP(void            ) const;
    
    UInt8  *getElemP     (UInt32 uiElemNum);
    UInt8  *getElemP     (UInt32 uiElemNum) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Memory Offsets                             */
    /*! \{                                                                 */

    Int32  getRefCountOff (void            ) const;
    Int32  getIdOff       (void            ) const;
    Int32  getFirstElemOff(void            ) const;
    Int32  getElemOff     (UInt32 uiElemNum) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Reference Counting                         */
    /*! \{                                                                 */

    void addRef          (void) const;
    void subRef          (void) const;

#if defined(OSG_FIXED_MFIELDSYNC)
    void doSubRef        (void) const;
#endif

    void deleteContainers(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Helper                                     */
    /*! \{                                                                 */

    void setNull(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldContainerFactory;
    friend class ChangeList;

#ifndef OSG_INVALID_PTR_CHECK
    
    friend OSG_SYSTEMLIB_DLLMAPPING
    void addRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void subRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void setRefdCP  (      FieldContainerPtrBase &objectP,
                     const FieldContainerPtrBase &newObjectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void clearRefCP (      FieldContainerPtrBase &objectP);

#else

    friend OSG_SYSTEMLIB_DLLMAPPING
    bool safeAddRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    bool safeSubRefCP   (const FieldContainerPtrBase &objectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    bool safeSetRefdCP  (      FieldContainerPtrBase &objectP,
                     const FieldContainerPtrBase &newObjectP);

    friend OSG_SYSTEMLIB_DLLMAPPING
    bool safeClearRefCP (      FieldContainerPtrBase &objectP);

#endif

    friend OSG_SYSTEMLIB_DLLMAPPING
    class FieldContainerType;

    static LockPool *_pRefCountLock;
};

#ifdef __sgi
#pragma reset woff 1375
#endif



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtr : public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    OSG_PROPERTY_DECL(Pointer);

    typedef FieldContainer        StoredObjectType;
    typedef FieldContainerPtr     ObjectType;

    typedef FieldContainerPtrBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtr(      void                         );
    FieldContainerPtr(const NullFieldContainerPtr &      );
    FieldContainerPtr(const FieldContainerPtr     &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FieldContainerPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    FieldContainer *operator->(void);
    FieldContainer *operator->(void) const;

    FieldContainer &operator *(void);
    FieldContainer &operator *(void) const;
 
    FieldContainer *getCPtr   (void);
    FieldContainer *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const NullFieldContainerPtr &      );
    void operator =(const FieldContainerPtr     &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    MT Edit                                   */
    /*! \{                                                                 */

    void beginEdit        (BitVector whichField, UInt32 origin) const;
    void endEdit          (BitVector whichField, UInt32 origin) const;
    void changed          (BitVector whichField, UInt32 origin) const;
    void endEditNotChanged(BitVector whichField, UInt32 origin) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit FieldContainerPtr(const FieldContainer &source);
    explicit FieldContainerPtr(const FieldContainer *source);

             FieldContainerPtr(const FieldContainer *source,
                               const UInt16          uiSize,
                               const UInt16          uiParentEPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;

    friend OSG_SYSTEMLIB_DLLMAPPING
    void beginEditCP        (const FieldContainerPtr &objectP, 
                                   BitVector          whichField,
                                   UInt32             origin    );

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditCP          (const FieldContainerPtr &objectP, 
                                   BitVector          whichField,
                                   UInt32             origin    );

    friend OSG_SYSTEMLIB_DLLMAPPING
    void changedCP          (const FieldContainerPtr &objectP, 
                                   BitVector          whichField,
                                   UInt32             origin    );

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditNotChangedCP(const FieldContainerPtr &objectP, 
                                   BitVector          whichField,
                                   UInt32             origin    );
};



/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING NullFieldContainerPtr : 
    public FieldContainerPtr 
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NullFieldContainerPtr(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~NullFieldContainerPtr(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! ConstFieldContainerPtr, read FieldContainer const * pFieldContainer
    NOT FieldContainer * const pFieldContainer
   \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING ConstFieldContainerPtr : 
    public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    OSG_PROPERTY_DECL(ConstPointer);

    typedef FieldContainer        StoredObjectType;
    typedef FieldContainerPtr     ObjectType;

    typedef FieldContainerPtrBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConstFieldContainerPtr(      void                          );
    ConstFieldContainerPtr(const NullFieldContainerPtr  &      );
    ConstFieldContainerPtr(const FieldContainerPtr      &source);
    ConstFieldContainerPtr(const ConstFieldContainerPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ConstFieldContainerPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    const FieldContainer *operator->(void);
    const FieldContainer *operator->(void) const;

    const FieldContainer &operator *(void);
    const FieldContainer &operator *(void) const;
 
    const FieldContainer *getCPtr   (void);
    const FieldContainer *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const NullFieldContainerPtr &       );
    void operator =(const FieldContainerPtr      &source);
    void operator =(const ConstFieldContainerPtr &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    explicit ConstFieldContainerPtr(const FieldContainer &source);
    explicit ConstFieldContainerPtr(const FieldContainer *source);

             ConstFieldContainerPtr(const FieldContainer *source,
                                    const UInt16          uiSize,
                                    const UInt16          uiParentEPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Template to construct custom field container pointers
    \ingroup GrpSystemFieldContainer
 */

template <class BasePtrTypeT, class FieldContainerTypeT> 
class FCPtr : public BasePtrTypeT
{
    /*==========================  PUBLIC  =================================*/

  public:

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, Pointer);

    typedef FieldContainerTypeT        StoredObjectType;
    typedef FCPtr                      ObjectType;

    typedef BasePtrTypeT               Inherited;

    typedef FCPtr<BasePtrTypeT,
                  FieldContainerTypeT> Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> inline
    static FCPtr dcast(const InTypeT oIn)
    {
        return FCPtr(
            (dynamic_cast<const typename FCPtr::StoredObjectType *>(
                oIn.getCPtr())),
            oIn.getContainerSize(),
            oIn.getParentFieldPos());
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FCPtr(      void                         ); 
    FCPtr(const NullFieldContainerPtr &      );
    FCPtr(const FCPtr                 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~FCPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    FieldContainerTypeT *operator->(void);
    FieldContainerTypeT *operator->(void) const;

    FieldContainerTypeT &operator *(void);
    FieldContainerTypeT &operator *(void) const;

    FieldContainerTypeT *getCPtr   (void);
    FieldContainerTypeT *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const FCPtr                 &source);
    void operator =(const NullFieldContainerPtr &      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
     *  use them only if you really now what you are doing ;-)             */

    explicit FCPtr(const FieldContainerTypeT &source);
    explicit FCPtr(const FieldContainerTypeT *source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */
    
    FCPtr(const FieldContainerTypeT *source,
          const UInt16               uiSize,
          const UInt16               uiParentPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Template to construct custom data store pointers
    \ingroup GrpSystemFieldContainerX
 */

template <class BasePtrTypeT, class FieldContainerTypeT> 
class ConstFCPtr : public BasePtrTypeT
{
    /*==========================  PUBLIC  =================================*/

  public:

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, ConstPointer);

    typedef FieldContainerTypeT                               StoredObjectType;
    typedef ConstFCPtr                                        ObjectType;

    typedef BasePtrTypeT                                      Inherited;

    typedef FCPtr<typename FieldContainerTypeT::Ptr::Inherited,
                  FieldContainerTypeT                         > NCFCPtr;

    typedef ConstFCPtr<BasePtrTypeT,
                       FieldContainerTypeT>                     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConstFCPtr(      void                         ); 
    ConstFCPtr(const NullFieldContainerPtr &      );
    ConstFCPtr(const NCFCPtr               &source);
    ConstFCPtr(const ConstFCPtr            &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~ConstFCPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    const FieldContainerTypeT *operator->(void);
    const FieldContainerTypeT *operator->(void) const;

    const FieldContainerTypeT &operator *(void);
    const FieldContainerTypeT &operator *(void) const;

    const FieldContainerTypeT *getCPtr   (void);
    const FieldContainerTypeT *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const NCFCPtr               &      );
    void operator =(const ConstFCPtr            &source);
    void operator =(const NullFieldContainerPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
     *  use them only if you really now what you are doing ;-)             */

    explicit ConstFCPtr(const FieldContainerTypeT &source);
    explicit ConstFCPtr(const FieldContainerTypeT *source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */

    ConstFCPtr(const FieldContainerTypeT *source,
               const UInt16               uiSize,
               const UInt16               uiParentPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
};


/*! \ingroup GrpSystemFieldContainerFuncs
    CPEditor class to wrap begin/endEditCP in an auto_ptr-like object
 */

class OSG_SYSTEMLIB_DLLMAPPING CPEditor
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    inline CPEditor(void);
    
    inline CPEditor(const FieldContainerPtr fc, 
                    const BitVector mask = FieldBits::AllFields);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    inline ~CPEditor();

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
  
    FieldContainerPtr   _fc;
    BitVector           _mask;
};

/*! \ingroup GrpSystemFieldContainerFuncs
    Helper macro to simplify using CPEditor
 */

#define CPEdit(fc, mask) \
 ::OSG::CPEditor CPEdit_##fc((fc),(mask))

#define CPEditAll(fc) \
 ::OSG::CPEditor CPEdit_##fc((fc))

#ifdef __sgi
#pragma reset woff 1375
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

#ifdef __sgi
#pragma reset woff 1424
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &operator <<(      std::ostream      &os,
                          const FieldContainerPtr &fc);

extern OSG_SYSTEMLIB_DLLMAPPING const NullFieldContainerPtr NullFC;

#define OSGNullFC OSG::NullFC

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRIMPL_H_ */
