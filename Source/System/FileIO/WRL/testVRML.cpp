
#include <stdio.h>

#include <OSGVRMLFile.h>
#include <OSGSceneFileHandler.h>

int main(int argc, char **argv)
{
    OSG::NodePtr pRoot;

    int i = 0;

    OSG::osgInit(i, NULL);

    OSG::Node::create();

    if((argc > 2) && (OSG::stringcmp(argv[2], "pushNames") == 0))
    {    
        OSG::SceneFileHandler::the().setOptions("wrl", "pushNames=true");
    }
    
    pRoot = OSG::SceneFileHandler::the().read(argv[1]);

    std::cerr << "Tree : " << std::endl;

    if(pRoot == OSG::NullFC)
    {
        std::cerr << "\t Empty" << std::endl;
    }
    else
    {
        pRoot->dump();
    }

//    char *szFilename = "stirnwand.wrl";

    OSG::osgExit();

    return 0;
}
