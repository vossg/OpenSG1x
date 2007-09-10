
#include <OSGConfig.h>

#include <iostream>

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
#include <OSGFieldContainer.h>
#include <OSGGroup.h>

#include <OSGGeometry.h>

#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

int main (int argc, char *argv[])
{
    osgInit(argc, argv);

    FieldContainerFactory::the()->setThrowInvalidPointerException(true);

#ifdef OSG_INVALID_PTR_CHECK
    try
    {
        NodePtr planeNode1 = makePlane(2,2, 1,1);
        NodePtr planeNode2 = planeNode1;
        
        addRefCP(planeNode1);
        subRefCP(planeNode1);

        if(planeNode1 == NullFC)
        {
            printf("planeNode1 == NullFC\n");
        }

        // now call subRefCP on a NullFC pointer!
        subRefCP(planeNode1);
        // now call subRefCP on a invalid pointer!
        subRefCP(planeNode2);

        NodePtr planeNode3 = makePlane(2,2, 1,1);
        NodePtr planeNode4 = planeNode3;

        addRefCP(planeNode3);
        subRefCP(planeNode3);

        NodeCorePtr core1 = planeNode4->getCore();

        NodeCorePtr core2 = planeNode3->getCore();
    }

    catch(InvalidPointerException &e)
    {
        printf("error: '%s'\n", e.what());
    }
#endif

    return 0;
}
