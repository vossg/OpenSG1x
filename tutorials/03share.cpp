
// Use a transformation to move objects

#include <GL/glut.h>

#include <OpenSG/OSGConfig.h>

// The Group core
#include <OpenSG/OSGGroup.h>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// number of copies to create
const UInt16 ncopies = 10;

TransformPtr trans[ncopies];

// Standard GLUT callback functions
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    for(UInt16 i=0; i<ncopies; ++i)
    {
        m.setTransform(Vec3f(osgsin(t / 1000.f + i * 4 * ncopies / Pi ), 
                             osgcos(t / 1500.f + i * 6 * ncopies / Pi ), 
                             osgsin(t / 2000.f + i * 7 * ncopies / Pi )));
    
        // set the transform's matrix
        beginEditCP(trans[i]);
        trans[i]->setMatrix(m);
        endEditCP(trans[i]);
    }
  
    mgr->redraw();
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    // create the scene
    // this time, create the geometry core only

    GeometryPtr torus = makeTorusGeo( .5, 2, 16, 16 );

    // create the scene
    // the scene has a single group with ncopies transformation below,
    // each of these carries a Node that shared the geometry
    
    // create the root Node
    NodePtr scene = Node::create();
    GroupPtr g = Group::create();
    
    beginEditCP(scene);
    scene->setCore(g);
    
    // create the copied geometry nodes and their transformations
    for(UInt16 i=0; i<ncopies; ++i)
    {
        NodePtr geonode=Node::create();
        
        beginEditCP(geonode);
        geonode->setCore(torus);
        endEditCP(geonode);

        NodePtr transnode=Node::create();
        
        trans[i]=Transform::create();
         
        beginEditCP(transnode);
        transnode->setCore(trans[i]);
        transnode->addChild(geonode);
        endEditCP(transnode);
       
        scene->addChild(transnode);
        
    }

    endEditCP(scene);
 
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
