#include "OSGSlicer.h"

#include <OSGConfig.h>

#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGDrawAction.h>
#include <OSGCamera.h>

OSG_USING_NAMESPACE

/*
void Slicer::getModelMatrix(DrawActionBase *da, Matrix mat) 
{
    mat = da->getActNode()->getToWorld();
}


void Slicer::getViewMatrix(DrawActionBase *da, Matrix mat) 
{
    mat =  da->getCamera()->getBeacon()->getToWorld();
    mat.invert();
}
*/

Int32 Slicer::getAASlicingDirection(DrawActionBase *da, Vec3f *pViewDir) 
{
    Int32 dir           = getSlicingDirection(da, NULL);
    Vec3f finalSliceDir;

    switch (dir) 
    {
        case SD_Z_FRONT_TO_BACK:
            finalSliceDir = Vec3f(0, 0, 1);
            break;

        case SD_Z_BACK_TO_FRONT:
            finalSliceDir = Vec3f(0, 0, -1);
            break;

        case SD_Y_BACK_TO_FRONT:
            finalSliceDir = Vec3f(0, -1, 0);
            break;

        case SD_Y_FRONT_TO_BACK:
            finalSliceDir = Vec3f(0, 1, 0);
            break;

        case SD_X_BACK_TO_FRONT:
            finalSliceDir = Vec3f(-1, 0, 0);
            break;

        case SD_X_FRONT_TO_BACK:
            finalSliceDir = Vec3f(1, 0, 0);
            break;

        default:
            finalSliceDir = Vec3f(0, 0, 1);
            break;
    }

    if (pViewDir != NULL)
        *pViewDir = finalSliceDir;

    return dir;
}


Int32 Slicer::getSlicingDirection(DrawActionBase *da, Vec3f *pViewDir) 
{
    static const Vec3f      zAxis(0.0, 0.0, 1.0);
    static       Quaternion dummyRot;   // static over all SoVolume instances
    static       Vec3f      vecToCam;   // only temporally, does not matter
    static       Vec3f      volTranslation;
    static       Vec3f      volScale;
    static       Vec3f      dummyVec;
    static       Quaternion volRotationInv;
    static       Quaternion camRotationInv;   
                 Vec3f      finalSliceDir;
   
    // Get viewing matrix
    Matrix   viewMat = da->getCameraToWorld();

    viewMat.invert();
    viewMat.getTransform(vecToCam, camRotationInv, dummyVec, dummyRot);
    camRotationInv.invert();

    // Get model matrix
    Matrix   modelMat = da->getActNode()->getToWorld();

    modelMat.getTransform(volTranslation, volRotationInv, volScale, dummyRot); 
    volRotationInv.invert();

    // Get viewing vector pointing to camera
    camRotationInv.multVec(zAxis, vecToCam);
    volRotationInv.multVec(vecToCam, finalSliceDir);

    Real64 x = finalSliceDir[0];
    Real64 y = finalSliceDir[1];
    Real64 z = finalSliceDir[2];
    Real64 X = (x > 0) ? x: -x;
    Real64 Y = (y > 0) ? y: -y;
    Real64 Z = (z > 0) ? z: -z;
   
    Int32 nfinalSliceDir;

    if((Z > Y) && (Z > X))  // Z is the largest component
    {
        if (z > 0) 
        { 
            nfinalSliceDir = SD_Z_FRONT_TO_BACK;
        } 
        else 
        {
            nfinalSliceDir = SD_Z_BACK_TO_FRONT;
        }
    } 
    else
    {
        if(Y > X) 
        {
            if(y < 0) 
            {
                nfinalSliceDir = SD_Y_BACK_TO_FRONT;
            } 
            else 
            {
                nfinalSliceDir = SD_Y_FRONT_TO_BACK;
            }
        } 
        else 
        {
            if(x < 0) 
            {
                nfinalSliceDir = SD_X_BACK_TO_FRONT;
            } 
            else 
            {
                nfinalSliceDir = SD_X_FRONT_TO_BACK;
            }
        }
    }

    if(pViewDir != NULL) 
    {
        *pViewDir = finalSliceDir;
    }

    return nfinalSliceDir;
}


void Slicer::rotateToLocal(DrawActionBase *da, Vec3f &in, Vec3f &out)
{
    static Quaternion   dummyRot;
    static Vec3f        tempVec;
    static Vec3f        volTranslation;
    static Vec3f        camTranslation;
    static Vec3f        volScale;
    static Vec3f        camScale;
    static Quaternion   volRotationInv;
    static Quaternion   camRotationInv; 
   
    // Get viewing matrix
    Matrix viewMat = da->getCameraToWorld();

    viewMat.invert();
    viewMat.getTransform(camTranslation, camRotationInv, camScale, dummyRot);
    camRotationInv.invert();
   
    // Get model matrix
    Matrix modelMat = da->getActNode()->getToWorld();

    modelMat.getTransform(volTranslation, volRotationInv, volScale, dummyRot); 
    volRotationInv.invert();
   
    // Rotate vector invers to view camera and model matrix
    camRotationInv.multVec(in,      tempVec);
    volRotationInv.multVec(tempVec, out    );
}


bool Slicer::isBackToFront(int sliceDir)
{
    switch(sliceDir)
    {
        case SD_Z_FRONT_TO_BACK:
        case SD_Y_FRONT_TO_BACK:
        case SD_X_FRONT_TO_BACK:
            return false;

        case SD_Z_BACK_TO_FRONT:
        case SD_Y_BACK_TO_FRONT:
        case SD_X_BACK_TO_FRONT:
            return true;

        default:
            // undefined 
            return false;
    }
}
  
