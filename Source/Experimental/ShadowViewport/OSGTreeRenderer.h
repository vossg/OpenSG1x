
#ifndef _OSGTREERENDERER_H_
#define _OSGTREERENDERER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGRenderActionBase.h>

#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>

#include <OSGPerspectiveCamera.h>
#include <OSGMatrixCamera.h>
#include <OSGTransform.h>
#include <OSGTextureChunk.h>

#include <OSGPassiveBackground.h>
#include <OSGDynamicVolume.h>

#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTileCameraDecorator.h>


OSG_BEGIN_NAMESPACE

class ShadowViewport;

class OSG_SYSTEMLIB_DLLMAPPING TreeRenderer
{
  private:

    bool initDone;

/*==========================  PUBLIC  =================================*/
  public:

    TreeRenderer(void);
    TreeRenderer(ShadowViewport *source);
    
    virtual ~TreeRenderer(void);
    
    virtual void render(RenderActionBase *action)=0;

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

  protected:

    OSGGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT;
    OSGGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT;
    OSGGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT;
    OSGGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT;
    OSGGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT;
    OSGGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT;
    OSGGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT;
    OSGGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT;
    OSGGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT;
    OSGGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT;
    OSGGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT;
    OSGGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT;
    OSGGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
    OSGGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT;
    OSGGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT;
    OSGGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT;
    OSGGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT;
    OSGGLDRAWBUFFERSARBPROC glDrawBuffersARB;

	static UInt32 _depth_texture_extension;
    static UInt32 _shadow_extension;
    static UInt32 _framebuffer_object_extension;
    static UInt32 _draw_buffers_extension;
    static UInt32 _funcDrawBuffers;
    static UInt32 _funcBindFramebuffer;
    static UInt32 _funcBindRenderbuffer;
    static UInt32 _funcCheckFramebufferStatus;
    static UInt32 _funcDeleteFramebuffers;
    static UInt32 _funcDeleteRenderbuffers;
    static UInt32 _funcFramebufferRenderbuffer;
    static UInt32 _funcFramebufferTexture1D;
    static UInt32 _funcFramebufferTexture2D;
    static UInt32 _funcFramebufferTexture3D;
    static UInt32 _funcGenFramebuffers;
    static UInt32 _funcGenRenderbuffers;
    static UInt32 _funcGenerateMipmap;
    static UInt32 _funcGetFramebufferAttachmentParameteriv;
    static UInt32 _funcGetRenderbufferParameteriv;
    static UInt32 _funcIsFramebuffer;
    static UInt32 _funcIsRenderbuffer;
    static UInt32 _funcRenderbufferStorage;

    // reference to parent
    ShadowViewport *shadowVP;
    
    bool useFBO;
	bool useNPOTTextures;
	bool useGLSL;
	bool useShadowExt;
	UInt32 maxPLMapSize;
	UInt32 PLMapSize;
	UInt32 maxTexSize;
	    
    void initialize(Window *win);
};

OSG_END_NAMESPACE


#endif /* _OSGTREERENDERER_H_ */
