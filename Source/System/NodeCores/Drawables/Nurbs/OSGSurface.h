/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
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

#ifndef _OSGSURFACE_H_
#define _OSGSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVertexProgramChunk.h"

#include "OSGSurfaceBase.h"

OSG_BEGIN_NAMESPACE


/*! \brief The OpenSG NURBS node.
 */

//---------------------------------------------------------------------------
// Forward References (for internal types)
//---------------------------------------------------------------------------
class CNurbsPatchSurface;
class BSplineTrimmedSurface;
class BSplineTensorSurface;
class SimplePolygon;
class BSplineCurve2D;

//class vec3d;

class OSG_SYSTEMLIB_DLLMAPPING Surface : public SurfaceBase
{
  private:

    typedef SurfaceBase Inherited;


    /*==========================  PUBLIC  =================================*/
  public:

    static const osg::BitVector CurveFieldMask;
    static const osg::BitVector SurfaceFieldMask;

    /*---------------------------------------------------------------------*/
    /*! \name                      user actions                            */
    /*! \{                                                                 */

    void addCurve( UInt32 dim,
                   std::vector<Real64>& knots,
                   std::vector<Pnt2f>& controlpoints,
                   bool newloop = false);

    void addCurve( UInt32 dim,
                   std::vector<Real64>& knots,
                   std::vector<Pnt3f>& controlpoints,
                   bool newloop = false);

    void removeCurves( void );

    SurfacePtr clone( void );
    void readfromtso( std::istream &infile, bool useTextures = false );
    void writetotso( std::ostream &outfile );
    UInt32 writetoobj( std::ostream &outfile, UInt32 offset );

    Real64 getDesiredError( Pnt3f viewPos, Real64 halfPixelSize );

    void forceTessellate(void);

    void flip(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setControlPoints       (const GeoPositionsPtr &value);
    void setTextureControlPoints(const GeoTexCoordsPtr &value);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32 origin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
   
    /*=========================  PROTECTED  ===============================*/
  protected:

    static const UInt32 TESSELLATE     = 0x0001;
    static const UInt32 RETESSELLATE   = 0x0002;
    static const UInt32 DONTTESSELLATE = 0x0004;

    // Variables should all be in SurfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Surface(void);
    Surface(const Surface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Surface(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Internal functions                         */
    /*! \{                                                                 */

    // tessellate from the beginning
    void tessellate(void);
    // only retessellate because error/delaunay mode change
    void reTessellate(void);
    Int32 convertSurface( void );
    Int32 tessellateSurface( std::vector< SimplePolygon > &triangles,
                             std::vector< Pnt3f > &gverts,
                             std::vector< Vec3f > &norms );
    Int32 tessellateSurface( std::vector< SimplePolygon > &triangles,
                             std::vector< Pnt3f > &gverts,
                             std::vector< Vec3f > &norms,
                             std::vector< Pnt2f > &texcoords );
    Int32 tessellateSurface( std::vector< SimplePolygon > &triangles,
                             std::vector< Pnt3f > &gverts, 
                             std::vector< Pnt2f > &texcoords );
                             
    Int32 buildSurface ( std::vector< SimplePolygon > &triangles,
                         std::vector< Pnt3f > &gverts,
                         std::vector< Vec3f > &norms,
                         std::vector< Pnt2f > &texcoords );

    bool checkOrient( UInt32 ui_v1, UInt32 ui_v2, UInt32 ui_v3,
                      std::vector< Pnt3f > &m_vclGlobalVertices,
                      std::vector< Vec3f > &m_vclNormal );

    /* protected functions for adaptive tessellation */   
    bool updateError( Pnt3f viewPos, Real64 halfPixelSize );
    void FindClosestPoint( Vec3f& rDist, const Pnt3f viewPos ) const;
    void FindClosestPointExact( Vec3f& rDist, const Pnt3f viewPos ) const;

    void onCreate(const Surface *source = NULL);
    void onDestroy(void);

    void handleGL(Window* win, UInt32 idstatus);

    void adjustVolume(Volume & volume);

    virtual Action::ResultE drawPrimitives (DrawActionBase * action );

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SurfaceBase;

    // private class variables
    // FIXME: this is UGLY, having 3 variables for almost the same thing
    // OK, it's just two now, but still...
    BSplineTrimmedSurface *_trimmedSurface;     // internal representation
    CNurbsPatchSurface *_surfacePatch;          // encompassing class 
                                                // (tessellator class)
    Pnt3d   _min;                               // trimming curves BB
    Pnt3d   _max;
    Pnt2d   _minParam;                          // trimming curves BB in
    Pnt2d   _maxParam;                          // parameter space
	                                            // all the surfaces)
    static void initMethod(void);

    void calcIndexMapping(void);

    // private variables:
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Surface &source);    
};

typedef Surface *SurfaceP;

OSG_END_NAMESPACE

#include "OSGSurface.inl"
#include "OSGSurfaceBase.inl"

#define OSGSURFACE_HEADER_CVSID "@(#)$Id: OSGSurface.h,v 1.3 2006-11-09 20:59:39 edhellon Exp $"

#endif /* _OSGSURFACE_H_ */
