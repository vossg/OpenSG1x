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
#ifndef _OSG_DCTPTYPES_H_
#define _OSG_DCTPTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include <OSGConfig.h>

#include <iostream>
#include <set>
#include <math.h>
#include <vector>
#include <list>

OSG_BEGIN_NAMESPACE

//#define OSG_DCTP_VECTORIZATION

#define DCTP_EPS 0.000000001
//#define DCTP_EPS 1.0e-20

#define DCTP_PRECISION 16
//#define OSG_INTEGER_MESH

#ifdef WIN32
	#define fabs(a)  ((a) >= 0.0 ? (a) : -(a))
#endif

//#ifdef __INTEL_COMPILER
//   const  struct fpos_t std::_Fpz = {0, 0};
//#endif

struct DCTP_double_less {
  bool operator()( const double d1, const double d2 ) const {
    return( d2 - d1 > DCTP_EPS );
  }
};


class vec3d;
#ifdef OSG_INTEGER_MESH
class vec2d;

class OSG_SYSTEMLIB_DLLMAPPING vec3i {
public:
  int x;
  int y;
  int z;

  vec3i() {}
  vec3i( const int x0, const int y0, const int z0 ) { x = x0; y = y0; z = z0; }
  vec3i( const double x0, const double y0, const double z0 ) { x = x0 + 0.5; y = y0 + 0.5; z = z0 + 0.5; }
  ~vec3i() {}

  // copy constructor
  inline vec3i( vec3i const &source )
  {
    x = source.x;
    y = source.y;
    z = 0;
  }

  inline vec3i( vec2d const &source );

  inline vec3i( vec3d const &source );

  inline bool operator<( const vec3i& vec ) const {
    if( vec.z > z )
      return true;
    if( z > vec.z )
      return false;
    if( vec.y > y )
      return true;
    if( y > vec.y )
      return false;
    if( vec.x > x )
      return true;
    return false;
  }

  inline bool operator>( const vec3i& vec ) const {
    if( vec.z < z )
      return true;
    if( z < vec.z )
      return false;
    if( vec.y < y )
      return true;
    if( y < vec.y )
      return false;
    if( vec.x < x )
      return true;
    return false;
  }

  inline bool operator==( const vec3i& vec ) const {
    if( x != vec.x )
      return false;
    if( y != vec.y )
      return false;
    if( z != vec.z )
      return false;
    return true;
  }

  inline bool operator!=( const vec3i& vec ) const {
    if( x != vec.x )
      return true;
    if( y != vec.y )
      return true;
    if( z != vec.z )
      return true;
    return false;
  }

  inline vec3i operator+( const vec3i v ) const
  {
    return vec3i( x + v.x, y + v.y, z + v.z );
  }

  inline vec3i operator-( const vec3i v ) const
  {
    return vec3i( x - v.x, y - v.y, z - v.z );
  }

  inline vec3i operator*( const double scale ) const
  {
    return vec3i( ( int ) ( x * scale + 0.5 ),
				  ( int ) ( y * scale + 0.5 ),
				  ( int ) ( z * scale + 0.5 ) );
  }

  friend inline std::ostream& operator<<(std::ostream&os, const vec3i &vec )
  {
    return os << "(" << vec.x << ", " << vec.y << ", " << vec.z <<")";
  }

};
#endif

class OSG_SYSTEMLIB_DLLMAPPING vec2d {
public:
  double x;
  double y;
#ifdef OSG_DCTP_VECTORIZATION
  double d1;
  double d2;
#endif
  vec2d() {}
  vec2d( const double x0, const double y0 ) { x = x0; y = y0; }
  ~vec2d() {}

// copy constructor
inline vec2d( vec2d const &source )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( source.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ];
#else
  x = source.x; y = source.y;
#endif
}

#ifdef OSG_INTEGER_MESH
inline vec2d( vec3i const &source )
{
  x = source.x;
  y = source.y;
}
#endif

inline vec2d( vec3d const &source );

inline vec2d operator*( const double mult ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec2d			result;
  const double	*pd_src = &x;
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ] * mult;

  return result;
#else
  return vec2d( x * mult, y * mult );
#endif
}

inline vec2d operator+( const vec2d v ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec2d			result;
  const double	*pd_src1 = &x;
  const double	*pd_src2 = &( v.x );
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src1[ i ] + pd_src2[ i ];

  return result;
#else
  return vec2d( x + v.x, y + v.y );
#endif
}

inline vec2d operator-( const vec2d v ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec2d			result;
  const double	*pd_src1 = &x;
  const double	*pd_src2 = &( v.x );
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src1[ i ] - pd_src2[ i ];

  return result;
#else
  return vec2d( x - v.x, y - v.y );
#endif
}

inline double dot ( const vec2d v ) const
{
	return x * v.x + y * v.y;
}

inline vec2d operator-(void) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec2d			result;
  const double	*pd_src = &x;
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = -pd_src[ i ];

  return result;
#else
  return vec2d( -x, -y );
#endif
}

inline vec2d& operator+=( const vec2d v )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( v.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] += pd_src[ i ];
#else
  x += v.x; y += v.y;
#endif

  return *this;
}

inline vec2d& operator-=( const vec2d v )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( v.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] -= pd_src[ i ];
#else
  x -= v.x; y -= v.y;
#endif

  return *this;
}

inline vec2d& operator*=( const double mult )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] *= mult;
#else
  x *= mult; y *= mult;
#endif

  return *this;
}

inline bool operator==( const vec2d& vec ) const {
  if ( ( fabs( x - vec.x ) < DCTP_EPS ) &&
       ( fabs( y - vec.y ) < DCTP_EPS ) )
    return true;
  else
    return false;
}

inline bool operator!=(const vec2d& vec ) const {
  // this should be better...
  if ( ( fabs( x - vec.x ) < DCTP_EPS ) &&
       ( fabs( y - vec.y ) < DCTP_EPS ) )
    return false;
  else
    return true;
}

inline bool operator<( const vec2d& vec ) const {
  // this should be better...
  if( vec.y - y >= DCTP_EPS ) // x < vec.x
    return true;
  if( y - vec.y >= DCTP_EPS ) // x > vec.x
    return false;
  if( vec.x - x >= DCTP_EPS ) // y < vec.y
    return true;
  return false;

/*  if ( *this == vec ) return false;

  if ( ( x < vec.x ) ||
//     ( fabs(x - vec.x ) < DCTP_EPS && y < vec.y ) )
//FIXME: is it allowed to write this?
     ( !(x > vec.x) && y < vec.y ))
    return true;
  else
    return false;*/
}


inline int operator>(const vec2d& vec ) const {
  // this should be better...
  if( y - vec.y >= DCTP_EPS )
    return true;
  if( vec.y - y >= DCTP_EPS )
    return false;
  if( x - vec.x >= DCTP_EPS )
    return true;
  return false;

/*  if ( *this == vec) return false;
  return !( *this < vec );*/
}

inline double quad_size( void ) const //size without squareroot, to save CPU time :)
{
  return( x*x + y*y );
}
// input/output
// note that this can't be a member function, it's just defined here
// but is _not_ a member function, c++ sukka...
friend inline std::ostream& operator<<(std::ostream& os, const vec2d &vec ) {
  return os << "(" << vec.x << ", " << vec.y << ")";
}

friend inline std::istream& operator>>( std::istream &is, vec2d &vec ) {
  //FIXME: check input data???
  char ch;
  is >> ch; // "("
  is >> vec.x;
  is >> ch; // ", "
  is >> vec.y;
  is >> ch; // ")"
  return is;
}

struct vec2dless {
  bool operator()(const vec2d v1, const vec2d v2) const
  {
    return (v1 < v2);
  }
};


}; // class vec2d


class OSG_SYSTEMLIB_DLLMAPPING vec3d {
public:
  double x;
  double y;
  double z;
#ifdef OSG_DCTP_VECTORIZATION
  double d;
#endif
  vec3d() {}
  vec3d( const double x0, const double y0, const double z0 ) { x = x0; y = y0; z = z0; }
  vec3d( const double x0, const double y0 ) { x = x0; y = y0; z = 0.0; }
  ~vec3d() {}

// copy constructor
inline vec3d( vec3d const &source )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( source.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ];
#else
  x = source.x; y = source.y; z = source.z;
#endif
}

inline vec3d( vec2d const &source )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( source.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ];

  z = 0.0;
#else
  x = source.x; y = source.y; z = 0.0;
#endif
}

#ifdef OSG_INTEGER_MESH
inline vec3d( vec3i const &source )
{
  x = source.x;
  y = source.y;
  z = source.z;
}
#endif

inline void set( const double x0, const double y0, const double z0 ) {
  x = x0; y = y0; z = z0;
}

inline double quad_size( void ) const //size without squareroot, to save CPU time :)
{
  return( x*x + y*y + z*z );
}
  
inline void normalize( void )
{
	const double	cd_fact = 1.0 / sqrt( x * x + y * y + z * z );

#ifdef OSG_DCTP_VECTORIZATION
	// SSE code ;)
	double		*pd_dst = &x;

	for( int i = 0; i < 4; ++i )
		pd_dst[ i ] *= cd_fact;
#else
	x *= cd_fact;
	y *= cd_fact;
	z *= cd_fact;
#endif
}
  
inline vec3d operator*( const double mult ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec3d			result;
  const double	*pd_src = &x;
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ] * mult;

  return result;
#else
  return vec3d( x * mult, y * mult, z * mult );
#endif
}

inline vec3d operator+( const vec3d& v ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec3d			result;
  const double	*pd_src1 = &x;
  const double	*pd_src2 = &( v.x );
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src1[ i ] + pd_src2[ i ];

  return result;
#else
  return vec3d( x + v.x, y + v.y, z + v.z );
#endif
}

inline vec3d operator-( const vec3d& v ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec3d			result;
  const double	*pd_src1 = &x;
  const double	*pd_src2 = &( v.x );
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src1[ i ] - pd_src2[ i ];

  return result;
#else
  return vec3d( x - v.x, y - v.y, z - v.z );
#endif
}

inline vec3d operator-( void ) const
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  vec3d			result;
  const double	*pd_src = &x;
  double		*pd_dst = &( result.x );

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = -pd_src[ i ];

  return result;
#else
  return vec3d( -x, -y, -z );
#endif
}

inline vec3d& operator+=( const vec3d& v )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( v.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] += pd_src[ i ];
#else
  x += v.x; y += v.y; z += v.z;
#endif

  return *this;
}

inline vec3d& operator-=( const vec3d v )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( v.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] -= pd_src[ i ];
#else
  x -= v.x; y -= v.y; z -= v.z;
#endif

  return *this;
}

inline vec3d& operator*=( const double mult )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] *= mult;
#else
  x *= mult; y *= mult; z *= mult;
#endif

  return *this;
}

inline bool operator==( const vec3d& vec ) const {
  if( ( fabs( x - vec.x ) < DCTP_EPS ) &&
      ( fabs( y - vec.y ) < DCTP_EPS ) &&
      ( fabs( z - vec.z ) < DCTP_EPS ) )
    return true;
  else return false;
}

inline bool operator!=(const vec3d& vec ) const {
  if( ( fabs( x - vec.x ) < DCTP_EPS ) &&
      ( fabs( y - vec.y ) < DCTP_EPS ) &&
      ( fabs( z - vec.z ) < DCTP_EPS ) )
    return false;
  else return true;
}

inline bool operator<( const vec3d& vec ) const {
  // this should be better...
  if( vec.z - z >= DCTP_EPS ) // x < vec.x
    return true;
  if( z - vec.z >= DCTP_EPS ) // x > vec.x
    return false;
  if( vec.y - y >= DCTP_EPS ) // y < vec.y
    return true;
  if( y - vec.y >= DCTP_EPS ) // y > vec.y
    return false;
  if( vec.x - x >= DCTP_EPS ) // z < vec.z
    return true;
  return false;

/*  if ( *this == vec ) return 0;
  if ( ( x < vec.x ) ||
//     ( fabs( x - vec.x ) < DCTP_EPS && y < vec.y ) ||
//     ( fabs( x - vec.x ) < DCTP_EPS && fabs( y - vec.y ) < DCTP_EPS && z < vec.z ))
//FIXME: is it allowed to write this?
     (  !(x > vec.x) && y < vec.y ) ||
     (  !(x > vec.x) && !(y > vec.y)  && z < vec.z ))
    return true;
  else
    return false;*/
}


inline bool operator>(const vec3d& vec ) const {
  // this should be better...
  if( z - vec.z >= DCTP_EPS )
    return true;
  if( vec.z - z >= DCTP_EPS )
    return false;
  if( y - vec.y >= DCTP_EPS )
    return true;
  if( vec.y - y >= DCTP_EPS )
    return false;
  if( x - vec.x >= DCTP_EPS )
    return true;
  return false;

/*  if ( *this == vec) return false;
  return !( *this < vec );*/
}

inline double dot(const vec3d& vec ) const
{
        return ( x * vec.x + y * vec.y + z * vec.z );
}

inline vec3d cross(const vec3d& vec) const
{
	return vec3d( y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x );
/*        vec3d res;
        //<Ay*Bz - Az*By, Az*Bx - Ax*Bz, Ax*By - Ay*Bx>
        res.x = y * vec.z - z * vec.y;
        res.y = z * vec.x - x * vec.z;
        res.z = x * vec.y - y * vec.x;

        return res;*/
}

// input/output
// note that this can't be a member function, it's just defined here
// but is _not_ a member function, c++ sukka...
friend inline std::ostream& operator<<(std::ostream&os, const vec3d &vec ) {
  return os << "(" << vec.x << ", " << vec.y << ", " << vec.z <<")";
}

friend inline std::istream& operator>>( std::istream &is, vec3d &vec ) {
  //FIXME: check input data???
  char ch;
  is >> ch; // "("
  is >> vec.x;
  is >> ch; // ", "
  is >> vec.y;
  is >> ch; // ", "
  is >> vec.z;
  is >> ch; // ")"
  return is;
}

struct vec3dless {
  bool operator()(const vec3d v1, const vec3d v2) const
  {
    return (v1 < v2);
  }
};

}; // class vec3d

#ifdef OSG_INTEGER_MESH
inline vec3i::vec3i( vec2d const &source )
{
  x = source.x + 0.5;
  y = source.y + 0.5;
  z = 0;
}

inline vec3i::vec3i( vec3d const &source )
{
  x = source.x + 0.5;
  y = source.y + 0.5;
  z = source.z + 0.5;
}
#endif

inline vec2d::vec2d( vec3d const &source )
{
#ifdef OSG_DCTP_VECTORIZATION
  // SSE code ;)
  const double	*pd_src = &( source.x );
  double		*pd_dst = &x;

  for( int i = 0; i < 4; ++i )
	pd_dst[ i ] = pd_src[ i ];
#else
  x = source.x; y = source.y;
#endif
}


typedef std::vector< double > dvector;
typedef std::vector< int > ivector;
typedef std::vector< ivector > imatrix;
typedef std::vector< vec2d > vec2dvector;
typedef std::vector< vec3d > vec3dvector;
typedef std::vector< vec3dvector > vec3dmatrix;
typedef std::list< double > dlist;
typedef std::set< double > dset;
typedef std::set< vec2d, vec2d::vec2dless > vec2dset;
typedef std::set< vec3d, vec3d::vec3dless > vec3dset;

OSG_END_NAMESPACE

#endif /* _OSG_DCTPTYPES_H_ */
