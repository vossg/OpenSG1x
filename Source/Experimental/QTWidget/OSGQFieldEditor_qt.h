
#ifndef _OSGQFIELDEDITOR_H_
#define _OSGQFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"

#include <OSGField.h>

#include <qwidget.h>

class QLineEdit;
class QResizeEvent;

OSG_BEGIN_NAMESPACE

class QFieldViewBase;

/*! \brief Base class for the field editor widgets
 */

class OSG_QTWIDGETLIB_DLLMAPPING QFieldEditorBase : public QWidget
{
    Q_OBJECT

public:
    QFieldEditorBase(QFieldViewBase *pView,   const char   *name=NULL);

    QFieldEditorBase(UInt32          uiIndex,
                     QFieldViewBase *pView,   const char   *name=NULL);

    virtual ~QFieldEditorBase(void) = 0;

    virtual       void            updateField (void          ) = 0;
    virtual       void            updateEditor(void          ) = 0;

    virtual       void            activate    (void          );
    virtual       void            deactivate  (void          );

                  void            setIndex    (UInt32 uiIndex);

                  bool            getActive   (void          ) const;
                  UInt32          getIndex    (void          ) const;

signals:
                  void            editorDone  (void          );
                  void            fieldUpdated(UInt32 uiIndex);

protected:
                  QFieldViewBase *getFieldView(void          );
            const QFieldViewBase *getFieldView(void          ) const;

                  Field          *getFieldPtr (void          );
            const Field          *getFieldPtr (void          ) const;

private:
    typedef QWidget Inherited;

    QFieldViewBase *_pView;
    UInt32          _uiIndex;
    bool            _bActive;
};

/*! \brief Field editor, which uses the text interface of the fields.
 */

class QGenericFieldEditor : public QFieldEditorBase
{
    Q_OBJECT

public:
    QGenericFieldEditor(QFieldViewBase *pView,   const char   *name=NULL);

    QGenericFieldEditor(UInt32          uiIndex,
                        QFieldViewBase *pView,   const char   *name=NULL);
    
    virtual ~QGenericFieldEditor(void);

    virtual void updateField    (void);
    virtual void updateEditor   (void);

    virtual void activate       (void);
    virtual void deactivate     (void);

protected slots:
    virtual void resizeEvent    (QResizeEvent *pEvent);

private slots:
            void onReturnPressed(void);

private:
    typedef QFieldEditorBase Inherited;

    QLineEdit *_pLineEdit;
};

OSG_END_NAMESPACE

#define OSGQFIELDEDITOR_HEADER_CVSID "@(#)$Id: OSGQFieldEditor_qt.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

#include "OSGQFieldEditor_qt.inl"

#endif /* _OSGQFIELDEDITOR_H_ */
