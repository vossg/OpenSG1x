#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <iostream>
#include <OSGLog.h>
#include <OSGStreamSockConnection.h>
#include <OSGClusterServer.h>
#include <OSGGLUTWindow.h>
#include <OSGRenderAction.h>
#include <OSGOSGWriter.h>
#include <OSGViewport.h>

OSG_USING_NAMESPACE

int             winid;
ClusterServer  *server;
GLUTWindowPtr   window;
RenderAction   *ract;
bool            running=false;

void display()
{
    if(!running)
    {
        server->start();
        running=true;
        glutShowWindow();
    }
    try
    {
        server->render(ract);
        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clearAll();
    } 
    catch(exception &)
    {
#if 0
        SLOG << e.what() << endl;
        delete server;
        osgExit(); 
#else
        // try to restart server
        try
        {
            server->stop();
        }
        catch(...)
        {
        }
        running=false;
        glutHideWindow();
#endif
    }
}

void reshape( int width, int height )
{
    cout << "reshape " << width << " " << height << endl;
	window->resize( width, height );
}

void key(unsigned char key, int /*x*/, int /*y*/)
{
	switch ( key )
	{
        case 'd':
            window->getPort()[0]->getRoot()->dump();
            break;
        case 's':
            ofstream outFileStream( "server.osg" );
            if( !outFileStream )
            {
                SLOG << "Can not open output stream to file: server.osg" << endl;
            }
            else
            {
                OSGWriter writer( outFileStream, 4 );
                writer.write( window->getPort()[0]->getRoot() );
            }
            break;
	}
}

int main(int argc,char **argv)
{
    char           *name          ="ClusterServer";
    char           *connectionType="StreamSock";
    bool           fullscreen     =true;
    string         address        ="";

    for(int i=1;i<argc;i++)
    {
        if(strlen(argv[i])>1 && argv[i][0]=='-')
        {
            switch(argv[i][1])
            {
                case 'm':
                    connectionType="Multicast";
                    break;
                case 'w':
                    fullscreen=false;
                    break;
                case 'a':
                    address=&(argv[i][2]);
                    break;
                case 'h':
                    cout << argv[0] 
                         << "-m "
                         << "-w "
                         << "-aAddress "
                         << endl;
                    cout << "-m        use multicast" << endl;
                    cout << "-w        no fullscreen" << endl;
                    cout << "-aAddress Server network address" << endl;
                    return 0;
            }
        }
        else
            name=argv[i];
    }
    try
    {
        osgInit(argc, argv);
        glutInit(&argc, argv);
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        winid = glutCreateWindow("OpenSG Cluster Client");

        if(fullscreen)
            glutFullScreen();
        /*
        else
            glutReshapeWindow(300,300);
        */

        glutPopWindow();
        glutDisplayFunc(display);       
        glutIdleFunc(display);       
        glutKeyboardFunc(key);
        glutReshapeFunc(reshape);       
        glutSetWindowTitle(name);
        // switch off cursor
        glutSetCursor(GLUT_CURSOR_NONE);
        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_NORMALIZE );
        ract=RenderAction::create();
        window     = GLUTWindow::create();
        window->setId(winid);
        window->init();
        server     = new ClusterServer(window,name,connectionType,address);
        server->start();
        running=true;
        glutMainLoop();
    } 
    catch(exception &e)
    {
        SLOG << e.what() << endl;
        delete server;
        osgExit(); 
    }
    return 0;
}
