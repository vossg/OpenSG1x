/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include <OSGLog.h>
#include <OSGQuaternion.h>
#include <OSGSimpleMaterial.h>
#include <OSGTriangleIterator.h>
#include "OSGSimpleGeometry.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Stores the default material used by the Simple Geometry.
*/
static SimpleMaterialPtr _defaultMaterial;

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Access the default Material for Simple Geometry. Also useful whenever 
    an arbitrary material is needed.
*/

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr OSG::getDefaultMaterial(void)
{
    if(_defaultMaterial == NullFC)
    {
        _defaultMaterial = SimpleMaterial::create();

        beginEditCP(_defaultMaterial);
        _defaultMaterial->setDiffuse(Color3f(.7,.7,.5));
        _defaultMaterial->setAmbient(Color3f(0.1,0.1,0.1));
        _defaultMaterial->setSpecular(Color3f(1,1,1));
        _defaultMaterial->setShininess(20);
        endEditCP  (_defaultMaterial);

        addRefCP(_defaultMaterial);
    }
    
    return _defaultMaterial;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Stores the default unlit material.
*/
static SimpleMaterialPtr _defaultUnlitMaterial;

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Access the default unlit Material. Useful whenever 
    an arbitrary unlit material is needed.
*/
OSG_SYSTEMLIB_DLLMAPPING MaterialPtr OSG::getDefaultUnlitMaterial(void)
{
    if(_defaultUnlitMaterial == NullFC)
    {
        _defaultUnlitMaterial = SimpleMaterial::create();

        beginEditCP(_defaultUnlitMaterial);
        _defaultUnlitMaterial->setDiffuse(Color3f(1,1,.5));
        _defaultUnlitMaterial->setLit(false);
        endEditCP  (_defaultUnlitMaterial);

        addRefCP(_defaultUnlitMaterial);
	}
    
    return _defaultUnlitMaterial;
}

// The Simple Geometry creation functions

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakePlane creates a plane in the x/y plane. It spans the [-\a xsize /2,\a
    xsize /2]x [-\a ysize /2,\a ysize/2] area and is subdivided into \a hor * 
    \a vert quads.
*/

NodePtr OSG::makePlane(Real32 xsize, Real32 ysize, UInt16 hor, UInt16 vert)
{
    GeometryPtr pGeo = makePlaneGeo(xsize, ysize, hor, vert);
 
    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);

    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makePlane. 
*/

GeometryPtr OSG::makePlaneGeo(Real32 xsize, Real32 ysize, 
                               UInt16 hor,   UInt16 vert)
{
    if(! hor || ! vert)
    {
        SWARNING << "makePlane: illegal parameters hor=" << hor << ", vert="
                 << vert << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr    pnts  = GeoPositions3f::create();
    GeoNormals3fPtr      norms = GeoNormals3f::create();
    GeoTexCoords2fPtr    tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr    index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr   lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr      types = GeoPTypesUI8::create();     
    
    UInt16 x,y;
    Real32 xstep,ystep;
    xstep=xsize / hor;
    ystep=ysize / vert;

    // calc the vertices

    GeoPositions3f::StoredFieldType  * p  = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType    * n  = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType  * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    for(y = 0; y <= vert; y++)
    {
        for(x = 0; x <= hor; x++)
        {
            p->push_back(Pnt3f(x * xstep - xsize / 2, y * ystep - ysize / 2, 0));
            n->push_back(Vec3f(0, 0, 1));
            tx->push_back(Vec2f(x / (Real32) hor, y / (Real32) vert));
        }
    }

    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType    * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType   * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType      * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    for(y = 0; y < vert; y++)
    {
        t->push_back(GL_TRIANGLE_STRIP);
        l->push_back(2 * (hor + 1));
        
        for(x = 0; x <= hor; x++)
        {
            i->push_back((y + 1) * (hor + 1) + x);
            i->push_back( y      * (hor + 1) + x);
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal   |
                                    Geometry::MapTexCoords);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);
    
    return geo;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeCone creates a cone. It's center sits in the origin of the x/z plane. 
    It's radius is \a radius and the base is subdivided into \a sides parts.

    Each part of the cone (bottom cap, sides) can be enabled or disabled.

*/

NodePtr OSG::makeCone(Real32 height, 
                      Real32 botradius, 
                      UInt16 sides, 
                      bool   doSide, 
                      bool   doBottom)
{
    return makeConicalFrustum(height, 
                              0, 
                              botradius, 
                              sides, 
                              doSide, 
                              false, 
                              doBottom);
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeCone. 
*/

GeometryPtr OSG::makeConeGeo(Real32 height, 
                             Real32 botradius, 
                             UInt16 sides, 
                             bool   doSide, 
                             bool   doBottom)
{
    return makeConicalFrustumGeo(height, 
                                 0, 
                                 botradius, 
                                 sides, 
                                 doSide, 
                                 false, 
                                 doBottom);
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeCylinder creates a cylinder. It's center sits in the origin of the 
    x/z plane. It's radius is \a radius and the base is subdivided into \a
    sides parts.

    Each part of the cylinder (top cap, bottom cap, sides) can be enabled or
    disabled.

*/

NodePtr OSG::makeCylinder(Real32 height, 
                          Real32 radius,
                          UInt16 sides, 
                          bool   doSide, 
                          bool   doTop, 
                          bool   doBottom)
{
    return makeConicalFrustum(height, 
                              radius, 
                              radius, 
                              sides, 
                              doSide, 
                              doTop, 
                              doBottom);
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeCylinder. 
*/

GeometryPtr OSG::makeCylinderGeo(Real32 height, 
                                 Real32 radius,
                                 UInt16 sides, 
                                 bool   doSide, 
                                 bool   doTop, 
                                 bool   doBottom)
{
    return makeConicalFrustumGeo(height, 
                                 radius, 
                                 radius, 
                                 sides, 
                                 doSide, 
                                 doTop, 
                                 doBottom);
}


/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeConicalFrustum creates a conical frustum. It's center sits in the
    origin of the x/z plane.  It's height is \a height and the base is
    subdivided into \a sides parts. The top radius is \a topradius, the bottom
    radius \a botradius.

    Each part of the frustum (top cap, bottom cap, sides) can be enabled or
    disabled. Caps forradius 0 are automatically disabled.

*/

NodePtr OSG::makeConicalFrustum(Real32 height, 
                                Real32 topradius, 
                                Real32 botradius, 
                                UInt16 sides, 
                                bool   doSide, 
                                bool   doTop, 
                                bool   doBottom)
{
    GeometryPtr pGeo = makeConicalFrustumGeo(height, 
                                             topradius, 
                                             botradius,
                                             sides, 
                                             doSide, 
                                             doTop, 
                                             doBottom);

    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);

    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeConicalFrustum. 
*/

GeometryPtr OSG::makeConicalFrustumGeo(Real32 height, 
                                       Real32 topradius, 
                                       Real32 botradius, 
                                       UInt16 sides, 
                                       bool   doSide, 
                                       bool   doTop, 
                                       bool   doBottom)
{
    if(height <= 0 || topradius < 0 || botradius < 0 || sides < 3)
    {
        SWARNING << "makeConicalFrustum: illegal parameters height=" << height 
                 << ", topradius=" << topradius 
                 << ", botradius=" << botradius 
                 << ", sides=" << sides 
                 << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr     norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr   index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr     types = GeoPTypesUI8::create();     
    
    Int16  j;
    Real32 delta = 2.f * Pi / sides;
    Real32 beta, x, z;
    Real32 incl = (botradius - topradius) / height;
    Real32 nlen = 1.f / osgsqrt(1 + incl * incl);
    
    // vertices

    GeoPositions3f::StoredFieldType     * p  = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType       * n  = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType     * tx = tex->getFieldPtr();

    // faces
    
    GeoIndicesUI32::StoredFieldType     * i  = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType    * l  = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType       * t  = types->getFieldPtr();

    // 
    
    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);
    
    if(doSide)
    {
        UInt32 baseindex = p->size();
        
        for(j = 0; j <= sides; j++)
        {
            beta = j * delta;
            x    =  osgsin(beta);
            z    = -osgcos(beta);         

            p->push_back(Pnt3f(x * topradius, height/2, z * topradius));
            n->push_back(Vec3f(x/nlen, incl/nlen, z/nlen));
            tx->push_back(Vec2f(1.f - j / (Real32) sides, 1));
        }
        
        for(j = 0; j <= sides; j++)
        {
            beta = j * delta;
            x    =  osgsin(beta);
            z    = -osgcos(beta);         

            p->push_back(Pnt3f(x * botradius, -height/2, z * botradius));
            n->push_back(Vec3f(x/nlen, incl/nlen, z/nlen));
            tx->push_back(Vec2f(1.f - j / (Real32) sides, 0));
        }

        t->push_back(GL_TRIANGLE_STRIP);
        l->push_back(2 * (sides + 1));

        for(j = 0; j <= sides; j++) 
        {
                i->push_back(baseindex + sides + 1 + j);
                i->push_back(baseindex + j);
        }
    }
    
    if(doTop && topradius > 0)
    {
        UInt32 baseindex = p->size();
        
        // need to duplicate the points fornow, as we don't have multi-index geo yet
        
        for(j = sides - 1; j >= 0; j--)
        {
            beta = j * delta;
            x    =  topradius * osgsin(beta);
            z    = -topradius * osgcos(beta);        

            p->push_back(Pnt3f(x, height/2, z));
            n->push_back(Vec3f(0, 1, 0));
            tx->push_back(Vec2f(x / topradius / 2 + .5f, -z / topradius / 2 + .5f));
        }

        t->push_back(GL_POLYGON);
        l->push_back(sides);

        for(j = 0; j < sides; j++) 
        {
            i->push_back(baseindex + j);
        }
    }
    
    if(doBottom && botradius > 0 )
    {
        UInt32 baseindex = p->size();
        
        // need to duplicate the points fornow, as we don't have multi-index geo yet
        
        for(j = sides - 1; j >= 0; j--)
        {
            beta = j * delta;
            x    =  botradius * osgsin(beta);
            z    = -botradius * osgcos(beta);      

            p->push_back(Pnt3f(x, -height/2, z));
            n->push_back(Vec3f(0, -1, 0));
            tx->push_back(Vec2f(x / botradius / 2 + .5f, z / botradius / 2 + .5f));
        }

        t->push_back(GL_POLYGON);
        l->push_back(sides);

        for(j = 0; j < sides; j++) 
        {
            i->push_back(baseindex + sides - 1 - j);
        }
    }
    
    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);
    
    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);

    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal   |
                                    Geometry::MapTexCoords);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);

    return geo;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeTorus creates a torus in the x/y plane. Sides are the number of
    subdivisions forthe inner radius, rings forthe outer.

*/

NodePtr OSG::makeTorus(Real32 innerRadius, Real32 outerRadius, UInt16 sides, 
                        UInt16 rings)
{
    GeometryPtr pGeo = makeTorusGeo(innerRadius, outerRadius, sides, rings);
 
    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);

    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeTorus. 
*/

GeometryPtr OSG::makeTorusGeo(Real32 innerRadius, Real32 outerRadius, UInt16 sides, 
                               UInt16 rings)
{
    if(innerRadius <= 0 || outerRadius <= 0 || sides < 3 || rings < 3)
    {
        SWARNING << "makeTorus: illegal parameters innerRadius=" << innerRadius 
                 << ", outerRadius=" << outerRadius 
                 << ", sides=" << sides 
                 << ", rings=" << rings 
                 << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr     norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr   index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr     types = GeoPTypesUI8::create();     
    
    UInt16 a, b;
    Real32 theta, phi;
    Real32 cosTheta, sinTheta;
    Real32 ringDelta, sideDelta;

    // calc the vertices

    GeoPositions3f::StoredFieldType   * p  = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType     * n  = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType   * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    ringDelta = 2.f * Pi / rings;
    sideDelta = 2.f * Pi / sides;

    for(a = 0, theta = 0.0; a <= rings; a++, theta += ringDelta) 
    {
        cosTheta = osgcos(theta);
        sinTheta = osgsin(theta);

        for(b = 0, phi = 0; b <= sides; b++, phi += sideDelta) 
        {
            GLfloat cosPhi, sinPhi, dist;

            cosPhi = osgcos(phi);
            sinPhi = osgsin(phi);
            dist   = outerRadius + innerRadius * cosPhi;

            n->push_back(Vec3f(cosTheta * cosPhi, 
                              -sinTheta * cosPhi, 
                              sinPhi));
            p->push_back(Pnt3f(cosTheta * dist, 
                              -sinTheta * dist, 
                              innerRadius * sinPhi));
            tx->push_back(Vec2f(- a / (Real32) rings, b / (Real32)sides));
        }
    }   

    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType  * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType    * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    for(a = 0; a < sides; a++) 
    {
        t->push_back(GL_TRIANGLE_STRIP);
        l->push_back((rings + 1) * 2);
        
        for(b = 0; b <= rings; b++)
        {
            i->push_back(b * (sides+1) + a);
            i->push_back(b * (sides+1) + a + 1);
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);

    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal   |
                                    Geometry::MapTexCoords);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);
    
    return geo;
}

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

Real32 setVecLen(Vec3f &vec, Real32 length) 
{
    Real32 len = vec.length();
    if(len == 0.0) 
    {
        len = 1;
    } 
    else 
    {
        len = length / len;
    }
    vec *= len;
    
    return length;
}

Real32 calcTexS(Vec3f &n, Real32 theta)
{
    const Real32 TwoPi  = 6.283185307179586;
    const Real32 HalfPi = 1.570796326794897;
    
    Real32 phi = osgatan2(-n[2], n[0]) - HalfPi;

    if (phi <= -Eps)
        phi += TwoPi;
    phi /= TwoPi;
    
    return phi;
}

void addPoint(Pnt3f v, UInt32 index, Real32 radius,
              GeoPositions3f::StoredFieldType *p,
              GeoNormals3f::StoredFieldType   *n,
              GeoTexCoords2f::StoredFieldType *tx)
{
    Vec3f norm(v[0], v[1], v[2]);

    norm.normalize();
    n->push_back(norm);

    Pnt3f pnt(radius * norm);
    p->push_back(pnt);

    Vec2f texCoord;

    // Theta -> v
    texCoord[1] = (Pi - osgacos(norm[1])) / Pi;

    // Phi -> u
    texCoord[0] = calcTexS(norm, texCoord[1]);

    tx->push_back(texCoord);
}

void subdivideTriangle( UInt32 i1, 
                        UInt32 i2, 
                        UInt32 i3,
                        Int32 depth, 
                        GeoPositions3f::StoredFieldType  *p,
                        GeoNormals3f::StoredFieldType    *n,
                        GeoTexCoords2f::StoredFieldType  *tx,
                        GeoIndicesUI32::StoredFieldType  *i,
                        UInt32& z, Real32 radius ) 
{   
    if (depth == 0) 
    {
        i->push_back(i1);
        i->push_back(i1);
        i->push_back(i2);
        i->push_back(i2);
        i->push_back(i3);
        i->push_back(i3);
                            
        return;         
    }

    Pnt3f v1 = (*p)[i1],
          v2 = (*p)[i2],
          v3 = (*p)[i3];
    Pnt3f v12, v23, v31;

    v12 = v1 + (v2 - v1) * .5f;
    v23 = v2 + (v3 - v2) * .5f;
    v31 = v3 + (v1 - v3) * .5f;
    
    v12 /= 2.0f;
    v23 /= 2.0f;
    v31 /= 2.0f;
    
    UInt32 i12 = z++, i23 = z++, i31 = z++;

    addPoint(v12,i12,radius,p,n,tx);
    addPoint(v23,i23,radius,p,n,tx);
    addPoint(v31,i31,radius,p,n,tx);
    
    subdivideTriangle( i1, i12, i31, depth - 1, p,n,tx,i, z, radius);
    subdivideTriangle( i2, i23, i12, depth - 1, p,n,tx,i, z, radius);
    subdivideTriangle( i3, i31, i23, depth - 1, p,n,tx,i, z, radius);
    subdivideTriangle(i12, i23, i31, depth - 1, p,n,tx,i, z, radius);
}

#endif            // exclude from doc

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeSphere creates a sphere centered in the origin. It is created by
    recursive subdivision of an icosahedron, with \a depth giving the number
    of subdivisions and \a radius being the radius.

*/

NodePtr OSG::makeSphere(UInt16 depth, Real32 radius)
{   
    GeometryPtr pGeo = makeSphereGeo(depth, radius);

    if(pGeo == NullFC)
    {
        return NullFC;
    }

    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);    
        
    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeSphere. 
*/

GeometryPtr OSG::makeSphereGeo(UInt16 depth, Real32 radius)
{
    const Real32 X = .525731112119133606;
    const Real32 Z = .850650808352039932;
    const Real32 HalfPi = 1.570796326794897;

    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr     norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr   index = GeoIndicesUI32::create();   
    GeoPLengthsPtr      lens  = GeoPLengthsUI32::create();  
    GeoPTypesPtr        types = GeoPTypesUI8::create();     
    UInt32              j,z;
   
    Vec3f v[12] = { Vec3f(-X, 0.,  Z),
                    Vec3f( X, 0.,  Z),
                    Vec3f(-X, 0., -Z),
                    Vec3f( X, 0., -Z),
                    Vec3f(0.,  Z,  X),
                    Vec3f(0.,  Z, -X),
                    Vec3f(0., -Z,  X),
                    Vec3f(0., -Z, -X),
                    Vec3f( Z,  X, 0.),
                    Vec3f(-Z,  X, 0.),
                    Vec3f( Z, -X, 0.),
                    Vec3f(-Z, -X, 0.)  };

    Quaternion q(Vec3f(0,1,0), osgacos(Z) + HalfPi);
    Matrix mat;

    mat.setTransform(q);

    for (j=0; j<12; j++)
        mat.mult(v[j]);
                
    Int32 tr[20][3] = { {1,4,0},  {4,9,0},  {4,5,9},  {8,5,4},  {1,8,4},
                        {1,10,8}, {10,3,8}, {8,3,5},  {3,2,5},  {3,7,2},
                        {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
                        {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9},  {11,2,7} };                  
                
    GeoPositions3f::StoredFieldType     * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType       * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType    * tx = tex->getFieldPtr();
    GeoIndicesUI32::StoredFieldType     * i = index->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);
    
    // initial sizing to prevent reallocation halfway through
    UInt32 estimatedSize = UInt32(osgpow(4.f, (Real32) depth) * 20.f);

    p->reserve (estimatedSize);
    n->reserve (estimatedSize);
    tx->reserve(estimatedSize);
    i->reserve (estimatedSize);
    
    // add the initial points to the fields     
    for (j=0; j<12; j++) 
    {
        Vec3f pnt = v[j];
        Vec3f norm = v[j];
        
        setVecLen(pnt, radius);
        norm.normalize();
        
        p->push_back(pnt.addToZero());
        n->push_back(norm);

        Vec2f texCoord;

        // Theta -> v
        texCoord[1] = (Pi - osgacos(norm[1])) / Pi;

        // Phi -> u
        texCoord[0] = calcTexS(norm, texCoord[1]);

        tx->push_back(texCoord);
    }
    
    // subdivide the triangles
    z=12;
    for(j=0; j<20; j++) 
    {
        subdivideTriangle(tr[j][0], tr[j][1], tr[j][2], 
                          depth, p, n, tx, i, z, radius);
    }

    types->push_back(GL_TRIANGLES);
    lens->push_back(i->size()/2);
    
    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);
    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->getIndexMapping().push_back(Geometry::MapPosition |
                                     Geometry::MapNormal);
    geo->getIndexMapping().push_back(Geometry::MapTexCoords);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->setTypes(types);
    geo->setLengths(lens);

    endEditCP(geo);

    // now check triangles: after having created all vertices,
    // make sure, that border vertices, intersecting the x=0 plane
    // in the negative halfspace of the z=0 plane, have duplicate 
    // texture coordinates (with tex.s=1 for triangles with x>=0)
    beginEditCP(geo);
    
    beginEditCP(tex);
    beginEditCP(index);

    for (TriangleIterator ti = geo->beginTriangles();
                          ti != geo->endTriangles(); ++ti)
    {
        Vec3f q[3];
        q[0] = ti.getNormal(0);
        q[1] = ti.getNormal(1);
        q[2] = ti.getNormal(2);

        // check if one triangle point lies on this border
        if  ( (osgabs(q[0][0]) <= 0.01 && q[0][2] <= Eps) ||
              (osgabs(q[1][0]) <= 0.01 && q[1][2] <= Eps) ||
              (osgabs(q[2][0]) <= 0.01 && q[2][2] <= Eps) )
        {
            for (UInt16 i=0; i<3; i++)
            {
                Vec3f norm(q[i]);

                if (osgabs(norm[0]) <= Eps && norm[2] <= Eps)
                {
                    //Real32 theta = (Pi - osgacos(norm[1])) / Pi;
                    Real32 theta = ti.getTexCoords(i).y();

                    // triangle lies completely in positive halfspace of x=0 plane
                    if ( !(q[0][0] <= -Eps || q[1][0] <= -Eps || q[2][0] <= -Eps) )
                    {
                        Vec2f texCoord(1, theta);

                        if ( osgabs(osgabs(norm[1]) - 1) <= Eps )
                            texCoord[0] = 0.5;
    
                        tex->push_back(texCoord);
    
                        index->setValue( tex->size() - 1, ti.getIndexIndex(i) + 1 );
                    }
                    else
                    {
                        Vec2f texCoord(0, theta);

                        if ( osgabs(osgabs(norm[1]) - 1) <= Eps )
                            texCoord[0] = 0.5;
    
                        tex->push_back(texCoord);
    
                        index->setValue( tex->size() - 1, ti.getIndexIndex(i) + 1 );
                    }
                }
            }
        }
    }
    
    endEditCP(tex);
    endEditCP(index);
    
    endEditCP(geo);

    return geo;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeLatLongSphere creates a sphere in the origin and divided in latitude
    and longitude. \a radius is the radius of the sphere, \a latres and \a
    longres are the number of subdivisions along the latitudes and longitudes.

*/

NodePtr OSG::makeLatLongSphere(UInt16 latres, UInt16 longres, Real32 radius)
{
    GeometryPtr pGeo = makeLatLongSphereGeo(latres, longres, radius);
 
    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);

    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeLatLongSphere. 
*/

GeometryPtr OSG::makeLatLongSphereGeo(UInt16 latres, UInt16 longres,
                                      Real32 radius)
{
    if(radius <= 0 || latres < 4 || longres < 4)
    {
        SWARNING << "makeLatLongSphere: illegal parameters "
                 << "latres=" << latres 
                 << ", longres=" << longres 
                 << ", radius=" << radius 
                 << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr     norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr   index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr     types = GeoPTypesUI8::create();     
    
    UInt16 a, b;
    Real32 theta, phi;
    Real32 cosTheta, sinTheta;
    Real32 latDelta, longDelta;

    // calc the vertices

    GeoPositions3f::StoredFieldType   * p  = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType     * n  = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType   * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    latDelta  =       Pi / latres;
    longDelta = 2.f * Pi / longres;

    for(a = 0, theta = -Pi / 2; a <= latres; a++, theta += latDelta) 
    {
        cosTheta = osgcos(theta);
        sinTheta = osgsin(theta);

        for(b = 0, phi = -Pi; b <= longres; b++, phi += longDelta) 
        {
            GLfloat cosPhi, sinPhi;

            cosPhi = osgcos(phi);
            sinPhi = osgsin(phi);
 
            n->push_back(Vec3f( cosTheta * sinPhi, 
                               sinTheta,
                               cosTheta * cosPhi));
            p->push_back(Pnt3f( cosTheta * sinPhi * radius, 
                               sinTheta          * radius, 
                               cosTheta * cosPhi * radius));
            tx->push_back(Vec2f(b / (Real32)longres, 
                               a / (Real32)latres));
        }
    }   

    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType  * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType    * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    for(a = 0; a < longres; a++) 
    {
        t->push_back(GL_TRIANGLE_STRIP);
        l->push_back((latres + 1) * 2);
        
        for(b = 0; b <= latres; b++)
        {
            i->push_back(b * (longres+1) + a);
            i->push_back(b * (longres+1) + a + 1);
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);

    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal   |
                                    Geometry::MapTexCoords);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);
    
    return geo;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    MakeBox creates a box around the origin. It spans the [-\a xsize /2,\a
    xsize /2]x [-\a ysize /2,\a ysize/2]x[-\a zsize /2,\a zsize/2] volume and
    is subdivided into \a hor * \a vert * \a depth quads.

*/

OSG_SYSTEMLIB_DLLMAPPING
NodePtr OSG::makeBox(Real32 xsize, Real32 ysize, Real32 zsize, 
                     UInt16 hor  , UInt16 vert , UInt16 depth)
{
    GeometryPtr pGeo = makeBoxGeo(xsize, ysize, zsize, hor, vert, depth);

    if(pGeo == NullFC)
    {
        return NullFC;
    }

    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);
    
    return node;
}

/*! \ingroup GrpSystemDrawablesGeometrySimpleGeometry
    Create the Geometry Core for used by osg::makeBox. 
*/

OSG_SYSTEMLIB_DLLMAPPING
GeometryPtr OSG::makeBoxGeo(Real32 xsize, Real32 ysize, Real32 zsize, 
                            UInt16 hor  , UInt16 vert , UInt16 depth)
{
    if(! hor || ! vert || ! depth)
    {
        SWARNING << "makeBox: illegal parameters hor=" << hor << ", vert="
                 << vert << ", depth=" << depth << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr    pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr         types = GeoPTypesUI8::create();     
    
    UInt16 x,y,pl;
    Vec3f size(xsize,  ysize,  zsize);
    Vec3f step(xsize / hor, ysize / vert, zsize / depth);
    Vec3f res(hor,  vert,  depth);

    // calc the vertices

    GeoPositions3f::StoredFieldType  * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType    * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    static int inds[6][2] =  { {0,1}, {0,1}, {2,1}, {2,1}, {0,2}, {0,2} };
    static int signs[6][2] = { {1,1}, {-1,1}, {-1,1}, {1,1}, {1,-1}, {1,1} };
    static int asigns[6] = { 1, -1, 1, -1, 1, -1 };
    
    for(pl = 0; pl < 6; pl++)
    {
        UInt16 axis = 3 - inds[pl][0] - inds[pl][1];
        
        for(y = 0; y <= res[inds[pl][1]] ; y++)
        {
            for(x = 0; x <= res[inds[pl][0]]; x++)
            {                       
                Pnt3f pnt;
                pnt[ inds[pl][0] ] = (x * step[inds[pl][0]] - size[inds[pl][0]] / 2) * 
                                        signs[pl][0];
                pnt[ inds[pl][1] ] = (y * step[inds[pl][1]] - size[inds[pl][1]] / 2) * 
                                        signs[pl][1];
                pnt[ axis ] = size[ axis ] * asigns[ pl ] / 2;
                p->push_back(pnt);
                
                Vec3f norm(0, 0, 0);
                norm[ axis ] = Real32(asigns[ pl ]);
                n->push_back(norm);
                tx->push_back(Vec2f(x / (Real32) res[inds[pl][0]], 
                                    y / (Real32) res[inds[pl][1]]));
            }
        }
    }
    
    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType     * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType    * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    UInt32 basepoint = 0;
    
    for(pl = 0; pl < 6; pl++)
    {
        for(y = 0; y < res[inds[pl][1]]; y++)
        {
            UInt16 h = UInt16(res[inds[pl][0]]);
            
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2 * (h + 1));
            
            for(x = 0; x <= h; x++)
            {
                i->push_back(basepoint + (y + 1) * (h + 1) + x);
                i->push_back(basepoint +  y      * (h + 1) + x);
            }
        }
        basepoint += UInt32((res[inds[pl][0]] + 1.f) * 
                            (res[inds[pl][1]] + 1.f) );
    }
    
    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setNormals(norms);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal |
                                    Geometry::MapTexCoords);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);

    return geo;
}

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

OSG_SYSTEMLIB_DLLMAPPING GeoPositions3fPtr OSG::makeGeoPositions3fPtr(UInt32 uiSize)
{
    GeoPositions3fPtr returnValue = GeoPositions3f::create();

    returnValue->resize(uiSize);

    return returnValue;
}

OSG_SYSTEMLIB_DLLMAPPING GeoIndicesUI32Ptr OSG::makeGeoIndicesUI32Ptr(UInt32 uiSize)
{
    GeoIndicesUI32Ptr returnValue = GeoIndicesUI32::create();

    returnValue->resize(uiSize);

    return returnValue;
}

OSG_SYSTEMLIB_DLLMAPPING GeoPLengthsPtr OSG::makeGeoPLengthsPtr(UInt32 uiSize)
{
    GeoPLengthsPtr returnValue = GeoPLengthsUI32::create();

    returnValue->resize(uiSize);

    return returnValue;
}

OSG_SYSTEMLIB_DLLMAPPING GeoPTypesPtr OSG::makeGeoPTypesPtr(UInt32 uiSize)
{
    GeoPTypesPtr returnValue = GeoPTypesUI8::create();

    returnValue->resize(uiSize);

    return returnValue;
}

#endif            // exclude from doc
