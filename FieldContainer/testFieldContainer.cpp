#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>

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

//	Field *pI;

	cout << "TypeCounter: "
         << " | " << sizeof(FieldContainerPtr) << endl;

	FieldContainerPtr pFC = 
		FieldContainerFactory::the().createNode("Node");

	FieldContainerPtr qFC = NullFC;
	
//	fprintf( stderr,"stderr output\n");
//    pFC.dump();

    NullFC.dump();

//	cout << "Stream output" << endl;

//	cout << "pFC: " ;
//	cout << pFC << endl;

//	cout << "NullFC: " << qFC << endl;


    if(pFC != NullFC)
    {
        pFC->getType().print();

//        cerr << pFC.dcast<NodePtr>()->getMFChildren() << endl;

//        pI = pFC->getField("children");

//        cerr << pI << endl;

//        cerr << pFC.dcast<NodePtr>()->getSFName() << endl;

//        pI = pFC->getField("name");

//        cerr << pI << endl;
    }

//    cerr << endl << endl;

    NodePtr  p1 = Node::create();

//    p1->getType().print();

    FieldContainerPtr pb1 = p1;

//    cerr << " N : " << p1->getType().getId() 
//         << endl;

//    cerr << " N : " << Node::getStaticType().getId() 
//         << endl;
    
//    pb1->getType().print();


    NodePtr p2 = Node::create();
    NodePtr p3 = Node::create();
    NodePtr p4 = Node::create();
    NodePtr p5 = Node::create();

    p1->getPtr();
    
    p1.dump();
    p2.dump();
    p3.dump();
    p4.dump();
    p5.dump();

    p1->print();
    p2->print();
    p3->print();
    p4->print();
    p5->print();

    osgBeginEditCP(p1);

    cerr << "add" << endl;

    p1->addChild(p2);
    p1->print();

    cerr << "add" << endl;

    p1->addChild(p3);
    p1->print();

    cerr << "add" << endl;

    p1->insertChild(1, p4);
    p1->print();

    cerr << "replace" << endl;

    p1->replaceChild( 2, p5 );
    p1->print();

    cerr << "replace" << endl;

    p1->replaceChild( 2, p3 );
//    p1->print();

    (*p1).print();
    //x(p1);
    //y(p1);

    cerr << "sub" << endl;

    p1->subChild(p2);
    p1->print();

    cerr << "sub" << endl;

    p1->subChild(1);
    p1->print();

    cerr << "sub" << endl;

    p1->subChild(0);
    p1->print();

    fprintf(stderr, "TCL : %x\n", Thread::getCurrentChangeList());

    osgEndEditCP(p1);   
    
	Thread::getCurrentChangeList()->dump();


    p1.dump();
    p2.dump();

    cerr << endl << "Attachment test" << endl;

    GeoPointsPtr pPoint;

	cerr << "GeoPoints::getClassname()=" << GeoPoints::getClassname() << endl;
	cerr << "GeoPointsPtr::getClassname()=" << GeoPointsPtr::getClassname() << endl;
	cerr << "pPoint.getClassname()=" << pPoint.getClassname() << endl;
	cerr << "(*pPoint).getClassname()=" << (*pPoint).getClassname() << endl;

    pPoint = GeoPoints::create();

    pPoint->getType().print();

    p1.dump();
    p1->addAttachment(pPoint);
    p1->print(0);

    p1->subAttachment(pPoint);
    p1->print(0);
    pPoint->print(0);

//    NewNode *pNewProto = NewNode::getStaticType().createPrototype();

    cerr << endl << "Proto test\n" << endl;

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

