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

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldContainer::cvsid[] = "@(#)$Id: $";

OSGFieldContainerType OSGFieldContainer::_type("FieldContainer");

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

OSGFieldContainerType &OSGFieldContainer::getType(void)
{ 
    return _type; 
}

const OSGFieldContainerType &OSGFieldContainer::getType(void) const
{ 
    return _type; 
}

OSGUInt32 OSGFieldContainer::getTypeId(void) const 
{
    return getType().getId(); 
}

OSGUInt16 OSGFieldContainer::getGroupId(void) const
{
    return getType().getGroupId(); 
}

const OSGChar8 *OSGFieldContainer::getTypeName(void) const 
{
    return getType().getName(); 
}


OSGField *OSGFieldContainer::getField(OSGUInt32 fieldId)
{
	const OSGFieldDescription *desc = getType().getFieldDescription(fieldId);

    return desc ? desc->getField(*this) : NULL;
}

OSGField *OSGFieldContainer::getField(const OSGChar8 *fieldName)
{
	const OSGFieldDescription *desc =getType().findFieldDescription(fieldName);

	return desc ? desc->getField(*this) : NULL;
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
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

void OSGFieldContainer::changed(OSGBitVector whichField, OSGChangeMode from)
{
    // fprintf(stderr, "FC Changed %d %d\n", whichField, fromSync);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



//---------------------------------------------------------------------------
//  FUNCTION: 
//---------------------------------------------------------------------------
//:  Example for the head comment of a function
//---------------------------------------------------------------------------
//
//p: Paramaters: 
//p: 
//
//g: GlobalVars:
//g: 
//
//r: Return:
//r: 
//
//c: Caution:
//c: 
//
//a: Assumptions:
//a: 
//
//d: Description:
//d: 
//
//s: SeeAlso:
//s: 
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

void osgAddRefCP(OSGFieldContainerPtr &objectP)
{
    if(objectP != OSGNullFC)
        objectP.addRef();
}

/*! osgSubRefP */
void osgSubRefCP(OSGFieldContainerPtr &objectP)
{
    if(objectP != OSGNullFC)
        objectP.subRef();
}

/*! osgBeginEditCP */
void osgBeginEditCP(OSGFieldContainerPtr &objectP, 
                    OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.beginEdit(whichField);
}

/*! osgEndEditCP */
void osgEndEditCP(OSGFieldContainerPtr &objectP, 
                  OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.endEdit(whichField);
}

void osgChangedCP(OSGFieldContainerPtr &objectP, 
                  OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.changed(whichField);
}

void osgEndEditNotChangedCP(OSGFieldContainerPtr &objectP, 
                            OSGBitVector          whichField)
{
    if(objectP != OSGNullFC)
        objectP.endEditNotChanged(whichField);
}

void osgSetRefdCP(OSGFieldContainerPtr &objectP,
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

OSG_END_NAMESPACE
