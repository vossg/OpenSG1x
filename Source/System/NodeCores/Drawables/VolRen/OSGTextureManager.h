#ifndef _OSGTEXTUREMANAGER_H_
#define _OSGTEXTUREMANAGER_H_

#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSystemDef.h>

#include <OSGChunkMaterial.h>
#include <OSGImage.h>

#include <vector>


OSG_BEGIN_NAMESPACE


// forward declarations

class DVRVolume;
class BrickSet;
class Brick;
class DrawActionBase;

/*! \brief *put brief class description here* 
  Auxiliary class for DVRVolume. It is intended for texture
  management and bricking.
 */

struct TextureRecord 
{
    ImagePtr _image;
    UInt32   _internalFormat;
    UInt32   _externalFormat;
    Int32    _textureStage0;
    Int32    _textureStage1;
  
    TextureRecord(ImagePtr img, 
                  UInt32   internal, 
                  UInt32   externalFormat,
                  Int32    stage0, 
                  Int32    stage1);
    ~TextureRecord(void);

  private:

    //!! We do not want the copy constructor to be called -
    //!! would require deep copy

    TextureRecord(const TextureRecord &source);
    void operator =(const TextureRecord &source);
};


typedef std::vector<TextureRecord *> TextureSet;


class OSG_SYSTEMLIB_DLLMAPPING TextureManager 
{
  public:

    //! Texture mode
    enum TextureMode 
    {
        TM_3D = 0,
        TM_2D,
        TM_2D_Multi,
        NUM_TEXTURE_MODES
    };

    //! Bricking mode
    enum BrickingMode 
    {
        BRICK_SUBDIVIDE_ON_TEXTURE_MEMORY = 0,
        BRICK_SUBDIVIDE_STATIC,
        BRICK_SUBDIVIDE_ON_BRICK_SIZE,
        NUM_BRICKING_MODES
    };
    
    //! Constructor/ destructor
    TextureManager(DVRVolume *volume);
    ~TextureManager(void);

    //! Register texture
    /*! \brief register an image for use as texture with direct volume 
     *         rendering
     *         image                   points to the image
     *         internal/externalFormat defines the texture format
     *         doBricking              specifies, whether the texture is uses 
     *                                 as utility
     *                                 texture or as volume texture 
     *                                 (volume textures are
     *                                 divided into bricks - utility textures
     *                                  are loaded as they are)
     *         textureState0
     *         textureState1           (optional) specifies which 
     *                                 (multi-)texture stages
     *                                 the texture shall be bound
     */

    Int32 registerTexture(ImagePtr image,
                          UInt32   internalFormat,
                          UInt32   externalFormat,
                          bool     doBricking    = 1,
                          Int32    textureStage0 = 0,
                          Int32    textureStage1 = -1);
    
    //! Remove texture
    void unregisterTexture(Int32 id);

    //! Reload texture
    void reloadTexture(Int32 id, DrawActionBase * action);

    //! Clear all registered textures
    void clearTextures(ChunkMaterialPtr material = NullFC);
      
    //! Create texture chunks for registered textures
    void buildTextures(ChunkMaterialPtr  material, 
                       DVRVolume        *volume, 
                       TextureMode       mode = TM_3D);

    //! Return sorted brick list
    Brick *sortBricks(DrawActionBase *da, 
                      Matrix          modelMat, 
                      Vec3f           eyePoint, 
                      DVRVolume      *volume, 
                      TextureMode     mode);
    
    //! Output the instance for debug purposes
    void dump(      UInt32     uiIndent = 0, 
              const BitVector  bvFlags  = 0) const;
      
  private:

    TextureSet   _registeredTextures;
    DVRVolume   *_parent;

    BrickSet    *_brickSets;

    //! Calculate bricking 
    static Vec3f calcBrickSubdivision(Int32      resX, 
                                      Int32      resY, 
                                      Int32      resZ, 
                                      Int32      dataSize, 
                                      DVRVolume *volume);

    friend struct BrickSet;
};

OSG_END_NAMESPACE

#endif
