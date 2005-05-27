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


#include <OSGGeoTypeGraphOp.h>
#include <OSGLog.h>

OSG_USING_NAMESPACE

    
GeoTypeGraphOp::GeoTypeGraphOp(const char* name)
    : SingleTypeGraphOp<Geometry>(name)
{
}

GraphOp* GeoTypeGraphOp::create()
{
    return new GeoTypeGraphOp();
}


bool GeoTypeGraphOp::travNodeEnter(NodePtr node)
{
    GeometryPtr geo = GeometryPtr::dcast(node->getCore());

    if(geo == NullFC)
    {
        return true;
    }

    GeoPositionsPtr positions = geo->getPositions();

    GeoNormalsPtr   normals   = geo->getNormals();
    GeoNormals3fPtr normals3f = GeoNormals3fPtr::dcast(normals);
    if (normals3f != NullFC) {
        MFVec3f& data = normals3f->getField();
        
        GeoNormals3bPtr normals3b = GeoNormals3b::create();
        beginEditCP(normals3b);
        for (size_t i = 0; i < data.size(); ++i) {
            Vec3f vec = data[i];
            vec *= (0.9f / vec.length());
            normals3b->push_back(vec);
        }
        endEditCP(normals3b);

        beginEditCP(geo);
        geo->setNormals(normals3b);
        endEditCP(geo);
    }

    GeoColorsPtr    colors    = geo->getColors();
    GeoColorsPtr    scolors   = geo->getSecondaryColors();
    
    return true;
}


bool GeoTypeGraphOp::travNodeLeave(NodePtr)
{
    return true;
}
