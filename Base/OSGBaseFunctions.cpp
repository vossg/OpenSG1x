/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGAspect.h"

OSG_BEGIN_NAMESPACE
static vector<OSGInitFuncF> *osgInitFunctions = NULL;
static vector<OSGExitFuncF> *osgExitFunctions = NULL;
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

void OSG::osgAddInitFunction(OSGInitFuncF initFunc)
{
    if(osgInitFunctions == NULL)
    {
        osgInitFunctions = new vector<OSGInitFuncF>;
    }

    osgInitFunctions->push_back(initFunc);
}

void OSG::osgAddExitFunction(OSGExitFuncF exitFunc)
{
    if(osgExitFunctions == NULL)
    {
        osgExitFunctions = new vector<OSGExitFuncF>;
    }
    
    osgExitFunctions->push_back(exitFunc);
}

OSGBool OSG::osgInit(int argc, char **argv)
{
    OSGBool returnValue = true;

    returnValue &= OSGAspect::init();
    returnValue &= OSGThreadManager::the()->init();

    if(osgInitFunctions == NULL)
        return returnValue;

    for(OSGUInt32 i = 0; i < osgInitFunctions->size(); i++)
    {
        returnValue &= (*osgInitFunctions)[i](argc, argv);

        if(returnValue == false)
            break;         
    }

    return returnValue;
}

OSGBool OSG::osgExit(void)
{
    OSGBool returnValue = true;

    OSGThread::getCurrentChangeList()->setReadOnly(true);

    if(osgExitFunctions != NULL)
    {
        for(OSGInt32 i = osgExitFunctions->size() - 1; i >= 0; i--)
        {
            returnValue &= (*osgExitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    }

    OSGThreadManager::the()->shutdown();
    OSGAspect::exit();

    return returnValue;
}

