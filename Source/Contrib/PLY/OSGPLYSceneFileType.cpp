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
 *                                                                           *
\*---------------------------------------------------------------------------*/

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
#include <OSGRefPtr.h>

#include "OSGPLYSceneFileType.h"
#include "OSGply.h"

OSG_USING_NAMESPACE


/*! \class osg::PLYSceneFileType
    \ingroup GrpSystemFileIO
 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)SG
#endif

static const Char8* suffixA[] = { "ply" };

PLYSceneFileType PLYSceneFileType::_the(suffixA,
                                        sizeof(suffixA),
                                        false,
                                        10,
                                        SceneFileType::OSG_READ_SUPPORTED);


const Char8 *PLYSceneFileType::getName(void) const
{
    return "PLY"; // ?
}

struct Vertex {
    float x;
    float y;
    float z;
};

struct Face {
    unsigned char nverts;
    int* verts;
};

static PlyProperty vert_props[] = { /* list of property information for a vertex */
  {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0},
};

static PlyProperty face_props[] = { /* list of property information for a vertex */
  {"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
                     1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)},
};


NodePtr PLYSceneFileType::read(std::istream& is, const Char8* /*fileNameOrExtension*/) const
{
    std::vector<std::string> elems;
    PlyFile* ply = ply_read(&is, elems);
    if (!ply)
    {
        return NullFC;
    }

    GeoPositions3fPtr pos3f;
    GeoIndicesUI32Ptr indices;

    for (size_t i = 0; i < elems.size(); ++i)
    {
        const std::string& elem_name = elems[i];
        int num_elems;
        std::vector<PlyProperty> props;
        if (!ply_get_element_description(ply, elem_name, &num_elems, props)) {
            continue;
        }

        if ("vertex" == elem_name)
        {
            pos3f = GeoPositions3f::create();
            beginEditCP(pos3f);

            MFPnt3f& data = pos3f->getField();
            data.resize(num_elems);

            ply_get_property(ply, elem_name, &vert_props[0]);
            ply_get_property(ply, elem_name, &vert_props[1]);
            ply_get_property(ply, elem_name, &vert_props[2]);

            for (int j = 0; j < num_elems; ++j)
            {
                Vertex vertex = { 0, 0, 0 };
                ply_get_element(ply, &vertex);
                data[j] = Pnt3f(vertex.x, vertex.y, vertex.z);
            }

            endEditCP(pos3f);
        }
        else if ("face" == elem_name)
        {
            indices = GeoIndicesUI32::create();
            beginEditCP(indices);

            MFUInt32& data = indices->getField();
            // At least three vertices per face...
            data.reserve(num_elems * 3);

            ply_get_property(ply, elem_name, &face_props[0]);

            for (int j = 0; j < num_elems; ++j)
            {
                Face f;
                ply_get_element(ply, &f);
                if (f.nverts < 3)
                {
                    FINFO(("PLYSceneFileType::read: face with less than 3 vertices?"));
                    continue;
                }

                // Treat faces as triangle strips.
                int v1 = f.verts[0];
                int v2 = f.verts[1];
                for (int k = 2; k < f.nverts; ++k)
                {
                    int v3 = f.verts[k];
                    data.push_back(v1);
                    data.push_back(v2);
                    data.push_back(v3);
                    v1 = v2;
                    v2 = v3;
                }

                free(f.verts);
            }

            endEditCP(indices);
        }
    }

    ply_close(ply);

    if (pos3f != NullFC && indices != NullFC)
    {
        GeometryPtr geo = osg::Geometry::create();

        GeoPTypesUI8Ptr types = osg::GeoPTypesUI8::create();
        beginEditCP(types);
        types->addValue(GL_TRIANGLES);
        endEditCP(types);

        GeoPLengthsUI32Ptr lengths = osg::GeoPLengthsUI32::create();
        beginEditCP(lengths);
        lengths->addValue(indices->getSize());
        endEditCP(lengths);
        
        beginEditCP(geo);
        geo->setTypes(types);
        geo->setLengths(lengths);
        geo->setPositions(pos3f);
        geo->setIndices(indices);
        endEditCP(geo);
        calcVertexNormals(geo);

        return makeNodeFor(geo);
    }
    else
    {
        // Clean up if necessary.
        RefPtr<FieldContainerPtr>(pos3f);
        RefPtr<FieldContainerPtr>(indices);
        return NullFC;
    }
}



PLYSceneFileType::PLYSceneFileType(const Char8*  suffixArray[],
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

PLYSceneFileType::PLYSceneFileType(const PLYSceneFileType& obj) :
    SceneFileType(obj)
{
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGPLYSceneFileType.cpp,v 1.1 2005/06/08 19:12:03 dirk Exp $";
    static Char8 cvsid_hpp[] = OSGPLYSCENEFILETYPE_HEADER_CVSID;
}
