/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGSkinDeformer.h"
#include <OSGGeometry.h>
#include "OSGDeformableGeometry.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

OSG_USING_NAMESPACE

/*! \class osg::SkinDeformer
Implements mesh skin deformation using a skeleton. Intended to recreate the functionality of Maya's skinCluster node. The vertexIndices, influenceIndices, and influenceWeights arrays will all have the same number of elements. which should allow looping through them all quickly with no conditional statements.
*/

/*----------------------- constructors & destructors ----------------------*/

SkinDeformer::SkinDeformer(void) :
    Inherited()
{
}

SkinDeformer::SkinDeformer(const SkinDeformer &source) :
    Inherited(source)
{
}

SkinDeformer::~SkinDeformer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkinDeformer::initMethod (void)
{
}

void SkinDeformer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SkinDeformer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkinDeformer NI" << std::endl;
}

void SkinDeformer::deform () {
#if 1
    if (getGeometry() == NullFC)
        return;
    DeformableGeometryPtr geo = osg::DeformableGeometryPtr::dcast(getGeometry()->getCore());
    if (geo == NullFC)
        return;
    //Matrix geometry_to_world = getGeometry()->getToWorld();
    //Matrix world_to_geometry = geometry_to_world;
    //world_to_geometry.invert();
    GeoPositionsPtr positions = geo->getPositions();
    GeoNormalsPtr normals = geo->getNormals();
    MFUInt32 * vertex_indices = getMFVertexIndices();
    MFUInt32 * normal_indices = getMFNormalIndices();
    UInt32 vertex_index, previous_vertex_index;
    UInt32 normal_index, previous_normal_index;
    Vec3f point, normal;
    Pnt3f base_point, deformed_point;
    Vec3f base_vec, deformed_vec;
    UInt16 infl;
    Pnt3f zero_point(0.0f, 0.0f, 0.0f);
    Vec3f zero_vec(0.0f, 0.0f, 0.0f);

    vector<Matrix> influences(getMFInfluences()->size()); // FIXME: Don't allocate memory in deform().
    for (unsigned int i = 0; i < getMFInfluences()->size(); i++) {
        Matrix base(getBaseMatrices(i));
        base.invert();
        //base.mult(geometry_to_world);
        Matrix joint(getInfluences(i)->getToWorld());
        joint.mult(base);
        //joint.multLeft(world_to_geometry);
        influences[i] = joint;
    }

    UInt32 count = vertex_indices->size();
    for (unsigned int i = 0; i < count; i++) {
        vertex_index = vertex_indices->getValue(i);
        if (i == 0 || vertex_index != previous_vertex_index) {
            base_point = positions->getValue(vertex_index);
            point = zero_vec;
            previous_vertex_index = vertex_index;
        }
        infl = getInfluenceIndices(i);
        Matrix & joint = influences[infl];
        joint.multMatrixPnt(base_point, deformed_point);
        point += getInfluenceWeights(i) * deformed_point - zero_point;
        positions->setValue(point, vertex_index);
    }

    count = normal_indices->size();
    for (unsigned int i = 0; i < count; i++) {
        normal_index = normal_indices->getValue(i);
        if (i == 0 || normal_index != previous_normal_index) {
            base_vec = normals->getValue(normal_index);
            normal = zero_vec;
            previous_normal_index = normal_index;
        }
        infl = getNormalInfluenceIndices(i);
        Matrix & joint = influences[infl];
        joint.multMatrixVec(base_vec, deformed_vec); // FIXME: Use inverse transpose.
        normal += getNormalInfluenceWeights(i) * deformed_vec;
        normals->setValue(normal, normal_index);
    }
#endif
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSkinDeformer.cpp,v 1.3 2003/04/28 23:55:49 michael Exp $";
    static Char8 cvsid_hpp       [] = OSGSKINDEFORMERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSKINDEFORMERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSKINDEFORMERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

