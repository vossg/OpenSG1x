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

//-------------------------------
//  Includes
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGSimpleMaterial.h>

#include "OSGBINSceneFileType.h"
#include "OSGBINLoader.h"


OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

const Char8            *BINSceneFileType::_suffixA[] = {"bin"};

      BINSceneFileType  BINSceneFileType::_the         (_suffixA,
                                                        sizeof(_suffixA),
                                                        false,
                                                        10);

/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Scene &image, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read the image from the given file
//SeeAlso:
//s:
//
//------------------------------

#ifdef __sgi
#pragma set woff 1209
#endif

NodePtr BINSceneFileType::read(const Char8 *fileName, UInt32) const
{
    FILE *inFile;
    inFile = fopen(fileName, "rb");
	if (inFile==NULL)
    {
		std::cerr << "ERROR: Cannot open file """ 
                  << fileName 
                  << """" 
                  << std::endl;

        return NullFC;
    }
    else
    {
        BINLoader loader(inFile);
	    loader.read();
        fclose(inFile);
        return loader.getRootNode();
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif


NodePtr BINSceneFileType::read(const Char8  *fileName,
                                     UInt32  uiAddOptions,
                                     UInt32  uiSubOption ) const
{
    return read(fileName, uiAddOptions & ~uiSubOption);
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: Scene &image, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: write the image to the given file
//SeeAlso:
//s:
//
//------------------------------

bool BINSceneFileType::write(const NodePtr  OSG_CHECK_ARG(node    ),
                             const Char8   *OSG_CHECK_ARG(fileName)) const
{
    return false;
}

/******************************
*protected
******************************/


/******************************
*private
******************************/


/***************************
*instance methodes
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: BINSceneFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], UInit16 suffixByteCount
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------

BINSceneFileType::BINSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority)
{
}

BINSceneFileType &BINSceneFileType::the(void)
{
    return _the;
}

const Char8 *BINSceneFileType::getName(void) const
{
    return "BIN GEOMETRY";
}

//----------------------------
// Function name: BINSceneFileType
//----------------------------
//
//Parameters:
//p: const BINSceneFileType &obj
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------

BINSceneFileType::BINSceneFileType(const BINSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

//----------------------------
// Function name: ~BINSceneFileType
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------

BINSceneFileType::~BINSceneFileType (void )
{
    return;
}


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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBINSCENEFILETYPE_HEADER_CVSID;
}
