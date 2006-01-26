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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

#include <string.h>


#include <vector>

#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGSharedObjectHandler.h"
#include "OSGFileSystem.h"

#ifdef OSG_GV_BETA
#include <OSGFactoryController.h>
#endif

OSG_BEGIN_NAMESPACE

static std::vector<InitFuncF>    *osgInitFunctions       = NULL;
static std::vector<ExitFuncF>    *osgSystemExitFunctions = NULL;

static std::vector<InitFuncF>    *osgPreMPInitFunctions  = NULL;
static std::vector<ExitFuncF>    *osgPostMPExitFunctions = NULL;

static std::vector<std::string>  *osgPreloadSharedObject = NULL;

/*! \ingroup GrpBaseBaseInitExit
 */

OSG_BASE_DLLMAPPING 
SystemState GlobalSystemState = Startup;

/*---------------------------------------------------------------------*/
/*! \name add init functions                                           */
/*! \{                                                                 */

/*! addInitFunction, function called by osgInit after the
    multithreading is initialized and after dynamically loading 
    a shared object
    \ingroup GrpBaseBaseInitExit
 */

void addInitFunction(InitFuncF initFunc)
{
    if(osgInitFunctions == NULL)
    {
        osgInitFunctions = new std::vector<InitFuncF>(0);
    }

    osgInitFunctions->push_back(initFunc);
}

/*! addMPInitFunction, function called by osgInit before
    the multithreading is initialized.
    \ingroup GrpBaseBaseInitExit
 */

void addPreMPInitFunction(InitFuncF initFunc)
{
    if(osgPreMPInitFunctions == NULL)
    {
        osgPreMPInitFunctions = new std::vector<InitFuncF>;
    }

    osgPreMPInitFunctions->push_back(initFunc);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name add exit function                                            */
/*! \{                                                                 */

/*! addSystemExitFunction, function called by osgExit before
    multithreading is termininated
   \ingroup GrpBaseBaseInitExit
 */

void addSystemExitFunction(ExitFuncF exitFunc)
{
    if(osgSystemExitFunctions == NULL)
    {
        osgSystemExitFunctions = new std::vector<ExitFuncF>(0);
    }
    
    osgSystemExitFunctions->push_back(exitFunc);
}

/*! addPostMPExitFunction, function called by osgExit after
    multithreading is terminated
    \ingroup GrpBaseBaseInitExit
 */

void addPostMPExitFunction(ExitFuncF exitFunc)
{
    if(osgPostMPExitFunctions == NULL)
    {
        osgPostMPExitFunctions = new std::vector<ExitFuncF>;
    }
    
    osgPostMPExitFunctions->push_back(exitFunc);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name init / exit                                                  */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseInitExit
 */

void preloadSharedObject(const Char8 *szName)
{
    if(osgPreloadSharedObject == NULL)
    {
        osgPreloadSharedObject = new std::vector<std::string>;
    }

    std::string tmpString(szName);

    osgPreloadSharedObject->push_back(tmpString);
}

/*! \ingroup GrpBaseBaseInitExit
 */

static void osgExitWrapper(void)
{
    osgExit();
}

/*! \ingroup GrpBaseBaseInitExit
 */

bool osgInit(Int32, Char8 **)
{
    // without it floats could be written as "1,456" ...
    setlocale(LC_NUMERIC, "English");
    
    UInt32 i;
    bool   returnValue = true;

    returnValue = SharedObjectHandler::the()->initialize();

    if(osgPreloadSharedObject != NULL)
    {
        for(UInt32 i = 0; i < osgPreloadSharedObject->size(); ++i)
        {
            SharedObjectHandler::the()->getOSGSharedObject(
                (*osgPreloadSharedObject)[i].c_str());
        }
    }

    char *szEnvLibs = getenv("OSG_LOAD_LIBS");

    if(szEnvLibs != NULL)
    {
        std::string tmpString(szEnvLibs);
        string_token_iterator libIt(tmpString, ":");

        string_token_iterator libEnd;

        while(libIt != libEnd)
        {
            SharedObjectHandler::the()->getOSGSharedObject(
                (*libIt).c_str());

            ++libIt;
        }
    }

    const char *szEnvPlugins       = getenv("OSG_PLUGIN_PATH");
    const char *szEnvPluginPattern = getenv("OSG_PLUGIN_PATTERN");

    if(szEnvPlugins != NULL)
    {
        if(szEnvPluginPattern == NULL)
        {
            szEnvPluginPattern = PluginPattern;
        }

        FINFO(("Get Plugins %s from %s\n", 
               szEnvPluginPattern,
               szEnvPlugins));

        std::vector<Char8 *> *pPlugins = 
            Directory::getEntries(szEnvPlugins, szEnvPluginPattern);

        if(pPlugins != NULL)
        {
            std::string szPluginName;

            for(UInt32 i = 0; i < pPlugins->size(); ++i)
            {
                if((*pPlugins)[i][0] == '.')
                {
                    if((*pPlugins)[i][1] == '\0')
                    {
                        continue;
                    }
                    else if((*pPlugins)[i][1] == '.' &&
                            (*pPlugins)[i][2] == '\0')
                    {
                        continue;
                    }
                }

                szPluginName.assign(szEnvPlugins);
                szPluginName += '/';
                szPluginName += (*pPlugins)[i];

                FINFO(("Loading plugin %s\n", 
                       szPluginName.c_str()));

                SharedObjectHandler::the()->getSharedObject(
                    szPluginName.c_str());
            }
        }

        delete pPlugins;
    }

    SharedObjectHandler::the()->dump();

    if(returnValue == false)
        return returnValue;

    if(osgPreMPInitFunctions != NULL)
    {
        for(i = 0; i < osgPreMPInitFunctions->size(); i++)
        {
            returnValue &= (*osgPreMPInitFunctions)[i]();
            
            if(returnValue == false)
                break;         
        }
    
        osgPreMPInitFunctions->clear();
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

    atexit(osgExitWrapper);
    
    return returnValue;
}

/*! \ingroup GrpBaseBaseInitExit
 */

bool osgExit(void)
{
    bool returnValue = true;

    if(GlobalSystemState != Running)
        return true;
        
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

/*! \}                                                                 */

OSG_END_NAMESPACE


OSG_USING_NAMESPACE


InitFuncWrapper::InitFuncWrapper(const InitFuncF func)
{
    addInitFunction(func);
}


 
StaticInitFuncWrapper::StaticInitFuncWrapper(const InitFuncF func)
{
    func();
}


/*! String tokenizer
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
    
    Based on code by Daniel Andersson
    from http://www.codeproject.com/string/stringsplitter.asp

    Useable to iterate over tokens in a std::string, separated by a specifiable
    set of separator characters.
 */

string_token_iterator::string_token_iterator() : _str(0), _start(0), _end(0) 
{
}
  
string_token_iterator::string_token_iterator(const std::string &str, 
                                             const char        *separator) :
        _separator(separator),
        _str(&str),
        _end(0)
{
    find_next();
}
  
string_token_iterator::string_token_iterator(const string_token_iterator & rhs) :
        _separator(rhs._separator),
        _str(rhs._str),
        _start(rhs._start),
        _end(rhs._end)
{
}

string_token_iterator & string_token_iterator::operator++()
{
    find_next();
    return *this;
}

string_token_iterator string_token_iterator::operator++(int)
{
    string_token_iterator temp(*this);
    ++(*this);
    return temp;
}

std::string string_token_iterator::operator*() const
{
    if(_end == std::string::npos)
    {
        return std::string(*_str, _start);
    }
    else
    {
        return std::string(*_str, _start, _end - _start);
    }
}

bool string_token_iterator::operator==(const string_token_iterator & rhs) const
{
    return (rhs._str == _str && rhs._start == _start && rhs._end == _end);
}

bool string_token_iterator::operator!=(const string_token_iterator & rhs) const
{
    return !(rhs == *this);
}

void string_token_iterator::find_next(void)
{
    _start = _str->find_first_not_of(_separator, _end);
    // Apparently some STL implementations don't do npos !?!
    if(_start == std::string::npos || _start >= _str->length())
    {
        _start = _end = 0;
        _str = 0;
        return;
    }

    _end = _str->find_first_of(_separator, _start);
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBASEFUNCTIONS_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGBASEFUNCTIONS_INLINE_CVSID;
}
