/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

inline bool Manipulator::hasSubHandle(const NodePtr& n)
{
    /*
    PLOG << "hasSubHandle(n=" << n << ")\n"
         << " getHandleXNode()=" << getHandleXNode() << "\n"
         << " getHandleYNode()=" << getHandleYNode() << "\n"
         << " getHandleZNode()=" << getHandleZNode() << "\n";
    */

    if( n == getHandleXNode() || n == getHandleYNode() || n == getHandleZNode() )
       return true;
    else
       return false;
}
OSG_END_NAMESPACE

#define OSGMANIPULATOR_INLINE_CVSID "@(#)$Id: OSGManipulator.inl,v 1.1 2005/06/26 12:44:40 a-m-z Exp $"

