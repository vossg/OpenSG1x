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

#include "OSGBlendShapeDeformer.h"
#include "OSGDeformableGeometry.h"

OSG_USING_NAMESPACE

/*! \class osg::BlendShapeDeformer
Implements mesh blend shape deformation.
*/

/*----------------------- constructors & destructors ----------------------*/

BlendShapeDeformer::BlendShapeDeformer(void) :
    Inherited()
{
}

BlendShapeDeformer::BlendShapeDeformer(const BlendShapeDeformer &source) :
    Inherited(source)
{
}

BlendShapeDeformer::~BlendShapeDeformer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BlendShapeDeformer::initMethod (void)
{
}

void BlendShapeDeformer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BlendShapeDeformer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BlendShapeDeformer NI" << std::endl;
}

void BlendShapeDeformer::deform () {
    if (getGeometry() == NullFC)
        return;
    DeformableGeometryPtr geo = osg::DeformableGeometryPtr::dcast(getGeometry()->getCore());
    if (geo == NullFC)
        return;
    GeoPositionsPtr positions = geo->getPositions();
    GeoPositionsPtr base_positions = geo->getBasePositions();
    GeoNormalsPtr normals = geo->getNormals();
    GeoNormalsPtr base_normals = geo->getBaseNormals();
    Pnt3f point;
    Vec3f vec;
    UInt32 vertex_index, normal_index;
    UInt32 count = getVertexIndices().size();
    // FIXME: Assumes we are the first deformer because we use base arrays.
    for (UInt32 i = 0; i < count; i++) {
        vertex_index = getVertexIndices(i);
        point = positions->getValue(vertex_index);
        point += getWeight(getTargetIndices(i))  * (getTargetVertices(i) - base_positions->getValue(vertex_index));
        positions->setValue(point, vertex_index);
    }

    count = getNormalIndices().size();
    for (UInt32 i = 0; i < count; i++) {
        normal_index = getNormalIndices(i);
        vec = normals->getValue(normal_index);
        vec += getWeight(getNormalTargetIndices(i))  * (getTargetNormals(i) - base_normals->getValue(normal_index));
        normals->setValue(vec, normal_index);
    }
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGBlendShapeDeformer.cpp,v 1.3 2003/04/28 23:55:49 michael Exp $";
    static Char8 cvsid_hpp       [] = OSGBLENDSHAPEDEFORMERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBLENDSHAPEDEFORMERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBLENDSHAPEDEFORMERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

