// GeoReceiver: a little pseudo/wrapper class to abstract objects that can 
// accept vertices/faces

#ifndef _GEORECEIVER_H
#define _GEORECEIVER_H

#include <ostream>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

class GeoReceiver
{
  public:
    
    typedef void (*pntRec)(GeoReceiver *obj, const OSG::Pnt3f &pnt);
    typedef void (*triRec)(GeoReceiver *obj, OSG::UInt32 i1, OSG::UInt32 i2, 
                                             OSG::UInt32 i3, OSG::UInt32 mat);
 
    virtual void print(std::ostream &str) = 0;
    
};

inline std::ostream &operator<<(std::ostream &str, GeoReceiver& obj)
{
    (&obj)->print(str);
    return str;
}

#endif
