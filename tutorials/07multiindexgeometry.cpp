// OpenSG Tutorial Example: Multiindex Geometry
//
// This example shows how to use an index mapping to use different indices
// for different attributes.
//

// Headers
#include <GL/glut.h>
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
    gwin->setWinID(winid);
    gwin->init();

    // create the scene
     
    /*
        In the previous example, the colors and positions used the same
        indices. That might not always be the preferred way, and it might not
        make sense for other properties, e.g. normals.
        
        It is possible to assign a different index for every property. See the
        indices section below for details.
    */
    
    /*
        The initial setup is the same as in the single indexed geometry...
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
   
    GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
    {
        colors->addValue(Color3f(1, 1, 0));
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 0, 0));
        colors->addValue(Color3f(1, 1, 0));
        colors->addValue(Color3f(0, 1, 1));
        colors->addValue(Color3f(1, 0, 1));
    }
    endEditCP  (colors, GeoPositions3f::GeoPropDataFieldMask);

    /*
        A new property: normals.
        
        They are used for lighting calculations and have to point away from the
        surface. Normals are standard vectors.
    */
    GeoNormals3fPtr norms = GeoNormals3f::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
    {
        norms->addValue(Vec3f(-1,  0,  0));
        norms->addValue(Vec3f( 1,  0,  0));
        norms->addValue(Vec3f( 0, -1,  0));
        norms->addValue(Vec3f( 0,  1,  0));
        norms->addValue(Vec3f( 0,  0, -1));
        norms->addValue(Vec3f( 0,  0,  1));
    }
    endEditCP  (norms, GeoNormals3f::GeoPropDataFieldMask);
    
  
    /*
        To use different indices for different attributes they have to be
        specified. This is done within the single index property, by using more
        than one index per vertex.
        
        In this case every vertex reads multiple indices from the Indices
        property. The meaning of every index is defined by the indexMapping
        given below.
    */
    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);
    {
        // indices for the polygon
        indices->addValue(0);   // position index
        indices->addValue(3);   // color/normal index
        indices->addValue(1);   // position index
        indices->addValue(3);   // color/normal index
        indices->addValue(2);   // position index
        indices->addValue(3);   // color/normal index
        indices->addValue(3);   // position index
        indices->addValue(3);   // color/normal index
       
        // indices for the triangles
        indices->addValue(7);   // position index
        indices->addValue(4);   // color/normal index
        indices->addValue(4);   // position index
        indices->addValue(4);   // color/normal index
        indices->addValue(8);   // position index
        indices->addValue(4);   // color/normal index

        indices->addValue(5);   // position index
        indices->addValue(5);   // color/normal index
        indices->addValue(6);   // position index
        indices->addValue(5);   // color/normal index
        indices->addValue(9);   // position index
        indices->addValue(5);   // color/normal index
        
        // indices for the quads
        indices->addValue(1);   // position index
        indices->addValue(5);   // color/normal index
        indices->addValue(2);   // position index
        indices->addValue(5);   // color/normal index
        indices->addValue(6);   // position index
        indices->addValue(5);   // color/normal index
        indices->addValue(5);   // position index
        indices->addValue(5);   // color/normal index

        indices->addValue(3);   // position index
        indices->addValue(4);   // color/normal index
        indices->addValue(0);   // position index
        indices->addValue(4);   // color/normal index
        indices->addValue(4);   // position index
        indices->addValue(4);   // color/normal index
        indices->addValue(7);   // position index
        indices->addValue(4);   // color/normal index
    }
    endEditCP  (indices, GeoIndicesUI32::GeoPropDataFieldMask);
    
    /*
       Put it all together into a Geometry NodeCore.
    */
    GeometryPtr geo=Geometry::create();
    beginEditCP(geo, Geometry::TypesFieldMask          |
                     Geometry::LengthsFieldMask        |
                     Geometry::IndicesFieldMask        |
                     Geometry::IndexMappingFieldMask   |
                     Geometry::PositionsFieldMask      |
                     Geometry::NormalsFieldMask        |
                     Geometry::ColorsFieldMask         |
                     Geometry::MaterialFieldMask       );
    {
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setIndices  (indices);
        
        /*
             The meaning of the different indices is given by the indexMapping
             field. 

             If contains an entry that defines which index for a vertex
             selects which attribute. In this example the first index selects
             the positions, the second is used for colors and normals.

             The number of elements in the indexMapping field defines the
             number of indices used for every vertex.
        */
        geo->getIndexMapping().addValue( Geometry::MapPosition   );
        geo->getIndexMapping().addValue( Geometry::MapColor    |
                                         Geometry::MapNormal     );
         
        geo->setPositions(pnts  );
        geo->setColors   (colors);
        geo->setNormals  (norms );
        
        /*
            Use a lit material this time, to show the effect of the normals.
        */
        geo->setMaterial (getDefaultMaterial());   
    }
    endEditCP  (geo, Geometry::TypesFieldMask          |
                     Geometry::LengthsFieldMask        |
                     Geometry::IndicesFieldMask        |
                     Geometry::IndexMappingFieldMask   |
                     Geometry::PositionsFieldMask      |
                     Geometry::NormalsFieldMask        |
                     Geometry::ColorsFieldMask         |
                     Geometry::MaterialFieldMask       );
    
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
