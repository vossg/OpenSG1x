#include <OSGConfig.h>

#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>

#include <OSGGeometry.h>
#include <OSGPointLight.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

#include <OSGSceneFileHandler.h>

#include <OSGOSGWriter.h>

OSG_USING_NAMESPACE

int main (int argc, char *argv[])
{
	for ( int i = 0; i < argc; i++ )
		cout << "Param " << i << ":" << argv[i] << endl;

    osgInit(argc, argv);
	
   	char *inFileName  = "osgWriterInput.osg";
	char *outFileName = "osgWriterOutput.osg";
	
		if( argc > 2 )
	{
		inFileName = argv[1];
		outFileName = argv[2];
	}
	
	NodePtr root = SceneFileHandler::the().read(inFileName,0);
  	
	ofstream outFileStream( outFileName );
	if( !outFileStream )
	{
		cerr << "Can not open output stream to file: " << outFileName << endl;
		return -1;
	}

	cerr << "STARTING PRINTOUT:" << endl;
	OSGWriter writer( outFileStream, 4 );
	writer.write( root );
				
	return 0;
}

