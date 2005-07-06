#include <OSGConfig.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSceneFileHandler.h>
#include <OSGGraphOpFactory.h>

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

    if(argc < 5)
    {
        std::cout << argv[0] << "opname opopts infile1 [infile2 ...] outfile" << std::endl;
        return 1;
    }
    
    GraphOp *op = GraphOpFactory::the().create(argv[1]);
    
    if(!op)
    {
        FFATAL(("Can't create %s GraphOp!\n", argv[1]));
        exit(1);
    }

    op->setParams(argv[2]);
    
    for(int a = 3; a < (argc - 1); ++a)
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

    if (argc == 5)
        root = root->getChild(0);

    op->traverse(root);
    
    SceneFileHandler::the().write(root,argv[argc-1]);

    endEditCP(root);
    endEditCP(group);
   
    return 0;
}
