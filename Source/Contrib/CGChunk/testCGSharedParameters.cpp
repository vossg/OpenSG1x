// OpenSG example: testCG
//
// Demonstrates the use of the CGChunk
// Ok this creates 1 CGChunk with different parameter sets for each geometry.

// Headers
#include <GL/glut.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>

#include <OSGGradientBackground.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>
#include <OSGMaterialGroup.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGCGChunk.h>
#include <OSGCGParameterChunk.h>

#include <Cg/cgGL.h>

// vertex shader program
static std::string _vp_program =
"struct a2v\n"
"{\n"
"    float4 Position     : POSITION;\n"
"};\n"
"\n"
"struct v2p\n"
"{\n"
"    float4 Position     : POSITION;\n"
"};\n"
"\n"
"\n"
"void main(in a2v IN, out v2p OUT)\n"
"{\n"
"    float4x4 ModelViewProj = glstate.matrix.mvp;\n"
"    float4x4 ModelViewIT   = glstate.matrix.invtrans.modelview[0];\n"
"\n"
"    OUT.Position = mul(ModelViewProj, IN.Position);\n"
"}\n";

// fragment shader program
static std::string _fp_program =
"struct v2p\n"
"{\n"
"    float4 Position     : POSITION;\n"
"};\n"
"\n"
"struct p2f\n"
"{\n"
"    float4 Color : COLOR0;\n"
"};\n"
"\n"
"// fragment program\n"
"void main(in v2p IN,\n"
"          out p2f OUT,\n"
"          uniform float3 SurfaceColor)\n"
"{\n"
"    OUT.Color = float4(SurfaceColor, 1.0);\n"
"}\n";


// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr;
// The scene
static NodePtr _scene;

static Int32 _animation = 1;
static CGParameterChunkPtr _cgparameter = NullFC;


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
    GLUTWindowPtr gwin = GLUTWindow::create();
    beginEditCP(gwin);
        gwin->setId(winid);
        gwin->setSize( 800, 800 );
        gwin->init();
    endEditCP(gwin);

    // create root node
    _scene = makeCoredNode<Group>();

    GeometryPtr geo = makeBoxGeo(0.5, 0.5, 0.5, 1, 1, 1);

    // share the chunk
    CGChunkPtr cg = CGChunk::create();
    beginEditCP(cg);
        cg->setVertexProfile(CG_PROFILE_ARBVP1);
        cg->setVertexProgram(_vp_program);
        cg->setFragmentProfile(CG_PROFILE_ARBFP1);
        cg->setFragmentProgram(_fp_program);
    endEditCP(cg);

    Int32 size = 4;
    
    // start color
    Vec3f sc(0.0, 0.0, 0.0);
    
    // end color
    Vec3f ec(1.0, 1.0, 1.0);

    Real32 sr = (ec[0] - sc[0]) / Real32((size*2));
    Real32 sg = (ec[1] - sc[1]) / Real32((size*2));
    Real32 sb = (ec[2] - sc[2]) / Real32((size*2));
    
    Vec3f color(sc);

    Int32 x = - size;
    Int32 y = - size;
    Int32 z = - size;

    UInt32 iterations = size*2 * size*2 * size*2;

    printf("Creating %u cubes ...\n", iterations);
    for(UInt32 i=0;i<iterations;++i)
    {
        ChunkMaterialPtr cmat = ChunkMaterial::create();

        // ok use one CGChunk and n CGParameterChunks
        CGParameterChunkPtr cgparameter = CGParameterChunk::create();
        beginEditCP(cgparameter);
            cgparameter->setCGChunk(cg);
            cgparameter->setUniformParameter("SurfaceColor", color);
        endEditCP(cgparameter);
        _cgparameter = cgparameter;

        beginEditCP(cmat);
            cmat->addChunk(cg);
            cmat->addChunk(cgparameter);
        endEditCP(cmat);
    
        TransformPtr trans;
        NodePtr trans_node = makeCoredNode<Transform>(&trans);
        beginEditCP(trans);
            trans->getMatrix().setTranslate(Real32(x), Real32(y), Real32(z));
        endEditCP(trans);

        MaterialGroupPtr mg;
        NodePtr mg_node = makeCoredNode<MaterialGroup>(&mg);
        beginEditCP(mg, MaterialGroup::MaterialFieldMask);
            mg->setMaterial(cmat);
        endEditCP(mg, MaterialGroup::MaterialFieldMask);

        NodePtr geonode = Node::create();
        beginEditCP(geonode, Node::CoreFieldMask);
            geonode->setCore(geo);
        endEditCP(geonode, Node::CoreFieldMask);
        
        beginEditCP(mg_node);
            mg_node->addChild(geonode);
        endEditCP(mg_node);

        beginEditCP(trans_node);
            trans_node->addChild(mg_node);
        endEditCP(trans_node);
    
        // add to scene
        beginEditCP(_scene);
            _scene->addChild(trans_node);
        endEditCP(_scene);
        
        // ----
        ++x;
        color[0] += sr;

        if(x == size)
        {
            x = - size;
            ++y;
            color[0] = sc[0];
            color[1] += sg;
            if(y == size)
            {
                y = - size;
                ++z;
                color[1] = sc[1];
                color[2] += sb;
            }
        }
    }


    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

    // create a gradient background.
    GradientBackgroundPtr gback = GradientBackground::create();
    beginEditCP(gback, GradientBackground::LineFieldMask);
        gback->clearLines();
        gback->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gback->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gback, GradientBackground::LineFieldMask);

    WindowPtr win = _mgr->getWindow();
    beginEditCP(win);
        for(int i=0;i<win->getPort().size();++i)
        {
            ViewportPtr vp = win->getPort()[i];
            beginEditCP(vp);
                vp->setBackground(gback);
            endEditCP(vp);
        }
    endEditCP(win);
        
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
    Real64 t = OSG::getSystemTime();
    // render scene
    _mgr->redraw();
    t = OSG::getSystemTime() - t;
    if(t > 0.0)
        printf("fps: %f\r", 1.0f / Real32(t));
    else
        printf("fps: very fast ...\r");
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
    static Real32 season = 0.0f; 
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
        case 'a':
            _animation = 1 - _animation;
        break;
        case 'c':
            if(_cgparameter != NullFC)
            {
                beginEditCP(_cgparameter);
                    _cgparameter->setUniformParameter("SurfaceColor", Vec3f(1.0f, 1.0f, 1.0f));
                endEditCP(_cgparameter);
            }
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

    glutIdleFunc(display);

    return winid;
}
