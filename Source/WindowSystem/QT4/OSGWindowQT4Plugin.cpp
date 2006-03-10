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

#include "OSGWindowQT4Plugin.h"

// #include "OSGQ4GLDesignerWidget_qt.h"
#include "OSGQ4GLManagedDesignerWidget_qt.h"
#include "OSGQ4GLManagedWidget_pixmap.xpm"

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

/*! Construct plugin. The class constructor simply calls the QObject
 *  base class constructor and sets the initialized variable to false.
 */
OSGWindowQTPlugin::OSGWindowQTPlugin( QObject* parent )
	: QObject(parent)
{
	initialized = false;
	
}

/*! Destruct plugin. The class destructor simply calls osgExit().
 */
OSGWindowQTPlugin::~OSGWindowQTPlugin()
{
	osgExit();
}

/*! Initialize this plugin. Qt Designer will initialize the plugin when
 *  it is required by calling the initialize() function.
 */
void OSGWindowQTPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (initialized)
		return;

	osgInit(0, NULL);
    initialized = true;
}

/*! Check init status. The isInitialized() function lets Qt Designer
 *  know whether the plugin is ready for use.
 */
bool OSGWindowQTPlugin::isInitialized() const
{
	return initialized;
}

/*! Create OSGQGLManagedDesignerWidget. Instances of OSGQGLManagedDesignerWidget
 *  are supplied by the createWidget() function.
 */
QWidget* 
OSGWindowQTPlugin::createWidget( QWidget *parent )
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
	
	OSGQGLManagedDesignerWidget *w = 
		new OSGQGLManagedDesignerWidget( parent );
			
	w->getManager().setRoot( makeInitialScene() ); 
	return w;
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

/*! Return name for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::name() const
{
	return "OSGQGLManagedDesignerWidget";
}

/*! Return name of group for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::group() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OpenSG";

	return "OpenSG";
}

/*! Return icon for widget type \a key (for Qt Designer).
 */
QIconSet OSGWindowQTPlugin::icon() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return QIconSet( QPixmap( OSGQGLManagedWidget_pixmap ) );
	
	return QIcon( QPixmap( OSGQGLManagedWidget_pixmap ) );
}

/*! Return tool tip text for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::toolTip() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OpenSG Qt Designer Widget";
	
	return "OpenSG Qt Managed Designer Widget";
}

/*! Return short description (what's this) text for widget type \a key (for Qt
 *  Designer).
 */
QString OSGWindowQTPlugin::whatsThis() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "A widget to display OpenSG scene";
	
	return "A widget to display OpenSG scene with Simple Scene Manager features";
}

/*! Returns, whether widget type \a key is a container widget (for Qt
 *  Designer).
 */
bool OSGWindowQTPlugin::isContainer() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return false;
	
	return false;
}

/*! The domXml() function provides a way to include default settings for the
 *  widget in the standard XML format used by Qt Designer. In this case, we
 *  only specify the widget's geometry.
 */
QString OSGWindowQTPlugin::domXml() const
{
    return "<widget class=\"OSGQGLManagedDesignerWidget\" name=\"osgqglManagedDesignerWidget\">\n"
            " <property name=\"geometry\">\n"
            "  <rect>\n"
            "   <x>0</x>\n"
            "   <y>0</y>\n"
            "   <width>100</width>\n"
            "   <height>100</height>\n"
            "  </rect>\n"
            " </property>\n"
            "</widget>\n";
}

/*! Return name of include file for widget type \a key (for Qt Designer).
 */
QString OSGWindowQTPlugin::includeFile() const
{
	// the OSGQGLDesignerWidget is disabled because it needs to be inherited
	// to be used. A widget plugin cannot be inherited within designer
// 	if ( key == "OSGQGLDesignerWidget" )
// 		return "OSGQGLDesignerWidget_qt.h";
	
	return "OpenSG/OSGQGLManagedDesignerWidget_qt.h";
}

QString OSGWindowQTPlugin::codeTemplate() const
{
    return "";
}

#include "OSGWindowQT4Plugin_moc.cpp"

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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGWindowQT4Plugin.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGWINDOWQTPLUGIN_HEADER_CVSID;
}
