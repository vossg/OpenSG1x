/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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


#ifndef _OSGNEWFIELDTYPE_H_
#define _OSGNEWFIELDTYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFieldType.h>

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

OSG_BEGIN_NAMESPACE

// This files demonstrates how to create a new Field type, to support the
// integration of user-defined types into OpenSG FieldContainers.
//
// Classes/Types that are to be used in Field have to have some special
// capabilities, which not every class has be default.
//
// Field values need to be able to convert themselves into strings and
// to read themselves from strings. They also need to be able to transform
// themselevs into a binary stream and read themselves from a binary stream.

// Let's define a simple class that should be used in a Field

class TripleInt
{
    public:
    
        TripleInt(UInt32 i1 = 0, UInt32 i2 = 0, UInt32 i3 = 0)
        {
            _values[0] = i1;
            _values[1] = i2;
            _values[2] = i3;           
        }
        
        virtual ~TripleInt()
        {
        }
        
        UInt32 getValue(UInt16 ind) const
        {
            return _values[ind]; 
        }
         
        void setValue(UInt16 ind, UInt32 val)
        {
            _values[ind] = val;
        }
        
    private:
    
    	// This is not strictly necessary and just for illustration
    	// You could just as well do the internal access in this class and 
    	// supply methods to the FieldDataTraits<>
    	friend struct FieldDataTraits<TripleInt>;
    	
        UInt32 _values[3]; 
};

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldDataTraits<TripleInt> : 
    public FieldTraitsRecurseBase<TripleInt>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFTripleInt"; }
    static Char8          *getMName     (void) { return "MFTripleInt"; }

    // Create a default instance of the class, needed for Field creation
    static TripleInt       getDefault   (void) { return TripleInt();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const TripleInt   &inVal,
                                  std::string &outVal)
    {
        // we can use the TypeTraits to do the conversion for the base types
        typedef TypeTraits<UInt32> tt;
        
        outVal.assign("\"");
        outVal.append(tt::putToString(inVal.getValue(0)));
        outVal.append(",");
        outVal.append(tt::putToString(inVal.getValue(1)));
        outVal.append(",");
        outVal.append(tt::putToString(inVal.getValue(2)));        
        outVal.append("\"");
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      TripleInt  &outVal,
                              const Char8     *&inVal)
    {
        UInt32 i1 = 0, i2 = 0, i3 = 0;
        
        if(sscanf(inVal,"\"%d,%d,%d\"", &i1, &i2, &i3) != 3)
        	return false;
        
        outVal.setValue(0, i1);
        outVal.setValue(1, i2);
        outVal.setValue(2, i3);
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const TripleInt &)
    {
        return sizeof(UInt32) * 3;
    }

    static UInt32 getBinSize (const TripleInt *, UInt32 num)
    {
        return sizeof(UInt32)* 3 * num;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const TripleInt         &obj)
    {
    	// Put a single value at a time
        bdh.putValue(obj.getValue(0));
        bdh.putValue(obj.getValue(1));
        bdh.putValue(obj.getValue(2));
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const TripleInt         *objs,
                                UInt32             num)
    {
    	// Put a set of values
    	for(UInt32 i = 0; i < num; ++i)
        	bdh.putValues(objs[i]._values, 3);
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            TripleInt         &obj)
    {
        UInt32 i1,i2,i3;
        // Get a single value at a time
        bdh.getValue(i1);   
        obj.setValue(0, i1);
        bdh.getValue(i2);   
        obj.setValue(1, i2);
        bdh.getValue(i3);   
        obj.setValue(2, i3);
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            TripleInt         *objs,
                            UInt32             num)
    {
    	// Get a set of values
    	for(UInt32 i = 0; i < num; ++i)
        	bdh.getValues(objs[i]._values, 3);
    }
};

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<TripleInt> SFTripleInt;
typedef MField<TripleInt> MFTripleInt;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILETRIPLEINTINST

// Declare the functions/classes/methods Windows needs
//OSG_DLLEXPORT_DECL1(SField, TripleInt, )
//OSG_DLLEXPORT_DECL1(MField, TripleInt, )

#endif


OSG_END_NAMESPACE

#define OSGNEWFIELDTYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGNEWFIELDTYPE_H_ */
