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
 *  \brief  base field traits 
 */

template <>
struct FieldDataTraits<Color3f> : public Traits
{
    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static Char8            *getSName(void)      { return "SFColor3f";    }

    static Char8            *getMName(void)      { return "MFColor3f";    }

    static Color3f           getDefault(void)    { return Color3f();      }

    static Bool              getFromString(      Color3f  &,
                                           const Char8   *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const Color3f &,
                                              String  &)
    {
        // TO_BE_DONE
    }
};

template <>
struct FieldDataTraits<Color4f> : public Traits
{
    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static Char8            *getSName(void)      { return "SFColor4f";    }

    static Char8            *getMName(void)      { return "MFColor4f";    }

    static Color4f           getDefault(void)    { return Color4f();      }
 
    static Bool              getFromString(      Color4f  &,
                                           const Char8   *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const Color4f &,
                                              String  &)
    {
        // TO_BE_DONE
    }
};

template <>
struct FieldDataTraits<String> : public Traits
{
    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static Char8            *getSName(void)      { return "SFString";    }

    static Char8            *getMName(void)      { return "MFString";    }

    static String            getDefault(void)    { return String();      }

    static Bool              getFromString(     String  &target,
                                          const Char8  *&source)
    {
        target.set(source);

        if(source != NULL)
        {
            source += strlen(source);
        }

        return true;
    }

    static void             putToString(const String &source,
                                              String &target)
    {
        target = source;
    }
};

template <>
struct FieldDataTraits1<Time> : public Traits
{
    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static Char8            *getSName(void)      { return "SFTime";    }

    static Char8            *getMName(void)      { return "MFTime";    }

    static Time              getDefault(void)    { return Time();      }

    static Bool              getFromString(      Time   &outVal,
                                           const Char8 *&inVal)
    {
        outVal = TypeConstants<Time>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Time   &,
                                              String &)
    {
        // TO_BE_DONE
    }
};

template <>
struct FieldDataTraits<DynamicVolume> : 
    public Traits
{
    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static Char8            *getSName(void)      { return "SFVolume";      }

    static Char8            *getMName(void)      { return "MFVolume";      }

    static DynamicVolume     getDefault(void)    { return DynamicVolume(); }

    static Bool             getFromString(      DynamicVolume  &,
                                          const Char8         *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const DynamicVolume &,
                                              String        &)
    {
        // TO_BE_DONE
    }
};

template <>
struct FieldDataTraits1<BitVector> : 
    public Traits
{
    enum                     { StringConvertable = 0x00 };

    static Char8            *getSName(void)      { return "SFBitVector";   }

    static Char8            *getMName(void)      { return "MFBitVector";   }

    static BitVector         getDefault(void)    { return BitVector(); }
};


OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */




