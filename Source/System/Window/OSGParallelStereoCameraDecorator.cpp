/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"
#include "OSGNode.h"

#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGParallelStereoCameraDecorator.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParallelStereoCameraDecoratorBase.cpp file.
// To modify it, please change the .fcd file (OSGParallelStereoCameraDecorator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParallelStereoCameraDecorator::initMethod(void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParallelStereoCameraDecorator::ParallelStereoCameraDecorator(void) :
    Inherited()
{
}

ParallelStereoCameraDecorator::ParallelStereoCameraDecorator(const ParallelStereoCameraDecorator &source) :
    Inherited(source)
{
}

ParallelStereoCameraDecorator::~ParallelStereoCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParallelStereoCameraDecorator::changed(BitVector whichField, 
                                            UInt32    origin)
{
    Inherited::changed(whichField, origin);
}

void ParallelStereoCameraDecorator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParallelStereoCameraDecorator NI" << std::endl;
}


float distortionFn( Vec4f d, float r )
{    
    float r2 = r * r;
    return r * (d[0] + (d[1] + (d[2] + d[3] * r2) * r2) * r2);
}

/*! Get the projection matrix, as described in OculusSDK doc
*/

void ParallelStereoCameraDecorator::getProjection(Matrix &result, 
                                                 UInt32  width, 
                                                 UInt32  height)
{
    
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        SLOG << "ParallelStereoCameraDecorator::getProjection(wxh): " << width << "x" << height << std::endl;
        return;
    }
       
#if 0
    PerspectiveCamera *cam = 
        dynamic_cast<PerspectiveCamera *>(getDecoratee());
#endif

    PerspectiveCameraPtr cam = PerspectiveCameraPtr::dcast(getDecoratee());

    if(cam == NullFC)
    {
        FFATAL(("ParallelStereoCameraDecorator::getProjection: can only"
                " decorate PerspectiveCameras!\n"));

        result.setIdentity();
        return;
    }


    float LensCenterx = 1.f - (2.f * getLensSeparationDistance() / getHScreenSize()); 
              
   
    float fovscale = 1.0;
    // compute scale
    {        
        // Convert fit value to distortion-centered coordinates before fit radius
        // calculation.        
        float dx = 0.5f + LensCenterx;
        float dy = 0.5f / cam->getAspect();
        float fitRadius = sqrt(dx * dx + dy * dy);
        fovscale = distortionFn( getDistortionK(), fitRadius ) / fitRadius;

        //SLOG << "fovscale: " << fovscale << std::endl;
    }

    setFoVScale(fovscale);
       
   
    // Compute Vertical FOV based on distance.
    float fov = 2.0f * atan(fovscale*getVScreenSize()/(2.0f*getEyeToScreenDistance()));
    
    Matrix P = Matrix( 1.0f / (cam->getAspect() * tan(fov/2.0f)), 0.f, 0.f, 0.f,
                       0.f, 1.0f / tan(fov/2.0f), 0.f, 0.f,
                       0.f, 0.f, cam->getFar()/(cam->getNear()-cam->getFar()), cam->getFar()*cam->getNear()/(cam->getNear()-cam->getFar()),
                       0.f, 0.f, -1.0f, 0.f);
    result = P;

        
    if (!getLeftEye()) LensCenterx*=-1.f;
    
    Matrix trans;
    trans.setTranslate(Vec3f(LensCenterx,0,0));

    result.multLeft(trans);        
}        


void ParallelStereoCameraDecorator::getViewing(Matrix &result, 
                                           UInt32  OSG_CHECK_ARG(width ),
                                           UInt32  OSG_CHECK_ARG(height))
{    
    NodePtr pUser = getUser();

    if(pUser == NULL)
    {
        FWARNING(("ParallelStereoCameraDecorator::getViewing: no user!\n"));

        CameraPtr pCamera = getDecoratee();

        if(pCamera == NULL)
        {
            result.setIdentity();

            return;
        }

        pCamera->getBeacon()->getToWorld(result);

        result.invert();
    }   
    else
    {
        pUser->getToWorld(result);  
        
        result.invert();
    }
    

    float halfIPD = getEyeSeparation() * 0.5f;

    if (!getLeftEye()) halfIPD*=-1.f;
    
    Matrix trans;
    trans.setTranslate(Vec3f(halfIPD,0,0));

    result.multLeft(trans);
    
}

void ParallelStereoCameraDecorator::getDecoration(Matrix &result, 
												 UInt32  width, 
                                                 UInt32  height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }

    CameraPtr camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("ParallelStereoCameraDecorator::getDecoration: no decoratee!\n"));

        result.setIdentity();

        return;
    }
	
    camera->getDecoration(result, width, height);
}

OSG_END_NAMESPACE
