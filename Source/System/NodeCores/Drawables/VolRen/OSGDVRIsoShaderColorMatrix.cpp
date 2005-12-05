#include <OSGConfig.h>

#include "OSGDVRIsoShader.h"
#include <OSGDVRShader.h>
#include <OSGDrawActionBase.h>
#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRIsoSurface.h>
#include <OSGWindow.h>
#include <OSGViewport.h>
#include <OSGSlicer.h>
#include <OSGCamera.h>

#include <OSGGLU.h>

OSG_USING_NAMESPACE

void DVRIsoShader::activate_ColorMatrixShading(DVRVolume      *volume, 
                                               DrawActionBase *)
{
    DVRVolumeTexturePtr vol      = DVRVOLUME_PARAMETER(volume,
                                                       DVRVolumeTexture);

    DVRIsoSurfacePtr    isoParam = DVRVOLUME_PARAMETER(volume, 
                                                       DVRIsoSurface);

    if((volume == NULL) || (vol == NullFC)) 
    {
        SWARNING << "NO Volume ..." << std::endl;
        return;
    }

    Real32 isoValue;
    UInt32 alphaMode;

    // get parameters from isosurface attachment if available
    if(isoParam!=NullFC)
    {
        isoValue  = isoParam->getIsoValue ();
        alphaMode = isoParam->getAlphaMode();
    }
    else
    {
        isoValue  = 1.0;
        alphaMode = GL_GREATER;
    }

    glPushAttrib(GL_COLOR_BUFFER_BIT   |
                 GL_ENABLE_BIT         | 
                 GL_DEPTH_BUFFER_BIT   | 
                 GL_STENCIL_BUFFER_BIT | 
                 GL_POLYGON_BIT        |
                 GL_PIXEL_MODE_BIT);

    if(volume->getDoTextures()) 
    { 
        
        glGetIntegerv(GL_COLOR_WRITEMASK,m_colorWriteMask);
        
        // draw color 1 for MODULATE
        glColor4f(1.0, 1.0, 1.0, 1.0);

        // Enable Alpha Test for isosurface
        glEnable(GL_ALPHA_TEST); 
        glAlphaFunc(alphaMode, isoValue);

        // no blending and lighting
        glDisable(GL_BLEND);
        glDisable(GL_LIGHTING);
    
        // setup stencil buffer
        // to mask the "volume region"
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_FALSE);
        glEnable(GL_STENCIL_TEST);
        glClearStencil(0xFF);
        glStencilMask(0xFF);
        glClear(GL_STENCIL_BUFFER_BIT);
        glStencilFunc(GL_ALWAYS, 0x0, 0x1); // write always
        glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    }

}


void DVRIsoShader::deactivate_ColorMatrixShading(DVRVolume      *volume, 
                                                 DrawActionBase *action)
{
    if(volume->getDoTextures()) 
    {
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_ALPHA_TEST);
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);

        glStencilFunc(GL_EQUAL, 0x0, 0xFF);
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);	       

        Color4f diffuseLightColor;
        Vec3f   diffuseDir;

        DirLightList diffuseLights;
        DirLightList specularLights;
        Color4f ambientLight(0.0f,0.0f,0.0f,0.0f);

        getLightSources(diffuseLights,specularLights,ambientLight);

        // use the first available diffuse lightsource for shading
        if(diffuseLights.empty())
        {
            diffuseLightColor[0] = 0.0f;
            diffuseLightColor[1] = 0.0f;
            diffuseLightColor[2] = 0.0f;
            diffuseLightColor[3] = 0.0f;
        }
        else
        {
            diffuseLightColor = diffuseLights.begin()->color;

            Slicer::rotateToLocal(action, 
                                  diffuseLights.begin()->dir, 
                                  diffuseDir);
        }

        // store the matrix mode
        GLint oldMatrixMode;
        glGetIntegerv(GL_MATRIX_MODE, &oldMatrixMode);
    
        // store alpha scale and bias
        GLfloat oldAlphaBias;
        GLfloat oldAlphaScale;

        glGetFloatv(GL_ALPHA_BIAS,  &oldAlphaBias);
        glGetFloatv(GL_ALPHA_SCALE, &oldAlphaScale);

        // ensure alpha is 1 
        glPixelTransferf(GL_ALPHA_SCALE, 0.00001f);
        glPixelTransferf(GL_ALPHA_BIAS,  0.999999f);

        // compute shading

        // switch to color matrix mode to compute diffuse shading
        glMatrixMode(GL_COLOR);
    
        // push actual color matrix
        glPushMatrix();
    
        GLfloat colorMatV[16];

        // set light color
        colorMatV[0] = m_colorWriteMask[0] ? diffuseLightColor[0] : 0.0f;
        colorMatV[1] = 0.0f;
        colorMatV[2] = 0.0f;
        colorMatV[3] = 0.0f;

        colorMatV[4] = 0.0f;
        colorMatV[5] = m_colorWriteMask[1] ? diffuseLightColor[1] : 0.0f;
        colorMatV[6] = 0.0f;
        colorMatV[7] = 0.0f;
    
        colorMatV[8] = 0.0f;
        colorMatV[9] = 0.0f;
        colorMatV[10] = m_colorWriteMask[2] ? diffuseLightColor[2] : 0.0f;
        colorMatV[11] = 0.0f;
	 
        colorMatV[12] = m_colorWriteMask[0] ? ambientLight[0] : 0.0f;
        colorMatV[13] = m_colorWriteMask[1] ? ambientLight[1] : 0.0f;
        colorMatV[14] = m_colorWriteMask[2] ? ambientLight[2] : 0.0f;
        colorMatV[15] = 1.0f;
    
        glLoadMatrixf(colorMatV);	

        // set light direction for computation of cosine-term
        colorMatV[0] = diffuseDir[0];
        colorMatV[1] = diffuseDir[0];
        colorMatV[2] = diffuseDir[0];
        //colorMatV[3] = 0.0f;
    
        colorMatV[4] = diffuseDir[1];
        colorMatV[5] = diffuseDir[1];
        colorMatV[6] = diffuseDir[1];
        //colorMatV[7] = 0.0f;
    
        colorMatV[8] = diffuseDir[2];
        colorMatV[9] = diffuseDir[2];
        colorMatV[10] = diffuseDir[2];
        //colorMatV[11] = 0.0f;
    
        colorMatV[12] = 0.0f;
        colorMatV[13] = 0.0f;
        colorMatV[14] = 0.0f;
        //colorMatV[15] = 1.0f;
    
        glMultMatrixf(colorMatV);		

        // rescale/bias gradients
        colorMatV[0] = 2.0f;
        colorMatV[1] = 0.0f;
        colorMatV[2] = 0.0f;
    
        colorMatV[3] = 0.0f;
    
        colorMatV[4] = 0.0f;
        colorMatV[5] = 2.0f;
        colorMatV[6] = 0.0f;
    
        colorMatV[7] = 0.0f;
	 
        colorMatV[8] = 0.0f;
        colorMatV[9] = 0.0f;
        colorMatV[10] = 2.0f;
    
        colorMatV[11] = 0.0f;
      
        colorMatV[12] = -1.0f;
        colorMatV[13] = -1.0f;
        colorMatV[14] = -1.0f;
    
        colorMatV[15] = 1.0f;

        // set the color matrix on top of the stack
        glMultMatrixf(colorMatV);
    
        // compute shading
        GLint drawBuf;
        glGetIntegerv(GL_DRAW_BUFFER, &drawBuf);
        glReadBuffer(drawBuf);

        // get covered screen rect in device coordinates
        GLfloat screenS[4];
        getCoveredScreenRect(volume,action,screenS);

        GLint vpOrigin[2];
        GLint vpSize[2];

        vpOrigin[0] = action->getViewport()->getPixelLeft();
        vpOrigin[1] = action->getViewport()->getPixelBottom();

        vpSize[0]   = 
            action->getViewport()->getPixelRight() -
            action->getViewport()->getPixelLeft ();

        vpSize[1]   = 
            action->getViewport()->getPixelTop   () -
            action->getViewport()->getPixelBottom();
    
        // compute covered pixels
        GLint sr[4];

        sr[0] = (GLint) osgfloor(vpOrigin[0]+(screenS[0]+1.0f)*(vpSize[0]/2));
        sr[1] = (GLint) osgfloor(vpOrigin[1]+(screenS[1]+1.0f)*(vpSize[1]/2));
        sr[2] = (GLint) osgceil (vpOrigin[0]+(screenS[2]+1.0f)*(vpSize[0]/2));
        sr[3] = (GLint) osgceil (vpOrigin[1]+(screenS[3]+1.0f)*(vpSize[1]/2));

        // copy covered pixels 
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glRasterPos2f(screenS[0],screenS[1]);
        glCopyPixels(sr[0],sr[1],sr[2]-sr[0]+1,sr[3]-sr[1]+1, GL_COLOR);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    
        // restore alpha bias and scale
        glPixelTransferf(GL_ALPHA_BIAS, oldAlphaBias);
        glPixelTransferf(GL_ALPHA_SCALE, oldAlphaScale);

        // restore old color matrix
        glMatrixMode(GL_COLOR);
        glPopMatrix();
      
        // restore old matrix mode
        glMatrixMode(oldMatrixMode);

    }

    glPopAttrib();
}

void DVRIsoShader::getCoveredScreenRect(DVRVolume      *volume, 
                                        DrawActionBase *action, 
                                        GLfloat         screenRect[4])
{
    int vpSize[2];

    vpSize[0] = action->getViewport()->getPixelWidth();
    vpSize[1] = action->getViewport()->getPixelHeight();
    
    DVRVolumeTexturePtr tex = DVRVOLUME_PARAMETER(volume, DVRVolumeTexture);

    if(tex != NullFC) 
    {
        
        Matrix4f modelMatrix = action->getActNode()->getToWorld();
        Matrix4f viewMatrix  = action->getCameraToWorld();

        viewMatrix.invert();

        Matrix4f prjTranslationMatrix;

        action->getCamera()->getProjectionTranslation(prjTranslationMatrix,
                                                      vpSize[0],
                                                      vpSize[1]);
        Matrix4f prjMatrix;

        action->getCamera()->getProjection(prjMatrix,
                                           vpSize[0],
                                           vpSize[1]);       

        Matrix4f toScreenMatrix = modelMatrix;

        toScreenMatrix.multLeft(viewMatrix);
        toScreenMatrix.multLeft(prjTranslationMatrix);
        toScreenMatrix.multLeft(prjMatrix);        
        
 
        Vec3f & res   = tex->getResolution();
        Vec3f & slice = tex->getSliceThickness();
        
        Pnt3f minBB(-0.5f * res[0] * slice[0], 
                    -0.5f * res[1] * slice[1], 
                    -0.5f * res[2] * slice[2]);

        Pnt3f maxBB(-minBB);
	
        Pnt3f BB[8] = 
        {
            Pnt3f(minBB[0],minBB[1],minBB[2]),
            Pnt3f(maxBB[0],minBB[1],minBB[2]),
            Pnt3f(maxBB[0],maxBB[1],minBB[2]),
            Pnt3f(minBB[0],maxBB[1],minBB[2]),
            Pnt3f(minBB[0],minBB[1],maxBB[2]),
            Pnt3f(maxBB[0],minBB[1],maxBB[2]),
            Pnt3f(maxBB[0],maxBB[1],maxBB[2]),
            Pnt3f(minBB[0],maxBB[1],maxBB[2])
        };
 

        Pnt3f tBB;
        toScreenMatrix.multFullMatrixPnt(BB[0],tBB);

        screenRect[0] = tBB[0]; 
        screenRect[1] = tBB[1]; 
        screenRect[2] = tBB[0]; 
        screenRect[3] = tBB[1];

        // get min,max coordinates
        for(unsigned int i = 1; i < 8; i++)
        {
            toScreenMatrix.multFullMatrixPnt(BB[i],tBB);
            
            if(tBB[0] < screenRect[0]) 
            {
                screenRect[0] = tBB[0];
            }
            else if(tBB[0] > screenRect[2]) 
            {
                screenRect[2] = tBB[0]; 
            }
          
            if(tBB[1] < screenRect[1]) 
            {
                screenRect[1] = tBB[1]; 
            }
            else if(tBB[1] > screenRect[3])
            {
                screenRect[3] = tBB[1]; 
            }
        }
        
        // clamp covered rectangle to viewport
        for(unsigned int i = 0; i < 4; i++)
        {
            if(screenRect[i] < -1.0) 
                screenRect[i] = -1.0;
            else if(screenRect[i] > 1.0) 
                screenRect[i] = 1.0;
        }
    }    
    else 
    {
        // something wrong with initialization - do not copy anything
        screenRect[0] = screenRect[1] = screenRect[2] = screenRect[3] = 0;
    }
}
