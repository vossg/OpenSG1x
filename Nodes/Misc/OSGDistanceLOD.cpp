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

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGCamera.h>
#include <OSGRenderAction.h>

//just for debug
#include <iostream>
//just for debug

#include "OSGDistanceLOD.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DistanceLOD

This Node manages the different levels of detail available for a Geometry and decides which one should be rendered, according to the distance from the current camera. The details of the selection process are taken from VRML97 standard.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DistanceLOD::cvsid[] = "@(#)$Id: OSGDistanceLOD.cpp,v 1.12 2001/09/30 19:34:51 dirk Exp $";

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
OSG::Action::ResultE DistanceLOD::DistLODDraw(CNodePtr &cnode, 
                                              Action  *pAction)
{
    NodeCore    *pNC = cnode.getCPtr();
    DistanceLOD *pSC = dynamic_cast<DistanceLOD *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "DLDE: core NULL\n");
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

void DistanceLOD::initMethod (void)
{
#ifndef OSG_NOFUNCTORS

	DrawAction::registerEnterDefault( getClassType(),
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,
								DistanceLODPtr,
								Action*>(&DistanceLOD::draw));

	RenderAction::registerEnterDefault(getClassType(),
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,
								DistanceLODPtr,
								Action*>(&DistanceLOD::draw));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        DistanceLOD::DistLODDraw));

    RenderAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        DistanceLOD::DistLODDraw));

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

DistanceLOD::DistanceLOD(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

DistanceLOD::DistanceLOD(const DistanceLOD &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

DistanceLOD::~DistanceLOD(void)
{
}


/** \brief react to field changes
 */

void DistanceLOD::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void DistanceLOD::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump DistanceLOD NI" << endl;
}



Action::ResultE DistanceLOD::draw(Action* action)
{
	DrawActionBase* da = dynamic_cast<DrawActionBase *>(action);
	UInt32 numLevels = action->getNNodes();
	UInt32 numRanges = getMFRange()->getSize();
	UInt32 limit = osgMin( numLevels, numRanges ); 
	
	UInt32 index = -1;

	Pnt3f eyepos;
	Pnt3f objpos;

	da->getCamera()->getBeacon()->getToWorld().transform(
        Pnt3f(0.0, 0.0, 0.0), eyepos);

	da->getActNode()->getToWorld().transform(getCenter(), objpos);
		
	
	Real32 dist = osgsqrt( (eyepos[0]-objpos[0])*(eyepos[0]-objpos[0]) +
						   (eyepos[1]-objpos[1])*(eyepos[1]-objpos[1]) +
						   (eyepos[2]-objpos[2])*(eyepos[2]-objpos[2]) );
	
	da->useNodeList();
	
    if(numRanges != 0)
    {
        if( dist < getMFRange()->getValue(0) )
        {
            index = 0;
        } 
        else if( dist >= getMFRange()->getValue(numRanges-1) )
        {
            index =  limit-1;
        }
        else
        {
            UInt32 i=1;
            while( i<numRanges && 
                   !( ( getMFRange()->getValue(i-1) <= dist ) && 
                      ( dist < getMFRange()->getValue(i) ) ) )
            {
                i++;
            }
            
            index = osgMin(i, limit-1);
        } 
		
        if ( da->isVisible( action->getNode( index ).getCPtr() ) )
			da->addNode( action->getNode( index ) );
	}
	return Action::Continue;
}
    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

