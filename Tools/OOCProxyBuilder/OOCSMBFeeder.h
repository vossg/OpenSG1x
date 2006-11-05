// OOC SMB data feeder

#ifndef _OOCSMBFEEDER_H
#define _OOCSMBFEEDER_H

#include <string>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>

#include "OOCFeeder.h"

class OOCSMBFeeder : public OOCFeeder
{
  public:
    
    OOCSMBFeeder(char *filenames[], int nf);
    ~OOCSMBFeeder();
    
    virtual void feedBoth(GeoReceiver *rec,   GeoReceiver::pntRec pfunc, 
                                              GeoReceiver::triRec tfunc);
  
    virtual void calcBasics(void);
  
  private:

};

#endif
