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


#ifndef _OSG_CONTAINERFIELDDATATYPE_H_
#define _OSG_CONTAINERFIELDDATATYPE_H_

#include <OSGFieldDataType.h>

OSG_BEGIN_NAMESPACE

class OSGFieldContainer;
class OSGNodePtr;
class OSGNodeCorePtr;
class OSGPropertyPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGFieldContainerPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGFieldContainerPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFFieldContainerPtr"; }
    static char *getMName(void) { return "MFFieldContainerPtr"; }

    static bool             getFromString(OSGFieldContainerPtr  &,
                                          const char           *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGFieldContainerPtr &,
                                              OSGString            &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGNodePtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGNodePtr> : public OSGTraits
{
    static char *getSName(void) { return "SFNodePtr"; }
    static char *getMName(void) { return "MFNodePtr"; }

    static bool             getFromString(OSGNodePtr  &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGNodePtr &,
                                              OSGString  &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGNodeCorePtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGNodeCorePtr> : public OSGTraits
{
    static char *getSName(void) { return "SFNodeCorePtr"; }
    static char *getMName(void) { return "MFNodeCorePtr"; }

    static bool             getFromString(OSGNodeCorePtr  &,
                                          const char     *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGNodeCorePtr &,
                                              OSGString      &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGPropertyPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGPropertyPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFPropertyPtr"; }
    static char *getMName(void) { return "MFPropertyPtr"; }
};

OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */







