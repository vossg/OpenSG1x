
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGBaseFunctions.h"
#include "OSGNode.h"
#include "OSGSceneFileHandler.h"
#include "OSGRAWSceneFileType.h"

OSG_USING_NAMESPACE

int main (int argc, char **argv)
{
	OSGNodePtr node;
	const char *fileName = (argc > 1) ? argv[1] : "test.raw";
	
	osgInit(argc, argv);

#ifdef WIN32
    OSGRAWSceneFileType *pR = &(OSGRAWSceneFileType::staticThe());
#endif

	OSGSceneFileHandler::the().print();

	node = OSGSceneFileHandler::the().read(argv[1]);

	node->updateVolume();

	OSGVec3f center;
	node->getVolume().getCenter(center);

	cerr << "Volume: center " << center << ", volume "
		 << node->getVolume().getVolume() << endl;

 
	return 0;
}
