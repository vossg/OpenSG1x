#ifndef OSGFOX_H
#define OSGFOX_H

#ifdef __sgi
#pragma once
#endif

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEWINDOWFOXLIB
#       define OSG_WINDOWFOXLIB_DLLMAPPING                __declspec(dllexport)
#       define OSG_WINDOWFOXLIB_DLLTMPLMAPPING            __declspec(dllexport)
#   else
#       define OSG_WINDOWFOXLIB_DLLMAPPING                __declspec(dllimport)
#       define OSG_WINDOWFOXLIB_DLLTMPLMAPPING            __declspec(dllimport)
#   endif
#else
#   define OSG_WINDOWFOXLIB_DLLMAPPING
#   define OSG_WINDOWFOXLIB_DLLTMPLMAPPING
#endif

#endif
