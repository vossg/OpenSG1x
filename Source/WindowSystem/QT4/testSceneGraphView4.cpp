
#include "OSGQ4SceneGraphView_qt.h"

#include <OSGSceneFileHandler.h>
#include <OSGSimpleGeometry.h>
#include <OSGNode.h>
#include <OSGLog.h>

#include <string>

#include <QApplication>

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    QApplication app(argc, argv);

    std::string      sceneFileName;
    NodePtr          pRootNode;
    QSceneGraphView *pView         = new QSceneGraphView(NULL, "pView");

    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));

        std::list<const char*> suffixes;
        SceneFileHandler::the().getSuffixList(suffixes);

        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        pRootNode = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        pRootNode = SceneFileHandler::the().read(argv[1]);
    }

    if(pRootNode == NullFC)
    {
        SFATAL << "Failed to load scene from file." << endLog;
        exit(1);
    }

    pView->setRoot(pRootNode);

    app.setMainWidget(pView);

    pView->show();

    return app.exec();
}
