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


#ifndef _OSG_BASEFIELDDATATYPE_H_
#define _OSG_BASEFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGString.h>
#include <OSGTime.h>
#include <OSGColor.h>
#include <OSGDynamicVolume.h>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSG base field traits 
 */

template <>
struct OSGFieldDataTraits<OSGString> : public OSGTraits
{
    static char            *getSName(void)      { return "SFString";    }

    static char            *getMName(void)      { return "MFString";    }

    static OSGString        getDefault(void)    { return OSGString();   }

    static bool             getFromString(OSGString   &target,
                                          const char *&source)
    {
        target.set(source);

        if(source != NULL)
        {
            source += strlen(source);
        }

        return true;
    }

    static void             putToString(const OSGString &source,
                                              OSGString &target)
    {
        target = source;
    }
};

template <>
struct OSGFieldDataTraits<OSGColor3f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFColor3f";    }

    static char            *getMName(void)      { return "MFColor3f";    }

    static OSGColor3f       getDefault(void)    { return OSGColor3f();   }

    static bool             getFromString(OSGColor3f    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGColor3f &,
                                              OSGString  &)
    {
        // TO_BE_DONE
    }
};

template <>
struct OSGFieldDataTraits<OSGColor4f> : public OSGTraits
{
    static char            *getSName(void)      { return "SFColor4f";    }

    static char            *getMName(void)      { return "MFColor4f";    }

    static OSGColor4f       getDefault(void)    { return OSGColor4f();   }

    static bool             getFromString(OSGColor4f    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGColor4f &,
                                              OSGString  &)
    {
        // TO_BE_DONE
    }
};

template <>
struct OSGFieldDataTraits<OSGDynamicVolume> : public OSGTraits
{
    static char            *getSName(void)      { return "SFVolume";    }

    static char            *getMName(void)      { return "MFVolume";    }

    static OSGDynamicVolume getDefault(void)    { return OSGDynamicVolume();}

    static bool             getFromString(OSGDynamicVolume  &,
                                          const char       *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGDynamicVolume &,
                                              OSGString        &)
    {
        // TO_BE_DONE
    }
};

OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */


