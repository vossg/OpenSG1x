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


#ifndef _OSG_MATHFIELDDATATYPE_H_
#define _OSG_MATHFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGMatrix.h>
#include <OSGQuaternion.h>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGMatrix field traits 
 */

template <>
struct OSGFieldDataTraits<OSGMatrix> : public OSGTraits
{
    static char *getSName(void) { return "SFMatrix"; }
    static char *getMName(void) { return "MFMatrix"; }

//    static OSGMatrix        getDefault(void)    { return OSGMatrix; }

    static bool             getFromString(OSGMatrix   &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGMatrix &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGQuaternion field traits 
 */

template <>
struct OSGFieldDataTraits<OSGQuaternion> : public OSGTraits
{
    static char *getSName(void) { return "SFQuaternion"; }
    static char *getMName(void) { return "MFQuaternion"; }

//    static OSGQuaternion    getDefault(void)    { return OSGQuaternion; }

    static bool             getFromString(OSGQuaternion  &,
                                          const char    *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGQuaternion &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

OSG_END_NAMESPACE

#endif /* _OSG_MATHFIELDDATATYPE_H_ */
