
#include "OSGQFieldEditorFactory.h"
#include "OSGQFieldView_qt.h"
#include "OSGQFieldEditor_qt.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQFieldEditorFactory.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDEDITORFACTORY_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGQFIELDEDITORFACTORY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldEditorFactory *QFieldEditorFactory::_the = 0;

QFieldEditorFactory::~QFieldEditorFactory(void)
{
}

QFieldEditorFactory &
QFieldEditorFactory::the(void)
{
    if(!_the)
        _the = new QFieldEditorFactory;

    return *_the;
}

QFieldEditorBase *
QFieldEditorFactory::createEditor(      QFieldViewBase *pView,
                                  const char           *name  )
{
    return new QGenericFieldEditor(pView, name);
}

QFieldEditorBase *
QFieldEditorFactory::createEditor(      UInt32  uiIndex, QFieldViewBase *pView,
                                  const char   *name)
{
    return new QGenericFieldEditor(uiIndex, pView, name);
}

QFieldEditorFactory::QFieldEditorFactory(void)
{
}
