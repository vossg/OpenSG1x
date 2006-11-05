// OOC OSG data feeder

#ifndef _OOCOSGFEEDER_H
#define _OOCOSGFEEDER_H

#include <string>
#include <map>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGGeometry.h>

#include "OOCFeeder.h"

class OOCOSGFeeder : public OOCFeeder
{
  public:
    
    OOCOSGFeeder(OSG::NodePtr root);
    OOCOSGFeeder(char *filename[], int nf);
    ~OOCOSGFeeder();
    
    virtual void feedBoth(GeoReceiver *rec,   GeoReceiver::pntRec pfunc, 
                                              GeoReceiver::triRec tfunc);
  
  private:

    // Feeder for a single in-mem graph
    OSG::NodePtr _root;

    // Traversal helpers
    OSG::Action::ResultE enter(OSG::NodePtr& node);

    std::map<OSG::GeoPositionsPtr, OSG::UInt32> _poss;
    OSG::UInt32 _pntindexbase;
    OSG::UInt32 _pntprog, _triprog;
    OSG::Real32 _nextpntprog, _nexttriprog;
    
    GeoReceiver *_rec;
    GeoReceiver::pntRec _pfunc;
    GeoReceiver::triRec _tfunc;
};

#endif
