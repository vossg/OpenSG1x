
#ifndef _OSGFIELDEDITORFACTORY_H_
#define _OSGFIELDEDITORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <qnamespace.h>

class QWidget;

OSG_BEGIN_NAMESPACE

class QFieldViewBase;
class QFieldEditorBase;

class QFieldEditorFactory : public Qt
{
public:
    ~QFieldEditorFactory(void);

    static QFieldEditorFactory &the();

    QFieldEditorBase *createEditor(      QFieldViewBase *pView,
                                   const char           *name = 0);

    QFieldEditorBase *createEditor(      UInt32          uiIndex,
                                         QFieldViewBase *pView,  
                                   const char           *name = 0);
private:
    QFieldEditorFactory(void);

    static QFieldEditorFactory *_the;
};

OSG_END_NAMESPACE

#define OSGQFIELDEDITORFACTORY_HEADER_CVSID "@(#)$Id: OSGQFieldEditorFactory.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

// #include "OSGQFieldEditorFactory.inl"

#endif /* _OSGQFIELDEDITORFACTORY_H_ */
