/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qfiledialog.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>

void MainWindow::load()
{
    QString s(QFileDialog::getOpenFileName(QString::null, "Szenenformate (*.wrl *.osg *.bin)"));
    if (!s.isEmpty()) {
	char *filename;
	filename = (char*)s.latin1();
	NodePtr n = SceneFileHandler::the().read(filename);
	if (n != NullFC)
	    osgWidget->getManager().setRoot(n);
	else
	    osgWidget->getManager().setRoot(makeTorus(0.5,2,16,16));
    }
}
