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
#include <math.h>

#define __EXTENSIONS__ 1
#include <string.h>

#include "OSGConfig.h"

#include <vector>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEBASE

#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGAspect.h"

OSG_BEGIN_NAMESPACE
static vector<InitFuncF> *osgInitFunctions = NULL;
static vector<ExitFuncF> *osgExitFunctions = NULL;
OSG_END_NAMESPACE

OSG_USING_NAMESPACE

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

OSG_BASE_DLLMAPPING 
void OSG::osgAddInitFunction(InitFuncF initFunc)
{
    if(osgInitFunctions == NULL)
    {
        osgInitFunctions = new vector<InitFuncF>;
    }

    osgInitFunctions->push_back(initFunc);
}

OSG_BASE_DLLMAPPING 
void OSG::osgAddExitFunction(ExitFuncF exitFunc)
{
    if(osgExitFunctions == NULL)
    {
        osgExitFunctions = new vector<ExitFuncF>;
    }
    
    osgExitFunctions->push_back(exitFunc);
}

OSG_BASE_DLLMAPPING 
Bool OSG::osgInit(int argc, char **argv)
{
    Bool returnValue = true;

    returnValue &= Aspect::init();
    returnValue &= ThreadManager::the()->init();

    if(osgInitFunctions == NULL)
        return returnValue;

    for(UInt32 i = 0; i < osgInitFunctions->size(); i++)
    {
        returnValue &= (*osgInitFunctions)[i](argc, argv);

        if(returnValue == false)
            break;         
    }

    return returnValue;
}

OSG_BASE_DLLMAPPING 
Bool OSG::osgExit(void)
{
    Bool returnValue = true;

    Thread::getCurrentChangeList()->setReadOnly(true);

    if(osgExitFunctions != NULL)
    {
        for(Int32 i = osgExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    ThreadManager::the()->shutdown();
    Aspect::exit();

    return returnValue;
}

