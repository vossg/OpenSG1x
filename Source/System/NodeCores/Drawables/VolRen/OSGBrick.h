#ifndef _OSGBRICK_H_
#define _OSGBRICK_H_

#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSystemDef.h>

#include <vector>

#include <OSGVector.h>
#include <OSGChunkMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>

#include "OSGDVRShader.h"
#include "OSGDVRClipper.h"
#include "OSGTextureManager.h"

OSG_BEGIN_NAMESPACE


// Forward declarations
class Brick;
class DVRVolume;


struct BrickSet 
{
    // Orientation values must be fix for they are used for indexing

    enum Orientation 
    {
        XY    = 0,
        XZ    = 1,
        YZ    = 2,
        UNDEF = 3   // especially for 3D textures
    };

    Brick       *m_pBricks;
    int          m_nNumBricks;
    Orientation  m_nOrientation;
  
    BrickSet(void);

    ~BrickSet(void);
  

    //! Return sorted brick list
    Brick *sortBricks3D(const Matrix &modelMat, 
                        const Vec3f  &eyePoint   );
    Brick *sortBricks2D(      bool    backToFront);


    //! Build textures for bricks
    void buildBrickTextures (ChunkMaterialPtr            &material, 
                             TextureSet                  &textures,
                             TextureManager::TextureMode  mode            );

    //! Reload brick textures
    void reloadBrickTextures(DrawActionBase              *action, 
                             UInt32                       texStage        );

    //! Clear brick textures
    void clearBrickTextures (ChunkMaterialPtr            &material        );
    
    //! Build 3D bricks
    void buildBricks3D      (DVRVolume                   *volume, 
                             Vec3f                        brickSubdivision, 
                             Int32                        overlap = 1,
                             Orientation                  ori     = UNDEF );
  
    //! Build 2D bricks
    void buildBricks2D      (DVRVolume                   *volume, 
                             Orientation                  ori             );


    //! Create texture chunk for image
    static TextureChunkPtr makeTexture(UInt32   internalFormat, 
                                       UInt32   externalFormat, 
                                       ImagePtr image         );
};


class Brick 
{
  public:

    //! Returns next brick in sorted order
    Brick *getNext(void);
    
    //! Initialize brick size and geometry
    void init(Int32  minVoxX, Int32  minVoxY, Int32  minVoxZ,
              Int32  resX,    Int32  resY,    Int32  resZ,
              Real32 xMin,    Real32 yMin,    Real32 zMin,
              Real32 xMax,    Real32 yMax,    Real32 zMax,

              Int32                 overlap = 1,
              BrickSet::Orientation ori     = BrickSet::UNDEF);

    //! Activate textures
    void activateTexture  (DrawActionBase *action             );
    void changeFromTexture(DrawActionBase *action, Brick * old);
    void deactivateTexture(DrawActionBase *action             );

    //! Render slices
    void renderSlices(DVRVolume                   *volume, 
                      DrawActionBase              *action,
                      DVRShaderPtr                 shader,  
                      DVRClipper                  *clipper,
                      TextureManager::TextureMode  mode);

    //! Render brick boundaries
    void renderBrick(void);

    //! Transform vertex to texture coordinates
    void vertToTex(Real32 *vx, Real32 *vy, Real32 *vz,
                   Real32 *tx, Real32 *ty, Real32 *tz);
    void vertToTex(Vec3f  &vert, 
                   Vec3f  &tex                       );
      
  private:

    Vec3f                  vertex[8];
    Line                   edges[12];
    TextureChunkPtr       *texture;
    UInt32                *texStage;
    Int32                  numTextures;
    Vec3f                  center;
    Real32                 radius;
    Vec3f                  texTranslate;
    Vec3f                  texScale;
    Int32                  voxSize[3];    // Voxelspace size of the brick
    Int32                  minVox[3];
    Vec3f                  m_lowerLeft;   // Geometrical size of the brick
    Vec3f                  m_upperRight;
    BrickSet::Orientation  m_ori;

    // temporary values
    Real32                 distance;
    Brick                 *prev;
    Brick                 *next;

    DVRSlice               slice;
    DVRRenderSlice         clippedSlice;

    //! Render slices
    void render3DSlices     (      DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   DVRShaderPtr    shader, 
                                   DVRClipper     *clipper,
                             const Vec3f          &sliceDir);

    void render2DSlices     (      DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   DVRShaderPtr    shader, 
                                   DVRClipper     *clipper,
                             const Vec3f          &sliceDir);

    void render2DMultiSlices(      DVRVolume      *volume,
                                   DrawActionBase *action,
                                   DVRShaderPtr    shader,
                                   DVRClipper     *clipper,
                                   bool            btf,
                             const Vec3f          &sliceDir);
    
    void render2DSliceXY    (      DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   DVRShaderPtr    shader,   
                                   DVRClipper     *clipper,
                             const Vec3f          &sliceDir,
                             const Real32         &zCoord  );
    
    void render2DSliceXZ    (      DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   DVRShaderPtr    shader,   
                                   DVRClipper     *clipper,
                             const Vec3f          &sliceDir,
                             const Real32         &yCoord  );
    
    void render2DSliceYZ    (      DVRVolume      *volume, 
                                   DrawActionBase *action, 
                                   DVRShaderPtr    shader,   
                                   DVRClipper     *clipper,
                             const Vec3f          &sliceDir,
                             const Real32         &xCoord  );

    friend class BrickSet;
};

OSG_END_NAMESPACE

#include "OSGBrick.inl"
#endif
