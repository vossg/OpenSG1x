
#include "OSGQFieldContainerView_qt.h"
#include <qapplication.h>

#include <OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    QApplication app(argc, argv);

    GeometryPtr geo = makeSphereGeo(5,3);

    QFieldContainerView *pFCView1 = new QFieldContainerView(NULL, "pFCView1");
    QFieldContainerView *pFCView2 = new QFieldContainerView(NULL, "pFCView2");

    pFCView1->setFieldContainer(geo);
    pFCView1->setAspect        (0  );

    pFCView2->setFieldContainer(geo);
    pFCView2->setAspect        (1  );

    app.setMainWidget(pFCView1);

    pFCView1->show();
    pFCView2->show();

    return app.exec();
}

    
