/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSysFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
#ifndef OSG_WIN32_CL
struct OSG_BASE_DLLMAPPING FieldDataTraits2<bool> :
#else
struct FieldDataTraits2<bool> :
#endif
    public FieldTraitsIntegralRecurseMapper<bool>
{
    static  DataType               _type;

    typedef FieldDataTraits2<bool>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFBool";            }
    static Char8    *getMName     (void) { return "MFBool";            }

    static bool      getDefault   (void) { return false;               }

    static bool      getFromString(      bool   &outVal,
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

    static void      putToString   (const      bool                  &inVal,
                                          std::string                &outStr)
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
         
#ifndef OSG_WIN32_CL
    static       UInt32    getBinSize (const bool & )
    {
        return sizeof(UInt8);
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const bool              &oObject)
    {
        UInt8 value=oObject;
        pMem.putValue(value);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    bool              &oObject)
    {
        UInt8 value;
        pMem.getValue(value);
        oObject=value;
    }
#endif
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<bool> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Int8> :
    public FieldTraitsIntegralRecurseMapper<Int8>
{
    static  DataType              _type;
    typedef FieldDataTraits<Int8>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFInt8";            }
    static Char8    *getMName     (void) { return "MFInt8";            }

    static Int8      getDefault   (void) { return 0;                   }

    static bool      getFromString(      Int8   &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeTraits<Int8>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const      Int8   &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Int8>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Int8> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<UInt8> :
    public FieldTraitsIntegralRecurseMapper<UInt8>
{
    static  DataType               _type;
    typedef FieldDataTraits<UInt8>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFUInt8";           }
    static Char8    *getMName     (void) { return "MFUInt8";           }

    static UInt8     getDefault   (void) { return 0;                   }

    static bool      getFromString(      UInt8   &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<UInt8>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const      UInt8  &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<UInt8>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<UInt8> */
/*! \hideinhierarchy                                */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Int16> :
    public FieldTraitsIntegralRecurseMapper<Int16>
{
    static  DataType               _type;
    typedef FieldDataTraits<Int16>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFInt16";           }
    static Char8    *getMName     (void) { return "MFInt16";           }

    static Int16     getDefault   (void) { return 0;                   }

    static bool      getFromString(      Int16  &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeTraits<Int16>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const      Int16  &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Int16>::putToString(inVal)); 
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Int16> */
/*! \hideinhierarchy                                */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<UInt16> : 
    public FieldTraitsIntegralRecurseMapper<UInt16>
{
    static  DataType                _type;
    typedef FieldDataTraits<UInt16>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFUInt16";          }
    static Char8    *getMName     (void) { return "MFUInt16";          }

    static UInt16    getDefault   (void) { return 0;                   }

    static bool      getFromString(      UInt16  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<UInt16>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const      UInt16 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<UInt16>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<UInt16> */
/*! \hideinhierarchy                                 */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Int32> : 
    public FieldTraitsIntegralRecurseMapper<Int32>
{
    static  DataType               _type;
    typedef FieldDataTraits<Int32>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFInt32";           }
    static Char8    *getMName     (void) { return "MFInt32";           }

    static Int32     getDefault   (void) { return 0;                   }

    static bool      getFromString(      Int32  &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeTraits<Int32>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const      Int32  &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Int32>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Int32> */
/*! \hideinhierarchy                                */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<UInt32> : 
    public FieldTraitsIntegralRecurseMapper<UInt32>
{
    static  DataType                _type;
    typedef FieldDataTraits<UInt32>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFUInt32";          }
    static Char8    *getMName     (void) { return "MFUInt32";          }

    static UInt32    getDefault   (void) { return 0;                   }

    static bool      getFromString(      UInt32  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<UInt32>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const      UInt32 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<UInt32>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<UInt32> */
/*! \hideinhierarchy                                 */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Int64> : 
    public FieldTraitsIntegralRecurseMapper<Int64>
{
    static  DataType               _type;
    typedef FieldDataTraits<Int64>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFInt64";           }
    static Char8    *getMName     (void) { return "MFInt64";           }

    static Int64     getDefault   (void) { return 0;                   }

    static bool      getFromString(      Int64   &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<Int64>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const      Int64  &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Int64>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Int64> */
/*! \hideinhierarchy                                */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<UInt64> : 
    public FieldTraitsIntegralRecurseMapper<UInt64>
{
    static  DataType                _type;
    typedef FieldDataTraits<UInt64>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFUInt64";          }
    static Char8    *getMName     (void) { return "MFUInt64";          }

    static UInt64    getDefault   (void) { return 0;                   }

    static bool      getFromString(      UInt64  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<UInt64>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const      UInt64 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<UInt64>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<UInt64> */
/*! \hideinhierarchy                                 */
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Real16> : 
    public FieldTraitsIntegralRecurseMapper<Real16>
{
    static  DataType                _type;
    typedef FieldDataTraits<Real16>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFReal16";          }
    static Char8    *getMName     (void) { return "MFReal16";          }

    static Real16    getDefault   (void) { return 0.f;                 }

    static bool      getFromString(      Real16  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<Real16>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const      Real16 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Real16>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Real16> */
/*! \hideinhierarchy                                 */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Real32> : 
    public FieldTraitsIntegralRecurseMapper<Real32>
{
    static  DataType                _type;
    typedef FieldDataTraits<Real32>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFReal32";          }
    static Char8    *getMName     (void) { return "MFReal32";          }

    static Real32    getDefault   (void) { return 0.f;                 }

    static bool      getFromString(      Real32  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<Real32>::getFromString(inVal);

        return true;
    }

    static void      putToString  (const      Real32 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Real32>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsIntegralRecurseMapper<Real32> */
/*! \hideinhierarchy                                 */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Real64> : 
    public FieldTraitsIntegralRecurseMapper<Real64>
{
    static  DataType                _type;
    typedef FieldDataTraits<Real64>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFReal64";          }
    static Char8    *getMName     (void) { return "MFReal64";          }

    static Real64    getDefault   (void) { return 0.;                  }

    static bool      getFromString(      Real64  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<Real64>::getFromString(inVal);
        
        return true;
    }

    static void      putToString  (const      Real64 &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<Real64>::putToString(inVal));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsIntegralRecurseMapper<Real64> */
/*! \hideinhierarchy                                */
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<void *> : 
    public FieldTraitsRecurseBase<void *>
{
    static  DataType                 _type;
    typedef FieldDataTraits<void *>  Self;
    typedef void *                   ArgumentType;
    typedef void *                   FieldTypeT;

    enum             { StringConvertable = 0x00                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVoidP";           }
    static Char8    *getMName     (void) { return "MFVoidP";           }

    static void     *getDefault   (void) { return NULL;                }

    static bool      getFromString(      FieldTypeT &voidP,
                                   const Char8      *inStr)
    {
        if(inStr[0] == '0' && tolower(inStr[1]) == 'x')
        {
            if(sscanf(inStr + 2, "%p", &voidP) != 1)
            {
                voidP = NULL;
                FWARNING(("FieldDataTraits<void *>::getFromString: '%s' "
                          "not understood!\n", inStr));
                return false;
            }
        }
        else
        {
            if(sscanf(inStr, "%lu", 
                        reinterpret_cast<unsigned long *>(&voidP)) != 1)
            {
                voidP = NULL;
                FWARNING(("FieldDataTraits<void *>::getFromString: '%s' "
                          "not understood!\n", inStr));
                return false;
            }
        }

        return true;
    }

    static void      putToString  (const FieldTypeT  &voidP,
                                         std::string &outStr)
    {
        char buf[32];
        sprintf(buf, "%p", voidP);
        outStr = buf;
    }
};


#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGSYSFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_SYSFIELDDATATYPE_H_ */





