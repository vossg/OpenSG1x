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

#include <GL/gl.h>

#include "OSGDirectionalLight.h"
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DirectionalLight
 *  DirectionalLight is an infinitely distant lightsource. Its only
 *  attribute is the light's direction.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DirectionalLight::cvsid[] = "@(#)$Id: $";

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
OSG::Action::ResultE DirectionalLight::DLightDrawEnter(CNodePtr &cnode, 
                                                       Action  *pAction)
{
    NodeCore         *pNC = cnode.getCPtr();
    DirectionalLight *pSC = dynamic_cast<DirectionalLight *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "DLDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}
OSG::Action::ResultE DirectionalLight::DLightDrawLeave(CNodePtr &cnode, 
                                                       Action  *pAction)
{
    NodeCore         *pNC = cnode.getCPtr();
    DirectionalLight *pSC = dynamic_cast<DirectionalLight *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "DLDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}
#endif

void DirectionalLight::initMethod (void)
{
#ifndef OSG_NOFUNCTORS

    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                DirectionalLightPtr, 
                                Action *>(&DirectionalLight::drawEnter));

    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                DirectionalLightPtr, 
                                Action *>(&DirectionalLight::drawLeave));

    RenderAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                DirectionalLightPtr, 
                                Action *>(&DirectionalLight::renderEnter));

    RenderAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                DirectionalLightPtr, 
                                Action *>(&DirectionalLight::renderLeave));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                         DirectionalLight::DLightDrawEnter));

    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                         DirectionalLight::DLightDrawLeave));

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

DirectionalLight::DirectionalLight(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

DirectionalLight::DirectionalLight(const DirectionalLight &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

DirectionalLight::~DirectionalLight(void)
{
}

/*------------------------------- set ---------------------------------------*/

void DirectionalLight::setDirection(Real32 rX, 
                                    Real32 rY, 
                                    Real32 rZ)
{
    _sfDirection.getValue().setValues(rX, rY, rZ);
}


/** \brief react to field changes
 */

void DirectionalLight::changed(BitVector, ChangeMode)
{
}

void DirectionalLight::makeChunk(void)
{
    Inherited::makeChunk();

    Vec4f dir(_sfDirection.getValue());

    dir[3] = 0;
   
    _pChunk->setPosition(dir);
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void DirectionalLight::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE DirectionalLight::drawEnter(Action * action )
{   
    if ( ! getOn() )
    	return Action::Continue;

    DrawAction *da = dynamic_cast<DrawAction *>(action);

    GLenum light = GL_LIGHT0 + da->getLightCount();
	
    LightBase::drawEnter( action );

    Vec4f dir( _sfDirection.getValue() );

    dir[3] = 0;
    glLightfv( light, GL_POSITION, dir.getValues() );
    glLightf( light, GL_SPOT_CUTOFF, 180 );

    glPopMatrix();

    return Action::Continue;
}
    
Action::ResultE DirectionalLight::drawLeave(Action * action )
{
    if ( ! getOn() )
    	return Action::Continue;

    return LightBase::drawLeave( action );
}

// generate drawtree
Action::ResultE DirectionalLight::renderEnter(Action *action)
{
    if(! getOn())
    	return Action::Continue;

    return LightBase::renderEnter(action);
}

Action::ResultE DirectionalLight::renderLeave(Action *action)
{
    if(! getOn())
    	return Action::Continue;

    return LightBase::renderLeave(action);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

