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
#ifdef WIN32
#	pragma warning (disable : 985)
#endif
#include "OSGDCTPMesh.h"

OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char DCTPMesh::ff_const_1[]="BEGINTRIANGLESOUP";
  const char DCTPMesh::ff_const_2[]="BEGINQUADSOUP";

DCTPMesh::DCTPMesh()
{
  vertex_count = 0;
  edge_count = 0;
  face_count = 0;
  invalid = true;
}

DCTPMesh::~DCTPMesh()
{
  dctpvertexset::iterator vend = vertices.end();
#ifdef OSG_NO_EDGE_SET
  dctpedgevector::iterator eend = edges.end();
#else
  dctpedgeset::iterator eend = edges.end();
#endif
  dctpfacevector::iterator fend = faces.end();

  for ( dctpvertexset::iterator i1 = vertices.begin(); i1 != vend; ++i1 ) {
    delete *i1;
  }
#ifdef OSG_NO_EDGE_SET
  for ( dctpedgevector::iterator i2 = edges.begin(); i2 != eend; ++i2 )
#else
  for ( dctpedgeset::iterator i2 = edges.begin(); i2 != eend; ++i2 )
#endif
  {
    delete *i2;
  }
  for ( dctpfacevector::iterator i3 = faces.begin(); i3 != fend; ++i3 ) {
    delete *i3;
  }
}

DCTPVertex *DCTPMesh::AddVertex( vec3d v )
{
  DCTPVertex *nv = new DCTPVertex;
  if ( !nv ) return nv;
  invalid = false;
  nv->coords = v;

  std::pair< dctpvertexset::iterator, bool > siv;
  siv = vertices.insert( nv );
  if ( !siv.second ) {
//    std::cerr << "AddVertex: already in: " << v << std::endl;
    delete nv;
    nv = *(siv.first);
  }
  else {
//    std::cerr << "AddVertex: adding vx.: " << v << std::endl;
    nv->id = vertex_count++;
  }
  return nv;
}

#ifdef OSG_INTEGER_MESH
int DCTPMesh::directEdge( vec3i& from, vec3i& into ) {
#else
int DCTPMesh::directEdge( vec3d& from, vec3d& into ) {
#endif
        DCTPVertex *from_vp = new DCTPVertex;
        DCTPVertex *into_vp = new DCTPVertex;
        if ( !from_vp || !into_vp ) {
                std::cerr << "Not enuf memory!" << std::endl;
                return -2;
        }
        from_vp->coords = from;
        into_vp->coords = into;

//        std::cerr << "directEdge in... coords: " << from << " " << into  << std::endl;
        dctpvertexset::iterator v1,v2, vend = vertices.end(); v1 =
        vertices.find( from_vp ); if ( v1 == vend ) {
          delete from_vp;
          delete into_vp;
          return -1;
        }
        v2 = vertices.find( into_vp );
        if ( v2 == vend ) {
          delete from_vp;
          delete into_vp;
          return -1;
        }
//        std::cerr << "still directEdge..." << std::endl;
//        std::cerr.precision( DCTP_PRECISION );
//        std::cerr << "v1->coords: " << (*v1)->coords << " v2->coords: " << (*v2)->coords << std::endl;
        delete from_vp;
        delete into_vp;
        std::vector< DCTPEdge* >::iterator eend = (*v1)->edges.end();
        for( std::vector< DCTPEdge* >::iterator i = (*v1)->edges.begin(); i != eend; ++i ) {
                DCTPVertex *tv1, *tv2;
                (*i)->getVertices( tv1, tv2 );
                if ( tv1->coords == (*v1)->coords && tv2->coords == (*v2)->coords ) {
						++(*i)->orientation;
                        return 0;
                }
                if ( tv1->coords == (*v2)->coords && tv2->coords == (*v1)->coords ) {
	                    --(*i)->orientation;
                        return 0;
                }
        }
        return -1;
}

DCTPEdge *DCTPMesh::AddEdge( DCTPVertex *v1, DCTPVertex *v2, int orient )
{
#ifdef OSG_NO_EDGE_SET
	DCTPEdge			*pcl_edge;
	const unsigned int	cui_edge_cnt = v1->edges.size( );
	unsigned int		ui_edge;
	DCTPVertex			*pcl_ev1;
	DCTPVertex			*pcl_ev2;

	for( ui_edge = 0; ui_edge < cui_edge_cnt; ++ui_edge )
	{
		pcl_edge = v1->edges[ ui_edge ];
		pcl_edge->getVertices( pcl_ev1, pcl_ev2 );
		if( ( v2 == pcl_ev1 ) || ( v2 == pcl_ev2 ) )
		{
			return pcl_edge;
		}
	}

	invalid = false;
	pcl_edge = new DCTPEdge( v1, v2, orient );
//	std::cerr << "4-" << pcl_edge << " " << v1 << " " << v2 << std::endl;
	v1->edges.push_back( pcl_edge );
	v2->edges.push_back( pcl_edge );
	edges.push_back( pcl_edge );

	return pcl_edge;
#else
  DCTPEdge *ne = new DCTPEdge( v1, v2, orient );
  if ( !ne ) return ne;

  invalid = false;
  std::pair< dctpedgeset::iterator, bool > sie;
//  bool newas = false;
/*
  dctpedgeset::iterator ee = edges.end();
  for (dctpedgeset::iterator i = edges.begin(); i !=ee; ++i ) {
    DCTPVertex *tt1, *tt2;
    (*i)->getVertices( tt1, tt2 );
    std::cerr << "edgeid: " << (*i)->id << " v1: " << (void*) tt1 << " " << (void*) tt2
    << std::endl;
  }
*/
  sie = edges.insert( ne );
  if ( !sie.second ) {
    delete ne;
	return *(sie.first);
//    ne = *(sie.first);  
//    newas = true;
  }
  else {
//    DCTPVertex *zz1, *zz2;
//    ne->getVertices( zz1, zz2 );
//    std::cerr << "Inserting new edge: " << (void*) zz1 << " " << (void*) zz2;
//    std::cerr << " with coords: " << v1->coords << " " << v2->coords << std::endl;
    ne->id = edge_count++;
//  }
//  if ( !newas ) { 
     v1->edges.push_back( ne );
     v2->edges.push_back( ne );
  }

  return ne;
#endif
}


DCTPFace *DCTPMesh::AddFace( void )
{
  DCTPFace *nf = new DCTPFace;
  if ( !nf ) return NULL;
  invalid = false;
  nf->id = face_count++;
  faces.push_back ( nf );

  return nf;
}

int DCTPMesh::AddTriangle( vec3d v1, vec3d v2, vec3d v3, double norm )
{
  DCTPVertex *nv1 = AddVertex( v1 );
  DCTPVertex *nv2 = AddVertex( v2 );
  DCTPVertex *nv3 = AddVertex( v3 );
  if ( !nv1 || !nv2 || !nv3 ) return -1;

  DCTPEdge *ne1 = AddEdge( nv1, nv2, 0 );
  DCTPEdge *ne2 = AddEdge( nv2, nv3, 0 );
  DCTPEdge *ne3 = AddEdge( nv3, nv1, 0 );
  if ( !ne1 || !ne2 || !ne3 ) return -1;

  DCTPFace *nf = AddFace();
  if ( !nf ) return -1;

  invalid = false;
  //do this here, to be able to dump valid data in DCTPEdge::AddFace
#ifdef OSG_UNION_TRI_QUAD
  nf->orig_face[ 0 ] = nv1;
  nf->orig_face[ 1 ] = nv2;
  nf->orig_face[ 2 ] = nv3;
  nf->orig_face[ 3 ] = NULL;
#else
  nf->orig_triangle[ 0 ] = nv1;
  nf->orig_triangle[ 1 ] = nv2;
  nf->orig_triangle[ 2 ] = nv3;
  // FIXME: is it really necessary? Any other (better) way to distinguish
  // FIXME: between triangle and quad faces?
  nf->orig_quad[ 0 ] = NULL;
  nf->orig_quad[ 1 ] = NULL;
  nf->orig_quad[ 2 ] = NULL;
  nf->orig_quad[ 3 ] = NULL;
#endif
  nf->norm = norm;

  ne1->AddFace( nf );
  ne2->AddFace( nf );
  ne3->AddFace( nf );

  nv1->faces.push_back( nf );
  nv2->faces.push_back( nf );
  nv3->faces.push_back( nf );

  nf->vertices.push_back( nv1 );
  nf->vertices.push_back( nv2 );
  nf->vertices.push_back( nv3 );
  nf->edges.push_back( ne1 );
  nf->edges.push_back( ne2 );
  nf->edges.push_back( ne3 );

  return 0;
}

int DCTPMesh::AddQuadSide( DCTPVertex *l, DCTPVertex *r, DCTPVertex *m, DCTPFace *nf )
{
  if ( m ) {
    DCTPEdge *ue1 = AddEdge( l, m, 0 );
    DCTPEdge *ue2 = AddEdge( m, r, 0 );
    if ( !ue1 || !ue2 ) return -1;
    ue1->AddFace( nf );
    ue2->AddFace( nf );
    nf->edges.push_back( ue1 );
    nf->edges.push_back( ue2 );
    l->faces.push_back( nf );
    m->faces.push_back( nf );
    r->faces.push_back( nf );
  }
  else {
    DCTPEdge *ue = AddEdge( l, r, 0 );
    if ( !ue ) return -1;
    ue->AddFace( nf );
    nf->edges.push_back( ue );
    l->faces.push_back( nf ); 
    r->faces.push_back( nf );
  }

  return 0;
}


/*  (nv1) ul   bool[0]   ur (nv2)
 *         X-----+-----X
 *         |           |
 *         |           |
 * bool[3] +           + bool[1]
 *         |           |
 *         |           |
 *         X-----+-----X
 *       ll   bool[2]   lr  (nv3)
 *  (nv4)                  (nv4)
 *
 *
 *  Note that this function adds vertices in clockwise order, i.e.
 *  nv1, nv,2 nv3, nv4 if there are no middle vertices.
 *
 *  Note that z coordinates are truncated to 0. This is essentially
 *  a 2D function using only (x, y) coords
 */
int DCTPMesh::AddQuadTreeLeaf( vec3d ul, vec3d lr, bool *sides, double norm )
{
  vec3d ur, ll;
  ur.x = lr.x; ur.y = ul.y; ur.z = 0.0;
  ll.x = ul.x; ll.y = lr.y; ll.z = 0.0;

  DCTPVertex *nv1 = AddVertex( ul );
  DCTPVertex *nv2 = AddVertex( ur );
  DCTPVertex *nv3 = AddVertex( lr );
  DCTPVertex *nv4 = AddVertex( ll );
  if ( !nv1 || !nv2 || !nv3 || !nv4 ) return -1;

  DCTPFace *nf = AddFace();
  if ( !nf ) return -1;

#ifdef OSG_UNION_TRI_QUAD
  nf->orig_face[ 0 ] = nv1;
  nf->orig_face[ 1 ] = nv2;
  nf->orig_face[ 2 ] = nv3;
  nf->orig_face[ 3 ] = nv4;
#else
  nf->orig_quad[ 0 ] = nv1;
  nf->orig_quad[ 1 ] = nv2;
  nf->orig_quad[ 2 ] = nv3;
  nf->orig_quad[ 3 ] = nv4;
  // FIXME: is it really necessary? Any other (better) way to distinguish
  // FIXME: between triangle and quad faces?
  nf->orig_triangle[ 0 ] = NULL;
  nf->orig_triangle[ 1 ] = NULL;
  nf->orig_triangle[ 2 ] = NULL;
#endif
  nf->norm = norm;

  if ( sides[ 0 ] ) {
    vec3d umv;
    umv.x = ( ur.x + ul.x ) / 2.0;
    umv.y = ur.y;
    umv.z = 0.0;
    DCTPVertex *um = AddVertex( umv );
    if ( !um ) return -1;
    AddQuadSide( nv1, nv2, um, nf );
    nf->vertices.push_back( nv1 ); // we have to add these here because
    nf->vertices.push_back( um ); // on subsequent sides we mustn't add
    nf->vertices.push_back( nv2 ); // some vertices in order to avoid duplications
  }
  else {
    AddQuadSide( nv1, nv2, NULL, nf );
    nf->vertices.push_back( nv1 ); // see comment above
    nf->vertices.push_back( nv2 );
  }
  if ( sides[ 1 ] ) {
    vec3d rmv;
    rmv.x = ur.x; 
    rmv.y = ( ur.y + lr.y ) / 2.0;
    rmv.z = 0.0;
    DCTPVertex *rm = AddVertex( rmv );
    if ( !rm ) return -1;
    AddQuadSide( nv2, nv3, rm, nf );
    nf->vertices.push_back( rm );  // we don't need to push nv2 !!!
    nf->vertices.push_back( nv3 );
  }
  else {
    AddQuadSide( nv2, nv3, NULL, nf );
    nf->vertices.push_back( nv3 ); // see comment above
  }
  if ( sides[ 2 ] ) {
    vec3d lmv;
    lmv.x = ( lr.x + ll.x ) / 2.0; 
    lmv.y = lr.y;
    lmv.z = 0.0;
    DCTPVertex *lm = AddVertex( lmv );
    if ( !lm ) return -1;
    AddQuadSide( nv3, nv4, lm, nf );
    nf->vertices.push_back( lm );  // we don't need to push nv3 !!!
    nf->vertices.push_back( nv4 );
  }
  else {
    AddQuadSide( nv3, nv4, NULL, nf );
    nf->vertices.push_back( nv4 ); // see comment above
  }
  if ( sides[ 3 ] ) {
    vec3d lemv;
    lemv.x = ll.x;
    lemv.y = ( ll.y + ul.y ) / 2.0;
    lemv.z = 0.0;
    DCTPVertex *lem = AddVertex( lemv );
    if ( !lem ) return -1;
    AddQuadSide( nv4, nv1, lem, nf );
    nf->vertices.push_back( lem );  // we don't need to push nv4 or nv1 !!!
  }
  else {
    AddQuadSide( nv4, nv1, NULL, nf );
  }
  return 0;
}

/* 
 * Note: in the SubdivideQuad() function we assume that the quads
 * were added this way:
 *
 * v1 .----. v2
 *    |    |
 * v4 `----' v3
 * 
 */
DCTPFace* DCTPMesh::AddQuad( vec3d v1, vec3d v2, vec3d v3, vec3d v4, double norm )
{
  DCTPVertex *nv1 = AddVertex( v1 );
  DCTPVertex *nv2 = AddVertex( v2 );
  DCTPVertex *nv3 = AddVertex( v3 );
  DCTPVertex *nv4 = AddVertex( v4 );
  if ( !nv1 || !nv2 || !nv3 || !nv4 ) 
  {
	  return NULL;
  }

  DCTPEdge *ne1 = AddEdge( nv1, nv2, 0 );
  DCTPEdge *ne2 = AddEdge( nv2, nv3, 0 );
  DCTPEdge *ne3 = AddEdge( nv3, nv4, 0 );
  DCTPEdge *ne4 = AddEdge( nv4, nv1, 0 );
  if ( !ne1 || !ne2 || !ne3 || !ne4)
  {
	  return NULL;
  }

  DCTPFace *nf = AddFace();
  if ( !nf )
  {
	  return NULL;
  }

  invalid = false;
#ifdef OSG_UNION_TRI_QUAD
  nf->orig_face[ 0 ] = nv1;
  nf->orig_face[ 1 ] = nv2;
  nf->orig_face[ 2 ] = nv3;
  nf->orig_face[ 3 ] = nv4;
#else
  nf->orig_quad[ 0 ] = nv1;
  nf->orig_quad[ 1 ] = nv2;
  nf->orig_quad[ 2 ] = nv3;
  nf->orig_quad[ 3 ] = nv4;
  // FIXME: is it really necessary? Any other (better) way to distinguish
  // FIXME: between triangle and quad faces?
  nf->orig_triangle[ 0 ] = NULL;
  nf->orig_triangle[ 1 ] = NULL;
  nf->orig_triangle[ 2 ] = NULL;
#endif

  ne1->AddFace( nf );
  ne2->AddFace( nf );
  ne3->AddFace( nf );
  ne4->AddFace( nf );

  nv1->faces.push_back( nf );
  nv2->faces.push_back( nf );
  nv3->faces.push_back( nf );
  nv4->faces.push_back( nf );

  nf->vertices.resize( 4 );
  nf->vertices[ 0 ] = nv1;
  nf->vertices[ 1 ] = nv2;
  nf->vertices[ 2 ] = nv3;
  nf->vertices[ 3 ] = nv4;
  nf->edges.resize( 4 );
  nf->edges[ 0 ] = ne1;
  nf->edges[ 1 ] = ne2;
  nf->edges[ 2 ] = ne3;
  nf->edges[ 3 ] = ne4;
  nf->norm = norm;

  return nf;
}

int DCTPMesh::read( std::ifstream & infile )
{
  std::vector < DCTPVertex* > invertices;
  std::vector < DCTPEdge* > inedges; 
//  std::vector < DCTPFace* > infaces;
  char txtbuffer[ 65536 ]; //dis makes me sick, the last SQL programmer
                           //woulda do it more elegant - Fec
  unsigned int i;

  reinit();

  // FIXME: more checks???
  infile >> txtbuffer;
  std::vector < DCTPVertex* >::size_type num_of_vertices;
  infile >> num_of_vertices >> std::ws;
  if ( num_of_vertices < 1 ) {
    invalid = true;
    return 0;
  }
  invertices.resize( num_of_vertices );

//  std::cerr << "verts: " << num_of_vertices << std::endl;
  for( i = 0; i < num_of_vertices; ++i ) {
    unsigned long act_id;
    DCTPVertex *actvert;
    vec3d act_coords;
    infile >> act_id;
    infile >> act_coords;
    infile.getline( txtbuffer, 65535 ); // why doesn't fucking ignore work???
//    std::cerr << "id: " << act_id << " act_coords: " << act_coords << std::endl;
    actvert = AddVertex( act_coords );
    invertices[ act_id ] = actvert;
    if ( !actvert ) {
        std::cerr << "DCTPMesh::read() cannot AddVertex, out of mem???\n";
        exit( -1 );
    }
  }
  infile >> txtbuffer;
//  std::cerr << txtbuffer << std::endl;
  std::vector < DCTPEdge* >::size_type num_of_edges;
  infile >> num_of_edges;
  inedges.resize( num_of_edges );
//  std::cerr << "edges: " << num_of_edges << std::endl;
  for ( i = 0; i < num_of_edges; ++i ) {
    unsigned long act_id;
    std::vector < DCTPVertex* >::size_type act_v1, act_v2;
    int act_orient;
    char ch;

    infile >> act_id;
    infile >> ch; // "("
    infile >> act_v1;
    infile >> ch; // ","
    infile >> act_v2;
    infile >> ch; // ")"
    infile >> act_orient;
    infile.getline( txtbuffer, 65535 ); // why doesn't fucking ignore work???

//    std::cerr << act_id << " act_v1: " << act_v1 << " act_v2: " << act_v2 << 
//         " act_orientation: " << act_orient << std::endl;

    DCTPEdge *actedge = AddEdge( invertices[ act_v1 ], invertices[ act_v2 ], 
                                 act_orient );
    inedges[ act_id ] = actedge;
  }
  infile >> txtbuffer;
//  std::cerr << txtbuffer << std::endl;
  unsigned int num_of_faces;
  char ch;
  infile >> num_of_faces >> std::ws;
//  std::cerr << "faces: " << num_of_faces << std::endl;
  for( i = 0; i < num_of_faces; ++i ) {
        DCTPFace *fp = AddFace();
        if ( !fp ) {
                std::cerr << "Outta memory!" << std::endl;
                return -1;
        }
        {
        unsigned int type;
        unsigned int faceid;
        infile >> faceid >> std::ws >> type >> std::ws;
//        std::cerr << faceid << " " << type << std::endl;
        if ( type != 3 && type != 4 ) {
                std::cerr << "Neither triangle, nor quad!" << std::endl;
                return -2;
        }
        if ( type == 3 ) {
           unsigned int a, b, c;
           infile >> a >> b >> c >> std::ws >> ch;
#ifdef OSG_UNION_TRI_QUAD
           fp->orig_face[ 0 ] = invertices[ a ];
           fp->orig_face[ 1 ] = invertices[ b ];
           fp->orig_face[ 2 ] = invertices[ c ];
           fp->orig_face[ 3 ] = NULL;
#else
           fp->orig_triangle[ 0 ] = invertices[ a ];
           fp->orig_triangle[ 1 ] = invertices[ b ];
           fp->orig_triangle[ 2 ] = invertices[ c ];
           fp->orig_quad[ 0 ] = NULL;
           fp->orig_quad[ 1 ] = NULL;
           fp->orig_quad[ 2 ] = NULL;
           fp->orig_quad[ 3 ] = NULL;
#endif
        } else {
           unsigned int a, b, c, d;
           infile >> a >> b >> c >> d >> std::ws >> ch;
#ifdef OSG_UNION_TRI_QUAD
           fp->orig_face[ 0 ] = invertices[ a ];
           fp->orig_face[ 1 ] = invertices[ b ];
           fp->orig_face[ 2 ] = invertices[ c ];
           fp->orig_face[ 3 ] = invertices[ d ];
#else
           fp->orig_triangle[ 0 ] = NULL;
           fp->orig_triangle[ 1 ] = NULL;
           fp->orig_triangle[ 2 ] = NULL;
           fp->orig_quad[ 0 ] = invertices[ a ];
           fp->orig_quad[ 1 ] = invertices[ b ];
           fp->orig_quad[ 2 ] = invertices[ c ];
           fp->orig_quad[ 3 ] = invertices[ d ];
#endif
        }
        }//end 'type' scope
        // read in edges
        unsigned int numedges;
        infile >> numedges;
//        std::cerr << " numofedges: " << numedges << std::endl;
        for ( unsigned int ne = 0; ne < numedges; ++ne ) {
          int aeff;
          infile >> aeff;
          fp->edges.push_back( inedges[ aeff ] );
          inedges[ aeff ]->AddFace( fp );
        }
        infile >> std::ws >> ch;
        // read in fucking vertices
        unsigned int numverts;
        infile >> numverts;
//        std::cerr << " numofverts: " << numverts << std::endl;
        for ( unsigned int nv = 0; nv < numverts; ++nv ) {
          int avff;
          infile >> avff;
          fp->vertices.push_back( invertices[ avff ] );
          invertices[ avff ]->faces.push_back( fp );
        }
        infile >> std::ws >> ch;
        // read in PHUCKING norm
        infile >> fp->norm >> std::ws; //and eat up the fukcing whitespaces
                                  //how do you think ya would reach EOF, ha??

  } // read faces for

  invalid = false;
  return 0;
}

void DCTPMesh::dump( char *fname )
{
  std::ofstream out( fname );
  write( out );
  out.close();
}

int DCTPMesh::write( std::ofstream & outfile )
{

  outfile.precision( DCTP_PRECISION );
  dctpvertexset::iterator vend = vertices.end();
#ifdef OSG_NO_EDGE_SET
  dctpedgevector::iterator eend = edges.end();
#else
  dctpedgeset::iterator eend = edges.end();
#endif
  dctpfacevector::iterator fend = faces.end();

  outfile << " VERTICES: " << vertices.size() << std::endl;
  for ( dctpvertexset::iterator v = vertices.begin(); v != vend; ++v ) {
    outfile << (*v)->id << " " << (*v)->coords << " # " << (*v)->edges.size() << " ";
    for ( std::vector<DCTPEdge *>::iterator j = (*v)->edges.begin(); 
          j != (*v)->edges.end(); ++j ) {
         outfile << " " << (*j)->id;         
    }
    outfile << std::endl;
  }

  outfile << " EDGES: " << edges.size() << std::endl;
#ifdef OSG_NO_EDGE_SET
  for ( dctpedgevector::iterator e = edges.begin(); e != eend; ++e )
#else
  for ( dctpedgeset::iterator e = edges.begin(); e != eend; ++e )
#endif
  {
    DCTPVertex * v1;
    DCTPVertex * v2;
    (*e)->getVertices( v1, v2 );
    outfile << (*e)->id << " ( " << v1->id << " , " <<
        v2->id << " ) " << (*e)->orientation << " # ";

    int num_of_faces = (*e)->faces.size();
    outfile << num_of_faces;
    dctpfacevector::iterator fe = (*e)->faces.end();
    for (dctpfacevector::iterator k = (*e)->faces.begin(); k != fe; ++k )
      outfile << " " << (*k)->id;
    outfile << std::endl;
  }

  outfile << " FACES: " << faces.size() << std::endl;
  // spit out "proprietary" info (orig_triangle/orig_quad id's)
  for ( dctpfacevector::iterator i = faces.begin( ); i != fend; ++i ) {
    outfile << (*i)->id << " ";
#ifdef OSG_UNION_TRI_QUAD
    if ( (*i)->orig_face[ 3 ] == NULL ) {
      outfile << "3 " <<(*i)->orig_face[ 0 ]->id << " " << 
                    (*i)->orig_face[ 1 ]->id << " " <<
                    (*i)->orig_face[ 2 ]->id;
    } 
    else {
      outfile << "4 " <<(*i)->orig_face[ 0 ]->id << " " << 
                    (*i)->orig_face[ 1 ]->id << " " <<
                    (*i)->orig_face[ 2 ]->id << " " <<
	            (*i)->orig_face[ 3 ]->id;
    }
#else
    if ( (*i)->orig_triangle[ 0 ] ) {
      outfile << "3 " <<(*i)->orig_triangle[ 0 ]->id << " " << 
                    (*i)->orig_triangle[ 1 ]->id << " " <<
                    (*i)->orig_triangle[ 2 ]->id;
    } 
    else if ( (*i)->orig_quad[ 0 ] ) {
      outfile << "4 " <<(*i)->orig_quad[ 0 ]->id << " " << 
                    (*i)->orig_quad[ 1 ]->id << " " <<
                    (*i)->orig_quad[ 2 ]->id << " " <<
	            (*i)->orig_quad[ 3 ]->id;
    }
    else {
      std::cerr << "FACE doesn't have either orig_triag or orig_quad set... " << std::endl;
    }
#endif
    // num of edges
    outfile << " # " << (*i)->edges.size() << " ";
    // split out edges for face
    for ( std::vector<DCTPEdge *>::iterator j = (*i)->edges.begin(); 
          j != (*i)->edges.end(); ++j ) {
         outfile << " " << (*j)->id;         
    }
    // num of vertices
    outfile << " # " << (*i)->vertices.size() << " ";
    // split out vertices for face
    for ( std::vector<DCTPVertex *>::iterator t = (*i)->vertices.begin(); 
          t != (*i)->vertices.end(); ++t ) {
         outfile << " " << (*t)->id;         
    }
    // FUCKING NORM FUCK FUCK FUCK FUCK
    outfile << " # " << (*i)->norm;
    outfile << std::endl;
  } // for faces...

  return 0;
}

void DCTPMesh::writeInvalid(std::ofstream &outfile ) 
{
  outfile << " VERTICES: 0" << std::endl;
}

bool DCTPMesh::isInvalid( void )
{
  return invalid;
}

DCTPVertex * DCTPMesh::SplitEdge( DCTPEdge *edge, double t ) {
/*  if ( t < 0.0 || t > 1.0 )
  {
	  std::cerr << "out of range" << std::endl;
	  return NULL;
  }*/
  DCTPVertex *v1, *v2;
  edge->getVertices( v1, v2 );
//  if ( t < DCTP_EPS ) return v1;
//  if ( t > 1 - DCTP_EPS ) return v2;

//  std::cerr << "split: " << v1->coords << " - " << v2->coords << ": " << t << std::endl;

  DCTPVertex *nv = new DCTPVertex;

  if ( !nv ) {
    std::cerr << "DCTPMesh::SplitEdge: Out of memory... " << std::endl;
    return NULL;
  }

  nv->coords = v1->coords + ( v2->coords - v1->coords ) * t;

  // add new vertex
  std::pair< dctpvertexset::iterator, bool > siv;
  siv = vertices.insert( nv );
  if ( !siv.second ) {
    // we already had this vertex in the mesh. Either the mesh is
    // corrupted/degenerate, or we've already applied this exact
    // SplitEdge operator.
    // or the splitvertex is very close to the ends of the edge... ;)
    delete nv;
    nv = *(siv.first);
    if ( nv->edges.size() > 0 ) {
        std::cerr << "DCTPMesh::SplitEdge: error: inserting already existing splitvertex with edges..." << std::endl;
//        std::cerr << "DCTPMesh::SplitEdge: error: numofedges: " << nv->edges.size()
//                << std::endl;
//        std::cerr << "DCTPMesh::SplitEdge: error: point location: " << nv->coords
//                <<std::endl;        
    }       
	return nv;
  }
  else
  {
	  nv->id = vertex_count++;
  }

  // modify old (original) edge to (v1, nv)
#ifdef OSG_NO_EDGE_SET
  edge->setVertices( v1, nv );
//  std::cerr << "old: " << v1->coords << " - " << nv->coords << std::endl;
#else
  // for this we have to erase the edge from the set
  // modify its vertices and insert it again.
  // NOTE: the _pointer_ itself does not change, only its iterator
  dctpedgeset::iterator edgeit = edges.find( edge );
  if( edgeit == edges.end( ) )
  {
	  std::cerr << "splitedge: edge not found" << std::endl;
	  exit( -1 );
  }
  edges.erase( edgeit );
  edge->setVertices( v1, nv );
  std::pair< dctpedgeset::iterator, bool > sie1;
  sie1 = edges.insert( edge );
  if ( !sie1.second ) {
    std::cerr << "DCTPMesh::SplitEdge: error: reinserting already existing splitedge (this shouldn't happen)" << std::endl;
    return NULL;
  }
#endif

  // add original edge to nv
//  std::cerr << "1-" << edge << " " << nv << std::endl;
  nv->edges.push_back( edge );

  // add original edge's faces to nv
  nv->faces.insert( nv->faces.end(), edge->faces.begin(), edge->faces.end() );
////  if ( edge->f1 ) nv->faces.push_back( edge->f1 );
////  if ( edge->f2 ) nv->faces.push_back( edge->f2 );

  // create new edge between ( nv, v2 )
#ifdef OSG_NO_EDGE_SET
  DCTPEdge *ne = AddEdge( nv, v2, edge->orientation );
  v2->edges.pop_back( ); // remove edge from old vertex (is added later...)
//  std::cerr << "new: " << nv->coords << " - " << v2->coords << std::endl;
#else
  DCTPEdge *ne = new DCTPEdge( nv, v2, edge->orientation );
  if ( !ne ) {
    std::cerr << "DCTPMesh::SplitEdge: Out of memory... " << std::endl;
    return NULL;
  }
  ne->id = edge_count++;

  std::pair< dctpedgeset::iterator, bool > sie;
  sie = edges.insert( ne );
  if ( !sie.second ) {
    delete ne;
    ne = *(sie.first);
    std::cerr << "DCTPMesh::SplitEdge: error: inserting already existing splitedge (this shouldn't happen)" << std::endl;
    return NULL;
  }

  // add new edge to nv
  nv->edges.push_back( ne );
#endif

  // add original edge's faces to the new edge
  ne->faces.insert( ne->faces.end(), edge->faces.begin(), edge->faces.end() );
////  ne->f1 = edge->f1; // Note: we don't have to check here :)
////  ne->f2 = edge->f2;

  // change v2's `edge' edge to `ne'
  std::vector< DCTPEdge* >::iterator v2ee = v2->edges.end();
  std::vector< DCTPEdge* >::iterator i;
  for ( i = v2->edges.begin(); i != v2ee; ++i )
    if ( *i == edge ) break;

  if (i == v2ee ) {
    std::cerr << " DCTPMesh::SplitEdge: error: couldn't find original edge in v2 " << std::endl;
    return NULL;
  }
  *i = ne;

  // store the new vertex and the new edge for all incident facez0rz
  dctpfacevector::iterator fe = edge->faces.end();
  for (dctpfacevector::iterator f = edge->faces.begin(); f != fe; ++f ) {
    (*f)->vertices.push_back( nv );
    (*f)->edges.push_back( ne );
  }
/*
  if ( edge->f1 ) {
    edge->f1->vertices.push_back( nv );
    edge->f1->edges.push_back( ne );
  }
  if ( edge->f2 ) {
    edge->f2->vertices.push_back( nv );
    edge->f2->edges.push_back( ne );
  }
*/

  //propagate `edgeinfo' to the new edge
  ne->edgeinfo = edge->edgeinfo;

  return nv;
}

double DCTPMesh::computeEdgePointDst( DCTPEdge *edg, vec3d& pnt ) {
        DCTPVertex *pp0,*pp1;
        vec3d p0, p1, pd;
        edg->getVertices( pp0, pp1 );
        p0 = pp0->coords; p1 = pp1->coords;
        vec3d v = p1 - p0;
        vec3d w = pnt - p0;
        double c1 = v.x * w.x + v.y * w.y + v.z * w.z;
        if ( c1 <= 0 ) {
                pd = p0;
                vec3d dist = pnt - p0;
                return sqrt( dist.quad_size() );
        }
        double c2 = v.quad_size();
        if ( c2 <= c1 ) {
                pd = p1;
                vec3d dist = pnt - p1;
                return sqrt( dist.quad_size() );
        }
        double b = c1 / c2;
        pd = v * b;
        pd = pd + p0;
        vec3d dist = pnt - pd;
        return sqrt( dist.quad_size() );
}

DCTPVertex* DCTPMesh::SplitEdge( DCTPEdge *edge, const vec3d& p ) {

  DCTPVertex *v1, *v2;
  edge->getVertices( v1, v2 );
#ifdef OSG_INTEGER_MESH
  vec3i &p1 = v1->coords;
  vec3i &p2 = v2->coords;
#else
  vec3d &p1 = v1->coords;
  vec3d &p2 = v2->coords;
#endif
  if ( p == p1 ) return v1;
  if ( p == p2 ) return v2;

  vec3d quickhack = p;
  double dist = computeEdgePointDst( edge, quickhack );
//DEBUG
//std::cerr << "SplitEdge, checkpoint I. distance = " << dist << std::endl;
#ifdef OSG_INTEGER_MESH
  if ( dist > 0.999 )
#else
  if ( dist > 1e-9 )
#endif
  {
#ifdef _DEBUG
//	std::cerr << "DCTPMesh::SplitEdge, dist too big " << dist << std::endl;
#endif
	return NULL;
  }
//DEBUG
//std::cerr << "SplitEdge, checkpoint II.\n";
  vec3d lng_vec1 = p1 - p2;
  double lng1 = sqrt( lng_vec1.quad_size() );
  vec3d lng_vec2 = p - p1;
  double lng2 = sqrt( lng_vec2.quad_size() );
  double par = lng2 / lng1;
  return SplitEdge( edge, par );
}

/*
 * MoveVertex: move a vertex in 3D space.
 * This must be a separate function, since the vertices are
 * stored in a set, and the key is their position in 3D space,
 * so the vertex must be taken out of the set and inserted back
 * after it was moved.
 * The pointer to the vertex does not change, only its iterator.
 * Returns zero on success, and a negative value on failure.
 */
int DCTPMesh::MoveVertex( DCTPVertex *vert, vec3d &newpos )
{
  if ( vert->coords == newpos ) return 0;
  dctpvertexset::iterator vi = vertices.find( vert );
  if ( vi == vertices.end() )
    return -1;

  vertices.erase( vi );
  vert->coords = newpos;
  std::pair< dctpvertexset::iterator, bool > vinsert;
  vinsert = vertices.insert( vert );
  if ( !vinsert.second ) {
    std::cerr << "DCTPMesh::MoveVertex: error: reinserting already existing vertex (this shouldn't happen) " << newpos << std::endl;
    return -2;
  }
  return 0;
}

#ifndef OSG_INTEGER_MESH
/*
 * SplitFace: split a face using a sequence of predefined
 * points. The points must all lie on the edge, plus
 * be ordered. The result vector contains pointers to the newly inserted
 * vertices, so that the following holds:
 *
 * res[ i ]->coords = points[ i ].
 */
int DCTPMesh::SplitFace( DCTPEdge *edge, vec3dvector &points, dctpvertexvector &res )
{
  DCTPVertex *v1, *v2;
  DCTPVertex *v;
  res.clear();
  edge->getVertices( v1, v2 );
  vec3d &lp = points[ points.size() - 1 ];
  vec3d &fp = points[ 0 ];
 
  if ( lp == fp ) { //just one point
    DCTPVertex *nv = SplitFace( edge, lp );
    if ( !nv ) return -1;
    res.push_back( nv );
    return 0;
  }
  if ( (v1->coords - lp).quad_size() < (v1->coords - fp).quad_size() ) v = v1;
  else v = v2;
//DEBUG std::cerr << "NAMOST MIAKURANYAD?\n";
  // v is the vertex closer to lp.
  vec3dvector::size_type k = points.size();
  for ( vec3dvector::size_type i = 0; i < k; ++i ) {
    DCTPVertex *nv = SplitFace( edge, points[ i ] );
//DEBUG std::cerr << "HANYSZOR BASZOL KI VELEM?" << points[ i ] << std::endl;
    if ( !nv ) return -1;
    res.push_back( nv );
    edge = findEdge( nv, v );
  } //for
  return 0;
}

/*
 * Split a face, by splitting an edge. 
 * This possibly has an effect on all faces that are incident on the edge.
 * Presupposes that all affected faces are triangles.
 *
 */
DCTPVertex *DCTPMesh::SplitFace( DCTPEdge *edge, const vec3d& p )
{
  //First we have to do an edgesplit, on the edge.
  DCTPVertex *v1, *v2;
  edge->getVertices( v1, v2 );
  if ( p == v1->coords ) return v1;
  if ( p == v2->coords ) return v2;

  DCTPVertex *nv = SplitEdge( edge, p );
  if ( !nv ) return NULL;
  
  dctpfacevector::iterator fe = edge->faces.end();
  //actually split all the faces belonging to the edge
  for ( dctpfacevector::iterator i = edge->faces.begin(); i != fe; ++i )
    SplitOneFace( *i, edge, nv );

  return nv;
}

/*
 * Finish splitting up a face, do the necessary "bookkeeping".
 *
 */
void DCTPMesh::SplitOneFace( DCTPFace *f, DCTPEdge *edge, DCTPVertex *nv)
{
  DCTPVertex *left, *right, *third;
  DCTPEdge *e1, *e2, *e3;
	unsigned int i;

  edge->getVertices( left, right );
  if ( left == nv ) { left = right; right = NULL; }
  if ( right == nv ) right = NULL;

//DEBUGCHECK
  if ( right ) std::cerr << "DCTPMesh::SplitOneFace: something strange..." << std::endl;

  //we must find the edge which is:
  // - edge over `f'
  // - has `nv' as one of its vertices
  // - not equal to `edge'
  e3 = NULL;
  std::vector< DCTPEdge* >::iterator fee = f->edges.end();
  for( std::vector< DCTPEdge* >::iterator e = f->edges.begin(); e != fee; ++e ) {
    DCTPVertex *tv1, *tv2;
    if ( *e != edge ) {
      (*e)->getVertices( tv1, tv2 );
      if ( tv1 == nv || tv2 == nv ) {
        e3 = *e;
        break;
      } //if
    } //if
  } //for
  if ( !e3 ) std::cerr << "DCTPMesh::SplitOneFace: something strange #1.5..." << std::endl;
  e3->getVertices( right, third );
  if ( right == nv ) { right = third; third = NULL; }
  if ( third == nv ) third = NULL;
  if ( third ) std::cerr << "DCTPMesh::SplitOneFace: something strange #2..." << std::endl;

  for ( i = 0; i < 3; ++i )
#ifdef OSG_UNION_TRI_QUAD
    if ( f->orig_face[ i ] != left && f->orig_face[ i ] != right ) {
      third = f->orig_face[ i ]; break;
    }
#else
    if ( f->orig_triangle[ i ] != left && f->orig_triangle[ i ] != right ) {
      third = f->orig_triangle[ i ]; break;
    }
#endif
  if ( !third ) std::cerr << "DCTPMesh::SplitOneFace: something strange #3..." << std::endl;

  e1 = findEdge( left, third );
  if ( !e1 ) std::cerr << "DCTPMesh::SplitOneFace: something strange #4..." << std::endl;
  e2 = findEdge( third, right );
  if ( !e2 ) std::cerr << "DCTPMesh::SplitOneFace: something strange #5..." << std::endl;

  //create new unoriented edge between 'third' and 'nv'
  DCTPEdge *ne = AddEdge( third, nv, 0 );
  //modify `f' such as:
  //change e2 to ne
  e2->RemoveFace( f );
  ne->AddFace( f );
  f->RemoveEdge( e2 );
  f->AddEdge( ne );

  //replace `right' with `nv'
  for ( i = 0; i < 3; ++i )
#ifdef OSG_UNION_TRI_QUAD
    if ( f->orig_face[ i ] == right ) {
      f->orig_face[ i ] = nv;
    }
#else
    if ( f->orig_triangle[ i ] == right ) {
      f->orig_triangle[ i ] = nv;
    }
#endif
  f->ReplaceVertex( right, nv );
  //remove last vertex of `f', which must be `nv'
  if ( f->vertices[ f->vertices.size() - 1 ] != nv )  std::cerr << "DCTPMesh::SplitOneFace: something strange #6..." << std::endl;
  f->vertices.resize( f->vertices.size() - 1 );

  //remove `f' from right
  right->RemoveFace( f );

  //remove `e3' from `f', since SplitEdge added it
  f->RemoveEdge( e3 );
  //remove `f' from `e3', since SplitEdge added it
  e3->RemoveFace( f );

  //OK, we're done with `f' so let's create the new face and fill it in!
  DCTPFace *nf = AddFace();
  //add the new edges
  nf->AddEdge( ne );
  nf->AddEdge( e2 );
  nf->AddEdge( e3 );

  if ( f->vertices.size() != 3 ) std::cerr << "DCTPMesh::SplitOneFace: something strange #7..." << std::endl;
  //add the vertices _in order_
  //FIXME: it could be more efficient if we create `nf' before, and copy 
  //everything from `f', and replace `left' with `nv'
  for ( i = 0; i< 3; ++i ) {
#ifdef OSG_UNION_TRI_QUAD
    if ( f->orig_face[ i ] == left )
      nf->orig_face[ i ] = nv;
    else if ( f->orig_face[ i ] == nv )
      nf->orig_face[ i ] = right;
    else
      nf->orig_face[ i ] = f->orig_face[ i ];
#else
    if ( f->orig_triangle[ i ] == left )
      nf->orig_triangle[ i ] = nv;
    else if ( f->orig_triangle[ i ] == nv )
      nf->orig_triangle[ i ] = right;
    else
      nf->orig_triangle[ i ] = f->orig_triangle[ i ];
#endif

    if ( f->vertices[ i ] == left )
      nf->vertices.push_back( nv );
    else if ( f->vertices[ i ] == nv )
      nf->vertices.push_back( right );
    else
      nf->vertices.push_back( f->vertices[ i ] );
  } //for

  //add `nf' to its vertices
  nv->AddFace( nf );
  third->AddFace( nf );
  right->AddFace( nf );

  //and to its edges
  ne->AddFace( nf );
  e2->AddFace( nf );
  e3->AddFace( nf );

} //end SplitOneFace
#endif

int DCTPMesh::write_trisoup( std::ofstream &outfile )
{
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  outfile << faces.size() << std::endl;

  for (dctpfacevector::iterator i = faces.begin(); i != faces.end(); ++i ) {
#ifdef OSG_UNION_TRI_QUAD
    outfile << (*i)->orig_face[ 0 ]->coords << " " <<
               (*i)->orig_face[ 1 ]->coords << " " <<
               (*i)->orig_face[ 2 ]->coords << " " <<
               (*i)->norm << std::endl;
#else
    outfile << (*i)->orig_triangle[ 0 ]->coords << " " <<
               (*i)->orig_triangle[ 1 ]->coords << " " <<
               (*i)->orig_triangle[ 2 ]->coords << " " <<
               (*i)->norm << std::endl;
#endif
  }
  return 0;
}

int DCTPMesh::read_trisoup( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];

  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format
  unsigned int trnum = 0;
  infile >> trnum;  

  for (unsigned int i = 0; i < trnum; ++i ) {
    vec3d v1, v2, v3;
    double norm;
    infile >> v1 >> v2 >> v3 >> norm;
    AddTriangle( v1, v2, v3, norm );
//    std::cerr << " i: " << i << std::endl;
//    std::cerr << v1.x << " " << v1.y << std::endl;
  }
  infile.getline( txtbuffer, 255 );
//  std::cerr << "bla: " << txtbuffer << std::endl;
  invalid = false;
  return 0;
}

int DCTPMesh::write_quadsoup( std::ofstream &outfile )
{
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_2 << std::endl;
  outfile << faces.size() << std::endl;

  for (dctpfacevector::iterator i = faces.begin(); i != faces.end(); ++i ) {
#ifdef OSG_UNION_TRI_QUAD
    outfile << (*i)->orig_face[ 0 ]->coords << " " <<
               (*i)->orig_face[ 1 ]->coords << " " <<
               (*i)->orig_face[ 2 ]->coords << " " <<
               (*i)->orig_face[ 3 ]->coords << " " <<
               (*i)->norm << std::endl;
#else
    outfile << (*i)->orig_quad[ 0 ]->coords << " " <<
               (*i)->orig_quad[ 1 ]->coords << " " <<
               (*i)->orig_quad[ 2 ]->coords << " " <<
               (*i)->orig_quad[ 3 ]->coords << " " <<
               (*i)->norm << std::endl;
#endif
  }
  return 0;
}

int DCTPMesh::read_quadsoup( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];

  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_2 ) ) return -1; //bad file format
  unsigned int trnum = 0;
  infile >> trnum;  

  for (unsigned int i = 0; i < trnum; ++i ) {
    vec3d v1, v2, v3, v4;
    double norm;
    infile >> v1 >> v2 >> v3 >> v4 >> norm;
    AddQuad( v1, v2, v3, v4, norm );
  }
  infile.getline( txtbuffer, 255 );
  invalid = false;
  return 0;
}

// G++ SUXXX

/*
 *  Subdivide the current (quad) face into four smaller faces. 
 *  Change the values of the current face to be the upper left
 *  quarter, and generate new faces, edges, etc. for the other
 *  three quarters.
 */
int DCTPMesh::SubdivideQuad( DCTPFace *f )
{

  vec3d n, s, e, w;
  DCTPVertex *np = NULL, *sp = NULL, *ep = NULL, *wp = NULL;

#ifdef OSG_UNION_TRI_QUAD
  n = ( f->orig_face[ 0 ]->coords + f->orig_face[ 1 ]->coords ) * 0.5;
  s = ( f->orig_face[ 2 ]->coords + f->orig_face[ 3 ]->coords ) * 0.5; 
  e = ( f->orig_face[ 1 ]->coords + f->orig_face[ 2 ]->coords ) * 0.5;
  w = ( f->orig_face[ 3 ]->coords + f->orig_face[ 0 ]->coords ) * 0.5; 
#else
  n = ( f->orig_quad[ 0 ]->coords + f->orig_quad[ 1 ]->coords ) * 0.5;
  s = ( f->orig_quad[ 2 ]->coords + f->orig_quad[ 3 ]->coords ) * 0.5; 
  e = ( f->orig_quad[ 1 ]->coords + f->orig_quad[ 2 ]->coords ) * 0.5;
  w = ( f->orig_quad[ 3 ]->coords + f->orig_quad[ 0 ]->coords ) * 0.5; 
#endif

  //iterate through the vertices and do splitedges if necessary
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();
  std::vector< DCTPVertex* >::iterator i;
  for ( i = f->vertices.begin(); i != ve; ++i ) {
    if ( (*i)->coords == n ) np = *i;
    if ( (*i)->coords == s ) sp = *i;
    if ( (*i)->coords == e ) ep = *i;
    if ( (*i)->coords == w ) wp = *i;
  }

#ifdef OSG_UNION_TRI_QUAD
  if ( !np )
    np = SplitEdge( getEdgeFromFace(f, f->orig_face[ 0 ], f->orig_face[ 1 ] ), 0.5 );
  if ( !sp )
    sp = SplitEdge( getEdgeFromFace(f, f->orig_face[ 2 ], f->orig_face[ 3 ] ), 0.5 );
  if ( !ep )
    ep = SplitEdge( getEdgeFromFace(f, f->orig_face[ 1 ], f->orig_face[ 2 ] ), 0.5 );
  if ( !wp )
    wp = SplitEdge( getEdgeFromFace(f, f->orig_face[ 3 ], f->orig_face[ 0 ] ), 0.5 );
#else
  if ( !np )
    np = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 0 ], f->orig_quad[ 1 ] ), 0.5 );
  if ( !sp )
    sp = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 2 ], f->orig_quad[ 3 ] ), 0.5 );
  if ( !ep )
    ep = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 1 ], f->orig_quad[ 2 ] ), 0.5 );
  if ( !wp )
    wp = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 3 ], f->orig_quad[ 0 ] ), 0.5 );
#endif

  //these removals must be done after the splitedge operators
  //go through the edges of the face, and remove this face
  //from each edge.
  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator ed = f->edges.begin(); ed != ee; ++ed )
    (*ed)->RemoveFace( f );

  //go through the vertices of the face, and remove this face
  //from each vertex.
  ve = f->vertices.end();
  for ( i = f->vertices.begin(); i != ve; ++i )
    (*i)->RemoveFace( f );


  buildNewFaces( f, np, sp, wp, ep );
  return 0;
}

void DCTPMesh::buildNewFaces( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp, DCTPVertex *wp, DCTPVertex *ep)
{
  //set up middle point
  vec3d middle = ( np->coords + sp->coords ) * 0.5;
  DCTPVertex * middlev = AddVertex( middle );
  //set up new edges to/from middlepoint
  // v1 .----. v2
  //    |    |
  // v4 `----' v3
  std::vector< DCTPVertex * > vertsides[ 8 ];

  setupSides( f, vertsides, 0.5, 0.5 );  
  sortSides( f, vertsides );
  //clear original face's edges and vertices
  f->edges.clear();
  f->vertices.clear();

  DCTPVertex * quad_save[ 4 ];
#ifdef OSG_UNION_TRI_QUAD
  quad_save[ 0 ] = f->orig_face[ 0 ]; quad_save[ 1 ] = f->orig_face[ 1 ];
  quad_save[ 2 ] = f->orig_face[ 2 ]; quad_save[ 3 ] = f->orig_face[ 3 ];
#else
  quad_save[ 0 ] = f->orig_quad[ 0 ]; quad_save[ 1 ] = f->orig_quad[ 1 ];
  quad_save[ 2 ] = f->orig_quad[ 2 ]; quad_save[ 3 ] = f->orig_quad[ 3 ];
#endif

  //construct the vertices-vectors of the new faces
  std::vector< DCTPVertex * > vertsvec;
  //upper left
  vertsvec.push_back( wp );
  vertsvec.insert( vertsvec.end(), vertsides[ 7 ].begin(), vertsides[ 7 ].end() );
  vertsvec.push_back( quad_save[ 0 ] );
  vertsvec.insert( vertsvec.end(), vertsides[ 0 ].begin(), vertsides[ 0 ].end() );
  vertsvec.push_back( np );
  vertsvec.push_back( middlev );
  buildQuadFace( vertsvec, f );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 1 ] = np; f->orig_face[ 2 ] = middlev; f->orig_face[ 3 ] = wp;
#else
  f->orig_quad[ 1 ] = np; f->orig_quad[ 2 ] = middlev; f->orig_quad[ 3 ] = wp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
  //upper right
  vertsvec.clear();
  vertsvec.push_back( np );
  vertsvec.insert( vertsvec.end(), vertsides[ 1 ].begin(), vertsides[ 1 ].end() );
  vertsvec.push_back( quad_save[ 1 ] );
  vertsvec.insert( vertsvec.end(), vertsides[ 2 ].begin(), vertsides[ 2 ].end() );
  vertsvec.push_back( ep );
  vertsvec.push_back( middlev );
//  std::cerr <<"lofasz size: " << vertsvec.size() << std::endl;
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = np; f->orig_face[ 1 ] = quad_save[ 1 ];
  f->orig_face[ 2 ] = ep; f->orig_face[ 3 ] = middlev;
#else
  f->orig_quad[ 0 ] = np; f->orig_quad[ 1 ] = quad_save[ 1 ];
  f->orig_quad[ 2 ] = ep; f->orig_quad[ 3 ] = middlev;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
  //lower right
  vertsvec.clear();
  vertsvec.push_back( ep );
  vertsvec.insert( vertsvec.end(), vertsides[ 3 ].begin(), vertsides[ 3 ].end() );
  vertsvec.push_back( quad_save[ 2 ] );
  vertsvec.insert( vertsvec.end(), vertsides[ 4 ].begin(), vertsides[ 4 ].end() );
  vertsvec.push_back( sp );
  vertsvec.push_back( middlev );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = middlev; f->orig_face[ 1 ] = ep;
  f->orig_face[ 2 ] = quad_save[ 2 ]; f->orig_face[ 3 ] = sp;
#else
  f->orig_quad[ 0 ] = middlev; f->orig_quad[ 1 ] = ep;
  f->orig_quad[ 2 ] = quad_save[ 2 ]; f->orig_quad[ 3 ] = sp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
  //lower left
  vertsvec.clear();
  vertsvec.push_back( sp );
  vertsvec.insert( vertsvec.end(), vertsides[ 5 ].begin(), vertsides[ 5 ].end() );
  vertsvec.push_back( quad_save[ 3 ] );
  vertsvec.insert( vertsvec.end(), vertsides[ 6 ].begin(), vertsides[ 6 ].end() );
  vertsvec.push_back( wp );
  vertsvec.push_back( middlev );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = wp; f->orig_face[ 1 ] = middlev;
  f->orig_face[ 2 ] = sp; f->orig_face[ 3 ] = quad_save[ 3 ];
#else
  f->orig_quad[ 0 ] = wp; f->orig_quad[ 1 ] = middlev;
  f->orig_quad[ 2 ] = sp; f->orig_quad[ 3 ] = quad_save[ 3 ];
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
}

/*
 *  Subdivide the current (quad) face into two smaller faces. 
 *  Change the values of the current face to be the upper
 *  half, and generate new faces, edges, etc. for the other
 *  quad.
 */
int DCTPMesh::SubdivideQuadNS( DCTPFace *f )
{

  vec3d e, w;
  DCTPVertex *ep = NULL, *wp = NULL;

#ifdef OSG_UNION_TRI_QUAD
  e = ( f->orig_face[ 1 ]->coords + f->orig_face[ 2 ]->coords ) * 0.5;
  w = ( f->orig_face[ 3 ]->coords + f->orig_face[ 0 ]->coords ) * 0.5; 
#else
  e = ( f->orig_quad[ 1 ]->coords + f->orig_quad[ 2 ]->coords ) * 0.5;
  w = ( f->orig_quad[ 3 ]->coords + f->orig_quad[ 0 ]->coords ) * 0.5; 
#endif

  //iterate through the vertices and do splitedges if necessary
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();
  std::vector< DCTPVertex* >::iterator i;
  for ( i = f->vertices.begin(); i != ve; ++i ) {
    if ( (*i)->coords == e ) ep = *i;
    if ( (*i)->coords == w ) wp = *i;
  }

#ifdef OSG_UNION_TRI_QUAD
  if ( !ep )
    ep = SplitEdge( getEdgeFromFace(f, f->orig_face[ 1 ], f->orig_face[ 2 ] ), 0.5 );
  if ( !wp )
    wp = SplitEdge( getEdgeFromFace(f, f->orig_face[ 3 ], f->orig_face[ 0 ] ), 0.5 );
#else
  if ( !ep )
    ep = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 1 ], f->orig_quad[ 2 ] ), 0.5 );
  if ( !wp )
    wp = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 3 ], f->orig_quad[ 0 ] ), 0.5 );
#endif

  //these removals must be done after the splitedge operators
  //go through the edges of the face, and remove this face
  //from each edge.
  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator ed = f->edges.begin(); ed != ee; ++ed )
    (*ed)->RemoveFace( f );

  //go through the vertices of the face, and remove this face
  //from each vertex.
  ve = f->vertices.end();
  for ( i = f->vertices.begin(); i != ve; ++i )
    (*i)->RemoveFace( f );


  buildNewFacesNS( f, wp, ep );
  return 0;
}

void DCTPMesh::buildNewFacesNS( DCTPFace *f, DCTPVertex *wp, DCTPVertex *ep)
{
  //set up middle point
#ifdef OSG_UNION_TRI_QUAD
  DCTPVertex *np = findVertex( ( f->orig_face[ 0 ]->coords + f->orig_face[ 1 ]->coords ) * 0.5 );
  DCTPVertex *sp = findVertex( ( f->orig_face[ 2 ]->coords + f->orig_face[ 3 ]->coords ) * 0.5 );
#else
  DCTPVertex *np = findVertex( ( f->orig_quad[ 0 ]->coords + f->orig_quad[ 1 ]->coords ) * 0.5 );
  DCTPVertex *sp = findVertex( ( f->orig_quad[ 2 ]->coords + f->orig_quad[ 3 ]->coords ) * 0.5 );
#endif
  //set up new edges
  // v1 .----. v2
  //    |    |
  // v4 `----' v3
  std::vector< DCTPVertex * > vertsides[ 8 ];

  setupSides( f, vertsides, 0.5, 0.5 );  
  sortSides( f, vertsides );
  //clear original face's edges and vertices
  f->edges.clear();
  f->vertices.clear();

  DCTPVertex * quad_save[ 4 ];
#ifdef OSG_UNION_TRI_QUAD
  quad_save[ 0 ] = f->orig_face[ 0 ]; quad_save[ 1 ] = f->orig_face[ 1 ];
  quad_save[ 2 ] = f->orig_face[ 2 ]; quad_save[ 3 ] = f->orig_face[ 3 ];
#else
  quad_save[ 0 ] = f->orig_quad[ 0 ]; quad_save[ 1 ] = f->orig_quad[ 1 ];
  quad_save[ 2 ] = f->orig_quad[ 2 ]; quad_save[ 3 ] = f->orig_quad[ 3 ];
#endif

  //construct the vertices-vectors of the new faces
  std::vector< DCTPVertex * > vertsvec;
  //upper
  vertsvec.push_back( quad_save[ 0 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 0 ].begin( ), vertsides[ 0 ].end( ) );
  if( np ) vertsvec.push_back( np );
  vertsvec.insert( vertsvec.end( ), vertsides[ 1 ].begin( ), vertsides[ 1 ].end( ) );
  vertsvec.push_back( quad_save[ 1 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 2 ].begin( ), vertsides[ 2 ].end( ) );
  vertsvec.push_back( ep );
  vertsvec.push_back( wp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 7 ].begin( ), vertsides[ 7 ].end( ) );
  buildQuadFace( vertsvec, f );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 2 ] = ep; f->orig_face[ 3 ] = wp;
#else
  f->orig_quad[ 2 ] = ep; f->orig_quad[ 3 ] = wp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << "NS: " << f->orig_quad[ 0 ]->coords << " ";
  std::cerr << f->orig_quad[ 1 ]->coords << " ";
  std::cerr << f->orig_quad[ 2 ]->coords << " ";
  std::cerr << f->orig_quad[ 3 ]->coords << std::endl;*/
  //lower
  vertsvec.clear( );
  vertsvec.push_back( wp );
  vertsvec.push_back( ep );
  vertsvec.insert( vertsvec.end( ), vertsides[ 3 ].begin( ), vertsides[ 3 ].end( ) );
  vertsvec.push_back( quad_save[ 2 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 4 ].begin( ), vertsides[ 4 ].end( ) );
  if( sp ) vertsvec.push_back( sp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 5 ].begin( ), vertsides[ 5 ].end( ) );
  vertsvec.push_back( quad_save[ 3 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 6 ].begin( ), vertsides[ 6 ].end( ) );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = wp; f->orig_face[ 1 ] = ep;
  f->orig_face[ 2 ] = quad_save[ 2 ]; f->orig_face[ 3 ] = quad_save[ 3 ];
#else
  f->orig_quad[ 0 ] = wp; f->orig_quad[ 1 ] = ep;
  f->orig_quad[ 2 ] = quad_save[ 2 ]; f->orig_quad[ 3 ] = quad_save[ 3 ];
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << f->orig_quad[ 0 ]->coords << " ";
  std::cerr << f->orig_quad[ 1 ]->coords << " ";
  std::cerr << f->orig_quad[ 2 ]->coords << " ";
  std::cerr << f->orig_quad[ 3 ]->coords << std::endl;*/

}

/*
 *  Subdivide the current (quad) face into two smaller faces. 
 *  Change the values of the current face to be the left
 *  half, and generate new faces, edges, etc. for the other
 *  quad.
 */
int DCTPMesh::SubdivideQuadEW( DCTPFace *f )
{

  vec3d n, s;
  DCTPVertex *np = NULL, *sp = NULL;

#ifdef OSG_UNION_TRI_QUAD
  n = ( f->orig_face[ 0 ]->coords + f->orig_face[ 1 ]->coords ) * 0.5;
  s = ( f->orig_face[ 2 ]->coords + f->orig_face[ 3 ]->coords ) * 0.5; 
#else
  n = ( f->orig_quad[ 0 ]->coords + f->orig_quad[ 1 ]->coords ) * 0.5;
  s = ( f->orig_quad[ 2 ]->coords + f->orig_quad[ 3 ]->coords ) * 0.5; 
#endif

  //iterate through the vertices and do splitedges if necessary
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();
  std::vector< DCTPVertex* >::iterator i;
  for ( i = f->vertices.begin(); i != ve; ++i ) {
    if ( (*i)->coords == n ) np = *i;
    if ( (*i)->coords == s ) sp = *i;
  }

#ifdef OSG_UNION_TRI_QUAD
  if ( !np )
    np = SplitEdge( getEdgeFromFace(f, f->orig_face[ 0 ], f->orig_face[ 1 ] ), 0.5 );
  if ( !sp )
    sp = SplitEdge( getEdgeFromFace(f, f->orig_face[ 2 ], f->orig_face[ 3 ] ), 0.5 );
#else
  if ( !np )
    np = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 0 ], f->orig_quad[ 1 ] ), 0.5 );
  if ( !sp )
    sp = SplitEdge( getEdgeFromFace(f, f->orig_quad[ 2 ], f->orig_quad[ 3 ] ), 0.5 );
#endif

  //these removals must be done after the splitedge operators
  //go through the edges of the face, and remove this face
  //from each edge.
  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator ed = f->edges.begin(); ed != ee; ++ed )
    (*ed)->RemoveFace( f );

  //go through the vertices of the face, and remove this face
  //from each vertex.
  ve = f->vertices.end();
  for ( i = f->vertices.begin(); i != ve; ++i )
    (*i)->RemoveFace( f );


  buildNewFacesEW( f, np, sp );
  return 0;
}

void DCTPMesh::buildNewFacesEW( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp)
{
  //set up middle point
#ifdef OSG_UNION_TRI_QUAD
  DCTPVertex *ep = findVertex( ( f->orig_face[ 1 ]->coords + f->orig_face[ 2 ]->coords ) * 0.5 );
  DCTPVertex *wp = findVertex( ( f->orig_face[ 0 ]->coords + f->orig_face[ 3 ]->coords ) * 0.5 );
#else
  DCTPVertex *ep = findVertex( ( f->orig_quad[ 1 ]->coords + f->orig_quad[ 2 ]->coords ) * 0.5 );
  DCTPVertex *wp = findVertex( ( f->orig_quad[ 0 ]->coords + f->orig_quad[ 3 ]->coords ) * 0.5 );
#endif
  //set up new edges
  // v1 .----. v2
  //    |    |
  // v4 `----' v3
  std::vector< DCTPVertex * > vertsides[ 8 ];

  setupSides( f, vertsides, 0.5, 0.5 );  
  sortSides( f, vertsides );
  //clear original face's edges and vertices
  f->edges.clear( );
  f->vertices.clear( );

  DCTPVertex * quad_save[ 4 ];
#ifdef OSG_UNION_TRI_QUAD
  quad_save[ 0 ] = f->orig_face[ 0 ]; quad_save[ 1 ] = f->orig_face[ 1 ];
  quad_save[ 2 ] = f->orig_face[ 2 ]; quad_save[ 3 ] = f->orig_face[ 3 ];
#else
  quad_save[ 0 ] = f->orig_quad[ 0 ]; quad_save[ 1 ] = f->orig_quad[ 1 ];
  quad_save[ 2 ] = f->orig_quad[ 2 ]; quad_save[ 3 ] = f->orig_quad[ 3 ];
#endif

  //construct the vertices-vectors of the new faces
  std::vector< DCTPVertex * > vertsvec;
  //left
  vertsvec.push_back( quad_save[ 0 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 0 ].begin( ), vertsides[ 0 ].end( ) );
  vertsvec.push_back( np );
  vertsvec.push_back( sp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 5 ].begin( ), vertsides[ 5 ].end( ) );
  vertsvec.push_back( quad_save[ 3 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 6 ].begin( ), vertsides[ 6 ].end( ) );
  if( wp ) vertsvec.push_back( wp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 7 ].begin( ), vertsides[ 7 ].end( ) );
  buildQuadFace( vertsvec, f );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 1 ] = np; f->orig_face[ 2 ] = sp;
#else
  f->orig_quad[ 1 ] = np; f->orig_quad[ 2 ] = sp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << "EW: " << f->orig_face[ 0 ]->coords << " ";
  std::cerr << f->orig_face[ 0 ]->coords << " ";
  std::cerr << f->orig_face[ 1 ]->coords << " ";
  std::cerr << f->orig_face[ 2 ]->coords << " ";
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/
  //right
  vertsvec.clear( );
  vertsvec.push_back( np );
  vertsvec.insert( vertsvec.end( ), vertsides[ 1 ].begin( ), vertsides[ 1 ].end( ) );
  vertsvec.push_back( quad_save[ 1 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 2 ].begin( ), vertsides[ 2 ].end( ) );
  if( ep ) vertsvec.push_back( ep );
  vertsvec.insert( vertsvec.end( ), vertsides[ 3 ].begin( ), vertsides[ 3 ].end( ) );
  vertsvec.push_back( quad_save[ 2 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 4 ].begin( ), vertsides[ 4 ].end( ) );
  vertsvec.push_back( sp );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = np; f->orig_face[ 1 ] = quad_save[ 1 ];
  f->orig_face[ 2 ] = quad_save[ 2 ]; f->orig_face[ 3 ] = sp;
#else
  f->orig_quad[ 0 ] = np; f->orig_quad[ 1 ] = quad_save[ 1 ];
  f->orig_quad[ 2 ] = quad_save[ 2 ]; f->orig_quad[ 3 ] = sp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << f->orig_face[ 0 ]->coords << " ";
  std::cerr << f->orig_face[ 1 ]->coords << " ";
  std::cerr << f->orig_face[ 2 ]->coords << " ";
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/

}

/*
 *  Subdivide the current (quad) face into two smaller faces. 
 *  Change the values of the current face to be the upper
 *  half, and generate new faces, edges, etc. for the other
 *  quad.
 */
int DCTPMesh::SubdivideQuadNS( DCTPFace *f, double dRatio )
{

  vec3d e, w;
  DCTPVertex *ep = NULL, *wp = NULL;

#ifdef OSG_UNION_TRI_QUAD
  e.x = f->orig_face[ 2 ]->coords.x;
  w.x = f->orig_face[ 3 ]->coords.x; 
  e.y = f->orig_face[ 2 ]->coords.y + ( f->orig_face[ 1 ]->coords.y - f->orig_face[ 2 ]->coords.y ) * dRatio;
  e.y = 10.0 * DCTP_EPS * floor( e.y / ( 10.0 * DCTP_EPS ) + 0.5 );
  w.y = e.y; 
  e.z = w.z = 0.0;
#else
  e = f->orig_quad[ 2 ]->coords + ( f->orig_quad[ 1 ]->coords - f->orig_quad[ 2 ]->coords ) * dRatio;
  w = f->orig_quad[ 3 ]->coords + ( f->orig_quad[ 0 ]->coords - f->orig_quad[ 3 ]->coords ) * dRatio; 
#endif

//  std::cerr.precision( 16 );
//  std::cerr << "SudivideQuadNS: " << dRatio << std::endl;
//  f->dump_triangle( );

  //iterate through the vertices and do splitedges if necessary
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();
  std::vector< DCTPVertex* >::iterator i;
  for ( i = f->vertices.begin(); i != ve; ++i ) {
    if ( (*i)->coords == e ) ep = *i;
    if ( (*i)->coords == w ) wp = *i;
  }

  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  std::vector< DCTPEdge* >::iterator ei;
  for( ei = f->edges.begin(); ei != ee; ++ei )
  {
	  ep = SplitEdge( *ei, e );
	  if( ep != NULL ) break;
  }
  ee = f->edges.end();
  for( ei = f->edges.begin(); ei != ee; ++ei )
  {
      wp = SplitEdge( *ei, w );
	  if( wp != NULL ) break;
  }

  if( ( ep == NULL ) || ( wp == NULL ) )
  {
	  std::cerr << "error" << std::endl;
  }

  //these removals must be done after the splitedge operators
  //go through the edges of the face, and remove this face
  //from each edge.
  /*std::vector< DCTPEdge* >::iterator*/
  ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator ed = f->edges.begin(); ed != ee; ++ed )
    (*ed)->RemoveFace( f );

  //go through the vertices of the face, and remove this face
  //from each vertex.
  ve = f->vertices.end();
  for ( i = f->vertices.begin(); i != ve; ++i )
    (*i)->RemoveFace( f );


  buildNewFacesNS( f, wp, ep, dRatio );
  return 0;
}

void DCTPMesh::buildNewFacesNS( DCTPFace *f, DCTPVertex *wp, DCTPVertex *ep, double dRatio)
{
  //set up middle point
#ifdef OSG_UNION_TRI_QUAD
  DCTPVertex *np = findVertex( ( f->orig_face[ 0 ]->coords + f->orig_face[ 1 ]->coords ) * 0.5 );
  DCTPVertex *sp = findVertex( ( f->orig_face[ 3 ]->coords + f->orig_face[ 2 ]->coords ) * 0.5 );
#else
  DCTPVertex *np = findVertex( ( f->orig_quad[ 0 ]->coords + f->orig_quad[ 1 ]->coords ) * 0.5 );
  DCTPVertex *sp = findVertex( ( f->orig_quad[ 3 ]->coords + f->orig_quad[ 2 ]->coords ) * 0.5 );
#endif
  //set up new edges
  // v1 .----. v2
  //    |    |
  // v4 `----' v3
  std::vector< DCTPVertex * > vertsides[ 8 ];

  setupSides( f, vertsides, 0.5, dRatio );  
  sortSides( f, vertsides );
  //clear original face's edges and vertices
  f->edges.clear();
  f->vertices.clear();

  DCTPVertex * quad_save[ 4 ];
#ifdef OSG_UNION_TRI_QUAD
  quad_save[ 0 ] = f->orig_face[ 0 ]; quad_save[ 1 ] = f->orig_face[ 1 ];
  quad_save[ 2 ] = f->orig_face[ 2 ]; quad_save[ 3 ] = f->orig_face[ 3 ];
#else
  quad_save[ 0 ] = f->orig_quad[ 0 ]; quad_save[ 1 ] = f->orig_quad[ 1 ];
  quad_save[ 2 ] = f->orig_quad[ 2 ]; quad_save[ 3 ] = f->orig_quad[ 3 ];
#endif

  //construct the vertices-vectors of the new faces
  std::vector< DCTPVertex * > vertsvec;
  //lower
  vertsvec.push_back( wp );
  vertsvec.push_back( ep );
  vertsvec.insert( vertsvec.end( ), vertsides[ 3 ].begin( ), vertsides[ 3 ].end( ) );
  vertsvec.push_back( quad_save[ 2 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 4 ].begin( ), vertsides[ 4 ].end( ) );
  if( sp ) vertsvec.push_back( sp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 5 ].begin( ), vertsides[ 5 ].end( ) );
  vertsvec.push_back( quad_save[ 3 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 6 ].begin( ), vertsides[ 6 ].end( ) );
  buildQuadFace( vertsvec, f );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = wp; f->orig_face[ 1 ] = ep;
//  f->orig_face[ 2 ] = quad_save[ 2 ]; f->orig_face[ 3 ] = quad_save[ 3 ];
#else
  f->orig_quad[ 0 ] = wp; f->orig_quad[ 1 ] = ep;
//  f->orig_quad[ 2 ] = quad_save[ 2 ]; f->orig_quad[ 3 ] = quad_save[ 3 ];
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << "NS: " << f << std::endl;
  std::cerr << f->orig_face[ 0 ]->coords << std::endl;
  std::cerr << f->orig_face[ 1 ]->coords << std::endl;
  std::cerr << f->orig_face[ 2 ]->coords << std::endl;
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/
  //upper
  vertsvec.clear( );
  vertsvec.push_back( quad_save[ 0 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 0 ].begin( ), vertsides[ 0 ].end( ) );
  if( np ) vertsvec.push_back( np );
  vertsvec.insert( vertsvec.end( ), vertsides[ 1 ].begin( ), vertsides[ 1 ].end( ) );
  vertsvec.push_back( quad_save[ 1 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 2 ].begin( ), vertsides[ 2 ].end( ) );
  vertsvec.push_back( ep );
  vertsvec.push_back( wp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 7 ].begin( ), vertsides[ 7 ].end( ) );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = quad_save[ 0 ]; f->orig_face[ 1 ] = quad_save[ 1 ];
  f->orig_face[ 2 ] = ep; f->orig_face[ 3 ] = wp;
#else
  f->orig_quad[ 0 ] = quad_save[ 0 ]; f->orig_quad[ 1 ] = quad_save[ 1 ];
  f->orig_quad[ 2 ] = ep; f->orig_quad[ 3 ] = wp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << f << std::endl;
  std::cerr << f->orig_face[ 0 ]->coords << std::endl;
  std::cerr << f->orig_face[ 1 ]->coords << std::endl;
  std::cerr << f->orig_face[ 2 ]->coords << std::endl;
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/

}

/*
 *  Subdivide the current (quad) face into two smaller faces. 
 *  Change the values of the current face to be the left
 *  half, and generate new faces, edges, etc. for the other
 *  quad.
 */
int DCTPMesh::SubdivideQuadEW( DCTPFace *f, double dRatio )
{

  vec3d n, s;
  DCTPVertex *np = NULL, *sp = NULL;

#ifdef OSG_UNION_TRI_QUAD
  n.x = f->orig_face[ 0 ]->coords.x + ( f->orig_face[ 1 ]->coords.x - f->orig_face[ 0 ]->coords.x ) * dRatio;
  n.x = 10.0 * DCTP_EPS * floor( n.x / ( 10.0 * DCTP_EPS ) + 0.5 );
  s.x = n.x; 
  n.y = f->orig_face[ 0 ]->coords.y;
  s.y = f->orig_face[ 3 ]->coords.y; 
  n.z = s.z = 0.0;
#else
  n = f->orig_quad[ 0 ]->coords + ( f->orig_quad[ 1 ]->coords - f->orig_quad[ 0 ]->coords ) * dRatio;
  s = f->orig_quad[ 3 ]->coords + ( f->orig_quad[ 2 ]->coords - f->orig_quad[ 3 ]->coords ) * dRatio; 
#endif

//  std::cerr.precision( 4 );
//  std::cerr << "SudivideQuadEW: " << dRatio << std::endl;
//  f->dump_triangle( );

  //iterate through the vertices and do splitedges if necessary
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();
  std::vector< DCTPVertex* >::iterator i;
  for ( i = f->vertices.begin(); i != ve; ++i ) {
    if ( (*i)->coords == n ) np = *i;
    if ( (*i)->coords == s ) sp = *i;
  }
  
  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  std::vector< DCTPEdge* >::iterator ei;
  for( ei = f->edges.begin(); ei != ee; ++ei )
  {
	  np = SplitEdge( *ei, n );
	  if( np != NULL ) break;
  }
  ee = f->edges.end();
  for( ei = f->edges.begin(); ei != ee; ++ei )
  {
      sp = SplitEdge( *ei, s );
	  if( sp != NULL ) break;
  }

  if( ( np == NULL ) || ( sp == NULL ) )
  {
	  std::cerr << "error" << std::endl;
  }

  //these removals must be done after the splitedge operators
  //go through the edges of the face, and remove this face
  //from each edge.
  /*std::vector< DCTPEdge* >::iterator*/
  ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator ed = f->edges.begin(); ed != ee; ++ed )
    (*ed)->RemoveFace( f );

  //go through the vertices of the face, and remove this face
  //from each vertex.
  ve = f->vertices.end();
  for ( i = f->vertices.begin(); i != ve; ++i )
    (*i)->RemoveFace( f );


  buildNewFacesEW( f, np, sp, dRatio );
  return 0;
}

void DCTPMesh::buildNewFacesEW( DCTPFace *f, DCTPVertex *np, DCTPVertex *sp, double dRatio)
{
  //set up middle point
#ifdef OSG_UNION_TRI_QUAD
  DCTPVertex *ep = findVertex( ( f->orig_face[ 2 ]->coords + f->orig_face[ 1 ]->coords ) * 0.5 );
  DCTPVertex *wp = findVertex( ( f->orig_face[ 3 ]->coords + f->orig_face[ 0 ]->coords ) * 0.5 );
#else
  DCTPVertex *ep = findVertex( ( f->orig_quad[ 2 ]->coords + f->orig_quad[ 1 ]->coords ) * 0.5 );
  DCTPVertex *wp = findVertex( ( f->orig_quad[ 3 ]->coords + f->orig_quad[ 0 ]->coords ) * 0.5 );
#endif
  //set up new edges
  // v1 .----. v2
  //    |    |
  // v4 `----' v3
  std::vector< DCTPVertex * > vertsides[ 8 ];

  setupSides( f, vertsides, dRatio, 0.5 );  
  sortSides( f, vertsides );
  //clear original face's edges and vertices
  f->edges.clear( );
  f->vertices.clear( );

  DCTPVertex * quad_save[ 4 ];
#ifdef OSG_UNION_TRI_QUAD
  quad_save[ 0 ] = f->orig_face[ 0 ]; quad_save[ 1 ] = f->orig_face[ 1 ];
  quad_save[ 2 ] = f->orig_face[ 2 ]; quad_save[ 3 ] = f->orig_face[ 3 ];
#else
  quad_save[ 0 ] = f->orig_quad[ 0 ]; quad_save[ 1 ] = f->orig_quad[ 1 ];
  quad_save[ 2 ] = f->orig_quad[ 2 ]; quad_save[ 3 ] = f->orig_quad[ 3 ];
#endif

  //construct the vertices-vectors of the new faces
  std::vector< DCTPVertex * > vertsvec;
  //left
  vertsvec.push_back( quad_save[ 0 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 0 ].begin( ), vertsides[ 0 ].end( ) );
  vertsvec.push_back( np );
  vertsvec.push_back( sp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 5 ].begin( ), vertsides[ 5 ].end( ) );
  vertsvec.push_back( quad_save[ 3 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 6 ].begin( ), vertsides[ 6 ].end( ) );
  if( wp ) vertsvec.push_back( wp );
  vertsvec.insert( vertsvec.end( ), vertsides[ 7 ].begin( ), vertsides[ 7 ].end( ) );
  buildQuadFace( vertsvec, f );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 1 ] = np; f->orig_face[ 2 ] = sp;
#else
  f->orig_quad[ 1 ] = np; f->orig_quad[ 2 ] = sp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << "EW: " << f << std::endl;
  std::cerr << f->orig_face[ 0 ]->coords << std::endl;
  std::cerr << f->orig_face[ 1 ]->coords << std::endl;
  std::cerr << f->orig_face[ 2 ]->coords << std::endl;
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/
  //right
  vertsvec.clear( );
  vertsvec.push_back( np );
  vertsvec.insert( vertsvec.end( ), vertsides[ 1 ].begin( ), vertsides[ 1 ].end( ) );
  vertsvec.push_back( quad_save[ 1 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 2 ].begin( ), vertsides[ 2 ].end( ) );
  if( ep ) vertsvec.push_back( ep );
  vertsvec.insert( vertsvec.end( ), vertsides[ 3 ].begin( ), vertsides[ 3 ].end( ) );
  vertsvec.push_back( quad_save[ 2 ] );
  vertsvec.insert( vertsvec.end( ), vertsides[ 4 ].begin( ), vertsides[ 4 ].end( ) );
  vertsvec.push_back( sp );
  f = buildQuadFace( vertsvec, NULL );
#ifdef OSG_UNION_TRI_QUAD
  f->orig_face[ 0 ] = np; f->orig_face[ 1 ] = quad_save[ 1 ];
  f->orig_face[ 2 ] = quad_save[ 2 ]; f->orig_face[ 3 ] = sp;
#else
  f->orig_quad[ 0 ] = np; f->orig_quad[ 1 ] = quad_save[ 1 ];
  f->orig_quad[ 2 ] = quad_save[ 2 ]; f->orig_quad[ 3 ] = sp;
  f->orig_triangle[ 0 ] = f->orig_triangle[ 1 ] = f->orig_triangle[ 2 ] = NULL;
#endif
/*  std::cerr << f << std::endl;
  std::cerr << f->orig_face[ 0 ]->coords << std::endl;
  std::cerr << f->orig_face[ 1 ]->coords << std::endl;
  std::cerr << f->orig_face[ 2 ]->coords << std::endl;
  std::cerr << f->orig_face[ 3 ]->coords << std::endl;*/

}

DCTPFace * DCTPMesh::buildQuadFace( std::vector< DCTPVertex * > &verts, DCTPFace *f )
{
  if ( !f ) f = AddFace();
//  std::cerr << "buildquadface numofedges begin: " << edge_count << std::endl;
  std::vector< DCTPVertex * >::size_type vs = verts.size() - 1;
  for( std::vector< DCTPVertex * >::size_type i = 0; i < vs; ++i ) {
	if( verts[ i ] != verts[ i + 1 ] )
	{
//      std::cerr << verts[ i ]->coords << verts[ i + 1 ]->coords << std::endl;
      DCTPEdge *ne = AddEdge( verts[ i ], verts[ i + 1 ], 0 ); //new edge
      f->edges.push_back( ne );
      f->vertices.push_back( verts[ i ] );
      ne->AddFace( f );
      verts[ i ]->AddFace( f );
	}
  }
  if( verts[ vs ] != verts[ 0 ] )
  {
//    std::cerr << verts[ vs ]->coords << verts[ 0 ]->coords << std::endl;
    DCTPEdge *ne = AddEdge( verts[ vs ], verts[ 0 ], 0 );
    f->edges.push_back( ne );
    f->vertices.push_back( verts[ vs ] );
    ne->AddFace( f );
    verts[ vs ]->AddFace( f );
  }
  f->norm = -1.0;
//  std::cerr << "buildquadface numofedges end: " << edge_count << std::endl;
  
  return f;
}

DCTPEdge *DCTPMesh::getEdgeFromFace(DCTPFace *f, DCTPVertex *v1, DCTPVertex *v2) 
{
  std::vector< DCTPEdge* >::iterator ee = f->edges.end();
  for ( std::vector< DCTPEdge* >::iterator i = f->edges.begin(); i != ee; ++i ) {
    DCTPVertex *tv1, *tv2;
    (*i)->getVertices( tv1, tv2 );
    if ( (v1->coords == tv1->coords && v2->coords == tv2->coords) || 
         (v1->coords == tv2->coords && v2->coords == tv1->coords)) return *i;
  }  
  std::cerr << "DCTPMesh:getEdgeFromFace: nonexistant edge requested... " << std::endl;
  return NULL;
}  

void DCTPMesh::sortSides( DCTPFace *f, std::vector< DCTPVertex * > * sides )
{
  std::sort( sides[ 0 ].begin(), sides[ 0 ].end(), sortnorth() );
  std::sort( sides[ 1 ].begin(), sides[ 1 ].end(), sortnorth() );
  std::sort( sides[ 2 ].begin(), sides[ 2 ].end(), sorteast() );
  std::sort( sides[ 3 ].begin(), sides[ 3 ].end(), sorteast() );
  std::sort( sides[ 4 ].begin(), sides[ 4 ].end(), sortsouth() );
  std::sort( sides[ 5 ].begin(), sides[ 5 ].end(), sortsouth() );
  std::sort( sides[ 6 ].begin(), sides[ 6 ].end(), sortwest() );
  std::sort( sides[ 7 ].begin(), sides[ 7 ].end(), sortwest() );

}

void DCTPMesh::setupSides( DCTPFace *f, std::vector< DCTPVertex * > * sides, double dXRatio, double dYRatio )
{
#ifdef OSG_UNION_TRI_QUAD
  vec3d n = f->orig_face[ 0 ]->coords + ( f->orig_face[ 1 ]->coords - f->orig_face[ 0 ]->coords ) * dXRatio;
  vec3d s = f->orig_face[ 3 ]->coords + ( f->orig_face[ 2 ]->coords - f->orig_face[ 3 ]->coords ) * dXRatio;
#else
  vec3d n = f->orig_quad[ 0 ]->coords + ( f->orig_quad[ 1 ]->coords - f->orig_quad[ 0 ]->coords ) * dXRatio;
  vec3d s = f->orig_quad[ 3 ]->coords + ( f->orig_quad[ 2 ]->coords - f->orig_quad[ 3 ]->coords ) * dXRatio;
#endif
  vec3d middle = s + ( n - s ) * dYRatio;
  std::vector< DCTPVertex* >::iterator ve = f->vertices.end();

  for ( std::vector< DCTPVertex* >::iterator i = f->vertices.begin(); i != ve; ++i ) {
    //top left and right
#ifdef OSG_UNION_TRI_QUAD
    if ( fabs((*i)->coords.y - f->orig_face[ 0 ]->coords.y ) < DCTP_EPS ) {
      //left
      if ( ((*i)->coords.x > f->orig_face[ 0 ]->coords.x ) &&
           ((*i)->coords.x < middle.x ))
#else
    if ( fabs((*i)->coords.y - f->orig_quad[ 0 ]->coords.y ) < DCTP_EPS ) {
      //left
      if ( ((*i)->coords.x > f->orig_quad[ 0 ]->coords.x ) &&
           ((*i)->coords.x < middle.x ))
#endif
        sides[ 0 ].push_back( *i );
      //right
#ifdef OSG_UNION_TRI_QUAD
      else if ( ((*i)->coords.x > middle.x ) && 
                ((*i)->coords.x < f->orig_face[ 1 ]->coords.x ))
#else
      else if ( ((*i)->coords.x > middle.x ) && 
                ((*i)->coords.x < f->orig_quad[ 1 ]->coords.x ))
#endif
        sides[ 1 ].push_back( *i );
    } //end if
    //right up and down
#ifdef OSG_UNION_TRI_QUAD
    if ( fabs((*i)->coords.x - f->orig_face[ 1 ]->coords.x ) < DCTP_EPS ) {
      //up
      if ( ((*i)->coords.y < f->orig_face[ 1 ]->coords.y ) &&
           ((*i)->coords.y > middle.y ))
#else
    if ( fabs((*i)->coords.x - f->orig_quad[ 1 ]->coords.x ) < DCTP_EPS ) {
      //up
      if ( ((*i)->coords.y < f->orig_quad[ 1 ]->coords.y ) &&
           ((*i)->coords.y > middle.y ))
#endif
        sides[ 2 ].push_back( *i );
      //down
#ifdef OSG_UNION_TRI_QUAD
      else if ( ((*i)->coords.y < middle.y ) && 
                ((*i)->coords.y > f->orig_face[ 2 ]->coords.y ))
#else
      else if ( ((*i)->coords.y < middle.y ) && 
                ((*i)->coords.y > f->orig_quad[ 2 ]->coords.y ))
#endif
        sides[ 3 ].push_back( *i );
    } //end if
    //bottom left and right
#ifdef OSG_UNION_TRI_QUAD
    if ( fabs((*i)->coords.y - f->orig_face[ 2 ]->coords.y ) < DCTP_EPS ) {
      //right
      if ( ((*i)->coords.x < f->orig_face[ 2 ]->coords.x ) &&
           ((*i)->coords.x > middle.x ))
#else
    if ( fabs((*i)->coords.y - f->orig_quad[ 2 ]->coords.y ) < DCTP_EPS ) {
      //right
      if ( ((*i)->coords.x < f->orig_quad[ 2 ]->coords.x ) &&
           ((*i)->coords.x > middle.x ))
#endif
        sides[ 4 ].push_back( *i );
      //left
#ifdef OSG_UNION_TRI_QUAD
      else if ( ((*i)->coords.x < middle.x ) && 
                ((*i)->coords.x > f->orig_face[ 3 ]->coords.x ))
#else
      else if ( ((*i)->coords.x < middle.x ) && 
                ((*i)->coords.x > f->orig_quad[ 3 ]->coords.x ))
#endif
        sides[ 5 ].push_back( *i );
    } //end if
    //left up and down
#ifdef OSG_UNION_TRI_QUAD
    if ( fabs((*i)->coords.x - f->orig_face[ 3 ]->coords.x ) < DCTP_EPS ) {
      //down
      if ( ((*i)->coords.y > f->orig_face[ 3 ]->coords.y ) &&
           ((*i)->coords.y < middle.y ))
#else
    if ( fabs((*i)->coords.x - f->orig_quad[ 3 ]->coords.x ) < DCTP_EPS ) {
      //down
      if ( ((*i)->coords.y > f->orig_quad[ 3 ]->coords.y ) &&
           ((*i)->coords.y < middle.y ))
#endif
        sides[ 6 ].push_back( *i );
      //up
#ifdef OSG_UNION_TRI_QUAD
      else if ( ((*i)->coords.y > middle.y ) && 
                ((*i)->coords.y < f->orig_face[ 0 ]->coords.y ))
#else
      else if ( ((*i)->coords.y > middle.y ) && 
                ((*i)->coords.y < f->orig_quad[ 0 ]->coords.y ))
#endif
        sides[ 7 ].push_back( *i );
    } //end if
  } //end for

}






unsigned long DCTPMesh::getNumOfVertices( void )
{
  return vertex_count;
}

unsigned long DCTPMesh::getNumOfFaces( void )
{
  return face_count;
}

void DCTPMesh::reinit( void )
{
  if( invalid ) return;

  dctpvertexset::iterator vend = vertices.end();
#ifdef OSG_NO_EDGE_SET
  dctpedgevector::iterator eend = edges.end();
#else
  dctpedgeset::iterator eend = edges.end();
#endif
  dctpfacevector::iterator fend = faces.end();

  for ( dctpvertexset::iterator v = vertices.begin(); v != vend; ++v ) {
    delete *v;
  }
#ifdef OSG_NO_EDGE_SET
  for ( dctpedgevector::iterator e = edges.begin(); e != eend; ++e )
#else
  for ( dctpedgeset::iterator e = edges.begin(); e != eend; ++e )
#endif
  {
    delete *e;
  }
  for ( dctpfacevector::iterator f = faces.begin(); f != fend; ++f ) {
    delete *f;
  }


  vertices.clear();
  edges.clear();
  faces.clear( );
  vertex_count = 0;  
  edge_count = 0;
  face_count = 0;
  invalid = true;
}

DCTPVertex * DCTPMesh::findVertex( const vec3d& v ) {
  DCTPVertex *vert = new DCTPVertex; 
  if ( !vert ) return NULL;
  vert->coords = v;
  dctpvertexset::iterator vi = vertices.find( vert );
  delete vert;
  if ( vi == vertices.end() ) 
    return NULL;
  else 
    return (*vi);
}

DCTPEdge *DCTPMesh::findEdge( DCTPVertex *v1, DCTPVertex *v2 )
{
#ifdef OSG_NO_EDGE_SET
	DCTPEdge			*pcl_edge;
	const unsigned int	cui_edge_cnt = v1->edges.size( );
	unsigned int		ui_edge;
	DCTPVertex			*pcl_ev1;
	DCTPVertex			*pcl_ev2;

	for( ui_edge = 0; ui_edge < cui_edge_cnt; ++ui_edge )
	{
		pcl_edge = v1->edges[ ui_edge ];
		pcl_edge->getVertices( pcl_ev1, pcl_ev2 );
		if( ( v2 == pcl_ev1 ) || ( v2 == pcl_ev2 ) )
		{
			return pcl_edge;
		}
	}

	return NULL;
#else
  DCTPEdge *e = new DCTPEdge( v1, v2, 0 );
  dctpedgeset::iterator ei = edges.find( e );
  delete e;
  if ( ei == edges.end() ) 
    return NULL;
  else
    return (*ei);  
#endif
}

DCTPEdge *DCTPMesh::findEdge( const vec3d &vc1, const vec3d &vc2 ) {
  DCTPVertex *v1 = findVertex( vc1 );
  if ( !v1 )
  {
//	std::cerr << "findEdge: vertex1 not found." << std::endl;
	return NULL;
  }
  DCTPVertex *v2 = findVertex( vc2 );
  if ( !v2 )
  {
//	std::cerr << "findEdge: vertex2 not found." << std::endl;
	return NULL;
  }
//  std::cerr << "seachring for edge " << v1->id << ", " << v2->id << std::endl;
  return findEdge( v1, v2 );
}


void DCTPMesh::removeFace( unsigned int ui_face )
{
	unsigned int	ui_loop;
	unsigned int	ui_loop_cnt;
	DCTPFace		*pcl_face = faces[ ui_face ];
	DCTPEdge		*pcl_edge;
	DCTPVertex		*pcl_vertex;
	DCTPVertex		*pcl_vertex2;
#ifdef OSG_NO_EDGE_SET
	unsigned int	ui_edge;
	unsigned int	ui_edge_cnt = edges.size( );
#endif

	// remove edges
	ui_loop_cnt = pcl_face->edges.size( );
	for( ui_loop = 0; ui_loop < ui_loop_cnt; ++ui_loop )
	{
		pcl_edge = pcl_face->edges[ ui_loop ];
		pcl_edge->RemoveFace( pcl_face );
		if( pcl_edge->faces.size( ) == 0 )
		{
			// no faces left on edge
			pcl_edge->getVertices( pcl_vertex, pcl_vertex2 );
			pcl_vertex->RemoveEdge( pcl_edge );
			pcl_vertex2->RemoveEdge( pcl_edge );
#ifdef OSG_NO_EDGE_SET
			for( ui_edge = 0; ui_edge < ui_edge_cnt; ++ui_edge )
			{
				if( edges[ ui_edge ] == pcl_edge )
				{
					--ui_edge_cnt;
					edges[ ui_edge ] = edges[ ui_edge_cnt ];
					edges.pop_back( );
					ui_edge = ui_edge_cnt;
				}
			}
#else
			edges.erase( pcl_edge );
#endif
		}
	}

	// remove vertices
	ui_loop_cnt = pcl_face->vertices.size( );
	for( ui_loop = 0; ui_loop < ui_loop_cnt; ++ui_loop )
	{
		pcl_vertex = pcl_face->vertices[ ui_loop ];
		pcl_vertex->RemoveFace( pcl_face );
		if( pcl_vertex->faces.size( ) == 0 )
		{
			vertices.erase( pcl_vertex );
		}
	}

	// finally remove face
	faces[ ui_face ] = faces[ faces.size( ) - 1 ];
	faces.pop_back( );
}
