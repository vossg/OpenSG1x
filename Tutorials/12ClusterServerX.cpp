// OpenSG Tutorial Example: Cluster Server
//
// This is a full functional OpenSG cluster server. In OpenSG
// the terms server and client are used similar to X11. The
// application is the client. Instances that are used for 
// rendering are called server.
//
// See the ClusterClient.cpp for an example of how to use them.

#include <iostream>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>
// The Cluster server definition
#include <OpenSG/OSGClusterServer.h>
// The GLUT-OpenSG connection class
#include <OpenSG/OSGXWindow.h>
// Render action definition. 
#include <OpenSG/OSGRenderAction.h>

OSG_USING_NAMESPACE

// local glut window
XWindowPtr   window;
// render action
RenderAction   *ract;
// pointer the the cluster server instance
ClusterServer  *server;

// forward declaration so we can have the interesting stuff upfront
void display();
void reshape( int width, int height );

int wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

// Initialize GLUT & OpenSG and start the cluster server
int main(int argc,char **argv)
{
    int             winid;
    char           *name          ="ClusterServer";
    char           *connectionType="StreamSock";
    bool            fullscreen     =true;
    std::string     address        ="";
    char           *opt;


    // evaluate params
    for(int a=1 ; a<argc ; ++a)
    {
        if(argv[a][0] == '-')
        {
            switch(argv[a][1])
            {
                case 'm': connectionType="Multicast";
                          break;
                case 'p': connectionType="SockPipeline";
                          break;
                case 'w': fullscreen=false;
                          break;
                case 'a': address = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(address == argv[argc])
                          { 
                              SLOG << "address missing" << endLog;
                              return 0;
                          }
                          std::cout << address << endLog;
                          break;
                default:  std::cout << argv[0] 
                                    << "-m "
                                    << "-p "
                                    << "-w "
                                    << "-a address "
                                    << endLog;
                          return 0;
            }
        }
        else
        {
            name=argv[a];
        }
    }
    try
    {
        ChangeList::setReadWriteDefault();
	
        // init OpenSG
        osgInit(argc, argv);

        static int snglBuf[] = {GLX_RGBA, 
                                GLX_DEPTH_SIZE, 16, 
                                None};
        static int dblBuf [] = {GLX_RGBA, 
                                GLX_DEPTH_SIZE, 16, 
                                GLX_DOUBLEBUFFER, 
                                None};

        GLboolean doubleBuffer = GL_FALSE;

        // X init
        DisplayP dpy = XOpenDisplay(NULL);

        if(dpy == NULL) 
        {
            std::cerr << "Error: Could not open display!" << std::endl;
        }

        int dummy;

        if(!glXQueryExtension( dpy, &dummy, &dummy))
        {
            std::cerr << "Error: X server has no OpenGL GLX extension"
                      << std::endl;
        }
        
        XVisualInfo *vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);

        if(vi == NULL) 
        {
            vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);

            if(vi == NULL)
            {
                std::cerr << "no RGB visual with depth buffer" << std::endl;
            }
            
            doubleBuffer = GL_FALSE;
        }

        if(vi->c_class != TrueColor)
        {
            std::cerr << "TrueColor visual required for this program"
                      << std::endl;
        }
        
        Colormap cmap = XCreateColormap(dpy, 
                                        RootWindow(dpy, vi->screen), 
                                        vi->visual, 
                                        AllocNone);
        XSetWindowAttributes swa;

        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = 
            ExposureMask      | 
            ButtonPressMask   | 
            ButtonReleaseMask |
            KeyPressMask      |
            Button1MotionMask |
            Button2MotionMask |
            Button3MotionMask | 
            StructureNotifyMask;
        
        // Create Window
        
        // Create a Window and connect it to the main display dpy
        X11Window hwin = XCreateWindow(dpy, 
                                       RootWindow(dpy, vi->screen), 
                                       0, 0, 300, 300, 
                                       0, 
                                       vi->depth,
                                       InputOutput, 
                                       vi->visual, 
                                       CWBorderPixel | 
                                       CWColormap    | 
                                       CWEventMask, 
                                       &swa );
        
        XSetStandardProperties(dpy, hwin, "testWindowX", "testWindowX", 
                               None, argv, argc, NULL);
        
        if(fullscreen == true)
        {
            Atom noDecorAtom = XInternAtom(dpy, 
                                           "_MOTIF_WM_HINTS",
                                           0);
            
            if(noDecorAtom == None) 
            {
                fprintf(stderr,
                        "Could not intern X atom for _MOTIF_WM_HINTS.\n");
            }
            
            struct NoDecorHints 
            {
                long flags;
                long functions;
                long decorations;
                long input_mode;
            };
            
            NoDecorHints oHints;
            
            oHints.flags = 2;
            oHints.decorations = 0;
            
            XChangeProperty(dpy, 
                            hwin,
                            noDecorAtom, 
                            noDecorAtom, 
                            32,
                            PropModeReplace, 
                            (unsigned char *) &oHints, 4);

        }
        

        // create the render action
        ract=RenderAction::create();

        // setup the OpenSG Glut window
        window     = XWindow::create();
        window->setDisplay ( dpy );
        window->setWindow ( hwin );    
        window->init();
 
        XEvent        event;

        XMapWindow(dpy, hwin);
        XIfEvent(dpy, &event, wait_for_map_notify, (char *)hwin);

        if(fullscreen == true)
        {
            XMoveWindow  (dpy, hwin, 0, 0);
            XResizeWindow(dpy, hwin,
                          DisplayWidth (dpy, vi->screen),
                          DisplayHeight(dpy, vi->screen));

            static char data[1] = {0};

            Cursor cursor;
            Pixmap blank;
            XColor dummyCol;
            
            blank = XCreateBitmapFromData(dpy, 
                                          hwin,
                                          data, 1, 1);

            cursor = XCreatePixmapCursor(dpy, 
                                         blank, 
                                         blank,
                                         &dummyCol, &dummyCol, 0, 0);

            XFreePixmap(dpy, blank);

            XDefineCursor(dpy,
                          hwin, 
                          cursor);
            XFlush(dpy);
        }

        window->activate();
       
        glEnable( GL_LIGHTING );
        glEnable( GL_LIGHT0 );
        glEnable( GL_NORMALIZE );

        // create the cluster server
        server     = new ClusterServer(window,name,connectionType,address);
        // start the server
        server->start();

        Real32 w,h,a,b,c,d;
        bool   stopIt = false;
        int ip;

        while(!stopIt) 
        {
            while(ip = XPending(dpy))
            {
                XNextEvent(dpy, &event);

                switch (event.type) 
                {
                    case ConfigureNotify:
                    {
                        reshape(event.xconfigure.width,
                                event.xconfigure.height);
                    }                                                   
                    break;

                    case Expose:
                        display();
                        break;

                } 
                
            }

            display();
        }   
    }
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << endLog;
        delete server;
        osgExit(); 
    }
    return 0;
}

/* render loop */
void display()
{
    try
    {
        // receive scenegraph and do rendering
        server->render(ract);
        // clear changelist 
        OSG::Thread::getCurrentChangeList()->clearAll();
    } 
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << endLog;
        // try to restart server
        server->stop();
        // start server, wait for client to connect
        server->start();
    }
}

/* window reshape */
void reshape( int width, int height )
{
    // set new window size
	window->resize( width, height );
}
