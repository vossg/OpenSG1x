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

//-------------------------------
// 	Includes 					 			    
//-------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#ifdef OSG_SGI_STL
#include <limits>
#endif

#define OSG_COMPILELOADER

#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>


#include "OSGRAWSceneFileType.h"

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const char *suffixA[] =  { "raw" };

RAWSceneFileType RAWSceneFileType::_the ( suffixA, sizeof(suffixA));

/*****************************
 *	  Classvariables
 *****************************/


/********************************
 *	  Class methodes
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
NodePtr RAWSceneFileType::read (const char *fileName ) const
{
	NodePtr root;
	ifstream in(fileName);
	GeometryPtr geo;
	GeoPosition3f::PtrType points;
	GeoNormal3f::PtrType   normals;
	GeoIndexUI32Ptr index;
	GeoPLengthPtr lens;
	GeoPTypePtr type;
	Vec3f vec[3];
	Int32 i = 0, n, triCount = 0;
	Real32 x,y,z;

	if (in) 
    {
		root = Node::create();
		geo = Geometry::create();

        osgBeginEditCP(root, Node::CoreFieldMask);
		root->setCore( geo );
        osgEndEditCP(root, Node::CoreFieldMask);

		points = GeoPosition3f::create();
  		geo->setPositions( points );
		normals = GeoNormal3f::create();
		geo->setNormals ( normals );

		triCount = i = 0;

		osgBeginEditCP(points,  FieldBits::AllFields);
		osgBeginEditCP(normals, FieldBits::AllFields);

		while (1) {
			in >> x >> y >> z;
			if (in.eof()) 
				break;
			else {
				points->getFieldPtr()->addValue( Pnt3f ( x, y, z) );
				vec[i].setValues(x,y,z);
				if (i == 2) {
					vec[0] -= vec[1];
					vec[1] -= vec[2];
					vec[0].crossThis(vec[1]);
					vec[0].normalize();
					
					normals->getFieldPtr()->addValue ( vec[0] );
					normals->getFieldPtr()->addValue ( vec[0] );
					normals->getFieldPtr()->addValue ( vec[0] );

					i = 0;
					triCount++;
				}
				else 
					i++;
			}
		}

		osgEndEditCP(points,  FieldBits::AllFields);
		osgEndEditCP(normals, FieldBits::AllFields);
		
		if (triCount) 
		{
		
			index = GeoIndexUI32::create();
			geo->setIndex( index );
			osgBeginEditCP(index, FieldBits::AllFields);
			n = triCount * 3;
			for (i = 0; i < n; i++) 
				index->getFieldPtr()->addValue( i );
			osgEndEditCP(index, FieldBits::AllFields);
			

			lens = GeoPLength::create();
			geo->setLengths( lens );
            osgBeginEditCP(lens, FieldBits::AllFields);
			lens->getFieldPtr()->addValue( n );
			osgEndEditCP(lens, FieldBits::AllFields);

			type = GeoPType::create();
			geo->setTypes( type );
			osgBeginEditCP(type, FieldBits::AllFields);
			type->getFieldPtr()->addValue( GL_TRIANGLES );
			osgEndEditCP(type, FieldBits::AllFields);
			
			geo->setNormalPerVertex( true );
		}

        osgEndEditCP(geo, FieldBits::AllFields);
	
		in.close();
	}

	if (triCount)
		SNOTICE << triCount << " triangle read " << endl;

	return root;
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
bool RAWSceneFileType::write ( const NodePtr node, 
																  const char *fileName) const
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
// Function name: RAWSceneFileType
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
RAWSceneFileType::RAWSceneFileType ( const char *suffixArray[], 
																					 UInt16 suffixByteCount )
	: SceneFileType ( suffixArray, suffixByteCount)
{
	return;
}

//----------------------------
// Function name: RAWSceneFileType
//----------------------------
//
//Parameters:
//p: const RAWSceneFileType &obj
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
RAWSceneFileType::RAWSceneFileType (const RAWSceneFileType &obj )
	: SceneFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~RAWSceneFileType
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

RAWSceneFileType::~RAWSceneFileType (void )
{
	return;
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
*protected	
****************************/


/****************************
*private
****************************/


