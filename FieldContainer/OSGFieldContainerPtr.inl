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

#include <OSGLog.h>
#include <OSGThread.h>

OSG_BEGIN_NAMESPACE

/** \fn const char *OSGFCPtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGFCPtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGBaseFieldContainerTypeT, class OSGFieldTypeT>
char OSGFCPtr<OSGBaseFieldContainerTypeT,
              OSGFieldTypeT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> 
const OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>
    OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::NullPtr;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::OSGFCPtr(void) :
	Inherited()
{
}

/** \brief Copy Constructor
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::OSGFCPtr(
    const OSGFCPtr &source) :
	Inherited(source)
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGObjectType *) _storeP;
#endif
}

/** \brief Construct a pointer from a give node.
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::OSGFCPtr(
    const OSGFieldContainerTypeT &source) :

    Inherited()
{
    _containerSize = sizeof(OSGFieldContainerTypeT);
    _storeP        = (OSGUInt8 *) &source;
    _storeP       -= getElemOff(OSGThread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGObjectType *) _storeP;
#endif
}

/** \brief Destructor
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::~OSGFCPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFieldContainerTypeT *OSGFCPtr<OSGBasePtrTypeT, 
                                 OSGFieldContainerTypeT>::operator ->(void)
{
    return (OSGFieldContainerTypeT *) getElemP(OSGThread::getAspect());
}

/** \brief Const arrow operator
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
const OSGFieldContainerTypeT *OSGFCPtr<OSGBasePtrTypeT, 
                                 OSGFieldContainerTypeT>::operator ->(
                                     void) const
{
    return (OSGFieldContainerTypeT *) getElemP(OSGThread::getAspect());
}

/** \brief Dereference operator
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFieldContainerTypeT &OSGFCPtr<OSGBasePtrTypeT, 
                                 OSGFieldContainerTypeT>::operator *(void)
{
    return *((OSGFieldContainerTypeT *) getElemP(OSGThread::getAspect()));
}

/** \brief Const dereference operator
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
const OSGFieldContainerTypeT &OSGFCPtr<OSGBasePtrTypeT, 
                                       OSGFieldContainerTypeT>::operator *(
                                           void) const
{
    return *((OSGFieldContainerTypeT *) getElemP(OSGThread::getAspect()));
}

/** \brief OSGFieldContainerTypeT * cast operator
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, 
         OSGFieldContainerTypeT>::operator OSGFieldContainerTypeT *(void)
{
    return (OSGFieldContainerTypeT *) getElemP(OSGThread::getAspect());
}


/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT> & 
    OSGFCPtr<OSGBasePtrTypeT, 
             OSGFieldContainerTypeT>::operator = (const OSGFCPtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

#ifdef OSG_DEBUG_TYPED_FCPTR
    _typedStoreP = (OSGObjectType *) _storeP;
#endif

    return *this;
}

template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
void OSGFCPtr<OSGBasePtrTypeT, 
              OSGFieldContainerTypeT>::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "CFC Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "CFC Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#ifdef OSG_DEBUG_TYPED_FCPTR
template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
void OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT>::updateTypedStore(void)
{
    _typedStoreP = (OSGObjectType *) _storeP;

    Inherited::updateTypedStore();
}
#endif

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

OSG_END_NAMESPACE

