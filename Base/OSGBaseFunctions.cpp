/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string.h>


#include <vector>

#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"

#ifdef OSG_GV_BETA
#include <OSGFactoryController.h>
#endif

OSG_BEGIN_NAMESPACE

static vector<InitFuncF> *osgInitFunctions       = NULL;
static vector<ExitFuncF> *osgSystemExitFunctions = NULL;

static vector<InitFuncF> *osgPreMPInitFunctions  = NULL;
static vector<ExitFuncF> *osgPostMPExitFunctions = NULL;

OSG_BASE_DLLMAPPING 
SystemState GlobalSystemState = Startup;

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

void OSG::addInitFunction(InitFuncF initFunc)
{
    if(osgInitFunctions == NULL)
    {
        osgInitFunctions = new vector<InitFuncF>(0);
    }

    osgInitFunctions->push_back(initFunc);
}

void OSG::addSystemExitFunction(ExitFuncF exitFunc)
{
    if(osgSystemExitFunctions == NULL)
    {
        osgSystemExitFunctions = new vector<ExitFuncF>(0);
    }
    
    osgSystemExitFunctions->push_back(exitFunc);
}

void OSG::addPreMPInitFunction(InitFuncF initFunc)
{
    if(osgPreMPInitFunctions == NULL)
    {
        osgPreMPInitFunctions = new vector<InitFuncF>;
    }

    osgPreMPInitFunctions->push_back(initFunc);
}

void OSG::addPostMPExitFunction(ExitFuncF exitFunc)
{
    if(osgPostMPExitFunctions == NULL)
    {
        osgPostMPExitFunctions = new vector<ExitFuncF>;
    }
    
    osgPostMPExitFunctions->push_back(exitFunc);
}

bool OSG::osgInit(Int32, Char8 **)
{
    UInt32 i;
    bool   returnValue = true;

    if(osgPreMPInitFunctions != NULL)
    {
        for(i = 0; i < osgPreMPInitFunctions->size(); i++)
        {
            returnValue &= (*osgPreMPInitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    if(returnValue == false)
        return returnValue;

    returnValue &= ThreadManager::initialize();

    if(returnValue == false)
        return returnValue;

    if(osgInitFunctions != NULL)
    {
        for(i = 0; i < osgInitFunctions->size(); i++)
        {
            returnValue &= (*osgInitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }

        osgInitFunctions->clear();
    }

    if(returnValue == false)
        return returnValue;

#ifdef OSG_GV_BETA
    returnValue &= FactoryController::the()->initialize();
#endif

    GlobalSystemState = Running;

    return returnValue;
}

bool OSG::osgExit(void)
{
    bool returnValue = true;

    GlobalSystemState = Shutdown;

#ifdef OSG_GV_BETA
    returnValue &= FactoryController::the()->terminate();
#endif

    if(osgSystemExitFunctions != NULL)
    {
        for(Int32 i = osgSystemExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgSystemExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    returnValue &= ThreadManager::terminate();

    if(osgPostMPExitFunctions != NULL)
    {
        for(Int32 i = osgPostMPExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgPostMPExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    return returnValue;
}

/*! \class InitFuncWrapper
    InitFuncWrapper is a little wrapper class that allows calling an init 
    function without an associated class.
 */
 
InitFuncWrapper::InitFuncWrapper(const InitFuncF func)
{
    addInitFunction(func);
}


/*! \class StaticInitFuncWrapper
    StaticInitFuncWrapper is a little wrapper class that allows calling a 
    static init function without an associated class.
 */
 
StaticInitFuncWrapper::StaticInitFuncWrapper(const InitFuncF func)
{
    func();
}
