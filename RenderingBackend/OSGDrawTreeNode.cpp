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

#include "OSGDrawTreeNode.h"
#include <OSGBaseFunctions.h>

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DrawTreeNode::cvsid[] = "@(#)$Id: $";

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



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

DrawTreeNode::DrawTreeNode(void) :
     Inherited   (),
    _pFirstChild (NULL),
    _pLastChild  (NULL),
    _pBrother    (NULL),
    _pState      (NULL),
    _pGeo        (NULL),
    _oMatrixStore(),
    _rScalarVal  (0.f)
{
    _oMatrixStore.first = 0;
}

/** \brief Destructor
 */

DrawTreeNode::~DrawTreeNode(void)
{
    subRefP(_pFirstChild);
    subRefP(_pBrother);
}

/*------------------------------ access -----------------------------------*/

DrawTreeNode *DrawTreeNode::getFirstChild(void)
{
    return _pFirstChild;
}

DrawTreeNode *DrawTreeNode::getLastChild(void)
{
    return _pLastChild;
}

void DrawTreeNode::addChild(DrawTreeNode *pChild)
{
    if(_pLastChild == NULL)
    {
        setRefP(_pFirstChild, pChild);
        _pLastChild  = pChild;
    }
    else
    {
        _pLastChild->setBrother(pChild);
        _pLastChild = pChild;
    }
}

void DrawTreeNode::insertFirstChild  (DrawTreeNode *pChild)
{
    if(pChild == NULL)
        return;

    if(_pFirstChild == NULL)
    {
        addChild(pChild);
    }
    else
    {
        pChild->setBrother(_pFirstChild);
        
        setRefP(_pFirstChild, pChild);
    }
    
}

void DrawTreeNode::insertChildAfter(DrawTreeNode *pCurrent, 
                                    DrawTreeNode *pChild)
{
    if(pCurrent == NULL || pChild == NULL)
        return;

    pChild  ->setBrother(pCurrent->getBrother());
    pCurrent->setBrother(pChild  );

    if(pCurrent == _pLastChild)
    {
        _pLastChild = pChild;
    }    
}

DrawTreeNode *DrawTreeNode::getBrother(void)
{
    return _pBrother;
}

void DrawTreeNode::setBrother(DrawTreeNode *pBrother)
{
    setRefP(_pBrother, pBrother);
}

void DrawTreeNode::setGeometry(Geometry *pGeo)
{
    _pGeo = pGeo;
}

Geometry *DrawTreeNode::getGeometry(void)
{
    return _pGeo;
}

void DrawTreeNode::setState(State *pState)
{
    _pState = pState;
}

State *DrawTreeNode::getState(void)
{
    return _pState;
}

void DrawTreeNode::setMatrixStore(const MatrixStore &oMatrixStore)
{
    _oMatrixStore = oMatrixStore;
}

MatrixStore &DrawTreeNode::getMatrixStore(void)
{
    return _oMatrixStore;
}

void DrawTreeNode::setScalar(Real32 rScalar)
{
    _rScalarVal = rScalar;
}

Real32 DrawTreeNode::getScalar(void)
{
    return _rScalarVal;
}

/*---------------------------- properties ---------------------------------*/
/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


