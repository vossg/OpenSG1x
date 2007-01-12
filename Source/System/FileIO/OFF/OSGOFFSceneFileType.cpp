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
#include <OSGSimpleMaterial.h>
#include <OSGSceneFileHandler.h>

#include "OSGOFFSceneFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::OFFSceneFileType
    \ingroup GrpSystemFileIO

*/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
const Char8 *OFFSceneFileType::     _suffixA[] = { "off" };

OFFSceneFileType OFFSceneFileType:: _the(_suffixA,
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
NodePtr OFFSceneFileType::read(std::istream &is, const Char8 *) const
{
    typedef std::vector<int> Face;

    std::vector<Face>   faceVec;

    char                head[256];
    NodePtr             root;
    GeometryPtr         geo;
    Pnt3f               point;
    Vec3f               norm;
    Color4f             color;
    Vec2f               texcoord;
    GeoPositions3fPtr   points;
    GeoIndicesUI32Ptr   index;
    GeoPLengthsPtr      lens;
    GeoPTypesPtr        type;
    GeoNormals3fPtr     norms;
    GeoColors4fPtr      colors;
    GeoTexCoords2fPtr   texcoords;
    SimpleMaterialPtr   mat;
    Int32               i, j, k, n, vN, fN, pType;
    Int32               triCount = 0, vertexCount, faceCount, edgeCount;
    Real32              x, y, z, a;
    bool                hasNormals = false, hasColors = false, hasTexCoords = false,
                        has4DimPoints = false;
    
    if(!is)
    {
        return NullFC;
    }

    is >> head >> vertexCount >> faceCount >> edgeCount;

    FDEBUG(("OFF Head/vertexCount/faceCount: %s/%d/%d\n", head,
           vertexCount, faceCount));

    if(!vertexCount || !faceCount)
    {
        return NullFC;
    }

    if(strstr(head, "ST"))
    {
        hasTexCoords = true;
    }

    if(strstr(head, "C"))
    {
        hasColors = true;
    }

    if(strstr(head, "N"))
    {
        hasNormals = true;
    }

    if(strstr(head, "4"))
    {
        has4DimPoints = true;
    }

    if(strstr(head, "nOFF"))
    {
        int ndim;
        
        is >> ndim;
        
        if(ndim != 3)
        {
            FWARNING(("OFFSceneFileType::read: nOFF with ndim != 3 not supported.\n"));
            return NullFC;
        }
    }
    
    if(has4DimPoints)
    {
         FWARNING(("OFFSceneFileType::read: 4D points not supported.\n"));
        return NullFC;       
    }
    
    
    //-------------------------------------------------------------------
    // create the OSG objects
    root = Node::create();
    geo = Geometry::create();
    points = GeoPositions3f::create();
    index = GeoIndicesUI32::create();
    lens = GeoPLengthsUI32::create();
    type = GeoPTypesUI8::create();
    mat = SimpleMaterial::create();
    if (hasNormals)
        norms = GeoNormals3f::create();
    if (hasColors)
        colors = GeoColors4f::create();
    if (hasTexCoords)
        texcoords = GeoTexCoords2f::create();

    beginEditCP(mat);
    {
        mat->setDiffuse(Color3f(0.42, 0.42, 0.52));
        mat->setSpecular(Color3f(1, 1, 1));
        mat->setShininess(20);
    }
    endEditCP(mat);

    beginEditCP(root, Node::CoreFieldMask);
    {
        root->setCore(geo);
    }
    endEditCP(root, Node::CoreFieldMask);

    beginEditCP(geo);
    {
        geo->setPositions(points);
        geo->setIndices(index);
        geo->setLengths(lens);
        geo->setTypes(type);
        geo->setMaterial(mat);
        if (hasNormals)
            geo->setNormals(norms);
        if (hasColors)
            geo->setColors(colors);
        if (hasTexCoords)
            geo->setTexCoords(texcoords);
            
    }
    endEditCP(geo);

    //-------------------------------------------------------------------
    // read/set the points
    beginEditCP(points);
    if(hasNormals)
        beginEditCP(norms);
    if(hasColors)
        beginEditCP(colors);
    if(hasTexCoords)
        beginEditCP(texcoords);
        
    {
        for(i = 0; (!is.eof()) && (i < vertexCount); i++)
        {
            SceneFileHandler::the().updateReadProgress();
            is >> x >> y >> z;
            point.setValues(Real32(x), Real32(y), Real32(z));
            points->push_back(point);
            
            if(hasNormals)
            {
                is >> x >> y >> z;
                norm.setValues(Real32(x), Real32(y), Real32(z));
                norms->push_back(norm);
            }
            
            if(hasColors)
            {
                is >> x >> y >> z >> a;
                color.setValuesRGBA(Real32(x), 
                                    Real32(y), 
                                    Real32(z), 
                                    Real32(a));
                colors->getField().push_back(color);
            }
            
            if(hasTexCoords)
            {
                is >> x >> y;
                texcoord.setValues(Real32(x), Real32(y));
                texcoords->push_back(texcoord);
            }
        }
    }
    endEditCP(points);
    if(hasNormals)
        endEditCP(norms);
    if(hasColors)
        endEditCP(colors);
    if(hasTexCoords)
        endEditCP(texcoords);

    //-------------------------------------------------------------------
    // read the faces
    // TODO; should we 'reserve' some index mem (3,4,..) ?
    faceVec.resize(faceCount);
    triCount = 0;
    for(i = 0; (!is.eof()) && (i < faceCount); i++)
    {
        is >> n;
        if(n >= 0)
        {
            triCount += n - 2;
            for(j = 0; (!is.eof()) && (j < n); j++)
            {
                is >> k;
                if((k >= 0) && (k < vertexCount))
                    faceVec[i].push_back(k);
                else
                {
                    FFATAL(("Invalid vertex index %d in face %d\n", k, i
                           ));
                }
            }
            is.ignore(1000, '\n');
        }
        else
        {
            FFATAL(("Invalid face vec num %d\n", n));
        }
    }

    //-------------------------------------------------------------------
    // set the faces
    for(i = 3; i <= 5; i++)
    {
        n = 0;
        for(j = 0; j < faceCount; j++)
        {
            fN = faceVec[j].size();
            if(fN >= 5)
                fN = 5;
            if(fN == i)
            {
                n += vN = faceVec[j].size();
                for(k = vN - 1; k >= 0; k--)
                {
                    index->getFieldPtr()->push_back(faceVec[j][k]);
                }

                if(i == 5)
                {
                    beginEditCP(lens);
                    {
                        lens->push_back(n);
                    }
                    endEditCP(lens);

                    beginEditCP(type, FieldBits::AllFields);
                    {
                        type->push_back(GL_POLYGON);
                    }
                    endEditCP(type, FieldBits::AllFields);
                }
            }
        }

        if(n)
        {
            switch(i)
            {
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

            if(pType)
            {
                beginEditCP(lens);
                {
                    lens->push_back(n);
                }
                endEditCP(lens);

                beginEditCP(type, FieldBits::AllFields);
                {
                    type->push_back(pType);
                }
                endEditCP(type, FieldBits::AllFields);
            }
        }
    }

    FNOTICE(("Number of triangle read: %d\n", triCount));

    createSharedIndex(geo);
    if(!hasNormals)
        calcVertexNormals(geo);

    SceneFileHandler::the().updateReadProgress(100);
    return root;
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
// Function name: OFFSceneFileType
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
OFFSceneFileType::OFFSceneFileType(const Char8 *suffixArray[],
                                   UInt16 suffixByteCount, bool override,
                                   UInt32 overridePriority,
                                   UInt32 flags) :
    SceneFileType(suffixArray, suffixByteCount,
                  override, overridePriority, flags)
{
}

//----------------------------
// Function name: OFFSceneFileType
//----------------------------
//
//Parameters:
//p: const OFFSceneFileType &obj
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
OFFSceneFileType::OFFSceneFileType(const OFFSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

//----------------------------
// Function name: ~OFFSceneFileType
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
OFFSceneFileType &OFFSceneFileType::the(void)
{
    return _the;
}

/* */
OFFSceneFileType::~OFFSceneFileType(void)
{
    return;
}

/* */
const Char8 *OFFSceneFileType::getName(void) const
{
    return "Geomview Geometry";
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
    static Char8 cvsid_hpp[] = OSGOFFSCENEFILETYPE_HEADER_CVSID;
}
