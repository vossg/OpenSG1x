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

#include <set>

#include "OSGConfig.h"

#include <OSGLog.h>

#include "OSGGeometry.h"
#include "OSGGeoPropPtrs.h"
#include "OSGTriangleIterator.h"
#include "OSGGeoFunctions.h"
#include "OSGFaceIterator.h"

#include "OSGNodeGraph.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \ingroup GeoFunctions

calcVertexNormals calculates the normals for the geometry's vertices. It
does this simply by accumulating the face normals of all triangles that
use the vertex and renormalizing.

*/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

#ifdef __sgi
#pragma set woff 1209
#endif

OSG_SYSTEMLIB_DLLMAPPING
void osg::calcVertexNormals( GeometryPtr geo )
/*

faster; but not well tested code

{
  //Vec3f vec0, vec1,vec2;
  GeoPositionsPtr positionPtr;
  GeoNormalsPtr   normalPtr;
  Int32 i, ni, pi, pN, p0, p1, p2, skipN = 0;
  TriangleIterator tI;
  Real32 x,y,z;
  std::vector<Vec3f> normalVec;

  if (geo != NullFC) {

    // get the pos bag and pos count
    positionPtr = geo->getPositions();
    pN = (positionPtr != NullFC) ? positionPtr->getSize() : 0;

    FNOTICE (("Create %d normal \n", pN ));

    if (pN) {

      // init the normal bag
      normalVec.resize(pN);
      for (i = 0; i < pN; ++i)
        normalVec[i].setValues(0,0,0);

      // fill the normal bag
      for (tI = geo->beginTriangles(); tI != geo->endTriangles(); ++tI) {

        if ((p0 == p1) || (p1 == p2) || (p2 == p0)) {
          skipN++;
        }
        else {

          // get the tri points
          p0 = tI.getPositionIndex(0);
          p1 = tI.getPositionIndex(1);
          p2 = tI.getPositionIndex(2);
          // get the points
          // TODO; use assign
          Vec3f vec0(tI.getPosition(0));
          Vec3f vec1(tI.getPosition(1));
          Vec3f vec2(tI.getPosition(2));

          // calc the face normal
          vec0 -= vec1;
          vec1 -= vec2;
          vec0.crossThis(vec1);
          vec0.normalize();

          // add the normal
          normalVec[p0] += vec0;
          normalVec[p1] += vec0;
          normalVec[p2] += vec0;
        }
      }

      // get/create/resize the normal bag
      normalPtr = geo->getNormals();
      if (normalPtr == NullFC) {
        normalPtr = GeoNormals3f::create();
        beginEditCP(geo);
        {
          geo->setNormals( normalPtr );
        }
        endEditCP(geo);
      }

      // get/create/resize the normal bag
      normalPtr = geo->getNormals();
      if (normalPtr == NullFC) {
        normalPtr = GeoNormals3f::create();
        beginEditCP(geo);
        {
          geo->setNormals( normalPtr );
        }
        endEditCP(geo);
      }

      // normalize and copy the result
      beginEditCP (normalPtr);
      {
        // resize the bag
        normalPtr->resize(pN);

        // normalize and copy the result
        for (i = 0; i < pN; ++i) {
          if (normalize)
            normalVec[i].normalize();
          normalPtr->setValue( normalVec[i], i );
        }
      }
      endEditCP (normalPtr);

      // adapting the indexMapping
      pi = geo->calcMappingIndex ( Geometry::MapPosition );
      ni = geo->calcMappingIndex ( Geometry::MapNormal   );
      if ((geo->getIndexMapping().size() > 1) && (pi >= 0) && (pi != ni)) {

        geo->getIndexMapping(ni) &= ~Geometry::MapNormal;
        if (geo->getIndexMapping(ni) == 0) {
          FFATAL (("Should delete normal entry; do impl !!!\n" ));
          geo->getIndexMapping(ni) = Geometry::MapEmpty;
        }
        else {
          FNOTICE (("Keep mindex mapping after createVertexNormal()\n"));
        }

        geo->getIndexMapping(pi) |= Geometry::MapNormal;
      }
      else {
        FNOTICE (("Keep single index mapping after createVertexNormal()\n"));
      }
    }
    else {
      FFATAL (("No valid points setting; can not create normal\n"));
    }
    if (skipN) {
      FNOTICE (( "Skip %d invalid triangles in createVertexNormal()\n",
                 skipN));
    }
  }
  else {
    FFATAL (("No valid geometry; can not create normal\n"));
  }

}

*/

{
    GeoNormalsPtr    norms;
    int              i;
    std::set<UInt32> used_indices;

    if(geo->getNormals() == NullFC)
    {
        norms = GeoNormals3f::create();
    }
    else
    {
        norms = geo->getNormals();
    }

    beginEditCP(norms);

    norms->resize( geo->getPositions()->getSize() );

    // problem: not all of the points of the property might be used by this
    // geometry. If the property has more than 1 users, be careful.
    if( 1 /* cannot check that yet, be conservative*/)
    {
        for ( TriangleIterator t = geo->beginTriangles(); t != geo->endTriangles(); ++t )
        {
            used_indices.insert(t.getPositionIndex(0));
            used_indices.insert(t.getPositionIndex(1));
            used_indices.insert(t.getPositionIndex(2));
        }

        std::set<UInt32>::iterator i   = used_indices.begin();
        std::set<UInt32>::iterator end = used_indices.end();

        while(i != end)
        {
            norms->setValue( Vec3f( 0,0,0 ), *i );
            
            ++i;
        }
    }
    else // just one user, can clear all
    {
        for ( i = 0; i < geo->getPositions()->getSize(); i++ )
        {
            norms->setValue( Vec3f( 0,0,0 ), i );
        }
    }

    for ( TriangleIterator t = geo->beginTriangles(); 
          t != geo->endTriangles(); ++t )
    {
        Plane p( t.getPosition(0), t.getPosition(1), t.getPosition(2) );

        norms->setValue( norms->getValue( t.getPositionIndex(0) ) +
                         p.getNormal(),
                         t.getPositionIndex(0) );
        norms->setValue( norms->getValue( t.getPositionIndex(1) ) +
                         p.getNormal(),
                         t.getPositionIndex(1) );
        norms->setValue( norms->getValue( t.getPositionIndex(2) ) +
                         p.getNormal(),
                         t.getPositionIndex(2) );
    }

    if( 1 /* cannot check that yet, be conservative*/)
    {
        std::set<UInt32>::iterator i   = used_indices.begin();
        std::set<UInt32>::iterator end = used_indices.end();

        while(i != end)
        {
            Vec3f n = norms->getValue( *i );
            n.normalize();
            norms->setValue( n, *i );

            ++i;
        }
    }
    else // just one user, can clear all
    {
        for ( i = 0; i < geo->getPositions()->getSize(); i++ )
        {
            Vec3f n = norms->getValue( i );
            n.normalize();
            norms->setValue( n, i );
        }
    }

    endEditCP(norms);

    beginEditCP(geo);
    {
        geo->setNormals( norms );

        MFUInt16 &im = geo->getIndexMapping();
        if ( im.size() > 0 )
        {
            Int16 pi,ni;
            pi = geo->calcMappingIndex( Geometry::MapPosition );
            ni = geo->calcMappingIndex( Geometry::MapNormal );

            if ( ni >= 0 )
                im[ni] = im[ni] & ~ Geometry::MapNormal;
            if ( pi >= 0 )
                im[pi] = im[pi] |   Geometry::MapNormal;
        }
    }
    endEditCP( geo );

}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*! \ingroup Geometry
    calcVertexNormals calculates the normals for the geometry's vertices. This
    version uses a creaseAngle to define which faces are averaged at the
    vertices. Only faces whose angle is smaller than the
    creaseAngle are used.
    
    Caveats: It won't always work for striped geometry. It will process it,
    but if a stripe point needs to be split because it has two normals, that
    won't be done.
*/

template <class type>
struct vecless
{
    bool operator() (const type &a, const type &b) const
    {
        UInt32 i;
        bool ret = false;

        for(i = 0; i < type::_iSize; i++)
        {
            if(osgabs(a[i] - b[i]) < Eps)
                continue;

            if(a[i] > b[i])
            {
                ret = false;
                break;
            }

            ret = true;
            break;
        }

        return ret;
    }
};

template <class type>
struct memless
{
  bool operator() (const type &a, const type &b) const
    {
      if (a.second && b.second)
      {  
        if (a.second == b.second)
          return ((memcmp(a.first,b.first,a.second) < 0) ? true : false);
        else
        {
          FFATAL (("a.memSize != b.memSize in memless::operator()\n"));
        }
      }
      else 
      {
        FFATAL (("memSize is NULL in memless::operator()\n"));
      }
      return false;
    }
};



OSG_SYSTEMLIB_DLLMAPPING
void osg::calcVertexNormals( GeometryPtr geo, Real32 creaseAngle )
{
    GeoNormalsPtr   norms;
    GeoPositionsPtr positions;

    if(creaseAngle >= Pi)
    {
        calcVertexNormals( geo );
        return;
    }

    // Get the positions property
    if (geo->getPositions() == NullFC)
    {
      FFATAL (("Geo without positions in calcVertexNormals()\n"));
      return;
    }
    else
    {
      positions = geo->getPositions();
    }

    // Get normal property, create if needed
    if(geo->getNormals() == NullFC)
    {
        norms = GeoNormals3f::create();
    }
    else
    {
        norms = geo->getNormals();
    }

    // need to set it early, is used below
    beginEditCP(geo);
    {
        geo->setNormals( norms );
    }
    endEditCP( geo );

    // Do the normals have their own index?
    MFUInt16      &im     = geo->getIndexMapping();
    Int16          ni     = geo->calcMappingIndex( Geometry::MapNormal );
    GeoIndicesPtr  ip     = geo->getIndices();
    UInt32         nind   = ip->size() / (im.size() ? im.size() : 1);
    int            imsize = 0;
    if(ni < 0 || im[ni] != Geometry::MapNormal)
    {
        // normals need their own index
        if(ni >= 0)
            im[ni] = im[ni] & ~Geometry::MapNormal;

        // need to be multi-indexed?
        if(im.size() == 0)
        {
            UInt32 map = Geometry::MapPosition;
            
            if(geo->getTexCoords() != NullFC)   
                map |= Geometry::MapTexCoords;
                
            if(geo->getColors()    != NullFC)   
                map |= Geometry::MapColor;
                
            im.push_back( map );           
        }
            
        ni = im.size();
        im.push_back( Geometry::MapNormal );
        
        // add an entry to the indices for the normals
		imsize = im.size();
        
        beginEditCP(ip);
        ip->resize(nind * imsize);

        for(UInt32 i = nind - 1; i > 0; --i)
        {
            for(Int16 j = imsize - 2; j >= 0; --j)
            {
                UInt32 val;
                ip->getValue( val, i * (imsize - 1) + j );
                ip->setValue( val, i *  imsize      + j );
            }
            ip->setValue( i, i *  imsize + imsize - 1 );
        }
        ip->setValue( 0, imsize - 1 );
        endEditCP(ip);
    }
    else // set the normal indices
    {
        imsize = im.size();
        beginEditCP(ip);
        for(UInt32 i = 0; i < nind; ++i)
        {
            ip->setValue( i, i * imsize + ni );
        }     
        endEditCP(ip);
    }
    
    
    // now calc the normals
    
    // if creaseAngle is 0, it's simple: every face uses its own.
    
    if(creaseAngle == 0)
    {
        beginEditCP(norms);
        beginEditCP(ip);
        
        norms->resize(nind);
        
        for(TriangleIterator ti = geo->beginTriangles(); 
                             ti != geo->endTriangles(); 
                             ++ti )
        {
            Vec3f d1 = ti.getPosition(1) - ti.getPosition(0);
            Vec3f d2 = ti.getPosition(2) - ti.getPosition(0);        
            d1.crossThis(d2);

            d1.normalize();
            
            norms->setValue( d1, ti.getNormalIndex(0) );
            norms->setValue( d1, ti.getNormalIndex(1) );
            norms->setValue( d1, ti.getNormalIndex(2) );
        }
        
        endEditCP(norms);
        endEditCP(ip);
        return;
    }
    
    // creaseAngle > 0, need to calculate

#if 0

    // orig pngMap based code (written by dirk)

    // collect a map from points to faces using this point
    // collect the face normals in a separate vector
    
    std::vector< Vec3f > faceNormals; 
    std::multimap< Pnt3f, UInt32, vecless<Pnt3f> > pntMap;
    TriangleIterator ti;
    
    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti )
    {
        Vec3f d1 = ti.getPosition(1) - ti.getPosition(0);
        Vec3f d2 = ti.getPosition(2) - ti.getPosition(0);        
        d1.crossThis(d2);
        
        d1.normalize();
        faceNormals.push_back(d1);  
             
        pntMap.insert(std::pair<Pnt3f, UInt32>(ti.getPosition(0),
                                               faceNormals.size() - 1));
        pntMap.insert(std::pair<Pnt3f, UInt32>(ti.getPosition(1),
                                               faceNormals.size() - 1));
        pntMap.insert(std::pair<Pnt3f, UInt32>(ti.getPosition(2),
                                               faceNormals.size() - 1));
    }
    
    // now walk through the geometry again and calc the normals
    
    beginEditCP(norms);
    beginEditCP(ip);

    norms->resize( nind );
    
    Real32 cosCrease = osgcos( creaseAngle );
    
    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti )
    {
        Int32 tind = ti.getIndex();
        Vec3f mynorm = faceNormals[tind];        
        
        std::multimap< Pnt3f, UInt32, vecless<Pnt3f> >::iterator st,en;  
        
        for(UInt16 i = 0; i < 3; ++i)
        {   
            // calculate the normal: average all different normals
            // that use a point. Simple addition or weighted addition
            // doesn't work, as it depends on the triangulation
            // of the object. :(
            
            std::set< Vec3f, vecless<Vec3f> > normset;
             
            st = pntMap.lower_bound(ti.getPosition(i));
            en = pntMap.upper_bound(ti.getPosition(i));

            for(; st != en; st++)
            {
                if(mynorm.dot(faceNormals[(*st).second]) > cosCrease)
                    normset.insert(faceNormals[(*st).second]);
            }
            
            Vec3f norm(0, 0, 0);
            typedef std::set< Vec3f, vecless<Vec3f> >::iterator NormSetIt;

            for(NormSetIt it = normset.begin(); it != normset.end(); ++it)
            {
                norm += (*it);
            }
            
            norm.normalize();
            norms->setValue(norm, ti.getNormalIndex(i));
        }
        
    }
    
    endEditCP(ip);
    endEditCP(norms);

#else
    
    // opt + normal share code (written by jbehr)

    // collect a map from points to faces using this point
    // collect the face normals in a separate vector

    //FLOG (("Run calcVertexNormals(%g)\n", creaseAngle));

    std::vector< Vec3f > faceNormals; 
    std::vector < std::vector< UInt32 > > pntFaceDic;
    TriangleIterator ti;
    UInt32 i, pN = positions->size();

    pntFaceDic.resize(pN);
    for( ti = geo->beginTriangles(), i = 0; 
         ti != geo->endTriangles(); ++ti, ++i )
    {
        Int32 v0 = ti.getPositionIndex(0);
        Int32 v1 = ti.getPositionIndex(1);
        Int32 v2 = ti.getPositionIndex(2);

        if (v0 != v1 && v0 != v2) {
        
          Vec3f d1 = ti.getPosition(1) - ti.getPosition(0);
          Vec3f d2 = ti.getPosition(2) - ti.getPosition(0);        
          d1.crossThis(d2);
          
          d1.normalize();
          faceNormals.push_back(d1);  
          
          pntFaceDic [ ti.getPositionIndex(0) ].push_back(i);
          pntFaceDic [ ti.getPositionIndex(1) ].push_back(i);
          pntFaceDic [ ti.getPositionIndex(2) ].push_back(i);

        }        
        else
        {
          // invalid Triangle
          faceNormals.push_back( Vec3f(0,0,0) );
        }
    }
    
    // now walk through the geometry again and calc the normals
    
    beginEditCP(norms);
    beginEditCP(ip);

    norms->clear();

    Real32 cosCrease = osgcos( creaseAngle );
    Vec3f norm;
    std::vector < UInt32> normset;
    std::vector < std::map< std::vector<UInt32>, UInt32 > > normDic;
    std::map< std::vector<UInt32>, UInt32 >::iterator ndI;
    UInt32         normalIndex = 0;

    normDic.resize( pN );

    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti )
    {
        Int32 tind = ti.getIndex();
        Vec3f mynorm(faceNormals[tind]);
        Int32 v0 = ti.getPositionIndex(0);
        Int32 v1 = ti.getPositionIndex(1);
        Int32 v2 = ti.getPositionIndex(2);

        if (v0 != v1 && v0 != v2)
          for(UInt16 i = 0; i < 3; ++i)
            {   
              // calculate the normal: average all different normals
              // that use a point. Simple addition or weighted addition
              // doesn't work, as it depends on the triangulation
              // of the object. :(
              
              UInt32 p = ti.getPositionIndex(i);
              UInt32 pf, f, fN = pntFaceDic[p].size();
              UInt32 n, nN;
              
              normset.clear();
              for (f = 0; f < fN; f++) {
                pf = pntFaceDic[p][f];
                if (mynorm.dot(faceNormals[pf]) > cosCrease)
                  normset.push_back(pf);
              }
              
              if ((nN = normset.size())) 
                {
                  // find normal
                  //std::sort ( normset.begin(), normset.end() );
                  ndI = normDic[p].find(normset);
                  if (ndI == normDic[p].end()) 
                    {
                      norm = faceNormals[normset[0]];
                      for (n = 1; n < nN; ++n) 
                        norm += faceNormals[normset[n]];
                      norm.normalize();
                      normalIndex = norms->size();
                      norms->push_back(norm);
                      normDic[p][normset] = normalIndex;
                    }
                  else 
                    {
                      normalIndex = ndI->second;
                    }
                }
              else
                {
                  // keep normalIndex
                  FWARNING (( "Empty normset for %d faces pos %d: %f/%f/%f\n",
                              fN, i, 
                              ti.getPosition(i).x(), ti.getPosition(i).y(),
                              ti.getPosition(i).z() ));                  
                }
              
              ip->setValue ( normalIndex, ti.getIndexIndex(i) + ni );
              
            }       
    }   

    endEditCP(ip);
    endEditCP(norms);

#endif

}

/*! \ingroup Geometry
    \param geo      the geometry to work on
    \param length   the length of the normal vectors

getNormals creates a geometry that consists of the normals of \a geo
as lines. Every line starts of the position the normals is associated
with (vertex for vertex normals, center of face for face normals) and
has the length \a length.

*/

#ifdef __sgi
#pragma set woff 1209
#endif

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr osg::getNormals ( GeometryPtr geo,
                          Real32      length)
{
  NodePtr  p = Node::create();
  GeometryPtr g = Geometry::create();
    GeoPositions3f::PtrType pnts = GeoPositions3f::create();
    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
    GeoPTypesPtr type = GeoPTypesUI8::create();
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();

    // calculate
    beginEditCP(pnts);

    PrimitiveIterator pi(geo);

    if ( 1 /* no easy way to check right now */ )
    {
        for ( pi  = geo->beginPrimitives();
              pi != geo->endPrimitives(); ++pi )
        {
            for ( UInt16 k = 0; k < pi.getLength(); k++ )
            {
                pnts->push_back( pi.getPosition( k ) );
                pnts->push_back( pi.getPosition( k ) +
                                length * pi.getNormal( k ) );
            }
        }
    }
    else
    {
        Pnt3f center(0,0,0);

        for ( pi  = geo->beginPrimitives();
              pi != geo->endPrimitives(); ++pi )
      {
        for ( UInt16 k = 0; k < pi.getLength(); k++ )
          {
            center[0] += pi.getPosition( k )[0];
            center[1] += pi.getPosition( k )[1];
            center[2] += pi.getPosition( k )[2];
          }
        pnts->push_back( center );
        pnts->push_back( center +  length * pi.getNormal( 0 ) );
      }
    }

    endEditCP(pnts);

    // create the geometry
    beginEditCP(index);
    for ( UInt32 i = 0; i < pnts->getSize(); i++ )
        index->push_back( i );
    endEditCP(index);

    beginEditCP(type);
    type->push_back( GL_LINES );
    endEditCP(type);

    beginEditCP(lens);
    lens->push_back( index->getSize() );
    endEditCP(lens);

    beginEditCP(g);
    g->setTypes( type );
    g->setLengths( lens );
    g->setIndices( index );
    g->setPositions( pnts );
    endEditCP(g);

    beginEditCP(p);
    p->setCore(g);
    endEditCP(p);

    return p;
}


#ifdef __sgi
#pragma reset woff 1209
#endif

/*! \brief create the geometry index form the given FaceSet (VRML style) data
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 osg::setIndexFromVRMLData(     GeometryPtr    geoPtr,
                                std::vector<Int32> &coordIndex,
                                std::vector<Int32> &normalIndex,
                                std::vector<Int32> &colorIndex,
                                std::vector<Int32> &texCoordIndex,
                                     bool           ,
                                     bool           ccw,
                                     bool           normalPerVertex,
                                     bool           colorPerVertex,
                                     bool           ,
                                     bool           faceSet)
{
  /** define the bag type */
  typedef std::vector<Int32>* IndexBagP;

  /** defines the Index Types */
  enum IndexType { UNKNOWN_IT = 0,
                   EMPTY_IT,
                   VERTEX_COORD_IT, VERTEX_IT, VERTEX_DUP_IT,
                   VERTEX_CREATE_IT,
                   PRIMITIVE_IT, PRIMITIVE_INDEX_IT,
                   PRIMITIVE_CREATE_IT
  };

  /** holds the Index types as str, mainly for log/debug outputs */
#ifdef OSG_DEBUG
  static const char *indexTypeStr[] = {
    "UNKNOWN_IT", "EMPTY_IT",
    "VERTEX_COORD_IT", "VERTEX_IT", "VERTEX_DUP_IT", "VERTEX_CREATE_IT",
    "PRIMTIVE_IT", "PRIMITIVE_INDEX_IT", "PRIMITIVE_CREATE_IT"
  };
#endif

  osg::GeoPositionsPtr posPtr;
  osg::GeoNormalsPtr normalPtr;
  osg::GeoColorsPtr colorPtr;
  osg::GeoTexCoordsPtr texCoordsPtr;
  osg::GeoPLengthsPtr lensPtr;
  osg::GeoPTypesPtr geoTypePtr;
  osg::GeoIndicesPtr indexPtr;

  Int32 index, i, pi, typei, mapi, primitiveN = 0, vN = 0;
  Int32 pType = 0, localPType;
  Int32 maxPType = (faceSet ? 5 : 3);
  Int32 minPType = (faceSet ? 3 : 2);
  Int32 beginIndex, endIndex, step, len, sysPType = 0;
  Int32 piN = 0, ciN = 0, niN = 0, tiN = 0;
  Int32 pN = 0, nN = 0, cN = 0, tN = 0;
  IndexType indexType[4];
  IndexType &coordIT = indexType[0];
  IndexType &normalIT = indexType[1];
  IndexType &colorIT = indexType[2];
  IndexType &textureIT = indexType[3];
  Int32 primitiveTypeCount[6];
  UInt32 triCount = 0;
  Int16 indexMap[4], indexMapID[4];
  IndexBagP indexBag[4] = { &coordIndex, &normalIndex,
                            &colorIndex, &texCoordIndex };

  //----------------------------------------------------------------------
  // init
  coordIT = VERTEX_IT;
  indexMap[0] = Geometry::MapPosition;

  //----------------------------------------------------------------------
  // get the property pointer and element count
  posPtr = geoPtr->getPositions();
  pN = ((posPtr == osg::NullFC) ? 0 : posPtr->getSize());

  normalPtr = geoPtr->getNormals();
  nN = ((normalPtr == osg::NullFC) ? 0 : normalPtr->getSize());

  colorPtr = geoPtr->getColors();
  cN = ((colorPtr == osg::NullFC) ? 0 : colorPtr->getSize());

  texCoordsPtr = geoPtr->getTexCoords();
  tN = ((texCoordsPtr == osg::NullFC) ? 0 : texCoordsPtr->getSize());

  FDEBUG (( "vertex attrib count P/N/C/T: %d/%d/%d/%d\n", pN, nN, cN, tN ));

  //----------------------------------------------------------------------
  // check the vertex index and count the primitives
  primitiveN = index = 0;
  for (pType = 0; pType < 6; pType++)
    primitiveTypeCount[pType] = 0;

  if (!pN) {
    FWARNING (("No points in osg::setIndexFromVRMLData()\n"));
		return 0;
  }
  else {
    piN = coordIndex.size();
		if (piN) 
    	for ( i = 0; i <= piN; i++) {
        index = (i == piN) ? -1 : coordIndex[i];
      	if ( (index < 0) && vN ) {
	        primitiveTypeCount [ (vN > maxPType) ? maxPType : vN]++;
  	      primitiveN++;
    	    vN = 0;
      	}
	      else {
  	      if (index >= pN && i != piN) {
    	      FWARNING (("Point index (%d/%d) out of range", index, pN));
      	    coordIndex[i] = 0;
        	}
  	      vN++;
    	  }
    	}
		else {
			FWARNING (("No coordIndex in osg::setIndexFromVRMLData()\n"));
			return 0;
		}
  }

  //----------------------------------------------------------------------
  // check the normal index
  normalIT = UNKNOWN_IT;
  niN = normalIndex.size();
  if (nN)
    // have normal elements
    if (normalPerVertex) {
      // normal per vertex
      if (niN >= piN) {
        // valid normal index number
        for (i = 0; i < piN; i++)
          // check if normal index equals the coord index
          if (normalIndex[i] != coordIndex[i]) {
            normalIT = VERTEX_IT;
            break;
          }
        if (normalIT == UNKNOWN_IT) {
          // if equal than delete unneeded normal index
          normalIT = VERTEX_DUP_IT;
        }
      }
      else {
        // no or not enough normal index
        normalIT = VERTEX_COORD_IT;
        if (niN) {
          FWARNING (( "Not enough normal index (%d,%d)\n",
                      normalIndex.size(), piN));
          normalIndex.clear();
        }
      }
    }
    else {
      // normal per primitive
      if (niN >= primitiveN) {
        // use one normal index per primitive
        normalIT = PRIMITIVE_INDEX_IT;
      }
      else {
        if (nN >= primitiveN) {
          // use one normal per primitive
          normalIT = PRIMITIVE_IT;
        }
        else {
          FINFO (("not enough normal index (%d,%d)\n", nN, primitiveN));
        }
      }
    }
  else {
    /* not yet !!!
    if (createNormal)
      if (normalPerVertex)
        normalIT = VERTEX_CREATE_IT;
      else
        normalIT = PRIMITIVE_CREATE_IT;
    else
    */
    normalIT = EMPTY_IT;
  }

  //----------------------------------------------------------------------
  // check the color index
  colorIT = UNKNOWN_IT;
  ciN = colorIndex.size();
  if (cN)
    // have color elements
    if (colorPerVertex) {
      // color per vertex
      if (ciN >= piN) {
        // valid color index number
        for (i = 0; i < piN; i++)
          // check if color index equals the coord index
          if (colorIndex[i] != coordIndex[i]) {
            colorIT = VERTEX_IT;
            break;
          }
        if (colorIT == UNKNOWN_IT) {
          // if equal than delete unneeded color index
          colorIT = VERTEX_DUP_IT;
        }
      }
      else {
        // no or not enough color index
        colorIT = VERTEX_COORD_IT;
        if (ciN) {
          FWARNING (( "Not enough color index (%d,%d)\n",
                      colorIndex.size(), piN));
          colorIndex.clear();
        }
      }
    }
    else {
      // color per primitive
      if (ciN >= primitiveN) {
        // use one color index per primitive
        colorIT = PRIMITIVE_INDEX_IT;
      }
      else {
        if (cN >= primitiveN) {
          // use one color per primitive
          colorIT = PRIMITIVE_IT;
        }
        else {
          FINFO (("not enough color index (%d,%d)\n", cN, primitiveN));
        }
      }
    }
  else
    colorIT = EMPTY_IT;

  //----------------------------------------------------------------------
  // check the texture index
  textureIT = UNKNOWN_IT;
  tiN = texCoordIndex.size();
  if (tN)
    // have texture elemnts
    if (tiN >= piN) {
      // valid texture index number
      for (i = 0; i < piN; i++)
        // check if texture index equals the coord index
        if (texCoordIndex[i] != coordIndex[i]) {
          textureIT = VERTEX_IT;
          break;
        }
      if (textureIT == UNKNOWN_IT) {
        // if equal than delete unneeded texture index
        textureIT = VERTEX_DUP_IT;
      }
    }
    else {
      // no or not enough texture index
      textureIT = VERTEX_COORD_IT;
      if (ciN) {
        FWARNING (( "Not enough texCoord index (%d,%d)\n",
                    texCoordIndex.size(), piN));
        texCoordIndex.clear();
      }
    }
  else
    textureIT = EMPTY_IT;

  if (faceSet) {
    FDEBUG (( "primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d 4/%d poly/%d\n",
              primitiveN,
              primitiveTypeCount[0],
              primitiveTypeCount[1],
              primitiveTypeCount[2],
              primitiveTypeCount[3],
              primitiveTypeCount[4],
              primitiveTypeCount[5] ));
  }
  else {
    FDEBUG (( "primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d\n",
              primitiveN,
              primitiveTypeCount[0],
              primitiveTypeCount[1],
              primitiveTypeCount[2],
              primitiveTypeCount[3] ));
  }

  FDEBUG (( "IndexType: coord: %s, color: %s, normal: %s, texture: %s \n",
            indexTypeStr[coordIT],
            indexTypeStr[colorIT],
            indexTypeStr[normalIT],
            indexTypeStr[textureIT] ));

    //----------------------------------------------------------------------
    // check/create the indexPtr/lengthsPtr/geoTypePtr
    indexPtr = geoPtr->getIndices();
    if (indexPtr == osg::NullFC)
        indexPtr = osg::GeoIndicesUI32::create();
    else {
	osg::beginEditCP(indexPtr);
        indexPtr->clear();
	osg::endEditCP(indexPtr);
	}

    lensPtr = geoPtr->getLengths();
    if (lensPtr == osg::NullFC)
        lensPtr = osg::GeoPLengthsUI32::create();
    else {
	osg::beginEditCP(lensPtr);
        lensPtr->clear();
	osg::endEditCP(lensPtr);
	}

    geoTypePtr = geoPtr->getTypes();
    if (geoTypePtr == osg::NullFC)
        geoTypePtr = osg::GeoPTypesUI8::create();
    else {
	osg::beginEditCP(geoTypePtr);
        geoTypePtr->clear();
	osg::endEditCP(geoTypePtr);
	}
	

    //----------------------------------------------------------------------
    // create the index mapping
    indexMapID[0] = Geometry::MapPosition;
    indexMapID[1] = Geometry::MapNormal;
    indexMapID[2] = Geometry::MapColor;
    indexMapID[3] = Geometry::MapTexCoords;
    for (mapi = i = 1; i <= 3; i++) {
      indexMap[i] = 0;
      switch (indexType[i]) {
      case UNKNOWN_IT:
      case EMPTY_IT:
        break;
      case VERTEX_COORD_IT:
      case VERTEX_DUP_IT:
        //case VERTEX_CREATE_IT:
        indexMap[0] |= indexMapID[i];
        break;
      case VERTEX_IT:
      case PRIMITIVE_IT:
      case PRIMITIVE_INDEX_IT:
        //case PRIMITIVE_CREATE_IT:
        indexMap[mapi++] = indexMapID[i];
        break;
      default: //X_CREATE_IT
        break;
      }
    }

    //----------------------------------------------------------------------
    // set lens/geoType/index/mapping the index mapping
    osg::beginEditCP(geoPtr);
    {
        geoPtr->setLengths(lensPtr);
        geoPtr->setTypes(geoTypePtr);
        geoPtr->setIndices(indexPtr);
        geoPtr->getIndexMapping().clear();
        // TODO: check for multiindex mapping ?
        // if (indexMap[1])
          for (i = 0; ((i <= 3) && indexMap[i]); i++)
            geoPtr->getIndexMapping().push_back( indexMap[i] );
    }
    osg::endEditCP(geoPtr);

    //----------------------------------------------------------------------
    // create index face/line data
    osg::beginEditCP (indexPtr);
    for (pType = minPType; pType <= maxPType; pType++) {

      // check for the pType count
      if (primitiveTypeCount[pType]) {

        // calc len/sysPType
        if (faceSet)
          if (pType < 5) {
            len = primitiveTypeCount[pType] * pType;
            sysPType = (pType == 3) ? GL_TRIANGLES : GL_QUADS;
          }
          else
            sysPType = 0;
        else
          if (pType == 2) {
            len = primitiveTypeCount[pType] * pType;
            sysPType = GL_LINES;
          }
          else
            sysPType = 0;

        // set len/sysPType
        if (sysPType) {
          osg::beginEditCP(lensPtr);
          {
            lensPtr->push_back(len);
          }
          osg::endEditCP (lensPtr);

          osg::beginEditCP (geoTypePtr);
          {
            geoTypePtr->push_back( sysPType );
          }
          osg::endEditCP (geoTypePtr);
        }

        primitiveN = 0;
        beginIndex = endIndex = -1;
        for ( i = 0; i <= piN; i++) {
          if ( ( (i == piN) && (coordIndex[i - 1] >= 0) ) ||
               ( (i <  piN) && (coordIndex[i    ] <  0) ) ) {

            len = i - beginIndex;
            if (ccw) {
              endIndex = i;
              step = 1;
            }
            else {
              endIndex = beginIndex - 1;
              beginIndex = i - 1;
              step = -1;
            }
            localPType = (len > maxPType) ? maxPType : len;
            if ((beginIndex >= 0) && (localPType == pType)) {
              if (len >= maxPType) {
                sysPType = faceSet ? GL_POLYGON : GL_LINE_STRIP;
                osg::beginEditCP(lensPtr);
                {
                  lensPtr->push_back(len);
                }
                osg::endEditCP (lensPtr);
                osg::beginEditCP (geoTypePtr);
                {
                  geoTypePtr->push_back( sysPType );
                }
                osg::endEditCP (geoTypePtr);
              }

              // add index data
              for (pi = beginIndex; pi != endIndex; pi += step) {
                indexPtr->push_back(coordIndex[pi]);
                for (mapi = 1; (mapi <= 3) && (indexMap[mapi]); mapi++) {
                  for (typei = 1; typei <= 3; typei++) {
                    if (indexMap[mapi] & indexMapID[typei]) {
                      switch (indexType[typei]) {
                      case UNKNOWN_IT:
                      case EMPTY_IT:
                      case VERTEX_COORD_IT:
                      case VERTEX_DUP_IT:
                        FFATAL (("Fatal index mapping error \n"));
                        break;
                      case VERTEX_IT:
                        index = (*indexBag[typei])[pi];
                        break;
                      case PRIMITIVE_IT:
                        index = primitiveN;
                        break;
                      case PRIMITIVE_INDEX_IT:
                        index = (*indexBag[typei])[primitiveN];
                        break;
                      default: //X_CREATE_IT
                        break;
                      }
                      indexPtr->push_back(index);
                    }
                  }
                }
              }
              triCount += len - 2;
            }
            primitiveN++;
            beginIndex = endIndex = -1;
          }
          else
            if (beginIndex < 0)
              beginIndex = i;
        }
      }
    }
    osg::endEditCP (indexPtr);

    return triCount;
}

/*! \brief optimize the geo by creating strips and fans,
 *  creates new index values but does not touch the property values
 *  returns the number of points to be tranformed
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 osg::createOptimizedPrimitives(GeometryPtr geoPtr,
                                     UInt32     iteration,
                                     bool       OSG_CHECK_ARG(createStrips   ),
                                     bool       OSG_CHECK_ARG(createFans     ),
                                     UInt32     OSG_CHECK_ARG(minFanEdgeCount),
                                     bool       OSG_CHECK_ARG(colorCode      ))
{
  NodeGraph graph;
  std::vector<NodeGraph::Path> pathVec[2];
  TriangleIterator tI;
  GeoPositionsPtr posPtr;
  Int32 cost = 0, startCost, bestCost = 0, worstCost = 0, best = 0;
  Int32 i, j, k, n, pN, index, indexMapSize;
  bool multiIndex;
  std::vector<int> primitive;
  GeoPLengthsPtr lensPtr;
  GeoPTypesPtr geoTypePtr;
  GeoIndicesPtr indexPtr = NullFC;
  Time time, inputT, optimizeT, outputT;
  UInt32 triN, lineN, pointN, triCount;
  Int32 typeVec[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN };
  Int32 t,typeN = sizeof(typeVec)/sizeof(Int32);
  std::vector<Int32> indexVec;
  Int32 v[3];
  IndexDic indexDic;
  bool invalidTriCount = 0;

  if (geoPtr != NullFC) 
    {
      posPtr = geoPtr->getPositions();
      pN = ((posPtr == osg::NullFC) ? 0 : posPtr->getSize());
      indexMapSize = (geoPtr->getIndexMapping().size());
      multiIndex = (indexMapSize > 1) ? true : false;
      calcPrimitiveCount(geoPtr,triN,lineN,pointN);
      indexPtr = geoPtr->getIndices();      
      if (indexPtr == NullFC)
        startCost = pN;
      else
      {
        if (indexMapSize)
          startCost = indexPtr->size() / indexMapSize;
        else
          startCost = indexPtr->size();
      }
    }
  else
    {
      pN = 0;
    }

  if (pN && (indexPtr != NullFC))
    {

      FNOTICE (( "GeoOpt: start/tri cost: %d/%d imp: %d tri/line/point: %d/%d/%d\n",
                 startCost, (triN * 3), indexMapSize, triN, lineN, pointN));
      
      inputT = getSystemTime();

      triCount = 0;
      invalidTriCount = 0;
      if (multiIndex) 
        {
          graph.init(triN * 3, triN, 8);
          indexVec.resize(indexMapSize);
          for ( tI = geoPtr->beginTriangles(); 
                tI != geoPtr->endTriangles(); ++tI)
            {
              for (i = 0; i < 3; i++)
                {
                  index = tI.getIndexIndex(i);
                  for (j = 0; j < indexMapSize; j++)
                    indexVec[j] = indexPtr->getValue(index + j);
                  v[i] = indexDic.entry(indexVec);
                }
              invalidTriCount +=
                graph.setNode ( triCount++, v[0], v[1], v[2] ) ? 0 : 1;
            }
          FNOTICE (( "Multi-index dic entry: %d/%d\n", 
                     indexDic.entryCount(), (triN * 3) ));
        }
      else
        {
          graph.init(pN,triN,8); 
          for ( tI = geoPtr->beginTriangles(); 
                tI != geoPtr->endTriangles(); ++tI)
            invalidTriCount += graph.setNode( triCount++,
                                              tI.getPositionIndex(0),
                                              tI.getPositionIndex(1),
                                              tI.getPositionIndex(2) )
              ? 0 : 1;
        }
      
      if (invalidTriCount)
        {
          FWARNING (("%d invalid tri during halfegde construction found\n",
                     invalidTriCount ));
        }

      graph.verify(true);
      if (triN != triCount) 
        {
          FFATAL (("Triangle count missmatch (%d/%d)\n", triN, triCount));
          return 0;
        }
      
      pathVec[1].resize(triN);
      if (iteration > 1)
        pathVec[0].resize(triN);
      
      //----------------------------------------------------------------------
      // create surface path vector with sampling
      FDEBUG (("Start path.createPathVec() \n"));
      time = getSystemTime();
      inputT = time - inputT;
      optimizeT = time;
      bestCost = triN * 3 + 1;
      worstCost = 0;
      for (i = 0; i < iteration; i++) 
        {
          cost = graph.createPathVec(pathVec[!best]);
          if (cost) 
            {
              if (cost < bestCost) 
                {
                  bestCost = cost;
                  best = !best;
                }
              if (cost > worstCost)
                worstCost = cost;
            }
          else 
            {
              bestCost = worstCost = 0;
              break;
            }
        }
      
      // valid result
      if (bestCost && (bestCost < startCost))
        {
          // check/create the indexPtr/lengthsPtr/geoTypePtr
          
          osg::beginEditCP(geoPtr, osg::Geometry::LengthsFieldMask | 
                                   osg::Geometry::TypesFieldMask    );

          lensPtr = geoPtr->getLengths();
          if (lensPtr == osg::NullFC)
          {
            lensPtr = osg::GeoPLengthsUI32::create();
            geoPtr->setLengths(lensPtr);
          }
          
          geoTypePtr = geoPtr->getTypes();
          if (geoTypePtr == osg::NullFC)
          {
            geoTypePtr = osg::GeoPTypesUI8::create();
            geoPtr->setTypes(geoTypePtr);
          }
          
          osg::endEditCP(geoPtr, osg::Geometry::LengthsFieldMask | 
                                 osg::Geometry::TypesFieldMask    );
          
          time = getSystemTime();
          optimizeT = time - optimizeT;
          outputT = time;
          
          beginEditCP(lensPtr);
          beginEditCP(geoTypePtr);
          beginEditCP(indexPtr);
          
          lensPtr->clear();
          geoTypePtr->clear();
          indexPtr->clear();
          
          FDEBUG (("Start graph.getPrimitive() loop (triN: %d)\n", triN));
          
          triCount = 0;
          cost = 0;
          for (t = 0; t < typeN; t++) 
            {
              for (i = 0; i < triN; i++) 
                {
                  if (pathVec[best][i].type == typeVec[t]) 
                    {
                      cost += n = graph.getPrimitive(pathVec[best][i],
                                                     primitive);
                      if (n) 
                        {
                          if (typeVec[t] == GL_TRIANGLES)
                            triCount += (n / 3);
                          else {
                             lensPtr->push_back(n);
                             geoTypePtr->push_back( typeVec[t] );
                          }
                          if (multiIndex)
                            {
                              for (j = 0; j < n; j++)
                                for (k = 0; k < indexMapSize; k++)
                                  {
                                    index = indexDic.entry( primitive[j] )[k];
                                    indexPtr->push_back ( index );
                                  }
                            }
                          else
                            for (j = 0; j < n; j++)
                              indexPtr->push_back( primitive[j]);
                        }
                      else
                        break;
                    }
                }

              if (triCount) 
                {
                  lensPtr->push_back(triCount * 3);
                  geoTypePtr->push_back( GL_TRIANGLES );
                  triCount = 0;
                }
            }

          endEditCP(lensPtr);
          endEditCP(geoTypePtr);
          endEditCP(indexPtr);
         
          time = getSystemTime();
          outputT = time - outputT;
          
          FNOTICE (( "Graph in/opt/out timing: %g/%g/%g \n",
                     inputT, optimizeT, outputT  ));

          if (cost != bestCost) {
            FFATAL (( "cost != bestCost: %d/%d; we lost some nodes !\n",
                      cost, bestCost ));
          }
          else {
            FNOTICE (( "OptResult: %2g%%, Sampling (%di): cost %d/%d \n",
                       double ( double(bestCost) / double(startCost) * 100.0),
                       iteration, bestCost, worstCost ));
          }
        }
      else 
        {
          FNOTICE (( "startCost (%d) <= bestCost (%d), triCost(%d); keep geo data\n",
                     startCost, bestCost, (triN * 3) ));
        }
    }
  
  return bestCost;
}

/*! \brief creates new index to share vertex property data
 *  \ingroup Geometry
 */

OSG_SYSTEMLIB_DLLMAPPING
Int32 osg::createSharedIndex ( GeometryPtr geoPtr )
{

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

  UInt32 indexSharedCount = 0, dataRemapCount = 0, indexRemapCount = 0;
  UInt32 i, iN, index, si, sN;
  UInt32 indexMapSize, indexBlock = 0, masterDSize;
  AbstractGeoPropertyInterface *masterProp = 0, *slaveProp = 0;
  UInt8  *masterData;
  std::vector<UInt32> slaveDSizeVec;
  std::vector<UInt8*> slaveDataVec;
  UInt16 mapMask, propMask, masterPropMask;
  typedef std::pair<UInt8*,UInt32> Mem;
  Mem mem;
  std::map< Mem, UInt32, memless<Mem> > memMap;
  std::map< Mem, UInt32, memless<Mem> >::iterator mmI;
  GeoIndicesPtr indexPtr;
  UChar8 *dataElem;
  std::vector<Int32> indexRemap;

  if (geoPtr != NullFC)
  {
    if (geoPtr->getPositions() != NullFC) 
    {
      // check/create indexPtr
      iN = geoPtr->getPositions()->size();
      indexPtr = geoPtr->getIndices();
      if (indexPtr == NullFC) 
      {
          indexPtr = GeoIndicesUI32::create();
          indexPtr->resize(iN);
          for (i = 0; i < iN; i++) 
            indexPtr->setValue( i, i );
          beginEditCP(geoPtr);
          {
            geoPtr->setIndices(indexPtr);
          }
          endEditCP(geoPtr);
      }
    }
    else 
    {
        FFATAL (("Invalid geoPtr->getPositions() in createSharedIndex()\n"));
    }      
  }
  else 
  {
    FFATAL (("Invalid geoPtr in createSharedIndex()\n"));
  }

  if ( indexPtr != NullFC )
  {
    // get the index count
    indexMapSize = geoPtr->getIndexMapping().size();
    
    // find first propMask;
    if (indexMapSize) 
    {
      propMask = geoPtr->getIndexMapping()[0];
    }
    else
    {
      // no index geo; find valid property
      for ( mapMask = 1, propMask = 0; 
            mapMask && mapMask != Geometry::MapEmpty; 
            mapMask <<= 1 )
      {
        if (geoPtr->getProperty(mapMask))
          propMask |= mapMask;
      }
      indexMapSize = 1;
    }
      
    // remap the index for a single index block
    for (indexBlock = 0; propMask;) 
    {
      // reset stat counter
      indexSharedCount = 0;
      dataRemapCount = 0;
      indexRemapCount = 0;

      // find master property
      for (masterPropMask = 1; (propMask & masterPropMask) == 0;)
        masterPropMask <<= 1;

      if ( (masterProp = geoPtr->getProperty(masterPropMask)) &&
           (masterData = masterProp->getData() ) )
      {
        // calc master data element size
        masterDSize = 
          masterProp->getFormatSize() * masterProp->getDimension()  + 
          masterProp->getStride();

        // find and store slave property data and size
        slaveDataVec.clear();
        slaveDSizeVec.clear();
        for ( mapMask = 1;
              mapMask && mapMask != Geometry::MapEmpty;
              mapMask <<= 1 )
          if ((mapMask != masterPropMask) && (mapMask & propMask))
            if ( (slaveProp = geoPtr->getProperty(mapMask & propMask)) )
            {
              slaveDataVec.push_back  ( slaveProp->getData() );
              slaveDSizeVec.push_back ( slaveProp->getFormatSize() * 
                                        slaveProp->getDimension() );
            }
            else
            {
              FFATAL (("Invalid slaveProp %d\n", (mapMask & propMask)));
            }

        sN = slaveDataVec.size();
        iN = indexPtr->size() / indexMapSize;
        memMap.clear();
        indexRemap.clear();
        indexRemap.resize(masterProp->size(), -1);
        mem.second = masterProp->getFormatSize() * masterProp->getDimension();

        for (i = 0; i < iN; i++) 
        {
          index = indexPtr->getValue(i * indexMapSize + indexBlock);          
          if (indexRemap[index] >= 0) {
            if (indexRemap[index] == index)
            {
              indexSharedCount++;
            }
            else
            {
              indexPtr->setValue( indexRemap[index], 
                                  i * indexMapSize + indexBlock );
              indexRemapCount++;
            }
          }
          else {
            // find/include the data block
            dataElem = masterData + (index * masterDSize);
            mem.first = dataElem;
            mmI = memMap.find(mem);
            if (mmI == memMap.end())
            {
                // index not found; store new data/index
                memMap[mem] = index;
                indexRemap[index] = index;
            }
            else
            {
                // data found; check slave property
                for ( si = 0; si < sN; si++ )
                  if ( memcmp( slaveDataVec[si] + 
                               (index * slaveDSizeVec[si]),
                               slaveDataVec[si] + 
                               (mmI->second * slaveDSizeVec[si]),
                               slaveDSizeVec[si] ) )
                    break;

                if (si == sN) 
                {
                  // no or valid slave data; remap the index
                  indexPtr->setValue ( mmI->second,
                                       i * indexMapSize + indexBlock );
                  indexRemap[index] = mmI->second;
                  dataRemapCount++;
                }
                else 
                {
                  // invalid slave data; cannot remap index
                  indexRemap[index] = index;
                }
            }
          }
        }
      }
      else
      {
        FFATAL (("Invalid masterProp %d, mask: %d, block: %d\n", 
                 int(masterProp), propMask, indexBlock ));
      }
      
      FNOTICE (("Create sharedIndex: %d/%d pass; data/index remap: %d/%d \n",
                indexBlock, int(propMask), 
                dataRemapCount, indexRemapCount ));

      // get next propery Mask
      if (++indexBlock < indexMapSize)
        propMask = geoPtr->getIndexMapping()[indexBlock];
      else
        propMask = 0;
    }
  }

  return (indexRemapCount + dataRemapCount);

#else

  FFATAL (( "Cannot run createSharedIndex: NO_GEO_INFACE\n" ));

#endif

}


/*! \brief creates a single index geo from multi(interleave) geo.
 *  function will change (resort) the properties.
 *  returns the number of property values
 *  \ingroup Geometry
 */

OSG_SYSTEMLIB_DLLMAPPING
Int32 osg::createSingleIndex ( GeometryPtr geoPtr )
{

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE

  Int16 mask, maskID, finalMask = 0;
  Int32 indexMapSize, indexCount, i, j,  vCount = 0;
  Int32 index;
  Int32 memSize, valueSize;
  UInt8  *pData, *data;
  GeoIndicesPtr indexPtr;
  IndexDic indexDic;
  std::vector<Int32> indexVec, sIndex;
  AbstractGeoPropertyInterface * pP = 0;
  
  if ( (geoPtr != NullFC) &&
       (indexMapSize = (geoPtr->getIndexMapping().size()) ) )
    {
      indexPtr = geoPtr->getIndices();
      indexVec.resize(indexMapSize);

      // fill the indexDic
      if (indexPtr != NullFC)
        {
          indexCount = indexPtr->size() / indexMapSize;
          sIndex.resize(indexCount);
          for (i = 0; i < indexCount; i++)
            {
              for (j = 0; j < indexMapSize; j++) 
                indexVec[j] = indexPtr->getValue(i * indexMapSize + j);
              sIndex[i] = indexDic.entry(indexVec);
            }
          vCount = indexDic.entryCount();
        }      
      else
        vCount = 0;

      // sort/copy property values
      finalMask = 0;
      if (vCount)
        {
          for (i = 0; i < indexMapSize; i++)
            {
              mask = geoPtr->getIndexMapping()[i];
              for (maskID = 1; maskID; maskID <<= 1)
                if ( (mask & maskID) &&
                     (pP = geoPtr->getProperty(maskID) ) )
                  {
                    valueSize = 
                      pP->getFormatSize() * pP->getDimension() + 
                      pP->getStride();
                    finalMask |= maskID;
                    memSize = pP->size() * valueSize;
                    data = new UInt8 [memSize];
                    pData = pP->getData();
                    memcpy (data,pData,memSize);
                    pP->resize(vCount);
                    pData = pP->getData();
                    for (j = 0; j < vCount; j++)
                      {
                        index = indexDic.entry(j)[i];
                        memcpy ( pData + (valueSize * j),
                                 data +  (valueSize * index),
                                 valueSize );
                      }
                    delete [] data;
                  }
            }
        }

      // copy single index and set the single mask
      if (finalMask) 
        {
          indexPtr->clear();
          for (i = 0; i < indexCount; i++)
            indexPtr->push_back(sIndex[i]);
          geoPtr->getIndexMapping().clear();
          geoPtr->getIndexMapping().push_back(finalMask);
        }
      else 
        {
          FFATAL (("No valid finalMask in createSingleIndex()\n"));
        }
    }

  return vCount;

#else

  FFATAL (( "Cannot run createSingleIndex: NO_GEO_INFACE\n" ));

#endif

}

/*! \brief return the number of triangle/line/point elem
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
UInt32 osg::calcPrimitiveCount ( GeometryPtr geoPtr,
                                 UInt32 &triangle,
                                 UInt32 &line,
                                 UInt32 &point )
{
  GeoPTypesUI8Ptr geoTypePtr;
  GeoPLengthsUI32Ptr lensPtr;
  GeoPTypesUI8Ptr::StoredObjectType::StoredFieldType::iterator typeI, endTypeI;
  GeoPLengthsUI32Ptr::StoredObjectType::StoredFieldType::iterator lenI;
  UInt32 lN, tN, len, type;

  // TODO; should we really reset the values ?
  triangle = line = point = 0;

  if (geoPtr == osg::NullFC) {
    FWARNING (("No geo in calcPrimitiveCount\n"));
  }
  else 
  {
    lensPtr = GeoPLengthsUI32Ptr::dcast( geoPtr->getLengths() );
    lN = (lensPtr == osg::NullFC) ? 0 : lensPtr->getSize();

    geoTypePtr = GeoPTypesUI8Ptr::dcast( geoPtr->getTypes() );
    tN = (geoTypePtr == osg::NullFC) ? 0 : geoTypePtr->getSize();

    if ((tN == 0) || (lN != 0 && tN != lN) || (lN == 0 && tN != 1)) 
    {
      FWARNING (("calcPrimitiveCount: Invalid GeoPLengths and "
                 "GeoPTypes data\n"));
    }
    else {
      typeI = geoTypePtr->getField().begin();
      if(lN != 0)
        lenI = lensPtr->getField().begin();
      endTypeI = geoTypePtr->getField().end();
      while ( typeI != endTypeI  ) {
        type = *typeI;
        if(lN != 0)
        {
            len = *lenI;
        }
        else
        {
            GeoPositionsPtr pos = geoPtr->getPositions();
            
            if(pos == osg::NullFC)
            {
                FWARNING (("calcPrimitiveCount: no Points!\n"));
                return -1;
            }
            
            len = pos->size();
        }
        switch (type) {
        case GL_POINTS:
          point += len;
          break;
        case GL_LINES:
          line += len / 2;
          break;
        case GL_LINE_LOOP:
          line += len;
          break;
        case GL_LINE_STRIP:
          line += len - 1;
          break;
        case GL_TRIANGLES:
          triangle += len / 3;
          break;
        case GL_TRIANGLE_STRIP:
          triangle += len - 2;
          break;
        case GL_TRIANGLE_FAN:
          triangle += len - 2;
          break;
        case GL_QUADS:
          triangle += len / 2;
          break;
        case GL_QUAD_STRIP:
          triangle += len - 2;
          break;
        case GL_POLYGON:
          triangle += len - 2;
          break;
        default:
          FWARNING (("Invalid geoType: %d\n", type));
          break;
        }
        ++typeI;
        ++lenI;
      }
    }
  }

  return (triangle + line + point);
}



OSG_SYSTEMLIB_DLLMAPPING
void osg::calcFaceNormals( GeometryPtr geo )
{
  GeoIndicesPtr newIndex = GeoIndicesUI32::create();
  GeoNormalsPtr newNormals = GeoNormals3f::create();
  Vec3f normal;

  FaceIterator faceIter = geo->beginFaces();
  GeoIndicesPtr oldIndex = geo->getIndices();

  if( oldIndex != NullFC )
    {
      //Indexed
      if( geo->getIndexMapping().size() > 0 )
    {
      //MULTI INDEXED
      beginEditCP(newIndex);
      MFUInt16 &oldIndexMap = geo->getIndexMapping();
      UInt32 oldIMSize = oldIndexMap.size();
      for( UInt32 i=0; i<oldIndex->getSize()/oldIMSize; ++i )
        {
          for( UInt32 k=0; k<oldIMSize; ++k )
        {
          newIndex->push_back( oldIndex->getValue(i*oldIMSize+k) );
        }
          newIndex->push_back(0);  //placeholder for normal index
        }

      beginEditCP(newNormals);
      for( UInt32 faceCnt=0; faceIter != geo->endFaces(); ++faceIter, ++faceCnt )
        {
          if( faceIter.getLength() == 3 )
        {
          //Face is a Triangle
          normal = (faceIter.getPosition(1)-faceIter.getPosition(0)).cross( faceIter.getPosition(2)-faceIter.getPosition(0) );
          normal.normalize();
        }
          else
        {
          //Face must be a Quad then
          normal = (faceIter.getPosition(1)-faceIter.getPosition(0)).cross( faceIter.getPosition(2)-faceIter.getPosition(0) );
          if( normal.length() == 0 )
            {
              //Quad is degenerate, choose different points for normal
              normal = (faceIter.getPosition(1)-faceIter.getPosition(2)).cross( faceIter.getPosition(3)-faceIter.getPosition(2) );
            }
          normal.normalize();
        }
          newNormals->push_back( normal ); //put the normal into the storage
          UInt32 base;
          switch( faceIter.getType() )
        {
        case GL_TRIANGLE_STRIP:
          base = faceIter.getIndexIndex(2);   //get last point's position in index field
          newIndex->setValue( faceCnt, base+(base/oldIMSize)+oldIMSize );
          break;
        case GL_TRIANGLE_FAN:
          base = faceIter.getIndexIndex(2);   //get last point's position in index field
          newIndex->setValue( faceCnt, base+(base/oldIMSize)+oldIMSize );
          break;
        case GL_QUAD_STRIP:
          base = faceIter.getIndexIndex(3);    //get last point's position in index field
          newIndex->setValue( faceCnt, base+(base/oldIMSize)+oldIMSize );
          break;
        default:
          for( UInt32 i=0; i<faceIter.getLength(); ++i )
            {
              base = faceIter.getIndexIndex(i);
              newIndex->setValue( faceCnt, base+(base/oldIMSize)+oldIMSize );
            }
          break;
        }
        }
      endEditCP(newNormals);
      endEditCP(newIndex);

      beginEditCP(geo);
      Int16 ni;
      ni = geo->calcMappingIndex( Geometry::MapNormal );
      if ( ni!=-1 )
        {
          oldIndexMap[ni] = oldIndexMap[ni] & ~ Geometry::MapNormal;
        }
      oldIndexMap.push_back( Geometry::MapNormal );
      geo->setNormals( newNormals );
      geo->setIndices( newIndex );
      endEditCP(geo);
      return;
    }
    }
  //SINGLE INDEXED or NON INDEXED
  //UInt32 pointCnt = 0;
  newNormals->resize( geo->getPositions()->getSize() );
  for( ;faceIter!=geo->endFaces(); ++faceIter )
    {
      if( faceIter.getLength() == 3 )
    {
      //Face is a Triangle
      normal = (faceIter.getPosition(1)-faceIter.getPosition(0)).cross( faceIter.getPosition(2)-faceIter.getPosition(0) );
      normal.normalize();
    }
      else
    {
      //Face must be a Quad then
      normal = (faceIter.getPosition(1)-faceIter.getPosition(0)).cross( faceIter.getPosition(2)-faceIter.getPosition(0) );
      if( normal.length() == 0 )
        {
          //Quad is degenerate, choose different points for normal
          normal = (faceIter.getPosition(1)-faceIter.getPosition(2)).cross( faceIter.getPosition(3)-faceIter.getPosition(2) );
        }
      normal.normalize();

    }
      switch( faceIter.getType() )
    {
    case GL_TRIANGLE_STRIP:
      newNormals->setValue( normal, faceIter.getPositionIndex(2) );
      break;
    case GL_TRIANGLE_FAN:
      newNormals->setValue( normal, faceIter.getPositionIndex(2) );
      break;
    case GL_QUAD_STRIP:
      newNormals->setValue( normal, faceIter.getPositionIndex(3) );
      break;
    default:
      for( UInt32 i=0; i<faceIter.getLength(); ++i )
        {
          newNormals->setValue( normal, faceIter.getPositionIndex(i) );
        }
      break;
    }
      beginEditCP( geo );
      geo->setNormals( newNormals );
      endEditCP( geo );
    }
}





OSG_SYSTEMLIB_DLLMAPPING NodePtr osg::getFaceNormals(GeometryPtr geo, Real32 length)
{
  NodePtr  p = Node::create();
  GeometryPtr g = Geometry::create();
  GeoPositions3f::PtrType pnts = GeoPositions3f::create();
  GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
  GeoPTypesPtr type = GeoPTypesUI8::create();
  GeoPLengthsPtr lens = GeoPLengthsUI32::create();

  // calculate

  FaceIterator faceIter = geo->beginFaces();
  Pnt3f center;

  beginEditCP(pnts);
  for( ; faceIter != geo->endFaces(); ++faceIter )
    {
      center[0] = 0;
      center[1] = 0;
      center[2] = 0;
      for( UInt16 i=0; i<faceIter.getLength(); ++i )
    {
      center[0] += faceIter.getPosition( i )[0]/faceIter.getLength();
      center[1] += faceIter.getPosition( i )[1]/faceIter.getLength();
      center[2] += faceIter.getPosition( i )[2]/faceIter.getLength();
    }
      pnts->push_back( center );
      switch( faceIter.getType() )
    {
    case GL_TRIANGLE_STRIP:
      pnts->push_back( center + length * faceIter.getNormal(2) );
      break;
    case GL_TRIANGLE_FAN:
      pnts->push_back( center + length * faceIter.getNormal(2) );
      break;
    case GL_QUAD_STRIP:
      pnts->push_back( center + length * faceIter.getNormal(3) );
      break;
    default:
      pnts->push_back( center + length * faceIter.getNormal(0) );  //does not matter which points normal
      break;
    }
    }
  endEditCP(pnts);

  beginEditCP(index);
  for ( UInt32 i = 0; i < pnts->getSize(); i++ )
    index->push_back( i );
  endEditCP(index);

  beginEditCP(type);
  type->push_back( GL_LINES );
  endEditCP(type);

  beginEditCP(lens);
  lens->push_back( index->getSize() );
  endEditCP(lens);

  beginEditCP(g);
  g->setTypes( type );
  g->setLengths( lens );
  g->setIndices( index );
  g->setPositions( pnts );
  endEditCP(g);

  beginEditCP(p);
  p->setCore(g);
  endEditCP(p);

  return p;
}

OSG_SYSTEMLIB_DLLMAPPING
void osg::mergeGeometries(std::vector<NodePtr> &nodes,
                          std::vector<NodePtr> &results)
{
    FFATAL(( "Merge Geometries: Not implemented yet!\n"));
    results.clear();

    for ( std::vector<NodePtr>::iterator n = nodes.begin();
          n != nodes.end(); ++n )
    {
        GeometryPtr actnode = GeometryPtr::dcast((*n)->getCore());

    if ( actnode == NullFC )
    {
        FWARNING(( "mergeGeometries: core of 0x%p is not a geometry!\n",
                    n->getCPtr() ));
        continue;
    }

    std::vector<NodePtr>::iterator r;
    for ( r = nodes.begin(); r != nodes.end(); ++r )
    {
        GeometryPtr res = GeometryPtr::dcast((*r)->getCore());

            if ( res->isMergeable( actnode ) )
        {
            res->merge( actnode );
        }
    }

        if ( r == nodes.end() )
    {
        // need a new one
        NodePtr node = Node::create();

        beginEditCP( node );
        node->setCore( actnode->clone() );
        endEditCP( node );

        results.push_back( node );
    }
    }
}
