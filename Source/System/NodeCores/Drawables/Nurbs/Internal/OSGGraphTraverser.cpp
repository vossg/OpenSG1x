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

#include <OSGLog.h>

#include "OSGGraphTraverser.h"
#include "OSGpredicates.h"
#include "OSGNurbsPatchSurface.h"	// for defines...

OSG_USING_NAMESPACE


#ifdef WIN32
#pragma warning (disable : 985)
#endif

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

void writeout( std::ofstream &outData, vec2d &k1, vec2d& k2 )
{
  outData.precision( DCTP_PRECISION );
  outData << k1.x << " " << k1.y << std::endl;
  outData << k2.x << " " << k2.y << std::endl << std::endl;
}

void WriteGraph( DirectedGraph<vec2d,unsigned char> *g, int fos )
        //DEBUG: write graph for gnuplot
        {       char fname[32];
                sprintf( fname, "dirA%05d.dat", fos );
                std::ofstream o1( fname );
                sprintf( fname, "dirB%05d.dat", fos );
                std::ofstream o2( fname );
                sprintf( fname, "edg%05d.dat", fos );
                std::ofstream o3( fname );

                DirectedNode<vec2d>::nodevector::iterator ne = 
                        g->nodes.end();
                DirectedEdge<unsigned char>::edgevector::iterator ee = 
                        g->edges.end();
                for( DirectedEdge<unsigned char>::edgevector::iterator i =
                     g->edges.begin(); i != ee; ++i ) {
                     if ( i->valid ) {
                        if ( i->direction ) {
                                vec2d mid = (g->nodes[ i->from ].nodeinfo +
                                             g->nodes[ i->to ].nodeinfo ) * 0.5;
                                writeout( o1, g->nodes[ i->from ].nodeinfo,
                                           mid );
                                writeout( o2, mid,
                                           g->nodes[ i->to ].nodeinfo );
                        }
                        else {
                                writeout( o3, g->nodes[ i->from ].nodeinfo,
                                           g->nodes[ i->to ].nodeinfo );
                        }
                     }
                }

        }
/***********************************************************/

void GraphTraverser::openBoundary( void )
{
  boundaryfile.open( "boundary.mesh" );
  boundaryfile.precision( DCTP_PRECISION );

}

void GraphTraverser::writePreBoundary( int boundary_index )
{
  boundaryfile << "begin_border_" << boundary_index << std::endl;
}

void GraphTraverser::writePostBoundary( int boundary_index )
{
  boundaryfile << "end_border_" << boundary_index << std::endl << std::endl; 
}

void GraphTraverser::writeNode( int nodeid )
{
  vec2d actcoord = g->nodes[ nodeid ].nodeinfo;

  boundaryfile << actcoord.x << " " << actcoord.y << " 0 " << std::endl;
}
void GraphTraverser::writeBoundary( int startedge )
{
  static int boundary_index = 0;
  int startnode = g->edges[ startedge ].from;
  int actedge = startedge;
  int actnode = startnode;

  if ( !boundary_index ) openBoundary();
  writePreBoundary( boundary_index );
  while ( g->edges[ actedge ].to != startnode ) {
    writeNode( actnode );
    actnode = g->edges[ actedge ].to;
    actedge = getOutGoingEdge( actnode );

  }

  writePostBoundary( boundary_index );
  boundary_index++;

}

/***********************************************************/
void GraphTraverser::Initialize( DirectedGraph<vec2d, unsigned char >& gg, bool
        usedelaunaytri )
{
  g = &gg;
  unsigned int ee = g->nodes.size();
  globalverts.resize( ee );

  for (unsigned int i = 0; i < ee; ++i )
    globalverts[ i ] = g->nodes[ i ].nodeinfo;

  usedelaunay = usedelaunaytri;
  polys.clear();
}



int GraphTraverser::triangulatePolygon( ivector& nodes, bool bConvex ) {
	unsigned int i;
        
        
        // if it's not convex we just return so that outer patches
        // don't get triangulated -> we will use point based rendering
        // for those sometime. :)
/////        if ( !bConvex ) return;
        
//  std::cerr<<"triangulate in..." << std::endl;
/*
static int cnt = 0;
char fname[32];
cnt++;
sprintf( fname, "POLY%02d.DAT", cnt );
//std::ofstream okadek( "POLY_.DAT", ios::app );
std::ofstream okadek( fname );

std::cerr << " Polygon #: " << cnt << " Size: " << nodes.size() << std::endl;
        unsigned int ne = nodes.size() - 1;
        for ( unsigned int i = 0; i < ne; ++i )
          writeout( okadek, g->nodes[ nodes[ i ] ].nodeinfo, g->nodes[ nodes[ i + 1 ] ].nodeinfo );
        writeout( okadek, g->nodes[ nodes[ ne ] ].nodeinfo, g->nodes[ nodes[ 0 ] ].nodeinfo );
okadek.close();
*/


/*
  std::cerr << "triangulate: " << nodes[ 0 ] << " size: " << nodes.size() << std::endl;
  if (nodes.size() == 27 || nodes.size() == 46 ) {
    std::cerr.precision( 12 );
    std::cerr << nodes.size() << std::endl;
    for ( unsigned int i = 0; i < nodes.size(); ++i )
      std::cerr  << globalverts[ nodes[ i ] ] << std::endl;
    std::cerr << std::endl;
  }
*/


/*
  std::cerr << "triangulate: " << nodes[ 0 ] << " size: " << nodes.size() << std::endl;
  for ( i = 0; i < nodes.size(); ++i )
      std::cerr  << globalverts[ nodes[ i ] ] << std::endl;
  std::cerr << std::endl;
*/
//  if ( nodes[ 0 ] == -1 ) SLOG << "GraphTraverser::triangulatePolygon: invalid nodes, duff.... " << std::endl;

  SimplePolygon actpoly;
  actpoly.vertices = nodes;
//  actpoly.is_marked = 1;
//  actpoly.is_marked = 0; // if zero, we use Delaunay triangulation for this poly
  actpoly.is_marked = !usedelaunay;
#ifdef OSG_TRIANGULATE_CONVEX
  if( bConvex )
  {
    actpoly.m_bConvex = bConvex;
//	std::cerr <<"convex bcoz of bConvex" << std::endl;
  }
  else if( nodes.size( ) > 4 )
  {
    actpoly.m_bConvex = actpoly.isConvex( globalverts );
//	std::cerr <<"isconvex: " <<actpoly.m_bConvex << std::endl;
  }
//  std::cerr << "convex: " << actpoly.m_bConvex << std::endl;
#endif

/*
  if( !m_bTriangulate )
  {
	  polys.push_back( actpoly );
	  return 0;
  }
*/
//  std::cerr << "calling triangulate... polyno:" << polys.size() << std::endl;
//  std::cerr << "calling triangulate... nodes:" << nodes.size() << std::endl;
  std::vector< SimplePolygon >	newpolys;

  int err =  actpoly.triangulate( globalverts, newpolys );
  if( ( err ) && ( usedelaunay ) )
  {
	// delaunay didn't work, so try any triangulation
    newpolys.clear();
	actpoly.is_marked = 1;
	err = actpoly.triangulate( globalverts, newpolys );
  }
  if( err )
  {
	// simple triagulation didn't work, so try to fix polygon
    newpolys.clear();
	actpoly.fixAndTriangulate( globalverts, newpolys );
  }
  polys.insert( polys.end( ), newpolys.begin( ), newpolys.end( ) );
#ifdef _DEBUG
  if ( err )
  {
//    std::cerr <<"polyno after error: " << polys.size() << std::endl;
//DEBUG
    //check for duplicated vertices passed to triangulate
    vec2dset vset;
    std::set < int > iset;
    std::pair< vec2dset::iterator, bool > siv;
    std::pair< std::set < int >::iterator, bool > niv;
    bool fuckedup = false;
    unsigned int k = nodes.size();
    std::cerr << "nodeids:";
    for (i = 0; i < k; ++i ) std::cerr << " " << nodes[ i ];
    std::cerr << std::endl;
    for (i = 0; i < k; ++i ) {
        siv = vset.insert( globalverts[ nodes[ i ] ] );
        if ( !siv.second ) {
           fuckedup = true;
           std::cerr << "duplicate vertex passed: " << globalverts[ nodes[ i ] ] << " i: " << i << std::endl;;
        }
        niv = iset.insert( nodes[ i ] );
        if ( !niv.second ) {
           fuckedup = true;
           std::cerr << "duplicate vertex index passed: " << nodes[ i ] << " i: " << i << std::endl;
        }
    } // for

//DEBUG END

/*    std::cerr << "Dumping info: " << std::endl;
    std::cerr.precision( 16 );
    std::cerr << nodes.size() << std::endl;
    for ( unsigned int i = 0; i < nodes.size(); ++i ) {
      std::cerr.precision( 16 );
      std::cerr  << globalverts[ nodes[ i ] ] << std::endl;
    }
    std::cerr << std::endl;*/

//    throw GraphTraverserError( GraphTraverserError::ERR_TRIANGULATE );
//	if( fuckedup ) exit( -1 );
  } //if err
#endif

//  std::cerr << " we have now: " << polys.size() << " triangles." << std::endl;
//  std::cerr <<"triangulate out " << std::endl;
  return 0;
}

int GraphTraverser::getADirectedEdge( void ) {
        static bool beenhere = false;
        if ( !beenhere ) beenhere = true;
        unsigned int e = g->edges.size();
        bool found = false;
        for( unsigned int i = 0; i < e; ++i )
                if ( g->edges[ i ].direction && g->edges[ i ].valid )
                        { e = i; found = true; break; }

        if ( !found && !beenhere ) {
                std::cerr << "No trimming thingie found!" << std::endl;
                throw GraphTraverserError( ERR_NO_TRIMMING );
//		abort();
        }
        else if ( !found ) return -1;
//        writeBoundary( e );
        return e;
}

void GraphTraverser::handleEdge( int eid, int to_nid, int &from_nid /* double& ang*/ ) {
//        int from_nid;
        if ( g->edges[ eid ].to == to_nid ) from_nid = g->edges[ eid ].from;
        else  from_nid = g->edges[ eid ].to;
/*        vec2d edge_vect =
                g->nodes[ from_nid ].nodeinfo - g->nodes[ to_nid ].nodeinfo;
        ang = atan2( edge_vect.y, edge_vect.x );
        if ( ang < 0.0 ) ang = 2 * M_PI + ang;*/
        if ( g->edges[ eid ].direction ) g->DeleteEdge( eid );
        else g->setEdgeDirection( eid, from_nid );
}

int GraphTraverser::getOtherEnd( int eid, int nid ) {
        DirectedEdge< unsigned char >& e = g->edges[ eid ];

        if ( e.to == nid )
		{
//			std::cerr << "following edge reversed " << eid << " -> " << e.from << std::endl;
			return e.from;
		}
        else
		{
//			std::cerr << "following edge " << eid << " -> " << e.to << std::endl;
			return e.to;
		}
}

int GraphTraverser::getOutGoingEdge( int nid ) {
        ivector::iterator ee = g->nodes[ nid ].edges.end();
        for( ivector::iterator i = g->nodes[ nid ].edges.begin();
             i != ee; ++i )
                if ( g->edges[ *i ].direction &&
                     g->edges[ *i ].from == nid )
                        return *i;
        return -1;
}

int GraphTraverser::Traverse( void ) {

	//first find a directed edge
//	int KKKbitch = 0;//DEBUG
	bool b_convex;
	int edgeID = getADirectedEdge();
	while ( edgeID != -1 ) {
		b_convex = ( g->edges[ edgeID ].edgeinfo == 0 );
		int start_node = g->edges[ edgeID ].from;
		int leave = -1, act_node = g->edges[ edgeID ].to;
		int last_node;
		ivector node_ids;
		node_ids.push_back( start_node );
		node_ids.push_back( act_node );
		while ( edgeID != -1 ) {
			if( g->edges[ edgeID ].edgeinfo ) b_convex = false;
			handleEdge( edgeID, act_node, last_node );
			edgeID = getNextEdge( act_node, last_node );
			if( edgeID == -1 ) break;
//			std::cerr << "edgeID: " << edgeID << " g->edges[edgeID]: " << (void*) &g->edges[ edgeID ] << std::endl;
//			std::cerr << "g->edges[ edgeID ].direction: " << g->edges[ edgeID ].direction << std::endl;
			if ( !g->edges[ edgeID ].direction && leave < 0 )
				leave = act_node;
			act_node = getOtherEnd( edgeID, act_node );
			if ( start_node == act_node ) {//a polygon finished
				if( g->edges[ edgeID ].edgeinfo ) b_convex = false;
				handleEdge( edgeID, start_node, last_node );
				triangulatePolygon( node_ids, b_convex );
				b_convex = true;
				node_ids.clear();
//				std::cerr << " act_node: " << act_node << " start_node: " << start_node << " leave: " << leave << std::endl;
				start_node = leave; leave = -1;
				if ( start_node != -1 ) {
					node_ids.push_back( start_node );
					edgeID = getOutGoingEdge( start_node );
					act_node = getOtherEnd( edgeID, start_node );
//					std::cerr << "new actnode: " << act_node << std::endl;
					node_ids.push_back( act_node );
//					WriteGraph( g, KKKbitch++ ); //DEBUG
				}
				else edgeID = -1;
			}
			else
			{
				const int	ci_size2 = node_ids.size( ) - 2;
				if( ci_size2 >= 0 )
				{
					if( node_ids[ ci_size2 ] == act_node )
					{
						// went in a dead end => delete last two nodes
						node_ids.resize( ci_size2 );
					}
				}
				node_ids.push_back( act_node );
			}
		}
		edgeID = getADirectedEdge();
	}
	return 0;
}

int GraphTraverser::writeTriangles( std::ofstream &of ) {

//  std::cerr << " we have " << polys.size() << " triangles..." << std::endl;
//  std::cerr << " and we have " << globalverts.size() << " vertices..." << std::endl;

  of << "VERTICES " << globalverts.size() << std::endl;
  vec2dvector::iterator ve = globalverts.end();
  of.precision( DCTP_PRECISION );
  for ( vec2dvector::iterator i = globalverts.begin(); i != ve; ++i )
    of << *i << std::endl;
  of << "TRIANGLES " << polys.size() << std::endl;
  simplepolygonvector::iterator te = polys.end();   
  for ( simplepolygonvector::iterator t = polys.begin(); t != te; ++t ) {
/*
    double k =  globalverts[ i->vertices[ 0 ] ].x * globalverts[ i->vertices[ 1 ] ].y -
         globalverts[ i->vertices[ 1 ] ].x * globalverts[ i->vertices[ 0 ] ].y +
         globalverts[ i->vertices[ 1 ] ].x * globalverts[ i->vertices[ 2 ] ].y -
         globalverts[ i->vertices[ 2 ] ].x * globalverts[ i->vertices[ 1 ] ].y;
//    std::cerr << "counterclockwise..." << k << std::endl; 
    if ( k < 0 ) {
       int tmp = i->vertices[ 0 ];
       i->vertices[ 0 ] = i->vertices[ 1 ];
       i->vertices[ 1 ] = tmp;
    }
*/
    of << t->vertices[ 0 ] << " " << t->vertices[ 1 ] << " " << t->vertices[ 2 ] << std::endl;
  }
//  return writeTrianglesInventor( of );
    return 0;
}

void GraphTraverser::writeInvalidTriangles( std::ofstream &of )
{
  of << "VERTICES 0" << std::endl;
  of << "TRIANGLES 0" << std::endl;
}

int GraphTraverser::getNextEdge( const int nodeid, const int previd /*const double& in_angle*/ ) {
        vec2d prev_vect = g->nodes[ previd ].nodeinfo;
        vec2d node_vect = g->nodes[ nodeid ].nodeinfo;
        int en = g->nodes[ nodeid ].edges.size(); //numbah o' 3dg4z

        if ( en == 1 ) {//most common case, along trimming curves over faces
                int e0 = g->nodes[ nodeid ].edges[ 0 ];
/*                if ( g->edges[ e0 ].from == nodeid &&
                     g->edges[ e0 ].direction )
                {
//					std::cerr << "tracing along graph " << nodeid << " -> " << e0 << std::endl;
                    return e0;
				}*/
				if( ( g->edges[ e0 ].from == nodeid ) ||
					( g->edges[ e0 ].to == nodeid ) )
				{
					return e0;
				}
				std::cerr << "Error " << nodeid << " <-> " << g->edges[ e0 ].from << " -> " << g->edges[ e0 ].to << std::endl;
                std::cerr << "Error in GraphTraverser::getNextEdge()." << std::endl;
                throw GraphTraverserError( ERR_GETNEXTEDGE );
//                abort();
        }

        ivector eid; //edge ids
//        dvector ea; //edge angles

        ivector::iterator ee = g->nodes[ nodeid ].edges.end();
        for( ivector::iterator iv = g->nodes[ nodeid ].edges.begin();
             iv != ee; ++iv )
		{
			DirectedEdge< unsigned char >& act_edge = g->edges[ *iv ];
			if( ( ( !act_edge.direction ) || ( act_edge.to != nodeid ) ) &&
				( ( act_edge.from != nodeid ) || ( act_edge.to != previd ) ) &&
				( ( act_edge.to != nodeid ) || ( act_edge.from != previd ) ) )
			{
				eid.push_back( *iv );
/*                DirectedNode< vec2d > *nptr;
                if ( act_edge.to == nodeid )
                        nptr = &( g->nodes[ act_edge.from ] );
                else nptr = &( g->nodes[ act_edge.to ] );
                vec2d v = nptr->nodeinfo - node_vect;
                double tmp = atan2( v.y, v.x );
                if ( tmp < 0.0 ) tmp = 2 * M_PI + tmp;
                ea.push_back( tmp );
				std::cerr << tmp << ", ";*/
			}
        }
//		std::cerr << std::endl;
        //DEBUG:
        if ( /*eid.size() != ea.size() ||*/ eid.size() == 0 ) {
//          std::cerr << "eid.size(): " << eid.size() << " ea.size(): " << ea.size() << std::endl;
//          throw GraphTraverserError( ERR_ZERO_SIZE );
			return -1;
        }
        //END DEBUG
		double a[ 2 ], b[ 2 ], c[ 2 ], d[ 2 ];
        unsigned int eae = eid.size();
        int leftmost = 0;
//		std::cerr << prev_vect << " -> " << node_vect << std::endl;
		a[ 0 ] = prev_vect.x;
		a[ 1 ] = prev_vect.y;
		b[ 0 ] = node_vect.x;
		b[ 1 ] = node_vect.y;
		if ( g->edges[ eid[ 0 ] ].to == nodeid )
		{
			c[ 0 ] = g->nodes[ g->edges[ eid[ 0 ] ].from ].nodeinfo.x;
			c[ 1 ] = g->nodes[ g->edges[ eid[ 0 ] ].from ].nodeinfo.y;
		}
		else
		{
			c[ 0 ] = g->nodes[ g->edges[ eid[ 0 ] ].to ].nodeinfo.x;
			c[ 1 ] = g->nodes[ g->edges[ eid[ 0 ] ].to ].nodeinfo.y;
		}
//		std::cerr << node_vect << " -> (" << c[ 0 ] << ", " << c[ 1 ] << ")" << std::endl;
        double orient = orient2d( a, b, c );
//        std::cerr << "in_angle: " << in_angle << std::endl;
        for( unsigned int i = 1; i < eae; ++i )
		{
//			std::cerr << "checking edge " << i << std::endl;
			if ( g->edges[ eid[ i ] ].to == nodeid )
			{
				d[ 0 ] = g->nodes[ g->edges[ eid[ i ] ].from ].nodeinfo.x;
				d[ 1 ] = g->nodes[ g->edges[ eid[ i ] ].from ].nodeinfo.y;
			}
			else
			{
				d[ 0 ] = g->nodes[ g->edges[ eid[ i ] ].to ].nodeinfo.x;
				d[ 1 ] = g->nodes[ g->edges[ eid[ i ] ].to ].nodeinfo.y;
			}
//			std::cerr << node_vect << " -> (" << d[ 0 ] << ", " << d[ 1 ] << ")" << std::endl;
			double tmp = orient2d( a, b, d );
//			std::cerr << orient << " " << tmp << std::endl;
			// fails, if both are = 0.0, but next test would fail too...
//			std::cerr << orient2d( b, c, d ) << std::endl;
			if( ( orient < 0.0 ) || ( tmp > 0.0 ) )
			{
				if( ( ( tmp > 0.0 ) && ( orient <= 0.0 ) ) ||
					( ( tmp == 0.0 ) && ( orient < 0.0 ) ) ||
					( orient2d( b, c, d ) > 0.0 ) )
				{
//					std::cerr << b[ 0 ] << ", " << b[ 1 ] << std::endl;
//					std::cerr << c[ 0 ] << ", " << c[ 1 ] << std::endl;
//					std::cerr << d[ 0 ] << ", " << d[ 1 ] << std::endl;
// 					std::cerr << "found better edge!" << std::endl;
					orient = tmp;
					leftmost = i;
					c[ 0 ] = d[ 0 ];
					c[ 1 ] = d[ 1 ];
//					std::cerr << node_vect << " -> (" << c[ 0 ] << ", " << c[ 1 ] << ")" << std::endl;
				}
			}
/*			double tmp = ea[ i ] - in_angle;
//			std::cerr << " tmp before" << tmp << "ea[i]: " << ea[i] << std::endl;
			if ( tmp < 0.0 ) tmp = 2 * M_PI + tmp;
//			std::cerr << "tmp: " << tmp << "angle: " << angle << std::endl;
			if ( tmp > angle ) { leftmost = i; angle = tmp; }*/
		}
//		if ( leftmost == -1 ) throw GraphTraverserError( GraphTraverserError::ERR_ALL_ZERO );
//		std::cerr << "leftmost: " << leftmost << "eae: " << eae << std::endl;
//		std::cerr << "going left on graph " << nodeid << " -> " << eid[ leftmost ] << std::endl;
        return eid[ leftmost ];
}
