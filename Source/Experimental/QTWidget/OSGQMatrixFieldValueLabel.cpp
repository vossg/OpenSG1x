
#include "OSGQMatrixFieldValueLabel.h"
#include "OSGQFieldLabelFactory.h"

#include <OSGMatrix.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQMatrixFieldValueLabel.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQMATRIXFIELDVALUELABEL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQMATRIXFIELDVALUELABEL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

namespace
{
    QLabelRegisterWrapper<QMatrixFieldValueLabel<Matrix4f> > 
    dummyMat4f("Matrix");
}
