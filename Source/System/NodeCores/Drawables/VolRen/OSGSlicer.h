#ifndef _OSGSLICER_H_
#define _OSGSLICER_H_

#ifdef __sgi
#pragma once
#pragma set woff 3201 // unreferenced variables
#endif


#include <OSGConfig.h>

#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGDrawActionBase.h>
#include <OSGDVRClipper.h>


OSG_BEGIN_NAMESPACE


// forward references


struct OSG_SYSTEMLIB_DLLMAPPING Slicer 
{
    enum SliceDir 
    {
        SD_X_FRONT_TO_BACK,
        SD_X_BACK_TO_FRONT,
        SD_Y_FRONT_TO_BACK,
        SD_Y_BACK_TO_FRONT,
        SD_Z_FRONT_TO_BACK,
        SD_Z_BACK_TO_FRONT
    };

//  static void  getModelMatrix       (DrawActionBase *da, Matrix  mat     );
//  static void  getViewMatrix        (DrawActionBase *da, Matrix  mat     );

    static Int32 getAASlicingDirection(DrawActionBase *da, Vec3f  *pViewDir);
    static Int32 getSlicingDirection  (DrawActionBase *da, Vec3f  *pViewDir);

    static void  rotateToLocal        (DrawActionBase *da, Vec3f  &in, 
                                                           Vec3f  &out     );

    static bool  isBackToFront        (                    Int32  sliceDir ); 
};

OSG_END_NAMESPACE

#endif
