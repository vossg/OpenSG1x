
#include <stdio.h>

#include <OSGVRMLFile.h>
#include <OSGSceneFileHandler.h>

int main(int argc, char **argv)
{
    OSG::NodePtr pRoot;

    int i = 0;

    OSG::osgInit(i, NULL);

    OSG::Node::create();

    pRoot = OSG::SceneFileHandler::the().read(argv[1]);

    cerr << "Tree : " << endl;

    if(pRoot == OSG::NullFC)
    {
        cerr << "\t Empty" << endl;
    }
    else
    {
        pRoot->dump();
    }

//    char *szFilename = "stirnwand.wrl";

    OSG::osgExit();

    return 0;
}
