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

#ifndef _OSGSPINBOXMAPPER_H_
#define _OSGSPINBOXMAPPER_H_
#ifdef __sgi
#pragma _once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

OSG_BEGIN_NAMESPACE

#define BUILDSPINBOXMAPPER(ValueType)                    \
class QSpinBox##ValueType;                               \
                                                         \
template <>                                              \
struct SpinBoxMapper<ValueType>                          \
{                                                        \
    typedef QSpinBox##ValueType SpinBoxType;             \
}

template <class ValueTypeT>
struct OSG_WINDOWQTLIB_DLLMAPPING SpinBoxMapper
{
};

BUILDSPINBOXMAPPER(Int8);
BUILDSPINBOXMAPPER(Int16);
BUILDSPINBOXMAPPER(Int32);
BUILDSPINBOXMAPPER(Int64);

BUILDSPINBOXMAPPER(UInt8);
BUILDSPINBOXMAPPER(UInt16);
BUILDSPINBOXMAPPER(UInt32);
BUILDSPINBOXMAPPER(UInt64);

BUILDSPINBOXMAPPER(Real32);
BUILDSPINBOXMAPPER(Real64);
BUILDSPINBOXMAPPER(Real128);

#undef BUILDSPINBOXMAPPER

OSG_END_NAMESPACE

//#include "OSGSpinBoxMapper.inl"

#define OSGSPINBOXMAPPER_HEADER_CVSID "@(#)$Id: OSGSpinBoxMapper.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGSPINBOXMAPPER_H_ */
