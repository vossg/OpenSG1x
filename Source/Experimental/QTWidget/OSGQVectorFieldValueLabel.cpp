
#include "OSGSFVecTypes.h"
#include "OSGMFVecTypes.h"
#include "OSGQVectorFieldValueLabel.h"
#include "OSGQFieldLabelFactory.h"
#include <OSGBaseFunctions.h>
#include <OSGVector.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQVectorFieldValueLabel.cpp,v 1.2 2003/05/10 05:28:28 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGQVECTORFIELDVALUELABEL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQVECTORFIELDVALUELABEL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

namespace
{
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec2s> > dummyVec2s("Vec2s");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec2f> > dummyVec2f("Vec2f");
    
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec3d> > dummyVec3d("Vec3d");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec3f> > dummyVec3f("Vec3f");

//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4ub> > dummyVec4ub("Vec4ub");
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4d> > dummyVec4d("Vec4d");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4f> > dummyVec4f("Vec4f");
}

