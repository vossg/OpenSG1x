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

#ifndef _OSGFIELDCONTAINERPROPERTIES_H_
#define _OSGFIELDCONTAINERPROPERTIES_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerProperties.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

#ifdef __sgi
#pragma set woff 1209
#endif

/*! \ingroup GrpSystemFieldContainer
    \hideinhierarchy
 */

struct FIELDCONTAINER_ERROR
{
    OSG_PROPERTY_VIOLATION(Pointer)
    OSG_PROPERTY_VIOLATION(ConstPointer)
};

#ifdef __sgi
#pragma reset woff 1174,1209
#endif

OSG_PROPERTY_SPEC(FIELDCONTAINER_ERROR, Pointer     );
OSG_PROPERTY_SPEC(FIELDCONTAINER_ERROR, ConstPointer);

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPROPERTIES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPROPERTIES_H_ */



