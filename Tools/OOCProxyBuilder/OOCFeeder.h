// OOC data feeder base class

#ifndef _OOCFEEDER_H
#define _OOCFEEDER_H

#include <string>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>

#include "GeoReceiver.h"

class OOCFeeder
{
  public:
    
    OOCFeeder(char *filename[], int nf);
    ~OOCFeeder();
  
    virtual void calcBasics(void); // Calc npnts, ntris, bbox
    
    virtual void feedPoints(GeoReceiver *rec, GeoReceiver::pntRec pfunc);
    virtual void feedTris(GeoReceiver *rec,   GeoReceiver::triRec tfunc);
    virtual void feedBoth(GeoReceiver *rec,   GeoReceiver::pntRec pfunc, 
                                              GeoReceiver::triRec tfunc) = 0;
    
    OSG::UInt32 getNPoints(void);
    OSG::UInt32 getNTris(void);
    OSG::Vec3f& getBBMin(void);
    OSG::Vec3f& getBBMax(void);
    
  protected:
 
    // Definition data
    std::vector<std::string> _filenames;
    
    // Basic data    
    OSG::UInt32 _npts, _ntris;
    OSG::Vec3f  _bbmin, _bbmax;
};

#endif
