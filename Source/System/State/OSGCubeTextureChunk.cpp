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

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>

#include "OSGDrawActionBase.h"

#include "OSGCubeTextureChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::CubeTextureChunk
    \ingroup StateChunks

CubeTexture Chunk. Similar to TextureChunk, but has 5 more textures. The
TextureChunk's texture is the negative z texture, the others are named
accordingly. Note that all textures have to be square and have to have the
same resolution.

*/

// this should go somewhere central...

#ifdef OSG_DEBUG
#define glErr(text)                           \
{                                   \
        GLenum glerr;                           \
        glerr=glGetError();                     \
        if(glerr!=GL_NO_ERROR)                     \
        {                               \
                fprintf(stderr, "%s failed: %s (%#x)\n", (text),    \
                                        gluErrorString(glerr), glerr);  \
        }                               \
}
#else
#define glErr(text)
#endif

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

CubeTextureChunk::CubeTextureChunk(void) :
    Inherited()
{
}

//! Copy Constructor

CubeTextureChunk::CubeTextureChunk(const CubeTextureChunk &source) :
    Inherited(source)
{
}

//! Destructor

CubeTextureChunk::~CubeTextureChunk(void)
{
    subRefP(_sfPosZImage.getValue());
    subRefP(_sfPosXImage.getValue());
    subRefP(_sfNegXImage.getValue());
    subRefP(_sfPosYImage.getValue());
    subRefP(_sfNegYImage.getValue());
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void CubeTextureChunk::initMethod (void)
{
}

/*----------------------------- onCreate --------------------------------*/

/** \brief instance initialization
 */

void CubeTextureChunk::onCreate(const CubeTextureChunk *)
{
    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    CubeTextureChunkPtr tmpPtr(*this);

    beginEditCP(tmpPtr, CubeTextureChunk::GLIdFieldMask);

    setGLId(
        Window::registerGLObject(
            osgTypedMethodVoidFunctor2ObjCPtrPtr<CubeTextureChunkPtr, 
                                                 Window , 
                                                 UInt32>(
                                                tmpPtr, 
                                                &CubeTextureChunk::handleGL),
            1));

    endEditCP(tmpPtr, CubeTextureChunk::GLIdFieldMask);
}

//! output the instance for debug purposes

void CubeTextureChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CubeTextureChunk NI" << std::endl;
}


// GL object handler
// create the texture and destroy it
void CubeTextureChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    
    // does the window support cubemaps?
    if(win->hasExtension(_arbCubeTex) == false)
        return;
        
    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {
        GLuint tex = id;
        glDeleteTextures(1, &tex);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize)
    {
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 
                      mode, getImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 
                      Window::initialize, getPosZImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 
                      Window::initialize, getNegYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 
                      Window::initialize, getPosYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 
                      Window::initialize, getNegXImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 
                      Window::initialize, getPosXImage());        
    }
    else if(mode == Window::needrefresh)
    {
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 
                      mode, getImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 
                      mode, getPosZImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 
                      mode, getNegYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 
                      mode, getPosYImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 
                      mode, getNegXImage());        
        handleTexture(win, id, 
                      GL_TEXTURE_CUBE_MAP_ARB, 
                      GL_NONE, 
                      GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 
                      mode, getPosXImage());        
    }
    else
    {
        SWARNING << "Win:" << win << "TextureChunk(" << this 
                 << "::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}


void CubeTextureChunk::activate( DrawActionBase *action, UInt32 idx )
{   
    // does the window support cubemaps?
    if(action->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
    
    TextureChunk::activateTexture(action->getWindow(), idx);
    
    action->getWindow()->validateGLObject(getGLId());

    glErr("CubeTextureChunk::activate precheck");
  
    FDEBUG(("CubeTextureChunk::activate - %d\n", getGLId()));

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, getGLId());

    glEnable(GL_TEXTURE_CUBE_MAP_ARB);

    glErr("CubeTextureChunk::activate");

    // texture env
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());
}

void CubeTextureChunk::changeFrom(  DrawActionBase *action, 
                                    StateChunk     *old   , 
                                    UInt32          idx )
{
    // does the window support cubemaps?
    if(action->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
        
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    CubeTextureChunk *oldp      = dynamic_cast<CubeTextureChunk *>(old);
    
    // If the old one is not a cube texture chunk, deactivate it and activate
    // ourselves
    if(!oldp)
    {
        old->deactivate(action, idx);
        activate(action, idx);
        return;
    }

    glErr("CubeTextureChunk::changeFrom precheck");
 
    TextureChunk::activateTexture(action->getWindow(), idx);

    action->getWindow()->validateGLObject(getGLId());
    
    FDEBUG(("CubeTextureChunk::activate - %d\n", getGLId()));

    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, getGLId());

    if(oldp->getEnvMode() != getEnvMode())
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());

    glErr("CubeTextureChunk::changeFrom");
}

void CubeTextureChunk::deactivate(DrawActionBase *action, UInt32 idx)
{
    // does the window support cubemaps?
    if(action->getWindow()->hasExtension(_arbCubeTex) == false)
        return;
        
    TextureChunk::activateTexture(action->getWindow(), idx);

    glDisable(GL_TEXTURE_CUBE_MAP_ARB);

    glErr("CubeTextureChunk::deactivate");
}

/*-------------------------- comparison -----------------------------------*/

Real32 CubeTextureChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool CubeTextureChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool CubeTextureChunk::operator == (const StateChunk &other) const
{
    CubeTextureChunk const *tother = 
            dynamic_cast<CubeTextureChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return  TextureChunk::operator==(other) &&
            getPosZImage()  == tother->getPosZImage() &&
            getPosYImage()  == tother->getPosYImage() &&
            getNegYImage()  == tother->getNegYImage() &&
            getPosXImage()  == tother->getPosXImage() &&
            getNegXImage()  == tother->getNegXImage();
}

/** \brief unequal
 */

bool CubeTextureChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGCUBETEXTURECHUNK_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCUBETEXTURECHUNK_INLINE_CVSID;
}
