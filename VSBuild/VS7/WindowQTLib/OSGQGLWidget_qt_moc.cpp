/****************************************************************************
** OSGQGLWidget meta object code from reading C++ file 'OSGQGLWidget_qt.h'
**
** Created: Sat Jun 22 16:11:03 2002
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

const char *OSGQGLWidget::className() const
{
    return "OSGQGLWidget";
}

QMetaObject *OSGQGLWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_OSGQGLWidget;

#ifndef QT_NO_TRANSLATION
QString OSGQGLWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSGQGLWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString OSGQGLWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "OSGQGLWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* OSGQGLWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"OSGQGLWidget", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_OSGQGLWidget.setMetaObject( metaObj );
    return metaObj;
}

void* OSGQGLWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "OSGQGLWidget" ) ) return (OSGQGLWidget*)this;
    return QGLWidget::qt_cast( clname );
}

bool OSGQGLWidget::qt_invoke( int _id, QUObject* _o )
{
    return QGLWidget::qt_invoke(_id,_o);
}

bool OSGQGLWidget::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool OSGQGLWidget::qt_property( int _id, int _f, QVariant* _v)
{
    return QGLWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
