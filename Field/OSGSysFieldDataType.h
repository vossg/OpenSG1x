/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include <string>

OSG_BEGIN_NAMESPACE

/*! \file OSGSysFieldDataType.h
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
    \brief OpenSG Sys Field Data Types  
*/



/*! \brief bool field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits2<bool> : 
    public FieldTraitsIntegralRecurseMapper<bool>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFBool";      }
    static Char8    *getMName     (void) { return "MFBool";      }

    static bool      getDefault   (void) { return false;         }

    static bool      getFromString(      bool  &outVal,
                                   const Char8 *&inVal)
    {
        if(inVal == NULL)
            return false;

        if(inVal[0] == 'T' || inVal[0] == 't')
        {
            if(inVal[1] != 'R' && inVal[1] != 'r')
            {
                return false;
            }

            if(inVal[2] != 'U' && inVal[2] != 'u')
            {
                return false;
            }

            if(inVal[3] != 'E' && inVal[3] != 'e')
            {
                return false;
            }

            outVal = true;
        }
        else if(inVal[0] == 'F' || inVal[0] == 'f')
        {
            if(inVal[1] != 'A' && inVal[1] != 'a')
            {
                return false;
            }

            if(inVal[2] != 'L' && inVal[2] != 'l')
            {
                return false;
            }

            if(inVal[3] != 'S' && inVal[3] != 's')
            {
                return false;
            }

            if(inVal[4] != 'E' && inVal[4] != 'e')
            {
                return false;
            }

            outVal = false;
        }
        else
        {
            return false;
        }
        
        return outVal;
    }


    static void      putToString   (const bool                  &inVal,
                                          string                &outStr)
    {
        if( inVal == true )
        {
            outStr.assign("TRUE");
        }
        else
        {
            outStr.assign("FALSE");
        }
    }
         
};


/*! \brief Int8 field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Int8> : public FieldTraitsIntegralRecurseMapper<Int8>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFInt8";      }
    static Char8    *getMName     (void) { return "MFInt8";      }

    static Int8      getDefault   (void) { return 0;             }

    static bool      getFromString(      Int8   &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeConstants<Int8>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const Int8   &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Int8>::putToString(inVal));
    }
};

/*! \brief UInt8 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits<UInt8> : public FieldTraitsIntegralRecurseMapper<UInt8>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFUInt8";     }
    static Char8    *getMName     (void) { return "MFUInt8";     }

    static UInt8     getDefault   (void) { return 0;             }

    static bool      getFromString(      UInt8   &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt8>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const UInt8  &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<UInt8>::putToString(inVal));
    }
};


/*! \brief Int16 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits<Int16> : public FieldTraitsIntegralRecurseMapper<Int16>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFInt16";     }
    static Char8    *getMName     (void) { return "MFInt16";     }

    static Int16     getDefault   (void) { return 0;             }

    static bool      getFromString(      Int16  &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeConstants<Int16>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const Int16  &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Int16>::putToString(inVal)); 
    }
};

/*! \brief UInt16 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<UInt16> : 
    public FieldTraitsIntegralRecurseMapper<UInt16>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFUInt16";    }
    static Char8    *getMName     (void) { return "MFUInt16";    }

    static UInt16    getDefault   (void) { return 0;             }

    static bool      getFromString(      UInt16  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt16>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const UInt16 &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<UInt16>::putToString(inVal));
    }
};


/*! \brief Int32 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Int32> : 
    public FieldTraitsIntegralRecurseMapper<Int32>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFInt32";     }
    static Char8    *getMName     (void) { return "MFInt32";     }

    static Int32     getDefault   (void) { return 0;             }

    static bool      getFromString(      Int32  &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeConstants<Int32>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const Int32  &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Int32>::putToString(inVal));
    }
};

/*! \brief UInt32 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<UInt32> : 
    public FieldTraitsIntegralRecurseMapper<UInt32>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFUInt32";    }
    static Char8    *getMName     (void) { return "MFUInt32";    }

    static UInt32    getDefault   (void) { return 0;             }

    static bool      getFromString(      UInt32  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt32>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const UInt32 &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<UInt32>::putToString(inVal));
    }
};


/*! \brief Int64 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Int64> : 
    public FieldTraitsIntegralRecurseMapper<Int64>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFInt64";     }
    static Char8    *getMName     (void) { return "MFInt64";     }

    static Int64     getDefault   (void) { return 0;             }

    static bool      getFromString(      Int64   &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<Int64>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const Int64  &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Int64>::putToString(inVal));
    }
};

/*! \brief UInt64 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<UInt64> : 
    public FieldTraitsIntegralRecurseMapper<UInt64>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFUInt64";    }
    static Char8    *getMName     (void) { return "MFUInt64";    }

    static UInt64    getDefault   (void) { return 0;             }

    static bool      getFromString(      UInt64  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<UInt64>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const UInt64 &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<UInt64>::putToString(inVal));
    }
};


/*! \brief Real32 field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/


template <>
struct FieldDataTraits<Real32> : 
    public FieldTraitsIntegralRecurseMapper<Real32>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFReal32";    }
    static Char8    *getMName     (void) { return "MFReal32";    }

    static Real32    getDefault   (void) { return 0.f;           }

    static bool      getFromString(      Real32  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<Real32>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const Real32 &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Real32>::putToString(inVal));
    }
};


/*! \brief Real64 field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Real64> : 
    public FieldTraitsIntegralRecurseMapper<Real64>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFReal64";    }
    static Char8    *getMName     (void) { return "MFReal64";    }

    static Real64    getDefault   (void) { return 0.;            }

    static bool      getFromString(      Real64  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeConstants<Real64>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const Real64 &inVal,
                                         string &outStr)
    {
        outStr.assign(TypeConstants<Real64>::putToString(inVal));
    }
};

OSG_END_NAMESPACE

#define OSGSYSFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_SYSFIELDDATATYPE_H_ */

