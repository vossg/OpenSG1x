#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include <OSGBaseFunctions.h>
#include <OSGFieldContainerFactory.h>

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    ostream * out = &cout;
    char * name = "TextureChunk";
    ofstream f;

    switch ( argc )
    {
    case 2: if ( ! strcmp( argv[1], "-" ) )
                out = &cout;
            else
            {
                f.open( argv[1] );
                out = &f;
            }
            break;
    case 3: if ( ! strcmp( argv[1], "-" ) )
                out = &cout;
            else
            {
                f.open( argv[1] );
                out = &f;
            }
            name = argv[2];
            break;
    }

    OSG::FieldContainerFactory::the()->writeFCD( name, out );

    OSG::osgExit();
}
