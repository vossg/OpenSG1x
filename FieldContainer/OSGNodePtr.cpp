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

#include "OSGNodePtr.h"
#include "OSGThread.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: $";
    char cvsid_hpp[] = OSGNODEPTR_HEADER_CVSID;
}

/** \typedef NodePtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

//const NodePtr NodePtr::NullPtr;

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

NodePtr::NodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

NodePtr::NodePtr(const NodePtr &source) :
    Inherited(source)
{
}

/** \brief NullPtr Constructor
 */

NodePtr::NodePtr(const NullFieldContainerPtr &source) :
    Inherited(source)
{
}

/** \brief Constructor from CNodePtr
 */

NodePtr::NodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

NodePtr::~NodePtr(void)
{
}

/*------------------------------- core access -------------------------------*/

NodeCore *NodePtr::getCore(void)
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore *NodePtr::getCore(void) const
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

Node *NodePtr::operator->(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

Node *NodePtr::operator->(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

Node &NodePtr::operator *(void)
{
    return *((Node *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

Node &NodePtr::operator *(void) const
{
    return *((Node *) getElemP(Thread::getAspect()));
}

Node *NodePtr::getCPtr(void)
{
    return (Node *) getElemP(Thread::getAspect());   
}

Node *NodePtr::getCPtr(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from CNodePtr
 */

void NodePtr::operator = (const CNodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/** \brief assignment
 */

void NodePtr::operator = (const NodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/** \brief assignment
 */

void NodePtr::operator = (const NullFieldContainerPtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

NodePtr::NodePtr(const Node &source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const Node *source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const Node   *source,
                 const UInt16  uiSize,
                 const UInt16  uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \typedef CNodePtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

//char CNodePtr::cvsid[] = "@(#)$Id: $";

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

CNodePtr::CNodePtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

CNodePtr::CNodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

/** \brief Copy Constructor
 */

CNodePtr::CNodePtr(const NullFieldContainerPtr &source) :
    Inherited(source)
{
}

/** \brief Constructor from NodePtr
 */

CNodePtr::CNodePtr(const NodePtr &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

CNodePtr::~CNodePtr(void)
{
}

/*-------------------------------- node access ------------------------------*/

Node *CNodePtr::getNode(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

Node *CNodePtr::getNode(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

NodeCore *CNodePtr::operator->(void)
{
    return
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/** \brief Const arrow operator
 */

NodeCore *CNodePtr::operator->(void) const
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/** \brief Dereference operator
 */

NodeCore &CNodePtr::operator *(void)
{
    return *(
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

/** \brief Const dereference operator
 */

NodeCore &CNodePtr::operator *(void) const
{
    return *(
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

NodeCore *CNodePtr::getCPtr(void)
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore *CNodePtr::getCPtr(void) const
{
    return 
        ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment from NodePtr
 */

void CNodePtr::operator = (const NodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/** \brief assignment
 */

void CNodePtr::operator = (const CNodePtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/** \brief assignment
 */

void CNodePtr::operator = (const NullFieldContainerPtr &source)
{
	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

CNodePtr::CNodePtr(const Node &source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const Node *source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const Node   *source,
                   const UInt16  uiSize,
                   const UInt16  uiParentPos) :
    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Write FC to the given stream
 */

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream  &os,
                          const NodePtr  &fc)
{
	if(fc == NullFC)
    {
		os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
	else
    {
		os << hex << "NodePtr 0x" 
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x" 
		   << hex << (int) (&(*fc)) << dec << ")";
    }

	return os;
}

/** \brief Write FC to the given stream
 */

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream  &os,
                          const CNodePtr &fc)
{
	if(fc == NullFC)
    {
		os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
	else
    {
		os << hex << "NodePtr 0x" 
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x" 
		   << hex << (int) (&(*fc)) << dec << ")";
    }

	return os;
}

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------




