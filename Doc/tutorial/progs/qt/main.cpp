#include <qapplication.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGNode.h>

#include "mainwindow.h"

OSG_USING_NAMESPACE;

int main(int argc, char **argv){
	osgInit(argc, argv);
	
	QApplication app (argc, argv);

	MainWindow main;
	app.setMainWidget(&main);
	main.show();

	int result = app.exec();
	return result;
}
