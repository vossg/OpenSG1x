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

#include "OSGConfig.h"

#include "OSGComponentTransform.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComponentTransform



*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ComponentTransform::cvsid[] = "@(#)$Id: OSGComponentTransform.cpp,v 1.3 2001/10/15 03:10:23 vossg Exp $";

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
OSG::Action::ResultE ComponentTransform::ComponentTransformDrawEnter(CNodePtr &cnode, 
                                                           Action  *pAction)
{
    NodeCore     *pNC = cnode.getCPtr();
    ComponentTransform *pTr = dynamic_cast<ComponentTransform *>(pNC);

    if(pTr == NULL)
    {
        fprintf(stderr, "VTRDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pTr->drawEnter(pAction);
    }
}

OSG::Action::ResultE ComponentTransform::ComponentTransformDrawLeave(CNodePtr &cnode, 
                                                           Action  *pAction)
{
    NodeCore     *pNC = cnode.getCPtr();
    ComponentTransform *pTr = dynamic_cast<ComponentTransform *>(pNC);

    if(pTr == NULL)
    {
        fprintf(stderr, "VTRDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pTr->drawLeave(pAction);
    }
}
#endif

void ComponentTransform::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                ComponentTransformPtr, 
                                Action *>(&ComponentTransform::drawEnter));
    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                ComponentTransformPtr, 
                                Action *>(&ComponentTransform::drawLeave));



    RenderAction::registerEnterDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                ComponentTransformPtr, 
                                Action *>(&ComponentTransform::renderEnter));
    RenderAction::registerLeaveDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                ComponentTransformPtr, 
                                Action *>(&ComponentTransform::renderLeave));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        ComponentTransform::ComponentTransformDrawEnter));
    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        ComponentTransform::ComponentTransformDrawLeave));
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

ComponentTransform::ComponentTransform(void) :
    Inherited()
{
    _sfScale.getValue().setValues(1.f, 1.f, 1.f);         
}

/** \brief Copy Constructor
 */

ComponentTransform::ComponentTransform(const ComponentTransform &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

ComponentTransform::~ComponentTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief react to field changes
 */

void ComponentTransform::changed(BitVector which, ChangeMode)
{
    ComponentTransformPtr ptr(*this);
    if(which != MatrixFieldMask)
    {
        beginEditCP(ptr,MatrixFieldMask);
        getMatrix().setTransform(getTranslation     (),
                                 getRotation        (),
                                 getScale           (),
                                 getScaleOrientation(),
                                 getCenter          ());
        endEditCP(ptr,MatrixFieldMask);
    }
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void ComponentTransform::dump(      UInt32    uiIndent, 
                              const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

