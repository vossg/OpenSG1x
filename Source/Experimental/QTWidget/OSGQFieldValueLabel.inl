
#include "OSGQFieldView_qt.h"

OSG_BEGIN_NAMESPACE

inline UInt32
QFieldValueLabelBase::getIndex(void) const
{
    return _uiIndex;
}

inline QFieldViewBase *
QFieldValueLabelBase::getFieldView(void)
{
    return _pView;
}

inline const QFieldViewBase *
QFieldValueLabelBase::getFieldView(void) const
{
    return _pView;
}

inline FieldContainerPtr &
QFieldValueLabelBase::getFieldContainer(void)
{
    return _pView->getFieldContainer();
}

inline const FieldContainerPtr &
QFieldValueLabelBase::getFieldContainer(void) const
{
    return _pView->getFieldContainer();
}

inline UInt32
QFieldValueLabelBase::getFieldId(void) const
{
    return _pView->getFieldId();
}

inline UInt32
QFieldValueLabelBase::getAspect(void) const
{
    return _pView->getAspect();
}

inline Field *
QFieldValueLabelBase::getFieldPtr(void)
{
    return _pView->getFieldPtr();
}

inline const Field *
QFieldValueLabelBase::getFieldPtr(void) const
{
    return _pView->getFieldPtr();
}

OSG_END_NAMESPACE

#define OSGQFIELDVALUELABEL_INLINE_CVSID "@(#)$Id: OSGQFieldValueLabel.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
