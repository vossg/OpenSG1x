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
#include <OSGTextureChunk.h>
#include <OSGImage.h>
#include <OSGRenderAction.h>
#include <OSGSimpleAttachments.h>
#include <OSGRemoteAspect.h>

#include "OSGFBOViewport.h"

/* ----------------------- GL_EXT_framebuffer_object ----------------------- */

#ifndef GL_ARB_draw_buffers
    #define GL_ARB_draw_buffers 1
#endif

#ifndef GL_EXT_framebuffer_object
    #define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
    #define GL_MAX_RENDERBUFFER_SIZE_EXT 0x84E8
    #define GL_FRAMEBUFFER_BINDING_EXT 0x8CA6
    #define GL_RENDERBUFFER_BINDING_EXT 0x8CA7
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8CD0
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8CD1
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8CD2
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8CD4
    #define GL_FRAMEBUFFER_COMPLETE_EXT 0x8CD5
    #define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
    #define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
    #define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT 0x8CD8
    #define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
    #define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
    #define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
    #define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
    #define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8CDD
    #define GL_FRAMEBUFFER_STATUS_ERROR_EXT 0x8CDE
    #define GL_MAX_COLOR_ATTACHMENTS_EXT 0x8CDF
    #define GL_COLOR_ATTACHMENT0_EXT 0x8CE0
    #define GL_COLOR_ATTACHMENT1_EXT 0x8CE1
    #define GL_COLOR_ATTACHMENT2_EXT 0x8CE2
    #define GL_COLOR_ATTACHMENT3_EXT 0x8CE3
    #define GL_COLOR_ATTACHMENT4_EXT 0x8CE4
    #define GL_COLOR_ATTACHMENT5_EXT 0x8CE5
    #define GL_COLOR_ATTACHMENT6_EXT 0x8CE6
    #define GL_COLOR_ATTACHMENT7_EXT 0x8CE7
    #define GL_COLOR_ATTACHMENT8_EXT 0x8CE8
    #define GL_COLOR_ATTACHMENT9_EXT 0x8CE9
    #define GL_COLOR_ATTACHMENT10_EXT 0x8CEA
    #define GL_COLOR_ATTACHMENT11_EXT 0x8CEB
    #define GL_COLOR_ATTACHMENT12_EXT 0x8CEC
    #define GL_COLOR_ATTACHMENT13_EXT 0x8CED
    #define GL_COLOR_ATTACHMENT14_EXT 0x8CEE
    #define GL_COLOR_ATTACHMENT15_EXT 0x8CEF
    #define GL_DEPTH_ATTACHMENT_EXT 0x8D00
    #define GL_STENCIL_ATTACHMENT_EXT 0x8D20
    #define GL_FRAMEBUFFER_EXT 0x8D40
    #define GL_RENDERBUFFER_EXT 0x8D41
    #define GL_RENDERBUFFER_WIDTH_EXT 0x8D42
    #define GL_RENDERBUFFER_HEIGHT_EXT 0x8D43
    #define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
    #define GL_STENCIL_INDEX_EXT 0x8D45
    #define GL_STENCIL_INDEX1_EXT 0x8D46
    #define GL_STENCIL_INDEX4_EXT 0x8D47
    #define GL_STENCIL_INDEX8_EXT 0x8D48
    #define GL_STENCIL_INDEX16_EXT 0x8D49
#endif

#ifndef GL_TEXTURE_RECTANGLE_ARB
    #define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#endif

#ifndef GL_DEPTH_COMPONENT_ARB
    #define GL_DEPTH_COMPONENT_ARB 0x1902
#endif

#ifndef GL_ARB_depth_texture
    #define GL_DEPTH_COMPONENT16_ARB 0x81A5
    #define GL_DEPTH_COMPONENT24_ARB 0x81A6
    #define GL_DEPTH_COMPONENT32_ARB 0x81A7
    #define GL_TEXTURE_DEPTH_SIZE_ARB 0x884A
    #define GL_DEPTH_TEXTURE_MODE_ARB 0x884B
#endif

#ifndef GL_ARB_shadow
    #define GL_TEXTURE_COMPARE_MODE_ARB 0x884C
    #define GL_TEXTURE_COMPARE_FUNC_ARB 0x884D
    #define GL_COMPARE_R_TO_TEXTURE_ARB 0x884E
#endif

#ifndef GL_EXT_depth_stencil
    #define GL_DEPTH_STENCIL_EXT        0x84F9
    #define GL_UNSIGNED_INT_24_8_EXT    0x84FA
    #define GL_DEPTH24_STENCIL8_EXT     0x88F0
    #define GL_TEXTURE_STENCIL_SIZE_EXT 0x88F1
#endif

//
#include <OSGShadowViewport.h>
#include <OSGForeground.h>
#include <OSGTextureGrabForeground.h>
//

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FBOViewport
First Release of FramebufferObjects-Viewport.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 FBOViewport::_tex3D_extension;
UInt32 FBOViewport::_framebuffer_object_extension;
UInt32 FBOViewport::_draw_buffers_extension;

UInt32 FBOViewport::_funcDrawBuffers                         = Window::invalidFunctionID;

UInt32 FBOViewport::_funcBindFramebuffer                     = Window::invalidFunctionID;
UInt32 FBOViewport::_funcBindRenderbuffer                    = Window::invalidFunctionID;
UInt32 FBOViewport::_funcCheckFramebufferStatus              = Window::invalidFunctionID;
UInt32 FBOViewport::_funcDeleteFramebuffers                  = Window::invalidFunctionID;
UInt32 FBOViewport::_funcDeleteRenderbuffers                 = Window::invalidFunctionID;
UInt32 FBOViewport::_funcFramebufferRenderbuffer             = Window::invalidFunctionID;
UInt32 FBOViewport::_funcFramebufferTexture1D                = Window::invalidFunctionID;
UInt32 FBOViewport::_funcFramebufferTexture2D                = Window::invalidFunctionID;
UInt32 FBOViewport::_funcFramebufferTexture3D                = Window::invalidFunctionID;
UInt32 FBOViewport::_funcGenFramebuffers                     = Window::invalidFunctionID;
UInt32 FBOViewport::_funcGenRenderbuffers                    = Window::invalidFunctionID;
UInt32 FBOViewport::_funcGenerateMipmap                      = Window::invalidFunctionID;
UInt32 FBOViewport::_funcGetFramebufferAttachmentParameteriv = Window::invalidFunctionID;
UInt32 FBOViewport::_funcGetRenderbufferParameteriv          = Window::invalidFunctionID;
UInt32 FBOViewport::_funcIsFramebuffer                       = Window::invalidFunctionID;
UInt32 FBOViewport::_funcIsRenderbuffer                      = Window::invalidFunctionID;
UInt32 FBOViewport::_funcRenderbufferStorage                 = Window::invalidFunctionID;
UInt32 FBOViewport::_funcCopyTexSubImage3D                   = Window::invalidFunctionID;

FBOViewport::renderparamscbfp FBOViewport::_renderParamsFP   = NULL;

typedef void (OSG_APIENTRY * OSGGLCOPYTEXSUBIMAGE3DPROC)
    (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);

typedef void (OSG_APIENTRY * OSGGLDRAWBUFFERSARBPROC)
    (GLsizei n, const GLenum* bufs);

typedef void (OSG_APIENTRY * OSGGLBINDFRAMEBUFFEREXTPROC)
    (GLenum target, GLuint framebuffer);
typedef void (OSG_APIENTRY * OSGGLBINDRENDERBUFFEREXTPROC)
    (GLenum target, GLuint renderbuffer);
typedef GLenum (OSG_APIENTRY * OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC)
    (GLenum target);
typedef void (OSG_APIENTRY * OSGGLDELETEFRAMEBUFFERSEXTPROC)
    (GLsizei n, const GLuint* framebuffers);
typedef void (OSG_APIENTRY * OSGGLDELETERENDERBUFFERSEXTPROC)
    (GLsizei n, const GLuint* renderbuffers);
typedef void (OSG_APIENTRY * OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC)
    (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * OSGGLFRAMEBUFFERTEXTURE1DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * OSGGLFRAMEBUFFERTEXTURE2DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * OSGGLFRAMEBUFFERTEXTURE3DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (OSG_APIENTRY * OSGGLGENFRAMEBUFFERSEXTPROC)
    (GLsizei n, GLuint* framebuffers);
typedef void (OSG_APIENTRY * OSGGLGENRENDERBUFFERSEXTPROC)
    (GLsizei n, GLuint* renderbuffers);
typedef void (OSG_APIENTRY * OSGGLGENERATEMIPMAPEXTPROC)
    (GLenum target);
typedef void (OSG_APIENTRY * OSGGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)
    (GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (OSG_APIENTRY * OSGGLGETRENDERBUFFERPARAMETERIVEXTPROC)
    (GLenum target, GLenum pname, GLint* params);
typedef GLboolean (OSG_APIENTRY * OSGGLISFRAMEBUFFEREXTPROC)
    (GLuint framebuffer);
typedef GLboolean (OSG_APIENTRY * OSGGLISRENDERBUFFEREXTPROC)
    (GLuint renderbuffer);
typedef void (OSG_APIENTRY * OSGGLRENDERBUFFERSTORAGEEXTPROC)
    (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FBOViewport::initMethod (void)
{
}

void FBOViewport::setRenderParamsCB(renderparamscbfp fp)
{
    _renderParamsFP = fp;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FBOViewport::FBOViewport(void) :
    Inherited(),
    _tiledeco(NullFC),
    _deco(NullFC)
{
}

FBOViewport::FBOViewport(const FBOViewport &source) :
    Inherited(source),
    _tiledeco(source._tiledeco),
    _deco(source._deco)
{
    _tex3D_extension = Window::registerExtension("GL_EXT_texture3D");
    
    _framebuffer_object_extension = Window::registerExtension("GL_EXT_framebuffer_object");

    _draw_buffers_extension = Window::registerExtension("GL_ARB_draw_buffers");

    _funcDrawBuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDrawBuffers", 
                                  _draw_buffers_extension);

    _funcBindFramebuffer =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBindFramebufferEXT", 
                                  _framebuffer_object_extension);
    _funcBindRenderbuffer =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBindRenderbufferEXT", 
                                  _framebuffer_object_extension);
    _funcCheckFramebufferStatus =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCheckFramebufferStatusEXT", 
                                  _framebuffer_object_extension);
    _funcDeleteFramebuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDeleteFramebuffersEXT", 
                                  _framebuffer_object_extension);
    _funcDeleteRenderbuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDeleteRenderbuffersEXT", 
                                  _framebuffer_object_extension);
    _funcFramebufferRenderbuffer =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFramebufferRenderbufferEXT", 
                                  _framebuffer_object_extension);
    _funcFramebufferTexture1D =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFramebufferTexture1DEXT", 
                                  _framebuffer_object_extension);
    _funcFramebufferTexture2D =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFramebufferTexture2DEXT", 
                                  _framebuffer_object_extension);
    _funcFramebufferTexture3D =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFramebufferTexture3DEXT", 
                                  _framebuffer_object_extension);
    _funcGenFramebuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGenFramebuffersEXT", 
                                  _framebuffer_object_extension);
    _funcGenRenderbuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGenRenderbuffersEXT", 
                                  _framebuffer_object_extension);
    _funcGenerateMipmap =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGenerateMipmapEXT", 
                                  _framebuffer_object_extension);
    _funcGetFramebufferAttachmentParameteriv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetFramebufferAttachmentParameterivEXT", 
                                  _framebuffer_object_extension);
    _funcGetRenderbufferParameteriv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetRenderbufferParameterivEXT", 
                                  _framebuffer_object_extension);
    _funcIsFramebuffer =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glIsFramebufferEXT", 
                                  _framebuffer_object_extension);
    _funcIsRenderbuffer =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glIsRenderbufferEXT", 
                                  _framebuffer_object_extension);
    _funcRenderbufferStorage =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glRenderbufferStorageEXT", 
                                  _framebuffer_object_extension);
                                  
    _funcCopyTexSubImage3D =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCopyTexSubImage3D", 
                                  _tex3D_extension);
}

FBOViewport::~FBOViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FBOViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FBOViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FBOViewport NI" << std::endl;
}

void FBOViewport::onCreate(const FBOViewport *source)
{
    // if we're in startup this is the prototype ...
    if (OSG::GlobalSystemState == OSG::Startup)
        return;

    // TODO; get maxBuffers - but window is needed
    
    // we need this for clustering. Without it FBO's are continuously allocated
    RemoteAspect::addFieldFilter(FBOViewport::getClassType().getId(), 
                                 FBOViewport::FrameBufferIndexFieldMask   |
                                 FBOViewport::DirtyFieldMask              |
                                 FBOViewport::StencilBufferIndexFieldMask |
                                 FBOViewport::DepthBufferIndexFieldMask );
    
    _tiledeco = TileCameraDecorator::create();
    addRefCP(_tiledeco);
    
    _deco = MatrixCameraDecorator::create();
    addRefCP(_deco);
}

void FBOViewport::onDestroy(void)
{
    // TODO; delete buffers - but window is needed
    
    subRefCP(_tiledeco);
    _tiledeco = NullFC;
    
    subRefCP(_deco);
    _deco = NullFC;
}

bool FBOViewport::initialize(Window *win, Int32 format)
{
    GLuint fbIndex, dbIndex, sbIndex;
    
    Int32 width  = getStorageWidth();
    Int32 height = getStorageHeight();

    if (width <= 0 || height <= 0)
        return false;

    glErr("FBO initizlize pre");
    
    if (getFrameBufferIndex() && !getDirty())
        return true;
    
    FBOViewportPtr thisP(*this);
    
    beginEditCP(thisP);
    
    setDirty(false);    // force re-initialization

    OSGGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        reinterpret_cast<OSGGLBINDFRAMEBUFFEREXTPROC>(
            win->getFunction(_funcBindFramebuffer));

    OSGGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT =
        reinterpret_cast<OSGGLBINDRENDERBUFFEREXTPROC>(
            win->getFunction(_funcBindRenderbuffer));

    OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        reinterpret_cast<OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC>(
            win->getFunction(_funcCheckFramebufferStatus));

    OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT =
        reinterpret_cast<OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC>(
            win->getFunction(_funcFramebufferRenderbuffer));

    OSGGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT =
        reinterpret_cast<OSGGLGENFRAMEBUFFERSEXTPROC>(
            win->getFunction(_funcGenFramebuffers));

    OSGGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT =
        reinterpret_cast<OSGGLGENRENDERBUFFERSEXTPROC>(
            win->getFunction(_funcGenRenderbuffers));

    OSGGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT =
        reinterpret_cast<OSGGLRENDERBUFFERSTORAGEEXTPROC>(
            win->getFunction(_funcRenderbufferStorage));
    

    glGenFramebuffersEXT(1, &fbIndex);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbIndex);

    setFrameBufferIndex(fbIndex);

    glDrawBuffer (GL_FALSE);
    glReadBuffer (GL_FALSE);
    
    GLuint depth = (format & FBO_DEPTH_16) ? GL_DEPTH_COMPONENT16_ARB :
                   (format & FBO_DEPTH_24) ? GL_DEPTH_COMPONENT24_ARB :
                   (format & FBO_DEPTH_32) ? GL_DEPTH_COMPONENT32_ARB : 0;
    
    GLuint stencil = (format & FBO_STENCIL_1 ) ? GL_STENCIL_INDEX1_EXT  :
                     (format & FBO_STENCIL_4 ) ? GL_STENCIL_INDEX4_EXT  :
                     (format & FBO_STENCIL_8 ) ? GL_STENCIL_INDEX8_EXT  :
                     (format & FBO_STENCIL_16) ? GL_STENCIL_INDEX16_EXT : 0;

    glErr("FBO initialize pre depth");
           
    if (depth)
    {
        glGenRenderbuffersEXT(1, &dbIndex);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, dbIndex);
        setDepthBufferIndex(dbIndex);
        
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, depth, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT,
                                     GL_RENDERBUFFER_EXT, dbIndex);
    }

    glErr("FBO initalize pre stencil");
    
    if (stencil)
    {
        glGenRenderbuffersEXT(1, &sbIndex);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, sbIndex);
        setStencilBufferIndex(sbIndex);
        
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, stencil, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_STENCIL_ATTACHMENT_EXT,
                                     GL_RENDERBUFFER_EXT, sbIndex);
    }
    
    glErr("FBO initalize post stencil");
    
    endEditCP(thisP);
    
    bool result = true; //checkFrameBufferStatus(win);
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    glErr("FBO initalize post");
    
    return result;
}

void FBOViewport::setTarget(Window *win, UInt32 id, GLenum attachment, GLenum target, GLint zoffset)
{
    OSGGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT =
        reinterpret_cast<OSGGLFRAMEBUFFERTEXTURE1DEXTPROC>(
            win->getFunction(_funcFramebufferTexture1D));

    OSGGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT =
        reinterpret_cast<OSGGLFRAMEBUFFERTEXTURE2DEXTPROC>(
            win->getFunction(_funcFramebufferTexture2D));

    OSGGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT =
        reinterpret_cast<OSGGLFRAMEBUFFERTEXTURE3DEXTPROC>(
            win->getFunction(_funcFramebufferTexture3D));

    if (getFrameBufferIndex())
    {
        if (target == GL_TEXTURE_3D) {
            glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, attachment, target, id, 0, zoffset);
        }
        else {
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment, target, id, 0);
        }
        
        if (!osgGlCheckError(__FILE__, __LINE__, "setTarget post"))
        {
            SWARNING << "Error with attachment: " << attachment
                     << ", id: " << id << ", target: " << target
                     << endLog;
        }
    }
    else
        FWARNING(("Invalid FrameBufferObject index!\n"));
}

void FBOViewport::bind(Window *win)
{
    OSGGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        reinterpret_cast<OSGGLBINDFRAMEBUFFEREXTPROC>(
            win->getFunction(_funcBindFramebuffer));
        
    if (getFrameBufferIndex()) 
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, getFrameBufferIndex());
    else
        FWARNING(("Invalid FrameBufferObject index!\n"));
}

/// unbind the frambuffer object, so subsequent drawing ops are not drawn
/// into the fbo targets; '0' means windowing system provided framebuffer
void FBOViewport::stop(Window *win)
{
    OSGGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        reinterpret_cast<OSGGLBINDFRAMEBUFFEREXTPROC>(
            win->getFunction(_funcBindFramebuffer));
        
    if (getFrameBufferIndex())
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBOViewport::render(RenderActionBase* action)
{
    if (!getEnabled())
        return;
    
    static GLenum targets[6] = {
                          GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
                          GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
                          GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
                        };

    static Matrix transforms[6] = {
                             Matrix( 1, 0, 0, 0,
                                     0,-1, 0, 0,
                                     0, 0,-1, 0,
                                     0, 0, 0, 1 ),
                                     
                             Matrix(-1, 0, 0, 0,
                                     0,-1, 0, 0,
                                     0, 0, 1, 0,
                                     0, 0, 0, 1 ),
                                     
                             Matrix( 1, 0, 0, 0,
                                     0, 0, 1, 0,
                                     0,-1, 0, 0,
                                     0, 0, 0, 1 ),
                                     
                             Matrix( 1, 0, 0, 0,
                                     0, 0,-1, 0,
                                     0, 1, 0, 0,
                                     0, 0, 0, 1 ),
                                     
                             Matrix( 0, 0,-1, 0,
                                     0,-1, 0, 0,
                                    -1, 0, 0, 0,
                                     0, 0, 0, 1 ),
                                     
                             Matrix( 0, 0, 1, 0,
                                     0,-1, 0, 0,
                                     1, 0, 0, 0,
                                     0, 0, 0, 1 ),
                        };

    Window *win = action->getWindow();
    
    if (win == NULL)
    {
        SWARNING << "FBOViewport::render: no window!" << std::endl;
        return;
    }
    if (getCamera() == NullFC)
    {
        SWARNING << "FBOViewport::render: no camera!" << std::endl;
        return;
    }
    if (getBackground() == NullFC)
    {
        SWARNING << "FBOViewport::render: no background!" << std::endl;
        return;
    }
    if (getRoot() == NullFC && getMFRenderNodes()->empty())
    {
        SWARNING << "FBOViewport::render: no root(s)!" << std::endl;
        return;
    }

    // Let the window handle resizes, to avoid interfering with the
    // FBOViewports settings
    win->resizeGL();

    GLint maxTexSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    
    beginEditCP(getPtr(), StorageWidthFieldMask | StorageHeightFieldMask);
        if (getStorageWidth() > maxTexSize)
            setStorageWidth( maxTexSize );
        if (getStorageHeight() > maxTexSize)
            setStorageHeight( maxTexSize );
    endEditCP(getPtr(), StorageWidthFieldMask | StorageHeightFieldMask);

    // set special render state
    if (_renderParamsFP != NULL)
        _renderParamsFP(FBO_RP_EFFECTS);

    bool depth = getGenDepthmaps();
    RenderAction *rAct = dynamic_cast<RenderAction*>(action);
    bool zWriteTransSave = rAct ? rAct->getZWriteTrans() : true;

    if (depth)
        rAct->setZWriteTrans(true);
            
    if (!getFboOn() || !extensionCheck())
    {
        UInt32 i, numBuffers = (getMFTextures()->getSize()) ? 1 : 0;
        
        if ( !win->hasExtension("GL_ARB_texture_non_power_of_two") )
        {
            beginEditCP(getPtr(), StorageWidthFieldMask | StorageHeightFieldMask);
            
            i = 1;
            do {
                i <<= 1;
            } while (getStorageHeight() >= i);
            setStorageHeight( i>>1 );
            
            i = 1;
            do {
                i <<= 1;
            } while (getStorageWidth() >= i);
            setStorageWidth( i>>1 );
            
            endEditCP(getPtr(), StorageWidthFieldMask | StorageHeightFieldMask);
        }

        if (numBuffers > 0)
        {
            Int32 j, sides = getGenCubemaps() ? 6 : 1;
            
            // invalid mode, used as workaround until a better idea for setting/ rendering env
            if (getGenDepthmaps() && getGenCubemaps())
                sides = 0;

            FDEBUG(( "Using standard GL (%d maxTexSize) with %d %sTextures and %d views...\n",
                     maxTexSize, numBuffers, (depth ? "depth" : ""), sides ));
        
            for (i=0; i<getMFExcludeNodes()->getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes(i);
                if (exnode != NullFC)
                    exnode->setActive(false);
            }
            
            CameraPtr cP = getCamera();
             
            if( getIgnoreCameraDecorators() )
            {
                // Ignore decorators passed to the viewport
                // Motivation:
                // Ignorance of Decorators is primarily used in order to ignore special 
                // decorators for stereo views or the tiles for cluster rendering: If e.g. 
                // you are rendering onto a tiled wall you usually don't want to have your 
                // FBO-rendered texture tiled.

                CameraDecoratorPtr cdP = CameraDecoratorPtr::dcast(cP);

                // ignore decorators!
                while (cdP != NullFC)
                {
                    cP = cdP->getDecoratee();
                    cdP = CameraDecoratorPtr::dcast(cP);
                }
            }
                 
            //action->setCamera    (cp.getCPtr()             );
            action->setBackground(getCPtr(getBackground()));
            action->setViewport  (this                     );
            action->setTravMask  (getTravMask()            );
            
            Int32 winWidth  = getParent()->getWidth ();
            Int32 winHeight = getParent()->getHeight();
            
            Int32 imgWidth  = getStorageWidth ();
            Int32 imgHeight = getStorageHeight();
            
            UInt32 x1, x2, y1, y2, tw, th;
            
            ShadowViewportPtr shadowVptPtr = NullFC;
            MFForegroundPtr fgndBag;
            MFForegroundPtr::iterator fgndIt;
            std::vector< Int32 > pos;
            Int32 n = 0;
            Real32 svpL = 0.f, svpB = 0.f, svpR = 0.f, svpT = 0.f;
            
            // there seems to be s.th. wrong with the svp init, only render if done
            static bool check = false;
            
            if (!sides)
            {
                if (imgWidth <= 1 || imgHeight <= 1)
                {
                    imgWidth = winWidth;
                    imgHeight = winHeight;
                }
                
                // TODO; introduce special mode instead of searching for this type
                for (j=0; j<win->getMFPort()->size(); j++)
                {
                    shadowVptPtr = ShadowViewportPtr::dcast(win->getPort(j));
                    
                    if (shadowVptPtr != NullFC)
                        break;
                }
                
                if (shadowVptPtr != NullFC)
                {
                    n = shadowVptPtr->getMFForegrounds()->size();
                    
                    for (j=n-1; j>=0; j--) {
                        TextureGrabForegroundPtr grab = 
                            TextureGrabForegroundPtr::dcast(
                                shadowVptPtr->getForegrounds(j));

                        if (grab == NullFC) {
                            fgndBag.push_back(shadowVptPtr->getForegrounds(j));

                            fgndIt = 
                                shadowVptPtr->editMFForegrounds()->begin() + j;

                            shadowVptPtr->editMFForegrounds()->erase(fgndIt);
                        }
                        else {
                            grab->setActive(false);
                            pos.push_back(j);
                        }
                    }
                    
                    svpL = shadowVptPtr->getLeft();
                    svpB = shadowVptPtr->getBottom();
                    svpR = shadowVptPtr->getRight();
                    svpT = shadowVptPtr->getTop();
                    
                    beginEditCP(shadowVptPtr, LeftFieldMask | RightFieldMask |
                                              BottomFieldMask | TopFieldMask);
                        shadowVptPtr->setSize(0, 0, imgWidth-1, imgHeight-1);
                    endEditCP(shadowVptPtr, LeftFieldMask | RightFieldMask |
                                            BottomFieldMask | TopFieldMask); 
                    
                    beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                          BottomFieldMask | TopFieldMask);
                        setSize(0, 0, imgWidth-1, imgHeight-1);
                    endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                        BottomFieldMask | TopFieldMask);
                    
                    ImagePtr i = getTextures(0)->getImage();
                    
                    if (i->getWidth() != imgWidth || i->getHeight() != imgHeight)
                    {
                        beginEditCP(getTextures(0), TextureChunk::ImageFieldMask);
                            i->set(i->getPixelFormat(), imgWidth, imgHeight);
                        endEditCP(getTextures(0), TextureChunk::ImageFieldMask);
                    }
                }
            }
            
            beginEditCP(_tiledeco);
                _tiledeco->setFullSize(imgWidth, imgHeight);
            endEditCP(_tiledeco);
            
            // render cubemaps
            if (sides == 6)
            {
                for (j=0; j<sides; j++)
                {
                    beginEditCP(_deco);
                        _deco->setDecoratee(cP);
                        _deco->setPreProjection(transforms[j]);
                    endEditCP(_deco);
                    
                    beginEditCP(_tiledeco);
                        _tiledeco->setDecoratee(_deco);
                    endEditCP(_tiledeco);
                    
                    action->setCamera(getCPtr(_tiledeco));
                    
                    for (y1=0; y1 < imgHeight; y1 += winHeight)
                    {
                        y2 = UInt32(osgMin(float(y1+winHeight-1), 
                                           float(imgHeight-1)));

                        th = y2 - y1 + 1;
                        
                        for (x1=0; x1 < imgWidth; x1 += winWidth)
                        {
                            x2 = UInt32(osgMin(float(x1+winWidth-1), 
                                               float(imgWidth-1)));
                            tw = x2 - x1 + 1;
                            
                            // set tile size to maximal renderable size
                            beginEditCP(_tiledeco);
                            _tiledeco->setSize(  x1/float(imgWidth),
                                                 y1/float(imgHeight),
                                                 (x2+1)/float(imgWidth), 
                                                 (y2+1)/float(imgHeight));
                            endEditCP(_tiledeco);
                            
                            beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                                  BottomFieldMask | TopFieldMask);
                                setSize(0, 0, tw-1, th-1);
                            endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                                BottomFieldMask | TopFieldMask);
                            
                            // activate viewport settings
                            activate();

                            // render tile for one side of cube
                            if (getMFRenderNodes()->getSize() == 0)
                            {
                                action->apply(getRoot());
                            }
                            else
                            {
                                for (i=0; i<getMFRenderNodes()->getSize(); i++)
                                {
                                    NodePtr rdnode = getRenderNodes(i);  
                                    if (rdnode != NullFC)
                                        action->apply(rdnode);
                                }
                            }
                            
                            for (UInt16 fi=0; fi<getMFForegrounds()->size(); fi++)
                                getForegrounds(fi)->draw(action, this);

                            // deactivate viewport settings
                            deactivate();
                            
                            win->validateGLObject(getTextures(0)->getGLId());
                            
                            glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 
                                win->getGLObjectId(getTextures(0)->getGLId()));
                            
                            glCopyTexSubImage2D(targets[j], 0, x1, y1, 0, 0, tw, th);
                            
                            glErr("Cube-Texture-Creation");
                            
                            glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 0);
                        }
                    }
                }
            }
            else if (sides == 1)
            {
                beginEditCP(_tiledeco);
                    _tiledeco->setDecoratee(cP);
                endEditCP(_tiledeco);
                
                action->setCamera(getCPtr(_tiledeco));
               
                // area stored in the texture, by default this is the size of
                // the texture
                int totalWidth  = imgWidth;
                int totalHeight = imgHeight;

                if(getFboOffIgnoreStorageSize())
                {
                    // for graphics cards that do not support NPOT textures
                    // the image (i.e. texture) is larger than the area we are
                    // interested in, so we use the window size instead.
                    totalWidth  = winWidth;
                    totalHeight = winHeight;
                }

                for (y1=0; y1 < totalHeight; y1 += winHeight)
                {
                    y2 = UInt32(osgMin(float(y1+winHeight-1), 
                                       float(totalHeight-1)));
                    th = y2 - y1 + 1;
                    
                    for (x1=0; x1 < totalWidth; x1 += winWidth)
                    {
                        x2 = UInt32(osgMin(float(x1+winWidth-1),
                                           float(totalWidth-1)));
                        tw = x2 - x1 + 1;
                        
                        // set tile size to maximal renderable size
                        beginEditCP(_tiledeco);
                        _tiledeco->setSize(  x1/float(totalWidth),     
                                             y1/float(totalHeight),
                                             (x2+1)/float(totalWidth),
                                             (y2+1)/float(totalHeight));
                        endEditCP(_tiledeco);
                        
                        beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                              BottomFieldMask | TopFieldMask);
                            setSize(0, 0, tw-1, th-1);
                        endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                            BottomFieldMask | TopFieldMask);
                        
                        // activate viewport settings
                        activate();

                        // render tile for texture
                        if (getMFRenderNodes()->getSize() == 0)
                        {
                            action->apply(getRoot());
                        }
                        else
                        {
                            for (i=0; i<getMFRenderNodes()->getSize(); i++)
                            {
                                NodePtr rdnode = getRenderNodes(i);  
                                if (rdnode != NullFC)
                                    action->apply(rdnode);
                            }
                        }
                        
                        for (UInt16 fi=0; fi<getMFForegrounds()->size(); fi++)
                            getForegrounds(fi)->draw(action, this);
                        
                        // deactivate viewport settings
                        deactivate();

                        GLenum target = GL_NONE;
                        // copy ALL attached textures.
                        // Most likely there's just one texture attached, the
                        // color buffer or the depth buffer. But in case both
                        // are attached, copy both!
                        for(UInt16 nt = 0; nt < getMFTextures()->getSize(); nt++)
                        {
                            win->validateGLObject(getTextures(nt)->getGLId());
                        
                            target = getTextures(nt)->getTarget();
                        
                            if (target == GL_NONE) {
                                if (getTextures(nt)->getImage()->getDepth() > 1)
                                    target = GL_TEXTURE_3D;
                                else
                                    target = GL_TEXTURE_2D;
                            }
                        
                            glBindTexture(target, 
                                win->getGLObjectId(getTextures(nt)->getGLId()));
                        
                            if (target == GL_TEXTURE_3D) 
                            {
                                OSGGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = 
                                    reinterpret_cast<
                                        OSGGLCOPYTEXSUBIMAGE3DPROC>(
                                            win->getFunction(
                                                _funcCopyTexSubImage3D));
                                    
                                if (glCopyTexSubImage3D) 
                                {
                                    UInt32 iZ, numZ = getMFZOffset()->size();
                                    
                                    for (iZ=0; iZ<numZ; iZ++) 
                                    {
                                        GLint zoffset = getZOffset(iZ);
                                        glCopyTexSubImage3D(target, 0, x1, y1, zoffset, 0, 0, tw, th);
                                    }
                                }
                                else
                                    SFATAL << "No func: glCopyTexSubImage3D" << endLog;
                            }
                            else
                                glCopyTexSubImage2D(target, 0, x1, y1, 0, 0, tw, th);
                            
                            glErr("Texture-Creation");
                            
                            if(getReadBuffer())
                            {
                                Int32 format = getTextures(nt)->getInternalFormat();
                                
                                if( format == GL_DEPTH_COMPONENT            || 
                                   (format >= GL_DEPTH_COMPONENT16_ARB &&
                                    format <= GL_DEPTH_COMPONENT32_ARB    ) ||
                                    format == GL_STENCIL_INDEX              ||
                                    format == GL_DEPTH_STENCIL_EXT            )
                                        continue; // ignore non-color buffers

                                ImagePtr texImg = getTextures(nt)->getImage();

                                if((texImg->getWidth () != getStorageWidth ()) ||
                                   (texImg->getHeight() != getStorageHeight()) ||
                                   (texImg->getData  () == NULL              )   )
                                {
                                    SINFO << "FBOViewport::render: "
                                          << "(Re)Allocating image for "
                                          << "read-back."
                                          << endLog;
            
                                    texImg->set(texImg->getPixelFormat(),
                                                getStorageWidth(),
                                                getStorageHeight()       );
                                }
            
                                // select back buffer and read data into image
                                glReadBuffer(GL_BACK); 
                                glReadPixels(0, 0, getStorageWidth(),
                                             getStorageHeight(), 
                                             texImg->getPixelFormat(),
                                             texImg->getDataType(),
                                             texImg->editData());

                                glReadBuffer(GL_NONE);
                            }
                        }
                            
                        glBindTexture(target, 0);
                    }
                }
            }
            else if (check && shadowVptPtr != NullFC) 
            {
                action->setCamera(getCPtr(getCamera()));
                
                shadowVptPtr->render(action);
                
                win->validateGLObject(getTextures(0)->getGLId());
                
                GLenum target = getTextures(0)->getTarget();
                
                if (target == GL_NONE) {
                    if (getTextures(0)->getImage()->getDepth() > 1)
                        target = GL_TEXTURE_3D;
                    else
                        target = GL_TEXTURE_2D;
                }
                
                glBindTexture(target, 
                    win->getGLObjectId(getTextures(0)->getGLId()));
                
                if (target == GL_TEXTURE_3D) 
                {
                    OSGGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = 
                        reinterpret_cast<OSGGLCOPYTEXSUBIMAGE3DPROC>(
                            win->getFunction(_funcCopyTexSubImage3D));
                        
                    if (glCopyTexSubImage3D) 
                    {
                        UInt32 iZ, numZ = getMFZOffset()->size();
                        
                        for (iZ=0; iZ<numZ; iZ++) 
                        {
                            GLint zoffset = getZOffset(iZ);
                            glCopyTexSubImage3D(target, 0, 0, 0, zoffset, 0, 0, imgWidth, imgHeight);
                        }
                    }
                    else
                        SFATAL << "No func: glCopyTexSubImage3D" << endLog;
                }
                else
                    glCopyTexSubImage2D(target, 0, 0, 0, 0, 0, imgWidth, imgHeight);           
                
                glErr("Texture-Creation special mode");
                
                glBindTexture(target, 0);
            }
            
            if (shadowVptPtr != NullFC)    // true if size==0
            {
                Int32 k = pos.size() - 1,
                      m = fgndBag.size() - 1;
                
                for (j=0;j<n; j++) {
                    if (shadowVptPtr->getMFForegrounds()->empty() && m >= 0) {
                        shadowVptPtr->editMFForegrounds()->push_back(fgndBag[m--]);
                    }
                    else if (k >= 0 && pos[k] == j) {
                        ForegroundPtr fp = shadowVptPtr->getForegrounds(j);
                        fp->setActive(true);
                        k--;
                    }
                    else if (m>=0) {
                        fgndIt = shadowVptPtr->editMFForegrounds()->begin() + j;
                        shadowVptPtr->editMFForegrounds()->insert(fgndIt, fgndBag[m--]);
                    }
                }
                fgndBag.clear();
                
                beginEditCP(shadowVptPtr, LeftFieldMask | RightFieldMask |
                                          BottomFieldMask | TopFieldMask);
                    shadowVptPtr->setSize(svpL, svpB, svpR, svpT);
                endEditCP(shadowVptPtr, LeftFieldMask | RightFieldMask |
                                        BottomFieldMask | TopFieldMask);
                
                check++;
            }
            
            beginEditCP(getPtr(), LeftFieldMask | RightFieldMask | 
                                  BottomFieldMask | TopFieldMask |
                                  StorageWidthFieldMask | StorageHeightFieldMask);
                setSize(0, 0, imgWidth-1, imgHeight-1);
            if (sides)
            {
                setStorageWidth(imgWidth);
                setStorageHeight(imgHeight);
            }
            endEditCP(getPtr(), LeftFieldMask | RightFieldMask | 
                                BottomFieldMask | TopFieldMask |
                                StorageWidthFieldMask | StorageHeightFieldMask);

            for (i=0; i<getMFExcludeNodes()->getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes(i);
                if (exnode != NullFC)
                    exnode->setActive(true);
            }
        }
    }
    else
    {
        OSGGLDRAWBUFFERSARBPROC glDrawBuffersARB =
            reinterpret_cast<OSGGLDRAWBUFFERSARBPROC>(
                win->getFunction(_funcDrawBuffers));   

        OSGGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT =
            reinterpret_cast<OSGGLGENERATEMIPMAPEXTPROC>(
                win->getFunction(_funcGenerateMipmap)); 
    
        // get number of render targets
        Int32 numBuffers = getMaxBuffers();
        GLenum *buffers = NULL;
        
        if (getMFTextures()->getSize() < numBuffers)
            numBuffers = getMFTextures()->getSize();

        if (numBuffers > 0 &&     // texture found
            getStorageWidth() > 0 && getStorageHeight() > 0) 
        {
            Int32 i, format;
            GLenum target = GL_TEXTURE_2D;

            // find depth & stencil texture
            TextureChunkPtr depthTex, stencilTex;
            MFTextureChunkPtr colorTextures;
            
            for (i=0; i<numBuffers; i++)
            {
                format = getTextures(i)->getInternalFormat();
                
                if ( format == GL_DEPTH_COMPONENT || 
                    (format >= GL_DEPTH_COMPONENT16_ARB &&
                    format <= GL_DEPTH_COMPONENT32_ARB) )
                {
                    depthTex = getTextures(i);
                }
                else if (format == GL_STENCIL_INDEX) {
                    stencilTex = getTextures(i);
                }
                else if (format == GL_DEPTH_STENCIL_EXT) {
                    SWARNING << "DEPTH_STENCIL format not yet impl." << endLog;
                }
                else {
                    colorTextures.push_back(getTextures(i));
                }
            }
            
            // TODO; allow setting of e.g. FBO_DEPTH_32
            //if (!depthTex) 
                format = FBO_DEPTH_24;
            // TODO; define DEPTH_STENCIL if depth is used as well
            if (stencilTex && depthTex) 
            {
                // format |= FBO_STENCIL_8;
                FWARNING((    "Rendering to separate depth and stencil textures "
                            "is not possible. Disabling stencil texture.\n" ));         
                stencilTex = NullFC;
            }

            if ( !initialize(win, format) ) {
                FFATAL(("Cannot initialize FBO\n"));
                assert(0);
            }

            glErr("FBO render pre\n");
            
            bind(win);
            
            // TODO; allow whole range and all at once, combine with buffers
            GLint zoffset = getMFZOffset()->size() ? getZOffset(0) : 0;
            bool needMipmaps = false;

            buffers = new GLenum[numBuffers];

            // TODO; optimize these if's
            if (!colorTextures.empty())
            {
                if (colorTextures.getSize() < numBuffers)
                    numBuffers = colorTextures.getSize();
                
                if (depthTex) 
                {
                    win->validateGLObject(depthTex->getGLId());
                    
                    target = depthTex->getTarget();
                    
                    if (target == GL_NONE) {
                        if (depthTex->getImage()->getDepth() > 1)
                            target = GL_TEXTURE_3D;
                        else
                            target = GL_TEXTURE_2D;
                    }
                    
                    // next TODO: clean up this mess!
                    needMipmaps = depthTex->getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
                                  depthTex->getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
                                  depthTex->getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
                                  depthTex->getMinFilter() == GL_LINEAR_MIPMAP_LINEAR;
                                  
                    if (needMipmaps && glGenerateMipmapEXT) {
                        glBindTexture(target, win->getGLObjectId(depthTex->getGLId()));
                        glGenerateMipmapEXT(target);
                        glBindTexture(target, 0);
                    }
                    
                    setTarget(win, win->getGLObjectId(depthTex->getGLId()), 
                                GL_DEPTH_ATTACHMENT_EXT, target, zoffset);                
                }
                else if (stencilTex) 
                {
                    win->validateGLObject(stencilTex->getGLId());
                    
                    target = stencilTex->getTarget();
                    
                    if (target == GL_NONE) {
                        if (stencilTex->getImage()->getDepth() > 1)
                            target = GL_TEXTURE_3D;
                        else
                            target = GL_TEXTURE_2D;
                    }
                        
                    setTarget(win, win->getGLObjectId(stencilTex->getGLId()), 
                                GL_STENCIL_ATTACHMENT_EXT, target, zoffset);                
                }

                for (i=0; i<numBuffers; i++)
                {
                    buffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;
                    
                    win->validateGLObject(colorTextures[i]->getGLId());
    
                    target = colorTextures[i]->getTarget();
    
                    if (target == GL_NONE) {
                        if (colorTextures[i]->getImage()->getDepth() > 1)
                            target = GL_TEXTURE_3D;
                        else
                            target = GL_TEXTURE_2D;
                    }
                    
                    needMipmaps = colorTextures[i]->getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
                                  colorTextures[i]->getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
                                  colorTextures[i]->getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
                                  colorTextures[i]->getMinFilter() == GL_LINEAR_MIPMAP_LINEAR;
                    
                    if (needMipmaps && glGenerateMipmapEXT) {
                        glBindTexture(target, win->getGLObjectId(colorTextures[i]->getGLId()));
                        glGenerateMipmapEXT(target);
                        glBindTexture(target, 0);
                    }
    
                    // bind this texture to the current fbo as color_attachment_i
                    setTarget(win, win->getGLObjectId(colorTextures[i]->getGLId()), 
                                buffers[i], target, zoffset);
                }

#ifdef OSG_DEBUG
                checkFrameBufferStatus(win);
#endif
            
                // draw scene, the results are being written into the associated textures
                if (glDrawBuffersARB)
                    glDrawBuffersARB (numBuffers, buffers);
                else
                {
                    if (numBuffers > 1)
                    {
                        FWARNING(("glDrawBuffersARB not supported, "
                                  "can't render to more than 1 buffer.\n" ));
                    }
                    glDrawBuffer ( *buffers );
                }
            }
            else if (depthTex)
            {
                buffers[0] = GL_DEPTH_ATTACHMENT_EXT;
                numBuffers = 1;
                
                win->validateGLObject(depthTex->getGLId());

                target = depthTex->getTarget();
                
                if (target == GL_NONE) {
                    if (depthTex->getImage()->getDepth() > 1)
                        target = GL_TEXTURE_3D;
                    else
                        target = GL_TEXTURE_2D;
                }
                
                needMipmaps = depthTex->getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
                              depthTex->getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
                              depthTex->getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
                              depthTex->getMinFilter() == GL_LINEAR_MIPMAP_LINEAR;
                
                if (needMipmaps && glGenerateMipmapEXT)
                {
                    glBindTexture(target, win->getGLObjectId(depthTex->getGLId()));
                    glGenerateMipmapEXT(target);
                    glBindTexture(target, 0);
                }
                
                setTarget(win, win->getGLObjectId(depthTex->getGLId()), 
                            buffers[0], target, zoffset);

                glDrawBuffer (GL_NONE);
                glReadBuffer (GL_NONE);

#ifdef OSG_DEBUG
                checkFrameBufferStatus(win);
#endif
            }
            else if (stencilTex)
            {
                buffers[0] = GL_STENCIL_ATTACHMENT_EXT;
                numBuffers = 1;
                
                win->validateGLObject(stencilTex->getGLId());

                target = stencilTex->getTarget();
                
                if (target == GL_NONE) {
                    if (stencilTex->getImage()->getDepth() > 1)
                        target = GL_TEXTURE_3D;
                    else
                        target = GL_TEXTURE_2D;
                }
                
                setTarget(win, win->getGLObjectId(stencilTex->getGLId()), 
                            buffers[0], target, zoffset);

                glDrawBuffer (GL_NONE);
                glReadBuffer (GL_NONE);

#ifdef OSG_DEBUG
                checkFrameBufferStatus(win);
#endif
            }

            // render
            for (i=0; i< Int32(getMFExcludeNodes()->getSize()); i++)
            {
                NodePtr exnode = getExcludeNodes(i);
                if (exnode != NullFC)
                    exnode->setActive(false);
            }
            
            CameraPtr cP = getCamera();

            if(getIgnoreCameraDecorators())
            {
                // Ignore decorators passed to the viewport
                // Motivation:
                // Ignorance of Decorators is primarily used in order to ignore special 
                // decorators for stereo views or the tiles for cluster rendering: If e.g. 
                // you are rendering onto a tiled wall you usually don't want to have your 
                // FBO-rendered texture tiled.

                CameraDecoratorPtr cdP = CameraDecoratorPtr::dcast(cP);

                // ignore decorators!
                while(cdP != NullFC)
                {
                    cP  = cdP->getDecoratee();
                    cdP = CameraDecoratorPtr::dcast(cP);
                }
            }     

            action->setCamera    (getCPtr(cP)             );
            action->setBackground(getCPtr(getBackground()));
            action->setViewport  (this                     );
            action->setTravMask  (getTravMask()            );
            
            // activate viewport settings
            activate();

            if (getMFRenderNodes()->getSize() == 0)
            {
                action->apply(getRoot());
            }
            else
            {
                for (i=0; i< Int32(getMFRenderNodes()->getSize()); i++)
                {
                    NodePtr rdnode = getRenderNodes(i);  
                    if (rdnode != NullFC)
                        action->apply(rdnode);
                }
            }
            
            for (UInt16 fi=0; fi < getMFForegrounds()->size(); fi++)
                getForegrounds(fi)->draw(action, this);
            
            if(getReadBuffer() && !colorTextures.empty())
            {
                for (i = 0; i < numBuffers; ++i)
                {
                    ImagePtr texImg = colorTextures[i]->getImage();
                    
                    if((texImg->getWidth () != getStorageWidth ()) ||
                       (texImg->getHeight() != getStorageHeight()) ||
                       (texImg->getData  () == NULL              )   )
                    {
                        SINFO << "FBOViewport::render: (Re)Allocating image "
                              << "for color buffer read-back."
                              << endLog;
                    
                        texImg->set(texImg->getPixelFormat(),
                                    getStorageWidth(),
                                    getStorageHeight()       );
                    }
                    
                    // select GL_COLORATTACHMENTn and read data into image
                    glReadBuffer(buffers[i]);
                    glReadPixels(0, 0, 
                                 getStorageWidth(), 
                                 getStorageHeight(),
                                 texImg->getPixelFormat(), 
                                 texImg->getDataType(),
                                 texImg->editData());
                    glReadBuffer(GL_NONE);
                }
            }
            else if(getReadBuffer() && depthTex)
            {
                ImagePtr texImg = depthTex->getImage();

                if((texImg->getWidth () != getStorageWidth ()) ||
                   (texImg->getHeight() != getStorageHeight()) ||
                   (texImg->getData  () == NULL              )   )
                {
                    SINFO << "FBOViewport::render: (Re)Allocating image "
                          << "for depth buffer read-back."
                          << endLog;
                
                    texImg->set(texImg->getPixelFormat(),
                                getStorageWidth(),
                                getStorageHeight(),
                                texImg->getDepth(),
                                texImg->getMipMapCount(),
                                texImg->getFrameCount(),
                                texImg->getFrameDelay(),
                                texImg->getData(),
                                texImg->getDataType(),
                                true,
                                texImg->getSideCount());
                }

                glReadBuffer(GL_DEPTH_ATTACHMENT_EXT);
                glReadPixels(0, 0, 
                             getStorageWidth(), 
                             getStorageHeight(),
                             texImg->getPixelFormat(), 
                             texImg->getDataType(),
                             texImg->editData());
                glReadBuffer(GL_NONE);
            }
                
            // deactivate viewport settings
            deactivate();

            for (i=0; i< Int32(getMFExcludeNodes()->getSize()); i++)
            {
                NodePtr exnode = getExcludeNodes(i);
                if (exnode != NullFC)
                    exnode->setActive(true);
            }
            
            stop(win);

            glErr("FBO render post");
        
            if (buffers)
                delete [] buffers;
        }
    }
    
    if (depth)
        rAct->setZWriteTrans(zWriteTransSave);

    // reset  special render state
    if (_renderParamsFP != NULL)
        _renderParamsFP(FBO_RP_NONE);
}

Int32 FBOViewport::getMaxBuffers(void)
{
  GLint max = 0;
  
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &max);
  FINFO(("GL_MAX_COLOR_ATTACHMENTS_EXT: %d\n", max));

  return max;
}

/// Checks if the needed OpenGL-Extensions are supported
bool FBOViewport::extensionCheck(void)
{
    if ( !getParent()->hasExtension(_framebuffer_object_extension) )
    {
        FWARNING(("I need GL_EXT_framebuffer_object-Extension!\n"));
        return false;
    }
    else
    {
        FDEBUG(("Extensions-Check done!\n"));
        return true;
    }
}

/// Checks if FBO status is ok
bool FBOViewport::checkFrameBufferStatus(Window *win)
{
    OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        reinterpret_cast<OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC>(
            win->getFunction(_funcCheckFramebufferStatus));

    GLenum errCode, status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    
    switch(status)
    {
        case GL_FRAMEBUFFER_COMPLETE_EXT: 
        FINFO(("%x: framebuffer complete!\n", status));
        break; 
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT: 
        FWARNING(("%x: framebuffer GL_FRAMEBUFFER_UNSUPPORTED_EXT\n", status));
        // choose different formats
        return false;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_ATTACHMENT\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        FWARNING(("%x: framebuffer FRAMEBUFFER_MISSING_ATTACHMENT\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        FWARNING(("%x: framebuffer FRAMEBUFFER_DIMENSIONS\n", status));
        break;
        /** not available on all plattforms
        case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT: 
        FWARNING(("%x: framebuffer INCOMPLETE_DUPLICATE_ATTACHMENT\n", status));
        break;
        */ 
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_FORMATS\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_DRAW_BUFFER\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_READ_BUFFER\n", status));
        break;
        case GL_FRAMEBUFFER_BINDING_EXT:
        FWARNING(("%x: framebuffer BINDING_EXT\n", status));
        break;
        default: 
        return false;
    }
    
    if ((errCode = glGetError()) != GL_NO_ERROR)
    {
        const GLubyte *errString = gluErrorString(errCode);
        FWARNING(("OpenGL Error: %s!\n", errString));
        return false;
    }
    return true;
}

// all fbo functions - just copy and past them when needed!
#if 0
    OSGGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        (OSGGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
    OSGGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT =
        (OSGGLBINDRENDERBUFFEREXTPROC)win->getFunction(_funcBindRenderbuffer);
    OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        (OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC)win->getFunction(_funcCheckFramebufferStatus);
    OSGGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT =
        (OSGGLDELETEFRAMEBUFFERSEXTPROC)win->getFunction(_funcDeleteFramebuffers);
    OSGGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT =
        (OSGGLDELETERENDERBUFFERSEXTPROC)win->getFunction(_funcDeleteRenderbuffers);
    OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT =
        (OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC)win->getFunction(_funcFramebufferRenderbuffer);
    OSGGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT =
        (OSGGLFRAMEBUFFERTEXTURE1DEXTPROC)win->getFunction(_funcFramebufferTexture1D);
    OSGGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT =
        (OSGGLFRAMEBUFFERTEXTURE2DEXTPROC)win->getFunction(_funcFramebufferTexture2D);
    OSGGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT =
        (OSGGLFRAMEBUFFERTEXTURE3DEXTPROC)win->getFunction(_funcFramebufferTexture3D);
    OSGGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT =
        (OSGGLGENFRAMEBUFFERSEXTPROC)win->getFunction(_funcGenFramebuffers);
    OSGGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT =
        (OSGGLGENRENDERBUFFERSEXTPROC)win->getFunction(_funcGenRenderbuffers);
    OSGGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT =
        (OSGGLGENERATEMIPMAPEXTPROC)win->getFunction(_funcGenerateMipmap);
    OSGGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT =
        (OSGGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)win->getFunction(_funcGetFramebufferAttachmentParameteriv);
    OSGGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT =
        (OSGGLGETRENDERBUFFERPARAMETERIVEXTPROC)win->getFunction(_funcGetRenderbufferParameteriv);
    OSGGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT =
        (OSGGLISFRAMEBUFFEREXTPROC)win->getFunction(_funcIsFramebuffer);
    OSGGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT =
        (OSGGLISRENDERBUFFEREXTPROC)win->getFunction(_funcIsRenderbuffer);
    OSGGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT =
        (OSGGLRENDERBUFFERSTORAGEEXTPROC)win->getFunction(_funcRenderbufferStorage);
#endif

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFBOViewport.cpp,v 1.30 2012/03/18 20:53:51 yjung Exp $";
    static Char8 cvsid_hpp       [] = OSGFBOVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFBOVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFBOVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
