
#include <OpenSG/OSGConfig.h>

#include "OSGActorEditViewCtl_qt.h"

#include <qapplication.h>

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication     myQApp      (argc, argv);
    ActorEditViewCtl actorEditCtl;

    myQApp.setMainWidget(&actorEditCtl);

    actorEditCtl.show();

    return myQApp.exec();
}
