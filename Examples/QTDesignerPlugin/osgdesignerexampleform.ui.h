/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qfiledialog.h>
#include <qapplication.h>
#include <qgl.h>

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGLog.h>

int main(int argc, char** argv)
{
    osgInit(argc,argv);
    QApplication app(argc, argv);
    
    QGLFormat::setDefaultFormat(QGLFormat(QGL::DirectRendering | 
                                          QGL::DoubleBuffer    |  
                                          QGL::DepthBuffer     |
                                          QGL::Rgba            ));
    
    OSGDesignerExampleForm form;
    form.show();
    app.setMainWidget(&form);
    int retval = app.exec();
    
    osgExit();
    return retval;
}

void OSGDesignerExampleForm::init()
{
    FDEBUG(("OSGDesignerExampleForm::init()"));
	osgViewer->updateGL();
	osgViewer->getManager().useOpenSGLogo();
    btnHeadlight->setOn( osgViewer->getManager().getHeadlightState() );
}

void OSGDesignerExampleForm::onOpenModel() 
{
  	QString filename = 
		QFileDialog::getOpenFileName("/home", 
						"Model files (*.bin *.obj *.off *.osg *.raw *.wrl)",
						this, 
						"Open model dialog",
						"Choose a model to open" );

	if( !filename.isEmpty() )
	{
		// Load the file	
		NodePtr file = NullFC;

		file = SceneFileHandler::the().read(filename.latin1());	
		if ( file == NullFC )
		{
	    	std::cerr << "Couldn't load file, ignoring" << std::endl;			
		}
		else
			osgViewer->getManager().setRoot(file); 
	}	

    osgViewer->getManager().showAll(); 
	osgViewer->updateGL();      	
}



void OSGDesignerExampleForm::showAll()
{
    osgViewer->getManager().showAll();
	osgViewer->updateGL();
}


void OSGDesignerExampleForm::toggleHeadlight()
{
    osgViewer->getManager().setHeadlight( btnHeadlight->isOn() );
	osgViewer->updateGL();
}
