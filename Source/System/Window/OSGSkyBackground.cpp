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

#include <OSGConfig.h>

#include <OSGDrawActionBase.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>
#include <OSGRemoteAspect.h>

#include "OSGSkyBackground.h"

#include <OSGGL.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SkyBackground
    \ingroup GrpSystemWindowBackgrounds

A Sky/Ground/Skybox background, inspired by VRML, see \ref
PageSystemWindowBackgroundSky for a description.

The sky is defined by the _mfSkyAngle and _mfSkyColor fields, the ground by the
_mfGroundAngle and _mfGround Color fields. The resolution of the sky sphere can
be influenced by the _sfSphereRes field. The sky box is defined by the
_sfBackTexture, _sfFrontTexture, _sfLeftTexture, _sfRightTexture, _sfTopTexture
and _sfBottomTexture fields.

*/

/*----------------------- constructors & destructors ----------------------*/

SkyBackground::SkyBackground(void) :
    Inherited()
{
}

SkyBackground::SkyBackground(const SkyBackground &source) :
    Inherited(source)
{
}

SkyBackground::~SkyBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkyBackground::initMethod (void)
{
}

void SkyBackground::onCreate(const SkyBackground *source)
{
    Inherited::onCreate(source);

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(SkyBackground::getClassType().getId(),
                                 SkyBackground::GLIdFieldMask);
}

void SkyBackground::onDestroy(void)
{
    Inherited::onDestroy();

    if(getGLId() != 0)
    {
        Window::destroyGLObject(getGLId(), 1);
        setGLId(0);
    }
}

/*! OpenGL object handler. Used for DisplayList caching.
*/
void SkyBackground::handleGL(Window* win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    UInt32 glid = 0;

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
                // create a display list.
                glid = glGenLists(1);
                win->setGLObjectId(id, glid);
        }

        glid = win->getGLObjectId(id);

        glNewList(glid, GL_COMPILE);
        drawSpheres();
        glEndList();

        if(glGetError() == GL_OUT_OF_MEMORY)
        {
            SFATAL << "SkyBackground::handleGL: couldn't create display list (out of memory) skipping background "
                   << this
                   << std::endl;

                // destroy old list.
                glDeleteLists(glid, 1);
                win->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::destroy)
    {
        glid = win->getGLObjectId(id);
        if(glid != 0)
        {
            glDeleteLists(glid, 1);
            // reset the display list id.
            win->setGLObjectId(id, 0);
        }
    }
}

static inline void interpolateColor(const Color4f &startColor, const Color4f &endColor, Real32 t, Color4f &result)
{
    Real32 t_inv = 1.f - t;
    result[0] = startColor[0] * t_inv + endColor[0] * t;
    result[1] = startColor[1] * t_inv + endColor[1] * t;
    result[2] = startColor[2] * t_inv + endColor[2] * t;
    result[3] = startColor[3] * t_inv + endColor[3] * t;
}

void SkyBackground::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & SphereResFieldMask)
    {
        UInt32 sr = _sfSphereRes.getValue() + 1;
        if (_hcos.size() != sr)
        {
            Real32 da = 2 * Pi / (sr - 1);
            _hcos.resize(sr);
            _hsin.resize(sr);
            for(UInt32 i = 0; i < sr; ++i)
            {
                _hcos[i] = -osgcos(i * da);
                _hsin[i] = osgsin(i * da);
            }
        }
    }

    if(whichField & (SphereResFieldMask | SkyAngleFieldMask | SkyColorFieldMask))
    {
        _sky_vcos.clear();
        _sky_vsin.clear();
        _skyColor.clear();
        Real32 optAngle = 2.f * Pi / _sfSphereRes.getValue();
        Color4f color, startColor, endColor = _mfSkyColor.empty() ? Color4f(0.f, 0.f, 0.f, 1.f) : _mfSkyColor[0];
        Real32 angle = 0.f, startAngle = 0.f, endAngle = 0.f, deltaAngle = 0.f;
        UInt32 angleIndex = 0, steps = 0, stepIndex = 0;
        _sky_vcos.push_back(1.f);
        _sky_vsin.push_back(0.f);
        _skyColor.push_back(endColor);
        while (true)
        {
            if (stepIndex >= steps)
            {
                angle = startAngle = endAngle;
                endAngle = angleIndex >= _mfSkyAngle.size() ? Pi : _mfSkyAngle[angleIndex];
                if (osgabs(endAngle - Pi) < Eps)
                    endAngle = Pi;
                ++angleIndex;
                startColor = endColor;
                if (angleIndex < _mfSkyColor.size())
                    endColor = _mfSkyColor[angleIndex];
                if (endAngle > Pi)
                {
                    interpolateColor(startColor, endColor, Pi / endAngle, endColor);
                    endAngle = Pi;
                }
                deltaAngle = endAngle - startAngle;
                steps = osgMax(Int32(osgfloor(deltaAngle / optAngle + 0.5f)), Int32(1));
                deltaAngle /= steps;
                stepIndex = 0;
            }
            ++stepIndex;
            if (stepIndex >= steps)
            {
                angle = endAngle;
                color = endColor;
            }
            else
            {
                angle += deltaAngle;
                interpolateColor(startColor, endColor, Real32(stepIndex) / steps, color);
            }
            if (osgabs(angle - Pi) < Eps)
                break;
            _sky_vcos.push_back(osgcos(angle));
            _sky_vsin.push_back(osgsin(angle));
            _skyColor.push_back(color);
        }
        _sky_vcos.push_back(-1.f);
        _sky_vsin.push_back(0.f);
        _skyColor.push_back(endColor);
    }

    if(whichField & (SphereResFieldMask | GroundAngleFieldMask | GroundColorFieldMask))
    {
        _ground_vcos.clear();
        _ground_vsin.clear();
        _groundColor.clear();
        if((_mfGroundAngle.empty() == false) && (_mfGroundColor.size() >= 2))
        {
            Real32 optAngle = 2.f * Pi / _sfSphereRes.getValue();
            Color4f color, startColor, endColor = _mfGroundColor[0];
            Real32 angle = 0.f, startAngle = 0.f, endAngle = 0.f, deltaAngle = 0.f;
            UInt32 angleIndex = 0, steps = 0, stepIndex = 0;
            _ground_vcos.push_back(-1.f);
            _ground_vsin.push_back(0.f);
            _groundColor.push_back(endColor);
            while (true)
            {
                if (stepIndex >= steps)
                {
                    angle = startAngle = endAngle;
                    if (angleIndex >= _mfGroundAngle.size())
                        break;
                    endAngle = _mfGroundAngle[angleIndex];
                    ++angleIndex;
                    startColor = endColor;
                    if (angleIndex >= _mfGroundColor.size())
                        break;
                    endColor = _mfGroundColor[angleIndex];
                    if (endAngle > Pi / 2.f)
                    {
                        interpolateColor(startColor, endColor, Pi / 2.f / endAngle, endColor);
                        endAngle = Pi / 2.f;
                    }
                    deltaAngle = endAngle - startAngle;
                    steps = osgMax(UInt32(osgfloor(deltaAngle / optAngle + 0.5f)), UInt32(1));
                    deltaAngle /= steps;
                    stepIndex = 0;
                }
                ++stepIndex;
                if (stepIndex >= steps)
                {
                    angle = endAngle;
                    color = endColor;
                }
                else
                {
                    angle += deltaAngle;
                    interpolateColor(startColor, endColor, Real32(stepIndex) / steps, color);
                }
                _ground_vcos.push_back(-osgcos(angle));
                _ground_vsin.push_back(osgsin(angle));
                _groundColor.push_back(color);
                if (osgabs(angle - Pi / 2.f) < Eps)
                    break;
            }
        }
    }

    if(getDlistCache() == true)
    {
        bool refresh = whichField & (SphereResFieldMask |
                                     SkyAngleFieldMask | SkyColorFieldMask |
                                     GroundAngleFieldMask | GroundColorFieldMask);
        if(getGLId() == 0)
        {
            SkyBackgroundPtr tmpPtr(*this);
            beginEditCP(tmpPtr, SkyBackground::GLIdFieldMask);
            setGLId(
                    Window::registerGLObject(
                    osgTypedMethodVoidFunctor2ObjCPtrPtr<
                            SkyBackgroundPtr,
                            Window ,
                            UInt32>(tmpPtr,
                                    &SkyBackground::handleGL),
                    1));
            endEditCP(tmpPtr, SkyBackground::GLIdFieldMask);
            refresh = true;
        }
        if (refresh == true)
            Window::refreshGLObject(getGLId());
    }
    else
    {
        if(getGLId() != 0)
        {
            Window::destroyGLObject(getGLId(), 1);
            setGLId(0);
        }
    }

    Inherited::changed(whichField, origin);
}

void SkyBackground::dump(     UInt32    ,
                         const BitVector) const
{
    SLOG << "Dump SkyBackground NI" << std::endl;
}

/*-------------------------- drawing ---------------------------------*/

void SkyBackground::drawFace(      DrawActionBase  * action,
                             const TextureChunkPtr  &tex,
                                   StateChunk      *&oldtex,
                             const Pnt3f            &p1,
                             const Pnt3f            &p2,
                             const Pnt3f            &p3,
                             const Pnt3f            &p4,
                             const Vec3f           * texCoord)
{
    if(tex != NullFC)
    {
        if(oldtex != NULL)
        {
            tex->changeFrom(action, oldtex);
        }
        else
        {
            tex->activate(action);
        }

        glBegin(GL_QUADS);
        glTexCoord3fv(static_cast<const GLfloat*>(texCoord[0].getValues()));
        glVertex3fv  (static_cast<const GLfloat*>(p1.getValues()));
        glTexCoord3fv(static_cast<const GLfloat*>(texCoord[1].getValues()));
        glVertex3fv  (static_cast<const GLfloat*>(p2.getValues()));
        glTexCoord3fv(static_cast<const GLfloat*>(texCoord[2].getValues()));
        glVertex3fv  (static_cast<const GLfloat*>(p3.getValues()));
        glTexCoord3fv(static_cast<const GLfloat*>(texCoord[3].getValues()));
        glVertex3fv  (static_cast<const GLfloat*>(p4.getValues()));
        glEnd();

        oldtex = getCPtr(tex);
    }
}

static inline const Vec3f *tfac(const TextureChunkPtr &t, UInt32 c)
{
    static Vec3f defaulttc[7][4] = {
        // 2D default TCs
        { Vec3f(0,0,0), Vec3f(1,0,0), Vec3f(1,1,0), Vec3f(0,1,0) },

        // Cubetex Default TCs
        { Vec3f(-1, 1,-1), Vec3f( 1, 1,-1), Vec3f( 1,-1,-1), Vec3f(-1,-1,-1) },
        { Vec3f( 1, 1, 1), Vec3f(-1, 1, 1), Vec3f(-1,-1, 1), Vec3f( 1,-1, 1) },
        { Vec3f( 1, 1,-1), Vec3f(-1, 1,-1), Vec3f(-1, 1, 1), Vec3f( 1, 1, 1) },
        { Vec3f( 1,-1, 1), Vec3f(-1,-1, 1), Vec3f(-1,-1,-1), Vec3f( 1,-1,-1) },
        { Vec3f( 1, 1,-1), Vec3f( 1, 1, 1), Vec3f( 1,-1, 1), Vec3f( 1,-1,-1) },
        { Vec3f(-1, 1, 1), Vec3f(-1, 1,-1), Vec3f(-1,-1,-1), Vec3f(-1,-1, 1) },
    };

    return defaulttc[c * ((t != NullFC) && (t->getImage() != NullFC) &&
                          (t->getImage()->getSideCount() == 6))];
}

void SkyBackground::drawBox(DrawActionBase *action)
{
    // now draw the textures, if set
    StateChunk *tchunk = NULL;

    drawFace(action, getBackTexture(),   tchunk,
                                         Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f(-0.5,  0.5,  0.5),
                                         Pnt3f( 0.5,  0.5,  0.5),
                                         getMFBackTexCoord()->size() ?
                                        &getBackTexCoord(0):
                                          tfac(getBackTexture(), 1));

    drawFace(action, getFrontTexture(),  tchunk,
                                         Pnt3f(-0.5, -0.5, -0.5),
                                         Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f( 0.5,  0.5, -0.5),
                                         Pnt3f(-0.5,  0.5, -0.5),
                                         getMFFrontTexCoord()->size() ?
                                         &getFrontTexCoord(0):
                                          tfac(getFrontTexture(), 2));

    drawFace(action, getBottomTexture(), tchunk,
                                         Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f(-0.5, -0.5, -0.5),
                                         getMFBottomTexCoord()->size() ?
                                         &getBottomTexCoord(0):
                                          tfac(getBottomTexture(), 3));

    drawFace(action, getTopTexture(),    tchunk,
                                         Pnt3f(-0.5,  0.5, -0.5),
                                         Pnt3f( 0.5,  0.5, -0.5),
                                         Pnt3f( 0.5,  0.5,  0.5),
                                         Pnt3f(-0.5,  0.5,  0.5),
                                         getMFTopTexCoord()->size() ?
                                         &getTopTexCoord(0):
                                          tfac(getTopTexture(), 4));

    drawFace(action, getLeftTexture(),   tchunk,
                                         Pnt3f(-0.5, -0.5,  0.5),
                                         Pnt3f(-0.5, -0.5, -0.5),
                                         Pnt3f(-0.5,  0.5, -0.5),
                                         Pnt3f(-0.5,  0.5,  0.5),
                                         getMFLeftTexCoord()->size() ?
                                         &getLeftTexCoord(0):
                                          tfac(getLeftTexture(), 5));

    drawFace(action, getRightTexture(),  tchunk,
                                         Pnt3f( 0.5, -0.5, -0.5),
                                         Pnt3f( 0.5, -0.5,  0.5),
                                         Pnt3f( 0.5,  0.5,  0.5),
                                         Pnt3f( 0.5,  0.5, -0.5),
                                         getMFRightTexCoord()->size() ?
                                         &getRightTexCoord(0):
                                          tfac(getRightTexture(), 6));

    if(tchunk != NULL)
        tchunk->deactivate(action);
}

void SkyBackground::drawSpheres()
{
    // Draw the top cap of the sky sphere
    glBegin(GL_TRIANGLE_FAN);
    glColor4fv(static_cast<const GLfloat*>(_skyColor.front().getValuesRGBA()));
    glVertex3f(0, 1, 0);
    const GLfloat *color = static_cast<const GLfloat*>(_skyColor[1].getValuesRGBA());
    glColor4fv(color);
    Real32 vsin = _sky_vsin[1];
    Real32 vcos = _sky_vcos[1];
    UInt32 sr = _sfSphereRes.getValue() + 1;
    for(UInt32 i = 0; i < sr; ++i)
        glVertex3f(vsin * _hsin[i], vcos, vsin * _hcos[i]);
    glEnd();

    // Draw the strips of the sky sphere
    UInt32 len = _skyColor.size() - 1;
    for (UInt32 j = 2; j < len; ++j)
    {
        glBegin(GL_QUAD_STRIP);
        Real32 prev_vsin = vsin;
        Real32 prev_vcos = vcos;
        vsin = _sky_vsin[j];
        vcos = _sky_vcos[j];
        const GLfloat *prevColor = color;
        color = static_cast<const GLfloat*>(_skyColor[j].getValuesRGBA());
        for (UInt32 i = 0; i < sr; ++i)
        {
            glColor4fv(prevColor);
            glVertex3f(prev_vsin * _hsin[i], prev_vcos, prev_vsin * _hcos[i]);
            glColor4fv(color);
            glVertex3f(vsin * _hsin[i], vcos, vsin * _hcos[i]);
        }
        glEnd();
    }

    // Draw the bottom cap of the sky sphere
    glBegin(GL_TRIANGLE_FAN);
    glColor4fv(static_cast<const GLfloat*>(_skyColor.back().getValuesRGBA()));
    glVertex3f(0, -1, 0);
    glColor4fv(color);
    for(UInt32 i = 0; i < sr; ++i)
        glVertex3f(-vsin * _hsin[i], vcos, vsin * _hcos[i]);
    glEnd();

    if(_groundColor.empty() == false)
    {
        // Draw the bottom cap of the ground sphere
        glBegin(GL_TRIANGLE_FAN);
        glColor4fv(static_cast<const GLfloat*>(_groundColor.front().getValuesRGBA()));
        glVertex3f(0, -1, 0);
        color = static_cast<const GLfloat*>(_groundColor[1].getValuesRGBA());
        glColor4fv(color);
        vsin = _ground_vsin[1];
        vcos = _ground_vcos[1];
        for(UInt32 i = 0; i < sr; ++i)
            glVertex3f(-vsin * _hsin[i], vcos, vsin * _hcos[i]);
        glEnd();

        // Draw the strips of the ground sphere
        len = _groundColor.size();
        for (UInt32 j = 2; j < len; ++j)
        {
            glBegin(GL_QUAD_STRIP);
            Real32 prev_vsin = vsin;
            Real32 prev_vcos = vcos;
            vsin = _ground_vsin[j];
            vcos = _ground_vcos[j];
            const GLfloat *prevColor = color;
            color = static_cast<const GLfloat*>(_groundColor[j].getValuesRGBA());
            for (UInt32 i = 0; i < sr; ++i)
            {
                glColor4fv(prevColor);
                glVertex3f(prev_vsin * _hsin[i], prev_vcos, prev_vsin * _hcos[i]);
                glColor4fv(color);
                glVertex3f(vsin * _hsin[i], vcos, vsin * _hcos[i]);
            }
            glEnd();
        }
    }
}

void SkyBackground::clear(DrawActionBase *action, Viewport *viewport)
{
    // Save old modelview matrix and calculate new one
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Matrix m,t;
    action->getCamera()->getViewing(m, viewport->getPixelWidth(),
                                       viewport->getPixelHeight());
    action->getCamera()->getProjectionTranslation(t,
                                        viewport->getPixelWidth(),
                                        viewport->getPixelHeight());
    m.multLeft(t);
    // Use beacon to rotate the background
    if (getBeacon() != NullFC)
    {
        getBeacon()->getToWorld(t);
        m.mult(t);
    }
    // Remove the translation from the modelview matrix
    m[3][0] = m[3][1] = m[3][2] = 0;
    glLoadMatrixf(m.getValues());

    // Save old projection matrix and calculate new one
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Squeeze all geometry onto the z=0.5 plane to make sure it
    // is inside the near and the far clipping planes
    glTranslatef(0.f, 0.f, 0.5);
    glScalef(1.f, 1.f, 0.f);
    action->getCamera()->getProjection( m,
                                        viewport->getPixelWidth(),
                                        viewport->getPixelHeight());
    glMultMatrixf(m.getValues());

    // Save old state
    glPushAttrib(GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_LIGHTING_BIT | GL_FOG_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Set new state
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Clear buffers
    glClearDepth(1.f);
    Int32 bit = getClearStencilBit();
    if (bit >= 0)
    {
        glClearStencil(bit);
        glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    else
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    // Draw the textured sky box outside
    bool boxInside = getBoxInside();
    if (boxInside == false)
        drawBox(action);

    // Draw the sky and the ground spheres
    if(getDlistCache() == true)
    {
        action->getWindow()->validateGLObject(getGLId());
        UInt32 glid = action->getWindow()->getGLObjectId(getGLId());
        if(glid != 0)
            glCallList(glid);
        else
            drawSpheres();
    }
    else
    {
        drawSpheres();
    }

    // Draw the textured sky box inside
    if (boxInside == true)
        drawBox(action);

    // Undo state changes
    glPopAttrib();

    // Undo changes to the projection and modelview matrices
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

 
/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGSKYBACKGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGSKYBACKGROUND_INLINE_CVSID;
}
