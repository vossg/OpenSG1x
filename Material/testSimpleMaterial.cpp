
#include <OSGLog.h>

#include <OSGStateChunk.h>
#include <OSGMaterialChunk.h>

#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
	osgInit(argc, argv);

	osgLog().setLogLevel( LOG_DEBUG );

	MaterialPtr m;
	
	SimpleMaterialPtr b = SimpleMaterial::create();	

	b->dump();

	// test simple settings
	
	b->setAmbient( Vec3f( 0.1, 0.1, 0.1) );
	b->setDiffuse( Vec3f( 0.5, 0.5, 0.5) );
	b->setSpecular( Vec3f( 0.7, 0.7, 0.7) );
	b->setShininess( 25 );
	b->setEmission( Vec3f( 0.1, 0.2, 0.3) );
	b->setTransparency( 0.5 );

	b->dump();

	// add a non-standard chunk
	MaterialChunkPtr mchunk1;
	mchunk1 = MaterialChunk::create();
	mchunk1->setDiffuse( Vec4f( 1,0,0,0 ) );
	mchunk1->setAmbient( Vec4f( 1,0,0,0 ) );
	mchunk1->setShininess( 20 );
	b->addChunk( mchunk1 );

	b->dump();

	b->subChunk( mchunk1 );

	b->dump();
			
	return 0;
}
