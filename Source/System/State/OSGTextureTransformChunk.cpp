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

#include <OSGGL.h>

#include "OSGTextureTransformChunk.h"
#include <OSGWindow.h>
#include <OSGDrawActionBase.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGTextureChunk.h>
#include <OSGTexGenChunk.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureTransformChunk
    \ingroup GrpSystemState

See \ref PageSystemTextureTransformChunk for a description.

This chunk wraps glLoadMatrix() for the GL_TEXTURE matrix mode. It is derived
from the osg::TransformChunk and uses its matrix.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TextureTransformChunk::_class("TextureTransform",
                                              osgMaxTexCoords);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureTransformChunk::initMethod (void)
{
    addInitFunction(&TextureTransformChunk::checkTexChunkOrder);
}

bool TextureTransformChunk::checkTexChunkOrder(void)
{
    FINFO(("Check order %d %d\n",
           TextureTransformChunk::getStaticClassId(),
           TextureChunk         ::getStaticClassId()));

    if(TextureTransformChunk::getStaticClassId() < 
       TextureChunk         ::getStaticClassId()  )
    {
  
        _class.swap(
            *(const_cast<StateChunkClass *>(TextureChunk::getStaticClass())));
    }

    return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

TextureTransformChunk::TextureTransformChunk(void) :
    Inherited()
{
}

TextureTransformChunk::TextureTransformChunk(const TextureTransformChunk &source) :
    Inherited(source)
{
}

TextureTransformChunk::~TextureTransformChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TextureTransformChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void TextureTransformChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void TextureTransformChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextureTransformChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void TextureTransformChunk::activate ( DrawActionBase * action, UInt32 idx )
{
    Window *win = action->getWindow();
    
    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureTransformChunk::deactivate: Trying to bind texcoord unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }

    TextureChunk::activateTexture(win, idx);
  
    glMatrixMode(GL_TEXTURE);
    //glPushMatrix();
    
    if(getUseCameraBeacon())
    {
        if(action->getCamera() != NULL && action->getViewport() != NULL)
        {
            Matrix m;
            action->getCamera()->getViewing(m,
                                        action->getViewport()->getPixelWidth(),
                                        action->getViewport()->getPixelHeight());
            m.invert();
            m[3].setValues(0, 0, 0, 1);
            
            glMultMatrixf(m.getValues());
            //glLoadMatrixf(m.getValues());
        }
    }
    else
    {
        glMultMatrixf(getMatrix().getValues());
        //glLoadMatrixf(getMatrix().getValues());
    }
    glMatrixMode(GL_MODELVIEW);
}

void TextureTransformChunk::changeFrom( DrawActionBase * action, StateChunk * old, UInt32 idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

    Window *win = action->getWindow();
    
    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureTransformChunk::deactivate: Trying to bind texcoord unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }

    TextureChunk::activateTexture(win, idx);

    glMatrixMode(GL_TEXTURE);
    //glPopMatrix();
    //glPushMatrix();
    
    if(getUseCameraBeacon())
    {
        if(action->getCamera() != NULL && action->getViewport() != NULL)
        {
            Matrix m;
            action->getCamera()->getViewing(m,
                                        action->getViewport()->getPixelWidth(),
                                        action->getViewport()->getPixelHeight());
            m.invert();
            m[3].setValues(0, 0, 0, 1);
            
            glMultMatrixf(m.getValues());
            //glLoadMatrixf(m.getValues());
        }
    }
    else
    {
        glMultMatrixf(getMatrix().getValues());
        //glLoadMatrixf(getMatrix().getValues());
    }
    glMatrixMode(GL_MODELVIEW);
}

void TextureTransformChunk::deactivate ( DrawActionBase * action, UInt32 idx )
{
    Window *win = action->getWindow();   

    Real32 ntexcoords;
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);
        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(ntexcoords))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureTransformChunk::deactivate: Trying to bind texcoord unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, ntexcoords));
#endif
        return;        
    }

    TextureChunk::activateTexture(win, idx);

    glMatrixMode(GL_TEXTURE);
    //glPopMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 TextureTransformChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureTransformChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

bool TextureTransformChunk::operator ==(const StateChunk &other) const
{
    TextureTransformChunk const *tother = 
                dynamic_cast<TextureTransformChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getMatrix() != tother->getMatrix())
        return false;

    return true;
}

bool TextureTransformChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGTEXTURETRANSFORMCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGTEXTURETRANSFORMCHUNK_INLINE_CVSID;
}
