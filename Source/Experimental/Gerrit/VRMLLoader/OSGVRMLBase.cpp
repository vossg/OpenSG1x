/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#if 0
#include <iostream>

#include <VSCLog.hpp>
#include <VSCVRMLToOSGAction.hpp>
#include <VSCVRMLWriteAction.hpp>
#include <VSCVRMLInitializeAction.hpp>
#include <VSCVRMLSensorTask.hpp>
#include <VSCVRMLRouteTask.hpp>
#include <VSCBaseFunctions.hpp>

#include <OpenSG/OSGThread.h>
#include <VSCScheduler.hpp>
#endif

OSG_USING_NAMESPACE

#if 0
void initOSGExternal(void)
{
    fprintf(stderr, "initOSGExternal\n");

    OSG::ExternalThread *pExtThread = OSG::ExternalThread::get("VSCScheduler");

    pExtThread->initialize(1);
}

VSCBool initSchedulerOSG(int &, char **)
{
    fprintf(stderr, "Init Scheduler OSG\n");

    VSCScheduler::the()->setExternalInitFunc(initOSGExternal);

    return true;
}

void VSCInitVRMLLibraryPreFactory(void)
{
    VSCSLOG << "VSCInitLibraryPreFactory : VRML" << endl;
    
    VSC::vscInitInitializeAction();
    VSC::vscInitToOpenSGAction  ();
    VSC::vscInitVRMLWriteAction ();
}

void VSCInitVRMLLibraryPostFactory(void)
{
    VSCSLOG << "VSCInitLibraryPostFactory : VRML" << endl;

    VSC::VSCVRMLSensorTask::the()->init();
    VSC::VSCVRMLRouteTask::the()->init();

    vscAddInitFunction(initSchedulerOSG);    
}
#endif

