/****************************************************************************
** OSGQGLManagedWidget meta object code from reading C++ file 'OSGQGLManagedWidget_qt.h'
**
** Created: Thu Sep 2 18:36:03 2004
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *OSGQGLManagedWidget::className() const
{
    return "OSGQGLManagedWidget";
}

QMetaObject *OSGQGLManagedWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_OSGQGLManagedWidget;

#ifndef QT_NO_TRANSLATION
QString OSGQGLManagedWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSGQGLManagedWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString OSGQGLManagedWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSGQGLManagedWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* OSGQGLManagedWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = OSGQGLWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ "object", &static_QUType_ptr, "QWidget", QUParameter::In }
    };
    static const QUMethod signal_0 = {"closed", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "closed(QWidget*)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"OSGQGLManagedWidget", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_OSGQGLManagedWidget.setMetaObject( metaObj );
    return metaObj;
}

void* OSGQGLManagedWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "OSGQGLManagedWidget" ) ) return (OSGQGLManagedWidget*)this;
    return OSGQGLWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL closed
void OSGQGLManagedWidget::closed( QWidget* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool OSGQGLManagedWidget::qt_invoke( int _id, QUObject* _o )
{
    return OSGQGLWidget::qt_invoke(_id,_o);
}

bool OSGQGLManagedWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: closed((QWidget*)static_QUType_ptr.get(_o+1)); break;
    default:
	return OSGQGLWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool OSGQGLManagedWidget::qt_property( int _id, int _f, QVariant* _v)
{
    return OSGQGLWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
