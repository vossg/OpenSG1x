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
#include <OSGString.h>

#include <string>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief  base field traits 
 */

template <>
struct FieldDataTraits<Color3f> : public FieldTraitsRecurseBase<Color3f>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static DataType         &getType (void)      { return _type;          }

    static Char8            *getSName(void)      { return "SFColor3f";    }

    static Char8            *getMName(void)      { return "MFColor3f";    }

    static Color3f           getDefault(void)    { return Color3f();      }

    static Bool              getFromString(      Color3f  &outVal,
                                           const Char8    *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void             putToString(const Color3f &inVal,
                                              std::string &outVal)
    {
        typedef TypeConstants<Color3f::ValueType> TypeConst;

        outVal.assign(TypeConst::putToString(inVal.red()));
        outVal.append(" ");
        outVal.append(TypeConst::putToString(inVal.green()));
        outVal.append(" ");
        outVal.append(TypeConst::putToString(inVal.blue()));
    }
};

template <>
struct FieldDataTraits<Color4f> : public FieldTraitsRecurseBase<Color4f>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static DataType         &getType (void)      { return _type;          }

    static Char8            *getSName(void)      { return "SFColor4f";    }

    static Char8            *getMName(void)      { return "MFColor4f";    }

    static Color4f           getDefault(void)    { return Color4f();      }
 
    static Bool              getFromString(      Color4f  &outVal,
                                           const Char8   *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void             putToString(const Color4f &inVal,
                                              std::string  &outVal)
    {
        outVal.assign( TypeConstants<Color4f::ValueType>::putToString(inVal.red()) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Color4f::ValueType>::putToString(inVal.green()) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Color4f::ValueType>::putToString(inVal.blue()) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Color4f::ValueType>::putToString(inVal.alpha()) );
    }
};

template <>
struct FieldDataTraits<Color3ub> : public FieldTraitsRecurseBase<Color3ub>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };

    static DataType &getType      (void)   { return _type;          }

    static Char8    *getSName     (void)   { return "SFColor3ub"; }
    static Char8    *getMName     (void)   { return "MFColor3ub"; }

    static Color3ub  getDefault   (void) { return Color3ub();   }

    static Bool      getFromString(      Color3ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Color3ub &inVal,
                                    std::string &outVal)
    {
       outVal.assign( TypeConstants<Color3ub::ValueType>::putToString(inVal.red()) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Color3ub::ValueType>::putToString(inVal.green()) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Color3ub::ValueType>::putToString(inVal.blue()) );
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Color4ub field traits 
 */

template <>
struct FieldDataTraits<Color4ub> : public FieldTraitsRecurseBase<Color4ub>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };

    static DataType &getType (void)      { return _type;           }

    static Char8    *getSName     (void) { return "SFColor4ub";    }

    static Char8    *getMName     (void) { return "MFColor4ub";    }

    static Color4ub  getDefault   (void) { return Color4ub();      }

    static Bool      getFromString(      Color4ub  &outVal,
                                const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Color4ub &inVal,
                                    std::string &outVal )
    {
        outVal.assign( TypeConstants<Color4ub::ValueType>::putToString(
                        inVal.red()) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Color4ub::ValueType>::putToString(
                        inVal.green()) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Color4ub::ValueType>::putToString(
                        inVal.blue()) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Color4ub::ValueType>::putToString(
                        inVal.alpha()) );
    }
};


template <>
struct FieldDataTraits<String> : public FieldTraitsRecurseBase<String>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static DataType         &getType (void)      { return _type;         }

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

    static void             putToString(const String &inVal,
                                              std::string &outVal )
    {
        outVal.assign( "\"" );
        outVal.append( inVal.str() );
        outVal.append( "\"" );
    }

    static UInt32 getBinSize(const String   &oObject)
    {
        return oObject.length() + 1 + sizeof(UInt32);
    }

    static UInt32 getBinSize(const String     *pObjectStore,
                                   UInt32      uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore,uiNumObjects);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const String              &oObject)
    {
        UInt32 size = 0;
        if(oObject.empty())
        {
            pMem.put(&size        , sizeof(size));
        }
        else
        {
            size = oObject.length() + 1;
            pMem.put(&size        , sizeof(size));
            pMem.put(oObject.str(), size);
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const String            *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            String            &oObject)
    {
        UInt32 size;
        Char8 *str;

        pMem.get(&size, sizeof(size));
        if(size==0)
        {
            oObject.set(NULL);
        }
        else
        {
            // we have to copy because the string maight not be
            // continous in pMem.
            str = new Char8[size];
            pMem.get(str,size);
            oObject.set(str);
            delete [] str;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            String            *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

template <>
struct FieldDataTraits1<Time> : public FieldTraitsRecurseBase<Time>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable };

    static DataType         &getType (void)      { return _type;         }

    static Char8            *getSName(void)      { return "SFTime";      }

    static Char8            *getMName(void)      { return "MFTime";      }

    static Time              getDefault(void)    { return Time();        }

    static Bool              getFromString(      Time   &outVal,
                                           const Char8 *&inVal)
    {
        outVal = TypeConstants<Time>::getFromString(inVal);

        return true;
    }

    static void             putToString(const Time &inVal,
                                              std::string &outVal)
    {
        outVal.assign( TypeConstants<Real64>::putToString( inVal ) );
    }
};

template <>
struct FieldDataTraits<DynamicVolume> : 
    public FieldTraitsRecurseBase<DynamicVolume>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable     };

    static DataType         &getType (void)      { return _type;             }

    static Char8            *getSName(void)      { return "SFDynamicVolume"; }

    static Char8            *getMName(void)      { return "MFDynamicVolume"; }

    static DynamicVolume     getDefault(void)    { return DynamicVolume();   }

    static Bool             getFromString(      DynamicVolume  &outVal,
                                          const Char8         *&inVal)
    {
        Real32 valStore[6];
        UInt32 length = strlen( inVal );
        Char8 str[256];
        Char8 *c = str;
    
        if( length > 256 )
        {
            cerr << "FieldDataTraits<DynamicVolume>::getFromString(): "
                 << "Input too long" << endl;
            return false;
        }
        strncpy( str, inVal, length );
        while( *c != '\0' )
        {
            if( *c == '[' )
                *c = ' ';
            if( *c == ']' )
                *c = ' ';
            if( *c == ',' )
                *c = ' ';
            c++;
        }
        
        Int16 count = sscanf( str, "%f %f %f %f %f %f",
                            &valStore[0], &valStore[1], &valStore[2],
                            &valStore[3], &valStore[4], &valStore[5] );
        
        if( count == 4 )
        {
            outVal.setVolumeType( DynamicVolume::SPHERE_VOLUME );
            SphereVolume &sVol = dynamic_cast<SphereVolume&>(
                                            outVal.getInstance() );
            sVol.setCenter( Pnt3f(valStore[0], valStore[1], valStore[2]) );
            sVol.setRadius( valStore[3] );
            return true;
        }
        else if( count == 6 )
        {
            outVal.setVolumeType( DynamicVolume::BOX_VOLUME );
            BoxVolume &bVol = dynamic_cast<BoxVolume&>( outVal.getInstance() );
            bVol.setBounds( valStore[0], valStore[1], valStore[2],
                            valStore[3], valStore[4], valStore[5] );
            return true;
        }
        else
        {
            outVal.setVolumeType( DynamicVolume::BOX_VOLUME );
            BoxVolume &bVol = dynamic_cast<BoxVolume&>( outVal.getInstance() );
            bVol.setBounds( 0,0,0, 0,0,0 );
            return false;
        }
    }

    static void             putToString(const DynamicVolume &inVal,
                                              std::string   &outVal)
    {
        
        Pnt3f min, max;
        
        outVal.assign( "[ " );
        switch( inVal.getType() )
        {
        case DynamicVolume::BOX_VOLUME : 
            inVal.getBounds( min, max );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    min.getValues()[0]) );
            outVal.append( " " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    min.getValues()[1]) );
            outVal.append( " " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    min.getValues()[2]) );
            outVal.append( ", " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    max.getValues()[0]) );
            outVal.append( " " );
            outVal.append(TypeConstants<Pnt3f::ValueType>::putToString(
                                                    max.getValues()[1]) );
            outVal.append( " " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    max.getValues()[2]) );
            break;
        case DynamicVolume::SPHERE_VOLUME :
            const SphereVolume &sVol = dynamic_cast<const SphereVolume&>(
                                                inVal.getInstance());
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    sVol.getCenter()[0]) );
            outVal.append( " " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    sVol.getCenter()[1]) );
            outVal.append( " " );
            outVal.append( TypeConstants<Pnt3f::ValueType>::putToString(
                                                    sVol.getCenter()[2]) );
            outVal.append( ", " );
            outVal.append( TypeConstants<Real32>::putToString(
                                                    sVol.getRadius()) );
            break;
        }
        outVal.append( " ]" );
                    
    }
};

template <>
struct FieldDataTraits1<BitVector> : public FieldTraitsRecurseBase<BitVector>
{
    static DataType         _type;

    enum                     { StringConvertable = 0x00 };

    static DataType         &getType (void)      { return _type;          }

    static Char8            *getSName(void)      { return "SFBitVector";   }

    static Char8            *getMName(void)      { return "MFBitVector";   }

    static BitVector         getDefault(void)    { return BitVector();     }
};


template <>
struct FieldDataTraits<Plane> : public FieldTraitsRecurseBase<Plane>
{
    static DataType         _type;

    enum                     { StringConvertable = ToStringConvertable | 
                                                   FromStringConvertable  };

    static DataType         &getType (void)      { return _type;          }

    static Char8            *getSName(void)      { return "SFPlane";      }

    static Char8            *getMName(void)      { return "MFPlane";      }

    static Plane     getDefault(void)    { return Plane(); }

    static Bool             getFromString(      Plane  &,
                                          const Char8         *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const Plane &inVal,
                                              std::string &outVal)
    {
        Vec3f normal = inVal.getNormal();
        Real32 dist = inVal.getDistanceFromOrigin();
        outVal.assign( TypeConstants<Vec3f::ValueType>::putToString( normal.getValues()[0]) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Vec3f::ValueType>::putToString( normal.getValues()[1]) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Vec3f::ValueType>::putToString( normal.getValues()[2]) );
        outVal.append( "  " );
        outVal.append( TypeConstants<Real32>::putToString(dist) );
    }
};


OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */
