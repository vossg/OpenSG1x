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

#ifndef _OSGMFVECTYPES_H_
#define _OSGMFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGVecFieldDataType.h>

/** \file OSGMFVecTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG vector and point multi fields
 * 
 *  <UL>
 *  <LI> osg::MFVec2f
 *  <LI> osg::MFVec3f
 *  <LI> osg::MFVec4f
 *  <LI> osg::MFVec4ub
 *  <LI> osg::MFPnt2f
 *  <LI> osg::MFPnt3f
 *  <LI> osg::MFPnt4f
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFVec2f
 */

typedef MField<Vec2f> MFVec2f;

/** \brief MFVec3f
 */

typedef MField<Vec3f> MFVec3f;

/** \brief MFVec4f
 */

typedef MField<Vec4f> MFVec4f;

/** \brief MFVec4ub
 */

typedef MField<Vec4ub> MFVec4ub;

/** \brief MFPnt3f
 */

typedef MField<Pnt2f> MFPnt2f;

/** \brief MFPnt3f
 */

typedef MField<Pnt3f> MFPnt3f;

/** \brief MFPnt3f
 */

typedef MField<Pnt4f> MFPnt4f;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
