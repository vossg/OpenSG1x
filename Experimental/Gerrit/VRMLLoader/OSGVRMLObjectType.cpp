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

#define OSG_COMPILEVRMLOBJECTS

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGBaseFunctions.h"
#include "OSGVRMLObjectType.h"
#include "OSGVRMLObject.h"
#include "OSGVRMLObjectFactory.h"

OSG_USING_NAMESPACE

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

bool VRMLObjectType::initPrototype(void)
{
    bool returnValue = true;

    if(_fPrototypeCreate != NULL)
    {
        _pPrototype = _fPrototypeCreate();

        addRefP(_pPrototype);
    }

    return returnValue;
}

bool VRMLObjectType::initialize(void)
{
    if(_bReflexTypeInitialized == true)
        return _bReflexTypeInitialized;

    Inherited::initialize();

    if(_bReflexTypeInitialized == false)
        return _bReflexTypeInitialized;

    _bReflexTypeInitialized = initPrototype();
    
    PINFO << "init VSCVRMLObjectTypeType " 
          << _szName.str() 
          << " (" 
          << _bReflexTypeInitialized 
          << ")" 
          << endl;

    return _bReflexTypeInitialized;
}

void VRMLObjectType::terminate (void)
{
    clearRefP(_pPrototype);    
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLObjectType::VRMLObjectType(
    
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
          VRMLProtoCreateF      fPrototypeCreate,
          VRMLInitObjectF       fInitMethod,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable) :

	Inherited(szName,
              szParentName,
              szGroupName,
              1,
              descInsertFunc,
              bDescsAddable),

    _pPrototype      (NULL            ),
    _fPrototypeCreate(fPrototypeCreate)
{
    VRMLObjectFactory::the()->registerType(this);

	if(fInitMethod != NULL)
		fInitMethod();
}

VRMLObjectType::~VRMLObjectType(void)
{
}

/*------------------------------ access -----------------------------------*/

VRMLObject *VRMLObjectType::getPrototype(void) const
{
    return _pPrototype;
}

bool VRMLObjectType::setPrototype(VRMLObject *pPrototype)
{
	bool returnValue = false;

    if(pPrototype != NULL)
    {
        setRefP(_pPrototype, pPrototype);
		returnValue = true;
    }

	return returnValue;
}

bool VRMLObjectType::isAbstract(void) const
{
    return (_pPrototype != NULL) ? false : true;
}

VRMLObject *VRMLObjectType::createObject(void) const
{
    VRMLObject *pObject = NULL;

    if(isAbstract() == false)
    {
        pObject = _pPrototype->shallowCopy();
    }

	return pObject;
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
    static Char8 cvsid_hpp[] = OSGVRMLOBJECTTYPE_HEADER_CVSID;
}


