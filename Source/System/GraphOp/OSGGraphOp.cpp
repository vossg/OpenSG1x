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

#include <OSGGraphOp.h>
#include <OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

GraphOp::GraphOp(const char* name): 
    _name(name), _excludeListNodes(), _excludeListNames()
{
}

GraphOp::~GraphOp(void)
{
}

bool GraphOp::traverse(NodePtr& node)
{
    Action::ResultE res;
    res = ::traverse(node,
          osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE,
          GraphOp,
          NodePtr>(this,&GraphOp::traverseEnter),
          osgTypedMethodFunctor2ObjPtrCPtrRef<Action::ResultE,
          GraphOp,
          NodePtr,
          Action::ResultE>(this,&GraphOp::traverseLeave));

    if (res == Action::Continue) 
        return true;
    else 
        return false;
}

/*--------------------------- Exclude List --------------------------------*/

void GraphOp::addToExcludeList(NodePtr& node)
{
    if (!isInExcludeListNodes(node))
        _excludeListNodes.push_back(node);
}

void GraphOp::addToExcludeList(const std::string &name)
{
    if (!isInExcludeListNames(name))
        _excludeListNames.push_back(name);
}

void GraphOp::removeFromExcludeList(NodePtr& node)
{
    _excludeListNodes.remove(node);
}

void GraphOp::removeFromExcludeList(const std::string &name)
{
    _excludeListNames.remove(name);
}

void GraphOp::clearExcludeList(void)
{
    _excludeListNames.clear();
    _excludeListNodes.clear();
}

bool GraphOp::isInExcludeListNodes(NodePtr& node)
{
    std::list<NodePtr>::iterator list_iter;
    list_iter = std::find(_excludeListNodes.begin(),_excludeListNodes.end(),node);

    if (list_iter==_excludeListNodes.end()) 
        return false;
    else 
        return true;
}

bool GraphOp::isInExcludeListNames(const std::string &name)
{
    std::list<std::string>::iterator namelist_iter;
    namelist_iter = std::find(_excludeListNames.begin(),_excludeListNames.end(),name);

    if (namelist_iter==_excludeListNames.end()) 
        return false;
    else 
        return true;
}

bool GraphOp::isInExcludeList(NodePtr& node)
{
    if (isInExcludeListNodes(node) || (OSG::getName(node)!=NULL && isInExcludeListNames(OSG::getName(node))))
        return true;
    else
        return false;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
