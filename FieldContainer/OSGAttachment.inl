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

/** \fn const char *OSGSimpleAttachment::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGSimpleAttachment::Inherited
 *  \brief Parent type
 */

/** \typedef OSGSimpleAttachment::_field
 *  \brief Data store
 */

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

OSG_FIELD_CONTAINER_INL_DEF(OSGAttachment, OSGAttachmentPtr)

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------- size ----------------------------------*/

/*------------------------------- dump ----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSGSimpleAttachment,
                                    OSGAttachmentDescT, 
                                    OSGSimpleField)

OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSGSimpleAttachment,
                                   OSGAttachmentDescT, 
                                   OSGSimpleField)
                                  

template <class OSGAttachmentDescT>
char OSGSimpleAttachment<OSGAttachmentDescT>::cvsid[] = "@(#)$Id: $";

/** \brief NULL pointer
 */

template <class OSGAttachmentDescT>
const  OSGSimpleAttachment<OSGAttachmentDescT>::OSGPtrType 
    OSGSimpleAttachment<OSGAttachmentDescT>::OSGNullPtr;

/** \brief Attachment field description
 */

template <class OSGAttachmentDescT>
OSGFieldDescription OSGSimpleAttachment<OSGAttachmentDescT>::_desc[] = 
{
	OSGFieldDescription(
        OSGFieldType::getClassType(), 
        OSGAttachmentDescT::getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(OSGSimpleField),
        false,
        (OSGFieldAccessMethod) &OSGSimpleAttachment::getFieldPtr,
        NULL)
};

/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class OSGAttachmentDescT>
OSGFieldContainerType OSGSimpleAttachment<OSGAttachmentDescT>::_type = 
	OSGFieldContainerType(
		OSGAttachmentDescT::getTypeName(),
		"Attachment",
		OSGAttachmentDescT::getGroupName(),
		(OSGPrototypeCreateF) &OSGSimpleAttachment<
                                              OSGAttachmentDescT>::createEmpty,
		OSGAttachmentDescT::getInitMethod(),
		_desc,
		sizeof(_desc));
#else
template <class OSGAttachmentDescT>
OSGFieldContainerType OSGSimpleAttachment<OSGAttachmentDescT>::_type(
    OSGAttachmentDescT::getTypeName(),
    "Attachment",
    OSGAttachmentDescT::getGroupName(),
    (OSGPrototypeCreateF) &OSGSimpleAttachment<
                                              OSGAttachmentDescT>::createEmpty,
    OSGAttachmentDescT::getInitMethod(),
    _desc,
    sizeof(OSGFieldDescription));
#endif



/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSGSimpleAttachment,
                                 OSGAttachmentDescT,
                                 OSGPtrType)

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

template <class OSGAttachmentDescT> inline
OSGSimpleAttachment<OSGAttachmentDescT>::OSGSimpleAttachment(void) :
	Inherited(),
    _field()
{
}

/** \brief Copy Constructor
 */

template <class OSGAttachmentDescT> inline
OSGSimpleAttachment<OSGAttachmentDescT>::OSGSimpleAttachment(
                      const OSGSimpleAttachment &source) :
    Inherited(source),
    _field(source._field)
{
}

/** \brief Destructor
 */

template <class OSGAttachmentDescT> inline
OSGSimpleAttachment<OSGAttachmentDescT>::~OSGSimpleAttachment(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Returns pointer to stored field
 */

template <class OSGAttachmentDescT> inline
OSGSimpleAttachment<OSGAttachmentDescT>::OSGFieldType *
    OSGSimpleAttachment<OSGAttachmentDescT>::getFieldPtr(void)
{
    return &_field;
}

/** \brief Returns reference to the stored field
 */

template <class OSGAttachmentDescT> inline
OSGSimpleAttachment<OSGAttachmentDescT>::OSGFieldType &
    OSGSimpleAttachment<OSGAttachmentDescT>::getField(void)
{
    return _field;
}

/** \brief Returns const reference to the stored field
 */

template <class OSGAttachmentDescT> inline
const OSGSimpleAttachment<OSGAttachmentDescT>::OSGFieldType &
    OSGSimpleAttachment<OSGAttachmentDescT>::getField(void) const
{
    return _field;
}


/*------------------------------- dump ----------------------------------*/

template <class OSGAttachmentDescT> inline
void OSGSimpleAttachment<OSGAttachmentDescT>::dump(void) const
{
    SDEBUG << "Dump OSGSimpleAttachment<OSGFieldTypeT, " 
           << "OSGAttachmentDescT> NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


OSG_END_NAMESPACE

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

