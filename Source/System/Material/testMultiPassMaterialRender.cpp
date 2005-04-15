#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGFaceIterator.h>
#include <OSGSimpleSceneManager.h>
#include <OSGGLUTWindow.h>

#include <OSGMaterialChunk.h>
#include <OSGPolygonChunk.h>

#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"
#include "OSGMultiPassMaterial.h"


OSG_USING_NAMESPACE

static SimpleSceneManager   *_mgr;

void display(void)
{
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
    }
}

int main (int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int id=glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    GLUTWindowPtr gwin=GLUTWindow::create();
    gwin->setId(id);
    gwin->init();

    // create the scene
    NodePtr scene = Node::create();
    beginEditCP(scene);
        scene->setCore(Group::create());
    endEditCP(scene);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (scene);

    // create the geometry.
    NodePtr plane = makePlane( 1, 1, 2, 2 );
    NodePtr torus = makeTorus( .2, 1, 16, 8 );

    GeometryPtr plane_geo, torus_geo;
    plane_geo = GeometryPtr::dcast(plane->getCore());
    torus_geo = GeometryPtr::dcast(torus->getCore());

    PolygonChunkPtr pchunk = PolygonChunk::create();
    beginEditCP(pchunk);
        pchunk->setFrontMode(GL_LINE);
        pchunk->setBackMode(GL_LINE);
        pchunk->setOffsetFactor(-1.0);
        pchunk->setOffsetLine(true);
    endEditCP(pchunk);

    // create materials for the plane.
    SimpleMaterialPtr pm1 = SimpleMaterial::create();
    beginEditCP(pm1);
        pm1->setDiffuse( Color3f( 0,1,0 ) );
        pm1->setAmbient( Color3f( 0,1,0 ) );
        pm1->setSpecular( Color3f( 0,0,0 ) );
    endEditCP(pm1);

    SimpleMaterialPtr pm2 = SimpleMaterial::create();
    beginEditCP(pm2);
        pm2->setDiffuse( Color3f( 1,0,0 ) );
        pm2->setAmbient( Color3f( 1,0,0 ) );
        pm2->setSpecular( Color3f( 0,0,0 ) );
        pm2->addChunk(pchunk);
    endEditCP(pm2);

    MultiPassMaterialPtr mppm = MultiPassMaterial::create();
    beginEditCP(mppm);
        mppm->addMaterial(pm1);
        mppm->addMaterial(pm2);
    endEditCP(mppm);

    plane_geo->setMaterial(mppm);

    // create materials for the torus.
    SimpleMaterialPtr tm1 = SimpleMaterial::create();
    beginEditCP(tm1);
        tm1->setDiffuse( Color3f( 0,0,1 ) );
        tm1->setAmbient( Color3f( 0,0,1 ) );
        tm1->setTransparency(0.6);
    endEditCP(tm1);

    SimpleMaterialPtr tm2 = SimpleMaterial::create();
    beginEditCP(tm2);
        tm2->setDiffuse( Color3f( 1,0,0 ) );
        tm2->setAmbient( Color3f( 1,0,0 ) );
        tm2->setSpecular( Color3f( 0,0,0 ) );
        tm2->addChunk(pchunk);
    endEditCP(tm2);

    MultiPassMaterialPtr mptm = MultiPassMaterial::create();
    beginEditCP(mptm);
        mptm->addMaterial(tm1);
        mptm->addMaterial(tm2);
    endEditCP(mptm);

    torus_geo->setMaterial( mptm );

    beginEditCP(scene);
        scene->addChild(plane);
        scene->addChild(torus);
    endEditCP(scene);

    // show the whole scene
    _mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

