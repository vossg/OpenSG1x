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

#if defined(WIN32_LEAN_AND_MEAN)
#include "winsock2.h"
#endif

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

void osgGetHostname(char *szBuffer, UInt32 uiSize)
{
    // get local host name
    if(getenv("OSG_HOSTNAME") != NULL)
    {
        strncpy(szBuffer, getenv("OSG_HOSTNAME"), uiSize);
    }
    else
    {
        gethostname(szBuffer, uiSize);
    }
}

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


/*! \ingroup GrpBaseBaseInitExit
    \hideinhierarchy
    .
 */

struct OSG_BASE_DLLMAPPING CompileConfig
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    CompileConfig(UInt16 major, UInt16 minor, UInt16 release,
                    bool debug, bool dll, bool mt) :
    _major(major),
    _minor(minor),
    _release(release),
    _debug(debug),
    _dll(dll),
    _mt(mt)
    {}

    bool compare(const CompileConfig& c);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Members                               */
    /*! \{                                                                 */

    UInt16  _major;
    UInt16  _minor;
    UInt16  _release;

    // Windows-specific ones
 
    bool    _mt;
    bool    _dll;
    bool    _debug;
    
    /*! \}                                                                 */
};

bool CompileConfig::compare(const CompileConfig& c)
{
    FDEBUG(("CompileConfig::compare: lib: version %d.%d.%d, %sdebug, %sdll, "
            "%smt \n",
            _major, _minor, _release, 
            _debug?"":"non-", _dll?"":"non-", _mt?"":"non-"));
    FDEBUG(("CompileConfig::compare: prog: version %d.%d.%d, %sdebug, %sdll, "
            "%smt \n",
            c._major, c._minor, c._release, 
            c._debug?"":"non-", c._dll?"":"non-", c._mt?"":"non-"));
             
    if(_major != c._major)
    {
        FFATAL(("The program is compiled against version %d headers, "
                "but the library is version %d! It's a miracle it linked, "
                "but it will not work.\n", _major, c._major));
        return true;
    }
    if(_minor != c._minor)
    {
        FWARNING(("The program is compiled against version %d.%d headers, "
                "but the library is version %d.%d! This is not recommended "
                "use at your own risk.\n", _major, _minor, c._major, c._minor));
    }
    if(_release != c._release)
    {
        FNOTICE(("The program is compiled against version %d.%d.%d headers, "
                "but the library is version %d.%d.%d! This should "
                "work fine, but if you have problems please mention it "
                "in your report.\n", _major, _minor, _release,
                c._major, c._minor, c._release));
    }
    if(_mt != c._mt)
    {
        FFATAL(("The program is linked against the %s-threaded runtime lib, "
                "but the library is linked against the %s-threaded one! "
                "This will lead to memory corruption, please link the "
                "%s-threaded lib (use /M%s%s instead of /M%s%s)!\n", 
                c._mt?"multi":"single", 
                _mt?"multi":"single", _mt?"multi":"single",
                _mt?"D":"L", _debug?"d":"", _mt?"L":"D", _debug?"d":""));
        return true;
    }
    
#ifdef WIN32
    if(_debug != c._debug)
    {
        FFATAL(("The program is linked against the %sdebug runtime lib, "
                "but the library is linked against the %sdebug one! "
                "This will lead to memory corruption, please link the "
                "%sdebug lib (use /M%s%s instead of /M%s%s)!\n", 
                c._debug?"":"non-", 
                _debug?"":"non-", _debug?"":"non-",
                _mt?"D":"L", _debug?"d":"", _mt?"D":"L", _debug?"d":""));
        return true;
    }
#endif

    return false;
}

/*! \ingroup GrpBaseBaseInitExit
 */

bool osgInit(Int32, Char8 **, UInt16 major, UInt16 minor, UInt16 release, 
             bool debug, bool dll, bool mt
)
{
    CompileConfig prog(major, minor, release, debug, dll, mt),
    lib(OSG_MAJOR_VERSION, OSG_MINOR_VERSION, 
                      OSG_RELEASE_VERSION,
#ifdef _DEBUG  
    true,
#else
    false,
#endif
#ifdef _DLL  
    true,
#else
    false,
#endif
#ifdef _MT  
    true
#else
    false
#endif
    );
    
    if(lib.compare(prog))
    {
        exit(1);
    }

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

#ifdef WIN32
    std::string pathSep(";");
#else
    std::string pathSep(":");
#endif

    char *szEnvLibs = getenv("OSG_LOAD_LIBS");

    if(szEnvLibs != NULL)
    {
        std::string tmpString(szEnvLibs);
        string_token_iterator libIt(tmpString, pathSep.c_str());

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
    SharedObjectHandler::the()->terminate();
    
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
        return std::string(*_str, _start, std::string::npos);
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
