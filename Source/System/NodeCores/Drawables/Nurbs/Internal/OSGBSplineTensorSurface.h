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
#ifndef _OSG_BSPLINETENSORSURFACE_H_
#define _OSG_BSPLINETENSORSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include <OSGConfig.h>
#include <OSGVector.h>


#include "OSGdctptypes.h"
#include "OSGBSplineBasisFunction.h"
#include "OSGBezierTensorSurface.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING BSplineTensorSurface {
protected:
  vec3dmatrix control_points; //control points of the surface
  int dimension_u, dimension_v; //dimension of the surface in u and v directions
  BSplineBasisFunction basis_function_u; //placeholder for the u knots & facility to easily compute 'em
  BSplineBasisFunction basis_function_v; //placeholder for the v knots & facility to easily compute 'em

  //file format constants
  static const char ff_const_1[];
  static const char ff_const_2[];
  static const char ff_const_3[];
  static const char ff_const_4[];

  int CheckKnotPoints( const dvector& knots, int dim ); //check whether knots has a right format
  // delete a knot which is on a 'bezier' curve, i.e. [0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3] -> [0 0 0 0 1 1 1 2 2 2 3 3 3 3]
  // must have a multiplicity of (at least) dimension + 1, and its associated control point also must have a multiplicity of (at least) 2.
  int deleteBezierKnot_U( double k );
  int deleteBezierKnot_V( double k );

public:
  BSplineTensorSurface();
  ~BSplineTensorSurface() {}

  //setup functions
  // FIXME: the setup interface is very rigid, maybe it should allow knot & dimension setting alone, eg. to resize dimension, etc
  // FIXME: and insertion of knots
  int setKnotsAndDimension( const dvector& knots_u, int dim_u, const dvector& knots_v, int dim_v ); //ok, acts like its name says
  void setControlPointMatrix( const vec3dmatrix &cps ); //set control point vector

  //query functions
  dvector& getKnotVector_U( void ); //return knot points of basisfunction_u
  dvector& getKnotVector_V( void ); //return knot points of basisfunction_u
  vec3dmatrix& getControlPointMatrix( void ) { return control_points; } //guess what!
  int getDimension_U( void ) { return dimension_u; } //returns dimension
  int getDimension_V( void ) { return dimension_v; } //returns dimension
  void getParameterInterval_U( double &minpar, double &maxpar ); //returns minimal and maximal parameter value
  void getParameterInterval_V( double &minpar, double &maxpar ); //returns minimal and maximal parameter value
  BSplineBasisFunction& getBasisFunctionU( ) { return basis_function_u; }
  BSplineBasisFunction& getBasisFunctionV( ) { return basis_function_v; }

  //I/O support - FIXME: read( char *fname ) outta be supported , etc
  int read( std::ifstream &infile );
  int write( std::ofstream &outfile );

  //some REAL functionality
  vec3d compute( vec2d uv, int &error ); //compute curve at parameter value t
  vec3d computeNormal( vec2d clUV, int &riError, vec3d &rclPos ); // compute normal at uv
  Vec3f computeNormal( vec2d clUV, int &riError, Pnt3f &rclPos ); // compute normal at uv
  vec3d computeNormalTex( vec2d &rclUV, 
                          int &riError, vec3d &rclPos, vec2d &rclTexCoord, 
                          const std::vector< std::vector< Pnt2f > > *cpvvclTexCP ); // compute normal at uv
  void compute( std::vector< vec2d > &rvclUV, std::vector< Pnt3f > &rvclPos ); //compute curve at parameter value uv
  void computeNormal( std::vector< vec2d > &rvclUV, 
                      std::vector< Pnt3f > &rvclPos, 
                      std::vector< Vec3f > &rvclNorm ); // compute normal at uv
  void computeNormalforTrimming( std::vector< vec2d > &rvclUV, 
                                 std::vector< vec3d > &rvclNorm,
								 std::vector< vec3d > *pvclPos = NULL ); // compute normal at uv
                      
  void computeNormalTex( std::vector< vec2d > &rvclUV, 
                         std::vector< Pnt3f > &rvclPos, 
                         std::vector< Vec3f > &rvclNorm,
			 std::vector< Pnt2f > &rvclTexCoord, 
                         const std::vector< std::vector< Pnt2f > > *cpvvclTexCP ); // compute normal at uv
  void computeTex( std::vector< vec2d > &rvclUV, 
                         std::vector< Pnt3f > &rvclPos, 
                         std::vector< Pnt2f > &rvclTexCoord, 
                         const std::vector< std::vector< vec2d > > *cpvvclTexCP );
  void computeTexforTrimming( std::vector< vec2d > &rvclUV, 
						      std::vector< vec2d > &rvclTexCoord, 
						      const std::vector< std::vector< vec2d > > *cpvvclTexCP );

  int insertKnot_U( double k ); // insert a new knot into U (recalculates control points and u knotvector)
  int insertKnot_V( double k ); // insert a new knot into V (recalculates control points and v knotvector)

  // convert curve into Bezier form.
  int makeBezier( beziersurfacematrix &beziers, dvector &upars, dvector &vpars );
  int getSplitParams( dvector &upars, dvector &vpars );

  //subdivide surface at midpoint into 4 bspline surfaces
  int midPointSubDivision( std::vector< std::vector< BSplineTensorSurface > > &rvvcl_newbspline );
  int midPointSubDivisionU( std::vector< BSplineTensorSurface > &rvcl_newbspline );
  int midPointSubDivisionV( std::vector< BSplineTensorSurface > &rvcl_newbspline );
  int subDivisionU( std::vector< BSplineTensorSurface > &rvcl_newbspline, double dSplit );
  int subDivisionV( std::vector< BSplineTensorSurface > &rvcl_newbspline, double dSplit );

  void correctDers( const vec2d cclUV, const vec3d cclPos, vec3d &rclDU, vec3d &rclDV );

};

OSG_END_NAMESPACE
#endif //BSplineTensorSurface.h
