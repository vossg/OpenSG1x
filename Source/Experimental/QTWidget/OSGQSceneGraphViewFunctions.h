

#ifndef _OSGQSCENEGRAPHVIEWFUNCTIONS_H_
#define _OSGQSCENEGRAPHVIEWFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGNode.h>

OSG_BEGIN_NAMESPACE

void sceneGraphViewThreadFunc (void    *pThreadArg);

bool startSceneGraphViewThread(NodePtr &pRootNode );

bool stopSceneGraphViewThread (void               );

OSG_END_NAMESPACE

#define OSGQSCENEGRAPHVIEWFUNCTIONS_HEADER_CVSID "@(#)$Id: OSGQSceneGraphViewFunctions.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

// #include "OSGQSceneGraphViewFunctions.inl"

#endif /* _OSGQSCENEGRAPHVIEWFUNCTIONS_H_ */
