
#include <OSGConfig.h>

#include "OSGQOSGWidgetFactory.h"
#include "OSGQFieldContainerEditor_qt.h"

#include <OSGSceneFileHandler.h>
#include <OSGSimpleGeometry.h>
#include <OSGLog.h>

#include <qapplication.h>
#include <qgrid.h>

#define NUM_SIZES 100

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    QApplication   *pQApp     = new QApplication  (argc, argv           );
    QGrid          *pGrid     = new QGrid         (1, NULL,  "pGrid"    );

    QOSGWidgetFactory::FieldEditorCF  cFunc;
    QFieldContainerEditor            *pFCEditor;

    NodePtr pScene;

    if(argc < 2)
    {
        FWARNING(("No file given, using a generated scene.\n"));

        pScene = makeTorus(1.0, 1.2, 5, 5);
    }
    else
    {
        pScene = SceneFileHandler::the().read(argv[1]);
    }

    pFCEditor = new QFieldContainerEditor(pGrid, "pFCEditor");
    pFCEditor->setReadOnly      (false );
    pFCEditor->setFieldContainer(pScene);

    pQApp->setMainWidget(pGrid);
    pGrid->show();

    return pQApp->exec();
}
