#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSimpleAttachments.h>

int main (int argc, char **argv)
{
    OSG::ChangeList::setReadWriteDefault();
    OSG::osgInit(argc, argv);

    OSG::Thread::getCurrent()->getChangeList()->dump();
    OSG::Thread::getCurrent()->getChangeList()->clearAll();
    OSG::Thread::getCurrent()->getChangeList()->dump();

    PLOG << "Num types : "
         << OSG::FieldContainerFactory::the()->getNumTypes()
         << std::endl;

    OSG::FieldContainerPtr pFC;

    pFC.dump(0, OSG::FCDumpFlags::RefCount);

    pFC = OSG::FieldContainerFactory::the()->createNode("Node");

    pFC.dump(0, OSG::FCDumpFlags::RefCount);

    OSG::addRefCP(pFC);

    pFC.dump(0, OSG::FCDumpFlags::RefCount);

    OSG::Thread::getCurrent()->getChangeList()->dump();

    pFC->dump();

    OSG::subRefCP(pFC);

    pFC.dump(0, OSG::FCDumpFlags::RefCount);

    OSG::Thread::getCurrent()->getChangeList()->dump();
    OSG::Thread::getCurrent()->getChangeList()->clearAll();

    // operator check
    
    pFC = OSG::NullFC;
    
    if(pFC)
    {
        std::cerr << "pFC set?!?" << std::endl;
    }
    else
    {
        std::cerr << "pFC not set" << std::endl;
    }

    pFC = OSG::FieldContainerFactory::the()->createNode("Node");
    
    if(pFC)
    {
        std::cerr << "pFC set" << std::endl;
    }
    else
    {
        std::cerr << "pFC not set?!?" << std::endl;
    }
    
    OSG::subRefCP(pFC);
    
    // child management


    OSG::NodePtr           p1  = OSG::Node::create();
    OSG::FieldContainerPtr pb1 = p1;

    OSG::addRefCP(p1);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    pb1.dump(0, OSG::FCDumpFlags::RefCount);

    std::cerr << " N : " << p1->getType().getId()              << std::endl;
    std::cerr << " N : " << OSG::Node::getClassType().getId() << std::endl;

    OSG::NodePtr p2 = OSG::Node::create();
    OSG::NodePtr p3 = OSG::Node::create();
    OSG::NodePtr p4 = OSG::Node::create();
    OSG::NodePtr p5 = OSG::Node::create();
    OSG::NodePtr p6 = OSG::Node::create();

    p1->dump (0, OSG::FCDumpFlags::RefCount);
    p2->dump (0, OSG::FCDumpFlags::RefCount);
    p3->dump (0, OSG::FCDumpFlags::RefCount);
    p4->dump (0, OSG::FCDumpFlags::RefCount);
    p5->dump (0, OSG::FCDumpFlags::RefCount);
    p6->dump (0, OSG::FCDumpFlags::RefCount);

    OSG::addRefCP(p6);

    OSG::beginEditCP(p1);

    std::cerr << "add p2" << std::endl;

    p1->addChild(p2);
    p1->dump (0, OSG::FCDumpFlags::RefCount);
    p1.dump(0, OSG::FCDumpFlags::RefCount);

    std::cerr << "add p3" << std::endl;

    OSG::addRefCP(p3);
    p1->addChild(p3);
    p1->dump (0, OSG::FCDumpFlags::RefCount);
    p1.dump  (0, OSG::FCDumpFlags::RefCount);
    p3.dump  (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "insert p4" << std::endl;

    p1->insertChild(1, p4);
    p1->dump (0, OSG::FCDumpFlags::RefCount);
    p1.dump  (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "replace p3 -> p5" << std::endl;

    p1->replaceChild(2, p5);
    p1->dump (0, OSG::FCDumpFlags::RefCount);
    p1.dump  (0, OSG::FCDumpFlags::RefCount);

    OSG::Thread::getCurrent()->getChangeList()->dump();

    p3.dump (0, OSG::FCDumpFlags::RefCount);
    p3->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "replace p5 -> p3" << std::endl;

    p1->replaceChildBy(p5, p3);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "sub p2" << std::endl;

    p2.dump (0, OSG::FCDumpFlags::RefCount);
    p1->subChild(p2);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "sub p6" << std::endl;

    p1->subChild(p6);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "sub child 1" << std::endl;

    p1->subChild(1);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << "sub child 0" << std::endl;

    p1->subChild(0);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);

    OSG::endEditCP(p1);



    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p2.dump (0, OSG::FCDumpFlags::RefCount);
    p3.dump (0, OSG::FCDumpFlags::RefCount);
    p4.dump (0, OSG::FCDumpFlags::RefCount);
    p5.dump (0, OSG::FCDumpFlags::RefCount);
    p6.dump (0, OSG::FCDumpFlags::RefCount);

    std::cerr << std::endl << std::endl << "Core test" << std::endl;

    p1.dump (0, OSG::FCDumpFlags::RefCount);

    OSG::GroupPtr g1 = OSG::Group::create();

    p1->setCore(g1);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    g1.dump (0, OSG::FCDumpFlags::RefCount);

    p1->setCore(OSG::NullFC);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    g1.dump (0, OSG::FCDumpFlags::RefCount);

    g1 = OSG::Group::create();

    p1->setCore(g1);
    g1.dump (0, OSG::FCDumpFlags::RefCount);

    p2 = OSG::NodePtr::dcast(p1->shallowCopy());
//    OSG::addRefCP(p2);

    g1.dump (0, OSG::FCDumpFlags::RefCount);

    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p2->dump(0, OSG::FCDumpFlags::RefCount);

    p1->setCore(g1);
    g1.dump (0, OSG::FCDumpFlags::RefCount);
    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p2->dump(0, OSG::FCDumpFlags::RefCount);

    std::cerr << std::endl << std::endl << "Indirect Del" << std::endl;

    p2->setCore(OSG::NullFC);

    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p2.dump(0, OSG::FCDumpFlags::RefCount);


    std::cerr << std::endl << std::endl << "Attachment test" << std::endl;

    OSG::NamePtr n1 = OSG::Name::create();
    OSG::NamePtr n2 = OSG::Name::create();

    p1->addAttachment(n1);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    n1.dump (0, OSG::FCDumpFlags::RefCount);

    p1->subAttachment(n1);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    n1.dump (0, OSG::FCDumpFlags::RefCount);

    n1 = OSG::Name::create();

    p1->addAttachment(n1);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    n1.dump (0, OSG::FCDumpFlags::RefCount);

    p1->addAttachment(n2);

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p1->dump(0, OSG::FCDumpFlags::RefCount);
    n1.dump (0, OSG::FCDumpFlags::RefCount);
    n2.dump (0, OSG::FCDumpFlags::RefCount);

    p2 = OSG::NodePtr::dcast(p1->shallowCopy());

    p1.dump (0, OSG::FCDumpFlags::RefCount);
    p2.dump (0, OSG::FCDumpFlags::RefCount);

    p1->dump(0, OSG::FCDumpFlags::RefCount);
    p2->dump(0, OSG::FCDumpFlags::RefCount);

    fprintf(stderr, "%p %p %p\n",
            p1.getBaseCPtr(),
            p1.getAspectCPtr(0),
            p1.getAspectCPtr(1));

    // test name convenience functions
    
    std::cerr << "Name convenience" << std::endl;
    
    if(OSG::getName(p3) == NULL)
    {
        std::cerr << "No name: (NULL)" << std::endl;
    }
    else
    {
        std::cerr << "Strange No name not NULL: " 
                  << OSG::getName(p3)  
                  << std::endl;
    }

    OSG::setName(p3, "Hugo");
    
    std::cerr << "Name: " << OSG::getName(p3) << std::endl;
    
    OSG::setName(p3, std::string("Hugo"));
    
    std::cerr << "String Name: " << OSG::getName(p3) << std::endl;
     
    OSG::setName(p3, NULL);
    
    if(OSG::getName(p3) == NULL)
    {
        std::cerr << "Removed name: (NULL)" << std::endl;
    }
    else
    {
        std::cerr << "Removed name not NULL: " 
                  << OSG::getName(p3)  
                  << std::endl;
    }

    if(OSG::getVoidP(p3) == NULL)
    {
        std::cerr << "No VoidPAttachent: (NULL)" << std::endl;
    }
    else
    {
        std::cerr << "Strange No VoidPAttachent not NULL: " 
                  << OSG::getVoidP(p3) 
                  << std::endl;
    }

    double d;

    OSG::setVoidP(p3, &d);
    std::cerr << "VoidPAttachent: " 
              << (&d) 
              << " | "
              << OSG::getVoidP(p3) << std::endl;

    OSG::setVoidP(p3, NULL);

    if(OSG::getVoidP(p3) == NULL)
    {
        std::cerr << "Removed VoidPAttachent: (NULL)" << std::endl;
    }
    else
    {
        std::cerr << "Strange Removed VoidPAttachent not NULL: " 
                  << OSG::getVoidP(p3) 
                  << std::endl;
    }

    OSG::subRefCP(p3);
    OSG::subRefCP(p1);

    OSG::osgExit();
}

#if 0
using namespace OSG;

void x(Node *xa)
{
    fprintf(stderr, "x : \n");
    xa->print();
}

void y(const Node *xa)
{
    fprintf(stderr, "y : \n");
    xa->print();
}

void initGeos(void)
{
    fprintf(stderr, "Initialize Geo\n");
}

struct SimpleAttDesc
{
    typedef MFVec3f FieldTypeT;

    static const char *getTypeName (void) { return "GeoPoints"; }
    static const char *getFieldName(void) { return "points"; }
    static const char *getGroupName(void) { return "points"; }
    static const char *getClassName(void) { return "GeoPointsAttachment"; }
    static InitContainerF getInitMethod(void) { return initGeos;}
};

typedef SimpleAttachment<SimpleAttDesc> GeoPoints;

template class SimpleAttachment<SimpleAttDesc>;

typedef FCPtr<AttachmentPtr,  GeoPoints> GeoPointsPtr;


#if 0
class NewNode;
typedef FCPtr<NodePtr,  NewNode> NewNodePtr;

class NewNode : public Node
{
  public :

    static FieldContainerType _type;

    static NewNodePtr create(void)
        {
            NewNodePtr fc;

#ifdef OSG_HAS_TEMPLATE_RETURNVALUES
            if(_type.getPrototype() != NullFC)
                fc = _type.getPrototype()->clone().dcast<NewNodePtr>();
#else
            if(_type.getPrototype() != NULL)
                _type.getPrototype()->clone().dcast(fc);
#endif

            return fc;
        }

    static NewNodePtr createEmpty(void)
        {
            NewNodePtr returnValue;

            newPtr(returnValue);

            return returnValue;
        }

    NewNode(void) {} ;
    ~NewNode(void) {};

    const FieldContainerType &getType(void) const { return _type; }
          FieldContainerType &getType(void)       { return _type; }

    virtual FieldContainerPtr clone(void) const
    {
            NewNodePtr returnValue;

            newPtr(returnValue, this);

            return returnValue;
    };

};

FieldContainerType NewNode::_type("NewNode",
                                        "Node",
                                        0,
                                        (PrototypeCreateF) &NewNode::createEmpty,
                                        0,
                                        NULL,
                                        0);

#endif

struct DynDesc
{
    typedef Attachment    Parent;
    typedef AttachmentPtr ParentPtr;

    static const char *getTypeName      (void) { return "DynDesc";    }
    static const char *getParentTypeName(void) { return "Attachment"; }
    static const char *getGroupName     (void) { return "Test";       }
};

int main (int argc, char **argv)
{

    osgInit(argc, argv);

//  Field *pI;

    std::cout << "TypeCounter: "
         << " | " << sizeof(FieldContainerPtr) << std::endl;


    FieldContainerPtr qFC = NullFC;

//  fprintf( stderr,"stderr output\n");
//    pFC.dump();

//    NullFC.dump();

//  std::cout << "Stream output" << std::endl;

//  std::cout << "pFC: " ;
//  std::cout << pFC << std::endl;

//  std::cout << "NullFC: " << qFC << std::endl;


    if(pFC != NullFC)
    {
//        pFC->getType().print();

//        std::cerr << pFC.dcast<NodePtr>()->getMFChildren() << std::endl;

//        pI = pFC->getField("children");

//        std::cerr << pI << std::endl;

//        std::cerr << pFC.dcast<NodePtr>()->getSFName() << std::endl;

//        pI = pFC->getField("name");

//        std::cerr << pI << std::endl;
    }

//    std::cerr << std::endl << std::endl;


//    pb1->getType().print();




    Thread::getCurrentChangeList()->dump();


//    p1.dump();
//    p2.dump();

    std::cerr << std::endl << "Attachment test" << std::endl;

    GeoPointsPtr pPoint;

    std::cerr << "GeoPoints::getClassname()=" << GeoPoints::getClassname() << std::endl;
    std::cerr << "GeoPointsPtr::getClassname()=" << GeoPointsPtr::getClassname() << std::endl;
    std::cerr << "pPoint.getClassname()=" << pPoint.getClassname() << std::endl;
    std::cerr << "(*pPoint).getClassname()=" << (*pPoint).getClassname() << std::endl;

    pPoint = GeoPoints::create();

    pPoint->getType().print();

//    p1.dump();
    p1->addAttachment(pPoint);
    p1->print(0);

    p1->subAttachment(pPoint);
    p1->print(0);
    pPoint->print(0);

//    NewNode *pNewProto = NewNode::getStaticType().createPrototype();

    std::cerr << std::endl << "Proto test\n" << std::endl;

//    NewNodePtr newNodeP = NewNode::create();
    NodePtr    nodeP    = Node::create();

    nodeP->getType().print();
//    newNodeP->getType().print();

//    NewNode *np = new NewNode();
//    Node *np = &(*nodeP);

//    Node::getStaticType().setPrototype(newNodeP);

    NodePtr    nodeP1    = Node::create();
    nodeP1->getType().print();

    if(! NullFC)
    {
        fprintf(stderr, "NN\n");
    }
    {
        fprintf(stderr, "IN\n");
    }

    if(! nodeP1)
    {
        fprintf(stderr, "PNN\n");
    }
    {
        fprintf(stderr, "PIN\n");
    }

    nodeP1 = NullNode;

    nodeP1.dump();

    typedef DynFieldAttachment<DynDesc> DynAtt;
    typedef FCPtr<AttachmentPtr, DynAtt> DynAttPtr;

    DynAttPtr da;

    da = DynAtt::create();

    da->getType().print();

    fprintf(stderr, "%x\n", da->getType().getFieldDescription(1));

    FieldDescription *pDesc;

    pDesc = new FieldDescription(
        SFString::getClassType(),
        "name",
        0, 0,
        false,
        (FieldIndexAccessMethod) &DynAtt::getDynamicField);

    UInt32 uiFI1 = da->addField(*pDesc);

    fprintf(stderr, "%d\n", uiFI1);



    pDesc = new FieldDescription(
        SFString::getClassType(),
        "name1",
        0, 0,
        false,
        (FieldIndexAccessMethod) &DynAtt::getDynamicField);

    UInt32 uiFI2 = da->addField(*pDesc);

    fprintf(stderr, "%d\n", uiFI2);

    da->getType().print();
    da->dump();

    da->subField(uiFI1);

    da->getType().print();

    da->dump();

    fprintf(stderr, "Retrieve Field 1 %d\n", da->getField(1));
    fprintf(stderr, "Retrieve Field 2 %d\n", da->getField(2));
    fprintf(stderr, "Retrieve Field 3 %d\n", da->getField(3));

    pDesc = new FieldDescription(
        SFString::getClassType(),
        "name2",
        0, 0,
        false,
        (FieldIndexAccessMethod) &DynAtt::getDynamicField);

    UInt32 uiFI3 = da->addField(*pDesc);

    fprintf(stderr, "%d\n", uiFI3);

    da->dump();

    da->getType().print();


    fprintf(stderr, "Retrieve Field 1 %d\n", da->getField(1));
    fprintf(stderr, "Retrieve Field 2 %d\n", da->getField(2));
    fprintf(stderr, "Retrieve Field 3 %d\n", da->getField(3));

    delete pDesc;

    return 0;
}

#endif
