
#include "OSGConfig.h"

#include <iostream>
#include <fstream>

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

    SceneFileHandler::the().print();

    node = SceneFileHandler::the().read(fileName);

    node->updateVolume();

    Vec3f center;
    node->getVolume().getCenter(center);

    std::cerr << "Volume: center " << center << ", volume "
         << node->getVolume().getScalarVolume() << std::endl;


    return 0;
}
