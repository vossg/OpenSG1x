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

#ifndef _OSGDVRSIMPLELUTSHADER_H_
#define _OSGDVRSIMPLELUTSHADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDVRSimpleLUTShaderBase.h>

#include <OSGTextureChunk.h>
#include <OSGFragmentProgramChunk.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRSimpleLUTShader : 
    public DVRSimpleLUTShaderBase
{
  private:

    typedef DVRSimpleLUTShaderBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Volume Rendering                             */
    /*! \{                                                                 */

    // Callback to set up shader - register textures here
    virtual bool initialize   (DVRVolume      *volume, 
                               DrawActionBase *action);
    
    // Callback before any slice is rendered - setup per volume
    virtual void activate     (DVRVolume      *volume, 
                               DrawActionBase *action);

    // Callback before any brick - state setup per brick
    virtual void brickActivate(DVRVolume      *volume, 
                               DrawActionBase *action, 
                               Brick          *brick );

    // Callback after all rendering of the volume is done
    virtual void deactivate   (DVRVolume      *volume, 
                               DrawActionBase *action);

    // Callback to clean up shader resources
    virtual void cleanup      (DVRVolume      *volume, 
                               DrawActionBase *action);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DVRSimpleLUTShaderBase.

    UInt8                   m_nTexturePaletteMode;
    Int8                    m_nTextureMode; 
    FragmentProgramChunkPtr m_pFragProg;
    TextureChunkPtr         m_pDepTexture;

    enum LutMode 
    {
        LM_AUTO = 0,
        LM_TABLE_SGI,
        LM_PALETTE_EXT,
        LM_DEPENDENT,
        LM_FRAGPROG,
        LM_RELOAD,
        LM_NO
    };
    
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRSimpleLUTShader(void);
    DVRSimpleLUTShader(const DVRSimpleLUTShader &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRSimpleLUTShader(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Volume Rendering                             */
    /*! \{                                                                 */

    // Returns suitable lookup table mode and texture formate for 
    // graphics adapter
    void getPaletteFormat(DrawActionBase *action, 
                          UInt8           lutMode,
                          GLenum         &internalFormat, 
                          GLenum         &externalFormat);

    // Checks whether the selected mode is supported
    bool isModeSupported (DrawActionBase *action, 
                          UInt8           mode, 
                          Int8            textureMode);
    // Automatically select a lookup table mode
    UInt8 selectMode     (DrawActionBase *action, 
                          Int8            textureMode);
    
    // Enable/disable palette
    void enablePalette (void);
    void disablePalette(void);

    // Handle dependent texture
    void initDependentTexture   (      Int32  size);
    void updateDependentTexture (      Int32  size, 
                                 const UInt8 *data);
    void destroyDependentTexture(      void       );

    // Register combiners
    void setupAlphaCorrectionRegisterCombiners(DrawActionBase *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // fragment programs used by fragment shader mode
    static char _fragProg2D[];	 
    static char _fragProg3D[];
    static char _fragProg2DMulti[];
    
    // extension indices for used extensions;
    static UInt32 _sgiTexColorTable;
    static UInt32 _extPalettedTexture;
    static UInt32 _extSharedPalettedTexture;
    static UInt32 _arbMultitexture;
    static UInt32 _nvTextureShader2;
    static UInt32 _arbFragmentProgram;
    static UInt32 _nvRegisterCombiners;

    // extension indices for used fucntions;
    static UInt32 _funcColorTableSGI;
    static UInt32 _funcColorTableEXT;
    static UInt32 _funcActiveTextureARB;
    static UInt32 _funcFinalCombinerInputNV;
    static UInt32 _funcCombinerInputNV;
    static UInt32 _funcCombinerOutputNV;
    
    friend class FieldContainer;
    friend class DVRSimpleLUTShaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRSimpleLUTShader &source);
};

typedef DVRSimpleLUTShader *DVRSimpleLUTShaderP;

OSG_END_NAMESPACE

#include <OSGDVRSimpleLUTShader.inl>
#include <OSGDVRSimpleLUTShaderBase.inl>

#define OSGDVRSIMPLELUTSHADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRSIMPLELUTSHADER_H_ */
