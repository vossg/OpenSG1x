
#include <stdio.h>

#include <OSGVRMLFile.h>

int main(int argc, char **argv)
{
    OSG::NodePtr pRoot;

    int i = 0;

    OSG::osgInit(i, NULL);

    OSG::VRMLFile *pFile = new OSG::VRMLFile;

    OSG::Node::create();

    pFile->scanStandardPrototypes("std.wrl", 0);

    pFile->scanFile(argv[1], 0);

    pRoot = pFile->getRoot();

    cerr << "Tree : " << endl;

    if(pRoot == OSG::NullNode)
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
