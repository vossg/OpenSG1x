/*------------------------------------------*
*              OpenSG                       *
*                                           *
*                                           *
*     Copyright 2000 by OpenSG Forum        *
*                                           *
* contact: {reiners|vossg}@igd.fhg.de,      *
*           jbehr@zgdv.de                   *
*-------------------------------------------*/
/*------------------------------------------*
*              Licence                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/
/*------------------------------------------*
*              Changes                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/


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

#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>


#include "OSGRAWSceneFileType.h"

OSG_USING_OSG_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const char *suffixA[] =  { "raw" };

OSGRAWSceneFileType OSGRAWSceneFileType::_the ( suffixA, sizeof(suffixA));

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
//p: OSGScene &image, const char *fileName
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
OSGNodePtr OSGRAWSceneFileType::read (const char *fileName ) const
{
	OSGNodePtr root;
	ifstream in(fileName);
	OSGGeometryPtr geo;
	OSGGeoPosition3f::OSGPtrType points;
	OSGGeoNormal3f::OSGPtrType   normals;
	OSGGeoIndexUI32Ptr index;
	OSGGeoPLengthPtr lens;
	OSGGeoPTypePtr type;
	OSGVec3f vec[3];
	OSGInt32 i = 0, n, triCount = 0;
	OSGReal32 x,y,z;

	if (in) 
    {
		root = OSGNode::create();
		geo = OSGGeometry::create();

        osgBeginEditCP(root, OSGNode::OSGCoreFieldMask);
		root->setCore( geo );
        osgEndEditCP(root, OSGNode::OSGCoreFieldMask);

		points = OSGGeoPosition3f::create();
  		geo->setPositions( points );
		normals = OSGGeoNormal3f::create();
		geo->setNormals ( normals );

		triCount = i = 0;

		osgBeginEditCP(points,  OSGFieldBits::OSGAllFields);
		osgBeginEditCP(normals, OSGFieldBits::OSGAllFields);

		while (1) {
			in >> x >> y >> z;
			if (in.eof()) 
				break;
			else {
				points->getFieldPtr()->addValue( OSGPnt3f ( x, y, z) );
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

		osgEndEditCP(points,  OSGFieldBits::OSGAllFields);
		osgEndEditCP(normals, OSGFieldBits::OSGAllFields);
		
		if (triCount) 
		{
		
			index = OSGGeoIndexUI32::create();
			geo->setIndex( index );
			osgBeginEditCP(index, OSGFieldBits::OSGAllFields);
			n = triCount * 3;
			for (i = 0; i < n; i++) 
				index->getFieldPtr()->addValue( i );
			osgEndEditCP(index, OSGFieldBits::OSGAllFields);
			

			lens = OSGGeoPLength::create();
			geo->setLengths( lens );
            osgBeginEditCP(lens, OSGFieldBits::OSGAllFields);
			lens->getFieldPtr()->addValue( n );
			osgEndEditCP(lens, OSGFieldBits::OSGAllFields);

			type = OSGGeoPType::create();
			geo->setTypes( type );
			osgBeginEditCP(type, OSGFieldBits::OSGAllFields);
			type->getFieldPtr()->addValue( GL_TRIANGLES );
			osgEndEditCP(type, OSGFieldBits::OSGAllFields);
			
			geo->setNormalPerVertex( true );
		}

        osgEndEditCP(geo, OSGFieldBits::OSGAllFields);
	
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
//p: OSGScene &image, const char *fileName
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
bool OSGRAWSceneFileType::write ( const OSGNodePtr node, 
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
// Function name: OSGRAWSceneFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], OSGUInit16 suffixByteCount
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
OSGRAWSceneFileType::OSGRAWSceneFileType ( const char *suffixArray[], 
																					 OSGUInt16 suffixByteCount )
	: OSGSceneFileType ( suffixArray, suffixByteCount)
{
	return;
}

//----------------------------
// Function name: OSGRAWSceneFileType
//----------------------------
//
//Parameters:
//p: const OSGRAWSceneFileType &obj
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
OSGRAWSceneFileType::OSGRAWSceneFileType (const OSGRAWSceneFileType &obj )
	: OSGSceneFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~OSGRAWSceneFileType
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
OSGRAWSceneFileType::~OSGRAWSceneFileType (void )
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


