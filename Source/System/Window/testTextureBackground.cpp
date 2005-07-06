
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
TextureBackgroundPtr g_bkgnd;
Real32 g_distortion=0.0f;
UInt16 g_hor=0;
UInt16 g_vert=0;
Vec2f g_center(0.5,0.5);
GLenum g_pMode=GL_FILL;
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
		break;
	case 'k':
	    g_distortion-=0.01f;
	    beginEditCP(g_bkgnd);//,TextureBackground::RadialDistortionFieldMask);
	    g_bkgnd->setRadialDistortion(g_distortion);
	    endEditCP(g_bkgnd);//,TextureBackground::RadialDistortionFieldMask);
	    break;
	case 'K':
	    g_distortion+=0.01f;
	    beginEditCP(g_bkgnd);//,TextureBackground::RadialDistortionFieldMask);
	    g_bkgnd->setRadialDistortion(g_distortion);
	    endEditCP(g_bkgnd);//,TextureBackground::RadialDistortionFieldMask);
	    break;
	case 'v':
	    if(g_vert>0)
	    {
		g_vert--;
		beginEditCP(g_bkgnd);//,TextureBackground::VertFieldMask);
		g_bkgnd->setVert(g_vert);
		endEditCP(g_bkgnd);//,TextureBackground::VertFieldMask);
	    }
	    break;
	case 'V':
	    g_vert++;
	    beginEditCP(g_bkgnd);//,TextureBackground::VertFieldMask);
	    g_bkgnd->setVert(g_vert);
	    endEditCP(g_bkgnd);//,TextureBackground::VertFieldMask);
	    break;
	case 'h':
	    if(g_hor>0)
	    {
		g_hor--;
		beginEditCP(g_bkgnd);//,TextureBackground::HorFieldMask);
		g_bkgnd->setHor(g_hor);
		endEditCP(g_bkgnd);//,TextureBackground::HorFieldMask);
	    }
	    break;
	case 'H':
	    g_hor++;
	    beginEditCP(g_bkgnd);//,TextureBackground::HorFieldMask);
	    g_bkgnd->setHor(g_hor);
	    endEditCP(g_bkgnd);//,TextureBackground::HorFieldMask);
	    break;
	case 'x':
	    if(g_center.x()>=0.05)

	    {
		g_center[0]-=.05f;
		beginEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
		g_bkgnd->setCenterOfDistortion(g_center);
		endEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
	    }
	    break;
	case 'X':
	    if(g_center.x()<=0.95)

	    {
		g_center[0]+=.05f;
		beginEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
		g_bkgnd->setCenterOfDistortion(g_center);
		endEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
	    }
	    break;
	case 'y':
	    if(g_center.y()>=0.05)

	    {
		g_center[1]-=.05f;
		beginEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
		g_bkgnd->setCenterOfDistortion(g_center);
		endEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
	    }
	    break;
	case 'Y':
	    if(g_center.y()<=0.95)

	    {
		g_center[1]+=.05f;
		beginEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
		g_bkgnd->setCenterOfDistortion(g_center);
		endEditCP(g_bkgnd);//,TextureBackground::CenterOfDistortionFieldMask);
	    }
	    break;
	case 'p':
	    g_pMode=(g_pMode==GL_FILL)?GL_LINE:GL_FILL;
	    glPolygonMode(GL_FRONT,g_pMode);
	    break;



    }
    printf("radial_distortion:%.2f , center=(%.1f,%.1f) , hor=%d, vert=%d\n", g_distortion, g_center.x(), g_center.y(), g_hor, g_vert);
}
void help()
{
    printf("--------------------------------------------------\n");
    printf("keybindings:\n");
    printf("K / k : increase / decrease radial_distortion\n");
    printf("x / X : move center of projection on x axis\n");
    printf("y / Y : move center of projection on y axis\n");
    printf("V / v : increase / decrease vertical subdivision\n");
    printf("H / h : increase / decrease horizontal subdivision\n");
    printf("--------------------------------------------------\n");
}

int main(int argc, char **argv)
{
    help();
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
    tex->setWrapT(GL_CLAMP);
    endEditCP(tex);

    // Background
    g_bkgnd = TextureBackground::create();

    beginEditCP(g_bkgnd);
        g_bkgnd->setTexture(tex);
        // add some user defined texture coordinates.
        // default values are (0 0) (1 0) (1 1) (0 1)
        //bkgnd->getTexCoords().push_back(Vec2f(0.0f, 0.0f));
        //bkgnd->getTexCoords().push_back(Vec2f(2.0f, 0.0f));
        //bkgnd->getTexCoords().push_back(Vec2f(2.0f, 2.0f));
        //bkgnd->getTexCoords().push_back(Vec2f(0.0f, 2.0f));
    endEditCP(g_bkgnd);

    // take the viewport
    ViewportPtr vp = gwin->getPort(0);

    beginEditCP(vp);
        vp->setBackground(g_bkgnd);
    endEditCP  (vp);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
