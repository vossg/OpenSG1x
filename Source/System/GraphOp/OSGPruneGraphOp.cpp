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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <OSGPruneGraphOp.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PruneGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
Removes nodes of size smaller than a given threshold from the scene.
*/

PruneGraphOp::PruneGraphOp(float size, Method method, const char* name)
    : GraphOp(name)
    , _size(size)
    , _method(method)
{
}

GraphOp* PruneGraphOp::create()
{
    return new PruneGraphOp(_size, _method);
}

Action::ResultE PruneGraphOp::traverseEnter(NodePtr& node)
{
    return isTooSmall(node) ? Action::Skip : Action::Continue;
}

Action::ResultE PruneGraphOp::traverseLeave(NodePtr& node, Action::ResultE res)
{
    beginEditCP(node);
    for (UInt32 i = 0; i < node->getNChildren(); ++i) {
        if (isTooSmall(node->getChild(i))) {
            node->subChild(i);
            --i;
        }
    }
    endEditCP(node);

    return res;
}

bool PruneGraphOp::isTooSmall(const NodePtr& node) {
    return getSize(node) < _size;
}

float PruneGraphOp::getSize(const NodePtr& node) {
    const DynamicVolume& dv = node->getVolume(true);
    if (_method == VOLUME) {
        return dv.getScalarVolume();
    } else if (_method == SUM_OF_DIMENSIONS) {
        Pnt3f min, max;
        dv.getBounds(min, max);
        Vec3f diff = max - min;
        return diff[0] + diff[1] + diff[2];
    } else {
        SWARNING << "Unknown size calculation method" << std::endl;
        return 0;
    }
}
