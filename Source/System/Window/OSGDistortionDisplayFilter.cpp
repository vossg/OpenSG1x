/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGConfig.h>

#include "OSGDistortionDisplayFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistortionDisplayFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistortionDisplayFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistortionDisplayFilter::DistortionDisplayFilter(void) :
    Inherited()
{
}

DistortionDisplayFilter::DistortionDisplayFilter(const DistortionDisplayFilter &source) :
    Inherited(source)
{
}

DistortionDisplayFilter::~DistortionDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistortionDisplayFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DistortionDisplayFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DistortionDisplayFilter NI" << std::endl;
}

void DistortionDisplayFilter::createFilter(DisplayFilterForeground *fg,
                                           Viewport *port)
{
    DisplayFilterForeground::DisplayFilterGroup *group = fg->findReadbackGroup("ColorDisplayFilter");

    if(getColumns() < 2 ||
       getRows() < 2)
    {
        SWARNING << "DistortionDisplayFilter columns or rows < 2" << std::endl;
        return;
    }
    
    if(!getPositions().empty() &&
       getColumns() * getRows() != getPositions().size())
    {
        SWARNING << "DistortionDisplayFilter wrong number of positions" << std::endl;
        return;
    }
       
    // prepare grid
    group->createGrid(getColumns(),getRows());

    GeoPositionsPtr pos = group->getGeometry()->getPositions();

    beginEditCP(pos,Geometry::PositionsFieldMask);
    for(UInt32 p = 0 ; p < getPositions().size() ; ++p)
    {
        pos->setValue(Pnt3f(getPositions()[p][0],
                            getPositions()[p][1],
                            0),p);
    }
    endEditCP(pos,Geometry::PositionsFieldMask);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDISTORTIONDISPLAYFILTERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISTORTIONDISPLAYFILTERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISTORTIONDISPLAYFILTERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

