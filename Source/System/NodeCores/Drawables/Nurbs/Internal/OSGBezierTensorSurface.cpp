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
#include "OSGBezierTensorSurface.h"

OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BezierTensorSurface::ff_const_1[]="BEGINBEZIERTENSORSURFACE";
  const char BezierTensorSurface::ff_const_2[]="NUMBEROFCONTROLPOINTSU";
  const char BezierTensorSurface::ff_const_3[]="NUMBEROFCONTROLPOINTSV";


//construction (& destruction, but not here :)
BezierTensorSurface::BezierTensorSurface()
{
  control_points.resize( 0 );
}

//setup functions
int BezierTensorSurface::setControlPointMatrix( const vec3dmatrix& cps )
{
  vec3dmatrix::size_type u_size = cps.size();
  if ( u_size < 2 ) return -1; //invalid, at least two row of points are required
  vec3dvector::size_type v_size = cps[ 0 ].size();
  if ( v_size < 2 ) return -1; //invalid size, at least two columns are needed
  for( vec3dvector::size_type i = 1; i < u_size; ++i )
    if ( cps[ i ].size() != v_size ) return -1; //the size of columns're not equal!
  control_points = cps;
  return 0;
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
int BezierTensorSurface::read( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];


  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; //yeah, bad file format again

  vec2dvector::size_type num_of_cps_u;
  infile >> num_of_cps_u >> std::ws;
  if ( num_of_cps_u < 2 ) return -2; //too few control points
  control_points.resize( num_of_cps_u ); //FIXME: whatif not enoght memory?


  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_3 ) )  return -1; //yeah, bad file format again
  vec2dvector::size_type num_of_cps_v;
  infile >> num_of_cps_v >> std::ws;
  if ( num_of_cps_v < 2 ) return -2; //too few control points

  for( dvector::size_type u = 0; u < num_of_cps_u; ++u ) {
    control_points[ u ].resize( num_of_cps_v ); //what if not wnough memory 'n an exeption is thrown
    for( dvector::size_type v = 0; v < num_of_cps_v; ++v ) {
      vec3d cp;
      infile >> cp.x >> cp.y >> cp.z >> std::ws;
      control_points[u][v] = cp; //FIXME: ya see, we need ERROR CHECKS!!!, eg. maybe there's not enough points in file
      }
  }

  return 0;

}

int BezierTensorSurface::write( std::ofstream &outfile )
{
  //FIXME: maybe we need more checks!!!
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  dvector::size_type num_of_cps_u = control_points.size();
  outfile << ff_const_2 << " " << num_of_cps_u << std::endl;
  dvector::size_type num_of_cps_v = control_points[ 0 ].size();
  outfile << ff_const_3 << " " << num_of_cps_v << std::endl;

  for( dvector::size_type u = 0; u < num_of_cps_u; ++u )
    for( dvector::size_type v = 0; v < num_of_cps_v; ++v ) {
      vec3d cp = control_points[u][v];
      outfile << cp.x << " " << cp.y << " " << cp.z << std::endl;
  }
  return 0;
}


//some REAL functionality
vec3d BezierTensorSurface::computewdeCasteljau( vec2d uv, int &/*error*/ )
{
	const unsigned int	cui_u = control_points.size( );
	const unsigned int	cui_v = control_points[ 0 ].size( ) - 1;

	double				*pd_ux = new double[ cui_u ];
	double				*pd_uy = new double[ cui_u ];
	double				*pd_uz = new double[ cui_u ];
	double				*pd_vx = new double[ cui_v ];
	double				*pd_vy = new double[ cui_v ];
	double				*pd_vz = new double[ cui_v ];
	unsigned int		ui_i;
	unsigned int		ui_j;
	unsigned int		ui_k;
	const double		cd_tu = uv.x;
	const double		cd_tu2 = 1.0 - cd_tu;
	const double		cd_tv = uv.y;
	const double		cd_tv2 = 1.0 - cd_tv;
	const unsigned int	cui_u1 = cui_u - 1;
	const unsigned int	cui_v1 = cui_v - 1;
	vec3d				cl_ret;

//	std::cerr << uv << std::endl;

	for( ui_i = 0; ui_i < cui_u; ++ui_i )
	{
		for( ui_j = 0; ui_j < cui_v; ++ui_j )
		{
			const unsigned int	cui_j1 = ui_j + 1;

			pd_vx[ ui_j ] = control_points[ ui_i ][ ui_j ].x * cd_tv2 + control_points[ ui_i ][ cui_j1 ].x * cd_tv;
			pd_vy[ ui_j ] = control_points[ ui_i ][ ui_j ].y * cd_tv2 + control_points[ ui_i ][ cui_j1 ].y * cd_tv;
			pd_vz[ ui_j ] = control_points[ ui_i ][ ui_j ].z * cd_tv2 + control_points[ ui_i ][ cui_j1 ].z * cd_tv;
//			std::cerr << pd_vx[ ui_j ] << " " << pd_vy[ ui_j ] << " " << pd_vz[ ui_j ] << std::endl;
		}

		for( ui_k = 0; ui_k < cui_v1; ++ui_k )
		{
			const unsigned int	cui_vk = cui_v1 - ui_k;

			for( ui_j = 0; ui_j < cui_vk; ++ui_j )
			{
				const unsigned int	cui_j1 = ui_j + 1;

				pd_vx[ ui_j ] *= cd_tv2;
				pd_vy[ ui_j ] *= cd_tv2;
				pd_vz[ ui_j ] *= cd_tv2;
				pd_vx[ ui_j ] += pd_vx[ cui_j1 ] * cd_tv;
				pd_vy[ ui_j ] += pd_vy[ cui_j1 ] * cd_tv;
				pd_vz[ ui_j ] += pd_vz[ cui_j1 ] * cd_tv;
			}
		}
		pd_ux[ ui_i ] = pd_vx[ 0 ];
		pd_uy[ ui_i ] = pd_vy[ 0 ];
		pd_uz[ ui_i ] = pd_vz[ 0 ];
//		std::cerr << pd_ux[ ui_i ] << " " << pd_uy[ ui_i ] << " " << pd_uz[ ui_i ] << std::endl;
	}

/*	for( ui_i = 0; ui_i < cui_u; ++ui_i )
	{
		const unsigned int	cui_i1 = ui_i + 1;

	}*/

	for( ui_k = 0; ui_k < cui_u1; ++ui_k )
	{
		const unsigned int	cui_uk = cui_u1 - ui_k;

		for( ui_i = 0; ui_i < cui_uk; ++ui_i )
		{
			const unsigned int	cui_i1 = ui_i + 1;

			pd_ux[ ui_i ] *= cd_tu2;
			pd_uy[ ui_i ] *= cd_tu2;
			pd_uz[ ui_i ] *= cd_tu2;
			pd_ux[ ui_i ] += pd_ux[ cui_i1 ] * cd_tu;
			pd_uy[ ui_i ] += pd_uy[ cui_i1 ] * cd_tu;
			pd_uz[ ui_i ] += pd_uz[ cui_i1 ] * cd_tu;
		}
	}

	cl_ret.x = pd_ux[ 0 ];
	cl_ret.y = pd_uy[ 0 ];
	cl_ret.z = pd_uz[ 0 ];

	delete[ ] pd_ux;
	delete[ ] pd_uy;
	delete[ ] pd_uz;
	delete[ ] pd_vx;
	delete[ ] pd_vy;
	delete[ ] pd_vz;

//	std::cerr << cl_ret << std::endl << std::endl;

	return cl_ret;

	// NOTE: Old code was far too slow, because of memory allocation...

  //FIXME: verification before goin' into computation!!
  //FIXME: there are a lot of unverified error reports!!
/*  vec3dmatrix::size_type n = control_points.size() - 1;
  vec3dvector::size_type m = control_points[ 0 ].size() - 1;

  if ( n <= m ) { //less expensive: first by u0 we get a (m+1) element vector
    vec3dvector Q( m + 1 ); //temp to store computed values at u0
    for( vec3dvector::size_type j = 0; j <= m; ++j ) {
      vec3dvector row( n + 1 ); //temp to store current row o' da control_points
      for( vec2dvector::size_type k = 0; k <= n; ++k ) row[ k ] = control_points[ k ][ j ]; //copied jth row
      BezierCurve3D curve_of_row;
      curve_of_row.setControlPointVector( row );
      Q[ j ] = curve_of_row.computewdeCasteljau( uv.x, error );
    } //OK - in Q now we have the points on the surface at u0 (uv.u )
    BezierCurve3D column_at_u0;
    column_at_u0.setControlPointVector( Q );
    return column_at_u0.computewdeCasteljau( uv.y, error );
  }
  else {
    vec3dvector Q( n + 1 );
    for( vec3dvector::size_type j = 0; j <= n; ++j ) {
      vec3dvector column( m + 1 ); //temp to current column o' da control_points
      column = control_points[ j ];
      BezierCurve3D curve_of_column;
      curve_of_column.setControlPointVector( column );
      Q[ j ] = curve_of_column.computewdeCasteljau( uv.y, error );
    } //OK - in Q now we have the points on the surfave at v0 (uv.v)
    BezierCurve3D row_at_v0;
    row_at_v0.setControlPointVector( Q );
    return row_at_v0.computewdeCasteljau( uv.x, error );
  }*/
}

vec3d BezierTensorSurface::computeLinearApproximation( vec2d uv, int &error )
{
  //FIXME: verification before goin' into computation!!
  vec3dmatrix::size_type n = control_points.size() - 1;
  vec3dvector::size_type m = control_points[ 0 ].size() - 1;
  vec3d result( 0.0, 0.0, 0.0 ), temp( 0.0, 0.0, 0.0 );

  if ( n < 1 || m < 1 ) { //too few points, at least 2 needed
    error = -1;
    return result;
  }
  result = ( control_points[ 0 ][ 0 ] * ( 1 - uv.x ) + control_points[ n ][ 0 ] * uv.x ) * ( 1 - uv.y );
  result += ( control_points[ 0 ][ m ] * ( 1 - uv.x ) + control_points[ n ][ m ] * uv.x ) * uv.y;
  return ( result ); 
}

// subdivide surface at midpoint into 4 bezier surfaces
int BezierTensorSurface::midPointSubDivision( beziersurfacematrix &newbeziers)
{
  int error;
  unsigned int i;
  newbeziers.resize( 2 );
  newbeziers[ 0 ].resize( 2 );
  newbeziers[ 1 ].resize( 2 ); // we return exactly 4 new bezier tensorsurfaces


  //FIXME: verification before goin' into computation!!
  //FIXME: there are a lot of unverified error reports!!
  vec3dmatrix::size_type n = control_points.size() - 1;
  vec3dvector::size_type m = control_points[ 0 ].size() - 1;
  bezier3dmatrix horizdiv( n + 1 );
  bezier3dmatrix vertdivleft( m + 1 );
  bezier3dmatrix vertdivright( m + 1 );
//  std::cerr << "n: " << n << " m: " << m << std::endl;
  //FIXME: does the order u->v or v->u really not matter? e.g. for speed if for nothing else
  for ( i = 0; i <= n; i++ ) {
	horizdiv[ i ].resize( 2 );
    horizdiv[ i ][ 0 ].setControlPointVector( control_points[ i ] );
    error = horizdiv[ i ][ 0 ].midPointSubDivision( horizdiv[ i ][ 1 ] );
    if ( error ) return error;
  }

  for ( i = 0; i <= m; i++ ) {
    vec3dvector tempvecleft( n + 1 );
    vec3dvector tempvecright( n + 1 );
    for ( dvector::size_type j = 0; j <= n; j++ ) {
      tempvecleft[ j ] = horizdiv[ j ][ 0 ].getControlPointVector()[ i ];
      tempvecright[ j ] = horizdiv[ j ][ 1 ].getControlPointVector()[ i ];
    } // j
	vertdivleft[ i ].resize( 2 );
    vertdivleft[ i ][ 0 ].setControlPointVector( tempvecleft );
    error = vertdivleft[ i ][ 0 ].midPointSubDivision( vertdivleft[ i ][ 1 ] );
    if ( error ) return error;
	vertdivright[ i ].resize( 2 );
    vertdivright[ i ][ 0 ].setControlPointVector( tempvecright );
    error = vertdivright[ i ][ 0 ].midPointSubDivision( vertdivright[ i ][ 1 ] );
    if ( error ) return error;
  } // i
  vec3dmatrix cps( n + 1 );
  for ( i = 0; i <= n; i++ )
     cps[ i ].resize( m + 1);

  for ( i = 0; i <= n; i++ ) {
    for ( vec3dmatrix::size_type j = 0; j <= m; j++ ) {
      cps[ i ][ j ] = vertdivleft[ j ][ 0 ].getControlPointVector()[ i ];
    }
  }
  newbeziers[ 0 ][ 0 ].setControlPointMatrix( cps );
  for ( i = 0; i <= n; i++ ) {
    for ( vec3dmatrix::size_type j = 0; j <= m; j++ ) {
      cps[ i ][ j ] = vertdivleft[ j ][ 1 ].getControlPointVector()[ i ];
    }
  }
  newbeziers[ 1 ][ 0 ].setControlPointMatrix( cps );
  for ( i = 0; i <= n; i++ ) {
    for ( vec3dmatrix::size_type j = 0; j <= m; j++ ) {
      cps[ i ][ j ] = vertdivright[ j ][ 0 ].getControlPointVector()[ i ];
    }
  }
  newbeziers[ 0 ][ 1 ].setControlPointMatrix( cps );
  for ( i = 0; i <= n; i++ ) {
    for ( vec3dmatrix::size_type j = 0; j <= m; j++ ) {
      cps[ i ][ j ] = vertdivright[ j ][ 1 ].getControlPointVector()[ i ];
    }
  }
  newbeziers[ 1 ][ 1 ].setControlPointMatrix( cps );


  return 0;
}

// subdivide surface at midpoint into 4 bezier surfaces
int BezierTensorSurface::midPointSubDivision( beziersurfacevector &newbeziers )
{
  int error;
  unsigned int i;

  newbeziers.resize( 3 ); // we return exactly 3 new bezier tensorsurfaces

  error = midPointSubDivisionU( newbeziers[ 1 ] );	// first in u because this is slower
  if( error ) return error;
  error = midPointSubDivisionV( newbeziers[ 0 ] );
  if( error ) return error;
  return newbeziers[ 1 ].midPointSubDivisionV( newbeziers[ 2 ] );
}

// subdivide surface at midpoint into 2 bezier surfaces
int BezierTensorSurface::midPointSubDivisionU( BezierTensorSurface &newsurface )
{
	// This function is time critical so optimize at the cost of readabiltity...
	vec3dmatrix::size_type n = control_points.size( );
	vec3dvector::size_type m = control_points[ 0 ].size( );

	if( ( n < 2 ) || ( m < 2 ) )
	{
		return -1;	//too few points, at least 2 needed to split curve
	}

	vec3dvector::size_type i, k;
	vec3dmatrix::size_type j;

	newsurface.control_points.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	newsurface.control_points.resize( n );
	for( j = 0; j < n; ++j )
	{
		vec3dvector &cp2 = newsurface.control_points[ j ];

		cp2.resize( m );
	}

	vec3dmatrix &cp1 = control_points;
	vec3dmatrix &cp2 = newsurface.control_points;

	--n;
	for( j = 0; j < m; ++j )
	{
		for( k = 0; k < n; ++k )
		{
			cp2[ n - k ][ j ].x = cp1[ n ][ j ].x;
			cp2[ n - k ][ j ].y = cp1[ n ][ j ].y;
			cp2[ n - k ][ j ].z = cp1[ n ][ j ].z;
			for( i = n; i > k; --i )
			{
				cp1[ i ][ j ].x += cp1[ i - 1 ][ j ].x;
				cp1[ i ][ j ].y += cp1[ i - 1 ][ j ].y;
				cp1[ i ][ j ].z += cp1[ i - 1 ][ j ].z;
				cp1[ i ][ j ].x *= 0.5;
				cp1[ i ][ j ].y *= 0.5;
				cp1[ i ][ j ].z *= 0.5;
			}
		}
		cp2[ 0 ][ j ].x = cp1[ n ][ j ].x;
		cp2[ 0 ][ j ].y = cp1[ n ][ j ].y;
		cp2[ 0 ][ j ].z = cp1[ n ][ j ].z;
	}
	
	return 0;
}

// subdivide surface at midpoint into 2 bezier surfaces
int BezierTensorSurface::midPointSubDivisionV( BezierTensorSurface &newsurface )
{
	// This function is time critical so optimize at the cost of readabiltity...
	vec3dmatrix::size_type n = control_points.size( );
	vec3dvector::size_type m = control_points[ 0 ].size( );

	if( ( n < 2 ) || ( m < 2 ) )
	{
		return -1;	//too few points, at least 2 needed to split curve
	}

	vec3dvector::size_type i, k;
	vec3dmatrix::size_type j;

	newsurface.control_points.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	newsurface.control_points.resize( n );
	--m;
	for( j = 0; j < n; ++j )
	{
		vec3dvector &cp1 = control_points[ j ];
		vec3dvector &cp2 = newsurface.control_points[ j ];

		cp2.resize( m + 1 );

		for( k = 0; k < m; ++k )
		{
			cp2[ m - k ].x = cp1[ m ].x;
			cp2[ m - k ].y = cp1[ m ].y;
			cp2[ m - k ].z = cp1[ m ].z;
			for( i = m; i > k; --i )
			{
				cp1[ i ].x += cp1[ i - 1 ].x;
				cp1[ i ].y += cp1[ i - 1 ].y;
				cp1[ i ].z += cp1[ i - 1 ].z;
				cp1[ i ].x *= 0.5;
				cp1[ i ].y *= 0.5;
				cp1[ i ].z *= 0.5;
			}
		}
		cp2[ 0 ].x = cp1[ m ].x;
		cp2[ 0 ].y = cp1[ m ].y;
		cp2[ 0 ].z = cp1[ m ].z;
	}
	
	return 0;
}
