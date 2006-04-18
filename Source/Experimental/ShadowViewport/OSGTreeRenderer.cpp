#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGQuaternion.h>
#include <OSGDrawAction.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGImage.h>

#include <OSGLight.h>

#include "OSGTreeRenderer.h"
#include "OSGShadowViewport.h"

#define PI 3.14159265f

//--------------------------------------------------------------------
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8CDD
#define GL_FRAMEBUFFER_EXT 0x8D40
#define GL_ARB_draw_buffers 1



OSG_USING_NAMESPACE

UInt32 TreeRenderer::_framebuffer_object_extension;
UInt32 TreeRenderer::_draw_buffers_extension;

UInt32 TreeRenderer::_funcDrawBuffers                         = Window::invalidFunctionID;

UInt32 TreeRenderer::_funcBindFramebuffer                     = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcBindRenderbuffer                    = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcCheckFramebufferStatus              = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcDeleteFramebuffers                  = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcDeleteRenderbuffers                 = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcFramebufferRenderbuffer             = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcFramebufferTexture1D                = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcFramebufferTexture2D                = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcFramebufferTexture3D                = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcGenFramebuffers                     = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcGenRenderbuffers                    = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcGenerateMipmap                      = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcGetFramebufferAttachmentParameteriv = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcGetRenderbufferParameteriv          = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcIsFramebuffer                       = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcIsRenderbuffer                      = Window::invalidFunctionID;
UInt32 TreeRenderer::_funcRenderbufferStorage                 = Window::invalidFunctionID;


TreeRenderer::TreeRenderer(void)
{
}

TreeRenderer::TreeRenderer(ShadowViewport *source)
{
	shadowVP = source;

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
	initDone = false;
	useFBO = false;
}


TreeRenderer::~TreeRenderer(void)
{
}

void TreeRenderer::initialize(Window *win)
{
	if(!initDone)
	{
	glBindFramebufferEXT =
        (OSGGLBINDFRAMEBUFFEREXTPROC)win->getFunction(_funcBindFramebuffer);
    glBindRenderbufferEXT =
        (OSGGLBINDRENDERBUFFEREXTPROC)win->getFunction(_funcBindRenderbuffer);
    glCheckFramebufferStatusEXT =
        (OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC)win->getFunction(_funcCheckFramebufferStatus);
    glDeleteFramebuffersEXT =
        (OSGGLDELETEFRAMEBUFFERSEXTPROC)win->getFunction(_funcDeleteFramebuffers);
    glDeleteRenderbuffersEXT =
        (OSGGLDELETERENDERBUFFERSEXTPROC)win->getFunction(_funcDeleteRenderbuffers);
    glFramebufferRenderbufferEXT =
        (OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC)win->getFunction(_funcFramebufferRenderbuffer);
    glFramebufferTexture1DEXT =
        (OSGGLFRAMEBUFFERTEXTURE1DEXTPROC)win->getFunction(_funcFramebufferTexture1D);
    glFramebufferTexture2DEXT =
        (OSGGLFRAMEBUFFERTEXTURE2DEXTPROC)win->getFunction(_funcFramebufferTexture2D);
    glFramebufferTexture3DEXT =
        (OSGGLFRAMEBUFFERTEXTURE3DEXTPROC)win->getFunction(_funcFramebufferTexture3D);
    glGenFramebuffersEXT =
        (OSGGLGENFRAMEBUFFERSEXTPROC)win->getFunction(_funcGenFramebuffers);
    glGenRenderbuffersEXT =
        (OSGGLGENRENDERBUFFERSEXTPROC)win->getFunction(_funcGenRenderbuffers);
    glGenerateMipmapEXT =
        (OSGGLGENERATEMIPMAPEXTPROC)win->getFunction(_funcGenerateMipmap);
    glGetFramebufferAttachmentParameterivEXT =
        (OSGGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)win->getFunction(_funcGetFramebufferAttachmentParameteriv);
    glGetRenderbufferParameterivEXT =
        (OSGGLGETRENDERBUFFERPARAMETERIVEXTPROC)win->getFunction(_funcGetRenderbufferParameteriv);
    glIsFramebufferEXT =
        (OSGGLISFRAMEBUFFEREXTPROC)win->getFunction(_funcIsFramebuffer);
    glIsRenderbufferEXT =
        (OSGGLISRENDERBUFFEREXTPROC)win->getFunction(_funcIsRenderbuffer);
    glRenderbufferStorageEXT =
        (OSGGLRENDERBUFFERSTORAGEEXTPROC)win->getFunction(_funcRenderbufferStorage);
	glDrawBuffersARB =
            (OSGGLDRAWBUFFERSARBPROC)win->getFunction(_funcDrawBuffers);

	if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_UNSUPPORTED_EXT)
	{
		useFBO=false;
		FINFO(("framebuffer objects not supportet, try new video drivers! FBO disabled.\n"));
	}
	else
	{
		useFBO = true;
		FINFO(("framebuffer objects supported!\n"));
	}
	initDone = true;
	}
}
 

