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


/* This is a helper file for the creation of Fieldtypes/FieldContainer types
   that are to be put into a library. Due to the Windows method of doing
   libraries you have to declare the classes differently, depending on whether
   you want to add it to the library or if it should be impotred from a
   library. 
   
   As in most cases you would want to use the same header files for both cases
   there needs to be a way to change the declaration of the classes in the
   header, depending on whether the library is just being compiled or if the
   header file is being used to access the created library.
   
   This file defines two macros that fulfill this task. They are switched by
   the OSG_COMPILEMYLIBRARY define, which should be set in
   the Makefile/project options. It should always be set when the library is
   compiled, and not when the library is used. In addition the OSG_BUILD_DLL
   define should be set when a library using OpenSG is compiled.

    Please adhere to the naming conventions. If the library is called MyLibrary
    (as used in the .fcd files, see OSGNewFieldContainerLib.fcd for an
    example), this file should be called OSGMyLibraryDef.h, and the defines
    should be called as seen below.
*/

#ifndef _OSGMYLIBRARYDEF_H_
#define _OSGMYLIBRARYDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEMYLIBRARY
#       define OSG_MYLIBRARY_DLLMAPPING     __declspec(dllexport)
#       define OSG_MYLIBRARY_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_MYLIBRARY_DLLMAPPING     __declspec(dllimport)
#       define OSG_MYLIBRARY_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_MYLIBRARY_DLLMAPPING
#define OSG_MYLIBRARY_DLLTMPLMAPPING
#endif

#endif /* _OSGMYLIBRARYDEF_H_ */
