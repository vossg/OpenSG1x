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

#include <OSGStripeGraphOp.h>
#include <OSGGeoFunctions.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StripeGraphOp
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

StripeGraphOp::StripeGraphOp(const char* name): 
    SingleTypeGraphOpGeo(name)
{
}

StripeGraphOp::~StripeGraphOp(void)
{
}

GraphOp *StripeGraphOp::create()
{
    StripeGraphOp *inst = new StripeGraphOp();
    return inst;
}

void StripeGraphOp::setParams(const std::string /*params*/)
{
    //if (params.find("bla",0)!=std::string::npos)
}

bool StripeGraphOp::travNodeEnter(NodePtr node)
{
    if (!node->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
    {
        FWARNING(("StripeGraphOp: travNodeEnter got a non-Geometry Node\n"));
        return false;
    }

    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    
    createSharedIndex(geo);
    createOptimizedPrimitives(geo);
    
    return Action::Continue;
}

bool StripeGraphOp::travNodeLeave(NodePtr)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
