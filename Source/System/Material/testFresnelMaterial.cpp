
#include <stdio.h>

#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGFresnelMaterial.h>

OSG_USING_NAMESPACE

static SimpleSceneManager   *_mgr;
static Real32               _index = 0.0f;
static Real32               _scale = 1.0f;
static Real32               _bias  = 1.0f;
static FresnelMaterialPtr   _fresnel = NullFC;

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
    
    _mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w,h);

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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:
            osgExit();
            exit(1);
        break;
        case 'i':
            _index += 0.1;
            beginEditCP(_fresnel);
                _fresnel->setIndex(_index);
            endEditCP(_fresnel);
        break;
        case 'I':
            _index -= 0.1;
            beginEditCP(_fresnel);
                _fresnel->setIndex(_index);
            endEditCP(_fresnel);
        break;
        case 's':
            _scale += 0.1;
            beginEditCP(_fresnel);
                _fresnel->setScale(_scale);
            endEditCP(_fresnel);
        break;
        case 'S':
            _scale -= 0.1;
            beginEditCP(_fresnel);
                _fresnel->setScale(_scale);
            endEditCP(_fresnel);
        break;
        case 'b':
            _bias += 0.1;
            beginEditCP(_fresnel);
                _fresnel->setBias(_bias);
            endEditCP(_fresnel);
        break;
        case 'B':
            _bias -= 0.1;
            beginEditCP(_fresnel);
                _fresnel->setBias(_bias);
            endEditCP(_fresnel);
        break;
    }
    
    printf("index = %f scale = %f bias = %f\n", _index, _scale, _bias);
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
    NodePtr scene = makeTorus(.5, 2, 32, 32);
    //NodePtr scene = makePlane(1.0, 1.0, 1, 1);
    
    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (scene);
    
    // crate a default texture.
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
   
    _fresnel = FresnelMaterial::create();
    beginEditCP(_fresnel);
        _fresnel->setAmbient(Color3f(0.1f, 0.1f, 0.2f));
        _fresnel->setDiffuse(Color3f(0.2f, 0.2f, 0.8f));
        _fresnel->setSpecular(Color3f(0.8f, 0.8f, 0.8f));
        _fresnel->setShininess(10.0f);
        _fresnel->setIndex(0.0f);
        _fresnel->setScale(1.0f);
        _fresnel->setBias(1.0f);
        _fresnel->setImage(img);
    endEditCP(_fresnel);
    
    GeometryPtr geo = GeometryPtr::dcast(scene->getCore());
    
    beginEditCP(geo);
        geo->setMaterial(_fresnel);
    endEditCP(geo);

    // show the whole scene
    _mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
