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
#define OSG_COMPILEATTACHMENTINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachment.h"
#include "OSGMFNodePtr.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE
#if defined(__sgi)

#pragma instantiate SimpleAttachment<NameAttachmentDesc>::_type
#pragma instantiate SimpleAttachment<NameAttachmentDesc>::_desc

#else

OSG_FC_DLLEXPORT_DEF      (SimpleAttachment, 
                           NameAttachmentDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/** \fn const char *Attachment::getClassname(void)
 *  \brief Classname
 */

/** \var MFFieldContainerPtr Attachment::_parents
 *  \brief Parents multifield
 */

/** \typedef Attachment::Inherited
 *  \brief Parent type
 */

/** \brief NULL attachment pointer
 */

const AttachmentPtr  OSG::NullAttachment;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const BitVector 
	Attachment::ParentsFieldMask  = (1 << Attachment::ParentsFieldId);

char Attachment::cvsid[] = "@(#)$Id: $";

/** \brief Attachment field description
 */

FieldDescription *Attachment::_desc[] = 
{
	new FieldDescription(
        MFNodePtr::getClassType(), 
        "parents", 
        OSG_FC_FIELD_IDM_DESC(ParentsField),
        false,
        (FieldAccessMethod) &Attachment::getMFParents,
        "test")
};

/** \brief Attachment type
 */

FieldContainerType Attachment::_type("Attachment",
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

OSG_FIELD_CONTAINER_DEF(Attachment, AttachmentPtr)

/*------------------------------ access -----------------------------------*/

MFFieldContainerPtr &Attachment::getParents(void)
{
    return _parents;
}

const MFFieldContainerPtr &Attachment::getParents(void) const
{
    return _parents;
}

/** \brief Returns pointer to parent field
 */

MFFieldContainerPtr *Attachment::getMFParents(void)
{
    return &_parents;
}

/** \brief Add given pointer to parent list
 */

void Attachment::addParent(FieldContainerPtr parent)
{
     addRefCP(parent);
    _parents.addValue(parent);
}

/**  \brief Sub given pointer from parent list
 */

void Attachment::subParent(FieldContainerPtr parent)
{
    MFFieldContainerPtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
         subRefCP(parent);
        _parents.erase(parentIt);
    }
}

/*--------------------------To / From Bin ------------------------------*/

UInt32 Attachment::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = 0;

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _parents.getBinSize();
    }

    return returnValue;
}

MemoryHandle Attachment::copyToBin(      MemoryHandle  pMem, 
                                   const BitVector    &whichField)
{
    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        pMem = _parents.copyToBin(pMem);
    }

    return pMem;
}

MemoryHandle Attachment::copyFromBin(      MemoryHandle  pMem, 
                                     const BitVector    &whichField)
{
    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        pMem = _parents.copyFromBin(pMem);
    }

    return pMem;
}
    

/*------------------------------- dump ------------------------------------*/

/** \brief Dump attachment contents to stderr, should be changed to use a 
 *  log stream instead
 */

void Attachment::dump(      UInt32     uiIndent, 
                      const BitVector &bvFlags) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);

    PLOG << "Attachment : " << getType().getName()
         << "("       << this << ")" << endl;

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

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Attachment::Attachment(void) :
    Inherited(),
    _parents()
{
}

/** \brief Copy Constructor 
 */

Attachment::Attachment(const Attachment &obj) :
    Inherited(obj),
    _parents()
{
}

/** \brief Destructor
 */

Attachment::~Attachment(void)
{
}

void Attachment::onDestroy(void)
{
    MFFieldContainerPtr::iterator parentIt = _parents.begin();

    while(parentIt != _parents.end())
    {
        subRefCP(*parentIt);
        parentIt++;
    }
}

void Attachment::executeSync(      FieldContainer &other,
                             const BitVector      &whichField)
{
    this->executeSyncImpl((Attachment *) &other, whichField);
}

void Attachment::executeSyncImpl(      Attachment     *pOther,
                                 const BitVector      &whichField)
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

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(ostream             &stream,
                          const AttachmentMap &amap)
{
    stream << "Attachment << NI" << endl;

    return stream;
}
