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
#ifndef _OSG_BEZIERCURVE2D_H_
#define _OSG_BEZIERCURVE2D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include <OSGConfig.h>
#include <OSGBaseFunctions.h>

#include "OSGdctptypes.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <deque>

OSG_BEGIN_NAMESPACE

class BezierCurve2D;
typedef std::vector< BezierCurve2D > bezier2dvector;
typedef std::vector< bezier2dvector > bezier2dmatrix;
typedef std::deque< BezierCurve2D > bezier2ddeque;
typedef std::vector< bezier2ddeque > bezier2ddequevector;

class OSG_SYSTEMLIB_DLLMAPPING BezierCurve2D {
protected:
  vec2dvector control_points; //control points of the curve

  //file format constants
  static const char ff_const_1[];
  static const char ff_const_2[];

  double pointLineDistance( vec2d p, vec2d a, vec2d b );
  double pointLineDistancewNormal( vec2d p, vec2d a, vec2d n );
  int minMaxIntersection( dvector &res, double s, double e );  
  int approximate_sub( vec2dvector &vertices, double delta);
  int approximateLength_sub( vec2dvector &vertices, double delta);
public:
  BezierCurve2D();
  ~BezierCurve2D() {}
  BezierCurve2D( BezierCurve2D const & b ) {
  	control_points = b.control_points;
  }
 
  //setup functions
  int setControlPointVector( const vec2dvector& cps ); //ok, acts like its name says 

  //query functions
  vec2dvector& getControlPointVector( void ) { return control_points; } //guess what!

  //I/O support - FIXME: read( char *fname ) outta be supported , etc
  int read( std::ifstream &infile );
  int write( std::ofstream &outfile );
  int write( );

  //some REAL functionality
  vec2d computewdeCasteljau( double t, int &error ); //compute curve at parameter value t
  vec2d computeLinearApproximation( double t, int &error ); //ok like its name sayz
  int midPointSubDivision( bezier2dvector &newbeziers ); //subdivide curve at midpoint into two new curves
  int midPointSubDivision( BezierCurve2D &newcurve ); //subdivide curve at midpoint into two new curves
  int subDivision( double t, bezier2dvector &newbeziers ); //subdivide curvee at t into two new curves
  int subDivision( double t, BezierCurve2D &newcurve ); //subdivide curvee at t into two new curves
  int intersection( dvector &res, vec2d a, vec2d b ); // calculate intersection of curve with polyline (a, b)
  int intersection( dvector &res, double a, bool horiz ); // calculate intersection of curve with line (a)
  int approximate( vec2dvector &vertices, double delta); // approximate curve linearly with given maximum tolerance
  int approximateLength( vec2dvector &vertices, double delta); // approximate curve linearly with given maximum tolerance
  bool reduceDegree( double tol = DCTP_EPS); //try to degree reduce the curve

  inline void optimizeDegree( )
  {
//	  std::cerr << "reduce degree (2d): " << control_points.size( ) - 1;
	  while( reduceDegree( ) ) { }
//	  std::cerr << " -> " << control_points.size( ) - 1 << std::endl;
  }
};

OSG_END_NAMESPACE

#endif //BezierCurve2D.h