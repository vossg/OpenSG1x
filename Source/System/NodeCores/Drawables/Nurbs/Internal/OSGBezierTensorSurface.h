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
#ifndef _OSG_BEZIERTENSORSURFACE_H_
#define _OSG_BEZIERTENSORSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include <OSGConfig.h>


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "OSGdctptypes.h"
#include "OSGBezierCurve3D.h"

OSG_BEGIN_NAMESPACE

class BezierTensorSurface;

typedef std::vector< BezierTensorSurface > beziersurfacevector;
typedef std::vector< beziersurfacevector > beziersurfacematrix;


class OSG_SYSTEMLIB_DLLMAPPING BezierTensorSurface {
protected:
  vec3dmatrix control_points; //control points of the curve

  //file format constants
  static const char ff_const_1[];
  static const char ff_const_2[];
  static const char ff_const_3[];

public:
  BezierTensorSurface();
  BezierTensorSurface( const vec3dmatrix &cps ) { control_points = cps; }
  BezierTensorSurface( const BezierTensorSurface& bts ) { control_points = bts.control_points; }
  ~BezierTensorSurface() {}
 
  //setup functions
  int setControlPointMatrix( const vec3dmatrix& cps ); //ok, acts like its name says 

  //query functions
  vec3dmatrix& getControlPointMatrix( void ) { return control_points; } //guess what!

  //I/O support - FIXME: read( char *fname ) outta be supported , etc
  int read( std::ifstream &infile );
  int write( std::ofstream &outfile );

  //some REAL functionality
  vec3d computewdeCasteljau( vec2d uv, int &error ); //compute curve at parameter value t
  vec3d computeLinearApproximation( vec2d uv, int &error ); //ok like its name sayz
  int midPointSubDivision( beziersurfacematrix &newbeziers ); //subdivide surface at midpoint into 4 bezier surfaces
  int midPointSubDivision( beziersurfacevector &newbeziers ); //subdivide surface at midpoint into 4 bezier surfaces
  int midPointSubDivisionU( BezierTensorSurface &newsurface );
  int midPointSubDivisionV( BezierTensorSurface &newsurface );
};

OSG_END_NAMESPACE

#endif //BezierTensorSurface.h