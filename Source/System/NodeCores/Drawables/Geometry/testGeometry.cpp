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
#include <OSGLog.h>
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

// try to create instances of all property types, to make sure they all work
// on Windows (MS compiler is pretty braindead about this) :((

#define DOTEST(name, etype)\
{\
    UInt16 i;\
    \
    FLOG(("Type:%s\n", #name));\
    \
    FLOG(("static ClassType: %s\n", name##::getClassType().getCName() ));\
   \
    name##::PtrType p = name::create();\
    FLOG(("dynamic ClassType: %s\n", p->getType().getCName() ));\
    \
    SLOG << "Resize...";\
    p->resize(32);\
    MF##etype *f = p->getFieldPtr();\
    PLOG << "FieldPtr push_back...";\
    for(i = 0; i < 128; ++i)\
    {\
		f->push_back( etype() );\
	}\
    PLOG << "Property push_back" << endLog;\
    for(i = 0; i < 128; ++i)\
    {\
		p->getField().push_back( etype() );\
	}\
	SLOG << "Dim:" << p->getDimension() << " Format: " << p->getFormat() \
		 << " FormatSize: " << p->getFormatSize() \
	     << " Stride:" << p->getStride() << " Size: " << p->getSize() << "," << p->size() \
	     << " Data:" << p->getData() << endLog; \
	name##::GenericType g;\
	SLOG << "Generic getValue...";\
	g = p->getValue(0);\
	PLOG << "Generic getValueTo...";\
	p->getValue(g, 0);\
	PLOG << "Generic setValue...";\
	p->setValue(g, 0);\
	PLOG << "Generic addValue" << endLog;\
	p->addValue(g);\
	SLOG << "Clone" << endLog;\
	name##Ptr q = name##Ptr::dcast(p->clone());\
	if(q == NullFC)\
		SLOG << "DCast failed" << endLog;\
	SLOG << "Clear" << endLog;\
	p->clear();\
	SLOG << "Destruct" << endLog;\
	subRefCP(p);\
	subRefCP(q);\
}

void testTypes(void)
{
	SLOG << "Testing type completeness" << endLog;
	DOTEST(GeoPTypesUI8,    UInt8   );
	DOTEST(GeoPLengthsUI32, UInt32  );
	DOTEST(GeoPLengthsUI16, UInt16  );
	DOTEST(GeoPLengthsUI8,  UInt8   );
	DOTEST(GeoIndicesUI32,  UInt32  );
	DOTEST(GeoIndicesUI16,  UInt16  );
	DOTEST(GeoPositions2s,  Pnt2s   );
	DOTEST(GeoPositions3s,  Pnt3s   );
	DOTEST(GeoPositions4s,  Pnt4s   );
	DOTEST(GeoPositions2f,  Pnt2f   );
	DOTEST(GeoPositions3f,  Pnt3f   );
	DOTEST(GeoPositions4f,  Pnt4f   );
	DOTEST(GeoPositions2d,  Pnt2d   );
	DOTEST(GeoPositions3d,  Pnt3d   );
	DOTEST(GeoPositions4d,  Pnt4d   );
	DOTEST(GeoTexCoords1f,  Real32  );
	DOTEST(GeoTexCoords2f,  Vec2f   );
	DOTEST(GeoTexCoords3f,  Vec3f   );
	DOTEST(GeoTexCoords4f,  Vec4f   );
	DOTEST(GeoTexCoords1d,  Real64  );
	DOTEST(GeoTexCoords2d,  Vec2d   );
	DOTEST(GeoTexCoords3d,  Vec3d   );
	DOTEST(GeoTexCoords4d,  Vec4d   );
	DOTEST(GeoNormals3f,    Vec3f   );
	DOTEST(GeoNormals3s,    Vec3s   );
	DOTEST(GeoColors3ub,    Color3ub);
	DOTEST(GeoColors4ub,    Color4ub);
	DOTEST(GeoColors3f,     Color3f );
	DOTEST(GeoColors4f,     Color4f );
	SLOG << "Types done" << endLog;
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
 //        << std::hex << pnts->getData() << std::dec 
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

	testTypes();
	
	osgExit();
	
    return 0;
}

