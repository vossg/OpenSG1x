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

#define OSG_COMPILESYSTEMLIB

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

OSG_USING_NAMESPACE

const FieldContainerPtr OSG::NullFC;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt16    FieldContainerPtrBase::InvalidParentEPos = 0xFFFF;

      char      FieldContainerPtrBase::cvsid[]           = "@(#)$Id: $";

      LockPool *FieldContainerPtrBase::_pRefCountLock    = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Bool FieldContainerPtrBase::initialize(int &, char **)
{
    Bool           returnValue = false;
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

Bool FieldContainerPtrBase::terminate(void)
{
    ThreadManager *pManager = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase terminate" << endl;

    if(pManager == NULL)
        return false;

    subRefP(_pRefCountLock);

    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#ifdef OSG_DEBUG_TYPED_FCPTR
void FieldContainerPtrBase::updateTypedStore(void)
{
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
}
#endif

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

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
    _uiParentEPos   (source._uiParentEPos),
	_storeP         (source._storeP)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Construct a pointer from a give fieldcontainer.
 */

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
        _storeP          = (UInt8 *) (const_cast<FieldContainer *>(source));
        _storeP         -= getElemOff(Thread::getAspect());
    }
    else
    {
        _storeP          = NULL;
    }

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Destructor
 */

FieldContainerPtrBase::~FieldContainerPtrBase(void)
{
}


/*----------------------------- Sync --------------------------------------*/

void FieldContainerPtrBase::executeSync(UInt32    uiFromAspect,
                                        UInt32    uiToAspect, 
                                        BitVector whichField)
{
    ((FieldContainer *) getElemP(uiToAspect))->executeSync
        (*((FieldContainer *) getElemP(uiFromAspect)), whichField);
}

/*----------------------------- Mem ---------------------------------------*/

Int32 *FieldContainerPtrBase::getRefCountP(void)
{
    return (Int32 *) (_storeP -  
                         sizeof(Int32)  -
                         sizeof(UInt32));
}

Int32 *FieldContainerPtrBase::getRefCountP(void) const
{
    return (Int32 *) (_storeP -  
                         sizeof(Int32)  -
                         sizeof(UInt32));
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

/*----------------------------- Mem Off -----------------------------------*/

Int32  FieldContainerPtrBase::getRefCountOff(void) const
{
    return - sizeof(Int32) - sizeof(UInt32);
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

/*----------------------------- Mem Off -----------------------------------*/

void FieldContainerPtrBase::addRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())++;
    
    _pRefCountLock->release(_storeP);

    Thread::getCurrentChangeList()->addAddRefd(*((FieldContainerPtr *) this));
}

void FieldContainerPtrBase::subRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())--;

    _pRefCountLock->release(_storeP);

    subRefUnlocked();
}

void FieldContainerPtrBase::subRefUnlocked(void) const
{
    if((*getRefCountP()) <= 0)
    {
        Thread::getCurrentChangeList()->addDestroyed(*getIdP());

        UInt8 *pTmp = getFirstElemP();

        ((FieldContainer *) pTmp)->onDestroy();

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ((FieldContainer *) pTmp)->~FieldContainer();
            
            pTmp += _containerSize;
        }

        operator delete(_storeP + getRefCountOff());
    }
    else
    {
        Thread::getCurrentChangeList()->addSubRefd(*((FieldContainerPtr *) this));
    }
}

void FieldContainerPtrBase::subRefUntraced(void) const
{
    if((*getRefCountP()) <= 0)
    {
        UInt8 *pTmp = getFirstElemP();

        ((FieldContainer *) pTmp)->onDestroy();

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ((FieldContainer *) pTmp)->~FieldContainer();
            
            pTmp += _containerSize;
        }

        operator delete(_storeP + getRefCountOff());
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------------- parent field pos -----------------------*/

void FieldContainerPtrBase::setParentFieldPos(UInt16 uiParentEPos)
{
    _uiParentEPos = uiParentEPos;
}

UInt16 FieldContainerPtrBase::getParentFieldPos(void) const
{
    return _uiParentEPos;
}

/*---------------------------- container id ---------------------------------*/

UInt32 FieldContainerPtrBase::getFieldContainerId(void) const
{
    return (*getIdP());
}

UInt16  FieldContainerPtrBase::getContainerSize(void) const
{
	return _containerSize;
}

/*-------------------------- assignment -----------------------------------*/

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

/*-------------------------- comparison -----------------------------------*/

/** \brief less than
 */

Bool FieldContainerPtrBase::operator < (const FieldContainerPtrBase &other)const
{
    return _storeP < other._storeP;
}

/** \brief equal
 */

Bool FieldContainerPtrBase::operator ==(const FieldContainerPtrBase &other)const
{
    return _storeP == other._storeP;
}

/** \brief not equal
 */

Bool FieldContainerPtrBase::operator !=(const FieldContainerPtrBase &other)const
{
	return ! (*this == other);
}

/** \brief not
 */

Bool FieldContainerPtrBase::operator !(void) const
{
    return _storeP == NULL;
}



void FieldContainerPtrBase::dump(      UInt32     uiIndent, 
                                 const BitVector &bvFlags) const
{
    if(_storeP != NULL)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "FCPtr Dump :" << endl;

        uiIndent += 4;

        indentLog(uiIndent, PLOG);
        PLOG << "Id       : " << (*(getIdP()))   << endl;

        indentLog(uiIndent, PLOG);
        PLOG << "Storage  : " << UInt32(getFirstElemP()) << endl;

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


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const FieldContainerPtr FieldContainerPtr::NullPtr;

      char            FieldContainerPtr::cvsid[]       = "@(#)$Id: $";


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Construct a pointer from a give fieldcontainer.
 */

FieldContainerPtr::FieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

/** \brief Construct a pointer from a give fieldcontainer.
 */

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*----------------------------- Sync --------------------------------------*/

/*----------------------------- Mem ---------------------------------------*/

/*-------------------------------- Edit -----------------------------------*/

void FieldContainerPtr::beginEdit(BitVector whichField) const
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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

FieldContainerPtr::FieldContainerPtr(void) :
    Inherited()
{
}

FieldContainerPtr::FieldContainerPtr(const FieldContainerPtr &source) :
    Inherited(source)
{
}



/** \brief Destructor
 */

FieldContainerPtr::~FieldContainerPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

FieldContainer *FieldContainerPtr::operator->(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief Const arrow operator
 */

FieldContainer *FieldContainerPtr::operator->(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief Dereference operator
 */

FieldContainer &FieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

/** \brief Const dereference operator
 */

FieldContainer &FieldContainerPtr::operator *(void) const
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

/** \brief get OSGFieldContainer * 
 */

FieldContainer *FieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief get const OSGFieldContainer *
 */

FieldContainer *FieldContainerPtr::getCPtr(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/*-------------------------- assignment -----------------------------------*/

void FieldContainerPtr::operator =(const FieldContainerPtr &source)
{
	if (this == &source)
		return;

    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------- comparison -----------------------------------*/


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const ConstFieldContainerPtr ConstFieldContainerPtr::NullPtr;

      char                 ConstFieldContainerPtr::cvsid[]   = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give fieldcontainer.
 */

ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

/** \brief Construct a pointer from a give fieldcontainer.
 */

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


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

ConstFieldContainerPtr::ConstFieldContainerPtr(void) :
    Inherited()
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainerPtr &source) :
    Inherited(source)
{
}

ConstFieldContainerPtr::ConstFieldContainerPtr(const ConstFieldContainerPtr &source):
    Inherited(source)
{
}

/** \brief Destructor
 */

ConstFieldContainerPtr::~ConstFieldContainerPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

const FieldContainer *ConstFieldContainerPtr::operator->(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief Const arrow operator
 */

const FieldContainer *ConstFieldContainerPtr::operator->(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief Dereference operator
 */

const FieldContainer &ConstFieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

/** \brief Const dereference operator
 */

const FieldContainer &ConstFieldContainerPtr::operator *(void) const
{
    return *((const FieldContainer *) (getElemP(Thread::getAspect())));
}

/** \brief get OSGFieldContainer * 
 */

const FieldContainer *ConstFieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief get const OSGFieldContainer *
 */

const FieldContainer *ConstFieldContainerPtr::getCPtr(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
}

/*-------------------------- assignment -----------------------------------*/

void ConstFieldContainerPtr::operator =(const FieldContainerPtr &source)
{
	if (static_cast<Inherited *>(this) == 
        static_cast<const Inherited *> (&source))
    {
		return;
    }

    *(static_cast<Inherited *>(this)) = source;
}

void ConstFieldContainerPtr::operator =(const ConstFieldContainerPtr &source)
{
	if (this == &source)
		return;

    *(static_cast<Inherited *>(this)) = source;
}

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

