/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGQSCENEGRAPHVIEWFUNCTIONS_H_
#define _OSGQSCENEGRAPHVIEWFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQTDef.h"
#include <OSGNode.h>

OSG_BEGIN_NAMESPACE

OSG_WINDOWQTLIB_DLLMAPPING void sceneGraphViewThreadFunc (void    *pThreadArg);

OSG_WINDOWQTLIB_DLLMAPPING bool startSceneGraphViewThread(NodePtr &pRootNode );

OSG_WINDOWQTLIB_DLLMAPPING bool stopSceneGraphViewThread (void               );

OSG_END_NAMESPACE

#define OSGQSCENEGRAPHVIEWFUNCTIONS_HEADER_CVSID "@(#)$Id: OSGQSceneGraphViewFunctions.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

// #include "OSGQSceneGraphViewFunctions.inl"

#endif /* _OSGQSCENEGRAPHVIEWFUNCTIONS_H_ */
