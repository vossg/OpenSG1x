
#include <OSGLog.h>

#include <OSGStateChunk.h>
#include <OSGMaterialChunk.h>

#include "OSGMaterial.h"
#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
	osgInit(argc, argv);

	MaterialPtr m;
	
	ChunkMaterialPtr b = ChunkMaterial::create();	

	b->dump();
	
	MaterialChunkPtr mchunk1, mchunk2;

	mchunk1 = MaterialChunk::create();
	mchunk1->setDiffuse( Color4f( 1,0,0,0 ) );
	mchunk1->setAmbient( Color4f( 1,0,0,0 ) );
	mchunk1->setShininess( 20 );
	b->addChunk( mchunk1 );

	b->dump();

	b->subChunk( mchunk1 );

	b->dump();

	return 0;
}
