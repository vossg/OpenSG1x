
#include "OSGQFieldView_qt.h"

#include <OSGFieldContainer.h>

OSG_BEGIN_NAMESPACE

inline bool
QFieldEditorBase::getActive(void) const
{
    return _bActive;
}

inline UInt32
QFieldEditorBase::getIndex(void) const
{
    return _uiIndex;
}

inline QFieldViewBase *
QFieldEditorBase::getFieldView(void)
{
    return _pView;
}

inline const QFieldViewBase *
QFieldEditorBase::getFieldView(void) const
{
    return _pView;
}

inline Field *
QFieldEditorBase::getFieldPtr(void)
{
    FieldContainer *pFCAsp = getFieldView()->getFieldContainer().getAspectCPtr(
                                                  getFieldView()->getAspect());

    return pFCAsp->getField(getFieldView()->getFieldId());
}

inline const Field *
QFieldEditorBase::getFieldPtr(void) const
{
    FieldContainer *pFCAsp = getFieldView()->getFieldContainer().getAspectCPtr(
                                                  getFieldView()->getAspect());

    return pFCAsp->getField(getFieldView()->getFieldId());
}

OSG_END_NAMESPACE

#define OSGQFIELDEDITOR_INLINE_CVSID "@(#)$Id: OSGQFieldEditor_qt.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
