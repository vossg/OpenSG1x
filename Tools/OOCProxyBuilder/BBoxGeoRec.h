// A very simple GeoReceiver that counts points and calculates the
// bounding box

#ifndef _BBOXGEOREC_H
#define _BBOXGEOREC_H

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

#include "GeoReceiver.h"

class BBoxGeoRec : public GeoReceiver
{
  public:
  
    BBoxGeoRec();
     
    void print(std::ostream &str);
   
    static void receivePnt(GeoReceiver *obj, const OSG::Pnt3f &pnt);
    static void receiveTri(GeoReceiver *obj, OSG::UInt32 i1, OSG::UInt32 i2, 
                                             OSG::UInt32 i3, OSG::UInt32 mat);
    
    const OSG::Vec3f &getLow(void);   
    const OSG::Vec3f &getHigh(void);   
          OSG::UInt32 getNPts(void);
          OSG::UInt32 getNTris(void);
    
  private:
  
    OSG::Vec3f _bblow, _bbhigh;
    OSG::UInt32 _npts, _ntris;
};


#endif
