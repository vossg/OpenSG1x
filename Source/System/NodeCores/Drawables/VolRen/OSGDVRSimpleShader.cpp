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

#include "OSGDVRSimpleShader.h"

#include "OSGDVRVolumeTexture.h"
#include "OSGDVRVolume.h"

OSG_USING_NAMESPACE

/*! \class osg::DVRSimpleShader
 *  Abstract shader class - not to be instantiated. Is intended to be 
 *  stateless - NO FIELDS!!
 */

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRSimpleShader::DVRSimpleShader(void) :
    Inherited   (  ),
    m_nTextureId(-1)
{
}

//! Copy Constructor
DVRSimpleShader::DVRSimpleShader(const DVRSimpleShader &source) :
    Inherited   (source),
    m_nTextureId(    -1)
{
}

//! Destructor
DVRSimpleShader::~DVRSimpleShader(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRSimpleShader::initMethod(void)
{
}

//! react to field changes
void DVRSimpleShader::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRSimpleShader::dump(      UInt32    , 
                           const BitVector ) const
{
    SLOG << "Dump DVRSimpleShader NI" << std::endl;
}


//! Callback to set up shader - register textures here
bool DVRSimpleShader::initialize(DVRVolume      *volume, 
                                 DrawActionBase * /*action*/)
{
    FDEBUG(("DVRSimpleShader::initialize\n"));
    
    m_nTextureId = -1;

    DVRVolumeTexturePtr vol = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    ImagePtr img = vol->getImage();
    
    // Map the size to an index
    
    static Int16 types[] =  { Image::OSG_UINT8_IMAGEDATA,
                              Image::OSG_UINT16_IMAGEDATA,
                              Image::OSG_UINT32_IMAGEDATA,
                              Image::OSG_FLOAT16_IMAGEDATA,
                              Image::OSG_FLOAT32_IMAGEDATA,
                              -1 };
    
    UInt16 type = 0;
    while(types[type] != -1 && types[type] != img->getDataType()) type++;
    
    if(!types[type])
    {
        FWARNING(("DVRSimpleShader::initialize: Image data type %d "
                  "unknown!\n", img->getDataType()));
        type = 0;
    }
    
    if(type > 2) // Ignore float types for now
    {
        FWARNING(("DVRSimpleShader::initialize: Can't do float image types,"
                  " treating as int.\n"));
        type = 0;
    }
    
    
    // Map the pixel format to an index
       
    static Int16 formats[] =  { Image::OSG_L_PF,
                                Image::OSG_LA_PF,
                                Image::OSG_RGBA_DXT1,
                                Image::OSG_RGBA_DXT3,
                                Image::OSG_RGBA_DXT5,
                                Image::OSG_RGBA_PF,
                                Image::OSG_RGB_DXT1,
                                Image::OSG_RGB_PF,
                                -1 };
    
    UInt16 format = 0;
    while(formats[format] != -1 && 
          formats[format] != img->getPixelFormat()) format++;
    
    if(!formats[format])
    {
        FWARNING(("DVRSimpleShader::initialize: Image pixel format %d "
                  "unknown!\n", img->getPixelFormat()));
        format = 0;
    }
    
    if(type > 5) // RGB doesn't have alpha...
    {
        FNOTICE(("DVRSimpleShader::initialize: Image pixel format doesn't "
                 "have alpha! Volume will not be transparent!\n"));
    }

    // Now get the best internal format for the image
    
    static GLenum intfs[8][3] = {
        { GL_INTENSITY, GL_INTENSITY16, GL_INTENSITY16 },
        { GL_LUMINANCE_ALPHA, GL_LUMINANCE16_ALPHA16, GL_LUMINANCE16_ALPHA16 },
        { GL_RGBA, GL_RGBA, GL_RGBA },
        { GL_RGBA, GL_RGBA, GL_RGBA },
        { GL_RGBA, GL_RGBA, GL_RGBA },
        { GL_RGBA, GL_RGBA16, GL_RGBA16 },
        { GL_RGB, GL_RGB, GL_RGB },
        { GL_RGB, GL_RGB16, GL_RGB16 }
        };
                               
    
    m_nTextureId = volume->getTextureManager().registerTexture(
        vol->getImage(),        // image
        intfs[format][type],    // internalFormat
        GL_NONE,                // externalFormat
        1,                      // doBricking
        0,                      // textureStage0
        -1);                    // textureStage1
    
    if(m_nTextureId == -1) 
    {
        SWARNING << "Error registering textures ..." << std::endl;
        return false;
    }
    
    return true;
}


//! Callback before any slice is rendered - setup per volume
void DVRSimpleShader::activate(DVRVolume *volume, DrawActionBase * /*action*/)
{
    //FDEBUG << "DVRSimpleShader::activate\n"));

    glPushAttrib(GL_ENABLE_BIT         | 
                 GL_COLOR_BUFFER_BIT   |
                 GL_STENCIL_BUFFER_BIT |
                 GL_DEPTH_BUFFER_BIT   | 
                 GL_POLYGON_BIT        | 
                 GL_TEXTURE_BIT);

    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    
    glColor4f(1.0,1.0,1.0,1.0); 
	
    if(volume->getDoTextures()) 
    {
        // glDisable(GL_TEXTURE_2D);  
        // glEnable(GL_TEXTURE_3D_EXT);  
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 	
        
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  
    }
}

//! Callback before any brick - state setup per brick
void DVRSimpleShader::brickActivate(DVRVolume      * /*volume*/, 
                                    DrawActionBase * /*action*/, 
                                    Brick          * /*brick */)
{
    //FDEBUG(("DVRSimpleShader::brickActivate\n"));
}

//! Callback after all rendering of the volume is done
void DVRSimpleShader::deactivate(DVRVolume      * /*volume*/, 
                                 DrawActionBase * /*action*/)
{
    FDEBUG(("DVRSimpleShader::deactivate\n"));
    
    glPopAttrib();
}

//! Callback to clean up shader resources
void DVRSimpleShader::cleanup(DVRVolume *volume, DrawActionBase * /*action*/)
{
    if (volume != NULL)
    {
        if (m_nTextureId != -1)
            volume->getTextureManager().unregisterTexture(m_nTextureId);
    }
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
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGDVRSIMPLESHADER_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRSIMPLESHADER_INLINE_CVSID;
}
