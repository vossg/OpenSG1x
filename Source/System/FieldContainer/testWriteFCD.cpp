#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGBaseFunctions.h>
#include <OSGFieldContainerFactory.h>

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    std::ostream * out = &std::cout;
    char * name = "TextureChunk";
    std::ofstream f;

    switch ( argc )
    {
    case 2: if ( ! strcmp( argv[1], "-" ) )
                out = &std::cout;
            else
            {
                f.open( argv[1] );
                out = &f;
            }
            break;
    case 3: if ( ! strcmp( argv[1], "-" ) )
                out = &std::cout;
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
