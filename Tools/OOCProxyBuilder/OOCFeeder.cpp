

#include <fstream>
#include <math.h>
#include <strings.h>

#include "OOCFeeder.h"
#include "BBoxGeoRec.h"

#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGZStream.h>

OSG_USING_NAMESPACE;


OOCFeeder::OOCFeeder(char *filename[], int nf) :
    _npts(0),
    _ntris(0),
    _bbmin(),
    _bbmax()
{
    _filenames.clear();
    
    for(int i = 0; i < nf; ++i)
        _filenames.push_back(filename[i]);
}

OOCFeeder::~OOCFeeder()
{
}


// Convenience feeder functions

void OOCFeeder::feedPoints(GeoReceiver *rec, GeoReceiver::pntRec func)
{
    feedBoth(rec, func, NULL);
}

void OOCFeeder::feedTris(GeoReceiver *rec, GeoReceiver::triRec func)
{
    feedBoth(rec, NULL, func);
}

// Access

OSG::UInt32 OOCFeeder::getNPoints(void)
{
    return _npts;
}

OSG::UInt32 OOCFeeder::getNTris(void)
{
    return _ntris;
}

OSG::Vec3f& OOCFeeder::getBBMin(void)
{
    return _bbmin;
}

OSG::Vec3f& OOCFeeder::getBBMax(void)
{
    return _bbmax;
}

void OOCFeeder::calcBasics(void)
{
    BBoxGeoRec bb;
    
    feedBoth(&bb, &BBoxGeoRec::receivePnt, &BBoxGeoRec::receiveTri);
    _bbmin = bb.getLow();
    _bbmax = bb.getHigh();
    _npts  = bb.getNPts();   
    _ntris = bb.getNTris();   
}
