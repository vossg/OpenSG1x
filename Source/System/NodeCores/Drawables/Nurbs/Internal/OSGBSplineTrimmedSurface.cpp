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
#include "OSGBSplineTrimmedSurface.h"

OSG_USING_NAMESPACE


#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
 #endif
#endif

  const char BSplineTrimmedSurface::ff_const_1[]="BEGINTRIMMEDSURFACE";
  const char BSplineTrimmedSurface::ff_const_2[]="NUMBEROFCURVELOOPS";
  const char BSplineTrimmedSurface::ff_const_3[]="CURVESPERLOOP";

// I/O facilities - FIXME: read( char *fname ), etc. missing
int BSplineTrimmedSurface::read( std::ifstream &infile )
{
  //FIXME: maybe we need more checks!!!
  char txtbuffer[ 256 ];
  int lc = 0;
  unsigned int numcurves;
  unsigned int i,j,k;

/*  infile.getline( txtbuffer, 255 ); //read line
  //FIXME: quick hack to allow us to step through
  while ( strcmp( txtbuffer, ff_const_1 ) && lc < 10 ) {
    infile.getline( txtbuffer, 255 ); //read line
    lc++;
  }
  if ( strcmp( txtbuffer, ff_const_1 ) ) return -1; //bad file format

  infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; // yeah, bad file format again*/

  infile >> txtbuffer >> std::ws; //FIXME: error prone: too long string causes problem!!!
  if ( strcmp( txtbuffer, ff_const_1 ) == 0 )
  {
	infile >> txtbuffer >> std::ws; //FIXME: error prone: too long string causes problem!!!
  }

//  infile >> txtbuffer >> std::ws; //FIXME: error prone: too long string causes problem!!!
//  std::cerr << "check " << ff_const_2 << " " << txtbuffer << std::endl;
  if ( strcmp( txtbuffer, ff_const_2 ) )  return -1; // yeah, bad file format again

  infile >> numcurves >> std::ws;
  if ( numcurves < 1 ) return -12; // bad number of curves
  trimming.resize( numcurves );
  for ( i = 0; i < numcurves; i++ ) {
    int actnumofcurves;
    infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
    if ( strcmp( txtbuffer, ff_const_3 ) )  return -13; // bad file format
    infile >> actnumofcurves >> std::ws;
    trimming[ i ].resize( actnumofcurves );
  }
  int err;
  err = surf.read( infile );
  if ( err ) 
  {
      std::cerr<<"error loading surfacedata."<<std::endl;
      return err;
  }

  for ( i = 0; i < numcurves; i++ ) {
    for ( j = 0; j < trimming[ i ].size(); j++) {
       err = trimming[ i ][ j ].read( infile );
       if ( err )
       {
           std::cerr<<"error loading trimming curve data, i: " << i << " j: " << j << std::endl;
            return err;
       }
    }
  }

  return 0;
}

void BSplineTrimmedSurface::normalize( void )
{
  double	d_offset_u;
  double	d_offset_v;
  double	d_scale_u;
  double	d_scale_v;
  unsigned int numcurves = trimming.size();
  unsigned int i, j, k;

  surf.getParameterInterval_U( d_offset_u, d_scale_u );
  surf.getParameterInterval_V( d_offset_v, d_scale_v );
  d_offset_u = -d_offset_u;
  d_offset_v = -d_offset_v;
#ifdef OSG_INTEGER_MESH
  d_scale_u = 1000000.0 / ( d_scale_u + d_offset_u );
  d_scale_v = 1000000.0 / ( d_scale_v + d_offset_v );
#else
  d_scale_u = 10000.0 / ( d_scale_u + d_offset_u );
  d_scale_v = 10000.0 / ( d_scale_v + d_offset_v );
#endif

  for( i = 0; i < surf.getKnotVector_U( ).size( ); ++i )
  {
	  surf.getKnotVector_U( )[ i ] =
		  ( surf.getKnotVector_U( )[ i ] + d_offset_u ) * d_scale_u;
  }
  for( i = 0; i < surf.getKnotVector_V( ).size( ); ++i )
  {
	  surf.getKnotVector_V( )[ i ] =
		  ( surf.getKnotVector_V( )[ i ] + d_offset_v ) * d_scale_v;
  }

  for( i = 0; i < numcurves; i++ )
  {
    for( j = 0; j < trimming[ i ].size( ); j++)
	{
	  for( k = 0; k < trimming[ i ][ j ].getControlPointVector( ).size( ); ++k )
	  {
		trimming[ i ][ j ].getControlPointVector( )[ k ].x =
		  ( trimming[ i ][ j ].getControlPointVector( )[ k ].x + d_offset_u ) * d_scale_u;
		trimming[ i ][ j ].getControlPointVector( )[ k ].y =
		  ( trimming[ i ][ j ].getControlPointVector( )[ k ].y + d_offset_v ) * d_scale_v;
	  }
    }
  }
}

int BSplineTrimmedSurface::write( std::ofstream &outfile )
{
  //FIXME: maybe we need more checks!!!
	unsigned int i;

  outfile.precision( DCTP_PRECISION );
  outfile << ff_const_1 << std::endl;
  outfile << ff_const_2 << " " << trimming.size() << std::endl;
  for ( i = 0; i < trimming.size(); i++ )
    outfile << ff_const_3 << " " << trimming[ i ].size() << std::endl;

  surf.write( outfile );

  for ( i = 0; i < trimming.size(); i++ ) {
    for ( bscvector::size_type j = 0; j < trimming[ i ].size(); j++) {
       trimming[ i ][ j ].write( outfile );
    }
  }

  return 0;
}


// flip the whole surface
void BSplineTrimmedSurface::flip( void )
{
    // mirror the u-knot vector
    dvector            &rvd_knots = surf.getKnotVector_U( );
    const unsigned int  cui_knot_cnt = rvd_knots.size( );
    const double        cd_min_param = rvd_knots[ 0 ];
    const double        cd_max_param = rvd_knots[ cui_knot_cnt - 1 ];
    UInt32              ui_swap;
    Real64              d_swap;

    for( ui_swap = 0; ui_swap < cui_knot_cnt; ++ui_swap )
    {
        rvd_knots[ ui_swap ] = cd_min_param + cd_max_param - rvd_knots[ ui_swap ];
    }
    for( ui_swap = 0; ui_swap < ( cui_knot_cnt >> 1 ); ++ui_swap )
    {
        d_swap = rvd_knots[ ui_swap ];
        rvd_knots[ ui_swap ] = rvd_knots[ cui_knot_cnt - 1 - ui_swap ];
        rvd_knots[ cui_knot_cnt - 1 - ui_swap ] = d_swap;
    }

    // swap the control points along the u-direction
    vec3dmatrix          &rvvcl_control_points = surf.getControlPointMatrix( );
    const unsigned int    cui_cp_cnt = rvvcl_control_points.size( );
    vec3dvector           vcl_swap;

    for( ui_swap = 0; ui_swap < ( cui_cp_cnt >> 1 ); ++ui_swap )
    {
        vcl_swap = rvvcl_control_points[ ui_swap ];
        rvvcl_control_points[ ui_swap ] = rvvcl_control_points[ cui_cp_cnt - 1 - ui_swap ];
        rvvcl_control_points[ cui_cp_cnt - 1 - ui_swap ] = vcl_swap;
    }

    // mirror the u-param of the trimming curves
    const unsigned int  cui_loop_cnt = trimming.size( );
    unsigned int        ui_loop;
    unsigned int        ui_curve_cnt;
    unsigned int        ui_curve;

    for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
    {
        ui_curve_cnt = trimming[ ui_loop ].size( );
        for( ui_curve = 0; ui_curve < ui_curve_cnt; ++ui_curve )
        {
            // mirror the knot vector
            dvector            &rvd_knots = trimming[ ui_loop ][ ui_curve ].getKnotVector( );
            const unsigned int  cui_knot_cnt = rvd_knots.size( );
            const double        cd_min_cparam = rvd_knots[ 0 ];
            const double        cd_max_cparam = rvd_knots[ cui_knot_cnt - 1 ];

/*            std::cerr.precision( 15 );
            std::cerr<<"--------------------------------------------"<<std::endl;
            std::cerr <<"Before: ";*/
            for( ui_swap = 0; ui_swap < cui_knot_cnt; ++ui_swap )
            {
//                std::cerr << rvd_knots[ ui_swap ] << " ";
                rvd_knots[ ui_swap ] = cd_min_cparam + cd_max_cparam - rvd_knots[ ui_swap ];
            }
/*            
            std::cerr <<std::endl<<"After1: ";
            for( ui_swap = 0; ui_swap < cui_knot_cnt; ++ui_swap )
            {
                std::cerr << rvd_knots[ ui_swap ] << " ";
            }
*/            
            for( ui_swap = 0; ui_swap < ( cui_knot_cnt >> 1 ); ++ui_swap )
            {
                d_swap = rvd_knots[ ui_swap ];
                rvd_knots[ ui_swap ] = rvd_knots[ cui_knot_cnt - 1 - ui_swap ];
                rvd_knots[ cui_knot_cnt - 1 - ui_swap ] = d_swap;
            }
/*            
            std::cerr <<std::endl<<"After2: ";
            for( ui_swap = 0; ui_swap < cui_knot_cnt; ++ui_swap )
            {
                std::cerr << rvd_knots[ ui_swap ] << " ";
            }
            std::cerr << std::endl;
            std::cerr.precision( 6 ); 
*/                       
            // swap and mirror the control points
            vec2dvector         &rvcl_control_points = trimming[ ui_loop ][ ui_curve ].getControlPointVector( );
            const unsigned int   cui_cp_cnt = rvcl_control_points.size( );
            vec2d                cl_swap;

            for( ui_swap = 0; ui_swap < cui_cp_cnt; ++ui_swap )
            {
                rvcl_control_points[ ui_swap ].x = cd_min_param + cd_max_param - rvcl_control_points[ ui_swap ].x;
            }
            for( ui_swap = 0; ui_swap < ( cui_cp_cnt >> 1 ); ++ui_swap )
            {
                cl_swap = rvcl_control_points[ ui_swap ];
                rvcl_control_points[ ui_swap ] = rvcl_control_points[ cui_cp_cnt - 1 - ui_swap ];
                rvcl_control_points[ cui_cp_cnt - 1 - ui_swap ] = cl_swap;
            }
        }

        // and swap the trimming curves
        BSplineCurve2D cl_swap;

        for( ui_swap = 0; ui_swap < ( ui_curve_cnt >> 1 ); ++ui_swap )
        {
            cl_swap = trimming[ ui_loop ][ ui_swap ];
            trimming[ ui_loop ][ ui_swap ] = trimming[ ui_loop ][ ui_curve_cnt - 1 - ui_swap ];
            trimming[ ui_loop ][ ui_curve_cnt - 1 - ui_swap ] = cl_swap;
        }
    }
}
