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

#include "OSGQPointFieldValueLabel.h"
#include "OSGQFieldLabelFactory.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQPointFieldValueLabel.cpp,v 1.2 2003/05/10 05:28:28 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGQPOINTFIELDVALUELABEL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQPOINTFIELDVALUELABEL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

namespace
{
//    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt2s> > dummyPnt2s("Pnt2s");
    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt2f> > dummyPnt2f("Pnt2f");
    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt2d> > dummyPnt2d("Pnt2d");

    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt3f> > dummyPnt3f("Pnt3f");
    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt3d> > dummyPnt3d("Pnt3d");
    
    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt4f> > dummyPnt4f("Pnt4f");
    QLabelRegisterWrapper<QPointFieldValueLabel<Pnt4d> > dummyPnt4d("Pnt4d");
}
