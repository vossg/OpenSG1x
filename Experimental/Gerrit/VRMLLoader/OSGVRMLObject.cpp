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

#define OSG_COMPILEVRMLOBJECTINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLObject.h"
#include "OSGVRMLObjectFactory.h"

OSG_USING_NAMESPACE

template class OSG_VRML_DLLMAPPING RefCountMixin<ReflexiveContainer>;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLObjectType VRMLObject::_type(
    "VRMLObject",
    "ReflexiveContainer",
    "VRMLObjects",
    NULL,
    NULL,
    NULL,
    false);

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

VRMLObjectType &VRMLObject::getClassType(void)
{
    return _type;
}

UInt32 VRMLObject::getClassTypeId(void)
{
    return _type.getId();
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

VRMLObject::VRMLObject(void) :
 	 Inherited( ),
    _uiId     (0)

{
    _uiId = VRMLObjectFactory::the()->registerContainer(this);
}


VRMLObject::VRMLObject(const VRMLObject &source) :
	 Inherited(source),
    _uiId     (0     )
{
    _uiId = VRMLObjectFactory::the()->registerContainer(this);
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLObject::~VRMLObject(void)
{
}

/*------------------------------ access -----------------------------------*/

ReflexiveContainerType &VRMLObject::getReflexType(void)
{
    return _type;
}

const ReflexiveContainerType &VRMLObject::getReflexType(void) const
{
    return _type;
}

VRMLObjectType &VRMLObject::getType(void)
{
    return _type;
}

const VRMLObjectType &VRMLObject::getType(void) const
{
    return _type;
}

Field *VRMLObject::getElement(UInt32  uiElementId)
{
    return static_cast<Field *>(Inherited::getElement(uiElementId));
}

Field *VRMLObject::getElement(const Char8 *szElementName)
{
    return static_cast<Field *>(Inherited::getElement(szElementName));
}

void VRMLObject::setElement(Field  *, 
                            UInt32  )
{
    fprintf(stderr,
            "Default VRMLNode %s setElement called, intended ??\n",
            getType().getCName());
}

UInt32 VRMLObject::getId(void) const
{
    return _uiId;
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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLOBJECT_HEADER_CVSID;
}

