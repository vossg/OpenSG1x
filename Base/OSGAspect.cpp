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

#include "OSGAspect.h"
#include "OSGThreadManager.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGAspect::cvsid[] = "@(#)$Id: $";

vector<OSGAspect *> OSGAspect::_aspectV(OSGThreadManager::getNumAspects());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

bool OSGAspect::init(void)
{
    for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
    {
        _aspectV[i] = new OSGAspect(i);
    }

    return true;
}

bool OSGAspect::exit(void)
{
    for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
    {
        delete _aspectV[i];
    }

    return true;
}

void OSGAspect::moveList(OSGChangeList *listP, 
                         OSGUInt32      fromAspect,
                         OSGUInt32      toAspect)
{
    if(listP != NULL)
    {
        _aspectV[toAspect]  ->_changeListS.insert(listP);
        _aspectV[fromAspect]->_changeListS.erase (listP);
    }

}

void OSGAspect::addList(OSGChangeList *listP,
                        OSGUInt32      aspectId)
{
    if(listP != NULL)
    {
        _aspectV[aspectId]->_changeListS.insert(listP);
    }
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

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

#if 0
CLASSNAME& CLASSNAME::operator = (const CLASSNAME &source)
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

OSGBool CLASSNAME::operator < (const CLASSNAME &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool CLASSNAME::operator == (const CLASSNAME &other) const
{
}

/** \brief unequal
 */

OSGBool CLASSNAME::operator != (const CLASSNAME &other) const
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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGAspect::OSGAspect(OSGUInt32 aspectId) :
    _aspectId(aspectId),
    _changeListS()
{
}

/** \brief Destructor
 */

OSGAspect::~OSGAspect(void)
{
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

