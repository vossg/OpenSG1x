
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
	NodePtr node;
	const char *fileName = (argc > 1) ? argv[1] : "test.raw";
	
	osgInit(argc, argv);

#ifdef __linux
    RAWSceneFileType *pR = &(RAWSceneFileType::staticThe());
#endif

	SceneFileHandler::the().print();

	node = SceneFileHandler::the().read(fileName);

	node->updateVolume();

	Vec3f center;
	node->getVolume().getCenter(center);

	cerr << "Volume: center " << center << ", volume "
		 << node->getVolume().getScalarVolume() << endl;

 
	return 0;
}
