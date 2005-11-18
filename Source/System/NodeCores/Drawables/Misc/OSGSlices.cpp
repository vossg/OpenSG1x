/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGGL.h>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGTypedFunctors.h>

#include <OSGCamera.h>

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>
#include <OSGWindow.h>
#include <OSGGLEXT.h>

#include "OSGSlices.h"

OSG_USING_NAMESPACE

/*! \class osg::Slices
*/

UInt32 Slices::_arbMultitexture = Window::invalidFunctionID;
UInt32 Slices::_funcMultiTexCoord3fARB = Window::invalidFunctionID;

typedef void (OSG_APIENTRY * PFNGLMULTITEXCOORD3FARBPROC)(GLenum target,
                                                          GLfloat s,
                                                          GLfloat t,
                                                          GLfloat r);

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Slices::Slices(void) :
    Inherited()
{
    _arbMultitexture = 
       Window::registerExtension("GL_ARB_multitexture");

    _funcMultiTexCoord3fARB =
        Window::registerFunction(OSG_DLSYM_UNDERSCORE"glMultiTexCoord3fARB", 
                                 _arbMultitexture);
}

//! Copy Constructor

Slices::Slices(const Slices &source) :
    Inherited(source)
{
}

//! Destructor

Slices::~Slices(void)
{
    subRefCP(_sfMaterial.getValue());
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Slices::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
                                    osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MaterialDrawablePtr  ,
                                    CNodePtr      ,
                                    Action       *>(&MaterialDrawable::drawActionHandler));
  
    RenderAction::registerEnterDefault( getClassType(),
                                      osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                      MaterialDrawablePtr  ,
                                      CNodePtr      ,
                                      Action       *>(&MaterialDrawable::renderActionHandler));
  
    IntersectAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                         SlicesPtr  ,
                                         CNodePtr      ,
                                         Action       *>(&Slices::intersect));
  

}

//! react to field changes

void Slices::changed(BitVector  whichField, 
                     UInt32     origin     )
{
    if(whichField & MaterialFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfMaterial.getValue());
            }
            else
            {
                MaterialPtr pMat = _sfMaterial.getValue();

                _sfMaterial.setValue(NullFC);

                setMaterial(pMat);
            }
        }
    }

    if(whichField & SizeFieldMask)
    {
       initEdgeVec();
       invalidateVolume();
    }

}

//! output the instance for debug purposes

void Slices::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Slices NI" << std::endl;
}

Action::ResultE Slices::intersect(Action * OSG_CHECK_ARG(action) )
{
  /*
    IntersectAction     * ia = dynamic_cast<IntersectAction*>(action);
    const DynamicVolume  &dv = ia->getActNode()->getVolume();

    if( dv.isValid() && !dv.intersect(ia->getLine()) )
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    TriangleIterator it;
    Real32 t;
    Vec3f norm;

    for( it = this->beginTriangles(); it != this->endTriangles(); ++it )
    {
        if( ia->getLine().intersect( it.getPosition(0),
                                     it.getPosition(1),
                                     it.getPosition(2), t, &norm) )
        {
            ia->setHit( t, ia->getActNode(), it.getIndex(), norm );
        }
    }
    
  */

    return Action::Continue;
}

Action::ResultE Slices::drawPrimitives(DrawActionBase *action)
{
    Matrix camera,toworld;
    UInt32 triCount, vertexCount;
    Vec3f planeNormal(0,0,1);
    StatCollector *coll = action->getStatistics();
    StatIntElem   *el   = 0;
    
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    
    camera = action->getCameraToWorld();
    
    if(ra != NULL)
    {
      toworld = ra->top_matrix();
    }
    else
    {
      action->getActNode()->getToWorld(toworld);
    }

    // normalize them, we don't want to neutralize scales in toworld
    toworld[0].normalize();
    toworld[1].normalize();
    toworld[2].normalize();
    toworld.invert();
    camera.multLeft(toworld);
  
    // Viewer direction  
    camera.multMatrixVec(planeNormal,planeNormal);
    planeNormal.normalize();

    drawSlices(action->getWindow(), planeNormal,triCount,vertexCount);

    if (coll) 
    {
        if((el = coll->getElem(Drawable::statNTriangles,false)))
            el->add(triCount);
        if((el = coll->getElem(Drawable::statNVertices,false)))
            el->add(vertexCount);
    }

    /* TODO; bbox draw code; just for debuggging; drawBBox opt ?
    glPushAttrib ( GL_ENABLE_BIT );
    glDisable (GL_LIGHTING);
    glDisable (GL_TEXTURE_1D);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_TEXTURE_3D);
    
    glBegin( GL_LINES );    
    {
        for (int i = 0; i < 12; i++) 
        {
            glVertex3fv (_pointVec[_edgeVec[i].pointIndexA].getValues());
            glVertex3fv (_pointVec[_edgeVec[i].pointIndexB].getValues());
        }
    }  
    glEnd();
    glPopAttrib();
    */

    return Action::Continue;
}

void Slices::adjustVolume( Volume & volume )
{   
    Vec3f v(_sfSize.getValue());
    Pnt3f p(v[0],v[1],v[2]);
    
    volume.setValid();
    volume.setEmpty();
    
    p /= 2;
    volume.extendBy ( p );
    
    p.negate();
    volume.extendBy ( p );
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void Slices::initEdgeVec( void )
{
    UInt32 i;
    std::vector<Pnt3f> & p(_pointVec);
    const Vec3f size(getSize());

    FDEBUG (("Run Slices::initEdgeVec()\n"));

    // create the corner points
    
    //     4--------5    
    //    /|       /|   
    //   / |      / |  
    //  /  |     /  | 
    // 7--------6   | 
    // |   0----|---1 
    // |  /     |  /  
    // | /      | /   
    // |/       |/   
    // 3--------2 

    _pointVec.resize(8);
    
    p[0][0] = p[3][0] = p[4][0] = p[7][0] = -0.5f * size.x();
    p[1][0] = p[2][0] = p[5][0] = p[6][0] =  0.5f * size.x();
    p[0][1] = p[1][1] = p[2][1] = p[3][1] = -0.5f * size.y();
    p[4][1] = p[5][1] = p[6][1] = p[7][1] =  0.5f * size.y();
    p[0][2] = p[1][2] = p[4][2] = p[5][2] = -0.5f * size.z();
    p[2][2] = p[3][2] = p[6][2] = p[7][2] =  0.5f * size.z();

    // create the edge description       
    //     4--------5      *---4----*     0: - - - 
    //    /|       /|     /|       /|     1: + - - 
    //   / |      / |    7 |      5 |     2: + - + 
    //  /  |     /  |   /  8     /  9     3: - - +
    // 7--------6   |  *----6---*   |     4: - + -
    // |   0----|---1  |   *---0|---*     5: + + -
    // |  /     |  /   11 /     10 /      6: + + +
    // | /      | /    | 3      | 1       7: - + + 
    // |/       |/     |/       |/        
    // 3--------2      *---2----*
    //
    // cubeCorners     edges

    _edgeVec.resize(12);

    _edgeVec[0].pointIndexA = 0;     // 1 : positiv   0: negativ   00: parallel
    _edgeVec[0].pointIndexB = 1;     // xmax xmin ymax ymin zmax zmin
    _edgeVec[0].edgeTag = 5;         //  0    0    0    1    0    1  
    
    _edgeVec[1].pointIndexA = 1;
    _edgeVec[1].pointIndexB = 2;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[1].edgeTag = 36;       //  1    0    0    1    0    0   
    
    _edgeVec[2].pointIndexA = 2;
    _edgeVec[2].pointIndexB = 3;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[2].edgeTag = 6;        //  0    0    0    1    1    0
    
    _edgeVec[3].pointIndexA = 3;
    _edgeVec[3].pointIndexB = 0;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[3].edgeTag = 20;       //  0    1    0    1    0    0
    
    _edgeVec[4].pointIndexA = 4;
    _edgeVec[4].pointIndexB = 5;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[4].edgeTag = 9;        //   0   0    1    0    0    1
          
    _edgeVec[5].pointIndexA = 5;
    _edgeVec[5].pointIndexB = 6;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[5].edgeTag = 40;       //   1   0    1    0    0    0
    
    _edgeVec[6].pointIndexA = 6;
    _edgeVec[6].pointIndexB = 7;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[6].edgeTag = 10;       //  0    0    1    0    1    0
    
    _edgeVec[7].pointIndexA = 7;
    _edgeVec[7].pointIndexB = 4;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[7].edgeTag = 24;       //  0    1    1    0    0    0
    
    _edgeVec[8].pointIndexA = 0;
    _edgeVec[8].pointIndexB = 4;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[8].edgeTag = 17;       //  0    1    0    0    0    1
    
    _edgeVec[9].pointIndexA = 1;
    _edgeVec[9].pointIndexB = 5;    // xmax xmin ymax ymin zmax zmin
    _edgeVec[9].edgeTag = 33;       //  1    0    0    0    0    1
    
    _edgeVec[10].pointIndexA = 2;
    _edgeVec[10].pointIndexB = 6;   // xmax xmin ymax ymin zmax zmin
    _edgeVec[10].edgeTag = 34;      //  1    0    0    0     1   0
    
    _edgeVec[11].pointIndexA = 3;
    _edgeVec[11].pointIndexB = 7;   // xmax xmin ymax ymin zmax zmin
    _edgeVec[11].edgeTag = 18;      //  0    1    0    0    1   0 

    // create one line for every edge
    for (i = 0; i < 12; i++) 
      _edgeVec[i].line.setValue( _pointVec[_edgeVec[i].pointIndexA],
                               _pointVec[_edgeVec[i].pointIndexB]);
}

UInt32 Slices::createSlice ( const OSG::Plane &plane, Slice &slice )
{
    UInt32 i,j,k, lastButOne;
    Vec3f v1, v2, winding;
    bool pointInHalfSpace[8];
    unsigned swapCount = 0;
    
    // clip the plane with the corner points
    for(i = 0; i < 8; i++) 
        pointInHalfSpace[i] = plane.isInHalfSpace(_pointVec[i]);
  
    // calculate the intersection points
    for(slice.numOfIntersection = i = 0; i < 12; i++)
    {
        if((pointInHalfSpace[_edgeVec[i].pointIndexA] !=
            pointInHalfSpace[_edgeVec[i].pointIndexB] )) 
        {
            plane.intersect(_edgeVec[i].line, 
                            slice.pointVec[slice.numOfIntersection] );
            slice.edgeVec[slice.numOfIntersection] = i;
            slice.numOfIntersection++;
        }
    }

    if (slice.numOfIntersection > 2) 
    {
        lastButOne = slice.numOfIntersection - 2;
        i=j=k=0;

        // edge sort
        for (; j++ <= lastButOne; i++)
        {
            // find first invalid edgeTag -> j 
            while((j <= lastButOne) && 
                  ((_edgeVec[slice.edgeVec[i]].edgeTag &
                  _edgeVec[slice.edgeVec[j]].edgeTag ) != 0)) 
            {
                i++;  
                j++;
            }

            // check whether edgeTags are disordered
            if (j <= lastButOne) 
            { 
                // find first valid edgeTag -> k
                k = j+1;
                while((k <= lastButOne) &&
                      ((_edgeVec[slice.edgeVec[i]].edgeTag &
                      _edgeVec[slice.edgeVec[k]].edgeTag ) == 0))
                {
                    k++;
                }

                // swap edge (j,k)
                osgSwap (slice.edgeVec[j],  slice.edgeVec[k]);
                osgSwap (slice.pointVec[j], slice.pointVec[k]);
                swapCount++;
            }
        }

        // TODO; find a better/faster way to check the winding
        // check winding
        v1 =  slice.pointVec[1];
        v1 -= slice.pointVec[0];
        v2 =  slice.pointVec[2];
        v2 -= slice.pointVec[0];
        winding = v1.cross(v2);
    
        slice.ccw = ( fabs (winding.x() + plane.getNormal().x())
                      >= fabs(plane.getNormal().x()) );
    }

    return slice.numOfIntersection;
}

void Slices::drawSlices(Window *win, const Vec3f &planeNormal,
                        UInt32 & triCount, UInt32 & vertexCount)
{
    bool has_multitexture = win->hasExtension(_arbMultitexture);

    PFNGLMULTITEXCOORD3FARBPROC multiTexCoord3f = NULL;
    if(has_multitexture)
        multiTexCoord3f = (PFNGLMULTITEXCOORD3FARBPROC)
                          win->getFunction(_funcMultiTexCoord3fARB);

    Real32 hsx = getSize().x()/2, hsy = getSize().y()/2, hsz = getSize().z()/2;
    Real32 ssx = 1/getSize().x(), ssy = 1/getSize().y(), ssz = 1/getSize().z();
    Slice slice;
    Plane plane;
    Real32 distance, sliceDistance, volumeDiagonal = getSize().length();
    Int32 i, si, numOfSlices;
    Vec3f texPos0, texPos1, texPos2, texOff, texSliceNormal;
    
    if(_edgeVec.empty())
        initEdgeVec();
    
    sliceDistance = getSliceDistance();
    numOfSlices = int (volumeDiagonal / sliceDistance) + 1;
    distance = - volumeDiagonal / 2;
    texOff = planeNormal;
    texOff.normalize();
    texOff *= sliceDistance * 0.5;
    
    texSliceNormal.setValues(planeNormal.x() * sliceDistance * ssx,
                             planeNormal.y() * sliceDistance * ssy,
                             planeNormal.z() * sliceDistance * ssz );
    
    triCount = 0;
    vertexCount = 0;
    
    if (numOfSlices) 
    {
        glNormal3fv ( planeNormal.getValues() );
    
        for(si = 0; si < numOfSlices; si++) 
        {
            plane.set   ( planeNormal, distance += sliceDistance );
    
            if(createSlice(plane,slice) > 2) 
            {
                triCount    += slice.numOfIntersection - 2;
                vertexCount += slice.numOfIntersection;
        
                ::glBegin(GL_POLYGON);
                if(slice.ccw)
                {
                    for(i = 0; i < slice.numOfIntersection; i++) 
                    {
                        texPos0 = texPos1 = texPos2 = slice.pointVec[i];
                        texPos1 += texOff;
                        texPos2 -= texOff;

                        texSliceNormal = texPos1;
                        texSliceNormal -= texPos2;
              
                        glTexCoord3f((hsx + texPos0.x()) * ssx,
                                    (hsy + texPos0.y()) * ssy,
                                    (hsz + texPos0.z()) * ssz );

                        if(has_multitexture)
                        {
                            multiTexCoord3f(GL_TEXTURE1_ARB,
                                            (hsx + texPos1.x()) * ssx,
                                            (hsy + texPos1.y()) * ssy,
                                            (hsz + texPos1.z()) * ssz );
    
                            multiTexCoord3f(GL_TEXTURE2_ARB,
                                            (hsx + texPos2.x()) * ssx,
                                            (hsy + texPos2.y()) * ssy,
                                            (hsz + texPos2.z()) * ssz );
                        }
                        glVertex3fv  ( slice.pointVec[i].getValues() );
                    }
                }
                else
                {
                    for(i = slice.numOfIntersection - 1; i >= 0; i--) 
                    {
                        texPos0 = texPos1 = texPos2 = slice.pointVec[i];
                        texPos1 += texOff;
                        texPos2 -= texOff;
                            
                        glTexCoord3f ((hsx + texPos0.x()) * ssx,
                                      (hsy + texPos0.y()) * ssy,
                                      (hsz + texPos0.z()) * ssz );

                        if(has_multitexture)
                        {
                            multiTexCoord3f(GL_TEXTURE1_ARB,
                                            (hsx + texPos1.x()) * ssx,
                                            (hsy + texPos1.y()) * ssy,
                                            (hsz + texPos1.z()) * ssz );
    
                            multiTexCoord3f(GL_TEXTURE2_ARB,
                                            (hsx + texPos2.x()) * ssx,
                                            (hsy + texPos2.y()) * ssy,
                                            (hsz + texPos2.z()) * ssz );
                        }
                        glVertex3fv  ( slice.pointVec[i].getValues() );
                    }
                }
                ::glEnd();
            }
        } 
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.12 2002/04/30 09:29:13 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGSLICESBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSLICESBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSLICESFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


