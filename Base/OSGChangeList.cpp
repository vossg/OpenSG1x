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

#include "OSGChangeList.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerFactory.h"
#include "OSGThread.h"
#include "OSGLog.h"
#include "OSGAspect.h"
#include "OSGThreadManager.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGChangeList::cvsid[] = "@(#)$Id: $";

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

OSGChangeList::OSGChangeList(void) :
    Inherited(),
    _bReadOnly(false),
    _aspectId(OSGThread::getAspect()),
    _listMode(OSGPublic),
    _changedFieldContainerV(),
    _addRefdFieldContainerV(),
    _subRefdFieldContainerV()
{
    OSGAspect::addList(this, _aspectId);
}


//CLASSNAME::CLASSNAME(const CLASSNAME &source) :
//	Inherited(source),
//	  // TODO: initialize members
//{
//}

/** \brief Destructor
 */

OSGChangeList::~OSGChangeList(void)
{
}

/*------------------------------ access -----------------------------------*/

OSGChangeList::changed_size_type OSGChangeList::sizeChanged(void)
{    
    return _changedFieldContainerV.size();
}

OSGChangeList::changed_const_iterator OSGChangeList::beginChanged(void) const
{
    return _changedFieldContainerV.begin();
}

OSGChangeList::changed_const_iterator OSGChangeList::endChanged(void) const
{
    return _changedFieldContainerV.end();
}

OSGChangeList::refd_size_type OSGChangeList::sizeAddRefd(void)
{
    return _addRefdFieldContainerV.size();
}

OSGChangeList::refd_const_iterator OSGChangeList::beginAddRefd(void) const
{
    return _addRefdFieldContainerV.begin();
}

OSGChangeList::refd_const_iterator OSGChangeList::endAddRefd(void) const
{
    return _addRefdFieldContainerV.end();
}

OSGChangeList::refd_size_type OSGChangeList::sizeSubRefd(void)
{
    return _subRefdFieldContainerV.size();
}

OSGChangeList::refd_const_iterator OSGChangeList::beginSubRefd(void) const
{
    return _subRefdFieldContainerV.begin();
}

OSGChangeList::refd_const_iterator OSGChangeList::endSubRefd(void) const
{
    return _subRefdFieldContainerV.end();
}

void OSGChangeList::addChanged(const OSGFieldContainerPtr &fieldP, 
                                     OSGBitVector          whichField)
{
    OSGChangeEntry tmpEntry;

    if(_bReadOnly == true)
        return;
    
    tmpEntry.first  = fieldP;
    tmpEntry.second = whichField;

    _changedFieldContainerV.push_back(tmpEntry);
}

void OSGChangeList::addAddRefd(const OSGFieldContainerPtr &fieldP)
{
    if(_bReadOnly == true)
        return;

    _addRefdFieldContainerV.push_back(fieldP);
}

void OSGChangeList::addSubRefd(const OSGFieldContainerPtr &fieldP)
{
    if(_bReadOnly == true)
        return;

    _subRefdFieldContainerV.push_back(fieldP);
}

void OSGChangeList::clearAll(void)
{
    _changedFieldContainerV.clear();
    _addRefdFieldContainerV.clear();
    _subRefdFieldContainerV.clear();
}

OSGBool OSGChangeList::merge(const OSGChangeList &list)
{
    OSGBool returnValue = true;
 
    _changedFieldContainerV.insert(_changedFieldContainerV.end(),
                                   list.beginChanged(), 
                                   list.endChanged());
    

    _addRefdFieldContainerV.insert(_addRefdFieldContainerV.end(),
                                   list.beginAddRefd(), 
                                   list.endAddRefd());
    

    _subRefdFieldContainerV.insert(_subRefdFieldContainerV.end(),
                                   list.beginSubRefd(), 
                                   list.endSubRefd());
    
   

    return returnValue;
}

void OSGChangeList::applyTo(OSGUInt32 aspectId)
{
    OSGUInt32 i;

    if(aspectId == _aspectId)
    {
        SWARNING << "Sync on the same aspects, ignored " << endl;
        return;
    }

    if(aspectId >= OSGThreadManager::getNumAspects())
    {
        SWARNING << "Invalid AspectId" << endl;
    }

    _bReadOnly = true;

    for(i = 0; i < _changedFieldContainerV.size(); i++)
    {
        _changedFieldContainerV[i].first.executeSync(
            _aspectId,
             aspectId,
            _changedFieldContainerV[i].second);
    }

    for(i = 0; i < _addRefdFieldContainerV.size(); i++)
    {
        osgAddRefCP(_addRefdFieldContainerV[i]);
    }

    for(i = 0; i < _subRefdFieldContainerV.size(); i++)
    {
        osgSubRefCP(_subRefdFieldContainerV[i]);
    }

    _changedFieldContainerV.clear();
    _addRefdFieldContainerV.clear();
    _subRefdFieldContainerV.clear();

    _bReadOnly = false;
}

void OSGChangeList::applyToCurrent(void)
{
    applyTo(OSGThread::getAspect());
}

void OSGChangeList::setAspect(OSGUInt32 aspectId)
{
    if(_changedFieldContainerV.size() != 0 ||
       _addRefdFieldContainerV.size() != 0 ||
       _subRefdFieldContainerV.size() != 0)
    {
        SWARNING << "Changing aspect on non empty changelist, all currrent "
                 << "entries will be lost" << endl;          
    }

    clearAll();

    OSGAspect::moveList(this, _aspectId, aspectId);

    _aspectId = aspectId;
}

void OSGChangeList::setReadOnly(OSGBool readOnly)
{
    _bReadOnly = readOnly;
}

void OSGChangeList::dump(void)
{
    OSGUInt32 i;

    fprintf(stderr, "CL: %d\n", _aspectId);
    fprintf(stderr, "CLChanged:\n");

    for(i = 0; i < _changedFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _changedFieldContainerV[i].first.getContainerId());
    }

    fprintf(stderr, "CLAdd:\n");
    for(i = 0; i < _addRefdFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _addRefdFieldContainerV[i].getContainerId());
    }

    fprintf(stderr, "CLSub:\n");
    for(i = 0; i < _subRefdFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _subRefdFieldContainerV[i].getContainerId());
    }
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

#if 0

/** \brief assignment
 */

OSGChangeList& OSGChangeList::operator = (const OSGChangeList &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

OSGBool OSGChangeList::operator < (const OSGChangeList &other) const
{
    return this < &other;
}


/** \brief equal
 */

OSGBool OSGChangeList::operator == (const OSGChangeList &other) const
{
}

/** \brief unequal
 */

OSGBool OSGChangeList::operator != (const OSGChangeList &other) const
{
	return ! (*this == other);
}

#endif

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

