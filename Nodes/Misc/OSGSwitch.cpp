/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OSGConfig.h>

#include "OSGSwitch.h"

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Switch



*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Switch::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE Switch::SwitchDraw(CNodePtr &cnode, 
                                        Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Switch    *pSC = dynamic_cast<Switch *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "SWDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->draw(pAction);
    }
}
#endif

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Switch::initMethod (void)
{
#ifndef OSG_NOFUNCTORS

	DrawAction::registerEnterDefault(
        getClassType(),
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								  CNodePtr            ,
								  SwitchPtr           ,
                                  Action *            >(&Switch::draw));

	RenderAction::registerEnterDefault(
        getClassType(),
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								  CNodePtr            ,
								  SwitchPtr           ,
                                  Action *            >(&Switch::draw));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Switch::SwitchDraw));

    RenderAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Switch::SwitchDraw));

#endif
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Switch::Switch(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Switch::Switch(const Switch &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Switch::~Switch(void)
{
}


/** \brief react to field changes
 */

void Switch::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Switch::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump Switch NI" << endl;
}

    
Action::ResultE Switch::draw(Action* action)
{
	DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    da->useNodeList();

	if((getChoice() >= 0                 ) && 
       (getChoice() < action->getNNodes()))
    {
		if ( da->isVisible( action->getNode(getChoice()).getCPtr() ) )
			da->addNode(action->getNode(getChoice()));
    }
	
	return Action::Continue;
}
 
/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

