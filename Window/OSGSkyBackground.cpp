/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OSGConfig.h>

#include <OSGDrawActionBase.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGTextureChunk.h>

#include "OSGSkyBackground.h"

#include <GL/gl.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSkyBackground.cpp,v 1.5 2002/01/21 01:51:00 dirk Exp $";
    static char cvsid_hpp[] = OSGSKYBACKGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSKYBACKGROUND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::SkyBackground
A sky/ground and skybox background, inspired by the VRML Background node. See http://www.vrml.org/technicalinfo/specifications/vrml97/part1/nodesRef.html#Background for details on the parameter restrictions.
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

SkyBackground::SkyBackground(void) :
    Inherited()
{
}

//! Copy Constructor

SkyBackground::SkyBackground(const SkyBackground &source) :
    Inherited(source)
{
}

//! Destructor

SkyBackground::~SkyBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void SkyBackground::initMethod (void)
{
}

//! react to field changes

void SkyBackground::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void SkyBackground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SkyBackground NI" << endl;
}

/*-------------------------- drawing ---------------------------------*/

void SkyBackground::drawFace(DrawActionBase *action, TextureChunkPtr tex, 
                             const Pnt3f &p1, const Pnt3f &p2, 
                             const Pnt3f &p3, const Pnt3f &p4)
{
    
    if(tex != NullFC)
    {
        tex->activate(action);
        
        if(tex->isTransparent())
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        }
        
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3fv( (GLfloat*) p1.getValues() );
        glTexCoord2f(1,0);
        glVertex3fv( (GLfloat*) p2.getValues() );
        glTexCoord2f(1,1);
        glVertex3fv( (GLfloat*) p3.getValues() );
        glTexCoord2f(0,1);
        glVertex3fv( (GLfloat*) p4.getValues() );
        glEnd();
        
        if(tex->isTransparent())
        {
            glDisable(GL_BLEND);
        }
        
        tex->deactivate(action);
    }
   
}

void SkyBackground::clear(DrawActionBase *action, Viewport *viewport)
{
    Matrix m;

    Bool light = glIsEnabled(GL_LIGHTING);
    if (light)  glDisable(GL_LIGHTING);

    GLint fill;
    glGetIntegerv(GL_POLYGON_MODE, &fill);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

    GLint depth;
    glGetIntegerv(GL_DEPTH_FUNC, &depth);
    glDepthFunc(GL_ALWAYS);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    action->getCamera()->getViewing( m, viewport->getPixelWidth(),
                                        viewport->getPixelHeight() );
    m[3][0] = m[3][1] = m[3][2] = 0;
    glLoadMatrixf( m.getValues() );         
    Real32 viewscale = (m[0].length() + m[1].length() + m[2].length()) / 3.f;
    float scale = ( action->getCamera()->getFar() + 
                    action->getCamera()->getNear() ) / 2 / viewscale;
    glScalef( scale, scale, scale );

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    action->getCamera()->getProjection( m, viewport->getPixelWidth(),
                                           viewport->getPixelHeight() );
    glLoadMatrixf( m.getValues() );         
    
    UInt32 i, j;
    UInt32 sr = _sfSphereRes.getValue() + 1;      // sphere resolution
    
    // These should be stored somewhere, not recalced.
    Real32 *cosval = new Real32 [ sr ];
    Real32 *sinval = new Real32 [ sr ];
    
    Real32  vcos1,vsin1,vcos2,vsin2;
    
    Real32 da = 2 * Pi / ( sr - 1 );    
    for(i = 0; i < sr; ++i)
    {
        cosval[i] = osgcos( i * da );
        sinval[i] = osgsin( i * da );     
    }
    
    if(_mfSkyAngle.getSize() > 0)
    {
        vcos1 = osgcos( _mfSkyAngle.getValue(0) );
        vsin1 = osgsin( _mfSkyAngle.getValue(0) );

        glBegin(GL_TRIANGLE_FAN);
        glColor3fv( (GLfloat*) _mfSkyColor.getValue(0).getValuesRGB() );
        glVertex3f(0, 1, 0);
        glColor3fv( (GLfloat*) _mfSkyColor.getValue(1).getValuesRGB() );

        for(i = 0; i < sr; ++i)
        {
            glVertex3f( vsin1 * sinval[i], vcos1, vsin1 * cosval[i] );
        }

        glEnd();


        for(j = 0; j < _mfSkyAngle.getSize() - 1; ++j)
        {
            Color3f c1, c2;

            c1 = _mfSkyColor.getValue(j+1);
            c2 = _mfSkyColor.getValue(j+2);

            vcos1 = osgcos(_mfSkyAngle.getValue(j  ));
            vsin1 = osgsin(_mfSkyAngle.getValue(j  ));
            vcos2 = osgcos(_mfSkyAngle.getValue(j+1));
            vsin2 = osgsin(_mfSkyAngle.getValue(j+1));

            glBegin(GL_TRIANGLE_STRIP);

            for(i = 0; i < sr; ++i)
            {
                glColor3fv( (GLfloat*) c1.getValuesRGB() );
                glVertex3f( vsin1 * sinval[i], vcos1, vsin1 * cosval[i] );
                glColor3fv( (GLfloat*) c2.getValuesRGB() );
                glVertex3f( vsin2 * sinval[i], vcos2, vsin2 * cosval[i] );
            }
            glEnd();
        }

        if(osgabs(_mfSkyAngle.getValue(j)-Pi) > Eps)
        {
            glBegin(GL_TRIANGLE_FAN);
            glColor3fv( (GLfloat*) _mfSkyColor.getValue(j+1).getValuesRGB() );
            glVertex3f(0, -1, 0);
            vcos1 = osgcos( _mfSkyAngle.getValue(j) );
            vsin1 = osgsin( _mfSkyAngle.getValue(j) );

            for(i = 0; i < sr; ++i)
            {
                glVertex3f( vsin1 * sinval[i], vcos1, vsin1 * cosval[i] );
            }

            glEnd();
        }
    }
    else // no angles, just fill single color
    {
        if(_mfSkyColor.size() > 0)
        {
            glClearColor(_mfSkyColor[0][0], _mfSkyColor[0][1], 
                         _mfSkyColor[0][2], 0 );
        }
        else
        {
            glClearColor(0, 0, 0, 0);
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    // Draw the ground.
    // It's possible to be smarter about this, but for now just overdraw.

    if(_mfGroundAngle.getSize() > 0)
    {    
        vcos1 = -osgcos( _mfGroundAngle.getValue(0) );
        vsin1 =  osgsin( _mfGroundAngle.getValue(0) );

        glBegin(GL_TRIANGLE_FAN);
        glColor3fv( (GLfloat*) _mfGroundColor.getValue(0).getValuesRGB() );
        glVertex3f(0, -1, 0);
        glColor3fv( (GLfloat*) _mfGroundColor.getValue(1).getValuesRGB() );

        for(i = 0; i < sr; ++i)
        {
            glVertex3f( vsin1 * sinval[i], vcos1, vsin1 * cosval[i] );
        }

        glEnd();


        for(j = 0; j < _mfGroundAngle.getSize() - 1; ++j)
        {
            Color3f c1, c2;

            c1 = _mfGroundColor.getValue(j+1);
            c2 = _mfGroundColor.getValue(j+2);

            vcos1 = -osgcos(_mfGroundAngle.getValue(j  ));
            vsin1 =  osgsin(_mfGroundAngle.getValue(j  ));
            vcos2 = -osgcos(_mfGroundAngle.getValue(j+1));
            vsin2 =  osgsin(_mfGroundAngle.getValue(j+1));

            glBegin(GL_TRIANGLE_STRIP);

            for(i = 0; i < sr; ++i)
            {
                glColor3fv( (GLfloat*) c1.getValuesRGB() );
                glVertex3f( vsin1 * sinval[i], vcos1, vsin1 * cosval[i] );
                glColor3fv( (GLfloat*) c2.getValuesRGB() );
                glVertex3f( vsin2 * sinval[i], vcos2, vsin2 * cosval[i] );
            }
            glEnd();
        }
    }
    
    // now draw the textures, if set
    
    drawFace(action, getBackTexture(),   Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f(-0.5,  0.5,  0.5),
                                         Pnt3f( 0.5,  0.5,  0.5));
    
    drawFace(action, getFrontTexture(),  Pnt3f(-0.5, -0.5, -0.5),
                                         Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f( 0.5,  0.5, -0.5),
                                         Pnt3f(-0.5,  0.5, -0.5));
    
    drawFace(action, getBottomTexture(), Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f(-0.5, -0.5, -0.5));
    
    drawFace(action, getTopTexture(),    Pnt3f(-0.5,  0.5, -0.5),
                                         Pnt3f( 0.5,  0.5, -0.5),
                                         Pnt3f( 0.5,  0.5,  0.5),
                                         Pnt3f(-0.5,  0.5,  0.5));
    
    drawFace(action, getLeftTexture(),   Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f(-0.5, -0.5, -0.5),
                                         Pnt3f(-0.5,  0.5, -0.5),
                                         Pnt3f(-0.5,  0.5,  0.5));
    
    drawFace(action, getRightTexture(),  Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f( 0.5,  0.5,  0.5),
                                         Pnt3f( 0.5,  0.5, -0.5));
     
    glClear( GL_DEPTH_BUFFER_BIT );

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDepthFunc(depth);
    glPolygonMode( GL_FRONT_AND_BACK, fill);
    if (light)  glEnable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);

    delete [] sinval;
    delete [] cosval;
}

 
