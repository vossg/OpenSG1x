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

    for(size_t i = 0; i < mfIn.size(); i++)
    {
        for(Int32 j = 0; j < PointInterfaceT::_iSize; j++)
        {
            returnValue[j] += mfIn[i][j];
        }
    }

    returnValue /= Real32(mfIn.size());

    return returnValue;
}

// try to create instances of all property types, to make sure they all work
// on Windows (MS compiler is pretty braindead about this) :((

#define DOTEST(name, etype, classtype, ptrtype, generictype)\
{\
    UInt16 i;\
    \
    FLOG(("Type:%s\n", #name));\
    \
    FLOG(("static ClassType: %s\n", classtype.getCName() ));\
   \
    ptrtype p = name::create();\
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
	generictype g;\
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
	DOTEST(GeoPTypesUI8,    UInt8   , GeoPTypesUI8::getClassType(), GeoPTypesUI8::PtrType, GeoPTypesUI8::GenericType);
	DOTEST(GeoPLengthsUI32, UInt32  , GeoPLengthsUI32::getClassType(), GeoPLengthsUI32::PtrType, GeoPLengthsUI32::GenericType);
	DOTEST(GeoPLengthsUI16, UInt16  , GeoPLengthsUI16::getClassType(), GeoPLengthsUI16::PtrType, GeoPLengthsUI16::GenericType);
	DOTEST(GeoPLengthsUI8,  UInt8   , GeoPLengthsUI8::getClassType(), GeoPLengthsUI8::PtrType, GeoPLengthsUI8::GenericType);
	DOTEST(GeoIndicesUI32,  UInt32  , GeoIndicesUI32::getClassType(), GeoIndicesUI32::PtrType, GeoIndicesUI32::GenericType);
	DOTEST(GeoIndicesUI16,  UInt16  , GeoIndicesUI16::getClassType(), GeoIndicesUI16::PtrType, GeoIndicesUI16::GenericType);
	DOTEST(GeoPositions2s,  Pnt2s   , GeoPositions2s::getClassType(), GeoPositions2s::PtrType, GeoPositions2s::GenericType);
	DOTEST(GeoPositions3s,  Pnt3s   , GeoPositions3s::getClassType(), GeoPositions3s::PtrType, GeoPositions3s::GenericType);
	DOTEST(GeoPositions4s,  Pnt4s   , GeoPositions4s::getClassType(), GeoPositions4s::PtrType, GeoPositions4s::GenericType);
	DOTEST(GeoPositions2f,  Pnt2f   , GeoPositions2f::getClassType(), GeoPositions2f::PtrType, GeoPositions2f::GenericType);
	DOTEST(GeoPositions3f,  Pnt3f   , GeoPositions3f::getClassType(), GeoPositions3f::PtrType, GeoPositions3f::GenericType);
	DOTEST(GeoPositions4f,  Pnt4f   , GeoPositions4f::getClassType(), GeoPositions4f::PtrType, GeoPositions4f::GenericType);
	DOTEST(GeoPositions2d,  Pnt2d   , GeoPositions2d::getClassType(), GeoPositions2d::PtrType, GeoPositions2d::GenericType);
	DOTEST(GeoPositions3d,  Pnt3d   , GeoPositions3d::getClassType(), GeoPositions3d::PtrType, GeoPositions3d::GenericType);
	DOTEST(GeoPositions4d,  Pnt4d   , GeoPositions4d::getClassType(), GeoPositions4d::PtrType, GeoPositions4d::GenericType);
	DOTEST(GeoTexCoords1f,  Real32  , GeoTexCoords1f::getClassType(), GeoTexCoords1f::PtrType, GeoTexCoords1f::GenericType);
	DOTEST(GeoTexCoords2f,  Vec2f   , GeoTexCoords2f::getClassType(), GeoTexCoords2f::PtrType, GeoTexCoords2f::GenericType);
	DOTEST(GeoTexCoords3f,  Vec3f   , GeoTexCoords3f::getClassType(), GeoTexCoords3f::PtrType, GeoTexCoords3f::GenericType);
	DOTEST(GeoTexCoords4f,  Vec4f   , GeoTexCoords4f::getClassType(), GeoTexCoords4f::PtrType, GeoTexCoords4f::GenericType);
	DOTEST(GeoTexCoords1d,  Real64  , GeoTexCoords1d::getClassType(), GeoTexCoords1d::PtrType, GeoTexCoords1d::GenericType);
	DOTEST(GeoTexCoords2d,  Vec2d   , GeoTexCoords2d::getClassType(), GeoTexCoords2d::PtrType, GeoTexCoords2d::GenericType);
	DOTEST(GeoTexCoords3d,  Vec3d   , GeoTexCoords3d::getClassType(), GeoTexCoords3d::PtrType, GeoTexCoords3d::GenericType);
	DOTEST(GeoTexCoords4d,  Vec4d   , GeoTexCoords4d::getClassType(), GeoTexCoords4d::PtrType, GeoTexCoords4d::GenericType);
	DOTEST(GeoNormals3f,    Vec3f   , GeoNormals3f::getClassType(), GeoNormals3f::PtrType, GeoNormals3f::GenericType);
	DOTEST(GeoNormals3s,    Vec3s   , GeoNormals3s::getClassType(), GeoNormals3s::PtrType, GeoNormals3s::GenericType);
#ifndef OSG_NO_INT8_PNT
    DOTEST(GeoNormals3b,    Vec3b   , GeoNormals3b::getClassType(), GeoNormals3b::PtrType, GeoNormals3b::GenericType);
#endif
	DOTEST(GeoColors3ub,    Color3ub, GeoColors3ub::getClassType(), GeoColors3ub::PtrType, GeoColors3ub::GenericType);
	DOTEST(GeoColors4ub,    Color4ub, GeoColors4ub::getClassType(), GeoColors4ub::PtrType, GeoColors4ub::GenericType);
	DOTEST(GeoColors3f,     Color3f , GeoColors3f::getClassType(), GeoColors3f::PtrType, GeoColors3f::GenericType);
	DOTEST(GeoColors4f,     Color4f , GeoColors4f::getClassType(), GeoColors4f::PtrType, GeoColors4f::GenericType);
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

