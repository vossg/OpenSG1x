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
#include <string.h>

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
#include <OSGGroup.h>
#include <OSGSceneFileHandler.h>

#include "OSGSLPSceneFileType.h"

OSG_USING_NAMESPACE

/*! \class osg::SLPSceneFileType
    \ingroup GrpSystemFileIO

*/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
const Char8 *SLPSceneFileType::     _suffixA[] = { "slp" };

SLPSceneFileType SLPSceneFileType:: _the(_suffixA,
                                         sizeof(_suffixA),
                                         false,
                                         10,
                                         SceneFileType::OSG_READ_SUPPORTED);

//------------------------------
NodePtr SLPSceneFileType::read(std::istream &is, const Char8 *) const
{
    char token[9];
    std::string tmpName; 
    NodePtr             root;
    GroupPtr            actGroup;
    GeometryPtr         geo;
    Pnt3f               point;
    Vec3f               norm;
    Color3f             meshcolor;
    Real64              r, g, b;
    Real64 n1x, n1y, n1z, n2x, n2y, n2z, n3x, n3y, n3z;
    Real64 v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
 
    std::vector<SLPFace> theFaces;
    int finished = 0;
    int parseResult = 0;

    GeoPositions3fPtr   points;
    GeoIndicesUI32Ptr   index;
    GeoPLengthsPtr      lens;
    GeoPTypesPtr        type;
    GeoNormals3fPtr     norms;
    GeoColors3fPtr      colors;
    SimpleMaterialPtr   mat;
 
    if(!is)
    {
        return NullFC;
    }

    root = Node::create();
    actGroup = Group::create();
    beginEditCP(root, Node::CoreFieldMask | Node::ChildrenFieldMask);
    root->setCore(actGroup);
    while ((finished == 0) && (! (is.eof())))
    {
        SceneFileHandler::the().updateReadProgress();
        // doesn't link on windows :-(
        //strnset(token, ' ',9);
        for(UInt32 i=0;i<9;++i)
        {
            if(token[i] == '\0')
                break;
            token[i] = ' ';
        }

        is >> token;
        for(UInt32 i = 0; i < strlen(token); ++i)
        {
            token[i] = toupper(token[i]);
        }
        if (strcmp(token, "SOLID") == 0)
            is >> tmpName;

        else if (strcmp(token, "COLOR") == 0)
        {
            if (!theFaces.empty())
            {
                // we have filled a mesh, add it now to OpenSG

                geo = Geometry::create();
                points = GeoPositions3f::create();
                norms = GeoNormals3f::create();
                index = GeoIndicesUI32::create();
                lens = GeoPLengthsUI32::create();
                type = GeoPTypesUI8::create();
                mat = SimpleMaterial::create();

                beginEditCP(type);
                {
                     type->addValue( GL_TRIANGLES );
                }
                endEditCP(type);
 
                // nb of vertex
                beginEditCP(lens);
                {
                    lens->addValue(theFaces.size()*3);
                }
                endEditCP(lens);
                //-------------------------------------------------------------------
                // set the points and normals
                std::vector<SLPFace>::iterator actIt, endIt;
                actIt = theFaces.begin();
                endIt = theFaces.end();

                beginEditCP(points);
                beginEditCP(norms);
                while (actIt != endIt)
                {
                    points->addValue(Pnt3f(actIt->v1x, actIt->v1y, actIt->v1z));
                    points->addValue(Pnt3f(actIt->v2x, actIt->v2y, actIt->v2z));
                    points->addValue(Pnt3f(actIt->v3x, actIt->v3y, actIt->v3z));
                    norms->addValue(Vec3f(actIt->n1x, actIt->n1y, actIt->n1z));
                    norms->addValue(Vec3f(actIt->n2x, actIt->n2y, actIt->n2z));
                    norms->addValue(Vec3f(actIt->n3x, actIt->n3y, actIt->n3z));
                    ++actIt;
                }
                endEditCP(norms);
                endEditCP(points);

                beginEditCP(mat);
                {
                    mat->setAmbient(Color3f(0.0,0.0,0.0));
                    mat->setDiffuse(meshcolor);
                    mat->setEmission(Color3f(0.0,0.0,0.0));
                    mat->setSpecular(Color3f(0.8,0.8,0.8));
                    mat->setShininess(100);
                    mat->setTransparency(0);
                    mat->setColorMaterial(GL_NONE);
                }
                endEditCP(mat);

                beginEditCP(geo);
                {
                    geo->setTypes    (type);
                    geo->setLengths  (lens);
                    geo->setPositions(points);
                     geo->setNormals  (norms);
                    geo->setMaterial(mat);
                }
                
                NodePtr n = Node::create();
                beginEditCP(n, Node::CoreFieldMask);
                {
                    n->setCore(geo);
                }
                endEditCP  (n, Node::CoreFieldMask);
 
                root->addChild( n );
                
                theFaces.clear();
            }
            is >> r >> g >> b;
            meshcolor.setValuesRGB(r, g, b);
        }
        else if (strcmp(token, "FACET") == 0)
        {
            SLPFace tmpFace;
            is >> token >> tmpFace.n1x >> tmpFace.n1y >> tmpFace.n1z;
            is >> token >> tmpFace.n2x >> tmpFace.n2y >> tmpFace.n2z;
            is >> token >> tmpFace.n3x >> tmpFace.n3y >> tmpFace.n3z;

            is >> token >> token;                // skip outer loop
            is >> token >> tmpFace.v1x >> tmpFace.v1y >> tmpFace.v1z;
            is >> token >> tmpFace.v2x >> tmpFace.v2y >> tmpFace.v2z;
            is >> token >> tmpFace.v3x >> tmpFace.v3y >> tmpFace.v3z;
            is >> token;                        // skip endloop
            is >> token;                        // skip endfacet
            theFaces.push_back(tmpFace);
        }
        else if (strcmp(token, "ENDSOLID") == 0)
        {
            if (!theFaces.empty())
            {
                geo = Geometry::create();
                points = GeoPositions3f::create();
                norms = GeoNormals3f::create();
                index = GeoIndicesUI32::create();
                lens = GeoPLengthsUI32::create();
                type = GeoPTypesUI8::create();
                mat = SimpleMaterial::create();

                beginEditCP(type);
                {
                     type->addValue( GL_TRIANGLES );
                }
                endEditCP(type);
 
                // nb of vertex
                beginEditCP(lens);
                {
                    lens->addValue(theFaces.size()*3);
                }
                endEditCP(lens);
                //-------------------------------------------------------------------
                // set the points and normals
                std::vector<SLPFace>::iterator actIt, endIt;
                actIt = theFaces.begin();
                endIt = theFaces.end();

                beginEditCP(points);
                beginEditCP(norms);
                while (actIt != endIt)
                {
                    points->addValue(Pnt3f(actIt->v1x, actIt->v1y, actIt->v1z));
                    points->addValue(Pnt3f(actIt->v2x, actIt->v2y, actIt->v2z));
                    points->addValue(Pnt3f(actIt->v3x, actIt->v3y, actIt->v3z));
                    norms->addValue(Vec3f(actIt->n1x, actIt->n1y, actIt->n1z));
                    norms->addValue(Vec3f(actIt->n2x, actIt->n2y, actIt->n2z));
                    norms->addValue(Vec3f(actIt->n3x, actIt->n3y, actIt->n3z));
                    ++actIt;
                }
                endEditCP(norms);
                endEditCP(points);

                beginEditCP(mat);
                {
                    mat->setAmbient(Color3f(0.0,0.0,0.0));
                    mat->setDiffuse(meshcolor);
                    mat->setEmission(Color3f(0.0,0.0,0.0));
                    mat->setSpecular(Color3f(1.0,1.0,1.0));
                    mat->setShininess(10);
                    mat->setTransparency(0);
                    mat->setColorMaterial(GL_NONE);
                }
                endEditCP(mat);

                beginEditCP(geo);
                {
                    geo->setTypes    (type);
                    geo->setLengths  (lens);
                    geo->setPositions(points);
                    geo->setNormals  (norms);
                    geo->setMaterial(mat);
                }

                NodePtr n = Node::create();
                beginEditCP(n, Node::CoreFieldMask);
                {
                    n->setCore(geo);
                }
                endEditCP  (n, Node::CoreFieldMask);
 
                root->addChild( n );
                
                theFaces.clear();
                finished = 1;    
            }
        }
    }
    endEditCP(root);

    SceneFileHandler::the().updateReadProgress(100);
    return root;
}

//------------------------------
SLPSceneFileType::SLPSceneFileType(const Char8 *suffixArray[],
                                   UInt16 suffixByteCount, bool override,
                                   UInt32 overridePriority,
                                   UInt32 flags) :
    SceneFileType(suffixArray, suffixByteCount,
                  override, overridePriority, flags)
{
}

//------------------------------
SLPSceneFileType::SLPSceneFileType(const SLPSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

//------------------------------
SLPSceneFileType &SLPSceneFileType::the(void)
{
    return _the;
}

/* */
SLPSceneFileType::~SLPSceneFileType(void)
{
    return;
}

/* */
const Char8 *SLPSceneFileType::getName(void) const
{
    return "Pro/Engineer Render Geometry";
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGSLPSceneFileType.cpp,v 1.3 2007/01/12 16:59:05 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGSLPSCENEFILETYPE_HEADER_CVSID;
}
