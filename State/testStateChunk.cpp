
#include <OSGLog.h>

#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGLightChunk.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
	osgInit(argc, argv);

	OSGStateChunkClass::iterator it;
	
	cerr << "StateChunk classes:" << endl;
	
	for ( it = OSGStateChunkClass::begin(); it != OSGStateChunkClass::end(); it++ )
	{
		cerr << *it << endl;
	}

	// test values

	OSGMatrix m1,m2;
	m1.setTranslate( 1,2,3 );

	OSGReal32 r1 = 123.45, r2;

	OSGVec3f v31(1, 2, 3), v32;
	OSGVec4f v41(1, 2, 3, 4), v42;

	// Test macros for simple set/get correspondence

#define testField( name, set,get, v1,v2,comp )				\
	set(v1);												\
	v2 = get();												\
	cerr << name;											\
	if ( ! comp )											\
	{														\
		cerr << " " << v1 << "!=" << v2 << "!!!" << endl;	\
		exit(1);											\
	}														\
	else													\
		cerr << " ok" << endl

#define testMatrixField( name, set, get )  	\
	testField( name, set, get, m1,m2, m1.equals( m2, osgEps ) )

#define testVec3fField( name, set, get )  	\
	testField( name, set, get, v31,v32, v31.equals( v32, osgEps ) )

#define testVec4fField( name, set, get )  	\
	testField( name, set, get, v41,v42, v41.equals( v42, osgEps ) )

#define testRealField( name, set, get )  	\
	testField( name, set, get, r1,r2, r1 == r2 )

	// Transform Chunk

	OSGTransformChunkPtr tchunk = OSGTransformChunk::create();

	cerr << "Transform chunk class: " << tchunk->getClass()->getName() << ", id "
		 << tchunk->getClassID() << ", numslots " << tchunk->getClass()->getNumSlots() 
		 << endl;

	testMatrixField( "OSGTransformChunk: matrix", tchunk->setMatrix, tchunk->getMatrix );

	// Material Chunk

	OSGMaterialChunkPtr mchunk = OSGMaterialChunk::create();

	cerr << "Material chunk class: " << mchunk->getClass()->getName() << ", id "
		 << mchunk->getClassID() << ", numslots " << tchunk->getClass()->getNumSlots() 
		 << endl;

	testVec4fField( "OSGMaterialChunk: diffuse", mchunk->setDiffuse, mchunk->getDiffuse );
	testVec4fField( "OSGMaterialChunk: ambient", mchunk->setAmbient, mchunk->getAmbient );
	testVec4fField( "OSGMaterialChunk: specular", mchunk->setSpecular, mchunk->getSpecular );
	testVec4fField( "OSGMaterialChunk: emission", mchunk->setEmission, mchunk->getEmission );
	testRealField( "OSGMaterialChunk: shininess", mchunk->setShininess, mchunk->getShininess );
	
	// Light chunk

	OSGLightChunkPtr lchunk = OSGLightChunk::create();

	cerr << "Light chunk class: " << lchunk->getClass()->getName() << ", id "
		 << lchunk->getClassID() << ", numslots " << lchunk->getClass()->getNumSlots() 
		 << endl;

	testVec4fField( "OSGLightChunk: diffuse", lchunk->setDiffuse, lchunk->getDiffuse );
	testVec4fField( "OSGLightChunk: ambient", lchunk->setAmbient, lchunk->getAmbient );
	testVec4fField( "OSGLightChunk: specular", lchunk->setSpecular, lchunk->getSpecular );
	testVec4fField( "OSGLightChunk: position", lchunk->setPosition, lchunk->getPosition );
	testVec3fField( "OSGLightChunk: direction", lchunk->setDirection, lchunk->getDirection );
	testRealField( "OSGLightChunk: exponent", lchunk->setExponent, lchunk->getExponent);
	testRealField( "OSGLightChunk: cutoff", lchunk->setCutoff, lchunk->getCutoff );
	testRealField( "OSGLightChunk: exponent", lchunk->setExponent, lchunk->getExponent );
	testRealField( "OSGLightChunk: constant attenuation", lchunk->setConstantAttenuation, 
			lchunk->getConstantAttenuation );
	testRealField( "OSGLightChunk: linear attenuation", lchunk->setLinearAttenuation, 
			lchunk->getLinearAttenuation );
	testRealField( "OSGLightChunk: quadratic attenuation", lchunk->setQuadraticAttenuation, 
			lchunk->getQuadraticAttenuation );
	

	return 0;
}
