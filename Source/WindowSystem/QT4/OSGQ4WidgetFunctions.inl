/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
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

OSG_BEGIN_NAMESPACE

inline Field *getParentsField(FieldContainerPtr pFC, UInt32 uiAspect)
{
    if(pFC == NullFC)
        return NULL;

    FieldContainer *pFCAsp      = pFC.getAspectCPtr(uiAspect);
    UInt32          uiNumFields = pFCAsp->getType().getNumFieldDescs();

    for(UInt32 uiFieldId = 1; uiFieldId <= uiNumFields; ++uiFieldId)
    {
        FieldDescription *pDesc  = 
            pFCAsp->getType().getFieldDescription  (uiFieldId);
        Field            *pField = pFCAsp->getField(uiFieldId);

        if((strstr(pField->getType().getCName(), "Ptr"   ) != NULL) &&
           (strstr(pDesc->getCName(),            "parent") != NULL)   )
        {
            return pField;
        }
    }

    return NULL;
}


inline bool isSFFieldContainerPtr(Field *pField)
{
    if((strstr(pField->getType().getCName(), "Ptr") != NULL) &&
       (pField->getCardinality()                   == FieldType::SINGLE_FIELD))
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool isMFFieldContainerPtr(Field *pField)
{
    if((strstr(pField->getType().getCName(), "Ptr") != NULL) &&
       (pField->getCardinality()                    == FieldType::MULTI_FIELD))
    {
        return true;
    }
    else
    {
        return false;
    }
}

OSG_END_NAMESPACE

#define OSGQWIDGETFUNCTIONS_INLINE_CVSID "@(#)$Id: OSGQ4WidgetFunctions.inl,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"
