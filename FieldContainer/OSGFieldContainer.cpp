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


#include "OSGFieldContainer.h"
#include "OSGFieldDescription.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGChangeList.h"
#include "OSGFieldContainerPtr.h"

OSG_USING_OSG_NAMESPACE

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

OSGFieldContainerType OSGFieldContainer::_type ( "FieldContainer" );


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

OSGFieldContainer::OSGFieldContainer(void) :
    _shares(0)
{
}

/** \brief Copy Constructor
 */

OSGFieldContainer::OSGFieldContainer(const OSGFieldContainer &) :
    _shares(0)
                   
{
}

/** \brief Destructor
 */

OSGFieldContainer::~OSGFieldContainer(void)
{
}


OSGField *OSGFieldContainer::getField(const char *fieldName)
{
	OSGFieldDescription *desc = getType().findFieldDescription(fieldName);

	return desc ? desc->getFieldValue(*this) : 0;
}

void OSGFieldContainer::changed(OSGBitVector whichField, OSGChangeMode from)
{
    // fprintf(stderr, "FC Changed %d %d\n", whichField, fromSync);
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

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

void OSG::osgAddRefCP(OSGFieldContainerPtr &objectP)
{
    if(objectP != OSGNullFC)
        objectP.addRef();
}

/*! osgSubRefP */
void OSG::osgSubRefCP(OSGFieldContainerPtr &objectP)
{
    if(objectP != OSGNullFC)
        objectP.subRef();
}

/*! osgBeginEditCP */
void OSG::osgBeginEditCP(OSGFieldContainerPtr &objectP, 
                         OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.beginEdit(whichField);
}

/*! osgEndEditCP */
void OSG::osgEndEditCP(OSGFieldContainerPtr &objectP, 
                       OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.endEdit(whichField);
}

void OSG::osgChangedCP(OSGFieldContainerPtr &objectP, 
                       OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.changed(whichField);
}

void OSG::osgEndEditNotChangedCP(OSGFieldContainerPtr &objectP, 
                                 OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.endEditNotChanged(whichField);
}

void OSG::osgSetRefdCP(OSGFieldContainerPtr &objectP,
                       OSGFieldContainerPtr &newObjectP)
{
    if(objectP != newObjectP)
    {
        if(objectP != OSGNullFC)
            objectP.subRef();

        objectP = newObjectP;

        if(objectP != OSGNullFC)
            objectP.addRef();        
    }
}
