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

#include <OSGDVRMtexLUTShader.h>

#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRLookupTable.h>

#include <OSGWindow.h>


OSG_USING_NAMESPACE

/*! \class osg::DVRMtexLUTShader
 * Abstract shader class - not to be instantiated. Is intended to be 
 * stateless - NO FIELDS!!
 */

UInt32 DVRMtexLUTShader::_arbMultitexture           = 
    Window::invalidExtensionID;

UInt32 DVRMtexLUTShader::_nvRegisterCombiners       = 
    Window::invalidExtensionID;    


UInt32 DVRMtexLUTShader::_funcMultiTexCoord2dARB    = 
    Window::invalidFunctionID;

UInt32 DVRMtexLUTShader::_funcCombinerParameteriNV  = 
    Window::invalidFunctionID;

UInt32 DVRMtexLUTShader::_funcCombinerParameterfvNV = 
    Window::invalidFunctionID;

UInt32 DVRMtexLUTShader::_funcCombinerInputNV       = 
    Window::invalidFunctionID;

UInt32 DVRMtexLUTShader::_funcCombinerOutputNV      = 
    Window::invalidFunctionID;

UInt32 DVRMtexLUTShader::_funcFinalCombinerInputNV  = 
    Window::invalidFunctionID;

bool DVRMtexLUTShader::hasRenderCallback(void)
{
    return true; 
}

bool DVRMtexLUTShader::useMTSlabs(void) 
{
    return true; 
} 

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRMtexLUTShader::DVRMtexLUTShader(void) :
    Inherited()
{
    _arbMultitexture           = 
        Window::registerExtension( "GL_ARB_multitexture"     );

    _nvRegisterCombiners       = 
        Window::registerExtension( "GL_NV_register_combiners");
    

    _funcMultiTexCoord2dARB    = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glMultiTexCoord2dARB",
                                _arbMultitexture);

    _funcCombinerParameteriNV  = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCombinerParameteriNV",
                                _nvRegisterCombiners);

    _funcCombinerParameterfvNV = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCombinerParameterfvNV",
                                _nvRegisterCombiners);

    _funcCombinerInputNV       = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCombinerInputNV",
                                _nvRegisterCombiners);

    _funcCombinerOutputNV      = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCombinerOutputNV",
                                _nvRegisterCombiners);

    _funcFinalCombinerInputNV  = 
      Window::registerFunction (OSG_DLSYM_UNDERSCORE"glFinalCombinerInputNV",
                                _nvRegisterCombiners);
}

//! Copy Constructor
DVRMtexLUTShader::DVRMtexLUTShader(const DVRMtexLUTShader &source) :
    Inherited(source)
{
}

//! Destructor
DVRMtexLUTShader::~DVRMtexLUTShader(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRMtexLUTShader::initMethod (void)
{
}

//! react to field changes
void DVRMtexLUTShader::changed(BitVector whichField, UInt32 origin)
{
    SWARNING << "DVRMtexLUTShader::changed" << std::endl;
    
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void DVRMtexLUTShader::dump(      UInt32    , 
                            const BitVector ) const
{
    SLOG << "Dump DVRMtexLUTShader NI" << std::endl;
}

//! callback to set up shader - register textures here
bool DVRMtexLUTShader::initialize(DVRVolume *volume, DrawActionBase *action)
{
    //FDEBUG(("DVRMtexLUTShader::initialize\n"));
    FWARNING(("DVRMtexLUTShader::initialize\n"));

    GLenum nInternalFormat;
    GLenum nExternalFormat;

    Window *win = action->getWindow();

    // Determine lookup table mechanism
    if(getLutMode() != LM_AUTO)
    {
        // A certain mode has been selected
        if(isModeSupported(action, 
                           getLutMode(), 
                           volume->getTextureMode(win)) == true)
        {
            SWARNING << "DVRMtexLUTShader - User specified lookup table mode "
                     << int(getLutMode()) 
                     << std::endl;

            m_nTexturePaletteMode = getLutMode();
        }
        else
        {
            SWARNING << "DVRMtexLUTShader - Unsupported lookup table mode " 
                     << int(getLutMode()) 
                     << " disabling LUT" 
                     << std::endl;

            m_nTexturePaletteMode = LM_NO;
        }
    }
    else 
    {
        // Use automatic mode selection
        m_nTexturePaletteMode = selectMode(action, 
                                           volume->getTextureMode(win));
    }

    setActiveLutMode(m_nTexturePaletteMode);

    
    getPaletteFormat(action, 
                     m_nTexturePaletteMode, 
                     nInternalFormat, 
                     nExternalFormat      );

    DVRLookupTablePtr   lut = DVRVOLUME_PARAMETER(volume, DVRLookupTable);
    DVRVolumeTexturePtr vol = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if((volume == NULL) || (vol == NullFC)) 
    {
        SWARNING << "NO Volume..." << std::endl;
        return false;
    }

    // This shader requires ARB_multitexture and 
    // NV_register_combiner extensions

    if(!action->getWindow()->hasExtension(_arbMultitexture))
    {
        SWARNING << "NO multi textures ..." << std::endl;

        return false;
    }

    SWARNING << "Multitextures found" << std::endl;

    if(!action->getWindow()->hasExtension(_nvRegisterCombiners))
    {
        SWARNING << "NO register combiners" << std::endl;
        return false;
    }

    SWARNING << "Register Combiners found" << std::endl;
    
    m_nTextureId = volume->getTextureManager().registerTexture(
        vol->getImage(), // image
        nInternalFormat, // internalFormat
        nExternalFormat, // externalFormat
        1,               // doBricking
        0,               // textureStage0
        1);              // textureStage1
    
    if(m_nTextureId == -1) 
    {
        SWARNING << "Error registering textures ..." << std::endl;
        return false;
    }
    else
    {
        SWARNING << "New texture Id: " << m_nTextureId << std::endl;
    }
    
    if(lut != NullFC)
        lut->setTouched(true); // force initialization in first render pass

    return true;
}


//! callback before any slice is rendered - setup per volume
void DVRMtexLUTShader::activate(DVRVolume *volume, DrawActionBase *action)
{
    //FDEBUG(("DVRMtexLUTShader::activate\n"));

#if !defined(GL_ARB_multitexture) || !defined(GL_NV_register_combiners)
    SWARNING << "DVRtexLUTShader requires ARB_multitexture and "
             << "NV_register_combiners extensions" 
             << std::endl;

    volume = volume; action = action; // calm down compiler
#else
    DVRSimpleLUTShader::activate(volume, action);

    if(volume->getDoTextures())
    {
        glEnable(GL_REGISTER_COMBINERS_NV);

        initCombiners(action);
    }
#endif // required extensions available
}


//! callback after all rendering of the volume is done
void DVRMtexLUTShader::deactivate(DVRVolume *volume, DrawActionBase *action)
{
    //FDEBUG(("DVRMtexLUTShader::deactivate\n"));

#if !defined(GL_ARB_multitexture) || !defined(GL_NV_register_combiners)
    SWARNING << "DVRtexLUTShader requires ARB_multitexture and " 
             << "NV_register_combiners extensions"
             << std::endl;

    volume = volume; action = action; // calm down compiler
#else
    if (volume->getDoTextures())
    {
        glDisable(GL_REGISTER_COMBINERS_NV);
    }
    
    DVRSimpleLUTShader::deactivate(volume, action);
#endif // required extensions available
}

//! callback to clean up shader resources
void DVRMtexLUTShader::cleanup(DVRVolume *volume, DrawActionBase * /*action*/)
{
    if(volume != NULL)
    {
        if(m_nTextureId != -1)
            volume->getTextureManager().unregisterTexture(m_nTextureId);
    }
}


typedef void (OSG_APIENTRY *CombinerParameterfvNVFunc)(      GLenum, 
                                                       const GLfloat *);

typedef void (OSG_APIENTRY *MultiTexCoord2dARBFunc   )(      GLenum, 
                                                             GLdouble, 
                                                             GLdouble);

//! callback for rendering slices
void DVRMtexLUTShader::renderSlice(DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   Real32         *data, 
                                   UInt32          vertices, 
                                   UInt32          values)
{
#if !defined(GL_ARB_multitexture) || !defined(GL_NV_register_combiners)
    SWARNING << "DVRtexLUTShader requires ARB_multitexture and "
             << "NV_register_combiners extensions" 
             << std::endl;

    volume   = volume;   action = action; data = data; // calm down compiler
    vertices = vertices; values = values; 
#else
    Window *win = action->getWindow();

    if(!win->hasExtension(_nvRegisterCombiners) ||
       !win->hasExtension(_arbMultitexture))
    {
        return;
    }

    CombinerParameterfvNVFunc CombinerParameterfvNV = 
        (CombinerParameterfvNVFunc) win->getFunction(
            _funcCombinerParameterfvNV);

    MultiTexCoord2dARBFunc MultiTexCoord2dARB = 
        (MultiTexCoord2dARBFunc) win->getFunction(_funcMultiTexCoord2dARB); 
    
    //FINFO(("DVRMtexLUTShader::renderSlice - vert(%d) - values(%d)\n", 
    //       vertices, values));
    
    if(values < 6)
    {
        SWARNING << "DVRMtexLUTShader::renderSlice - insufficient values" 
                 << std::endl;
        return;
    }
    
    
    float col[4] = 
    { 
        0.f, 0.f, 0.f, data[5]
    };

    CombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, col);

    glFogfv(GL_FOG_COLOR, col);

    if(volume->getDoTextures())
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else
    {
        //!! TODO - alpha correction
        glColor4f(1.0, 1.0, 1.0, 1.0);

        glBegin(GL_LINE_LOOP);
    }

    
    for(UInt32 i = 0; i < vertices; i++)
    {
        Real32 *vert = data + i *values;
        
    // constant color is used as blending factor between tex0 and tex1
    // a == 0 means tex0
    // a == 1 means tex1 
    // float col[4] = {0, 0, 0, vert[5]};
    // CombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, col);
      
        MultiTexCoord2dARB(GL_TEXTURE0_ARB, vert[3], vert[4]);
        MultiTexCoord2dARB(GL_TEXTURE1_ARB, vert[3], vert[4]);
        
        glVertex3f(vert[0], vert[1], vert[2]);  
        
    }
    glEnd();
    
#endif // required extensions
}

// Callback for rendering clipped slices
void DVRMtexLUTShader::renderSlice(DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   DVRRenderSlice *clippedSlice)
{
#if !defined(GL_ARB_multitexture) || !defined(GL_NV_register_combiners)
    SWARNING << "DVRtexLUTShader requires ARB_multitexture and "
             << "NV_register_combiners extensions" 
             << std::endl;

    volume       = volume; 
    action       = action; 
    clippedSlice = clippedSlice; // calm down compiler
#else

    Window *win = action->getWindow();

    if(!win->hasExtension(_nvRegisterCombiners) ||
       !win->hasExtension(_arbMultitexture))
    {
        return;
    }

    CombinerParameterfvNVFunc CombinerParameterfvNV =
        (CombinerParameterfvNVFunc) win->getFunction(
            _funcCombinerParameterfvNV);

    MultiTexCoord2dARBFunc MultiTexCoord2dARB = 
        (MultiTexCoord2dARBFunc) win->getFunction(_funcMultiTexCoord2dARB); 
   
    GLfloat intFactor = 0;
    
    switch(clippedSlice->orientation)
    {
        case DVRRenderSlice::XY:
            intFactor = 
                Real32((*(*clippedSlice->begin())->vertices.begin())[5]);
            break;

        case DVRRenderSlice::XZ:
            intFactor = 
                Real32((*(*clippedSlice->begin())->vertices.begin())[4]);
            break;

        case DVRRenderSlice::YZ:
            intFactor = 
                Real32((*(*clippedSlice->begin())->vertices.begin())[3]);
            break;

        default:
            break;
    }

    if(intFactor < 0 || intFactor > 1)
        std::cerr << intFactor << std::endl;
    
    float col[4] = 
    {
        0.f, 0.f, 0.f, intFactor
    };

    CombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, col);

    glFogfv(GL_FOG_COLOR, col);

    if(volume->getDoTextures())
    {
        //glBegin(GL_TRIANGLE_FAN);
    }
    else
    {
        //!! TODO - alpha correction
        glColor4f(1.0, 1.0, 1.0, 1.0);
        //glBegin(GL_LINE_LOOP);
    }

    switch(clippedSlice->orientation)
    {
        case DVRRenderSlice::XY:

            for(std::vector<DVRRenderSlicePrimitive *>::const_iterator prim = 
                    clippedSlice->begin();

                  prim != clippedSlice->end();
                ++prim)
            {
                glBegin((*prim)->type);
                
                std::vector<GLdouble *>::const_iterator vert = 
                    (*prim)->vertices.begin();        

                for(; vert != (*prim)->vertices.end(); ++vert)
                {
                    MultiTexCoord2dARB(GL_TEXTURE0_ARB, 
                                       (*vert)[3], 
                                       (*vert)[4]);

                    MultiTexCoord2dARB(GL_TEXTURE1_ARB, 
                                       (*vert)[3], 
                                       (*vert)[4]);

                    glVertex3dv(*vert);
                }      
                glEnd();
            }     
            break;

        case DVRRenderSlice::XZ:

            for(std::vector<DVRRenderSlicePrimitive *>::const_iterator prim = 
                    clippedSlice->begin();
 
                  prim != clippedSlice->end();
                ++prim)
            {
                glBegin((*prim)->type);
                
                std::vector<GLdouble *>::const_iterator vert = 
                    (*prim)->vertices.begin();        

                for(; vert != (*prim)->vertices.end(); vert++)
                {
                    MultiTexCoord2dARB(GL_TEXTURE0_ARB, 
                                       (*vert)[3], 
                                       (*vert)[5]);
                    MultiTexCoord2dARB(GL_TEXTURE1_ARB, 
                                       (*vert)[3], 
                                       (*vert)[5]);

                    glVertex3dv(*vert);
                }      
                glEnd();
            }     
            break;

        case DVRRenderSlice::YZ:
            
            for(std::vector<DVRRenderSlicePrimitive*>::const_iterator prim = 
                    clippedSlice->begin();

                  prim != clippedSlice->end();
                ++prim)
            {
                glBegin((*prim)->type);
   
                std::vector<GLdouble*>::const_iterator vert = 
                    (*prim)->vertices.begin();        

                for(; vert != (*prim)->vertices.end(); vert++)
                {
                    MultiTexCoord2dARB(GL_TEXTURE0_ARB, 
                                       (*vert)[4], 
                                       (*vert)[5]);

                    MultiTexCoord2dARB(GL_TEXTURE1_ARB, 
                                       (*vert)[4], 
                                       (*vert)[5]);
                    glVertex3dv(*vert);
                }      
                glEnd();
            }
            break;

        default:
            break;
    }
#endif // required extensions
}


#if defined(GL_ARB_multitexture) && defined(GL_NV_register_combiners)

typedef void (OSG_APIENTRY *CombinerParameteriNVFunc)(      GLenum, 
                                                      const GLint    );
typedef void (OSG_APIENTRY *CombinerInputNVFunc     )(      GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum   );
typedef void (OSG_APIENTRY *CombinerOutputNVFunc    ) (     GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLboolean, 
                                                            GLboolean, 
                                                            GLboolean);
typedef void (OSG_APIENTRY *FinalCombinerInputNVFunc)(      GLenum, 
                                                            GLenum, 
                                                            GLenum, 
                                                            GLenum   );

//! set up correct register combiner state
void DVRMtexLUTShader::initCombiners(DrawActionBase *action)
{
    Window *win = action->getWindow();

    if(!win->hasExtension(_nvRegisterCombiners) ||
       !win->hasExtension(_arbMultitexture))
    {
        return;
    }

    CombinerParameteriNVFunc CombinerParameteriNV = 
        (CombinerParameteriNVFunc) win->getFunction(_funcCombinerParameteriNV);

    CombinerInputNVFunc CombinerInputNV           =
        (CombinerInputNVFunc     ) win->getFunction(_funcCombinerInputNV     );

    CombinerOutputNVFunc CombinerOutputNV         =
        (CombinerOutputNVFunc    ) win->getFunction(_funcCombinerOutputNV    );

    FinalCombinerInputNVFunc FinalCombinerInputNV =
        (FinalCombinerInputNVFunc) win->getFunction(_funcFinalCombinerInputNV);
    
    // use only first general combiner
    CombinerParameteriNV(GL_NUM_GENERAL_COMBINERS_NV, 1);

    // RGB-Portion
    // --------------------------------------------
    // Alpha value of const color is used as
    // blending factor for the two textures 0 and 1
    
    CombinerInputNV(             // (1 - ConstColor0) -> A
        GL_COMBINER0_NV,         // stage
        GL_RGB,                  // portion
        GL_VARIABLE_A_NV,        // variable
        GL_CONSTANT_COLOR0_NV,   // input  <- const color 0
        GL_UNSIGNED_INVERT_NV,   // mapping (1-x)
        GL_ALPHA);               // componentUsage
    
    CombinerInputNV(             // Texture0     -> B
        GL_COMBINER0_NV,         // stage         
        GL_RGB,                  // portion       
        GL_VARIABLE_B_NV,        // variable      
        GL_TEXTURE0_ARB,         // input <- texture 0         
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_RGB);                 // componentUsage
    
    CombinerInputNV(             // ConstColor0    -> C
        GL_COMBINER0_NV,         // stage         
        GL_RGB,                  // portion       
        GL_VARIABLE_C_NV,        // variable      
        GL_CONSTANT_COLOR0_NV,   // input    <- const color 0     
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_ALPHA);               // componentUsage
    
    CombinerInputNV(             // Texture1      -> D
        GL_COMBINER0_NV,         // stage         
        GL_RGB,                  // portion       
        GL_VARIABLE_D_NV,        // variable      
        GL_TEXTURE1_ARB,         // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_RGB);                 // componentUsage
    
    // Alpha-Portion
    // --------------------------------------------
    // Alpha value of const color is used as
    // blending factor for the two textures 0 and 1

    CombinerInputNV(             // (1 - ConstColor0) -> A/
        GL_COMBINER0_NV,         // stage         
        GL_ALPHA,                // portion       
        GL_VARIABLE_A_NV,        // variable 
        GL_CONSTANT_COLOR0_NV,   // input <- const color 0     
        GL_UNSIGNED_INVERT_NV,   // mapping (1-x) 
        GL_ALPHA);               // componentUsage
    
    CombinerInputNV(             //  Texture0 -> A
        GL_COMBINER0_NV,         // stage         
        GL_ALPHA,                // portion       
        GL_VARIABLE_B_NV,        // variable      
        GL_TEXTURE0_ARB,         // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_ALPHA);               // componentUsage
    
    CombinerInputNV(             // ConstColor0 -> C
        GL_COMBINER0_NV,         // stage         
        GL_ALPHA,                // portion       
        GL_VARIABLE_C_NV,        // variable      
        GL_CONSTANT_COLOR0_NV,   // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_ALPHA);               // componentUsage
    
    CombinerInputNV(             // Texture1 -> D
        GL_COMBINER0_NV,         // stage         
        GL_ALPHA,                // portion       
        GL_VARIABLE_D_NV,        // variable      
        GL_TEXTURE1_ARB,         // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping
        GL_ALPHA);               // componentUsage
    
    // general combiner output
    //------------------------------------- 
 
    CombinerOutputNV(    // Spare0(RGB) = AB+CD
        GL_COMBINER0_NV, // stage
        GL_RGB,          // portion
        GL_DISCARD_NV,   // abOutput  (not used)
        GL_DISCARD_NV,   // cdOutput  (not used)
        GL_SPARE0_NV,    // sumOutput (this is AB+CD) 
        GL_NONE,         // scale     (not used)
        GL_NONE,         // bias      (not used)
        GL_FALSE,        // abDotProduct
        GL_FALSE,        // cdDotproduct
        GL_FALSE);       // muxSum                      
    
    CombinerOutputNV(    // Spare0(A) = AB+CD
        GL_COMBINER0_NV, // stage                       
        GL_ALPHA,        // portion                     
        GL_DISCARD_NV,   // abOutput  (not used)        
        GL_DISCARD_NV,   // cdOutput  (not used)        
        GL_SPARE0_NV,    // sumOutput (this is AB+CD)   
        GL_NONE,         // scale     (not used)        
        GL_NONE,         // bias      (not used)        
        GL_FALSE,        // abDotProduct                
        GL_FALSE,        // cdDotproduct                
        GL_FALSE);       // muxSum                      
    
    // final combiner input
    //------------------------------------- 
    
    FinalCombinerInputNV(        // A(RGB) = 0
        GL_VARIABLE_A_NV,        // variable
        GL_ZERO,                 // input
        GL_UNSIGNED_IDENTITY_NV, // mapping 
        GL_RGB);                 // componentUsage
    
    FinalCombinerInputNV(        // B(RGB) = 0
        GL_VARIABLE_B_NV,        // variable         
        GL_ZERO,                 // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping        
        GL_RGB);                 // componentUsage
    
    FinalCombinerInputNV(        // C(RGB) = 0
        GL_VARIABLE_C_NV,        // variable      
        GL_ZERO,                 // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping        
        GL_RGB);                 // componentUsage
    
    FinalCombinerInputNV(        // D = Spare0(RGB)
        GL_VARIABLE_D_NV,        // variable      
        GL_SPARE0_NV,            // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping        
        GL_RGB);                 // componentUsage
    
    FinalCombinerInputNV(        // G = Spare0(A)
        GL_VARIABLE_G_NV,        // variable      
        GL_SPARE0_NV,            // input         
        GL_UNSIGNED_IDENTITY_NV, // mapping        
        GL_ALPHA);               // componentUsage
}

#endif // required extensions


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
    static char cvsid_hpp[] = OSGDVRMTEXLUTSHADER_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRMTEXLUTSHADER_INLINE_CVSID;
}

