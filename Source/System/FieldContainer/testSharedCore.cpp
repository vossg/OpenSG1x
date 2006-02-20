#include <OSGConfig.h>

#include <iostream>

#include <string>
#include <map>
#include <set>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>

#include <OSGGeometry.h>
#include <OSGTextureChunk.h>
#include <OSGPolygonChunk.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

#include <OSGRefPtr.h>


OSG_USING_NAMESPACE

int main (int argc, char *argv[])
{
	for ( int i = 0; i < argc; i++ )
		std::cout << "Param " << i << ":" << argv[i] << std::endl;

    osgInit(argc, argv);
   
  	
	NodePtr planeNode1 = makePlane( 2,2, 1,1 );
	NodePtr planeNode2 = makePlane( 1,1, 1,1 );
	addRefCP( planeNode2 );
	//NodePtr planeNode2 = Node::create();
	
	if( argc >=2 && *(argv[1]) == '1' )
	{
		std::cout << "Sharing the positions..." << std::endl;
		beginEditCP( planeNode2 );
		GeometryPtr::dcast(planeNode2->getCore())->setPositions(
					GeometryPtr::dcast(planeNode1->getCore())->getPositions() );
		endEditCP( planeNode2 );
	}
	else if( argc >=2 && *(argv[1]) == '2' )
	{
		//This case crashes with Segmentation fault, see below
		std::cout << "Sharing the core..." << std::endl;
		beginEditCP( planeNode2 );
		planeNode2->setCore( planeNode1->getCore() );
		endEditCP( planeNode2 );
		std::cerr << "Core set..." << std::endl;
	}
	
	NodePtr root = Node::create();
	GroupPtr rootCore = Group::create();
	std::cerr << "Building root node..." << std::endl;
	beginEditCP(root);
	std::cerr << "setcore..." << std::endl;
	root->setCore( rootCore );
	std::cerr << "addChild..." << std::endl;
	root->addChild( planeNode1 );
	std::cerr << "addChild..." << std::endl;
	root->addChild( planeNode2 );	//Here it happens
	std::cerr << "endEditCP..." << std::endl;
	endEditCP(root);
	std::cerr << "done" << std::endl;
        
        
        // makeNode test
        
        NodePtr n1 = makeCoredNode<Geometry>();
        addRefCP(n1);
       
        GeometryPtr geo;
        NodePtr n2 = makeCoredNode<Geometry>(&geo);
        addRefCP(n2);

        PLOG << "n1 " << n1.getRefCount() << endLog;
        PLOG << "n2 " << n1.getRefCount() << endLog;
        
        // RefPtr test
        
        RefPtr<NodePtr> r1(n1),r2; // Note: r1 = n1; doesn't work
        
        PLOG << "r1 " << r1.get().getRefCount() << endLog;
        
        r2 = n2;
        
        PLOG << "r2 = n2;" << std::endl;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;
         
        r1->addChild(r2);
         
        PLOG << "r1->addChild(r2);" << std::endl;
        PLOG << "r1 " << r1.get().getRefCount() << endLog;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;
      
        r2 = r1;
        
        PLOG << "r2 = r1;" << std::endl;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;     

        {
        std::vector< RefPtr<NodePtr> > v;
        
        v.push_back(r1);
        v.push_back(r2);

        PLOG << "in vector" << endLog;
        PLOG << "r1 " << r1.get().getRefCount() << endLog;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;
        }
        
        {
        std::set< RefPtr<NodePtr> > s;
        
        s.insert(r1);
        s.insert(r2);

        PLOG << "in set" << endLog;
        PLOG << "r1 " << r1.get().getRefCount() << endLog;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;
        }
        
        if(r1 < NullFC) PLOG << "r1 < NullFC" << endLog;
        else            PLOG << "!(r1 < NullFC)" << endLog;

        if(r1 == NullFC) PLOG << "r1 == NullFC" << endLog;
        else            PLOG << "!(r1 == NullFC)" << endLog;

        if(r1 != NullFC) PLOG << "r1 != NullFC" << endLog;
        else            PLOG << "!(r1 != NullFC)" << endLog;

        if(r1)          PLOG << "r1 (unspec bool)" << endLog;
        else            PLOG << "!r1 (unspec bool)" << endLog;

        if(r1 < r2) PLOG << "r1 < r2" << endLog;
        else        PLOG << "!(r1 < r2)" << endLog;

        if(r1 == r2) PLOG << "r1 == r2" << endLog;
        else         PLOG << "!(r1 == r2)" << endLog;

        if(r1 != r2) PLOG << "r1 != r2" << endLog;
        else         PLOG << "!(r1 != r2)" << endLog;

        if(r1 < r2.get())   PLOG << "r1 < r2.get()" << endLog;
        else                PLOG << "!(r1 < r2.get())" << endLog;

        if(r1 == r2.get())  PLOG << "r1 == r2.get()" << endLog;
        else                PLOG << "!(r1 == r2.get())" << endLog;

        if(r1 != r2.get())  PLOG << "r1 != r2.get()" << endLog;
        else                PLOG << "!(r1 != r2.get())" << endLog;

        if(!r1) PLOG << "!r1" << endLog;
        else         PLOG << "!(!r1)" << endLog;


        
        r1 = r2 = NullFC;
        
        PLOG << "r1 = r2 = NullFC;" << std::endl;
        PLOG << "r1 " << r1.get().getRefCount() << endLog;
        PLOG << "r2 " << r2.get().getRefCount() << endLog;
        PLOG << "n1 " << n1.getRefCount() << endLog;
        PLOG << "n2 " << n2.getRefCount() << endLog;
          
        subRefCP(n1);
        
        PLOG << "subRefCP(n1);" << std::endl;
        PLOG << "n1 " << n1.getRefCount() << endLog;
        PLOG << "n2 " << n2.getRefCount() << endLog;
        
	return 0;
}
