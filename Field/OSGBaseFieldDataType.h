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

#ifndef _OSG_BASEFIELDDATATYPE_H_
#define _OSG_BASEFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGTime.h>
#include <OSGColor.h>
#include <OSGDynamicVolume.h>
#include <OSGSphereVolume.h>
#include <OSGBoxVolume.h>
#include <OSGPlane.h>

#include <string>

OSG_BEGIN_NAMESPACE

/*! \file OSGBaseFieldDataType.h
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
    \brief OpenSG Base Field Data Types  
*/

/*! \brief Color3f field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color3f> : 
    public FieldTraitsRecurseBase<Color3f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFColor3f";   }

    static Char8    *getMName     (void) { return "MFColor3f";   }

    static Color3f   getDefault   (void) { return Color3f();     }

    static bool      getFromString(      Color3f  &outVal,
                                   const Char8    *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const Color3f &inVal,
                                         string  &outStr)
    {
        typedef TypeConstants<Color3f::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.blue() ));
    }
};


/*! \brief Color4f field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color4f> : 
    public FieldTraitsRecurseBase<Color4f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFColor4f";   }

    static Char8    *getMName     (void) { return "MFColor4f";   }

    static Color4f   getDefault   (void){ return Color4f();      }
 
    static bool      getFromString(      Color4f  &outVal,
                                   const Char8   *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const Color4f &inVal,
                                         string  &outStr)
    {
        typedef TypeConstants<Color4f::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.blue() ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.alpha()));
    }
};


/*! \brief Color3ub field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color3ub> : 
    public FieldTraitsRecurseBase<Color3ub>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFColor3ub";  }
    static Char8    *getMName     (void) { return "MFColor3ub";  }

    static Color3ub  getDefault   (void) { return Color3ub();    }

    static bool      getFromString(      Color3ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }
    
    static void      putToString  (const Color3ub &inVal,
                                   string   &outStr)
    {
        typedef TypeConstants<Color3ub::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.blue() ));
    }
};


/*! \brief Color4ub field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Color4ub> : public FieldTraitsRecurseBase<Color4ub>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType (void)      { return _type;         }

    static Char8    *getSName     (void) { return "SFColor4ub";  }

    static Char8    *getMName     (void) { return "MFColor4ub";  }

    static Color4ub  getDefault   (void) { return Color4ub();    }

    static bool      getFromString(      Color4ub  &outVal,
                                   const Char8    *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const Color4ub &inVal,
                                         string   &outStr)
    {
        typedef TypeConstants<Color4ub::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.blue() ));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(inVal.alpha()));
    }
};


/*! \brief string field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<string> : 
    public FieldTraitsRecurseBase<string>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFString";    }

    static Char8    *getMName     (void) { return "MFString";    }

    static string    getDefault   (void) { return string();      }

    static bool      getFromString(      string  &target,
                                   const Char8  *&source)
    {
        target.assign(source);

        if(source != NULL)
        {
            source += strlen(source);
        }

        return true;
    }

    static void      putToString(const string &inVal,
                                       string &outStr)
    { 
        outStr.assign("\"");
        outStr.append(inVal);
        outStr.append("\"");
    }

    static UInt32    getBinSize (const string &oObject)
    {
        return oObject.length() + 1 + sizeof(UInt32);
    }

    static UInt32    getBinSize (const string *pObjectStore,
                                       UInt32  uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore,uiNumObjects);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const string              &oObject)
    {
        UInt32 size = 0;

        if(oObject.empty())
        {
            pMem.put(&size, sizeof(UInt32));
        }
        else
        {
            size = oObject.length() + 1;
            pMem.put(&size          , sizeof(UInt32));
            pMem.put(oObject.c_str(), size);
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const string            *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            string            &oObject)
    {
        UInt32  size;
        Char8  *str;

        pMem.get(&size, sizeof(UInt32));

        if(size == 0)
        {
            oObject.erase();
        }
        else
        {
            // we have to copy because the string maight not be
            // continous in pMem.

            str = new Char8[size];

            pMem   .get   (str, size);
            oObject.assign(str      );

            delete [] str;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            string            *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};


/*! \brief Time field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits1<Time> : 
    public FieldTraitsRecurseBase<Time>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFTime";      }

    static Char8    *getMName     (void) { return "MFTime";      }

    static Time      getDefault   (void) { return Time();        }

    static bool      getFromString(      Time   &outVal,
                                   const Char8 *&inVal)
    {
        outVal = TypeConstants<Time>::getFromString(inVal);

        return true;
    }

   static void      putToString(const Time   &inVal,
                                      string &outStr)
    {
        outStr.assign(TypeConstants<Time>::putToString(inVal));
    }
};


/*! \brief DynamicVolume field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<DynamicVolume> : 
    public FieldTraitsRecurseBase<DynamicVolume>
{
    static DataType      _type;

    enum                  { StringConvertable = ToStringConvertable       | 
                                                FromStringConvertable     };

    static DataType      &getType      (void) { return _type;             }

    static Char8         *getSName     (void) { return "SFDynamicVolume"; }

    static Char8         *getMName     (void) { return "MFDynamicVolume"; }

    static DynamicVolume  getDefault   (void) { return DynamicVolume();   }

    static bool           getFromString(      DynamicVolume  &outVal,
                                        const Char8         *&inVal)
    {
        Real32 valStore[  6];
        Char8  str     [256];

        UInt32  length = strlen(inVal);
        Char8  *c      = str;
    
        if(length > 256)
        {
            cerr << "FieldDataTraits<DynamicVolume>::getFromString(): "
                 << "Input too long" << endl;

            return false;
        }

        strncpy(str, inVal, length);

        while(*c != '\0')
        {
            if(*c == '[')
                *c = ' ';
            if(*c == ']')
                *c = ' ';
            if(*c == ',')
                *c = ' ';

            c++;
        }
        
        Int16 count = sscanf(str, "%f %f %f %f %f %f",
                             &valStore[0], &valStore[1], &valStore[2],
                             &valStore[3], &valStore[4], &valStore[5]);
        
        if(count == 4)
        {
            outVal.setVolumeType(DynamicVolume::SPHERE_VOLUME);

            SphereVolume &sVol = 
                dynamic_cast<SphereVolume &>(outVal.getInstance());

            sVol.setCenter(Pnt3f(valStore[0], valStore[1], valStore[2]));
            sVol.setRadius(valStore[3]);

            return true;
        }
        else if(count == 6)
        {
            outVal.setVolumeType(DynamicVolume::BOX_VOLUME);

            BoxVolume &bVol = dynamic_cast<BoxVolume &>(outVal.getInstance());

            bVol.setBounds(valStore[0], valStore[1], valStore[2],
                           valStore[3], valStore[4], valStore[5]);

            return true;
        }
        else
        {
            outVal.setVolumeType(DynamicVolume::BOX_VOLUME);

            BoxVolume &bVol = dynamic_cast<BoxVolume &>(outVal.getInstance());

            bVol.setBounds(0.,0.,0., 0.,0.,0.);

            return false;
        }
    }

    static void      putToString(const DynamicVolume &inVal,
                                       string        &outStr)
    {
        Pnt3f min, max;
        outStr.erase();
        switch(inVal.getType())
            {

            case DynamicVolume::BOX_VOLUME:

                typedef TypeConstants<Pnt3f::ValueType> TypeConst;

                inVal.getBounds(min, max);
                outStr.append(TypeConst::putToString(min.getValues()[0]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(min.getValues()[1]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(min.getValues()[2]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(max.getValues()[0]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(max.getValues()[1]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(max.getValues()[2]));
                break;


            case DynamicVolume::SPHERE_VOLUME:

                typedef TypeConstants<Pnt3f::ValueType> TypeConst;

                const SphereVolume &sVol = 
                    dynamic_cast<const SphereVolume&>(inVal.getInstance());

                outStr.append(TypeConst::putToString(sVol.getCenter()[0]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(sVol.getCenter()[1]));
                outStr.append(" ");
                outStr.append(TypeConst::putToString(sVol.getCenter()[1]));
                outStr.append(" ");
                outStr.append(TypeConstants<Real32>::
                              putToString(sVol.getRadius()));
                break;
            }
    }
        
    static UInt32 getBinSize(const DynamicVolume &oObject)
    {
        DynamicVolume::Type type = oObject.getType();
        UInt32              size = sizeof(DynamicVolume::Type);

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
                size += sizeof(Pnt3f) + sizeof(Pnt3f);
                break;

            case DynamicVolume::SPHERE_VOLUME :
                size += sizeof(Pnt3f) + sizeof(Real32);
                break;

            default :
                SWARNING << "Unknown volume type in getBinSize" << endl;
        }

        return sizeof(size);
    }

    static UInt32 getBinSize(const DynamicVolume *pObjectStore,
                                   UInt32         uiNumObjects)
    {
        UInt32 size = 0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[uiNumObjects]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const DynamicVolume       &oObject)
    {
        DynamicVolume::Type type = oObject.getType();

        pMem.put(&type, sizeof(DynamicVolume::Type));

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
            {
                const BoxVolume &bVol = 
                    dynamic_cast<const BoxVolume &>(oObject.getInstance());

                pMem.put(&bVol.getMin(), sizeof(Pnt3f));
                pMem.put(&bVol.getMax(), sizeof(Pnt3f));

                break;
            }
            case DynamicVolume::SPHERE_VOLUME :
            {
                const SphereVolume &sVol = 
                    dynamic_cast<const SphereVolume &>(oObject.getInstance());

                Real32 radius = sVol.getRadius();

                pMem.put(&sVol.getCenter(), sizeof(Pnt3f ));
                pMem.put(&radius,           sizeof(Real32));

                break;
            }

            default:
                SWARNING << "Unknown volume type in copyToBin" << endl;
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const DynamicVolume     *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            DynamicVolume     &oObject)
    {
        DynamicVolume::Type type;

        pMem.get(&type, sizeof(DynamicVolume::Type));

        oObject.setVolumeType(type);

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
            {
                BoxVolume &bVol = 
                    dynamic_cast<BoxVolume&>(oObject.getInstance());

                Pnt3f min,max;

                pMem.get(&min, sizeof(Pnt3f));
                pMem.get(&max, sizeof(Pnt3f));

                bVol.setBounds(min, max);

                break;
            }
            case DynamicVolume::SPHERE_VOLUME :
            {
                SphereVolume &sVol = 
                    dynamic_cast<SphereVolume&>(oObject.getInstance());

                Pnt3f center;
                Real32 radius;

                pMem.get(&center, sizeof(Pnt3f ));
                pMem.get(&radius, sizeof(Real32));

                sVol.setCenter(center);
                sVol.setRadius(radius);
                
                break;
            }

            default:
                SWARNING << "Unknown volume type in copyFronBin" << endl;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            DynamicVolume     *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

/*! \brief BitVector field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits1<BitVector> : 
    public FieldTraitsRecurseBase<BitVector>
{
    static DataType  _type;

    enum              { StringConvertable = 0x00 };

    static DataType  &getType (void)   { return _type;           }

    static Char8     *getSName(void)   { return "SFBitVector";   }

    static Char8     *getMName(void)   { return "MFBitVector";   }

    static BitVector  getDefault(void) { return BitVector();     }
};


/*! \brief Plane field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Plane> : 
    public FieldTraitsRecurseBase<Plane>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable    | 
                                           FromStringConvertable  };

    static DataType &getType      (void) { return _type;          }

    static Char8    *getSName     (void) { return "SFPlane";      }

    static Char8    *getMName     (void) { return "MFPlane";      }

    static Plane     getDefault   (void) { return Plane();        }

    static bool      getFromString(      Plane  &,
                                   const Char8 *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void      putToString  (const Plane  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Vec3f::ValueType> TypeConst;
        Vec3f  normal = inVal.getNormal();
        Real32 dist   = inVal.getDistanceFromOrigin();
        
        outStr.assign(TypeConst::putToString(normal.getValues()[0]));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(normal.getValues()[1]));
        outStr.append(" ");
        outStr.append(TypeConst::putToString(normal.getValues()[2]));
        outStr.append(", ");
        outStr.append(TypeConstants<Real32>::putToString(dist));
    }
};

OSG_END_NAMESPACE

#define OSGBASEFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_BASEFIELDDATATYPE_H_ */

