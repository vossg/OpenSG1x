
#ifndef _OSGFIELDEDITORFACTORY_H_
#define _OSGFIELDEDITORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"

#include <OSGBaseTypes.h>

#include <qnamespace.h>

class QWidget;

OSG_BEGIN_NAMESPACE

class QFieldViewBase;
class QFieldEditorBase;

class OSG_QTWIDGETLIB_DLLMAPPING QFieldEditorFactory : public Qt
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

#define OSGQFIELDEDITORFACTORY_HEADER_CVSID "@(#)$Id: OSGQFieldEditorFactory.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

// #include "OSGQFieldEditorFactory.inl"

#endif /* _OSGQFIELDEDITORFACTORY_H_ */
