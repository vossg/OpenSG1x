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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGVRMLSceneFileType.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLSceneFileType::cvsid[] = "@(#)$Id: $";

const char *VRMLSceneFileType::_suffixA[] =  { "wrl" };

VRMLSceneFileType VRMLSceneFileType::_the(_suffixA, sizeof(_suffixA));

Bool     VRMLSceneFileType::_bLoaderInitialized = false;
VRMLFile VRMLSceneFileType::_vrmlLoader;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

VRMLSceneFileType &VRMLSceneFileType::the(void)
{
    return _the;
}

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

NodePtr VRMLSceneFileType::read(const char *fileName) const
{
    if(_bLoaderInitialized == false)
    {
        _vrmlLoader.scanStandardPrototypes("std.wrl", 0);

        _bLoaderInitialized = true;
    }

    _vrmlLoader.scanFile(fileName, OSG::VRMLFile::CreateNormals);

    return  _vrmlLoader.getRoot();
}

Bool VRMLSceneFileType::write(const NodePtr, const char *) const
{
    return false;
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

VRMLSceneFileType::VRMLSceneFileType(const char   *suffixArray[], 
                                           UInt16  suffixByteCount) :
	Inherited(suffixArray, suffixByteCount)
{
    fprintf(stderr, "Init VRML Scene File Type %d\n", this);
	return;
}


/** \brief Destructor
 */

VRMLSceneFileType::~VRMLSceneFileType(void)
{
}

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

