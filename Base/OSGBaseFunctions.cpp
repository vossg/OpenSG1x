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

OSG_BEGIN_NAMESPACE
static vector<InitFuncF> *osgInitFunctions   = NULL;
static vector<ExitFuncF> *osgExitFunctions   = NULL;

static vector<InitFuncF> *osgMPInitFunctions = NULL;
static vector<ExitFuncF> *osgMPExitFunctions = NULL;
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

void OSG::addExitFunction(ExitFuncF exitFunc)
{
    if(osgExitFunctions == NULL)
    {
        osgExitFunctions = new vector<ExitFuncF>(0);
    }
    
    osgExitFunctions->push_back(exitFunc);
}

void OSG::addMPInitFunction(InitFuncF initFunc)
{
    if(osgMPInitFunctions == NULL)
    {
        osgMPInitFunctions = new vector<InitFuncF>;
    }

    osgMPInitFunctions->push_back(initFunc);
}

void osg::addMPExitFunction(ExitFuncF exitFunc)
{
    if(osgMPExitFunctions == NULL)
    {
        osgMPExitFunctions = new vector<ExitFuncF>;
    }
    
    osgMPExitFunctions->push_back(exitFunc);
}

Bool OSG::osgInit(int argc, char **argv)
{
    UInt32 i;
    Bool returnValue = true;

    if(osgMPInitFunctions == NULL)
        return false;

    for(i = 0; i < osgMPInitFunctions->size(); i++)
    {
        returnValue &= (*osgMPInitFunctions)[i](argc, argv);

        if(returnValue == false)
            break;         
    }

    if(returnValue == false)
        return returnValue;

    if(osgInitFunctions == NULL)
        return returnValue;

    for(i = 0; i < osgInitFunctions->size(); i++)
    {
        returnValue &= (*osgInitFunctions)[i](argc, argv);

        if(returnValue == false)
            break;         
    }

    return returnValue;
}

Bool OSG::osgExit(void)
{
    Bool returnValue = true;

// Check it (GV)
//    Thread::getCurrentChangeList()->setReadOnly(true);

    if(osgExitFunctions != NULL)
    {
        for(Int32 i = osgExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    if(osgMPExitFunctions != NULL)
    {
        for(Int32 i = osgMPExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgMPExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    return returnValue;
}

