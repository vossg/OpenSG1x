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

#include "OSGRAWSceneFileType.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! \class osg::RAWSceneFileType
    \ingroup GrpSystemFileIO

 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

const Char8            *RAWSceneFileType::_suffixA[] = {"raw"};

      RAWSceneFileType  RAWSceneFileType::_the         (_suffixA,
                                                        sizeof(_suffixA),
                                                        false,
                                                        10,
                                                        SceneFileType::OSG_READ_SUPPORTED);

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

NodePtr RAWSceneFileType::read(std::istream &is, const Char8 *) const
{
    NodePtr root;
    GeometryPtr geo;
    GeoPositions3f::PtrType points;
    GeoNormals3f::PtrType   normals;
    GeoIndicesUI32Ptr index;
    GeoPLengthsUI32Ptr lens;
    GeoPTypesUI8Ptr type;
    Vec3f vec[3];
    UInt32 i = 0, n, triCount = 0;
    Real32 x,y,z;

    fprintf(stderr, "Loading using Loader 0\n");

    if(is)
    {
        root = Node::create();
        geo = Geometry::create();

        beginEditCP(geo, FieldBits::AllFields);
        beginEditCP(root, Node::CoreFieldMask);
        root->setCore( geo );
        endEditCP(root, Node::CoreFieldMask);

        points = GeoPositions3f::create();
        geo->setPositions( points );
        normals = GeoNormals3f::create();
        geo->setNormals ( normals );

        triCount = i = 0;

        beginEditCP(points,  FieldBits::AllFields);
        beginEditCP(normals, FieldBits::AllFields);

        while (1) {
            is >> x >> y >> z;
            if (is.eof())
                break;
            else {
                points->getFieldPtr()->push_back( Pnt3f ( x, y, z) );
                vec[i].setValues(x,y,z);
                if (i == 2) {
                    vec[0] -= vec[1];
                    vec[1] -= vec[2];
                    vec[0].crossThis(vec[1]);
                    vec[0].normalize();

                    normals->getFieldPtr()->push_back ( vec[0] );
                    normals->getFieldPtr()->push_back ( vec[0] );
                    normals->getFieldPtr()->push_back ( vec[0] );

                    i = 0;
                    triCount++;
                }
                else
                    i++;
            }
        }

        endEditCP(points,  FieldBits::AllFields);
        endEditCP(normals, FieldBits::AllFields);

        if (triCount)
        {

            index = GeoIndicesUI32::create();
            geo->setIndices( index );
            beginEditCP(index, FieldBits::AllFields);
            n = triCount * 3;
            for (i = 0; i < n; i++)
                index->getFieldPtr()->push_back( i );
            endEditCP(index, FieldBits::AllFields);


            lens = GeoPLengthsUI32::create();
            geo->setLengths( lens );
            beginEditCP(lens, FieldBits::AllFields);
            lens->push_back( n );
            endEditCP(lens, FieldBits::AllFields);

            type = GeoPTypesUI8::create();
            geo->setTypes( type );
            beginEditCP(type, FieldBits::AllFields);
            type->push_back( GL_TRIANGLES );
            endEditCP(type, FieldBits::AllFields);
        }

        SimpleMaterialPtr mat = SimpleMaterial::create();
        beginEditCP(mat, FieldBits::AllFields);
        mat->setDiffuse( Color3f( .8, .8, .8 ) );
        mat->setSpecular( Color3f( 1, 1, 1 ) );
        mat->setShininess( 20 );
        endEditCP(mat, FieldBits::AllFields);

        geo->setMaterial( mat );
        endEditCP(geo, FieldBits::AllFields);
    }

    if (triCount)
        SNOTICE << triCount << " triangle read " << std::endl;

    return root;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

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

RAWSceneFileType::RAWSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority,
                                         UInt32  flags) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority,
                  flags)
{
}

RAWSceneFileType &RAWSceneFileType::the(void)
{
    return _the;
}

const Char8 *RAWSceneFileType::getName(void) const
{
    return "RAW Geometry";
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

RAWSceneFileType::RAWSceneFileType(const RAWSceneFileType &obj) :
    SceneFileType(obj)
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
    static Char8 cvsid_hpp[] = OSGRAWSCENEFILETYPE_HEADER_CVSID;
}

