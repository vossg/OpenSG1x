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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGFieldContainerPtr.h"

#include "OSGLog.h"
#include "OSGThreadManager.h"
#include "OSGThread.h"
#include "OSGChangeList.h"
#include "OSGLock.h"
#include "OSGFieldContainer.h"

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
#include "OSGTime.h"
#endif

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERPTR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINERPTR_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

const NullFieldContainerPtr OSG::NullFC;




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::FieldContainerPtrBase
 */

const UInt16    FieldContainerPtrBase::InvalidParentEPos = 0xFFFF;

      LockPool *FieldContainerPtrBase::_pRefCountLock    = NULL;


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerPtrBase::FieldContainerPtrBase(void) :
    _containerSize(0),
    _uiParentEPos(InvalidParentEPos),
    _storeP(NULL)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _szTypename = NULL;
#endif
}

FieldContainerPtrBase::FieldContainerPtrBase(
    const FieldContainerPtrBase &source) :

    _containerSize(source._containerSize),
    _uiParentEPos (source._uiParentEPos),
    _storeP       (source._storeP)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerPtrBase::~FieldContainerPtrBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                         Parent Field Pos                                */

void FieldContainerPtrBase::setParentFieldPos(UInt16 uiParentEPos)
{
    _uiParentEPos = uiParentEPos;
}

UInt16 FieldContainerPtrBase::getParentFieldPos(void) const
{
    return _uiParentEPos;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

UInt32 FieldContainerPtrBase::getFieldContainerId(void) const
{
    return (*getIdP());
}

UInt16  FieldContainerPtrBase::getContainerSize(void) const
{
    return _containerSize;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void FieldContainerPtrBase::operator =(const FieldContainerPtrBase &source)
{
    if (this == &source)
        return;

    _containerSize = source._containerSize;
    _uiParentEPos  = source._uiParentEPos;
    _storeP        = source._storeP;

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool FieldContainerPtrBase::operator < (
    const FieldContainerPtrBase &other)const
{
    return _storeP < other._storeP;
}

bool FieldContainerPtrBase::operator ==(
    const FieldContainerPtrBase &other) const
{
    return _storeP == other._storeP;
}

bool FieldContainerPtrBase::operator !=(
    const FieldContainerPtrBase &other) const
{
    return ! (*this == other);
}

bool FieldContainerPtrBase::operator ! (void) const
{
    return _storeP == NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void FieldContainerPtrBase::dump(      UInt32    uiIndent,
                                 const BitVector bvFlags) const
{
    if(this != NULL && _storeP != NULL)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "FCPtr Dump :" << endl;

        uiIndent += 4;

        indentLog(uiIndent, PLOG);
        PLOG << "Id       : " << (*(getIdP()))   << endl;

        indentLog(uiIndent, PLOG);
        PLOG << "Storage  : " << hex << (UInt32 *)getFirstElemP() << endl;

        if(bvFlags & FCDumpFlags::RefCount)
        {
             indentLog(uiIndent, PLOG);
             PLOG << "RefCount : " << *(getRefCountP()) << endl;
        }

//        dumpContent();
    }
    else
    {
        PLOG << "FCPtr Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool FieldContainerPtrBase::initialize(int &, char **)
{
    bool           returnValue = false;
    ThreadManager *pManager    = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase init" << endl;

    if(pManager != NULL)
    {
        _pRefCountLock = pManager->getLockPool("DSPTRRefCountLockPool");

        addRefP(_pRefCountLock);

        if(_pRefCountLock != NULL)
            returnValue = true;
    }

    return returnValue;
}

bool FieldContainerPtrBase::terminate(void)
{
    ThreadManager *pManager = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase terminate" << endl;

    if(pManager == NULL)
        return false;

    subRefP(_pRefCountLock);

    return true;
}

#ifdef OSG_DEBUG_TYPED_FCPTR
void FieldContainerPtrBase::updateTypedStore(void)
{
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
}
#endif


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer &source)
{
    _containerSize   = source.getContainerSize();
    _uiParentEPos    = InvalidParentEPos;
    _storeP          = (UInt8 *) (const_cast<FieldContainer *>(&source));
    _storeP         -= getElemOff(Thread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source)
{
    _uiParentEPos    = InvalidParentEPos;

    if(source != NULL)
    {
        _containerSize = source->getContainerSize();
        _storeP          = (UInt8 *) (const_cast<FieldContainer *>(source));
        _storeP         -= getElemOff(Thread::getAspect());
    }
    else
    {
        _containerSize = 0;
        _storeP          = NULL;
    }

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source,
                                             const UInt16         uiSize,
                                             const UInt16         uiParentEPos)
{
    _uiParentEPos  = uiParentEPos;
    _containerSize = uiSize;

    if(source != NULL)
    {
        _storeP  = (UInt8 *) (const_cast<FieldContainer *>(source));
        _storeP -= getElemOff(Thread::getAspect());
    }
    else
    {
        _storeP  = NULL;
    }

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void FieldContainerPtrBase::executeSync(UInt32    uiFromAspect,
                                        UInt32    uiToAspect,
                                        BitVector whichField)
{
    FieldContainer *pTo = ((FieldContainer *) getElemP(uiToAspect));
    
    pTo->executeSync(*((FieldContainer *) getElemP(uiFromAspect)), whichField);
    pTo->changed(whichField, FieldContainer::Sync);
}

/*-------------------------------------------------------------------------*/
/*                         Get Memory Locations                            */

Int32 *FieldContainerPtrBase::getRefCountP(void)
{
    return (Int32 *) (_storeP - sizeof(Int32) - sizeof(UInt32));
}

Int32 *FieldContainerPtrBase::getRefCountP(void) const
{
    return (Int32 *) (_storeP - sizeof(Int32) - sizeof(UInt32));
}

UInt32 *FieldContainerPtrBase::getIdP(void)
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

UInt32 *FieldContainerPtrBase::getIdP(void) const
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum)
{
    return (_storeP + (_containerSize * uiElemNum));
}

UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum) const
{
    return (_storeP + (_containerSize * uiElemNum));
}

UInt8 *FieldContainerPtrBase::getFirstElemP(void)
{
    return _storeP;
}

UInt8 *FieldContainerPtrBase::getFirstElemP(void) const
{
    return _storeP;
}

/*-------------------------------------------------------------------------*/
/*                         Get Memory Offsets                              */

Int32  FieldContainerPtrBase::getRefCountOff(void) const
{
    return - (sizeof(Int32) + sizeof(UInt32));
}

Int32  FieldContainerPtrBase::getIdOff(void) const
{
    return - sizeof(UInt32);
}

Int32  FieldContainerPtrBase::getFirstElemOff(void) const
{
    return 0;
}

Int32  FieldContainerPtrBase::getElemOff(UInt32 uiElemNum) const
{
    return (_containerSize * uiElemNum);
}

/*-------------------------------------------------------------------------*/
/*                           Reference Counting                            */

void FieldContainerPtrBase::addRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())++;

    _pRefCountLock->release(_storeP);

    Thread::getCurrentChangeList()->addAddRefd(
        *(static_cast<const FieldContainerPtr *>(this)));
}

void FieldContainerPtrBase::subRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())--;

    if((*getRefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        deleteContainers();
    }
    else
    {
        _pRefCountLock->release(_storeP);

        Thread::getCurrentChangeList()->addSubRefd(
            *(static_cast<const FieldContainerPtr *>(this)));
    }
}

void FieldContainerPtrBase::deleteContainers(void) const
{
    Thread::getCurrentChangeList()->addDestroyed(*getIdP());
    
    FieldContainerFactory::the()->unregisterFieldContainer(
        *((const FieldContainerPtr *) this));
    
    UInt8 *pTmp = getFirstElemP();
    
    ((FieldContainer *) pTmp)->onDestroy();
    
#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
    fprintf(stderr, "GV_MEM_FC_DBG : (%u|%lf|%I64d) d (%p|%s|%u)\n", 
            Thread::getAspect(),
            getSystemTime(), 
            getPerfCounter(),
            pTmp,
            ((FieldContainer *) pTmp)->getType().getCName(),
            ((FieldContainer *) pTmp)->getType().getId());
#endif
    
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        ((FieldContainer *) pTmp)->~FieldContainer();
        
        pTmp += _containerSize;
    }
    
    operator delete(_storeP + getRefCountOff());
}

#if 0
void FieldContainerPtrBase::subRefUntraced(void) const
{
    if((*getRefCountP()) <= 0)
    {
        UInt8 *pTmp = getFirstElemP();

        ((FieldContainer *) pTmp)->onDestroy();

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
        fprintf(stderr, "GV_MEM_FC_DBG : (%u|%lf|%I64d) d (%p|%s|%u)\n", 
                Thread::getAspect(),
                getSystemTime(), 
                getPerfCounter(),
                pTmp,
                ((FieldContainer *) pTmp)->getType().getCName(),
                ((FieldContainer *) pTmp)->getType().getId());
#endif

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ((FieldContainer *) pTmp)->~FieldContainer();

            pTmp += _containerSize;
        }

        operator delete(_storeP + getRefCountOff());
    }
}
#endif




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::FieldContainerPtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerPtr::FieldContainerPtr(void) :
    Inherited()
{
}

FieldContainerPtr::FieldContainerPtr(const FieldContainerPtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerPtr::~FieldContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

FieldContainer *FieldContainerPtr::operator->(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

FieldContainer *FieldContainerPtr::operator->(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

FieldContainer &FieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

FieldContainer &FieldContainerPtr::operator *(void) const
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

FieldContainer *FieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

FieldContainer *FieldContainerPtr::getCPtr(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void FieldContainerPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                             MT Edit                                     */

void FieldContainerPtr::beginEdit(BitVector OSG_CHECK_ARG(whichField)) const
{
}

void FieldContainerPtr::endEdit(BitVector whichField) const
{
    endEditNotChanged(whichField);
    changed(whichField);
}

void FieldContainerPtr::changed(BitVector whichField) const
{
    (*this)->changed(whichField, FieldContainer::External);
}

void FieldContainerPtr::endEditNotChanged(BitVector whichField) const
{
    Thread::getCurrentChangeList()->addChanged(*this, whichField);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerPtr::FieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

FieldContainerPtr::FieldContainerPtr(const FieldContainer *source) :
    Inherited(source)
{
}


FieldContainerPtr::FieldContainerPtr(const FieldContainer *source,
                                     const UInt16          uiSize,
                                     const UInt16          uiParentEPos) :
    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::ConstFieldContainerPtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ConstFieldContainerPtr::ConstFieldContainerPtr(void) :
    Inherited()
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(
    const FieldContainerPtr &source) :
    Inherited(source)
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(
    const ConstFieldContainerPtr &source):
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ConstFieldContainerPtr::~ConstFieldContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Container Access                              */

const FieldContainer *ConstFieldContainerPtr::operator->(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

const FieldContainer *ConstFieldContainerPtr::operator->(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
}

const FieldContainer &ConstFieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

const FieldContainer &ConstFieldContainerPtr::operator *(void) const
{
    return *((const FieldContainer *) (getElemP(Thread::getAspect())));
}

const FieldContainer *ConstFieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

const FieldContainer *ConstFieldContainerPtr::getCPtr(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void ConstFieldContainerPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

void ConstFieldContainerPtr::operator =(const ConstFieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainer *source) :
    Inherited(source)
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(
    const FieldContainer *source,
    const UInt16          uiSize,
    const UInt16          uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::NullFieldContainerPtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

NullFieldContainerPtr::NullFieldContainerPtr(void) :
    FieldContainerPtr()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

NullFieldContainerPtr::~NullFieldContainerPtr(void)
{
}
