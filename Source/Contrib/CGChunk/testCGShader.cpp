// OpenSG example: testCGShader
//
// Demonstrates the use of the CGChunk
// Implements a simple bumpmapping via vertex and fragment cg shader.

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

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGCGChunk.h>

#include <Cg/cgGL.h>

// vertex shader program
static std::string _vp_program =
"struct a2v\n"
"{\n"
"    float4 Position     : POSITION;\n"
"    float2 Texcoord     : TEXCOORD0;\n"
"    //float4 Color      : COLOR0;\n"
"    float4 Normal       : NORMAL;\n"
"    //float4 Tangent      : TANGENT;\n"
"};\n"
"\n"
"struct v2p\n"
"{\n"
"    float4 Position     : POSITION;\n"
"    float4 Color        : COLOR0;\n"
"    float2 Texcoord0    : TEXCOORD0;\n"
"    float2 Texcoord1    : TEXCOORD1;\n"
"};\n"
"\n"
"\n"
"void main(in a2v IN, out v2p OUT)\n"
"{\n"
"    float4x4 ModelViewProj = glstate.matrix.mvp;\n"
"    float4x4 ModelViewIT   = glstate.matrix.invtrans.modelview[0];\n"
"\n"
"    OUT.Position = mul(ModelViewProj, IN.Position);\n"
"\n"
"    float3 normalVec = normalize(mul(ModelViewIT, IN.Normal).xyz);\n"
"\n"
"    float4 LightVec = glstate.light[0].position;\n"
"    float3 lightVec = normalize(LightVec.xyz);\n"
"\n"
"\n"
"    float3 eyeVec = float3(0.0, 0.0, 1.0);\n"
"    float3 halfVec = normalize((glstate.light[0].half).xyz);\n"
"\n"
"    float diffuse = dot(normalVec, lightVec.xyz); // calculate diffuse component\n"
"    float specular = dot(normalVec, halfVec); // calculate specular component\n"
"    float4 lighting = lit(diffuse, specular, glstate.material.shininess);\n"
"\n"
"    // - Pre-computed products of light colors with the corresponding\n"
"    // front material colors\n"
"    float3 ambientProd = (glstate.lightprod[0].ambient).rgb;\n"
"    float3 diffProd = (glstate.lightprod[0].diffuse).rgb;\n"
"    float3 specProd = (glstate.lightprod[0].specular).rgb;\n"
"\n"
"    OUT.Color.rgb=lighting.x*ambientProd+lighting.y*diffProd+lighting.z*specProd;\n"
"    //OUT.Color.a  = IN.Color.a;\n"
"\n"
"    OUT.Texcoord0 = IN.Texcoord;\n"
"    OUT.Texcoord1 = IN.Texcoord;\n"
"}\n";

// fragment shader program
static std::string _fp_program =
"struct v2p\n"
"{\n"
"    float4 Position     : POSITION;\n"
"    float4 Diffuse      : COLOR0;\n"
"    float2 Texcoord0    : TEXCOORD0;\n"
"    float2 Texcoord1    : TEXCOORD1;\n"
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
"          uniform sampler2D tex0,\n"
"          uniform sampler2D tex1)\n"
"{\n"
"    float4 color = tex2D(tex0, IN.Texcoord0);\n"
"    float4 normal = tex2D(tex1, IN.Texcoord1);\n"
"    //float4 diffuse = float4(1, 1, 1, 0.5);\n"
"\n"
"    OUT.Color = color * dot(2.0 * (normal - 0.5), 2.0 * (IN.Diffuse - 0.5));\n"
"}\n";


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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf("Usage: testCGShader [base texture filename] [normal map filename]\n");
    char *base_img_name = "wood.jpg";
    char *normal_map_img_name = "normalmap.jpg";

    Color4f tmp;

    if( argc > 1 )
        base_img_name = argv[1];
    if( argc > 2 )
        normal_map_img_name = argv[2];

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

    // Read the image for the base texture
    ImagePtr base_img = Image::create();
    if(!base_img->read(base_img_name))
    {
        fprintf(stderr, "Couldn't read base texture '%s'!\n", base_img_name);
        return 1;
    }

    ImagePtr normal_map_img = Image::create();
    if(!normal_map_img->read(normal_map_img_name))
    {
        fprintf(stderr, "Couldn't read normalmap texture '%s'!\n", normal_map_img_name);
        return 1;
    }

    ChunkMaterialPtr cmat = ChunkMaterial::create();

    MaterialChunkPtr matc = MaterialChunk::create();
    beginEditCP(matc);
        matc->setAmbient(Color4f(0.1, 0.1, 0.1, 1.0));
        matc->setDiffuse(Color4f(0.3, 0.3, 0.3, 1.0));
        matc->setSpecular(Color4f(0.8, 0.8, 0.8, 1.0));
        matc->setShininess(100);
        matc->setLit(true);
    endEditCP(matc);

    // we use the glstate in the cg program so we force
    // to use the CG_PROFILE_ARBVP1 and CG_PROFILE_ARBFP1 extensions.

    CGChunkPtr cg = CGChunk::create();
    beginEditCP(cg);
        cg->setVertexProfile(CG_PROFILE_ARBVP1);
        cg->setVertexProgram(_vp_program);
        cg->setFragmentProfile(CG_PROFILE_ARBFP1);
        cg->setFragmentProgram(_fp_program);
    endEditCP(cg);

    TextureChunkPtr tex_base = TextureChunk::create();
    beginEditCP(tex_base);
        tex_base->setImage(base_img);
        tex_base->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
        tex_base->setMagFilter(GL_LINEAR);
        tex_base->setWrapS(GL_REPEAT);
        tex_base->setWrapT(GL_REPEAT);
        tex_base->setEnvMode(GL_MODULATE);
    endEditCP(tex_base);

    TextureChunkPtr tex_normal_map = TextureChunk::create();
    beginEditCP(tex_normal_map);
        tex_normal_map->setImage(normal_map_img);
        tex_normal_map->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
        tex_normal_map->setMagFilter(GL_LINEAR);
        tex_normal_map->setWrapS(GL_REPEAT);
        tex_normal_map->setWrapT(GL_REPEAT);
        tex_normal_map->setEnvMode(GL_MODULATE);
    endEditCP(tex_normal_map);

    beginEditCP(cmat);
        cmat->addChunk(matc);
        cmat->addChunk(cg);
        cmat->addChunk(tex_base);
        cmat->addChunk(tex_normal_map);
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


