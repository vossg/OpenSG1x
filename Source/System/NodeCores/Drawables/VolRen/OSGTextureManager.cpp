#include <OSGConfig.h>

#include "OSGTextureManager.h"

#include <OSGTextureChunk.h>
#include <OSGDrawActionBase.h>
#include <OSGMatrix.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGLog.h>

#include "OSGDVRVolumeTexture.h"
#include "OSGDVRVolume.h"
#include "OSGSlicer.h"
#include "OSGBrick.h"


#define FACE_FRONT  (1)
#define FACE_BACK   (2)
#define FACE_RIGHT  (4)
#define FACE_LEFT   (8)
#define FACE_BOTTOM (16)
#define FACE_TOP    (32) 


OSG_BEGIN_NAMESPACE

//!! --- CLASS TextureRecord -------------------------------------------------

TextureRecord::TextureRecord(ImagePtr img, 
                             UInt32   internal, 
                             UInt32   externalFormat,
                             Int32    stage0, 
                             Int32    stage1) :
    _internalFormat(internal      ),
    _externalFormat(externalFormat),
    _textureStage0 (stage0        ),
    _textureStage1 (stage1        )
{
    _image = img;
    addRefCP(_image);
}

TextureRecord::~TextureRecord()
{
    subRefCP(_image);
    _image = NullFC;
}


//!! --- CLASS TextureManager ------------------------------------------------


TextureManager::TextureManager(DVRVolume *volume) :
    _registeredTextures(    ),
    _parent            (NULL),
    _brickSets         (NULL)
{
    _parent   = volume;
    _brickSets = new BrickSet[3];
}

TextureManager::~TextureManager()
{
    clearTextures();

    delete [] _brickSets;
}

//! Register texture
Int32 TextureManager::registerTexture(ImagePtr image,
                                      UInt32   internalFormat,
                                      UInt32   externalFormat,
                                      bool     /*doBricking*/,
                                      Int32    textureStage0,
                                      Int32    textureStage1)
{ 
    FDEBUG(("TextureManager::registerTexture stage0: %d - stage1: %d\n",
            textureStage0, textureStage1));
    
    //!! TODO:
    //!! make shure the user specifies two texture stages for mt-slab mode
    //!! (e.g. accept only textures with two stages set once two stages have
    //!!       been specified).
    
    // check for unique texture stages
    bool unique = true;

    for(UInt32 i = 0; i < _registeredTextures.size(); i++)
    {
        if(textureStage0 == _registeredTextures[i]->_textureStage0 ||
           textureStage0 == _registeredTextures[i]->_textureStage1  )
        {
            unique = false;
        }

        if((textureStage1 != -1                                    ) &&
           (textureStage1 == _registeredTextures[i]->_textureStage0 ||
            textureStage1 == _registeredTextures[i]->_textureStage1  )  )
        {
            unique = false;
        }
    }

    if(unique == false)
    {
        SWARNING << "TextureManager::registerTexture - "
                 << "ID already in use -> ignoring texture" 
                 << std::endl;
        return -1;
    }

    // store record
    TextureRecord * record = new TextureRecord(image,
                                               internalFormat,
                                               externalFormat,
                                               textureStage0,
                                               textureStage1);
    _registeredTextures.push_back(record);
    
    return _registeredTextures.size() - 1; 
}


//! Remove texture
void TextureManager::unregisterTexture(Int32 id)
{
    FDEBUG(("TextureManager::unregisterTexture\n"));

    if((id < 0) || (UInt32(id) > _registeredTextures.size()))
    {
        SWARNING << "TextureManager::unregisterTexture - invalid id " 
                 << id 
                 << std::endl;
        return;
    }

    TextureSet::iterator iter = _registeredTextures.begin();

    delete _registeredTextures[id];

    _registeredTextures.erase(iter + id);
}


//! Reload texture
void TextureManager::reloadTexture(Int32 id, DrawActionBase *action)
{
    if((id < 0) || (UInt32(id) > _registeredTextures.size()))
    {
        SWARNING << "TextureManager::reloadTexture - invalid id " 
                 << id 
                 << std::endl;
        return;
    }
    
    for(UInt32 k = 0; k < 3; k++)
    {
        _brickSets[k].reloadBrickTextures(
            action, 
            _registeredTextures[id]->_textureStage0);

        _brickSets[k].reloadBrickTextures(
            action, 
            _registeredTextures[id]->_textureStage1);
    }
}


//! Clear all registered textures
void TextureManager::clearTextures(ChunkMaterialPtr material)
{
    FDEBUG(("TextureManager::clearTexture\n"));

    //!! TODO: destroy created texture chunks - even if material is not known

    if (material != NullFC) 
    {
        for(UInt32 k = 0; k < 3; k++) 
        {
            _brickSets[k].clearBrickTextures(material);

            delete [] _brickSets[k].m_pBricks;
            
            _brickSets[k].m_pBricks    = 0;
            _brickSets[k].m_nNumBricks = 0;
        }
    }
    
    for(UInt32 i = 0; i < _registeredTextures.size(); i++)
    {
        delete _registeredTextures[i];
    } 

    _registeredTextures.clear();
}
      

//! Create texture chunks for registered textures
void TextureManager::buildTextures(ChunkMaterialPtr  material,
                                   DVRVolume        *volume,
                                   TextureMode       textureMode)
{
    FDEBUG(("TextureManager::buildTextures\n"));

    DVRVolumeTexturePtr vT = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(vT == NullFC) 
    {
        SWARNING << "TextureManager::buildTextures - No Volume" << std::endl;
        return;
    }

    if(_registeredTextures.size() < 1) 
    {
        SWARNING << "TextureManager::buildTextures - No registerd textures" 
                 << std::endl;
        return;
    }
    
    switch(textureMode)
    {
        case TM_2D_Multi:
        {
            // Multi-Texture Slabs
            Vec3f res = vT->getResolution();

            Vec3f brickSizeX(2,      res[1], res[2]);
            Vec3f brickSizeY(res[0], 2,      res[2]);
            Vec3f brickSizeZ(res[0], res[1], 2     );
            
            _brickSets[BrickSet::XY].buildBricks3D(volume, 
                                                   brickSizeZ, 
                                                   1, 
                                                   BrickSet::XY);
            _brickSets[BrickSet::XZ].buildBricks3D(volume, 
                                                   brickSizeY, 
                                                   1, 
                                                   BrickSet::XZ);
            _brickSets[BrickSet::YZ].buildBricks3D(volume, 
                                                   brickSizeX, 
                                                   1, 
                                                   BrickSet::YZ);
            
            _brickSets[BrickSet::XY].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            _brickSets[BrickSet::XZ].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            _brickSets[BrickSet::YZ].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            
            break;
        }
        case TM_2D:
        {
            // Ordinary 2D-Slices
            _brickSets[BrickSet::XY].buildBricks2D(volume, BrickSet::XY);
            _brickSets[BrickSet::XZ].buildBricks2D(volume, BrickSet::XZ);
            _brickSets[BrickSet::YZ].buildBricks2D(volume, BrickSet::YZ);
            
            _brickSets[BrickSet::XY].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            _brickSets[BrickSet::XZ].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            _brickSets[BrickSet::YZ].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode); 
            
            break;
        }

        default:
        case TM_3D:
        {
            // Ordinary 3D-Bricks
            Vec3f res              = vT->getResolution();
            Vec3f brickSubdivision = 
                calcBrickSubdivision(int(res[0]), 
                                     int(res[1]), 
                                     int(res[2]),
                                     vT->getImage()->getBpp(), volume);

            Vec3f brickSize(Real32((int)(res[0] / brickSubdivision[0])),
                            Real32((int)(res[1] / brickSubdivision[1])),
                            Real32((int)(res[2] / brickSubdivision[2])));
            

            FDEBUG(
                ("TextureManager::buildTextures - BrickSubdivision %d %d %d\n",
                 brickSubdivision[0], 
                 brickSubdivision[1], 
                 brickSubdivision[2]));
            
            _brickSets[BrickSet::XY].buildBricks3D(volume, 
                                                   brickSize, 
                                                   volume->getBrickOverlap());
            
            _brickSets[BrickSet::XY].buildBrickTextures( material, 
                                                        _registeredTextures, 
                                                         textureMode);
            
            break;
        }
    }
}


//! Output the instance for debug purposes
void TextureManager::dump(      UInt32     /*uiIndent*/, 
                          const BitVector  /*bvFlags*/) const
{
    SLOG << "TextureManager:" << std::endl;

    for (UInt32 i = 0; i < _registeredTextures.size(); i++)
    {
        SLOG << "image:          " << _registeredTextures[i]->_image 
             << std::endl;
        SLOG << "internalFormat: " << _registeredTextures[i]->_internalFormat 
             << std::endl;
        SLOG << "textureStage0:  " << _registeredTextures[i]->_textureStage0 
             << std::endl;
        SLOG << "textureStage1:  " << _registeredTextures[i]->_textureStage1 
             << std::endl;
    } 
}


Vec3f TextureManager::calcBrickSubdivision(Int32      resX, 
                                           Int32      resY, 
                                           Int32      resZ, 
                                           Int32      dataSize, 
                                           DVRVolume *volume)
{
    Int32 mode = volume->getBrickingMode();

    
    Vec3f subdivision(1,1,1);
    
    switch (mode) 
    {
        case BRICK_SUBDIVIDE_STATIC:
        {
            subdivision = volume->getBrickStaticSubdivision();
            break;
        }
        
        case BRICK_SUBDIVIDE_ON_TEXTURE_MEMORY:
        {
            Real32 fMB_available = 
                1024.0F * 1024.0F * (Real32) volume->getBrickStaticMemoryMB();

            Real32 fMB_required  = (Real32) (resX * resY * resZ * dataSize);

            Int32 nNumBricks     = (Int32) osgceil(fMB_required / 
                                                   fMB_available);
            Int32 nRealNumBricks = 1;

            while(nNumBricks > nRealNumBricks) 
            {
                if ((resX >= resY) && (resX >= resZ)) 
                {
                    resX /= 2;
                    subdivision[0] *= 2;
                } 
                else if (resY >= resZ) 
                {
                    resY /= 2;
                    subdivision[1] *= 2;
                    
                }
                else 
                {
                    resZ /= 2;
                    subdivision[2] *= 2;
                }
                
                nRealNumBricks = 
                    (Int32)(subdivision[0] * subdivision[1] * subdivision[2]);
            }
            break;
        }
        
        case BRICK_SUBDIVIDE_ON_BRICK_SIZE:
        {
            Vec3f maxSize = volume->getBrickMaxSize();
            
            while(resX > (Int32) maxSize[0]) 
            {
                resX /= 2;
                subdivision[0] *= 2;
            }
            while(resY > (Int32) maxSize[1]) 
            {
                resY /= 2;
                subdivision[1] *= 2;
            }
            while(resZ > (Int32) maxSize[2]) 
            {
                resZ /= 2;
                subdivision[2] *= 2;
            }
            break;
        }
        
    }
    return subdivision;
}


Brick *TextureManager::sortBricks(DrawActionBase *da, 
                                  Matrix          modelMat, 
                                  Vec3f           eyePoint, 
                                  DVRVolume      * /*volume*/, 
                                  TextureMode     mode) 
{
    
    FDEBUG(("TextureManager::sortBricks\n"));

    if ((mode == TM_2D) || (mode == TM_2D_Multi)) 
    {
        // select the right bickset
        BrickSet::Orientation ori = BrickSet::XY;
        bool                  btf = true;

        switch(Slicer::getSlicingDirection(da,NULL))
        {
            case Slicer::SD_X_FRONT_TO_BACK:
                ori = BrickSet::YZ;
                btf = false;
                break;
            case Slicer::SD_X_BACK_TO_FRONT:
                ori = BrickSet::YZ;
                btf = true;
                break;
            case Slicer::SD_Y_FRONT_TO_BACK:
                ori = BrickSet::XZ;
                btf = false;
                break;
            case Slicer::SD_Y_BACK_TO_FRONT:
                ori = BrickSet::XZ;
                btf = true;
                break;
            case Slicer::SD_Z_FRONT_TO_BACK:
                ori = BrickSet::XY;
                btf = false;
                break;
            case Slicer::SD_Z_BACK_TO_FRONT:
                ori = BrickSet::XY;
                btf = true;
                break;
            default:
                break;
        }
        
    // btf or ftb? 
        return _brickSets[ori].sortBricks2D(btf);
    } 
    else 
    {
        return _brickSets[BrickSet::XY].sortBricks3D(modelMat, eyePoint);
    }
}


OSG_END_NAMESPACE


