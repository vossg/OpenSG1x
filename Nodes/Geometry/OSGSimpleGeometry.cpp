/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include <OSGSimpleMaterial.h>
#include "OSGSimpleGeometry.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup SimpleGeometry
    \ingroup GeometryLib

SimpleGeometry combines a number of functions to create some specialized 
geometry very easily. 

*/

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: $";

#ifdef __sgi
#pragma reset woff 1174
#endif

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif


/*! The default materials used for simple geometries. 
 */

static SimpleMaterialPtr _defaultMaterial;

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr OSG::getDefaultMaterial(void)
{
    if(_defaultMaterial == NullFC)
    {
        _defaultMaterial = SimpleMaterial::create();
        beginEditCP(_defaultMaterial);
        _defaultMaterial->setDiffuse( Color3f( .7,.7,.5 ) );
        _defaultMaterial->setAmbient( Color3f( 0.1,0.1,0.1 ) );
        _defaultMaterial->setSpecular( Color3f( 1,1,1 ) );
        _defaultMaterial->setShininess( 20 );
        endEditCP(_defaultMaterial);
    }
    
    return _defaultMaterial;
}

static SimpleMaterialPtr _defaultUnlitMaterial;

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr OSG::getDefaultUnlitMaterial(void)
{
    if(_defaultUnlitMaterial == NullFC)
    {
        _defaultUnlitMaterial = SimpleMaterial::create();
        beginEditCP(_defaultUnlitMaterial);
        _defaultUnlitMaterial->setDiffuse( Color3f( 1,1,.5 ) );
        _defaultUnlitMaterial->setLit( false );
        endEditCP(_defaultUnlitMaterial);
    }
    
    return _defaultUnlitMaterial;
}

/*! \ingroup SimpleGeometry

makePlane creates a plane in the x/y plane. It spans the [-\a xsize /2,\a xsize /2]x
[-\a ysize /2,\a ysize/2] area and is subdivided into \a hor * \a vert quads.

*/

NodePtr OSG::makePlane( Real32 xsize, Real32 ysize, UInt16 hor, UInt16 vert )
{
    GeometryPtr pGeo = makePlaneGeo(xsize, ysize, hor, vert );
 
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

GeometryPtr OSG::makePlaneGeo( Real32 xsize, Real32 ysize, 
                               UInt16 hor,   UInt16 vert )
{
    if ( ! hor || ! vert )
    {
        SWARNING << "makePlane: illegal parameters hor=" << hor << ", vert="
                 << vert << endl;
        return NullFC;
    }
    
    GeoPositions3fPtr    pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr         types = GeoPTypesUI8::create();     
    
    UInt16 x,y;
    Real32 xstep,ystep;
    xstep = xsize / hor;
    ystep = ysize / vert;

    // calc the vertices

    GeoPositions3f::StoredFieldType  * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType    * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    for ( y = 0; y <= vert; y++ )
    {
        for ( x = 0; x <= hor; x++ )
        {
            p->addValue( Pnt3f( x * xstep - xsize / 2, y * ystep - ysize / 2, 0 ) );
            n->addValue( Vec3f( 0, 0, 1) );
            tx->addValue( Vec2f( x / (Real32) hor, y / (Real32) vert) );
        }
    }

    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType     * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType   * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType     * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    for ( y = 0; y < vert; y++ )
    {
        t->addValue( GL_TRIANGLE_STRIP );
        l->addValue( 2 * ( hor + 1 ) );
        
        for ( x = 0; x <= hor; x++ )
        {
            i->addValue( ( y + 1) * ( hor + 1 ) + x );
            i->addValue(   y      * ( hor + 1 ) + x );
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial( getDefaultMaterial() );
    geo->setPositions( pnts );
    geo->setNormals( norms );
    geo->setTexCoords( tex );
    geo->setIndices( index );
    geo->getIndexMapping().addValue( Geometry::MapPosition | 
                                      Geometry::MapNormal |
                      Geometry::MapTexcoords );
    geo->setTypes( types );
    geo->setLengths( lens );
    endEditCP(geo);
    
    return geo;
}


/*! \ingroup SimpleGeometry
    \return NodePtr the created cone
    \param height   the cone's height
    \param radius   the cone's radius
    \param sides    number of subdivisons in the x direction

makeCone creates a cone. It's center sits in the origin of the x/z plane. 
It's radius is \a radius and the base is subdivided into \a sides parts.

Each part of the cone (bottom cap, sides) can be enabled or disabled.

*/

GeometryPtr OSG::makeConeGeo(Real32 height, 
                             Real32 botradius, 
                             UInt16 sides, 
                             Bool   doSide, 
                             Bool   doBottom)
{
    return makeConicalFrustumGeo(height, 
                                 0, 
                                 botradius, 
                                 sides, 
                                 doSide, 
                                 false, 
                                 doBottom);
}

NodePtr OSG::makeCone(Real32 height, 
                      Real32 botradius, 
                      UInt16 sides, 
                      Bool   doSide, 
                      Bool   doBottom)
{
    return makeConicalFrustum(height, 
                              0, 
                              botradius, 
                              sides, 
                              doSide, 
                              false, 
                              doBottom);
}

/*! \ingroup SimpleGeometry
    \return NodePtr the created cylinder
    \param height   the cylinder's height
    \param radius   the cylinder's radius
    \param sides    number of subdivisons in the x direction

makeCylinder creates a cylinder. It's center sits in the origin of the x/z plane. 
It's radius is \a radius and the base is subdivided into \a sides parts.

Each part of the cylinder (top cap, bottom cap, sides) can be enabled or disabled.

*/

GeometryPtr OSG::makeCylinderGeo(Real32 height, 
                                 Real32 radius,
                                 UInt16 sides, 
                                 Bool   doSide, 
                                 Bool   doTop, 
                                 Bool   doBottom)
{
    return makeConicalFrustumGeo(height, 
                                 radius, 
                                 radius, 
                                 sides, 
                                 doSide, 
                                 doTop, 
                                 doBottom);
}

NodePtr OSG::makeCylinder(Real32 height, 
                          Real32 radius,
                          UInt16 sides, 
                          Bool   doSide, 
                          Bool   doTop, 
                          Bool   doBottom)
{
    return makeConicalFrustum(height, 
                              radius, 
                              radius, 
                              sides, 
                              doSide, 
                              doTop, 
                              doBottom);
}


/*! \ingroup SimpleGeometry
    \return NodePtr     the created frustum
    \param height       the frustum's height
    \param topradius    the frustum's radius at the top
    \param botradius    the frustum's radius at the bottom
    \param sides        number of subdivisons
    \param doSide       create the geometry for the side
    \param doTop        create the geometry for the top cap
    \param doBottom         create the geometry for the bottmo cap

makeConicalFrustum creates a conical frustum. It's center sits in the origin of
the x/z plane.  It's height is \a height and the base is subdivided into
\a sides parts. The top radius is \a topradius, the bottom radius \a
botradius.

Each part of the frustum (top cap, bottom cap, sides) can be enabled or disabled.
Caps for radius 0 are automatically disabled.

*/

GeometryPtr OSG::makeConicalFrustumGeo(Real32 height, 
                                       Real32 topradius, 
                                       Real32 botradius, 
                                       UInt16 sides, 
                                       Bool   doSide, 
                                       Bool   doTop, 
                                       Bool   doBottom)
{
    if ( height <= 0 || topradius < 0 || botradius < 0 || sides < 3 )
    {
        SWARNING << "makeConicalFrustum: illegal parameters height=" << height 
                 << ", topradius=" << topradius 
                 << ", botradius=" << botradius 
                 << ", sides=" << sides 
                 << endl;
        return NullFC;
    }
    
    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr         types = GeoPTypesUI8::create();     
    
    UInt16 j;
    Real32 delta = 2.0 * Pi / sides;
    Real32 beta, x, z;
    Real32 incl = ( botradius - topradius ) / height;
    Real32 nlen = 1.f / osgsqrt( 1 + incl * incl );
    
    // vertices

    GeoPositions3f::StoredFieldType     * p  = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType       * n  = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType * tx = tex->getFieldPtr();

    // faces
    
    GeoIndicesUI32::StoredFieldType     * i  = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType * l  = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType    * t  = types->getFieldPtr();

    // 
    
    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);
    
    if ( doSide )
    {
        UInt32 baseindex = p->getSize();
        
        for ( j = 0; j <= sides; j++ )
        {
            beta = j * delta;
            x = sin(beta);
            z = -cos(beta);         

            p->addValue( Pnt3f( x * topradius, height/2, z * topradius ) );
            n->addValue( Vec3f( x/nlen, incl/nlen, z/nlen ) );
            tx->addValue( Vec2f( j / (Real32) sides, 1 ) );
        }
        
        for ( j = 0; j <= sides; j++ )
        {
            beta = j * delta;
            x = sin(beta);
            z = -cos(beta);         

            p->addValue( Pnt3f(x * botradius, -height/2, z * botradius) );
            n->addValue( Vec3f(x/nlen, incl/nlen, z/nlen) );
            tx->addValue( Vec2f( j / (Real32) sides, 0) );
        }

        t->addValue(GL_TRIANGLE_STRIP);
        l->addValue( 2 * ( sides + 1 ) );

        for ( j = 0; j <= sides; j++ ) 
        {
                i->addValue( baseindex + sides + 1 + j );
                i->addValue( baseindex + j );
        }
    }
    
    if ( doTop && topradius > 0 )
    {
        UInt32 baseindex = p->getSize();
        
        // need to duplicate the points for now, as we don't have multi-index geo yet
        
        for ( j = 0; j < sides; j++ )
        {
            beta = j * delta;
            x = topradius * cos(beta);
            z = - topradius * sin(beta);        

            p->addValue( Pnt3f( x, height/2, z ) );
            n->addValue( Vec3f( 0, 1, 0) );
            tx->addValue( Vec2f( x / topradius / 2 + .5, z / topradius / 2 + .5 ) );
        }

        t->addValue(GL_POLYGON);
        l->addValue( sides );

        for ( j = 0; j < sides; j++ ) 
        {
                i->addValue( baseindex + j );
        }
    }
    
    if ( doBottom && botradius > 0  )
    {
        UInt32 baseindex = p->getSize();
        
        // need to duplicate the points for now, as we don't have multi-index geo yet
        
        for ( j = 0; j < sides; j++ )
        {
            beta = j * delta;
            x = - botradius * cos(beta);
            z = botradius * sin(beta);      

            p->addValue( Pnt3f( x, -height/2, z ) );
            n->addValue( Vec3f( 0, -1, 0 ) );
            tx->addValue( Vec2f( x / botradius / 2 + .5, z / botradius / 2 + .5 ) );
        }

        t->addValue(GL_POLYGON);
        l->addValue( sides );

        for ( j = 0; j < sides; j++ ) 
        {
                i->addValue( baseindex + sides - 1 - j );
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
    geo->setMaterial( getDefaultMaterial() );
    geo->setPositions( pnts );
    geo->setNormals( norms );
    geo->getIndexMapping().addValue( Geometry::MapPosition | 
                                      Geometry::MapNormal |
                      Geometry::MapTexcoords );
    geo->setTexCoords( tex );
    geo->setIndices( index );
    geo->setTypes( types );
    geo->setLengths( lens );
    endEditCP(geo);

    return geo;
}

NodePtr OSG::makeConicalFrustum(Real32 height, 
                                Real32 topradius, 
                                Real32 botradius, 
                                UInt16 sides, 
                                Bool   doSide, 
                                Bool   doTop, 
                                Bool   doBottom)
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

/*! \ingroup SimpleGeometry
    \return NodePtr the created torus
    \param innerRadius  the torus' inner radius
    \param outerRadius  the torus' outer radius
    \param sides        number of subdivisons for the inner radius
    \param rings        number of subdivisons for the outer radius

makeTorus creates a torus in the x/y plane.

*/

GeometryPtr OSG::makeTorusGeo( Real32 innerRadius, Real32 outerRadius, UInt16 sides, 
                               UInt16 rings )
{
    if ( innerRadius <= 0 || outerRadius <= 0 || sides < 3 || rings < 3 )
    {
        SWARNING << "makeTorus: illegal parameters innerRadius=" << innerRadius 
                 << ", outerRadius=" << outerRadius 
                 << ", sides=" << sides 
                 << ", rings=" << rings 
                 << endl;
        return NullFC;
    }
    
    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr         types = GeoPTypesUI8::create();     
    
    UInt16 a, b;
    Real32 theta, phi;
    Real32 cosTheta, sinTheta;
    Real32 ringDelta, sideDelta;

    // calc the vertices

    GeoPositions3f::StoredFieldType     * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType       * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType   * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    ringDelta = 2.0 * Pi / rings;
    sideDelta = 2.0 * Pi / sides;

    for (a = 0, theta = 0.0; a <= rings; a++, theta += ringDelta) 
    {
            cosTheta = cos(theta);
            sinTheta = sin(theta);
        
            for (b = 0, phi = 0; b <= sides; b++, phi += sideDelta ) 
            {
                GLfloat cosPhi, sinPhi, dist;
            
                cosPhi = cos(phi);
                sinPhi = sin(phi);
                dist = outerRadius + innerRadius * cosPhi;

                n->addValue( Vec3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi) );
                p->addValue( Pnt3f(cosTheta * dist, -sinTheta * dist, innerRadius * sinPhi) );
                tx->addValue( Vec2f( - a / (Real32) rings, b / (Real32)sides ) );
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

    for ( a = 0; a < sides; a++ ) 
    {
        t->addValue(GL_TRIANGLE_STRIP);
        l->addValue( ( rings + 1 ) * 2);
        
        for ( b = 0; b <= rings; b++ )
        {
            i->addValue( b * (sides+1) + a );
            i->addValue( b * (sides+1) + a + 1 );
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);

    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial( getDefaultMaterial() );
    geo->setPositions( pnts );
    geo->setNormals( norms );
    geo->getIndexMapping().addValue( Geometry::MapPosition | 
                                      Geometry::MapNormal |
                      Geometry::MapTexcoords );
    geo->setTexCoords( tex );
    geo->setIndices( index );
    geo->setTypes( types );
    geo->setLengths( lens );
    endEditCP(geo);
    
    return geo;
}


NodePtr OSG::makeTorus( Real32 innerRadius, Real32 outerRadius, UInt16 sides, 
                        UInt16 rings )
{
    GeometryPtr pGeo = makeTorusGeo(innerRadius, outerRadius, sides, rings );
 
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

/*! \ingroup SimpleGeometry
*/

Real32 setVecLen(Vec3f &vec, Real32 length ) 
{
    Real32 len = vec.length();
    if (len == 0.0) 
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

/*! \ingroup SimpleGeometry
*/

#define addPoint( v, index )                                                \
{                                                                           \
    Vec3f norm( (v)[0], (v)[1], (v)[2]);                                                            \
                                                                            \
    norm.normalize();                                           \
    n->addValue( norm );                                                    \
    tx->addValue(   Vec2f(  osgatan2( -(v)[0], -(v)[2] ) / Pi / 2 + .5,     \
                            osgabs( osgatan2( -(v)[1],                      \
                                              osgsqrt( (v)[2] * (v)[2] +    \
                                                       (v)[0] * (v)[0]      \
                                                     )                      \
                                            )                               \
                                  )  / Pi + .5                              \
                )        );                                                 \
    p->addValue( norm * radius );                                           \
}

    
static void subdivideTriangle( UInt32 i1, 
                        UInt32 i2, 
                        UInt32 i3, 
                        Int32 depth, 
                        GeoPositions3f::StoredFieldType  *p, 
                        GeoNormals3f::StoredFieldType    *n,
                        GeoTexCoords2f::StoredFieldType *tx,
                        GeoIndicesUI32::StoredFieldType   *i,
                        UInt32& z, Real32 radius) 
{   
    if (depth == 0) 
    {
        i->addValue( i1 );
        i->addValue( i2 );
        i->addValue( i3 );
                            
        return;         
    }

    Pnt3f   v1 = p->getValue( i1 ), 
            v2 = p->getValue( i2 ), 
            v3 = p->getValue( i3 );
    Pnt3f v12, v23, v31;

    v12 = v1 + ( v2 - v1 ) * .5;
    v23 = v2 + ( v3 - v2 ) * .5;
    v31 = v3 + ( v1 - v3 ) * .5;
    
    v12 /= 2.0;
    v23 /= 2.0;
    v31 /= 2.0;
    
    UInt32 i12 = z++, i23 = z++, i31 = z++;
    
    addPoint( v12,i12 );
    addPoint( v23,i23 );
    addPoint( v31,i31 );
    
    subdivideTriangle(  i1, i12, i31, depth - 1, p,n,tx,i, z, radius );
    subdivideTriangle(  i2, i23, i12, depth - 1, p,n,tx,i, z, radius );
    subdivideTriangle(  i3, i31, i23, depth - 1, p,n,tx,i, z, radius );
    subdivideTriangle( i12, i23, i31, depth - 1, p,n,tx,i, z, radius );
}

/*! \ingroup SimpleGeometry
    \return NodePtr the created sphere
    \param depth    the sphere's subdivision depth
    \param radius   the sphere's radius

makeSphere creates a sphere centered in the origin. It is created by recursive 
subdivision of an icosahedron, with \a depth giving the number of subdivisions.

*/

GeometryPtr OSG::makeSphereGeo(UInt16 depth, Real32 radius)
{   
    
    #define X .525731112119133606
    #define Z .850650808352039932   

    GeoPositions3fPtr   pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsPtr      lens  = GeoPLengthsUI32::create();  
    GeoPTypesPtr            types = GeoPTypesUI8::create();     
    UInt32              j,z;
    
    static Vec3f v[12] = {  Vec3f( -X, 0.,  Z ),
                             Vec3f(  X, 0.,  Z ),
                             Vec3f( -X, 0., -Z ),
                             Vec3f(  X, 0., -Z ),
                             Vec3f( 0.,  Z,  X ),
                             Vec3f( 0.,  Z, -X ),
                             Vec3f( 0., -Z,  X ),
                             Vec3f( 0., -Z, -X ),
                             Vec3f(  Z,  X, 0. ),
                             Vec3f( -Z,  X, 0. ),
                             Vec3f(  Z, -X, 0. ),
                             Vec3f( -Z, -X, 0. )   };
                
    Int32 tr[20][3] = { {1,4,0},  {4,9,0},  {4,5,9},  {8,5,4},  {1,8,4},
                           {1,10,8}, {10,3,8}, {8,3,5},  {3,2,5},  {3,7,2},
                           {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
                           {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9},  {11,2,7} };                  
                
    GeoPositions3f::StoredFieldType     * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType       * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType   * tx = tex->getFieldPtr();
    GeoIndicesUI32::StoredFieldType     * i = index->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);
    
    // initial sizing to prevent reallocation halfway through

    UInt32 estimatedSize = UInt32(osgpow(3.f, (Real32) depth ) * 20.f);

    p->reserve (estimatedSize);
    n->reserve (estimatedSize);
    tx->reserve(estimatedSize);
    i->reserve (estimatedSize);
    
    // add the initial points to the fields     
    for ( j=0; j<12; j++ ) 
    {
        Vec3f pnt = v[j];
        Vec3f norm = v[j];
        setVecLen( pnt, radius );
        norm.normalize();
        //addPoint( pnt, j );
        p->addValue( pnt );
        n->addValue( norm );
        tx->addValue( Vec2f(    osgatan2( -(pnt)[0], -(pnt)[2] ) / Pi / 2 + .5, \
                            osgabs( osgatan2( -(pnt)[1],                    \
                                              osgsqrt( (pnt)[2] * (pnt)[2] +    \
                                                       (pnt)[0] * (pnt)[0]      \
                                                     )                      \
                                            )                               \
                                  )  / Pi + .5                              \
                )        ); 
    }
    
    // if we do not subdivide then lets have the icosahedron at least
    if( depth < 1 )
    {
        for( UInt32 c1=0; c1<20; ++c1 )
        {
            for( UInt32 c2=0; c2<3; ++c2 )
            {
                i->addValue( tr[c1][c2] );
            }
        }
    }
    // subdivide the triangles
    z=12;
    for ( j=0; j<20; j++ ) 
    {
        subdivideTriangle( tr[j][0], tr[j][1], tr[j][2],
                   depth, p, n, tx, i, z, radius );
    }

    types->addValue( GL_TRIANGLES );
    lens->addValue( i->getSize() );
    
    endEditCP(pnts);
    endEditCP(norms);
    endEditCP(tex);
    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial( getDefaultMaterial() );
    geo->setPositions( pnts );
    geo->setNormals( norms );
    geo->getIndexMapping().addValue( Geometry::MapPosition | 
                                      Geometry::MapNormal |
                      Geometry::MapTexcoords );
    geo->setTexCoords( tex );
    geo->setIndices( index );
    geo->setTypes( types );
    geo->setLengths( lens );
    endEditCP(geo);
        
    return geo;
}


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

/*! \ingroup SimpleGeometry
    \return NodePtr the created box
    \param xsize    the box's size in the x direction
    \param ysize    the box's size in the y direction
    \param zsize    the box's size in the z direction
    \param hor      number of subdivisons in the x direction
    \param vert         number of subdivisons in the y direction
    \param depth    number of subdivisons in the z direction

makeBox creates a box around the origin. It spans the [-\a xsize /2,\a xsize /2]x
[-\a ysize /2,\a ysize/2]x[-\a zsize /2,\a zsize/2] volume and is subdivided into 
\a hor * \a vert * \a depth quads.

*/

OSG_SYSTEMLIB_DLLMAPPING
GeometryPtr OSG::makeBoxGeo(Real32 xsize, Real32 ysize, Real32 zsize, 
                            UInt16 hor  , UInt16 vert , UInt16 depth)
{
    if ( ! hor || ! vert || ! depth)
    {
        SWARNING << "makeBox: illegal parameters hor=" << hor << ", vert="
                 << vert << ", depth=" << depth << endl;
        return NullFC;
    }
    
    GeoPositions3fPtr    pnts  = GeoPositions3f::create();
    GeoNormals3fPtr         norms = GeoNormals3f::create();
    GeoTexCoords2fPtr   tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr       index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr  lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr         types = GeoPTypesUI8::create();     
    
    UInt16 x,y,pl;
    Vec3f size( xsize,  ysize,  zsize );
    Vec3f step( xsize / hor, ysize / vert, zsize / depth );
    Vec3f res( hor,  vert,  depth );

    // calc the vertices

    GeoPositions3f::StoredFieldType  * p = pnts->getFieldPtr();
    GeoNormals3f::StoredFieldType    * n = norms->getFieldPtr();
    GeoTexCoords2f::StoredFieldType * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(norms);
    beginEditCP(tex);
    
    static int inds[6][2] =  { {0,1}, {0,1}, {1,2}, {1,2}, {2,0}, {2,0} };
    static int signs[6][2] = { {1,1}, {-1,1}, {1,1}, {-1,1}, {1,1}, {-1,1} };
    static int asigns[6] = { 1, -1, 1, -1, 1, -1 };
    
    for ( pl = 0; pl < 6; pl++ )
    {
        UInt16 axis = 3 - inds[pl][0] - inds[pl][1];
        
        for ( y = 0; y <= res[inds[pl][1]] ; y++ )
        {
            for ( x = 0; x <= res[inds[pl][0]]; x++ )
            {                       
                Pnt3f pnt;
                pnt[ inds[pl][0] ] = ( x * step[inds[pl][0]] - size[inds[pl][0]] / 2 ) * 
                                        signs[pl][0];
                pnt[ inds[pl][1] ] = ( y * step[inds[pl][1]] - size[inds[pl][1]] / 2 ) * 
                                        signs[pl][1];
                pnt[ axis ] = size[ axis ] * asigns[ pl ] / 2;
                p->addValue( pnt );
                
                Vec3f norm( 0, 0, 0 );
                norm[ axis ] = asigns[ pl ];
                n->addValue( norm );
                tx->addValue( Vec2f( x / (Real32) res[inds[pl][0]], 
                                     y / (Real32) res[inds[pl][1]]) );
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
    
    for ( pl = 0; pl < 6; pl++ )
    {
        for ( y = 0; y < res[inds[pl][1]]; y++ )
        {
            UInt16 h = UInt16(res[inds[pl][0]]);
            
            t->addValue( GL_TRIANGLE_STRIP );
            l->addValue( 2 * ( h + 1 ) );
            
            for ( x = 0; x <= h; x++ )
            {
                i->addValue( basepoint + ( y + 1) * ( h + 1 ) + x );
                i->addValue( basepoint +   y      * ( h + 1 ) + x );
            }
        }
        basepoint += UInt32( (res[inds[pl][0]] + 1.f) * 
                             (res[inds[pl][1]] + 1.f) );
    }
    
    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial( getDefaultMaterial() );
    geo->setPositions( pnts );
    geo->setNormals( norms );
    geo->getIndexMapping().addValue( Geometry::MapPosition | 
                                      Geometry::MapNormal |
                      Geometry::MapTexcoords );
    geo->setTexCoords( tex );
    geo->setIndices( index );
    geo->setTypes( types );
    geo->setLengths( lens );
    endEditCP(geo);

    return geo;
}

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
    node->setCore(pGeo );
    endEditCP    (node);
    
    return node;
}

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

