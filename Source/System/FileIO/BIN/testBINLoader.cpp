#include <OSGConfig.h>

#include <iostream>
#include <fstream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGGeometry.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGBackground.h"
#include "OSGGradientBackground.h"

#include "OSGTrackball.h"

#include <OSGSceneFileHandler.h>
#include "OSGBINLoader.h"
#include <OSGVolumeDraw.h>

//#include "OSGActivateColMat.hpp"
using namespace     OSG;

DrawAction          *dact;
RenderAction        *ract;
bool                doRender = true;

NodePtr             root;

NodePtr             file;

WindowPtr           win;

DirectionalLightPtr headlight;

TransformPtr        cam_trans;

Trackball           tball;

int                 mouseb = 0;
int                 lastx = 0, lasty = 0;

/* */
void display(void)
{
    Matrix  m1, m2;

    m1.setRotate(tball.getRotation());
    m2.setTranslate(tball.getPosition());

    m1.mult(m2);
    cam_trans->getSFMatrix()->setValue(m1);

    if(doRender)
        win->render(ract);
    else
        win->draw(dact);
}

/* */
void reshape(int w, int h)
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize(w, h);
}

/* */
void animate(void)
{
    glutPostRedisplay();
}

// tballall stuff
void motion(int x, int y)
{
    Real32  w = win->getWidth(), h = win->getHeight();

    Real32  a = -2. * (lastx / w - .5), b = -2. * (.5 - lasty / h), c = -2. *
        (x / w - .5), d = -2. * (.5 - y / h);

    if(mouseb & (1 << GLUT_LEFT_BUTTON))
    {
        tball.updateRotation(a, b, c, d);
    }
    else if(mouseb & (1 << GLUT_MIDDLE_BUTTON))
    {
        tball.updatePosition(a, b, c, d);
    }
    else if(mouseb & (1 << GLUT_RIGHT_BUTTON))
    {
        tball.updatePositionNeg(a, b, c, d);
    }

    lastx = x;
    lasty = y;
}

/* */
void mouse(int button, int state, int x, int y)
{
    if(state == 0)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            tball.setAutoPosition(true);
            break;
        case GLUT_RIGHT_BUTTON:
            tball.setAutoPositionNeg(true);
            break;
        }

        mouseb |= 1 << button;
    }
    else if(state == 1)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            tball.setAutoPosition(false);
            break;
        case GLUT_RIGHT_BUTTON:
            tball.setAutoPositionNeg(false);
            break;
        }

        mouseb &= ~(1 << button);
    }

    lastx = x;
    lasty = y;
}

/* */
void vis(int visible)
{
    if(visible == GLUT_VISIBLE)
    {
        glutIdleFunc(animate);
    }
    else
    {
        glutIdleFunc(NULL);
    }
}

/* */
void key(unsigned char key, int, int)
{
    switch(key)
    {
    case 27:
        osgExit();
        exit(0);
    case 'z':
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        std::cerr << "PolygonMode: Point." << std::endl;
        break;
    case 'x':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        std::cerr << "PolygonMode: Line." << std::endl;
        break;
    case 'c':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        std::cerr << "PolygonMode: Fill." << std::endl;
        break;
    case 'q':
        glDisable(GL_COLOR_MATERIAL);
        std::cerr << "ColorMaterial disabled." << std::endl;
        break;
    case 'w':
        glEnable(GL_COLOR_MATERIAL);
        std::cerr << "ColorMaterial enabled." << std::endl;
        break;
    case 'd':
        ract->setFrustumCulling(!ract->getFrustumCulling());
        std::cerr <<
            "Culling: " <<
            (ract->getFrustumCulling() ? "on" : "off") <<
            std::endl;
        break;
    case 'f':
        ract->setVolumeDrawing(!ract->getVolumeDrawing());
        std::cerr << "Volume Drawing: " << (ract->getVolumeDrawing() ? "on" : "off") << std::endl;
        break;
    case 'r':
        headlight->setOn(!headlight->getOn());
        std::cerr <<
            "Headlight: " <<
            (headlight->getOn() ? "on" : "off") <<
            std::endl;
        break;
    case 'R':
        doRender = !doRender;
        printf("Now using %s action\n", doRender ? "render" : "draw");
        break;
    }
}

/* */
int main(int argc, char **argv)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << "Param " << i << ":" << argv[i] << std::endl;
    }

    OSG::osgInit(argc, argv);

    char    *inFileName = "tie.bin";

    if(argc > 1)
        inFileName = argv[1];

    std::ifstream in(inFileName, std::ios::binary);
    if(!in)
    {
        std::cerr <<
            "ERROR: Cannot open file " <<
            inFileName <<
            "" <<
            std::endl;
        return -1;
    }

    OSG::BINLoader loader(in);
    loader.read();
    in.close();
    std::cout <<
        "MAIN: " <<
        loader.getRootNode().getFieldContainerId() <<
        " is root" <<
        std::endl;

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutIdleFunc(display);

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glClearColor(0.5, 0.5, 0.5, 1.);

    // OSG
    //    OSGSceneFileHandler::the().print();
    //    FhsFile::touch();
    // create the graph
    // beacon for camera and light
    NodePtr     b1n = Node::create();
    GroupPtr    b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore(b1);
    endEditCP(b1n);

    // transformation
    NodePtr         t1n = Node::create();
    TransformPtr    t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore(t1);
    t1n->addChild(b1n);
    endEditCP(t1n);

    cam_trans = t1;

    // light
    NodePtr dlight = Node::create();
    headlight = DirectionalLight::create();

    beginEditCP(dlight);
    dlight->setCore(headlight);
    endEditCP(dlight);

    beginEditCP(headlight);
    headlight->setAmbient(.3, .3, .3, 1);
    headlight->setDiffuse(1, 1, 1, 1);
    headlight->setSpecular(1, 1, 1, 1);
    headlight->setDirection(0, 0, 1);
    headlight->setBeacon(b1n);
    endEditCP(headlight);

    // root
    root = Node::create();

    GroupPtr    gr1 = Group::create();
    beginEditCP(root);
    root->setCore(gr1);
    root->addChild(t1n);
    root->addChild(dlight);
    endEditCP(root);

    // Load the file
    NodePtr     fileRoot = Node::create();

    //  OSGActivateColMatPtr colMat = OSGActivateColMat::create();
    GroupPtr    gr = Group::create();

    beginEditCP(fileRoot);

    //  fileRoot->setCore(colMat);
    fileRoot->setCore(gr);
    endEditCP(fileRoot);

    beginEditCP(dlight);
    dlight->addChild(fileRoot);
    endEditCP(dlight);

    //   for(UInt32 numFiles = 1; numFiles < argc; numFiles++)
    //    {
    //       file = SceneFileHandler::the().read(argv[1]);
    file = loader.getRootNode();
    beginEditCP(fileRoot);
    fileRoot->addChild(file);
    fileRoot->invalidateVolume();
    endEditCP(fileRoot);

    //    }
    dlight->updateVolume();

    Vec3f   min, max;
    dlight->getVolume().getBounds(min, max);

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    //std::cerr << "Tree: " << std::endl;
    //root->dump();
    // Camera
    PerspectiveCameraPtr    cam = PerspectiveCamera::create();

    cam->setBeacon(b1n);
    cam->setFov(deg2rad(60));
    cam->setNear(1.);
    cam->setFar(100000.);

    // Background
    GradientBackgroundPtr   bkgnd = GradientBackground::create();

    bkgnd->addLine(Color3f(0, 0, 0), 0);
    bkgnd->addLine(Color3f(.5, .5, 0), 0.5);
    bkgnd->addLine(Color3f(.7, .7, 1), 0.5);
    bkgnd->addLine(Color3f(0, 0, 1), 1);

    // Viewport
    ViewportPtr vp = Viewport::create();
    vp->setCamera(cam);
    vp->setBackground(bkgnd);
    vp->setRoot(root);
    vp->setSize(0, 0, 1, 1);

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowPtr   gwin;

    GLint           glvp[4];
    glGetIntegerv(GL_VIEWPORT, glvp);

    gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize(glvp[2], glvp[3]);

    win = gwin;

    win->addPort(vp);

    // Actions
    dact = DrawAction::create();
    ract = RenderAction::create();

    // tball
    /*
	Vec3f pos(min[0] + 0.5 * (max[0] - min[0]),
              min[1] + 0.5 * (max[1] - min[1]),
              max[2] + 1.5 * (max[2] - min[2]));
*/
    Vec3f   pos(0, 0, max[2] + 1.5 * (max[2] - min[2]));

    tball.setMode(Trackball::OSGObject);
    tball.setStartPosition(pos, true);
    tball.setSum(true);
    tball.setTranslationMode(Trackball::OSGFree);
    tball.setTranslationScale(10000.);

    // run...
    glutMainLoop();

    return 0;
}
