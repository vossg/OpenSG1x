/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#include "OSGNode.h"
#include "OSGNodeCore.h"

OSG_USING_NAMESPACE

const NodeCorePtr OSG::NullNodeCore;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const BitVector 
	NodeCore::ParentsFieldMask     = (1 << NodeCore::ParentsFieldId    );

FieldDescription *NodeCore::_desc[] = 
{
	new FieldDescription(MFNodePtr::getClassType(), 
                         "parents", 
                         OSG_FC_FIELD_IDM_DESC(ParentsField),
                         false,
                         (FieldAccessMethod) &NodeCore::getMFParents)
};

FieldContainerType NodeCore::_type("NodeCore",
                                   "FieldContainer",
                                   NULL,
                                   NULL,
                                   NULL,
                                   _desc,
                                   sizeof(_desc));


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

OSG_ABSTR_FIELD_CONTAINER_DEF(NodeCore, NodeCorePtr)

/*------------------------------ access -----------------------------------*/

MFNodePtr &NodeCore::getParents(void)
{
    return _parents;
}

const MFNodePtr &NodeCore::getParents(void) const
{
    return _parents;
}

MFNodePtr *NodeCore::getMFParents(void)
{
    return &_parents;
}

/*---------------------------- properties ---------------------------------*/

NodeCorePtr NodeCore::getPtr(void)
{
    return NodeCorePtr(*this);
}

/*-------------------------- your_category---------------------------------*/

void NodeCore::accumulateMatrix(Matrix &)
{
}

void NodeCore::adjustVolume(Volume &)
{
}

void NodeCore::invalidateVolume( void)
{
	for( int i = 0; i < _parents.size(); i++)
    {
		_parents[i]->invalidateVolume();
	}
}

/*-------------------------- assignment -----------------------------------*/

void NodeCore::dump(      UInt32     uiIndent, 
                    const BitVector &bvFlags) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);

    PLOG << "Core : " << getType().getName()
         << " " 
         << _attachmentMap.getValue().size() 
         << " attachments | "
         << this 
         << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << endl;
        
    for(i = 0; i < _parents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_parents[i])) << endl;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "]" << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << endl;

    Inherited::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

NodeCore::NodeCore(void) :
    Inherited     (),
    _parents      ()
{
	return;
}

/** \brief Copy Constructor
 */

NodeCore::NodeCore(const NodeCore &obj) :
    Inherited     (obj),
    _parents      ()
{
}

/** \brief Destructor
 */

NodeCore::~NodeCore (void )
{
}

void NodeCore::onDestroy(void)
{
/*
    MFNodePtr::iterator parentIt = _parents.begin();

    while(parentIt != _parents.end())
    {
        subRefCP(*parentIt);
        parentIt++;
    }
*/
}

void NodeCore::addParent(const NodePtr &parent)
{
     addRefCP(parent);
    _parents.addValue(parent);
}

void NodeCore::subParent(const NodePtr &parent)
{
    MFNodePtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
         subRefCP(parent);
        _parents.erase(parentIt);
    }
}

UInt32 NodeCore::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _parents.getBinSize();
    }

    return returnValue;
}

MemoryHandle NodeCore::copyToBin(      MemoryHandle  pMem, 
                                 const BitVector    &whichField)
{
    pMem = Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        pMem = _parents.copyToBin(pMem);
    }

    return pMem;
}

MemoryHandle NodeCore::copyFromBin(      MemoryHandle  pMem, 
                                   const BitVector    &whichField)
{
    pMem = Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        pMem = _parents.copyFromBin(pMem);
    }

    return pMem;
}

void NodeCore::executeSync(      FieldContainer &other,
                           const BitVector      &whichField)
{
    this->executeSyncImpl((NodeCore *) &other, whichField);
}


void NodeCore::executeSyncImpl(      NodeCore  *pOther,
                               const BitVector &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

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
