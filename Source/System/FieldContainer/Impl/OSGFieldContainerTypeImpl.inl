/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *            Copyright (C) 2000-2002,2002 by the OpenSG Forum               *
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

#ifndef _OSGFIELDCONTAINERTYPEIMPL_INL_
#define _OSGFIELDCONTAINERTYPEIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerTypeImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt16 FieldContainerType::getGroupId (void) const
{
    return _uiGroupId;
}

inline
FieldContainerType *FieldContainerType::getParent(void) const
{
    return _pParent;
}

inline
FieldDescription *FieldContainerType::getFieldDescription(UInt32 uiFieldId)
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

inline
const FieldDescription *FieldContainerType::getFieldDescription(
    UInt32 uiFieldId) const
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

inline
FieldDescription *FieldContainerType::findFieldDescription(
    const Char8 *szFieldName)
{
    DescMapIt descIt = _mDescMap.find(IDStringLink(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
const FieldDescription *FieldContainerType::findFieldDescription(
    const Char8 *szFieldName) const
{
    DescMapConstIt descIt = _mDescMap.find(IDStringLink(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 FieldContainerType::getNumFieldDescs(void) const
{
    return _vDescVec.size();
}


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool FieldContainerType::isInitialized(void) const
{
    return _bInitialized;
}

inline
bool FieldContainerType::isDerivedFrom(const TypeBase &other) const
{
    return Inherited::isDerivedFrom(other);
}

inline
bool FieldContainerType::isDerivedFrom(const FieldContainerType &other) const
{
    bool                returnValue = false;
    FieldContainerType *pCurrType   = _pParent;

    if(_uiTypeId == other._uiTypeId)
    {
        returnValue = true;
    }
    else
    {
        while(pCurrType != NULL && returnValue == false)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                returnValue = true;
            }
            else
            {
                pCurrType = pCurrType->_pParent;
            }
        }
    }

    return returnValue;
}

inline
bool FieldContainerType::isNode(void) const
{
    return (_baseType == IsNode);
}

inline
bool FieldContainerType::isNodeCore(void) const
{
    return (_baseType == IsNodeCore);
}

inline
bool FieldContainerType::isAttachment(void) const
{
    return (_baseType == IsAttachment);
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERTYPE_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERTYPEIMPL_INL_ */
