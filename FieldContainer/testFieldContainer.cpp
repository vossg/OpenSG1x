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


using namespace OSG;

void x(OSGNode *xa)
{
    fprintf(stderr, "x : \n");
    xa->print();
}

void y(const OSGNode *xa)
{
    fprintf(stderr, "y : \n");
    xa->print();
}

void initGeos(void)
{
    fprintf(stderr, "Initialize Geo\n");
}

struct OSGSimpleAttDesc
{
    typedef OSGMFVec3f OSGFieldTypeT;

    static const char *getTypeName (void) { return "GeoPoints"; }
    static const char *getFieldName(void) { return "points"; }
    static const char *getGroupName(void) { return "points"; }
    static const char *getClassName(void) { return "GeoPointsAttachment"; }
    static OSGInitContainerF getInitMethod(void) { return initGeos;}
};

typedef OSGSimpleAttachment<OSGSimpleAttDesc> OSGGeoPoints;

template class OSGSimpleAttachment<OSGSimpleAttDesc>;

typedef OSGFCPtr<OSGAttachmentPtr,  OSGGeoPoints> OSGGeoPointsPtr;

class OSGNewNode;
typedef OSGFCPtr<OSGNodePtr,  OSGNewNode> OSGNewNodePtr;

class OSGNewNode : public OSGNode
{
  public :
    
	static OSGFieldContainerType _type;

    static OSGNewNodePtr create(void)
        {
            OSGNewNodePtr fc;

#ifdef OSG_HAS_TEMPLATE_RETURNVALUES
            if(_type.getPrototype() != OSGNullFC)
                fc = _type.getPrototype()->clone().dcast<OSGNewNodePtr>();
#else
            if(_type.getPrototype() != NULL)
                _type.getPrototype()->clone().dcast(fc);
#endif
            
            return fc;
        }

    static OSGNewNodePtr createEmpty(void)
        {
            OSGNewNodePtr returnValue;

            newPtr(returnValue);

            return returnValue;
        }

    OSGNewNode(void) {} ;
    ~OSGNewNode(void) {};

    const OSGFieldContainerType &getType(void) const { return _type; }

    virtual OSGFieldContainerPtr clone(void) 
    {
            OSGNewNodePtr returnValue;

            newPtr(returnValue, this);
            
            return returnValue;    
    };

};

OSGFieldContainerType OSGNewNode::_type("NewNode", 
                                        "Node", 
                                        0,
                                        (OSGPrototypeCreateF) &OSGNewNode::createEmpty,
                                        0,
                                        NULL, 
                                        0);


int main (int argc, char **argv)
{
    
    osgInit(argc, argv);

	OSGField *pI;

	cout << "TypeCounter: "
         << " | " << sizeof(OSGFieldContainerPtr) << endl;

	OSGFieldContainerPtr pFC = 
		OSGFieldContainerFactory::the().createNode("Node");

	OSGFieldContainerPtr qFC = OSGNullFC;
	
	fprintf( stderr,"stderr output\n");
    pFC.dump();

    OSGNullFC.dump();

	cout << "Stream output" << endl;

	cout << "pFC: " ;
	cout << pFC << endl;

	cout << "OSGNullFC: " << qFC << endl;


    if(pFC != OSGNullFC)
    {
        pFC->getType().print();

//        cerr << pFC.dcast<OSGNodePtr>()->getMFChildren() << endl;

        pI = pFC->getField("children");

        cerr << pI << endl;

//        cerr << pFC.dcast<OSGNodePtr>()->getSFName() << endl;

        pI = pFC->getField("name");

        cerr << pI << endl;
    }

    cerr << endl << endl;

    OSGNodePtr  p1 = OSGNode::create();

    p1->getType().print();

    OSGFieldContainerPtr pb1 = p1;

    cerr << " N : " << p1->getType().getId() 
         << endl;

    cerr << " N : " << OSGNode::getStaticType().getId() 
         << endl;
    
    pb1->getType().print();


    OSGNodePtr p2 = OSGNode::create();
    OSGNodePtr p3 = OSGNode::create();
    OSGNodePtr p4 = OSGNode::create();
    OSGNodePtr p5 = OSGNode::create();

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
    x(p1);
    y(p1);

    cerr << "sub" << endl;

    p1->subChild(p2);
    p1->print();

    cerr << "sub" << endl;

    p1->subChild(1);
    p1->print();

    cerr << "sub" << endl;

    p1->subChild(0);
    p1->print();

    fprintf(stderr, "TCL : %x\n", OSGThread::getCurrentChangeList());

    osgEndEditCP(p1);   
    
	OSGThread::getCurrentChangeList()->dump();


    p1.dump();
    p2.dump();

    cerr << endl << "Attachment test" << endl;

    OSGGeoPointsPtr pPoint;

	cerr << "OSGGeoPoints::getClassname()=" << OSGGeoPoints::getClassname() << endl;
	cerr << "OSGGeoPointsPtr::getClassname()=" << OSGGeoPointsPtr::getClassname() << endl;
	cerr << "pPoint.getClassname()=" << pPoint.getClassname() << endl;
	cerr << "(*pPoint).getClassname()=" << (*pPoint).getClassname() << endl;

    pPoint = OSGGeoPoints::create();

    pPoint->getType().print();

    p1.dump();
    p1->addAttachment(pPoint);
    p1->print(0);

    p1->subAttachment(pPoint);
    p1->print(0);
    pPoint->print(0);

//    OSGNewNode *pNewProto = OSGNewNode::getStaticType().createPrototype();

    cerr << endl << "Proto test\n" << endl;

    OSGNewNodePtr newNodeP = OSGNewNode::create();
    OSGNodePtr    nodeP    = OSGNode::create();

    nodeP->getType().print();
    newNodeP->getType().print();

    OSGNewNode *np = new OSGNewNode();
//    OSGNode *np = &(*nodeP);

    OSGNode::getStaticType().setPrototype(newNodeP);

    OSGNodePtr    nodeP1    = OSGNode::create();
    nodeP1->getType().print();

    if(! OSGNullFC)
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

    nodeP1 = OSGNullNode;

    nodeP1.dump();

    return 0;
}

