
OSG_BEGIN_NAMESPACE

inline FieldContainerPtr &
QFieldViewBase::getFieldContainer(void)
{
    return _pFieldCon;
}

inline const FieldContainerPtr &
QFieldViewBase::getFieldContainer(void) const
{
    return _pFieldCon;
}

inline UInt32
QFieldViewBase::getFieldId(void) const
{
    return _uiFieldId;
}

inline UInt32
QFieldViewBase::getAspect(void) const
{
    return _uiAspect;
}

inline Field *
QFieldViewBase::getFieldPtr(void)
{
    FieldContainer *pFCAsp = _pFieldCon.getAspectCPtr(_uiAspect);

    return pFCAsp->getField(_uiFieldId);
}

inline const Field *
QFieldViewBase::getFieldPtr(void) const
{
    FieldContainer *pFCAsp = _pFieldCon.getAspectCPtr(_uiAspect);

    return pFCAsp->getField(_uiFieldId);
}

OSG_END_NAMESPACE

#define OSGQFIELDVIEWBASE_INLINE_CVSID "@(#)$Id: OSGQFieldView_qt.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
