/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDCONTAINERFUNCSIMPL_H_
#define _OSGFIELDCONTAINERFUNCSIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerPtrFuncsImpl.h
    \ingroup GrpSystemFieldContainer
    \ingroup GrpSystemFieldContainerFuncs
 */
#endif

#include <OSGSystemDef.h>
#include <OSGFieldContainerBase.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifndef OSG_INVALID_PTR_CHECK

OSG_SYSTEMLIB_DLLMAPPING
inline
void addRefCP   (const FieldContainerPtrBase &objectP);

#else

#define addRefCP(objectP) \
do \
{ \
    if(!safeAddRefCP(objectP)) \
    { \
        FFATAL(("addRefCP: invalid pointer in file '%s' line %d!\n", __FILE__, __LINE__)); \
    } \
} \
while (0)

OSG_SYSTEMLIB_DLLMAPPING
inline
bool safeAddRefCP   (const FieldContainerPtrBase &objectP);

#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifndef OSG_INVALID_PTR_CHECK

OSG_SYSTEMLIB_DLLMAPPING
inline
void subRefCP   (const FieldContainerPtrBase &objectP);

#else

#define subRefCP(objectP) \
do \
{ \
    if(!safeSubRefCP(objectP)) \
    { \
        FFATAL(("subRefCP: invalid pointer in file '%s' line %d!\n", __FILE__, __LINE__)); \
    } \
} \
while (0)

OSG_SYSTEMLIB_DLLMAPPING
inline
bool safeSubRefCP   (const FieldContainerPtrBase &objectP);

#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifndef OSG_INVALID_PTR_CHECK

OSG_SYSTEMLIB_DLLMAPPING
inline
void setRefdCP  (      FieldContainerPtrBase &objectP,
                 const FieldContainerPtrBase &newObjectP);

#else

#define setRefdCP(objectP, newObjectP) \
do \
{ \
    if(!safeSetRefdCP(objectP, newObjectP)) \
    { \
        FFATAL(("setRefdCP: invalid pointer in file '%s' line %d!\n", __FILE__, __LINE__)); \
    } \
} \
while (0)

OSG_SYSTEMLIB_DLLMAPPING
inline
bool safeSetRefdCP  (      FieldContainerPtrBase &objectP,
                 const FieldContainerPtrBase &newObjectP);

#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifndef OSG_INVALID_PTR_CHECK

OSG_SYSTEMLIB_DLLMAPPING
inline
void clearRefCP(FieldContainerPtrBase &objectP);

#else

#define clearRefCP(objectP) \
do \
{ \
    if(!safeClearRefCP(objectP)) \
    { \
        FFATAL(("clearRefCP: invalid pointer in file '%s' line %d!\n", __FILE__, __LINE__)); \
    } \
} \
while (0)

OSG_SYSTEMLIB_DLLMAPPING
inline
bool safeClearRefCP(FieldContainerPtrBase &objectP);

#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
inline
void beginEditCP(const FieldContainerPtr &objectP, 
                       BitVector         whichField = FieldBits    ::AllFields,
                       UInt32            origin     = ChangedOrigin::External);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
inline
void endEditCP  (const FieldContainerPtr &objectP, 
                       BitVector         whichField = FieldBits    ::AllFields,
                       UInt32            origin     = ChangedOrigin::External);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
inline
void changedCP  (const FieldContainerPtr &objectP, 
                       BitVector         whichField = FieldBits    ::AllFields,
                       UInt32            origin     = ChangedOrigin::External);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
inline
void endEditNotChangedCP(
    const FieldContainerPtr &objectP, 
          BitVector          whichField = FieldBits    ::AllFields,
          UInt32             origin     = ChangedOrigin::External);


// 2.x compat

template <class OutPtrT> inline
OutPtrT dynamic_fcptr_cast(const FieldContainerPtr &pPtr)
{
    return OutPtrT::dcast(pPtr);
}

template <class PtrT> inline
typename PtrT::StoredObjectType *getCPtr(PtrT &ptr)
{
    return ptr.getCPtr();
}

template <class PtrT> inline
Int32 getRefCount(const PtrT &ptr)
{
    return ptr.getRefCount();
}

template <class PtrT> inline
UInt32 getContainerId(const PtrT &objectP)
{
    return objectP.getFieldContainerId();
}

template <class PtrT> inline
void subRef(const PtrT &ptr)
{
    subRefCP(ptr);
}

template <class PtrT> inline
void addRef(const PtrT &ptr)
{
    subRefCP(ptr);
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFUNDS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINREFUNCSIMPL_H_ */
