
#include <OSGLog.h>

#include "OSGState.h"
#include "OSGTransformChunk.h"
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

	TransformChunkPtr tchunk = TransformChunk::create();

	cerr << "Transform chunk class: " << tchunk->getClassID() << endl;

	Matrix m;
	
	tchunk->setMatrix( m );


	LightChunkPtr lchunks[9];
	
	for ( int i = 0; i < 9; i++ )
		lchunks[i] = LightChunk::create();

	cerr << "Light chunk class: " << lchunks[0]->getClassID() << endl;


	// State

	StatePtr state = State::create();

	state->dump();

	cerr << "TransformChunk present? " 
		 << (state->chunkPresent( tchunk->getClassID() )?"Yes":"No") << endl;
	cerr << "TransformChunk present (class)? " 
		 << (state->chunkPresent( tchunk )?"Yes":"No") << endl;

	state->addChunk( tchunk );

	state->dump();

	cerr << "TransformChunk present? " 
		 << (state->chunkPresent( tchunk->getClassID() )?"Yes":"No") << endl;

	cerr << "TransformChunk present (class)? " 
		 << (state->chunkPresent( tchunk )?"Yes":"No") << endl;


	cerr << "Test the multiple light chunks..." << endl;

	cerr << "Single add..." << endl;
	state->addChunk( lchunks[0], -1 );
	state->dump();

	cerr << "Specific set (index = 2)..." << endl;
	state->addChunk( lchunks[1], 2 );
	state->dump();

	cerr << "Multiple adds..." << endl;
	state->addChunk( lchunks[2], -1 );
	state->addChunk( lchunks[3], -1 );
	state->addChunk( lchunks[4], -1 );
	state->addChunk( lchunks[5], -1 );
	state->addChunk( lchunks[6], -1 );
	state->addChunk( lchunks[7], -1 );
	state->dump();
	
	cerr << "This one shouldn't work..." << endl;
	state->addChunk( lchunks[8], -1 );
	state->dump();
	
	cerr << "Now try to get rid of them..." << endl;
	
	cerr << "direct index (0)" << endl;
	state->subChunk( lchunks[0], 0 );
	state->dump();

	cerr << "automatic find (last)" << endl;	
	state->subChunk( lchunks[7] );
	state->dump();
	
	cerr << "automatic find (rest)" << endl;	
	state->subChunk( lchunks[1] );
	state->subChunk( lchunks[2] );
	state->subChunk( lchunks[3] );
	state->subChunk( lchunks[4] );
	state->subChunk( lchunks[5] );
	state->subChunk( lchunks[6] );
	state->subChunk( tchunk );
	state->dump();

	cerr << "should be empty now" << endl;	
	
	return 0;
}
