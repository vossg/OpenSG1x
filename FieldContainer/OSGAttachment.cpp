/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEFIELDCONTAINER
#define OSG_COMPILEATTACHMENTINST

#include "OSGAttachment.h"

OSG_USING_NAMESPACE

#if defined(__sgi)

#pragma instantiate SimpleAttachment<NameAttachmentDesc>::_type
#pragma instantiate SimpleAttachment<NameAttachmentDesc>::_desc

#else

OSG_FC_DLLEXPORT_DEF      (SimpleAttachment, 
                           NameAttachmentDesc, 
                           OSG_FIELDCONTAINER_TMPLDLLMAPPING)

#endif

/** \fn const char *Attachment::getClassname(void)
 *  \brief Classname
 */

/** \var MFFieldContainerPtr Attachment::_parents
 *  \brief Parents multifield
 */

/** \typedef Attachment::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(Attachment, ParentsField)

OSG_FC_LAST_FIELD_IDM_DEF (Attachment, ParentsField)


char Attachment::cvsid[] = "@(#)$Id: $";

/** \brief Attachment field description
 */

FieldDescription Attachment::_desc[] = 
{
	FieldDescription(
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
    _parents.addValue(parent);
}

/**  \brief Sub given pointer from parent list
 */

void Attachment::subParent(FieldContainerPtr parent)
{
    MFFieldContainerPtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
    }
}

/*------------------------------- dump ------------------------------------*/

/** \brief Dump attachment contents to stderr, should be changed to use a 
 *  log stream instead
 */

void Attachment::print(UInt32 indent) const
{
    UInt32 i;
    UInt32 j;

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    getType().print();

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    fprintf(stderr, "NCParents : \n");

    for(i = 0; i < _parents.size(); i++)
    {
        for(j = 0; j < indent + 1; j++)
            fprintf(stderr, " ");

        _parents[i].dump();
    }
}

void Attachment::dump(void) const
{
    SDEBUG << "Dump Attachment NI" << endl;
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

OSG_FIELDCONTAINER_DLLMAPPING
ostream &OSG::operator <<(ostream                &stream,
                          const AttachmentMap &map)
{
    stream << "Attachment << NI" << endl;

    return stream;
}
