// OpenSG Tutorial Example: Indexed Geometry
//
// This example shows how to use Indices to reuse data within a Geometry
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGGeometry.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Quaternion( Vec3f(0,1,0), 
                               t / 1000.f));
    
    // set the transform's matrix
    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    endEditCP  (trans, Transform::MatrixFieldMask);
   
    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
     
    /*
        Some of the positions in the Geometry example were added to it 
        multiple times, when they were used by multiple primitives.
        
        For large objects that's very inefficient memorywise, thus it is
        possible to reuse the positions by using an index.
    */
    
    /*
        The initial setup is the same as in the geometry...
    */
    GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_POLYGON  );
        type->addValue(GL_TRIANGLES);
        type->addValue(GL_QUADS    );
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(4);
        lens->addValue(6);
        lens->addValue(8);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
       
    /*
        This time, only unique positions are stored.
    */
    GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
        // the base
        pnts->addValue(Pnt3f(-1, -1, -1));
        pnts->addValue(Pnt3f(-1, -1,  1));
        pnts->addValue(Pnt3f( 1, -1,  1));
        pnts->addValue(Pnt3f( 1, -1, -1));

        // the roof base
        pnts->addValue(Pnt3f(-1,  0, -1));
        pnts->addValue(Pnt3f(-1,  0,  1));
        pnts->addValue(Pnt3f( 1,  0,  1));
        pnts->addValue(Pnt3f( 1,  0, -1));

        // the gable
        pnts->addValue(Pnt3f( 0,  1, -1));
        pnts->addValue(Pnt3f( 0,  1,  1));
    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
   
    /*
        The first new part: Colors.
        
        In parallel to the Positions every vertex can also have a separate
        color.
        
        Colors also have their own types, they are neither Points nor Vectors.
    */
    GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
    {
        // the base
        colors->addValue(Color3f(1, 1, 0));
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 1, 0));

        // the roof base
        colors->addValue(Color3f(0, 1, 1));
        colors->addValue(Color3f(1, 0, 1));
        colors->addValue(Color3f(1, 0, 1));
        colors->addValue(Color3f(0, 1, 1));

        // the gable
        colors->addValue(Color3f( 0,  1,  1));
        colors->addValue(Color3f( 1,  1,  0));
    }
    endEditCP  (colors, GeoPositions3f::GeoPropDataFieldMask);
  
    /*
        The second new part: Indices.
        
        The Indices are positioned between the primitives and the positions
        (and other attribute data like colors). So in this example the polygon
        does not use the first 4 elements from the positions property, it used
        the first 4 elements from the indices property, which define the
        positions to be used. The same 4 indices are used to select the colors
        for the vertices.
    */
    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);
    {
        // indices for the polygon
        indices->addValue(0);
        indices->addValue(1);
        indices->addValue(2);
        indices->addValue(3);
        
        // indices for the triangles
        indices->addValue(7);
        indices->addValue(4);
        indices->addValue(8);

        indices->addValue(5);
        indices->addValue(6);
        indices->addValue(9);
        
        // indices for the quads
        indices->addValue(1);
        indices->addValue(2);
        indices->addValue(6);
        indices->addValue(5);

        indices->addValue(3);
        indices->addValue(0);
        indices->addValue(4);
        indices->addValue(7);
    }
    endEditCP  (indices, GeoIndicesUI32::GeoPropDataFieldMask);
    
    /*
       Put it all together into a Geometry NodeCore.
    */
    GeometryPtr geo=Geometry::create();
    beginEditCP(geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::IndicesFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::ColorsFieldMask    |
                     Geometry::MaterialFieldMask  );
    {
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setIndices  (indices);
        geo->setPositions(pnts);
        geo->setColors   (colors);
        geo->setMaterial (getDefaultMaterial());   
    }
    endEditCP  (geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::IndicesFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::ColorsFieldMask    |
                     Geometry::MaterialFieldMask  );
    
    // put the geometry core into a node
    NodePtr n = Node::create();
    beginEditCP(n, Node::CoreFieldMask);
    {
        n->setCore(geo);
    }
    endEditCP  (n, Node::CoreFieldMask);
    
    // add a transformation to make it move     
    NodePtr scene = Node::create();  
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask  );
    {
        scene->setCore(trans);
        scene->addChild(n);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask  );
 

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
