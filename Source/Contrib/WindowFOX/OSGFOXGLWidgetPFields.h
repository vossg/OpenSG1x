#ifndef _OSGFOXGLWIDGETPFIELDS_H_
#define _OSGFOXGLWIDGETPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowFOXDef.h>

#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGBaseFieldDataType.h>

OSG_BEGIN_NAMESPACE

class FOXGLWidget;
typedef FOXGLWidget* FOXGLWidgetP;

/*! \brief FOXGLWidgetP field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<FOXGLWidgetP> : 
    public FieldTraitsRecurseBase<FOXGLWidgetP>
{
    static DataType             _type;                       

    enum                        { StringConvertable = 0x00 };
    enum                        { bHasParent        = 0x01 };

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFFOXGLWidgetP"; }
    static char     *getMName(void) { return "MFFOXGLWidgetP"; }

    static bool      getFromString(      FOXGLWidgetP      &display,
                                   const Char8         *)
    {
        display=NULL;
        return true;
    }

    static void      putToString  (const      FOXGLWidgetP &,
                                         std::string   &outStr)
    {
        outStr.assign("DisplayP");
    }
};

//! SFFOXGLWidgetP
//! \ingroup SingleFields

typedef SField<FOXGLWidgetP> SFFOXGLWidgetP;

#ifndef OSG_COMPILEWINDOWFOXINST
#if defined(__sgi)

#pragma do_not_instantiate SField<FOXGLWidgetP>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, FOXGLWidgetP, OSG_WINDOWFOXLIB_DLLTMPLMAPPING)

#endif
#endif

//! MFFOXGLWidgetP
//! \ingroup MultiFields

typedef MField<FOXGLWidgetP> MFFOXGLWidgetP;

#ifndef OSG_COMPILEWINDOWFOXINST
#if defined(__sgi)

#pragma do_not_instantiate MField<FOXGLWidgetP>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, FOXGLWidgetP, OSG_WINDOWFOXLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif
