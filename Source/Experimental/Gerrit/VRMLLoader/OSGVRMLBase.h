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

#ifndef _OSGVRMLBASE_HPP_
#define _OSGVRMLBASE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainer.h>

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEWINDOWGLUTLIB
#       define OSG_VRML_DLLMAPPING     __declspec(dllexport)
#       define OSG_VRML_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_VRML_DLLMAPPING     __declspec(dllimport)
#       define OSG_VRML_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_VRML_DLLMAPPING
#define OSG_VRML_DLLTMPLMAPPING
#endif

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

/*! \brief addRef
 *  \ingroup GrpBaseFunctions
 */

//CHECKCHECK
#ifndef __linux
template <class T> inline
void addRef(T &pObject)
{
    if(pObject != T::VSCNullPtr)
        pObject.addRef();
}
#endif

/*! \brief addRef
 *  \ingroup GrpBaseFunctions
 */

template <class T> inline
void addRef(T *pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}


/*! \brief subRef
 *  \ingroup GrpBaseFunctions
 */

//CHECKCHECK
#ifndef __linux
template <class T> inline
void subRef(T &pObject)
{
    if(pObject != T::VSCNullPtr)
        pObject.subRef();
}
#endif

/*! \brief subRef
 *  \ingroup GrpBaseFunctions
 */

template <class T> inline
void subRef(T *pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}


//CHECKCHECK
#ifndef __linux
template <class T> inline
void beginEdit(T &oT, const BitVector whichField)
{
    oT.beginEdit(whichField);
}
#endif

template <class T> inline
void beginEdit(T *pT, const BitVector whichField)
{
    pT->beginEdit(whichField);
}

//CHECKCHECK
#ifndef __linux
template <class T> inline
void endEditNoChanged(T &oT, const BitVector whichField)
{
    oT.endEdit(whichField);
}
#endif

template <class T> inline
void endEditNoChanged(T *pT, const BitVector whichField)
{
    pT->endEdit(whichField);
}

//CHECKCHECK
#if !defined(__linux)
template <class T> inline
void endEdit(T &oT, const BitVector whichField)
{
    endEditNoChanged<T>(oT, whichField);
    oT.changed(whichField, ChangedOrigin::External);
}
#endif

template <class T> inline
void endEdit(T *pT, const BitVector whichField)
{
    endEditNoChanged<T>(pT, whichField);
//CHECKCHECK
//    pT->changed(whichField, ChangedOrigin::External);
}

OSG_END_NAMESPACE

#define OSG_DEBUG_VRMLTOOSG


#endif /* _OSGVRMLNODEBASE_HPP_ */



