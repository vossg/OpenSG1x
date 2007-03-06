/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
// Includes
//-------------------------------
#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGGL.h>

#include <ios>
#include <iostream>
#include <fstream>


#include <OSGLog.h>
#include <OSGBaseFunctions.h>
#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGGeoFunctions.h>
#include <OSGSimpleMaterial.h>
#include <OSGGroup.h>
#include <OSGSimpleAttachments.h>
#include <OSGSceneFileHandler.h>

#include "OSGSTLSceneFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::STLSceneFileType
    \ingroup GrpSystemFileIO

*/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
const Char8 *STLSceneFileType::     _suffixA[] = { "stl", "stla", "stlb" };

STLSceneFileType STLSceneFileType:: _the(_suffixA,
                                         sizeof(_suffixA),
                                         false,
                                         10,
                                         SceneFileType::OSG_READ_SUPPORTED);

/*****************************
 *  Classvariables
 *****************************/

/********************************
 *  Class methodes
 *******************************/

/*******************************
*public
*******************************/

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: std::istream &is, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:NodePtr
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read the node from the given file
//SeeAlso:
//s:
//
//------------------------------
NodePtr STLSceneFileType::read(std::istream &is, const Char8 *fileNameOrExtension) const
{
	NodePtr fileRoot = OSG::NullFC;;
 
	STLFaceList theFaces;
	std::string theName;
	bool isAscii = IsASCII(is, fileNameOrExtension);
	if (isAscii)
	{
		if (!readASCII(is, theFaces, theName))
			return OSG::NullFC;
	}
	else
	{
		if (!readBinary(is, theFaces, theName))
			return OSG::NullFC;
	}
	if (!theFaces.empty())
	{
		GeometryPtr         geo;
		Pnt3f               point;
		Vec3f               norm;
		GeoPositions3fPtr   points;
		GeoPLengthsPtr      lens;
		GeoPTypesPtr        type;
		GeoNormals3fPtr     norms;
	    SimpleMaterialPtr   mat;

		fileRoot = Node::create();
		setName(fileRoot, theName.c_str());
		beginEditCP(fileRoot, Node::CoreFieldMask);

		geo = Geometry::create();
		points = GeoPositions3f::create();
		norms = GeoNormals3f::create();
		lens = GeoPLengthsUI32::create();
		type = GeoPTypesUI8::create();
		mat = SimpleMaterial::create();

		beginEditCP(mat);
		{
			mat->setDiffuse(Color3f(0.42, 0.42, 0.52));
			mat->setSpecular(Color3f(1, 1, 1));
			mat->setShininess(20);
		}
		endEditCP(mat);


		beginEditCP(type);
		{
			type->addValue( GL_TRIANGLES );
		}
		endEditCP(type);
	 
		// nb of vertices
		beginEditCP(lens);
		{
			lens->addValue(theFaces.size()*3);
		}
		endEditCP(lens);
		//-------------------------------------------------------------------
		// set the points and normals
		STLFaceListIterator actIt, endIt;
		actIt = theFaces.begin();
		endIt = theFaces.end();

		beginEditCP(points);
		beginEditCP(norms);
		while (actIt != endIt)
		{
			points->addValue(Pnt3f(actIt->v1x, actIt->v1y, actIt->v1z));
			points->addValue(Pnt3f(actIt->v2x, actIt->v2y, actIt->v2z));
			points->addValue(Pnt3f(actIt->v3x, actIt->v3y, actIt->v3z));
			norms->addValue(Vec3f(actIt->nx, actIt->ny, actIt->nz));
			norms->addValue(Vec3f(actIt->nx, actIt->ny, actIt->nz));
			norms->addValue(Vec3f(actIt->nx, actIt->ny, actIt->nz));
			++actIt;
		}
		endEditCP(norms);
		endEditCP(points);

		beginEditCP(geo);
		{
			geo->setTypes    (type);
			geo->setLengths  (lens);
			geo->setPositions(points);
			geo->setNormals  (norms);
			geo->setMaterial (mat);
		}
		endEditCP(geo);
					
		fileRoot->setCore(geo);
		endEditCP(fileRoot);
	}
//	SceneFileHandler::the().write(fileRoot, "c:\\teststl.osg");
    SceneFileHandler::the().updateReadProgress(100);
	return fileRoot;
}

/******************************
*protected
******************************/
//----------------------------
// Function name: isASCII
//----------------------------
//
//Parameters:
//p: std::istream &is, const Char8* fileNameOrExtensio
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: checks if a file is ascii or binary written 
//SeeAlso:
//s:
//
//------------------------------

bool STLSceneFileType::IsASCII(std::istream &is, const Char8* fileNameOrExtension) const
{
	std::string theAbsName = fileNameOrExtension;
	std::string theExtension;
	int nameLength = theAbsName.length();
	int separator = theAbsName.rfind(".", nameLength);
	theExtension = theAbsName.substr(separator+1, nameLength-separator-1);
	for (int i = 0; i < theExtension.length(); i++)
		theExtension[i] = tolower(theExtension[i]);
	if (theExtension.compare("stla") == 0)
		return true;
	else if (theExtension.compare("stlb") == 0)
		return false;
	else
	{
		// we have to check if our file start with "solid"
		std::string theCheck;
		is >> theCheck;
		for (int i = 0; i< theCheck.length(); i++)
			theCheck[i] = tolower(theCheck[i]);
		is.seekg( 0, std::ios_base::beg );

		return (theCheck.compare("solid") == 0);

	}
}


//----------------------------
// Function name: readASCII
//----------------------------
//
//Parameters:
//p: std::istream &is, STLFaceList& theFaces, std::string& theName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read the STL entries ascii from the given stream
//SeeAlso:
//s:
//
//------------------------------
bool STLSceneFileType::readASCII(std::istream &is, STLFaceList& theFaces, std::string& theName) const
{
	char token[9];
	int finished = 0;
	int parseResult = 0;
	UInt32 i;

	if(!is)
        return false;

	while ((finished == 0) && (! (is.eof())))
	{
        SceneFileHandler::the().updateReadProgress();
		memset(token, ' ', 9);
		is >> token;
		for (i = 0; i < strlen(token); i++)
		{
			token[i] = tolower(token[i]);
		}
		if (strcmp(token, "solid") == 0)
		{
			char tmp = is.get();
			if (tmp == ' ')
				is >> theName;
		}
		else if (strcmp(token, "facet") == 0)
		{
			STLFace tmpFace;
			is >> token >> tmpFace.nx >> tmpFace.ny >> tmpFace.nz;

			is >> token >> token;				// skip "outer loop"
			is >> token >> tmpFace.v1x >> tmpFace.v1y >> tmpFace.v1z;
			is >> token >> tmpFace.v2x >> tmpFace.v2y >> tmpFace.v2z;
			is >> token >> tmpFace.v3x >> tmpFace.v3y >> tmpFace.v3z;
			is >> token;						// skip "endloop"
			is >> token;						// skip "endfacet"
			theFaces.push_back(tmpFace);
		}
		else if (strcmp(token, "endsolid") == 0)
		{
			finished = 1;
			return true;
		}
	}
    return false;
}

//----------------------------
// Function name: readBinary
//----------------------------
//
//Parameters:
//p: std::istream &is, STLFaceList& theFaces, std::string& theName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read the STL entries binary from the given stream
//SeeAlso:
//s:
//
//------------------------------
bool STLSceneFileType::readBinary(std::istream &is, STLFaceList& theFaces, std::string& theName) const
{
    if(!is)
        return false;

    bool bigEndian = osg::osgIsBigEndian();

    int HeaderSize = 84;	// 80bytes for name and 4 bytes for number of facets 
    char name[80] = "";
    is.read( &name[0], 80 );
    theName = name;
    is.read(&name[0], 4); // skip the number of facets
    while (!is.eof())
    {
        SceneFileHandler::the().updateReadProgress();
        // a binary facet block has 50 bytes
        STLFace tmpFace;

        tmpFace.nx = ReadFloat(is, bigEndian);
        tmpFace.ny = ReadFloat(is, bigEndian);
        tmpFace.nz = ReadFloat(is, bigEndian);

        tmpFace.v1x = ReadFloat(is, bigEndian);
        tmpFace.v1y = ReadFloat(is, bigEndian);
        tmpFace.v1z = ReadFloat(is, bigEndian);

        tmpFace.v2x = ReadFloat(is, bigEndian);
        tmpFace.v2y = ReadFloat(is, bigEndian);
        tmpFace.v2z = ReadFloat(is, bigEndian);

        tmpFace.v3x = ReadFloat(is, bigEndian);
        tmpFace.v3y = ReadFloat(is, bigEndian);
        tmpFace.v3z = ReadFloat(is, bigEndian);

        theFaces.push_back(tmpFace);
        char buffer[2]; // offset filler
        is.read (&buffer[0], 2);
    }
    return true;
}

//----------------------------
// Function name: readBinary
//----------------------------
//
//Parameters:
//p: std::istream &is, bool bigEndian
//GlobalVars:
//g:
//Returns:
//r:Real32
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: read a float binary from a stream
//SeeAlso:
//s:
//
//------------------------------

Real32 STLSceneFileType::ReadFloat(std::istream& is, bool bigEndian) const
{
	Real32 result = 0;

	unsigned char buffer[4];
	is.read ((char*)&buffer[0], 4);
	Real32* tmp = (Real32*)&buffer;
	result = *tmp;
	if (bigEndian)
		result = osg::osgntohf(result);
	return result;
}


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
// Function name: STLSceneFileType
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
STLSceneFileType::STLSceneFileType(const Char8 *suffixArray[],
                                   UInt16 suffixByteCount, bool override,
                                   UInt32 overridePriority,
                                   UInt32 flags) :
    SceneFileType(suffixArray, suffixByteCount,
                  override, overridePriority, flags)
{
}

//----------------------------
// Function name: STLSceneFileType
//----------------------------
//
//Parameters:
//p: const STLSceneFileType &obj
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
STLSceneFileType::STLSceneFileType(const STLSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

//----------------------------
// Function name: ~STLSceneFileType
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
STLSceneFileType &STLSceneFileType::the(void)
{
    return _the;
}

/* */
STLSceneFileType::~STLSceneFileType(void)
{
    return;
}

/* */
const Char8 *STLSceneFileType::getName(void) const
{
    return "Stereolithography Geometry";
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGSTLSceneFileType.cpp,v 1.6 2007/03/06 09:28:28 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGSTLSCENEFILETYPE_HEADER_CVSID;
}

