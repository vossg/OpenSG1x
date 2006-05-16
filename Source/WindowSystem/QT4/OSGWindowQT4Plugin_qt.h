/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGWINDOWQTPLUGIN_H_
#define _OSGWINDOWQTPLUGIN_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#ifdef OSG_WITH_QT

// #ifdef __sgi
// #pragma set woff 1375
// #endif

// #ifdef OSG_WIN32_ICL
// #pragma warning (disable : 171)
// #endif

#include <QDesignerCustomWidgetInterface>

// #ifdef OSG_WIN32_ICL
// #pragma warning (error : 171)
// #endif

// #ifdef __sgi
// #pragma reset woff 1375
// #endif

#include "OSGConfig.h"
#include <OSGWindowQT4Def.h>
#include <OSGBaseTypes.h>

#include "OSGQT4Window.h"

namespace osg {
	class NodePtr;
}

//OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! \brief Qt plugin wrapper for OpenSG Qt Window Widget(s)
//! \todo Documentation review
//! \ingroup baselib

class OSG_WINDOWQTLIB_DLLMAPPING OSGWindowQTPlugin : public QObject, QDesignerCustomWidgetInterface
{
	Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
	OSGWindowQTPlugin(QObject *parent = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*---------------------------------------------------------------------*/
    /*! \name                     Destructor                               */
    /*! \{                                                                 */
	~OSGWindowQTPlugin();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Qt Plugin Interface                        */
    /*! \{                                                                 */
	bool isContainer() const;
	bool isInitialized() const;
	QIcon icon() const;
	QString codeTemplate() const;
    QString domXml() const;
	QString group() const;
	QString includeFile() const;
	QString name() const;
	QString toolTip() const;
	QString whatsThis() const;
	QWidget* createWidget( QWidget* parent = 0 );
	void initialize(QDesignerFormEditorInterface *core);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
	
  protected:
    osg::NodePtr makeInitialScene();
	
  private:

    typedef QDesignerCustomWidgetInterface Inherited;
    bool initialized;



    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGWindowQTPlugin(const OSGWindowQTPlugin &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OSGWindowQTPlugin &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */

// typedef OSGWindowQTPlugin *OSGWindowQTPluginP;

//OSG_END_NAMESPACE

#define OSGWINDOWQTPLUGIN_HEADER_CVSID "@(#)$Id: OSGWindowQT4Plugin_qt.h,v 1.1 2006/05/16 02:40:14 vossg Exp $"

#endif /* OSG_WITH_QT */

#endif /* _OSGWINDOWQTPLUGIN_H_ */
