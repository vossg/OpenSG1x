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

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGImage.h>

#include "OSGDrawActionBase.h"

#include "OSGTextureChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureChunk
    \ingroup GrpSystemState

See \ref PageSystemTextureChunk for a description.

This chunk wraps glTexImage[123]D (osg::TextureChunk::_sfImage, 
osg::TextureChunk::_sfInternalFormat, osg::TextureChunk::_sfExternalFormat),
glTexParameter (osg::TextureChunk::_sfMinFilter,
osg::TextureChunk::_sfMagFilter, osg::TextureChunk::_sfWrapS, 
osg::TextureChunk::_sfWrapT, osg::TextureChunk::_sfWrapR), glTexEnv 
(osg::TextureChunk::_sfEnvMode, osg::TextureChunk::_sfEnvColor,
osg::TextureChunk::_sfPriority). The ARB combine extension is also supported,
where available (osg::TextureChunk::_sfEnvCombineRGB,  
osg::TextureChunk::_sfEnvScaleRGB, osg::TextureChunk::_sfEnvSource0RGB,
osg::TextureChunk::_sfEnvSource1RGB, osg::TextureChunk::_sfEnvSource2RGB,
osg::TextureChunk::_sfEnvOperand0RGB, osg::TextureChunk::_sfEnvOperand1RGB,
osg::TextureChunk::_sfEnvOperand2RGB, 
osg::TextureChunk::_sfEnvCombineAlpha,   osg::TextureChunk::_sfEnvScaleAlpha,
osg::TextureChunk::_sfEnvSource0Alpha, osg::TextureChunk::_sfEnvSource1Alpha,
osg::TextureChunk::_sfEnvSource2Alpha, osg::TextureChunk::_sfEnvOperand0Alpha,
osg::TextureChunk::_sfEnvOperand1Alpha,
osg::TextureChunk::_sfEnvOperand2Alpha). It is possible to enable the point
sprite coordinate replacement  (osg::TextureChunk::_sfPointSprite), see \ref
PageSystemPointChunk for details. The two parameters
osg::TextureChunk::_sfScale and osg::TextureChunk::_sfFrame specify details
about the texture.

On hardware that supports it (i.e. NVidia boards) the texture shader
extension(s) are also available.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TextureChunk::cvsid[] = "@(#)$Id: OSGTextureChunk.cpp,v 1.41 2002/06/17 12:27:14 jbehr Exp $";

StateChunkClass TextureChunk::_class("Texture", osgMaxTextures);

UInt32 TextureChunk::_extTex3D;
UInt32 TextureChunk::_arbMultiTex;
UInt32 TextureChunk::_arbCubeTex;
UInt32 TextureChunk::_nvPointSprite;
UInt32 TextureChunk::_nvTextureShader;
UInt32 TextureChunk::_nvTextureShader2;
UInt32 TextureChunk::_nvTextureShader3;
UInt32 TextureChunk::_funcTexImage3D    = Window::invalidFunctionID;
UInt32 TextureChunk::_funcTexSubImage3D = Window::invalidFunctionID;
UInt32 TextureChunk::_funcActiveTexture = Window::invalidFunctionID;

// define GL_TEXTURE_3D, if not defined yet
#ifndef GL_VERSION_1_2
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3DEXT"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3DEXT"
#else
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3D"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3D"
#endif


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void TextureChunk::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

TextureChunk::TextureChunk(void) :
    Inherited()
{
    _extTex3D          = 
        Window::registerExtension("GL_EXT_texture3D"       );
    _arbMultiTex       = 
        Window::registerExtension("GL_ARB_multitexture"    );
    _arbCubeTex        = 
        Window::registerExtension("GL_ARB_texture_cube_map");
    _nvPointSprite     = 
        Window::registerExtension("GL_NV_point_sprite"     );
    _nvTextureShader   = 
        Window::registerExtension("GL_NV_texture_shader"   );
    _nvTextureShader2  = 
        Window::registerExtension("GL_NV_texture_shader2"  );
    _nvTextureShader3  = 
        Window::registerExtension("GL_NV_texture_shader3"  );
    _funcTexImage3D    = 
        Window::registerFunction (GL_FUNC_TEXIMAGE3D                        );
    _funcTexSubImage3D = 
        Window::registerFunction (GL_FUNC_TEXSUBIMAGE3D                     );
    _funcActiveTexture = 
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glActiveTextureARB"  );
}

TextureChunk::TextureChunk(const TextureChunk &source) :
    Inherited(source)
{
}

TextureChunk::~TextureChunk(void)
{
    if(_sfImage.getValue() != NullFC)
        subRefCP(_sfImage.getValue());
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TextureChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep 
    it consistent with the cubeTexture specifics
*/

void TextureChunk::changed(BitVector whichField, UInt32 origin)
{
    if((whichField & ~(MinFilterFieldMask | MagFilterFieldMask)) == 0)
    {
        if((getMinFilter() != GL_NEAREST) &&
           (getMinFilter() != GL_LINEAR))
        {
	        Window::reinitializeGLObject(getGLId());
        }
        else
        {
            Window::refreshGLObject(getGLId());
        }
    }
    else if((whichField & ~PriorityFieldMask) == 0)
    {
        Window::refreshGLObject(getGLId());
    }
    else
    {
        Window::reinitializeGLObject(getGLId());
    }

    if(whichField & ImageFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfImage.getValue());
            }
            else
            {
                ImagePtr pImage = _sfImage.getValue();
                
                _sfImage.setValue(NullFC);
                
                setImage(pImage);
            }
        }
    }

    Inherited::changed(whichField, origin);
}

bool TextureChunk::isTransparent(void) const
{
    // Even if the texture has alpha, the Blending is makes the sorting
    // important, thus textures per se are not transparent
    return false;
}


/*----------------------------- onCreate --------------------------------*/

void TextureChunk::onCreate(const TextureChunk *)
{
    if(GlobalSystemState == Startup)
        return;
        
    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    TextureChunkPtr tmpPtr(*this);

    beginEditCP(tmpPtr, TextureChunk::GLIdFieldMask);

    setGLId(
        Window::registerGLObject(
            osgTypedMethodVoidFunctor2ObjCPtrPtr<TextureChunkPtr, 
                                                 Window , 
                                                 UInt32>(
                                                     tmpPtr, 
                                                     &TextureChunk::handleGL),
            1));

    endEditCP(tmpPtr, TextureChunk::GLIdFieldMask);
}


/*------------------------------ Output ----------------------------------*/

void TextureChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                        const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TextureChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

/*! Texture handler. Create/update a single texture.
    Also used by derived CubeMap chunk.
*/

void TextureChunk::handleTextureShader(Window *win, GLenum bindtarget)
{    
	if(!win->hasExtension(_nvTextureShader))
	{
        if(getShaderOperation() != GL_NONE)
		    FINFO(("NV Texture Shaders not supported on Window %p!\n", win));
		return;
	}
     
    glErr("textureShader precheck");
    
    glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV,
                getShaderOperation());
    
    glErr("textureShader setup: operation");
    
    if(getShaderOperation() == GL_NONE)
        return;

    if(bindtarget == GL_TEXTURE_3D && !win->hasExtension(_nvTextureShader2))
    {
        FINFO(("NV Texture Shaders 2 not supported on Window %p!\n", win));
        return;
    }
    
    if(getShaderInput() != GL_NONE)
        glTexEnvi(GL_TEXTURE_SHADER_NV, GL_PREVIOUS_TEXTURE_INPUT_NV,
                    getShaderInput());
        
    glErr("textureShader setup: input");
    
    if(getShaderRGBADotProduct() != GL_NONE)
        glTexEnvi(GL_TEXTURE_SHADER_NV, GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV,
                    getShaderRGBADotProduct());
         
    glErr("textureShader setup: rgba dotprod");
   
    if(getShaderOffsetMatrix().size() == 4)
    {
        glTexEnvfv(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_MATRIX_NV,
                    (GLfloat*)&(getShaderOffsetMatrix()[0]));
        
        glErr("textureShader setup: offset matrix");
    }
    else if(getShaderOffsetMatrix().size() != 0)
    {
        FWARNING(("TextureChunk::handleTextureShader: shaderOffsetMatrix has"
                    " to have 4 entries, not %d!\n",
                    getShaderOffsetMatrix().size() ));
    }
    
    glTexEnvf(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_SCALE_NV,
                getShaderOffsetScale());
        
    glErr("textureShader setup: offset scale");
    
    glTexEnvf(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_BIAS_NV,
                getShaderOffsetBias());
        
    glErr("textureShader setup: offset bias");
    
    GLint cullmodes[4];
    if(getShaderCullModes() & 0x1)
    {
        cullmodes[0] = GL_GEQUAL;
    }
    else
    {
        cullmodes[0] = GL_LESS;
    }
    
    if(getShaderCullModes() & 0x2)
    {
        cullmodes[1] = GL_GEQUAL;
    }
    else
    {
        cullmodes[1] = GL_LESS;
    }
    
    if(getShaderCullModes() & 0x4)
    {
        cullmodes[2] = GL_GEQUAL;
    }
    else
    {
        cullmodes[2] = GL_LESS;
    }
    
    if(getShaderCullModes() & 0x8)
    {
        cullmodes[3] = GL_GEQUAL;
    }
    else
    {
        cullmodes[3] = GL_LESS;
    }
    
    glTexEnviv(GL_TEXTURE_SHADER_NV, GL_CULL_MODES_NV, 
                    cullmodes);
       
    glErr("textureShader setup: cull modes");
    
    glTexEnvfv(GL_TEXTURE_SHADER_NV, GL_CONST_EYE_NV, 
                    getShaderConstEye().getValues());
       
    glErr("textureShader setup: const eye");

    
    
#ifdef OSG_DEBUG
    GLint consistent;
    glGetTexEnviv(GL_TEXTURE_SHADER_NV, GL_SHADER_CONSISTENT_NV,
          &consistent);
    if(!consistent)
    {
        FWARNING(("Texture shaders not consistent!\n"));
    }
#endif
}

void TextureChunk::handleTexture(Window *win, UInt32 id, 
    GLenum bindtarget, 
    GLenum paramtarget, 
    GLenum imgtarget, 
    Window::GLObjectStatusE mode, ImagePtr img)
{
    if( img==NullFC || ! img->getDimension()) // no image ?
        return;

    if(mode == Window::initialize || mode == Window::reinitialize)
    {
		if(bindtarget == GL_TEXTURE_3D && !win->hasExtension(_extTex3D))
		{
			FINFO(("3D textures not supported on Window %p!\n", win));
			return;
		}
		
		if(paramtarget == GL_TEXTURE_CUBE_MAP_ARB && !win->hasExtension(_arbCubeTex))
		{
			FINFO(("Cube textures not supported on Window %p!\n", win));
			return;
		}
		     
        if(mode == Window::reinitialize)
        {
            GLuint tex = id;
            glDeleteTextures(1, &tex);
        }
        
        // 3D texture functions
        void (OSG_APIENTRY*TexImage3D)(GLenum target, GLint level, GLenum internalformat, 
                           GLsizei width, GLsizei height, GLsizei depth, 
                           GLint border, GLenum format, GLenum type, 
                           const GLvoid *pixels) = 
            (void (OSG_APIENTRY*)(GLenum target, GLint level, GLenum internalformat, 
                      GLsizei width, GLsizei height, GLsizei depth, 
                      GLint border, GLenum format, GLenum type, 
                      const GLvoid *pixels))
            win->getFunction(_funcTexImage3D);

        void (OSG_APIENTRY*TexSubImage3D)
                          (GLenum target, GLint level, GLint xoffset, 
                           GLint yoffset, GLint zoffset, GLsizei width, 
                           GLsizei height, GLsizei depth, GLenum format, 
                           GLenum type, const GLvoid *pixels) =
            (void (OSG_APIENTRY*)(GLenum target, GLint level, GLint xoffset, 
                      GLint yoffset, GLint zoffset, GLsizei width, 
                      GLsizei height, GLsizei depth, GLenum format, 
                      GLenum type, const GLvoid *pixels)) 
            win->getFunction(_funcTexSubImage3D);

        // as we're not allocating anything here, the same code can be used
        // for reinitialization
        if(! img || ! img->getDimension()) // no image ?
            return;

        glErr("TextureChunk::initialize precheck");

        FDEBUG(("texture (re-)initialize\n"));

        // activate the texture
        glBindTexture(bindtarget, id);

        if(paramtarget != GL_NONE)
        {
            // set the parameters
            glTexParameterf(paramtarget, GL_TEXTURE_PRIORITY,   getPriority());
            glTexParameteri(paramtarget, GL_TEXTURE_MIN_FILTER, getMinFilter());
            glTexParameteri(paramtarget, GL_TEXTURE_MAG_FILTER, getMagFilter());
            glTexParameteri(paramtarget, GL_TEXTURE_WRAP_S, getWrapS());
            if(paramtarget == GL_TEXTURE_2D || 
                 paramtarget == GL_TEXTURE_3D ||
                 paramtarget == GL_TEXTURE_CUBE_MAP_ARB
              )
                glTexParameteri(paramtarget, GL_TEXTURE_WRAP_T, getWrapT());
            if(paramtarget == GL_TEXTURE_3D)
                glTexParameteri(paramtarget, GL_TEXTURE_WRAP_R, getWrapR());

            glErr("TextureChunk::initialize params");
        }
        
        // set the image
        GLenum internalFormat = getInternalFormat();
        GLenum externalFormat = img->getPixelFormat();
        GLenum type           = GL_UNSIGNED_BYTE;
        UInt32 width          = img->getWidth();
        UInt32 height         = img->getHeight();
        UInt32 depth          = img->getDepth();

        bool doScale = getScale(); // scale the texture to 2^?
        UInt32 frame = getFrame();

        bool defined = false;   // Texture defined ?
        bool needMipmaps =  getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
                            getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
                            getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
                            getMinFilter() == GL_LINEAR_MIPMAP_LINEAR   ;

	    if(getExternalFormat() != GL_NONE)
	        externalFormat = getExternalFormat();

	    if(internalFormat == GL_NONE)
        {
            switch(externalFormat)
            {
#if defined(GL_BGR) && defined(GL_BGR_EXT)
            case GL_BGR:
#else
#  if defined(GL_BGR)
            case GL_BGR:
#  endif
#  if defined(GL_BGR_EXT)
            case GL_BGR_EXT:
#  endif
#endif
#if defined(GL_BGR) || defined(GL_BGR_EXT)
                            internalFormat = GL_RGB;
                            break;
#endif
#if defined(GL_BGRA) && defined(GL_BGRA_EXT)
            case GL_BGRA:
#else
#  if defined(GL_BGRA)
            case GL_BGRA:
#  endif
#  if defined(GL_BGRA_EXT)
            case GL_BGRA_EXT:
#  endif
#endif
#if defined(GL_BGRA) || defined(GL_BGRA_EXT)
                            internalFormat = GL_RGBA;
                            break;
#endif
            default:    internalFormat = externalFormat;
                        break;
	        }
        }
        
        // do we need mipmaps?
        if(needMipmaps)
        {
            // do we have usable mipmaps ?
            if(img->getMipMapCount() == img->calcMipmapLevelCount() &&
                 osgispower2(width) && osgispower2(height) && 
                 osgispower2(depth)
              )
            {
                for(UInt16 i = 0; i < img->getMipMapCount(); i++)
                {
                    UInt32 w, h, d;
                    img->calcMipmapGeometry(i, w, h, d);

                    switch (imgtarget)
                    {
                    case GL_TEXTURE_1D:
                        glTexImage1D(GL_TEXTURE_1D, i, internalFormat,
                                        w, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
                    case GL_TEXTURE_2D:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                        glTexImage2D(imgtarget, i, internalFormat,
                                        w, h, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
                    case GL_TEXTURE_3D:
                          TexImage3D(GL_TEXTURE_3D, i, internalFormat,
                                        w, h, d, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
                   default:
                            SFATAL << "TextureChunk::initialize1: unknown target "
                                   << imgtarget << "!!!" << std::endl;
                            break;
                    }
                }
                defined = true;
            }

            if(! defined)
            {
                // Nope, try to use gluBuild?DMipmaps
                void * data = NULL;

                // can we use it directly?
                if(! osgispower2(width) ||
                     ! osgispower2(height) ||
                     ! osgispower2(depth)
                  )
                {
                    // scale is only implemented for 2D
                    if(imgtarget != GL_TEXTURE_2D)
                    {
                        SWARNING << "TextureChunk::initialize: can't mipmap "
                                 << "non-2D textures that are not 2^x !!!"
                                 << std::endl;
                    }
                    else
                    {
                        UInt32 outw = osgnextpower2(width);
                        UInt32 outh = osgnextpower2(height);

                        // type is always ubyte right now
                        data = malloc(outw * outh * sizeof(GLubyte) * 4);

                        // should we scale to next power of 2?
                        if(doScale)
                        {
                            GLint res = gluScaleImage(externalFormat,
                                            width, height, type, img->getData(0, frame),
                                            outw, outh, type, data);

                            if(res)
                            {
                                SWARNING << "TextureChunk::initialize: "
                                         << "gluScaleImage failed: "
                                         << gluErrorString(res) << "("
                                         << res << ")!" 
                                         << std::endl;
                                free(data);
                                data = NULL;
                            }
                            else
                            {
                                width = outw;
                                height = outh;
                            }
                        }
                        else // nope, just copy the image to the lower left part
                        {
                            memset(data, 0, outw * outh * sizeof(GLubyte) * 4);

                            UInt16 bpl = width * img->getBpp();
                            UInt8 * src = (UInt8 *) img->getData();
                            UInt8 * dest= (UInt8 *) data;

                            for(int y = 0; y < height; y++)
                            {
                                memcpy(dest, src, bpl);

                                src  += bpl;
                                dest += outw * img->getBpp();
                            }
                            width = outw;
                            height = outh;
                        }
                    }
                }
                else
                    data = img->getData(0, frame);

                if(data)
                {
                    switch (imgtarget)
                    {
                    case GL_TEXTURE_1D:
                            gluBuild1DMipmaps(imgtarget, internalFormat, width,
                                                externalFormat, type, data);
                            break;
                    case GL_TEXTURE_2D:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                            gluBuild2DMipmaps(imgtarget, internalFormat,
                                                width, height,
                                                externalFormat, type, data);
                            break;
                    case GL_TEXTURE_3D:
#  ifdef GLU_VERSION_1_3
                            gluBuild3DMipmaps(imgtarget, internalFormat,
                                                width, height, depth,
                                                externalFormat, type, data);
#  else
                            FWARNING(("TextureChunk::initialize: 3d textures "
                                      "supported, but GLU version < 1.3, thus "
                                      "gluBuild3DMipmaps not supported!\n"));
#  endif
                            break;
                    default:
                            SFATAL << "TextureChunk::initialize2: unknown target "
                                   << imgtarget << "!!!" << std::endl;
                    }

                    if(data != img->getData(0, frame))
                        free(data);
                    defined = true;
                } // data
            } // use gluBuildMipmaps
        } // need mipmaps?

        // no mipmaps, or mipmapping failed?
        if(! defined)
        {
            // got here needing mipmaps?
            if(needMipmaps && paramtarget != GL_NONE)  // turn them off
                glTexParameteri(paramtarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            void * data = NULL;

            // should we scale to next power of 2?
            if(doScale)
            {
                // can we use the texture directly?
                if(! osgispower2(width) ||
                     ! osgispower2(height)
                  )
                {
                    // scale is only implemented for 2D
                    if(imgtarget != GL_TEXTURE_2D &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
                      )
                    {
                        SWARNING << "TextureChunk::initialize: can't scale "
                                 << "non-2D textures that are not 2^x !!!"
                                 << std::endl;
                    }
                    else
                    {
                        UInt32 outw = osgnextpower2(width);
                        UInt32 outh = osgnextpower2(height);

                        // biggest possible: RGBA FLOAT
                        data = malloc(outw * outh * sizeof(GL_FLOAT) * 4);

                        GLint res = gluScaleImage(externalFormat,
                                        width, height, type, img->getData(0, frame),
                                        outw, outh, type, data);

                        if(res)
                        {
                            SWARNING << "TextureChunk::initialize: "
                                     << "gluScaleImage failed: "
                                     << gluErrorString(res) << "("
                                     << res << ")!" << std::endl;
                            free(data);
                            data = NULL;
                        }
                        else
                        {
                            width = outw;
                            height = outh;
                        }
                    }
                }
                else
                    data = img->getData(0, frame);

                if(data)
                {
                    switch (imgtarget)
                    {
                    case GL_TEXTURE_1D:
                        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                        width, 0,
                                        externalFormat, type,
                                        data);
                        break;
                    case GL_TEXTURE_2D:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                        glTexImage2D(imgtarget, 0, internalFormat,
                                        width, height, 0,
                                        externalFormat, type,
                                        data);
                        break;
                    case GL_TEXTURE_3D:
                          TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                        width, height, depth, 0,
                                        externalFormat, type,
                                        data);
                        break;
                    default:
                        SFATAL << "TextureChunk::initialize3: unknown target "
                               << imgtarget << "!!!" << std::endl;
                    }
                }
            }
            else // don't scale, just use ll corner
            {
                switch (imgtarget)
                {
                case GL_TEXTURE_1D:
                    glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                    osgnextpower2(width), 0,
                                    externalFormat, type,
                                    NULL);
                    glTexSubImage1D(GL_TEXTURE_1D, 0, 0, width,
                                    externalFormat, type, 
                                     img->getData(0, frame));
                    break;
                case GL_TEXTURE_2D:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                    glTexImage2D(imgtarget, 0, internalFormat,
                                    osgnextpower2(width), 
                                    osgnextpower2(height), 0,
                                    externalFormat, type,
                                    NULL);
                    glTexSubImage2D(imgtarget, 0, 0, 0, width, height,
                                    externalFormat, type, 
                                    img->getData(0, frame));
                    break;
                case GL_TEXTURE_3D:
                      TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                    osgnextpower2(width), 
                                    osgnextpower2(height), 
                                    osgnextpower2(depth), 
                                    0, externalFormat, type, NULL);
                      TexSubImage3D(GL_TEXTURE_3D, 0,  0, 0, 0,
                                    width, height, depth,
                                    externalFormat, type, 
                                    img->getData(0, frame));
                    break;
                default:
                        SFATAL << "TextureChunk::initialize4: unknown target "
                               << imgtarget << "!!!" << std::endl;
                }
            }

            if(data != img->getData(0, frame))
                free(data);
        }

        glErr("TextureChunk::initialize image");
    }
    else if(mode == Window::needrefresh)
    {
        void (OSG_APIENTRY*TexSubImage3D)
                          (GLenum target, GLint level, GLint xoffset, 
                           GLint yoffset, GLint zoffset, GLsizei width, 
                           GLsizei height, GLsizei depth, GLenum format, 
                           GLenum type, const GLvoid *pixels) =
            (void (OSG_APIENTRY*)(GLenum target, GLint level, GLint xoffset, 
                      GLint yoffset, GLint zoffset, GLsizei width, 
                      GLsizei height, GLsizei depth, GLenum format, 
                      GLenum type, const GLvoid *pixels)) 
            win->getFunction(_funcTexSubImage3D);

        GLenum externalFormat = img->getPixelFormat();

	    if(getExternalFormat() != GL_NONE)
	        externalFormat = getExternalFormat();


        if(! img) // no image ?
            return;

        if(! getScale() || (osgispower2(img->getWidth() ) &&
                            osgispower2(img->getHeight()) &&
                            osgispower2(img->getDepth() )
          )                )
        {
            // activate the texture
            glBindTexture(bindtarget, id);

            switch (imgtarget)
            {
            case GL_TEXTURE_1D:
                glTexSubImage1D(GL_TEXTURE_1D, 0, 0, img->getWidth(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
            case GL_TEXTURE_2D:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                glTexSubImage2D(imgtarget, 0, 0, 0, img->getWidth(),
                                img->getHeight(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
            case GL_TEXTURE_3D:
                  TexSubImage3D(GL_TEXTURE_3D, 0,  0, 0, 0,
                                img->getWidth(),
                                img->getHeight(), img->getDepth(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
            default:
                    SFATAL << "TextureChunk::refresh: unknown target "
                           << imgtarget << "!!!" << std::endl;
            }
            
            if(paramtarget != GL_NONE)
                glTexParameterf(paramtarget, GL_TEXTURE_PRIORITY, 
                                  getPriority());
        }
        else
        {
            SWARNING << "TextureChunk::refresh: not implemented yet for "
                     << "scaling!!!" << std::endl;
        }

        glErr("TextureChunk::refresh image");
    }
}


/*! GL object handler
    create the texture and destroy it
*/
void TextureChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    
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
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh )
    {
        GLenum target;
        
        ImagePtr img = getImage();

        if(img != NullFC) 
        {
           if(img->getDepth() > 1)
           {
              if(win->hasExtension(_extTex3D))
                  target = GL_TEXTURE_3D;
              else
              {
                FWARNING(("TextureChunk::initialize: 3D textures not "
                            "supported for this window!\n"));
                return;
              }
           }
           else if(img->getHeight() > 1)        target = GL_TEXTURE_2D;
           else                                 target = GL_TEXTURE_1D;

           handleTexture(win, id, target, target, target, mode, img);        
        }
    }
    else
    {
        SWARNING << "TextureChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

void TextureChunk::activate( DrawActionBase *action, UInt32 idx )
{
    activateTexture(action->getWindow(), idx);
 
    action->getWindow()->validateGLObject(getGLId());

    ImagePtr img = getImage();
    GLenum target;

    if( img == NullFC || ! img->getDimension()) // no image ?
        return;

    glErr("TextureChunk::activate precheck");
    
    if(img->getDepth() > 1)
    {
        if(action->getWindow()->hasExtension(_extTex3D))
              target = GL_TEXTURE_3D;
        else
        {
            FWARNING(("TextureChunk::activate: 3D textures not "
                        "supported for this window!\n"));
            return;
        }
    }
    else if(img->getHeight() > 1)        target = GL_TEXTURE_2D;
    else                                    target = GL_TEXTURE_1D;


    FDEBUG(("TextureChunk::activate - %d\n", getGLId()));

    glBindTexture(target, getGLId());

    // texture env
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, 
                (GLfloat*)getEnvColor().getValuesRGBA());

#ifdef GL_NV_point_sprite
    if(getPointSprite() &&
       action->getWindow()->hasExtension(_nvPointSprite))
    {
        glTexEnvi(GL_POINT_SPRITE_NV, GL_COORD_REPLACE_NV, GL_TRUE);
    }
#endif
    
    if(getEnvMode() == GL_COMBINE_EXT)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT,  getEnvCombineRGB ());
        glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT,    getEnvScaleRGB   ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT,  getEnvSource0RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT,  getEnvSource1RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_EXT,  getEnvSource2RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, getEnvOperand0RGB()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, getEnvOperand1RGB()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_EXT, getEnvOperand2RGB()); 

        glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, getEnvCombineAlpha ());
        glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE,       getEnvScaleAlpha   ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, getEnvSource0Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, getEnvSource1Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA_EXT, getEnvSource2Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT,getEnvOperand0Alpha());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT,getEnvOperand1Alpha());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA_EXT,getEnvOperand2Alpha());
    }

    handleTextureShader(action->getWindow(), target);

    if(getShaderOperation() != GL_NONE &&
       action->getWindow()->hasExtension(_nvTextureShader) &&
       idx == 0)
    {       
        glEnable(GL_TEXTURE_SHADER_NV);
    }

    glEnable(target);

    glErr("TextureChunk::activate");
}


void TextureChunk::changeFrom(DrawActionBase *action, 
                              StateChunk     *old   , 
                              UInt32          idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;
    
    // If the old one is not a texture chunk, deactivate it and activate
    // ourselves
    // Need to check for exact type, as derived chunks might change
    // different state (e.g. CubeTexture)
    if(getTypeId() != old->getTypeId())
    {
        old->deactivate(action, idx);
        activate(action, idx);
        return;
    }

    TextureChunk *oldp      = dynamic_cast<TextureChunk *>(old);
    
    ImagePtr      img       = getImage();
    GLenum        target;
    GLenum        oldtarget = GL_INVALID_ENUM;

    if(img == NullFC || img->getDimension() == 0)
    {
        oldp->deactivate(action, idx);
        return;
    }
    
    glErr("TextureChunk::changeFrom precheck");
    
    activateTexture(action->getWindow(), idx);
     
    if(img->getDepth() > 1)
    {
        if(action->getWindow()->hasExtension(_extTex3D))
              target = GL_TEXTURE_3D;
        else
        {
            FWARNING(("TextureChunk::changeFrom: 3D textures not "
                        "supported for this window!\n"));
            oldp->deactivate(action, idx);
            return;
        }
    }
    else if(img->getHeight() > 1)
    {
        target = GL_TEXTURE_2D;
    }
    else
    {
        target = GL_TEXTURE_1D;
    }

    if(oldp->getImage() != NullFC)
    {
        if(oldp->getImage()->getDepth() > 1)
        {
            if(action->getWindow()->hasExtension(_extTex3D))
                  oldtarget = GL_TEXTURE_3D;
            else
            {
                FWARNING(("TextureChunk::changeFrom: 3D textures not "
                            "supported for this window!\n"));
                oldp->deactivate(action, idx);
                return;
            }
        }
        else if(oldp->getImage()->getHeight() > 1)
        {
            oldtarget = GL_TEXTURE_2D;
        }
        else
        {
            oldtarget = GL_TEXTURE_1D;
        }

        if(target != oldtarget)
        {
            glDisable(oldtarget);
        }
    }

    action->getWindow()->validateGLObject(getGLId());

    glBindTexture(target, getGLId());

    if(oldp->getEnvMode() != getEnvMode())
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());

    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, 
                    (GLfloat*)getEnvColor().getValuesRGBA());

#ifdef GL_NV_point_sprite
    if(oldp->getPointSprite() != getPointSprite() &&
       action->getWindow()->hasExtension(_nvPointSprite)
      )
    {
        glTexEnvi(GL_POINT_SPRITE_NV, GL_COORD_REPLACE_NV, getPointSprite());
    }
#endif
    
    if(getEnvMode() == GL_COMBINE_EXT)
    {
        glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT,  getEnvCombineRGB ());
        glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT,    getEnvScaleRGB   ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT,  getEnvSource0RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT,  getEnvSource1RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_EXT,  getEnvSource2RGB ()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, getEnvOperand0RGB()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, getEnvOperand1RGB()); 
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_EXT, getEnvOperand2RGB()); 

        glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, getEnvCombineAlpha ());
        glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE,       getEnvScaleAlpha   ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, getEnvSource0Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, getEnvSource1Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA_EXT, getEnvSource2Alpha ());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT,getEnvOperand0Alpha());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT,getEnvOperand1Alpha());
        glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA_EXT,getEnvOperand2Alpha());
    }

    if(target != oldtarget)
    {
        glEnable(target);
    }

    if(action->getWindow()->hasExtension(_nvTextureShader))
    {
        if(      getShaderOperation() != GL_NONE &&
           oldp->getShaderOperation() == GL_NONE    )
        {
            handleTextureShader(action->getWindow(), target);
            if(idx == 0)
                glEnable(GL_TEXTURE_SHADER_NV);
        }
        else if(      getShaderOperation() == GL_NONE &&
                oldp->getShaderOperation() != GL_NONE    )
        {
            glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE);
            if(idx == 0)
                glDisable(GL_TEXTURE_SHADER_NV);
        }
    }

    glErr("TextureChunk::changeFrom");
}

void TextureChunk::deactivate(DrawActionBase *action, UInt32 idx)
{
    ImagePtr img = getImage();
    GLenum target;

    if( img == NullFC || ! img->getDimension())
      return;

    glErr("TextureChunk::deactivate precheck");

    activateTexture(action->getWindow(), idx);

    if(img->getDepth() > 1)
    {
        if(action->getWindow()->hasExtension(_extTex3D))
              target = GL_TEXTURE_3D;
        else
        {
            FWARNING(("TextureChunk::deactivate: 3D textures not "
                        "supported for this window!\n"));
            return;
        }
    }
    else if(img->getHeight() > 1) 
    {       
        target = GL_TEXTURE_2D;
    }
    else
    {                                    
        target = GL_TEXTURE_1D;
    }

    if(getShaderOperation() != GL_NONE &&
       action->getWindow()->hasExtension(_nvTextureShader))
    {
        glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE);
        
        if(idx == 0)
            glDisable(GL_TEXTURE_SHADER_NV);
    }
    
    glDisable(target);

#ifdef GL_NV_point_sprite
    if(getPointSprite() &&
       action->getWindow()->hasExtension(_nvPointSprite)
      )
    {
        glTexEnvi(GL_POINT_SPRITE_NV, GL_COORD_REPLACE_NV, GL_FALSE);
    }
#endif

    glErr("TextureChunk::deactivate");
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TextureChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TextureChunk::operator == (const StateChunk &other) const
{
    TextureChunk const *tother = dynamic_cast<TextureChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    

    bool returnValue =  
        getImage    () == tother->getImage    () &&
        getMinFilter() == tother->getMinFilter() &&
        getMagFilter() == tother->getMagFilter() &&
        getWrapS    () == tother->getWrapS    () &&
        getWrapT    () == tother->getWrapT    () &&
        getWrapR    () == tother->getWrapR    () &&
        getPriority () == tother->getPriority () &&
        getEnvMode  () == tother->getEnvMode  ();

    if(returnValue == true && getEnvMode() == GL_COMBINE_EXT)
    {
        returnValue = 
            getEnvCombineRGB ()   == tother->getEnvCombineRGB   () &&

            getEnvSource0RGB ()   == tother->getEnvSource0RGB   () && 
            getEnvSource1RGB ()   == tother->getEnvSource1RGB   () && 
            getEnvSource2RGB ()   == tother->getEnvSource2RGB   () && 

            getEnvOperand0RGB()   == tother->getEnvOperand0RGB  () && 
            getEnvOperand1RGB()   == tother->getEnvOperand1RGB  () && 
            getEnvOperand2RGB()   == tother->getEnvOperand2RGB  () && 

            getEnvCombineAlpha () == tother->getEnvCombineAlpha () &&

            getEnvSource0Alpha () == tother->getEnvSource0Alpha () &&
            getEnvSource1Alpha () == tother->getEnvSource1Alpha () &&
            getEnvSource2Alpha () == tother->getEnvSource2Alpha () &&

            getEnvOperand0Alpha() == tother->getEnvOperand0Alpha() &&
            getEnvOperand1Alpha() == tother->getEnvOperand1Alpha() &&
            getEnvOperand2Alpha() == tother->getEnvOperand2Alpha();


        returnValue &=
           ((        getEnvScaleRGB  () - tother->getEnvScaleRGB  ()) < Eps) &&
           ((tother->getEnvScaleRGB  () -         getEnvScaleRGB  ()) < Eps) &&
           ((        getEnvScaleAlpha() - tother->getEnvScaleAlpha()) < Eps) &&
           ((tother->getEnvScaleAlpha() -         getEnvScaleAlpha()) < Eps);


    }

    return returnValue;
}

bool TextureChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGTEXTURECHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTURECHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTURECHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

