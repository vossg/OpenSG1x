
#include <OpenSG/OSGBaseFunctions.h>

#include "BBoxGeoRec.h"

OSG_USING_NAMESPACE

BBoxGeoRec::BBoxGeoRec()
{
    _bblow.setValues(1e10,1e10,1e10);
    _bbhigh.setValues(-1e10,-1e10,-1e10);
    _npts = 0;
    _ntris = 0;
}

void BBoxGeoRec::print(std::ostream &str)
{
    str << "BBoxGeoRec: " << _npts << " points/" << _ntris 
        << "tris gave (" << _bblow << ")-("
        << _bbhigh << ") box";
}

void BBoxGeoRec::receivePnt(GeoReceiver *obj, const Pnt3f &pnt)
{
    BBoxGeoRec *me = reinterpret_cast<BBoxGeoRec *>(obj);

    me->_npts++;

    me->_bblow[0]  = osgMin(me->_bblow[0],  pnt[0]);
    me->_bblow[1]  = osgMin(me->_bblow[1],  pnt[1]);
    me->_bblow[2]  = osgMin(me->_bblow[2],  pnt[2]);
    me->_bbhigh[0] = osgMax(me->_bbhigh[0], pnt[0]);
    me->_bbhigh[1] = osgMax(me->_bbhigh[1], pnt[1]);
    me->_bbhigh[2] = osgMax(me->_bbhigh[2], pnt[2]);
}

void BBoxGeoRec::receiveTri(GeoReceiver *obj, OSG::UInt32 i1, OSG::UInt32 i2, 
                                              OSG::UInt32 i3, OSG::UInt32 mat)
{
    BBoxGeoRec *me = reinterpret_cast<BBoxGeoRec *>(obj);

    me->_ntris++;
}

const Vec3f &BBoxGeoRec::getLow(void)
{
    return _bblow;
}

const Vec3f &BBoxGeoRec::getHigh(void)
{
    return _bbhigh;
}

UInt32 BBoxGeoRec::getNPts(void)
{
    return _npts;
}

UInt32 BBoxGeoRec::getNTris(void)
{
    return _ntris;
}
