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

#include <GL/gl.h>

#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>

#include "OSGTransform.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Transform

The basic Transformation class. Just keeps a single matrix. For more complex 
behaviour, see its descendents. 	

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Transform::cvsid[] = "@(#)$Id: $";

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
OSG::Action::ResultE Transform::TransformDrawEnter(CNodePtr &cnode, 
                                                   Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}

OSG::Action::ResultE Transform::TransformDrawLeave(CNodePtr &cnode, 
                                                   Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}

OSG::Action::ResultE Transform::TransformIntEnter(CNodePtr &cnode, 
                                                  Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRIE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersectEnter(pAction);
    }
}

OSG::Action::ResultE Transform::TransformIntLeave(CNodePtr &cnode, 
                                                  Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    Transform *pSC = dynamic_cast<Transform *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "TRIL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersectLeave(pAction);
    }
}
#endif

void Transform::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::drawEnter));
    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::drawLeave));

    IntersectAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::intersectEnter));
    IntersectAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                TransformPtr, 
                                Action *>(&Transform::intersectLeave));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Transform::TransformDrawEnter));
    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Transform::TransformDrawLeave));

    IntersectAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Transform::TransformIntEnter));
    IntersectAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Transform::TransformIntLeave));
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

Transform::Transform(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Transform::Transform(const Transform &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Transform::~Transform(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief react to field changes
 */

void Transform::changed(BitVector, ChangeMode)
{
	invalidateVolume();
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */


void Transform::accumulateMatrix( Matrix & result )
{
    result.mult( getMatrix() );
}

void Transform::adjustVolume( Volume & volume )
{
    volume.transform( _sfMatrix.getValue() );
}

/*------------------------------- dump ----------------------------------*/

void Transform::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    
/** Actions */

// execute the OpenGL commands directly 
Action::ResultE Transform::drawEnter(Action *  )
{
    // should use the chunk, but it's not updated yet
    glPushMatrix();
    glMultMatrixf( getMatrix().getValues() );

    return Action::Continue;
}

Action::ResultE Transform::drawLeave(Action *  )
{
    glPopMatrix();

    return Action::Continue;
}

// test the ray 
// transform it into the local coordinate space
Action::ResultE Transform::intersectEnter( Action *action )
{
	IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
	Matrix m = this->getMatrix();
	m.invert();
	
	Pnt3f pos;
	Vec3f dir;
	m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
	m.multMatrixVec( ia->getLine().getDirection(), dir );
	
	ia->setLine( Line( pos, dir ), ia->getMaxDist() );

	return Action::Continue; 
}

Action::ResultE Transform::intersectLeave( Action *action )
{
	IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
	Matrix m = this->getMatrix();
	
	Pnt3f pos;
	Vec3f dir;
	m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
	m.multMatrixVec( ia->getLine().getDirection(), dir );
	
	ia->setLine( Line( pos, dir ), ia->getMaxDist() );

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

