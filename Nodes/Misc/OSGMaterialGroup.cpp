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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGMaterialGroup.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MaterialGroup



*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char MaterialGroup::cvsid[] = "@(#)$Id: OSGMaterialGroup.cpp,v 1.11 2001/09/17 04:02:52 vossg Exp $";

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

/** \brief initialize the static features of the class, e.g. action callbacks
 */

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE MaterialGroup::MatGroupDrawEnter(CNodePtr &cnode, 
                                                      Action  *pAction)
{
    NodeCore      *pNC = cnode.getCPtr();
    MaterialGroup *pSC = dynamic_cast<MaterialGroup *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}

OSG::Action::ResultE MaterialGroup::MatGroupDrawLeave(CNodePtr &cnode, 
                                                      Action  *pAction)
{
    NodeCore      *pNC = cnode.getCPtr();
    MaterialGroup *pSC = dynamic_cast<MaterialGroup *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}
OSG::Action::ResultE MaterialGroup::MatGroupRenderEnter(CNodePtr &cnode, 
                                                      Action  *pAction)
{
    NodeCore      *pNC = cnode.getCPtr();
    MaterialGroup *pSC = dynamic_cast<MaterialGroup *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->renderEnter(pAction);
    }
}

OSG::Action::ResultE MaterialGroup::MatGroupRenderLeave(CNodePtr &cnode, 
                                                      Action  *pAction)
{
    NodeCore      *pNC = cnode.getCPtr();
    MaterialGroup *pSC = dynamic_cast<MaterialGroup *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->renderLeave(pAction);
    }
}
#endif

void MaterialGroup::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                MaterialGroupPtr, 
                                Action *>(&MaterialGroup::drawEnter));
    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                MaterialGroupPtr, 
                                Action *>(&MaterialGroup::drawLeave));

    RenderAction::registerEnterDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  MaterialGroupPtr, 
                                  Action *>(&MaterialGroup::renderEnter));
    RenderAction::registerLeaveDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                 CNodePtr,  
                                 MaterialGroupPtr, 
                                 Action *>(&MaterialGroup::renderLeave));
#else
    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        MaterialGroup::MatGroupDrawEnter));
    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        MaterialGroup::MatGroupDrawLeave));
    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        MaterialGroup::MatGroupRenderEnter));
    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        MaterialGroup::MatGroupRenderLeave));
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

MaterialGroup::MaterialGroup(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

MaterialGroup::MaterialGroup(const MaterialGroup &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

MaterialGroup::~MaterialGroup(void)
{
}


/** \brief react to field changes
 */

void MaterialGroup::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void MaterialGroup::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

//! DrawAction:  execute the OpenGL commands directly   
Action::ResultE MaterialGroup::drawEnter(Action * action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL && _sfMaterial.getValue() != NullFC)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())));
    }

    da->selectVisibles();
	
    return Action::Continue;
}

Action::ResultE MaterialGroup::drawLeave(Action * action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da != NULL)
    {
        da->setMaterial(NULL);
    }

    return Action::Continue;
}

//! RenderAction:  generate draw tree
Action::ResultE MaterialGroup::renderEnter(Action * action)
{
//    fprintf(stderr, "MaterialGroup::renderEnter\n");

    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL && _sfMaterial.getValue() != NullFC)
    {
        da->setMaterial(&(*(_sfMaterial.getValue())));
    }

    return Action::Continue;
}

Action::ResultE MaterialGroup::renderLeave(Action * action)
{
//    fprintf(stderr, "MaterialGroup::renderLeave\n");

    RenderAction *da = dynamic_cast<RenderAction *>(action);

    if(da != NULL)
    {
        da->setMaterial(NULL);
    }

    return Action::Continue;
}

 
/*-------------------------------------------------------------------------*\
  -  private                                                                -
  \*-------------------------------------------------------------------------*/

