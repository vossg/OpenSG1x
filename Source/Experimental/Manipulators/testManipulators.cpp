#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGGroup.h>
#include <OSGSimpleMaterial.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>

#include "OSGManipulatorManager.h"

OSG_USING_NAMESPACE

NodePtr         scene        = NullFC;
TransformPtr interTC    = NullFC;
NodePtr         interN        = NullFC;
NodePtr         maniN        = NullFC;

ManipulatorManager *mama;
SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );
NodePtr makeCoordAxes(void);

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    int winid = setupGLUT(&argc, argv);

    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    mgr = new SimpleSceneManager;    
    mama = new ManipulatorManager;

    GroupPtr g = Group::create();
    scene = Node::create();    
    
    interTC = Transform::create();
    interN    = Node::create();
    
    Matrix m;
    m.setIdentity();
    m.setTransform( Vec3f(1.0f, 1.0f, 1.0f) );
    
    beginEditCP(interTC);
    {
        interTC->setMatrix(m);
    }
    endEditCP(interTC);

    beginEditCP(interN);
    {
        interN->setCore(interTC);
        interN->addChild( makeBox(1, 0.2, 0.2, 1, 1, 1) );
    }
    endEditCP(interN);    
                                                    
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(g);
        scene->addChild( makeCoordAxes() );
        scene->addChild(interN);
    }    
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    
    maniN = mama->createManipulator(ManipulatorManager::TRANSLATE);
        
    beginEditCP(interN);
    {
        interN->addChild( maniN );
    }
    endEditCP(interN);
    
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->setClickCenter( false );
    mgr->showAll();
    
    mama->setTarget( interN );
    mama->setViewport( mgr->getWindow()->getPort()[0] );
    
    glutReshapeWindow(600, 600);
    glutMainLoop();
    
    return 0;
}


void display(void)
{
    mgr->redraw();
}


void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
    if (state)
    {
        if( mama->isActive() )
        {            
            mama->mouseButtonRelease(button, x, y);
        }
        
        mgr->mouseButtonRelease(button, x, y);        
    }
    else
    {
        Line l;

        l = mgr->calcViewRay(x, y);

        IntersectAction *act = IntersectAction::create();

        act->setLine( l );
        act->apply( scene );

        if ( (act->didHit()) && (mama->activate( act->getHitObject()) ) )
        {
            mama->mouseButtonPress(button, x, y);
        }
        
        mgr->mouseButtonPress(button, x, y);            
    }

    glutPostRedisplay();
}


void motion(int x, int y)
{
    if( mama->isActive() )
    {                
        mama->mouseMove(x, y);
    }
    else
        mgr->mouseMove(x, y);
        
    glutPostRedisplay();
}


void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    exit(1);
    case ' ':
    {
        maniN->setActive(false);
        glutPostRedisplay();                    
        break;
    }
    case 'r':            
    case 't':
    case 's':            
    {
        maniN->setActive(true);
        if (k == 't')
        {
            mama->changeManipulator( ManipulatorManager::TRANSLATE );
        }
        else if (k == 'r')
        {
            mama->changeManipulator( ManipulatorManager::ROTATE );
        }
        else if (k == 's')
        {
            mama->changeManipulator( ManipulatorManager::SCALE );
        }
        glutPostRedisplay();                    
        break;
    }
    case 'w':
        SceneFileHandler::the().write(scene, "scene.osb");
    break;
    }
}


int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("Manipulator Demo");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

GeometryPtr makeCoordAxesGeo(void)
{
    GeometryPtr axesG = Geometry::create();

    GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_LINES    );
        type->addValue(GL_TRIANGLES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);
    
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(6);
        lens->addValue(9);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
       
    GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
        // the 6 points of the three Lines
        pnts->addValue(Pnt3f( 0, 0, 0 ));
        pnts->addValue(Pnt3f( 1, 0, 0 ));
        
        pnts->addValue(Pnt3f( 0, 0, 0 ));
        pnts->addValue(Pnt3f( 0, 1, 0 ));
        
        pnts->addValue(Pnt3f( 0, 0, 0 ));
        pnts->addValue(Pnt3f( 0, 0, 1 ));

        // the 9 points of the three Triangles
        pnts->addValue(Pnt3f(   1,   0,   0 ));    
        pnts->addValue(Pnt3f( 0.8, 0.2, 0.2 ));    
        pnts->addValue(Pnt3f( 0.8,-0.2,-0.2 ));    
        
        pnts->addValue(Pnt3f(   0,   1,   0 ));    
        pnts->addValue(Pnt3f( 0.2, 0.8, 0.2 ));    
        pnts->addValue(Pnt3f(-0.2, 0.8,-0.2 ));    

        pnts->addValue(Pnt3f(   0,   0,   1 ));
        pnts->addValue(Pnt3f( 0.2, 0.2, 0.8 ));
        pnts->addValue(Pnt3f(-0.2,-0.2, 0.8 ));
    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);

    GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
    {
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));

        colors->addValue(Color3f(0, 1, 0));
        colors->addValue(Color3f(0, 1, 0));

        colors->addValue(Color3f(0, 0, 1));
        colors->addValue(Color3f(0, 0, 1));

        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));

        colors->addValue(Color3f(0, 1, 0));
        colors->addValue(Color3f(0, 1, 0));
        colors->addValue(Color3f(0, 1, 0));

        colors->addValue(Color3f(0, 0, 1));
        colors->addValue(Color3f(0, 0, 1));
        colors->addValue(Color3f(0, 0, 1));
    }
    endEditCP  (colors, GeoPositions3f::GeoPropDataFieldMask);
   
    beginEditCP(axesG);
    {
        axesG->setTypes    (type);
        axesG->setLengths  (lens);
        axesG->setPositions(pnts);
        axesG->setColors(colors);
        axesG->setMaterial(getDefaultUnlitMaterial());   
    }
    endEditCP  (axesG);    
    
    return axesG;
}

NodePtr makeCoordAxes(void)
{
    NodePtr axesN = Node::create();

    beginEditCP(axesN, Node::CoreFieldMask);
    {
        axesN->setCore( makeCoordAxesGeo() );
    }
    endEditCP  (axesN, Node::CoreFieldMask);

    return axesN;
}