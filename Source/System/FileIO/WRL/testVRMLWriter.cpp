
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
#include <OSGSceneFileHandler.h>
#include "OSGSimpleGeometry.h"

OSG_USING_NAMESPACE

#if 1
int main (int argc, char **argv)
{
    NodePtr  node;

    const char *fileName = (argc > 1) ? argv[1] : "tie.wrl";
    
    osgInit(argc, argv);

    NodePtr  pScene      = Node::create();
    GroupPtr pSceneGroup = Group::create();

    pScene->setCore(pSceneGroup);

    node = SceneFileHandler::the().read(fileName, 0);

    node->updateVolume();

    Vec3f center;
    node->getVolume().getCenter(center);

    std::cerr << "Volume: center " << center << ", volume "
              << node->getVolume().getScalarVolume() << std::endl;


    pScene->addChild(node);

    VRMLWriteAction *pWriter = VRMLWriteAction::create();

//    pWriter->addOptions(VRMLWriteAction::OSGNoNormals);

//VRMLWriteAction::OSGNoIndent |

    pWriter->open((argc > 2) ? argv[2] : "test.wrl");

    pWriter->write(pScene);

    pWriter->close();
 
    return 0;
}

#else

int main (int argc, char **argv)
{
    NodePtr  node;

    osgInit(argc, argv);

    NodePtr  pScene      = Node::create();
    GroupPtr pSceneGroup = Group::create();

    pScene->setCore(pSceneGroup);
    
    setName(pScene,      "foo");
    setName(pSceneGroup, "bar");

    NodePtr     pSceneChild     = Node::create();
//    NodeCorePtr pSceneChildCore = Group::create();
    NodeCorePtr pSceneChildCore = makeSphereGeo(3, 1);

    pSceneChild->setCore(pSceneChildCore);

    setName(pSceneChild,     "foo1");
//    setName(pSceneChildCore, "bar1");

    pScene->addChild(pSceneChild);


    pSceneChild     = Node::create();
//    pSceneChildCore = Group::create();
//    pSceneChildCore = makeSphereGeo(3, 1);
    
    pSceneChild->setCore(pSceneChildCore);

//    setName(pSceneChild,     "foo2");
    setName(pSceneChildCore, "bar2");

    pScene->addChild(pSceneChild);


    pSceneChild     = Node::create();
    pSceneChildCore = Group::create();

    pSceneChild->setCore(pSceneChildCore);

    setName(pSceneChild,     "foo3");
    setName(pSceneChildCore, "bar3");

    pScene->addChild(pSceneChild);


    pSceneChild     = Node::create();
    pSceneChildCore = Group::create();

    pSceneChild->setCore(pSceneChildCore);

    setName(pSceneChild,     "foo4");
    setName(pSceneChildCore, "bar4");

    pScene->addChild(pSceneChild);


    pSceneChild     = Node::create();
//    pSceneChildCore = Group::create();

    pSceneChild->setCore(pSceneChildCore);

   setName(pSceneChild,     "foo4");
//    setName(pSceneChildCore, "bar4");

    pScene->addChild(pSceneChild);



    VRMLWriteAction *pWriter = VRMLWriteAction::create();

    pWriter->addOptions(VRMLWriteAction::OSGNoNormals);
//VRMLWriteAction::OSGNoIndent |
                        
    pWriter->open((argc > 2) ? argv[2] : "test.wrl");

    pWriter->write(pScene);

    pWriter->close();
 
    return 0;
}
#endif
