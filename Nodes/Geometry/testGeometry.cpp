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

using namespace OSG;

int main (int argc, char **argv)
{
    osgInit(argc, argv);
    
    NodePtr  p1 = Node::create();
    GeometryPtr g1 = Geometry::create();

    GeoPosition3f::getStaticType().getId();

	p1->setCore( g1 );

	cerr << "Geometry Node: " << hex << (Geometry*) g1.getCPtr() << endl;

	GeoPosition3f::PtrType pnts = GeoPosition3f::create();

	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnts->getDimension() << ", Format:" << hex << pnts->getFormat() << dec
		 << ", Stride:" << pnts->getStride() << ", Data:" << hex << (int)pnts->getData() << dec << endl;

	g1->setPositions( pnts );

	osgBeginEditCP(g1, FieldBits::AllFields);

	MFPnt3f *p = pnts->getFieldPtr();		// The p pointer is not MT-safe!!

	pnts->getFieldPtr()->addValue( Pnt3f( -1, -1, -1) );
	pnts->getFieldPtr()->addValue( Pnt3f(  1, -1, -1) );
	p->addValue( Pnt3f( -1,  1, -1) );
	p->addValue( Pnt3f(  1,  1, -1) );
	p->addValue( Pnt3f( -1, -1,  1) );
	p->addValue( Pnt3f(  1, -1,  1) );
	p->addValue( Pnt3f( -1,  1,  1) );
	p->addValue( Pnt3f(  1,  1,  1) );

	osgEndEditCP(g1, FieldBits::AllFields);
    
	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnts->getDimension() << ", Format:0x" << hex << pnts->getFormat() 
		 << dec << ", Stride:" << pnts->getStride() << ", Data:0x" << hex 
		 << (int)pnts->getData() << dec << endl;

	cerr << "Geometry Points: " << hex << g1->getPositions() << endl;
	cerr << p->size() << " Points: " << endl;

	for ( int i = 0; i < p->size(); i++ )
	{
		cerr << "Point " << i << " " << p->getValue( i ) << endl;
	}

	cerr << "Geometry Points: " << hex << g1->getPositions() << endl;
	
	// invalidate manually, automatic not yet working
	const_cast<Volume&>(p1->getVolume()).setValid( false );

	p1->updateVolume();

	Vec3f center;
	p1->getVolume().getCenter(center);

	cerr << "Volume: center " << center << ", volume "
		 << p1->getVolume().getVolume() << endl;

    return 0;
}

