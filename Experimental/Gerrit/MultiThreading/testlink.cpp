
#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGNodePtr.h>
#include <OSGNode.h>
#include <OSGGroup.h>

int main (int argc, char **argv)
{
    OSG::osgInit(argc, argv);

    OSG::GroupPtr pGroup   = OSG::Group::create();

    OSG::NodePtr  pNode1   = OSG::Node::create();

    OSG::NodePtr  pNode11  = OSG::Node::create();
    OSG::NodePtr  pNode111 = OSG::Node::create();
    OSG::NodePtr  pNode112 = OSG::Node::create();
    OSG::NodePtr  pNode113 = OSG::Node::create();

    OSG::NodePtr  pNode12  = OSG::Node::create();
    OSG::NodePtr  pNode121 = OSG::Node::create();
    OSG::NodePtr  pNode122 = OSG::Node::create();
    OSG::NodePtr  pNode123 = OSG::Node::create();

    OSG::NodePtr  pNode21  = OSG::Node::create();
    OSG::NodePtr  pNode211 = OSG::Node::create();
    OSG::NodePtr  pNode212 = OSG::Node::create();
    OSG::NodePtr  pNode213 = OSG::Node::create();

    OSG::NodePtr  pNode22  = OSG::Node::create();
    OSG::NodePtr  pNode221 = OSG::Node::create();
    OSG::NodePtr  pNode222 = OSG::Node::create();
    OSG::NodePtr  pNode223 = OSG::Node::create();

    pNode1->addChild(pNode11);
    pNode1->addChild(pNode12);
    pNode1->addChild(pNode21);
    pNode1->addChild(pNode22);
    pNode1->setCore (pGroup );

    pNode11->addChild(pNode111);
    pNode11->addChild(pNode112);
    pNode11->addChild(pNode113);
    pNode11->setCore (pGroup  );

    pNode12->addChild(pNode121);
    pNode12->addChild(pNode122);
    pNode12->addChild(pNode123);
    pNode12->setCore (pGroup  );

    pNode21->addChild(pNode211);
    pNode21->addChild(pNode212);
    pNode21->addChild(pNode213);
    pNode21->setCore (pGroup  );

    pNode22->addChild(pNode221);
    pNode22->addChild(pNode222);
    pNode22->addChild(pNode223);
    pNode22->setCore (pGroup  );

    pNode111->setCore(pGroup  );
    pNode112->setCore(pGroup  );
    pNode113->setCore(pGroup  );

    pNode121->setCore(pGroup  );
    pNode122->setCore(pGroup  );
    pNode123->setCore(pGroup  );

    pNode211->setCore(pGroup  );
    pNode212->setCore(pGroup  );
    pNode213->setCore(pGroup  );

    pNode221->setCore(pGroup  );
    pNode222->setCore(pGroup  );
    pNode223->setCore(pGroup  );
    
    pNode1->dump();

//    OSG::addRefCP(pNode1);

    OSG::addRefCP(pGroup);
    pNode1->unlinkSubTree();
//    pNode1->unlink();

//    pNode1->dump();

    return 0;
}


