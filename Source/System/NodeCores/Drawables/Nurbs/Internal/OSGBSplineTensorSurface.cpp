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
#include "OSGBSplineTensorSurface.h"

OSG_USING_NAMESPACE


#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BSplineTensorSurface::ff_const_1[]="BEGINBSPLINETENSORSURFACE";
  const char BSplineTensorSurface::ff_const_2[]="DIMENSIONU";
  const char BSplineTensorSurface::ff_const_3[]="DIMENSIONV";
  const char BSplineTensorSurface::ff_const_4[]="NUMBEROFCONTROLPOINTS";

//construction (& destruction, but not here :)
BSplineTensorSurface::BSplineTensorSurface()
{
  dimension_u = dimension_v = -1; //sets invalid value
  control_points.resize( 0 );
}


int BSplineTensorSurface::CheckKnotPoints( const dvector& knots, int dim )
{
  //now check knotvector whether it has
  //(a,a,....a, ......., b,b,....b)
  // |-dim+1-|           |-dim+1-|
  //structure

  dvector::size_type max_index = knots.size() - 1;
  double test_begin = knots[ 0 ], test_end = knots[ max_index ];

  for( dvector::size_type i = 1; i < ( unsigned int ) dim + 1; ++i )
    if ( knots[ i ] != test_begin || knots[ max_index - i ] != test_end ) return -1; //FIXME: double comparison ?!

  return 0;
}

int BSplineTensorSurface::deleteBezierKnot_U( double k )
{
  dvector knots = basis_function_u.getKnotVector();

  if ( k >= knots[ knots.size() - 1 ] ) return -1; // knot is too high
  if ( k <= knots[ 0 ] ) return -2; // knot is too low

  dvector::size_type i = 0;
  int mult = 0;
  while ( knots[ i ] <= k ) {
    if ( knots[ i ] == k ) mult++;
    i++;
  }
  if ( mult < dimension_u + 1 ) return -3; // knot doesn't have enough multiplicity
  i--;

  // delete from knotvector
  knots.erase( knots.begin() + i );
  // set new knot vector
  basis_function_u.setKnotVector( knots );
  // delete control points from the control point mesh corresponding to just deleted knot
  control_points.erase( control_points.begin() + i - dimension_u );
  return 0;

}

int BSplineTensorSurface::deleteBezierKnot_V( double k )
{
  dvector knots = basis_function_v.getKnotVector();

  if ( k >= knots[ knots.size() - 1 ] ) return -1; // knot is too high
  if ( k <= knots[ 0 ] ) return -2; // knot is too low

  dvector::size_type i = 0;
  int mult = 0;
  while ( knots[ i ] <= k ) {
    if ( knots[ i ] == k ) mult++;
    i++;
  }
  if ( mult < dimension_v + 1 ) return -3; // knot doesn't have enough multiplicity
  i--;

  // delete from knotvector
  knots.erase( knots.begin() + i );
  // set new knot vector
  basis_function_v.setKnotVector( knots );
  // delete control points from the control point mesh corresponding to just deleted knot
  for (vec3dvector::size_type j = 0; j < control_points.size(); j++ ) {
    control_points[ j ].erase( control_points[ j ].begin() + i - dimension_v );
  }
  return 0;
}


//setup functions
int BSplineTensorSurface::setKnotsAndDimension( const dvector& knots_u, int dim_u, const dvector& knots_v, int dim_v )
{
  if ( dim_u < 1 || dim_v < 1 ) return -1; //invalid dimension

  dvector::size_type max_index = knots_u.size() - 1;
  if ( max_index < 3 ) return -2; //here's an implicit check fer structure, see below
  if ( CheckKnotPoints( knots_u, dim_u ) ) return -3;

  max_index = knots_v.size() - 1;
  if ( max_index < 3 ) return -2; //here's an implicit check fer structure, see below
  if ( CheckKnotPoints( knots_v, dim_v ) ) return -3;

  dimension_u = dim_u; dimension_v = dim_v;
  if ( basis_function_u.setKnotVector( knots_u ) ) return -4; //error in BSplineBasisFunction.setKno...
  if ( basis_function_v.setKnotVector( knots_v ) ) return -4; //error in BSplineBasisFunction.setKno...

  return 0;
}

void BSplineTensorSurface::setControlPointMatrix( const vec3dmatrix &cps )
{
  // FIXME: check that this is really a matrix
  control_points = cps;
}

//query functions
dvector& BSplineTensorSurface::getKnotVector_U( void )
{
  return basis_function_u.getKnotVector();
}

dvector& BSplineTensorSurface::getKnotVector_V( void )
{
  return basis_function_v.getKnotVector();
}

void BSplineTensorSurface::getParameterInterval_U( double &minpar, double &maxpar )
{
  basis_function_u.getParameterInterval( minpar, maxpar );
}

void BSplineTensorSurface::getParameterInterval_V( double &minpar, double &maxpar )
{
  basis_function_v.getParameterInterval( minpar, maxpar );
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
//! Read the surface parameters from a given input stream.
/*!
 *
 * \param infile the stream from which the surface should be read.
 * \return zero on success, a negative value on failure.
 *
 */
int BSplineTensorSurface::read( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];


  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; //yeah, bad file format again
  infile >> dimension_u >> std::ws;
  if ( dimension_u < 1 ) return -2; //ah, bad dimension

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_3 ) )  return -1; //yeah, bad file format again
  infile >> dimension_v >> std::ws;
  if ( dimension_v < 1 ) return -2; //ah, bad dimension

   
  if ( basis_function_u.read( infile ) ) return -3; //error reading basis function
  if ( CheckKnotPoints( basis_function_u.getKnotVector(), dimension_u ) ) return -4;
  infile >> std::ws;
  if ( basis_function_v.read( infile ) ) return -3; //error reading basis function
  if ( CheckKnotPoints( basis_function_v.getKnotVector(), dimension_v ) ) return -4;
  infile >> std::ws;

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_4 ) ) return -1; //bad file format once again

  vec3dmatrix::size_type num_of_cps_u;
  vec3dvector::size_type num_of_cps_v;
  infile >> num_of_cps_u >> num_of_cps_v >> std::ws;
  if ( num_of_cps_u < 1 || num_of_cps_v < 1 ) return -5; //too few control points
  control_points.resize( num_of_cps_u ); //FIXME: whatif not enoght memory?
  for( dvector::size_type u = 0; u < num_of_cps_u; ++u ) {
    control_points[ u ].resize( num_of_cps_v );  //FIXME: not enough mem, exception thrown by STL
    for( dvector::size_type v = 0; v < num_of_cps_v; ++v ) {
      vec3d cp;
      infile >> cp.x >> cp.y >> cp.z >> std::ws;
      control_points[ u ][ v ] = cp; //FIXME: ya see, we need ERROR CHECKS!!!
    }
  }

  return 0;

}

//! Write the surface parameters out to a given output stream.
/*!
 *
 * \param outfile the stream into which the surface should be written.
 * \return zero on success, a negative value on failure.
 *
 */

int BSplineTensorSurface::write( std::ofstream &outfile )
{
  //FIXME: maybe we need more checks!!!
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  outfile << ff_const_2 << " " << dimension_u << std::endl;
  outfile << ff_const_3 << " " << dimension_v << std::endl;
  basis_function_u.write( outfile );
  basis_function_v.write( outfile );
  vec3dmatrix::size_type num_of_cps_u = control_points.size();
  vec3dvector::size_type num_of_cps_v = control_points[0].size();//FIXME:what if it's not initialized yet
  outfile << ff_const_4 << " " << num_of_cps_u << " " << num_of_cps_v << std::endl;
  for( dvector::size_type u = 0; u < num_of_cps_u; ++u )
    for ( dvector::size_type v = 0; v < num_of_cps_v; ++v ) {
    vec3d cp = control_points[ u ][ v ];
    outfile << cp.x << " " << cp.y << " " << cp.z << std::endl;
  }
  return 0;
}


//! Compute the surface at a given (u,v) point in parameter space.
/*!
 *
 * \param uv the point (in parameter space) where the surface should be
 *           computed.
 * \param error flag to indicate if an error happened. It is set to 0
 *              if everything went fine, otherwise to a negative value.
 * \return the value of the surface in 3D space.
 *
 */
vec3d BSplineTensorSurface::compute( vec2d uv, int &error )
{
  //FIXME: verification before goin' into computation!!
  double *nu;
  int span_u = basis_function_u.computeAllNonzero( uv.x, dimension_u, nu );
  double *nv;
  int span_v = basis_function_v.computeAllNonzero( uv.y, dimension_v, nv );

  vec3d result( 0.0, 0.0, 0.0 );
  if ( span_u < 0 || span_v < 0 ) {
    std::cerr << "spanu: " << span_u << " spanv: " << span_v << std::endl;
    error = ( span_u < 0 ) ? span_u : span_v;
	if( span_u >= 0 ) delete[ ] nu;
	if( span_v >= 0 ) delete[ ] nv;
    return result;//error occured in BSplineBasisFunction.computeAll...
  }

  unsigned int	index_v = span_v - dimension_v;
  vec3d			temp;
  unsigned int	index_u;
  for( int l = 0; l <= dimension_v; ++l )
  {
    temp.x = temp.y = temp.z = 0.0;
    index_u = span_u - dimension_u;
    for( vec3dmatrix::size_type k = 0; k <= ( unsigned int ) dimension_u; ++k )
	{
      temp += control_points[ index_u ][ index_v ] * nu[ k ];
	  ++index_u;
	}
	++index_v;
    result += temp * nv[ l ];
  }
  delete[ ] nu;
  delete[ ] nv;

  return ( result );
}


//! Compute the surface normal at a given (u,v) point in parameter space.
/*!
 *
 * \param uv the point (in parameter space) where the surface should be
 *           computed.
 * \param error flag to indicate if an error happened. It is set to 0
 *              if everything went fine, otherwise to a negative value.
 * \return the value of the surface in 3D space.
 *
 */
Vec3f BSplineTensorSurface::computeNormal( vec2d clUV, int &riError, Pnt3f &rclPos )
{
	int							i_uspan;
	int							i_vspan;
	double						**ppd_nu;
	double						**ppd_nv;
	vec3d						cl_temp;
	Vec3f						cl_normal;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*pcl_temp;
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;

	i_uspan = basis_function_u.computeDersBasisFuns( clUV.x, dimension_u, ppd_nu, 1 );
	i_vspan = basis_function_v.computeDersBasisFuns( clUV.y, dimension_v, ppd_nv, 1 );
	if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
	{
		riError = -1;
		return cl_normal;
	}

//	vvcl_skl.resize( 2 );
//	vvcl_skl[ 0 ].resize( 2 );
//	vvcl_skl[ 1 ].resize( 2 );
	pcl_temp = new vec3d[ dimension_v + 1 ];
//	vcl_temp.resize( dimension_v + 1 );

	for( i_k = 0; i_k <= 1; ++i_k )
	{
		i_v = i_vspan - dimension_v;
		for( i_s = 0; i_s <= dimension_v; ++i_s )
		{
			pcl_temp[ i_s ].x = pcl_temp[ i_s ].y = pcl_temp[ i_s ].z = 0.0;
			i_u = i_uspan - dimension_u;
			for( i_r = 0; i_r <= dimension_u; ++i_r )
			{
				pcl_temp[ i_s ] += control_points[ i_u ][ i_v ] * ppd_nu[ i_k ][ i_r ];
				++i_u;
			}
			++i_v;
		}
		for( i_l = 0; i_l <= 1 - i_k; ++i_l )
		{
			aacl_skl[ i_k ][ i_l ].x = aacl_skl[ i_k ][ i_l ].y = aacl_skl[ i_k ][ i_l ].z = 0.0;
			for( i_s = 0; i_s <= dimension_v; ++i_s )
			{
				aacl_skl[ i_k ][ i_l ] += pcl_temp[ i_s ] * ppd_nv[ i_l ][ i_s ];
			}
		}
	}

	correctDers( clUV, aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
	cl_temp = aacl_skl[ 1 ][ 0 ].cross( aacl_skl[ 0 ][ 1 ] );
	d_len = cl_temp.quad_size( );
	if( d_len < DCTP_EPS * DCTP_EPS )
	{
		cl_normal[ 0 ] = cl_normal[ 1 ] = cl_normal[ 2 ] = 0.0;
		riError = -2;
	}
	else
	{
		cl_temp *= 1.0 / sqrt( d_len );
		riError = 0;
		cl_normal[ 0 ] = cl_temp.x;
		cl_normal[ 1 ] = cl_temp.y;
		cl_normal[ 2 ] = cl_temp.z;
	}

	rclPos[ 0 ] = aacl_skl[ 0 ][ 0 ].x;
	rclPos[ 1 ] = aacl_skl[ 0 ][ 0 ].y;
	rclPos[ 2 ] = aacl_skl[ 0 ][ 0 ].z;

	// clean up allocated memory
	delete[ ] ppd_nu[ 0 ];
	delete[ ] ppd_nu[ 1 ];
	delete[ ] ppd_nv[ 0 ];
	delete[ ] ppd_nv[ 1 ];
	delete[ ] ppd_nu;
	delete[ ] ppd_nv;
	delete[ ] pcl_temp;

	return cl_normal;
}


vec3d BSplineTensorSurface::computeNormal( vec2d clUV, int &riError, vec3d &rclPos )
{
	int							i_uspan;
	int							i_vspan;
	double						**ppd_nu;
	double						**ppd_nv;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*pcl_temp;
	vec3d						cl_normal;
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;

	i_uspan = basis_function_u.computeDersBasisFuns( clUV.x, dimension_u, ppd_nu, 1 );
	i_vspan = basis_function_v.computeDersBasisFuns( clUV.y, dimension_v, ppd_nv, 1 );
	if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
	{
		riError = -1;
		return cl_normal;
	}

	pcl_temp = new vec3d[ dimension_v + 1 ];

	for( i_k = 0; i_k <= 1; ++i_k )
	{
		i_v = i_vspan - dimension_v;
		for( i_s = 0; i_s <= dimension_v; ++i_s )
		{
			pcl_temp[ i_s ].x = pcl_temp[ i_s ].y = pcl_temp[ i_s ].z = 0.0;
			i_u = i_uspan - dimension_u;
			for( i_r = 0; i_r <= dimension_u; ++i_r )
			{
				pcl_temp[ i_s ] += control_points[ i_u ][ i_v ] * ppd_nu[ i_k ][ i_r ];
				++i_u;
			}
			++i_v;
		}
		for( i_l = 0; i_l <= 1 - i_k; ++i_l )
		{
			aacl_skl[ i_k ][ i_l ].x = aacl_skl[ i_k ][ i_l ].y = aacl_skl[ i_k ][ i_l ].z = 0.0;
			for( i_s = 0; i_s <= dimension_v; ++i_s )
			{
				aacl_skl[ i_k ][ i_l ] += pcl_temp[ i_s ] * ppd_nv[ i_l ][ i_s ];
			}
		}
	}

	rclPos = aacl_skl[ 0 ][ 0 ];

	correctDers( clUV, aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
	cl_normal = aacl_skl[ 1 ][ 0 ].cross( aacl_skl[ 0 ][ 1 ] );
	d_len = cl_normal.quad_size( );

	if( d_len < DCTP_EPS * DCTP_EPS )
	{
		cl_normal.x = cl_normal.y = cl_normal.z = 0.0;
		riError = -2;
	}
	else
	{
		cl_normal *= 1.0 / sqrt( d_len );
		riError = 0;
	}

	// clean up allocated memory
	delete[ ] ppd_nu[ 0 ];
	delete[ ] ppd_nu[ 1 ];
	delete[ ] ppd_nv[ 0 ];
	delete[ ] ppd_nv[ 1 ];
	delete[ ] ppd_nu;
	delete[ ] ppd_nv;
	delete[ ] pcl_temp;

	return cl_normal;
}


//! Compute the surface normal and texture coordinate at a given (u,v) point in parameter space.
/*!
 *
 * \param uv the point (in parameter space) where the surface should be
 *           computed.
 * \param error flag to indicate if an error happened. It is set to 0
 *              if everything went fine, otherwise to a negative value.
 * \return the value of the surface in 3D space.
 *
 */
vec3d BSplineTensorSurface::computeNormalTex( vec2d &rclUV, 
                                              int &riError, 
                                              vec3d &rclPos, 
                                              vec2d &rclTexCoord, 
                                              const std::vector< std::vector< Pnt2f > > *cpvvclTexCP )
{
	int							i_uspan;
	int							i_vspan;
	double						**ppd_nu;
	double						**ppd_nv;
	vec3d						cl_normal;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*pcl_temp;
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;
	double						*pd_nvl;
	double						*pd_nuk;
	vec2d						cl_temp;

	i_uspan = basis_function_u.computeDersBasisFuns( rclUV.x, dimension_u, ppd_nu, 1 );
	i_vspan = basis_function_v.computeDersBasisFuns( rclUV.y, dimension_v, ppd_nv, 1 );
	if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
	{
		riError = -1;
		return cl_normal;
	}

//	vvcl_skl.resize( 2 );
//	vvcl_skl[ 0 ].resize( 2 );
//	vvcl_skl[ 1 ].resize( 2 );
	pcl_temp = new vec3d[ dimension_v + 1 ];
//	vcl_temp.resize( dimension_v + 1 );

	for( i_k = 0; i_k <= 1; ++i_k )
	{
		i_v = i_vspan - dimension_v;
		for( i_s = 0; i_s <= dimension_v; ++i_s )
		{
			pcl_temp[ i_s ].x = pcl_temp[ i_s ].y = pcl_temp[ i_s ].z = 0.0;
			i_u = i_uspan - dimension_u;
			for( i_r = 0; i_r <= dimension_u; ++i_r )
			{
				pcl_temp[ i_s ] += control_points[ i_u ][ i_v ] * ppd_nu[ i_k ][ i_r ];
				++i_u;
			}
			++i_v;
		}
		for( i_l = 0; i_l <= 1 - i_k; ++i_l )
		{
			aacl_skl[ i_k ][ i_l ].x = aacl_skl[ i_k ][ i_l ].y = aacl_skl[ i_k ][ i_l ].z = 0.0;
			for( i_s = 0; i_s <= dimension_v; ++i_s )
			{
				aacl_skl[ i_k ][ i_l ] += pcl_temp[ i_s ] * ppd_nv[ i_l ][ i_s ];
			}
		}
	}

	rclPos = aacl_skl[ 0 ][ 0 ];

	correctDers( rclUV, aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
	cl_normal = aacl_skl[ 1 ][ 0 ].cross( aacl_skl[ 0 ][ 1 ] );
	d_len = cl_normal.quad_size( );

	if( d_len < DCTP_EPS * DCTP_EPS )
	{
		cl_normal.x = cl_normal.y = cl_normal.z = 0.0;
		riError = -2;
	}
	else
	{
		cl_normal *= 1.0 / sqrt( d_len );
		riError = 0;
	}

	// calculate texture coord
	rclTexCoord.x = rclTexCoord.y = 0.0;
	i_v = i_vspan - dimension_v;
	pd_nvl = ppd_nv[ 0 ];
	for( i_l = 0; i_l <= dimension_v; ++i_l )
	{
		cl_temp.x = cl_temp.y = 0.0;
		i_u = i_uspan - dimension_u;
		pd_nuk = ppd_nu[ 0 ];
		for( i_k = 0; i_k <= dimension_u; ++i_k )
		{
			cl_temp.x += ( *cpvvclTexCP )[ i_u ][ i_v ].x() * *pd_nuk;
			cl_temp.y += ( *cpvvclTexCP )[ i_u ][ i_v ].y() * *pd_nuk;
			++i_u;
			++pd_nuk;
		}
		++i_v;
		rclTexCoord += cl_temp * *pd_nvl;
		++pd_nvl;
	}

	// clean up allocated memory
	delete[ ] ppd_nu[ 0 ];
	delete[ ] ppd_nu[ 1 ];
	delete[ ] ppd_nv[ 0 ];
	delete[ ] ppd_nv[ 1 ];
	delete[ ] ppd_nu;
	delete[ ] ppd_nv;
	delete[ ] pcl_temp;

	return cl_normal;
}


//! Insert a u knot into the surface. Returns < 0 on error, otherwise 0.
/*!
 *
 * \param k the knot to be inserted.
 * \return zero on success, and a negative integer if some error occured.
 *
 */
int BSplineTensorSurface::insertKnot_U( double k )
{
  dvector knots = basis_function_u.getKnotVector();
  int span = basis_function_u.insertKnot( k );
  if ( span < 0 ) return span; // some error happened

  vec3dmatrix newcps( control_points.size() + 1 );
  vec3dvector::size_type i;
  for ( i = 0; i < newcps.size(); i++ ) {
    newcps[ i ].resize( control_points[ 0 ].size() ); // this must be 0 (or at least < newcps.size() - 1
  }
  for ( i = 0; ( int ) i <= span - dimension_u; i++ )
    newcps[ i ] = control_points[ i ];
  for ( i = span - dimension_u + 1; i <= ( unsigned int ) span; i++ ) {
    double alpha;
    if ( knots[ i + dimension_u ] != knots[ i ] )
      alpha = ( k - knots[ i ] ) / ( knots[ i + dimension_u ] - knots[ i ]);
    else
      alpha = 0;
    for ( vec3dvector::size_type j = 0; j < newcps[ i ].size(); j++ ) {
      newcps[ i ][ j ] = control_points[ i ][ j ] * alpha + control_points[ i - 1 ][ j ] * ( 1 - alpha );
    } // j
  } // i
  for ( i = span + 1; i < newcps.size(); i++ ) {
    newcps[ i ] = control_points[ i - 1 ];
  }
  control_points = newcps;
  return span;
}


//! Insert v knot into the surface. Returns < 0 on error, otherwise 0.
/*!
 *
 * \param k the knot to be inserted.
 * \return zero on success, and a negative integer if some error occured.
 *
 */
int BSplineTensorSurface::insertKnot_V( double k )
{
  dvector knots = basis_function_v.getKnotVector();
  int span = basis_function_v.insertKnot( k );
  if ( span < 0 ) return span; // some error happened
  vec3dmatrix newcps( control_points.size() );
  vec3dvector::size_type i, j;
  for ( i = 0; i < newcps.size(); i++ )
    newcps[ i ].resize( control_points[ i ].size() + 1 );

  for ( i = 0; i < control_points.size(); i++ )
    for ( j = 0; j <= span - dimension_v; j++ )
       newcps[ i ][ j ] = control_points[ i ][ j ];

  // precalculate alpha values
  dvector alphavec( dimension_v  );

  for ( j = span - dimension_v + 1; j <= span; j++ ) {
      if ( knots[ j + dimension_v ] != knots[ j ] )
        alphavec[ j - span + dimension_v - 1 ] = ( k - knots[ j ] ) / ( knots[ j + dimension_v ] - knots[ j ]);
      else
        alphavec[ j - span + dimension_v - 1 ] = 0;
  }
  for ( i = 0; i < control_points.size(); i++ )
    for ( j = span - dimension_v + 1; j <= span; j++ ) {
      double alpha = alphavec[ j - span + dimension_v - 1 ];
      newcps[ i ][ j ] = control_points[ i ][ j ] * alpha + control_points[ i  ][ j - 1 ] * ( 1 - alpha );
    } // j

  for ( i = 0; i < control_points.size(); i++ )
    for ( j = span + 1; j < newcps[ i ].size(); j++ )
       newcps[ i ][ j ] = control_points[ i ][ j - 1];

  control_points = newcps;
  return span;
}

//! Convert a surface into Bezier patches.
/*!
 * This function converts a surface into Bezier patches with 
 * appropriate knot insertions. (And if necessary knot deletions. )
 * Leaves the original surface unchanged.
 * 
 * \param beziers the matrix of BezierTensorSurface's to store the patches 
 * \param upars the u parameter vector to store where each patch begins in the 
 *        original parameter space of the surface
 * \param vpars the same for v parameter.
 * \return zero on success, and a negative integer if some error occured.
 * 
 * For example, for patch (i, j) it covers the parameter space of the
 * original surface between upars[ i ]..upars[ i + 1 ] and
 * vpars[ j ]..vpars[ j + 1 ].
 */
int BSplineTensorSurface::makeBezier( beziersurfacematrix &beziers, dvector &upars, dvector &vpars )
{
  double firstknotu, lastknotu;
  double firstknotv, lastknotv;
  basis_function_u.getParameterInterval( firstknotu, lastknotu );
  basis_function_v.getParameterInterval( firstknotv, lastknotv );
  dvector uknots = basis_function_u.getKnotVector();
  dvector vknots = basis_function_v.getKnotVector();
  dvector origuknots = uknots;  // backup original curve characteristics
  dvector origvknots = vknots; // same here
  vec3dmatrix origcps = control_points; // same here
  double prevknot = firstknotu;
  int mult = 0;
  int err;
  unsigned int i;

  // first convert along u knots
  for ( i = 1; i < uknots.size(); i++) {
    double actk = uknots[ i ];
    if ( actk == prevknot ) 
      mult++;
    else {
      for ( int j = mult + 1; j < dimension_u; j++ ) {//each interior knot must have the multiplicity of dimension -1
        //std::cerr << "about to insert uknot: " << prevknot << std::endl;
        err = insertKnot_U( prevknot );
        //std::cerr << "inserted uknot..." << std::endl;
        if ( err < 0 ) return err; // some error happened during insertKnot
		err = 0;
      }
      if ( prevknot != firstknotu && prevknot != lastknotu ) {
        for ( int j = mult; j > dimension_u - 1; j-- ) {
          //std::cerr << "about to delete knot: " << prevknot << std::endl;
          err = deleteBezierKnot_U( prevknot );
          //std::cerr << "deleted knot..." << std::endl;
          if ( err ) return err; // some error happened during deleteBezierKnot
        }
      }
      mult = 0;
    }
    prevknot = actk;
  }

  // now convert along v knots
  mult = 0;
  prevknot = firstknotv;
  for (i = 1; i < vknots.size(); i++) {
    double actk = vknots[ i ];
    if ( actk == prevknot ) 
      mult++;
    else {
      for ( int j = mult + 1; j < dimension_v; j++ ) {//each interior knot must have the multiplicity of dimension -1
//        std::cerr << "about to insert vknot: " << prevknot << std::endl;
        err = insertKnot_V( prevknot );
//        std::cerr << "inserted vknot..." << std::endl;
        if ( err < 0 ) return err; // some error happened during insertKnot
		err = 0;
      }
      if ( prevknot != firstknotv && prevknot != lastknotv ) {
        for ( int j = mult; j > dimension_v - 1; j-- ) {
//          std::cerr << "about to delete knot: " << prevknot << std::endl;
          err = deleteBezierKnot_V( prevknot );
//          std::cerr << "deleted knot..." << std::endl;
          if ( err ) return err; // some error happened during deleteBezierKnot
        }
      }
      mult = 0;
    }
    prevknot = actk;
  }

  // now do the actual conversation into nxm bezier segments
  uknots = basis_function_u.getKnotVector(); // FIXME: it could be more efficient.
  int unum_of_beziers = ( uknots.size() - 2 ) / dimension_u - 1;
  if ( ( unum_of_beziers * dimension_u + 2 ) != uknots.size() - dimension_u ) {
    basis_function_u.setKnotVector( origuknots );
    basis_function_v.setKnotVector( origuknots );
    control_points = origcps;
    return -5;
  }
  vknots = basis_function_v.getKnotVector(); // FIXME: it could be more efficient.
  int vnum_of_beziers = ( vknots.size() - 2 ) / dimension_v - 1;
  if ( ( vnum_of_beziers * dimension_v + 2 ) != vknots.size() - dimension_v ) {
    basis_function_u.setKnotVector( origuknots );
    basis_function_v.setKnotVector( origuknots );
    control_points = origcps;
    return -5;
  }

  beziers.resize( unum_of_beziers );
  upars.resize ( unum_of_beziers + 1 );
  vpars.resize ( vnum_of_beziers + 1 );
  for ( i = 0; i < unum_of_beziers + 1; i++ ) 
    upars[ i ] = uknots[ 1 + dimension_u * i ];
  for (i = 0; i < vnum_of_beziers + 1; i++ ) 
    vpars[ i ] = vknots[ 1 + dimension_v * i ];
  for ( i = 0; i < unum_of_beziers; i++ )
    beziers[ i ].resize( vnum_of_beziers );
  vec3dmatrix beziercps( dimension_u + 1 );
  for ( i = 0; i < dimension_u + 1; i++ )  
    beziercps[ i ].resize( dimension_v + 1 );

  for ( i = 0; i < unum_of_beziers; i++ ) {
    for ( beziersurfacevector::size_type j = 0; j < vnum_of_beziers; j++ ) {
      for (vec3dvector::size_type u = 0; u < dimension_u + 1; u++ ) {
        for (vec3dvector::size_type v = 0; v < dimension_v + 1; v++ ) {
          beziercps[ u ][ v ] = control_points[ i * dimension_u + u][ j * dimension_v + v];
        } // v
      } // u
      beziers[ i ][ j ].setControlPointMatrix( beziercps );
    } // j
  } // i

  // restore original curve
  basis_function_u.setKnotVector( origuknots );
  basis_function_v.setKnotVector( origvknots );
  control_points = origcps;
  return 0;

}


int BSplineTensorSurface::getSplitParams( dvector &upars, dvector &vpars )
{
	dvector	&uknots = basis_function_u.getKnotVector();
	dvector	&vknots = basis_function_v.getKnotVector();
	int		unum_of_beziers = ( uknots.size() - 2 ) / dimension_u - 1;
	int		vnum_of_beziers = ( vknots.size() - 2 ) / dimension_v - 1;
	int		i;

	upars.resize ( unum_of_beziers + 1 );
	vpars.resize ( vnum_of_beziers + 1 );
	for( i = 0; i < unum_of_beziers + 1; i++ ) 
		upars[ i ] = uknots[ 1 + dimension_u * i ];
	for( i = 0; i < vnum_of_beziers + 1; i++ ) 
		vpars[ i ] = vknots[ 1 + dimension_v * i ];

	return 0;
}



// subdivide surface at midpoint into 4 bezier surfaces
int BSplineTensorSurface::midPointSubDivision( std::vector< std::vector< BSplineTensorSurface > > &rvvcl_newbspline )
{
	double					d_min;
	double					d_max;
	unsigned int				ui_cnt;
	unsigned int				ui_idx;
	int					i_span;
	std::vector< std::vector< vec3d > >	vvcl_cp;
	unsigned int				ui_cpy;
	unsigned int				ui_cpy_cnt;

	rvvcl_newbspline.resize( 2 );
	rvvcl_newbspline[ 0 ].resize( 2 );
	rvvcl_newbspline[ 1 ].resize( 2 );

	// insert knots in u direction
	rvvcl_newbspline[ 0 ][ 0 ] = *this;
	rvvcl_newbspline[ 0 ][ 0 ].getParameterInterval_U( d_min, d_max );
	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getDimension_U( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		i_span = rvvcl_newbspline[ 0 ][ 0 ].insertKnot_U( ( d_min + d_max ) * 0.5 );
	}
	i_span -= dimension_u - 2;
	rvvcl_newbspline[ 0 ][ 1 ].dimension_u = dimension_u;
	rvvcl_newbspline[ 1 ][ 0 ].dimension_u = dimension_u;
	rvvcl_newbspline[ 1 ][ 1 ].dimension_u = dimension_u;
	rvvcl_newbspline[ 0 ][ 1 ].dimension_v = dimension_v;
	rvvcl_newbspline[ 1 ][ 0 ].dimension_v = dimension_v;
	rvvcl_newbspline[ 1 ][ 1 ].dimension_v = dimension_v;

	// split in u direction
	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx <= dimension_u; ++ui_idx )
	{
		rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_U( ).push_back(
			rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( )[ i_span ] );
	}
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( ).push_back(
			rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( )[ ui_idx ] );
		rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_U( ).push_back(
			rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( )[ ui_idx + dimension_u + 1 ] );
	}
	rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).resize( i_span );
	rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( ).resize( i_span + dimension_u );
	rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( ).push_back( 
		rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( )[ i_span + dimension_u - 1 ] );
	rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( ) = rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( );

	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_u - 1;
	while( rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( )[ ui_cnt ] == rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( )[ ui_idx ] )
	{
		rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( ).pop_back( );
		rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).pop_back( );
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	std::ofstream	cl_write;

	cl_write.open( "subdiv.txt" );

	write( cl_write );
	rvvcl_newbspline[ 0 ][ 0 ].write( cl_write );
	rvvcl_newbspline[ 1 ][ 0 ].write( cl_write );
#endif*/

	// insert knots in v direction
	rvvcl_newbspline[ 0 ][ 0 ].getParameterInterval_V( d_min, d_max );
	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getDimension_V( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		i_span = rvvcl_newbspline[ 0 ][ 0 ].insertKnot_V( ( d_min + d_max ) * 0.5 );
		i_span = rvvcl_newbspline[ 1 ][ 0 ].insertKnot_V( ( d_min + d_max ) * 0.5 );
	}
	i_span -= dimension_v - 2;

	// split in v direction
	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( )[ 0 ].size( );
	for( ui_idx = 0; ui_idx <= dimension_v; ++ui_idx )
	{
		rvvcl_newbspline[ 0 ][ 1 ].getKnotVector_V( ).push_back(
			rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( )[ i_span ] );
		rvvcl_newbspline[ 1 ][ 1 ].getKnotVector_V( ).push_back(
			rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( )[ i_span ] );
	}
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		ui_cpy_cnt = rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).size( );
		rvvcl_newbspline[ 0 ][ 1 ].getControlPointMatrix( ).resize( ui_cpy_cnt );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvvcl_newbspline[ 0 ][ 1 ].getControlPointMatrix( )[ ui_cpy ].push_back(
				rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( )[ ui_cpy ][ ui_idx ] );
		}
		ui_cpy_cnt = rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( ).size( );
		rvvcl_newbspline[ 1 ][ 1 ].getControlPointMatrix( ).resize( ui_cpy_cnt );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvvcl_newbspline[ 1 ][ 1 ].getControlPointMatrix( )[ ui_cpy ].push_back(
				rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( )[ ui_cpy ][ ui_idx ] );
		}
		rvvcl_newbspline[ 0 ][ 1 ].getKnotVector_V( ).push_back(
			rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( )[ ui_idx + dimension_v + 1 ] );
		rvvcl_newbspline[ 1 ][ 1 ].getKnotVector_V( ).push_back(
			rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( )[ ui_idx + dimension_v + 1 ] );
	}
	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( )[ ui_idx ].resize( i_span );
	}
	ui_cnt = rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( )[ ui_idx ].resize( i_span );
	}
	rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( ).resize( i_span + dimension_v );
	rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( ).push_back( 
		rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( )[ i_span + dimension_v - 1 ] );
	rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( ).resize( i_span + dimension_v );
	rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( ).push_back( 
		rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( )[ i_span + dimension_v - 1 ] );
	rvvcl_newbspline[ 0 ][ 1 ].getKnotVector_U( ) = rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_U( );
	rvvcl_newbspline[ 1 ][ 1 ].getKnotVector_U( ) = rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_U( );

	ui_cnt = rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_v - 1;
	while( rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( )[ ui_cnt ] == rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( )[ ui_idx ] )
	{
		rvvcl_newbspline[ 0 ][ 0 ].getKnotVector_V( ).pop_back( );
		ui_cpy_cnt = rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( ).size( );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvvcl_newbspline[ 0 ][ 0 ].getControlPointMatrix( )[ ui_cpy ].pop_back( );
		}
		rvvcl_newbspline[ 1 ][ 0 ].getKnotVector_V( ).pop_back( );
		ui_cpy_cnt = rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( ).size( );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvvcl_newbspline[ 1 ][ 0 ].getControlPointMatrix( )[ ui_cpy ].pop_back( );
		}
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	rvvcl_newbspline[ 0 ][ 0 ].write( cl_write );
	rvvcl_newbspline[ 1 ][ 0 ].write( cl_write );
	rvvcl_newbspline[ 0 ][ 1 ].write( cl_write );
	rvvcl_newbspline[ 1 ][ 1 ].write( cl_write );

	cl_write.close( );
#endif*/

	return 0;
}


// subdivide surface at midpoint into 2 bezier surfaces
int BSplineTensorSurface::midPointSubDivisionU( std::vector< BSplineTensorSurface > &rvcl_newbspline )
{
	double					d_min;
	double					d_max;
	unsigned int				ui_cnt;
	unsigned int				ui_idx;
	int					i_span;
	std::vector< std::vector< vec3d > >	vvcl_cp;
	unsigned int				ui_cpy;
	unsigned int				ui_cpy_cnt;

	rvcl_newbspline.resize( 2 );

	// insert knots in u direction
	rvcl_newbspline[ 0 ] = *this;
	getParameterInterval_U( d_min, d_max );
	ui_cnt = rvcl_newbspline[ 0 ].getDimension_U( );
	for( ui_idx = 0; ui_idx <= ui_cnt; ++ui_idx )
	{
		i_span = rvcl_newbspline[ 0 ].insertKnot_U( ( d_min + d_max ) * 0.5 );
	}
	i_span -= dimension_u - 2;
	rvcl_newbspline[ 1 ].dimension_u = dimension_u;
	rvcl_newbspline[ 1 ].dimension_v = dimension_v;

	// split in u direction
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx <= dimension_u; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getKnotVector_U( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_U( )[ i_span ] );
	}
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getControlPointMatrix( ).push_back(
			rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_idx ] );
		rvcl_newbspline[ 1 ].getKnotVector_U( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_idx + dimension_u + 1 ] );
	}
	rvcl_newbspline[ 0 ].getControlPointMatrix( ).resize( i_span );
	rvcl_newbspline[ 0 ].getKnotVector_U( ).resize( i_span + dimension_u );
	rvcl_newbspline[ 0 ].getKnotVector_U( ).push_back( 
		rvcl_newbspline[ 0 ].getKnotVector_U( )[ i_span + dimension_u - 1 ] );
	rvcl_newbspline[ 1 ].getKnotVector_V( ) = rvcl_newbspline[ 0 ].getKnotVector_V( );

	ui_cnt = rvcl_newbspline[ 0 ].getKnotVector_U( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_u - 1;
	while( rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_cnt ] == rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_idx ] )
	{
		rvcl_newbspline[ 0 ].getKnotVector_U( ).pop_back( );
		rvcl_newbspline[ 0 ].getControlPointMatrix( ).pop_back( );
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	std::ofstream	cl_write;

	cl_write.open( "subdiv.txt" );

	write( cl_write );
	rvcl_newbspline[ 0 ].write( cl_write );
	rvcl_newbspline[ 1 ].write( cl_write );

	cl_write.close( );
#endif*/

	return 0;
}


// subdivide surface at midpoint into 2 bezier surfaces
int BSplineTensorSurface::midPointSubDivisionV( std::vector< BSplineTensorSurface > &rvcl_newbspline )
{
	double					d_min;
	double					d_max;
	unsigned int				ui_cnt;
	unsigned int				ui_idx;
	int					i_span;
	std::vector< std::vector< vec3d > >	vvcl_cp;
	unsigned int				ui_cpy;
	unsigned int				ui_cpy_cnt;

	rvcl_newbspline.resize( 2 );

	// insert knots in u direction
	rvcl_newbspline[ 0 ] = *this;
	getParameterInterval_V( d_min, d_max );
	ui_cnt = rvcl_newbspline[ 0 ].getDimension_V( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		i_span = rvcl_newbspline[ 0 ].insertKnot_V( ( d_min + d_max ) * 0.5 );
	}
	i_span -= dimension_v - 2;
	rvcl_newbspline[ 1 ].dimension_u = dimension_u;
	rvcl_newbspline[ 1 ].dimension_v = dimension_v;

	// split in v direction
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( )[ 0 ].size( );
	for( ui_idx = 0; ui_idx <= dimension_v; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getKnotVector_V( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_V( )[ i_span ] );
	}
	ui_cpy_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	rvcl_newbspline[ 1 ].getControlPointMatrix( ).resize( ui_cpy_cnt );
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvcl_newbspline[ 1 ].getControlPointMatrix( )[ ui_cpy ].push_back(
				rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_cpy ][ ui_idx ] );
		}
		rvcl_newbspline[ 1 ].getKnotVector_V( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_idx + dimension_v + 1 ] );
	}
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_idx ].resize( i_span );
	}
	rvcl_newbspline[ 0 ].getKnotVector_V( ).resize( i_span + dimension_v );
	rvcl_newbspline[ 0 ].getKnotVector_V( ).push_back( 
		rvcl_newbspline[ 0 ].getKnotVector_V( )[ i_span + dimension_v - 1 ] );
	rvcl_newbspline[ 1 ].getKnotVector_U( ) = rvcl_newbspline[ 0 ].getKnotVector_U( );

	ui_cnt = rvcl_newbspline[ 0 ].getKnotVector_V( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_v - 1;
	while( rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_cnt ] == rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_idx ] )
	{
		rvcl_newbspline[ 0 ].getKnotVector_V( ).pop_back( );
		ui_cpy_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_cpy ].pop_back( );
		}
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	std::ofstream	cl_write;

	cl_write.open( "subdiv.txt" );

	write( cl_write );
	rvcl_newbspline[ 0 ].write( cl_write );
	rvcl_newbspline[ 1 ].write( cl_write );

	cl_write.close( );
#endif*/

	return 0;
}


// subdivide surface at param into 2 bezier surfaces
int BSplineTensorSurface::subDivisionU( std::vector< BSplineTensorSurface > &rvcl_newbspline, double dSplit )
{
	double					d_min;
	double					d_max;
	unsigned int				ui_cnt;
	unsigned int				ui_idx;
	int					i_span;
	std::vector< std::vector< vec3d > >	vvcl_cp;
	unsigned int				ui_cpy;
	unsigned int				ui_cpy_cnt;

	rvcl_newbspline.clear( );
	rvcl_newbspline.resize( 2 );

	// insert knots in u direction
	rvcl_newbspline[ 0 ] = *this;
	getParameterInterval_U( d_min, d_max );
	ui_cnt = rvcl_newbspline[ 0 ].getDimension_U( );
	for( ui_idx = 0; ui_idx <= ui_cnt; ++ui_idx )
	{
		i_span = rvcl_newbspline[ 0 ].insertKnot_U( d_min + ( d_max - d_min ) * dSplit );
	}
	i_span -= dimension_u - 2;
	rvcl_newbspline[ 1 ].dimension_u = dimension_u;
	rvcl_newbspline[ 1 ].dimension_v = dimension_v;

	// split in u direction
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx <= dimension_u; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getKnotVector_U( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_U( )[ i_span ] );
	}
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getControlPointMatrix( ).push_back(
			rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_idx ] );
		rvcl_newbspline[ 1 ].getKnotVector_U( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_idx + dimension_u + 1 ] );
	}
	rvcl_newbspline[ 0 ].getControlPointMatrix( ).resize( i_span );
	rvcl_newbspline[ 0 ].getKnotVector_U( ).resize( i_span + dimension_u );
	rvcl_newbspline[ 0 ].getKnotVector_U( ).push_back( 
		rvcl_newbspline[ 0 ].getKnotVector_U( )[ i_span + dimension_u - 1 ] );
	rvcl_newbspline[ 1 ].getKnotVector_V( ) = rvcl_newbspline[ 0 ].getKnotVector_V( );

	ui_cnt = rvcl_newbspline[ 0 ].getKnotVector_U( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_u - 1;
	while( rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_cnt ] == rvcl_newbspline[ 0 ].getKnotVector_U( )[ ui_idx ] )
	{
		rvcl_newbspline[ 0 ].getKnotVector_U( ).pop_back( );
		rvcl_newbspline[ 0 ].getControlPointMatrix( ).pop_back( );
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	std::ofstream	cl_write;

	cl_write.open( "subdiv.txt" );

	write( cl_write );
	rvcl_newbspline[ 0 ].write( cl_write );
	rvcl_newbspline[ 1 ].write( cl_write );

	cl_write.close( );
#endif*/

	return 0;
}


// subdivide surface at param into 2 bezier surfaces
int BSplineTensorSurface::subDivisionV( std::vector< BSplineTensorSurface > &rvcl_newbspline, double dSplit )
{
	double					d_min;
	double					d_max;
	unsigned int				ui_cnt;
	unsigned int				ui_idx;
	int					i_span;
	std::vector< std::vector< vec3d > >	vvcl_cp;
	unsigned int				ui_cpy;
	unsigned int				ui_cpy_cnt;

	rvcl_newbspline.clear( );
	rvcl_newbspline.resize( 2 );

	// insert knots in u direction
	rvcl_newbspline[ 0 ] = *this;
	getParameterInterval_V( d_min, d_max );
	ui_cnt = rvcl_newbspline[ 0 ].getDimension_V( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		i_span = rvcl_newbspline[ 0 ].insertKnot_V( d_min + ( d_max - d_min ) * dSplit );
	}
	i_span -= dimension_v - 2;
	rvcl_newbspline[ 1 ].dimension_u = dimension_u;
	rvcl_newbspline[ 1 ].dimension_v = dimension_v;

	// split in v direction
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( )[ 0 ].size( );
	for( ui_idx = 0; ui_idx <= dimension_v; ++ui_idx )
	{
		rvcl_newbspline[ 1 ].getKnotVector_V( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_V( )[ i_span ] );
	}
	ui_cpy_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	rvcl_newbspline[ 1 ].getControlPointMatrix( ).resize( ui_cpy_cnt );
	for( ui_idx = i_span - 1; ui_idx < ui_cnt; ++ui_idx )
	{
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvcl_newbspline[ 1 ].getControlPointMatrix( )[ ui_cpy ].push_back(
				rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_cpy ][ ui_idx ] );
		}
		rvcl_newbspline[ 1 ].getKnotVector_V( ).push_back(
			rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_idx + dimension_v + 1 ] );
	}
	ui_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
	for( ui_idx = 0; ui_idx < ui_cnt; ++ui_idx )
	{
		rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_idx ].resize( i_span );
	}
	rvcl_newbspline[ 0 ].getKnotVector_V( ).resize( i_span + dimension_v );
	rvcl_newbspline[ 0 ].getKnotVector_V( ).push_back( 
		rvcl_newbspline[ 0 ].getKnotVector_V( )[ i_span + dimension_v - 1 ] );
	rvcl_newbspline[ 1 ].getKnotVector_U( ) = rvcl_newbspline[ 0 ].getKnotVector_U( );

	ui_cnt = rvcl_newbspline[ 0 ].getKnotVector_V( ).size( ) - 1;
	ui_idx = ui_cnt - dimension_v - 1;
	while( rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_cnt ] == rvcl_newbspline[ 0 ].getKnotVector_V( )[ ui_idx ] )
	{
		rvcl_newbspline[ 0 ].getKnotVector_V( ).pop_back( );
		ui_cpy_cnt = rvcl_newbspline[ 0 ].getControlPointMatrix( ).size( );
		for( ui_cpy = 0; ui_cpy < ui_cpy_cnt; ++ui_cpy )
		{
			rvcl_newbspline[ 0 ].getControlPointMatrix( )[ ui_cpy ].pop_back( );
		}
		--ui_cnt;
		--ui_idx;
	}

/*#ifdef _DEBUG
	std::ofstream	cl_write;

	cl_write.open( "subdiv.txt" );

	write( cl_write );
	rvcl_newbspline[ 0 ].write( cl_write );
	rvcl_newbspline[ 1 ].write( cl_write );

	cl_write.close( );
#endif*/

	return 0;
}


//new vector-enabled computational functions from Michael
void BSplineTensorSurface::compute( std::vector< vec2d > &rvclUV, 
                                    std::vector< Pnt3f > &rvclPos )

{
	const unsigned int	cui_cnt = rvclUV.size( );
	unsigned int		ui_idx;
	double				*pd_nu;
	double				*pd_nv;
	int					i_span_u = -1;
	int					i_span_v = -1;
	unsigned int		ui_index_v;
	vec3d				*pcl_temp = new vec3d[ dimension_u + 1 ];
	unsigned int		ui_index_u;
	int					i_l;
	int					i_k;
	double				*pd_nul;
	double				*pd_nvk;
	bool				b_u_new;
	bool				b_v_new;
	vec3d				*pcl_templ;
	int					i_old_u;

	rvclPos.resize( cui_cnt );

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
			i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_span_u;
				if( i_span_u >= 0 ) delete[ ] pd_nu;
				i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
				b_u_new = true;
				b_v_new = ( i_old_u != i_span_u ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_span_v >= 0 ) delete[ ] pd_nv;
				i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
				b_v_new = true;
			}
		}

		if( ( i_span_u < 0 ) || ( i_span_v < 0 ) )
		{
			rvclPos[ ui_idx ][0] = rvclPos[ ui_idx ][1]= rvclPos[ ui_idx ][2] = 0.0;
		}
		else if( b_v_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_templ = pcl_temp;
                        vec3d tempposition(0, 0, 0);
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				pcl_templ->x = pcl_templ->y = pcl_templ->z = 0.0;
				ui_index_v = i_span_v - dimension_v;
				pd_nvk = pd_nv;
				for( i_k = 0; i_k <= dimension_v; ++i_k )
				{
					*pcl_templ += control_points[ ui_index_u ][ ui_index_v ] * *pd_nvk;
					++ui_index_v;
					++pd_nvk;
				}
				++ui_index_u;
				tempposition += *pcl_templ * *pd_nul;
				++pd_nul;
				++pcl_templ;
			}
                       rvclPos[ ui_idx ][0] = tempposition.x;
                       rvclPos[ ui_idx ][1] = tempposition.y;
                       rvclPos[ ui_idx ][2] = tempposition.z;
                       
	}
		else if( b_u_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_templ = pcl_temp;
                       vec3d tempposition(0, 0, 0);
		for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				++ui_index_u;
				tempposition += *pcl_templ * *pd_nul;
				++pd_nul;
				++pcl_templ;
			}
                       rvclPos[ ui_idx ][0] = tempposition.x;
                       rvclPos[ ui_idx ][1] = tempposition.y;
                       rvclPos[ ui_idx ][2] = tempposition.z;
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclPos[ ui_idx ] = rvclPos[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
		++g_uiSameComp;
#endif
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	if( i_span_u >= 0 ) delete[ ] pd_nu;
	if( i_span_v >= 0 ) delete[ ] pd_nv;
	delete[ ] pcl_temp;

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::computeNormal( std::vector< vec2d > &rvclUV, 
                                          std::vector< Pnt3f > &rvclPos, 
                                          std::vector< Vec3f > &rvclNorm )
{
	const unsigned int			cui_cnt = rvclUV.size( );
	unsigned int				ui_idx;
	int							i_uspan = -1;
	int							i_vspan = -1;
	double						**ppd_nu;
	double						**ppd_nv;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*apcl_temp[ 2 ];
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;
	bool						b_u_new;
	bool						b_v_new;
	vec3d						*pcl_temps;
	double						*pd_nuls;
	double						*pd_nvkr;
	vec3d						*pcl_sklkl;
	int							i_old_u;

//	std::cerr << dimension_u << " " << dimension_v << std::endl;

	apcl_temp[ 0 ] = new vec3d[ dimension_u + 1 ];
	apcl_temp[ 1 ] = new vec3d[ dimension_u + 1 ];

	rvclPos.resize( cui_cnt );
	rvclNorm.resize( cui_cnt );

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
			i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_uspan;
				if( i_uspan >= 0 )
				{
					delete[ ] ppd_nu[ 0 ];
					delete[ ] ppd_nu[ 1 ];
					delete[ ] ppd_nu;
				}
				i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
				b_u_new = true;
				b_v_new = ( i_old_u != i_uspan ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_vspan >= 0 )
				{
					delete[ ] ppd_nv[ 0 ];
					delete[ ] ppd_nv[ 1 ];
					delete[ ] ppd_nv;
				}
				i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
				b_v_new = true;
			}
		}
		if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
		{
			rvclPos[ ui_idx ][0] = rvclPos[ ui_idx ][1] = rvclPos[ ui_idx ][2] = 0.0;
			rvclNorm[ ui_idx ][0]= rvclNorm[ ui_idx ][1] = rvclNorm[ ui_idx ][2] = 0.0;
		}
		else if( b_v_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				i_u = i_uspan - dimension_u;
				pcl_temps = apcl_temp[ i_k ];
				for( i_s = 0; i_s <= dimension_u; ++i_s )
				{
					pcl_temps->x = pcl_temps->y = pcl_temps->z = 0.0;
					i_v = i_vspan - dimension_v;
					pd_nvkr = ppd_nv[ i_k ];
					for( i_r = 0; i_r <= dimension_v; ++i_r )
					{
						*pcl_temps += control_points[ i_u ][ i_v ] * *pd_nvkr;
						++i_v;
						++pd_nvkr;
					}
					++i_u;
					++pcl_temps;
				}
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}

//			rvclPos[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
            rvclPos[ ui_idx ][0] = aacl_skl[ 0 ][ 0 ].x;
            rvclPos[ ui_idx ][1] = aacl_skl[ 0 ][ 0 ].y;                        
            rvclPos[ ui_idx ][2] = aacl_skl[ 0 ][ 0 ].z;                        

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
//			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );	// switched because of optimization!
//			d_len = rvclNorm[ ui_idx ].quad_size( );
            vec3d tempnorm = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
            rvclNorm[ ui_idx ][0] = tempnorm.x;
            rvclNorm[ ui_idx ][1] = tempnorm.y;
            rvclNorm[ ui_idx ][2] = tempnorm.z;
            d_len = tempnorm.quad_size();
        
			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ][ 0 ] = rvclNorm[ ui_idx ][ 1 ] = rvclNorm[ ui_idx ][ 2 ] = 0.0;
			}
		}
		else if( b_u_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}
//			rvclPos[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
            rvclPos[ ui_idx ][0] = aacl_skl[ 0 ][ 0 ].x;
			rvclPos[ ui_idx ][1] = aacl_skl[ 0 ][ 0 ].y;
			rvclPos[ ui_idx ][2] = aacl_skl[ 0 ][ 0 ].z;

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
//			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );	// switched because of optimization!
//			d_len = rvclNorm[ ui_idx ].quad_size( );
			vec3d tempnorm = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
			rvclNorm[ ui_idx ][0] = tempnorm.x;
			rvclNorm[ ui_idx ][1] = tempnorm.y;
			rvclNorm[ ui_idx ][2] = tempnorm.z;
			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ][ 0 ] = rvclNorm[ ui_idx ][ 1 ] = rvclNorm[ ui_idx ][ 2 ] = 0.0;
			}
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclPos[ ui_idx ] = rvclPos[ ui_idx - 1 ];
			rvclNorm[ ui_idx ] = rvclNorm[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
			++g_uiSameComp;
#endif
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	// clean up allocated memory
	if( i_uspan >= 0 )
	{
		delete[ ] ppd_nu[ 0 ];
		delete[ ] ppd_nu[ 1 ];
		delete[ ] ppd_nu;
	}
	if( i_vspan >= 0 )
	{
		delete[ ] ppd_nv[ 0 ];
		delete[ ] ppd_nv[ 1 ];
		delete[ ] ppd_nv;
	}
	delete[ ] apcl_temp[ 0 ];
	delete[ ] apcl_temp[ 1 ];

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::computeNormalforTrimming( std::vector< vec2d > &rvclUV, 
                                                     std::vector< vec3d > &rvclNorm,
													 std::vector< vec3d > *pvclPos )
{
	const unsigned int			cui_cnt = rvclUV.size( );
	unsigned int				ui_idx;
	int							i_uspan = -1;
	int							i_vspan = -1;
	double						**ppd_nu;
	double						**ppd_nv;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*apcl_temp[ 2 ];
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;
	bool						b_u_new;
	bool						b_v_new;
	vec3d						*pcl_temps;
	double						*pd_nuls;
	double						*pd_nvkr;
	vec3d						*pcl_sklkl;
	int							i_old_u;

	apcl_temp[ 0 ] = new vec3d[ dimension_u + 1 ];
	apcl_temp[ 1 ] = new vec3d[ dimension_u + 1 ];

	rvclNorm.resize( cui_cnt );
	if( pvclPos != NULL )
	{
		pvclPos->resize( cui_cnt );
	}

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
			i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_uspan;
				if( i_uspan >= 0 )
				{
					delete[ ] ppd_nu[ 0 ];
					delete[ ] ppd_nu[ 1 ];
					delete[ ] ppd_nu;
				}
				i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
				b_u_new = true;
				b_v_new = ( i_old_u != i_uspan ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_vspan >= 0 )
				{
					delete[ ] ppd_nv[ 0 ];
					delete[ ] ppd_nv[ 1 ];
					delete[ ] ppd_nv;
				}
				i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
				b_v_new = true;
			}
		}
		if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
		{
			rvclNorm[ ui_idx ].x = rvclNorm[ ui_idx ].y = rvclNorm[ ui_idx ].z = 0.0;
			if( pvclPos != NULL )
			{
				( *pvclPos )[ ui_idx ].x = ( *pvclPos )[ ui_idx ].y = ( *pvclPos )[ ui_idx ].z = 0.0;
			}
		}
		else if( b_v_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				i_u = i_uspan - dimension_u;
				pcl_temps = apcl_temp[ i_k ];
				for( i_s = 0; i_s <= dimension_u; ++i_s )
				{
					pcl_temps->x = pcl_temps->y = pcl_temps->z = 0.0;
					i_v = i_vspan - dimension_v;
					pd_nvkr = ppd_nv[ i_k ];
					for( i_r = 0; i_r <= dimension_v; ++i_r )
					{
						*pcl_temps += control_points[ i_u ][ i_v ] * *pd_nvkr;
						++i_v;
						++pd_nvkr;
					}
					++i_u;
					++pcl_temps;
				}
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );	// switched because of optimization!
			d_len = rvclNorm[ ui_idx ].quad_size( );
			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ].x = rvclNorm[ ui_idx ].y = rvclNorm[ ui_idx ].z = 0.0;
			}
			if( pvclPos != NULL )
			{
				( *pvclPos )[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
			}
		}
		else if( b_u_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );	// switched because of optimization!
			d_len = rvclNorm[ ui_idx ].quad_size( );
			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ].x = rvclNorm[ ui_idx ].y = rvclNorm[ ui_idx ].z = 0.0;
			}
			if( pvclPos != NULL )
			{
				( *pvclPos )[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
			}
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclNorm[ ui_idx ] = rvclNorm[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
			++g_uiSameComp;
#endif
			if( pvclPos != NULL )
			{
				( *pvclPos )[ ui_idx ] = ( *pvclPos )[ ui_idx - 1 ];
			}
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	// clean up allocated memory
	if( i_uspan >= 0 )
	{
		delete[ ] ppd_nu[ 0 ];
		delete[ ] ppd_nu[ 1 ];
		delete[ ] ppd_nu;
	}
	if( i_vspan >= 0 )
	{
		delete[ ] ppd_nv[ 0 ];
		delete[ ] ppd_nv[ 1 ];
		delete[ ] ppd_nv;
	}
	delete[ ] apcl_temp[ 0 ];
	delete[ ] apcl_temp[ 1 ];

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::computeNormalTex( std::vector< vec2d > &rvclUV, 
                                             std::vector< Pnt3f > &rvclPos, 
                                             std::vector< Vec3f > &rvclNorm,
                                             std::vector< Pnt2f > &rvclTexCoord, 
                                       const std::vector< std::vector< Pnt2f > > *cpvvclTexCP )
{
	const unsigned int			cui_cnt = rvclUV.size( );
	unsigned int				ui_idx;
	int							i_uspan = -1;
	int							i_vspan = -1;
	double						**ppd_nu;
	double						**ppd_nv;
	int							i_k;
	int							i_s;
	int							i_l;
	vec3d						aacl_skl[ 2 ][ 2 ];
	vec3d						*apcl_temp[ 2 ];
	int							i_r;
	double						d_len;
	int							i_u;
	int							i_v;
	bool						b_u_new;
	bool						b_v_new;
	vec3d						*pcl_temps;
	double						*pd_nuls;
	double						*pd_nvkr;
	vec3d						*pcl_sklkl;
	vec2d						*pcl_temp_2d = new vec2d[ dimension_u + 1 ];
	vec2d						*pcl_temp_2dl;
	int							i_old_u;

	apcl_temp[ 0 ] = new vec3d[ dimension_u + 1 ];
	apcl_temp[ 1 ] = new vec3d[ dimension_u + 1 ];

	rvclPos.resize( cui_cnt );
	rvclNorm.resize( cui_cnt );
	rvclTexCoord.resize( cui_cnt );

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
			i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_uspan;
				if( i_uspan >= 0 )
				{
					delete[ ] ppd_nu[ 0 ];
					delete[ ] ppd_nu[ 1 ];
					delete[ ] ppd_nu;
				}
				i_uspan = basis_function_u.computeDersBasisFuns( rvclUV[ ui_idx ].x, dimension_u, ppd_nu, 1 );
				b_u_new = true;
				b_v_new = ( i_old_u != i_uspan ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_vspan >= 0 )
				{
					delete[ ] ppd_nv[ 0 ];
					delete[ ] ppd_nv[ 1 ];
					delete[ ] ppd_nv;
				}
				i_vspan = basis_function_v.computeDersBasisFuns( rvclUV[ ui_idx ].y, dimension_v, ppd_nv, 1 );
				b_v_new = true;
			}
		}
		if( ( i_uspan < 0 ) || ( i_vspan < 0 ) )
		{
			rvclPos[ ui_idx ][0] = rvclPos[ ui_idx ][1] = rvclPos[ ui_idx ][2] = 0.0;
			rvclNorm[ ui_idx ][0] = rvclNorm[ ui_idx ][1] = rvclNorm[ ui_idx ][2] = 0.0;
		}
		else if( b_v_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				i_u = i_uspan - dimension_u;
				pcl_temps = apcl_temp[ i_k ];
				for( i_s = 0; i_s <= dimension_u; ++i_s )
				{
					pcl_temps->x = pcl_temps->y = pcl_temps->z = 0.0;
					i_v = i_vspan - dimension_v;
					pd_nvkr = ppd_nv[ i_k ];
					for( i_r = 0; i_r <= dimension_v; ++i_r )
					{
						*pcl_temps += control_points[ i_u ][ i_v ] * *pd_nvkr;
						++i_v;
						++pd_nvkr;
					}
					++i_u;
					++pcl_temps;
				}
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}

//			rvclPos[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
            rvclPos[ ui_idx ][0] = aacl_skl[ 0 ][ 0 ].x;
            rvclPos[ ui_idx ][1] = aacl_skl[ 0 ][ 0 ].y;                        
            rvclPos[ ui_idx ][2] = aacl_skl[ 0 ][ 0 ].z;                        

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
//			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
//			d_len = rvclNorm[ ui_idx ].quad_size( );
            vec3d tempnorm = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
            rvclNorm[ ui_idx ][0] = tempnorm.x;
            rvclNorm[ ui_idx ][1] = tempnorm.y;
            rvclNorm[ ui_idx ][2] = tempnorm.z;
            d_len = tempnorm.quad_size();

			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ][ 0 ] = rvclNorm[ ui_idx ][ 1 ] = rvclNorm[ ui_idx ][ 2 ] = 0.0;
			}

			// calculate texture coord
//			rvclTexCoord[ ui_idx ].x() = rvclTexCoord[ ui_idx ].y() = 0.0;
                        vec2d temptexcoord(0, 0 );
			i_u = i_uspan - dimension_u;
			pd_nuls = ppd_nu[ 0 ];
			pcl_temp_2dl = pcl_temp_2d;
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				pcl_temp_2dl->x = pcl_temp_2dl->y = 0.0;
				i_v = i_vspan - dimension_v;
				pd_nvkr = ppd_nv[ 0 ];
				for( i_k = 0; i_k <= dimension_v; ++i_k )
				{
					pcl_temp_2dl->x += ( *cpvvclTexCP )[ i_u ][ i_v ].x() * *pd_nvkr;
					pcl_temp_2dl->y += ( *cpvvclTexCP )[ i_u ][ i_v ].y() * *pd_nvkr;
					++i_v;
					++pd_nvkr;
				}
				++i_u;
				temptexcoord += *pcl_temp_2dl * *pd_nuls;
				++pd_nuls;
				++pcl_temp_2dl;
                                rvclTexCoord[ ui_idx][0] = temptexcoord.x;
                                rvclTexCoord[ ui_idx][1] = temptexcoord.y;
			}
		}
		else if( b_u_new )
		{
			for( i_k = 0; i_k <= 1; ++i_k )
			{
				pcl_sklkl = aacl_skl[ i_k ];
				for( i_l = 0; i_l <= 1 - i_k; ++i_l )
				{
					pcl_sklkl->x = pcl_sklkl->y = pcl_sklkl->z = 0.0;
					pcl_temps = apcl_temp[ i_k ];
					pd_nuls = ppd_nu[ i_l ];
					for( i_s = 0; i_s <= dimension_u; ++i_s )
					{
						*pcl_sklkl += *pcl_temps * *pd_nuls;
						++pcl_temps;
						++pd_nuls;
					}
					++pcl_sklkl;
				}
			}

			//rvclPos[ ui_idx ] = aacl_skl[ 0 ][ 0 ];
            rvclPos[ ui_idx ][0] = aacl_skl[ 0 ][ 0 ].x;
            rvclPos[ ui_idx ][1] = aacl_skl[ 0 ][ 0 ].y;                        
            rvclPos[ ui_idx ][2] = aacl_skl[ 0 ][ 0 ].z;                        

			correctDers( rvclUV[ ui_idx ], aacl_skl[ 0 ][ 0 ], aacl_skl[ 1 ][ 0 ], aacl_skl[ 0 ][ 1 ] );
//			rvclNorm[ ui_idx ] = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
//			d_len = rvclNorm[ ui_idx ].quad_size( );
            vec3d tempnorm = aacl_skl[ 0 ][ 1 ].cross( aacl_skl[ 1 ][ 0 ] );
            rvclNorm[ ui_idx ][0] = tempnorm.x;
            rvclNorm[ ui_idx ][1] = tempnorm.y;
            rvclNorm[ ui_idx ][2] = tempnorm.z;
            d_len = tempnorm.quad_size();
			if( d_len > DCTP_EPS * DCTP_EPS )
			{
				rvclNorm[ ui_idx ] *= 1.0 / sqrt( d_len );
			}
			else
			{
				rvclNorm[ ui_idx ][ 0 ] = rvclNorm[ ui_idx ][ 1 ] = rvclNorm[ ui_idx ][ 2 ] = 0.0;
			}

			// calculate texture coord
//			rvclTexCoord[ ui_idx ][0] = rvclTexCoord[ ui_idx ][1] = 0.0;
			pd_nuls = ppd_nu[ 0 ];
			pcl_temp_2dl = pcl_temp_2d;
                        vec2d temptexcoord(0, 0 );
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				temptexcoord += *pcl_temp_2dl * *pd_nuls;
				++pd_nuls;
				++pcl_temp_2dl;
			}
                        rvclTexCoord[ ui_idx][0] = temptexcoord.x;
                        rvclTexCoord[ ui_idx][1] = temptexcoord.y;
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclPos[ ui_idx ] = rvclPos[ ui_idx - 1 ];
			rvclNorm[ ui_idx ] = rvclNorm[ ui_idx - 1 ];
			rvclTexCoord[ ui_idx ] = rvclTexCoord[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
			++g_uiSameComp;
#endif
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	// clean up allocated memory
	if( i_uspan >= 0 )
	{
		delete[ ] ppd_nu[ 0 ];
		delete[ ] ppd_nu[ 1 ];
		delete[ ] ppd_nu;
	}
	if( i_vspan >= 0 )
	{
		delete[ ] ppd_nv[ 0 ];
		delete[ ] ppd_nv[ 1 ];
		delete[ ] ppd_nv;
	}
	delete[ ] apcl_temp[ 0 ];
	delete[ ] apcl_temp[ 1 ];
	delete[ ] pcl_temp_2d;

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::computeTex( std::vector< vec2d > &rvclUV, 
                                       std::vector< Pnt3f > &rvclPos, 
		                       std::vector< Pnt2f > &rvclTexCoord, 
                                       const std::vector< std::vector< vec2d > > *cpvvclTexCP )
{
	const unsigned int	cui_cnt = rvclUV.size( );
	unsigned int		ui_idx;
	double				*pd_nu;
	double				*pd_nv;
	int					i_span_u = -1;
	int					i_span_v = -1;
	unsigned int		ui_index_v;
	vec3d				*pcl_temp = new vec3d[ dimension_u + 1 ];
	vec2d				*pcl_ttemp = new vec2d[ dimension_u + 1 ];
	unsigned int		ui_index_u;
	int					i_l;
	int					i_k;
	double				*pd_nul;
	double				*pd_nvk;
	bool				b_u_new;
	bool				b_v_new;
	vec3d				*pcl_templ;
	vec2d				*pcl_ttempl;
	int					i_old_u;

	rvclPos.resize( cui_cnt );
	rvclTexCoord.resize( cui_cnt );

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
			i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_span_u;
				if( i_span_u >= 0 ) delete[ ] pd_nu;
				i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
				b_u_new = true;
				b_v_new = ( i_old_u != i_span_u ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_span_v >= 0 ) delete[ ] pd_nv;
				i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
				b_v_new = true;
			}
		}

		if( ( i_span_u < 0 ) || ( i_span_v < 0 ) )
		{
			rvclPos[ ui_idx ][0] = rvclPos[ ui_idx ][1] = rvclPos[ ui_idx ][2] = 0.0;
			rvclTexCoord[ ui_idx ][0] = rvclTexCoord[ ui_idx ][1] = 0.0;
		}
		else if( b_v_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_templ = pcl_temp;
			pcl_ttempl = pcl_ttemp;
			vec3d tempposition(0, 0, 0);
			vec2d temptex(0, 0);
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				pcl_templ->x = pcl_templ->y = pcl_templ->z = 0.0;
				pcl_ttempl->x = pcl_ttempl->y = 0.0;
				ui_index_v = i_span_v - dimension_v;
				pd_nvk = pd_nv;
				for( i_k = 0; i_k <= dimension_v; ++i_k )
				{
					*pcl_templ += control_points[ ui_index_u ][ ui_index_v ] * *pd_nvk;
					*pcl_ttempl += (*cpvvclTexCP)[ ui_index_u ][ ui_index_v ] * *pd_nvk;
					++ui_index_v;
					++pd_nvk;
				}
				++ui_index_u;
				tempposition += *pcl_templ * *pd_nul;
				temptex += *pcl_ttempl * *pd_nul;
				++pd_nul;
				++pcl_templ;
				++pcl_ttempl;
			}
			rvclPos[ ui_idx ][0] = tempposition.x;
			rvclPos[ ui_idx ][1] = tempposition.y;
			rvclPos[ ui_idx ][2] = tempposition.z;
			rvclTexCoord[ ui_idx ][0] = temptex.x;
			rvclTexCoord[ ui_idx ][1] = temptex.y;
		}
		else if( b_u_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_templ = pcl_temp;
			pcl_ttempl = pcl_ttemp;
			vec3d tempposition(0, 0, 0);
			vec2d temptex(0, 0);
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				++ui_index_u;
				tempposition += *pcl_templ * *pd_nul;
				temptex += *pcl_ttempl * *pd_nul;
				++pd_nul;
				++pcl_templ;
				++pcl_ttempl;
			}
			rvclPos[ ui_idx ][0] = tempposition.x;
			rvclPos[ ui_idx ][1] = tempposition.y;
			rvclPos[ ui_idx ][2] = tempposition.z;
			rvclTexCoord[ ui_idx ][0] = temptex.x;
			rvclTexCoord[ ui_idx ][1] = temptex.y;
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclPos[ ui_idx ] = rvclPos[ ui_idx - 1 ];
			rvclTexCoord[ ui_idx ] = rvclTexCoord[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
			++g_uiSameComp;
#endif
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	if( i_span_u >= 0 ) delete[ ] pd_nu;
	if( i_span_v >= 0 ) delete[ ] pd_nv;
	delete[ ] pcl_temp;
	delete[ ] pcl_ttemp;

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::computeTexforTrimming( std::vector< vec2d > &rvclUV, 
            					  std::vector< vec2d > &rvclTexCoord, 
		                                  const std::vector< std::vector< vec2d > > *cpvvclTexCP )
{
	const unsigned int	cui_cnt = rvclUV.size( );
	unsigned int		ui_idx;
	double				*pd_nu;
	double				*pd_nv;
	int					i_span_u = -1;
	int					i_span_v = -1;
	unsigned int		ui_index_v;
	vec2d				*pcl_ttemp = new vec2d[ dimension_u + 1 ];
	unsigned int		ui_index_u;
	int					i_l;
	int					i_k;
	double				*pd_nul;
	double				*pd_nvk;
	bool				b_u_new;
	bool				b_v_new;
	vec2d				*pcl_ttempl;
	int					i_old_u;

	rvclTexCoord.resize( cui_cnt );

	for( ui_idx = 0; ui_idx < cui_cnt; ++ui_idx )
	{
		if( ui_idx == 0 )
		{
			i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
			i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
			b_u_new = b_v_new = true;
		}
		else
		{
			if( fabs( rvclUV[ ui_idx ].x - rvclUV[ ui_idx - 1 ].x ) > DCTP_EPS )
			{
				i_old_u = i_span_u;
				if( i_span_u >= 0 ) delete[ ] pd_nu;
				i_span_u = basis_function_u.computeAllNonzero( rvclUV[ ui_idx ].x, dimension_u, pd_nu );
				b_u_new = true;
				b_v_new = ( i_old_u != i_span_u ) ? true : false;
			}
			else
			{
				b_u_new = false;
				b_v_new = false;
			}
			if( fabs( rvclUV[ ui_idx ].y - rvclUV[ ui_idx - 1 ].y ) > DCTP_EPS )
			{
				if( i_span_v >= 0 ) delete[ ] pd_nv;
				i_span_v = basis_function_v.computeAllNonzero( rvclUV[ ui_idx ].y, dimension_v, pd_nv );
				b_v_new = true;
			}
		}

		if( ( i_span_u < 0 ) || ( i_span_v < 0 ) )
		{
			rvclTexCoord[ ui_idx ].x = rvclTexCoord[ ui_idx ].y = 0.0;
		}
		else if( b_v_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_ttempl = pcl_ttemp;
			rvclTexCoord[ ui_idx ].x = rvclTexCoord[ ui_idx ].y = 0.0;
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				pcl_ttempl->x = pcl_ttempl->y = 0.0;
				ui_index_v = i_span_v - dimension_v;
				pd_nvk = pd_nv;
				for( i_k = 0; i_k <= dimension_v; ++i_k )
				{
					*pcl_ttempl += (*cpvvclTexCP)[ ui_index_u ][ ui_index_v ] * *pd_nvk;
					++ui_index_v;
					++pd_nvk;
				}
				++ui_index_u;
				rvclTexCoord[ ui_idx ] += *pcl_ttempl * *pd_nul;
				++pd_nul;
				++pcl_ttempl;
			}
		}
		else if( b_u_new )
		{
			ui_index_u = i_span_u - dimension_u;
			pd_nul = pd_nu;
			pcl_ttempl = pcl_ttemp;
			rvclTexCoord[ ui_idx ].x = rvclTexCoord[ ui_idx ].y = 0.0;
			for( i_l = 0; i_l <= dimension_u; ++i_l )
			{
				++ui_index_u;
				rvclTexCoord[ ui_idx ] += *pcl_ttempl * *pd_nul;
				++pd_nul;
				++pcl_ttempl;
			}
#ifdef OSG_COUNT_COMP
			++g_uiVSameComp;
#endif
		}
		else
		{
			rvclTexCoord[ ui_idx ] = rvclTexCoord[ ui_idx - 1 ];
#ifdef OSG_COUNT_COMP
			++g_uiSameComp;
#endif
		}
#ifdef OSG_COUNT_COMP
		++g_uiTotalComp;
#endif
	}

	if( i_span_u >= 0 ) delete[ ] pd_nu;
	if( i_span_v >= 0 ) delete[ ] pd_nv;
	delete[ ] pcl_ttemp;

#ifdef OSG_COUNT_COMP
	cerr << g_uiTotalComp << " " << g_uiVSameComp << " " << g_uiSameComp << endl;
#endif
}


void BSplineTensorSurface::correctDers( const vec2d cclUV, const vec3d cclPos, vec3d &rclDU, vec3d &rclDV )
{
	return;
#if 0
	if( rclDU.quad_size( ) < DCTP_EPS )
	{
		// du is zero
		vec3d	cl_temp;
		vec3d	cl_low;
		vec3d	cl_high;
		vec2d	cl_param;
		double	d_step;
		double	d_minpar;
		double	d_maxpar;
		int		i_err;

		getParameterInterval_U( d_minpar, d_maxpar );

		// step in -u direction
		cl_param = cclUV;
		cl_low = cclPos;
		d_step = cl_param.x - d_minpar;
		while( d_step > DCTP_EPS )
		{
			d_step *= 0.5;
			cl_param.x -= d_step;
			cl_temp = compute( cl_param, i_err );
			if( ( cl_temp - cclPos ).quad_size( ) > DCTP_EPS )
			{
				cl_low = cl_temp;
				cl_param.x += d_step;
			}
/*			else if( ( cl_temp - cclPos ).quad_size( ) > ( cl_low - cclPos ).quad_size( ) )
			{
				cl_low = cl_temp;
			}*/
		}

		// step in +u direction
		cl_param = cclUV;
		cl_high = cclPos;
		d_step = d_maxpar - cl_param.x;
		while( d_step > DCTP_EPS )
		{
			d_step *= 0.5;
			cl_param.x += d_step;
			cl_temp = compute( cl_param, i_err );
			if( ( cl_temp - cclPos ).quad_size( ) > DCTP_EPS )
			{
				cl_high = cl_temp;
				cl_param.x -= d_step;
			}
/*			else if( ( cl_temp - cclPos ).quad_size( ) > ( cl_high - cclPos ).quad_size( ) )
			{
				cl_high = cl_temp;
			}*/
		}

		// calculate dirivative
//		std::cerr << "du: " << rclDU;
		if( ( cl_high - cl_low ).quad_size( ) > DCTP_EPS )
		{
			rclDU = cl_high - cl_low;
		}
		else
		{
			rclDU.x = rclDU.y = rclDU.z = 0.0;
		}
//		std::cerr << " -> " << rclDU << std::endl;
	}

	if( rclDV.quad_size( ) < DCTP_EPS )
	{
		// dv is zero
		vec3d	cl_temp;
		vec3d	cl_low;
		vec3d	cl_high;
		vec2d	cl_param;
		double	d_step;
		double	d_minpar;
		double	d_maxpar;
		int		i_err;

		getParameterInterval_V( d_minpar, d_maxpar );

		// step in -v direction
		cl_param = cclUV;
		cl_low = cclPos;
		d_step = cl_param.y - d_minpar;
		while( d_step > DCTP_EPS )
		{
			d_step *= 0.5;
			cl_param.y -= d_step;
			cl_temp = compute( cl_param, i_err );
			if( ( cl_temp - cclPos ).quad_size( ) > DCTP_EPS )
			{
				cl_low = cl_temp;
				cl_param.y += d_step;
			}
/*			else if( ( cl_temp - cclPos ).quad_size( ) > ( cl_low - cclPos ).quad_size( ) )
			{
				cl_low = cl_temp;
			}*/
		}

		// step in +v direction
		cl_param = cclUV;
		cl_high = cclPos;
		d_step = d_maxpar - cl_param.y;
		while( d_step > DCTP_EPS )
		{
			d_step *= 0.5;
			cl_param.y += d_step;
			cl_temp = compute( cl_param, i_err );
			if( ( cl_temp - cclPos ).quad_size( ) > DCTP_EPS )
			{
				cl_high = cl_temp;
				cl_param.y -= d_step;
			}
/*			else if( ( cl_temp - cclPos ).quad_size( ) > ( cl_high - cclPos ).quad_size( ) )
			{
				cl_high = cl_temp;
			}*/
		}

		// calculate dirivative
//		std::cerr << "dv: " << rclDV;
		if( ( cl_high - cl_low ).quad_size( ) > DCTP_EPS )
		{
			rclDV = cl_high - cl_low;
		}
		else
		{
			rclDV.x = rclDV.y = rclDV.z = 0.0;
		}
//		std::cerr << " -> " << rclDV << std::endl;
	}
#endif
}
