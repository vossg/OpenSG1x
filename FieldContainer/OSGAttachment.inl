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

#include <OSGFieldFactory.h>

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

OSG_FIELD_CONTAINER_INL_DEF(Attachment, AttachmentPtr)

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


OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(SimpleAttachment,
                                    AttachmentDescT, 
                                    SimpleField)

OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(SimpleAttachment,
                                   AttachmentDescT, 
                                   SimpleField)
                                  

template <class AttachmentDescT>
char SimpleAttachment<AttachmentDescT>::cvsid[] = "@(#)$Id: $";

/** \brief NULL pointer
 */

template <class AttachmentDescT>
const  SimpleAttachment<AttachmentDescT>::PtrType 
    SimpleAttachment<AttachmentDescT>::NullPtr;

/** \brief Attachment field description
 */

template <class AttachmentDescT>
FieldDescription SimpleAttachment<AttachmentDescT>::_desc[] = 
{
	FieldDescription(
        FieldType::getClassType(), 
        AttachmentDescT::getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(SimpleField),
        false,
        (FieldAccessMethod) &SimpleAttachment::getFieldPtr,
        NULL)
};

/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class AttachmentDescT>
FieldContainerType SimpleAttachment<AttachmentDescT>::_type = 
	FieldContainerType(
		AttachmentDescT::getTypeName(),
		"Attachment",
		AttachmentDescT::getGroupName(),
		(PrototypeCreateF) &SimpleAttachment<
                                              AttachmentDescT>::createEmpty,
		AttachmentDescT::getInitMethod(),
		_desc,
		sizeof(_desc));
#else
template <class AttachmentDescT>
FieldContainerType SimpleAttachment<AttachmentDescT>::_type(
    AttachmentDescT::getTypeName(),
    "Attachment",
    AttachmentDescT::getGroupName(),
    (PrototypeCreateF) &SimpleAttachment<
                                              AttachmentDescT>::createEmpty,
    AttachmentDescT::getInitMethod(),
    _desc,
    sizeof(FieldDescription));
#endif



/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

OSG_FIELD_CONTAINER_INL_TMPL_DEF(SimpleAttachment,
                                 AttachmentDescT,
                                 PtrType)

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

/*------------------------------ access -----------------------------------*/

/** \brief Returns pointer to stored field
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::FieldType *
    SimpleAttachment<AttachmentDescT>::getFieldPtr(void)
{
    return &_field;
}

/** \brief Returns reference to the stored field
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::FieldType &
    SimpleAttachment<AttachmentDescT>::getField(void)
{
    return _field;
}

/** \brief Returns const reference to the stored field
 */

template <class AttachmentDescT> inline
const SimpleAttachment<AttachmentDescT>::FieldType &
    SimpleAttachment<AttachmentDescT>::getField(void) const
{
    return _field;
}


/*------------------------------- dump ----------------------------------*/

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::dump(void) const
{
    SDEBUG << "Dump SimpleAttachment<FieldTypeT, " 
           << "AttachmentDescT> NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::SimpleAttachment(void) :
	Inherited(),
    _field()
{
}

/** \brief Copy Constructor
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::SimpleAttachment(
                      const SimpleAttachment &source) :
    Inherited(source),
    _field(source._field)
{
}

/** \brief Destructor
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::~SimpleAttachment(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


template <class AttachmentDescT> 
char DynFieldAttachment<AttachmentDescT>::cvsid[] = "@(#)$Id: $";

/** \brief NULL pointer
 */

template <class AttachmentDescT> 
const  DynFieldAttachment<AttachmentDescT>::PtrType 
    DynFieldAttachment<AttachmentDescT>::NullPtr;

/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class AttachmentDescT> 
FieldContainerType SynFieldAttachment<AttachmentDescT>::_type = 
	FieldContainerType(
		AttachmentDescT::getTypeName(),
		"Attachment",
		NULL,
		(PrototypeCreateF) &DynFieldAttachment<
                                              AttachmentDescT>::createEmpty,
		NULL,
		NULL,
		0);
#else
template <class AttachmentDescT> 
FieldContainerType DynFieldAttachment<AttachmentDescT>::_type(
    AttachmentDescT::getTypeName(),
    "Attachment",
    NULL,
    (PrototypeCreateF) &DynFieldAttachment<
                                              AttachmentDescT>::createEmpty,
    NULL,
    NULL,
    0);
#endif


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

OSG_FIELD_CONTAINER_ST_INL_TMPL_DEF(DynFieldAttachment,
                                    AttachmentDescT,
                                    PtrType)

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

/*------------------------------ access -----------------------------------*/

template <class AttachmentDescT> inline
FieldContainerType& DynFieldAttachment<AttachmentDescT>::getType(void)
{
    return _localType;
}

template <class AttachmentDescT> inline
const FieldContainerType& 
    DynFieldAttachment<AttachmentDescT>::getType(void) const
{
    return _localType;
}

template <class AttachmentDescT> inline
UInt32 DynFieldAttachment<AttachmentDescT>::addField(
    const FieldDescription &fieldDesc)
{
    UInt32            returnValue = 0;
    Field            *fieldP      = NULL;
    FieldDescription *descP       = NULL;

    returnValue = _localType.addDescription(fieldDesc);

    if(returnValue != 0)
    {
        descP = _localType.getFieldDescription(returnValue);

        if(descP != NULL)
        {
            descP->setFieldId  (returnValue);
            descP->setFieldMask(1 << (returnValue - 1));

            fieldP = FieldFactory::the().createField(fieldDesc.getTypeId());

            if(_dynFieldsV.size() <=
               returnValue - Inherited::NextFieldId)
            {
                _dynFieldsV.resize((returnValue - 
                                    Inherited::NextFieldId) + 1);
            }
            
            _dynFieldsV[returnValue - Inherited::NextFieldId] = fieldP;
        }
    }

    return returnValue;
}

template <class AttachmentDescT> inline
void DynFieldAttachment<AttachmentDescT>::subField(UInt32 fieldId)
{
    if(_localType.subDescription(fieldId) == true)
    {
        vector<Field *>::iterator vIt = _dynFieldsV.begin();

        vIt += fieldId - Inherited::NextFieldId;

        if(vIt != _dynFieldsV.end())
        {
            delete (*vIt);

            (*vIt) = NULL;
        }
    }
}

template <class AttachmentDescT> inline
Field *DynFieldAttachment<AttachmentDescT>::getDynamicField(
    UInt32 index)
{
    return _dynFieldsV[index - Inherited::NextFieldId];
}

/*------------------------------- dump ----------------------------------*/

template <class AttachmentDescT> inline
void DynFieldAttachment<AttachmentDescT>::dump(void) const
{
    SDEBUG << "Dump DynFieldAttachment<> NI" << endl;

    _localType.print();

    for(UInt32 i = 0; i < _dynFieldsV.size(); i++)
    {
        fprintf(stderr, "%d\n", _dynFieldsV[i]);
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class AttachmentDescT> inline
DynFieldAttachment<AttachmentDescT>::DynFieldAttachment(void) :
	Inherited(),
    _localType(_type),
    _dynFieldsV()
{
}

/** \brief Copy Constructor
 */

template <class AttachmentDescT> inline
DynFieldAttachment<AttachmentDescT>::DynFieldAttachment(
                      const DynFieldAttachment &source) :
    Inherited(source),
    _localType(_type),
    _dynFieldsV(source._dynFieldsV) // Do a real copy soon ;-)
{
}

/** \brief Destructor
 */

template <class AttachmentDescT> inline
DynFieldAttachment<AttachmentDescT>::~DynFieldAttachment(void)
{
}

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

