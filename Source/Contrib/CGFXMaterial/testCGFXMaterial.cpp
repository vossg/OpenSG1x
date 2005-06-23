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
#include <OSGGradientBackground.h>
#include <OSGGeoFunctions.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGCGFXMaterial.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char k, int x, int y);


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr = NULL;

static GLUTWindowPtr _gwin = NullFC;

// The scene
static NodePtr _scene = NullFC;

static CGFXMaterialPtr _cgfxmat = NullFC;

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG CGFX Shader");

    // the connection between GLUT and OpenSG
    _gwin = GLUTWindow::create();
    _gwin->setId(winid);
    _gwin->setSize( 800, 800 );
    _gwin->init();

    // init callbacks
    glutSetWindow(winid);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    const char *effectFile = "BumpGlossedShiny.fx";

    if(argc > 1)
    {
        effectFile = argv[1];
    }

    _cgfxmat = CGFXMaterial::create();
    beginEditCP(_cgfxmat);
        _cgfxmat->setEffectFile(effectFile);
        // this multipass technique leads to a render bug, I have no idea what's wrong :-(
        //_cgfxmat->setTechnique(1);
    endEditCP(_cgfxmat);

    ChunkMaterialPtr mat2 = ChunkMaterial::create();
    MaterialChunkPtr matc = MaterialChunk::create();
    beginEditCP(matc);
        matc->setDiffuse(Color4f(1, 0, 0, 1));
    endEditCP(matc);
    beginEditCP(mat2);
        mat2->addChunk(matc);
        //mat2->addChunk(texc);
    endEditCP(mat2);

    // create root node
    _scene = Node::create();

    GeometryPtr geo1 = makeLatLongSphereGeo(50, 50, 100.0f);
    
    OSG::calcVertexTangents(geo1, 0, Geometry::TexCoords1FieldId, Geometry::TexCoords2FieldId);

    beginEditCP( geo1, Geometry::MaterialFieldMask);
        geo1->setMaterial(_cgfxmat);
    endEditCP(geo1, Geometry::MaterialFieldMask);

    NodePtr sphere1 = Node::create();
    beginEditCP(sphere1, Node::CoreFieldMask);
        sphere1->setCore(geo1);
    endEditCP(sphere1, Node::CoreFieldMask);

    TransformPtr trans1 = Transform::create();
    beginEditCP(trans1);
        trans1->getMatrix().setTranslate(-2 , 0, 0);
    endEditCP(trans1);
    NodePtr transn1 = Node::create();
    beginEditCP(transn1);
        transn1->setCore(trans1);
        transn1->addChild(sphere1);
    beginEditCP(transn1);

    //
    GeometryPtr geo2 = makeLatLongSphereGeo(50, 50, 1.0f);
    
    beginEditCP( geo2, Geometry::MaterialFieldMask);
        geo2->setMaterial(mat2);
    endEditCP(geo2, Geometry::MaterialFieldMask);

    NodePtr sphere2 = Node::create();
    beginEditCP(sphere2, Node::CoreFieldMask);
        sphere2->setCore(geo2);
    endEditCP(sphere2, Node::CoreFieldMask);

    TransformPtr trans2 = Transform::create();
    beginEditCP(trans2);
        trans2->getMatrix().setTranslate(2 , 0, 0);
    endEditCP(trans2);
    NodePtr transn2 = Node::create();
    beginEditCP(transn2);
        transn2->setCore(trans2);
        transn2->addChild(sphere2);
    beginEditCP(transn2);

    beginEditCP(_scene);
        _scene->setCore(Group::create());
        _scene->addChild(transn1);
        _scene->addChild(transn2);
    endEditCP(_scene);

    // create the SimpleSceneManager
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_gwin);

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
    Real32 bumpHeight;

    switch(k)
    {
        case 27:
        case 'q':
            glutDestroyWindow(glutGetWindow());
            delete _mgr;
            subRefCP(_gwin);
            return;
        break;
        case 'r':
            if(_cgfxmat != NullFC)
            {
                // reload cgfx material.
                beginEditCP(_cgfxmat);
                    _cgfxmat->setEffectFile(_cgfxmat->getEffectFile());
                endEditCP(_cgfxmat);
            }
        break;
        case 'w':
            SceneFileHandler::the().write(_scene, "scene.osb.gz", true);
            printf("wrote scene.osb.gz\n");
        break;
        case 'e':
            SceneFileHandler::the().write(_scene, "scene.osg");
            printf("wrote scene.osg\n");
        break;
        case 'b':
            if(_cgfxmat != NullFC && _cgfxmat->getParameter("bumpHeight", bumpHeight))
            {
                bumpHeight += 0.1;
                beginEditCP(_cgfxmat, CGFXMaterial::ParametersFieldMask);
                    _cgfxmat->setParameter("bumpHeight", bumpHeight);
                endEditCP(_cgfxmat, CGFXMaterial::ParametersFieldMask);
                glutPostRedisplay();
            }
        break;
        case 'n':
            if(_cgfxmat != NullFC && _cgfxmat->getParameter("bumpHeight", bumpHeight))
            {
                bumpHeight -= 0.1;
                beginEditCP(_cgfxmat, CGFXMaterial::ParametersFieldMask);
                    _cgfxmat->setParameter("bumpHeight", bumpHeight);
                endEditCP(_cgfxmat, CGFXMaterial::ParametersFieldMask);
                glutPostRedisplay();
            }
        break;
        case 't':
            if(_cgfxmat != NullFC)
            {
                Int32 technique = _cgfxmat->getTechnique();
                technique = 1 - technique;
                printf("setting technique to '%s'\n", _cgfxmat->getTechniqueString(technique).c_str());
                beginEditCP(_cgfxmat, CGFXMaterial::TechniqueFieldMask);
                    _cgfxmat->setTechnique(technique);
                endEditCP(_cgfxmat, CGFXMaterial::TechniqueFieldMask);
                glutPostRedisplay();
            }
        break;
    }

    glutPostRedisplay();
}
