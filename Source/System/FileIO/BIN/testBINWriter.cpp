#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>
#include <OSGBINWriter.h>
#include <OSGSceneFileHandler.h>

/* */
int main(int argc, char *argv[])
{
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

        OSG::NodePtr    node = OSG::SceneFileHandler::the().read(argv[a]);
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

    // print volume
    root->invalidateVolume();
    root->updateVolume();
    const OSG::DynamicVolume &vol = root->getVolume();
    OSG::Vec3f vmin,vmax;
    vol.getBounds(vmin, vmax);
    std::cout << "Volume: from " << vmin << " to " << vmax << std::endl;

    OSG::SceneFileHandler::the().write(root,argv[argc-1]);

    OSG::endEditCP(root);
    OSG::endEditCP(group);

    return 0;
}
