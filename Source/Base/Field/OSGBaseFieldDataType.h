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

#ifndef _OSG_BASEFIELDDATATYPE_H_
#define _OSG_BASEFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGTime.h>
#include <OSGColor.h>
#include <OSGDynamicVolume.h>
#include <OSGSphereVolume.h>
#include <OSGBoxVolume.h>
#include <OSGPlane.h>
#include <OSGGL.h>

#include <string>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGBaseFieldDataType.h
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
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color3f> : 
    public FieldTraitsRecurseBase<Color3f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType &getType      (void) { return _type;         }

    static const Char8    *getSName     (void) { return "SFColor3f";   }

    static const Char8    *getMName     (void) { return "MFColor3f";   }

    static const Color3f   getDefault   (void) { return Color3f();     }

    static       bool      getFromString(      Color3f  &outVal,
                                         const Char8    *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static       void      putToString  (const      Color3f &inVal,
                                               std::string  &outStr)
    {
        typedef TypeTraits<Color3f::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.blue() ));
    }
    
    static       UInt32    getBinSize (const Color3f &)
    {
        return sizeof(Real32) * 3;
    }

    static       UInt32    getBinSize (const Color3f *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Real32)* 3 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Color3f           &oObject)
    {
        pMem.putValues(&oObject[0], 3);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Color3f           &oObject)
    {
        pMem.getValues(&oObject[0], 3);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Color3f     *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0], uiNumObjects*3);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Color3f           *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0], uiNumObjects*3);
    }


};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Color3f> */
/*! \hideinhierarchy                        */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color4f> : 
    public FieldTraitsRecurseBase<Color4f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType &getType      (void) { return _type;         }

    static const Char8    *getSName     (void) { return "SFColor4f";   }

    static const Char8    *getMName     (void) { return "MFColor4f";   }

    static       Color4f   getDefault   (void){ return Color4f();      }
 
    static       bool      getFromString(      Color4f  &outVal,
                                         const Char8   *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static       void      putToString  (const      Color4f &inVal,
                                               std::string  &outStr)
    {
        typedef TypeTraits<Color4f::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.blue() ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.alpha()));
    }
    
    static       UInt32    getBinSize (const Color4f &)
    {
        return sizeof(Real32) * 4;
    }

    static       UInt32    getBinSize (const Color4f *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Real32) * 4 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Color4f        &oObject)
    {
        pMem.putValues(&oObject[0], 4);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Color4f           &oObject)
        {
        pMem.getValues(&oObject[0], 4);
        }
    
    
    static void copyToBin(      BinaryDataHandler &pMem,
                                const Color4f     *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.putValues(&pObjectStore[0][0], uiNumObjects*4);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Color4f           *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.getValues(&pObjectStore[0][0], uiNumObjects*4);
    }



};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Color4f> */
/*! \hideinhierarchy                        */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color3ub> : 
    public FieldTraitsRecurseBase<Color3ub>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType &getType      (void) { return _type;         }

    static const Char8    *getSName     (void) { return "SFColor3ub";  }
    static const Char8    *getMName     (void) { return "MFColor3ub";  }

    static       Color3ub  getDefault   (void) { return Color3ub();    }

    static       bool      getFromString(      Color3ub  &outVal,
                                         const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }
    
    static       void       putToString  (const      Color3ub &inVal,
                                                std::string   &outStr)
    {
        typedef TypeTraits<Color3ub::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.blue() ));
    }

    static       UInt32    getBinSize (const Color3ub &)
    {
        return sizeof(UInt8) * 3;
    }

    static       UInt32    getBinSize (const Color3ub *,
                                             UInt32    uiNumObjects)
    {
        return sizeof(UInt8)* 3 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Color3ub        &oObject)
    {
        pMem.putValues(&oObject[0], 3);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Color3ub           &oObject)
    {
        pMem.getValues(&oObject[0], 3);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Color3ub    *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.putValues(&pObjectStore[0][0], uiNumObjects*3);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Color3ub          *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.getValues(&pObjectStore[0][0], uiNumObjects*3);
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Color3ub> */
/*! \hideinhierarchy                         */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Color4ub> :
    public FieldTraitsRecurseBase<Color4ub>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType &getType      (void) { return _type;         }

    static const Char8    *getSName     (void) { return "SFColor4ub";  }

    static const Char8    *getMName     (void) { return "MFColor4ub";  }

    static       Color4ub  getDefault   (void) { return Color4ub();    }

    static       bool      getFromString(      Color4ub  &outVal,
                                         const Char8    *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static       void      putToString  (const      Color4ub &inVal,
                                               std::string   &outStr)
    {
        typedef TypeTraits<Color4ub::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString(inVal.red()  ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.green()));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.blue() ));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(inVal.alpha()));
    }

    static       UInt32    getBinSize (const Color4ub &)
    {
        return sizeof(UInt8) * 4;
    }

    static       UInt32    getBinSize (const Color4ub *,
                                             UInt32    uiNumObjects)
    {
        return sizeof(UInt8) * 4 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Color4ub        &oObject)
    {
        pMem.putValues(&oObject[0], 4);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Color4ub         &oObject)
    {
        pMem.getValues(&oObject[0], 4);
    }


    static void copyToBin(      BinaryDataHandler &pMem,
                                const Color4ub    *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.putValues(&pObjectStore[0][0], uiNumObjects*4);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Color4ub          *pObjectStore,
                                UInt32             uiNumObjects)
    {
	    pMem.getValues(&pObjectStore[0][0], uiNumObjects*4);
    }




};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Color4ub> */
/*! \hideinhierarchy                         */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<std::string> : 
    public FieldTraitsRecurseBase<std::string>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType   &getType      (void) { return _type;         }

    static const Char8      *getSName     (void) { return "SFString";    }

    static const Char8      *getMName     (void) { return "MFString";    }

    static       std::string getDefault   (void) { return std::string(); }

    static       bool        getFromString(      std::string  &target,
                                           const      Char8  *&source)
    {
        target.assign(source);

        if(source != NULL)
        {
            source += strlen(source);
        }

        return true;
    }

    static       void      putToString(const std::string &inVal,
                                             std::string &outStr)
    { 
        outStr.assign("\"");
        outStr.append(inVal);
        outStr.append("\"");
    }


    static       UInt32    getBinSize (const std::string &oObject)
    {
        return oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const std::string *pObjectStore,
                                                  UInt32  uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(           BinaryDataHandler   &pMem, 
                          const std::string              &oObject)
    {
    	pMem.putValue(oObject);
    }

    static void copyToBin(           BinaryDataHandler &pMem, 
                          const std::string            *pObjectStore,
                                     UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(     BinaryDataHandler &pMem, 
                            std::string            &oObject)
    {
        pMem.getValue(oObject);
    }

    static void copyFromBin(     BinaryDataHandler &pMem, 
                            std::string            *pObjectStore,
                                 UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<std::string> */
/*! \hideinhierarchy                            */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits1<Time> : 
    public FieldTraitsRecurseBase<Time>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable       };

    static       DataType &getType      (void) { return _type;         }

    static const Char8    *getSName     (void) { return "SFTime";      }

    static const Char8    *getMName     (void) { return "MFTime";      }

    static       Time      getDefault   (void) { return Time();        }

    static       bool      getFromString(      Time   &outVal,
                                         const Char8 *&inVal)
    {
        outVal = TypeTraits<Time>::getFromString(inVal);

        return true;
    }

   static        void      putToString(const      Time   &inVal,
                                             std::string &outStr)
    {
        outStr.assign(TypeTraits<Time>::putToString(inVal));
    }

    static       UInt32    getBinSize (const Time &)
    {
        return sizeof(Time);
    }

    static       UInt32    getBinSize (const Time   *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Time)*uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const Time                &oObject)
    {
    	pMem.putValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            Time              &oObject)
    {
        pMem.getValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Time        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0], uiNumObjects);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Time              *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0], uiNumObjects);
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Time> */
/*! \hideinhierarchy                     */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<DynamicVolume> : 
    public FieldTraitsRecurseBase<DynamicVolume>
{
    static DataType      _type;

    enum                  { StringConvertable = ToStringConvertable       | 
                                                FromStringConvertable     };

    static       DataType     &getType     (void) { return _type;             }

    static const Char8        *getSName    (void) { return "SFDynamicVolume"; }

    static const Char8        *getMName    (void) { return "MFDynamicVolume"; }

    static const DynamicVolume getDefault  (void) { return DynamicVolume();   }

    static bool               getFromString(      DynamicVolume  &outVal,
                                            const Char8         *&inVal)
    {
        Real32 valStore[  6];
        Char8  str     [256];

        UInt32  length = strlen(inVal);
        Char8  *c      = str;
    
        if(length > 256)
        {
            std::cerr << "FieldDataTraits<DynamicVolume>::getFromString(): "
                      << "Input too long" << std::endl;

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

            SphereVolume *pSVol = 
                    dynamic_cast<SphereVolume *>(&(outVal.getInstance()));

            pSVol->setCenter(Pnt3f(valStore[0], valStore[1], valStore[2]));
            pSVol->setRadius(valStore[3]);
            
            outVal.instanceChanged();

            return true;
        }
        else if(count == 6)
        {
            outVal.setVolumeType(DynamicVolume::BOX_VOLUME);

            BoxVolume *pBVol = 
                dynamic_cast<BoxVolume *>(&(outVal.getInstance()));

            pBVol->setBounds(valStore[0], valStore[1], valStore[2],
                             valStore[3], valStore[4], valStore[5]);
            
            outVal.instanceChanged();

            return true;
        }
        else
        {
            outVal.setVolumeType(DynamicVolume::BOX_VOLUME);

            BoxVolume *pBVol = 
                dynamic_cast<BoxVolume *>(&(outVal.getInstance()));

            pBVol->setBounds(0.,0.,0., 0.,0.,0.);
            
            outVal.instanceChanged();

            return false;
        }
    }

    static void putToString(const      DynamicVolume &inVal,
                                  std::string        &outStr)
    {
        Pnt3f min, max;
        outStr.erase();

        switch(inVal.getType())
        {

            case DynamicVolume::BOX_VOLUME:

                typedef TypeTraits<Pnt3f::ValueType> TypeTrait;

                inVal.getBounds(min, max);
                outStr.append(TypeTrait::putToString(min.getValues()[0]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(min.getValues()[1]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(min.getValues()[2]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(max.getValues()[0]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(max.getValues()[1]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(max.getValues()[2]));
                break;


            case DynamicVolume::SPHERE_VOLUME:

                typedef TypeTraits<Pnt3f::ValueType> TypeTrait;

                const SphereVolume &sVol = 
                    dynamic_cast<const SphereVolume&>(inVal.getInstance());

                outStr.append(TypeTrait::putToString(sVol.getCenter()[0]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(sVol.getCenter()[1]));
                outStr.append(" ");
                outStr.append(TypeTrait::putToString(sVol.getCenter()[1]));
                outStr.append(" ");
                outStr.append(TypeTraits<
                                  Real32>::putToString(sVol.getRadius()));
                break;
        }
    }
        
    static UInt32 getBinSize(const DynamicVolume &oObject)
    {
        UInt32  type = oObject.getType();
        UInt32  size = sizeof(DynamicVolume::Type) + sizeof(UInt16);

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
                size += sizeof(Pnt3f) + sizeof(Pnt3f);
                break;

            case DynamicVolume::SPHERE_VOLUME :
                size += sizeof(Pnt3f) + sizeof(Real32);
                break;

            default :
                SWARNING << "Unknown volume type in getBinSize" << std::endl;
        }

        return size;
    }

    static UInt32 getBinSize(const DynamicVolume *pObjectStore,
                                   UInt32         uiNumObjects)
    {
        UInt32 size = 0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const DynamicVolume       &oObject)
    {
        UInt32 type = (UInt32)(oObject.getType());

        pMem.putValue(type);

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
            {
                const BoxVolume *pBVol = 
                    dynamic_cast<const BoxVolume *>(
                        &(oObject.getInstance()));

                UInt16 state = pBVol->getState();
                
                pMem.putValue(state);

                pMem.putValues(&(pBVol->getMin()[0]), 3);
                pMem.putValues(&(pBVol->getMax()[0]), 3);

                break;
            }
            case DynamicVolume::SPHERE_VOLUME :
            {
                const SphereVolume *pSVol = 
                    dynamic_cast<const SphereVolume *>(
                        &(oObject.getInstance()));

                Real32 radius = pSVol->getRadius();

                UInt16 state = pSVol->getState();
                
                pMem.putValue(state);

                pMem.putValues(&(pSVol->getCenter()[0]), 3);
                pMem.putValue (radius);

                break;
            }

            default:
                SWARNING << "Unknown volume type in copyToBin" << std::endl;
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
        UInt32 type;
        
        pMem.getValue(type);
        DynamicVolume::Type volumeType=
            static_cast<DynamicVolume::Type>(type);
        oObject.setVolumeType(volumeType);

        switch(type)
        {
            case DynamicVolume::BOX_VOLUME : 
            {
                BoxVolume *pBVol = 
                    dynamic_cast<BoxVolume *>(&(oObject.getInstance()));

                Pnt3f min,max;
                UInt16 state;

                pMem.getValue (state       );
                pMem.getValues(&(min[0]), 3);
                pMem.getValues(&(max[0]), 3);

                pBVol->setState (state   );
                pBVol->setBounds(min, max);

                break;
            }
            case DynamicVolume::SPHERE_VOLUME :
            {
                SphereVolume *pSVol = 
                    dynamic_cast<SphereVolume *>(&(oObject.getInstance()));

                Pnt3f center;
                Real32 radius;
                UInt16 state;

                pMem.getValue(state);
                pMem.getValues(&(center[0]), 3);
                pMem.getValue (radius);

                pSVol->setState (state );
                pSVol->setCenter(center);
                pSVol->setRadius(radius);
                
                break;
            }

            default:
                SWARNING << "Unknown volume type in copyFronBin" << std::endl;
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

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<DynamicVolume> */
/*! \hideinhierarchy                              */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits1<BitVector> : 
    public FieldTraitsRecurseBase<BitVector>
{
    static DataType  _type;

    enum              { StringConvertable = 0x00                       };

    static       DataType  &getType (void)   { return _type;           }

    static const Char8     *getSName(void)   { return "SFBitVector";   }

    static const Char8     *getMName(void)   { return "MFBitVector";   }

    static       BitVector  getDefault(void) { return BitVector();     }

    static       UInt32    getBinSize(const BitVector &)
    {
        return sizeof(BitVector);
    }

    static       UInt32    getBinSize (const BitVector *,
                                             UInt32     uiNumObjects)
    {
        return sizeof(BitVector)*uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const BitVector         &oObject)
    {
        BitVector value=oObject;
        pMem.putValue(value);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const BitVector         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    BitVector         &oObject)
    {
        BitVector value;
        pMem.getValue(value);
        oObject=value;
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            BitVector         *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }

};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<BitVector> */
/*! \hideinhierarchy                          */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits1<GLenum> : 
    public FieldTraitsRecurseBase<GLenum>
{
    static  DataType                 _type;
    typedef FieldDataTraits1<GLenum>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFGLenum";          }
    static Char8    *getMName     (void) { return "MFGLenum";          }

    static GLenum    getDefault   (void) { return 0;                   }

    static bool      getFromString(      GLenum  &outVal,
                                   const Char8  *&inVal)
    {
        outVal = TypeTraits<GLenum>::getFromString(inVal);
        
        return false;
    }

    static void      putToString  (const      GLenum &inVal,
                                         std::string &outStr)
    {
        outStr.assign(TypeTraits<GLenum>::putToString(inVal));
    }

    static       UInt32    getBinSize (const GLenum &)
    {
        return sizeof(UInt32);
    }

    static       UInt32    getBinSize (const GLenum     *,
                                             UInt32     uiNumObjects)
    {
        return sizeof(UInt32)*uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const GLenum            &oObject)
    {
        pMem.putValue ((UInt32)oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const GLenum             *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    GLenum            &oObject)
    {
        UInt32 val;
        pMem.getValue (val);
        oObject = val;
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            GLenum             *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<GLenum> */
/*! \hideinhierarchy                       */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Plane> : 
    public FieldTraitsRecurseBase<Plane>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable    | 
                                           FromStringConvertable  };

    static       DataType &getType      (void) { return _type;          }

    static const Char8    *getSName     (void) { return "SFPlane";      }

    static const Char8    *getMName     (void) { return "MFPlane";      }

    static       Plane     getDefault   (void) { return Plane();        }

    static       bool      getFromString(      Plane  &,
                                         const Char8 *&)
    {
        // TO_BE_DONE
        return false;
    }

    static       void      putToString  (const      Plane  &inVal,
                                               std::string &outStr)
    {
        typedef TypeTraits<Vec3f::ValueType> TypeTrait;

        Vec3f  normal = inVal.getNormal();
        Real32 dist   = inVal.getDistanceFromOrigin();
        
        outStr.assign(TypeTrait::putToString(normal.getValues()[0]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(normal.getValues()[1]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString(normal.getValues()[2]));
        outStr.append(", ");
        outStr.append(TypeTraits<Real32>::putToString(dist));
    }

    static       UInt32    getBinSize (const Plane &)
    {
        return sizeof(UInt32) * 4;
    }

    static       UInt32    getBinSize (const Plane     *,
                                             UInt32     uiNumObjects)
    {
        return sizeof(UInt32) * 4 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Plane            &oObject)
    {
        const Vec3f &normal   = oObject.getNormal            ();
        Real32       distance = oObject.getDistanceFromOrigin();

        pMem.putValues(&normal[0], 3);
        pMem.putValue ( distance    );
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const Plane             *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Plane            &oObject)
    {
        Vec3f  normal;
        Real32 distance;

        pMem.getValues(&normal[0], 3);
        pMem.getValue ( distance    );

        oObject.set(normal, distance);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            Plane             *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Plane> */
/*! \hideinhierarchy                      */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGBASEFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_BASEFIELDDATATYPE_H_ */







