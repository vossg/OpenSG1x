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
 * 2002/10/16: added transparency path. Thanks to Franck Sourdin             *
 *            (sourdin@ai.cluny.ensam.fr) for it!                            *
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

#include <OSGGL.h>

#include <iostream>
#include <fstream>

#include <vector>

#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGGeoFunctions.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGImageFileHandler.h>
#include <OSGGroup.h>

#include "OSGOBJSceneFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::OBJSceneFileType 
    \ingroup GrpSystemFileIO
    
 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
const Char8 *OBJSceneFileType::_suffixA[] =  { "obj" };

OBJSceneFileType  OBJSceneFileType::_the         (_suffixA,
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
NodePtr OBJSceneFileType::read(const Char8 *fileName, UInt32) const
{
  NodePtr rootPtr, nodePtr;
  std::ifstream in(fileName);
  std::string elem;
  std::map<std::string, DataElem>::const_iterator elemI;
  Vec3f vec3f;
  Vec2f vec2f;
  Real32 x,y,z;
  GeoPositionsPtr coordPtr      = GeoPositions3f::create();
  GeoTexCoordsPtr  texCoordPtr  = GeoTexCoords2f::create();
  GeoNormalsPtr     normalPtr   = GeoNormals3f::create(); 
  GeometryPtr geoPtr;
  GeoIndicesPtr indexPtr;
  GeoPLengthsPtr lensPtr;
  GeoPTypesPtr typePtr; 
  DataElem dataElem;
  Char8 strBuf[8192], *token, *nextToken;
  Int32 strBufSize = sizeof(strBuf)/sizeof(Char8);
  Int32 index, posIndex, indexType;
  Int32 i,j,n,primCount[3];
  std::list<Mesh> meshList;
  std::map<std::string, SimpleTexturedMaterialPtr> mtlMap;
  std::map<std::string, SimpleTexturedMaterialPtr>::iterator mtlI;
  Mesh emptyMesh;
  Face emptyFace;
  TiePoint  emptyTie;
  Int32 indexMask, meshIndexMask;
  std::list<Face>::iterator faceI;
  std::list<Mesh>::iterator meshI;
  bool isSingleIndex;

  // Path handler for material files
  PathHandler ph;
  ph.setBaseFile(fileName);
  
  // create the first mesh entry
  meshList.push_back(emptyMesh);
  meshI = meshList.begin();

    if (in)
    {
      primCount[0] = 0;
      primCount[1] = 0;
      primCount[2] = 0;  

      beginEditCP(coordPtr);
      beginEditCP(texCoordPtr);
      beginEditCP(normalPtr);

      for (in >> elem; in.eof() == false; in >> elem) 
        if (elem[0] == '#' ||
	    elem[0] == '$'
	    )
          in.ignore(INT_MAX, '\n'); 
        else
          {
            elemI = _dataElemMap.find(elem);
            dataElem = ((elemI == _dataElemMap.end()) ?
                        UNKNOWN_DE : elemI->second );
            switch (dataElem) 
              {
              case OBJECT_DE:
              case GROUP_DE:
              case SMOOTHING_GROUP_DE:
                in.ignore(INT_MAX, '\n'); 
                break;
              case VERTEX_DE:
                primCount[0]++;
                in >> x >> y >> z;
                vec3f.setValues(x,y,z);
                coordPtr->push_back(vec3f);                    
                break;
              case VERTEX_TEXTURECOORD_DE:
                primCount[1]++;
                in >> x >> y;
                vec2f.setValues(x,y);
                texCoordPtr->push_back(vec2f);
                break;
              case VERTEX_NORMAL_DE:
                primCount[2]++;
                in >> x >> y >> z;
                vec3f.setValues(x,y,z);
                normalPtr->push_back(vec3f);                    
                break;
              case LIB_MTL_DE:
                in >> elem;
                readMTL ( elem.c_str(), ph, mtlMap );
                in.ignore(INT_MAX, '\n'); 
                break;
              case USE_MTL_DE:
                in >> elem;
                if (meshI->faceList.empty() == false)
                  {
                    meshList.push_front(emptyMesh);
                    meshI = meshList.begin();
                  }
                mtlI = mtlMap.find(elem);
                if (mtlI == mtlMap.end())
                  {
                    FFATAL (("Unkown mtl %s\n", elem.c_str()));
                  }
                else
                  meshI->mtlPtr = mtlI->second;
                break;
              case FACE_DE:
                meshI->faceList.push_front(emptyFace);
                faceI = meshI->faceList.begin();
                in.get(strBuf,strBufSize);
                token = strBuf;
                indexType = 0;
                while (token && *token) 
                  {
                    for (; *token == '/'; token++)
                      indexType++;
                    for (; isspace(*token); token++)
                      indexType = 0;
                    index = strtol(token, &nextToken, 10);
                    if (token == nextToken)
                      break;
                    if (indexType == 0)
                      faceI->tieVec.push_back(emptyTie);
                    if (index >= 0)
                      index--;
                    else
                      index =  primCount[indexType] + index;        
                    faceI->tieVec.back().index[indexType] = index;
                    token = nextToken;
                  }
                break;
              case UNKNOWN_DE:
              default:
                FWARNING (( "Unkown obj data elem: %s\n", 
                            elem.c_str()));
                in.ignore(INT_MAX, '\n'); 
                break;
              }
          }

      endEditCP(coordPtr);
      endEditCP(texCoordPtr);
      endEditCP(normalPtr);

#if 0
      std::cerr << "------------------------------------------------" << std::endl;
      i = 0;
      for (meshI = meshList.begin(); meshI != meshList.end(); meshI++) {
        std::cerr << "Mesh " << i << " faceCount :" 
                  << meshI->faceList.size() << std::endl;
        j = 0 ;
        for ( faceI = meshI->faceList.begin(); faceI != meshI->faceList.end();
              faceI++)
          std::cerr << "MESH " <<  i << "face: " << j++ << "tie num: " 
                    << faceI->tieVec.size() << std::endl;
        i++;
      }
      std::cerr << "------------------------------------------------" << std::endl;
=======
#endif
      // create Geometry objects
      for (meshI = meshList.begin(); meshI != meshList.end(); meshI++)
        {
          geoPtr   = Geometry::create();
          indexPtr = GeoIndicesUI32::create();  
          lensPtr  = GeoPLengthsUI32::create();  
          typePtr  = GeoPTypesUI8::create();
          
          // create and check mesh index mask
          meshIndexMask = 0;
          isSingleIndex = true;
          if ( meshI->faceList.empty() == false)
            for ( faceI = meshI->faceList.begin(); 
                  faceI != meshI->faceList.end(); faceI++)
              {
                indexMask = 0;
                n = faceI->tieVec.size();
                for (i = 0; i < n; i++)
                  for (j = 0; j < 3; j++)
                  { 
                    if ((index = (faceI->tieVec[i].index[j])) >= 0) {
                      indexMask |= (1 << j);
                      if (j)
                        isSingleIndex &= (posIndex == index);
                      else
                        posIndex = index;
                    }
                  }
                if (meshIndexMask == 0)
                  meshIndexMask = indexMask;
                else
                  if (meshIndexMask != indexMask)
                    {
                      FFATAL (( "IndexMask unmatch, can not create geo\n"));
                      meshIndexMask = 0;
                      break;
                    }
              }
          else
            {
              FWARNING (("Mesh with empty faceList\n"));
            }
          
          // fill the geo properties
          if (meshIndexMask) 
            {
                beginEditCP ( geoPtr );
                {

                  if (isSingleIndex)
                  {
                    indexType = 0;
                    if (meshIndexMask & 1)
                      indexType |= Geometry::MapPosition;
                    if (meshIndexMask & 2)
                      indexType |= Geometry::MapTexCoords;
                    if (meshIndexMask & 4)
                      indexType |= Geometry::MapNormal;
                    geoPtr->getIndexMapping().push_back( indexType );
                  }
                  else
                  {
                    if (meshIndexMask & 1)
                    {
                      indexType = Geometry::MapPosition;
                      geoPtr->getIndexMapping().push_back( indexType);
                    }
                    if (meshIndexMask & 2)
                    {
                      indexType = Geometry::MapTexCoords;
                      geoPtr->getIndexMapping().push_back( indexType);
                    }
                    if (meshIndexMask & 4)
                    {
                      indexType = Geometry::MapNormal;
                      geoPtr->getIndexMapping().push_back( indexType);
                    }
                  }

                  geoPtr->setPositions ( coordPtr );
                  geoPtr->setTexCoords ( texCoordPtr );
                  geoPtr->setNormals   ( normalPtr );
                  geoPtr->setIndices   ( indexPtr );
                  geoPtr->setLengths   ( lensPtr );
                  geoPtr->setTypes     ( typePtr );
                  
                  if (meshI->mtlPtr == NullFC)
                  {
                    meshI->mtlPtr = SimpleTexturedMaterial::create();
                    beginEditCP( meshI->mtlPtr );
                    {
                      meshI->mtlPtr->setDiffuse( Color3f( .8, .8, .8 ) );
                      meshI->mtlPtr->setSpecular( Color3f( 1, 1, 1 ) );
                      meshI->mtlPtr->setShininess( 20 );
                    }
                    endEditCP( meshI->mtlPtr );
                  }
                  geoPtr->setMaterial  ( meshI->mtlPtr ); 
                }
                endEditCP ( geoPtr );
                
                beginEditCP(lensPtr);
                beginEditCP(typePtr);
                beginEditCP(indexPtr);
                
                for ( faceI = meshI->faceList.begin(); 
                      faceI != meshI->faceList.end(); faceI++)
                {
                  n = faceI->tieVec.size();
                  
                  // add the lens entry
                  lensPtr->push_back(n);
                  
                  // add the type entry
                  typePtr->push_back(GL_POLYGON);
                  
                  // create the index values
                  for (i = 0; i < n; i++)
                    if (isSingleIndex)
                      indexPtr->push_back( faceI->tieVec[i].index[0]);
                    else
                      for (j = 0; j < 3; j++)
                        if ( meshIndexMask & (1 << j))
                          indexPtr->push_back( faceI->tieVec[i].index[j]);
                }
            
                endEditCP(indexPtr);
                endEditCP(typePtr);
                endEditCP(lensPtr);
                
                createSharedIndex( geoPtr );
                
                // check if we have normals
                if ((meshIndexMask & 4) == 0)
                  calcVertexNormals(geoPtr);
                
                // TODO; need opt flag
                createOptimizedPrimitives(geoPtr);
                
                // create and link the node
                nodePtr = Node::create();
                beginEditCP ( nodePtr );
                {
                  nodePtr->setCore( geoPtr );
                }
                endEditCP ( nodePtr );
                
                if (meshList.size() > 1)
                  {
                    if (rootPtr == NullFC)
                      {
                        rootPtr = Node::create();
                        beginEditCP (rootPtr);
                        {
                          rootPtr->setCore ( Group::create() );
                          rootPtr->addChild(nodePtr);
                        }
                        endEditCP (rootPtr);
                      }
                    else
                      {
                        beginEditCP(rootPtr);
                        {
                          rootPtr->addChild(nodePtr);
                        }
                        endEditCP  (rootPtr);
                      }
                  }
                else
                  rootPtr = nodePtr;
            }
        }
    }
    
  
  return rootPtr;
}

NodePtr OBJSceneFileType::read(const Char8  *fileName,
                                     UInt32  uiAddOptions,
                                     UInt32  uiSubOptions) const
{
    return read(fileName, uiAddOptions & ~uiSubOptions);
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
bool OBJSceneFileType::write (const NodePtr  OSG_CHECK_ARG(node    ),
                              const Char8   *OSG_CHECK_ARG(fileName)) const
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
                                         bool    override,
                                         UInt32  overridePriority) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority),
    _dataElemMap()

{
    initElemMap();
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
    initElemMap();
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

OBJSceneFileType &OBJSceneFileType::the(void)
{
    return _the;
}

OBJSceneFileType::~OBJSceneFileType(void)
{
    return;
}

const Char8 *OBJSceneFileType::getName(void) const
{
    return "OBJ GEOMETRY";
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


void OBJSceneFileType::initElemMap(void)
{
  if (_dataElemMap.empty())
    {
      _dataElemMap[""]        = UNKNOWN_DE;
     
      _dataElemMap["v"]       = VERTEX_DE;
      _dataElemMap["vt"]      = VERTEX_TEXTURECOORD_DE;
      _dataElemMap["vn"]      = VERTEX_NORMAL_DE;
      _dataElemMap["f"]       = FACE_DE;
      _dataElemMap["fo"]      = FACE_DE;
      _dataElemMap["mtllib"]  = LIB_MTL_DE;
      _dataElemMap["usemtl"]  = USE_MTL_DE;
      _dataElemMap["g"]       = GROUP_DE;
      _dataElemMap["s"]       = SMOOTHING_GROUP_DE;
      _dataElemMap["o"]       = OBJECT_DE;
    }

  if (_mtlElemMap.empty())
    {
      _mtlElemMap[""]        = UNKNOWN_ME;

      _mtlElemMap["newmtl"]  = NEW_MTL_ME;
      _mtlElemMap["Kd"]      = MTL_DIFFUSE_ME;
      _mtlElemMap["Ka"]      = MTL_AMBIENT_ME;
      _mtlElemMap["Ks"]      = MTL_SPECULAR_ME;
      _mtlElemMap["Ns"]      = MTL_SHININESS_ME;
      _mtlElemMap["Tr"]      = MTL_TRANSPARENCY_ME;
      _mtlElemMap["map_Kd"]  = MTL_MAP_KD_ME;
      _mtlElemMap["map_Ka"]  = MTL_MAP_KA_ME;
      _mtlElemMap["map_Ks"]  = MTL_MAP_KS_ME;
      _mtlElemMap["illum"]   = MTL_ILLUM_ME;
      _mtlElemMap["refl"]    = MTL_REFL_ME;
    }
}

Int32 OBJSceneFileType::readMTL ( const Char8 *fileName,
                                  PathHandler &pathHandler,
                                  std::map<std::string, SimpleTexturedMaterialPtr> & mtlMap )
  const
{
  Int32 mtlCount = 0;
  std::ifstream in(pathHandler.findFile(fileName).c_str());
  SimpleTexturedMaterialPtr mtlPtr = NullFC;
  Real32 a,b,c;
  std::string elem;
  std::map<std::string, MaterialElem>::const_iterator elemI;
  MaterialElem mtlElem;
  std::map<std::string, osg::Image*> imageMap;
  std::map<std::string, osg::Image*>::iterator iI;
  Image *image = 0;
  bool constDiffuse, constAmbient, constSpecular;

  if (in)
    for (in >> elem; in.eof() == false; in >> elem) 
      if (elem[0] == '#' || elem[0] == '$' )
        in.ignore(INT_MAX, '\n'); 
      else
        {
          elemI = _mtlElemMap.find(elem);
          mtlElem = ((elemI == _mtlElemMap.end()) ?
                     UNKNOWN_ME : elemI->second);
          if (mtlElem == NEW_MTL_ME)
          {
            in >> elem;
            if (mtlPtr != NullFC)
              endEditCP(mtlPtr);
            mtlPtr = SimpleTexturedMaterial::create();
            beginEditCP(mtlPtr);
            mtlPtr->setColorMaterial(GL_NONE);
            mtlPtr->setEnvMode(GL_MODULATE);
            mtlMap[elem] = mtlPtr;
            mtlCount++;
            constDiffuse  = false;
            constAmbient  = false;
            constSpecular = false;
          }
          else
          {
            if (mtlPtr == NullFC)
            {  
              FFATAL (( "Invalid Mtl token: %s, newmtl expected in %s\n",
                        elem.c_str(), fileName ));
              in.ignore(INT_MAX, '\n');
            }
            else 
            {
              switch (mtlElem) 
              {
              case MTL_DIFFUSE_ME:
                in >> a >> b >> c;
                if (!constDiffuse) 
                  mtlPtr->setDiffuse( Color3f( a,b,c ));
                break;
              case MTL_AMBIENT_ME:
                in >> a >> b >> c;
                if (!constAmbient)
                  mtlPtr->setAmbient( Color3f( a,b,c ));
                break;
              case MTL_SPECULAR_ME:
                in >> a >> b >> c;
                if (!constSpecular)
                  mtlPtr->setSpecular( Color3f( a,b,c ));
                break;
              case MTL_SHININESS_ME:
                in >> a;
                mtlPtr->setShininess(a);
                break;
              case MTL_ILLUM_ME:
                ; // TODO: What to do with illum ?!?
                in >> elem;
                // FFATAL (("obj mtl illum not handled yet\n"));
                break;
              case MTL_REFL_ME:
                mtlPtr->setEnvMap(true);
                break;
              case MTL_TRANSPARENCY_ME:
                in >> a;
                mtlPtr->setTransparency(a);
                break;
              case MTL_MAP_KD_ME:
              case MTL_MAP_KA_ME:
              case MTL_MAP_KS_ME:
                image = 0;
                in >> elem;                
                iI = imageMap.find(elem);
                if (iI == imageMap.end())
                {
                  elem = pathHandler.findFile(elem.c_str());
                  image = osg::ImageFileHandler::the().read(elem.c_str());
                  imageMap[elem] = image;
                }                     
                else 
                {
                  image = iI->second;
                }
                if (image) {
                  mtlPtr->setImage(image);
                  switch (mtlElem) {
                  case MTL_MAP_KD_ME:
                    constDiffuse = true;
                    mtlPtr->setDiffuse  ( Color3f( 1, 1, 1) );
                    break;
                  case MTL_MAP_KA_ME:
                    constAmbient = true;
                    mtlPtr->setAmbient  ( Color3f( 1, 1, 1) );
                    break;
                  case MTL_MAP_KS_ME:
                    constSpecular = true;
                    mtlPtr->setSpecular ( Color3f( 1, 1, 1) );
                    break;
                  }
                }
                else
                {
                  FFATAL (( "Can not find %s texture file in mtl %s \n",
                            elem.c_str(), fileName ));
                }
              break;               
              default:
              FWARNING (( "Invalid %s entry in %s\n",
                          elem.c_str(), fileName ));
              in.ignore(INT_MAX, '\n');
              }
            }
          }
        }
  
  if (mtlPtr != NullFC)
    endEditCP(mtlPtr);
          
  return mtlCount;
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
    static Char8 cvsid_hpp[] = OSGOBJSCENEFILETYPE_HEADER_CVSID;
}

