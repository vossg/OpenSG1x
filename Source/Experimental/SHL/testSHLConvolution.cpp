// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Implements a simple bumpmapping via vertex and fragment shader.

// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>
#include <OSGPolygonForeground.h>
#include <OSGTextureGrabForeground.h>
#include <OSGSceneFileHandler.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGSHLChunk.h>


// vertex shader program for bump mapping in surface local coordinates
static std::string _vp_program =
"    void main(void)\n"
"    {\n"
"        gl_Position = ftransform();\n"
"        gl_TexCoord[0] = gl_MultiTexCoord0;\n"
"    }\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"uniform vec2 offset[5];\n"
"uniform vec4 scaleFactor;\n"
"uniform sampler2D baseImage;\n"
"\n"
"void main()\n"
"{\n"
"    int i;\n"
"    vec4 sum = vec4(0.0);\n"
"\n"
"    for (i = 0; i < 5 ; i++)\n"
"        sum += texture2D(baseImage, gl_TexCoord[0].st + offset[i]);\n"
"\n"
"    gl_FragColor = sum * scaleFactor;\n"
"}\n";

// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr;

static NodePtr _scene = NullFC;
static PolygonForegroundPtr _pf = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    if(argc > 1)
    {
        _scene = SceneFileHandler::the().read(argv[1], NULL);
    }
    else
    {
        // create a box.
        NodePtr box = makeBox(1.0f, 1.0f, 1.0f, 1, 1, 1);
    
        // create root node
        _scene = Node::create();
        beginEditCP(_scene);
            _scene->setCore(Group::create());
            _scene->addChild(box);
        endEditCP(_scene);
    }

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // --------------------

    ImagePtr img = Image::create();
    beginEditCP(img);
    img->set(Image::OSG_RGB_PF, 512, 512);
    endEditCP(img);
    addRefCP(img);

    TextureChunkPtr texc = TextureChunk::create();
    beginEditCP(texc);
        texc->setImage(img);
        texc->setMinFilter(GL_NEAREST);
        texc->setMagFilter(GL_NEAREST);
        texc->setEnvMode(GL_REPLACE);
    endEditCP(texc);

    TextureGrabForegroundPtr fg = TextureGrabForeground::create();
    beginEditCP(fg);
        fg->setTexture(texc);
    endEditCP(fg);

    Real32 over = 1.0f;
    Real32 stepw = over / Real32(img->getWidth());
    Real32 steph = over / Real32(img->getHeight());

    MFVec2f offset;
    offset.resize(5);
    offset[0] = Vec2f(0.0f, 0.0f);
    offset[1] = Vec2f(0.0f, steph);
    offset[2] = Vec2f(0.0f, -steph);
    offset[3] = Vec2f(stepw, 0.0f);
    offset[4] = Vec2f(-stepw, 0.0f);

    SHLChunkPtr shlc = SHLChunk::create();
    beginEditCP(shlc);
        shlc->setVertexProgram(_vp_program);
        shlc->setFragmentProgram(_fp_program);
        shlc->setUniformParameter("offset", offset);
        shlc->setUniformParameter("scaleFactor", Vec4f(0.2f, 0.2f, 0.2f, 0.2f));
        shlc->setUniformParameter("baseImage", 0);
    endEditCP(shlc);

    ChunkMaterialPtr cmat = ChunkMaterial::create();
    beginEditCP(cmat);
        cmat->addChunk(texc);
        cmat->addChunk(shlc);
    endEditCP(cmat);

    _pf = PolygonForeground::create();

    beginEditCP(_pf);
        _pf->setMaterial(cmat);
        _pf->getTexCoords().push_back(Vec3f(0.0f, 0.0f, 0.0f));
        _pf->getPositions().push_back(Pnt2f(0.0f, 0.0f));
        _pf->getTexCoords().push_back(Vec3f(1.0f, 0.0f, 0.0f));
        _pf->getPositions().push_back(Pnt2f(1.0f, 0.0f));
        _pf->getTexCoords().push_back(Vec3f(1.0f, 1.0f, 0.0f));
        _pf->getPositions().push_back(Pnt2f(1.0f, 1.0f));
        _pf->getTexCoords().push_back(Vec3f(0.0f, 1.0f, 0.0f));
        _pf->getPositions().push_back(Pnt2f(0.0f, 1.0f));
 
        _pf->setNormalizedX(true);
        _pf->setNormalizedY(true);
    endEditCP(_pf);

    // take the viewport
    ViewportPtr vp = gwin->getPort(0);

    beginEditCP(vp);
        vp->getForegrounds().push_back(fg);
        vp->getForegrounds().push_back(_pf);
    endEditCP  (vp);

    // show the whole scene
    _mgr->showAll();

    // enable local lights.
    RenderAction *ract = (RenderAction *) _mgr->getAction();
    ract->setLocalLights(true);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
  // render scene
  _mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
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
        case 'q':
            exit(1);
        break;
        case 'w':
            SceneFileHandler::the().write(_scene, "scene.osb", true);
            printf("wrote scene.osb\n");
        break;
        case 'f':
            beginEditCP(_pf);
                _pf->setActive(!_pf->getActive());
            endEditCP(_pf);
        printf("Filtering '%s'\n", _pf->getActive() ? "enabled" : "disabled");
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(512, 512);

    int winid = glutCreateWindow("OpenSG GLSL Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}


