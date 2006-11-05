// OOC PLY data feeder

#ifndef _OOCPLYFEEDER_H
#define _OOCPLYFEEDER_H

#include <string>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>

#include "OOCFeeder.h"

class OOCPLYFeeder : public OOCFeeder
{
  public:
    
    OOCPLYFeeder(char *filenames[], int nf);
    ~OOCPLYFeeder();
    
    virtual void feedBoth(GeoReceiver *rec,   GeoReceiver::pntRec pfunc, 
                                              GeoReceiver::triRec tfunc);
  
  private:

};

#endif
