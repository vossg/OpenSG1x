/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGVOLUMEDRAW_H_
#define _OSGVOLUMEDRAW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGNode.h"

#include "OSGAction.h"
#include "OSGMaterial.h"

#include "OSGVolume.h"
#include "OSGBoxVolume.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                   Draw Functions                             */
/*! \{                                                                 */

#ifndef OSG_2_PREP
OSG_SYSTEMLIB_DLLMAPPING void drawVolume(const DynamicVolume  &volume);
#endif
OSG_SYSTEMLIB_DLLMAPPING void drawVolume(const BoxVolume      &volume);
OSG_SYSTEMLIB_DLLMAPPING void drawVolume(const SphereVolume   &volume);
OSG_SYSTEMLIB_DLLMAPPING void drawVolume(const FrustumVolume  &volume);
OSG_SYSTEMLIB_DLLMAPPING void drawVolume(const CylinderVolume &volume);

OSG_SYSTEMLIB_DLLMAPPING void dropVolume(DrawActionBase *action, 
                                         NodePtr node,
                                         Color3f col);

#ifndef OSG_2_PREP
OSG_SYSTEMLIB_DLLMAPPING void dropVolume(      DrawActionBase *action, 
                                         const DynamicVolume  &volume,
                                               Color3f         col    );
#else
OSG_SYSTEMLIB_DLLMAPPING void dropVolume(      DrawActionBase *action, 
                                         const BoxVolume      &volume,
                                               Color3f         col    );
#endif

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGVOLUMEDRAW_H_ */
