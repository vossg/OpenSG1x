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
#include "OSGBSplineCurve2D.h"

OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BSplineCurve2D::ff_const_1[]="BEGINBSPLINECURVE2D";
  const char BSplineCurve2D::ff_const_2[]="DIMENSION";
  const char BSplineCurve2D::ff_const_3[]="NUMBEROFCONTROLPOINTS";

//construction (& destruction, but not here :)
BSplineCurve2D::BSplineCurve2D()
{
  dimension = -1; //sets invalid value
  control_points.resize( 0 );
}


int BSplineCurve2D::CheckKnotPoints( const dvector& knots, int dim )
{
  //now check knotvector whether it has
  //(a,a,....a, ......., b,b,....b)
  // |-dim+1-|           |-dim+1-|
  //structure

  dvector::size_type max_index = knots.size() - 1;
  double test_begin = knots[ 0 ], test_end = knots[ max_index ];

  for( dvector::size_type i = 1; i < (unsigned int) dim + 1; ++i )
    if ( knots[ i ] != test_begin || knots[ max_index - i ] != test_end ) return -1; //FIXME: double comparison ?!

  return 0;
}

int BSplineCurve2D::deleteBezierKnot( double k )
{
  dvector knots = basis_function.getKnotVector();

  if ( k >= knots[ knots.size() - 1 ] ) return -1; // knot is too high
  if ( k <= knots[ 0 ] ) return -2; // knot is too low

  dvector::size_type i = 0;
  int mult = 0;
  while ( knots[ i ] <= k ) {
    if ( knots[ i ] == k ) mult++;
    i++;
  }
  if ( mult < dimension + 1 ) return -2; // knot doesn't have enough multiplicity
  i--; 

  // delete from knotvector
  knots.erase( knots.begin() + i );
  // set new knot vector
  basis_function.setKnotVector( knots );
  // delete control point corresponding to just deleted knot
  control_points.erase( control_points.begin() + i - dimension );
  return 0;
}


//setup functions
int BSplineCurve2D::setKnotsAndDimension( const dvector& knots, int dim )
{
  if ( dim < 1 ) return -1; //invalid dimension

  dvector::size_type max_index = knots.size() - 1;
  if ( max_index < 3 ) return -2; //here's an implicit check fer structure, see below

  if ( CheckKnotPoints( knots, dim ) ) return -3;

  dimension = dim;
  if ( basis_function.setKnotVector( knots ) ) return -4; //error in BSplineBasisFunction.setKno...

  return 0;
}

void BSplineCurve2D::setControlPointVector( const vec2dvector &cps )
{
  control_points = cps;
}

//query functions
dvector& BSplineCurve2D::getKnotVector( void )
{
  return basis_function.getKnotVector();
}

void BSplineCurve2D::getParameterInterval( double &minpar, double &maxpar )
{
  basis_function.getParameterInterval( minpar, maxpar );
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
int BSplineCurve2D::read( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];


  infile.getline( txtbuffer, 255 ); //read line
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; //yeah, bad file format again

  infile >> dimension >> std::ws;
  if ( dimension < 1 ) return -2; //ah, bad dimension

  if ( basis_function.read( infile ) ) return -3; //error reading basis function
  if ( CheckKnotPoints( basis_function.getKnotVector(), dimension ) ) return -4;

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_3 ) ) return -1; //bad file format once again

  vec2dvector::size_type num_of_cps;
  infile >> num_of_cps >> std::ws;
  if ( num_of_cps < 1 ) return -5; //too few control points
  control_points.resize( num_of_cps ); //FIXME: whatif not enoght memory?

  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec2d cp;
    infile >> cp.x >> cp.y >> std::ws;
    control_points[ i ] = cp; //FIXME: ya see, we need ERROR CHECKS!!!
  }

  return 0;

}

int BSplineCurve2D::write( std::ofstream &outfile )
{
  //FIXME: maybe we need more checks!!!
  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  outfile << ff_const_2 << " " << dimension << std::endl;
  basis_function.write( outfile );
  dvector::size_type num_of_cps = control_points.size();
  outfile << ff_const_3 << " " << num_of_cps << std::endl;
  for( dvector::size_type i = 0; i < num_of_cps; ++i ) {
    vec2d cp = control_points[ i ];
    outfile << cp.x << " " << cp.y << std::endl;
  }
  return 0;
}


//some REAL functionality
vec2d BSplineCurve2D::compute( double t, int &error )
{
  //FIXME: verification before goin' into computation!!
  double	*pd_n;
//  dvector n;
  int span = basis_function.computeAllNonzero( t, dimension, pd_n );
  vec2d result( 0.0, 0.0 );
  if ( span < 0 ) {
    error = span;
    return result; //error occured in BSplineBasisFunction.computeAll...
  }
  for( int i = 0; i <= dimension; ++i ) result = result + control_points[ span - dimension + i ] * pd_n[ i ];
  delete[ ] pd_n;
  return result; 
}

//insert knot. Returns < 0 on error, otherwise 0.
int BSplineCurve2D::insertKnot( double k )
{
  dvector knots = basis_function.getKnotVector();
  int span = basis_function.insertKnot( k );
  if ( span < 0 ) return span; // some error happened

  vec2dvector newcps;
  newcps.resize( control_points.size() + 1 );
  vec2dvector::size_type i;
  for ( i = 0; i <= (unsigned int) span - dimension; i++ )
    newcps[ i ] = control_points[ i ];
  for ( i = span - dimension + 1; i <= (unsigned int) span; i++ ) {
    double alpha;
    if ( knots[ i + dimension ] != knots[ i ] )
      alpha = ( k - knots[ i ] ) / ( knots[ i + dimension ] - knots[ i ]);
    else
      alpha = 0; 
    newcps[ i ] = control_points[ i ] * alpha + control_points[ i - 1 ] * ( 1 - alpha );
  }
  for ( i = span + 1; i < newcps.size(); i++ ) {
    newcps[ i ] = control_points[ i - 1 ]; 
  }
  control_points = newcps;
  return 0;
}

int BSplineCurve2D::makeBezier( bezier2dvector &beziers, dvector &pars )
{
  double firstknot, lastknot;
  basis_function.getParameterInterval( firstknot, lastknot );
  dvector knots = basis_function.getKnotVector();
  dvector origknots = knots;  // backup original curve characteristics
  vec2dvector origcps = control_points; // same here
  double prevknot = firstknot;
  int mult = 0;
  int err;
  unsigned int i;

  for (i = 1; i < knots.size(); i++) {
    double actk = knots[ i ];
    if ( actk == prevknot ) 
      mult++;
    else {
      for ( int j = mult + 1; j < dimension; j++ ) {//each interior knot must have the multiplicity of dimension -1
        err = insertKnot( prevknot );
        if ( err ) return err; // some error happened during insertKnot
      }
      if ( prevknot != firstknot && prevknot != lastknot ) {
        for ( int j = mult; j > dimension - 1; j-- ) {
          err = deleteBezierKnot( prevknot );
          if ( err ) return err; // some error happened during deleteBezierKnot
        }
      }
      mult = 0;
    }
    prevknot = actk;
  }

  // now do the actual conversation into n. bezier segments
  knots = basis_function.getKnotVector(); // FIXME: it could be more efficient.
  unsigned int num_of_beziers = ( knots.size() - 2 ) / dimension - 1;
  if ( ( num_of_beziers * dimension + 2 ) != knots.size() - dimension ) {
    basis_function.setKnotVector( origknots );
    control_points = origcps;
    return -5;
  }

  beziers.resize( num_of_beziers );
  pars.resize ( num_of_beziers + 1 );
  for (i = 0; i < num_of_beziers + 1; i++ )
    pars[ i ] = knots[ 1 + dimension * i ];
  vec2dvector beziercps( dimension + 1 );
  vec2d firstcp;
  bool degenerate;
  bezier2dvector::size_type bezind = 0;
  bezier2dvector::size_type orig_num_of_beziers = num_of_beziers;
  for ( i = 0; i < orig_num_of_beziers; i++ ) {
    firstcp = control_points[ i * dimension + 0 ];
    degenerate = true;
    for (vec2dvector::size_type j = 0; j < (unsigned int) dimension + 1; j++ ) {
      beziercps[ j ] = control_points[ i * dimension + j ];
      if ( degenerate ) 
         if ( firstcp != beziercps[ j ] ) degenerate = false;
    } // j
    if ( degenerate ) {
       num_of_beziers--; 
       bezier2dvector::iterator bi = beziers.begin() + bezind; // + i ??? 
       dvector::iterator pi = pars.begin() + bezind;
       beziers.erase( bi ); beziers.resize( num_of_beziers );
       pars.erase ( pi ); pars.resize( num_of_beziers + 1 );
//       std::cerr << "Ignoring degenerate curve, DaimlerCrysler r0xx... :-|" << std::endl;
    }
    else beziers[ bezind++ ].setControlPointVector( beziercps );
  } // i

  // restore original curve
  basis_function.setKnotVector( origknots );
  control_points = origcps;
  return 0;
}
