/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

#include "OSGDeformableGeometry.h"

OSG_USING_NAMESPACE

/*! \class osg::DeformableGeometry

*/

/*----------------------- constructors & destructors ----------------------*/

DeformableGeometry::DeformableGeometry(void) :
    Inherited()
{
}

DeformableGeometry::DeformableGeometry(const DeformableGeometry &source) :
    Inherited(source)
{
}

DeformableGeometry::~DeformableGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeformableGeometry::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          DeformableGeometryPtr,
                                          CNodePtr,
                                          Action *>(&MaterialDrawable::drawActionHandler));

    IntersectAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          DeformableGeometryPtr,
                                          CNodePtr,
                                          Action *>(&Geometry::intersect));

    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          DeformableGeometryPtr,
                                          CNodePtr,
                                          Action *>(&MaterialDrawable::renderActionHandler));


}

void DeformableGeometry::adjustVolume( Volume & volume ) {
    //if (!volume.isValid())
    //    Inherited::adjustVolume(volume);
    volume.setValid(true);
    //volume.setInfinite(true); // Make infinite so we don't calculate it each frame. Doesn't work.
    volume.setEmpty(true);
    volume.extendBy(Pnt3f(1000000.0f, 1000000.0f, 1000000.0f));
    volume.extendBy(Pnt3f(-1000000.0f, -1000000.0f, -1000000.0f));
    volume.setStatic(true); // ???.
}

void DeformableGeometry::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DeformableGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DeformableGeometry NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGDeformableGeometry.cpp,v 1.3 2003/04/28 23:55:49 michael Exp $";
    static Char8 cvsid_hpp       [] = OSGDEFORMABLEGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFORMABLEGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFORMABLEGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

