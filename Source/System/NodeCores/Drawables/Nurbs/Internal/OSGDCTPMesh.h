/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2004 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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
#ifndef _OSG_DCTPMESH_H_
#define _OSG_DCTPMESH_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNurbsDef.h"
#include <OSGConfig.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <vector>

#include "OSGdctptypes.h"

#include "OSGDCTPFace.h"
#include "OSGDCTPEdge.h"
#include "OSGDCTPVertex.h"

OSG_BEGIN_NAMESPACE

class OSG_NURBSLIB_DLLMAPPING DCTPMesh {
public:
  DCTPMesh();
  ~DCTPMesh();

  DCTPVertex *AddVertex( vec3d v );
  DCTPEdge *AddEdge( DCTPVertex *v1, DCTPVertex *v2, int orient );
  DCTPFace *AddFace( void );
  int AddTriangle( vec3d v1, vec3d v2, vec3d v3, double norm );
  int AddQuadTreeLeaf( vec3d ul, vec3d lr, bool *sides, double norm );
  DCTPFace *AddQuad( vec3d v1, vec3d v2, vec3d v3, vec3d v4, double norm );
  int SubdivideQuad( DCTPFace *f );
  int SubdivideQuadNS( DCTPFace *f );
  int SubdivideQuadEW( DCTPFace *f );
  int SubdivideQuadNS( DCTPFace *f, double dRatio );
  int SubdivideQuadEW( DCTPFace *f, double dRatio );
  DCTPVertex * SplitEdge( DCTPEdge *edge, double t );
  DCTPVertex * SplitEdge( DCTPEdge *edge, const vec3d& p );
#ifndef OSG_INTEGER_MESH
  int SplitFace( DCTPEdge *edge, vec3dvector &points, dctpvertexvector &res );
  DCTPVertex * SplitFace( DCTPEdge *edge, const vec3d& p );
  void SplitOneFace( DCTPFace *f, DCTPEdge *edge, DCTPVertex *nv);
#endif
  int MoveVertex( DCTPVertex *vert, vec3d &newpos );
  void dump( char *fname );
  int write( std::ofstream &);
  void writeInvalid( std::ofstream &);
  bool isInvalid( void ); // whether the current mesh is invalid
  int read( std::ifstream &infile );
#ifdef OSG_INTEGER_MESH
  int directEdge( vec3i& from, vec3i& into );
#else
  int directEdge( vec3d& from, vec3d& into );
#endif
  DCTPVertex *findVertex( const vec3d& v );
  DCTPEdge *findEdge( const vec3d &vc1, const vec3d &vc2 );
  DCTPEdge *findEdge( DCTPVertex *v1, DCTPVertex *v2 );
  int write_trisoup( std::ofstream &outfile );
  int write_quadsoup( std::ofstream &outfile );
  int read_trisoup( std::ifstream &infile );  
  int read_quadsoup( std::ifstream &infile );  
  unsigned long getNumOfVertices( void );
  unsigned long getNumOfFaces( void );
  void reinit( void );
  double computeEdgePointDst( DCTPEdge *edg, vec3d& pnt );

  void removeFace( unsigned int ui_face );

  //file format constants
  static const char ff_const_1[];
  static const char ff_const_2[];
      
      
private:
public:

  dctpvertexset vertices;
#ifdef OSG_NO_EDGE_SET
  dctpedgevector edges;
#else
  dctpedgeset edges;
#endif
  dctpfacevector faces;
protected:
  int AddQuadSide( DCTPVertex *l, DCTPVertex *r, DCTPVertex *m, DCTPFace *nf );
  void setupSides( DCTPFace *f, std::vector< DCTPVertex * > * sides, double dXRatio, double dYRatio );
  void sortSides( DCTPFace *f, std::vector< DCTPVertex * > * sides );
  DCTPEdge *getEdgeFromFace(DCTPFace *f, DCTPVertex *v1, DCTPVertex *v2);
  void buildNewFaces( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp, DCTPVertex *wp, DCTPVertex *ep);
  void buildNewFacesNS( DCTPFace *f, DCTPVertex *wp, DCTPVertex *ep);
  void buildNewFacesEW( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp);
  void buildNewFacesNS( DCTPFace *f, DCTPVertex *wp, DCTPVertex *ep, double dRatio);
  void buildNewFacesEW( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp, double dRatio);
  DCTPFace *buildQuadFace( std::vector< DCTPVertex * > &verts, DCTPFace *f );
  unsigned long vertex_count;
  unsigned long edge_count;
  unsigned long face_count;  
  bool invalid; // true if no mesh loaded or invalid (null) mesh read from file
};

struct sortnorth 
{
  bool operator()( DCTPVertex *v1, DCTPVertex *v2 ) 
  {
    return ( v1->coords.x < v2->coords.x );
  }
};

struct sortsouth 
{
  bool operator()( DCTPVertex *v1, DCTPVertex *v2 ) 
  {
    return ( v1->coords.x > v2->coords.x );
  }
};

struct sorteast
{
  bool operator()( DCTPVertex *v1, DCTPVertex *v2 ) 
  {
    return ( v1->coords.y > v2->coords.y );
  }
};

struct sortwest
{
  bool operator()( DCTPVertex *v1, DCTPVertex *v2 ) 
  {
    return ( v1->coords.y < v2->coords.y );
  }
};

typedef std::vector< DCTPMesh * > mesh_vector;

OSG_END_NAMESPACE

#endif // DCTPMesh.h
