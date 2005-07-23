
#include <OSGLog.h>

#include <OSGStateChunk.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>

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

    TextureChunkPtr t1,t2,t3;
    t1 = TextureChunk::create();
    t2 = TextureChunk::create();
    t3 = TextureChunk::create();
    
    b->addChunk(t1);
    b->addChunk(t2);
    b->addChunk(t3,5);
 
    b->dump();
   
    StateChunkPtr s;
    s = b->find(TextureChunk::getClassType());
    std::cerr << "Chunk found: " << s << std::endl;

    s = b->find(TextureChunk::getClassType(), 1);
    std::cerr << "Chunk (1) found: " << s << std::endl;

    Int32 ind = b->find(t2);
    std::cerr << "TChunk direct found: " << ind << std::endl;
   
    s = b->find(TextureChunk::getClassType(), 5);
    std::cerr << "Chunk (5) found: " << s << std::endl;
    
    return 0;
}
