/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
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

#include "OSGAttachment.h"

OSG_USING_NAMESPACE

/** \fn const char *OSGAttachment::getClassname(void)
 *  \brief Classname
 */

/** \var OSGMFFieldContainerPtr OSGAttachment::_parents
 *  \brief Parents multifield
 */

/** \typedef OSGAttachment::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGAttachment, OSGParentsField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGAttachment, OSGParentsField)


char OSGAttachment::cvsid[] = "@(#)$Id: $";

/** \brief Attachment field description
 */

OSGFieldDescription OSGAttachment::_desc[] = 
{
	OSGFieldDescription(
        OSGMFNodePtr::getClassType(), 
        "parents", 
        OSG_FC_FIELD_IDM_DESC(OSGParentsField),
        false,
        (OSGFieldAccessMethod) &OSGAttachment::getMFParents,
        "test")
};

/** \brief Attachment type
 */

OSGFieldContainerType OSGAttachment::_type("Attachment",
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

OSG_FIELD_CONTAINER_DEF(OSGAttachment, OSGAttachmentPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGAttachment::OSGAttachment(void) :
    Inherited(),
    _parents()
{
}

/** \brief Copy Constructor 
 */

OSGAttachment::OSGAttachment(const OSGAttachment &obj) :
    Inherited(obj),
    _parents()
{
}

/** \brief Destructor
 */

OSGAttachment::~OSGAttachment(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Returns pointer to parent field
 */

OSGMFFieldContainerPtr *OSGAttachment::getMFParents(void)
{
    return &_parents;
}

/** \brief Add given pointer to parent list
 */

void OSGAttachment::addParent(OSGFieldContainerPtr parent)
{
    _parents.addValue(parent);
}

/**  \brief Sub given pointer from parent list
 */

void OSGAttachment::subParent(OSGFieldContainerPtr parent)
{
    OSGMFFieldContainerPtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
    }
}

/*------------------------------- dump ------------------------------------*/

/** \brief Dump attachment contents to stderr, should be changed to use a 
 *  log stream instead
 */

void OSGAttachment::print(OSGUInt32 indent) const
{
    OSGUInt32 i;
    OSGUInt32 j;

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

void OSGAttachment::dump(void) const
{
    SDEBUG << "Dump OSGAttachment NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

ostream &OSG::operator <<(ostream                &stream,
                          const OSGAttachmentMap &map)
{
    stream << "OSGAttachment << NI" << endl;
}
