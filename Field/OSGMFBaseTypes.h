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

#ifndef _OSGMFBASETYPES_H_
#define _OSGMFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGMFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG base multi fields
 *
 * <UL>
 * <LI> osg::MFString
 * <LI> osg::MFTime
 * <LI> osg::MFColor3f
 * <LI> osg::MFColor4f
 * <LI> osg::MFVolume
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFString
 */

typedef MField<String>        MFString;

/** \brief MFTime
 */

typedef MField<Time, 1>       MFTime;

/** \brief MFColor3f
 */

typedef MField<Color3f>       MFColor3f;

/** \brief MFColor4f
 */

typedef MField<Color4f>       MFColor4f;

/** \brief MFVolume
 */

typedef MField<DynamicVolume> MFVolume;

/** \brief MFBitVector
 */

typedef MField<BitVector, 1>  MFBitVector;

OSG_END_NAMESPACE

#endif /* _OSGMFBASETYPES_H_ */
