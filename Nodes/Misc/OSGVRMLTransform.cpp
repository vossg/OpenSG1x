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

#include "OSGConfig.h"

#include "OSGVRMLTransform.h"
#include "OSGDrawAction.h"
#include "OSGRenderAction.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VRMLTransform



*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLTransform::cvsid[] = "@(#)$Id: $";

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
OSG::Action::ResultE VRMLTransform::VRMLTransformDrawEnter(CNodePtr &cnode, 
                                                           Action  *pAction)
{
    NodeCore     *pNC = cnode.getCPtr();
    VRMLTransform *pTr = dynamic_cast<VRMLTransform *>(pNC);

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

OSG::Action::ResultE VRMLTransform::VRMLTransformDrawLeave(CNodePtr &cnode, 
                                                           Action  *pAction)
{
    NodeCore     *pNC = cnode.getCPtr();
    VRMLTransform *pTr = dynamic_cast<VRMLTransform *>(pNC);

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

void VRMLTransform::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::drawEnter));
    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::drawLeave));



    RenderAction::registerEnterDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::renderEnter));
    RenderAction::registerLeaveDefault(getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::renderLeave));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        VRMLTransform::VRMLTransformDrawEnter));
    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        VRMLTransform::VRMLTransformDrawLeave));
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

VRMLTransform::VRMLTransform(void) :
    Inherited()
{
    _sfScale.getValue().setValues(1.f, 1.f, 1.f);         
}

/** \brief Copy Constructor
 */

VRMLTransform::VRMLTransform(const VRMLTransform &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

VRMLTransform::~VRMLTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief react to field changes
 */

void VRMLTransform::changed(BitVector, ChangeMode)
{
    getMatrix().setTransform(getTranslation     (),
                             getRotation        (),
                             getScale           (),
                             getScaleOrientation(),
                             getCenter          ());
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void VRMLTransform::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

