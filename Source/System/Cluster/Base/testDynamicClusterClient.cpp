// testDynamicclusterClient
//
// OpenSG cluster client program where you can dynamicly connect/disconnect
// to the servers.
// 
// To test it, run 
//   ./testClusterServer -w pipe0 &
//   ./testDynamicClusterClient pipe0
//
// press 'c' to connect to the servers and 'd' to disconnect. 


#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGMultiDisplayWindow.h>
#include <OSGSceneFileHandler.h>
#include <OSGRemoteAspect.h>

#include <string>
#include <vector>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager          *_mgr = NULL;
GLUTWindowPtr               _client_win = NullFC;
MultiDisplayWindowPtr       _cluster_win = NullFC;
NodePtr                     _root = NullFC;
std::vector<std::string>    _pipenames;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    std::cout << "start a cluster server with './testClusterServer -w pipe0'\n"
                 "press 'c' to connect to the servers.\n"
                 "press 'd' to disconnect from the servers.\n"
                 "press 'n' to delete current scene.\n"
                 "press 't' to create a torus.\n"
                 "press 'l' to load scene 'tie.wrl'.\n"
              << std::endl;
    
    // OSG init
    ChangeList::setReadWriteDefault();
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    _client_win= GLUTWindow::create();
    _client_win->setId(winid);
    _client_win->init();
    _client_win->setSize(300,300);
    
    for(UInt32 i=0;i<argc-1;++i)
    {
        if(argv[i+1] != NULL)
            _pipenames.push_back(argv[i+1]);
    }

    if(_pipenames.empty())
        _pipenames.push_back("pipe0");
    
    _root = Node::create();
    beginEditCP(_root);
        _root->setCore(Group::create());
    endEditCP(_root);
    
    // create default scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);
    beginEditCP(_root);
        _root->addChild(scene);
    endEditCP(_root);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_client_win );
    _mgr->setRoot  (_root);

    // show the whole scene
    _mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

static void connectCluster(void)
{
    if(_cluster_win != NullFC)
        return;

    ViewportPtr clientvp = _client_win->getPort()[0];
    
    // create the viewports for the cluster just a simple one ...
    ViewportPtr vp = Viewport::create();
    beginEditCP(vp);
        vp->setCamera    (_mgr->getCamera());
        vp->setBackground(clientvp->getBackground());
        vp->setRoot      (clientvp->getRoot());
        vp->setSize      (0,0, 1,1);
    endEditCP(vp);

    // the connection between this client and the servers
    _cluster_win = MultiDisplayWindow::create();

    // all changes must be enclosed in beginEditCP and endEditCP
    // otherwise the changes will not be transfered over the network.
    beginEditCP(_cluster_win);

        for(UInt32 i=0;i<_pipenames.size();++i)
            _cluster_win->getServers().push_back(_pipenames[i]);
        // dummy size for navigator
        _cluster_win->setSize(300,300);
        _cluster_win->addPort(vp);

    endEditCP(_cluster_win);

    // now store all changes and clear current change list.
    RemoteAspect::storeChangeList(Thread::getCurrentChangeList());
    Thread::getCurrentChangeList()->clearAll();

    // merge all fieldcontainers in the scene to the current changelist.
    RemoteAspect::restoreChangeList(Thread::getCurrentChangeList());

    // initialize window
    _cluster_win->init();
    
    // if we don't do this our created changelist is stored again
    // in the store list with the next render update.
    _cluster_win->render((RenderAction *) _mgr->getAction());
    Thread::getCurrentChangeList()->clearAll();

    glutPostRedisplay();
}

static void disconnectCluster(void)
{
    if(_cluster_win == NullFC)
        return;

    // merge all fieldcontainers in the scene to the current changelist.
    RemoteAspect::restoreChangeList(Thread::getCurrentChangeList());
    _cluster_win->render((RenderAction *) _mgr->getAction());
    Thread::getCurrentChangeList()->clearAll();

    ViewportPtr vp = _cluster_win->getPort(0);
    subRefCP(_cluster_win);
    _cluster_win = NullFC;

    if(vp != NullFC)
        subRefCP(vp);
    
    // merge all created, addRefd, subRefd, destroyed into the created list.
    ChangeList *cl = OSG::Thread::getCurrentChangeList();
    RemoteAspect::storeChangeList(cl);
    cl->clearAll();
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    // redraw the client window
    _mgr->redraw();

    try
    {
        if(_cluster_win != NullFC)
        {
            // redraw the server windows
            _cluster_win->render((RenderAction *) _mgr->getAction());
        }
    }
    
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        //printf("error: '%s'\n", e.what());
        printf("ClusterServer was killed!\n");
        ViewportPtr vp = _cluster_win->getPort(0);
        subRefCP(_cluster_win);
        _cluster_win = NullFC;

        if(vp != NullFC)
            subRefCP(vp);
    } 

    // merge all created, addRefd, subRefd, destroyed into the created list.
    ChangeList *cl = OSG::Thread::getCurrentChangeList();
    RemoteAspect::storeChangeList(cl);
    // clear change list. If you don't clear the changelist,
    // then the same changes will be transmitted a second time
    // in the next frame. 
    cl->clearAll();
}

// react to size changes
void reshape(int w, int h)
{
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            OSG::osgExit();
            exit(0);
        }
        case 'n':
            beginEditCP(_root);
                while(_root->getNChildren() > 0)
                    _root->subChild(_root->getChild(0));
            endEditCP(_root);
            glutPostRedisplay();
        break;
        case 'l':
        {
            NodePtr scene = SceneFileHandler::the().read("tie.wrl");
            if(scene != NullFC)
            {
                beginEditCP(_root);
                    _root->addChild(scene);
                endEditCP(_root);
                _mgr->showAll();
                glutPostRedisplay();
            }
        }
        break;
        case 't':
        {
            NodePtr scene = makeTorus(.5, 2, 16, 16);
            beginEditCP(_root);
                _root->addChild(scene);
            endEditCP(_root);
            _mgr->showAll();
            glutPostRedisplay();
        }
        break;
        case 'c':
            connectCluster();
        break;
        case 'd':
            disconnectCluster();
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
