
#include <OSGLog.h>

#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGLightChunk.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
	osgInit(argc, argv);

	StateChunkClass::iterator it;
	
	cerr << "StateChunk classes:" << endl;
	
	for ( it = StateChunkClass::begin(); it != StateChunkClass::end(); it++ )
	{
		cerr << *it << endl;
	}

	// test values

	Matrix m1,m2;
	m1.setTranslate( 1,2,3 );

	Real32 r1 = 123.45, r2;

	Vec3f v31(1, 2, 3), v32;
	Vec4f v41(1, 2, 3, 4), v42;

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
	testField( name, set, get, m1,m2, m1.equals( m2, Eps ) )

#define testVec3fField( name, set, get )  	\
	testField( name, set, get, v31,v32, v31.equals( v32, Eps ) )

#define testVec4fField( name, set, get )  	\
	testField( name, set, get, v41,v42, v41.equals( v42, Eps ) )

#define testRealField( name, set, get )  	\
	testField( name, set, get, r1,r2, r1 == r2 )

	// Transform Chunk

	TransformChunkPtr tchunk = TransformChunk::create();

	cerr << "Transform chunk class: " << tchunk->getClass()->getName() << ", id "
		 << tchunk->getClassID() << ", numslots " << tchunk->getClass()->getNumSlots() 
		 << endl;

	testMatrixField( "TransformChunk: matrix", tchunk->setMatrix, tchunk->getMatrix );

	// Material Chunk

	MaterialChunkPtr mchunk = MaterialChunk::create();

	cerr << "Material chunk class: " << mchunk->getClass()->getName() << ", id "
		 << mchunk->getClassID() << ", numslots " << tchunk->getClass()->getNumSlots() 
		 << endl;

	testVec4fField( "MaterialChunk: diffuse", mchunk->setDiffuse, mchunk->getDiffuse );
	testVec4fField( "MaterialChunk: ambient", mchunk->setAmbient, mchunk->getAmbient );
	testVec4fField( "MaterialChunk: specular", mchunk->setSpecular, mchunk->getSpecular );
	testVec4fField( "MaterialChunk: emission", mchunk->setEmission, mchunk->getEmission );
	testRealField( "MaterialChunk: shininess", mchunk->setShininess, mchunk->getShininess );
	
	// Light chunk

	LightChunkPtr lchunk = LightChunk::create();

	cerr << "Light chunk class: " << lchunk->getClass()->getName() << ", id "
		 << lchunk->getClassID() << ", numslots " << lchunk->getClass()->getNumSlots() 
		 << endl;

	testVec4fField( "LightChunk: diffuse", lchunk->setDiffuse, lchunk->getDiffuse );
	testVec4fField( "LightChunk: ambient", lchunk->setAmbient, lchunk->getAmbient );
	testVec4fField( "LightChunk: specular", lchunk->setSpecular, lchunk->getSpecular );
	testVec4fField( "LightChunk: position", lchunk->setPosition, lchunk->getPosition );
	testVec3fField( "LightChunk: direction", lchunk->setDirection, lchunk->getDirection );
	testRealField( "LightChunk: exponent", lchunk->setExponent, lchunk->getExponent);
	testRealField( "LightChunk: cutoff", lchunk->setCutoff, lchunk->getCutoff );
	testRealField( "LightChunk: exponent", lchunk->setExponent, lchunk->getExponent );
	testRealField( "LightChunk: constant attenuation", lchunk->setConstantAttenuation, 
			lchunk->getConstantAttenuation );
	testRealField( "LightChunk: linear attenuation", lchunk->setLinearAttenuation, 
			lchunk->getLinearAttenuation );
	testRealField( "LightChunk: quadratic attenuation", lchunk->setQuadraticAttenuation, 
			lchunk->getQuadraticAttenuation );
	

	return 0;
}
