
OSG_BEGIN_NAMESPACE

inline FieldContainerPtr &
QFieldContainerView::getFieldContainer(void)
{
    return _pFC;
}

inline const FieldContainerPtr &
QFieldContainerView::getFieldContainer(void) const
{
    return _pFC;
}

inline UInt32
QFieldContainerView::getAspect(void) const
{
    return _uiAspect;
}

inline bool
QFieldContainerView::getShowTypeColumn(void) const
{
    return _bShowTypeColumn;
}

OSG_END_NAMESPACE

#define OSGQFIELDCONTAINERVIEW_INLINE_CVSID "@(#)$Id: OSGQFieldContainerView_qt.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
