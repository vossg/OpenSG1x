/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGStatisticsForeground.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGStatisticsForeground.cpp,v 1.1 2002/03/19 17:46:18 dirk Exp $";
    static char cvsid_hpp[] = OSGSTATISTICSFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSTATISTICSFOREGROUND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::StatisticsForeground
Background is the base class for all background clearing.  	 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

StatisticsForeground::StatisticsForeground(void) :
    Inherited()
{
}

//! Copy Constructor

StatisticsForeground::StatisticsForeground(const StatisticsForeground &source) :
    Inherited(source)
{
}

//! Destructor

StatisticsForeground::~StatisticsForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void StatisticsForeground::initMethod (void)
{
}

//! react to field changes

void StatisticsForeground::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void StatisticsForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StatisticsForeground NI" << endl;
}

