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
#include "OSGLog.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGFieldContainerPtr::getClassname(void)
 *  \brief Classname
 */

/** \var OSGUInt32 OSGFieldContainerPtr::_containerSize
 *  \brief Size of the container referenced by the pointer
 */

/** \var OSGUInt8 OSGFieldContainerPtr::_storeP
 *  \brief Generic pointer to the actuall memory location of the container
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSGUInt16 OSGFieldContainerPtr::OSGInvalidParentFPos = 0xFFFF;

char OSGFieldContainerPtr::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGBool OSGFieldContainerPtr::initialize(int , char **)
{
    SINFO << "OSGFieldContainerPtr init" << endl;
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

OSGFieldContainerPtr::OSGFieldContainerPtr(void) :
    _containerSize(0),
    _parentFPos(OSGInvalidParentFPos),
	_storeP(NULL)
{
}

/** \brief Copy Constructor
 */

OSGFieldContainerPtr::OSGFieldContainerPtr(
    const OSGFieldContainerPtr &source) :
    _containerSize(source._containerSize),
    _parentFPos   (source._parentFPos),
	_storeP       (source._storeP)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((OSGFieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Construct a pointer from a give node.
 */

OSGFieldContainerPtr::OSGFieldContainerPtr(const OSGFieldContainer &source)
{
    _containerSize = source.getSize();
    _parentFPos    = OSGInvalidParentFPos;
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((OSGFieldContainer *) _storeP)->getType().getName();
#endif
}

/** \brief Destructor
 */

OSGFieldContainerPtr::~OSGFieldContainerPtr(void)
{
}

void OSGFieldContainerPtr::addRef(void)
{
    (*getRefCountP())++;
    
    OSGThread::getCurrentChangeList()->addAddRefd(*this);
}

void OSGFieldContainerPtr::subRef(void)
{
    OSGUInt8 *pTmp = getFirstElemP();

    (*getRefCountP())--;

    OSGThread::getCurrentChangeList()->addSubRefd(*this);

    if((*getRefCountP()) <= 0)
    {
        for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
        {
            ( (OSGFieldContainer *) pTmp)->~OSGFieldContainer();
            
            pTmp += _containerSize;
        }

        operator delete(_storeP + getRefCountOff());

        _storeP        = NULL;        
        _containerSize = 0;   
        _parentFPos    = OSGInvalidParentFPos;
    }
}

void OSGFieldContainerPtr::beginEdit(OSGBitVector whichField)
{
}

void OSGFieldContainerPtr::endEdit(OSGBitVector whichField)
{
    endEditNotChanged(whichField);
    changed(whichField);
}

void OSGFieldContainerPtr::changed(OSGBitVector whichField)
{
    (*this)->changed(whichField, OSGFieldContainer::OSGExternal);
}

void OSGFieldContainerPtr::endEditNotChanged(OSGBitVector whichField)
{
    OSGThread::getCurrentChangeList()->addChanged(*this, whichField);
}

OSGUInt32 OSGFieldContainerPtr::getContainerId(void)
{
    return (*getIdP());
}

/*----------------------------- parent field pos -----------------------*/

void OSGFieldContainerPtr::setParentFieldPos(OSGUInt16 parentFPos)
{
    _parentFPos = parentFPos;
}

OSGUInt16 OSGFieldContainerPtr::getParentFieldPos(void)
{
    return _parentFPos;
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

OSGFieldContainer *OSGFieldContainerPtr::operator->(void)
{
    return (OSGFieldContainer *) (getElemP(OSGThread::getAspect()));
}

/** \brief Const arrow operator
 */

const OSGFieldContainer *OSGFieldContainerPtr::operator->(void) const
{
    return (OSGFieldContainer *) (getElemP(OSGThread::getAspect()));
}

/** \brief Dereference operator
 */

OSGFieldContainer &OSGFieldContainerPtr::operator *(void)
{
    return *((OSGFieldContainer *) (getElemP(OSGThread::getAspect())));
}

/** \brief Const dereference operator
 */

const OSGFieldContainer &OSGFieldContainerPtr::operator *(void) const
{
    return *((OSGFieldContainer *) (getElemP(OSGThread::getAspect())));
}

/** \brief OSGFieldContainer * cast operator
 */

OSGFieldContainerPtr::operator OSGFieldContainer *(void)
{
    return (OSGFieldContainer *) (getElemP(OSGThread::getAspect()));
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGFieldContainerPtr &OSGFieldContainerPtr::operator = (
    const OSGFieldContainerPtr &source)
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
        _typename = ((OSGFieldContainer *) _storeP)->getType().getName();
#endif

    return *this;
}


/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

OSGBool OSGFieldContainerPtr::operator < (
    const OSGFieldContainerPtr &other) const
{
    return _storeP < other._storeP;
}

/** \brief equal
 */

OSGBool OSGFieldContainerPtr::operator == (
    const OSGFieldContainerPtr &other) const
{
    return _storeP == other._storeP;
}

/** \brief not equal
 */

OSGBool OSGFieldContainerPtr::operator != (
    const OSGFieldContainerPtr &other) const
{
	return ! (*this == other);
}

OSGBool OSGFieldContainerPtr::operator !(void) const
{
    return _storeP == NULL;
}

/*------------------------------ dump ---------------------------------------*/

/** Dump pointer contents to stderr, should be changed to use a log stream
 */

void OSGFieldContainerPtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "FC Dump : %d " << (*(getIdP())) << endl;

        dumpContent();
    }
    else
    {
        SDEBUG << "FC Dump : (NULL)" << endl;
    }
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#ifdef OSG_DEBUG_TYPED_FCPTR
void OSGFieldContainerPtr::updateTypedStore(void)
{
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((OSGFieldContainer *) _storeP)->getType().getName();
}
#endif

void OSGFieldContainerPtr::executeSync(OSGUInt32    fromAspect,
                                       OSGUInt32    toAspect, 
                                       OSGBitVector whichField)
{
    OSGBool syncHappened = false;

    fprintf(stderr, "Do Sync %d %d %08x\n", fromAspect, toAspect, whichField);

    OSGFieldContainer *pFrom   = ((OSGFieldContainer *)
                                  (_storeP + (_containerSize  *  fromAspect)));

    OSGFieldContainer *pTo     = ((OSGFieldContainer *)
                                  (_storeP + (_containerSize  *  toAspect)));

    OSGBitVector currentField = OSGFieldBits::OSGField0;

    for(OSGUInt32 i = 0; i < pTo->getType().getNumFieldDescriptions(); i++)
    {
        if(currentField & whichField)
        {
            OSGFieldDescription *pDesc = pTo->getType().getFieldDescription(i);

            OSGField *pFromField;
            OSGField *pToField;
            
            if(pDesc != NULL)
            {
                pFromField = pDesc->getFieldValue(*pFrom);
                pToField   = pDesc->getFieldValue(*pTo);
                
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
        pTo->changed(whichField, OSGFieldContainer::OSGSync);
    }
}


OSGInt32  OSGFieldContainerPtr::getRefCountOff(void) const
{
    return - sizeof(OSGInt32) - sizeof(OSGUInt32);
}

OSGInt32  OSGFieldContainerPtr::getIdOff(void) const
{
    return - sizeof(OSGUInt32);
}

OSGInt32  OSGFieldContainerPtr::getElemOff(OSGUInt32 elemNum) const
{
    return (_containerSize * elemNum);
}

OSGInt32 *OSGFieldContainerPtr::getRefCountP(void)
{
    return (OSGInt32 *) (_storeP -  
                         sizeof(OSGInt32)  -
                         sizeof(OSGUInt32));
}

const OSGInt32 *OSGFieldContainerPtr::getRefCountP(void) const
{
    return (OSGInt32 *) (_storeP -  
                         sizeof(OSGInt32)  -
                         sizeof(OSGUInt32));
}

OSGUInt32 *OSGFieldContainerPtr::getIdP(void)
{
    return (OSGUInt32 *) (_storeP - sizeof(OSGUInt32));
}

const OSGUInt32 *OSGFieldContainerPtr::getIdP(void) const
{
    return (OSGUInt32 *) (_storeP - sizeof(OSGUInt32));
}

OSGUInt8 *OSGFieldContainerPtr::getElemP(OSGUInt32 elemNum)
{
    return (_storeP + (_containerSize * elemNum));
}

const OSGUInt8 *OSGFieldContainerPtr::getElemP(OSGUInt32 elemNum) const
{
    return (_storeP + (_containerSize * elemNum));
}

OSGUInt8 *OSGFieldContainerPtr::getFirstElemP(void)
{
    return _storeP;
}

const OSGUInt8 *OSGFieldContainerPtr::getFirstElemP(void) const
{
    return _storeP;
}

void OSGFieldContainerPtr::dumpContent(void) const
{
    OSGUInt8 *pTmp = _storeP + getRefCountOff();    

    if(_storeP != NULL)
    {
        SDEBUG << "\tRefCount : " <<  (*((OSGInt32 *) pTmp)) << endl;

        pTmp += sizeof(OSGInt32);
        
        SDEBUG << "\tId : " << (*((OSGUInt32 *) pTmp)) << endl;
        
        pTmp += sizeof(OSGUInt32);
        
        for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
        {
            SDEBUG << "\tDumpAspect : " << i << endl;
            ((OSGFieldContainer *) pTmp)->dump();
            
            pTmp += _containerSize;
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Write FC to the given stream
 */

ostream &OSG::operator <<(ostream &outStream,
                          const OSGFieldContainerPtr &fcPtr)
{
	if(fcPtr == OSGNullFC)
    {
		outStream << hex << "0x" << &fcPtr << dec << ":OSGNullFC";
    }
	else
    {
		outStream << hex << "0x"  << &fcPtr 
                  << dec << " : " <<  fcPtr->getType().getName() 
                  << "Ptr(0x"     << hex << (int) fcPtr._storeP << dec << ")";
    }

	return outStream;
}


/** \fn const char *OSGNodePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGNodePtr::Inherited
 *  \brief Parent type
 */

/** \typedef OSGNode OSGNodePtr::OSGObjectType
 *  \brief Stored container type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGNodePtr::cvsid[] = "@(#)$Id: $";

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

OSGNodePtr::OSGNodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

OSGNodePtr::OSGNodePtr(const OSGNodePtr &source) :
    Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Constructor from OSGCNodePtr
 */

OSGNodePtr::OSGNodePtr(const OSGCNodePtr &source) :
    Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Construct a pointer from a give node.
 */

OSGNodePtr::OSGNodePtr(const OSGNode &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = OSGInvalidParentFPos;
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Destructor
 */

OSGNodePtr::~OSGNodePtr(void)
{
}

/*------------------------------- core access -------------------------------*/

OSGNodeCore *OSGNodePtr::getCore(void)
{
    return (OSGNodeCore *) 
        ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore();
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

OSGNode *OSGNodePtr::operator->(void)
{
    return (OSGNode *) getElemP(OSGThread::getAspect());
}

/** \brief Const arrow operator
 */

const OSGNode *OSGNodePtr::operator->(void) const
{
    return (OSGNode *) getElemP(OSGThread::getAspect());
}

/** \brief Dereference operator
 */

OSGNode &OSGNodePtr::operator *(void)
{
    return *((OSGNode *) getElemP(OSGThread::getAspect()));
}

/** \brief Const dereference operator
 */

const OSGNode &OSGNodePtr::operator *(void) const
{
    return *((OSGNode *) getElemP(OSGThread::getAspect()));
}

/** \brief OSGNode * cast operator
 */

OSGNodePtr::operator OSGNode *(void)
{
    return (OSGNode *) getElemP(OSGThread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from OSGCNodePtr
 */

OSGNodePtr &OSGNodePtr::operator = (const OSGCNodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

/** \brief assignment
 */

OSGNodePtr &OSGNodePtr::operator = (const OSGNodePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif

    return *this;
}

void OSGNodePtr::dump(void) const
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

#ifdef OSG_DEBUG_TYPED_FCPTR
void OSGNodePtr::updateTypedStore(void)
{
    _typedStoreP = (OSGNode *) _storeP;
    
    Inherited::updateTypedStore();
}
#endif

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/





/** \fn const char *OSGCNodePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGCNodePtr::Inherited
 *  \brief Parent type
 */

/** \typedef OSGNode OSGCNodePtr::OSGObjectType
 *  \brief Stored container type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGCNodePtr::cvsid[] = "@(#)$Id: $";

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

OSGCNodePtr::OSGCNodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

OSGCNodePtr::OSGCNodePtr(const OSGCNodePtr &source) :
    Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Constructor from OSGNodePtr
 */

OSGCNodePtr::OSGCNodePtr(const OSGNodePtr &source) :
    Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Construct a pointer from a give node.
 */

OSGCNodePtr::OSGCNodePtr(const OSGNode &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = OSGInvalidParentFPos;
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif
}

/** \brief Destructor
 */

OSGCNodePtr::~OSGCNodePtr(void)
{
}

/*-------------------------------- node access ------------------------------*/

OSGNode *OSGCNodePtr::getNode(void)
{
    return (OSGNode *) getElemP(OSGThread::getAspect());
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

OSGNodeCore *OSGCNodePtr::operator->(void)
{
    return (OSGNodeCore *) 
        ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore();
}

/** \brief Const arrow operator
 */

const OSGNodeCore *OSGCNodePtr::operator->(void) const
{
    return (OSGNodeCore *) 
        ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore();
}

/** \brief Dereference operator
 */

OSGNodeCore &OSGCNodePtr::operator *(void)
{
    return *((OSGNodeCore *) 
             ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore());
}

/** \brief Const dereference operator
 */

const OSGNodeCore &OSGCNodePtr::operator *(void) const
{
    return *((OSGNodeCore *) 
             ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore());
}

/** \brief OSGNodeCore * cast operator
 */

OSGCNodePtr::operator OSGNodeCore *(void)
{
    return (OSGNodeCore *) 
        ((OSGNode *) getElemP(OSGThread::getAspect()))->getCore();
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from OSGNodePtr
 */

OSGCNodePtr &OSGCNodePtr::operator = (const OSGNodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

/** \brief assignment
 */

OSGCNodePtr &OSGCNodePtr::operator = (const OSGCNodePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNode *) _storeP;
#endif

    return *this;
}

void OSGCNodePtr::dump(void) const
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

#ifdef OSG_DEBUG_TYPED_FCPTR
void OSGCNodePtr::updateTypedStore(void)
{
    _typedStoreP = (OSGNode *) _storeP;

    Inherited::updateTypedStore();
}
#endif

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/




/** \fn const char *OSGNodeCorePtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGNodeCorePtr::Inherited
 *  \brief Parent type
 */


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGNodeCorePtr::cvsid[] = "@(#)$Id: $";

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

OSGNodeCorePtr::OSGNodeCorePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

OSGNodeCorePtr::OSGNodeCorePtr(const OSGNodeCorePtr &source) :
    Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNodeCore *) _storeP;
#endif
}

/** \brief Construct a pointer from a give node core.
 */

OSGNodeCorePtr::OSGNodeCorePtr(const OSGNodeCore &source) :
    Inherited()
{
    _containerSize = source.getSize();
    _parentFPos    = OSGInvalidParentFPos;
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNodeCore *) _storeP;
#endif
}


/** \brief Destructor
 */

OSGNodeCorePtr::~OSGNodeCorePtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

OSGNodeCore *OSGNodeCorePtr::operator->(void)
{
    return (OSGNodeCore *) getElemP(OSGThread::getAspect());
}

/** \brief Const arrow operator
 */

const OSGNodeCore *OSGNodeCorePtr::operator->(void) const
{
    return (OSGNodeCore *) getElemP(OSGThread::getAspect());
}

/** \brief Dereference operator
 */

OSGNodeCore &OSGNodeCorePtr::operator *(void)
{
    return *((OSGNodeCore *) getElemP(OSGThread::getAspect()));
}

/** \brief Const dereference operator
 */

const OSGNodeCore &OSGNodeCorePtr::operator *(void) const
{
    return *((OSGNodeCore *) getElemP(OSGThread::getAspect()));
}

/** \brief OSGNode * cast operator
 */

OSGNodeCorePtr::operator OSGNodeCore *(void)
{
    return (OSGNodeCore *) getElemP(OSGThread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGNodeCorePtr &OSGNodeCorePtr::operator = (const OSGNodeCorePtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGNodeCore *) _storeP;
#endif

    return *this;
}

void OSGNodeCorePtr::dump(void) const
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

#ifdef OSG_DEBUG_TYPED_FCPTR
void OSGNodeCorePtr::updateTypedStore(void)
{
    _typedStoreP = (OSGNodeCore *) _storeP;

    Inherited::updateTypedStore();
}
#endif



/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \fn const char *OSGAttachmentPtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGAttachmentPtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGAttachmentPtr::cvsid[] = "@(#)$Id: $";

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

OSGAttachmentPtr::OSGAttachmentPtr(void) :
	Inherited()
{
}

/** \brief Copy Constructor
 */

OSGAttachmentPtr::OSGAttachmentPtr(const OSGAttachmentPtr &source) :
	Inherited(source)
{
}

OSGAttachmentPtr::OSGAttachmentPtr(const OSGAttachment &source)
{
    _containerSize = source.getSize();
    _parentFPos    = OSGInvalidParentFPos;
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());
}

/** \brief Destructor
 */

OSGAttachmentPtr::~OSGAttachmentPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

OSGAttachment *OSGAttachmentPtr::operator->(void)
{
    return (OSGAttachment *) getElemP(OSGThread::getAspect());
}

/** \brief Const arrow operator
 */

const OSGAttachment *OSGAttachmentPtr::operator->(void) const
{
    return (OSGAttachment *) getElemP(OSGThread::getAspect());
}

/** \brief Dereference operator
 */

OSGAttachment &OSGAttachmentPtr::operator *(void)
{
    return *((OSGAttachment *) getElemP(OSGThread::getAspect()));
}

/** \brief Const dereference operator
 */

const OSGAttachment &OSGAttachmentPtr::operator *(void) const
{
    return *((OSGAttachment *) getElemP(OSGThread::getAspect()));
}

/** \brief OSGAttachment * cast operator
 */

OSGAttachmentPtr::operator OSGAttachment *(void)
{
    return (OSGAttachment *) getElemP(OSGThread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGAttachmentPtr& OSGAttachmentPtr::operator =(const OSGAttachmentPtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

void OSGAttachmentPtr::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "OSGAttachment Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "OSGAttachment Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

const OSGFieldContainerPtr   OSG::OSGNullFC;

/** \brief NULL node pointer
 */

const OSGNodePtr             OSG::OSGNullNode;

/** \brief NULL node core pointer
 */

const OSGNodeCorePtr         OSG::OSGNullNodeCore;

/** \brief NULL attachment pointer
 */

const OSGAttachmentPtr         OSG::OSGNullAttachment;

