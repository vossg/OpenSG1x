/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


bool ParticleBSPNode::isLeaf(void) const
{
    return _axis == Leaf;
}

Int32 ParticleBSPNode::getValue(void) const
{
    return _value;
}

Real32 ParticleBSPNode::getSplitValue(void) const
{
    return _splitvalue;
}

UInt8 ParticleBSPNode::getAxis(void) const
{
    return _axis;
}


void ParticleBSPNode::setValue(Int32 value)
{
    _value = value;
    _axis = Leaf;
}

void ParticleBSPNode::setSplit(UInt8 axis, Real32 splitvalue)
{
    _splitvalue = splitvalue;
    _axis       = axis;
}

inline bool ParticleBSPTree::created(void)
{
    return _tree.size() > 1;
}

OSG_END_NAMESPACE

#define OSGPARTICLEBSP_INLINE_CVSID "@(#)$Id: OSGParticleBSP.inl,v 1.2 2002/02/04 20:14:10 dirk Exp $"

