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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class StaticDescT>
vector<
  typename VRMLStaticActionMixin<StaticDescT>::VRMLActionFunctor> *
    VRMLStaticActionMixin<StaticDescT>::_pDefaultTravFunctors = NULL;

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

template <class StaticDescT> inline
void VRMLStaticActionMixin<StaticDescT>::registerDefaultTrav(
    const VRMLObjectType    &oType,
    const VRMLActionFunctor &oFunc)
{
    fprintf(stderr, "Add Trav for : %s\n", oType.getCName());

    if(_pDefaultTravFunctors == NULL)
    {
        _pDefaultTravFunctors = new FunctorStore;
    }

    while(oType.getId() >= _pDefaultTravFunctors->size())
    {
        _pDefaultTravFunctors->push_back(
            osgTypedFunctionFunctor2Ref<ActionResult,
                                        VRMLNode,
                                        VRMLAction *>(
                                            &VRMLAction::defaultTrav));
    }

    (*_pDefaultTravFunctors)[oType.getId()] = oFunc;
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

template <class StaticDescT> inline
VRMLStaticActionMixin<StaticDescT>::VRMLStaticActionMixin(void) :
	 Inherited      ( ),
    _vTravFunctors  ( ),
    _uiTraverseDepth(0)
{
    if(_pDefaultTravFunctors != NULL)
        _vTravFunctors = *_pDefaultTravFunctors;
}

//CLASSNAME::CLASSNAME(const CLASSNAME &source) :
//	Inherited(source),
//	  // TODO: initialize members
//{
//}

template <class StaticDescT> inline
VRMLStaticActionMixin<StaticDescT>::FunctorStore *
    VRMLStaticActionMixin<StaticDescT>::getDefaultTravFunctors(void)
{
    return _pDefaultTravFunctors;
}

template <class StaticDescT> inline
VRMLAction::ActionResult 
    VRMLStaticActionMixin<StaticDescT>::traverse(VRMLNode *pNode)
{
    ActionResult returnValue = Continue;

    if(pNode == NULL)
        return returnValue;

    UInt32 uiFunctorIndex = pNode->getType().getId();

    if(uiFunctorIndex < _vTravFunctors.size())
    {
        returnValue = _vTravFunctors[uiFunctorIndex].call(*pNode, this);
    }
    else if(                 _pDefaultTravFunctors != NULL &&
            uiFunctorIndex < _pDefaultTravFunctors->size()  )
    {
        while(_pDefaultTravFunctors->size() > _vTravFunctors.size())
        {
            _vTravFunctors.push_back(
                (*_pDefaultTravFunctors)[_vTravFunctors.size()]);
        }

        returnValue = _vTravFunctors[uiFunctorIndex].call(*pNode, this);
    }
    else
    {
        returnValue = defaultTrav(*pNode, this);
    }

    return returnValue;
}

template <class StaticDescT> inline
void VRMLStaticActionMixin<StaticDescT>::start(VRMLNode *)
{
}

template <class StaticDescT> inline
void VRMLStaticActionMixin<StaticDescT>::stop(VRMLNode *)
{
}


template <class StaticDescT> inline
void VRMLStaticActionMixin<StaticDescT>::start(VRMLNodeStoreIt,
                                               VRMLNodeStoreIt)
{
}

template <class StaticDescT> inline
void VRMLStaticActionMixin<StaticDescT>::stop(VRMLNodeStoreIt,
                                              VRMLNodeStoreIt)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

template <class StaticDescT> inline
VRMLStaticActionMixin<StaticDescT>::~VRMLStaticActionMixin(void)
{
}

template <class StaticDescT> inline
VRMLAction::ActionResult 
    VRMLStaticActionMixin<StaticDescT>::apply(
        VRMLNodeStoreIt nodesBeginIt,
        VRMLNodeStoreIt nodesEndIt)
{
    ActionResult returnValue = Continue;

    if(_uiTraverseDepth == 0)
    {
        start(nodesBeginIt, nodesEndIt);
    }

    ++_uiTraverseDepth;

    while(nodesBeginIt != nodesEndIt)
    {
        if(*nodesBeginIt == NULL)
        {
            SWARNING << "apply: encountered NullNode!" << endl;

            return Stop;
        }
        else
        {
            returnValue = traverse(*nodesBeginIt);

            if(returnValue != Continue)
                break;
        }

        ++nodesBeginIt;
    }

    if(_uiTraverseDepth > 0)
    {
        --_uiTraverseDepth;
    }

    if(_uiTraverseDepth == 0)
    {
        stop (nodesBeginIt, nodesEndIt);
    }

    return returnValue;
}


template <class StaticDescT> inline
VRMLAction::ActionResult 
    VRMLStaticActionMixin<StaticDescT>::apply(VRMLNode *pRoot)
{
    ActionResult returnValue = Continue;

    if(_uiTraverseDepth == 0)
    {
        start(pRoot);
    }

    ++_uiTraverseDepth;

    if(pRoot != NULL)
    {
        returnValue = traverse(pRoot);
    }

    if(_uiTraverseDepth > 0)
    {
        --_uiTraverseDepth;
    }

    if(_uiTraverseDepth == 0)
    {
        stop (pRoot);
    }

    return returnValue;
}

/*------------------------------ access -----------------------------------*/

OSG_END_NAMESPACE

#define OSGVRMLACTION_INLINE_CVSID "@(#)$Id: $"
