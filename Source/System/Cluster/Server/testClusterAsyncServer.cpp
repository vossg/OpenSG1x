#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <iostream>
#include <OSGLog.h>
#include <OSGClusterServer.h>
#include <OSGGLUTWindow.h>
#include <OSGRenderAction.h>
#include <OSGOSGWriter.h>
#include <OSGViewport.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>

OSG_USING_NAMESPACE

int             winid;
ClusterServer  *server;
GLUTWindowPtr   window;
RenderAction   *ract;
bool            running=false;
bool            exitOnError=false;
Barrier        *syncBarrier = NULL;
ThreadBase     *mainThread  = NULL;
ThreadBase     *syncThread  = NULL;
bool            doRun=true;

void syncThreadProc (void *OSG_CHECK_ARG(arg)) 
{               
    while(doRun)
    {
        if(!running)
        {
            server->start();
            glutShowWindow();
        }
        try
        {
            // receive changes into changelist
            server->doSync(true);
            syncBarrier->enter( 2 );
            running=true;
            syncBarrier->enter( 2 );
            OSG::Thread::getCurrentChangeList()->clearAll();
        } 
        catch(OSG_STDEXCEPTION_NAMESPACE::exception &/*e*/)
        {
            if(exitOnError)
            {
                syncBarrier->enter( 2 );
                doRun = running = false;
                syncBarrier->enter( 2 );
                osgExit();
                return;
            }
            else
            {
                // try to restart server
                syncBarrier->enter( 2 );
                running=false;
                syncBarrier->enter( 2 );
                try
                {
                    server->stop();
                }
                catch(...)
                {
                }
                glutHideWindow();
            }
        }
    }
}

void display()
{
    try
    {
        syncBarrier->enter( 2 );
#ifndef OSG_DISABLE_DEPRECATED
        syncThread->getChangeList()->applyToCurrent();
#endif
        syncBarrier->enter( 2 );
        if(!doRun)
        {
            printf("error exit\n");
            exit(0);
        }
        if(running)
        {
            server->doRender(ract);
            server->doSwap();
        }
        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clearAll();
    } 
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        if(exitOnError)
        {
            SLOG << e.what() << std::endl;
            try
            {
                delete server;
            }
            catch(...)
            {
            }
            osgExit();
            exit(0);
        }
        else
        {
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
        }
    }
}

void reshape( int width, int height )
{
    std::cout << "reshape " << width << " " << height << std::endl;
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
            std::ofstream outFileStream( "server.osg" );
            if( !outFileStream )
            {
                SLOG << "Can not open output stream to file: server.osg" 
                     << std::endl;
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
    std::string    address        ="";
    int width=-1,height=300,x=0,y=0;

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
                case 'e':
                    exitOnError=true;
                    break;
                case 'a':
                    address=&(argv[i][2]);
                    break;
                case 'g':
                    if(sscanf(&(argv[i][2]),"%d,%d,%d,%d",
                              &width,&height,&x,&y)!=4)
                    {
                        SWARNING << "Wrong args in -g. Use -gw,h,x,y" 
                                 << std::endl;
                        exit(0);
                    }
                    break;
                case 'h':
                    std::cout << argv[0] 
                              << "-A "
                              << "-m "
                              << "-w "
                              << "-e "
                              << "-gw,h,x,y "
                              << "-aAddress "
                              << std::endl;
                    std::cout << "-m        use multicast" << std::endl;
                    std::cout << "-w        no fullscreen" << std::endl;
                    std::cout << "-e        exit after closed connection" 
                              << std::endl;
                    std::cout << "-g        geometry" << std::endl;
                    std::cout << "-aAddress Server network address" 
                              << std::endl;
                    std::cout << "-A        run asynchron"
                              << std::endl;
                    return 0;
            }
        }
        else
            name=argv[i];
    }
    // exitOnError=true;
    //    exitOnError=true;
    try
    {
        ChangeList::setReadWriteDefault();
        osgInit(argc, argv);
        glutInit(&argc, argv);
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowPosition(x,y);
        if(width>0)
            glutInitWindowSize(width,height);
        winid = glutCreateWindow("OpenSG Cluster Client");
        if(fullscreen)
            glutFullScreen();
        /*
          else
          glutReshapeWindow(300,300);
        */
        if(width>0)
            glutReshapeWindow(width,height);
        glutPositionWindow(x, y);

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

        OSG::Thread::getCurrentChangeList()->clearAll();

        syncBarrier = Barrier::get("syncBarrier");
        // start sync thread
        syncThread=
            dynamic_cast<Thread *>(ThreadManager::the()
                                   ->getThread(NULL));
        if ( syncThread == NULL )   
        {
            std::cerr << "Unable to create syncThread" << std::endl;
            exit(0);
        }
        syncThread->runFunction( syncThreadProc, 1, NULL );

        glutMainLoop();
    } 
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << std::endl;
        delete server;
        osgExit(); 
    }
    return 0;
}
