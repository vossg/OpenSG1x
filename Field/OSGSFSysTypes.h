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


#ifndef _OSGSFSYSTYPES_H_
#define _OSGSFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGSFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG system single fields
 *
 *  <UL>
 *  <LI> osg::SFBool
 *  <LI> osg::SFInt8
 *  <LI> osg::SFUInt8
 *  <LI> osg::SFInt16
 *  <LI> osg::SFUInt16
 *  <LI> osg::SFInt32
 *  <LI> osg::SFUInt32
 *  <LI> osg::SFInt64
 *  <LI> osg::SFUInt64
 *  <LI> osg::SFReal32
 *  <LI> osg::SFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE


/** \brief SFBool
 */

typedef SField<Bool>   SFBool;


/** \brief SFInt8
 */

typedef SField<Int8>   SFInt8;

/** \brief SFUInt8
 */

typedef SField<UInt8>  SFUInt8;


/** \brief SFInt16
 */

typedef SField<Int16>  SFInt16;

/** \brief SFUInt16
 */

typedef SField<UInt16> SFUInt16;


/** \brief SFInt32
 */
typedef SField<Int32>  SFInt32;

/** \brief SFUInt32
 */

typedef SField<UInt32> SFUInt32;


/** \brief SFInt64
 */
typedef SField<Int64>  SFInt64;

/** \brief SFUInt64
 */

typedef SField<UInt64> SFUInt64;


/** \brief SFReal32
 */

typedef SField<Real32> SFReal32;

/** \brief SFReal64
 */

typedef SField<Real64> SFReal64;

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















