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

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLU.h>

#include "OSGDrawActionBase.h"

#include "OSGTextureChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureChunk
    \ingroup StateChunks

The texture chunk class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TextureChunk::cvsid[] = "@(#)$Id: OSGTextureChunk.cpp,v 1.38 2002/06/01 10:37:25 vossg Exp $";

StateChunkClass TextureChunk::_class("Texture", 4);

UInt32 TextureChunk::_extTex3D;
UInt32 TextureChunk::_arbMultiTex;
UInt32 TextureChunk::_funcTexImage3D    = TypeConstants<UInt32>::getMax();
UInt32 TextureChunk::_funcTexSubImage3D = TypeConstants<UInt32>::getMax();

// define GL_TEXTURE_3D, if not defined yet
#ifndef GL_VERSION_1_2
#  ifdef GL_EXT_texture3D
#    define GL_TEXTURE_3D GL_TEXTURE_3D_EXT
#    define GL_FUNC_TEXIMAGE3D    "glTexImage3DEXT"
#    define GL_FUNC_TEXSUBIMAGE3D "glTexSubImage3DEXT"
#  else
#    define GL_FUNC_TEXIMAGE3D    NULL
#    define GL_FUNC_TEXSUBIMAGE3D NULL
#  endif
#else
#  define GL_FUNC_TEXIMAGE3D    "glTexImage3D"
#  define GL_FUNC_TEXSUBIMAGE3D "glTexSubImage3D"
#endif


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void TextureChunk::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

// this should go somewhere central...

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

TextureChunk::TextureChunk(void) :
    Inherited()
{
    _extTex3D          = Window::registerExtension( "GL_EXT_texture3D" );
    _arbMultiTex       = Window::registerExtension( "GL_ARB_multitexture" );
    _funcTexImage3D    = Window::registerFunction ( GL_FUNC_TEXIMAGE3D );
    _funcTexSubImage3D = Window::registerFunction ( GL_FUNC_TEXSUBIMAGE3D );
}

/** \brief Copy Constructor
 */

TextureChunk::TextureChunk(const TextureChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

TextureChunk::~TextureChunk(void)
{
}


/** \brief react to field changes
 */

void TextureChunk::changed(BitVector fields, UInt32)
{
    if(fields & ImageFieldMask)
    {
        Window::reinitializeGLObject(getGLId());
    }
    else if((fields & ~(MinFilterFieldMask | MagFilterFieldId)) == 0)
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
    else
    {
        Window::reinitializeGLObject(getGLId());
    }
}

bool TextureChunk::isTransparent(void) const
{
    bool returnValue = false;

    if(getImage() != NULL)
    {
        returnValue = getImage()->hasAlphaChannel();
    }

    return returnValue;
}


/*----------------------------- onCreate --------------------------------*/

/** \brief instance initialization
 */

void TextureChunk::onCreate(const TextureChunk *)
{
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


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void TextureChunk::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                        const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump TextureChunk NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

// GL object handler
// create the texture and destroy it
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
        //SWARNING << "Last texture user destroyed" << endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize)
    {
        if(mode == Window::reinitialize)
        {
            GLuint tex = id;
            glDeleteTextures(1, &tex);
        }
        
        // 3D texture functions
        void (*TexImage3D)(GLenum target, GLint level, GLenum internalformat, 
                           GLsizei width, GLsizei height, GLsizei depth, 
                           GLint border, GLenum format, GLenum type, 
                           const GLvoid *pixels) = 
            (void (*)(GLenum target, GLint level, GLenum internalformat, 
                      GLsizei width, GLsizei height, GLsizei depth, 
                      GLint border, GLenum format, GLenum type, 
                      const GLvoid *pixels))
#ifdef GL_TEXTURE_3D
            win->getFunction(_funcTexImage3D);
#else
            NULL;
#endif                         
        void (*TexSubImage3D)
                          (GLenum target, GLint level, GLint xoffset, 
                           GLint yoffset, GLint zoffset, GLsizei width, 
                           GLsizei height, GLsizei depth, GLenum format, 
                           GLenum type, const GLvoid *pixels) =
            (void (*)(GLenum target, GLint level, GLint xoffset, 
                      GLint yoffset, GLint zoffset, GLsizei width, 
                      GLsizei height, GLsizei depth, GLenum format, 
                      GLenum type, const GLvoid *pixels)) 
#ifdef GL_TEXTURE_3D
            win->getFunction(_funcTexSubImage3D);
#else
            NULL;
#endif                         
        // as we're not allocating anything here, the same code can be used
        // for reinitialization
        ImageP img = getImage();

        if(! img || ! img->getDimension()) // no image ?
            return;

        glErr("TextureChunk::initialize precheck");

        GLenum target;
        if(img->getDepth() > 1)
        {
#ifdef GL_TEXTURE_3D
            if(win->hasExtension(_extTex3D))
                  target = GL_TEXTURE_3D;
            else
            {
                FWARNING(("TextureChunk::initialize: 3D textures not "
                            "supported for this window!\n"));
                return;
            }
#else
            FWARNING(("TextureChunk::initialize: 3D textures not "
                            "supported for this executable!\n"));
            return;
#endif
        }
        else if(img->getHeight() > 1)        target = GL_TEXTURE_2D;
        else                                    target = GL_TEXTURE_1D;


        FDEBUG(("texture (re-)initialize\n"));

        // activate the texture
        glBindTexture(target, id);

        // set the parameters
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, getMinFilter());
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, getMagFilter());
        glTexParameteri(target, GL_TEXTURE_WRAP_S, getWrapS());
        if(target == GL_TEXTURE_2D || 
#ifdef GL_TEXTURE_3D
             target == GL_TEXTURE_3D 
#else
             true
#endif
          )
            glTexParameteri(target, GL_TEXTURE_WRAP_T, getWrapT());
#ifdef GL_TEXTURE_3D
#ifdef GL_TEXTURE_WRAP_R_EXT
        if(target == GL_TEXTURE_3D)
            glTexParameteri(target, GL_TEXTURE_WRAP_R_EXT, getWrapR());
#else
        if(target == GL_TEXTURE_3D)
            glTexParameteri(target, GL_TEXTURE_WRAP_R, getWrapR());
#endif
#endif

        glErr("TextureChunk::initialize params");

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

	if ( getExternalFormat() != GL_NONE )
	    externalFormat = getExternalFormat();

	if ( internalFormat == GL_NONE )
            internalFormat = externalFormat;
	
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

                    switch (target)
                    {
                    case GL_TEXTURE_1D:
                        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                        w, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
                    case GL_TEXTURE_2D:
                        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                                        w, h, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
#ifdef GL_TEXTURE_3D
                    case GL_TEXTURE_3D:
                          TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                        w, h, d, 0,
                                        externalFormat, type,
                                        img->getData(i, frame));
                        break;
#endif
                    default:
                            SFATAL << "TextureChunk::initialize1: unknown target "
                                   << target << "!!!" << endl;
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
                    if(target != GL_TEXTURE_2D)
                    {
                        SWARNING << "TextureChunk::initialize: can't mipmap "
                                 << "non-2D textures that are not 2^x !!!"
                                 << endl;
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
                                         << res << ")!" << endl;
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
                    switch (target)
                    {
                    case GL_TEXTURE_1D:
                            gluBuild1DMipmaps(target, internalFormat, width,
                                                externalFormat, type, data);
                            break;
                    case GL_TEXTURE_2D:
                            gluBuild2DMipmaps(target, internalFormat,
                                                width, height,
                                                externalFormat, type, data);
                            break;
#ifdef GL_TEXTURE_3D
                    case GL_TEXTURE_3D:
#  ifdef GLU_VERSION_1_3
                            gluBuild3DMipmaps(target, internalFormat,
                                                width, height, depth,
                                                externalFormat, type, data);
#  else
                            FWARNING(("TextureChunk::initialize: 3d textures "
                                      "supported, but GLU version < 1.3, thus "
                                      "gluBuild3DMipmaps not supported!\n"));
#  endif
                            break;
#endif
                    default:
                            SFATAL << "TextureChunk::initialize2: unknown target "
                                   << target << "!!!" << endl;
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
            if(needMipmaps)  // turn them off
                glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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
                    if(target != GL_TEXTURE_2D)
                    {
                        SWARNING << "TextureChunk::initialize: can't scale "
                                 << "non-2D textures that are not 2^x !!!"
                                 << endl;
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
                                     << res << ")!" << endl;
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
                    switch (target)
                    {
                    case GL_TEXTURE_1D:
                        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                        width, 0,
                                        externalFormat, type,
                                        data);
                        break;
                    case GL_TEXTURE_2D:
                        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                                        width, height, 0,
                                        externalFormat, type,
                                        data);
                        break;
#ifdef GL_TEXTURE_3D
                    case GL_TEXTURE_3D:
                          TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                        width, height, depth, 0,
                                        externalFormat, type,
                                        data);
                        break;
#endif
                    default:
                        SFATAL << "TextureChunk::initialize3: unknown target "
                               << target << "!!!" << endl;
                    }
                }
            }
            else // don't scale, just use ll corner
            {
                switch (target)
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
                    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                                    osgnextpower2(width), 
                                    osgnextpower2(height), 0,
                                    externalFormat, type,
                                    NULL);
                    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
                                    externalFormat, type, 
                                    img->getData(0, frame));
                    break;
#ifdef GL_TEXTURE_3D
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
#endif
                    break;
                default:
                        SFATAL << "TextureChunk::initialize4: unknown target "
                               << target << "!!!" << endl;
                }

            }

            if(data != img->getData(0, frame))
                free(data);
        }

        glErr("TextureChunk::initialize image");
    }
    else if(mode == Window::needrefresh)
    {
        void (*TexSubImage3D)
                          (GLenum target, GLint level, GLint xoffset, 
                           GLint yoffset, GLint zoffset, GLsizei width, 
                           GLsizei height, GLsizei depth, GLenum format, 
                           GLenum type, const GLvoid *pixels) =
            (void (*)(GLenum target, GLint level, GLint xoffset, 
                      GLint yoffset, GLint zoffset, GLsizei width, 
                      GLsizei height, GLsizei depth, GLenum format, 
                      GLenum type, const GLvoid *pixels)) 
#ifdef GL_TEXTURE_3D
            win->getFunction(_funcTexSubImage3D);
#else
            NULL;
#endif                         

        ImageP img = getImage();
        GLenum externalFormat = img->getPixelFormat();

	if ( getExternalFormat() != GL_NONE )
	    externalFormat = getExternalFormat();


        if(! img) // no image ?
            return;

        if(! getScale() || (osgispower2(img->getWidth() ) &&
                               osgispower2(img->getHeight()) &&
                               osgispower2(img->getDepth())
          )                )
        {
            GLenum target;
            if(img->getDepth() > 1)
            {
#ifdef GL_TEXTURE_3D
                if(win->hasExtension(_extTex3D))
                      target = GL_TEXTURE_3D;
                else
                {
                    FWARNING(("TextureChunk::refresh: 3D textures not "
                                "supported for this window!\n"));
                    return;
                }
#else
                FWARNING(("TextureChunk::refresh: 3D textures not "
                            "supported for this executable!\n"));
                return;            
#endif
            }
            else if(img->getHeight() > 1)        target = GL_TEXTURE_2D;
            else                                    target = GL_TEXTURE_1D;

            // activate the texture
            glBindTexture(target, id);

            switch (target)
            {
            case GL_TEXTURE_1D:
                glTexSubImage1D(GL_TEXTURE_1D, 0, 0, img->getWidth(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
            case GL_TEXTURE_2D:
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img->getWidth(),
                                img->getHeight(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
#ifdef GL_TEXTURE_3D
            case GL_TEXTURE_3D:
                  TexSubImage3D(GL_TEXTURE_3D, 0,  0, 0, 0,
                                img->getWidth(),
                                img->getHeight(), img->getDepth(),
                                externalFormat, GL_UNSIGNED_BYTE,
                                img->getData( 0, getFrame() ) );
                break;
#endif
            default:
                    SFATAL << "TextureChunk::refresh: unknown target "
                           << target << "!!!" << endl;
            }
        }
        else
        {
            SWARNING << "TextureChunk::refresh: not implemented yet for "
                     << "scaling!!!" << endl;
        }

        glErr("TextureChunk::refresh image");
    }
    else
    {
        SWARNING << "TextureChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << endl;
    }

}

// little helper macro to activate genfuncs
#define setGenFunc(func, genfunc, getfunc, getplane)                  \
    if(getfunc() != GL_NONE)                                         \
    {                                                                   \
        GLfloat p[4] = { getplane()[0],                                 \
                         getplane()[1],                                 \
                         getplane()[2],                                 \
                         getplane()[3] };                               \
        glTexGeni(func, GL_TEXTURE_GEN_MODE, getfunc());              \
        if(getfunc() == GL_OBJECT_LINEAR)                            \
            glTexGenfv(func, GL_OBJECT_PLANE, p);                     \
        else if(getfunc() == GL_EYE_LINEAR)                          \
            glTexGenfv(func, GL_EYE_PLANE, p);                        \
        glEnable(genfunc);                                            \
    }

#if defined(GL_ARB_multitexture)
void TextureChunk::activate( DrawActionBase *action, UInt32 idx )
#else
void TextureChunk::activate( DrawActionBase *action, UInt32 )
#endif
{
    action->getWindow()->validateGLObject(getGLId());

    ImageP img = getImage();
    GLenum target;

    if(! img || ! img->getDimension()) // no image ?
        return;

    glErr("TextureChunk::activate precheck");

    
#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
          glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif

    
    if ( img->getDepth() > 1 )
    {
#ifdef GL_TEXTURE_3D
            if(action->getWindow()->hasExtension(_extTex3D))
                  target = GL_TEXTURE_3D;
            else
            {
                FWARNING(("TextureChunk::activate: 3D textures not "
                            "supported for this window!\n"));
                return;
            }
#else
            FWARNING(("TextureChunk::activate: 3D textures not "
                            "supported for this executable!\n"));
            return;
#endif
    }
    else if(img->getHeight() > 1)        target = GL_TEXTURE_2D;
    else                                    target = GL_TEXTURE_1D;


    FDEBUG(("TextureChunk::activate - %d\n", getGLId()));

    glBindTexture(target, getGLId());

    // texture env
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());

    // register combiners etc. goes here

    // genfuncs
    setGenFunc(GL_S, GL_TEXTURE_GEN_S, getGenFuncS, getGenFuncSPlane);
    setGenFunc(GL_T, GL_TEXTURE_GEN_T, getGenFuncT, getGenFuncTPlane);
    setGenFunc(GL_R, GL_TEXTURE_GEN_R, getGenFuncR, getGenFuncRPlane);
    setGenFunc(GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ, getGenFuncQPlane);

    glEnable(target);

    glErr("TextureChunk::activate");
}


#define changeGenFunc(func, genfunc, getfunc, getplane)              \
    if(getfunc() != GL_NONE)                                         \
    {                                                                \
        GLfloat p[4] = { getplane()[0],                              \
                         getplane()[1],                              \
                         getplane()[2],                              \
                         getplane()[3] };                            \
        glTexGeni(func, GL_TEXTURE_GEN_MODE, getfunc());             \
        if(getfunc() == GL_OBJECT_LINEAR)                            \
            glTexGenfv(func, GL_OBJECT_PLANE, p);                    \
        else if(getfunc() == GL_EYE_LINEAR)                          \
            glTexGenfv(func, GL_EYE_PLANE, p);                       \
        if(oldp->getfunc() == GL_NONE)                               \
            glEnable(genfunc);                                       \
    }                                                                \
    else if(oldp->getfunc() != GL_NONE)                              \
        glDisable(genfunc)

void TextureChunk::changeFrom(DrawActionBase *action, 
                              StateChunk     *old   , 
#if defined(GL_ARB_multitexture)
                              UInt32          idx )
#else
                              UInt32 )
#endif
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    TextureChunk *oldp      = dynamic_cast<TextureChunk *>(old);
    ImageP        img       = getImage();
    GLenum        target;
    GLenum        oldtarget = GL_INVALID_ENUM;

    if(img == NULL || img->getDimension() == 0)
      return;

    glErr("TextureChunk::changeFrom precheck");

    
#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
          glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif

     
    if(img->getDepth() > 1)
    {
#ifdef GL_TEXTURE_3D
        if(action->getWindow()->hasExtension(_extTex3D))
              target = GL_TEXTURE_3D;
        else
        {
            FWARNING(("TextureChunk::changeFrom: 3D textures not "
                        "supported for this window!\n"));
            return;
        }
#else
        FWARNING(("TextureChunk::changeFrom: 3D textures not "
                        "supported for this executable!\n"));
        return;
#endif
    }
    else if(img->getHeight() > 1)
    {
        target = GL_TEXTURE_2D;
    }
    else
    {
        target = GL_TEXTURE_1D;
    }

    if(oldp->getImage() != NULL)
    {
        if(oldp->getImage()->getDepth() > 1)
        {
#ifdef GL_TEXTURE_3D
            if(action->getWindow()->hasExtension(_extTex3D))
                  oldtarget = GL_TEXTURE_3D;
            else
            {
                FWARNING(("TextureChunk::changeFrom: 3D textures not "
                            "supported for this window!\n"));
                return;
            }
#else
            FWARNING(("TextureChunk::changeFrom: 3D textures not "
                            "supported for this executable!\n"));
            return;
#endif
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

    changeGenFunc(GL_S, GL_TEXTURE_GEN_S, getGenFuncS, getGenFuncSPlane);
    changeGenFunc(GL_T, GL_TEXTURE_GEN_T, getGenFuncT, getGenFuncTPlane);
    changeGenFunc(GL_R, GL_TEXTURE_GEN_R, getGenFuncR, getGenFuncRPlane);
    changeGenFunc(GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ, getGenFuncQPlane);

    if(target != oldtarget)
    {
        glEnable(target);
    }

    glErr("TextureChunk::changeFrom");
}

void TextureChunk::deactivate ( DrawActionBase *action,
#if defined(GL_ARB_multitexture)
                                UInt32 idx )
#else
                                UInt32 )
#endif
{
    ImageP img = getImage();
    GLenum target;

    if(! img || ! img->getDimension())
      return;

    glErr("TextureChunk::deactivate precheck");


#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
          glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif

    if ( img->getDepth() > 1 )
    {
#ifdef GL_TEXTURE_3D
        if(action->getWindow()->hasExtension(_extTex3D))
              target = GL_TEXTURE_3D;
        else
        {
            FWARNING(("TextureChunk::deactivate: 3D textures not "
                        "supported for this window!\n"));
            return;
        }
#else
        FWARNING(("TextureChunk::deactivate: 3D textures not "
                        "supported for this executable!\n"));
        return;
#endif
    }
    else if(img->getHeight() > 1) 
    {       
        target = GL_TEXTURE_2D;
    }
    else
    {                                    
        target = GL_TEXTURE_1D;
    }
    
    glDisable(target);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_S);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_T);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_R);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_Q);

    glErr("TextureChunk::deactivate");
}

/*-------------------------- comparison -----------------------------------*/

Real32 TextureChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool TextureChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool TextureChunk::operator == (const StateChunk &other) const
{
    TextureChunk const *tother = dynamic_cast<TextureChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return getImage()       == tother->getImage() &&
            getMinFilter()  == tother->getMinFilter() &&
            getMagFilter()  == tother->getMagFilter() &&
            getWrapS()      == tother->getWrapS() &&
            getWrapT()      == tother->getWrapT() &&
            getWrapR()      == tother->getWrapR() &&
            getEnvMode()    == tother->getEnvMode() &&
            getGenFuncS()   == tother->getGenFuncS() &&
            getGenFuncT()   == tother->getGenFuncT() &&
            getGenFuncR()   == tother->getGenFuncR() &&
            getGenFuncQ()   == tother->getGenFuncQ() &&
            // not quite right. needs only to be tested for genfuncs using them
            getGenFuncSPlane()  == tother->getGenFuncSPlane() &&
            getGenFuncTPlane()  == tother->getGenFuncTPlane() &&
            getGenFuncRPlane()  == tother->getGenFuncRPlane() &&
            getGenFuncQPlane()  == tother->getGenFuncQPlane() ;
}

/** \brief unequal
 */

bool TextureChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

