#include <OSGConfig.h>

#include <OSGBrick.h>

#include <OSGSlicer.h>
#include <OSGDVRClipper.h>
#include <OSGDVRVolume.h>
#include <OSGDVRClipObjects.h>
#include <OSGDVRVolumeTexture.h>


#define FACE_FRONT  (1)
#define FACE_BACK   (2)
#define FACE_RIGHT  (4)
#define FACE_LEFT   (8)
#define FACE_BOTTOM (16)
#define FACE_TOP    (32) 


OSG_BEGIN_NAMESPACE

BrickSet::~BrickSet()
{
    delete [] m_pBricks;
}

void BrickSet::buildBricks3D(DVRVolume   *volume, 
                             Vec3f        brickSize, 
                             Int32        overlap, 
                             Orientation  ori)
{
    FDEBUG(("BrickSet::buildBricks3D %d %d %d\n", 
            brickSize[0],
            brickSize[1], 
            brickSize[2]));

    SINFO << "BrickSet::buildBricks3D (size)" 
          << brickSize[0] << ", " 
          << brickSize[1] << ","
          << brickSize[2] << std::endl;
    
    m_nOrientation = ori;
    
    DVRVolumeTexturePtr vT = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(vT == NullFC) 
    {
        SWARNING << "BrickSet::buildTextures3D - No Volume" << std::endl;
        return;
    }

    if((brickSize[0] <= overlap) || 
       (brickSize[1] <= overlap) || 
       (brickSize[2] <= overlap)  )
    {
        SFATAL << "BrickSet::buildBricks3D - brickSize too small: "
               << brickSize[0] << ","
               << brickSize[1] << "," 
               << brickSize[2] << "for overlap " 
               << overlap << std::endl;

        return;
    }
    
    Vec3f vox  = vT->getSliceThickness();
    Vec3f res  = vT->getResolution();
    Int32 resX = (Int32) res[0];
    Int32 resY = (Int32) res[1];
    Int32 resZ = (Int32) res[2];

    Int32 nNumBricksX = Int32((resX - overlap) / (brickSize[0] - overlap));
    Int32 nNumBricksY = Int32((resY - overlap) / (brickSize[1] - overlap));
    Int32 nNumBricksZ = Int32((resZ - overlap) / (brickSize[2] - overlap));

    SINFO << "BrickSet::buildBricks3D (num)" 
          << nNumBricksX << ", " 
          << nNumBricksY << ","
          << nNumBricksZ << std::endl;
    
    m_nNumBricks = nNumBricksX * nNumBricksY * nNumBricksZ; 

    m_pBricks = new Brick[m_nNumBricks];
    
    Int32 nBrickSizeX = Int32(brickSize[0]);
    Int32 nBrickSizeY = Int32(brickSize[1]);
    Int32 nBrickSizeZ = Int32(brickSize[2]);

    Int32 nXMin = 0;
    Int32 nYMin = 0;
    Int32 nZMin = 0;

    Real32 xmin = (overlap - 1 + 0.5f - resX / 2) * vox[0];
    Real32 ymin = (overlap - 1 + 0.5f - resY / 2) * vox[1];
    Real32 zmin = (overlap - 1 + 0.5f - resZ / 2) * vox[2];

    Real32 xmax = 0, ymax = 0, zmax = 0;
    
    Int32 index = 0;
    
    for(Int32 z = 0; z < nNumBricksZ; z++) 
    {
        nYMin = 0;
        ymin  = (overlap - 1 + 0.5f - resY / 2) * vox[1];
        
        for(Int32 y = 0; y < nNumBricksY; y++) 
        {
            nXMin = 0;
            xmin  = (overlap - 1 + 0.5f - resX / 2) * vox[0];
            
            for(Int32 x = 0; x < nNumBricksX; x++) 
            {
                xmax = xmin + (nBrickSizeX - (2 * (overlap - 1) + 1)) * vox[0];
                ymax = ymin + (nBrickSizeY - (2 * (overlap - 1) + 1)) * vox[1];
                zmax = zmin + (nBrickSizeZ - (2 * (overlap - 1) + 1)) * vox[2];
                
                m_pBricks[index].init(nXMin,       nYMin,       nZMin,
                                      nBrickSizeX, nBrickSizeY, nBrickSizeZ,
                                      xmin,        ymin,        zmin,
                                      xmax,        ymax,        zmax,
                                      overlap, 
                                      ori                                  );
                
                index++;

                nXMin += nBrickSizeX - (2 * overlap - 1);
                xmin   = xmax; 
            }

            nYMin += nBrickSizeY - (2 * overlap - 1);
            ymin   = ymax;
        }
        
        nZMin += nBrickSizeZ - (2 * overlap - 1);
        zmin   = zmax;
    }
}


void BrickSet::buildBricks2D(DVRVolume *volume, Orientation ori)
{
    m_nOrientation = ori;
    
    DVRVolumeTexturePtr vT = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(vT == NullFC) 
        return;
    
    Vec3f  vox = vT->getSliceThickness();
    Vec3f  res = vT->getResolution();

    Int32  resX = 0, resY= 0, resZ= 0;
    Real32 xmin = 0, ymin = 0, zmin = 0;             
    Real32 xmax = 0, ymax = 0, zmax = 0;          
    Real32 xinc = 0, yinc = 0, zinc = 0;
    
    switch(ori) 
    {
        case XY: 
        {
            // XY stack of textures
            resX  = (Int32) res[0];
            resY  = (Int32) res[1];
            resZ  = 1;
            
            xinc = 0;
            yinc = 0;
            zinc = 1;

            // "geometrical" size of the brick
            xmin = (-(res[0] - 1) / 2) * vox[0];  
            ymin = (-(res[1] - 1) / 2) * vox[1];
            zmin = (-(res[2]    ) / 2) * vox[2];
            
            xmax = -xmin;
            ymax = -ymin;
            zmax =  zmin + zinc * vox[2];

            m_nNumBricks = (int) res[2];
            m_pBricks    = new Brick[m_nNumBricks];

            break;
        }

        case XZ: 
        {
            // XZ stack of textures
            resX  = (Int32) res[0];
            resY  = 1;
            resZ  = (Int32) res[2];
            
            xinc = 0;
            yinc = 1;
            zinc = 0;
            
            // "geometrical" size of the brick
            xmin = (-(res[0] - 1) / 2) * vox[0];  
            ymin = (-(res[1]    ) / 2) * vox[1];
            zmin = (-(res[2] - 1) / 2) * vox[2];
            
            xmax = -xmin;
            ymax =  ymin + yinc * vox[1];
            zmax = -zmin;
            
            m_nNumBricks = (int) res[1];
            m_pBricks    = new Brick[m_nNumBricks];

            break;
        }

        case YZ: 
        {
            // YZ stack of textures
            resX  = 1;
            resY  = (Int32) res[1];
            resZ  = (Int32) res[2];
            
            xinc = 1;
            yinc = 0;
            zinc = 0;
            
            // "geometrical" size of the brick
            xmin = (-(res[0]    ) / 2) * vox[0];  
            ymin = (-(res[1] - 1) / 2) * vox[1];
            zmin = (-(res[2] - 1) / 2) * vox[2];
            
            xmax =  xmin + xinc * vox[0];
            ymax = -ymin;
            zmax = -zmin;
            
            m_nNumBricks = (int) res[0];
            m_pBricks    = new Brick[m_nNumBricks];

            break;
        }

        case UNDEF: 
        {
            SFATAL << "BrickSet::buildBricks2D called with unspecified "
                   << "orientation" 
                   << std::endl;
            break;
        }
    }
    
    for(Int32 index = 0; index < m_nNumBricks; index++) 
    {
        m_pBricks[index].init(resX == 1 ? index : 0,
                              resY == 1 ? index : 0,
                              resZ == 1 ? index : 0,
                              resX, resY, resZ,
                              xmin, ymin, zmin,
                              xmax, ymax, zmax, 
                              1, 
                              ori);
        
        xmin += xinc * vox[0];
        xmax += xinc * vox[0];
        
        ymin += yinc * vox[1];
        ymax += yinc * vox[1];
        
        zmin += zinc * vox[2];
        zmax += zinc * vox[2];
    }
}


//! Create texture chunk for image
TextureChunkPtr BrickSet::makeTexture(UInt32   internalFormat,
                                      UInt32   externalFormat,
                                      ImagePtr img) 
{
    TextureChunkPtr chunk = TextureChunk::create();

    beginEditCP(chunk);
    {
        chunk->setImage         (img           );
        chunk->setInternalFormat(internalFormat);
        chunk->setExternalFormat(externalFormat);

        FDEBUG(("TextureManager - makeTexture: intern %d - extern %d\n",
                internalFormat, externalFormat));

        //!! FIXME: this is required by the PreIntegration shader but
        //!! may not be supported on all OpenSG platforms - so we must
        //!! add a way that the shader can specify the wrapping
#if defined GL_ARB_texture_border_clamp
        chunk->setWrapS(GL_CLAMP_TO_BORDER);
        chunk->setWrapT(GL_CLAMP_TO_BORDER);
        chunk->setWrapR(GL_CLAMP_TO_BORDER);
#else
//      chunk->setWrapS(GL_CLAMP_TO_EDGE);
//      chunk->setWrapT(GL_CLAMP_TO_EDGE);
//      chunk->setWrapR(GL_CLAMP_TO_EDGE);
        
        chunk->setWrapS(GL_CLAMP);
        chunk->setWrapT(GL_CLAMP);
        chunk->setWrapR(GL_CLAMP);
#endif

        chunk->setMinFilter(GL_LINEAR);
        chunk->setMagFilter(GL_LINEAR);
    
//      chunk->setEnvMode(GL_REPLACE);
        chunk->setEnvMode(GL_MODULATE);
    }
    endEditCP(chunk);

    return chunk;
}


//! Build textures for bricks
void BrickSet::buildBrickTextures(ChunkMaterialPtr            &material,
                                  TextureSet                  &textures,
                                  TextureManager::TextureMode  mode    )
{
    // overall number of textures
    UInt32 numTextures = textures.size();
    
    if(mode == TextureManager::TM_2D_Multi)
        numTextures *= 2;
    
    beginEditCP(material);
    {
        // build all texture chunks
        for(Int32 index = 0; index < m_nNumBricks; index++)
        {
            Int32 &resX  = m_pBricks[index].voxSize[0];
            Int32 &resY  = m_pBricks[index].voxSize[1];
            Int32 &resZ  = m_pBricks[index].voxSize[2];
            
            Int32 &nXMin = m_pBricks[index].minVox[0];
            Int32 &nYMin = m_pBricks[index].minVox[1];
            Int32 &nZMin = m_pBricks[index].minVox[2];
            
            int texCounter = 0;
            
            m_pBricks[index].texture     = new TextureChunkPtr[numTextures];
            m_pBricks[index].texStage    = new UInt32[numTextures];
            m_pBricks[index].numTextures = numTextures;
            
            // create texture chunks
            for(UInt32 tch = 0; tch < textures.size(); tch++) 
            { 
                ImagePtr img = Image::create();
                
                switch (mode)
                {
                    case TextureManager::TM_2D_Multi: // 2D multi textures
                    {
                        // first texture
                        textures[tch]->_image->slice(resX == 2 ? nXMin : -1,
                                                     resY == 2 ? nYMin : -1,
                                                     resZ == 2 ? nZMin : -1,
                                                     img);
                        if (index == 0)
                        {
                            m_pBricks[index].texture[texCounter] = 
                                makeTexture(textures[tch]->_internalFormat,
                                            textures[tch]->_externalFormat,
                                            img                           );
                        }
                        else
                        {
                            // each but first brick can reuse texture 
                            // chunks of previous brick

                            m_pBricks[index].texture[texCounter] = 
                                m_pBricks[index-1].texture[texCounter+1];
                        }
                        
                        m_pBricks[index].texStage[texCounter] = 
                            textures[tch]->_textureStage0;

                        material->addChunk(
                            m_pBricks[index].texture[texCounter]);

                        texCounter++;
                        
                        // second texture
                        img = Image::create();

                        textures[tch]->_image->slice(
                            resX == 2 ? nXMin + 1 : -1,
                            resY == 2 ? nYMin + 1 : -1,
                            resZ == 2 ? nZMin + 1 : -1,
                            img                       );

                        m_pBricks[index].texture[texCounter] = 
                            makeTexture(textures[tch]->_internalFormat,
                                        textures[tch]->_externalFormat,
                                        img                           );

                        m_pBricks[index].texStage[texCounter] = 
                            textures[tch]->_textureStage1;

                        material->addChunk(
                            m_pBricks[index].texture[texCounter]);

                        texCounter++;
                        
                        break;
                    }
                    
                    case TextureManager::TM_2D: // 2D ordinary textures
                    {
                        textures[tch]->_image->slice(resX == 1 ? nXMin : -1,
                                                     resY == 1 ? nYMin : -1,
                                                     resZ == 1 ? nZMin : -1,
                                                     img);

                        m_pBricks[index].texture[texCounter] = 
                            makeTexture(textures[tch]->_internalFormat,
                                        textures[tch]->_externalFormat,
                                        img                           );

                        m_pBricks[index].texStage[texCounter] = 
                            textures[tch]->_textureStage0;

                        material->addChunk(
                            m_pBricks[index].texture[texCounter]);

                        texCounter++;
                        
                        break;
                    }
                    
                    case TextureManager::TM_3D: // 3D ordinary textures
                    default:
                    {
                        textures[tch]->_image->subImage(nXMin, nYMin, nZMin,
                                                        resX, resY, resZ,
                                                        img                );

                        m_pBricks[index].texture[texCounter] = 
                            makeTexture(textures[tch]->_internalFormat,
                                        textures[tch]->_externalFormat,
                                        img                           );

                        m_pBricks[index].texStage[texCounter] = 
                            textures[texCounter]->_textureStage0;

                        material->addChunk(
                            m_pBricks[index].texture[texCounter]);

                        texCounter++;
                        
                        break;
                    }
                }
                
            } // for all registered textures
            
        } // for all bricks
    }
    endEditCP(material);
}

    
//! Reload brick textures
void BrickSet::reloadBrickTextures(DrawActionBase *action, UInt32 texStage)
{
    for(Int32 i = 0; i < m_nNumBricks; i++)
    {
        for(Int32 j = 0; j < m_pBricks[i].numTextures; j++)
        {
            if(m_pBricks[i].texStage[j] == texStage)
            {
                action->getWindow()->refreshGLObject(
                    m_pBricks[i].texture[j]->getGLId());
            }
        }
    }
}


//! Clear brick textures
void BrickSet::clearBrickTextures(ChunkMaterialPtr & material)
{
    for(Int32 i = 0; i < m_nNumBricks; i++)
    {
        for(Int32 j = 0; j < m_pBricks[i].numTextures; j++)
        {
            material->subChunk(m_pBricks[i].texture[j]);
        }
    }
}


//! Return sorted brick list
Brick *BrickSet::sortBricks3D(const Matrix & modelMat, const Vec3f & eyePoint)
{
    
    Brick  *BrickList = m_pBricks;

    Int32   nBrick;
    Real32  distance;
    Brick  *previous, *current, *incoming;
    
    Vec3f transformedCenter;

    m_pBricks[0].prev = NULL;
    m_pBricks[0].next = NULL;

    modelMat.multMatrixPnt(m_pBricks[0].center,transformedCenter);

    m_pBricks[0].distance = (eyePoint - transformedCenter).length();
    

    for(nBrick = 1; nBrick < m_nNumBricks; nBrick++) 
    {
        incoming = &(m_pBricks[nBrick]);

        modelMat.multMatrixPnt(incoming->center,transformedCenter);

        distance = (eyePoint - transformedCenter).length();

        incoming->distance = distance;
        incoming->next     = NULL;
        incoming->prev     = NULL;

        current  = BrickList;
        previous = NULL;

        while((current != NULL) && (current->distance > distance)) 
        {
            previous = current;
            current = current->next;
        }

        // insert 
        if (current == NULL) 
        {
            // insert at the end of the list;
            previous->next = incoming;
            incoming->prev = previous;
            
        }
        else
        {
            incoming->next = current;
            incoming->prev = current->prev;
            current->prev  = incoming;

            if (incoming->prev == NULL) 
            {
                BrickList = incoming;
            } 
            else
            {
                incoming->prev->next = incoming;
            }
        }
    }
    
    return BrickList;
}


//! Return sorted brick list
Brick *BrickSet::sortBricks2D(bool backToFront)
{
    Brick *brickList = m_pBricks;
    
    if(brickList) 
    {
        if(backToFront) 
        {
            for(int i = m_nNumBricks - 1; i >= 0; i--) 
            {
                m_pBricks[i].prev = &(m_pBricks[i + 1]);
                m_pBricks[i].next = &(m_pBricks[i - 1]);
            }
            
            m_pBricks[0].next                = NULL;
            m_pBricks[m_nNumBricks - 1].prev = NULL;
            
            brickList = &(m_pBricks[m_nNumBricks - 1]);
        } 
        else 
        {
            for (int i = 0; i < m_nNumBricks; i++) 
            {
                m_pBricks[i].prev = &(m_pBricks[i - 1]);
                m_pBricks[i].next = &(m_pBricks[i + 1]);
            }
            
            m_pBricks[0].prev                = NULL;
            m_pBricks[m_nNumBricks - 1].next = NULL;
            
            brickList = &(m_pBricks[0]);
        }
    }
    
    return brickList;
}


//! Initialize brick size and geometry 
void Brick::init(Int32  minVoxX, Int32  minVoxY, Int32  minVoxZ,
                 Int32  resX,    Int32  resY,    Int32  resZ,
                 Real32 xmin,    Real32 ymin,    Real32 zmin,
                 Real32 xmax,    Real32 ymax,    Real32 zmax,
                 Int32                 overlap, 
                 BrickSet::Orientation ori                     )
{
    
    FINFO(("Brick::init - upper left (%d, %d, %d)\n",
           minVoxX, minVoxY, minVoxZ));

    FINFO(("Brick::init (%d, %d, %d): %f %f %f -> %f %f %f \n",
           resX, resY, resZ, xmin, ymin, zmin, xmax, ymax, zmax));

    Real32 xrange = xmax - xmin;
    Real32 yrange = ymax - ymin;
    Real32 zrange = zmax - zmin;               
    
    minVox[0] = minVoxX;
    minVox[1] = minVoxY;
    minVox[2] = minVoxZ;
    
    voxSize[0] = resX;
    voxSize[1] = resY;
    voxSize[2] = resZ;
    
    m_lowerLeft  = Vec3f(xmin, ymin, zmin);
    m_upperRight = Vec3f(xmax, ymax, zmax);
    
    m_ori = ori;
    
    Real32 texCoorMin[3], texCoorMax[3];
    
    texCoorMin[0] = (2 * Real32(overlap) - 1) / 2.0f / Real32(resX);
    texCoorMin[1] = (2 * Real32(overlap) - 1) / 2.0f / Real32(resY);
    texCoorMin[2] = (2 * Real32(overlap) - 1) / 2.0f / Real32(resZ);
    
    texCoorMax[0] = 1 - texCoorMin[0];
    texCoorMax[1] = 1 - texCoorMin[1];
    texCoorMax[2] = 1 - texCoorMin[2];
    
    texScale = Vec3f((texCoorMax[0] - texCoorMin[0]) / xrange,
                     (texCoorMax[1] - texCoorMin[1]) / yrange,
                     (texCoorMax[2] - texCoorMin[2]) / zrange);

    texTranslate = Vec3f(texCoorMin[0] - texScale[0] * xmin,
                         texCoorMin[1] - texScale[1] * ymin,
                         texCoorMin[2] - texScale[2] * zmin);
    
    FINFO (("Brick::init - overlap:      %d \n", 
            overlap));

    FINFO (("Brick::init - texScale:     %f %f %f \n", 
            texScale[0], texScale[1], texScale[2]));

    FINFO (("Brick::init - texTranslate: %f %f %f \n", 
            texTranslate[0], texTranslate[1], texTranslate[2]));
    
    //!! Initialize edge/vertex structure
    
    //
    //                         e3       
    //          v5 o----------------o v4
    //            /|               /|
    //           / |              / |
    //      e10 /  |          e9 /  |e7
    //         /   |   e1       /   |
    //     v3 o----------------o v2 |
    //        |    |           |    |
    //        |    |e6         |    |
    //        |e5  |           |e4  |
    //        |    |    e2     |    |
    //        |    o-----------|----o v7
    //        |   /  v6        |   /
    //        |  /             |  /
    //        | /e11           | /e8
    //        |/               |/
    //   y    o----------------o
    //   | z  v0      e0       v1
    //   |/
    //   +---x
                
    // ------------- Initialize 8 Vertices -------------

    vertex[0] = Vec3f( xmin,  ymin,  zmin); 
    vertex[1] = Vec3f( xmax,  ymin,  zmin);
    vertex[2] = Vec3f( xmax,  ymax,  zmin);
    vertex[3] = Vec3f( xmin,  ymax,  zmin);
    
    vertex[4] = Vec3f( xmax,  ymax,  zmax);
    vertex[5] = Vec3f( xmin,  ymax,  zmax); 
    vertex[6] = Vec3f( xmin,  ymin,  zmax);
    vertex[7] = Vec3f( xmax,  ymin,  zmax);
    
    center = Vec3f(0.0, 0.0, 0.0);

    for(Int32 j = 0; j < 8; j++) 
    {
        center += vertex[j];
    }

    center /= 8.0;
    radius  = (vertex[0] - center).length();
    
    // -------------- Initialize 12 Edges --------------

    const int eindex[12][2] = 
    {
        {0, 1}, // e0
        {2, 3}, // e1
        {6, 7}, // e2
        {4, 5}, // e3
        {1, 2}, // e4
        {0, 3}, // e5
        {5, 6}, // e6
        {4, 7}, // e7
        {1, 7}, // e8
        {2, 4}, // e9
        {3, 5}, // e10
        {0, 6}  // e11
    };
    
    for(Int32 i = 0; i < 12; i++) 
    {
        edges[i] = Line(Pnt3f(vertex[eindex[i][0]]),
                        Pnt3f(vertex[eindex[i][1]]));
    }
    
#if 0
    TOUT("Init Brick");
    TOUT("Brick (" << x << ", " << y << ", " << z << ")");
    TOUT(VARDUMP(nXMin) << ", " << VARDUMP(nXMax));
    TOUT(VARDUMP(nYMin) << ", " << VARDUMP(nYMax));
    TOUT(VARDUMP(nZMin) << ", " << VARDUMP(nZMax));
    TOUT(VARDUMP(nDataSize));
#endif
}


//! Activate textures
void Brick::activateTexture(DrawActionBase *action)
{
    for(Int32 i = 0; i < numTextures; i++) 
    {
        FDEBUG(("Brick::activateTexture - Brick: %d - Texture %d "
                "- Stage: %d - ID: %d\n",
                this, i, texStage[i], texture[i]->getGLId()));

        texture[i]->activate(action, texStage[i]);
    }
}


//! Change active texture 
void Brick::changeFromTexture(DrawActionBase *action, Brick *old)
{
    FDEBUG(("Brick::changeFromTexture\n"));
    
    if(old == NULL)
        activateTexture(action);
    
    for(Int32 i = 0; i < numTextures; i++)
    {
        texture[i]->changeFrom(action, &(*(old->texture[i])), texStage[i]);
    }
}


//! Deactivate textures
void Brick::deactivateTexture(DrawActionBase *action)
{
    for(Int32 i = 0; i < numTextures; i++) 
    {
        texture[i]->deactivate(action, texStage[i]);
    }
    
}


//! Render 2D/3D Slices
void Brick::renderSlices(DVRVolume                   *volume, 
                         DrawActionBase              *action,
                         DVRShaderPtr                 shader,  
                         DVRClipper                  *clipper,
                         TextureManager::TextureMode  textureMode)
{  
    switch (textureMode)
    {
        case TextureManager::TM_2D:
        {
            GLboolean val;
            glGetBooleanv(GL_TEXTURE_3D, &val);

            if(val != 0) 
            {
                glDisable(GL_TEXTURE_3D);
                SWARNING << "Brick::renderSlices - 3DTextures enabled "
                         << "-> DISABLING " 
                         << (int) val 
                         << std::endl;
            }

            Vec3f sliceDir;

            Slicer::getAASlicingDirection(action, &sliceDir);

            render2DSlices(volume, action, shader, clipper, sliceDir);

            break;
        }
        case TextureManager::TM_2D_Multi:
        {
            FDEBUG(("Brick::renderSlices - 2D MTex Slabs\n"));

            Vec3f sliceDir;

            Int32 dir = Slicer::getAASlicingDirection(action, &sliceDir);

            render2DMultiSlices(volume, action, shader, clipper,
                                Slicer::isBackToFront(dir),sliceDir);
            break;
        }

        default:
        case TextureManager::TM_3D:
        {
            FDEBUG(("Brick::renderSlices -3D slices\n"));

            Vec3f sliceDir;

            Slicer::getSlicingDirection(action, &sliceDir);

            render3DSlices(volume, action, shader, clipper, sliceDir);

            break;
        }
    }
}


//! Render brick bounding box
void Brick::renderBrick()
{
    FDEBUG(("Brick::renderBrick"));
    
    const int eindex[12][2] = 
    {
        {0,1}, 
        {2,3}, 
        {6,7}, 
        {4,5}, 
        {1,2}, 
        {0,3}, 
        {5,6}, 
        {4,7}, 
        {1,7}, 
        {2,4}, 
        {3,5}, 
        {0,6}
    };
    
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable   (GL_TEXTURE_3D);
    glDisable   (GL_TEXTURE_2D);

    glColor4f   (1.0, 0.0, 0.0, 1.0 );
    
    glBegin(GL_LINES);
    {
        for(Int32 i = 0; i < 12; i++) 
        {
            glVertex3fv(vertex[eindex[i][0]].getValues());
            glVertex3fv(vertex[eindex[i][1]].getValues());
        }
    }
    glEnd();
    
    glPopAttrib();
}


//! Transform vertex to texture coordinates
void Brick::vertToTex(Real32 *vx, Real32 *vy, Real32 *vz,
                      Real32 *tx, Real32 *ty, Real32 *tz)
{
    *tx = *vx * texScale[0] + texTranslate[0];
    *ty = *vy * texScale[1] + texTranslate[1]; 
    *tz = *vz * texScale[2] + texTranslate[2];
}


//! Transform vertex to texture coordinates
void Brick::vertToTex(Vec3f &vert, Vec3f &tex)
{
    tex[0] = vert[0] * texScale[0] + texTranslate[0];
    tex[1] = vert[1] * texScale[1] + texTranslate[1];
    tex[2] = vert[2] * texScale[2] + texTranslate[2];
};


//! Render 3D Slices
void Brick::render3DSlices(DVRVolume      *volume,
                           DrawActionBase *action,
                           DVRShaderPtr    shader,
                           DVRClipper     *clipper,
                           const Vec3f    &sliceDir)
{
    Int32 i, j;

    DVRVolumeTexturePtr tex = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(tex == NullFC) 
        return;
    
    Vec3f res            = tex->getResolution();
    Vec3f vox            = tex->getSliceThickness();

    Real32 fSampleRate    = volume->getSampling();
    Real32 fSliceDistance = vox.length() / 2.0f / fSampleRate;
    Real32 fTolerance     = fSliceDistance / 100.0f;
    Real32 fAlphaCorrect  = 1.f - osgpow(1.f  - volume->getBaseAlpha(), 
                                         1.0f / fSampleRate           );
    
    SINFO << "Sampling rate: "
          << fSampleRate 
          << " Alpha-Correction " 
          << fAlphaCorrect
          << std::endl;
    
    Vec3f diag(res[0]*vox[0], res[1]*vox[1], res[2]*vox[2]);

    Real32 fRadius = 0.5f * diag.length();
    
    const int ecodes[12] = 
    {
        (FACE_FRONT  + FACE_BOTTOM), // edge 0
        (FACE_FRONT  + FACE_TOP   ), // edge 1
        (FACE_BACK   + FACE_BOTTOM), // edge 2
        (FACE_BACK   + FACE_TOP   ), // edge 3

        (FACE_FRONT  + FACE_RIGHT ), // edge 4
        (FACE_FRONT  + FACE_LEFT  ), // edge 5
        (FACE_BACK   + FACE_LEFT  ), // edge 6
        (FACE_BACK   + FACE_RIGHT ), // edge 7

        (FACE_RIGHT  + FACE_BOTTOM), // edge 8
        (FACE_RIGHT  + FACE_TOP   ), // edge 9
        (FACE_TOP    + FACE_LEFT  ), // edge 10
        (FACE_BOTTOM + FACE_LEFT  )  // edge 11
    };
    
    // get the slicing normal
    Vec3f vecViewDir = sliceDir;

    Plane planeSlice(vecViewDir, -fRadius);

    Int32 numSlices = 1 + (Int32) (2.0f * fRadius/ fSliceDistance); 
    
    Vec3f   vecIntersections[12];
    Int32   nEdgeCodes[12];

    bool    bIntersectionUsed[12];

    Vec3f   vecIntersectionsSorted[12];
    Vec3f   vecIntersection;

    Int32   nSlice, numIntersections, nEdgeCode, numUsedIntersections;

    Vec3f   v, texscale, textrans; 

    texscale = texScale;
    textrans = texTranslate;

    // set the reference plane for clipping
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);

    bool doClipping = false;

    if(clipObjects != NullFC)
    {
        if(clipObjects->count()       >  0                && 
           clipObjects->getClipMode() != DVRClipObjects::Off)
        {
            doClipping = true;
            clipper->reset(volume);
        }
    }

    slice.setTextureTransform(texScale,texTranslate);

    for(nSlice = 0; nSlice < numSlices; nSlice++) 
    {
        
        // calculate intersection with each edge
        numIntersections = 0;

        for(i = 0; i < 12; i++) 
        {
            if(planeSlice.intersect(edges[i],vecIntersection)) 
            {
                
                if((vecIntersection-center).length() <= radius) 
                {
                    vecIntersections[numIntersections]  = vecIntersection;
                    nEdgeCodes[numIntersections]        = ecodes[i];
                    bIntersectionUsed[numIntersections] = false;

                    numIntersections++;
                }
            }
        }
        
        // eleminate double vertices
        // --------------------------------------------

        if (numIntersections > 2) 
        {
            for(i = 0; i < numIntersections-1; i++) 
            {
                for(j = i+1; j < numIntersections; j++) 
                {
                    if((vecIntersections[i]-vecIntersections[j]).length() < 
                       fTolerance) 
                    {
                        // merge the two intersections
                        nEdgeCodes[i] |= nEdgeCodes[j];
                        // remove j
                        if(j < numIntersections-1) 
                        {
                            vecIntersections[j] = 
                                vecIntersections[numIntersections-1];
                            nEdgeCodes[j] = nEdgeCodes[numIntersections-1];

                            // vertex j has changed, so examine the 
                            // vertex j again
                            j--; 
                        }

                        numIntersections--;
                    }
                }
            }
        }
        
        assert(numIntersections <= 6);
        
        if(numIntersections > 2) 
        {
            
            //find correct sequence;
            vecIntersectionsSorted[0] = vecIntersections[0];
            bIntersectionUsed[0]      = true;
            numUsedIntersections      = 1;
              
            nEdgeCode = nEdgeCodes[0];

            // HACK need to fix the endless loop!
            UInt32 count = 0;
            while(numUsedIntersections != numIntersections && ++count <= numIntersections)
            {
                for(Int32 i = 1; i < numIntersections; i++) 
                {
                    if ((bIntersectionUsed[i] == false   ) && 
                        (nEdgeCodes[i]        & nEdgeCode)  ) 
                    {
                        vecIntersectionsSorted[numUsedIntersections] = 
                            vecIntersections[i];

                        nEdgeCode            = nEdgeCodes[i];
                        bIntersectionUsed[i] = true;

                        numUsedIntersections++;
                    }
                }
            }
            
            if(doClipping)
            {
                // check slice orientation
                Vec3f sliceNormal = 
                    (vecIntersectionsSorted[1] -
                     vecIntersectionsSorted[0]).cross(
                         vecIntersectionsSorted[2]-vecIntersectionsSorted[1]);
                
                bool sliceCCW = sliceNormal.dot(sliceDir) > 0.0; 
                
                slice.resetSlice();
                
                if(sliceCCW)
                {
                    for(Int32 i = 0; i < numIntersections; i++)
                    {
                        slice.setVertex(vecIntersectionsSorted[i]);
                    }
                }
                else
                {
                    for(Int32 i = numIntersections-1; i >=0 ; i--)
                    {
                        slice.setVertex(vecIntersectionsSorted[i]);
                    }       
                }
                
                slice.setNormal(sliceDir);
                
                // number of additional per vertex attributes 
                // (not position + first texture coordinates)

                clippedSlice.numPerVertexData = 0;
                
                // we use 3D textures
                clippedSlice.orientation = DVRRenderSlice::UNDEFINED;
                
                // contours only
                if(clipObjects->getDoContours())
                {
                    deactivateTexture(action);
                    clipper->clipSlice(volume, 
                                       slice, 
                                       sliceDir,
                                       fSliceDistance * nSlice, 
                                       clippedSlice);
                    activateTexture(action);
                }        
                else if (shader->hasRenderCallback()) 
                {
                    // shader managed slice rendering
                    
                    clippedSlice.directRender = false;
                    
                    clipper->clipSlice(volume, slice, 
                                       sliceDir,
                                       fSliceDistance * nSlice, 
                                       clippedSlice);
                    
                    shader->renderSlice(volume, action, &clippedSlice);
                } 
                else if (volume->getDoTextures()) 
                {
                    // textured slices
                    
                    clippedSlice.directRender = true;
                    
                    clipper->clipSlice(volume, 
                                       slice, 
                                       sliceDir,
                                       fSliceDistance * nSlice, 
                                       clippedSlice);
                }
                else 
                {
                    // untextured slices only

                    glColor4f(1.0, 1.0, 1.0, 1.0);

                    clippedSlice.directRender = true;   
    
                    clipper->clipSlice(volume, 
                                       slice, 
                                       sliceDir,
                                       fSliceDistance * nSlice, 
                                       clippedSlice);
                }
                clippedSlice.clear();
            }      
            else
            { 
                // clipping disabled    
                
                if(shader->hasRenderCallback()) 
                {
                    
                    // copy all data into a single field and 
                    // call rendercallback

                    Real32 data[12 * 6]; // numIntersections is bounded by 12
                    UInt32 index = 0;

                    for(Int32 i = 0; i < numIntersections; i++) 
                    {
                        v = vecIntersectionsSorted[i];
                        
                        data[index++] = v[0];
                        data[index++] = v[1];
                        data[index++] = v[2];
                        
                        data[index++] = v[0] * texscale[0] + textrans[0];
                        data[index++] = v[1] * texscale[1] + textrans[1];
                        data[index++] = v[2] * texscale[2] + textrans[2];
                    }
                    
                    shader->renderSlice(volume, 
                                        action, 
                                        data, 
                                        numIntersections, 
                                        6);
                } 
                else if (volume->getDoTextures()) 
                {
                    // textured slices
                    
                    glBegin(GL_TRIANGLE_FAN);
                    
                    for(i = 0; i < numIntersections; i++) 
                    {
                        v = vecIntersectionsSorted[i];
                        
                        glColor4f(1.0, 1.0, 1.0, fAlphaCorrect);

                        glTexCoord3f((v[0] * texscale[0] + textrans[0]), 
                                     (v[1] * texscale[1] + textrans[1]) , 
                                     (v[2] * texscale[2] + textrans[2]));
                        glVertex3fv(v.getValues());
                        
                        FDEBUG(
                            ("Brick::render3DSlices V: %f %f %f T: %f %f %f\n",
                             v[0], v[1], v[2],
                             (v[0] * texscale[0] + textrans[0]), 
                             (v[1] * texscale[1] + textrans[1]), 
                             (v[2] * texscale[2] + textrans[2])));
                    }

                    glEnd();
                    
                }
                else 
                {
                    // untextured slices only
                    
                    glColor4f(1.0, 1.0, 1.0, 1.0);

                    glBegin(GL_LINE_LOOP);
                    {
                        for(i = 0; i < numIntersections; i++) 
                        {
                            v = vecIntersectionsSorted[i];

                            glVertex3fv(v.getValues());
                        }
                    }                    
                    glEnd();
                }
            }
        }
        
        // next plane
        planeSlice.offset(fSliceDistance);
    }
}


void Brick::render2DSliceXY(DVRVolume      *volume, 
                            DrawActionBase *action, 
                            DVRShaderPtr    shader, 
                            DVRClipper     *clipper,
                            const Vec3f    &sliceDir,
                            const Real32   &zCoord)
{
    Real32 xmin = vertex[0][0];
    Real32 xmax = vertex[1][0];
    
    Real32 ymin = vertex[0][1];
    Real32 ymax = vertex[2][1]; 
  
    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);
  
    // check whether clipping should be performed
    bool doClipping = false;  
    if(clipObjects != NullFC)
    {
        if(clipObjects->count()       >  0                && 
           clipObjects->getClipMode() != DVRClipObjects::Off)
        {
            doClipping = true;
        }
    }
    
    if(doClipping)
    {
        slice.resetSlice();
        
        if(sliceDir[2] > 0.0)
        {
            slice.setVertex(Vec3f(xmin, ymin, zCoord));
            slice.setVertex(Vec3f(xmax, ymin, zCoord));
            slice.setVertex(Vec3f(xmax, ymax, zCoord));
            slice.setVertex(Vec3f(xmin, ymax, zCoord));
        }
        else
        {
            slice.setVertex(Vec3f(xmin, ymax, zCoord));
            slice.setVertex(Vec3f(xmax, ymax, zCoord));
            slice.setVertex(Vec3f(xmax, ymin, zCoord));
            slice.setVertex(Vec3f(xmin, ymin, zCoord));
        }

        slice.setNormal(sliceDir);
        
        Real32 dist = clipper->getReferencePlane().distance(
            Pnt3f(center[0], center[1], zCoord)); 
    
        FDEBUG(("Brick - dist to refPlane: %f\n",dist))
            FDEBUG(("Brick - Brick center: %f\n",zCoord))

            // contours only
            if(clipObjects->getDoContours())
            {
                deactivateTexture(action);

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);

                activateTexture(action);
            }        
            else if (shader->hasRenderCallback()) 
            {
                // shader managed slice rendering
      
                clippedSlice.directRender = false;
                
                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
                
                shader->renderSlice(volume, action, &clippedSlice);
            } 
            else if(volume->getDoTextures()) 
            {
                // textured slices
      
                clippedSlice.directRender = true;
                
                clipper->clipSlice(volume, slice, 
                                   sliceDir,dist, 
                                   clippedSlice);
            }
            else 
            {
                // untextured slices only

                glColor4f(1.0, 1.0, 1.0, 1.0);

                clippedSlice.directRender = true;       

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
            }
        clippedSlice.clear();
    }    
    else 
    { 
        // clipping disabled
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        } 
        else if(volume->getDoTextures()) 
        {
            glBegin(GL_TRIANGLE_FAN);
        } 
        else
        {
            glColor4f(1.0, 1.0, 1.0, 1.0);
            glBegin(GL_LINE_LOOP);
        }      
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // copy all data into a single field and call rendercallback
      
            Real32 multiTexIntFactor = zCoord - m_lowerLeft[2];
            
            Real32 data[] = 
            {
                xmin, 
                ymin, 
                zCoord, // first vertex
                xmin * texScale[0] + texTranslate[0], 
                ymin * texScale[1] + texTranslate[1], 
                multiTexIntFactor,

                xmax, 
                ymin, 
                zCoord, // second vertex
                xmax * texScale[0] + texTranslate[0], 
                ymin * texScale[1] + texTranslate[1], multiTexIntFactor,

                xmax, 
                ymax, 
                zCoord, // third vertex
                xmax * texScale[0] + texTranslate[0], 
                ymax * texScale[1] + texTranslate[1], 
                multiTexIntFactor,

                xmin, 
                ymax, 
                zCoord, // fourth vertex
                xmin * texScale[0] + texTranslate[0], 
                ymax * texScale[1] + texTranslate[1], 
                multiTexIntFactor
            };
            
            shader->renderSlice(volume, action, data, 4, 6);
            
        } 
        else 
        {
            glTexCoord2f(xmin * texScale[0] + texTranslate[0],
                         ymin * texScale[1] + texTranslate[1]);

            glVertex3f(xmin, ymin, zCoord);
            

            glTexCoord2f(xmax * texScale[0] + texTranslate[0],
                         ymin * texScale[1] + texTranslate[1]);

            glVertex3f(xmax, ymin, zCoord);
            

            glTexCoord2f(xmax * texScale[0] + texTranslate[0],
                         ymax * texScale[1] + texTranslate[1]);

            glVertex3f(xmax, ymax, zCoord);
            

            glTexCoord2f(xmin * texScale[0] + texTranslate[0],
                         ymax * texScale[1] + texTranslate[1]);

            glVertex3f(xmin, ymax, zCoord);
        }
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        } 
        else
        {
            glEnd();
        }
        
    }
    
}

void Brick::render2DSliceXZ(DVRVolume      *volume, 
                            DrawActionBase *action, 
                            DVRShaderPtr    shader, 
                            DVRClipper     *clipper,
                            const Vec3f    &sliceDir,
                            const Real32   &yCoord)
{
    Real32 xmin = vertex[0][0];
    Real32 xmax = vertex[1][0];
    
    Real32 zmin = vertex[0][2];
    Real32 zmax = vertex[4][2]; 
  
    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);

    // check whether clipping should be performed
    bool doClipping = false;  
    if(clipObjects != NullFC)
    {
        if(clipObjects->count()       >  0                && 
           clipObjects->getClipMode() != DVRClipObjects::Off)
        {
            doClipping = true;
        }
    }
    
    if(doClipping)
    {
        slice.resetSlice();

        if(sliceDir[1] < 0.0)
        {
            slice.setVertex(Vec3f(xmin, yCoord, zmin));
            slice.setVertex(Vec3f(xmax, yCoord, zmin));
            slice.setVertex(Vec3f(xmax, yCoord, zmax));
            slice.setVertex(Vec3f(xmin, yCoord, zmax));
        }
        else
        {
            slice.setVertex(Vec3f(xmin, yCoord, zmax));
            slice.setVertex(Vec3f(xmax, yCoord, zmax));
            slice.setVertex(Vec3f(xmax, yCoord, zmin));
            slice.setVertex(Vec3f(xmin, yCoord, zmin));
        }
        
        slice.setNormal(sliceDir);
    
        Real32 dist = clipper->getReferencePlane().distance(
            Pnt3f(center[0], yCoord, center[2])); 
        
        FDEBUG(("Brick - dist to refPlane: %f\n",dist))
            FDEBUG(("Brick - Brick center: %f\n",yCoord))
            
            // contours only
            if(clipObjects->getDoContours())
            {
                deactivateTexture(action);

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);

                activateTexture(action);
            }        
            else if(shader->hasRenderCallback()) 
            {
                // shader managed slice rendering
                
                clippedSlice.directRender = false;
                
                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
                
                shader->renderSlice(volume, action, &clippedSlice);
            } 
            else if(volume->getDoTextures()) 
            {      
                // textured slices
      
                clippedSlice.directRender = true;
                
                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
            }
            else 
            {
                // untextured slices only

                glColor4f(1.0, 1.0, 1.0, 1.0);

                clippedSlice.directRender = true;       

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
            }
        clippedSlice.clear();
    }    
    else 
    { 
        // clipping disabled
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        }
        else if(volume->getDoTextures()) 
        {
            glBegin(GL_TRIANGLE_FAN);
        }
        else
        {
            glColor4f(1.0, 1.0, 1.0, 1.0);

            glBegin(GL_LINE_LOOP);
        }
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // copy all data into a single field and call rendercallback
            
            Real32 multiTexIntFactor = yCoord - m_lowerLeft[1];
            
            Real32 data[] = 
            {
                xmin, 
                yCoord, 
                zmin, // first vertex
                xmin * texScale[0] + texTranslate[0], 
                zmin * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xmax, 
                yCoord, 
                zmin, // second vertex
                xmax * texScale[0] + texTranslate[0], 
                zmin * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xmax, 
                yCoord, 
                zmax, // third vertex
                xmax * texScale[0] + texTranslate[0], 
                zmax * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xmin, 
                yCoord, 
                zmax, // fourth vertex
                xmin * texScale[0] + texTranslate[0], 
                zmax * texScale[2] + texTranslate[2], 
                multiTexIntFactor
            };
                 
            shader->renderSlice(volume, action, data, 4, 6);
        } 
        else 
        {
            FDEBUG(("XZ render2dslice (texcoor): %f %f\n",
                    xmin * texScale[0] + texTranslate[0],
                    zmin * texScale[2] + texTranslate[2]));       

            glTexCoord2f(xmin * texScale[0] + texTranslate[0],
                         zmin * texScale[2] + texTranslate[2]);
        
            glVertex3f(xmin, yCoord, zmin);
            
            
            glTexCoord2f(xmax * texScale[0] + texTranslate[0],
                         zmin * texScale[2] + texTranslate[2]);

            glVertex3f(xmax, yCoord, zmin);
            

            glTexCoord2f(xmax * texScale[0] + texTranslate[0],
                         zmax * texScale[2] + texTranslate[2]);

            glVertex3f(xmax, yCoord, zmax);
            

            glTexCoord2f(xmin * texScale[0] + texTranslate[0],
                         zmax * texScale[2] + texTranslate[2]);

            glVertex3f(xmin, yCoord, zmax);
        }
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        } 
        else
        {
            glEnd();
        }
    }
}

void Brick::render2DSliceYZ(DVRVolume      *volume, 
                            DrawActionBase *action, 
                            DVRShaderPtr    shader,                           
                            DVRClipper     *clipper,
                            const Vec3f    &sliceDir,
                            const Real32   &xCoord)
{  
    Real32 ymin = vertex[0][1];
    Real32 ymax = vertex[2][1]; 
    
    Real32 zmin = vertex[0][2];
    Real32 zmax = vertex[4][2]; 
  
    // get clip objects
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(volume, 
                                                        DVRClipObjects);
  
    // check whether clipping should be performed
    bool doClipping = false;  

    if(clipObjects != NullFC)
    {
        if(clipObjects->count()       >  0                && 
           clipObjects->getClipMode() != DVRClipObjects::Off)
        {
            doClipping = true;
        }
    }
    
    if(doClipping)
    {
        
        slice.resetSlice();
        
        if(sliceDir[0] > 0.0)
        {
            slice.setVertex(Vec3f(xCoord, ymin, zmin));
            slice.setVertex(Vec3f(xCoord, ymax, zmin));
            slice.setVertex(Vec3f(xCoord, ymax, zmax));
            slice.setVertex(Vec3f(xCoord, ymin, zmax));
        }
        else
        {
            slice.setVertex(Vec3f(xCoord, ymin, zmax));
            slice.setVertex(Vec3f(xCoord, ymax, zmax));
            slice.setVertex(Vec3f(xCoord, ymax, zmin));
            slice.setVertex(Vec3f(xCoord, ymin, zmin));
        }
    
        slice.setNormal(sliceDir);
    
        Real32 dist = clipper->getReferencePlane().distance(
            Pnt3f(xCoord,center[1],center[2])); 
        
        FDEBUG(("Brick - dist to refPlane: %f\n",dist))
            FDEBUG(("Brick - Brick center: %f\n",xCoord))
            
            // contours only
            if(clipObjects->getDoContours())
            {
                deactivateTexture(action);

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);

                activateTexture(action);
            }        
            else if(shader->hasRenderCallback()) 
            {
                // shader managed slice rendering
                
                clippedSlice.directRender = false;
                
                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
                
                shader->renderSlice(volume, action, &clippedSlice);
                
            } 
            else if (volume->getDoTextures()) 
            {     
                // textured slices
                
                clippedSlice.directRender = true;
                
                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
            }
            else 
            {
                // untextured slices only

                glColor4f(1.0, 1.0, 1.0, 1.0);

                clippedSlice.directRender = true;       

                clipper->clipSlice(volume, 
                                   slice, 
                                   sliceDir,
                                   dist, 
                                   clippedSlice);
            }
        clippedSlice.clear();
    }    
    else 
    { 
        // clipping disabled

        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        } 
        else if (volume->getDoTextures()) 
        {
            glBegin(GL_TRIANGLE_FAN);
        } 
        else 
        {
            glColor4f(1.0, 1.0, 1.0, 1.0);

            glBegin(GL_LINE_LOOP);
        }

        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // copy all data into a single field and call render callback
            
            Real32 multiTexIntFactor = xCoord - m_lowerLeft[0];
            
            Real32 data[] = 
            { 
                xCoord, 
                ymin, 
                zmin,
                ymin * texScale[1] + texTranslate[1], 
                zmin * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xCoord, 
                ymax, 
                zmin,
                ymax * texScale[1] + texTranslate[1], 
                zmin * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xCoord, 
                ymax, 
                zmax,
                ymax * texScale[1] + texTranslate[1], 
                zmax * texScale[2] + texTranslate[2], 
                multiTexIntFactor,

                xCoord, 
                ymin, 
                zmax,
                ymin * texScale[1] + texTranslate[1], 
                zmax * texScale[2] + texTranslate[2], 
                multiTexIntFactor
            };
                 
            shader->renderSlice(volume, action, data, 4, 6);
        } 
        else 
        {
            glTexCoord2f(ymin * texScale[1] + texTranslate[1],
                         zmin * texScale[2] + texTranslate[2]);

            glVertex3f(xCoord, ymin, zmin);
            

            glTexCoord2f(ymax * texScale[1] + texTranslate[1],
                         zmin * texScale[2] + texTranslate[2]);

            glVertex3f(xCoord, ymax, zmin);
            

            glTexCoord2f(ymax * texScale[1] + texTranslate[1],
                         zmax * texScale[2] + texTranslate[2]);

            glVertex3f(xCoord, ymax, zmax);

            
            glTexCoord2f(ymin * texScale[1] + texTranslate[1],
                         zmax * texScale[2] + texTranslate[2]);

            glVertex3f(xCoord, ymin, zmax);
        }
        
        if((shader != NullFC) && shader->hasRenderCallback()) 
        {
            // do nothing
        } 
        else
        {
            glEnd();
        }
    }
}


void Brick::render2DSlices(DVRVolume      *volume, 
                           DrawActionBase *action, 
                           DVRShaderPtr    shader, 
                           DVRClipper     *clipper,
                           const Vec3f    &sliceDir)
{
    // number of additional per vertex attributes 
    // (not position + first texture coordinates)

    clippedSlice.numPerVertexData = 0;

    slice.setTextureTransform(texScale,texTranslate);

    switch(m_ori)
    {
        case BrickSet::XY:
            clippedSlice.orientation = DVRRenderSlice::XY;
            render2DSliceXY(volume,
                            action,
                            shader,
                            clipper,
                            sliceDir,
                            center[2]);
            break;

        case BrickSet::XZ:
            clippedSlice.orientation = DVRRenderSlice::XZ;
            render2DSliceXZ(volume,
                            action,
                            shader,
                            clipper,
                            sliceDir,
                            center[1]);
            break;

        case BrickSet::YZ:
            clippedSlice.orientation = DVRRenderSlice::YZ;
            render2DSliceYZ(volume,
                            action,
                            shader,
                            clipper,
                            sliceDir,
                            center[0]);
            break;

        default:
            break;
    }   
}


//! Render Slices 2D with Multi-textures
void Brick::render2DMultiSlices(DVRVolume      *volume,
                                DrawActionBase *action,
                                DVRShaderPtr    shader,
                                DVRClipper     *clipper,
                                bool            btf,
                                const Vec3f    &sliceDir)
{
    DVRVolumeTexturePtr tex = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(tex == NullFC) 
        return;

    Vec3f  res         = tex->getResolution();
    Vec3f  vox         = tex->getSliceThickness();

    Real32 fSampleRate = volume->getSampling();
    
    Int32  dim       = 2 - m_ori; // dimension perpenticular to slice planes

    Real32 numSlices = res[dim] * fSampleRate;

    // ancor for the slices
    Real32 anchor    = (-res[dim] / 2.0f + 0.5f) * vox[dim]; 
    Real32 dist      = vox[dim] / fSampleRate;

    if(btf)
    {
        SINFO << "Brick::render2DMultiSlices - BTF" << std::endl;

        anchor = -anchor;
        dist   = -dist;
    }
    
    FDEBUG(("Brick::render2DMultiSlices - ori:       %d", m_ori));
    FDEBUG(("Brick::render2DMultiSlices - numSlices: %d", numSlices));
    
    // number of additional per vertex attributes 
    // (not position + first texture coordinates)

    clippedSlice.numPerVertexData = 0;
    
    Vec3f multiTexScale     = texScale;
    Vec3f multiTexTranslate = texTranslate;
    
    switch(m_ori)
    {
        case BrickSet::XY:

            clippedSlice.orientation = DVRRenderSlice::XY;

            // "reuse" texScale/translate for setting the interpolation 
            // factor whem clipping is performed
            multiTexScale[2] = 0.0;

            for(UInt32 nSlice = 0; nSlice < numSlices; nSlice++)
            {
                if((anchor >= m_lowerLeft[2]) && (anchor < m_upperRight[2]))
                {      
                    FDEBUG(("Slice %d: %f\n", nSlice, anchor));

                    multiTexTranslate[2] = anchor - m_lowerLeft[2];

                    slice.setTextureTransform(multiTexScale,multiTexTranslate);

                    render2DSliceXY(volume,
                                    action,
                                    shader,
                                    clipper,
                                    sliceDir,
                                    anchor);
                }

                // next slice
                anchor += dist;
            }    
            break;

        case BrickSet::XZ:

            clippedSlice.orientation = DVRRenderSlice::XZ;

            multiTexScale[1] = 0.0;

            for(UInt32 nSlice = 0; nSlice < numSlices; nSlice++)
            {
                if((anchor >= m_lowerLeft[1]) && (anchor < m_upperRight[1]))
                {        
                    FDEBUG(("Slice %d: %f\n", nSlice, anchor));
                    // "reuse" texScale/translate for setting the 
                    // interpolation factor whem clipping is performed

                    multiTexTranslate[1] = anchor - m_lowerLeft[1];

                    slice.setTextureTransform(multiTexScale,multiTexTranslate);

                    render2DSliceXZ(volume,
                                    action,
                                    shader,
                                    clipper,
                                    sliceDir,
                                    anchor);
                }
                // next slice
                anchor += dist;
            }
            break;

        case BrickSet::YZ:

            clippedSlice.orientation = DVRRenderSlice::YZ;

            multiTexScale[0] = 0.0;

            for(UInt32 nSlice = 0; nSlice < numSlices; nSlice++)
            {
                if((anchor >= m_lowerLeft[0]) && (anchor < m_upperRight[0]))
                {        
                    FDEBUG(("Slice %d: %f\n", nSlice, anchor));
                    // "reuse" texScale/translate for setting the 
                    // interpolation factor whem clipping is performed

                    multiTexTranslate[0] = anchor - m_lowerLeft[0];

                    slice.setTextureTransform(multiTexScale,multiTexTranslate);

                    render2DSliceYZ(volume,
                                    action,
                                    shader,
                                    clipper,
                                    sliceDir,
                                    anchor);
                }

                // next slice
                anchor += dist;
            }
            break;

        default:
            break;
    }
}

OSG_END_NAMESPACE


