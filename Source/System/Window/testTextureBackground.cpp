
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>

#include <OSGTextureChunk.h>

#include <OSGTextureBackground.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

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
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
    // Create the textured material
    UChar8 imgdata[] =
      {  255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 };
   
    ImagePtr img = Image::create();
    beginEditCP(img);
    if(argc > 1)
        img->read(argv[1]);
    else
        img->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );
    endEditCP(img);
    addRefCP(img);
   
    TextureChunkPtr tex = TextureChunk::create();
    beginEditCP(tex);
    tex->setImage(img);
    tex->setMinFilter(GL_NEAREST);
    tex->setMagFilter(GL_LINEAR);
    tex->setEnvMode(GL_REPLACE);
    tex->setEnvMode(GL_REPLACE);
    tex->setWrapS(GL_CLAMP);
    endEditCP(tex);
    
    // Background
    TextureBackgroundPtr bkgnd = TextureBackground::create();
    
    beginEditCP(bkgnd);
        bkgnd->setTexture(tex);
        // add some user defined texture coordinates.
        // default values are (0 0) (1 0) (1 1) (0 1)
        //bkgnd->getTexCoords().push_back(Vec2f(0.0f, 0.0f));
        //bkgnd->getTexCoords().push_back(Vec2f(0.5f, 0.0f));
        //bkgnd->getTexCoords().push_back(Vec2f(0.5f, 0.5f));
        //bkgnd->getTexCoords().push_back(Vec2f(0.0f, 0.5f));
    endEditCP(bkgnd);
    
    // take the viewport
    ViewportPtr vp = gwin->getPort(0);

    beginEditCP(vp);
        vp->setBackground(bkgnd);
    endEditCP  (vp);

    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
