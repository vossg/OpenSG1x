#ifndef _OSGEXTERNALUPDATEHANDLER_H
#define _OSGEXTERNALUPDATEHANDLER_H

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include <OSGSimpleGeometry.h>

using namespace osg;

class OSG_SYSTEMLIB_DLLMAPPING ExternalUpdateHandler
{
public:
    virtual ~ExternalUpdateHandler() {}
    virtual void update( NodePtr& TransformNode ) = 0;
};

#endif // _OSGEXTERNALUPDATEHANDLER_H

