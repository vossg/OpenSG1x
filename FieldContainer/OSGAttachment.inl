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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGFieldFactory.h>
#include "OSGBinaryDataHandler.h"

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


template <class AttachmentDescT>
const BitVector SimpleAttachment<AttachmentDescT>::SimpleFieldMask =
    (1 << SimpleAttachment<AttachmentDescT>::SimpleFieldId);


/** \brief Attachment field description
 */

template <class AttachmentDescT>
FieldDescription *SimpleAttachment<AttachmentDescT>::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(),
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
    sizeof(FieldDescription *));
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
SimpleAttachment<AttachmentDescT>::StoredFieldType *
    SimpleAttachment<AttachmentDescT>::getFieldPtr(void)
{
    return &_field;
}

/** \brief Returns reference to the stored field
 */

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::StoredFieldType &
    SimpleAttachment<AttachmentDescT>::getField(void)
{
    return _field;
}

/** \brief Returns const reference to the stored field
 */

template <class AttachmentDescT> inline
const SimpleAttachment<AttachmentDescT>::StoredFieldType &
    SimpleAttachment<AttachmentDescT>::getField(void) const
{
    return _field;
}

template <class AttachmentDescT> inline
UInt32 SimpleAttachment<AttachmentDescT>::getBinSize(
    const BitVector &whichField)
{
    UInt32 returnValue = 0;

    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyToBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyFromBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}


/*------------------------------- dump ----------------------------------*/

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::dump(      UInt32    uiIndent,
                                             const BitVector bvFlags ) const
{
    Inherited::dump(uiIndent, bvFlags);
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

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField)
{
    this->executeSyncImpl((SimpleAttachment *) &other,
                          whichField);
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::executeSyncImpl(
          SimpleAttachment *pOther,
    const BitVector        &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        _field.syncWith(pOther->_field);
    }
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


/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class AttachmentDescT>
FieldContainerType DynFieldAttachment<AttachmentDescT>::_type =
    FieldContainerType(
        AttachmentDescT::getTypeName(),
        AttachmentDescT::getParentTypeName(),
        AttachmentDescT::getGroupName(),
        (PrototypeCreateF) &DynFieldAttachment<AttachmentDescT>::createEmpty,
        NULL,
        NULL,
        NULL,
        true);
#else
template <class AttachmentDescT>
FieldContainerType DynFieldAttachment<AttachmentDescT>::_type(
    AttachmentDescT::getTypeName(),
    AttachmentDescT::getParentTypeName(),
    AttachmentDescT::getGroupName(),
    (PrototypeCreateF) &DynFieldAttachment<AttachmentDescT>::createEmpty,
    NULL,
    NULL,
    NULL,
    true);
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
FieldContainerType &DynFieldAttachment<AttachmentDescT>::getType(void)
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
            descP->setFieldMask(1 << returnValue);

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

template <class AttachmentDescT> inline
FieldContainerPtr DynFieldAttachment<AttachmentDescT>::emptyCopy(void)
{
    PtrType returnValue = DynFieldAttachment<AttachmentDescT>::createEmpty();

    for(UInt32 i  = Inherited::NextFieldId;
               i <= _localType.getNumFieldDescs();
               i++)
    {
        returnValue->addField(*(_localType.getFieldDescription(i)));
    }

    return returnValue;
}

template <class AttachmentDescT> inline
FieldContainerPtr DynFieldAttachment<AttachmentDescT>::clone(void)
{
    PtrType returnValue = DynFieldAttachment<AttachmentDescT>::createEmpty();
    UInt32 i;

    for( i = Inherited::NextFieldId;
         i <= _localType.getNumFieldDescs();
         i++)
    {
        returnValue->addField(*(_localType.getFieldDescription(i)));
    }

    for( i = Inherited::NextFieldId;
         i <= _localType.getNumFieldDescs();
         i++)
    {
        returnValue->getDynamicField(i)->setAbstrValue(
            *(_dynFieldsV[i - Inherited::NextFieldId]));
    }

    return returnValue;
}

/*------------------------------- dump ----------------------------------*/

template <class AttachmentDescT> inline
void DynFieldAttachment<AttachmentDescT>::dump(      UInt32    uiIndent,
                                               const BitVector ) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "DynFieldAttachment (" ;

    _localType.dump();
    PLOG << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << endl;

    uiIndent += 4;

    for(UInt32 i = 1; i <= getType().getNumFieldDescs(); i++)
    {
        indentLog(uiIndent, PLOG);
        PLOG <<      getType().getFieldDescription(i)->getCName ()
             << " ("
             << const_cast<DynFieldAttType *>(this)->getField(
                     getType().getFieldDescription(i)->getFieldId())
             << ")"
             << endl;
    }

    uiIndent -= 4;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
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

#define OSGATTACHMENT_INLINE_CVSID "@(#)$Id: $"


