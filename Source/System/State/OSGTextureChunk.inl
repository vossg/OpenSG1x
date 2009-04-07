/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

inline
UInt32 TextureChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
const StateChunkClass *TextureChunk::getStaticClass(void)
{
    return &TextureChunk::_class;
}

/*! Set the image used as texture by this chunk.

    Images should only ever be set by calling this method, because it ensures
    that this TextureChunk is registered as a parent of the image and thus
    can be notified about changes to the image.
 */
inline
void TextureChunk::setImage(const ImagePtr &pImage)
{
    if(_sfImage.getValue() != NullFC)
    {
        TextureChunkPtr thisPtr(*this);
    
        _sfImage.getValue()->subParent(thisPtr);
    }

     addRefCP(pImage);
     subRefCP(_sfImage.getValue());

    _sfImage.setValue(pImage);
    
    if(_sfImage.getValue() != NullFC)
    {
        TextureChunkPtr thisPtr(*this);
        
        _sfImage.getValue()->addParent(thisPtr);
    }
}

/*! Utility function to be called when a region of the image changed.
    Calling this function can improve the performance of applications that
    only modify small regions of a large texture, by defining the a dirty
    area. On the next refresh of the texture only the dirty area will be
    updated instead of the whole texture.

    \warning Successive calls to this function will overwrite the previously
    set dirty area. If an application makes changes to multiple regions
    they have to accumulated by the user before calling this function.
*/
inline 
void TextureChunk::imageContentChanged( Int32 minx, Int32 maxx, 
                                        Int32 miny, Int32 maxy,
                                        Int32 minz, Int32 maxz)
{
    TextureChunkPtr tc(*this);
    
    beginEditCP(tc, DirtyMinXFieldMask | DirtyMaxXFieldMask |
                    DirtyMinYFieldMask | DirtyMaxYFieldMask |
                    DirtyMinZFieldMask | DirtyMaxZFieldMask);
    
    tc->setDirtyMinX(minx);
    tc->setDirtyMaxX(maxx);
    tc->setDirtyMinY(miny);
    tc->setDirtyMaxY(maxy);
    tc->setDirtyMinZ(minz);
    tc->setDirtyMaxZ(maxz);
    
    endEditCP(  tc, DirtyMinXFieldMask | DirtyMaxXFieldMask |
                    DirtyMinYFieldMask | DirtyMaxYFieldMask |
                    DirtyMinZFieldMask | DirtyMaxZFieldMask);
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
        reinterpret_cast<void (OSG_APIENTRY*)(GLenum target)>(
            win->getFunction(_funcActiveTexture));

    ActiveTexture(GL_TEXTURE0_ARB + texture);
}

//! call glActiveTexture via the extension mechanism, if MultiTextures
//! are supported. Return false if successful, true if not.
inline 
bool TextureChunk::activateTexture(Window *win, UInt16 texture)
{
    if(hasMultiTexture(win))
    {
        activeTexture(win, texture);
    }
#ifdef OSG_DEBUG
    else
    {
        if(texture != 0)
        {
            FWARNING(("TextureChunk::activateTexture: trying to activate "
                "texture %d, but Window %p doesn't support multi-textures!\n",
                texture, win));
            return true;
        }
    }
#endif
    return false;
}

inline
void TextureChunk::setShaderOffsetMatrix(Real32 m11, Real32 m12, 
                                         Real32 m21, Real32 m22)
{
    editMFShaderOffsetMatrix()->resize(4);

    (*editMFShaderOffsetMatrix())[0] = m11;
    (*editMFShaderOffsetMatrix())[1] = m12;
    (*editMFShaderOffsetMatrix())[2] = m21;
    (*editMFShaderOffsetMatrix())[3] = m22;
}

inline void
TextureChunk::triggerRefresh(void)
{
    if(Int32(Thread::getAspect()) != _sfIgnoreGLForAspect.getValue())
    {
        Window::refreshGLObject(getGLId());
    }
}

inline void
TextureChunk::triggerReInit(void)
{
    if(Int32(Thread::getAspect()) != _sfIgnoreGLForAspect.getValue())
    {
        Window::reinitializeGLObject(getGLId());
    }
}

OSG_END_NAMESPACE

#define OSGTEXTURECHUNK_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.7 2001/09/17 14:15:07 vossg Exp $"

