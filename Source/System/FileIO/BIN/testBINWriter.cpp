#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>
#include <OSGBINWriter.h>

/* */
int main(int argc, char *argv[])
{
    FILE    *outFile;

    OSG::osgInit(argc, argv);

    OSG::NodePtr    root = OSG::Node::create();
    OSG::GroupPtr   group = OSG::Group::create();
    OSG::beginEditCP(root);
    OSG::beginEditCP(group);
    root->setCore(group);

    if(argc < 3)
    {
        std::cout << argv[0] << "infile1 [infile2 ...] outfile" << std::endl;
        return 1;
    }

    for(int a = 1; a < (argc - 1); ++a)
    {
        std::cout << "read:" << argv[a] << std::endl;

        OSG::NodePtr    node = OSG::SceneFileHandler::the().read(argv[a], 0);
        if(node == OSG::NullFC)
        {
            std::cerr <<
                "ERROR: Cannot read file " <<
                argv[a] <<
                "" <<
                std::endl;
            continue;
        }

        root->addChild(node);
    }

    std::cout << "write:" << argv[argc - 1] << std::endl;
    outFile = fopen(argv[argc - 1], "wb");
    if(outFile == NULL)
    {
        std::cerr <<
            "ERROR: Cannot create file " <<
            argv[argc - 1] <<
            "" <<
            std::endl;
        return 1;
    }

    OSG::BINWriter writer(outFile);

    // print volume
    root->invalidateVolume();
    root->updateVolume();
    const OSG::DynamicVolume &vol = root->getVolume();
    OSG::Vec3f vmin,vmax;
    vol.getBounds(vmin, vmax);
    std::cout << "Volume: from " << vmin << " to " << vmax << std::endl;

    writer.write(root);

    OSG::endEditCP(root);
    OSG::endEditCP(group);

    return 0;
}
