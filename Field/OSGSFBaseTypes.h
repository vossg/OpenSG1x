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

#ifndef _OSGSFBASETYPES_H_
#define _OSGSFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGSFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG base single fields
 *
 * <UL>
 * <LI> osg::SFString
 * <LI> osg::SFTime
 * <LI> osg::SFColor3f
 * <LI> osg::SFColor4f
 * <LI> osg::SFVolume
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief SFString
 */

typedef SField<String>        SFString;

/** \brief SFTime
 */

typedef SField<Time, 1>       SFTime;

/** \brief SFColor3f
 */

typedef SField<Color3f>       SFColor3f;

/** \brief SFColor4f
 */

typedef SField<Color4f>       SFColor4f;

/** \brief SFVolume
 */

typedef SField<DynamicVolume> SFVolume;

/** \brief SFBitVector
 */

typedef SField<BitVector, 1>  SFBitVector;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
