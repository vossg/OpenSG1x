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

#ifndef _OSGDVRISOSHADER_H_
#define _OSGDVRISOSHADER_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include <OSGConfig.h>
#include <OSGWindow.h>
#include <OSGGL.h>
#include <OSGSystemDef.h>
#include <OSGDVRShader.h>
#include <OSGDrawActionBase.h>
#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGCamera.h>
#include <OSGColor.h>
#include <OSGFragmentProgramChunk.h>

#include <OSGDVRIsoShaderBase.h>

OSG_BEGIN_NAMESPACE


/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRIsoShader : public DVRIsoShaderBase
{
  private:

    typedef DVRIsoShaderBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    //    static bool _initialized;

    // Callback to set up shader - register textures here
    virtual bool initialize       (DVRVolume      *volume, 
                                   DrawActionBase *action      );
    
    // Callback before any slice is rendered - setup per volume
    virtual void activate         (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Callback before any brick - state setup per brick
    virtual void brickActivate    (DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   Brick          *brick       );

    // Callback after all rendering of the volume is done
    virtual void deactivate       (DVRVolume      *volume, 
                                   DrawActionBase *action      );
    
    // Callback to clean up shader resources
    virtual void cleanup          (DVRVolume      *volume, 
                                   DrawActionBase *action      );
    
    // Callback for rendering not clipped slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   Real32         *data, 
                                   UInt32          vertices, 
                                   UInt32          values      );

    // Callback for rendering clipped slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   DVRRenderSlice *clippedSlice);
    
    // Returns whether the shader has an implementation of 'renderSlice'
    virtual bool hasRenderCallback(void                        );

    // Returns whether the shader requires multitextured slabs instead 
    // of bricks
    virtual bool useMTSlabs       (void                        ); 

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
    
    enum ShadingMode 
    {
        SM_AUTO = 0,
        SM_COLORMATRIX_2D, 
        SM_COLORMATRIX_3D, 
        SM_REGISTER_COMBINERS_2D, 
        SM_REGISTER_COMBINERS_MULTI2D, 
        SM_REGISTER_COMBINERS_3D,
        SM_FRAGMENT_PROGRAM_2D,
        SM_FRAGMENT_PROGRAM_3D,
        SM_NONE
    };
    
    struct DirLight 
    {
        Vec3f dir;
        Color4f color;
    };
    
    typedef std::vector<DirLight> DirLightList;  


    ImagePtr                m_gradientImage;

    bool                    m_hasPerStageConstants;
    GLint                   m_maxCombiners;

    UInt8                   m_shadingMode;

    FragmentProgramChunkPtr m_pFragProg;

    Int32                   m_textureId; 

    GLint                   m_colorWriteMask[4];

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRIsoShader(void);
    DVRIsoShader(const DVRIsoShader &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRIsoShader(void); 

    /*! \}                                                                 */

    // compute gradient image from volume texture
    ImagePtr createGradientImage(DVRVolumeTexturePtr volTex);


    /* checks if the current OpenGL version is greater or equal to the 
       given one
    */
    bool checkGLVersion                       (GLfloat         version       );

    // Checks whether the selected mode is supported
    bool isModeSupported                      (DVRVolume      *volume, 
                                               DrawActionBase *action, 
                                               UInt8           mode          );

    // Automatically select the probably best shading mode
    UInt8 selectMode                          (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // try to select the given mode
    bool tryMode                              (DVRVolume      *volume, 
                                               DrawActionBase *action, 
                                               UInt8           mode          );

    // get active light sources from current OpenGL state
    void getLightSources                      (DirLightList   &diffuseLights, 
                                               DirLightList   &specularLights,
                                               Color4f        &ambientLight  );

    void getCoveredScreenRect                 (DVRVolume      *volume, 
                                               DrawActionBase *action, 
                                               GLfloat         screenRect[4] );
      
    // setup state for color matrix shading
    void activate_ColorMatrixShading          (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // cleanup state for color matrix shading 
    void deactivate_ColorMatrixShading        (DVRVolume      *volume, 
                                               DrawActionBase *action        );
    
    // setup state for shading using NV_register_combiners
    void activate_NVRegisterCombinerShading   (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // cleanup state used for shading with NV_register_combiners
    void deactivate_NVRegisterCombinerShading (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // setup state for shading with fragment program
    void activate_FragmentProgramShading      (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // cleanup state for shading with fragment program
    void deactivate_FragmentProgramShading    (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // render a slice for 2D multitexture register combiner shading
    void renderSlice_NVRegisterCombinerShading(DVRVolume      *volume, 
                                               DrawActionBase *action,
                                               Real32         *data, 
                                               UInt32          vertices, 
                                               UInt32          values        );

    // render a clipped slice for 2D multitexture register combiner shading
    void renderSlice_NVRegisterCombinerShading(DVRVolume *volume, 
                                               DrawActionBase *action,
                                               DVRRenderSlice *clippedSlice  );

    // render a slice for 2D multitexture fragment program shading
    void renderSlice_FragmentProgramShading   (DVRVolume *volume, 
                                               DrawActionBase *action,
                                               Real32         *data, 
                                               UInt32          vertices, 
                                               UInt32          values        );

    // render a clipped slice for 2D multitexture fragment program shading
    void renderSlice_FragmentProgramShading   (DVRVolume      *volume, 
                                               DrawActionBase *action,
                                               DVRRenderSlice *clippedSlice  );
    
    // setup register combiner parameters for diffuse lighted shading
    void setupCombinerParametersDiffuse       (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // setup register combiner parameters for specular lighted shading
    void setupCombinerParametersSpecular      (DVRVolume      *volume, 
                                               DrawActionBase *action        );

    // setup register combiners for diffuse lighted shading
    void initCombiners_IsoSurfaceDiffuse      (DrawActionBase *action        );

    // setup register combiners for diffuse lighted shading, if only 
    // two general combiners are available
    // this allows up to two diffuse light sources
    void initCombiners_Diffuse2Combiners      (DrawActionBase *action        );

    // setup register combiners for diffuse lighted shading, if more
    // than two general combiners are available
    // this allows a arbitrary number of diffuse light sources, in fact  
    // with 8 general register combiners (GeForce3/4) there are up to 6
    // lightsources available
    void initCombiners_DiffuseMultiCombiners  (DrawActionBase *action        );

    // setup register combiners for specular lighted shading
    void initCombiners_IsoSurfaceSpecular     (DrawActionBase *action        );

    // setup register combiners for specular lighted shading, if only 
    // two general combiners are available
    // this allows one diffuse and one specular white lightsource, only 
    // the RED components of the lights colors affect the shading intensity
    void initCombiners_Specular2Combiners     (DrawActionBase *action        );

    // setup register combiners for diffuse lighted shading, if more 
    // than two general combiners are available
    // currently uses 8 general combiners. So up to 3 diffuse and 3 specular
    // (fullcolor) lightsources are supported
    void initCombiners_SpecularMultiCombiners (DrawActionBase *action        );
 

    // fragment programs used by fragment shader mode
    static char _fragProg2D[];	 
    static char _fragProg3D[];

    // extension indices for used extensions
    static UInt32 _ARB_multitexture;
    static UInt32 _EXT_texture3D; 
    static UInt32 _EXT_secondary_color; 

    static UInt32 _NV_register_combiners;
    static UInt32 _NV_register_combiners2;

    static UInt32 _SGI_color_matrix;

    static UInt32 _ARB_fragment_program;
    
    // extension indices for used functions
    static UInt32 _funcActiveTextureARB;
    static UInt32 _funcMultiTexCoord2dARB;    
    static UInt32 _funcTexImage3DEXT;

    static UInt32 _funcCombinerParameteriNV;
    static UInt32 _funcCombinerParameterfvNV;
    static UInt32 _funcCombinerStageParameterfvNV;
    static UInt32 _funcCombinerInputNV;
    static UInt32 _funcCombinerOutputNV;
    static UInt32 _funcFinalCombinerInputNV;

    static UInt32 _funcSecondaryColor3fEXT;
    static UInt32 _funcSecondaryColor3fvEXT;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DVRIsoShaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRIsoShader &source);
};

typedef DVRIsoShader *DVRIsoShaderP;

OSG_END_NAMESPACE

#include "OSGDVRIsoShader.inl"
#include "OSGDVRIsoShaderBase.inl"

#define OSGDVRISOSHADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRISOSHADER_H_ */
