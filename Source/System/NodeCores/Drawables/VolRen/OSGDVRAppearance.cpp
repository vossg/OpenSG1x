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

#include "OSGDVRAppearance.h"

OSG_USING_NAMESPACE


/*! \class osg::DVRAppearance
    Appearance used for the OpenSG direct volume rendering module. It
    represents the volume data to be rendered as long as some other visual
    parameters like transfer function or normal for shading. 
 */

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRAppearance::DVRAppearance(void) :
    Inherited()
{
}

//! Copy Constructor
DVRAppearance::DVRAppearance(const DVRAppearance &source) :
    Inherited(source)
{
}

//! Destructor
DVRAppearance::~DVRAppearance(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRAppearance::initMethod (void)
{
}

//! react to field changes
void DVRAppearance::changed(BitVector whichField, UInt32 origin)
{ 
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRAppearance::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DVRAppearance NI" << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGDVRAPPEARANCE_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRAPPEARANCE_INLINE_CVSID;
}
