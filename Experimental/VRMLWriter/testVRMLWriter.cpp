
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
#include "OSGGroup.h"
#include "OSGVRMLWriteAction.h"
#include <OSGVRMLFile.h>

OSG_USING_NAMESPACE

int main (int argc, char **argv)
{
    NodePtr  node;

    const char *fileName = (argc > 1) ? argv[1] : "tie.wrl";
    
    osgInit(argc, argv);

    NodePtr  pScene      = Node::create();
    GroupPtr pSceneGroup = Group::create();

    pScene->setCore(pSceneGroup);

    VRMLFile *pFile = new VRMLFile;

    pFile->scanStandardPrototypes("std.wrl", 0);

    pFile->scanFile(fileName, 0);

    node = pFile->getRoot();

    node->updateVolume();

    Vec3f center;
    node->getVolume().getCenter(center);

    cerr << "Volume: center " << center << ", volume "
         << node->getVolume().getScalarVolume() << endl;


    pScene->addChild(node);

    VRMLWriteAction *pWriter = VRMLWriteAction::create();

    pWriter->open("test.wrl");

    pWriter->write(pScene);

    pWriter->close();
 
    return 0;
}
