/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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
#include <OSGViewport.h>
#include <OSGTextureChunk.h>

#include <OSGImage.h>

#include "OSGTextureBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureBackground

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureBackground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureBackground::TextureBackground(void) :
    Inherited()
{
}

TextureBackground::TextureBackground(const TextureBackground &source) :
    Inherited(source)
{
}

TextureBackground::~TextureBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureBackground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TextureBackground::clear(DrawActionBase *action, Viewport *OSG_CHECK_ARG(viewport))
{
    TextureChunkPtr tex = getTexture();
    
    if(tex == NullFC)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return;
    }

    GLboolean light = glIsEnabled(GL_LIGHTING);
    if (light == GL_TRUE)  
        glDisable(GL_LIGHTING);

    GLint fill[2];
    glGetIntegerv(GL_POLYGON_MODE, fill);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClear(GL_DEPTH_BUFFER_BIT);

    GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    GLint depthFunc;
    glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);
    glDepthFunc(GL_ALWAYS);

    glDepthMask(GL_FALSE);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    tex->activate(action);

    if(tex->isTransparent())
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }
    
    if(getTexCoords().getSize() < 4)
    {
        // set some default texture coordinates.
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
            glTexCoord2f(getTexCoords()[0].getValues()[0],
                         getTexCoords()[0].getValues()[1]);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glTexCoord2f(getTexCoords()[3].getValues()[0],
                         getTexCoords()[3].getValues()[1]);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glTexCoord2f(getTexCoords()[2].getValues()[0],
                         getTexCoords()[2].getValues()[1]);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glTexCoord2f(getTexCoords()[1].getValues()[0],
                         getTexCoords()[1].getValues()[1]);
            glVertex3f(0.0f, 1.0f, 0.0f);
        glEnd();
    }
    
    if(tex->isTransparent())
    {
        glDisable(GL_BLEND);
    }
    
    tex->deactivate(action);

    glClear(GL_DEPTH_BUFFER_BIT);
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glDepthMask(GL_TRUE);
    if(depth)    
        glEnable(GL_DEPTH_TEST);
    glDepthFunc(depthFunc);

    glPolygonMode(GL_FRONT, fill[0]);
    glPolygonMode(GL_BACK , fill[1]);
    if(light)  
        glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void TextureBackground::dump(UInt32,
                             const BitVector ) const
{
    SLOG << "Dump TextureBackground NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGTextureBackground.cpp,v 1.3 2004/02/03 15:31:08 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGTEXTUREBACKGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTUREBACKGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTUREBACKGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
