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
        cout << "Param " << i << ":" << argv[i] << endl;

    OSG::osgInit(argc, argv);

    FILE *outFile;
    const char *inFileName  = "tie.wrl";
    const char *outFileName = "tie.bin";
    string s;
    
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
			cerr<<"ERROR: Cannot create file """<<outFileName<<""""<<endl;
		else
		{
    		cout << "reading " << inFileName << "..." << endl;
			OSG::NodePtr root = OSG::SceneFileHandler::the().read(inFileName,0);
    		cout << "writing " << outFileName << "..." << endl;
			OSG::BINWriter writer(outFile);
    		writer.write( root );
			cout<<"done"<<endl;
//            root->dump();
		}

		fclose(outFile);
	}
	else cerr<<inFileName<<" not found!"<<endl;
    
	
	return 0;
}
