
#include <OSGLog.h>

#include "OSGState.h"
#include "OSGTransformChunk.h"
#include "OSGLightChunk.h"

OSG_USING_NAMESPACE


int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

    StateChunkClass::iterator it;

    std::cerr << "StateChunk classes:" << std::endl;

    for ( it = StateChunkClass::begin(); it != StateChunkClass::end(); it++ )
    {
        std::cerr << *it << std::endl;
    }

    TransformChunkPtr tchunk = TransformChunk::create();

    std::cerr << "Transform chunk class: " << tchunk->getClassId() << std::endl;

    Matrix m;

    tchunk->setMatrix( m );


    LightChunkPtr lchunks[9];

    for ( int i = 0; i < 9; i++ )
        lchunks[i] = LightChunk::create();

    std::cerr << "Light chunk class: " << lchunks[0]->getClassId() << std::endl;


    // State

    StatePtr state = State::create();

    state->dump();

    std::cerr << "TransformChunk present? "
         << (state->chunkPresent( tchunk->getClassId() )?"Yes":"No") << std::endl;
    std::cerr << "TransformChunk present (class)? "
         << (state->chunkPresent( tchunk )?"Yes":"No") << std::endl;

    state->addChunk( tchunk );

    state->dump();

    std::cerr << "TransformChunk present? "
         << (state->chunkPresent( tchunk->getClassId() )?"Yes":"No") << std::endl;

    std::cerr << "TransformChunk present (class)? "
         << (state->chunkPresent( tchunk )?"Yes":"No") << std::endl;


    std::cerr << "Test the multiple light chunks..." << std::endl;

    std::cerr << "Single add..." << std::endl;
    state->addChunk( lchunks[0], -1 );
    state->dump();

    std::cerr << "Specific set (index = 2)..." << std::endl;
    state->addChunk( lchunks[1], 2 );
    state->dump();

    std::cerr << "Multiple adds..." << std::endl;
    state->addChunk( lchunks[2], -1 );
    state->addChunk( lchunks[3], -1 );
    state->addChunk( lchunks[4], -1 );
    state->addChunk( lchunks[5], -1 );
    state->addChunk( lchunks[6], -1 );
    state->addChunk( lchunks[7], -1 );
    state->dump();

    std::cerr << "This one shouldn't work..." << std::endl;
    state->addChunk( lchunks[8], -1 );
    state->dump();

    std::cerr << "Now try to get rid of them..." << std::endl;

    std::cerr << "automatic find (0)" << std::endl;
    state->subChunk( lchunks[0] );
    state->dump();

    std::cerr << "automatic find (last)" << std::endl;
    state->subChunk( lchunks[7] );
    state->dump();

    std::cerr << "automatic find (rest)" << std::endl;
    state->subChunk( lchunks[1] );
    state->subChunk( lchunks[2] );
    state->subChunk( lchunks[3] );
    state->subChunk( lchunks[4] );
    state->subChunk( lchunks[5] );
    state->subChunk( lchunks[6] );
    state->subChunk( tchunk );
    state->dump();

    std::cerr << "should be empty now" << std::endl;

    return 0;
}
