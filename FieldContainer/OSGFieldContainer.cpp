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

char FieldContainer::cvsid[] = "@(#)$Id: $";

FieldContainerType FieldContainer::_type("FieldContainer");

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

FieldContainerType &FieldContainer::getType(void)
{ 
    return _type; 
}

const FieldContainerType &FieldContainer::getType(void) const
{ 
    return _type; 
}

UInt32 FieldContainer::getTypeId(void) const 
{
    return getType().getId(); 
}

UInt16 FieldContainer::getGroupId(void) const
{
    return getType().getGroupId(); 
}

const Char8 *FieldContainer::getTypeName(void) const 
{
    return getType().getName(); 
}


Field *FieldContainer::getField(UInt32 fieldId)
{
	const FieldDescription *desc = getType().getFieldDescription(fieldId);

    return desc ? desc->getField(*this) : NULL;
}

Field *FieldContainer::getField(const Char8 *fieldName)
{
	const FieldDescription *desc =getType().findFieldDescription(fieldName);

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

FieldContainer::FieldContainer(void) :
    _shares(0)
{
}

/** \brief Copy Constructor
 */

FieldContainer::FieldContainer(const FieldContainer &) :
    _shares(0)
                   
{
}

/** \brief Destructor
 */

FieldContainer::~FieldContainer(void)
{
}

void FieldContainer::changed(BitVector whichField, ChangeMode from)
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

void osgAddRefCP(FieldContainerPtr &objectP)
{
    if(objectP != NullFC)
        objectP.addRef();
}

/*! osgSubRefP */
void osgSubRefCP(FieldContainerPtr &objectP)
{
    if(objectP != NullFC)
        objectP.subRef();
}

/*! osgBeginEditCP */
void osgBeginEditCP(FieldContainerPtr &objectP, 
                    BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.beginEdit(whichField);
}

/*! osgEndEditCP */
void osgEndEditCP(FieldContainerPtr &objectP, 
                  BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.endEdit(whichField);
}

void osgChangedCP(FieldContainerPtr &objectP, 
                  BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.changed(whichField);
}

void osgEndEditNotChangedCP(FieldContainerPtr &objectP, 
                            BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.endEditNotChanged(whichField);
}

void osgSetRefdCP(FieldContainerPtr &objectP,
                  FieldContainerPtr &newObjectP)
{
    if(objectP != newObjectP)
    {
        if(objectP != NullFC)
            objectP.subRef();

        objectP = newObjectP;

        if(objectP != NullFC)
            objectP.addRef();        
    }
}

OSG_END_NAMESPACE
