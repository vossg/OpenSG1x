#include "OpenSGWidget.h"

//constructor
OpenSGWidget::OpenSGWidget(QGLFormat f, QWidget *parent, const char *name ) : QGLWidget( f, parent, name ){	
	mMgr = new SimpleSceneManager;
	mPwin = PassiveWindow::create();
	mMgr->setWindow(mPwin);
}

SimpleSceneManager *OpenSGWidget::getManager(void){
	return mMgr;
}
 
void OpenSGWidget::initializeGL(){
	mPwin->init();	
}

void OpenSGWidget::resizeGL(int width, int height){
	mMgr->resize(width,height);
}

// this replaces the display function
void OpenSGWidget::paintGL(){
	mMgr->redraw();
	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f(2.5,2.5,0);
		glVertex3f(-2.5,2.5,0);
		glVertex3f(-2.5,-2.5,0);
		glVertex3f(2.5,-2.5,0);
	glEnd();
}

void OpenSGWidget::mousePressEvent(QMouseEvent *ev){
	UInt32 button;
	
	// translate the button value from qt to OpenSG
	switch (ev->button()){
		case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
		case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
		case RightButton: button = SimpleSceneManager::MouseRight;  break;
		default:          return;
	}
	
	//passs the event to the manager object
	mMgr->mouseButtonPress(button, ev->x(), ev->y());
	update();
}

void OpenSGWidget::mouseReleaseEvent(QMouseEvent *ev){
     UInt32 button;

	switch (ev->button()){
		case LeftButton:  button = SimpleSceneManager::MouseLeft;   break;
		case MidButton:   button = SimpleSceneManager::MouseMiddle; break;
		case RightButton: button = SimpleSceneManager::MouseRight;  break;
		default:          return;
	}
     
     mMgr->mouseButtonRelease(button, ev->x(), ev->y());
     update();
 }

void OpenSGWidget::mouseMoveEvent(QMouseEvent *ev){
	mMgr->mouseMove(ev->x(), ev->y());
	update();
}

void OpenSGWidget::wheelEvent(QWheelEvent *ev){
	mMgr->mouseButtonPress(ev->delta() > 0 ? SimpleSceneManager::MouseUp : SimpleSceneManager::MouseDown, ev->x(), ev->y());
    
	ev->accept();
	update();
}

int main( int argc, char **argv ){
     osgInit(argc,argv);

	//fire up the widget
     QApplication application(argc, argv);
     OpenSGWidget widget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::DirectRendering));

     NodePtr scene;

	//Load stuff from the command line, 
	//if present
     if(argc > 1){
         scene = Node::create();
         GroupPtr g = Group::create();

         beginEditCP(scene);
         	scene->setCore(g);

         	for(UInt16 i = 1; i < argc; ++i)
			scene->addChild(SceneFileHandler::the().read(argv[i]));
         endEditCP(scene);
     }else{
         scene = makeTorus(.5, 3, 16, 16);
     }

     widget.getManager()->setRoot(scene);
     widget.getManager()->showAll();

     application.setMainWidget( &widget );
     widget.show();
	 // replaces the glutMainLoop()
	 // giving control to the QT Main Loop
     return application.exec();
}

