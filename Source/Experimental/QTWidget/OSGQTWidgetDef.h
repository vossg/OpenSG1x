
#ifndef _OSGQTWIDGETDEF_H_
#define _OSGQTWIDGETDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEQTEWIDGETLIB
#       define OSG_QTWIDGETLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_QTWIDGETLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_QTWIDGETLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_QTWIDGETLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_QTWIDGETLIB_DLLMAPPING
#define OSG_QTWIDGETLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGQTWIDGETDEF_H_ */
