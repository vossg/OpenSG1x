
// Create polygonal geometry using indices

#include <GL/glut.h>

#include <OpenSG/OSGConfig.h>

// quaternions for orientation
#include <OpenSG/OSGQuaternion.h>

// the geometry node core
#include <OpenSG/OSGGeometry.h>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// The pointer to the transformation
TransformPtr trans;

// Standard GLUT callback functions
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    Quaternion q;
    
    q.setValueAsAxisRad(0,1,0, t/1000.f );
    
    m.setTransform(q);
    
    // set the transform's matrix
    beginEditCP(trans);
    trans->setMatrix(m);
    endEditCP(trans);
   
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
    
    // create the geometry node. This is a minimal setup
    
    // the geometry consists of several parts:
    
    // the types of the primitives to be rendered,
    GeoPTypesPtr type = GeoPTypesUI8::create();	   
    beginEditCP(type);
	type->addValue( GL_POLYGON );
	type->addValue( GL_TRIANGLES );
	type->addValue( GL_LINES );
	endEditCP(type);

    // the number of vertices per primitive,
	GeoPLengthsPtr lens = GeoPLengthsUI32::create();	
	beginEditCP(lens);
	lens->addValue( 4 );
	lens->addValue( 6 );
	lens->addValue( 10 );
	endEditCP(lens);

    // the indices, mapping from the primitives into the data
	GeoIndicesUI32Ptr index = GeoIndicesUI32::create();	
	beginEditCP(index);
	index->getFieldPtr()->addValue( 0 );    // indices for the polygon
	index->getFieldPtr()->addValue( 1 );
 	index->getFieldPtr()->addValue( 2 );
	index->getFieldPtr()->addValue( 3 );
   
	index->getFieldPtr()->addValue( 4 );    // indices for the triangles
	index->getFieldPtr()->addValue( 5 );
 	index->getFieldPtr()->addValue( 6 );
	index->getFieldPtr()->addValue( 7 );
	index->getFieldPtr()->addValue( 8 );
	index->getFieldPtr()->addValue( 9 );
    
	index->getFieldPtr()->addValue( 0 );    // indices for the lines
	index->getFieldPtr()->addValue( 5 );
	index->getFieldPtr()->addValue( 1 );
	index->getFieldPtr()->addValue( 7 );
	index->getFieldPtr()->addValue( 2 );
	index->getFieldPtr()->addValue( 8 );
	index->getFieldPtr()->addValue( 3 );
	index->getFieldPtr()->addValue( 4 );
	index->getFieldPtr()->addValue( 6 );
	index->getFieldPtr()->addValue( 9 );
	endEditCP(index);

    // the vertices.
	GeoPositions3fPtr pnts = GeoPositions3f::create();
 	beginEditCP(pnts);
	pnts->addValue( Pnt3f( -1, -1, -1) );
	pnts->addValue( Pnt3f( -1, -1,  1) );
	pnts->addValue( Pnt3f(  1, -1,  1) );
	pnts->addValue( Pnt3f(  1, -1, -1) );
    
	pnts->addValue( Pnt3f(  1,  0, -1) );
	pnts->addValue( Pnt3f( -1,  0, -1) );
	pnts->addValue( Pnt3f(  0,  1, -1) );
    
	pnts->addValue( Pnt3f( -1,  0,  1) );
	pnts->addValue( Pnt3f(  1,  0,  1) );
	pnts->addValue( Pnt3f(  0,  1,  1) );
	endEditCP(pnts);
   
    // put it all together into a geometry
    GeometryPtr geo=Geometry::create();
 	beginEditCP(geo);
    geo->setTypes(type);
    geo->setLengths(lens);
    geo->setIndices(index);
    geo->setPositions(pnts);
     
    // assign a material to the geometry to make it visible. The details
    // of materials are defined elsewhere.
    geo->setMaterial(getDefaultUnlitMaterial());

    endEditCP(geo);
    
    // put the geometry core into a node
    NodePtr n = Node::create();
    beginEditCP(n);
    n->setCore(geo);
    endEditCP(n);
    
    // add a transformation to make it move
     
    NodePtr scene = Node::create();  
    trans = Transform::create();
    beginEditCP(scene);
    scene->setCore(trans);
    scene->addChild(n);
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
