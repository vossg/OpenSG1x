
#include <qapplication.h>
#include "OSGMainView_qt.h"
#include <OpenSG/OSGBaseFunctions.h>
#include <qgl.h>

int main( int argc, char ** argv )
{
    QApplication a(argc, argv);
    OSGMainView *w;

    osg::osgInit(argc,argv);

    w = new OSGMainView;


    a.setMainWidget(w);

    a.processEvents();

    w->show();
    
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
