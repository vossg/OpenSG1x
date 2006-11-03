
#include <qapplication.h>
#include "OSGMainView_qt.h"
#include <OpenSG/OSGBaseFunctions.h>
#include <qgl.h>

OSGMainView *_main_view = NULL;

int main( int argc, char ** argv )
{
    QApplication a(argc, argv);
    OSGMainView *w;

    OSG::osgInit(argc,argv);

    _main_view = new OSGMainView;

    a.setMainWidget(_main_view);

    a.processEvents();

    _main_view->show();

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    int result = a.exec();

    OSG::osgExit();

    return result;
}
