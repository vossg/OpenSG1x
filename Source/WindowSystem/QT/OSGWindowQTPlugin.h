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

#include <qwidgetplugin.h>

// #ifdef OSG_WIN32_ICL
// #pragma warning (error : 171)
// #endif

// #ifdef __sgi
// #pragma reset woff 1375
// #endif

#include "OSGConfig.h"
#include <OSGWindowQTDef.h>
#include <OSGBaseTypes.h>

#include "OSGQTWindow.h"

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

class OSG_WINDOWQTLIB_DLLMAPPING OSGWindowQTPlugin : public QWidgetPlugin
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
	OSGWindowQTPlugin();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Qt Plugin Interface                        */
    /*! \{                                                                 */
	QStringList keys() const;
	QWidget* create( const QString &classname, QWidget* parent = 0, const char* name = 0 );
	QString group( const QString& ) const;
	QIconSet iconSet( const QString& ) const;
	QString includeFile( const QString& ) const;
	QString toolTip( const QString& ) const;
	QString whatsThis( const QString& ) const;
	bool isContainer( const QString& ) const;
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
	
  protected:
    osg::NodePtr makeInitialScene();
	
  private:

    typedef QWidgetPlugin Inherited;


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

#define OSGWINDOWQTPLUGIN_HEADER_CVSID "@(#)$Id: OSGWindowQTPlugin.h,v 1.1 2003/06/17 15:35:19 eschler Exp $"

#endif /* OSG_WITH_QT */

#endif /* _OSGWINDOWQTPLUGIN_H_ */
