#define OSG_COMPILEWINDOWFOXINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGFOXGLWidgetPFields.h"

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<FOXGLWidgetP>::_type("FOXGLWidgetP", "IntegralType");

#if defined(__sgi)

#pragma instantiate SField<FOXGLWidgetP>::_fieldType
#pragma instantiate MField<FOXGLWidgetP>::_fieldType

#else

OSG_DLLEXPORT_SFIELD_DEF1(FOXGLWidgetP, OSG_WINDOWFOXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(FOXGLWidgetP, OSG_WINDOWFOXLIB_DLLTMPLMAPPING);

#endif

OSG_END_NAMESPACE
