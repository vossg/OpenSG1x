
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

    for(UInt32 i=0;i<20;++i)
    {
        NodePtr planeNode = makePlane(2,2, 1,1);
        addRefCP(planeNode);
        subRefCP(planeNode);

#ifdef OSG_INVALID_PTR_CHECK
        // now call subRefCP on a invalid pointer!
        subRefCP(planeNode);
#endif
    }

    NodePtr planeNode = makePlane(2,2, 1,1);
    addRefCP(planeNode);
    subRefCP(planeNode);

    return 0;
}
