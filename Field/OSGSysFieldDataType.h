/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
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
 *  \brief Bool field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Bool> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFBool";    }
    static Char8           *getMName(void)      { return "MFBool";    }

    static Bool             getDefault(void)    { return false; }

    static Bool             getFromString(Bool         &outVal,
                                          const Char8 *&inVal)
    {
        if(inVal == NULL)
            return false;

        if(inVal[0] == 'T' || inVal[0] == 't')
        {
            if(inVal[1] != 'R' && inVal[1] != 'r' )
            {
                return false;
            }

            if(inVal[2] != 'U' && inVal[2] != 'u' )
            {
                return false;
            }

            if(inVal[3] != 'E' && inVal[3] != 'e' )
            {
                return false;
            }

            outVal = true;
        }
        else if(inVal[0] == 'F' || inVal[0] == 'f')
        {
            if(inVal[1] != 'A' && inVal[1] != 'a' )
            {
                return false;
            }

            if(inVal[2] != 'L' && inVal[2] != 'l' )
            {
                return false;
            }

            if(inVal[3] != 'S' && inVal[3] != 's' )
            {
                return false;
            }

            if(inVal[4] != 'E' && inVal[4] != 'e' )
            {
                return false;
            }

            outVal = false;
        }
        else
        {
            return false;
        }
        
        return true;
    }

    static void             putToString(const Bool   &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Int8 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Int8> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFInt8";    }
    static Char8           *getMName(void)      { return "MFInt8";    }

    static Int8             getDefault(void)    { return 0; }

    static Bool             getFromString(      Int8   &outVal,
                                          const Char8 *&inVal)
    {
        outVal = TypeConstants<Int8>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Int8   &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief UInt8 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<UInt8> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFUInt8";    }
    static Char8           *getMName(void)      { return "MFUInt8";    }

    static UInt8            getDefault(void)    { return 0; }

    static Bool             getFromString(      UInt8   &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt8>::getFromString(inVal);

        return true;
    }

    static void             putToString(const UInt8  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Int16 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Int16> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFInt16";    }
    static Char8           *getMName(void)      { return "MFInt16";    }

    static Int16            getDefault(void)    { return 0; }

    static Bool             getFromString(      Int16  &outVal,
                                          const Char8 *&inVal)
    {
        outVal = TypeConstants<Int16>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Int16  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief UInt16 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<UInt16> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFUInt16";    }
    static Char8           *getMName(void)      { return "MFUInt16";    }

    static UInt16           getDefault(void)    { return 0; }

    static Bool             getFromString(      UInt16  &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt16>::getFromString(inVal);

        return true;
    }

    static void             putToString(const UInt16  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Int32 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Int32> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFInt32";    }
    static Char8           *getMName(void)      { return "MFInt32";    }

    static Int32            getDefault(void)    { return 0; }

    static Bool             getFromString(      Int32  &outVal,
                                          const Char8 *&inVal)
    {
        outVal = TypeConstants<Int32>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Int32  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief UInt32 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<UInt32> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFUInt32";    }
    static Char8           *getMName(void)      { return "MFUInt32";    }

    static UInt32           getDefault(void)    { return 0; }

    static Bool             getFromString(      UInt32  &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt32>::getFromString(inVal);

        return false;
    }

    static void             putToString(const UInt32  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Int64 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Int64> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFInt64";    }
    static Char8           *getMName(void)      { return "MFInt64";    }

    static Int64            getDefault(void)    { return 0; }

    static Bool             getFromString(      Int64   &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<Int64>::getFromString(inVal);

        return false;
    }

    static void             putToString(const Int64  &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief UInt64 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<UInt64> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFUInt64";    }
    static Char8           *getMName(void)      { return "MFUInt64";    }

    static UInt64           getDefault(void)    { return 0; }

    static Bool             getFromString(      UInt64  &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt64>::getFromString(inVal);

        return false;
    }

    static void             putToString(const UInt64 &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Real32 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Real32> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFReal32";    }
    static Char8           *getMName(void)      { return "MFReal32";    }

    static Real32           getDefault(void)    { return 0.f; }

    static Bool             getFromString(      Real32  &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<Real32>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Real32 &,
                                              String &)
    {
        // TO_BE_DONE
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Real64 field traits 
 */

template <>
struct OSG_DLLEXPORT FieldDataTraits<Real64> : public Traits
{
    enum                    { StringConvertable = ToStringConvertable | 
                                                  FromStringConvertable };

    static Char8           *getSName(void)      { return "SFReal64";    }
    static Char8           *getMName(void)      { return "MFReal64";    }

    static Real64           getDefault(void)    { return 0.; }

    static Bool             getFromString(      Real64  &outVal,
                                          const Char8  *&inVal)
    {
        outVal = TypeConstants<Real64>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Real64 &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

OSG_END_NAMESPACE

#endif /* _OSG_SYSFIELDDATATYPE_H_ */

