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
// 	Includes 					 			    
//-------------------------------

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/gl.h>

#include <iostream>
#include <fstream>

#include <vector>

#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGGeoFunctions.h>
#include <OSGSimpleMaterial.h>

#include "OSGOBJSceneFileType.h"

// #include "glm.exh"
// #include "glm.exc"

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: OSGOBJSceneFileType.cpp,v 1.4 2001/10/03 20:37:33 dirk Exp $";
    char cvsid_hpp[] = OSGOBJSCENEFILETYPE_HEADER_CVSID;
}


/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const Char8 *suffixA[] =  { "obj" };

OBJSceneFileType OBJSceneFileType::_the(suffixA, 
                                        sizeof(suffixA),
                                        false,
                                        10);

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
//r:Bool
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
NodePtr OBJSceneFileType::read(const Char8 *fileName, UInt32) const
{
  typedef std::vector<int> Face;

  std::vector<Face> faceVec;

  char head[256];
	ifstream in(fileName);
	NodePtr root;
	GeometryPtr geo;
  Vec3f point;
  GeoPositions3fPtr points;
 	GeoIndicesUI32Ptr index;
	GeoPLengthsPtr lens;
	GeoPTypesPtr type;   
  SimpleMaterialPtr mat;
  Int32 i,j,k,n,vN,fN,pType;
  Int32 triCount = 0, vertexCount, faceCount, uk;
  Real64 x, y, z;

  if (in) {
    in >> head >> vertexCount >> faceCount >> uk;

    FDEBUG (( "OBJ Head/vertexCount/faceCount: %s/%d/%d\n",
              head, vertexCount, faceCount ));
 
    if (vertexCount && faceCount) {

      //-------------------------------------------------------------------
      // create the OSG objects
      root = Node::create();
      geo = Geometry::create();
      points = GeoPositions3f::create();
      index = GeoIndicesUI32::create();  
      lens = GeoPLengthsUI32::create();  
      type = GeoPTypesUI8::create();
      mat = SimpleMaterial::create();
      
      beginEditCP(mat);
      {
         mat->setDiffuse( Color3f( 0.42, 0.42, 0.52 ) );
         mat->setSpecular( Color3f( 1, 1, 1 ) );
         mat->setShininess( 20 );
      }
      endEditCP(mat);
		
      
      beginEditCP ( root, Node::CoreFieldMask);
      {
        root->setCore( geo );
      }
      endEditCP ( root, Node::CoreFieldMask);
      
      beginEditCP ( geo );
      {
        geo->setPositions ( points );
        geo->setIndices   ( index );
        geo->setLengths   ( lens );
        geo->setTypes     ( type );
        geo->setMaterial  ( mat ); 
      }
      
      //-------------------------------------------------------------------
      // read/set the points
      beginEditCP ( points );
      {
        for (i = 0; (!in.eof()) && (i < vertexCount); i++) {
          in >> x >> y >> z;
          point.setValues (x,y,z);
          points->push_back(point);
        }
      }
      beginEditCP ( points );
      
      //-------------------------------------------------------------------
      // read the faces
      // TODO; should we 'reserve' some index mem (3,4,..) ?
      faceVec.resize(faceCount);
      triCount = 0;
      for (i = 0; (!in.eof()) && (i < faceCount); i++) {
        in >> n;
        if (n >= 0) {
          triCount += n - 2;
          for (j = 0; (!in.eof()) && (j < n); j++) {
            in >> k;
            if ((k >= 0) && (k < vertexCount))
              faceVec[i].push_back(k);
            else {
              FFATAL (("Invalid vertex index %d in face %d\n", k, i));
            }     
          }
        }
        else {
          FFATAL (("Invalid face vec num %d\n",n));
        }
      }
      
      //-------------------------------------------------------------------
      // set the faces
      for (i = 3; i <= 5; i++) {
        n = 0;
        for (j = 0; j < faceCount; j++) {
          fN = faceVec[j].size();
          if (fN >= 5)
            fN = 5;
          if (fN == i) {
            n += vN = faceVec[j].size();
            for (k = vN-1; k >= 0; k--) {
              index->getFieldPtr()->addValue( faceVec[j][k] );    
            }       
            if (i == 5) {
              beginEditCP(lens);
              {
                lens->addValue( n );
              }
              endEditCP(lens);
              
              beginEditCP(type, FieldBits::AllFields);
              {
                type->addValue( GL_POLYGON );
              }
            endEditCP(type, FieldBits::AllFields);
            }
          }
        }
        if (n) { 
          switch (i) {
          case 3:
            pType = GL_TRIANGLES;
            break;
          case 4:
            pType = GL_QUADS;
            break;
          default:
            pType = 0;
            break;
          }
          if (pType) {
            beginEditCP(lens);
            {
              lens->addValue( n );
            }
            endEditCP(lens);
            
            beginEditCP(type, FieldBits::AllFields);
            {
              type->addValue( pType );
            }
            endEditCP(type, FieldBits::AllFields);
          }
        }
      }
    }
  }

  FNOTICE (("Number of triangle read: %d\n", triCount));

  calcVertexNormals(geo);
  createOptimizedPrimitives(geo);

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
//r:Bool
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
Bool OBJSceneFileType::write ( const NodePtr node, 
                               const Char8 *fileName) const
{	
  FFATAL (("OBJSceneFileType::write() is not impl.\n"));
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
// Function name: OBJSceneFileType
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

OBJSceneFileType::OBJSceneFileType(const Char8  *suffixArray[], 
                                         UInt16  suffixByteCount,
                                         Bool    override,
                                         UInt32  overridePriority) :
	SceneFileType(suffixArray, 
                  suffixByteCount,
                  override,
                  overridePriority)
{
}

//----------------------------
// Function name: OBJSceneFileType
//----------------------------
//
//Parameters:
//p: const OBJSceneFileType &obj
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

OBJSceneFileType::OBJSceneFileType(const OBJSceneFileType &obj) :
	SceneFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~OBJSceneFileType
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

OBJSceneFileType::~OBJSceneFileType(void)
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


