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

#include "OSGSFVecTypes.h"
#include "OSGMFVecTypes.h"
#include "OSGQVectorFieldValueLabel.h"
#include "OSGQFieldLabelFactory.h"
#include <OSGBaseFunctions.h>
#include <OSGVector.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQVectorFieldValueLabel.cpp,v 1.3 2003/05/19 07:36:41 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQVECTORFIELDVALUELABEL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQVECTORFIELDVALUELABEL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

namespace
{
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec2s> > dummyVec2s("Vec2s");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec2f> > dummyVec2f("Vec2f");
    
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec3d> > dummyVec3d("Vec3d");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec3f> > dummyVec3f("Vec3f");

//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4ub> > dummyVec4ub("Vec4ub");
//    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4d> > dummyVec4d("Vec4d");
    QLabelRegisterWrapper<QVectorFieldValueLabel<Vec4f> > dummyVec4f("Vec4f");
}

