/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGDrawable.h"

OSG_USING_NAMESPACE

/*! \class osg::Drawable

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Drawable::Drawable(void) :
    Inherited()
{
}

//! Copy Constructor

Drawable::Drawable(const Drawable &source) :
    Inherited(source)
{
}

//! Destructor

Drawable::~Drawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Drawable::initMethod (void)
{
}

//! react to field changes

void Drawable::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void Drawable::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Drawable NI" << endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGDrawable.cpp,v 1.1 2002/09/25 16:46:16 jbehr Exp $";
    static Char8 cvsid_hpp       [] = OSGDRAWABLEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDRAWABLEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDRAWABLEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

