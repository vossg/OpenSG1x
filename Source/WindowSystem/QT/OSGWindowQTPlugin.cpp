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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "qstring.h"

#include "OSGWindowQTPlugin.h"

// #include "OSGQGLDesignerWidget_qt.h"
#include "OSGQGLManagedDesignerWidget_qt.h"
#include "OSGQGLManagedWidget_pixmap.xpm"

#include <OSGDrawAction.h>
#include "OSGSimpleGeometry.h"
#include "OSGViewport.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGTrackball.h"

#include <OSGNode.h>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::OSGWindowQTPlugin
    Provides Qt Designer plugin for the widget(s) 
	\c osg::OSGQGLManagedWidget, ...
 */

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------- constructors ----------------------------------*/

/*! Construct plugin
 */
OSGWindowQTPlugin::OSGWindowQTPlugin()
{
	osgInit(0, NULL);
}

/*! Destruct plugin
 */
OSGWindowQTPlugin::~OSGWindowQTPlugin()
{
	osgExit();
}


/*! Get keys of the widget types of this plugin.
 */
QStringList OSGWindowQTPlugin::keys() const
{
	QStringList list;
	
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
	// list << "OSGQGLDesignerWidget";
	list << "OSGQGLManagedDesignerWidget";
	return list;
}

/*! Create widget for \a key.
 */
QWidget* 
OSGWindowQTPlugin::create( const QString &key, QWidget *parent, const char *name )
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 	{
// 		OSGQGLDesignerWidget *w     = new OSGQGLDesignerWidget( parent, name );
// 		ViewportPtr           vp    = osg::NullFC;		
//         NodePtr               root  = osg::NullFC;
// 		TransformPtr          cam_trans = osg::NullFC;
//         DrawAction            *ract;
//     	PerspectiveCameraPtr  cam   = osg::NullFC;
//     	SolidBackgroundPtr    bkgnd = SolidBackground::create();
//         Trackball             *tball = new Trackball();  // mem leak here
//         
//     	// beacon for camera and light  
//     	NodePtr b1n = Node::create();
//     	GroupPtr b1 = Group::create();
//     	beginEditCP(b1n);
//     	b1n->setCore( b1 );
//     	endEditCP(b1n);
// 		
//     	// transformation
//     	NodePtr t1n = Node::create();
//     	TransformPtr t1 = Transform::create();
//     	beginEditCP(t1n);
//     	t1n->setCore( t1 );
//     	t1n->addChild( b1n );
//     	endEditCP(t1n);
// 
//     	cam_trans = t1;
// 
//     	// light
// 
//     	NodePtr dlight = Node::create();
//     	DirectionalLightPtr dl = DirectionalLight::create();
// 
//     	beginEditCP(dlight);
//     	dlight->setCore( dl );
//     	endEditCP(dlight);
// 
//     	beginEditCP(dl);
//     	dl->setAmbient( .3, .3, .3, 1 );
//     	dl->setDiffuse( 1, 1, 1, 1 );
//     	dl->setDirection(0,0,1);
//     	dl->setBeacon( b1n);
//     	endEditCP(dl);
// 
//     	// root
//     	root = Node::create();
//     	GroupPtr gr1 = Group::create();
//     	beginEditCP(root);
//     	root->setCore( gr1 );
//     	root->addChild( t1n );
//     	root->addChild( dlight );
//     	endEditCP(root);
// 		
// 		NodePtr file = makeInitialScene();
//     	file->updateVolume();
// 
//     	Vec3f min,max;
//     	file->getVolume().getBounds( min, max );
// 
//     	beginEditCP(dlight);
//     	dlight->addChild( file );
//     	endEditCP(dlight);
// 		
// 		// camera
//     	cam = PerspectiveCamera::create();
//     	cam->setBeacon( b1n );
//     	cam->setFov( deg2rad( 60 ) );
//     	cam->setNear( 100 );
//     	cam->setFar( 100000 );
// 
//     	// Background
//     	bkgnd->setColor( Color3f( 0,0,1 ) );
// 
//     	// Viewport
// 
//     	vp = Viewport::create();
//     	vp->setCamera( cam );
//     	vp->setBackground( bkgnd );
//     	vp->setRoot( root );
//     	vp->setSize( 0,0, 1,1 );
// 
//     	// Action
//     	ract = DrawAction::create();
// 
//     	Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );
// 		
//     	tball->setMode( Trackball::OSGObject );
//     	tball->setStartPosition( pos, true );
//     	tball->setSum( true );
//     	tball->setTranslationMode( Trackball::OSGFree );
// 
//     	QTWindowPtr osgWin = QTWindow::create();
//     	osgWin->setGlWidget( w );
//     	osgWin->addPort( vp );
//         osgWin->init();     // create the context
//         osgWin->activate(); // and activate it
// 						
// 		return w;
// 	}
	if ( key == "OSGQGLManagedDesignerWidget" )
	{
		OSGQGLManagedDesignerWidget *w = 
			new OSGQGLManagedDesignerWidget( parent, name );
			
	    w->getManager().setRoot( makeInitialScene() ); 
		return w;
	}
	return 0;
}

osg::NodePtr OSGWindowQTPlugin::makeInitialScene()
{
	OSG::NodePtr scene = OSG::makeTorus(.5, 1, 8, 8);
	OSG::NodePtr scene2 = OSG::makeTorus(.1, 2, 10, 12);

	OSG::NodePtr grn = OSG::Node::create();
	OSG::GroupPtr gr = OSG::Group::create();

	OSG::beginEditCP(grn, OSG::Node::CoreFieldMask | OSG::Node::ChildrenFieldMask );
	grn->setCore(gr);
	grn->addChild(scene);
	grn->addChild(scene2);
	OSG::endEditCP  (grn, OSG::Node::CoreFieldMask | OSG::Node::ChildrenFieldMask );	
	
	return grn;
}

/*! Return name of include file for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::includeFile( const QString& key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OSGQGLDesignerWidget_qt.h";
	if ( key == "OSGQGLManagedDesignerWidget" )
		return "OpenSG/OSGQGLManagedDesignerWidget_qt.h";
	return QString::null;
}

/*! Return name of group for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::group( const QString& key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OpenSG";
	if ( key == "OSGQGLManagedDesignerWidget" )
		return "OpenSG";
	return QString::null;
}

/*! Return icon set for widget type \a key (for Qt Designer).
 */
QIconSet OSGWindowQTPlugin::iconSet( const QString& key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return QIconSet( QPixmap( OSGQGLManagedWidget_pixmap ) );
	if ( key == "OSGQGLManagedDesignerWidget" )
		return QIconSet( QPixmap( OSGQGLManagedWidget_pixmap ) );
	return QIconSet();
}

/*! Return tool tip text for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::toolTip( const QString& key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OpenSG Qt Designer Widget";
	if ( key == "OSGQGLManagedDesignerWidget" )
		return "OpenSG Managed Qt Designer Widget";
	return QString::null;
}

/*! Return short description (what's this) text for widget type \a key (for Qt
 *  Designer).
 */
QString OSGWindowQTPlugin::whatsThis( const QString& key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "A widget to display OpenSG scene";
	if ( key == "OSGQGLManagedDesignerWidget" )
		return "A widget to display OpenSG scene with Simple Scene Manager features";
	return QString::null;
}

/*! Returns, whether widget type \a key is a container widget (for Qt
 *  Designer).
 */
bool OSGWindowQTPlugin::isContainer( const QString & key ) const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return false;
	if ( key == "OSGQGLManagedDesignerWidget" )
		return false;
	return false;
}

Q_EXPORT_PLUGIN( OSGWindowQTPlugin )

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGWindowQTPlugin.cpp,v 1.2 2003/07/09 08:53:32 dirk Exp $";
    static Char8 cvsid_hpp[] = OSGWINDOWQTPLUGIN_HEADER_CVSID;
}

