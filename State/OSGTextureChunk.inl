/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

#ifndef GL_TEXTURE0_ARB
#define GL_TEXTURE0_ARB 0x84C0
#endif

inline
const StateChunkClass *TextureChunk::getClass( void ) const
{
    return &_class;
}

inline
void TextureChunk::setImage(ImageP &pImage)
{
     addRefP(pImage);

     subRefP(_sfImage.getValue());

    _sfImage.setValue(pImage);
}


inline 
void TextureChunk::imageContentChanged( void )
{
    Window::refreshGLObject(getGLId());
}


inline 
bool TextureChunk::hasMultiTexture(Window *win)
{
    return win->hasExtension(_arbMultiTex);
}

//! call glActiveTexture via the extension mechanism
inline 
void TextureChunk::activeTexture(Window *win, UInt16 texture)
{
    void (OSG_APIENTRY *ActiveTexture)(GLenum target) = 
        (void (OSG_APIENTRY*)(GLenum target))
            win->getFunction(_funcActiveTexture);

    ActiveTexture(GL_TEXTURE0_ARB + texture);
}

//! call glActiveTexture via the extension mechanism, if MultiTextures
//! are supported
inline 
void TextureChunk::activateTexture(Window *win, UInt16 texture)
{
    if(hasMultiTexture(win))
        activeTexture(win, texture);
}

OSG_END_NAMESPACE

