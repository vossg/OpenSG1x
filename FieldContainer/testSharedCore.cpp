#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <string>
#include <map>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>

#include <OSGGeometry.h>
#include <OSGTextureChunk.h>
#include <OSGPolygonChunk.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

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
	return 0;
}
