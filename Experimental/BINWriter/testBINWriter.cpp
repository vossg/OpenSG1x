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
    char *inFileName  = "tie.wrl";
    char *outFileName = "tie.bin";
    if( argc > 1 )
        inFileName  = argv[1];

	if (argc > 2)
			outFileName = argv[2];
    
    
	if(fopen(inFileName, "rb")!=NULL)
	{
		outFile = fopen(outFileName, "wb");
		
		if (outFile==NULL)
			cerr<<"ERROR: Cannot create file """<<outFileName<<""""<<endl;
		else
		{
			OSG::NodePtr root = OSG::SceneFileHandler::the().read(inFileName,0);
    		cout << "#starting binary conversion for "<<inFileName<<endl;
			OSG::BINWriter writer(outFile);
    		writer.write( root );
			cout<<"#finished!"<<endl;
//            root->dump();
		}

		fclose(outFile);
	}
	else cerr<<inFileName<<" not found!"<<endl;
    
	
	return 0;
}
