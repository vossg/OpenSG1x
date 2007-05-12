/*---------------------------------------------------------------------------* \
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

#include <set>

#include "OSGConfig.h"

#include <OSGLog.h>

#include <OSGGLU.h>

#include "OSGGeometry.h"
#include "OSGGeoPropPtrs.h"
#include "OSGTriangleIterator.h"
#include "OSGGeoFunctions.h"
#include "OSGFaceIterator.h"

//#include "OSGNodeGraph.h"
#include "OSGHalfEdgeGraph.h"

OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning(disable : 383)
#endif
#ifdef __sgi
#pragma set woff 1209
#endif

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcVertexNormals calculates the normals for the geometry's vertices, see 
    \ref PageSystemGeoFunctionsCalcNormals for a description. 
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::calcVertexNormals(GeometryPtr geo)
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
    GeoNormalsPtr   norms;
    typedef std::set<UInt32> IndexSet;
    IndexSet used_indices;

    if(geo->getNormals() == NullFC)
    {
        norms = GeoNormals3f::create();
    }
    else
    {
        norms = geo->getNormals();
    }
    beginEditCP(norms);

    norms->resize(geo->getPositions()->getSize());

    // problem: not all of the points of the property might be used by this
    // geometry. If the property has more than 1 users, be careful.
    if(norms->getParents().size() > 1)
    {
        for(TriangleIterator t = geo->beginTriangles(); t != geo->endTriangles();
                    ++t)
        {
            used_indices.insert(t.getPositionIndex(0));
            used_indices.insert(t.getPositionIndex(1));
            used_indices.insert(t.getPositionIndex(2));
        }

        for (IndexSet::iterator i = used_indices.begin();
             i != used_indices.end();
             ++i)
        {
            norms->setValue(Vec3f(0, 0, 0), *i);
        }
    }
    else            // just one user, can clear all
    {
        for(unsigned i = 0; i < geo->getPositions()->getSize(); i++)
        {
            norms->setValue(Vec3f(0, 0, 0), i);
        }
    }

    for(TriangleIterator t = geo->beginTriangles(); t != geo->endTriangles();
            ++t)
    {
        Pnt3f p0 = t.getPosition(0);
        Pnt3f p1 = t.getPosition(1);
        Pnt3f p2 = t.getPosition(2);
        Plane p(p0, p1, p2);

        Int32 i0 = t.getPositionIndex(0);
        Int32 i1 = t.getPositionIndex(1);
        Int32 i2 = t.getPositionIndex(2);
        norms->setValue( norms->getValue(i0) + p.getNormal(), i0 );
        norms->setValue( norms->getValue(i1) + p.getNormal(), i1 );
        norms->setValue( norms->getValue(i2) + p.getNormal(), i2 );
    }
    if(norms->getParents().size() > 1)
    {
        std::set < UInt32 >::iterator i = used_indices.begin();
        std::set < UInt32 >::iterator end = used_indices.end();

        while(i != end)
        {
            Vec3f   n = norms->getValue(*i);
            n.normalize();
            norms->setValue(n, *i);

            ++i;
        }
    }
    else            // just one user, can clear all
    {
        for(unsigned i = 0; i < geo->getPositions()->getSize(); i++)
        {
            Vec3f   n = norms->getValue(i);
            n.normalize();
            norms->setValue(n, i);
        }
    }
    endEditCP(norms);

    beginEditCP(geo);
    {
        geo->setNormals(norms);

        MFUInt16    &im = geo->getIndexMapping();
        if(im.size() > 0)
        {
            Int16   pi, ni;
            pi = geo->calcMappingIndex(Geometry::MapPosition);
            ni = geo->calcMappingIndex(Geometry::MapNormal);

            if(ni >= 0)
            {
                im[ni] = im[ni] &~Geometry::MapNormal;
            }
            if(pi >= 0)
            {
                im[pi] = im[pi] | Geometry::MapNormal;
            }
        }
    }
    endEditCP(geo);
}
#ifdef __sgi
#pragma reset woff 1209
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
/*! \ingroup STLHelpers
    vector comparison
*/
template<class type>
struct vecless
{
    bool operator () (const type &a, const type &b) const
    {
        UInt32  i;
        bool    ret = false;

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

/*! \ingroup STLHelpers
    memory comparison
*/
template<class type>
struct memless
{
    bool operator () (const type &a, const type &b) const
    {
        if(a.second && b.second)
        {
            if(a.second == b.second)
            {
                return (memcmp(a.first, b.first, a.second) < 0) ? true : false;
            }
            else
            {
                FFATAL(("a.memSize != b.memSize in memless::operator()\n"));
            }
        }
        else
        {
            FFATAL(("memSize is NULL in memless::operator()\n"));
        }
        return false;
    }
};
#endif  // remove from all but dev docs


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcVertexNormals calculates the normals for the geometry's vertices, see
    \ref PageSystemGeoFunctionsCalcNormals for a description. 
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::calcVertexNormals(GeometryPtr geo,
                                                     Real32 creaseAngle)
{
    GeoNormalsPtr   norms;
    GeoPositionsPtr positions;

    if(creaseAngle >= Pi)
    {
        calcVertexNormals(geo);
        return;
    }

    // Get the positions property
    if(geo->getPositions() == NullFC)
    {
        FINFO(("Geo without positions in calcVertexNormals()\n"));
        return;
    }
    else
    {
        positions = geo->getPositions();
    }

    if(positions->size() < 3)
    {
        FINFO(("Geo with less than 3 positions in calcVertexNormals()\n"));
        return;
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
        geo->setNormals(norms);
    }

    endEditCP(geo);

    // Do the normals have their own index?
    MFUInt16        &im = geo->getIndexMapping();
    Int16           ni = geo->calcMappingIndex(Geometry::MapNormal);
    GeoIndicesPtr   ip = geo->getIndices();
    
    // HACK but without indices it crashes.
    if(ip == NullFC || ip->size() == 0)
    {
        FINFO(("Geo without indices in calcVertexNormals()\n"));
        return;
    }

    UInt32          nind = ip->size() / (im.size() ? im.size() : 1);
    int             imsize = 0;
    if(ni < 0 || im[ni] != Geometry::MapNormal)
    {
        // normals need their own index
        if(ni >= 0)
        {
            im[ni] = im[ni] &~Geometry::MapNormal;
        }

        // need to be multi-indexed?
        if(im.size() == 0)
        {
            UInt32  map = Geometry::MapPosition;

            if(geo->getTexCoords() != NullFC)
                map |= Geometry::MapTexCoords;

            if(geo->getColors() != NullFC)
                map |= Geometry::MapColor;

            im.push_back(map);
        }

        ni = im.size();
        im.push_back(Geometry::MapNormal);

        // add an entry to the indices for the normals
        imsize = im.size();

        beginEditCP(ip);
        ip->resize(nind * imsize);

        for(UInt32 i = nind - 1; i > 0; --i)
        {
            for(Int16 j = imsize - 2; j >= 0; --j)
            {
                UInt32  val;
                ip->getValue(val, i * (imsize - 1) + j);
                ip->setValue(val, i * imsize + j);
            }

            ip->setValue(i, i * imsize + imsize - 1);
        }

        ip->setValue(0, imsize - 1);
        endEditCP(ip);
    }
    else            // set the normal indices
    {
        imsize = im.size();
        beginEditCP(ip);
        for(UInt32 i = 0; i < nind; ++i)
        {
            ip->setValue(i, i * imsize + ni);
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
                    ti != geo->endTriangles(); ++ti)
        {
            Vec3f   d1 = ti.getPosition(1) - ti.getPosition(0);
            Vec3f   d2 = ti.getPosition(2) - ti.getPosition(0);
            d1.crossThis(d2);

            d1.normalize();

            norms->setValue(d1, ti.getNormalIndex(0));
            norms->setValue(d1, ti.getNormalIndex(1));
            norms->setValue(d1, ti.getNormalIndex(2));
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
    std::vector < Vec3f > faceNormals;
    std::multimap<Pnt3f, UInt32, vecless<Pnt3f> > pntMap;

    TriangleIterator    ti;

    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti)
    {
        Vec3f   d1 = ti.getPosition(1) - ti.getPosition(0);
        Vec3f   d2 = ti.getPosition(2) - ti.getPosition(0);
        d1.crossThis(d2);

        d1.normalize();
        faceNormals.push_back(d1);

        pntMap.insert(std::pair< Pnt3f, UInt32 > 
                        (ti.getPosition(0), faceNormals.size() - 1));
        pntMap.insert(std::pair< Pnt3f, UInt32 > 
                        (ti.getPosition(1), faceNormals.size() - 1));
        pntMap.insert(std::pair< Pnt3f, UInt32 > 
                        (ti.getPosition(2), faceNormals.size() - 1));
    }

    // now walk through the geometry again and calc the normals
    beginEditCP(norms);
    beginEditCP(ip);

    norms->resize(nind);

    Real32  cosCrease = osgcos(creaseAngle);

    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti)
    {
        Int32   tind = ti.getIndex();
        Vec3f   mynorm = faceNormals[tind];

        std::multimap<Pnt3f, UInt32, vecless<Pnt3f> >::iterator st, en;

        for(UInt16 i = 0; i < 3; ++i)
        {
            // calculate the normal: average all different normals
            // that use a point. Simple addition or weighted addition
            // doesn't work, as it depends on the triangulation
            // of the object. :(
            std::set<Vec3f, vecless<Vec3f> > normset;

            st = pntMap.lower_bound(ti.getPosition(i));
            en = pntMap.upper_bound(ti.getPosition(i));

            for(; st != en; st++)
            {
                if(mynorm.dot(faceNormals[(*st).second]) > cosCrease)
                {
                    normset.insert(faceNormals[(*st).second]);
                }
            }

            Vec3f                                               norm(0, 0, 0);
            typedef std::set<Vec3f, vecless<Vec3f> >::iterator  NormSetIt;

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
    std::vector < Vec3f > faceNormals;
    std::vector < std::vector < UInt32 > > pntFaceDic;

    TriangleIterator ti;
    UInt32 i, pN = positions->size();

    pntFaceDic.resize(pN);
    for(ti = geo->beginTriangles(), i = 0; ti != geo->endTriangles(); ++ti, ++i)
    {
        Int32 v0 = ti.getPositionIndex(0);
        Int32 v1 = ti.getPositionIndex(1);
        Int32 v2 = ti.getPositionIndex(2);

        if(v0 != v1 && v0 != v2)
        {
            Vec3f d1 = ti.getPosition(1) - ti.getPosition(0);
            Vec3f d2 = ti.getPosition(2) - ti.getPosition(0);
            d1.crossThis(d2);

            if(d1.squareLength() >= 0)
            {
                d1.normalize();
                faceNormals.push_back(d1);

                pntFaceDic[ti.getPositionIndex(0)].push_back(i);
                pntFaceDic[ti.getPositionIndex(1)].push_back(i);
                pntFaceDic[ti.getPositionIndex(2)].push_back(i);
            }
            else
            {
                faceNormals.push_back(Vec3f(0, 0, 0));
            }
        }
        else
        {
            faceNormals.push_back(Vec3f(0, 0, 0));
        }
    }

    // now walk through the geometry again and calc the normals
    beginEditCP(norms);
    beginEditCP(ip);

    norms->clear();

    Real32 cosCrease = osgcos(creaseAngle);
    Vec3f norm;
    std::vector < UInt32 > normset;
    std::vector < std::map < std::vector < UInt32 > , UInt32 > > normDic;
    std::map < std::vector < UInt32 > , UInt32 >::iterator ndI;

    UInt32 normalIndex = 0;

    normDic.resize(pN);

    for(ti = geo->beginTriangles(); ti != geo->endTriangles(); ++ti)
    {
        Int32 tind = ti.getIndex();
        Vec3f faceNorm(faceNormals[tind]);

        if(faceNorm.squareLength() != 0.0)
        {
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
                for(f = 0; f < fN; f++)
                {
                    if(((pf = pntFaceDic[p][f]) == tind) ||
                       (faceNorm.dot(faceNormals[pf]) > cosCrease))
                        normset.push_back(pf);
                }

                if((nN = normset.size()))
                {
                    // find normal
                    //std::sort ( normset.begin(), normset.end() );
                    ndI = normDic[p].find(normset);
                    if(ndI == normDic[p].end())
                    {
                        norm = faceNormals[normset[0]];
                        for(n = 1; n < nN; ++n)
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
                    FWARNING(("Empty normset for %d faces pos %d: %f/%f/%f\n",
                               fN, i, ti.getPosition(i).x(),
                               ti.getPosition(i).y(), ti.getPosition(i).z()
                            ));
                }

                ip->setValue(normalIndex, ti.getIndexIndex(i) + ni);
            }
        }
        else
        {
            // keep normal for degenerated triangle

            normalIndex = norms->size();
            norms->push_back(norm);
            
            ip->setValue ( normalIndex, ti.getIndexIndex(0) + ni );
            ip->setValue ( normalIndex, ti.getIndexIndex(1) + ni );
            ip->setValue ( normalIndex, ti.getIndexIndex(2) + ni );
        }
    }

    endEditCP(ip);
    endEditCP(norms);
#endif
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcFaceNormals calculates the normals for the geometry's faces, see 
    \ref PageSystemGeoFunctionsCalcNormals for a description. 
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::calcFaceNormals(GeometryPtr geo)
{
    if(geo->getPositions() == NullFC ||
       geo->getPositions()->size() == 0)
    {
        FINFO(("Geo without positions in calcFaceNormals()\n"));
        return;
    }

    GeoIndicesPtr newIndex = GeoIndicesUI32::create();
    GeoNormalsPtr newNormals = GeoNormals3f::create();
    Vec3f normal;

    FaceIterator faceIter = geo->beginFaces();
    GeoIndicesPtr oldIndex = geo->getIndices();

    if(oldIndex != NullFC)
    {
        //Indexed
        if(geo->getIndexMapping().size() > 0)
        {
            //MULTI INDEXED
            beginEditCP(newIndex);

            MFUInt16    &oldIndexMap = geo->getIndexMapping();
            UInt32 oldIMSize = oldIndexMap.size();
            for(UInt32 i = 0; i < oldIndex->getSize() / oldIMSize; ++i)
            {
                for(UInt32 k = 0; k < oldIMSize; ++k)
                {
                    newIndex->push_back(oldIndex->getValue(i * oldIMSize + k));
                }

                newIndex->push_back(0);                                 //placeholder for normal index
            }

            beginEditCP(newNormals);
            for(UInt32 faceCnt = 0; faceIter != geo->endFaces();
                            ++faceIter, ++faceCnt)
            {
                if(faceIter.getLength() == 3)
                {
                    //Face is a Triangle
                    normal =
                        (
                            faceIter.getPosition(1) -
                            faceIter.getPosition(0)
                        ).cross(faceIter.getPosition(2) - faceIter.getPosition(0));
                    normal.normalize();
                }
                else
                {
                    //Face must be a Quad then
                    normal =
                        (
                            faceIter.getPosition(1) -
                            faceIter.getPosition(0)
                        ).cross(faceIter.getPosition(2) - faceIter.getPosition(0));
                    if(normal.length() == 0)
                    {
                        //Quad is degenerate, choose different points for normal
                        normal =
                            (
                                faceIter.getPosition(1) -
                                faceIter.getPosition(2)
                            ).cross(faceIter.getPosition(3) -
                                                                faceIter.getPosition(2));
                    }

                    normal.normalize();
                }

                newNormals->push_back(normal);                          //put the normal into the storage
                UInt32 base;
                switch(faceIter.getType())
                {
                case GL_TRIANGLE_STRIP:
                    base = faceIter.getIndexIndex(2);                   //get last point's position in index field
                    newIndex->setValue(faceCnt, base + (base / oldIMSize) + oldIMSize);
                    break;
                case GL_TRIANGLE_FAN:
                    base = faceIter.getIndexIndex(2);                   //get last point's position in index field
                    newIndex->setValue(faceCnt, base + (base / oldIMSize) + oldIMSize);
                    break;
                case GL_QUAD_STRIP:
                    base = faceIter.getIndexIndex(3);                   //get last point's position in index field
                    newIndex->setValue(faceCnt, base + (base / oldIMSize) + oldIMSize);
                    break;
                default:
                    for(UInt32 i = 0; i < faceIter.getLength(); ++i)
                    {
                        base = faceIter.getIndexIndex(i);
                        newIndex->setValue(faceCnt,
                                                                   base + (base / oldIMSize) + oldIMSize);
                    }
                    break;
                }
            }

            endEditCP(newNormals);
            endEditCP(newIndex);

            beginEditCP(geo);

            Int16 ni;
            ni = geo->calcMappingIndex(Geometry::MapNormal);
            if(ni != -1)
            {
                oldIndexMap[ni] = oldIndexMap[ni] &~Geometry::MapNormal;
            }

            oldIndexMap.push_back(Geometry::MapNormal);
            geo->setNormals(newNormals);
            geo->setIndices(newIndex);
            endEditCP(geo);
            return;
        }
    }

    //SINGLE INDEXED or NON INDEXED
    //UInt32 pointCnt = 0;
    newNormals->resize(geo->getPositions()->getSize());
    for(; faceIter != geo->endFaces(); ++faceIter)
    {
        if(faceIter.getLength() == 3)
        {
            //Face is a Triangle
            normal = (faceIter.getPosition(1) - faceIter.getPosition(0)).cross(faceIter.getPosition(2) - faceIter.getPosition(0));
            normal.normalize();
        }
        else
        {
            //Face must be a Quad then
            normal = (faceIter.getPosition(1) - faceIter.getPosition(0)).cross(faceIter.getPosition(2) - faceIter.getPosition(0));
            if(normal.length() == 0)
            {
                //Quad is degenerate, choose different points for normal
                normal =
                    (
                        faceIter.getPosition(1) -
                        faceIter.getPosition(2)
                    ).cross(faceIter.getPosition(3) - faceIter.getPosition(2));
            }

            normal.normalize();
        }

        switch(faceIter.getType())
        {
        case GL_TRIANGLE_STRIP:
            newNormals->setValue(normal, faceIter.getPositionIndex(2));
            break;
        case GL_TRIANGLE_FAN:
            newNormals->setValue(normal, faceIter.getPositionIndex(2));
            break;
        case GL_QUAD_STRIP:
            newNormals->setValue(normal, faceIter.getPositionIndex(3));
            break;
        default:
            for(UInt32 i = 0; i < faceIter.getLength(); ++i)
            {
                newNormals->setValue(normal, faceIter.getPositionIndex(i));
            }
            break;
        }

        beginEditCP(geo);
        geo->setNormals(newNormals);
        endEditCP(geo);
    }
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    setIndexFromVRMLData creates an osg::Geometry's interleaved index data
    from VRML-style separate indices, see \ref PageSystemGeoFunctionsMakeGeo
    for a description.

    \a coordIndex, \a normalIndex, \a colorIndex and \a texCoordIndex are
    VRML97-style indices. \a ccw sets whether poylgons are defined
    counter-clockwise or clockwise, \a normalPerVertex and \a colorPerVertex
    specify bindings, and \a faceSet defines whether a VRML IndexedFaceSet or
    an IndexedLineSet is being generated. See the VRML97 specification at
    http://www.web3d.org for details.

    Note: the \a convex and \a createNormals parameters are ignored right now!
*/

OSG_SYSTEMLIB_DLLMAPPING 
Int32 OSG::setIndexFromVRMLData(GeometryPtr geoPtr,
                                std::vector<Int32> &coordIndex,
                                std::vector<Int32> &normalIndex,
                                std::vector<Int32> &colorIndex,
                                std::vector<Int32> &texCoordIndex,
                                bool convex, 
                                bool ccw,
                                bool normalPerVertex, 
                                bool colorPerVertex,
                                bool createNormal, 
                                bool faceSet)
{
  Int32 primitiveType = faceSet ? GL_POLYGON : GL_LINE_STRIP;

  return setIndexFromIndexedX3DData ( geoPtr,
                                      coordIndex,
                                      normalIndex,
                                      colorIndex,
                                      texCoordIndex,
                                      primitiveType,
                                      convex,
                                      ccw,
                                      normalPerVertex,
                                      colorPerVertex,
                                      createNormal );
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    setIndexFromIndexedX3DData creates an osg::Geometry's interleaved index data
    from X3D-style separate indices, see \ref PageSystemGeoFunctionsMakeGeo
    for a description.
    
    The \a primitiveType defines the GL-Primtive (e.g. GL_LINE, GL_TRIANGLE_STRIP,
    GL_POLYGON) which should be used.

    \a coordIndex, \a normalIndex, \a colorIndex and \a texCoordIndex are
    X3D-style indices. \a ccw sets whether poylgons are defined
    counter-clockwise or clockwise, \a normalPerVertex and \a colorPerVertex
    specify bindings. See the X3D specification at
    http://www.web3d.org for details.

    Note: the \a convex and \a createNormals parameters are ignored right now!
*/

OSG_SYSTEMLIB_DLLMAPPING 
Int32 OSG::setIndexFromIndexedX3DData ( GeometryPtr geoPtr,
                                        std::vector<Int32> &coordIndex,
                                        std::vector<Int32> &normalIndex,
                                        std::vector<Int32> &colorIndex,
                                        std::vector<Int32> &texCoordIndex,
                                        Int32 primitiveType, 
                                        bool OSG_CHECK_ARG(convex), 
                                        bool ccw,
                                        bool normalPerVertex, 
                                        bool colorPerVertex,
                                        bool OSG_CHECK_ARG(createNormal) )
{
    /** define the bag type */
    typedef std::vector<Int32>  *IndexBagP;

    /** defines the Index Types */
    enum IndexType
    {
        UNKNOWN_IT          = 0,
        EMPTY_IT,
        VERTEX_COORD_IT,
        VERTEX_IT,
        VERTEX_DUP_IT,
        VERTEX_CREATE_IT,
        PRIMITIVE_IT,
        PRIMITIVE_INDEX_IT,
        PRIMITIVE_CREATE_IT
    };

    /** holds the Index types as str, mainly for log/debug outputs */
    static const char *indexTypeStr[] =
    {
        "UNKNOWN_IT",
        "EMPTY_IT",
        "VERTEX_COORD_IT",
        "VERTEX_IT",
        "VERTEX_DUP_IT",
        "VERTEX_CREATE_IT",
        "PRIMTIVE_IT",
        "PRIMITIVE_INDEX_IT",
        "PRIMITIVE_CREATE_IT"
    };
    OSG::GeoPositionsPtr posPtr;
    OSG::GeoNormalsPtr normalPtr;
    OSG::GeoColorsPtr colorPtr;
    OSG::GeoTexCoordsPtr texCoordsPtr;
    OSG::GeoPLengthsPtr lensPtr;
    OSG::GeoPTypesPtr geoTypePtr;
    OSG::GeoIndicesPtr indexPtr;

    //bool faceSet = (primitiveType == GL_POLYGON);
    Int32 index, i, pi, typei, mapi, primitiveN = 0, vN = 0;
    Int32 pType = 0, localPType;
    Int32 maxPType; //  = (faceSet ? 5 : 3);
    Int32 minPType; //  = (faceSet ? 3 : 2);
    Int32 beginIndex, endIndex, step, len, sysPType = 0;
    Int32 piN = 0, ciN = 0, niN = 0, tiN = 0;
    Int32 pN = 0, nN = 0, cN = 0, tN = 0, tN1 = 0, tN2 = 0, tN3 = 0,
          tN4 = 0, tN5 = 0, tN6 = 0, tN7 = 0;
    IndexType indexType[4];
    IndexType &coordIT = indexType[0];
    IndexType &normalIT = indexType[1];
    IndexType &colorIT = indexType[2];
    IndexType &textureIT = indexType[3];
    Int32 primitiveTypeCount[6];
    UInt32 triCount = 0;
    Int16 indexMap[4], indexMapID[4];
    UInt32 uiNumTextures = 0;

    IndexBagP indexBag[4] =
    {
        &coordIndex,
        &normalIndex,
        &colorIndex,
        &texCoordIndex
    };

    //----------------------------------------------------------------------
    // init
    coordIT = VERTEX_IT;
    indexMap[0] = Geometry::MapPosition;

    //----------------------------------------------------------------------
    // set maxPType and minPTypr from primitiveType
    switch (primitiveType) {
    case GL_POINTS:
      minPType = 1;
      maxPType = 1;
      break;
    case GL_LINES:
      minPType = 2;
      maxPType = 3;
      break;
    case GL_LINE_STRIP:
      minPType = 2;
      maxPType = 3;
      break;
    case GL_LINE_LOOP:
      minPType = 2;
      maxPType = 3;
      break;
    case GL_TRIANGLES:
      minPType = 3;
      maxPType = 3;
      break;
    case GL_TRIANGLE_STRIP:
      minPType = 3;
      maxPType = 3;
      break;
    case GL_TRIANGLE_FAN:
      minPType = 3;
      maxPType = 3;
      break;
    case GL_QUADS:
      minPType = 3;
      maxPType = 4;
      break;
    case GL_QUAD_STRIP:    
      minPType = 3;
      maxPType = 4;
      break;
    case GL_POLYGON:
      minPType = 3;
      maxPType = 5;
      break;
    default:
      FFATAL (( "Can not fill index; Invalid primitiveType: %d\n",
                primitiveType ));
      break;
    }
      

    //----------------------------------------------------------------------
    // get the property pointer and element count
    posPtr = geoPtr->getPositions();
    pN = ((posPtr == OSG::NullFC) ? 0 : posPtr->getSize());

    normalPtr = geoPtr->getNormals();
    nN = ((normalPtr == OSG::NullFC) ? 0 : normalPtr->getSize());

    colorPtr = geoPtr->getColors();
    cN = ((colorPtr == OSG::NullFC) ? 0 : colorPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords();
    tN = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords1();
    tN1 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords2();
    tN2 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords3();
    tN3 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords4();
    tN4 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords5();
    tN5 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords6();
    tN6 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    texCoordsPtr = geoPtr->getTexCoords7();
    tN7 = ((texCoordsPtr == OSG::NullFC) ? 0 : texCoordsPtr->getSize());

    FDEBUG(("vertex attrib count P/N/C/T: %d/%d/%d/%d\n", pN, nN, cN, tN));

    //----------------------------------------------------------------------
    // check the vertex index and count the primitives
    primitiveN = index = 0;
    for(pType = 0; pType < 6; pType++)
        primitiveTypeCount[pType] = 0;

    if(!pN)
    {
        FINFO(("No points in OSG::setIndexFromVRMLData()\n"));
        return 0;
    }
    else
    {
        piN = coordIndex.size();
        if(piN)
        {
            for(i = 0; i <= piN; i++)
            {
                index = (i == piN) ? -1 : coordIndex[i];
                if((index < 0) && vN)
                {
                    primitiveTypeCount[(vN > maxPType) ? maxPType : vN]++;
                    primitiveN++;
                    vN = 0;
                }
                else
                {
                    if(index >= pN && i != piN)
                    {
                        FWARNING(("Point index (%d/%d) out of range", index, pN));
                        coordIndex[i] = 0;
                    }

                    vN++;
                }
            }
        }
        else
        {
            FWARNING(("No coordIndex in OSG::setIndexFromVRMLData()\n"));
            return 0;
        }
    }

    //----------------------------------------------------------------------
    // check the normal index
    normalIT = UNKNOWN_IT;
    niN = normalIndex.size();
    if(nN)
    {               // have normal elements
        if(normalPerVertex)
        {
            // normal per vertex
            if(niN >= piN)
            {
                // valid normal index number
                for(i = 0; i < piN; i++)
                {   // check if normal index equals the coord index
                    if(normalIndex[i] != coordIndex[i])
                    {
                        normalIT = VERTEX_IT;
                        break;
                    }
                }

                if(normalIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded normal index
                    normalIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough normal index
                normalIT = VERTEX_COORD_IT;
                if(niN)
                {
                    FWARNING(("Not enough normal index (%d,%d)\n", normalIndex.
                                                     size(), piN));
                    normalIndex.clear();
                }
            }
        }
        else
        {
            // normal per primitive
            if(niN >= primitiveN)
            {
                // use one normal index per primitive
                normalIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(nN >= primitiveN)
                {
                    // use one normal per primitive
                    normalIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough normal index (%d,%d)\n", nN, primitiveN));
                }
            }
        }
    }
    else
    {
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
    if(cN)
    {               // have color elements
        if(colorPerVertex)
        {
            // color per vertex
            if(ciN >= piN)
            {
                // valid color index number
                for(i = 0; i < piN; i++)
                {   // check if color index equals the coord index
                    if(colorIndex[i] != coordIndex[i])
                    {
                        colorIT = VERTEX_IT;
                        break;
                    }
                }

                if(colorIT == UNKNOWN_IT)
                {
                    // if equal than delete unneeded color index
                    colorIT = VERTEX_DUP_IT;
                }
            }
            else
            {
                // no or not enough color index
                colorIT = VERTEX_COORD_IT;
                if(ciN)
                {
                    FWARNING(("Not enough color index (%d,%d)\n", colorIndex.
                                                     size(), piN));
                    colorIndex.clear();
                }
            }
        }
        else
        {
            // color per primitive
            if(ciN >= primitiveN)
            {
                // use one color index per primitive
                colorIT = PRIMITIVE_INDEX_IT;
            }
            else
            {
                if(cN >= primitiveN)
                {
                    // use one color per primitive
                    colorIT = PRIMITIVE_IT;
                }
                else
                {
                    FINFO(("not enough color index (%d,%d)\n", cN, primitiveN));
                }
            }
        }
    }
    else
    {
        colorIT = EMPTY_IT;
    }

    //----------------------------------------------------------------------
    // check the texture index
    textureIT = UNKNOWN_IT;
    tiN = texCoordIndex.size();
    if(tN)
    {               // have texture elemnts
        if(tiN >= piN)
        {
            // valid texture index number
            for(i = 0; i < piN; i++)
            {       // check if texture index equals the coord index
                if(texCoordIndex[i] != coordIndex[i])
                {
                    textureIT = VERTEX_IT;
                    break;
                }
            }

            if(textureIT == UNKNOWN_IT)
            {
                // if equal than delete unneeded texture index
                textureIT = VERTEX_DUP_IT;
            }
        }
        else
        {
            // no or not enough texture index
            textureIT = VERTEX_COORD_IT;
            if(ciN)
            {
                FWARNING(("Not enough texCoord index (%d,%d)\n", texCoordIndex.
                                             size(), piN));
                texCoordIndex.clear();
            }
        }
    }
    else
    {
        textureIT = EMPTY_IT;
    }

    FNOTICE (( "primitiveN:  %d, %d, 0/%d 1/%d 2/%d 3/%d 4/%d 5/%d\n",
            primitiveType,
            primitiveN, primitiveTypeCount[0],
            primitiveTypeCount[1], primitiveTypeCount[2],
            primitiveTypeCount[3], primitiveTypeCount[4],
            primitiveTypeCount[5]));
    
    FNOTICE (( "IndexType: coord: %s, color: %s, normal: %s, texture: %s \n",
            indexTypeStr[coordIT], indexTypeStr[colorIT], 
            indexTypeStr[normalIT], indexTypeStr[textureIT]));

    //----------------------------------------------------------------------
    // check/create the indexPtr/lengthsPtr/geoTypePtr
    indexPtr = geoPtr->getIndices();
    if(indexPtr == OSG::NullFC)
    {
        indexPtr = OSG::GeoIndicesUI32::create();
    }
    else
    {
        OSG::beginEditCP(indexPtr);
        indexPtr->clear();
        OSG::endEditCP(indexPtr);
    }

    lensPtr = geoPtr->getLengths();
    if(lensPtr == OSG::NullFC)
    {
        lensPtr = OSG::GeoPLengthsUI32::create();
    }
    else
    {
        OSG::beginEditCP(lensPtr);
        lensPtr->clear();
        OSG::endEditCP(lensPtr);
    }

    geoTypePtr = geoPtr->getTypes();
    if(geoTypePtr == OSG::NullFC)
    {
        geoTypePtr = OSG::GeoPTypesUI8::create();
    }
    else
    {
        OSG::beginEditCP(geoTypePtr);
        geoTypePtr->clear();
        OSG::endEditCP(geoTypePtr);
    }

    //----------------------------------------------------------------------
    // create the index mapping
    indexMapID[0] = Geometry::MapPosition;
    indexMapID[1] = Geometry::MapNormal;
    indexMapID[2] = Geometry::MapColor;
    indexMapID[3] = Geometry::MapTexCoords;

    for(mapi = i = 1; i <= 3; i++)
    {
        indexMap[i] = 0;
        switch(indexType[i])
        {
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
        default:    //X_CREATE_IT
            break;
        }
    }

    //----------------------------------------------------------------------
    // set lens/geoType/index/mapping the index mapping
    OSG::beginEditCP(geoPtr);
    {
        geoPtr->setLengths(lensPtr);
        geoPtr->setTypes(geoTypePtr);
        geoPtr->setIndices(indexPtr);
        geoPtr->getIndexMapping().clear();

        // TODO: check for multiindex mapping ?
        // if (indexMap[1])
        for(i = 0; ((i <= 3) && indexMap[i]); i++)
        {
            if(i == 0)
            {
                if(indexMap[i] & Geometry::MapTexCoords)
                {
                    ++uiNumTextures;
                    
                    if(tN1 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords1;
                    }
                    
                    if(tN2 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords2;
                    }
                    
                    if(tN3 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords3;
                    }
                    
                    if(tN4 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords4;
                    }
                    
                    if(tN5 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords5;
                    }
                    
                    if(tN6 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords6;
                    }
                    
                    if(tN7 != 0)
                    {
                        indexMap[i] |= Geometry::MapTexCoords7;
                    }
                }

                geoPtr->getIndexMapping().push_back(indexMap[i]);
            }
            else
            {
                geoPtr->getIndexMapping().push_back(indexMap[i]);
                
                if(indexMap[i] & Geometry::MapTexCoords)
                {
                    ++uiNumTextures;
                    
                    if(tN1 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords1);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN2 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords2);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN3 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords3);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN4 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords4);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN5 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords5);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN6 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords6);
                        
                        ++uiNumTextures;
                    }
                    
                    if(tN7 != 0)
                    {
                        geoPtr->getIndexMapping().push_back(
                            Geometry::MapTexCoords7);
                        
                        ++uiNumTextures;
                    }
                }
            }
        }
    }
    OSG::endEditCP(geoPtr);

    //----------------------------------------------------------------------
    // create index face/line data
    OSG::beginEditCP(indexPtr);
    OSG::beginEditCP(lensPtr);
    OSG::beginEditCP(geoTypePtr);

    for(pType = minPType; pType <= maxPType; pType++)
    {
        // check for the pType count
        if(primitiveTypeCount[pType])
        {
            // calc len/sysPType
          
            if(pType < maxPType)
            {
                len = primitiveTypeCount[pType] * pType;
                switch (pType) 
                {
                  case 1:
                    sysPType = GL_POINTS;
                    break;
                  case 2:
                    sysPType = GL_LINES;
                    break;
                  case 3:
                    sysPType = GL_TRIANGLES;
                    break;
                  case 4:
                    sysPType = GL_QUADS;
                    break;
                }
            }
            else
            { 
                sysPType = 0;
            }

            // set len/sysPType
            if(sysPType)
            {
              lensPtr->push_back(len);
              geoTypePtr->push_back(sysPType);
            }

            primitiveN = 0;
            beginIndex = endIndex = -1;
            for(i = 0; i <= piN; i++)
            {
                if(((i == piN) && (coordIndex[i - 1] >= 0)) ||
                                   ((i < piN) && (coordIndex[i] < 0)))
                {
                    len = i - beginIndex;
                    if(ccw)
                    {
                        endIndex = i;
                        step = 1;
                    }
                    else
                    {
                        endIndex = beginIndex - 1;
                        beginIndex = i - 1;
                        step = -1;
                    }

                    localPType = (len > maxPType) ? maxPType : len;
                    if((beginIndex >= 0) && (localPType == pType))
                    {
                        if(len >= maxPType)
                        {
                            sysPType = primitiveType;
                            lensPtr->push_back(len);
                            geoTypePtr->push_back(sysPType);
                        }

                        // add index data
                        for(pi = beginIndex; pi != endIndex; pi += step)
                        {
                            indexPtr->push_back(coordIndex[pi]);
                            for(mapi = 1; (mapi <= 3) && (indexMap[mapi]);
                                                            mapi++)
                            {
                                for(typei = 1; typei <= 3; typei++)
                                {
                                    if(indexMap[mapi] & indexMapID[typei])
                                    {
                                        switch(indexType[typei])
                                        {
                                        case UNKNOWN_IT:
                                        case EMPTY_IT:
                                        case VERTEX_COORD_IT:
                                        case VERTEX_DUP_IT:
                                            FFATAL(("Fatal index mapping error \n"));
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
                                        default:                        //X_CREATE_IT
                                            break;
                                        }

                                        indexPtr->push_back(index);
                                        
                                        if(indexMap[mapi] & Geometry::MapTexCoords)
                                        {
                                            for(UInt32 ti = 0; ti < uiNumTextures - 1; ++ti)
                                            {
                                                indexPtr->push_back(index);
                                            }
                                        }
                                    }
                                    
                                }
                            }
                        }

                        triCount += len - 2;
                    }

                    primitiveN++;
                    beginIndex = endIndex = -1;
                }
                else if(beginIndex < 0)
                    beginIndex = i;
            }
        }
    }

    OSG::endEditCP(geoTypePtr);
    OSG::endEditCP(lensPtr);
    OSG::endEditCP(indexPtr);

    return triCount;
}


//! \ingroup GrpSystemDrawablesGeometryFunctions
//! Multi/Single index dictionary
struct  IndexDic
{
    typedef std::vector<Int32>  Int32Vec;
  public:

    Int32           entry(Int32Vec &indexVec);

    const Int32Vec  &entry(Int32 index);

    UInt32          entryCount(void) const;
  private:

    typedef std::map<Int32Vec, Int32> IndexMap;
    IndexMap _indexMap;

    std::vector < const Int32Vec * > _indexVec;
};

inline Int32 IndexDic::entry(Int32Vec &indexVec)
{
    IndexMap::iterator iI = _indexMap.find(indexVec);
    if(iI == _indexMap.end())
    {
        std::pair < IndexMap::iterator, bool > mapRes =
            _indexMap.insert(IndexMap::value_type(indexVec, _indexVec.size()));
        if(mapRes.second)
        {
            iI = mapRes.first;
            _indexVec.push_back(&(iI->first));
        }
        else
        {
            FFATAL(("IndexDic::entry() map insert error\n"));
        }
    }

    return iI->second;
}

inline const IndexDic::Int32Vec & IndexDic::entry(Int32 index)
{
    return *(_indexVec[index]);
}

inline UInt32 IndexDic::entryCount(void) const
{
    return _indexVec.size();
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcVertexTexCoords calculates the texCoords for the geometry's vertices, see
    \ref PageSystemGeoFunctionsCalcTexCoords for a description.
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::calcVertexTexCoords(GeometryPtr geo, Int32 texIndex)
{
    struct Key {
        Real32 value;
        Int32 pos;
    } key[3], rem;

    Int32 S = -1, T = -1, n = 3, i, j; 
    Real32 sDenom, tDenom, sMin, tMin;
    
    MFUInt16 &im = geo->getIndexMapping();
    UInt16 mapTex = 0;

    GeoIndicesPtr ip = geo->getIndices();
    GeoPositionsPtr posP = geo->getPositions();
    GeoTexCoordsPtr texP;

    if (posP == NullFC || !posP->size() || ip == NullFC || !ip->size())
    {
        FFATAL(("Geo without indices/ positions in calcVertexTexCoords()\n"));
        return;
    }
    
    for (MFNodePtr::iterator pnI = geo->getMFParents()->begin();
         pnI != geo->getMFParents()->end(); ++pnI)
    {
        NodePtr node = *pnI;

        if (node != NullFC)
        {
            DynamicVolume &dVol = node->getVolume(true);
            Pnt3f min, max;
            dVol.getBounds(min, max);
    
            Vec3f dia(max - min);
            for (i=0; i<3; i++)
            {
                key[i].value = dia[i];
                key[i].pos = i;
            }
    
            for (i=1; i<n; i++)
            {
                for (j=n-1; j>=i; j--)
                {
                    if (key[j-1].value > key[j].value)
                    {
                        rem = key[j];
                        key[j] = key[j-1];
                        key[j-1] = rem;
                    }
                }
            }
    
            S = key[2].pos;
            T = key[1].pos;
            sDenom = dia[S];
            tDenom = dia[T];
            sMin = min[S];
            tMin = min[T];
    
            break;
        }
    }

    if (S < 0 || T < 0)
    {
        FFATAL(("Geo without parents in calcVertexTexCoords()\n"));
        return;
    }

    switch (texIndex)
    {
        case 0:
            if (geo->getTexCoords() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords();
            }
            mapTex = Geometry::MapTexCoords;
            break;
        case 1:
            if (geo->getTexCoords1() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords1(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords1();
            }
            mapTex = Geometry::MapTexCoords1;
            break;
        case 2:
            if (geo->getTexCoords2() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords2(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords2();
            }
            mapTex = Geometry::MapTexCoords2;
            break;
        case 3:
            if (geo->getTexCoords3() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords3(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords3();
            }
            mapTex = Geometry::MapTexCoords3;
            break;
        case 4:
            if (geo->getTexCoords4() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords4(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords4();
            }
            mapTex = Geometry::MapTexCoords4;
            break;
        case 5:
            if (geo->getTexCoords5() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords5(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords5();
            }
            mapTex = Geometry::MapTexCoords5;
            break;
        case 6:
            if (geo->getTexCoords6() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords6(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords6();
            }
            mapTex = Geometry::MapTexCoords6;
            break;
        case 7:
            if (geo->getTexCoords7() == osg::NullFC)
            {
                texP = GeoTexCoords2f::create();
                beginEditCP(geo);
                    geo->setTexCoords7(texP);
                endEditCP(geo);
            }
            else
            {
                texP = geo->getTexCoords7();
            }
            mapTex = Geometry::MapTexCoords7;
            break;
        default:
            FWARNING(("Parameters are [0|1|2|3|4|5|6|7] in calcVertexTexCoords()\n"));
            return;
    }

    Int16 niTex = geo->calcMappingIndex(mapTex),
          niPos = geo->calcMappingIndex(Geometry::MapPosition);
    Int32 len = posP->size(), indexMapSize = im.size(), imsize = 0, ibsize;
    UInt32 nind = ip->size() / (indexMapSize ? indexMapSize : 1);
        
    Pnt3f point;
    Vec2f texCoord;

    if (indexMapSize > 1)
    {
        MFUInt16::iterator imIt = im.begin();
        std::vector<UInt32> indexBuffer;

        if (niTex >= 0)
            im[niTex] = im[niTex] &~ mapTex;

        im.push_back(mapTex);

        for (i=0; i<nind; i++)
        {
            for (j=0; j<indexMapSize; j++)
            {
                if (j != niTex || im[niTex] >= 1)
                    indexBuffer.push_back(ip->getValue(i*indexMapSize + j));
            }
            indexBuffer.push_back(ip->getValue(i*indexMapSize + niPos));
        }

        if (niTex >= 0 && im[niTex] < 1)
            im.erase(imIt + niTex);
            
        imsize = im.size();
        ibsize = indexBuffer.size();

        beginEditCP(ip);
        {
            ip->clear();

            if (imsize != indexMapSize)
                ip->resize(ibsize);

            for (i=0; i<ibsize; i++)
                ip->setValue(indexBuffer[i], i);
        }
        endEditCP(ip);

        niTex = imsize ? imsize - 1 : 0;
    }

    beginEditCP(texP);
    {
        niPos = geo->calcMappingIndex(Geometry::MapPosition);
        niPos = (niPos >= 0) ? niPos : 0;
        
        if (texP->size() != len)
            texP->resize(len);

        beginEditCP(ip);
        {
            for (i=0; i<len; i++)
            {
                posP->getValue(point, i);
    
                texCoord[0] = (point[S] - sMin) / sDenom;
                texCoord[1] = (point[T] - tMin) / tDenom;

                texP->setValue(texCoord, i);
            }
        }
        endEditCP(ip);
    }
    endEditCP(texP);
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcVertexTangents calculates the tangents/ binormals for the geometry's vertices, see
    \ref PageSystemGeoFunctionsCalcTangents for a description. 
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::calcVertexTangents (GeometryPtr geo,
                                                       Int32 srcTexIndex,
                                                       Int32 dstAttribTan,
                                                       Int32 dstAttribBin)
{
    GeoTexCoords4fPtr tangentP, binormalP;
    std::vector<Vec3f> tangent, binormal, normal;
    UInt16 mapTan = 0, mapBin = 0, mapTex = 0;
    
    // fallback in case of user error: use none mode
    if (dstAttribTan == dstAttribBin)
        dstAttribBin = -1;
    
    switch (srcTexIndex) 
    {
        case 0:
            mapTex = Geometry::MapTexCoords;
            break;
        case 1:
            mapTex = Geometry::MapTexCoords1;
            break;
        case 2:
            mapTex = Geometry::MapTexCoords2;
            break;
        case 3:
            mapTex = Geometry::MapTexCoords3;
            break;
        case 4:
            mapTex = Geometry::MapTexCoords4;
            break;
        case 5:
            mapTex = Geometry::MapTexCoords5;
            break;
        case 6:
            mapTex = Geometry::MapTexCoords6;
            break;
        case 7:
            mapTex = Geometry::MapTexCoords7;
            break;
        default:
            FWARNING(("Currently only 8 TexCoords allowed in GeoPtr\n"));  
            srcTexIndex = 0;
            mapTex = Geometry::MapTexCoords;
            break;
    }
  
    switch (dstAttribTan) 
    {    
        case Geometry::TexCoordsFieldId:
            beginEditCP(geo);
            {
                // because we need more than 2 coords, as is usual,
                // it is safer & easier to set a new texCoordsPtr 
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords;
            break;
        case Geometry::TexCoords1FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords1(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords1;
            break;
        case Geometry::TexCoords2FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords2(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords2;
            break;
        case Geometry::TexCoords3FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords3(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords3;
            break;
        case Geometry::TexCoords4FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords4(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords4;
            break;
        case Geometry::TexCoords5FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords5(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords5;
            break;
        case Geometry::TexCoords6FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords6(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords6;
            break;
        case Geometry::TexCoords7FieldId:
            beginEditCP(geo);
            {
                tangentP = GeoTexCoords4f::create();
                geo->setTexCoords7(tangentP);
            }
            endEditCP(geo);
            mapTan = Geometry::MapTexCoords7;
            break;

        case Geometry::PositionsFieldId:
        case Geometry::NormalsFieldId:
        case Geometry::ColorsFieldId:
        case Geometry::SecondaryColorsFieldId:
            FWARNING(("Case currently not treated, using NONE\n"));     
            dstAttribTan = -1;
              
        case -1:
            tangentP = GeoTexCoords4f::create();    // to be deleted
            break;
    }
    
    switch (dstAttribBin) 
    {
        case Geometry::TexCoordsFieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords;
            break;
        case Geometry::TexCoords1FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords1(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords1;
            break;
        case Geometry::TexCoords2FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords2(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords2;
            break;
        case Geometry::TexCoords3FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords3(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords3;
            break;
        case Geometry::TexCoords4FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords4(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords4;
            break;
        case Geometry::TexCoords5FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords5(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords5;
            break;
        case Geometry::TexCoords6FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords6(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords6;
            break;
        case Geometry::TexCoords7FieldId:
            beginEditCP(geo);
            {
                binormalP = GeoTexCoords4f::create();
                geo->setTexCoords7(binormalP);
            }
            endEditCP(geo);
            mapBin = Geometry::MapTexCoords7;
            break;

        case Geometry::PositionsFieldId:
        case Geometry::NormalsFieldId:
        case Geometry::ColorsFieldId:
        case Geometry::SecondaryColorsFieldId:
            FWARNING(("Case currently not treated, using NONE\n")); 
            dstAttribBin = -1;
                  
        case -1:
            binormalP = GeoTexCoords4f::create();
            break;
    }
    
    // can't eval what combination was meant
    if ( srcTexIndex < 0 || srcTexIndex > 3 || 
        (dstAttribTan == -1 && dstAttribBin == -1)) 
    {
        FFATAL(("Index set not supported in calcVertexTangents()\n"));
        return;
    }
    
    GeoIndicesPtr ip = geo->getIndices();
        
    // HACK but without indices it crashes
    if (ip == NullFC || ip->size() == 0) 
    {
        FFATAL(("Geo without indices in calcVertexTangents()\n"));
        return;
    }
    
    GeoPositionsPtr positions = geo->getPositions();
    
    // Get the positions property
    if (positions == NullFC) 
    {
        FFATAL(("Geo without positions in calcVertexTangents()\n"));
        return;
    }

    MFUInt16 &im = geo->getIndexMapping();
    Int16 niTan = (mapTan > 0) ? geo->calcMappingIndex(mapTan) : -1,
          niBin = (mapBin > 0) ? geo->calcMappingIndex(mapBin) : -1;
          
    Int32 indexMapSize = im.size(), j, imsize = 0;
    UInt32 i, val, nind = ip->size() / (indexMapSize ? indexMapSize : 1);
    bool multiIndex = (indexMapSize > 1) ? true : false;
    
    beginEditCP(geo, Geometry::IndexMappingFieldMask |
                     Geometry::IndicesFieldMask );
   
    if (multiIndex) 
    {
        // separate the attrib's index if exist
        if (niTan >= 0) 
            im[niTan] = im[niTan] & ~mapTan;
        if (niBin >= 0)
            im[niBin] = im[niBin] & ~mapBin; 
            
        // if im[ni] < 1 erase because index is unused
        MFUInt16::iterator imIt = im.begin();
        if (niTan == niBin) 
        {
            if (niTan >= 0 && im[niTan] < 1)
                im.erase(imIt + niTan);
            else 
                niTan = niBin = -1;    // not deleted
        }
        else if (niTan < niBin) 
        {
            if (niBin >= 0 && im[niBin] < 1)
                im.erase(imIt + niBin);
            else 
                niBin = -1;
            if (niTan >= 0 && im[niTan] < 1)
                im.erase(imIt + niTan);
            else 
                niTan = -1;
        }
        else 
        {
            if (niTan >= 0 && im[niTan] < 1)
                im.erase(imIt + niTan);
            else 
                niTan = -1;
            if (niBin >= 0 && im[niBin] < 1)
                im.erase(imIt + niBin);
            else 
                niBin = -1;
        }

        // create new mapping for attribs
        UInt16 map = 0;
        if (mapTan > 0)
            map |= mapTan;
        if (mapBin > 0)
            map |= mapBin;
        if (map > 0)
            im.push_back(map);
        imsize = im.size();

        // add an entry to the indices for the attribs        
        std::vector<UInt32> indexBuffer;
        int status, l = 0, g = 0, ibSize;
        
        if (niTan < 0 && niBin < 0) 
        {
            status = 0;
        }
        else if (niBin < 0 && niTan >= 0 || 
                 niBin >= 0 && niTan < 0 ||
                 niBin >= 0 && niBin == niTan) 
        {
            status = 1;
            l = (niBin < niTan) ? niTan : niBin;
        }
        else /*if (niBin > 0 && niTan > 0)*/ 
        {
            status = 2;
            l = (niBin < niTan) ? niBin : niTan;
            g = (niBin < niTan) ? niTan : niBin;
        }
        
        // discard positions l and g and provide index for tangent|binormal
        for (i=0; i<nind; i++) 
        {
            for (j=0; j<indexMapSize; j++) 
            {
                switch (status) 
                {
                    case 0:
                        indexBuffer.push_back(ip->getValue(i*indexMapSize+j));
                        break;
                    case 1: 
                        if (j != l)
                            indexBuffer.push_back(ip->getValue(i*indexMapSize+j));
                        break;
                    case 2:
                        if (j != l && j != g)
                            indexBuffer.push_back(ip->getValue(i*indexMapSize+j));
                        break;
                }
            }
            indexBuffer.push_back(0);    // will be tangent|binormal index
        }
        ibSize = indexBuffer.size();
        
        beginEditCP(ip);
        {
            ip->clear();
            ip->resize(ibSize);

            for (i=0; i<ibSize; i++) 
                ip->setValue(indexBuffer[i], i);
        }
        endEditCP(ip);
        
    } // multiIndex
    else
    {
        // add index map for single index.
        if(im.size() > 0)
            im[0] |= (mapTan | mapBin);
    }

    endEditCP(geo, Geometry::IndexMappingFieldMask |
                   Geometry::IndicesFieldMask );
    
    TriangleIterator tI;
    IndexDic indexDic;
    Int32 k, index, v[3];
    Vec4f vect(0, 0, 0, 0);
    
    std::vector<Int32>indexVec;
    Int16 niPos  = geo->calcMappingIndex(Geometry::MapPosition),
          niNorm = geo->calcMappingIndex(Geometry::MapNormal),
          niTex  = geo->calcMappingIndex(mapTex);
    
    indexVec.resize(3);    
    
    beginEditCP(ip);

    // calc max index.
    UInt32 maxindex = 0;
    for(i=0;i<ip->size();++i)
        maxindex = ip->getValue(i) > maxindex ? ip->getValue(i) : maxindex;

    // init property arrays
    // amz we can't use the indices size (nind) here!
    tangent.resize(maxindex + 1);
    binormal.resize(maxindex + 1);
    normal.resize(maxindex + 1);

    for (tI=geo->beginTriangles(), i=0; tI!=geo->endTriangles(); ++tI, ++i) 
    {         
        // first, get index for every vertex
        for (k=0; k<3; ++k) 
        {
            index = tI.getIndexIndex(k);
            
            if (multiIndex) 
            {
                // make vertex unique with resp. to Position, Normal, TexCoord
                for (j=0; j<imsize; j++) 
                {
                    if (j == niPos || j == niNorm || j == niTex)
                        indexVec[j] = ip->getValue(index + j);
                }
                v[k] = indexDic.entry(indexVec);
            }
            else 
            {
                v[k] = tI.getPositionIndex(k); //index;
            }
        }
        
        // second, calculate tangent and binormal for every tri
        Int32 v0 = tI.getPositionIndex(0),
              v1 = tI.getPositionIndex(1),
              v2 = tI.getPositionIndex(2);
        Vec2f t0, t1, t2, tex1, tex2;
        Vec3f edge1, edge2, sdir, tdir;
        
        switch (srcTexIndex) 
        {
            case 0:
                t0 = tI.getTexCoords(0);
                t1 = tI.getTexCoords(1);
                t2 = tI.getTexCoords(2);
                break;
            case 1:
                t0 = tI.getTexCoords1(0);
                t1 = tI.getTexCoords1(1);
                t2 = tI.getTexCoords1(2);
                break;
            case 2:
                t0 = tI.getTexCoords2(0);
                t1 = tI.getTexCoords2(1);
                t2 = tI.getTexCoords2(2);
                break;
            case 3:
                t0 = tI.getTexCoords3(0);
                t1 = tI.getTexCoords3(1);
                t2 = tI.getTexCoords3(2);
                break;
            case 4:
                t0 = tI.getTexCoords4(0);
                t1 = tI.getTexCoords4(1);
                t2 = tI.getTexCoords4(2);
                break;
            case 5:
                t0 = tI.getTexCoords5(0);
                t1 = tI.getTexCoords5(1);
                t2 = tI.getTexCoords5(2);
                break;
            case 6:
                t0 = tI.getTexCoords6(0);
                t1 = tI.getTexCoords6(1);
                t2 = tI.getTexCoords6(2);
                break;
            case 7:
                t0 = tI.getTexCoords7(0);
                t1 = tI.getTexCoords7(1);
                t2 = tI.getTexCoords7(2);
                break;
        }
        
        edge1 = tI.getPosition(1) - tI.getPosition(0),
        edge2 = tI.getPosition(2) - tI.getPosition(0);
        tex1 = t1 - t0;
        tex2 = t2 - t0;

        // in rare cases this is zero!
        Real32 invDet = (tex1[0]*tex2[1] - tex2[0]*tex1[1]);
        if(invDet != 0.0f)
            invDet = 1.0f / invDet;
        else
            invDet = 0.0f;

        sdir = invDet * (tex2[1]*edge1 - tex1[1]*edge2);    // tangent
        tdir = invDet * (tex1[0]*edge2 - tex2[0]*edge1);    // binormal
        
        // set value for every vertex
        int tanOffset = (imsize == 0) ? 0 : imsize-1;
        
        for (k=0; k<3; ++k) 
        {
            tangent[v[k]] += sdir;
            binormal[v[k]] += tdir;
            normal[v[k]] = tI.getNormal(k);
            ip->setValue(v[k], tI.getIndexIndex(k) + tanOffset); 
        }
    }
    endEditCP(ip);
    
    // orthogonalize vectors (Gram-Schmidt) and calc handedness    
    Vec3f T, B, N;
    Real32 sign = 0, l1, l2;
    tangentP->clear();
    binormalP->clear();

    beginEditCP(tangentP);
    beginEditCP(binormalP);

    for (i=0;i < tangent.size();++i)
    {
        T = tangent [i];
        B = binormal[i];
        N = normal  [i];    // must be normalized: n*n = 1

        sign = ((N.cross(T)).dot(B) < 0) ? -1 : 1;
        
        T = T - N.dot(T) * N;
        T.normalize();
        B = B - N.dot(B) * N - T.dot(B) * T;
        B.normalize(); 
        
        vect.setValues(T[0], T[1], T[2], sign);
        tangentP->getField().push_back(vect); 
        
        vect.setValues(B[0], B[1], B[2], sign);
        binormalP->getField().push_back(vect); 
    }

    endEditCP(tangentP);
    endEditCP(binormalP);
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    createOptimizedPrimitives changes the Geometry to make it faster to render
    by creating triangle strips and fans, see \ref
    PageSystemGeoFunctionsOptimizeGeo for a description.
    
    \a geoPtr is the Geometry to optimize and \a iteration is the number of
    iteratiosn that are tried to find the best solution. \a createStripes and
    \a createFans defines whether stripes, fans or both should be created, with
    \a minFanEdgeCount giving the number of adjacent edges a vertex need to be
    considered for a fan. For visualising the results, a random \a colorCode
    can be assigned to each generated primitive.
    
    It returns the number of vertex transformations needed to render the
    Geometry.
*/

OSG_SYSTEMLIB_DLLMAPPING 
Int32 OSG::createOptimizedPrimitives(GeometryPtr geoPtr,
                                     UInt32 iteration,
                                     bool createStrips,
                                     bool createFans,
                                     UInt32 minFanEdgeCount,
                                     bool OSG_CHECK_ARG(colorCode),
                                     bool stitchStrips)
{
    if (geoPtr == NullFC)
    {
        return 0;
    }

    HalfEdgeGraph graph;

    UInt32 cost = 0, startCost, bestCost = 0, worstCost = 0, best = 0;

    GeoPLengthsPtr lensPtr;
    GeoPTypesPtr geoTypePtr;
    Time time, inputT, optimizeT, outputT;

    IndexDic indexDic;
    int invalidTriCount = 0;

    GeoPositionsPtr posPtr = geoPtr->getPositions();
    UInt32 pN = ((posPtr == OSG::NullFC) ? 0 : posPtr->getSize());
    UInt32 indexMapSize = (geoPtr->getIndexMapping().size());
    bool remapIndex = (indexMapSize > 1) ? true : false;

    UInt32 triN, lineN, pointN;
    calcPrimitiveCount(geoPtr, triN, lineN, pointN);

    GeoIndicesPtr indexPtr = geoPtr->getIndices();

    // Calculate startCost.
    if(indexPtr == NullFC)
        startCost = pN;
    else
    {
        if(indexMapSize)
        {
            startCost = indexPtr->size() / indexMapSize;
        }
        else
            startCost = indexPtr->size();
    }

    // Leave early if we have no indices or positions.
    if (pN == 0 || indexPtr == NullFC)
    {
        return 0;
    }
    
    FDEBUG(("GeoOpt: start/tri cost: %d/%d imp: %d tri/line/point: %d/%d/%d\n",
            startCost, (triN * 3), indexMapSize, triN, lineN, pointN));

    inputT = getSystemTime();

    invalidTriCount = 0;
    
    if (!remapIndex && (pN > (triN * 3))) 
    {
        FINFO (( "Force index remap for unusual vertex/tri count: %d/%d\n",
                    pN, triN ));
        indexMapSize = 1;
        remapIndex = true;
    }

    if(remapIndex)
    {
        graph.reserve(triN * 3, triN, 8);
        std::vector < Int32 > indexVec(indexMapSize);
        UInt32 triCount = 0;
        for(TriangleIterator tI = geoPtr->beginTriangles(); (triCount < triN) && (tI != geoPtr->endTriangles());
                        ++tI)
        {
            Int32 v[3];
            for(Int32 i = 0; i < 3; i++)
            {
                Int32 index = tI.getIndexIndex(i);
                for(Int32 j = 0; j < indexMapSize; j++)
                {
                    indexVec[j] = indexPtr->getValue(index + j);
                }

                v[i] = indexDic.entry(indexVec);
            }

            invalidTriCount += graph.addTriangle(v[0], v[1], v[2]) ? 0 : 1;
            ++triCount;
        }

        FDEBUG(("Multi-index dic entry: %d/%d\n", indexDic.entryCount(),
                                (triN * 3)));
    }
    else
    {
        graph.reserve(osgMin(pN, triN * 3), triN, 8);
        UInt32 triCount = 0;
        for(TriangleIterator tI = geoPtr->beginTriangles(); (triCount < triN) && (tI != geoPtr->endTriangles());
                        ++tI)
        {
            invalidTriCount += graph.addTriangle(tI.getPositionIndex(0),
                                                 tI.getPositionIndex(1),
                                                 tI.getPositionIndex(2)) ? 0 : 1;
            ++triCount;
        }
    }

    if(invalidTriCount)
    {
        FNOTICE(("%d invalid tri during halfegde construction found\n",
                                 invalidTriCount));
    }

#ifdef OSG_DEBUG
        graph.verify();
#endif

    time = getSystemTime();
    inputT = time - inputT;
    optimizeT = time;
    bestCost = triN * 3 + 1;
    worstCost = 0;
    cost = graph.calcOptPrim(iteration, createStrips, createFans, minFanEdgeCount);
    if(cost)
    {
        if(cost < bestCost)
            bestCost = cost;

        if(cost > worstCost)
            worstCost = cost;
    }
    else
    {
        bestCost = worstCost = 0;
    }

    // valid result
    if(bestCost && (bestCost < startCost))
    {
        // check/create the indexPtr/lengthsPtr/geoTypePtr
        OSG::beginEditCP(geoPtr, OSG::Geometry::LengthsFieldMask |
                                     OSG::Geometry::TypesFieldMask);

        lensPtr = geoPtr->getLengths();
        if(lensPtr == OSG::NullFC)
        {
            lensPtr = OSG::GeoPLengthsUI32::create();
            geoPtr->setLengths(lensPtr);
        }

        geoTypePtr = geoPtr->getTypes();
        if(geoTypePtr == OSG::NullFC)
        {
            geoTypePtr = OSG::GeoPTypesUI8::create();
            geoPtr->setTypes(geoTypePtr);
        }

        OSG::endEditCP(geoPtr, OSG::Geometry::LengthsFieldMask |
                               OSG::Geometry::TypesFieldMask);

        time = getSystemTime();
        optimizeT = time - optimizeT;
        outputT = time;

        beginEditCP(lensPtr);
        beginEditCP(geoTypePtr);
        beginEditCP(indexPtr);

        lensPtr->clear();
        geoTypePtr->clear();
        indexPtr->clear();

        FDEBUG(("Start graph.getPrimitive() loop (triN: %d)\n", triN));

        UInt32 numPrimitives = graph.primitiveCount();
        std::vector<std::vector<UInt32> > primIndex(numPrimitives);

        const Int32 typeVec[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN };
        const Int32 typeN = sizeof(typeVec) / sizeof(Int32);

        cost = 0;

        for(Int32 t = 0; t < typeN; ++t)
        {
            UInt32 triCount = 0;

            bool stitch = false;
            UInt32 windingCorrection = 0;
            UInt32 lastTriStripIndex = 0;
            UInt32 totalTriStripLength = 0;

            for(Int32 i = 0; i < Int32(numPrimitives); ++i)
            {
                graph.getPrimitive(primIndex[i], typeVec[t]);
                const Int32 n = primIndex[i].size();
                cost += n;

                if(!n)
                {
                    break;
                }

                if(typeVec[t] == GL_TRIANGLES)
                {
                    triCount += (n / 3);
                }
                else if (typeVec[t] == GL_TRIANGLE_STRIP)
                {
                    if (stitchStrips)
                    {
                        if (stitch)
                        {
                            // add the previous index and the first of the
                            // new one, but make sure winding is still correct.
                            if (remapIndex)
                            {
                                for (int j = 0; j < 1 + windingCorrection; ++j)
                                {
                                    for (int k = 0; k < indexMapSize; ++k)
                                    {
                                        indexPtr->push_back(indexDic.entry(lastTriStripIndex)[k]);
                                    }
                                }
                                for (int k = 0; k < indexMapSize; ++k)
                                {
                                    indexPtr->push_back(indexDic.entry(primIndex[i][0])[k]);
                                }
                            }
                            else
                            {
                                for (int j = 0; j < 1 + windingCorrection; ++j)
                                {
                                    indexPtr->push_back(lastTriStripIndex);
                                }
                                indexPtr->push_back(primIndex[i][0]);
                            }
                            totalTriStripLength += 2 + windingCorrection;
                        }
                        stitch = true;
                        windingCorrection = n % 2;
                        lastTriStripIndex = primIndex[i][n - 1];
                    }
                    else
                    {
                        lensPtr->push_back(n);
                        geoTypePtr->push_back(typeVec[t]);
                    }
                }
                else
                {
                    lensPtr->push_back(n);
                    geoTypePtr->push_back(typeVec[t]);
                }

                if(remapIndex)
                {
                    for(Int32 j = 0; j < n; ++j)
                    {
                        for(Int32 k = 0; k < indexMapSize; ++k)
                        {
                            Int32 index = indexDic.entry(primIndex[i][j])[k];
                            indexPtr->push_back(index);
                        }
                    }
                }
                else
                {
                    for(Int32 j = 0; j < n; ++j)
                    {
                        indexPtr->push_back(primIndex[i][j]);
                    }
                }
                totalTriStripLength += n;
            }

            if(triCount && typeVec[t] == GL_TRIANGLES)
            {
                lensPtr->push_back(triCount * 3);
                geoTypePtr->push_back(GL_TRIANGLES);
            }

            if(stitchStrips && totalTriStripLength &&
               typeVec[t] == GL_TRIANGLE_STRIP)
            {
                lensPtr->push_back(totalTriStripLength);
                geoTypePtr->push_back(GL_TRIANGLE_STRIP);
            }
        }

        endEditCP(lensPtr);
        endEditCP(geoTypePtr);
        endEditCP(indexPtr);

        time = getSystemTime();
        outputT = time - outputT;

        FNOTICE(("Graph in/opt/out timing: %g/%g/%g \n", inputT, optimizeT,
                                outputT));

        if(cost != bestCost)
        {
            FWARNING(("cost != bestCost: %d/%d; we lost some nodes !\n",
                                       cost, bestCost));
        }
        else
        {
            FINFO(("OptResult: %2g%%, Sampling (%di): cost %d/%d \n",
                                        double(double(bestCost) / double(
                                            startCost) * 100.0
                                ), iteration, bestCost, worstCost));
        }
    }
    else
    {
        FINFO(("startCost (%d) <= bestCost (%d), triCost(%d); keep geo data\n",
                        startCost, bestCost, (triN * 3)));
    }

    return bestCost;
}

//Define the gluTessCallback functions 

//Dummy edge handler: Switches off the creation of triangle strips
//and fans
void OSG_APIENTRY gluTessEdgeFlagCB(GLboolean /*flag*/)
{
  //empty 
  FDEBUG(("gluEdgeVertexCB called\n"));
}

//Vertex data handler: Receives the triangle vertex indices from the 
//GLU Tesselator
void OSG_APIENTRY gluTessVertexDataCB(UInt32              *curIndexPtr, 
                                      std::vector<UInt32> *indexV)
{
    if(indexV != NULL)
    {
        FDEBUG(("gluVertexDataCB called: indexV@%p->push_back(%d)\n", 
                indexV, *curIndexPtr));
        indexV->push_back(*curIndexPtr);
    }
    else 
    {
        FDEBUG(("Null Pointer in gluTessVertexDataCB\n"));
    }
}

//Begin data handler: Initializes the pointer to the index data
void OSG_APIENTRY gluTessBeginDataCB(GLenum type, std::vector<UInt32>  *indexV)
{
    if(indexV != NULL) 
    {
        FDEBUG(("gluTessBeginDataCB: Beginning new Polygon\n"));
        FDEBUG(("gluTessBeginDataCB: Type is %d\n", type));
        FDEBUG(("gluTessBeginDataCB: indexV* is 0x%p\n", indexV));
    }
    else 
    {
        FDEBUG(("Null Pointer in gluTessVertexDataCB\n"));
    }
}

//End handler: For debugging purposes only
void OSG_APIENTRY gluTessEndCB()
{
  FDEBUG(("gluTessEndCB called\n"));
}

//Error handler: Called by the GLU Tesselator to signal errors
void OSG_APIENTRY gluTessErrorCB(GLenum errNo)
{
    FWARNING(("gluTesselator Error: %s\n", gluErrorString(errNo)));
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    createConvexPrimitives iterates over all primitives of the passed
    geometry tesselating them with the aid of the GLU tesselator. 
    As a result every planar polygon is tesselated into a sequence of 
    triangles covering it.

    In case of nonplanar Polygons the results are not guaranteed to be 
    correct.

    Simple, i.e non-indexed geometries are not supported.
*/

OSG_SYSTEMLIB_DLLMAPPING 
void OSG::createConvexPrimitives(GeometryPtr geoPtr)
{
  FINFO(("Entering createConvexPrimitives()\n"));

	GLenum windingRule = GLU_TESS_WINDING_ODD;

  OSG::GeoIndicesUI32Ptr       indexPtr;
  OSG::GeoIndicesUI32Ptr       newIndexPtr = GeoIndicesUI32::create();
  OSG::GeoPTypesPtr            newTypesPtr = GeoPTypesUI8::create();
  OSG::GeoPLengthsPtr          newLengthsPtr  = GeoPLengthsUI32::create();

  bool indexed = true;

  std::vector< UInt32 >    inIndexV;
  std::vector< UInt32 >    outIndexV;
  std::vector< GLdouble >  positionV;

  inIndexV.reserve(4096);  
  outIndexV.reserve(4096);
  positionV.reserve(4096);

  if(geoPtr == NullFC)
  {
      FINFO(("Invalid geoPtr in createConvexPrimitives()\n"));
      return;
  }

  //scan the geometry for GL_POLYGONs
  bool containsPolygon = false; 
  PrimitiveIterator primI = geoPtr->beginPrimitives();
  for(;primI != geoPtr->endPrimitives(); ++primI)
  {
      if(primI.getType() == GL_POLYGON)
      {
          containsPolygon = true;
          break;
      }
  }

  // skip geometry if it doesn't contain a GL_POLYGON
  if(!containsPolygon)
  {
      FINFO(("Geometry with no GL_POLYGONs in createConvexPrimitives:\n"));
      FINFO(("Nothing to do for createConvexPrimitives: Returning\n"));
      return;
  }

  // determine whether the geometry is indexed
  indexPtr =  GeoIndicesUI32Ptr::dcast(geoPtr->getIndices());
  indexed = (indexPtr == NullFC) ?  false : true;
  FDEBUG(("Indexed: %d\n",indexed));

  // skip geometry if it is empty or not indexed
  if(!indexed)
  {
      FINFO(("Skipping nonindexed geometry in createConvexPrimitives()\n"));
      return;
  }
  else
  {
      if(geoPtr->getIndices()->size() == 0)
      {
          FINFO(("Skipping empty geometry in createConvexPrimitives()\n")); 
          return;
      }
  }

  // convert function pointers to the type expected by the GLU Tesselator
  OSGGLUfuncptr gluTessBeginDataCBPtr = 
    reinterpret_cast<OSGGLUfuncptr>(gluTessBeginDataCB);

  OSGGLUfuncptr gluTessEdgeFlagCBPtr = 
    reinterpret_cast<OSGGLUfuncptr>(gluTessEdgeFlagCB);

  OSGGLUfuncptr gluTessVertexDataCBPtr = 
    reinterpret_cast<OSGGLUfuncptr>(gluTessVertexDataCB);

  OSGGLUfuncptr gluTessEndCBPtr = 
    reinterpret_cast<OSGGLUfuncptr>(gluTessEndCB);

  OSGGLUfuncptr gluTessErrorCBPtr = 
    reinterpret_cast<OSGGLUfuncptr>(gluTessErrorCB);

  // create and setup a new GLU Tesselator
  FDEBUG(("gluNewTess()\n"));
  GLUtesselator* tess = gluNewTess();

  if(tess == NULL)
  {
      FFATAL(("Creation of GLUtesselator failed\n"));
      return;
  }
  else
    FINFO(("Created GLU Tesselator (%p)\n", tess));

  // set the specified winding rule
  FDEBUG(("gluTessProperty(%p, GLU_TESS_WINDING_RULE, %d)\n",
          tess, windingRule));
  gluTessProperty(tess, GLU_TESS_WINDING_RULE, windingRule);

  // register self defined GLU Tesselator callback methods
  FDEBUG(("gluTessCallback(%p, GLU_TESS_ERROR, %p)\n", 
          tess, gluTessErrorCBPtr));
  gluTessCallback(tess, GLU_TESS_ERROR, gluTessErrorCBPtr);

  FDEBUG(("gluTessCallback(%p, GLU_TESS_BEGIN_DATA, %p)\n", 
          tess, gluTessBeginDataCBPtr));
  gluTessCallback(tess, GLU_TESS_BEGIN_DATA, gluTessBeginDataCBPtr);

  FDEBUG(("gluTessCallback(%p, GLU_TESS_EDGE_FLAG, %p)\n",
          tess, gluTessEdgeFlagCBPtr));
  gluTessCallback(tess, GLU_TESS_EDGE_FLAG, gluTessEdgeFlagCBPtr);

  FDEBUG(("gluTessCallback(%p, GLU_TESS_VERTEX_DATA, %p)\n",
          tess, gluTessVertexDataCBPtr));
  gluTessCallback(tess, GLU_TESS_VERTEX_DATA, gluTessVertexDataCBPtr);

  FDEBUG(("gluTessCallback(%p, GLU_TESS_END, %p)\n",
          tess, gluTessEndCBPtr));
  gluTessCallback(tess, GLU_TESS_END, gluTessEndCBPtr);

  beginEditCP(newTypesPtr);
  beginEditCP(newIndexPtr);
  beginEditCP(newLengthsPtr);

  primI = geoPtr->beginPrimitives();
  for(;primI != geoPtr->endPrimitives(); ++primI)
  {
      FDEBUG(("Primitive index: %d\n", primI.getIndex()));
      
      // if the primitive is not of type GL_POLYGON just copy its contents
      if(primI.getType() != GL_POLYGON)
      {
          FDEBUG(("Not a GL_POLYGON. Copying properties\n"));
          if(!indexed)
          {
              FWARNING(("createConvexPrimitives(): Nonindexed geometries are not implemented!\n"));
          }
          else
          {
              newTypesPtr->push_back(primI.getType());

              // maybe we should use memcpy here instead of explicitly copying
              // each multiindex
              for(UInt32 i = 0; i < primI.getLength(); i++)
              {
                  Int32 curIndex = primI.getIndexIndex(i);
                  for(UInt32 j = 0; j < geoPtr->getIndexMapping().size(); j++)
                  {
                      UInt32 val = indexPtr->getValue(curIndex + j);
                      newIndexPtr->push_back(val);
                  }
              }
              newLengthsPtr->push_back(primI.getLength());
          }
      }
      // Process GL_POLYGONs i.e. tesselate them
      else
      {
          FDEBUG(("Tesselating GL_POLYGON (PrimitiveIndex: %d, Vertices %d)\n",
                 primI.getIndex(), primI.getLength()));

          inIndexV.clear();  
          outIndexV.clear();
          positionV.clear();
          
          for(UInt32 i = 0; i < primI.getLength(); i++)
          {
              // Convert the vertices to double precision
              // (the tesselator expects them that way)
              positionV.push_back(static_cast< GLdouble >(primI.
                                                          getPosition(i)[0]));
              positionV.push_back(static_cast< GLdouble >(primI.
                                                          getPosition(i)[1]));
              positionV.push_back(static_cast< GLdouble >(primI.
                                                          getPosition(i)[2]));

              // Store the start index of the current multi index
              // to pass it as "meta data" to the tesselator later on
              UInt32 curIndex = indexed ? primI.getIndexIndex(i) : i;
              inIndexV.push_back(curIndex);
          }

#ifdef OSG_DEBUG          

          for(UInt32 i = 0; i < primI.getLength(); i++) 
					{

            int index = inIndexV.at(i);
            double x  = positionV.at(3*i); 
            double y  = positionV.at(3*i + 1); 
            double z  = positionV.at(3*i + 2);

            FDEBUG(("Position index: %i Position: (%f,%f,%f)\n", 
                    index, x, y, z));
          }
#endif

          // cast the address of the std::vector which stores the 
          // tesselator output to a GLvoid *
          GLvoid* outIndexPtr = reinterpret_cast< GLvoid* >(&outIndexV);

          FDEBUG(("gluTessBeginPolygon(%p, %p)\n", tess, outIndexPtr));
          gluTessBeginPolygon(tess, outIndexPtr);

          FDEBUG(("gluTessBeginContour(%p)\n", tess));
          gluTessBeginContour(tess);


          for(UInt32 i = 0; i <  primI.getLength(); i++)
          {
              GLvoid* curIndexPtr = reinterpret_cast< GLvoid* >(&inIndexV[i]);
              FDEBUG(("gluTessVertex(%p, %p, %p)\n",
                      tess, &positionV[i * 3], curIndexPtr));

              // feed the prepared position data and the according beginning 
              // of its multiindex in the index property to the tesselator
              gluTessVertex(tess, &positionV[i * 3], curIndexPtr);
          }

          FDEBUG(("gluTessEndContour(%p)\n", tess));
          gluTessEndContour(tess);

          FDEBUG(("gluTessEndPolygon(%p)\n", tess));
          // trigger the tesselator action
          gluTessEndPolygon(tess); 

          newTypesPtr->push_back(GL_TRIANGLES);
          
          if(!indexed)
          {
              FWARNING(("createConvexPrimitives(): Nonindexed geometries are not implemented!\n"));
          }
          else
          {
              FDEBUG(("Rebuilding multi indices ...\n"));
              // copy the indices gathered during the tesselator run
              // into a new index container
              for(UInt32 i = 0; i < outIndexV.size(); i++)
              {
                  UInt32 vII = outIndexV[i];
                  for(UInt32 j = 0; j < geoPtr->getIndexMapping().size(); j++)
                  {
                      FDEBUG(("Index in tesselated data %d\n",vII + j));
                      Int32 curIndex = indexPtr->getValue(vII + j);
                      
                      FDEBUG(("newIndexPtr->push_back(%d)\n", curIndex));
                      newIndexPtr->push_back(curIndex);
                  }
              }
          }
          FINFO(("Vertex count: %d/%d (before/after tesselation)\n",
                 primI.getLength(), outIndexV.size()));
          newLengthsPtr->push_back(outIndexV.size());
      }
  }
  
  endEditCP(newTypesPtr);
  endEditCP(newIndexPtr);
  endEditCP(newLengthsPtr);
  
  beginEditCP(geoPtr);

  // update the geometry properties 
  geoPtr->setTypes(newTypesPtr);
  geoPtr->setIndices(newIndexPtr);
  geoPtr->setLengths(newLengthsPtr);
  
  endEditCP(geoPtr);
    
  FDEBUG(("gluDeleteTess(%p)\n", tess));
  gluDeleteTess(tess);

  FDEBUG(("Exiting from createConvexPrimitives()\n"));
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    createSharedIndex tries to merge identical elements in the Geometry's
    Properties, see \ref
    PageSystemGeoFunctionsOptimizeGeo for a description.
*/

OSG_SYSTEMLIB_DLLMAPPING Int32 OSG::createSharedIndex(GeometryPtr geoPtr)
{
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    UInt32 indexSharedCount = 0, dataRemapCount = 0, indexRemapCount = 0;
    UInt32 i, iN, index, si, sN;
    UInt32 indexMapSize, indexBlock = 0, masterDSize;
    GeoPropertyArrayInterface *masterProp = 0, *slaveProp = 0;
    UInt8 *masterData;
    std::vector < UInt32 > slaveDSizeVec;
    std::vector < UInt8 * > slaveDataVec;

    UInt16 mapMask, propMask, masterPropMask;
    typedef std::pair<UInt8 *, UInt32> Mem;
    Mem mem;
    std::map<Mem, UInt32, memless<Mem> > memMap;
    std::map<Mem, UInt32, memless<Mem> >::iterator mmI;

    GeoIndicesPtr indexPtr;
    UChar8 *dataElem;
    std::vector < Int32 > indexRemap;

    if(geoPtr != NullFC)
    {
        if(geoPtr->getPositions() != NullFC)
        {
            // check/create indexPtr
            iN = geoPtr->getPositions()->size();
            indexPtr = geoPtr->getIndices();
            if(indexPtr == NullFC)
            {
                indexPtr = GeoIndicesUI32::create();
                indexPtr->resize(iN);
                for(i = 0; i < iN; i++)
                    indexPtr->setValue(i, i);
                beginEditCP(geoPtr);
                {
                    geoPtr->setIndices(indexPtr);
                }

                endEditCP(geoPtr);
            }
        }
        else
        {
            FNOTICE(("Invalid geoPtr->getPositions() in createSharedIndex()\n"));
        }
    }
    else
    {
        FNOTICE(("Invalid geoPtr in createSharedIndex()\n"));
    }

    if(indexPtr != NullFC)
    {
        // get the index count
        indexMapSize = geoPtr->getIndexMapping().size();

        // find first propMask;
        if(indexMapSize)
        {
            propMask = geoPtr->getIndexMapping()[0];
        }
        else
        {
            // no index geo; find valid property
            for(mapMask = 1, propMask = 0; mapMask && mapMask != Geometry::MapEmpty;
                            mapMask <<= 1)
            {
                if(geoPtr->getProperty(mapMask))
                    propMask |= mapMask;
            }

            indexMapSize = 1;
        }

        // remap the index for a single index block
        for(indexBlock = 0; propMask;)
        {
            // reset stat counter
            indexSharedCount = 0;
            dataRemapCount = 0;
            indexRemapCount = 0;

            // find master property
            for(masterPropMask = 1; (propMask & masterPropMask) == 0;)
                masterPropMask <<= 1;

            if((masterProp = geoPtr->getProperty(masterPropMask)) &&
                           (masterData = masterProp->getData()))
            {
                // calc master data element size
                masterDSize = masterProp->getFormatSize() *
                    masterProp->getDimension() +
                    masterProp->getStride();

                // find and store slave property data and size
                slaveDataVec.clear();
                slaveDSizeVec.clear();
                for(mapMask = 1; mapMask && mapMask != Geometry::MapEmpty;
                                    mapMask <<= 1)
                {
                    if((mapMask != masterPropMask) && (mapMask & propMask))
                    {
                        if((slaveProp = geoPtr->getProperty(mapMask & propMask)))
                        {
                            slaveDataVec.push_back(slaveProp->getData());
                            slaveDSizeVec.push_back(slaveProp->getFormatSize() *
                                                                                slaveProp->getDimension());
                        }
                        else
                        {
                            FWARNING(("Invalid slaveProp %d\n", (mapMask & propMask)
                                                       ));
                        }
                    }
                }

                sN = slaveDataVec.size();
                iN = indexPtr->size() / indexMapSize;
                memMap.clear();
                indexRemap.clear();
                indexRemap.resize(masterProp->size(), -1);
                mem.second = masterProp->getFormatSize() * masterProp->getDimension();

                for(i = 0; i < iN; i++)
                {
                    index = indexPtr->getValue(i * indexMapSize + indexBlock);
                    if(indexRemap[index] >= 0)
                    {
                        if(indexRemap[index] == index)
                        {
                            indexSharedCount++;
                        }
                        else
                        {
                            indexPtr->setValue(indexRemap[index],
                                                                           i * indexMapSize + indexBlock);
                            indexRemapCount++;
                        }
                    }
                    else
                    {
                        // find/include the data block
                        dataElem = masterData + (index * masterDSize);
                        mem.first = dataElem;
                        mmI = memMap.find(mem);
                        if(mmI == memMap.end())
                        {
                            // index not found; store new data/index
                            memMap[mem] = index;
                            indexRemap[index] = index;
                        }
                        else
                        {
                            // data found; check slave property
                            for(si = 0; si < sN; si++)
                            {
                                if(memcmp(slaveDataVec[si] + 
                                             (index * slaveDSizeVec[si]),
                                          slaveDataVec[si] +
                                             (mmI->second * slaveDSizeVec[si]),
                                          slaveDSizeVec[si]))
                                    break;
                            }

                            if(si == sN)
                            {
                                // no or valid slave data; remap the index
                                indexPtr->setValue(mmI->second,
                                                i * indexMapSize + indexBlock);
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
                FWARNING(("Invalid masterProp %p, mask: %d, block: %d\n",
                                           masterProp, propMask, indexBlock));
            }

            FINFO(("Create sharedIndex: %d/%d pass; "
                     "data/index remap: %d/%d \n",
                            indexBlock, int(propMask), dataRemapCount, 
                            indexRemapCount));

            // get next propery Mask
            if(++indexBlock < indexMapSize)
            {
                propMask = geoPtr->getIndexMapping()[indexBlock];
            }
            else
                propMask = 0;
        }
    }

    return indexRemapCount + dataRemapCount;

#else
    FFATAL(("Cannot run createSharedIndex: NO_GEO_INFACE\n"));
    return -1;
#endif
}

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    createSingleIndex manipulates the Geometry's Properties to only use
    a single index, see \ref
    PageSystemGeoFunctionsOptimizeGeo for a description.
    
    It returns the number of property values kept.
*/

OSG_SYSTEMLIB_DLLMAPPING Int32 OSG::createSingleIndex(GeometryPtr geoPtr)
{
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    Int16 mask, maskID, finalMask = 0;
    Int32 indexMapSize, indexCount, i, j, vCount = 0;
    Int32 index;
    Int32 memSize, valueSize;
    UInt8 *pData, *data;
    GeoIndicesPtr indexPtr;
    IndexDic indexDic;
    std::vector < Int32 >

    indexVec, sIndex;
    GeoPropertyArrayInterface *pP = 0;

    if((geoPtr != NullFC) &&
           (indexMapSize = (geoPtr->getIndexMapping().size())))
    {
        beginEditCP(geoPtr, Geometry::IndexMappingFieldMask |
                            Geometry::IndicesFieldMask);

        indexPtr = geoPtr->getIndices();
        indexVec.resize(indexMapSize);

        // fill the indexDic
        if(indexPtr != NullFC)
        {
            indexCount = indexPtr->size() / indexMapSize;
            sIndex.resize(indexCount);
            for(i = 0; i < indexCount; i++)
            {
                for(j = 0; j < indexMapSize; j++)
                {
                    indexVec[j] = indexPtr->getValue(i * indexMapSize + j);
                }

                sIndex[i] = indexDic.entry(indexVec);
            }

            vCount = indexDic.entryCount();
        }
        else
            vCount = 0;

        // sort/copy property values
        finalMask = 0;
        if(vCount)
        {
            for(i = 0; i < indexMapSize; i++)
            {
                mask = geoPtr->getIndexMapping()[i];
                for(maskID = 1; maskID; maskID <<= 1)
                {
                    if((mask & maskID) && (pP = geoPtr->getProperty(maskID)))
                    {
                        valueSize = pP->getFormatSize() *
                            pP->getDimension() +
                            pP->getStride();
                        finalMask |= maskID;
                        memSize = pP->size() * valueSize;
                        data = new UInt8[memSize];
                        pData = pP->getData();
                        memcpy(data, pData, memSize);
                        pP->resize(vCount);
                        pData = pP->getData();
                        for(j = 0; j < vCount; j++)
                        {
                            index = indexDic.entry(j)[i];
                            memcpy(pData + (valueSize * j),
                                                               data + (valueSize * index),
                                                               valueSize);
                        }

                        delete[] data;
                    }
                }
            }
        }

        // copy single index and set the single mask
        if(finalMask)
        {
            indexPtr->clear();
            for(i = 0; i < indexCount; i++)
            {
                indexPtr->push_back(sIndex[i]);
            }

            geoPtr->getIndexMapping().clear();
            geoPtr->getIndexMapping().push_back(finalMask);
        }
        else
        {
            FWARNING(("No valid finalMask in createSingleIndex()\n"));
        }

        endEditCP(geoPtr, Geometry::IndexMappingFieldMask |
                          Geometry::IndicesFieldMask);
    }

    return vCount;

#else
    FFATAL(("Cannot run createSingleIndex: NO_GEO_INFACE\n"));
    return -1;
#endif
}


/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcPrimitiveCount calculates some statistical information about the
    Geometry, see \ref
    PageSystemGeoFunctionsOptimizeGeo for a description.
    
    It returns the sum of the primitives found, and the separate counts in teh
    passed-in references.
*/
OSG_SYSTEMLIB_DLLMAPPING UInt32 OSG::calcPrimitiveCount(GeometryPtr geoPtr,
                                                        UInt32 &triangle,
                                                        UInt32 &line,
                                                        UInt32 &point)
{
    GeoPTypesUI8Ptr geoTypePtr;
    GeoPLengthsUI32Ptr lens32Ptr;
    GeoPLengthsUI16Ptr lens16Ptr;
    GeoPTypesUI8Ptr::StoredObjectType::StoredFieldType::iterator typeI, endTypeI;
    GeoPLengthsUI32Ptr::StoredObjectType::StoredFieldType::iterator len32I;
    GeoPLengthsUI16Ptr::StoredObjectType::StoredFieldType::iterator len16I;

    UInt32 lN, tN, len, type;

    // TODO; should we really reset the values ?
    triangle = line = point = 0;

    if(geoPtr == OSG::NullFC)
    {
        FINFO(("No geo in calcPrimitiveCount\n"));
    }
    else
    {
        lens32Ptr = GeoPLengthsUI32Ptr::dcast(geoPtr->getLengths());
    
        if(lens32Ptr == NullFC)
        {
            lens16Ptr = GeoPLengthsUI16Ptr::dcast(geoPtr->getLengths());
            lN = (lens16Ptr == OSG::NullFC) ? 0 : lens16Ptr->getSize();
        }
        else
        {
            lN = (lens32Ptr == OSG::NullFC) ? 0 : lens32Ptr->getSize();
        }

        geoTypePtr = GeoPTypesUI8Ptr::dcast(geoPtr->getTypes());
        tN = (geoTypePtr == OSG::NullFC) ? 0 : geoTypePtr->getSize();

        if((tN == 0) || (lN != 0 && tN != lN) || (lN == 0 && tN != 1))
        {
            return 0;
        }

        typeI = geoTypePtr->getField().begin();
        if(lN != 0)
        {
            if(lens32Ptr != NullFC)
                len32I = lens32Ptr->getField().begin();
            else
                len16I = lens16Ptr->getField().begin();
        }

        endTypeI = geoTypePtr->getField().end();
        while(typeI != endTypeI)
        {
            type = *typeI;
            if(lN != 0)
            {
                if(lens32Ptr != NullFC)
                    len = *len32I;
                else
                    len = *len16I;
            }
            else
            {
                GeoPositionsPtr pos = geoPtr->getPositions();

                if(pos == OSG::NullFC)
                {
                    FINFO(("calcPrimitiveCount: no Points!\n"));
                    return 0;
                }

                len = pos->size();
            }

            switch(type)
            {
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
                FWARNING(("calcPrimitiveCount(): Invalid geoType: %d\n", type));
                break;
            }

            ++typeI;
			if (lN > 0)
			{
				if(lens32Ptr != NullFC)
					++len32I;
				else if(lens16Ptr != NullFC)
					++len16I;
			}
        }
    }

    return triangle + line + point;
}



/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcVertexNormalsGeo creates a geometry object that shows the \a geo's
    normals, see \ref PageSystemGeoFunctionsShowNormals for a description.

    \a geo is the geometry whose normals should be displayed, \a length is the
    length of the normals. The new geometry is created in the local coordinate
    system of \a geo.    
*/

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr OSG::calcVertexNormalsGeo(GeometryPtr geo, Real32 length)
{
    GeoPositions3f::PtrType pnts = GeoPositions3f::create();
    // calculate
    beginEditCP(pnts);

    PrimitiveIterator   pi(geo);

    if(1 /* no easy way to check right now */ )
    {
        for(pi = geo->beginPrimitives(); pi != geo->endPrimitives(); ++pi)
        {
            for(UInt32 k = 0; k < pi.getLength(); k++)
            {
                pnts->push_back(pi.getPosition(k));
                pnts->push_back(pi.getPosition(k) + length * pi.getNormal(k));
            }
        }
    }
    else
    {
        Pnt3f   center(0, 0, 0);

        for(pi = geo->beginPrimitives(); pi != geo->endPrimitives(); ++pi)
        {
            for(UInt32 k = 0; k < pi.getLength(); k++)
            {
                center[0] += pi.getPosition(k)[0];
                center[1] += pi.getPosition(k)[1];
                center[2] += pi.getPosition(k)[2];
            }

            pnts->push_back(center);
            pnts->push_back(center + length * pi.getNormal(0));
        }
    }

    endEditCP(pnts);

    GeoPTypesPtr type = GeoPTypesUI8::create();
    beginEditCP(type);
    type->push_back(GL_LINES);
    endEditCP(type);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();
    beginEditCP(lens);
    lens->push_back(pnts->getSize());
    endEditCP(lens);

    GeometryPtr g = Geometry::create();
    beginEditCP(g);
    g->setTypes(type);
    g->setLengths(lens);
    g->setPositions(pnts);
    endEditCP(g);

    return makeNodeFor(g);
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    calcFaceNormalsGeo creates a geometry object that shows the \a geo's
    normals, see \ref PageSystemGeoFunctionsShowNormals for a description.

    \a geo is the geometry whose normals should be displayed, \a length is the
    length of the normals. The new geometry is created in the local coordinate
    system of \a geo.    
*/

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr OSG::calcFaceNormalsGeo(GeometryPtr geo, Real32 length)
{
    NodePtr p = Node::create();
    GeometryPtr g = Geometry::create();
    GeoPositions3f::PtrType pnts = GeoPositions3f::create();
    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
    GeoPTypesPtr type = GeoPTypesUI8::create();
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();

    // calculate
    FaceIterator faceIter = geo->beginFaces();
    Pnt3f center;

    beginEditCP(pnts);
    for(; faceIter != geo->endFaces(); ++faceIter)
    {
        center[0] = 0;
        center[1] = 0;
        center[2] = 0;
        for(UInt16 i = 0; i < faceIter.getLength(); ++i)
        {
            center[0] += faceIter.getPosition(i)[0] / faceIter.getLength();
            center[1] += faceIter.getPosition(i)[1] / faceIter.getLength();
            center[2] += faceIter.getPosition(i)[2] / faceIter.getLength();
        }

        pnts->push_back(center);
        switch(faceIter.getType())
        {
        case GL_TRIANGLE_STRIP:
            pnts->push_back(center + length * faceIter.getNormal(2));
            break;
        case GL_TRIANGLE_FAN:
            pnts->push_back(center + length * faceIter.getNormal(2));
            break;
        case GL_QUAD_STRIP:
            pnts->push_back(center + length * faceIter.getNormal(3));
            break;
        default:
            //does not matter which point's normal
            pnts->push_back(center + length * faceIter.getNormal(0));
            break;
        }
    }

    endEditCP(pnts);

    beginEditCP(index);
    for(UInt32 i = 0; i < pnts->getSize(); i++)
        index->push_back(i);
    endEditCP(index);

    beginEditCP(type);
    type->push_back(GL_LINES);
    endEditCP(type);

    beginEditCP(lens);
    lens->push_back(index->getSize());
    endEditCP(lens);

    beginEditCP(g);
    g->setTypes(type);
    g->setLengths(lens);
    g->setIndices(index);
    g->setPositions(pnts);
    endEditCP(g);

    beginEditCP(p);
    p->setCore(g);
    endEditCP(p);

    return p;
}

// keep out of the doc right now, doesn't work yet!

#if !defined(OSG_DO_DOC)
OSG_SYSTEMLIB_DLLMAPPING void OSG::mergeGeometries(std::vector<NodePtr> &nodes,
                                                   std::vector<NodePtr> &results)
{
    FFATAL(("Merge Geometries: Not implemented yet!\n"));
    results.clear();

    for(std::vector < NodePtr >::iterator n = nodes.begin(); n != nodes.end();
            ++n)
    {
        GeometryPtr actnode = GeometryPtr::dcast((*n)->getCore());

        if(actnode == NullFC)
        {
            FWARNING(("mergeGeometries: core of 0x%p is not a geometry!\n", n->
                                     getCPtr()));
            continue;
        }

        std::vector < NodePtr >::iterator r;
        for(r = nodes.begin(); r != nodes.end(); ++r)
        {
            GeometryPtr res = GeometryPtr::dcast((*r)->getCore());

            if(res->isMergeable(actnode))
            {
                res->merge(actnode);
            }
        }

        if(r == nodes.end())
        {
            // need a new one
            NodePtr node = Node::create();

            beginEditCP(node);
            node->setCore(actnode->clone());
            endEditCP(node);

            results.push_back(node);
        }
    }
}
#endif

#define separateProperty(TypeT, Type) \
    Geo ## TypeT ## Ptr Type = geo->get ## Type (); \
    if(Type != NullFC && Type->getParents().size() > 1) \
    { \
        beginEditCP(geo, Geometry :: Type ## FieldMask); \
            geo->set ## Type (Geo ## TypeT ## Ptr::dcast(OSG::deepClone(Type))); \
        endEditCP(geo, Geometry :: Type ## FieldMask); \
    }

/*! \ingroup GrpSystemDrawablesGeometryFunctions

    Separates shared geometry properties.
*/

OSG_SYSTEMLIB_DLLMAPPING void OSG::separateProperties(GeometryPtr geo)
{
    separateProperty(PTypes, Types)
    separateProperty(PLengths, Lengths)
    separateProperty(Positions, Positions)
    separateProperty(Normals, Normals)
    separateProperty(Colors, Colors)
    separateProperty(Colors, SecondaryColors)
    separateProperty(TexCoords, TexCoords)
    separateProperty(TexCoords, TexCoords1)
    separateProperty(TexCoords, TexCoords2)
    separateProperty(TexCoords, TexCoords3)
    separateProperty(TexCoords, TexCoords4)
    separateProperty(TexCoords, TexCoords5)
    separateProperty(TexCoords, TexCoords6)
    separateProperty(TexCoords, TexCoords7)
    separateProperty(Indices, Indices)
}
