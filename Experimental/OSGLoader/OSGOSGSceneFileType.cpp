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

#include "OSGOSGSceneFileType.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGOSGSCENEFILETYPE_HEADER_CVSID;
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

const Char8 *OSGSceneFileType::_suffixA[] =  { "osg" };

OSGSceneFileType OSGSceneFileType::_the(_suffixA, 
                                        sizeof(_suffixA),
                                        false,
                                        10);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSGSceneFileType &OSGSceneFileType::the(void)
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

const Char8 *OSGSceneFileType::getName(void) const 
{ 
    return "OSG GEOMETRY"; 
}


NodePtr OSGSceneFileType::read(const Char8  *fileName, 
                                     UInt32  uiReplaceOptions) const
{
    _pFile->scanFile(fileName, uiReplaceOptions);

    return _pFile->getRootNode();
}

NodePtr OSGSceneFileType::read(const Char8  *fileName, 
                                     UInt32  uiAddOptions,
                                     UInt32  uiSubOptions) const
{
    _pFile->scanFile(fileName, uiAddOptions, uiSubOptions);

    return _pFile->getRootNode();    
}

OSGSceneFileType::FCPtrStore OSGSceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiReplaceOptions) const
{
    _pFile->scanFile(fileName, uiReplaceOptions);

    return _pFile->getRootNodes();
}

OSGSceneFileType::FCPtrStore OSGSceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiAddOptions,
          UInt32  uiSubOptions) const
{
    _pFile->scanFile(fileName, uiAddOptions, uiSubOptions);

    return _pFile->getRootNodes();
}

Bool OSGSceneFileType::write(const NodePtr, const char *) const
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

OSGSceneFileType::OSGSceneFileType(const char   *suffixArray[], 
                                         UInt16  suffixByteCount,
                                         Bool    override,
                                         UInt32  overridePriority) :
    Inherited(suffixArray, 
              suffixByteCount, 
              override, 
              overridePriority)
{
    _pFile = new OSGLoader;

    return;
}


/** \brief Destructor
 */

OSGSceneFileType::~OSGSceneFileType(void)
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

