// OpenSG example: testSHL
//
// Demonstrates the use of the SHLChunk
// Implements a simple bumpmapping via vertex and fragment shader.

// Headers
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGSHLChunk.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr;
// The scene
static NodePtr _scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

static std::string _vertex_shader =
"void main(void)\n"
"{\n"
"    gl_Position = ftransform();\n"
"}\n"
"\n";

static std::string _fragment_shader =
"void main (void)\n"
"{\n"
"    gl_FragColor = vec4 (1.0, 0.0, 0.0, 1.0);\n"
"\n"
"}\n";

static std::string _geometry_shader =
"#version 120\n"
"#extension GL_EXT_geometry_shader4 : enable\n"
"\n"
"void main(void)\n"
"{\n"
"      mat4x4 bezierBasis=mat4x4( 1, -3, 3, -1, 0, 3, -6, 3 , 0, 0, 3, -3 , 0, 0, 0, 1);\n"
"      for(int i=0; i<64; i++)\n"
"      {\n"
"            float t = i / (64.0-1.0);\n"
"            vec4 tvec= vec4(1, t, t*t, t*t*t);\n"
"            vec4 b =tvec*bezierBasis;\n"
"            vec4 p = gl_PositionIn[0]*b.x+ gl_PositionIn[1]*b.y+ gl_PositionIn[2]*b.z+ gl_PositionIn[3]*b.w;\n"
"            gl_Position =p;\n"
"            EmitVertex();\n"
"      }\n"
"      EndPrimitive();\n"
"\n"
"}\n";


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

    // Create the shader material
    ChunkMaterialPtr cmat = ChunkMaterial::create();

    MaterialChunkPtr matc = MaterialChunk::create();
    beginEditCP(matc);
        matc->setAmbient(Color4f(0.1, 0.1, 0.1, 1.0));
        matc->setDiffuse(Color4f(0.3, 0.3, 0.3, 1.0));
        matc->setSpecular(Color4f(0.8, 0.8, 0.8, 1.0));
        matc->setShininess(100);
        matc->setLit(true);
    endEditCP(matc);

    SHLChunkPtr shl = SHLChunk::create();
    beginEditCP(shl);
        shl->getProgramParameterNames().push_back(GL_GEOMETRY_INPUT_TYPE_EXT);
        shl->getProgramParameterValues().push_back(GL_LINES_ADJACENCY_EXT);

        shl->getProgramParameterNames().push_back(GL_GEOMETRY_OUTPUT_TYPE_EXT);
        shl->getProgramParameterValues().push_back(GL_LINE_STRIP);

        //glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &count);
        shl->getProgramParameterNames().push_back(GL_GEOMETRY_VERTICES_OUT_EXT);
        shl->getProgramParameterValues().push_back(1024);

        //shl->setVertexProgram(_vertex_shader);
        //shl->setFragmentProgram(_fragment_shader);
        shl->setGeometryProgram(_geometry_shader);
    endEditCP(shl);

    beginEditCP(cmat);
        cmat->addChunk(shl);
    endEditCP(cmat);


    // create root node
    _scene = Node::create();

    // create torus
    GeometryPtr geo = makeTorusGeo(.8, 1.8, 128, 128);
    beginEditCP( geo, Geometry::MaterialFieldMask);
        geo->setMaterial(cmat);
    endEditCP(geo, Geometry::MaterialFieldMask);

    NodePtr torus = Node::create();
    beginEditCP(torus, Node::CoreFieldMask);
        torus->setCore(geo);
    endEditCP(torus, Node::CoreFieldMask);

    // add torus to scene
    GroupPtr group = Group::create();
    beginEditCP(_scene);
        _scene->setCore(group);
        _scene->addChild(torus);
    endEditCP(_scene);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

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
            SceneFileHandler::the().write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG CG Shader");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}


