
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

#define OSGQWIDGETFUNCTIONS_INLINE_CVSID "@(#)$Id: OSGQWidgetFunctions.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
