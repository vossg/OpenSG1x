/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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


#ifndef _OSG_VECFIELDDATATYPE_H_
#define _OSG_VECFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGVector.h>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGVec2f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGVec2f> : public OSGTraits
{
    static char *getSName(void) { return "SFVec2f"; }
    static char *getMName(void) { return "MFVec2f"; }

    static OSGVec2f        getDefault(void)     { return OSGVec2f();   }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGVec3f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGVec3f> : public OSGTraits
{
    static char *getSName(void) { return "SFVec3f"; }
    static char *getMName(void) { return "MFVec3f"; }

    static OSGVec3f        getDefault(void)     { return OSGVec3f();   }

    static bool             getFromString(OSGVec3f    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGVec3f  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGVec4f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGVec4f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFVec4f";    }

    static char            *getMName(void)      { return "MFVec4f";    }

    static OSGVec4f        getDefault(void)     { return OSGVec4f();   }

    static bool             getFromString(OSGVec4f    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGVec4f  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGPnt2f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGPnt2f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFPnt2f";    }

    static char            *getMName(void)      { return "MFPnt2f";    }

    static OSGPnt2f        getDefault(void)     { return OSGPnt2f();   }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGVec4ub field traits 
 */

template <>
struct OSGFieldDataTraits<OSGVec4ub> : public OSGTraits
{
    static char            *getSName(void)      { return "SFVec4ub";    }

    static char            *getMName(void)      { return "MFVec4ub";    }

    static OSGVec4ub        getDefault(void)     { return OSGVec4ub();   }

    static bool             getFromString(OSGVec4ub   &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGVec4ub &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGPnt3f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGPnt3f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFPnt3f";    }

    static char            *getMName(void)      { return "MFPnt3f";    }

    static OSGPnt3f        getDefault(void)     { return OSGPnt3f();   }

    static bool             getFromString(OSGPnt3f    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGPnt3f  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGPnt4f field traits 
 */

template <>
struct OSGFieldDataTraits<OSGPnt4f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFPnt4f";    }

    static char            *getMName(void)      { return "MFPnt4f";    }

    static OSGPnt4f         getDefault(void)    { return OSGPnt4f();   }
};

OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */
