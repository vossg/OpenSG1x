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
    
    OSGNodePtr  p1 = OSGNode::create();
    OSGGeometryPtr g1 = OSGGeometry::create();

    OSGGeoPosition3f::getStaticType().getId();

	p1->setCore( g1 );

	cerr << "Geometry Node: " << hex << (OSGGeometry*) g1 << endl;

	OSGGeoPosition3f::OSGPtrType pnts = OSGGeoPosition3f::create();

	cerr << "Positions: " << endl;
	cerr << "Dim:" << pnts->getDimension() << ", Format:" << hex << pnts->getFormat() << dec
		 << ", Stride:" << pnts->getStride() << ", Data:" << hex << (int)pnts->getData() << dec << endl;

	g1->setPositions( pnts );

	osgBeginEditCP(g1, OSGFieldBits::OSGAllFields);

	OSGMFPnt3f *p = pnts->getFieldPtr();		// The p pointer is not MT-safe!!

	pnts->getFieldPtr()->addValue( OSGPnt3f( -1, -1, -1) );
	pnts->getFieldPtr()->addValue( OSGPnt3f(  1, -1, -1) );
	p->addValue( OSGPnt3f( -1,  1, -1) );
	p->addValue( OSGPnt3f(  1,  1, -1) );
	p->addValue( OSGPnt3f( -1, -1,  1) );
	p->addValue( OSGPnt3f(  1, -1,  1) );
	p->addValue( OSGPnt3f( -1,  1,  1) );
	p->addValue( OSGPnt3f(  1,  1,  1) );

	osgEndEditCP(g1, OSGFieldBits::OSGAllFields);
    
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
	const_cast<OSGVolume&>(p1->getVolume()).setValid( false );

	p1->updateVolume();

	OSGVec3f center;
	p1->getVolume().getCenter(center);

	cerr << "Volume: center " << center << ", volume "
		 << p1->getVolume().getVolume() << endl;

    return 0;
}

