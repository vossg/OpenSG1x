// OpenSG Example: Cal3D Character

// Standad includes
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleGeometry.h>
#include <OSGSHLChunk.h>
#include <OSGGradientBackground.h>

// The new core
#include "OSGCharacterModel.h"
#include "OSGCharacter.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

CharacterModelPtr model;
CharacterPtr charac;
SHLChunkPtr shader;

Real32 timeScale = 1;
Int32 animation = 0;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{ 
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <cfg file>" << std::endl;
        exit(1);
    }

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
    
    // Get the shader for hardware skinning
    
    shader = SHLChunk::create();
    
    beginEditCP(shader);
    if(!shader->readVertexProgram("bonesShader.vp"))
    {
        subRefCP(shader);
        shader = NullFC;
    }
    else
    {
        if(!shader->readFragmentProgram("bonesShader.fp"))
        {
            subRefCP(shader);
            shader = NullFC;
        }
        else
        {
            endEditCP(shader);
        }
    }
   
    // Load the character model
    
    model = CharacterModel::create();
    beginEditCP(model);
    model->setConfigFile(argv[1]);
    model->setShader(shader);
    endEditCP(model);
    
    // Create the Scene
    NodeRefPtr scene;
    scene = Node::create();
    GroupPtr grcore = Group::create();
    
    beginEditCP(scene);
    scene->setCore(grcore);

    // Add a Plane for the ground
    
    TransformNodePtr tr;
    
    tr = Transform::create();
    
    beginEditCP(tr);
    
    tr.node()->addChild(makePlane(200, 200, 16, 16));
    
    Matrix m;
    m.setTransform(Vec3f(0,0,-1));
    tr->setMatrix(m);
    
    endEditCP(tr);
    
    scene->addChild(tr.node());
   
    
    // Create a character
    
    charac = Character::create();

    beginEditCP(charac, Character::ModelFieldMask | 
                        Character::CurrentAnimationFieldMask);
    charac->setModel(model);
    charac->setCurrentAnimation(0);
    endEditCP(  charac, Character::ModelFieldMask | 
                        Character::CurrentAnimationFieldMask);
 
    scene->addChild(makeNodeFor(charac));

    endEditCP(scene);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);


    // Background
    GradientBackgroundPtr gbkgnd = GradientBackground::create();

    beginEditCP(gbkgnd, GradientBackground::LineFieldMask);
    gbkgnd->addLine( Color3f(.7,.7,1.), 0.0 );
    gbkgnd->addLine( Color3f(0, 0, 1), 0.5 );
    gbkgnd->addLine( Color3f(0, 0, .2), 1.0 );
    endEditCP  (gbkgnd, GradientBackground::LineFieldMask);
    
    mgr->getWindow()->getPort(0)->setBackground(gbkgnd);
 
    // show the whole scene
    mgr->showAll();
    
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
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    exit(1);
    
    case ' ':   
                beginEditCP(charac, Character::TimeScaleFieldMask);
                if(charac->getTimeScale() == 0)
                    charac->setTimeScale(timeScale);
                else
                    charac->setTimeScale(0);
                endEditCP(charac, Character::TimeScaleFieldMask);
                break;
    
    case 'a':   animation = (++animation) % model->getNumAnimations();
                beginEditCP(charac, Character::CurrentAnimationFieldMask);
                charac->setCurrentAnimation(animation);
                endEditCP(charac, Character::CurrentAnimationFieldMask);
                SLOG << "Animation set to " << animation << endLog;
                break;
    
    case 's':   animation = (--animation < 0) ? model->getNumAnimations() - 1
                                              : animation;
                beginEditCP(charac, Character::CurrentAnimationFieldMask);
                charac->setCurrentAnimation(animation);
                endEditCP(charac, Character::CurrentAnimationFieldMask);
                SLOG << "Animation set to " << animation << endLog;
                break;
    
    case 'z':   timeScale *= 0.9;
                beginEditCP(charac, Character::TimeScaleFieldMask);
                charac->setTimeScale(timeScale);
                endEditCP(charac, Character::TimeScaleFieldMask);
                SLOG << "Time scale set to " << timeScale << endLog;
                break;
    
    case 'x':   timeScale *= 1.1;
                beginEditCP(charac, Character::TimeScaleFieldMask);
                charac->setTimeScale(timeScale);
                endEditCP(charac, Character::TimeScaleFieldMask);
                SLOG << "Time scale set to " << timeScale << endLog;
                break;
    
    case 'h':   beginEditCP(charac, Character::UseShaderForGeometryFieldMask);
                charac->setUseShaderForGeometry(true);
                endEditCP(charac, Character::UseShaderForGeometryFieldMask);
                SLOG << "Switched to shaders" << endLog;
                break;
    
    case 'r':   
                beginEditCP(shader);
                if(!shader->readVertexProgram("bonesShader.vp"))
                    fprintf(stderr, "Couldn't read vertex program "
                                    "'bonesShader.vp'\n");
                if(!shader->readFragmentProgram("bonesShader.fp"))
                    fprintf(stderr, "Couldn't read vertex program "
                                    "'bonesShader.fp'\n");
                endEditCP(shader);
                SLOG << "Shader reloaded" << endLog;
                break;                
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
