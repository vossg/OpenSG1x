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

#ifndef _OSGMFSYSTYPES_H_
#define _OSGMFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGMFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG system multi fields
 *
 *  <UL>
 *  <LI> osg::MFBool
 *  <LI> osg::MFInt8
 *  <LI> osg::MFUInt8
 *  <LI> osg::MFInt16
 *  <LI> osg::MFUInt16
 *  <LI> osg::MFInt32
 *  <LI> osg::MFUInt32
 *  <LI> osg::MFInt64
 *  <LI> osg::MFUInt64
 *  <LI> osg::MFReal32
 *  <LI> osg::MFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFBool
 */

typedef MField<Bool>   MFBool;


/** \brief MFInt8
 */

typedef MField<Int8>   MFInt8;

/** \brief MFUInt8
 */

typedef MField<UInt8>  MFUInt8;


/** \brief MFInt16
 */

typedef MField<Int16>  MFInt16;

/** \brief MFUInt16
 */

typedef MField<UInt16> MFUInt16;


/** \brief MFInt32
 */

typedef MField<Int32>  MFInt32;

/** \brief MFUInt32
 */

typedef MField<UInt32> MFUInt32;


/** \brief MFInt64
 */

typedef MField<Int64>  MFInt64;

/** \brief MFUInt64
 */

typedef MField<UInt64> MFUInt64;


/** \brief MFReal32
 */

typedef MField<Real32> MFReal32;

/** \brief MFReal64
 */

typedef MField<Real64> MFReal64;

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















