#include <OSGConfig.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSceneFileHandler.h>
#include <OSGGraphOpFactory.h>
#include <OSGGraphOpSeq.h>

using namespace OSG;

/* */
int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    NodePtr    root = Node::create();
    GroupPtr   group = Group::create();
    beginEditCP(root);
    beginEditCP(group);
    root->setCore(group);

    if(argc < 4)
    {
        std::cout << argv[0] << " opseq infile1 [infile2 ...] outfile" << std::endl;
        return 1;
    }
    
    GraphOpSeq seq(argv[1]);
    
    for(int a = 2; a < (argc - 1); ++a)
    {
        std::cout << "read:" << argv[a] << std::endl;

        NodePtr node = SceneFileHandler::the().read(argv[a]);
        if(node == NullFC)
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

    if (argc == 4)
        root = root->getChild(0);

    seq.run(root);
    
    SceneFileHandler::the().write(root,argv[argc-1]);

    endEditCP(root);
    endEditCP(group);
   
    return 0;
}
