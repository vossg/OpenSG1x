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

#ifndef _OSGSFVECTYPES_H_
#define _OSGSFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGVecFieldDataType.h>

/** \file OSGSFVecTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG vector and point single fields
 * 
 *  <UL>
 *  <LI> osg::SFVec2f
 *  <LI> osg::SFVec3f
 *  <LI> osg::SFVec4f
 *  <LI> osg::SFPnt2f
 *  <LI> osg::SFPnt3f
 *  <LI> osg::SFPnt4f
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief SFVec2f
 */

typedef SField<Vec2f> SFVec2f;

/** \brief SFVec3f
 */

typedef SField<Vec3f> SFVec3f;

/** \brief SFVec4f
 */

typedef SField<Vec4f> SFVec4f;

/** \brief SFPnt2f
 */

typedef SField<Pnt2f> SFPnt2f;

/** \brief SFPnt3f
 */

typedef SField<Pnt3f> SFPnt3f;

/** \brief SFPnt4f
 */

typedef SField<Pnt4f> SFPnt4f;

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
