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

#include <OSGConceptPropertyChecks.h>
#include <OSGFieldContainerProperties.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>

#include <utility>

OSG_BEGIN_NAMESPACE

class FieldContainer;
class LockPool;
class NullFieldContainerPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! FieldContainerPtrBase
//! \ingroup FieldContainerLib

#ifdef __sgi
#pragma set woff 1424
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    static const UInt16           InvalidParentEPos;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtrBase(void); 
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

    UInt32 getFieldContainerId(void) const;
    UInt16 getContainerSize   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const FieldContainerPtrBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator <  (const FieldContainerPtrBase &other) const;
    
    bool operator == (const FieldContainerPtrBase &other) const;
    bool operator != (const FieldContainerPtrBase &other) const;

    bool operator !  (void                              ) const;

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

    static bool initialize(int &argc, char **argv);
    static bool terminate (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16  _containerSize;
    UInt16  _uiParentEPos;
    UInt8  *_storeP;

#ifdef OSG_DEBUG_TYPED_FCPTR
    const Char8 *_szTypename;
#endif

    /*! \}                                                                 */

#ifdef OSG_DEBUG_TYPED_FCPTR
    void updateTypedStore(void);
#endif

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

    void addRef        (void) const;
    void subRef        (void) const;

    void subRefUnlocked(void) const;
    void subRefUntraced(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FieldContainerFactory;
    friend class ChangeList;

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

    static LockPool *_pRefCountLock;
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! FieldContainerPtr
//! \ingroup FieldContainerLib

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerPtr : public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    OSG_PROPERTY_DECL(Pointer);

    typedef FieldContainer        ObjectType;

    typedef FieldContainerPtrBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerPtr(void);
    FieldContainerPtr(const FieldContainerPtr &source);

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

    void operator =(const FieldContainerPtr     &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    MT Edit                                   */
    /*! \{                                                                 */

    void beginEdit        (BitVector whichField) const;
    void endEdit          (BitVector whichField) const;
    void changed          (BitVector whichField) const;
    void endEditNotChanged(BitVector whichField) const;

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
                                   BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditCP          (const FieldContainerPtr &objectP, 
                                   BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void changedCP          (const FieldContainerPtr &objectP, 
                                   BitVector          whichField);

    friend OSG_SYSTEMLIB_DLLMAPPING
    void endEditNotChangedCP(const FieldContainerPtr &objectP, 
                                   BitVector          whichField);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ConstFieldContainerPtr, read FieldContainer const * pFieldContainer
//! NOT FieldContainer * const pFieldContainer
//! \ingroup FieldContainerLib

class OSG_SYSTEMLIB_DLLMAPPING ConstFieldContainerPtr : 
    public FieldContainerPtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    OSG_PROPERTY_DECL(ConstPointer);

    typedef FieldContainer        ObjectType;

    typedef FieldContainerPtrBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConstFieldContainerPtr(void                                );
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

//! Template to construct custom field container pointers
//! \ingroup FieldContainerLib

template <class BasePtrTypeT, class FieldContainerTypeT> 
class OSG_SYSTEMLIB_DLLMAPPING FCPtr : public BasePtrTypeT
{
    /*==========================  PUBLIC  =================================*/
  public:

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, Pointer);

    typedef FieldContainerTypeT ObjectType;

    typedef BasePtrTypeT        Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> inline
    static FCPtr dcast(const InTypeT oIn)
    {
        return FCPtr(
            (dynamic_cast<const typename FCPtr::ObjectType *>(oIn.getCPtr())),
            oIn.getContainerSize(),
            oIn.getParentFieldPos());
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FCPtr(void                               ); 
    FCPtr(const NullFieldContainerPtr &source);
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
    void operator =(const NullFieldContainerPtr &source);

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

//! Template to construct custom data store pointers
//! \ingroup FieldContainerLib

template <class BasePtrTypeT, class FieldContainerTypeT> 
class OSG_SYSTEMLIB_DLLMAPPING ConstFCPtr : public BasePtrTypeT
{
    /*==========================  PUBLIC  =================================*/
  public:

    OSG_PROPERTY_REQUIREMENT(BasePtrTypeT, ConstPointer);

    typedef FieldContainerTypeT                                 ObjectType;

    typedef BasePtrTypeT                                        Inherited;

    typedef FCPtr<typename FieldContainerTypeT::Ptr::Inherited,
                  FieldContainerTypeT                         > NCFCPtr;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ConstFCPtr(void                               ); 
    ConstFCPtr(const NullFieldContainerPtr &source);
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

    void operator =(const NCFCPtr               &source);
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




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! NullPtr Class
//! \ingroup FieldContainerLib

class NullFieldContainerPtr : public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/
  public:

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

#ifdef __sgi
#pragma reset woff 1375
#endif

#ifdef __sgi
#pragma reset woff 1424
#endif

extern OSG_SYSTEMLIB_DLLMAPPING const NullFieldContainerPtr NullFC;

OSG_END_NAMESPACE

#include <OSGFieldContainerPtr.inl>

#define OSGFIELDCONTAINERPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTR_H_ */
