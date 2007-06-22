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
#include <OSGMatrixCameraDecorator.h>
#include <OSGTileCameraDecorator.h>
#include <OSGRenderAction.h>
#include <OSGSimpleAttachments.h>

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

FBOViewport::renderparamscbfp FBOViewport::_renderParamsFP   = NULL;

typedef void (OSG_APIENTRY * PFNGLDRAWBUFFERSARBPROC)
    (GLsizei n, const GLenum* bufs);
    
typedef void (OSG_APIENTRY * PFNGLBINDFRAMEBUFFEREXTPROC)
    (GLenum target, GLuint framebuffer);
typedef void (OSG_APIENTRY * PFNGLBINDRENDERBUFFEREXTPROC)
    (GLenum target, GLuint renderbuffer);
typedef GLenum (OSG_APIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)
    (GLenum target);
typedef void (OSG_APIENTRY * PFNGLDELETEFRAMEBUFFERSEXTPROC)
    (GLsizei n, const GLuint* framebuffers);
typedef void (OSG_APIENTRY * PFNGLDELETERENDERBUFFERSEXTPROC)
    (GLsizei n, const GLuint* renderbuffers);
typedef void (OSG_APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)
    (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (OSG_APIENTRY * PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (OSG_APIENTRY * PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)
    (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (OSG_APIENTRY * PFNGLGENFRAMEBUFFERSEXTPROC)
    (GLsizei n, GLuint* framebuffers);
typedef void (OSG_APIENTRY * PFNGLGENRENDERBUFFERSEXTPROC)
    (GLsizei n, GLuint* renderbuffers);
typedef void (OSG_APIENTRY * PFNGLGENERATEMIPMAPEXTPROC)
    (GLenum target);
typedef void (OSG_APIENTRY * PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)
    (GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (OSG_APIENTRY * PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)
    (GLenum target, GLenum pname, GLint* params);
typedef GLboolean (OSG_APIENTRY * PFNGLISFRAMEBUFFEREXTPROC)
    (GLuint framebuffer);
typedef GLboolean (OSG_APIENTRY * PFNGLISRENDERBUFFEREXTPROC)
    (GLuint renderbuffer);
typedef void (OSG_APIENTRY * PFNGLRENDERBUFFERSTORAGEEXTPROC)
    (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);


namespace
{
  bool checkGLError(const char* where)
  {
    GLenum errCode = 0;
    if ((errCode = glGetError()) != GL_NO_ERROR)
    {
        const GLubyte *errString = gluErrorString(errCode);
        FWARNING(("%s OpenGL Error: %s!\n", where, errString));
    }

    return errCode == GL_NO_ERROR;
  }
}

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
    Inherited()
{
}

FBOViewport::FBOViewport(const FBOViewport &source) :
    Inherited(source)
{
    _framebuffer_object_extension = Window::registerExtension("GL_EXT_framebuffer_object");

    _draw_buffers_extension = Window::registerExtension("GL_ARB_draw_buffers");

    _funcDrawBuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDrawBuffers", 
                                  GL_ARB_draw_buffers);

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
}

void FBOViewport::onDestroy(void)
{
    // TODO; delete buffers - but window is needed
}

bool FBOViewport::initialize(Window *win, Int32 format)
{
    GLuint fbIndex, dbIndex, sbIndex;
    
    Int32 width  = getStorageWidth();
    Int32 height = getStorageHeight();
    
    if (width <= 0 || height <= 0)
        return false;

    checkGLError("FBO initalize pre");

    if (getFrameBufferIndex() && !getDirty())
        return true;
    
    FBOViewportPtr thisP(*this);
    
    beginEditCP(thisP);
    
    setDirty(false);    // force re-initialization

    PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        (PFNGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
    PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT =
        (PFNGLBINDRENDERBUFFEREXTPROC)win->getFunction(_funcBindRenderbuffer);
    PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)win->getFunction(_funcCheckFramebufferStatus);
    PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT =
        (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)win->getFunction(_funcFramebufferRenderbuffer);
    PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT =
        (PFNGLGENFRAMEBUFFERSEXTPROC)win->getFunction(_funcGenFramebuffers);
    PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT =
        (PFNGLGENRENDERBUFFERSEXTPROC)win->getFunction(_funcGenRenderbuffers);
    PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT =
        (PFNGLRENDERBUFFERSTORAGEEXTPROC)win->getFunction(_funcRenderbufferStorage);
    
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

    checkGLError("FBO initalize pre depth");
           
    if (depth)
    {
        glGenRenderbuffersEXT(1, &dbIndex);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, dbIndex);
        setDepthBufferIndex(dbIndex);
        
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, depth, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT,
                                     GL_RENDERBUFFER_EXT, dbIndex);
    }

    checkGLError("FBO initalize pre stencil");
    
    if (stencil)
    {
        glGenRenderbuffersEXT(1, &sbIndex);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, sbIndex);
        setStencilBufferIndex(sbIndex);
        
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, stencil, width, height);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_STENCIL_ATTACHMENT_EXT,
                                     GL_RENDERBUFFER_EXT, sbIndex);
    }
    
    checkGLError("FBO initalize post stencil");
    
    endEditCP(thisP);
    
    bool result = true; //checkFrameBufferStatus(win);
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    checkGLError("FBO initalize post");
    
    return result;
}

void FBOViewport::setTarget(Window *win, UInt32 id, GLenum attachment, GLenum target)
{
    PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT =
        (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)win->getFunction(_funcFramebufferTexture1D);
    PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT =
        (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)win->getFunction(_funcFramebufferTexture2D);
    PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT =
        (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)win->getFunction(_funcFramebufferTexture3D);

    if (getFrameBufferIndex())
    {
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment, target, id, 0);

        if (!checkGLError("setTarget post"))
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
    PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        (PFNGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
        
    if (getFrameBufferIndex()) 
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, getFrameBufferIndex());
    else
        FWARNING(("Invalid FrameBufferObject index!\n"));
}

/// unbind the frambuffer object, so subsequent drawing ops are not drawn
/// into the fbo targets; '0' means windowing system provided framebuffer
void FBOViewport::stop(Window *win)
{
    PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        (PFNGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
        
    if (getFrameBufferIndex())
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBOViewport::render(RenderActionBase* action)
{
    if (!getEnabled())
        return;
        
    Window *win = action->getWindow();

    // Let the window handle resizes, to avoid interfering with the
    // FBOViewports settings
    
    win->resizeGL();
    
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
    if (getRoot() == NullFC && getRenderNodes().empty())
    {
        SWARNING << "FBOViewport::render: no root(s)!" << std::endl;
        return;
    }

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
        UInt32 i, numBuffers = (getTextures().getSize()) ? 1 : 0;
        
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
        
            for (i=0; i<getExcludeNodes().getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes()[i];
                if (exnode != NullFC)
                    exnode->setActive(false);
            }
            
            CameraPtr cP = getCamera();
            CameraDecoratorPtr cdP = CameraDecoratorPtr::dcast(cP);

            // ignore decorators!
            while (cdP != NullFC)
            {
                cP = cdP->getDecoratee();
                cdP = CameraDecoratorPtr::dcast(cP);
            }
        
            //action->setCamera(getCamera().getCPtr());
            action->setBackground(getBackground().getCPtr());
            action->setViewport(this);
            action->setTravMask(getTravMask());
            
            Int32 winWidth = getParent()->getWidth();
            Int32 winHeight = getParent()->getHeight();
            
            Int32 imgWidth = getStorageWidth();
            Int32 imgHeight = getStorageHeight();
            
            UInt32 x1, x2, y1, y2, tw, th;
            
            ShadowViewportPtr shadowVptPtr = NullFC;
            MFForegroundPtr fgndBag;
            MFForegroundPtr::iterator fgndIt;
            std::vector< Int32 > pos;
            Int32 n = 0;
            Real32 svpL, svpB, svpR, svpT;
            
            // there seems to be s.th. wrong with the svp init, only render if done
            static bool check = false;
            
            if (!sides)
            {
                if (imgWidth <= 1 || imgHeight <= 1)
                {
                    imgWidth = winWidth;
                    imgHeight = winHeight;
                    //SWARNING << "noDim: " << imgWidth << ", " << imgHeight << std::endl;
                }
                
                // TODO; introduce special mode instead of searching for this type
                for (j=0; j<win->getPort().size(); j++)
                {
                    shadowVptPtr = ShadowViewportPtr::dcast(win->getPort(j));
                    
                    if (shadowVptPtr != NullFC)
                        break;
                }
                
                if (shadowVptPtr != NullFC)
                {
                    n = shadowVptPtr->getForegrounds().size();
                    
                    for (j=n-1; j>=0; j--) {
                        TextureGrabForegroundPtr grab = TextureGrabForegroundPtr::dcast(
                                                        shadowVptPtr->getForegrounds(j));
                        if (grab == NullFC) {
                            fgndBag.push_back(shadowVptPtr->getForegrounds(j));
                            fgndIt = shadowVptPtr->getForegrounds().begin() + j;
                            shadowVptPtr->getForegrounds().erase(fgndIt);
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
            
            TileCameraDecoratorPtr tiledeco = TileCameraDecorator::create();
            
            beginEditCP(tiledeco);
                tiledeco->setFullSize(imgWidth, imgHeight);
            endEditCP(tiledeco);
            
            // render cubemaps
            if (sides == 6)
            {
                MatrixCameraDecoratorPtr deco = MatrixCameraDecorator::create();
                
                for (j=0; j<sides; j++)
                {
                    beginEditCP(deco);
                        deco->setDecoratee(cP);
                        deco->setPreProjection(transforms[j]);
                    endEditCP(deco);
                    
                    beginEditCP(tiledeco);
                        tiledeco->setDecoratee(deco);
                    endEditCP(tiledeco);
                    
                    action->setCamera(tiledeco.getCPtr());
                    
                    for (y1=0; y1 < imgHeight; y1 += winHeight)
                    {
                        y2 = osgMin((float)(y1+winHeight-1), (float)(imgHeight-1));
                        th = y2 - y1 + 1;
                        
                        for (x1=0; x1 < imgWidth; x1 += winWidth)
                        {
                            x2 = osgMin((float)(x1+winWidth-1), (float)(imgWidth-1));
                            tw = x2 - x1 + 1;
                            
                            // set tile size to maximal renderable size
                            beginEditCP(tiledeco);
                                tiledeco->setSize(  x1/(float)imgWidth,     y1/(float)imgHeight,
                                                (x2+1)/(float)imgWidth, (y2+1)/(float)imgHeight);
                            endEditCP(tiledeco);
                            
                            beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                                  BottomFieldMask | TopFieldMask);
                                setSize(0, 0, tw-1, th-1);
                            endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                                BottomFieldMask | TopFieldMask);
                            
                            // activate viewport settings
                            activate();

                            // render tile for one side of cube
                            if (getRenderNodes().getSize() == 0)
                            {
                                action->apply(getRoot());
                            }
                            else
                            {
                                for (i=0; i<getRenderNodes().getSize(); i++)
                                {
                                    NodePtr rdnode = getRenderNodes()[i];  
                                    if (rdnode != NullFC)
                                        action->apply(rdnode);
                                }
                            }
                            
                            for (UInt16 fi=0; fi<getForegrounds().size(); fi++)
                                getForegrounds(fi)->draw(action, this);

                            // deactivate viewport settings
                            deactivate();
                            
                            win->validateGLObject(getTextures(0)->getGLId());
                            
                            glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 
                                win->getGLObjectId(getTextures(0)->getGLId()));
                            
                            glCopyTexSubImage2D(targets[j], 0, x1, y1, 0, 0, tw, th);
                            
                            if (glGetError() != GL_NO_ERROR)
                                SWARNING << "Error in Cube-Texture-Creation!" << endLog;    
                            
                            glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 0);
                        }
                    }
                }
                
                subRefCP(deco);
            }
            else if (sides == 1)
            {
                beginEditCP(tiledeco);
                    tiledeco->setDecoratee(cP);
                endEditCP(tiledeco);
                
                action->setCamera(tiledeco.getCPtr());
                
                for (y1=0; y1 < imgHeight; y1 += winHeight)
                {
                    y2 = osgMin((float)(y1+winHeight-1), (float)(imgHeight-1));
                    th = y2 - y1 + 1;
                    
                    for (x1=0; x1 < imgWidth; x1 += winWidth)
                    {
                        x2 = osgMin((float)(x1+winWidth-1), (float)(imgWidth-1));
                        tw = x2 - x1 + 1;
                        
                        // set tile size to maximal renderable size
                        beginEditCP(tiledeco);
                            tiledeco->setSize(  x1/(float)imgWidth,     y1/(float)imgHeight,
                                            (x2+1)/(float)imgWidth, (y2+1)/(float)imgHeight);
                        endEditCP(tiledeco);
                        
                        beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                              BottomFieldMask | TopFieldMask);
                            setSize(0, 0, tw-1, th-1);
                        endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                                            BottomFieldMask | TopFieldMask);
                        
                        // activate viewport settings
                        activate();

                        // render tile for texture
                        if (getRenderNodes().getSize() == 0)
                        {
                            action->apply(getRoot());
                        }
                        else
                        {
                            for (i=0; i<getRenderNodes().getSize(); i++)
                            {
                                NodePtr rdnode = getRenderNodes()[i];  
                                if (rdnode != NullFC)
                                    action->apply(rdnode);
                            }
                        }
                        
                        for (UInt16 fi=0; fi<getForegrounds().size(); fi++)
                            getForegrounds(fi)->draw(action, this);
                        
                        // deactivate viewport settings
                        deactivate();

                        win->validateGLObject(getTextures(0)->getGLId());
                        
                        GLenum target = getTextures(0)->getTarget();
                        
                        // TODO; check if target is valid and allow usage of 3d texture slices
                        if (target == GL_NONE)
                            target = GL_TEXTURE_2D;
                        
                        glBindTexture(target, 
                            win->getGLObjectId(getTextures(0)->getGLId()));
                        
                        glCopyTexSubImage2D(target, 0, x1, y1, 0, 0, tw, th);
                        
                        if (glGetError() != GL_NO_ERROR)
                            SWARNING << "Error in Texture-Creation! " << endLog;    
                        
                        glBindTexture(target, 0);
                    }
                }
            }
            else if (check && shadowVptPtr != NullFC) 
            {
                action->setCamera(getCamera().getCPtr());
                
                shadowVptPtr->render(action);
                
                win->validateGLObject(getTextures(0)->getGLId());
                
                GLenum target = getTextures(0)->getTarget();
                
                if (target == GL_NONE)
                    target = GL_TEXTURE_2D;
                
                glBindTexture(target, 
                    win->getGLObjectId(getTextures(0)->getGLId()));
                
                glCopyTexSubImage2D(target, 0, 0, 0, 0, 0, imgWidth, imgHeight);
                
                if (glGetError() != GL_NO_ERROR)
                    SWARNING << "Error in Texture-Creation of special mode! " << endLog;    
                
                glBindTexture(target, 0);
            }
            
            if (shadowVptPtr != NullFC)    // true if size==0
            {
                Int32 k = pos.size() - 1,
                      m = fgndBag.size() - 1;
                
                for (j=0;j<n; j++) {
                    if (shadowVptPtr->getForegrounds().empty() && m >= 0) {
                        shadowVptPtr->getForegrounds().push_back(fgndBag[m--]);
                    }
                    else if (k >= 0 && pos[k] == j) {
                        ForegroundPtr fp = shadowVptPtr->getForegrounds(j);
                        fp->setActive(true);
                        k--;
                    }
                    else if (m>=0) {
                        fgndIt = shadowVptPtr->getForegrounds().begin() + j;
                        shadowVptPtr->getForegrounds().insert(fgndIt, fgndBag[m--]);
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
            
            subRefCP(tiledeco);
            
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

            for (i=0; i<getExcludeNodes().getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes()[i];
                if (exnode != NullFC)
                    exnode->setActive(true);
            }
        }
    }
    else
    {
        PFNGLDRAWBUFFERSARBPROC glDrawBuffersARB =
            (PFNGLDRAWBUFFERSARBPROC)win->getFunction(_funcDrawBuffers);    
    
        // get number of render targets
        Int32 numBuffers = getMaxBuffers();
        GLenum *buffers = NULL;
        
        if (getTextures().getSize() < numBuffers)
            numBuffers = getTextures().getSize();

        if (numBuffers > 0) // texture found
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
				FWARNING((	"Rendering to separate depth and stencil textures "
							"is not possible. Disabling stencil texture.\n" ));         
                stencilTex = NullFC;
            }

            if ( !initialize(win, format) )
                assert(0);

            checkGLError("FBO render pre\n");
            
            bind(win);

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
                    
                    if (target == GL_NONE)
                        target = GL_TEXTURE_2D;
                    
                    setTarget(win, win->getGLObjectId(depthTex->getGLId()), 
								GL_DEPTH_ATTACHMENT_EXT, target);                
                }
                else if (stencilTex) 
                {
                    win->validateGLObject(stencilTex->getGLId());
					
                    target = stencilTex->getTarget();
                    
                    if (target == GL_NONE)
                        target = GL_TEXTURE_2D;
                        
                    setTarget(win, win->getGLObjectId(stencilTex->getGLId()), 
								GL_STENCIL_ATTACHMENT_EXT, target);                
                }

                for (i=0; i<numBuffers; i++)
                {
                    buffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;
                    
                    win->validateGLObject(colorTextures[i]->getGLId());
    
                    target = colorTextures[i]->getTarget();
    
                    // TODO; check if target is valid and allow usage of 3d texture slices
                    if (target == GL_NONE)
                        target = GL_TEXTURE_2D;
    
                    // bind this texture to the current fbo as color_attachment_i
                    setTarget(win, win->getGLObjectId(colorTextures[i]->getGLId()), 
								buffers[i], target);
                }

                checkFrameBufferStatus(win);
            
                // draw scene, the results are being written into the associated textures
                if (glDrawBuffersARB)
					glDrawBuffersARB (numBuffers, buffers);
                else {
					if (numBuffers > 1) {
						FWARNING((	"glDrawBuffersARB not supported, "
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
                
                if (target == GL_NONE)
                    target = GL_TEXTURE_2D;
                
                setTarget(win, win->getGLObjectId(depthTex->getGLId()), buffers[0], target);

                glDrawBuffer (GL_NONE);
                glReadBuffer (GL_NONE);

                checkFrameBufferStatus(win);
            }
            else if (stencilTex)
            {
                buffers[0] = GL_STENCIL_ATTACHMENT_EXT;
                numBuffers = 1;
                
                win->validateGLObject(stencilTex->getGLId());

                target = stencilTex->getTarget();
                
                if (target == GL_NONE)
                    target = GL_TEXTURE_2D;
				
                setTarget(win, win->getGLObjectId(stencilTex->getGLId()), buffers[0], target);

                glDrawBuffer (GL_NONE);
                glReadBuffer (GL_NONE);

                checkFrameBufferStatus(win);
            }

            // render
            for (i=0; i<(Int32)getExcludeNodes().getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes()[i];
                if (exnode != NullFC)
                    exnode->setActive(false);
            }
            
            CameraPtr cP = getCamera();
            CameraDecoratorPtr cdP = CameraDecoratorPtr::dcast(cP);

            // ignore decorators!
            while (cdP != NullFC)
            {
                cP = cdP->getDecoratee();
                cdP = CameraDecoratorPtr::dcast(cP);
            }
            
            action->setCamera(cP.getCPtr());
            action->setBackground(getBackground().getCPtr());
            action->setViewport(this);
            action->setTravMask(getTravMask());
            
            // activate viewport settings
            activate();

            if (getRenderNodes().getSize() == 0)
            {
                action->apply(getRoot());
            }
            else
            {
                for (i=0; i<(Int32)getRenderNodes().getSize(); i++)
                {
                    NodePtr rdnode = getRenderNodes()[i];  
                    if (rdnode != NullFC)
                        action->apply(rdnode);
                }
            }
            
            for (UInt16 fi=0; fi<getForegrounds().size(); fi++)
                getForegrounds(fi)->draw(action, this);
            
            // deactivate viewport settings
            deactivate();

            for (i=0; i<(Int32)getExcludeNodes().getSize(); i++)
            {
                NodePtr exnode = getExcludeNodes()[i];
                if (exnode != NullFC)
                    exnode->setActive(true);
            }
            
            stop(win);

            checkGLError("FBO render post");
        
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
    PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)win->getFunction(_funcCheckFramebufferStatus);
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
    PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT =
        (PFNGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
    PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT =
        (PFNGLBINDRENDERBUFFEREXTPROC)win->getFunction(_funcBindRenderbuffer);
    PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT =
        (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)win->getFunction(_funcCheckFramebufferStatus);
    PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT =
        (PFNGLDELETEFRAMEBUFFERSEXTPROC)win->getFunction(_funcDeleteFramebuffers);
    PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT =
        (PFNGLDELETERENDERBUFFERSEXTPROC)win->getFunction(_funcDeleteRenderbuffers);
    PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT =
        (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)win->getFunction(_funcFramebufferRenderbuffer);
    PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT =
        (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)win->getFunction(_funcFramebufferTexture1D);
    PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT =
        (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)win->getFunction(_funcFramebufferTexture2D);
    PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT =
        (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)win->getFunction(_funcFramebufferTexture3D);
    PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT =
        (PFNGLGENFRAMEBUFFERSEXTPROC)win->getFunction(_funcGenFramebuffers);
    PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT =
        (PFNGLGENRENDERBUFFERSEXTPROC)win->getFunction(_funcGenRenderbuffers);
    PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT =
        (PFNGLGENERATEMIPMAPEXTPROC)win->getFunction(_funcGenerateMipmap);
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT =
        (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)win->getFunction(_funcGetFramebufferAttachmentParameteriv);
    PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT =
        (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)win->getFunction(_funcGetRenderbufferParameteriv);
    PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT =
        (PFNGLISFRAMEBUFFEREXTPROC)win->getFunction(_funcIsFramebuffer);
    PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT =
        (PFNGLISRENDERBUFFEREXTPROC)win->getFunction(_funcIsRenderbuffer);
    PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT =
        (PFNGLRENDERBUFFERSTORAGEEXTPROC)win->getFunction(_funcRenderbufferStorage);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFBOViewport.cpp,v 1.8 2007/06/22 00:13:01 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFBOVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFBOVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFBOVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
