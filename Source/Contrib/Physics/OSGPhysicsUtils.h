
#ifndef _OSGPHYSICSUTILS_H_
#define _OSGPHYSICSUTILS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include <OSGConfig.h>
#include <OSGContribDef.h>
#include <OSGSimpleGeometry.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGAction.h>
#include <OSGPhysicsHandler.h>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBLIB_DLLMAPPING PhysicsHandlerFinder
{
public:

    PhysicsHandlerFinder(void);

    PhysicsHandlerPtr operator() (NodePtr root);

    static PhysicsHandlerPtr find(NodePtr root);

private:

    Action::ResultE check(NodePtr& node);

    PhysicsHandlerPtr  _found;
};

class OSG_CONTRIBLIB_DLLMAPPING PhysicsGeometryFinder
{
public:

    PhysicsGeometryFinder(void);

    NodePtr operator() (NodePtr root);

    static NodePtr find(NodePtr root);

private:

    Action::ResultE check(NodePtr& node);

    NodePtr  _found;
};

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSUTILS_H_ */
