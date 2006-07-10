
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>

#include <OSGSimpleTexturedMaterial.h>

#include <OSGDisplayFilterForeground.h>
#include <OSGSolidBackground.h>
#include <OSGSceneFileHandler.h>
#include <OSGResolutionDisplayFilter.h>
#include <OSGColorDisplayFilter.h>
#include <OSGDistortionDisplayFilter.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

ColorDisplayFilterPtr colorFilterPtr;
DistortionDisplayFilterPtr distortionFilterPtr;
ResolutionDisplayFilterPtr resolutionFilterPtr;


// redraw the window
void display(void)
{
    static Time lastTime = 0; 
    static UInt32 frames = 0, lastFrame = 0;
    
    ++frames;
    Time now = getSystemTime();
    
    if(now - 4 > lastTime)
    {
        if(lastTime != 0)
        {
            char title[200];
            sprintf(title, "%.2f fps", 
                            (frames - lastFrame) / (now - lastTime) );
            printf("%s\n", title);
        }
        lastTime = now;
        lastFrame = frames;
    }
    
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);

    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:    osgExit();
            exit(1);
        case 'c':
            beginEditCP(colorFilterPtr);
            colorFilterPtr->setEnabled(!colorFilterPtr->getEnabled());
            endEditCP(colorFilterPtr);
            break;
        case 'r':
            beginEditCP(resolutionFilterPtr);
            resolutionFilterPtr->setEnabled(!resolutionFilterPtr->getEnabled());
            endEditCP(resolutionFilterPtr);
            break;
        case 'd':
            beginEditCP(distortionFilterPtr);
            distortionFilterPtr->setEnabled(!distortionFilterPtr->getEnabled());
            endEditCP(distortionFilterPtr);
            break;
    }
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int id=glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    GLUTWindowPtr gwin=GLUTWindow::create();
    gwin->setId(id);
    gwin->init();

    // create the scene
//    NodePtr scene = makeTorus(.5, 2, 16, 16);
    NodePtr scene = Node::create();
    beginEditCP(scene);
    scene->setCore(Group::create());
    endEditCP(scene);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
    DisplayFilterForegroundPtr fg = DisplayFilterForeground::create();

    beginEditCP(fg);
    // add filter
    endEditCP(fg);

    // take the viewport
    ViewportPtr vp = gwin->getPort(0);

    beginEditCP(vp);
    vp->getForegrounds().push_back(fg);    
    endEditCP  (vp);

    colorFilterPtr = ColorDisplayFilter::create();
    distortionFilterPtr = DistortionDisplayFilter::create();
    resolutionFilterPtr = ResolutionDisplayFilter::create();

    beginEditCP(colorFilterPtr);
    beginEditCP(resolutionFilterPtr);
    beginEditCP(distortionFilterPtr);
    beginEditCP(fg);
    colorFilterPtr->setMatrix(osg::Matrix(0,0,1,0,
                                          1,0,0,0,
                                          0,1,0,0,
                                          0,0,0,1));
    resolutionFilterPtr->setDownScale(0.25);

    distortionFilterPtr->setColumns(2);
    distortionFilterPtr->setRows(2);
    distortionFilterPtr->getPositions().push_back(Vec2f(0,.5));
    distortionFilterPtr->getPositions().push_back(Vec2f(.5,0));
    distortionFilterPtr->getPositions().push_back(Vec2f(.5,1));
    distortionFilterPtr->getPositions().push_back(Vec2f(1,.5));
    
    fg->getFilter().push_back(colorFilterPtr);
    fg->getFilter().push_back(resolutionFilterPtr);
    fg->getFilter().push_back(distortionFilterPtr);

    endEditCP(distortionFilterPtr);
    endEditCP(colorFilterPtr);
    endEditCP(resolutionFilterPtr);
    endEditCP(fg);

    for(UInt32 a=1 ; a<argc ;a++)
    {
        NodePtr file = SceneFileHandler::the().read(argv[a],0);
        if(file != NullFC)
            scene->addChild(file);
        else
            std::cerr << "Couldn't load file, ignoring " << argv[a] << std::endl;
    }
	if ( scene->getNChildren() == 0 )
	{
        scene->addChild(makeTorus( .5, 2, 16, 16 ));
//        scene->addChild(makeBox(.6,.6,.6,5,5,5));
    }

    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
