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
	useFBO = true;
	useNPOTTextures = true;
	useGLSL = true;

	shadowVP = source;

	_framebuffer_object_extension = Window::registerExtension("GL_EXT_framebuffer_object");

    _draw_buffers_extension = Window::registerExtension("GL_ARB_draw_buffers");

    _funcDrawBuffers =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDrawBuffers", GL_ARB_draw_buffers);

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
}


TreeRenderer::~TreeRenderer(void)
{
}

void TreeRenderer::initialize(Window *win)
{
	if(!initDone)
	{
		//check support for framebuffer objects
		useFBO = true;
	
		if(!win->hasExtension("GL_EXT_framebuffer_object")) useFBO = false;
		//ist das nötig?
		//if(!win->hasExtension("GL_ARB_draw_buffers")) useFBO = false;
	
		if(useFBO) 	
		{
			FNOTICE(("framebuffer objects supported.\n"));
		}
		else 
		{
			FNOTICE(("framebuffer objects not supported, try new video drivers. FBO disabled.\n"));
		}

		//check support for non-power-of-two textures
		useNPOTTextures = true;

		if(!win->hasExtension("GL_ARB_texture_non_power_of_two")) useNPOTTextures = false;

		if(useNPOTTextures)
		{
			FNOTICE(("texture_non_power_of_two supported.\n"));
		}
		else 
		{
			FNOTICE(("texture_non_power_of_two not supported by hardware.\n"));
		}

		//check if GLSL is available
		useGLSL = true;
		if(	!win->hasExtension("GL_ARB_shading_language_100") ||
			!win->hasExtension("GL_ARB_fragment_shader") ||
			!win->hasExtension("GL_ARB_vertex_shader") ||
			!win->hasExtension("GL_ARB_shader_objects") )	useGLSL = false;
		
		if(!useGLSL)
		{
			FNOTICE(("GLSL not supported, some shadow modes will be disabled.\n"));
		}
		else
		{
			FNOTICE(("GLSL supported.\n"));
		}

		//No NPOTTextures supportet if FBOs are disabled
		if(!useFBO) useNPOTTextures = false;

		if(useFBO)
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

		GLenum errCode, status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
   
		switch(status)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT: 
			FINFO(("%x: framebuffer complete!\n", status));
			break; 
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT: 
			FWARNING(("%x: framebuffer GL_FRAMEBUFFER_UNSUPPORTED_EXT\n", status));
			break;
			/*case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT: 
			FWARNING(("%x: framebuffer INCOMPLETE_ATTACHMENT\n", status));
			break; 
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT: 
			FWARNING(("%x: framebuffer FRAMEBUFFER_MISSING_ATTACHMENT\n", status));
			break; 
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT: 
			FWARNING(("%x: framebuffer FRAMEBUFFER_DIMENSIONS\n", status));
			break; 
			case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT: 
			FWARNING(("%x: framebuffer INCOMPLETE_DUPLICATE_ATTACHMENT\n", status));
			break; 
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
			break; */
			default: 
			break;
		}
    
		initDone = true;
		}
	}
}
 

