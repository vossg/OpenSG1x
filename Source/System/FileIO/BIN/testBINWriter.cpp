#include <OSGConfig.h>
 
#include <iostream>
#include <fstream>

#include <OSGNode.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>
#include <OSGBINWriter.h>

int main (int argc, char *argv[])
{
    for ( int i = 0; i < argc; i++ )
        std::cout << "Param " << i << ":" << argv[i] << std::endl;

    OSG::osgInit(argc, argv);

    FILE *outFile;
    const char *inFileName  = "tie.wrl";
    const char *outFileName = "tie.bin";
    std::string s;
    
    if( argc > 1 )
        inFileName  = argv[1];

	if (argc > 2)
			outFileName = argv[2];
    else
    {
        s = argv[1];
        s.replace( s.rfind("."), s.size(), ".bin");
        outFileName = s.c_str();
    }
    
	if(fopen(inFileName, "rb")!=NULL)
	{
		outFile = fopen(outFileName, "wb");
		
		if (outFile==NULL)
			std::cerr<<"ERROR: Cannot create file """<<outFileName<<""""<<std::endl;
		else
		{
    		std::cout << "reading " << inFileName << "..." << std::endl;
			OSG::NodePtr root = OSG::SceneFileHandler::the().read(inFileName,0);
    		std::cout << "writing " << outFileName << "..." << std::endl;
			OSG::BINWriter writer(outFile);
    		writer.write( root );
			std::cout<<"done"<<std::endl;
//            root->dump();
		}

		fclose(outFile);
	}
	else std::cerr<<inFileName<<" not found!"<<std::endl;
    
	
	return 0;
}
