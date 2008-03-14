// OpenSG Tutorial Example: Phong Shader with OpenGL Materials
//
// This example shows how to use a GLSL Phong shader with materials brought
// along with the Model.
// It shows how to add/remove the phong shader chunk and how to use the
// OpenGL Materials though built-in variables like gl_FrontMaterial.

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGGradientBackground.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

using namespace std;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager            *_mgr         = NULL;

bool                           phong_active = false;
std::vector<ChunkMaterialPtr>  materials;
SHLChunkPtr                    phong_chunk  = NullFC;

NodePtr                        scene        = NullFC;


//----------------------------------------------------
//phong_chunk Shader
//----------------------------------------------------
// vertex shader program.
static std::string _vp_program =
"\n"
"varying vec3 ViewDirection;\n"
"varying vec3 fvObjectPosition;\n"
"varying vec3 Normal;\n"
"   \n"
"void main( void )\n"
"{\n"
"   gl_Position = ftransform();\n"
"    \n"
"   fvObjectPosition = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
"   \n"
"   ViewDirection  = - fvObjectPosition.xyz;\n"
"   Normal         = gl_NormalMatrix * gl_Normal;\n"
"   gl_FrontColor  = gl_FrontMaterial.diffuse;\n"
"   \n"
"}\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"vec4 fvAmbient  = vec4(0.36, 0.36, 0.36, 1.0);\n"
"vec4 fvSpecular = vec4(0.7,  0.7,  0.7,  1.0);\n"
"vec4 fvDiffuse  = vec4(0.5,  0.5,  0.5,  1.0);\n"
"float fSpecularPower = 25.0;\n"
"\n"
"uniform sampler2D baseMap;\n"
"uniform int useTexture;\n"
"\n"
"varying vec2 Texcoord;\n"
"varying vec3 ViewDirection;\n"
"varying vec3 fvObjectPosition;\n"
"varying vec3 Normal;\n"
"\n"
"void main( void )\n"
"{\n"
"   vec3  fvLightDirection = normalize( gl_LightSource[0].position.xyz - fvObjectPosition.xyz);\n"
"   vec3  fvNormal         = normalize( Normal );\n"
"   float fNDotL           = dot( fvNormal, fvLightDirection ); \n"
"   \n"
"   vec3  fvReflection     = normalize( ( ( 2.0 * fvNormal ) * fNDotL ) - fvLightDirection ); \n"
"   vec3  fvViewDirection  = normalize( ViewDirection );\n"
"   float fRDotV           = max( 0.0, dot( fvReflection, fvViewDirection ) );\n"
"   \n"
"   vec4  fvBaseColor      = gl_Color;\n"
"   \n"
"   vec4  fvTotalAmbient   = fvAmbient * fvBaseColor; \n"
"   vec4  fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; \n"
"   vec4  fvTotalSpecular  = fvSpecular * ( pow( fRDotV, fSpecularPower ) );\n"
"  \n"
"   gl_FragColor = ( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular );\n"
"}\n";

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);


// ---------------------------------------------------------------------------------

// redraw the window
void display(void)
{
    _mgr->redraw();
}

// ---------------------------------------------------------------------------------

void update(void)
{
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------------

SHLChunkPtr createPhongShaderMaterial(){

    SHLChunkPtr _shl = SHLChunk::create();

    beginEditCP(_shl);
        _shl->setVertexProgram(_vp_program);
        _shl->setFragmentProgram(_fp_program);
    endEditCP(_shl);

    return _shl;
}

// ---------------------------------------------------------------------------------

ChunkMaterialPtr getChunkMaterial(OSG::NodePtr node)
{
    NodeCorePtr      pCore = node->getCore();
    ChunkMaterialPtr cm    = NullFC;
    
    if((pCore != NullFC) && 
       (pCore->getType().isDerivedFrom(MaterialGroup::getClassType())))
    {
        MaterialGroupPtr g = MaterialGroupPtr::dcast(pCore);
        cm = ChunkMaterialPtr::dcast(g->getMaterial());
    }
    else if((pCore != NullFC) &&
            (pCore->getType().isDerivedFrom(Geometry::getClassType())))
    {
        GeometryPtr g = GeometryPtr::dcast(pCore);
        cm = ChunkMaterialPtr::dcast(g->getMaterial());
    }
    
    return cm;
}

// ---------------------------------------------------------------------------------

void getAllMaterials(NodePtr node, std::vector<ChunkMaterialPtr> &mats)
{
    ChunkMaterialPtr cm = getChunkMaterial(node);
    
    if(cm != NullFC)
    {
        mats.push_back(cm);
    }
    
    for(int i = 0; i < node->getNChildren(); ++i)
        getAllMaterials(node->getChild(i), mats);
}

// ---------------------------------------------------------------------------------

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    if(argc >= 2)
        scene = SceneFileHandler::the().read(argv[1]);
    else
        scene = SceneFileHandler::the().read("Data/tie.wrl");
    
    if(scene == NullFC)
        scene = makeTorus(0.3, 4, 16, 64);

    // init material
    phong_chunk = createPhongShaderMaterial();
    
    // the phong chunk will be added/removed materials, but it may not die
    // will being removed.
    addRefCP(phong_chunk);

    // get all the Materials of the current scene
    getAllMaterials(scene, materials);

    // add the phong material chunk to every found material
    for(int i = 0; i < materials.size(); ++i)
    {
        beginEditCP(materials[i]);
            (materials[i])->addChunk(phong_chunk);
        endEditCP(materials[i]);
    }
    phong_active = true;

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    beginEditCP(gwin);
        gwin->setId(winid);
        gwin->init (     );
    endEditCP(gwin);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow      (gwin );
    _mgr->setRoot        (scene);
    _mgr->turnHeadlightOn(     );

    // show the whole scene
    _mgr->showAll();

    // create a gradient background.
    GradientBackgroundPtr gbg = GradientBackground::create();
    beginEditCP(gbg, GradientBackground::LineFieldMask);
        gbg->clearLines();
        gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gbg, GradientBackground::LineFieldMask);
    
    //set gradient background
    beginEditCP(gwin);
        ViewportPtr vp = gwin->getPort(0);
        beginEditCP(vp);
            vp->setBackground(gbg);
        endEditCP(vp);
    endEditCP(gwin);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------------

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------------

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------------

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    GeometryPtr geo;

    switch(k)
    {
        case '1':   
        {
            if(phong_active == false)
            {
                for (int i = 0; i < materials.size(); ++i)
                {
                    beginEditCP(materials[i]);
                        (materials[i])->addChunk(phong_chunk);
                    endEditCP(materials[i]);
                }
                phong_active = true;
                cout << "Phong Shader" << endl;
            }
            break;
        }
        case '2':
        {
            if(phong_active == true)
            {
                for (int i = 0; i < materials.size(); ++i)
                {
                    beginEditCP(materials[i]);
                        (materials[i])->subChunk(phong_chunk);
                    endEditCP(materials[i]);
                }
                phong_active = false;
                cout << "Standard OpenGL" << endl;
            }
            break;
        }
        case 27:
                    OSG::osgExit();
                    exit(0);
        break;
        case 'x':
                    SceneFileHandler::the().write(_mgr->getRoot(), "scene.osb.gz", true);
                    printf("wrote scene.\n");
        break;
    }
}

// ---------------------------------------------------------------------------------

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG Shader Material");
    
    cout << "OpenSG Tutorial Example: Phong Shader with OpenGL Materials" << endl;
    cout << "Press Keys 1/2 to switch between Standard OpenGL "
         << "and Phong Shader visualization" << endl;

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutIdleFunc(update);

    return winid;
}

