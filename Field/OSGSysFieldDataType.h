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


#ifndef _OSG_SYSFIELDDATATYPE_H_
#define _OSG_SYSFIELDDATATYPE_H_

#include <OSGFieldDataType.h>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGBool field traits 
 */

template <>
struct OSGFieldDataTraits<OSGBool> : public OSGTraits
{
    static char            *getSName(void)      { return "SFBool";    }
    static char            *getMName(void)      { return "MFBool";    }

    static OSGBool          getDefault(void)    { return false; }

    static bool             getFromString(OSGBool     &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGBool   &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGInt8 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGInt8> : public OSGTraits
{
    static char            *getSName(void)      { return "SFInt8";    }
    static char            *getMName(void)      { return "MFInt8";    }

    static OSGInt8          getDefault(void)    { return 0; }

    static bool             getFromString(OSGInt8     &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGInt8   &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGUInt8 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGUInt8> : public OSGTraits
{
    static char            *getSName(void)      { return "SFUInt8";    }
    static char            *getMName(void)      { return "MFUInt8";    }

    static OSGUInt8         getDefault(void)    { return 0; }

    static bool             getFromString(OSGUInt8    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGUInt8  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGInt16 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGInt16> : public OSGTraits
{
    static char            *getSName(void)      { return "SFInt16";    }
    static char            *getMName(void)      { return "MFInt16";    }

    static OSGInt16         getDefault(void)    { return 0; }

    static bool             getFromString(OSGInt16    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGInt16  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGUInt16 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGUInt16> : public OSGTraits
{
    static char            *getSName(void)      { return "SFUInt16";    }
    static char            *getMName(void)      { return "MFUInt16";    }

    static OSGUInt16        getDefault(void)    { return 0; }

    static bool             getFromString(OSGUInt16    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGUInt16  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGInt32 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGInt32> : public OSGTraits
{
    static char            *getSName(void)      { return "SFInt32";    }
    static char            *getMName(void)      { return "MFInt32";    }

    static OSGInt32         getDefault(void)    { return 0; }

    static bool             getFromString(OSGInt32    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGInt32  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGUInt32 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGUInt32> : public OSGTraits
{
    static char            *getSName(void)      { return "SFUInt32";    }
    static char            *getMName(void)      { return "MFUInt32";    }

    static OSGUInt32        getDefault(void)    { return 0; }

    static bool             getFromString(OSGUInt32    &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGUInt32  &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGInt64 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGInt64> : public OSGTraits
{
    static char            *getSName(void)      { return "SFInt64";    }
    static char            *getMName(void)      { return "MFInt64";    }

    static OSGInt64         getDefault(void)    { return 0; }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGUInt64 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGUInt64> : public OSGTraits
{
    static char            *getSName(void)      { return "SFUInt64";    }
    static char            *getMName(void)      { return "MFUInt64";    }

    static OSGUInt64        getDefault(void)    { return 0; }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGReal32 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGReal32> : public OSGTraits
{
    static char            *getSName(void)      { return "SFReal32";    }
    static char            *getMName(void)      { return "MFReal32";    }

    static OSGReal32        getDefault(void)    { return 0.f; }

    static bool             getFromString(OSGReal32   &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGReal32 &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGReal64 field traits 
 */

template <>
struct OSGFieldDataTraits<OSGReal64> : public OSGTraits
{
    static char            *getSName(void)      { return "SFReal64";    }
    static char            *getMName(void)      { return "MFReal64";    }

    static OSGReal64        getDefault(void)    { return 0.; }
};

OSG_END_NAMESPACE

#endif /* _OSG_SYSFIELDDATATYPE_H_ */
