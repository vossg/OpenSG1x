/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#define OSG_COMPILEVRMLOBJECTFACTORYINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLObjectType.h"
#include "OSGVRMLObjectFactory.h"
#include "OSGContainerFactoryMixin.inl"
#include "OSGVRMLNode.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLOBJECTFACTORY_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

template class OSG_VRML_DLLMAPPING 
    ContainerFactoryMixin<VRMLObjectFactoryDesc>;

template class OSG_VRML_DLLMAPPING
    PrototypeFactoryMixin<
        ContainerFactoryMixin<VRMLObjectFactoryDesc> >;

template class OSG_VRML_DLLMAPPING
    ContainerStoreFactoryMixin<
        PrototypeFactoryMixin<
            ContainerFactoryMixin<VRMLObjectFactoryDesc> > >;

template class OSG_VRML_DLLMAPPING
    ChangeListFactoryMixin<
        ContainerStoreFactoryMixin<
            PrototypeFactoryMixin<
                ContainerFactoryMixin<VRMLObjectFactoryDesc> > > >;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLObjectFactory::VRMLObjectFactory(const Char8 *szName) : 
    Inherited(szName)
{
}

VRMLObjectFactory::~VRMLObjectFactory(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

VRMLNode *VRMLObjectFactory::createNode(const Char8 *szName)
{    
    VRMLObject *pObj  = Inherited::createContainer(szName);
    VRMLNode   *pNode = dynamic_cast<VRMLNode *>(pObj);

    if(pNode == NULL)
    {
        delete pObj;
    }
    
    return pNode;
}

VRMLNode *VRMLObjectFactory::getNode(UInt32 uiNodeId)
{
    return dynamic_cast<VRMLNode *>(Inherited::getContainer(uiNodeId));
}
