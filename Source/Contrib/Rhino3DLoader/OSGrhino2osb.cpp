/*---------------------------------------------------------------------------*\
 *                        OpenSG openNURBS loader                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2007-2008 by Seac02 S.r.l.     http://www.seac02.it         *
 * Copyright (C) 2008  by Patrik Mueller    muellerptr@users.sourceforge.net *
 * Copyright (C) 2008  by Akos Balazs       edhellon@cs.uni-bonn.de          *
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
/*
// Some portions are based on example_gl.cpp in the openNURBS distribution:
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#include <opennurbs/opennurbs.h>
#include "OSGrhino2osb.h"
#include <OSGSurface.h>
#include <OSGSwitch.h>
#include <OSGCoredNodePtr.h>
#include <OSGBaseFunctions.h>
#include <OSGMaterialMergeGraphOp.h>
#include <OSGSimpleAttachments.h>

OSG_USING_NAMESPACE


rhino2osb::rhino2osb(int curveInterpolationSteps, float tessError, bool doTessellation, const std::string &options):
    m_curveInterpolationSteps(curveInterpolationSteps),
    m_tessellationError(tessError),
    m_bDoTessellation(doTessellation),
    m_options(options),
    m_materials()
{
    // OpenNURBS init can be run multiple times so it should be safe here
    ON::Begin();
}


rhino2osb::~rhino2osb()
{
    // OpenNURBS deinit can be run multiple times so it should be safe here
    ON::End();
}

// create knot vectors from the ON knot vectors for surfaces and curves
NodePtr rhino2osb::convert_knots( const int order,     // ON_NurbsCurve order
              const int cv_count,  // ON_NurbsCurve cv count
              const double* knot,  // ON_NurbsCurve knot vector
              GLfloat* glknot,     // GL knot vector
              int bPermitScaling,  // TRUE if knot scaling is allowed
              double* scale        // If not NULL and knot scaling is
                                   // allowed, then the scaling
                                   // parameters are returned here.
                                   // glknot = (knot - scale[0])*scale[1]
            )
{
  // Because GL uses floats instead of doubles for knot vectors and
  // because some GLs are intolerant of closely spaced knots,
  // the returned glknots[] may be re-scaled when bPermitScaling
  // is TRUE.  When the knots belong to a trimmed surface, any rescaling
  // done to the surface's knots must be applied to the trimming geometry.

  const int knot_count = order + cv_count - 2;
  const int nknots = knot_count+2;
  
  // GL knot vectors have old-fashioned extra knot at start and end
  const double k0 = ON_SuperfluousKnot( order, cv_count, knot,0);
  const double k1 = ON_SuperfluousKnot( order, cv_count, knot,1);

  if ( scale ) {
    scale[0] = 0.0;
    scale[1] = 1.0;
  }
  
  int i, j;
  if ( bPermitScaling ) {
    double d0 = knot[order-2];
    double dk = 1.0;
    if ( bPermitScaling ) {
      double dmin = 1.0;
      double dmax = 1.0;
      double d;
      for ( i = 1; i < knot_count; i++ ) {
        d = knot[i] - knot[i-1];
        if ( d <= 0.0 )
          continue; // multiple knot
        if ( d < dmin )
          dmin = d;
        else if ( d > dmax )
          dmax = d;
      }
      if ( dmin > 0.0 && dmax >= dmin ) {
        if ( dmin < 1.0e-2 )
          dk = 1.0e-2/dmin;
        else if ( dmax > 1.0e4 ) {
          if ( 1.0e4*dmin >= 1.0e-2*dmax )
            dk = 1.0e4/dmax;        
        }
      }
    }
    if ( scale ) {
      scale[0] = d0;
      scale[1] = dk;
    }
    glknot[0] = (GLfloat)((k0-d0)*dk);
    for( i = 1, j = 0; j < knot_count; i++, j++ )
      glknot[i] = (GLfloat)((knot[j]-d0)*dk);
    glknot[nknots-1] = (GLfloat)((k1-d0)*dk);
  }
  else {
    glknot[0] = (GLfloat)k0;
    for( i = 1, j = 0; j < knot_count; i++, j++ )
      glknot[i] = (GLfloat)knot[j];
    glknot[nknots-1] = (GLfloat)k1;
  }

  return NullFC;
}

static void GetGLCV( const int dim, const int is_rat, const double* cv,
                     double xform[4][4], 
                     GLfloat* glcv )
{
  if ( xform ) {
    const double x = cv[0];
    const double y = cv[1];
    const double z = (dim == 3) ? cv[2] : 0.0;
    const double w = (is_rat) ? cv[dim] : 1.0;
    glcv[0] = (GLfloat)(xform[0][0]*x + xform[0][1]*y + xform[0][2]*z + xform[0][3]*w);
    glcv[1] = (GLfloat)(xform[1][0]*x + xform[1][1]*y + xform[1][2]*z + xform[1][3]*w);
    if ( dim == 3 )
      glcv[2] = (GLfloat)(xform[2][0]*x + xform[2][1]*y + xform[2][2]*z + xform[2][3]*w);
    if ( is_rat )
      glcv[dim] = (GLfloat)(xform[3][0]*x + xform[3][1]*y + xform[3][2]*z + xform[3][3]*w);
  }
  else {
    glcv[0] = (GLfloat)cv[0];
    glcv[1] = (GLfloat)cv[1];
    if ( dim == 3)
      glcv[2] = (GLfloat)cv[2];
    if ( is_rat )
      glcv[dim] = (GLfloat)cv[dim];
  }
}

NodePtr rhino2osb::process_curve( const ON_Curve& curve, double xform[][4] )
{
    const ON_PolyCurve* poly_curve = ON_PolyCurve::Cast(&curve);
    if ( poly_curve ) 
    {
        ON_Curve* pSegmentCurve = 0;
        int segment_count = poly_curve->Count();
        int i;
        for ( i = 0; i < segment_count; i++ ) {
            pSegmentCurve = poly_curve->SegmentCurve(i);
            if ( pSegmentCurve )
                process_curve( *pSegmentCurve, xform );
        }
        return NullFC;
    }
    
    const ON_CurveProxy* curve_proxy = ON_CurveProxy::Cast(&curve);
    if ( curve_proxy && !curve_proxy->ProxyCurveIsReversed() ) 
    {
        const ON_Curve* real_curve = curve_proxy->ProxyCurve();
        if ( 0 == real_curve )
            return NullFC;
        if ( curve_proxy == real_curve )
            return NullFC;
        if ( curve_proxy->ProxyCurveDomain() == real_curve->Domain() )
        {
//            printf("found proxy curve\n");
            return process_curve( *real_curve, xform );
        }
    }
    
    ON_NurbsCurve tmp;
    const ON_NurbsCurve* nurbs_curve = ON_NurbsCurve::Cast(&curve);
    if ( !nurbs_curve ) 
    {
        if ( curve.GetNurbForm(tmp) )
        {
            nurbs_curve = &tmp;
        }
        else
        {
            printf("Failed to get nurbs form of curve\n");
            return NullFC;
        }
        
    }
    return process_trimcurve( nurbs_curve->Dimension(), 
                              nurbs_curve->IsRational(),
                              nurbs_curve->Order(),
                              nurbs_curve->CVCount(),
                              nurbs_curve->Knot(),
                              nurbs_curve->m_cv_stride,
                              nurbs_curve->m_cv,
                              TRUE,
                              NULL,
                              xform );
}


NodePtr rhino2osb::process_trimcurve( int dim, int is_rat, int nurb_order, int cv_count,
              const double* knot_vector, 
              int cv_stride, const double* cv,
              int bPermitKnotScaling,
              double* knot_scale,
              double xform[][4]
            )
{
    std::vector<Real64> knotv;
    std::vector<Pnt3f> cps;
    int i;

    double dbg_ks[2];
    GLint nknots = nurb_order + cv_count; // GL knot count = TL knot count + 2
    GLfloat* knot = (GLfloat*)onmalloc( nknots*sizeof(*knot) );
    convert_knots( nurb_order, cv_count, knot_vector, knot, bPermitKnotScaling, dbg_ks);//knot_scale );

    // TRIMMING!
    GLint stride = cv_stride;
    GLfloat* ctlarray = (GLfloat*)onmalloc( stride*cv_count*sizeof(*ctlarray) );

//    printf("trim dim: %d is_rat: %d stride: %d order: %d\n", dim, is_rat, stride, nurb_order);
    for ( i = 0; i < cv_count; i++ ) 
    {
        GetGLCV( dim, is_rat, cv + i*cv_stride, xform, ctlarray + stride*i );
    } 
    
    // fill OpenSG structure
    for ( i = 0; i < cv_count; i++ )
    {
        Pnt3f actcp;
        if ( is_rat )
        {
            actcp[0] = *(ctlarray + i * stride + 0);
            actcp[1] = *(ctlarray + i * stride + 1);
            actcp[2] = *(ctlarray + i * stride + 2);
        }
        else
        {
            actcp[0] = *(ctlarray + i * stride + 0);
            actcp[1] = *(ctlarray + i * stride + 1);
            actcp[2] = 1.0;            
        }
        cps.push_back(actcp);

//        printf( "trim ctrl %f %f %f\n", actcp[0], actcp[1], actcp[2] );
    }

    for (i = 0; i < nknots; ++i)
    {
        // fill OpenSG structure
        knotv.push_back(knot[i]);
//        printf( "trim knot %f\n", knot[i] );
    }

    if( m_cCurrentSurface != NullFC )
    {
//        printf( "dimension: %d order: %d\n", dim, nurb_order );
        OSG_ASSERT(knotv.size() == cps.size() + nurb_order);
        /* add trim curve  */
        beginEditCP(m_cCurrentSurface, Surface::CurveFieldMask);
            m_cCurrentSurface->addCurve(nurb_order-1, knotv, cps, m_bNewTrimLoop );
        endEditCP  (m_cCurrentSurface, Surface::CurveFieldMask);
        m_bNewTrimLoop = false; // next curve will be in the same curveloop, if not
                             // the caller will set it to true
    }

  onfree( ctlarray );
  onfree( knot );


  return NullFC;
}

/* Here's the essence! */
NodePtr rhino2osb::convert_surface_to_osg( const ON_NurbsSurface& sOrig, 
                                         GLfloat* sknot, GLfloat* tknot )
{
    ON_NurbsSurface s = sOrig;
    int i, j;
    const int cv_size= s.CVSize();
    const int cv_count[2] = {s.CVCount(0), s.CVCount(1)};
    SurfacePtr surface;
    NodePtr ret = makeCoredNode<Surface>(&surface); 
    GeoPositions4fPtr cps4;
    GeoPositions3fPtr cps3;

    m_cCurrentSurface = surface;

    const bool isRational = s.IsRational();

    if (isRational)
    {
        cps4 = GeoPositions4f::create();
        beginEditCP( cps4, GeoPositions4f::GeoPropDataFieldMask );
        {
            cps4->clear();
            for (i = 0; i < cv_count[0]; i++)
            {
                for (j = 0; j < cv_count[1]; j++)
                {
                    ON_4dPoint tmpON_Point;
                    BOOL success = s.GetCV(i, j, tmpON_Point);
                    //printf("i%d j: %d on_point: %f %f %f %f\n", i, j, tmpON_Point.x, tmpON_Point.y, tmpON_Point.z, tmpON_Point.w);
                    //tmpON_Point.w = 1.0;
                    assert( success );
                    cps4->getField().push_back( Pnt4f(  tmpON_Point.x,  tmpON_Point.y,  tmpON_Point.z, tmpON_Point.w ));
                }
            }
        }
        endEditCP( cps4, GeoPositions4f::GeoPropDataFieldMask );
    }
    else
    {
        cps3 = GeoPositions3f::create();
        beginEditCP( cps3, GeoPositions3f::GeoPropDataFieldMask );
        {
            cps3->clear();
            for (int i = 0; i < cv_count[0]; i++)
            {
                for (int j = 0; j < cv_count[1]; j++)
                {
                    ON_4dPoint tmpON_Point;
                    BOOL success = s.GetCV(i, j, tmpON_Point);
                    assert (success);
                    //printf("i%d j: %d on_point: %f %f %f %f\n", i, j, tmpON_Point.x, tmpON_Point.y, tmpON_Point.z, tmpON_Point.w);
                    double weight = 1.0;
                    if (tmpON_Point.w != 0.0)
                    {
                        weight = 1.0/tmpON_Point.w;
                    }
                    Pnt3f thePoint(tmpON_Point.x*weight, 
                                   tmpON_Point.y*weight, 
                                   tmpON_Point.z*weight);
                    cps3->getField().push_back(thePoint);
                }
            }
        }
        endEditCP( cps3, GeoPositions3f::GeoPropDataFieldMask );
    } 

    int nControl = cv_count[0]*cv_count[1];
    GLint sknot_count = s.KnotCount(0) + 2;
    GLint tknot_count = s.KnotCount(1) + 2;
    GLint orderU, orderV;
    orderU = s.Order(0);
    orderV = s.Order(1);

    if( (sknot_count-orderU)*(tknot_count-orderV) != nControl )
    {
        printf( "inconsistent control points\n" );
        return NullFC;
    }

    beginEditCP(surface);
    {
        // let's clear the trimming
        surface->removeCurves();
        // set up dimensions and knot vectors:
        surface->setDimU( orderU-1 );
        surface->setDimV( orderV-1 );
        surface->getKnotsU().clear();
        surface->getKnotsV().clear();

        for (i = 0; i < sknot_count; ++i)
        {
            surface->getKnotsU().push_back(sknot[i]);
//            printf( "knot s %f\n", (float)sknot[i] );
        }

        for (i = 0; i < tknot_count; ++i)
        {
            surface->getKnotsV().push_back(tknot[i]);
//            printf( "knot t %f\n", (float)tknot[i] );
        }

        // set control points
        if( isRational )
            surface->setControlPoints(cps4);
        else
            surface->setControlPoints(cps3);
        // set error
        surface->setError( m_tessellationError);
        // and finally set the material
        surface->setMaterial(m_actMaterial);
    }
    endEditCP(surface);
    return ret;
}

// See comments in opennurbs_gl.h for calling instructions.

NodePtr rhino2osb::process_NURBS_surface( const ON_NurbsSurface& sOrig,
              int bPermitKnotScaling,
              double* knot_scale0,
              double* knot_scale1
             )
{
    int i, j, k;

    ON_NurbsSurface s = sOrig;

    if( !s.IsClamped(0) )
    {
        s.ClampEnd( 0, 2 );
    }
    if( !s.IsClamped(1) )
    {
        s.ClampEnd( 1, 2 );
    }

    // The "bPermitScaling" parameters to the ON_GL() call that
    // fills in the knot vectors is set to FALSE because any
    // rescaling that is applied to a surface domain must also
    // be applied to parameter space trimming curve geometry.

    // GL "s" knots
    GLint sknot_count = s.KnotCount(0) + 2;
    GLfloat* sknot = (GLfloat*)onmalloc( sknot_count*sizeof(*sknot) );
    convert_knots( s.Order(0), s.CVCount(0), s.Knot(0), sknot, 
                   bPermitKnotScaling, knot_scale0 );

    // GL "t" knots
    GLint tknot_count = s.KnotCount(1) + 2;
    GLfloat* tknot = (GLfloat*)onmalloc( tknot_count*sizeof(*tknot) );
    convert_knots( s.Order(1), s.CVCount(1), s.Knot(1), tknot,
                   bPermitKnotScaling, knot_scale1 );

    // control vertices
    const int cv_size= s.CVSize();
    const int cv_count[2] = {s.CVCount(0), s.CVCount(1)};
    GLint s_stride = cv_size*cv_count[1];
    GLint t_stride = cv_size;
    GLfloat* ctlarray = (GLfloat*)onmalloc( s_stride*cv_count[0]*sizeof(*ctlarray) );
    for ( i = 0; i < cv_count[0]; i++ ) 
    {
        for ( j = 0; j < cv_count[1]; j++ ) 
        {
            const double*  cv = s.CV(i,j);
            GLfloat* gl_cv = ctlarray + s_stride*i + t_stride*j;
            for ( k = 0; k < cv_size; k++ ) 
            {
                gl_cv[k] = (GLfloat)cv[k];
            }
        }
    }
  
    GLint sorder = s.Order(0);
    GLint torder = s.Order(1);

  
    // instead of calling gluNurbsSurface, try to convert the nurbs into
    // a OpenSG surface!
    NodePtr ret = convert_surface_to_osg( s, sknot, tknot );

    onfree( ctlarray );
    onfree( tknot );
    onfree( sknot );
  
    return ret;
}

NodePtr rhino2osb::process_brep(const ON_Brep& brep)
{
    const int face_count = brep.m_F.Count();
    int face_index;

    NodePtr child, parent = makeCoredNode<Group>();

    beginEditCP( parent );
    {
        //printf("brep face count: %d\n", face_count);
        for ( face_index = 0; face_index < face_count; face_index++ ) 
        {
            const ON_BrepFace& face = brep.m_F[face_index];
            child = process_brepface(face);
            if( child != NullFC )
            {
                parent->addChild(child);
            }
        }
    }
    endEditCP(parent);
    return parent;
}

void rhino2osb::doTess(NodePtr node)
{
    if ( m_bDoTessellation == false )
    {
        return;
    }
    SurfacePtr surf = SurfacePtr::dcast(node->getCore());
    if ( surf != NullFC )
    {
        beginEditCP(surf);
        //printf("tess start\n");
        surf->forceTessellate();
        //printf("tess end\n");
        unsigned int numtris = surf->getIndices()->size();
        //printf("number of tris: %d\n", numtris);
        endEditCP(surf);
    }
}

NodePtr rhino2osb::process_brepface( const ON_BrepFace& face )
{
    NodePtr ret = NullFC;

    const ON_Mesh* mesh;
    mesh = face.Mesh(ON::render_mesh);
    if ( mesh ) 
    {
        // use saved render mesh
        //printf("Found mesh associated with brepface, ignoring\n");
        if(m_options.find("importRenderMeshes=true") != std::string::npos)
            return process_mesh(mesh);
    }

    // convert to OpenSG struct
    double knot_scale[2][2] = {{0.0,1.0},{0.0,1.0}};
    const ON_Brep* brep = face.Brep();
    if ( !brep )
    {
        printf("Invalid brep for brepface\n");
        return NullFC;
    }

    // untrimmed surface
    ON_NurbsSurface tmp_nurbssrf;
    const ON_Surface* srf = brep->m_S[face.m_si];
    const ON_NurbsSurface* nurbs_srf = ON_NurbsSurface::Cast(srf);
    if ( !nurbs_srf ) 
    {
        // attempt to get NURBS form of this surface
        if ( srf->GetNurbForm( tmp_nurbssrf ) )
          nurbs_srf = &tmp_nurbssrf;
    }
    if ( !nurbs_srf )
    {
        printf("NURBS surface of face is invalid\n");
        return NullFC;
    }
    ret = process_NURBS_surface( *nurbs_srf, TRUE, knot_scale[0], knot_scale[1]);
    if ( brep->FaceIsSurface( face.m_face_index ) ) 
    {
        //printf("trivially trimmed face\n");
        doTess(ret);
        return ret; // face is trivially trimmed
    }

    int fli, li, lti, ti;

    // any knot scaling applied to the surface must also be applied to
    // the parameter space trimming geometry
    double xform[4][4] 
      = {{knot_scale[0][1], 0.0, 0.0, -knot_scale[0][0]*knot_scale[0][1] },
         {0.0, knot_scale[1][1], 0.0, -knot_scale[1][0]*knot_scale[1][1] },
         {0.0, 0.0, 1.0, 0.0},
         {0.0, 0.0, 0.0, 1.0}};

    // Add face's 2d trimming loop(s)
    const int face_loop_count = face.m_li.Count();
    for( fli = 0; fli < face_loop_count; fli++ ) 
    {
        li = face.m_li[fli];
        const ON_BrepLoop& loop = brep->m_L[li];
        const int loop_trim_count = loop.m_ti.Count();
      
        // set flag for opensg trimming semantics
        m_bNewTrimLoop = true;
        for( lti = 0; lti < loop_trim_count; lti++ ) 
        {
            ti = loop.m_ti[lti];
            const ON_BrepTrim& trim = brep->m_T[ti];
            // TRIMMING LOOP
//            printf("converting loop: %d curve: %d\n", fli, lti);
            process_curve(trim, xform);
        } // curves per loop
    } // loops

  // if not trivially trimmed, only tessellate after the trimcurves have been added
  doTess(ret);
    
  return ret;
}

NodePtr rhino2osb::process_surface(const ON_Surface& surface)
{
    ON_NurbsSurface tmp;
    const ON_NurbsSurface* nurbs_surface;
    nurbs_surface = ON_NurbsSurface::Cast(&surface);
    if ( !nurbs_surface ) 
    {
        if ( surface.GetNurbForm(tmp) ) 
        {
            nurbs_surface = &tmp;
        }
        else
        {
            printf("Unable to get NURBS representation of surface\n");
            return NullFC;
        }
    }
    if ( nurbs_surface )
    {
        // if it's not a brepface, it can't be trimmed
        NodePtr ret = NullFC;
        ret = process_NURBS_surface( *nurbs_surface, TRUE );
        doTess(ret);
        return ret; 
    }
    return NullFC;
}

void rhino2osb::process_material( const ONX_Model& model, int index )
{
    ON_Color actcol;
    // debug checks for material
/*
    ON_3dmObjectAttributes on_attr = model.m_object_table[index].m_attributes;
    int material_index = -1;
    if (on_attr.MaterialSource() == ON::material_from_layer )
    {
        printf("material is from layer attribs\n");
        if ( on_attr.m_layer_index >= 0 && 
        on_attr.m_layer_index < model.m_layer_table.Count() )
        {
            material_index = model.m_layer_table[on_attr.m_layer_index].RenderMaterialIndex();
        }
     }
     else if (on_attr.MaterialSource() == ON::material_from_object )
     {
         printf("material is from object\n");
     }
     else if (on_attr.MaterialSource() == ON::material_from_parent )
     {
         printf("material is from parent\n");
     }
     else
     {
         printf("unknown material attrib: %x\n", on_attr.MaterialSource());
     }
     printf("material index: %d\n", material_index);
 */
    const ONX_Model_Object& mo = model.m_object_table[index];
    const ON_Object* geometry = mo.m_object;
    // we have to check if it's a curve and adjust its material accordingly
    const ON_Curve* curve = NULL;
    ON_Material mat;
    model.GetRenderMaterial(mo.m_attributes, mat);
    std::map<int, SimpleMaterialPtr>::iterator it = m_materials.find(mat.MaterialIndex());
    if(it != m_materials.end())
    {
        m_actMaterial = (*it).second;
        return;
    }

    curve = ON_Curve::Cast(geometry);
    if (NULL != curve)
    {
        ON_Color c = model.WireframeColor( mo.m_attributes );
        ON_Color black(0,0,0);
        mat.Default();
        mat.SetAmbient(black);
        mat.SetDiffuse(black);
        mat.SetSpecular(black);
        mat.SetEmission(c);
    }

    m_actMaterial = SimpleMaterial::create();
    beginEditCP(m_actMaterial);
    {
        actcol = mat.Diffuse();
        m_actMaterial->setDiffuse( Color3f(actcol.FractionRed(), 
                                           actcol.FractionGreen(),
                                           actcol.FractionBlue() ) );
        actcol = mat.Ambient();
        m_actMaterial->setAmbient( Color3f(actcol.FractionRed(), 
                                           actcol.FractionGreen(),
                                           actcol.FractionBlue() ) );
        actcol = mat.Emission();
        m_actMaterial->setEmission( Color3f(actcol.FractionRed(), 
                                            actcol.FractionGreen(),
                                            actcol.FractionBlue() ) );
        actcol = mat.Specular();
        m_actMaterial->setSpecular( Color3f(actcol.FractionRed(), 
                                            actcol.FractionGreen(),
                                            actcol.FractionBlue() ) );
        // dunno why it's done this way, but this is how the Rhino GL example
        // gets sort of okay lighting
        if (mat.Shine() < ON_EPSILON )
        {
            m_actMaterial->setSpecular( Color3f(0.0f, 0.0f, 0.0f) );
        }
        m_actMaterial->setShininess( 128.0*(mat.Shine() / ON_Material::MaxShine() ) );
    }
    endEditCP(m_actMaterial);

    ON_String mat_name = mat.m_material_name;
    if(mat_name.Array() != NULL)
        OSG::setName(m_actMaterial, mat_name.Array());

    m_materials.insert(std::make_pair(mat.MaterialIndex(), m_actMaterial));

    //m_actMaterial->dump();
}

NodePtr rhino2osb::buildNode( const ONX_Model& model, int index )
{
    // Called from myDisplay() to show geometry.
    // Uses ON_GL() functions found in rhinoio_gl.cpp.
    const ON_Point* point = NULL;
    const ON_PointCloud* cloud = NULL;
    const ON_PointGrid* grid = NULL;
    const ON_Brep* brep = NULL;
    const ON_Mesh* mesh = NULL;
    const ON_Curve* curve = NULL;
    const ON_Surface* surface = NULL;
    const ONX_Model_Object& mo = model.m_object_table[index];
    const ON_Object* geometry = mo.m_object;
    
    if ( geometry == NULL )
    {
        return NullFC;
    }

    brep = ON_Brep::Cast(geometry);
    if ( brep ) 
    {
        //printf("found brep\n");
        process_material(model, index);
        return process_brep(*brep);
    }
    mesh = ON_Mesh::Cast(geometry);
    if ( mesh ) 
    {
        //printf("found mesh\n");
        process_material(model, index);
        return process_mesh(mesh);
    }

//    curve = ON_Curve::Cast(geometry);
//    if ( curve ) 
//    {
//        printf("found curve\n");
//        process_material(model, index);
//        return process_curve( *curve, 0 );
//    }

    surface = ON_Surface::Cast(geometry);
    if ( surface ) 
    {
        //printf("found surface\n");
        process_material(model, index);
        return process_surface( *surface );
    }

    point = ON_Point::Cast(geometry);
    if ( point ) 
    {
        //printf("found point\n");
        process_material(model, index);
        return process_point(point);
    }

    cloud = ON_PointCloud::Cast(geometry);
    if ( cloud ) 
    {
        //printf("found pointcloud\n");
        process_material(model, index);
        return process_pointcloud(cloud);
    }

    grid = ON_PointGrid::Cast(geometry);
    if ( grid ) 
    {
        //printf("found pointgrid\n");
        process_material(model, index);
        return process_pointgrid(grid);
    }
    curve = ON_Curve::Cast(geometry);
    if ( curve ) 
    {
        //printf("found curve\n");
        process_material(model, index);
        return process_curve(curve);
    }
    printf("found unkown object\n");
    return NullFC;
}

NodePtr rhino2osb::process_point(const ON_Point* theGeometry)
{
    return process_points(theGeometry);
}

NodePtr rhino2osb::process_pointcloud(const ON_PointCloud* theGeometry)
{
    return process_points(theGeometry);
}

NodePtr rhino2osb::process_pointgrid(const ON_PointGrid* theGeometry)
{
    return process_points(theGeometry);
}


NodePtr rhino2osb::process_points(const ON_Geometry* theGeometry)
{
    NodePtr result = NullFC;
    
    if (theGeometry != NULL)
    {
        const ON_Point* thePoint = ON_Point::Cast(theGeometry);
        const ON_PointCloud* theCloud = ON_PointCloud::Cast(theGeometry);
        const ON_PointGrid* theGrid = ON_PointGrid::Cast(theGeometry);

        long nbPoints = 0;
        if (NULL != thePoint)
            nbPoints = 1;
        else if (NULL != theCloud)
            nbPoints = theCloud->m_P.Count();
        else if (NULL != theGrid)
            nbPoints = theGrid->PointCount(0) * theGrid->PointCount(1);
        
        if (nbPoints > 0)
        {
            GeometryPtr geom;

            GeoPositions3fPtr   points;
            GeoPLengthsPtr      lens;
            GeoPTypesPtr        type;

            geom = Geometry::create();
            points = GeoPositions3f::create();

            lens = GeoPLengthsUI32::create();
            type = GeoPTypesUI8::create();

            // set the points and normals
            beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
            GeoNormals3fPtr     norms;

            beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
            beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);

            if (NULL != thePoint)
            {
                type->addValue( GL_POINTS );
                lens->addValue(1);
                points->addValue(Pnt3f(thePoint->point.x, thePoint->point.y, thePoint->point.z));
            }
            else if (NULL != theCloud)
            {
                for (long i = 0; i < nbPoints; i++)
                {
                    type->addValue( GL_POINT );
                    lens->addValue(1);
                    const ON_3dPoint* tmpPoint = theCloud->m_P.At(i);
                    points->addValue(Pnt3f(tmpPoint->x, tmpPoint->y, tmpPoint->z));
                }
            }
            else if (NULL != theGrid)
            {
                for (long i = 0; i < theGrid->PointCount(0); i++)
                {
                    for (long j = 0; j < theGrid->PointCount(1); j++)
                    {

                        type->addValue( GL_POINT );
                        lens->addValue(1);
                        const ON_3dPoint& tmpPoint = theGrid->Point(i,j);
                        points->addValue(Pnt3f(tmpPoint.x, tmpPoint.y, tmpPoint.z));
                    }
                }
            }

            endEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
            endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);

            endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);

            beginEditCP(result, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
            {
                geom->setTypes    (type);
                geom->setLengths  (lens);
                geom->setPositions(points);
                geom->setMaterial(m_actMaterial);
            }
            endEditCP(result, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
            
            result = makeCoredNode<Geometry>(&geom); 
 
        }
    }    
    return result;
}

OSG::NodePtr rhino2osb::process_curve(const ON_Geometry* theGeometry)
{
    if (theGeometry != NULL)
    {
        const ON_Curve* theCurve = ON_Curve::Cast(theGeometry);
        if (theCurve != NULL)
        {
            if (theCurve->IsValid())
            {
                const ON_LineCurve* lineCurve = ON_LineCurve::Cast(theCurve);
                if (lineCurve)
                    return process_linecurve(lineCurve);

                const ON_PolylineCurve* polylineCurve = ON_PolylineCurve::Cast(theCurve);
                if (polylineCurve)
                    return process_polylinecurve(polylineCurve);

                const ON_NurbsCurve* actNurbsCurve = ON_NurbsCurve::Cast(theCurve);
                if (actNurbsCurve)
                    return process_nurbscurve(actNurbsCurve);
                actNurbsCurve = theCurve->NurbsCurve();
                if (actNurbsCurve)
                    return process_curve(actNurbsCurve);
            }
        }
    }
    return NullFC;
}

OSG::NodePtr rhino2osb::process_nurbscurve(const ON_NurbsCurve* theGeometry)
{
    NodePtr result = NullFC;
    
    if (theGeometry != NULL)
    {
        result = Node::create();
        ON_Interval startEnd = theGeometry->Domain();


        const double length = osgabs(startEnd.m_t[1] - startEnd.m_t[0]);
        const double step = length / m_curveInterpolationSteps;

        GeoPositions3fPtr   points;
        GeoPLengthsPtr      lens;
        GeoPTypesPtr        type;

        GeometryPtr geom = Geometry::create();
        points = GeoPositions3f::create();
        int nbPoints = 0;
        lens = GeoPLengthsUI32::create();
        type = GeoPTypesUI8::create();

        // set the points
        beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
            ON_3dPoint tmpPoint;

            for (double i = startEnd.m_t[0]; i <= startEnd.m_t[1]; i += step)
            {
                if (theGeometry->EvPoint(i, tmpPoint))
                {
                    points->addValue(Pnt3f(tmpPoint.x, tmpPoint.y, tmpPoint.z));
                    ++nbPoints;
                }
            }
            if (theGeometry->IsClosed())
            {
                if (theGeometry->EvPoint(startEnd.m_t[0], tmpPoint))
                {
                    points->addValue(Pnt3f(tmpPoint.x, tmpPoint.y, tmpPoint.z));
                    ++nbPoints;
                }
            }
        endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);

        beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
            type->addValue( GL_LINE_STRIP );
        endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);

        beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
            lens->addValue(nbPoints);
        endEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);


        beginEditCP(geom, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );
        {
            geom->setTypes    (type);
            geom->setLengths  (lens);
            geom->setPositions(points);
            geom->setMaterial(m_actMaterial);
        }
        endEditCP(geom, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );

        beginEditCP(result, Node::CoreFieldMask);
        {
            result->setCore(geom);
        }
        endEditCP(result, Node::CoreFieldMask);

    }    
    return result;
}

OSG::NodePtr rhino2osb::process_polylinecurve(const ON_PolylineCurve* theGeometry)
{
    NodePtr result = NullFC;
    if (theGeometry != NULL)
    {
        GeoPositions3fPtr   points;
        GeoPLengthsPtr      lens;
        GeoPTypesPtr        type;

        result = Node::create();

        GeometryPtr geom = Geometry::create();
        points = GeoPositions3f::create();
        int nbPoints = theGeometry->PointCount();
        lens = GeoPLengthsUI32::create();
        type = GeoPTypesUI8::create();

        // set the points
        beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
            for (long i = 0; i < nbPoints; i++)
            {
                const ON_3dPoint* tmpPoint = theGeometry->m_pline.At(i);
                points->addValue(Pnt3f(tmpPoint->x, tmpPoint->y, tmpPoint->z));
            }
            if (theGeometry->IsClosed())
            {
                const ON_3dPoint* tmpPoint = theGeometry->m_pline.At(0);
                points->addValue(Pnt3f(tmpPoint->x, tmpPoint->y, tmpPoint->z));
                ++nbPoints;
            }
        endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);

        beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
            type->addValue( GL_LINE_STRIP );
        endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);

        beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
            lens->addValue(nbPoints);
        endEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);


        beginEditCP(geom, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );
        {
            geom->setTypes    (type);
            geom->setLengths  (lens);
            geom->setPositions(points);
            geom->setMaterial(m_actMaterial);
        }
        endEditCP(result, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );

        beginEditCP(result, Node::CoreFieldMask);
        {
            result->setCore(geom);
        }
        endEditCP(result, Node::CoreFieldMask);
    }    
    return result;
}


OSG::NodePtr rhino2osb::process_linecurve(const ON_LineCurve* theGeometry)
{
    NodePtr result = NullFC;
    
    if (theGeometry != NULL)
    {
        result = Node::create();
        
        GeoPositions3fPtr   points;
        GeoPLengthsPtr      lens;
        GeoPTypesPtr        type;

        GeometryPtr geom = Geometry::create();
        points = GeoPositions3f::create();

        lens = GeoPLengthsUI32::create();
        type = GeoPTypesUI8::create();

        // set the points and normals
        beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
            points->addValue(Pnt3f(theGeometry->m_line.from.x, theGeometry->m_line.from.y, theGeometry->m_line.from.z));
            points->addValue(Pnt3f(theGeometry->m_line.to.x, theGeometry->m_line.to.y, theGeometry->m_line.to.z));
        endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);

        beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
            type->addValue( GL_LINES );
        endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);

        beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
            lens->addValue(2);
        endEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);


        beginEditCP(geom, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );
        {
            geom->setTypes    (type);
            geom->setLengths  (lens);
            geom->setPositions(points);
            geom->setMaterial(m_actMaterial);
        }
        endEditCP(geom, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::MaterialFieldMask  );

        beginEditCP(result, Node::CoreFieldMask);
        {
            result->setCore(geom);
        }
        endEditCP(result, Node::CoreFieldMask);

    }    
    return result;
}


OSG::NodePtr rhino2osb::process_mesh(const ON_Mesh* theMesh)
{
    NodePtr result = NullFC;
    if (theMesh == NULL)
        return result;

    const int face_count = theMesh->FaceCount();

    if(face_count <= 0)
        return result;

    result = Node::create();
    GeometryPtr geo = Geometry::create();
    beginEditCP(result, Node::CoreFieldMask);
        result->setCore(geo);
    endEditCP(result, Node::CoreFieldMask);

    const bool bHasNormals = theMesh->HasVertexNormals();
    const bool bHasTCoords = theMesh->HasTextureCoordinates();

    GeoPositions3fPtr points = GeoPositions3f::create();
    GeoNormals3fPtr normals = NullFC;
    if(bHasNormals)
        normals = GeoNormals3f::create();
    GeoTexCoords2fPtr texcoords  = NullFC;
    if(bHasTCoords)
        texcoords  = GeoTexCoords2f::create();

    beginEditCP(points);
    if(normals != NullFC)
        beginEditCP(normals);
    if(texcoords != NullFC)
        beginEditCP(texcoords);

    int tri_count = 0;
    int i0, i1, i2, j0, j1, j2;
    ON_3fPoint v[4];
    ON_3fVector n[4];
    ON_2fPoint t[4];
    for(int fi = 0; fi < face_count; ++fi)
    {
        const ON_MeshFace& f = theMesh->m_F[fi];

        v[0] = theMesh->m_V[f.vi[0]];
        v[1] = theMesh->m_V[f.vi[1]];
        v[2] = theMesh->m_V[f.vi[2]];

        if ( bHasNormals )
        {
            n[0] = theMesh->m_N[f.vi[0]];
            n[1] = theMesh->m_N[f.vi[1]];
            n[2] = theMesh->m_N[f.vi[2]];
        }

        if ( bHasTCoords )
        {
            t[0] = theMesh->m_T[f.vi[0]];
            t[1] = theMesh->m_T[f.vi[1]];
            t[2] = theMesh->m_T[f.vi[2]];
        }

        if (f.IsQuad() )
        {
            // quadrangle - render as two triangles
            v[3] = theMesh->m_V[f.vi[3]];
            if ( bHasNormals )
                n[3] = theMesh->m_N[f.vi[3]];
            if ( bHasTCoords )
                t[3] = theMesh->m_T[f.vi[3]];
            if ( v[0].DistanceTo(v[2]) <= v[1].DistanceTo(v[3]) )
            {
                i0 = 0; i1 = 1; i2 = 2;
                j0 = 0; j1 = 2; j2 = 3;
            }
            else
            {
                i0 = 1; i1 = 2; i2 = 3;
                j0 = 1; j1 = 3; j2 = 0;
            }
            tri_count += 2;
        }
        else
        {
            // single triangle
            i0 = 0; i1 = 1; i2 = 2;
            j0 = j1 = j2 = 0;
            ++tri_count;
        }

        // first triangle
        points->editFieldPtr()->push_back(Pnt3f(v[i0].x, v[i0].y, v[i0].z));
        points->editFieldPtr()->push_back(Pnt3f(v[i1].x, v[i1].y, v[i1].z));
        points->editFieldPtr()->push_back(Pnt3f(v[i2].x, v[i2].y, v[i2].z));
        if ( bHasNormals )
        {
            normals->editFieldPtr()->push_back(Vec3f(n[i0].x, n[i0].y, n[i0].z));
            normals->editFieldPtr()->push_back(Vec3f(n[i1].x, n[i1].y, n[i1].z));
            normals->editFieldPtr()->push_back(Vec3f(n[i2].x, n[i2].y, n[i2].z));
        }
        if ( bHasTCoords )
        {
            texcoords->editFieldPtr()->push_back(Vec2f(t[i0].x, t[i0].y ));
            texcoords->editFieldPtr()->push_back(Vec2f(t[i1].x, t[i1].y ));
            texcoords->editFieldPtr()->push_back(Vec2f(t[i2].x, t[i2].y ));
        }

        if ( j0 != j1 )
        {
            // if we have a quad, second triangle
            points->editFieldPtr()->push_back(Pnt3f(v[j0].x, v[j0].y, v[j0].z));
            points->editFieldPtr()->push_back(Pnt3f(v[j1].x, v[j1].y, v[j1].z));
            points->editFieldPtr()->push_back(Pnt3f(v[j2].x, v[j2].y, v[j2].z));
            if ( bHasNormals )
            {
                normals->editFieldPtr()->push_back(Vec3f(n[j0].x, n[j0].y, n[j0].z));
                normals->editFieldPtr()->push_back(Vec3f(n[j1].x, n[j1].y, n[j1].z));
                normals->editFieldPtr()->push_back(Vec3f(n[j2].x, n[j2].y, n[j2].z));
            }
            if ( bHasTCoords )
            {
                texcoords->editFieldPtr()->push_back(Vec2f(t[j0].x, t[j0].y ));
                texcoords->editFieldPtr()->push_back(Vec2f(t[j1].x, t[j1].y ));
                texcoords->editFieldPtr()->push_back(Vec2f(t[j2].x, t[j2].y ));
            }
        }
    }

    if(texcoords != NullFC)
        endEditCP(texcoords);
    if(normals != NullFC)
        endEditCP(normals);
    endEditCP(points);

    int nv = tri_count * 3;

    GeoPLengthsUI32Ptr lengths = GeoPLengthsUI32::create();
    beginEditCP(lengths);
        lengths->push_back(nv);
    endEditCP(lengths);
    
    GeoPTypesUI8Ptr types = GeoPTypesUI8::create();
    beginEditCP(types);
        types->push_back(GL_TRIANGLES);
    endEditCP(types);

    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices);
        indices->getFieldPtr()->reserve(nv);
        for (int i = 0; i < nv; ++i)
            indices->editFieldPtr()->push_back(i);
    endEditCP(indices);

    int imapping = Geometry::MapPosition;
    if(normals != NullFC)
        imapping |= Geometry::MapNormal;
    if(texcoords != NullFC)
        imapping |= Geometry::MapTexCoords;

    beginEditCP(geo);
        geo->setMaterial(m_actMaterial);
        geo->setPositions(points);
        if(normals != NullFC)
            geo->setNormals(normals);
        if(texcoords != NullFC)
            geo->setTexCoords(texcoords);
        geo->setIndices(indices);
        geo->setLengths(lengths);
        geo->setTypes(types);
        geo->editMFIndexMapping()->push_back(imapping);
    endEditCP(geo);

    return result;
}

NodePtr rhino2osb::load( const char *fileName )
{
  
    ON_TextLog on_error_log;
    
    // read the file
    ONX_Model model;
    if ( !model.Read( fileName, &on_error_log ) )
    {
        return NullFC;
    }
    
    NodePtr child;
    
    m_pRootNode = makeCoredNode<Group>();
    
    int i;
    int object_count = model.m_object_table.Count();
    printf("object count: %d\n", object_count);
    
    beginEditCP( m_pRootNode );
    for ( i = 0; i < object_count; i++ ) 
    {
        child = buildNode(model, i);
        if( child != NullFC )
        {
            ON_3dmObjectAttributes &attr = model.m_object_table[i].m_attributes;
            ON_String node_name = attr.m_name;
            if(node_name.Array() != NULL)
                OSG::setName(child, node_name.Array());
            m_pRootNode->addChild( child );
        }
    }
    endEditCP( m_pRootNode );

    // disabled it, duplicated materials are already removed via material map.
#if 0
    // merge materials
    MaterialMergeGraphOp *mergematop = new MaterialMergeGraphOp;
    bool res = mergematop->traverse(m_pRootNode);
    if (!res)
    {
        FWARNING(("Material merge graphOp failed\n"));
    }
    delete mergematop;
#endif

    return m_pRootNode;
}
