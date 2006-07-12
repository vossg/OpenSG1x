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

#include "OSGResolutionDisplayFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ResolutionDisplayFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ResolutionDisplayFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ResolutionDisplayFilter::ResolutionDisplayFilter(void) :
    Inherited()
{
}

ResolutionDisplayFilter::ResolutionDisplayFilter(const ResolutionDisplayFilter &source) :
    Inherited(source)
{
}

ResolutionDisplayFilter::~ResolutionDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ResolutionDisplayFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ResolutionDisplayFilter::dump(      UInt32    , 
                                   const BitVector ) const
{
    SLOG << "Dump ResolutionDisplayFilter NI" << std::endl;
}


void ResolutionDisplayFilter::createFilter(DisplayFilterForeground *fg,
                                           Viewport *)
{
    DisplayFilterForeground::DisplayFilterGroup *color      = fg->findReadbackGroup("ColorDisplayFilter");
    DisplayFilterForeground::DisplayFilterGroup *resolution = fg->findReadbackGroup("ResolutionDisplayFilter");

    Real32 downScale = getDownScale();
    if(downScale > 1)
        downScale = 1;
    if(downScale < 0)
        downScale = 0;

    beginEditCP(color->getTransform());
    color->getTransform()->setScale(Vec3f(downScale,
                                          downScale, 1.0));
    endEditCP(color->getTransform());
    beginEditCP(resolution->getTransform());
    resolution->getTransform()->setScale(Vec3f(1/downScale,
                                               1/downScale, 1.0));
    endEditCP(resolution->getTransform());
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
    static Char8 cvsid_hpp       [] = OSGRESOLUTIONDISPLAYFILTERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRESOLUTIONDISPLAYFILTERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRESOLUTIONDISPLAYFILTERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

