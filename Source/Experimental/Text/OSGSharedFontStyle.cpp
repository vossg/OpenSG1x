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

#include "OSGSharedFontStyle.h"

OSG_USING_NAMESPACE

/*! \class osg::SharedFontStyle

*/

/*----------------------- constructors & destructors ----------------------*/

SharedFontStyle::SharedFontStyle(void) :
    Inherited()
{
}

SharedFontStyle::SharedFontStyle(const SharedFontStyle &source) :
    Inherited(source)
{
}

SharedFontStyle::~SharedFontStyle(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SharedFontStyle::initMethod (void)
{
}

void SharedFontStyle::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SharedFontStyle::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SharedFontStyle NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.17 2002/12/04 14:22:22 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSHAREDFONTSTYLEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHAREDFONTSTYLEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHAREDFONTSTYLEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

