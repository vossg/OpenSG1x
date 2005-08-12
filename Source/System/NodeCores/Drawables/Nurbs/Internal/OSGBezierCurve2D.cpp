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

#include "OSGBezierCurve2D.h"

OSG_USING_NAMESPACE


#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BezierCurve2D::ff_const_1[]="BEGINBEZIERCURVE2D";
  const char BezierCurve2D::ff_const_2[]="NUMBEROFCONTROLPOINTS";

//construction (& destruction, but not here :)
BezierCurve2D::BezierCurve2D()
{
  control_points.resize( 0 );
}

//setup functions
int BezierCurve2D::setControlPointVector( const vec2dvector& cps )
{
  if ( cps.size() < 2 ) return -1; //invalid dimension, at least rwo points are required
  control_points = cps;
  return 0;
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
int BezierCurve2D::read( std::istream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];


  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; //yeah, bad file format again

  vec2dvector::size_type num_of_cps;
  infile >> num_of_cps >> std::ws;

  if ( num_of_cps < 2 ) return -2; //too few control points
  control_points.resize( num_of_cps ); //FIXME: whatif not enoght memory?

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec2d cp;
    infile >> cp.x >> cp.y >> std::ws;
    control_points[ i ] = cp; //FIXME: ya see, we need ERROR CHECKS!!!, eg. maybe there's not enough points in file
  }

  return 0;

}

int BezierCurve2D::write( std::ostream &outfile )
{
  //FIXME: maybe we need more checks!!!
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  dvector::size_type num_of_cps = control_points.size();
  outfile << ff_const_2 << " " << num_of_cps << std::endl;

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec2d cp = control_points[ i ];
    outfile << cp.x << " " << cp.y << std::endl;
  }
  return 0;
}


int BezierCurve2D::write( )
{
  //FIXME: maybe we need more checks!!!
  std::cerr << ff_const_1 << std::endl;
  dvector::size_type num_of_cps = control_points.size();
  std::cerr << ff_const_2 << " " << num_of_cps << std::endl;

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec2d cp = control_points[ i ];
	std::cerr << cp.x << " " << cp.y << std::endl;
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
 *  \return the computed value
 *
 */
vec2d BezierCurve2D::computewdeCasteljau( double t, int &error )
{
  //FIXME: verification before goin' into computation!!
  vec2dvector Q = control_points; //local array not to destroy da other points
  vec2dvector::size_type n = Q.size() - 1; 

  error = 0;
  if ( n < 1 ) { //too few points, at least 2 needed
    error = -1;
	Q[ 0 ].x = DCTP_EPS * floor( Q[ 0 ].x / DCTP_EPS );
	Q[ 0 ].y = DCTP_EPS * floor( Q[ 0 ].y / DCTP_EPS );
    return Q[0];
  }
//  std::cerr.precision( DCTP_PRECISION );
//  for ( unsigned int kkk = 0; kkk < Q.size(); kkk++ )
//     std::cerr << Q[ kkk ] << " " ;
//  std::cerr << std::endl;

  // orig fecu code
  for( vec2dvector::size_type k = 0; k < n; ++k ) 
    for( vec2dvector::size_type i = 0; i < n - k; ++i )
      Q[ i ] = Q[ i ] * ( 1.0 - t ) + Q[ i + 1 ] * t;
/*
  for( vec2dvector::size_type k = 1; k <= n; ++k ) 
    for( vec2dvector::size_type i = 0; i <= n - k; ++i ) {
//      std::cerr << "i: " << i << "n-k: " << n-k << std::endl;
      Q[ i ] = Q[ i ] * ( 1.0 - t ) + Q[ i + 1 ] * t;
    }
*/
//  std::cerr.precision( DCTP_PRECISION );
//  for ( unsigned int kkk = 0; kkk < Q.size(); kkk++ )
//	std::cerr << Q[ kkk ] << " " ;
//  std::cerr << std::endl;

  return ( Q[0] ); 
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
vec2d BezierCurve2D::computeLinearApproximation( double t, int &error )
{
  //FIXME: verification before goin' into computation!!
  vec2dvector::size_type n = control_points.size() - 1;
  vec2d result( 0.0, 0.0 );

  error = 0;
  if ( n < 1 ) { //too few points, at least 2 needed
    error = -1;
    return result;
  }
  result = control_points[ 0 ] * ( 1 - t ) + control_points[ n ] * t;
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
int BezierCurve2D::midPointSubDivision( bezier2dvector &newbeziers )
{
  // This function is time critical so optimize at the cost of readabiltity...
  vec2dvector::size_type n = control_points.size();

  if ( n < 2 ) { //too few points, at least 2 needed to split curve
    return -1;
  }

  newbeziers.resize( 2 ); // we return exactly two curves
//  vec2dvector Q = control_points; //local array not to destroy da other points
//  vec2dvector cp1( n + 1 );
//  vec2dvector cp2( n + 1 );
  vec2dvector::size_type i, k;

  vec2dvector &cp1 = newbeziers[ 0 ].control_points;
  vec2dvector &cp2 = newbeziers[ 1 ].control_points;
/*  cp1.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
  cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
  cp1.resize( n );
  cp2.resize( n );

  --n;
  for( k = 0; k < n; ++k )
  {
    cp1[ k ] = Q [ 0 ];
    cp2[ n - k ] = Q [ n - k ];
    for( i = 0; i < n - k; ++i ) {
	  Q[ i ] += Q[ i + 1 ];
	  Q[ i ] *= 0.5;
//      Q[ i ] = Q[ i ] * ( 1.0 - 0.5 ) + Q[ i + 1 ] * 0.5;
    }
  }
  cp1[ n ] = Q[ 0 ];
  cp2[ 0 ] = Q[ 0 ];*/

	cp1.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp1.resize( n );
	cp2.resize( n );

	for( k = 0; k < n; ++k )
	{
		cp1[ k ] = control_points[ k ];
//		cp1[ k ].x = control_points[ k ].x;
//		cp1[ k ].y = control_points[ k ].y;
	}
	--n;
	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ] = cp1[ n ];
//		cp2[ n - k ].x = cp1[ n ].x;
//		cp2[ n - k ].y = cp1[ n ].y;
		for( i = n; i > k; --i )
		{
			cp1[ i ] += cp1[ i - 1 ];
//			cp1[ i ].x += cp1[ i - 1 ].x;
//			cp1[ i ].y += cp1[ i - 1 ].y;
			cp1[ i ] *= 0.5;
//			cp1[ i ].x *= 0.5;
//			cp1[ i ].y *= 0.5;
		}
//      Q[ i ] = Q[ i ] * ( 1.0 - 0.5 ) + Q[ i + 1 ] * 0.5;
    }
	cp2[ 0 ] = cp1[ n ];
//	cp2[ 0 ].x = cp1[ n ].x;
//	cp2[ 0 ].y = cp1[ n ].y;
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
int BezierCurve2D::midPointSubDivision( BezierCurve2D &newcurve )
{
	// This function is time critical so optimize at the cost of readabiltity...
	vec2dvector::size_type n = control_points.size();

	if ( n < 2 )
	{
		return -1;	//too few points, at least 2 needed to split curve
	}

	vec2dvector::size_type i, k;

	vec2dvector &cp1 = control_points;
	vec2dvector &cp2 = newcurve.control_points;

	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.resize( n );

	--n;
	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ] = cp1[ n ];
//		cp2[ n - k ].x = cp1[ n ].x;
//		cp2[ n - k ].y = cp1[ n ].y;
		for( i = n; i > k; --i )
		{
			cp1[ i ] += cp1[ i - 1 ];
//			cp1[ i ].x += cp1[ i - 1 ].x;
//			cp1[ i ].y += cp1[ i - 1 ].y;
			cp1[ i ] *= 0.5;
//			cp1[ i ].x *= 0.5;
//			cp1[ i ].y *= 0.5;
		}
    }
	cp2[ 0 ] = cp1[ n ];
//	cp2[ 0 ].x = cp1[ n ].x;
//	cp2[ 0 ].y = cp1[ n ].y;
	
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
int BezierCurve2D::subDivision( double t, bezier2dvector &newbeziers )
{
  if ( t <= 0.0 || t >= 1.0 ) return -1; // t must be between (0, 1) exclusive

  newbeziers.resize( 2 ); // we return exactly two curves
  vec2dvector Q = control_points; //local array not to destroy da other points
  vec2dvector::size_type n = control_points.size() - 1;
  vec2dvector cp1( n + 1 );
  vec2dvector cp2( n + 1 ); 
  if ( n < 1 ) { //too few points, at least 2 needed to split curve
    return -1;
  }

  for( vec2dvector::size_type k = 0; k < n; ++k ) {
    cp1[ k ] = Q [ 0 ];
    cp2[ n - k ] = Q [ n - k ];
    for( vec2dvector::size_type i = 0; i < n - k; ++i ) {
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
int BezierCurve2D::subDivision( double t, BezierCurve2D &newcurve )
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

	vec2dvector::size_type i, k;

	vec2dvector &cp1 = control_points;
	vec2dvector &cp2 = newcurve.control_points;

	cp2.clear( );	// very imporatant for performance (no copying around of obsolte stuff!)
	cp2.resize( n );

	--n;

	for( k = 0; k < n; ++k )
	{
		cp2[ n - k ] = cp1[ n ];
//		cp2[ n - k ].x = cp1[ n ].x;
//		cp2[ n - k ].y = cp1[ n ].y;
		for( i = n; i > k; --i )
		{
			cp1[ i ] *= t;
//			cp1[ i ].x *= t;
//			cp1[ i ].y *= t;
			cp1[ i ] += cp1[ i - 1 ] * t2;
//			cp1[ i ].x += cp1[ i - 1 ].x * t2;
//			cp1[ i ].y += cp1[ i - 1 ].y * t2;
		}
    }
	cp2[ 0 ] = cp1[ n ];
//	cp2[ 0 ].x = cp1[ n ].x;
//	cp2[ 0 ].y = cp1[ n ].y;
	
	return 0;
}

//! Calculate intersection of the Bezier curve with the polyline (a, b).
/*!
 *  This function calculates the number of intersections the curve has
 *  with the polyline (a, b), using Bezier clipping and the minmax algorithm.
 *
 *  \param res the double vector which will contain the results 
 *             (in (0, 1) parameter space) 
 *  \param a   the first point of the polyline
 *  \param b   the second point of the polyline
 *  \return zero on success, a negative value if some error occured, and <BR>
 *          1 if the curve lies entirely on the polyline. <BR>
 *          2 if the curve lies partly on the polyline. <BR>
 *
 */
int BezierCurve2D::intersection( dvector &res, vec2d a, vec2d b )
{
  int result;
  unsigned int i;

  if ( fabs( a.x - b.x ) < DCTP_EPS && fabs( a.y - b.y ) < DCTP_EPS )
    return -1; // the two points are (almost) the same

//  dvector dists( control_points.size() ); // the signed distance of the control points and the polyline
  vec2d norm; // norm of ( a - b )
  //due to the check above, lab must be positive
  double lab = sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
  norm.x = -( b.y - a.y ) / lab; // This is a normal -> rotated 90 degrees
  norm.y = ( b.x - a.x ) / lab;


  vec2dvector newcp( control_points.size() ); // the control points of the explicit Bezier curve
  int flag = 1;
  unsigned int cpsize = control_points.size() - 1;
  for( i = 0; i <= cpsize; i++ ) {
//    std::cerr.precision( DCTP_PRECISION );
//    std::cerr << "cp[i].x: " << control_points[ i ].x << " cp[i].y: " << control_points[ i ].y << std::endl; 
    newcp[ i ].x = i / cpsize;
    newcp[ i ].y = pointLineDistancewNormal( control_points[ i ], a, norm );
    //std::cerr << " dists[i]: " << newcp[ i ].y << std::endl;
    if ( newcp[ i ].y < -DCTP_EPS || newcp[ i ].y > DCTP_EPS) flag = 0;
  }
  if ( flag ) {
    res.resize( 0 ); // zero result vector because 
    // check start and endpoint of curve, is it really on the polyline, or before/after ?
    double ta, tb;

    if ( fabs( control_points[ cpsize ].x - control_points[ 0 ].x ) > DCTP_EPS ) {
      ta = ( a.x - control_points[ 0 ].x ) / (  control_points[ cpsize ].x - control_points[ 0 ].x );
      tb = ( b.x - control_points[ 0 ].x ) / (  control_points[ cpsize ].x - control_points[ 0 ].x );
    }
    else {
      ta = ( a.y - control_points[ 0 ].y ) / (  control_points[ cpsize ].y - control_points[ 0 ].y );
      tb = ( b.y - control_points[ 0 ].y ) / (  control_points[ cpsize ].y - control_points[ 0 ].y );
    }

    if ( tb < ta ) {
        double tmp = ta;
        ta = tb;
        tb = tmp;
    }
    if ( ta <= 0.0 ) ta = 0.0;
    if ( tb <= 0.0 ) tb = 0.0;
    if ( ta >= 1.0 ) ta = 1.0;
    if ( tb >= 1.0 ) tb = 1.0;

    if ( ta == tb ) return 0; // fully before or after
    if ( ta == 0.0 && tb == 1.0 ) return 1; // fully on the polyline

    res.resize( 2 ); // the curve lies partially on the polyline
//    std::cerr << " ta: " << ta << " tb: " << tb << std::endl;
    res[ 0 ] = ta;
    res[ 1 ] = tb;
    return 2;     //the curve partially lies on the polyline
  }

  BezierCurve2D bstart;
  result = bstart.setControlPointVector( newcp );
  if ( result ) return result; // some error happened
  result = bstart.minMaxIntersection( res, 0.0, 1.0 );
  bool zeroroot = ( fabs( newcp[ 0 ].y ) < DCTP_EPS );
  bool oneroot = ( fabs( newcp[ cpsize ].y ) < DCTP_EPS );

  // special care taken for start/end points
  // FIXME: hack #1 :-|
  if ( res.size() ) {
     if ( res[ res.size() - 1 ] >= 1.0 - DCTP_EPS ) res[ res.size() - 1 ] = 1.0;
     if ( res[ 0 ] <= DCTP_EPS ) res[ 0 ] = 0.0;
  }
  if ( zeroroot ) {
    // we have some solutions, but the first solution is not 0.0, we
    // have to insert 0.0 as first solution
    if ( res.size() && res[ 0 ] >= DCTP_EPS ) res.insert( res.begin(), 0.0 );
    // we don't have any solutions yet, but this is a solution, so we have to
    // insert this
    else if ( !res.size() ) res.push_back( 0.0 );
  }
  if ( oneroot ) {
    // if we have oneroot, and the last item is not 1.0, we have to insert it 
    // as last result, regardless of what is actually in the vector (it can even be empty)
    // check for the last item ( & its existence )
    if ( res.size() && res[ res.size() - 1 ] < 1.0 - DCTP_EPS ) res.push_back( 1.0 );
    // insert it if the resultvector is empty
    else if ( !res.size() ) res.push_back( 1.0 );
  }


// FIXME: obsolete ( & slightly buggy ) code, kept for posterity - JUST FOR NOW 
//  else {
//     if ( fabs( newcp[ 0 ].y ) < DCTP_EPS ) res.push_back( 0 );
//     if ( fabs( newcp[ cpsize ].y ) < DCTP_EPS ) res.push_back( 1 );  
//  }


//  std::cerr << "still here. solutions: " << res.size() << std::endl;
  for (i = 0; i < res.size(); i++ ) {
    vec2d p;
    int er;
    double t;
//    std::cerr << " i: " << i << " solution[i]: " << res[ i ];
    p = computewdeCasteljau( res[ i ], er );
//    std::cerr << " value: " << p.x << " " << p.y << std::endl;
    if ( fabs( b.x - a.x ) > DCTP_EPS ) 
      t = ( p.x - a.x )/ ( b.x - a.x );
    else
      t = ( p.y - a.y )/ ( b.y - a.y );   
//    std::cerr << " lineparam: " << t << std::endl;
    if ( p != a && p != b ) 
      if ( t < -DCTP_EPS || t > ( 1 + DCTP_EPS) ) {
        res.erase ( res.begin() + i );
        i--;
      }
  }
//  std::cerr << "still here. solutions after: " << res.size() << std::endl; 
//  if ( res.size() ) std::cerr << res[ 0 ] << std::endl;

#if 0
  // we have to make this check _after_ the results have been filtered
  if ( res.size() > control_points.size() ) {
    /*
     * We have more results than possible, the curve partly lies on the polyline
     * we only return the first and last results, and hope for the best.
     * note this is not a 100% general solution, but in the vast majority
     * of cases it works. 
     * FIXME: a 100% general solution may be desirable some day...
     */
    double tt = res[ res.size() - 1 ];
    res.resize( 2 );
    res[ 1 ] = tt;
    return -2; // to indicate some problem happened
  }
#endif
  return result;
}


// calculate intersection of curve with line (a)
int BezierCurve2D::intersection( dvector &res, double a, bool horiz )
{
  vec2dvector newcp( control_points.size() ); // the control points of the explicit Bezier curve
  BezierCurve2D tempcurve;
  const unsigned int cpsize = control_points.size( ) - 1;

  for( unsigned int i = 0; i < newcp.size( ); ++i )
  {
	  if( horiz )
	  {
		  newcp[ i ] = control_points[ i ];
	  }
	  else
	  {
		  newcp[ i ].x = control_points[ i ].y;
		  newcp[ i ].y = control_points[ i ].x;
	  }
	  newcp[ i ].y -= a;
  }

  int result = tempcurve.setControlPointVector( newcp );
  if ( result ) return result; // some error happened
  result = tempcurve.minMaxIntersection( res, 0.0, 1.0 );
  bool zeroroot = ( fabs( newcp[ 0 ].y ) < DCTP_EPS );
  bool oneroot = ( fabs( newcp[ cpsize ].y ) < DCTP_EPS );
  // special care taken for start/end points
  // FIXME: hack #1 :-|
  if ( res.size() ) {
     if ( res[ res.size() - 1 ] >= 1.0 - DCTP_EPS ) res[ res.size() - 1 ] = 1.0;
     if ( res[ 0 ] <= DCTP_EPS ) res[ 0 ] = 0.0;
  }
  if ( zeroroot ) {
    // we have some solutions, but the first solution is not 0.0, we
    // have to insert 0.0 as first solution
    if ( res.size() && res[ 0 ] >= DCTP_EPS ) res.insert( res.begin(), 0.0 );
    // we don't have any solutions yet, but this is a solution, so we have to
    // insert this
    else if ( !res.size() ) res.push_back( 0.0 );
  }
  if ( oneroot ) {
    // if we have oneroot, and the last item is not 1.0, we have to insert it 
    // as last result, regardless of what is actually in the vector (it can even be empty)
    // check for the last item ( & its existence )
    if ( res.size() && res[ res.size() - 1 ] < 1.0 - DCTP_EPS ) res.push_back( 1.0 );
    // insert it if the resultvector is empty
    else if ( !res.size() ) res.push_back( 1.0 );
  }
  return result;
}


// calculate intersection of x axis and Bezier curve, calls itself recursively
int BezierCurve2D::minMaxIntersection( dvector &res, double s, double e )
{
  double miny = control_points[ 0 ].y;
  double maxy = control_points[ 0 ].y;
  int result;
  vec2d r;
  double mid = 0.0;

//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << "minmax for: " << s << " " << e << std::endl;
  // find the minmax box of the control polygon - note we only need the y values
  // meanwhile also check that we do not lie on the line :)
  vec2dvector::size_type cpsize = control_points.size();
  vec2dvector::size_type i;
  for ( i = 1; i < cpsize; i++ ) {
    if ( control_points[ i ].y > maxy ) maxy = control_points[ i ].y;
    else if ( control_points[ i ].y < miny ) miny = control_points[ i ].y;
  }
//  std::cerr << " miny: " << miny << " maxy: " << maxy << std::endl;

#if 0
  if (miny > -DCTP_EPS && miny < DCTP_EPS && maxy > -DCTP_EPS && maxy < DCTP_EPS ) {
    std::cerr << " found interval: [ " << control_points[ 0 ].x << " - " << control_points[ cpsize - 1 ].x << " ]" << std::endl;
    return 0;
  }
  if ( fabs( control_points[ 0 ].y ) < DCTP_EPS ) {
///   original shit
//    if ( res.size() && res[ res.size() - 1 ] == s ) return 0;
    if ( !res.size() || res[ res.size() - 1 ] != s ) {
    std::cerr << " special recording: " << s << std::endl;
    res.push_back( s );
    // we have to check for the last point too, for really degenerate cases
//    if ( !( fabs( control_points[ cpsize - 1 ].y )  < DCTP_EPS ) || control_points[ 0 ] == control_points[ cpsize - 1 ] )
//       return 0;
    }
  }
  std::cerr << "still here 1 " << std::endl;
  if ( fabs( control_points[ cpsize - 1 ].y ) < DCTP_EPS ) {
/// original shit
//    if ( res.size() && res[ res.size() - 1 ] == e ) return 0;
    if ( !res.size() || res[ res.size() - 1 ] != e ) {
    std::cerr << " special recording #2: " << e << std::endl;
    res.push_back( e );
//    return 0;
    }
  }
  std::cerr << "still here 2 " << std::endl;
#endif

  if ( ( miny > 0 && maxy > 0 ) || ( miny < 0 && maxy < 0 ) ) return 0;

/*
  if ( ( miny <= 0.0 && maxy <= 0.0 ) ||
       ( miny > 0.0 && maxy > 0.0 ) ) return 0;
*/
//  if ( ! ( (miny < 0.0 && maxy > 0.0) ||
//           (miny > 0.0 && maxy < 0.0) ) ) return 0;
//  std::cerr <<"still here 3 " << std::endl;
  if( maxy - miny < DCTP_EPS )
  {
	  if( e - s > DCTP_EPS )
	  {
		  // completely on the line, so return start and end...
		  if( res.size( ) == 0 )
		  {
			  res.push_back( s );
		  }
		  res.push_back( e );
	  }
	  else
	  {
		  res.push_back( ( s + e ) / 2.0 ); // we have a new (unique) solution, record it
	  }
	  return 0;
  }
/*  if( maxy - miny < DCTP_EPS )	// this should be sufficient...
//  if( control_points[ 0 ] == control_points[ cpsize - 1 ] &&
//       (e - s ) < DCTP_EPS )
  {
    if ( res.size() > 0 ) {
      if ( fabs( res[ res.size() - 1 ] - (s + e) / 2.0 ) > DCTP_EPS )
//           fabs( res[ res.size() - 1 ].x - e ) > DCTP_MINMAX_DIFFTOL) {
//        std::cerr << " recording : " << s << std::endl;
//        std::cerr << " res.size(): " << res.size() << " res[res.size()-1]: " << res[res.size()-1] << std::endl;
        res.push_back( (s + e) / 2.0 ); // we have a new (unique) solution, record it
//      }
      return 0;
    }
    else {
//      std::cerr << " recording first: " << s << std::endl;
      res.push_back( (s + e) / 2.0 ); // this is the first solution, record it anyway
      return 0;
    }
  }*/
  // we have a solution in our minmax box, subdivide and continue recursively
  BezierCurve2D newbez;

  // find first intersection of contol polygon with axis
  for( i = 1; i < cpsize; ++i )
  {
	  const double	&p1 =  control_points[ i - 1 ].y;
	  const double	&p2 =  control_points[ i ].y;

	  if( p1 < 0.0 )
	  {
		  if( p2 >= 0.0 )
		  {
			  if( ( p2 == 0.0 ) && ( i == cpsize - 1 ) )
			  {
				  res.push_back( e );
				  return 0;
			  }
			  else
			  {
				  mid = ( i - p2 / ( p2 - p1 ) ) / cpsize;
				  break;
			  }
		  }
	  }
	  else if( p1 > 0.0 )
	  {
		  if( p2 <= 0.0 )
		  {
			  if( ( p2 == 0.0 ) && ( i == cpsize - 1 ) )
			  {
				  res.push_back( e );
				  return 0;
			  }
			  else
			  {
				  mid = ( i + p2 / ( p1 - p2 ) ) / cpsize;
				  break;
			  }
		  }
	  }
	  else if( i == 1 )
	  {
		  if( res.size( ) != 0 )
		  {
		      if( fabs( res[ res.size( ) - 1 ] - s ) > DCTP_EPS )
			  {
				  res.push_back( s ); // we have a new (unique) solution, record it
			  }
		  }
		  else
		  {
		      res.push_back( s ); // this is the first solution, record it anyway
		  }
	  }
  }
  if( i == cpsize )
  {
    return 0;
  }
//  for( i = 0; i < cpsize; ++i )
//  {
//	std::cerr << control_points[ i ].y << " ";
//  }
//  std::cerr << std::endl;

  mid = osgMin( 0.999, osgMax( 0.001, mid ) );
//  std::cerr << mid << std::endl;
  result = subDivision( mid, newbez );
//  result = midPointSubDivision( newbez );
  if ( result ) return result; // some error happened

  result = minMaxIntersection( res, s, s + ( e - s ) * mid );
//  result = minMaxIntersection( res, s, ( (s + e) / 2 ) );
  if ( result ) return result; // some error happened

  result = newbez.minMaxIntersection( res, s + ( e - s ) * mid, e );
//  result = newbez.minMaxIntersection( res, ( (s + e) / 2 ), e );
  return result;
}



// calculate the signed distance between a point and a line (given with two points)
// returns the signed distance
double BezierCurve2D::pointLineDistance( vec2d p, vec2d a, vec2d b )
{
  vec2d norm;
  double lab = sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
  norm.x = -( b.y - a.y ) / lab; // This is a normal -> rotated by 90 degrees
  norm.y = ( b.x - a.x ) / lab;
  return pointLineDistancewNormal( p, a, norm );
}

// calculate the signed distance between a point and a line (given with a point and a normalvector)
// returns the signed distance
double BezierCurve2D::pointLineDistancewNormal( vec2d p, vec2d a, vec2d n )
{
  vec2d t;
  t = p - a;
//  t.x = p.x - a.x;
//  t.y = p.y - a.y;
//  std::cerr << " a.x: " << a.x << " a.y: " << a.y << " p.x: " << p.x << " p.y: " << p.y << std::endl;
  return t.x * n.x + t.y * n.y;
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
int BezierCurve2D::approximate( vec2dvector &vertices, double delta)
{
  vertices.resize( 0 );

  // check for first degree Bezier.
  if ( control_points.size() == 2 ) {
    vertices.push_back( control_points[ 0 ] );
    vertices.push_back( control_points[ 1 ] );
    return 0;
  }

  // call recursive subdividing function
  return approximate_sub( vertices, delta);

}

int BezierCurve2D::approximateLength( vec2dvector &vertices, double delta)
{
  vertices.resize( 0 );

  // check for first degree Bezier.
  std::cerr << control_points.size( ) << std::endl;
  if( control_points.size( ) == 2 )
  {
	double	d_dist = sqrt( ( control_points[ 1 ] - control_points[ 0 ] ).quad_size( ) );
	int		i_steps = ( int ) ceil( d_dist / ( 1.5 * delta ) );
	int		i_step;
	double	d_param;

	std::cerr << d_dist << " - " << delta << " -> " << i_steps << " " << d_dist / ( 3.0 * delta ) << std::endl;

    vertices.push_back( control_points[ 0 ] );
	for( i_step = 1; i_step < i_steps; ++i_step )
	{
		d_param = ( double ) i_step / ( double ) i_steps;
	    vertices.push_back( control_points[ 0 ] + ( control_points[ 1 ] - control_points[ 0 ] ) * d_param );
	}
    vertices.push_back( control_points[ 1 ] );
    return 0;
  }

  // call recursive subdividing function
 // std::cerr << "approx..." << std::endl;
  return approximateLength_sub( vertices, delta);

}

int BezierCurve2D::approximate_sub( vec2dvector &vertices, double delta)
{
  double act_error;
  double max_error = 0;
  vec2d  ae;
  double twopower = 1;
  double aenorm;
  double t1, t2;

  int n = control_points.size() - 1;
  for ( int i = 0; i <= n; i++ ) {
    t1 = ( (double) ( n - i ) ) / n;
    t2 = ( (double) i ) / n;
    ae = control_points[ i ] - control_points[ 0 ] * t1 - control_points[ n ] * t2;
//    ae.x = control_points[ i ].x - t1 * control_points[ 0 ].x - t2 * control_points[ n ].x;
//    ae.y = control_points[ i ].y - t1 * control_points[ 0 ].y - t2 * control_points[ n ].y;

//    std::cerr << "i: " << i << " ae.x: " << ae.x << " ae.y: " << ae.y << std::endl;

    aenorm = sqrt( ae.x * ae.x + ae.y * ae.y );
    if (aenorm > max_error ) max_error = aenorm;
    if ( i ) twopower *= 2; // this is a double so it can be arbitrarily high, an int wouldn't suffice
  }
  act_error = ( ( twopower - 1 ) / twopower ) * max_error;
//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ].x << " " << control_points[ 0 ].y << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ].x << " " << control_points[ control_points.size() - 1 ].y << std::endl;
  if ( act_error > delta ) {
    // we have to subdivide further
    BezierCurve2D	newbez;
    int error;
    error = midPointSubDivision( newbez );
    if ( error ) return error;
    approximate_sub( vertices, delta );
    newbez.approximate_sub( vertices, delta );
  }
  else {
    // this is a good enough approximation
    if ( !vertices.size() ) {
      // this is the first approximation, we have to record both the
      // startpoint and the endpoint  
      vertices.push_back( control_points[ 0 ] );
      vertices.push_back( control_points[ control_points.size() - 1 ] );
    }
    else {
      // we had some subdivisions before, we only need to record the endpoint
      vertices.push_back( control_points[ control_points.size() - 1 ] );
    }
  }
  return 0;
}

int BezierCurve2D::approximateLength_sub( vec2dvector &vertices, double delta)
{
  double act_error;
  double max_error = 0;
  vec2d  ae;
  double twopower = 1;
  double aenorm;
  double t1, t2;

  int n = control_points.size() - 1;
  double	d_dist = sqrt( ( control_points[ n ] - control_points[ 0 ] ).quad_size( ) );
//  std::cerr << d_dist << " - " << delta << std::endl;
  if( d_dist > delta * 1.5 )
  {
    // we have to subdivide further
    bezier2dvector newbez;
    int error;
    error = midPointSubDivision( newbez );
    if ( error ) return error;
    newbez[ 0 ].approximateLength_sub( vertices, delta );
    newbez[ 1 ].approximateLength_sub( vertices, delta );
  }
  else
  {
    for ( int i = 0; i <= n; i++ ) {
      t1 = ( (double) ( n - i ) ) / n;
      t2 = ( (double) i ) / n;
      ae = control_points[ i ] - control_points[ 0 ] * t1 - control_points[ n ] * t2;
  //    ae.x = control_points[ i ].x - t1 * control_points[ 0 ].x - t2 * control_points[ n ].x;
//      ae.y = control_points[ i ].y - t1 * control_points[ 0 ].y - t2 * control_points[ n ].y;

//      std::cerr << "i: " << i << " ae.x: " << ae.x << " ae.y: " << ae.y << std::endl;

      aenorm = sqrt( ae.x * ae.x + ae.y * ae.y );
      if (aenorm > max_error ) max_error = aenorm;
      if ( i ) twopower *= 2; // this is a double so it can be arbitrarily high, an int wouldn't suffice
	}
    act_error = ( ( twopower - 1 ) / twopower ) * max_error;
//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ].x << " " << control_points[ 0 ].y << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ].x << " " << control_points[ control_points.size() - 1 ].y << std::endl;
    if( act_error > delta ) {
      // we have to subdivide further
      bezier2dvector newbez;
      int error;
      error = midPointSubDivision( newbez );
      if ( error ) return error;
      newbez[ 0 ].approximateLength_sub( vertices, delta );
      newbez[ 1 ].approximateLength_sub( vertices, delta );
	}
    else {
      // this is a good enough approximation
      if ( !vertices.size() ) {
        // this is the first approximation, we have to record both the
        // startpoint and the endpoint  
        vertices.push_back( control_points[ 0 ] );
        vertices.push_back( control_points[ control_points.size() - 1 ] );
	  }
      else {
        // we had some subdivisions before, we only need to record the endpoint
        vertices.push_back( control_points[ control_points.size() - 1 ] );
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
bool BezierCurve2D::reduceDegree( double tol )
{
    unsigned int      n = control_points.size() - 1; // orig cps: 0, ..., n
    if ( n < 2 )
    {
        // cannot degree reduce a first degree curve
        return false;
    }
    vec2dvector b_left( n );
    vec2dvector b_right( n );
    unsigned int      i;

    // calculate b_right:
    b_right[ 0 ] = control_points[ 0 ];
    for (i = 1; i < n; ++i)
    {
        b_right[ i ] = (control_points[ i ] * n - b_right[ i - 1 ] * i) *
                       (1.0 / (double)(n - i));
    }

    // calculate b_left:
    b_left[ n - 1 ] = control_points[ n ];
    for (i = n - 1; i > 0; --i)
    {
        b_left[i - 1] = (control_points[ i ] * n - b_left[ i ] * (n - i)) *
                        (1.0 / (double)i);
    }

    // check for introduced error:
    double quad_error = tol * tol;
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

    unsigned int n_half = n >> 1;
    unsigned int n_half1 = (n + 1) >> 1;
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

