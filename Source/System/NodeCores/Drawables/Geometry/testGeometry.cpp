#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include "OSGGeometry.h"
#include "OSGGeoProperty.h"

using namespace OSG;

OSG::Pnt3f calcMean(const MFPnt3f &mfIn)
{
    typedef Pnt3f PointInterfaceT;

    PointInterfaceT returnValue;

    if(mfIn.size() == 0)
        return returnValue;

    for(Int32 i = 0; i < mfIn.size(); i++)
    {
        for(Int32 j = 0; j < PointInterfaceT::_iSize; j++)
        {
            returnValue[j] += mfIn[i][j];
        }
    }

    returnValue /= mfIn.size();

    return returnValue;
}

int main (int argc, char **argv)
{
    UInt32 i;
    osgInit(argc, argv);
    
    NodePtr  p1 = Node::create();
    GeometryPtr g1 = Geometry::create();

    GeoPositions3f::getClassType();

    p1->setCore( g1 );

    std::cerr << "Geometry Node: " << std::hex << (Geometry*) g1.getCPtr() << std::endl;

    GeoPositions3f::PtrType pnts = GeoPositions3f::create();
    GeoPositionsPtr pnt = pnts;

    std::cerr << "Positions: " << std::endl;
    std::cerr << "Dim:" << pnts->getDimension() << ", Format:" 
         << std::hex << pnts->getFormat() << std::dec
         << ", Stride:" << pnts->getStride() << ", Data:" 
         << std::hex << pnts->getData() << std::dec 
         << ", getSize " << pnts->getSize()
         << ", size " << pnts->size()
         << std::endl;

    g1->setPositions( pnts );

    beginEditCP(g1, FieldBits::AllFields);

    MFPnt3f *p = pnts->getFieldPtr();       // The p pointer is not MT-safe!!
    // generic access
    pnts->push_back( Pnt3f( -1, -1, -1) );
    // via the property
    pnts->getFieldPtr()->push_back( Pnt3f(  1, -1, -1) );
    // via the field
    p->push_back( Pnt3f( -1,  1, -1) );
    p->push_back( Pnt3f(  1,  1, -1) );
    p->push_back( Pnt3f( -2, -1,  1) );
    p->push_back( Pnt3f(  1, -1,  1) );
    p->push_back( Pnt3f( -2,  1,  1) );
    p->push_back( Pnt3f(  1,  1,  1) );

    endEditCP(g1, FieldBits::AllFields);
    
    std::cerr << "Positions: " << std::endl;
    std::cerr << "Dim:" << pnts->getDimension() << ", Format:" 
         << std::hex << pnts->getFormat() << std::dec
         << ", Stride:" << pnts->getStride() << ", Data:" 
         << std::hex << pnts->getData() << std::dec 
         << ", Size " << pnts->getSize()
         << ", size " << pnts->size()
         << std::endl;

    pnts->resize(10);

    std::cerr << "Geometry Points: " << std::hex << g1->getPositions() << std::endl;
    std::cerr << p->size() << " Points: " << std::endl;

    for(i = 0; i < p->size(); i++ )
    {
        std::cerr << "Point " << i << " " << (*p)[i] << std::endl;
    }

    std::cerr << "Generic Access" << std::endl;
    std::cerr << pnts->getSize() << " Points: " << std::endl;
    for(i = 0; i < pnts->getSize(); i++ )
    {
        Pnt3f pp;
        pnts->getValue(pp,i);
        std::cerr << "Point " << i << " " << pnts->getValue(i) << " " << pp << std::endl;
    }

    std::cerr << "Geometry Points: " << std::hex << g1->getPositions() << std::endl;

    Pnt3f mean = calcMean(*p);

    std::cerr << "Mean " << mean << std::endl;

    p1->updateVolume();

    Vec3f center;
    p1->getVolume().getCenter(center);

    std::cerr << "Volume: center " << center << ", volume "
         << p1->getVolume().getScalarVolume() << std::endl;

    return 0;
}

