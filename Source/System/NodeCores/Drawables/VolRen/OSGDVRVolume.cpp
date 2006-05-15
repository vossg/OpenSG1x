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

#include <OSGAction.h>
#include <OSGCamera.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>
#include <OSGSimpleMaterial.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRAppearance.h>
#include <OSGBrick.h>
#include <OSGSlicer.h>

#include "OSGDVRVolume.h"
#include "OSGDVRClipObjects.h"
#include "OSGDVRClipper.h"


OSG_USING_NAMESPACE

/*! \class osg::DVRVolume
    OpenSG NodeCore for direct volume rendering
*/

UInt32 DVRVolume::_extTex3D = Window::registerExtension( "GL_EXT_texture3D" );

/*----------------------- constructors & destructors ----------------------*/

#ifdef OSG_WIN32_CL
#pragma warning( disable : 4355 )
#endif

//! Constructor
DVRVolume::DVRVolume(void) :
    Inherited         (     ),
    drawStyleListValid(false),
    textureManager    (this ),
    shadingInitialized(false)
{
    SINFO << "DVRVolume::DVRVolume(void) this: " << this << std::endl;

    commonConstructor();
}

//! Copy Constructor
DVRVolume::DVRVolume(const DVRVolume &source) :
    Inherited         (source),
    drawStyleListValid(false ),
    textureManager    (this  ),
    shadingInitialized(false )
{
    SINFO << "DVRVolume::DVRVolume(const DVRVolume &source) this: "
          << this << std::endl;

    //!! FIXME:
    //!! This is only performed during instantiation of real objects
    //!! Which is only done with the copy constructor
    //!!
    //!! Otherwise my code cores - (maybe the copy constructor of FCPtr is 
    //!! broken?!)

    DVRVolumePtr ptr(*this);
    
    // Fake material for render action
    SimpleMaterialPtr m = SimpleMaterial::create();

    beginEditCP(m);
    {
        m->setTransparency(0.001f                );
        m->setLit         (false                 );
        m->setDiffuse     (Color3f(1.0, 1.0, 1.0));
        m->setAmbient     (Color3f(1.0, 1.0, 1.0));
    }
    endEditCP(m);
    
    // Chunk material as storage fieldcontainer for textures
    ChunkMaterialPtr cm = SimpleMaterial::create();

    // Add all
    beginEditCP(ptr, RenderMaterialFieldMask | TextureStorageFieldMask);
    {
        setRenderMaterial(m );
        setTextureStorage(cm);
    }
    endEditCP  (ptr, RenderMaterialFieldMask | TextureStorageFieldMask);

    commonConstructor();
}

#ifdef OSG_WIN32_CL
#pragma warning( default : 4355 )
#endif

//! Destructor
DVRVolume::~DVRVolume(void)
{
    SINFO << "~DVRVolume this: " 
          << this 
          << std::endl
          << "~DVRVolume appearance: "          
          << getAppearance() 
          << std::endl
          << "~DVRVolume::subRefCP(Appearance)" 
          << std::endl;

    subRefCP(_sfAppearance.getValue());

    SINFO << "~DVRVolume::subRefCP(Geometry)" 
          << std::endl;
//        << "~DVRVolume geometry: " 
//        << int(_sfGeometry.getValue()) 
//        << std::endl;

    subRefCP(_sfGeometry.getValue());

    SINFO << "~DVRVolume::subRefCP(Shader)"                << std::endl;
    SINFO << "~DVRVolume shader: "          << getShader() << std::endl;

    subRefCP(_sfShader.getValue());

    SINFO << "~DVRVolume::subRefCP(RenderMaterial)" 
          << std::endl
          << "~DVRVolume renderMaterial: " 
          << getRenderMaterial() 
          << std::endl;

    subRefCP(_sfRenderMaterial.getValue());

    SINFO << "~DVRVolume::subRefCP(TextureStorage)"
          << std::endl
          << "~DVRVolume textureStorage: " 
          << getTextureStorage() 
          << std::endl;

    subRefCP(_sfTextureStorage.getValue());
}

/*----------------------------- class specific ----------------------------*/


//! set the bounding volume of the node
void DVRVolume::adjustVolume(Volume &volume)
{
    volume.setValid();
    volume.setEmpty();
    
    DVRVolumeTexturePtr tex = DVRVOLUME_PARAMETER(this, DVRVolumeTexture);

    if (tex != NullFC) 
    {
        Vec3f & res   = tex->getResolution    ();
        Vec3f & slice = tex->getSliceThickness();
    
        Vec3f minBB(-0.5f * res[0] * slice[0],
                    -0.5f * res[1] * slice[1],
                    -0.5f * res[2] * slice[2]);

        Vec3f maxBB(-minBB);
    
        volume.extendBy(minBB);
        volume.extendBy(maxBB);
    }    
    else 
    {
        // something wrong with initialization - show boundingbox either
        Vec3f minBB(-0.5, -0.5, -0.5);
        Vec3f maxBB( 0.5,  0.5,  0.5);
        
        volume.extendBy(minBB);
        volume.extendBy(maxBB);
    }
}


//! initialize the static features of the class, e.g. action callbacks
void DVRVolume::initMethod(void)
{
    DrawAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                              DVRVolumePtr, 
                              CNodePtr,  
                              Action *>(&DVRVolume::doDraw));
    
    IntersectAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                          DVRVolumePtr, 
                              CNodePtr,  
                          Action *>(&DVRVolume::intersect));
    
    RenderAction::registerEnterDefault( getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                          DVRVolumePtr, 
                              CNodePtr,  
                              Action *>(&DVRVolume::render));
}


//! react to field changes
void DVRVolume::changed(BitVector whichField, UInt32 origin)
{
    FDEBUG(("DVRVolume::changed\n"));

    if((whichField & BrickStaticMemoryMBFieldMask)) 
    {
        // override invalid value
        if(_sfBrickStaticMemoryMB.getValue() == 0)
        {
            _sfBrickStaticMemoryMB.setValue(1);
        }
    }

    if((whichField & ShaderFieldMask)) 
    {
        shadingInitialized = false;
    }

    if((whichField & Textures2DFieldMask)) 
    {
        shadingInitialized = false;
    }

    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRVolume::dump(      UInt32    uiIndent, 
                     const BitVector         ) const
{
    DVRVolumePtr thisP(*this);

    thisP.dump(uiIndent, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);
    PLOG << "DVRVolume at " << this << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\trenderMaterial: " << getRenderMaterial() << std::endl;

    if (getRenderMaterial() != NullFC)
        getRenderMaterial()->dump(uiIndent);
    
    indentLog(uiIndent, PLOG);
    PLOG << "\ttextureStorage: " << getTextureStorage() << std::endl;

    if (getTextureStorage() != NullFC)
        getTextureStorage()->dump(uiIndent);
    
#if 0
    indentLog(uiIndent, PLOG);
    PLOG << "\tambient: " << getAmbient() << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tdiffuse: " << getDiffuse()  << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tspecular: " << getSpecular()  << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tshininess: " << getShininess()  << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\temission: " << getEmission()  << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\ttransparency: " << getTransparency()  << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tlit: " << getLit() << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "\tChunks: " << endl;

    for(MFStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "\t" << *i << endl;
    }
#endif
    
    indentLog(uiIndent, PLOG);
    PLOG << "DVRVolume end " << this << std::endl;
}


//! execute the OpenGL c\ommands to draw the geometry   
Action::ResultE DVRVolume::doDraw(Action * action )
{
//    FDEBUG(("DVRVolume::doDraw\n"));

    DrawAction *a = dynamic_cast<DrawAction*>(action);

    if(a == NULL) 
    {
        SWARNING << "DVRVolume::doDraw - unexpected action" << std::endl; 
        return Action::Skip;
    }

#if 1
    Material::DrawFunctor func;

    func = osgTypedMethodFunctor1ObjPtr(this, &DVRVolume::draw);
    
    // implementation from OGSGeometry
    if(a->getMaterial() != NULL)
    {
        a->getMaterial()->draw( func, a );
    }
//     else if ( getMaterial() != NullFC )
//     {
//         getMaterial()->draw( func );
//     }
    else
    {
        draw(a);
    }

    return Action::Skip;

#else
    return draw(a);
#endif

}

//! low-level OpenGL calls, ignoring materials  
Action::ResultE DVRVolume::draw(DrawActionBase *action)
{
    FINFO(("DVRVolume::draw\n"));

    Window *window = action->getWindow();

    if(getShader() != NullFC) 
    {
        // determine texture mode
        TextureManager::TextureMode mode = getTextureMode(window);
        
        FDEBUG(("DVRVolume::draw - using Shader: %s\n",
                //getShader()->getClassname()));
                getShader()->getType().getCName()));

        // initialization
        if(shadingInitialized == false) 
        {     
            // clear old texture chunks 
            textureManager.clearTextures( getTextureStorage() );

            // initialize shader 
            bool result = getShader()->initialize( this, action );

            if(result != true)
            {
                SFATAL << "DVRVolume::draw - error initializing shader" 
                       << std::endl;
            }

            //!! Shader::initialize may change the useMTSlabs() flag
            if(getShader()->useMTSlabs())
                mode = TextureManager::TM_2D_Multi;
            
            // create texture chunks
            SINFO << "TextureMode = " << mode << std::endl;

            textureManager.buildTextures(getTextureStorage(), this, mode);
            
            // initialize slice clipper
            clipper.initialize(this);
            
            shadingInitialized = true;
        }

        // sort bricks
        Pnt3f eyePointWorld(0.f, 0.f, 0.f);
        action->getCameraToWorld().mult(eyePointWorld);

        Matrix modelMat = action->getActNode()->getToWorld();
      
        // SINFO << "DVRVolume::draw - modelMat " << modelMat << std::endl;
        // SINFO << "DVRVolume::draw - eyePoint " << eyePointWorld << std::endl;
        //Brick * first = textureManager.sortBricks(
        //    action,modelMat, eyePointWorld, this, mode);

        Brick *first = textureManager.sortBricks(
            action, modelMat, eyePointWorld.subZero(), this, mode);

        // render brick boundaries

        if(getShowBricks())
        {
            for(Brick *current  = first; 
                current != NULL; 
                current  = current->getNext())
            {
                current->renderBrick();
            }
        }
        
        // initialize clipping
        initializeClipObjects(action, modelMat);
        
        // Texture_3D bricks need per brick clipping setup
        // whereas for Texture_2D bricks the clipper has to be initialized 
        // only once in that case the reset is done in Brick::render3DSlices(..)
        
        if(mode != TextureManager::TM_3D) 
            clipper.reset(this);
        
        //!! Rendering
        if(first != NULL)
        {
            getShader()->activate(this, action);
            
            // for all bricks
            Brick *prev = NULL;

            for(Brick *current  = first;
                       current != NULL;
                       prev     = current, current = current->getNext())
            {
                //FDEBUG(("DVRVolume::draw - render Brick: %d\n" i++));
                
                // switch to texture chunk
                if(getDoTextures()) 
                {
                    if (prev == NULL)
                    {
                        current->activateTexture(action);
                    }
                    else
                    {
                        current->changeFromTexture(action, prev);
                    }
                }
                
                // activate shader
                getShader()->brickActivate(this, action, current);
                
                // render slices
                current->renderSlices(this, 
                                      action, 
                                      getShader(), 
                                      &clipper, 
                                      mode);
            }
            
            // deactivate last texture chunk
            prev->deactivateTexture(action);
            
            getShader()->deactivate(this, action);
        }
    }
    else
    {
        // Show some slices anyway
        Vec3f min, max;

        action->getActNode()->getVolume().getBounds(min, max);
        
        FDEBUG(("DVRVolume::draw dummy geometry - %f %f %f -> %f %f %f\n",
                min[0], min[1], min[2], max[0], max[1], max[2]));
        
        // resolution of volume in voxel
        UInt32 res[3] = {64, 64, 64};

        // offset for slices
        Real32 offset[3] = {(max[0] - min[0]) / 2 / res[0],
                            (max[1] - min[1]) / 2 / res[1],
                            (max[2] - min[2]) / 2 / res[2]};
        // increment for slices
        Real32 inc[3] = {(max[0] - min[0]) / res[0],
                         (max[1] - min[1]) / res[1],
                         (max[2] - min[2]) / res[2]};
        
        // slices perpenticular to Z-axis
        Real32 value = min[2] + offset[2];

        for(UInt32 i = 0; i < res[2]; i++, value += inc[2])
        {
            
            glBegin(GL_LINE_LOOP); 
            {
                glVertex3f(min[0] + offset[0], min[1] + offset[1], value);
                glTexCoord2f(0.0f + offset[0],  0.0f + offset[1]);
                
                glVertex3f(max[0] - offset[0], min[1] + offset[1], value);
                glTexCoord2f(1.0f - offset[0],  0.0f + offset[1]);
                
                glVertex3f(min[0] + offset[0],  max[1] - offset[1], value);
                glTexCoord2f(0.0f + offset[0],  1.0f - offset[1]);
                
                glVertex3f(max[0] - offset[0],  max[1] - offset[1], value);
                glTexCoord2f(1.0f - offset[0],  1.0f - offset[1]);
            } 
            glEnd();
        }
    }
    
    return Action::Skip;

    //return Geometry::draw(action);
}


//! generate draw tree
Action::ResultE DVRVolume::render(Action *action)
{
    FDEBUG(("DVRVolume::render\n"));

    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;

    func = osgTypedMethodFunctor1ObjPtr(this, &DVRVolume::draw);

    a->dropFunctor(func, &(*getRenderMaterial()));

    return Action::Continue;
}


//! used to initialize member variables - called by every constructor
void DVRVolume::commonConstructor( void )
{
    drawStyleListValid = false;
    shadingInitialized = false;

    if(osgLog().getLogLevel() == LOG_DEBUG)
    {
        FDEBUG(("DVRVolume::commonConstructor: \n"));
        dump();
    }
}


//! intersection test
Action::ResultE DVRVolume::intersect(Action * action)
{ 
    FDEBUG(("DVRVolume::intersect\n"));

          IntersectAction *ia = dynamic_cast<IntersectAction*>(action);
    const DynamicVolume   &dv = ia->getActNode()->getVolume();
    
    if(dv.isValid() && !dv.intersect(ia->getLine()))
    {
        return Action::Skip; //bv missed -> can not hit children
    }

    //!! FIXME: simulate hit when bounding volume is hit

    Real32 t, v;
    Vec3f  norm;

    if(dv.intersect(ia->getLine(), t, v))
        ia->setHit(t, ia->getActNode(), 0, norm);
    
    return Action::Continue;
}


//! conveniance function for finding a specific attachment in the volume kit
AttachmentPtr DVRVolume::findParameter(const FieldContainerType &type, 
                                             UInt16              binding)
{
    DVRAppearancePtr app = getAppearance();

    if(osgLog().getLogLevel() == LOG_DEBUG)
    {
        FDEBUG(("DVRVolume::findParameter: \n"));
        type.dump();
    }

    if(app != NullFC) 
        return app->findAttachment(type, binding);

    SWARNING << "DVRVolume::findParameter - NO such parameter " << std::endl;
   
    return NullFC;
}


//! conveniance function for finding a specific attachment in the volume kit
AttachmentPtr DVRVolume::findParameter(UInt32 groupId, UInt16 binding)
{
    DVRAppearancePtr app = getAppearance();

    if(app != NullFC) 
        return app->findAttachment(groupId, binding);

    return NullFC;
}


//! aquires DrawStyleNames and insert them into the name field
void DVRVolume::buildDrawStyleList(Window *OSG_CHECK_ARG(win))
{
}


//! determine which texture mode to use
TextureManager::TextureMode DVRVolume::getTextureMode(Window *window)
{
    TextureManager::TextureMode mode;
    
    switch(getTextures2D()) 
    {
        case 0: // 3D textures
            mode = TextureManager::TM_3D;
            break;

        case 1: // 2D textures
            mode = TextureManager::TM_2D;
            break;
            
        default: // auto
            mode = window->hasExtension(_extTex3D) ?
                TextureManager::TM_3D : TextureManager::TM_2D;
    }

    if(getShader()->useMTSlabs())
        mode = TextureManager::TM_2D_Multi;

    return mode;
}


//! reinitialize inventor volume
void DVRVolume::reload(void)
{
    if(getShader() != NullFC) 
    {
        textureManager.clearTextures(getTextureStorage());

        shadingInitialized = false;
    }
}

void DVRVolume::initializeClipObjects(      DrawActionBase *action, 
                                      const Matrix         &volumeToWorld)
{
    DVRClipObjectsPtr clipObjects = DVRVOLUME_PARAMETER(this, DVRClipObjects);
  
    if(clipObjects                != NullFC && 
       clipObjects->getClipMode() != DVRClipObjects::Off)
    {
        
        DVRVolumeTexturePtr tex = DVRVOLUME_PARAMETER(this, DVRVolumeTexture);

        if(tex != NullFC) 
        {
            Vec3f &res   = tex->getResolution();
            Vec3f &slice = tex->getSliceThickness();
            
            Vec3f diag(res[0] * slice[0], 
                       res[1] * slice[1], 
                       res[2] * slice[2]);
            
            Vec3f sliceDir;
            
            if(getShader()->useMTSlabs())
            {
                Slicer::getAASlicingDirection(action,&sliceDir);
            }
            else
            {  
                switch (getTextures2D()) 
                {
                    case 0: // 3D textures
                        Slicer::getSlicingDirection(action, &sliceDir);    
                        break;

                    case 1: // 2D textures  
                        Slicer::getAASlicingDirection(action, &sliceDir);
                        break;

                    default: // auto
                        Window *window = action->getWindow();

                        if(window->hasExtension(_extTex3D))
                            Slicer::getSlicingDirection(action, &sliceDir);
                        else
                            Slicer::getAASlicingDirection(action, &sliceDir);
                }
            }
            
            Plane clipReferencePlane(sliceDir, -0.5f * diag.length());  
            
            clipObjects->initialize(volumeToWorld, clipReferencePlane);

            clipper.setReferencePlane(clipReferencePlane);
        }
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
    static char cvsid_hpp[] = OSGDVRVOLUME_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRVOLUME_INLINE_CVSID;
}
