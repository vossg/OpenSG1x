/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2003 by the OpenSG Forum                 *
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


//#include <stdlib.h>
//#include <stdio.h>

#include <iostream>

#include "OSGConfig.h"

#include "OSGDXFSceneFileType.h"
#include "OSGDXFFile.h"

OSG_USING_NAMESPACE


/*! \class DXFSceneFileType 
    \ingroup GrpSystemFileIO

 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8 *DXFSceneFileType::_suffixA[] =  { "dxf" };

DXFSceneFileType DXFSceneFileType::_the(_suffixA, 
                                        sizeof(_suffixA),
                                        false,
                                        10);

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

/*------------------------------ access -----------------------------------*/

DXFSceneFileType &DXFSceneFileType::the(void)
{
    return _the;
}

NodePtr DXFSceneFileType::read(std::istream &is,
                               const Char8 *) const
{
    return  DXFFile::load(is);
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Constructor
 */

DXFSceneFileType::DXFSceneFileType(const Char8   *suffixArray[], 
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority) :
	Inherited(suffixArray, suffixByteCount, override, overridePriority)
{
	return;
}


/** \brief Destructor
 */

DXFSceneFileType::~DXFSceneFileType(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGDXFSceneFileType.cpp,v 1.1 2004/02/19 16:45:40 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGDXFSCENEFILETYPE_HEADER_CVSID;
}
