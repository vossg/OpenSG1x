#include <OSGConfig.h>

#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <fstream>
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
#include <OSGPointLight.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

#include <OSGSceneFileHandler.h>

#include <OSGOSGWriter.h>

OSG_USING_NAMESPACE

int main (int argc, char *argv[])
{
    for ( int i = 0; i < argc; i++ )
        std::cout << "Param " << i << ":" << argv[i] << std::endl;

    osgInit(argc, argv);

    char *inFileName  = "osgWriterInput.osg";
    char *outFileName = "osgWriterOutput.osg";
    NodePtr root;

    if( argc > 2 )
    {
        inFileName = argv[1];
        outFileName = argv[2];
        root = SceneFileHandler::the().read(inFileName);
    }
    else
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        root = makeTorus( .5, 2, 16, 16 );
    }


/*
    NamePtr pName = Name::create();

    pName->getField().getValue().assign("xxxx");

    NodePtr root = Node::create();
    root->setCore(Group::create());
    root->addAttachment(pName);
    */

    std::ofstream outFileStream( outFileName );
    if( !outFileStream )
    {
        std::cerr << "Can not open output stream to file: "
                  << outFileName << std::endl;
        return -1;
    }

    std::cerr << "STARTING PRINTOUT:" << std::endl;
    OSGWriter writer( outFileStream, 4 );
    writer.write( root );
    outFileStream.close();

    return 0;
}

