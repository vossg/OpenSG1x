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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGLog.h>

#include "OSGGeometry.h"
#include "OSGGeoPropPtrs.h"
#include "OSGTriangleIterator.h"
#include "OSGGeoFunctions.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: OSGGeoFunctions.cpp,v 1.8 2001/07/29 17:57:20 vossg Exp $";

#ifdef __sgi
#pragma reset woff 1174
#endif



/*! \ingroup Geometry
	\param geo	the geometry to work on

calcVertexNormals calculates the normals for the geometry's vertices. It
does this simply by accumulating the face normals of all triangles that
use the vertex and renormalizing. 

*/

OSG_SYSTEMLIB_DLLMAPPING
void osg::calcVertexNormals( GeometryPtr geo )
{
	GeoNormalPtr norms;
    int          i;

	if ( geo->getNormals() == GeoNormal3fPtr::NullPtr )
	{
		norms = GeoNormal3f::create();
	}
	else
		norms = geo->getNormals();
	
	beginEditCP(norms);

	norms->resize( geo->getPositions()->getSize() );

	for ( i = 0; i < geo->getPositions()->getSize(); i++ )
	{
		norms->setValue( Vec3f( 0,0,0 ), i );
	}

	for ( TriangleIterator t = geo->beginTriangles(); t != geo->endTriangles(); ++t )
	{
		Plane p( t.getPosition(0), t.getPosition(1), t.getPosition(2) );
		
		norms->setValue( norms->getValue( t.getPositionIndex(0) ) + p.getNormal(), 
						 t.getPositionIndex(0) ); 
		norms->setValue( norms->getValue( t.getPositionIndex(1) ) + p.getNormal(), 
						 t.getPositionIndex(1) ); 
		norms->setValue( norms->getValue( t.getPositionIndex(2) ) + p.getNormal(), 
						 t.getPositionIndex(2) ); 
	}

	for ( i = 0; i < geo->getPositions()->getSize(); i++ )
	{
		Vec3f n = norms->getValue( i );
		n.normalize();
		norms->setValue( n, i );
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
        
            if ( ni )
                im.setValue( im.getValue(ni) & ~ Geometry::MapNormal, ni );
            if ( pi >= 0 )
                im.setValue( im.getValue(pi) |   Geometry::MapNormal, pi );
        }    
    }
	endEditCP( geo );

}


/*! \ingroup Geometry
	\param geo		the geometry to work on
	\param length	the length of the normal vectors

getNormals creates a geometry that consists of the normals of \a geo
as lines. Every line starts of the position the normals is associated
with (vertex for vertex normals, center of face for face normals) and
has the length \a length.

*/
OSG_SYSTEMLIB_DLLMAPPING NodePtr osg::getNormals(GeometryPtr geo, 
                                                 Real32      length)
{
    NodePtr  p = Node::create();
    GeometryPtr g = Geometry::create();
	GeoPosition3f::PtrType pnts = GeoPosition3f::create();
	GeoIndexUI32Ptr index = GeoIndexUI32::create();	
	GeoPTypePtr type = GeoPType::create();	
	GeoPLengthPtr lens = GeoPLength::create();	

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
				pnts->addValue( pi.getPosition( k ) );
				pnts->addValue( pi.getPosition( k ) + 
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
			pnts->addValue( center );
			pnts->addValue( center +  length * pi.getNormal( 0 ) );
		}
	}

	endEditCP(pnts);
	
	// create the geometry
	beginEditCP(index);
	for ( UInt32 i = 0; i < pnts->getSize(); i++ )
		index->addValue( i );
	endEditCP(index);

	beginEditCP(type);
	type->addValue( GL_LINES );
	endEditCP(type);

	beginEditCP(lens);
	lens->addValue( index->getSize() );
	endEditCP(lens);
	
	beginEditCP(g);
	g->setTypes( type );
	g->setLengths( lens );
	g->setIndex( index );
	g->setPositions( pnts );
	endEditCP(g);
	
	beginEditCP(p);
	p->setCore(g);
	endEditCP(p);
	
	return p;
}



/*! \brief create the geometry index form the given FaceSet (VRML style) data 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING 
Int32 osg::setIndexFromVRMLData ( GeometryPtr geoPtr, 
                                  vector<Int32> coordIndex,
                                  vector<Int32> normalIndex,
                                  vector<Int32> colorIndex,
                                  vector<Int32> texCoordIndex,
                                  Bool convex, 
                                  Bool ccw,
                                  Bool normalPerVertex,
                                  Bool colorPerVertex,
                                  Bool faceSet )
{
    /** define the bag type */
    typedef vector<Int32>* IndexBagP;

  /** defines the Index Types */
    enum IndexType { UNKNOWN_IT = 0,
                     EMPTY_IT,
                     VERTEX_COORD_IT, VERTEX_IT, VERTEX_DUP_IT,
                     PRIMITIVE_IT, PRIMITIVE_INDEX_IT
    };
  
    /** holds the Index types as str, mainly for log/debug outputs */
    static const char *indexTypeStr[] = {
        "UNKNOWN_IT", "EMPTY_IT",
        "VERTEX_COORD_IT", "VERTEX_IT", "VERTEX_DUP_IT",
        "PRIMTIVE_IT", "PRIMITIVE_INDEX_IT"
    };

    osg::GeoPositionPtr posPtr;
    osg::GeoNormalPtr normalPtr;
    osg::GeoColorPtr colorPtr;
    osg::GeoTexCoordsPtr texCoordsPtr;
    osg::GeoPLengthPtr lensPtr;
    osg::GeoPTypePtr geoTypePtr;
    osg::GeoIndexPtr indexPtr;

    Int32 index, i, pi, typei, mapi, primitiveN = 0, vN = 0, pType = 0;
    Int32 maxPType = (faceSet ? 5 : 3);
    Int32 beginIndex, endIndex, len, sysPType = 0;
    Int32 piN = 0, ciN = 0, niN = 0, tiN = 0;
    Int32 pN = 0, nN = 0, cN = 0, tN = 0;
    IndexType indexType[4];
//  IndexType &coordIT = indexType[0];
    IndexType &normalIT = indexType[1];
    IndexType &colorIT = indexType[2];
    IndexType &textureIT = indexType[3];
    Int32 primitiveTypeCount[6];
    UInt32 triCount = 0;
    Int16 indexMap[4], indexMapID[4];
    IndexBagP indexBag[4] = { &coordIndex, &normalIndex,
                              &colorIndex, &texCoordIndex };

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

    //----------------------------------------------------------------------
    // check the vertex index and count the primitives
    primitiveN = index = 0;
    for (pType = 0; pType <= maxPType; pType++)
        primitiveTypeCount[pType] = 0;

    if (!pN) {
        FWARNING (("No points in osg::setIndexFromVRMLData()"));
    }
    else {
        piN = coordIndex.size();
        for ( i = 0; i < piN; i++) {
            if ( ((index = coordIndex[i]) < 0 ) || (vN && (i == piN)) ) {
                primitiveTypeCount [ (vN > maxPType) ? maxPType : vN]++;
                primitiveN++;
                vN = 0;
            }
            else {
                if (index >= pN) {
                    FWARNING (("Point index (%d/%d) out of range", index, pN));
                    coordIndex[i] = 0;
                }
                vN++;
            }
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
    else 
        normalIT = EMPTY_IT;    

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
        FLOG (( "primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d 4/%d poly/%d\n",
                primitiveN,
                primitiveTypeCount[0], 
                primitiveTypeCount[1], 
                primitiveTypeCount[2],
                primitiveTypeCount[3], 
                primitiveTypeCount[4], 
                primitiveTypeCount[5] ));
    }
    else {
        FLOG (( "primitiveN:  %d, 0/%d 1/%d 2/%d 3/%d\n",
                primitiveN,
                primitiveTypeCount[0], 
                primitiveTypeCount[1], 
                primitiveTypeCount[2],
                primitiveTypeCount[3] ));
    }


    FLOG (( "IndexType: color: %s, normal: %s, texture: %s \n", 
            indexTypeStr[colorIT], indexTypeStr[normalIT],
            indexTypeStr[textureIT] ));

    //----------------------------------------------------------------------
    // check/create the indexPtr/lengthsPtr/geoTypePtr
    indexPtr = geoPtr->getIndex();
    if (indexPtr == osg::NullFC)
        indexPtr = osg::GeoIndexUI32::create();
    else
        indexPtr->clear();
  
    lensPtr = geoPtr->getLengths();
    if (lensPtr == osg::NullFC)
        lensPtr = osg::GeoPLength::create();
    else
        lensPtr->clear();
  
    geoTypePtr = geoPtr->getTypes();
    if (geoTypePtr == osg::NullFC)
        geoTypePtr = osg::GeoPType::create();
    else
        geoTypePtr->clear();

  //----------------------------------------------------------------------
  // create the index mapping
    indexMapID[0] = Geometry::MapPosition;
    indexMapID[1] = Geometry::MapNormal;
    indexMapID[2] = Geometry::MapColor;
    indexMapID[3] = Geometry::MapTexcoords;
    indexMap[0] = Geometry::MapPosition;
    indexType[0] = VERTEX_IT;
    for (mapi = i = 1; i <= 3; i++) {
        indexMap[i] = 0;
        switch (indexType[i]) {
            case UNKNOWN_IT:
            case EMPTY_IT:
                break;
            case VERTEX_COORD_IT:
            case VERTEX_DUP_IT:
                indexMap[0] |= indexMapID[i];
                break;
            case VERTEX_IT:
            case PRIMITIVE_IT:
            case PRIMITIVE_INDEX_IT:
                indexMap[mapi++] = indexMapID[i];
                break;
        }
    }
  
    //----------------------------------------------------------------------
    // set lens/geoType/index/mapping the index mapping  
    osg::beginEditCP(geoPtr);
    {
        geoPtr->setLengths(lensPtr);
        geoPtr->setTypes(geoTypePtr);
        geoPtr->setIndex(indexPtr);
        geoPtr->getIndexMapping().clear();
        // check for multiindex mapping 
        if (indexMap[1]) 
            for (i = 0; ((i <= 3) && indexMap[i]); i++)
                geoPtr->getIndexMapping().addValue( indexMap[i] );
    }
    osg::endEditCP(geoPtr);
  
  //----------------------------------------------------------------------
  // create index face/line data
    for (pType = (faceSet ? 3 : 2); pType <= maxPType; pType++) {
    
        if (primitiveTypeCount[pType]) {

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

            if (sysPType) {
                osg::beginEditCP(lensPtr);
                {
                    lensPtr->getFieldPtr()->addValue(len);
                }
                osg::endEditCP (lensPtr);
        
                osg::beginEditCP (geoTypePtr);
                {
                    geoTypePtr->getFieldPtr()->addValue( sysPType );
                }
                osg::endEditCP (geoTypePtr);        
            }
      
            primitiveN = 0;
            beginIndex = endIndex = -1;
            for ( i = 0; i <= piN; i++) {
                if ( ((coordIndex[i]) < 0 ) || (i == piN) ) {
                    endIndex = i;
                    len = endIndex - beginIndex;
                    if ((beginIndex >= 0) && (len == pType)) {
            
                        if (len >= maxPType) {
                            sysPType = faceSet ? GL_POLYGON : GL_LINE_STRIP;
                            osg::beginEditCP(lensPtr);
                            {
                                lensPtr->getFieldPtr()->addValue(len);
                            }
                            osg::endEditCP (lensPtr);
                            osg::beginEditCP (geoTypePtr);
                            {
                                geoTypePtr->getFieldPtr()->addValue( sysPType );
                            }
                            osg::beginEditCP (geoTypePtr);
                        }
            
                        // add index data
                        for (pi = beginIndex; pi < endIndex; pi++) {
                            indexPtr->addValue(coordIndex[pi]);
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
                                        }
                                        indexPtr->addValue(index);
                                    }
                                }
                            }
                        }
            
                        triCount += len - 2;
                        primitiveN++;
                    }
                    beginIndex = endIndex = -1;
                }
                else 
                    if (beginIndex < 0)
                        beginIndex = i;
            }
        }
    }

    return triCount;
}
