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

#include "OSGConfig.h"

#include "OSGVRMLSceneFileType.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    Char8 cvsid_cpp[] = "@(#)$Id: $";
    Char8 cvsid_hpp[] = OSGVRMLSCENEFILETYPE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const char *VRMLSceneFileType::_suffixA[] =  { "wrl" };

VRMLSceneFileType VRMLSceneFileType::_the(_suffixA,
                                          sizeof(_suffixA),
                                          false,
                                          10);

VRMLFile *VRMLSceneFileType::_pVRMLLoader = NULL;

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

const Char8 *VRMLSceneFileType::getName(void) const
{
    return "VRML GEOMETRY";
}

/*------------------------------ access -----------------------------------*/

NodePtr VRMLSceneFileType::read(const Char8  *fileName,
                                      UInt32  uiReplaceOptions) const
{
    if(_pVRMLLoader == NULL)
    {
        _pVRMLLoader = new VRMLFile();

//        _pVRMLLoader->scanStandardPrototypes("std.wrl", 0);
        _pVRMLLoader->createStandardPrototypes();
    }

    _pVRMLLoader->scanFile(fileName, uiReplaceOptions);

    return  _pVRMLLoader->getRoot();
}

NodePtr VRMLSceneFileType::read(const Char8  *fileName,
                                      UInt32  uiAddOptions,
                                      UInt32  uiSubOptions) const
{
    if(_pVRMLLoader == NULL)
    {
        _pVRMLLoader = new VRMLFile();

//        _pVRMLLoader->scanStandardPrototypes("std.wrl", 0);
        _pVRMLLoader->createStandardPrototypes();
    }

    _pVRMLLoader->scanFile(fileName, uiAddOptions, uiSubOptions);

    return  _pVRMLLoader->getRoot();
}

VRMLSceneFileType::FCPtrStore VRMLSceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiReplaceOptions)const
{
    FCPtrStore fcVec;

    NodePtr    nodePtr = read(fileName, uiReplaceOptions);

    if(nodePtr != NullFC)
        fcVec.push_back(nodePtr);

    return fcVec;
}

VRMLSceneFileType::FCPtrStore VRMLSceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiAddOptions,
          UInt32  uiSubOptions)const
{
    FCPtrStore fcVec;

    NodePtr    nodePtr = read(fileName, uiAddOptions, uiSubOptions);

    if(nodePtr != NullFC)
        fcVec.push_back(nodePtr);

    return fcVec;
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
                                           UInt16  suffixByteCount,
                                           Bool    override,
                                           UInt32  overridePriority) :
    Inherited(suffixArray,
              suffixByteCount,
              override,
              overridePriority)
{
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

