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
#include "OSGBezierCurve3D.h"
#include <OSGBaseTypes.h>

OSG_USING_NAMESPACE



#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BezierCurve3D::ff_const_1[]="BEGINBEZIERCURVE3D";
  const char BezierCurve3D::ff_const_2[]="NUMBEROFCONTROLPOINTS";
  std::vector< std::vector< std::vector< double > > > BezierCurve3D::m_svvvdCreateMatrix;

//construction (& destruction, but not here :)
BezierCurve3D::BezierCurve3D()
{
  control_points.resize( 0 );
}

//setup functions
int BezierCurve3D::setControlPointVector( const vec3dvector& cps )
{
  if ( cps.size() < 2 ) return -1; //invalid dimension, at least two points are required
  control_points = cps;
  return 0;
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
int BezierCurve3D::read( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];


  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; //yeah, bad file format again

  vec3dvector::size_type num_of_cps;
  infile >> num_of_cps >> std::ws;

  if ( num_of_cps < 2 ) return -2; //too few control points
  control_points.resize( num_of_cps ); //FIXME: whatif not enoght memory?

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec3d cp;
    infile >> cp.x >> cp.y >> cp.z >> std::ws;
    control_points[ i ] = cp; //FIXME: ya see, we need ERROR CHECKS!!!, eg. maybe there's not enough points in file
  }

  return 0;

}

int BezierCurve3D::write( std::ofstream &outfile )
{
  //FIXME: maybe we need more checks!!!
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  dvector::size_type num_of_cps = control_points.size();
  outfile << ff_const_2 << " " << num_of_cps << std::endl;

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec3d cp = control_points[ i ];
    outfile << cp.x << " " << cp.y << " " << cp.z << std::endl;
  }
  return 0;
}

int BezierCurve3D::write( )
{
  //FIXME: maybe we need more checks!!!
  std::cerr << ff_const_1 << std::endl;
  dvector::size_type num_of_cps = control_points.size();
  std::cerr << ff_const_2 << " " << num_of_cps << std::endl;

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec3d cp = control_points[ i ];
    std::cerr << cp.x << " " << cp.y << " " << cp.z << std::endl;
  }
  return 0;
}


//some REAL functionality
//! Compute the value of the Bezier curve at given the parameter value.
/*!
 *  This function computes the value of the Bezier curve
 *  at the given parameter value, using de Casteljau's method of
 *  repeated linear interpolations.
 *
 *  \param t the parameter value at which to compute the approximation
 *  \param error flag to indicate if an error has happened
 *  \return the approximated value
 *
 */
vec3d BezierCurve3D::computewdeCasteljau( double t, int &error )
{
  //FIXME: verification before goin' into computation!!
//  vec3dvector Q = control_points; //local array not to destroy da other points
  const unsigned int	n = control_points.size( ) - 1; 
  vec3d					ret;

  if ( n < 1 )  //too few points, at least 2 needed
  {
    error = -1;
    ret = control_points[ 0 ];
	ret.x = DCTP_EPS * floor( ret.x / DCTP_EPS );
	ret.y = DCTP_EPS * floor( ret.y / DCTP_EPS );
	ret.z = DCTP_EPS * floor( ret.z / DCTP_EPS );
	return ret;
  }

  unsigned int			i, k;
  vec3d					*Q = new vec3d[ n ];
//  double				*Qx = new double[ n ];
//  double				*Qy = new double[ n ];
//  double				*Qz = new double[ n ];
  const double			t2 = 1.0 - t;
  const unsigned int	n1 = n - 1;

  for( i = 0; i < n; ++i )
  {
	  const unsigned int	i1 = i + 1;
	  Q[ i ] = control_points[ i ] * t2 + control_points[ i1 ] * t;
//	  Qx[ i ] = control_points[ i ].x * t2 + control_points[ i1 ].x * t;
//	  Qy[ i ] = control_points[ i ].y * t2 + control_points[ i1 ].y * t;
//	  Qz[ i ] = control_points[ i ].z * t2 + control_points[ i1 ].z * t;
  }

  for( k = 0; k < n1; ++k )
  {
	  const unsigned int	nk = n1 - k;
	  for( i = 0; i < nk; ++i )
	  {
		  const unsigned int	i1 = i + 1;
		  Q[ i ] *= t2;
//		  Qx[ i ] *= t2;
//		  Qy[ i ] *= t2;
//		  Qz[ i ] *= t2;
		  Q[ i ] += Q[ i1 ] * t;
//		  Qx[ i ] += Qx[ i1 ] * t;
//		  Qy[ i ] += Qy[ i1 ] * t;
//		  Qz[ i ] += Qz[ i1 ] * t;
	  }
  }

  ret = Q[ 0 ];
//  ret.x = Qx[ 0 ];
//  ret.y = Qy[ 0 ];
//  ret.z = Qz[ 0 ];
  delete[ ] Q;
//  delete[ ] Qx;
//  delete[ ] Qy;
//  delete[ ] Qz;
  return ret;

/*  for( vec3dvector::size_type k = 0; k < n; ++k ) 
    for( vec3dvector::size_type i = 0; i < n - k; ++i )
      Q[ i ] = Q[ i ] * ( 1.0 - t ) + Q[ i + 1 ] * t;
  return ( Q[0] ); */
}

//! Compute the linear approximation of the Bezier curve at the given parameter value.
/*!
 *  This function computes the linear approximation of the Bezier curve
 *  at the given parameter value.
 *
 *  \param t the parameter value at which to compute the approximation
 *  \param error flag to indicate if an error has happened
 *  \return the approximated value
 *
 */
vec3d BezierCurve3D::computeLinearApproximation( double t, int &error )
{
  //FIXME: verification before goin' into computation!!
  vec3dvector::size_type n = control_points.size() - 1;
  vec3d result( 0.0, 0.0, 0.0 );

  if ( n < 1 ) { //too few points, at least 2 needed
    error = -1;
    return result;
  }
  result = control_points[ 0 ] * t + control_points[ n ] * ( 1 - t );
  return ( result ); 
}

//! Subdivide Bezier curve at midpoint into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the midpoint, using de Casteljau's
 *  algorithm.
 *
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::midPointSubDivision( bezier3dvector &newbeziers )
{
  // This function is time critical so optimize at the cost of readabiltity...
  vec3dvector::size_type n = control_points.size();

  if ( n < 2 ) { //too few points, at least 2 needed to split curve
    return -1;
  }

  newbeziers.resize( 2 ); // we return exactly two curves
//  vec3dvector Q = control_points; //local array not to destroy da other points
//  vec3dvector cp1( n + 1 );
//  vec3dvector cp2( n + 1 );
  vec3dvector::size_type i, k;

  vec3dvector &cp1 = newbeziers[ 0 ].control_points;
  vec3dvector &cp2 = newbeziers[ 1 ].control_points;
/*  cp1.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
  cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
  cp1.resize( n );
  cp2.resize( n );

  --n;
  for( k = 0; k < n; ++k ) {
    cp1[ k ] = Q [ 0 ];
    cp2[ n - k ] = Q [ n - k ];
    for( i = 0; i < n - k; ++i ) {
	  Q[ i ] += Q[ i + 1 ];
	  Q[ i ] *= 0.5;
//      Q[ i ] = Q[ i ] * ( 1.0 - 0.5 ) + Q[ i + 1 ] * 0.5;
    }
  }
//  std::cerr << "--- " << Q[ 0 ] << std::endl;
  cp1[ n ] = Q[ 0 ];
  cp2[ 0 ] = Q[ 0 ];*/

	cp1.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp1.resize( n );
	cp2.resize( n );

	for( k = 0; k < n; ++k )
	{
		cp1[ k ].x = control_points[ k ].x;
		cp1[ k ].y = control_points[ k ].y;
		cp1[ k ].z = control_points[ k ].z;
	}
	--n;
	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ].x = cp1[ n ].x;
		cp2[ n - k ].y = cp1[ n ].y;
		cp2[ n - k ].z = cp1[ n ].z;
		for( i = n; i > k; --i )
		{
			cp1[ i ].x += cp1[ i - 1 ].x;
			cp1[ i ].y += cp1[ i - 1 ].y;
			cp1[ i ].z += cp1[ i - 1 ].z;
			cp1[ i ].x *= 0.5;
			cp1[ i ].y *= 0.5;
			cp1[ i ].z *= 0.5;
		}
//      Q[ i ] = Q[ i ] * ( 1.0 - 0.5 ) + Q[ i + 1 ] * 0.5;
    }
	cp2[ 0 ] = cp1[ n ];
//  newbeziers[ 0 ].setControlPointVector( cp1 );
//  newbeziers[ 1 ].setControlPointVector( cp2 );
  return 0;
}

//! Subdivide Bezier curve at midpoint into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the midpoint, using de Casteljau's
 *  algorithm.
 *
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::midPointSubDivision( BezierCurve3D &newcurve )
{
	// This function is time critical so optimize at the cost of readabiltity...
	vec3dvector::size_type n = control_points.size();

	if( n < 2 )
	{
		return -1;	//too few points, at least 2 needed to split curve
	}

	vec3dvector::size_type i, k;

	vec3dvector &cp1 = control_points;
	vec3dvector &cp2 = newcurve.control_points;

	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.resize( n );

	--n;
	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ].x = cp1[ n ].x;
		cp2[ n - k ].y = cp1[ n ].y;
		cp2[ n - k ].z = cp1[ n ].z;
		for( i = n; i > k; --i )
		{
			cp1[ i ].x += cp1[ i - 1 ].x;
			cp1[ i ].y += cp1[ i - 1 ].y;
			cp1[ i ].z += cp1[ i - 1 ].z;
			cp1[ i ].x *= 0.5;
			cp1[ i ].y *= 0.5;
			cp1[ i ].z *= 0.5;
		}
    }
	cp2[ 0 ].x = cp1[ n ].x;
	cp2[ 0 ].y = cp1[ n ].y;
	cp2[ 0 ].z = cp1[ n ].z;
	
	return 0;
}

//! Subdivide Bezier curve at t into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the parameter value `t', using de Casteljau's
 *  algorithm.
 *
 *  \param t the parameter at which to subdivide the curve.
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::subDivision( double t, bezier3dvector &newbeziers )
{
  if ( t <= 0.0 || t >= 1.0 ) return -1; // t must be between (0, 1) exclusive

  newbeziers.resize( 2 ); // we return exactly two curves
  vec3dvector Q = control_points; //local array not to destroy da other points
  vec3dvector::size_type n = control_points.size() - 1;
  vec3dvector cp1( n + 1 );
  vec3dvector cp2( n + 1 );
  if ( n < 1 ) { //too few points, at least 2 needed to split curve
    return -1;
  }

  for( vec3dvector::size_type k = 0; k < n; ++k ) {
    cp1[ k ] = Q [ 0 ];
    cp2[ n - k ] = Q [ n - k ];
    for( vec3dvector::size_type i = 0; i < n - k; ++i ) {
      Q[ i ] = Q[ i ] * ( 1.0 - t ) + Q[ i + 1 ] * t;
    }
  }
  cp1[ n ] = Q[ 0 ];
  cp2[ 0 ] = Q[ 0 ];
  newbeziers[ 0 ].setControlPointVector( cp1 );
  newbeziers[ 1 ].setControlPointVector( cp2 );
  return 0;
}

//! Subdivide Bezier curve at t into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the parameter value `t', using de Casteljau's
 *  algorithm.
 *
 *  \param t the parameter at which to subdivide the curve.
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::subDivision( double t, BezierCurve3D &newcurve )
{
	if ( t <= 0.0 || t >= 1.0 )
	{
		return -1; // t must be between (0, 1) exclusive
	}
	
	// This function is time critical so optimize at the cost of readabiltity...
	vec2dvector::size_type n = control_points.size();

	if ( n < 2 )
	{
		return -1;	//too few points, at least 2 needed to split curve
	}

	double	t2 = 1.0 - t;

	vec3dvector::size_type i, k;

	vec3dvector &cp1 = control_points;
	vec3dvector &cp2 = newcurve.control_points;

	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.resize( n );

	--n;

	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ] = cp1[ n ];
		for( i = n; i > k; --i )
		{
			cp1[ i ] *= t;
			cp1[ i ] += cp1[ i - 1 ] * t2;
		}
    }
	cp2[ 0 ] = cp1[ n ];
	
	return 0;
}

//! Approximate curve linearly with given maximum tolerance.
/*!
 *  This function approximates the Bezier curve with a polyline. The maximum
 *  error of the approximation will not be larger than the given tolerance.
 *
 *
 *  \param vertices the vertices of the approximating polyline.
 *  \param delta maximum error.
 *  \return zero on success, and a negative value when some error occured.
 */
int BezierCurve3D::approximate( std::vector< double > &vertices, double delta, unsigned char strategy )
{
  vertices.resize( 0 );

  // check for first degree Bezier.
  if ( control_points.size() == 2 ) {
    vertices.push_back( 0.0 );
    vertices.push_back( 1.0 );
    return 0;
  }

  // call recursive subdividing function
  return approximate_sub( vertices, delta, 0.0, 1.0, strategy );

}

int BezierCurve3D::approximate_sub( std::vector< double > &vertices, double delta, double min, double max, unsigned char strategy )
{
  double act_error;
  double max_error = 0;
  vec3d  ae;
  double twopower = 1;
  double aenorm;
  double t1, t2;
  int worst_i;
  vec3d  n0_norm;

  int n = control_points.size() - 1;

  if( ( strategy & DISTANCE ) == LINE_DISTANCE )
  {
	  n0_norm = control_points[ n ] - control_points[ 0 ];
	  aenorm = n0_norm.quad_size( );
	  if( aenorm > 1e-300 )
	  {
		  n0_norm *= 1.0 / aenorm;
	  }
	  else
	  {
		  n0_norm = vec3d( 0.0, 0.0, 0.0 );
	  }
  }

  for ( int i = 0; i <= n; i++ ) {
    if( ( strategy & DISTANCE ) == POINT_DISTANCE )
	{
      t2 = ( (double) i ) / n;
	}
	else
	{
	  t2 = ( control_points[ i ] - control_points[ 0 ] ).dot( n0_norm );
	  if( t2 < 0.0 )
	  {
		  t2 = 0.0;
	  }
	  else if( t2 > 1.0 )
	  {
		  t2 = 1.0;
	  }
	}
    t1 = 1.0 - t2;
    ae = control_points[ i ] - control_points[ 0 ] * t1 - control_points[ n ] * t2;

//    std::cerr << "i: " << i << " ae.x: " << ae.x << " ae.y: " << ae.y << std::endl;

    aenorm = sqrt( ae.quad_size( ) );
    if (aenorm > max_error )
	{
	  max_error = aenorm;
	  worst_i = i;
	}
    if ( i ) twopower *= 2.0; // this is a double so it can be arbitrarily high, an int wouldn't suffice
  }
  act_error = ( ( twopower - 1 ) / twopower ) * max_error;
//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ].x << " " << control_points[ 0 ].y << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ].x << " " << control_points[ control_points.size() - 1 ].y << std::endl;
  if ( act_error > delta ) {
    // we have to subdivide further
    BezierCurve3D	newbez;
    int error;
	double mid;
    if( ( strategy & SUBDIVISION ) == MIDPOINT_SUBDIVISION )
	{
	  error = midPointSubDivision( newbez );
      if ( error ) return error;
	  mid = ( min + max ) * 0.5;
	}
	else
	{
	  mid = ( ( double ) worst_i ) / n;
	  error = subDivision( mid, newbez );
      if ( error ) return error;
	  mid = min + ( max - min ) * mid;
	}
    approximate_sub( vertices, delta, min, mid, strategy );
    newbez.approximate_sub( vertices, delta, mid, max, strategy );
  }
  else {
    // this is a good enough approximation
    if ( !vertices.size() ) {
      // this is the first approximation, we have to record both the
      // startpoint and the endpoint  
      vertices.push_back( min );
      vertices.push_back( max );
    }
    else {
      // we had some subdivisions before, we only need to record the endpoint
      vertices.push_back( max );
    }
  }
  return 0;
}

// generate a bezier curve through these points
int BezierCurve3D::createCurve( vec3dvector &points )
{
	int	n = points.size( ) - 1;

	if( n < 1 )
	{
		return -1;	// too few points
	}

	control_points.resize( n + 1 );

	control_points[ 0 ] = points[ 0 ];
	control_points[ n ] = points[ n ];

	if( n == 1 )
	{
		return 0;	// linear curve, so we are done...
	}

/*	if( m_svvvdCreateMatrix.size( ) == 0 )
	{
		if( loadCreateMatrices( ) != 0 )
		{
			return -3;	// matrix file not found
		}
	}

	if( n - 1 > m_svvvdCreateMatrix.size( ) )
	{
		return -2;	// degree too high (sorry...)
	}*/

	int	i;
	int	j;
//	std::vector< std::vector< double > >	&mat = m_svvvdCreateMatrix[ n - 2 ];

	for( i = 1; i < n; ++i )
	{
/*		std::vector< double >	&row = mat[ i ];
		control_points[ i ].x = control_points[ i ].y = control_points[ i ].z = 0.0;
		for( j = 0; j <= n; ++j )
		{
			control_points[ i ] += ( points[ j ] - points[ n >> 1 ] ) * row[ j ];
//			std::cerr << row[ j ] << " ";
		}
		control_points[ i ] += points[ n >> 1 ];
//		std::cerr << std::endl;*/
		control_points[ i ] = points[ i ];
	}

	// try to approximate it better
	double	maxerr = 1.0;

//	std::cerr << "n = " << n;

	unsigned int	ui_exit = 0;
	while( maxerr > 1e-8 )
	{
		std::vector< vec3d >	vcl_err( n + 1 );

		maxerr = 0.0;
		for( i = 0; i <= n; ++i )
		{
			int err = 0;
			vcl_err[ i ] = points[ i ] - computewdeCasteljau( ( ( double ) i ) / n, err );

			double acterr = ( vcl_err[ i ] ).quad_size( );

			maxerr = osgMax( maxerr, acterr );
		}
		for( i = 1; i < n; ++i )
		{
//			std::vector< double >	&row = mat[ i ];
			control_points[ i ] += vcl_err[ i ];
		}

		if( ( ++ui_exit ) > 10000 )
		{
			for( i = 0; i <= n; ++i )
			{
				std::cerr << points[ i ] << std::endl;
			}
			std::cerr << std::endl;
			std::cerr << "approxerr: " << sqrt( maxerr ) << std::endl;

			return -2;
		}
	}
//	std::cerr << ", approxerr: " << sqrt( maxerr ) << std::endl;
	return 0;	// everything ok.
}

int BezierCurve3D::loadCreateMatrices( )
{
	std::ifstream	cl_matrix_file;
	unsigned int	ui_mat;
	unsigned int	ui_i;
	unsigned int	ui_j;
	char			ac_val[ 17 ];
	UInt64			*pui64_read;
	UInt64			ui64_tmp;

	cl_matrix_file.open( "bezier_matrices_101.ini" );
	if( !cl_matrix_file.good( ) )
	{
		std::cerr << "Bezier matrix file missing!" << std::endl;
		return -1;
	}

	cl_matrix_file >> ui_mat >> std::ws;
	m_svvvdCreateMatrix.resize( ui_mat - 1 );

	for( ui_mat = 0; ui_mat < m_svvvdCreateMatrix.size( ); ++ui_mat )
	{
		m_svvvdCreateMatrix[ ui_mat ].resize( ui_mat + 3 );
		for( ui_i = 0; ui_i <= ui_mat + 2; ++ui_i )
		{
			m_svvvdCreateMatrix[ ui_mat ][ ui_i ].resize( ui_mat + 3 );
			for( ui_j = 0; ui_j <= ui_mat + 2; ++ui_j )
			{
				cl_matrix_file >> ac_val >> std::ws;
				pui64_read = ( UInt64* ) &( m_svvvdCreateMatrix[ ui_mat ][ ui_i ][ ui_j ] );
				*pui64_read = 0l;
				for( unsigned int ui_x = 0; ui_x < 16; ++ui_x )
				{
					if( ( ac_val[ ui_x ] >= '0' ) && ( ac_val[ ui_x ] <= '9' ) )
					{
						ui64_tmp = ac_val[ ui_x ] - '0';
					}
					else if( ( ac_val[ ui_x ] >= 'a' ) && ( ac_val[ ui_x ] <= 'f' ) )
					{
						ui64_tmp = 10 + ac_val[ ui_x ] - 'a';
					}
					else if( ( ac_val[ ui_x ] >= 'A' ) && ( ac_val[ ui_x ] <= 'F' ) )
					{
						ui64_tmp = 10 + ac_val[ ui_x ] - 'A';
					}
					ui64_tmp <<= 4 * ( 15 - ui_x );
					*pui64_read += ui64_tmp;
				}
			}
		}
	}

	return 0;
}


//! Degree reduce the Bezier curve with t tolerance if possible.
/*!
 *  This function tries to degree reduce the Bezier curve ensuring
 *  that the new curve does not deviate more from the original curve
 *  than a specified error tolerance.
 *
 *  \param t error tolerance which is still accepted for the new
 *           (lower degree) curve.
 *  \return true on success, false if degree reduction is not possible
 *           within the given tolerance.
 */
bool BezierCurve3D::reduceDegree( double tol )
{
    UInt32      n = control_points.size() - 1; // orig cps: 0, ..., n
    if ( n < 2 )
    {
        // cannot degree reduce a first degree curve
        return false;
    }
    vec3dvector b_left( n );
    vec3dvector b_right( n );
    UInt32      i;

    // calculate b_right:
    b_right[ 0 ] = control_points[ 0 ];
    for (i = 1; i < n; ++i)
    {
        b_right[ i ] = (control_points[ i ] * n - b_right[ i - 1 ] * i) *
                       (1.0 / (Real64)(n - i));
    }

    // calculate b_left:
    b_left[ n - 1 ] = control_points[ n ];
    for (i = n - 1; i > 0; --i)
    {
        b_left[i - 1] = (control_points[ i ] * n - b_left[ i ] * (n - i)) *
                        (1.0 / (Real64)i);
    }

    // check for introduced error:
    Real64 quad_error = tol * tol;
    vec3d dist;
    for (i = 0; i < n; ++i)
    {
        dist = b_right[ i ] - b_left[ i ];
        if ( dist.quad_size() > quad_error )
        {
            // debug:
/*            std::cerr<< "Cannot reduce degree, i: " << i <<
                        " left: " << b_left[ i ] <<
                        " right: " << b_right[ i ] << std::endl;*/

            return false;
        }
    }

	control_points.resize( n );

    UInt32 n_half = n >> 1;
    UInt32 n_half1 = ( n + 1 ) >> 1;
	for (i = 0; i < n_half; ++i)
    {
        control_points[ i ] = b_right[ i ];
    }
    for (i = n_half1; i < n; ++i)
    {
        control_points[ i ] = b_left[ i ];
    }
    if ( n_half != n_half1 )
    {
        control_points[ n_half ] = b_left[ n_half ] * 0.5 + b_right[ n_half ] * 0.5;
    }

//    setControlPointVector( b_new );

    return true;
}

