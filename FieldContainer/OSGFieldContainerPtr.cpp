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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGFieldContainerPtr.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAttachment.h"
#include "OSGThreadManager.h"
#include "OSGThread.h"
#include "OSGLog.h"
#include "OSGLock.h"
#include "OSGChangeList.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const UInt16 FieldContainerPtr::InvalidParentFPos = 0xFFFF;

char FieldContainerPtr::cvsid[] = "@(#)$Id: $";

LockPool *FieldContainerPtr::_refCountLockP = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Bool FieldContainerPtr::initialize(int , char **)
{
    Bool           returnValue = false;
    ThreadManager *pManager    = ThreadManager::the();

    SINFO << "FieldContainerPtr init" << endl;

    if(pManager != NULL)
    {
        _refCountLockP = pManager->getLockPool("FCPTRRefCountLockPool");

        if(_refCountLockP != NULL)
            returnValue = true;
    }

    return returnValue;
}

Bool FieldContainerPtr::terminate(void)
{
    ThreadManager *pManager = ThreadManager::the();

    SINFO << "FieldContainerPtr terminate" << endl;

    if(pManager == NULL)
        return false;
    
    pManager->freeLockPool(_refCountLockP);

    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

FieldContainerPtr::FieldContainerPtr(void) :
    _containerSize(0),
    _parentFPos(InvalidParentFPos),
	_storeP(NULL)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typename = NULL;
#endif
}

/** \brief Copy Constructor
 */

FieldContainerPtr::FieldContainerPtr(
    const FieldContainerPtr &source) :
    _containerSize(source._containerSize),
    _parentFPos   (source._parentFPos),
	_storeP       (source._storeP)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Destructor
 */

FieldContainerPtr::~FieldContainerPtr(void)
{
}

/*----------------------------- parent field pos -----------------------*/

void FieldContainerPtr::setParentFieldPos(UInt16 parentFPos)
{
    _parentFPos = parentFPos;
}

UInt16 FieldContainerPtr::getParentFieldPos(void) const
{
    return _parentFPos;
}

/*---------------------------- container id ---------------------------------*/

UInt32 FieldContainerPtr::getContainerId(void) const
{
    return (*getIdP());
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

const FieldContainer *FieldContainerPtr::operator->(void) const
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

const FieldContainer &FieldContainerPtr::operator *(void) const
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

/** \brief get FieldContainer * 
 */

FieldContainer *FieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

/** \brief get const FieldContainer *
 */

const FieldContainer *FieldContainerPtr::getCPtr(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
/** \brief FieldContainer * cast operator
 */

FieldContainerPtr::operator FieldContainer *(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

FieldContainerPtr &FieldContainerPtr::operator = (
    const FieldContainerPtr &source)
{
	if (this == &source)
		return *this;

    _containerSize = source._containerSize;
    _parentFPos    = source._parentFPos;
    _storeP        = source._storeP;    

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif

    return *this;
}


/*-------------------------- comparison -----------------------------------*/

/** \brief less than
 */

Bool FieldContainerPtr::operator < (
    const FieldContainerPtr &other) const
{
    return _storeP < other._storeP;
}

/** \brief equal
 */

Bool FieldContainerPtr::operator == (
    const FieldContainerPtr &other) const
{
    return _storeP == other._storeP;
}

/** \brief not equal
 */

Bool FieldContainerPtr::operator != (
    const FieldContainerPtr &other) const
{
	return ! (*this == other);
}

/** \brief not
 */

Bool FieldContainerPtr::operator !(void) const
{
    return _storeP == NULL;
}

/*------------------------------ dump ---------------------------------------*/

/** Dump pointer contents to stderr, should be changed to use a log stream
 */

void FieldContainerPtr::dump(void) const
{
    if(_storeP != NULL)
    {
        PDEBUG << "FC Dump : %d " << (*(getIdP())) << endl;

        dumpContent();
    }
    else
    {
        PDEBUG << "FC Dump : (NULL)" << endl;
    }
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#ifdef OSG_DEBUG_TYPED_FCPTR
void FieldContainerPtr::updateTypedStore(void)
{
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
}
#endif

void FieldContainerPtr::executeSync(UInt32    fromAspect,
                                    UInt32    toAspect, 
                                    BitVector whichField)
{
    Bool syncHappened = false;

    fprintf(stderr, "Do Sync %d %d %08x\n", fromAspect, toAspect, whichField);

    FieldContainer *pFrom   = ((FieldContainer *)
                                  (_storeP + (_containerSize  *  fromAspect)));

    FieldContainer *pTo     = ((FieldContainer *)
                                  (_storeP + (_containerSize  *  toAspect)));

    BitVector currentField = FieldBits::Field0;

    for(UInt32 i = 0; i < pTo->getType().getNumFieldDescriptions(); i++)
    {
        if(currentField & whichField)
        {
            const FieldDescription *pDesc = 
                pTo->getType().getFieldDescription(i);

            Field *pFromField;
            Field *pToField;
            
            if(pDesc != NULL)
            {
                pFromField = pDesc->getField(*pFrom);
                pToField   = pDesc->getField(*pTo);
                
                pToField->doSync(pFromField);

                syncHappened = true;
                
                fprintf(stderr, "%s %s\n",
                        pFromField->getType().getName(),
                        pToField->getType().getName());
            }

            pFrom->getType().print();
        }

        currentField = currentField << 1;
    }   

    if(syncHappened == true)
    {
        pTo->changed(whichField, FieldContainer::Sync);
    }
}

Int32 *FieldContainerPtr::getRefCountP(void)
{
    return (Int32 *) (_storeP -  
                         sizeof(Int32)  -
                         sizeof(UInt32));
}

const Int32 *FieldContainerPtr::getRefCountP(void) const
{
    return (Int32 *) (_storeP -  
                         sizeof(Int32)  -
                         sizeof(UInt32));
}

UInt32 *FieldContainerPtr::getIdP(void)
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

const UInt32 *FieldContainerPtr::getIdP(void) const
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

UInt8 *FieldContainerPtr::getElemP(UInt32 elemNum)
{
    return (_storeP + (_containerSize * elemNum));
}

const UInt8 *FieldContainerPtr::getElemP(UInt32 elemNum) const
{
    return (_storeP + (_containerSize * elemNum));
}

UInt8 *FieldContainerPtr::getFirstElemP(void)
{
    return _storeP;
}

const UInt8 *FieldContainerPtr::getFirstElemP(void) const
{
    return _storeP;
}

Int32  FieldContainerPtr::getRefCountOff(void) const
{
    return - sizeof(Int32) - sizeof(UInt32);
}

Int32  FieldContainerPtr::getIdOff(void) const
{
    return - sizeof(UInt32);
}

Int32  FieldContainerPtr::getFirstElemOff(void) const
{
    return 0;
}

Int32  FieldContainerPtr::getElemOff(UInt32 elemNum) const
{
    return (_containerSize * elemNum);
}

void FieldContainerPtr::addRef(void)
{
    _refCountLockP->aquire(_storeP);

    (*getRefCountP())++;
    
    _refCountLockP->release(_storeP);

    Thread::getCurrentChangeList()->addAddRefd(*this);
}

void FieldContainerPtr::subRef(void)
{
    _refCountLockP->aquire(_storeP);

    (*getRefCountP())--;

    _refCountLockP->release(_storeP);

    Thread::getCurrentChangeList()->addSubRefd(*this);

    if((*getRefCountP()) <= 0)
    {
        UInt8 *pTmp = getFirstElemP();

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ( (FieldContainer *) pTmp)->~FieldContainer();
            
            pTmp += _containerSize;
        }

        operator delete(_storeP + getRefCountOff());

        _storeP        = NULL;        
        _containerSize = 0;   
        _parentFPos    = InvalidParentFPos;
    }
}

void FieldContainerPtr::beginEdit(BitVector whichField)
{
}

void FieldContainerPtr::endEdit(BitVector whichField)
{
    endEditNotChanged(whichField);
    changed(whichField);
}

void FieldContainerPtr::changed(BitVector whichField)
{
    (*this)->changed(whichField, FieldContainer::External);
}

void FieldContainerPtr::endEditNotChanged(BitVector whichField)
{
    Thread::getCurrentChangeList()->addChanged(*this, whichField);
}

void FieldContainerPtr::dumpContent(void) const
{
    UInt8 *pTmp = _storeP + getRefCountOff();    

    if(_storeP != NULL)
    {
        PDEBUG << "\tRefCount : " <<  (*((Int32 *) pTmp)) << endl;

        pTmp += sizeof(Int32);
        
        PDEBUG << "\tId : " << (*((UInt32 *) pTmp)) << endl;
        
        pTmp += sizeof(UInt32);
        
        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            PDEBUG << "\tDumpAspect : " << i << endl;
            ((FieldContainer *) pTmp)->dump();
            
            pTmp += _containerSize;
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give fieldcontainer.
 */

FieldContainerPtr::FieldContainerPtr(const FieldContainer &source)
{
    _containerSize = source.getSize();
    _parentFPos    = InvalidParentFPos;
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Write FC to the given stream
 */

ostream &OSG::operator <<(ostream &outStream,
                          const FieldContainerPtr &fcPtr)
{
	if(fcPtr == NullFC)
    {
		outStream << hex << "0x" << &fcPtr << dec << ":NullFC";
    }
	else
    {
		outStream << hex << "0x"  << &fcPtr 
                  << dec << " : " <<  fcPtr->getType().getName() 
                  << "Ptr(0x"     << hex << (int) fcPtr._storeP << dec << ")";
    }

	return outStream;
}


/** \fn const char *NodePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef NodePtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char NodePtr::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

NodePtr::NodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

NodePtr::NodePtr(const NodePtr &source) :
    Inherited(source)
{
}

/** \brief Constructor from CNodePtr
 */

NodePtr::NodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

NodePtr::~NodePtr(void)
{
}

/*------------------------------- core access -------------------------------*/

NodeCore *NodePtr::getCore(void)
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

Node *NodePtr::operator->(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

const Node *NodePtr::operator->(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

Node &NodePtr::operator *(void)
{
    return *((Node *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

const Node &NodePtr::operator *(void) const
{
    return *((Node *) getElemP(Thread::getAspect()));
}

Node *NodePtr::getCPtr(void)
{
    return (Node *) getElemP(Thread::getAspect());   
}

const Node *NodePtr::getCPtr(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
/** \brief Node * cast operator
 */

NodePtr::operator Node *(void)
{
    return (Node *) getElemP(Thread::getAspect());
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from CNodePtr
 */

NodePtr &NodePtr::operator = (const CNodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

/** \brief assignment
 */

NodePtr &NodePtr::operator = (const NodePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

void NodePtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "Node Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "Node Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

NodePtr::NodePtr(const Node &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = InvalidParentFPos;
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());
}





/** \fn const char *CNodePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef CNodePtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char CNodePtr::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

CNodePtr::CNodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

CNodePtr::CNodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

/** \brief Constructor from NodePtr
 */

CNodePtr::CNodePtr(const NodePtr &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

CNodePtr::~CNodePtr(void)
{
}

/*-------------------------------- node access ------------------------------*/

Node *CNodePtr::getNode(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

NodeCore *CNodePtr::operator->(void)
{
    return
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/** \brief Const arrow operator
 */

const NodeCore *CNodePtr::operator->(void) const
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/** \brief Dereference operator
 */

NodeCore &CNodePtr::operator *(void)
{
    return *(
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

/** \brief Const dereference operator
 */

const NodeCore &CNodePtr::operator *(void) const
{
    return *(
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

NodeCore *CNodePtr::getCPtr(void)
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

const NodeCore *CNodePtr::getCPtr(void) const
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
/** \brief NodeCore * cast operator
 */

CNodePtr::operator NodeCore *(void)
{
    return (NodeCore *) 
        ((Node *) getElemP(Thread::getAspect()))->getCore();
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from NodePtr
 */

CNodePtr &CNodePtr::operator = (const NodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

/** \brief assignment
 */

CNodePtr &CNodePtr::operator = (const CNodePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

void CNodePtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "NodeC Dump\n" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "NodeC Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

CNodePtr::CNodePtr(const Node &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = InvalidParentFPos;
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());
}




/** \fn const char *NodeCorePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef NodeCorePtr::Inherited
 *  \brief Parent type
 */


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char NodeCorePtr::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

NodeCorePtr::NodeCorePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

NodeCorePtr::NodeCorePtr(const NodeCorePtr &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

NodeCorePtr::~NodeCorePtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

NodeCore *NodeCorePtr::operator->(void)
{
    return (NodeCore *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

const NodeCore *NodeCorePtr::operator->(void) const
{
    return (NodeCore *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

NodeCore &NodeCorePtr::operator *(void)
{
    return *((NodeCore *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

const NodeCore &NodeCorePtr::operator *(void) const
{
    return *((NodeCore *) getElemP(Thread::getAspect()));
}

NodeCore *NodeCorePtr::getCPtr(void)
{
    return (NodeCore *) getElemP(Thread::getAspect());
}

const NodeCore *NodeCorePtr::getCPtr(void) const
{
    return (NodeCore *) getElemP(Thread::getAspect());
}

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
/** \brief Node * cast operator
 */

NodeCorePtr::operator NodeCore *(void)
{
    return (NodeCore *) getElemP(Thread::getAspect());
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

NodeCorePtr &NodeCorePtr::operator = (const NodeCorePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

void NodeCorePtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "NodeCore Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "NodeCore Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node core.
 */

NodeCorePtr::NodeCorePtr(const NodeCore &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = InvalidParentFPos;
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());
}




/** \fn const char *AttachmentPtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef AttachmentPtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char AttachmentPtr::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

AttachmentPtr::AttachmentPtr(void) :
	Inherited()
{
}

/** \brief Copy Constructor
 */

AttachmentPtr::AttachmentPtr(const AttachmentPtr &source) :
	Inherited(source)
{
}

/** \brief Destructor
 */

AttachmentPtr::~AttachmentPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

Attachment *AttachmentPtr::operator->(void)
{
    return (Attachment *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

const Attachment *AttachmentPtr::operator->(void) const
{
    return (Attachment *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

Attachment &AttachmentPtr::operator *(void)
{
    return *((Attachment *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

const Attachment &AttachmentPtr::operator *(void) const
{
    return *((Attachment *) getElemP(Thread::getAspect()));
}

Attachment *AttachmentPtr::getCPtr(void)
{
    return (Attachment *) getElemP(Thread::getAspect());
}

const Attachment *AttachmentPtr::getCPtr(void) const
{
    return (Attachment *) getElemP(Thread::getAspect());
}

#ifdef OSG_FCPTR_HAS_CAST_OPERATOR
/** \brief Attachment * cast operator
 */

AttachmentPtr::operator Attachment *(void)
{
    return (Attachment *) getElemP(Thread::getAspect());
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

AttachmentPtr& AttachmentPtr::operator =(const AttachmentPtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

void AttachmentPtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "Attachment Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "Attachment Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

AttachmentPtr::AttachmentPtr(const Attachment &source)
{
    _containerSize = source.getSize();
    _parentFPos    = InvalidParentFPos;
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());
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

/** \brief NULL field container pointer
 */

OSG_DLLEXPORT const FieldContainerPtr   OSG::NullFC;

/** \brief NULL node pointer
 */

OSG_DLLEXPORT const NodePtr             OSG::NullNode;

/** \brief NULL node core pointer
 */

OSG_DLLEXPORT const NodeCorePtr         OSG::NullNodeCore;

/** \brief NULL attachment pointer
 */

OSG_DLLEXPORT const AttachmentPtr       OSG::NullAttachment;

