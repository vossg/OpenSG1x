#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

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
    osgInit(argc, argv);
    
    NodePtr  p1 = Node::create();
    GeometryPtr g1 = Geometry::create();

    GeoPosition3f::getClassType();

	p1->setCore( g1 );

	cerr << "Geometry Node: " << hex << (Geometry*) g1.getCPtr() << endl;

	GeoPosition3f::PtrType pnts = GeoPosition3f::create();
	GeoPositionPtr pnt = pnts;

	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnts->getDimension() << ", Format:" 
		 << hex << pnts->getFormat() << dec
		 << ", Stride:" << pnts->getStride() << ", Data:" 
		 << hex << (int)pnts->getData() << dec 
		 << ", Size " << (int)pnts->getSize()
		 << endl;

	g1->setPositions( pnts );

	beginEditCP(g1, FieldBits::AllFields);

	MFPnt3f *p = pnts->getFieldPtr();		// The p pointer is not MT-safe!!
	// generic access
	pnts->addValue( Pnt3f( -1, -1, -1) );
	// via the property
	pnts->getFieldPtr()->addValue( Pnt3f(  1, -1, -1) );
	// via the field
	p->addValue( Pnt3f( -1,  1, -1) );
	p->addValue( Pnt3f(  1,  1, -1) );
	p->addValue( Pnt3f( -2, -1,  1) );
	p->addValue( Pnt3f(  1, -1,  1) );
	p->addValue( Pnt3f( -2,  1,  1) );
	p->addValue( Pnt3f(  1,  1,  1) );

	endEditCP(g1, FieldBits::AllFields);
    
	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnts->getDimension() << ", Format:" 
		 << hex << pnts->getFormat() << dec
		 << ", Stride:" << pnts->getStride() << ", Data:" 
		 << hex << (int)pnts->getData() << dec 
		 << ", Size " << (int)pnts->getSize()
		 << endl;

	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnt->getDimension() << ", Format:" 
		 << hex << pnt->getFormat() << dec
		 << ", Stride:" << pnt->getStride() << ", Data:" 
		 << hex << (int)pnt->getData() << dec 
		 << ", Size " << (int)pnt->getSize()
		 << endl;

	cerr << "Geometry Points: " << hex << g1->getPositions() << endl;
	cerr << p->size() << " Points: " << endl;

	for ( int i = 0; i < p->size(); i++ )
	{
		cerr << "Point " << i << " " << p->getValue( i ) << endl;
	}

	cerr << "Generic Access" << endl;
	cerr << pnts->getSize() << " Points: " << endl;
	for ( int i = 0; i < pnts->getSize(); i++ )
	{
		Pnt3f pp;
		pnts->getValue(pp,i);
		cerr << "Point " << i << " " << pnts->getValue(i) << " " << pp << endl;
	}

	cerr << "Geometry Points: " << hex << g1->getPositions() << endl;

    Pnt3f mean = calcMean(*p);

    cerr << "Mean " << mean << endl;

	p1->updateVolume();

	Vec3f center;
	p1->getVolume().getCenter(center);

	cerr << "Volume: center " << center << ", volume "
		 << p1->getVolume().getScalarVolume() << endl;

    return 0;
}

