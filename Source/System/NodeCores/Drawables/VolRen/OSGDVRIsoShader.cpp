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
#include <OSGGLEXT.h>
#include <OSGSlicer.h>
#include <OSGGLU.h>

#include "OSGDVRIsoShader.h"

OSG_USING_NAMESPACE


// register extensions and initialize extension functions

UInt32 DVRIsoShader::_ARB_multitexture       = Window::invalidExtensionID;
UInt32 DVRIsoShader::_EXT_texture3D          = Window::invalidExtensionID;
UInt32 DVRIsoShader::_NV_register_combiners  = Window::invalidExtensionID;
UInt32 DVRIsoShader::_NV_register_combiners2 = Window::invalidExtensionID;
UInt32 DVRIsoShader::_SGI_color_matrix       = Window::invalidExtensionID;
UInt32 DVRIsoShader::_ARB_fragment_program   = Window::invalidExtensionID;
UInt32 DVRIsoShader::_EXT_secondary_color    = Window::invalidExtensionID;


UInt32 DVRIsoShader::_funcActiveTextureARB            =  
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcMultiTexCoord2dARB          = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcTexImage3DEXT               = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcCombinerParameteriNV        = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcCombinerParameterfvNV       = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcCombinerStageParameterfvNV  = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcSecondaryColor3fEXT         = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcSecondaryColor3fvEXT        = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcCombinerInputNV             = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcCombinerOutputNV            = 
    Window::invalidFunctionID;

UInt32 DVRIsoShader::_funcFinalCombinerInputNV        = 
    Window::invalidFunctionID;

/*! \class osg::DVRIsoShader
  Simple iso surface shader
*/

/*----------------------- constructors & destructors ----------------------*/

#ifndef GL_VERSION_1_2
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3DEXT"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3DEXT"
#else
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3D"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3D"
#endif

//! Constructor
DVRIsoShader::DVRIsoShader(void) :
    Inherited()
{
    m_gradientImage = NullFC;
    m_shadingMode   = SM_NONE;
    m_pFragProg     = NullFC;
    m_textureId     = -1;

    // Do this here, will change in future for OpenSG as a whole
    _ARB_multitexture       = 
        Window::registerExtension("GL_ARB_multitexture"      );

    _EXT_texture3D          = 
        Window::registerExtension("GL_EXT_texture3D"         );

    _EXT_secondary_color     = 
        Window::registerExtension("GL_EXT_secondary_color"   );

    _NV_register_combiners  = 
        Window::registerExtension("GL_NV_register_combiners" );

    _NV_register_combiners2 = 
        Window::registerExtension("GL_NV_register_combiners2");

    _SGI_color_matrix       = 
        Window::registerExtension("GL_SGI_color_matrix"      );

    _ARB_fragment_program   = 
        Window::registerExtension("GL_ARB_fragment_program"  );


    _funcActiveTextureARB            =  
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glActiveTextureARB",    
                                _ARB_multitexture);

    _funcMultiTexCoord2dARB          = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glMultiTexCoord2dARB",    
                                _ARB_multitexture);

    _funcTexImage3DEXT               = 
       Window::registerFunction(GL_FUNC_TEXIMAGE3D,    
                                _EXT_texture3D, 0x0102);

    _funcCombinerParameteriNV        = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glCombinerParameteriNV",    
                                _NV_register_combiners);
    
    _funcCombinerParameterfvNV       = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glCombinerParameterfvNV",    
                                _NV_register_combiners);

    _funcCombinerStageParameterfvNV  = 
       Window::registerFunction(
           OSG_DLSYM_UNDERSCORE"glCombinerStageParameterfvNV",    
                                _NV_register_combiners);

    _funcSecondaryColor3fEXT         = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glSecondaryColor3fEXT",    
                                _EXT_secondary_color);

    _funcSecondaryColor3fvEXT        = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glSecondaryColor3fvEXT",    
                                _EXT_secondary_color);

    _funcCombinerInputNV             = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glCombinerInputNV",    
                                _NV_register_combiners);

    _funcCombinerOutputNV            = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glCombinerOutputNV",    
                                _NV_register_combiners);

    _funcFinalCombinerInputNV        = 
       Window::registerFunction(OSG_DLSYM_UNDERSCORE"glFinalCombinerInputNV",    
                                _NV_register_combiners);

}

//! Copy Constructor
DVRIsoShader::DVRIsoShader(const DVRIsoShader &source) :
    Inherited(source)
{  
    m_gradientImage = NullFC;
    m_shadingMode = SM_NONE;
    m_pFragProg = NullFC;
    m_textureId = -1;
}

//! Destructor
DVRIsoShader::~DVRIsoShader(void)
{
    if(m_pFragProg != NullFC) 
    {
        subRefCP(m_pFragProg);

        m_pFragProg = NullFC;
    }

    if(m_gradientImage != NullFC) 
    {
        subRefCP(m_gradientImage);

        m_gradientImage = NullFC;
    }

    m_textureId = -1;
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRIsoShader::initMethod(void)
{
}

//! react to field changes

void DVRIsoShader::changed(BitVector whichField, UInt32 origin)
{
    // trigger re-initialization
    if(whichField & ShadeModeFieldMask)
        setActiveShadeMode(SM_AUTO);
    
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRIsoShader::dump(      UInt32    , 
                        const BitVector ) const
{
    SLOG << "Dump DVRIsoShader NI" << std::endl;
}

// Callback to set up shader - register textures here
bool DVRIsoShader::initialize(DVRVolume *volume, DrawActionBase *action)
{  

    DVRVolumeTexturePtr vol = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);
  
    if((volume == NULL) || (vol == NullFC)) 
    {
        SWARNING << "DVRIsoShader - NO Volume" << std::endl;
        return false;
    }

    // Determine shading mechanism
    tryMode(volume, action, getShadeMode());

    GLenum nInternalFormat = GL_RGBA;
    GLenum nExternalFormat = GL_RGBA;

    // create gradient texture
    if(m_gradientImage != NullFC)
        subRefCP(m_gradientImage);

    m_gradientImage = createGradientImage(vol);

    addRefCP(m_gradientImage);
  
    if((m_shadingMode == SM_REGISTER_COMBINERS_MULTI2D) || 
       (m_shadingMode == SM_FRAGMENT_PROGRAM_2D       )  )
    {
        // init multitexture 
        m_textureId = volume->getTextureManager().registerTexture(
            m_gradientImage, 
            nInternalFormat, 
            nExternalFormat,                      
            true,
            0,
            1);
    }
    else
    {
        // init single texture
        m_textureId = volume->getTextureManager().registerTexture(
            m_gradientImage, 
            nInternalFormat, 
            nExternalFormat,
            true,
            0,
            -1);
    }
    
    if( m_textureId < 0)
    {
        SWARNING << "DVRIsoShader - Could not register texture: "
                 << m_textureId 
                 << std::endl; 

        subRefCP(m_gradientImage);

        return false;
    }
    
    return true;
}


// Callback before any slice is rendered - setup per volume
void DVRIsoShader::activate(DVRVolume *volume, DrawActionBase *action)
{
    // reinitialize if hardware mode has not yet been chosen or mode 
    // has changed

    if(getActiveShadeMode() == SM_AUTO) 
    {
        cleanup   (volume, action);
        initialize(volume, action);
        
        // notify volume about shader changed
        beginEditCP(DVRVolumePtr(volume), DVRVolume::ShaderFieldMask);
        endEditCP(DVRVolumePtr  (volume), DVRVolume::ShaderFieldMask);
    }

    switch(m_shadingMode)
    {
        case SM_COLORMATRIX_2D:
        case SM_COLORMATRIX_3D:
            activate_ColorMatrixShading(volume, action);
            break;

        case SM_REGISTER_COMBINERS_2D:
        case SM_REGISTER_COMBINERS_MULTI2D:
        case SM_REGISTER_COMBINERS_3D: 
            activate_NVRegisterCombinerShading(volume, action);
            break;

        case SM_FRAGMENT_PROGRAM_2D: 
        case SM_FRAGMENT_PROGRAM_3D:
            activate_FragmentProgramShading(volume, action);
            break;

        case SM_NONE:
        default:
            break;
    }
}


// Callback before any brick - state setup per brick
void DVRIsoShader::brickActivate(DVRVolume *, DrawActionBase *, Brick *)
{
    FDEBUG(("DVRIsoShader::brickActivate - nothing to do\n"));  
}


// Callback after all rendering of the volume is done
void DVRIsoShader::deactivate(DVRVolume *volume, DrawActionBase *action)
{
    switch(m_shadingMode)
    {
        case SM_COLORMATRIX_2D:
        case SM_COLORMATRIX_3D:
            deactivate_ColorMatrixShading(volume, action);
            break;

        case SM_REGISTER_COMBINERS_2D:
        case SM_REGISTER_COMBINERS_MULTI2D:
        case SM_REGISTER_COMBINERS_3D:
            deactivate_NVRegisterCombinerShading(volume, action);
            break;

        case SM_FRAGMENT_PROGRAM_2D: 
        case SM_FRAGMENT_PROGRAM_3D:
            deactivate_FragmentProgramShading(volume, action);
            break;

        case SM_NONE:
        default:
            break;
    }
}


// Callback to clean up shader resources
void DVRIsoShader::cleanup(DVRVolume *volume, DrawActionBase *)
{
    if(m_pFragProg != NullFC) 
    {
        subRefCP(m_pFragProg);

        m_pFragProg = NullFC;
    }

    if(m_gradientImage != NullFC) 
    {
        subRefCP(m_gradientImage);

        m_gradientImage = NullFC;        
    }
    
    if (m_textureId != -1)
    {
        volume->getTextureManager().unregisterTexture(m_textureId);
    }
}


// Own function for rendering a slice, only needed for 2D texturing with 
// slice interpolation, otherwise this is done by the volume
void DVRIsoShader::renderSlice(DVRVolume      *volume, 
                               DrawActionBase *action,
                               Real32         *data, 
                               UInt32          vertices, 
                               UInt32          values  )
{
    switch(m_shadingMode)
    {
        case SM_REGISTER_COMBINERS_MULTI2D:
            renderSlice_NVRegisterCombinerShading(volume,
                                                  action,
                                                  data,
                                                  vertices,
                                                  values);
            break;

        case SM_FRAGMENT_PROGRAM_2D:
            renderSlice_FragmentProgramShading(volume,
                                               action,
                                               data,
                                               vertices,
                                               values);
            break;
        default:
            break;
    }
}


// Callback for rendering clipped slices
void DVRIsoShader::renderSlice(DVRVolume      *volume, 
                               DrawActionBase *action,
                               DVRRenderSlice *clippedSlice) 
{
    switch(m_shadingMode)
    {
        case SM_REGISTER_COMBINERS_MULTI2D:
            renderSlice_NVRegisterCombinerShading(volume,action,clippedSlice);
            break;

        case SM_FRAGMENT_PROGRAM_2D:
            renderSlice_FragmentProgramShading(volume,action,clippedSlice);
            break;

        default:
            break;
     }
}


// Indicate whether a private function for rendering a slice should be 
// used or not only needed for 2D texturing with slice interpolation
bool DVRIsoShader::hasRenderCallback(void) 
{
    switch(m_shadingMode)
    {
        case SM_REGISTER_COMBINERS_MULTI2D:
            return true;

        case SM_FRAGMENT_PROGRAM_2D:
            return true;

        default:
            break;
    }

    return false;
}


// Indicate whether slices should be multitextured or not
bool DVRIsoShader::useMTSlabs(void)
{
    switch(m_shadingMode)
    {
        case SM_REGISTER_COMBINERS_MULTI2D:
            return true;

        case SM_FRAGMENT_PROGRAM_2D:
            return true;

        default:
            break;
    }

    return false;
}


// Compute gradients from a 3D volume
ImagePtr DVRIsoShader::createGradientImage(DVRVolumeTexturePtr volTex)
{ 
    int resX = (int) volTex->getImage()->getWidth(); 
    int resY = (int) volTex->getImage()->getHeight(); 
    int resZ = (int) volTex->getImage()->getDepth(); 
    
    int nGradSetSize =   resX * resY * resZ * 4; 
    int zOff         =   resX * resY; 
    int yOff         =   resX;
    
    
    //  Compute the Gradients  
    UChar8 *volData = volTex->getImage()->getData();
  
    UChar8 *gradbuffer = new UChar8[nGradSetSize];  

    Vec3f gradient;

    for(int z = 0 ; z < resZ ; z++) 
    { 
        for(int y = 0 ; y < resY ; y++) 
        { 
            for(int x = 0 ; x < resX ; x++) 
            { 
                
                if(x == 0)
                {
                    gradient = Vec3f(-1.0, 0.0, 0.0);
                } 
                else if (x == resX-1) 
                {
                    gradient = Vec3f( 1.0, 0.0, 0.0);
                } 
                else if (y == 0) 
                {
                    gradient = Vec3f(0.0, -1.0, 0.0);
                }
                else if (y == resY-1) 
                {
                    gradient = Vec3f(0.0,  1.0, 0.0);
                } 
                else if (z == 0) 
                {
                    gradient = Vec3f(0.0, 0.0, -1.0);
                } else if (z == resZ-1) 
                {
                    gradient = Vec3f(0.0, 0.0,  1.0);
                } 
                else 
                {
                    UChar8 &dataXl = 
                        volData[z      * zOff +  y      * yOff + x - 1]; 

                    UChar8 &dataXr = 
                        volData[z      * zOff +  y      * yOff + x + 1]; 

                    UChar8 &dataYb = 
                        volData[z      * zOff + (y - 1) * yOff + x    ]; 

                    UChar8 &dataYt = 
                        volData[z      * zOff + (y + 1) * yOff + x    ]; 

                    UChar8 &dataZf = 
                        volData[(z - 1) * zOff +  y      * yOff + x    ]; 

                    UChar8 &dataZn = 
                        volData[(z + 1) * zOff +  y      * yOff + x    ]; 
					
                    gradient = Vec3f((float)(dataXl - dataXr), 
                                     (float)(dataYb - dataYt), 
                                     (float)(dataZf - dataZn));  

                    if(gradient.length() != 0.0)
                        gradient.normalize(); 
                    
                } 
		
                gradbuffer[4 * (z * zOff + y * yOff + x)  ] 
                    = (UChar8) (127.0 + gradient[0] * 127.0); // R 

                gradbuffer[4 * (z * zOff + y * yOff + x) + 1] 
                    = (UChar8) (127.0 + gradient[1] * 127.0); // G 

                gradbuffer[4 * (z * zOff + y * yOff + x) + 2] 
                    = (UChar8) (127.0 + gradient[2] * 127.0); // B 

                gradbuffer[4 * (z * zOff + y * yOff + x) + 3] 
                    = volData[z * zOff +  y    * yOff + x  ]; // A 

            } // for x 
            
        } // for y 
        
    } // for z 
    
    ImagePtr m_gradientImage = Image::create();

    m_gradientImage->set(Image::OSG_RGBA_PF,
                         resX, 
                         resY, 
                         resZ,
                         1, 
                         1, 
                         0.0, 
                         gradbuffer);

    delete [] gradbuffer;
    
    return m_gradientImage;
}

// get currently active lightsources from OpenGL state
// should be changed as soon as OpenSG actions can handle this
void DVRIsoShader::getLightSources(DirLightList &diffuseLights,
                                   DirLightList &specularLights,
                                   Color4f      &ambientLight   )
{
    ambientLight  .clear();
    diffuseLights .clear();
    specularLights.clear();

    GLint maxNumLights;

    glGetIntegerv(GL_MAX_LIGHTS, &maxNumLights);

    GLfloat  lightPos     [4];
    GLfloat  diffuseColor [4];
    GLfloat  specularColor[4];
    GLfloat  ambientColor [4];  

    for(int i = 0; i < maxNumLights; i++) 
    {
        if(glIsEnabled(GLenum(GL_LIGHT0 + i)))
        {
            glGetLightfv(GLenum(GL_LIGHT0 + i), GL_POSITION, lightPos     );
            glGetLightfv(GLenum(GL_LIGHT0 + i), GL_AMBIENT,  ambientColor );
            glGetLightfv(GLenum(GL_LIGHT0 + i), GL_DIFFUSE,  diffuseColor );
            glGetLightfv(GLenum(GL_LIGHT0 + i), GL_SPECULAR, specularColor);
            
            //	    SLOG << "LightSource: " << i << " enabled" << std::endl;

            // check for directional light
            // homogenous coordinate = 0 -> infinity !
            if(1.0 ==  lightPos[3] + 1.0) 
            { 
                DirLight light;
                
                // set global light direction
                light.dir.setValues(lightPos[0],lightPos[1],lightPos[2]);
                
                // SLOG << "Pos: " << i << " :" << light.dir << std::endl;
                
                // diffuse
                if(diffuseColor[0] > 1e-6 || 
                   diffuseColor[1] > 1e-6 || 
                   diffuseColor[2] > 1e-6)
                {
                    light.color = Color4f(diffuseColor[0],
                                          diffuseColor[1],
                                          diffuseColor[2],
                                          0.0f);

                    diffuseLights.push_back(light);
                }
                
                // specular
                if(specularColor[0] > 1e-6 || 
                   specularColor[1] > 1e-6 || 
                   specularColor[2] > 1e-6)
                {
                    light.color = Color4f(specularColor[0],
                                          specularColor[1],
                                          specularColor[2],
                                          0.0f);

                    specularLights.push_back(light);
                }
                
                // ambient
                for(unsigned int i = 0; i < 4; i++)
                {
                    ambientLight[i] += ambientColor[i];
                }
            }
        }
    }
    
    // global ambient
    glGetFloatv(GL_LIGHT_MODEL_AMBIENT,ambientColor);

    for(unsigned int i = 0; i < 4; i++)
    {
        ambientLight[i] += ambientColor[i];
    }
}

// check if current OpenGL version is greater or equal to the given version
// Note: only the major and the minor version is checked!!
bool DVRIsoShader::checkGLVersion(GLfloat minVersion)
{
    char *versionString = (char*) glGetString(GL_VERSION);

    if(atof(versionString) >= minVersion)
        return true;
    else
        return false;
}


//! Automatically select a shading mode
UInt8 DVRIsoShader::selectMode(DVRVolume *volume, DrawActionBase *action)
{
    if(isModeSupported(volume, action, SM_FRAGMENT_PROGRAM_3D))
    { 
        FINFO(("DVRIsoShader - Autoselect: Using 3D textures and "
               "fragment program...\n"));

        return SM_FRAGMENT_PROGRAM_3D;
    }

    if(isModeSupported(volume, action, SM_FRAGMENT_PROGRAM_2D))
    { 
        FINFO(("DVRIsoShader - Autoselect: Using 2D textures and "
               "fragment program...\n"));

        return SM_FRAGMENT_PROGRAM_2D;
    }

    if(isModeSupported(volume, action, SM_REGISTER_COMBINERS_3D))
    { 
        FINFO(("DVRIsoShader - Autoselect: Using 3D textures and "
               "register combiners...\n"));
        
        return SM_REGISTER_COMBINERS_3D;
    }

    if(isModeSupported(volume, action, SM_REGISTER_COMBINERS_MULTI2D))
    {
        FINFO(("DVRIsoShader - Autoselect: Using 2D multi textures and "
               "register combiners...\n"));
        
        return SM_REGISTER_COMBINERS_MULTI2D;
    }

    if(isModeSupported(volume, action, SM_REGISTER_COMBINERS_2D))
    { 
        FINFO(("DVRIsoShader - Autoselect: Using 2D textures and "
               "register combiners...\n"));

        return SM_REGISTER_COMBINERS_2D;
    }
    
    if(isModeSupported(volume, action, SM_COLORMATRIX_3D))
    {
        FINFO(("DVRIsoShader - Autoselect: Using 3D textures and "
               "color matrix...\n"));

        return SM_COLORMATRIX_3D;
    }

    if(isModeSupported(volume, action, SM_COLORMATRIX_2D))
    {
        FINFO(("DVRIsoShader - Autoselect: Using 2D textures and "
               "color matrix...\n"));

        return SM_COLORMATRIX_2D;
    }
    
    SWARNING << "DVRIsoShader - None of the implemented shading algorithms"
             <<std::endl
             <<"is supported by this hardware!"
             <<std::endl;

    return SM_NONE;
}

//! Checks whether the selected mode is supported
bool DVRIsoShader::isModeSupported(DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   UInt8           mode  )
{ 
    Window *win = action->getWindow();
    
    if(!win)
    {
        SWARNING << "DVRIsoShader - No valid window" << std::endl;
        return false;
    }

    GLint numStencil;
    bool  forceTexture2D = false;
    bool  forceTexture3D = false;

    if(volume->getTextures2D() == 1)
    {
        forceTexture2D = true;
        SLOG << "DVRIsoShader - 2D textures forced" << std::endl;
    }
    else if(volume->getTextures2D() == 0)
    {
        forceTexture3D = true;
        SLOG << "DVRIsoShader - 3D textures forced" << std::endl;
    }
    
    switch(mode) 
    {
        case SM_COLORMATRIX_2D:
            glGetIntegerv(GL_STENCIL_BITS, &numStencil);

            return 
                numStencil > 0                           && 
                (win->hasExtension(_SGI_color_matrix) || 
                 checkGLVersion(1.2)                   ) && 
                !forceTexture3D;

        case SM_COLORMATRIX_3D:
            glGetIntegerv(GL_STENCIL_BITS,&numStencil);

            return 
                numStencil > 0                          && 
                win->hasExtension(_EXT_texture3D)       && 
                (win->hasExtension(_SGI_color_matrix) || 
                 checkGLVersion(1.2)                   ) && 
                !forceTexture2D;

        case SM_REGISTER_COMBINERS_2D:
            return 
                win->hasExtension(_NV_register_combiners) && !forceTexture3D;

        case SM_REGISTER_COMBINERS_MULTI2D:
            return 
                win->hasExtension(_ARB_multitexture     ) && 
                win->hasExtension(_NV_register_combiners) && 
                !forceTexture3D;

        case SM_REGISTER_COMBINERS_3D:
            return 
                win->hasExtension(_EXT_texture3D        ) && 
                win->hasExtension(_NV_register_combiners) && 
                !forceTexture2D;

        case SM_FRAGMENT_PROGRAM_2D:
            return 
                win->hasExtension(_ARB_multitexture    ) && 
                win->hasExtension(_ARB_fragment_program) && 
                !forceTexture3D;

        case SM_FRAGMENT_PROGRAM_3D:
            return 
                win->hasExtension(_EXT_texture3D       ) && 
                win->hasExtension(_ARB_fragment_program) && 
                !forceTexture2D;

        case SM_NONE:  
            return true;

        default: 	
            break;
    }
    
    return false;
}

//! Checks whether the selected mode is supported
bool DVRIsoShader::tryMode(DVRVolume      *volume, 
                           DrawActionBase *action, 
                           UInt8           mode )
{
    if(mode != SM_AUTO)
    {
        // A certain mode has been selected
        if(isModeSupported( volume, action, mode ))
        {
            SWARNING << "DVRIsoShader - User specified shading mode "
                     << int(mode) 
                     << std::endl;

            m_shadingMode =  mode;
        }
        else
        {
            SWARNING << "DVRIsoShader - Unsupported shading mode requested "
                     << int(mode)
                     << " disabling shading" 
                     << std::endl;

            m_shadingMode = SM_NONE;
        }
    }
    else 
    {
        // Use automatic mode selection
        m_shadingMode = selectMode(volume, action);
    }

    setActiveShadeMode(m_shadingMode);
    
    return m_shadingMode == mode;
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
    static char cvsid_hpp[] = OSGDVRISOSHADER_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRISOSHADER_INLINE_CVSID;
}
