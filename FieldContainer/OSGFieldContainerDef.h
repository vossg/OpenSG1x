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


#ifndef _OSGFIELDCONTAINERDEF_H_
#define _OSGFIELDCONTAINERDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEFIELDCONTAINER
#       define OSG_FIELDCONTAINER_DLLMAPPING     __declspec(dllexport)
#       define OSG_FIELDCONTAINER_TMPLDLLMAPPING __declspec(dllexport)
#   else
#       if defined(OSG_NEW_DLLS) && (defined(OSG_COMPILEDRAWACTION)        || \
                                     defined(OSG_COMPILEACTION)            || \
                                     defined(OSG_COMPILEINTERSECTACTION)   || \
                                     defined(OSG_COMPILEFIELD)             || \
                                     defined(OSG_COMPILEIMAGE)             || \
                                     defined(OSG_COMPILELOADER)            || \
                                     defined(OSG_COMPILEMATERIAL)          || \
                                     defined(OSG_COMPILEMULTITHREADING)    || \
                                     defined(OSG_COMPILEMISC)              || \
                                     defined(OSG_COMPILELIGHT)             || \
                                     defined(OSG_COMPILEGEOMETRY)          || \
                                     defined(OSG_COMPILESTATE)             || \
                                     defined(OSG_COMPILEWINDOW)            || \
                                     defined(OSG_COMPILESYSTEMLIB))
#           define OSG_FIELDCONTAINER_DLLMAPPING     __declspec(dllexport)
#           define OSG_FIELDCONTAINER_TMPLDLLMAPPING __declspec(dllexport)
#       else
#           define OSG_FIELDCONTAINER_DLLMAPPING     __declspec(dllimport)
#           define OSG_FIELDCONTAINER_TMPLDLLMAPPING __declspec(dllimport)
#   endif
#   endif
#else
#define OSG_FIELDCONTAINER_DLLMAPPING
#define OSG_FIELDCONTAINER_TMPLDLLMAPPING
#endif

#endif /* _OSGFIELDCONTAINERDEF_H_ */
