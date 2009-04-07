/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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
#include <algorithm>

#include <OSGConfig.h>

#include "OSGMultiSwitch.h"

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MultiSwitch

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiSwitch::initMethod (void)
{
    DrawAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MultiSwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&MultiSwitch::draw));

    RenderAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MultiSwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&MultiSwitch::draw));

    IntersectAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MultiSwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&MultiSwitch::intersect));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiSwitch::MultiSwitch(void) :
    Inherited()
{
}

MultiSwitch::MultiSwitch(const MultiSwitch &source) :
    Inherited(source)
{
}

MultiSwitch::~MultiSwitch(void)
{
}

/*! Sets \c _mfChoices such that it only contains those indices that correspond
    to ones in \a childMask, i.e. if \a childMask is \c 00101 (binary) children
    with indices 0 and 2 are selected.
 */
void MultiSwitch::setBitfield(const BitVector childMask)
{
    _mfChoices.clear();
    
    BitVector anchor = 1;
    for(UInt32 idx = 0; idx < 64; ++idx)
    {
        BitVector mask = anchor << idx;
        
        if(childMask & mask)
            _mfChoices.push_back(idx);
    }
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE MultiSwitch::draw(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;
    DrawActionBase  *da          = dynamic_cast<DrawActionBase *>(action);

    switch(getSwitchMode())
    {
    default:
        FWARNING(("MultiSwitch::draw: Invalid value in _sfSwitchMode.\n"));
        // fall through!
    case CHOICES:
    {
        if(_mfChoices.empty())
            returnValue = Action::Skip;

        da->useNodeList();

        //
        // Assumption: _mfChoices is sorted; see function changed
        //
        MFUInt32::const_iterator choiceIt  = _mfChoices.begin();
        MFUInt32::const_iterator choiceEnd = _mfChoices.end  ();
        UInt32                   numNodes  = da->getNNodes   ();

        for(; choiceIt != choiceEnd; ++choiceIt)
        {
            if(*choiceIt < numNodes                           &&
               da->isVisible(getCPtr(da->getNode(*choiceIt)))   )
            {
                da->addNode(da->getNode(*choiceIt));
            }
        }
    }
    break;
    case NONE:
    {
        returnValue = Action::Skip;
    }
    break;
    case ALL:
    {
        if(da->selectVisibles() == 0)
            returnValue = Action::Skip;
    }
    break;
    }

    return returnValue;
}

Action::ResultE MultiSwitch::intersect(Action *action)
{
    Action::ResultE   returnValue = Action::Continue;
    IntersectAction  *da          = dynamic_cast<IntersectAction *>(action);

    switch(getSwitchMode())
    {
    default:
        FWARNING(("MultiSwitch::intersect: Invalid value in _sfSwitchMode.\n"));
        // fall through!
    case CHOICES:
    {
        if(_mfChoices.empty())
            returnValue = Action::Skip;

        //
        // Assumption: _mfChoices is sorted; see function changed
        //
        MFUInt32::const_iterator choiceIt  = _mfChoices.begin();
        MFUInt32::const_iterator choiceEnd = _mfChoices.end  ();
        UInt32                   numNodes  = da->getNNodes   ();

        for(; choiceIt != choiceEnd; ++choiceIt)
        {
            if(*choiceIt < numNodes)
                da->addNode(da->getNode(*choiceIt));
        }
    }
    break;
    case NONE:
    {
        returnValue = Action::Skip;
    }
    break;
    case ALL:
    {
        returnValue = Action::Continue;
    }
    break;
    }

    return returnValue;
}
/*----------------------------- class specific ----------------------------*/

void MultiSwitch::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if(whichField & ChoicesFieldMask)
    {
        // sort _mfChoices and remove duplicates
        
        std::sort(_mfChoices.begin(), _mfChoices.end());
        
        _mfChoices.erase(std::unique(_mfChoices.begin(),
                                     _mfChoices.end  () ),
                         _mfChoices.end()                 );
    }
}

void MultiSwitch::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MultiSwitch NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGMultiSwitch.cpp,v 1.4 2009/04/07 17:09:31 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGMULTISWITCHBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMULTISWITCHBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMULTISWITCHFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

