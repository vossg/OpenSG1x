
#include "OSGQFieldView_qt.h"
#include <qapplication.h>

#include <OSGVec3fFields.h>

#include <OSGSimpleGeometry.h>
#include <OSGGeoPropPositions.h>

OSG_USING_NAMESPACE

int main(int argc, char* argv[])
{
    osgInit(argc, argv);
    
    QApplication app(argc, argv);
    
    GeometryPtr  geo    = makeSphereGeo(5, 3);

    QMFieldView *mfView = 
        new QMFieldView(geo->getPositions(), 3, 0, NULL, "mfView");
    
    app.setMainWidget(mfView);
    
    mfView->show();
    
    return app.exec();
}

    
