// OpenSG NURBS example: testSurfaceFatBordersRender.cpp
//
// Shows how to render a neighbouring trimmed NURBS surfaces without gaps
// using the Fat Borders.

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleMaterial.h>
#include <OSGGLUTWindow.h>
#include <OSGSolidBackground.h>
#include <OSGSurface.h>
#include <OSGFatBorderChunk.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
SimpleMaterialPtr  gpcl_defaultmat;
Real32             g_error1;
Real32             g_error2;
bool               gb_nofatborders = false;
bool               gb_differenterrors = false;
SurfacePtr         gpcl_surface1;
SurfacePtr         gpcl_surface2;
FatBorderChunkPtr  gpcl_fb_chunk;

// redraw the window
void display(void)
{      
    // render
    mgr->redraw();
    // all done, swap  (better not GV)
    //glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    exit(1);
    case 'y':   
    case 'z':
                glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
                std::cerr << "PolygonMode: Point." << std::endl;
                break;
    case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                std::cerr << "PolygonMode: Line." << std::endl;
                break;
    case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                std::cerr << "PolygonMode: Fill." << std::endl;
                break;
    case 'f':   g_error1 *= 2;
                if ( !gb_differenterrors )
                {
                    std::cerr << "Error: " << g_error1 << std::endl;
                }
                else
                {
                    std::cerr << "Error1: " << g_error1 << std::endl;
                }
                beginEditCP( gpcl_surface1, Surface::ErrorFieldMask );
                {
                    gpcl_surface1->setError( g_error1 );
                }
                endEditCP(   gpcl_surface1, Surface::ErrorFieldMask );
                if ( !gb_differenterrors )
                {
                    g_error2 = g_error1;
                    beginEditCP( gpcl_surface2, Surface::ErrorFieldMask );
                    {
                        gpcl_surface2->setError( g_error2 );
                    }
                    endEditCP(   gpcl_surface2, Surface::ErrorFieldMask );
                }
                break;
    case 'g':   g_error1 /= 2;
                if ( !gb_differenterrors )
                {
                    std::cerr << "Error: " << g_error1 << std::endl;
                }
                else
                {
                    std::cerr << "Error1: " << g_error1 << std::endl;
                }
                beginEditCP( gpcl_surface1, Surface::ErrorFieldMask );
                {
                    gpcl_surface1->setError( g_error1 );
                }
                endEditCP(   gpcl_surface1, Surface::ErrorFieldMask );
                if ( !gb_differenterrors )
                {
                    g_error2 = g_error1;
                    beginEditCP( gpcl_surface2, Surface::ErrorFieldMask );
                    {
                        gpcl_surface2->setError( g_error2 );
                    }
                    endEditCP(   gpcl_surface2, Surface::ErrorFieldMask );
                }
                break;
    case 'h':   g_error2 *= 2;
                if ( !gb_differenterrors )
                {
                    std::cerr << "Error: " << g_error2 << std::endl;
                }
                else
                {
                    std::cerr << "Error2: " << g_error2 << std::endl;
                }
                beginEditCP( gpcl_surface2, Surface::ErrorFieldMask );
                {
                    gpcl_surface2->setError( g_error2 );
                }
                endEditCP(   gpcl_surface2, Surface::ErrorFieldMask );
                if ( !gb_differenterrors )
                {
                    g_error1 = g_error2;
                    beginEditCP( gpcl_surface1, Surface::ErrorFieldMask );
                    {
                        gpcl_surface1->setError( g_error1 );
                    }
                    endEditCP(   gpcl_surface1, Surface::ErrorFieldMask );
                }
                break;
    case 'j':   g_error2 /= 2;
                if ( !gb_differenterrors )
                {
                    std::cerr << "Error: " << g_error2 << std::endl;
                }
                else
                {
                    std::cerr << "Error2: " << g_error2 << std::endl;
                }
                beginEditCP( gpcl_surface2, Surface::ErrorFieldMask );
                {
                    gpcl_surface2->setError( g_error2 );
                }
                endEditCP(   gpcl_surface2, Surface::ErrorFieldMask );
                if ( !gb_differenterrors )
                {
                    g_error1 = g_error2;
                    beginEditCP( gpcl_surface1, Surface::ErrorFieldMask );
                    {
                        gpcl_surface1->setError( g_error1 );
                    }
                    endEditCP(   gpcl_surface1, Surface::ErrorFieldMask );
                }
                break;
    }
}

void setupDefaultMaterial( void )
{
    gpcl_fb_chunk = FatBorderChunk::create();
	beginEditCP( gpcl_fb_chunk );
	{
   		gpcl_fb_chunk->activateWithStandardLighting( );
	}
	endEditCP( gpcl_fb_chunk );
    gpcl_defaultmat = SimpleMaterial::create();
	addRefCP( gpcl_defaultmat );
    beginEditCP(gpcl_defaultmat);
	{
		gpcl_defaultmat->setDiffuse( Color3f(1.0,0.0,0.0) ); // RED
		gpcl_defaultmat->setAmbient( Color3f(0.2,0.2,0.2) );
		gpcl_defaultmat->setEmission( Color3f(0.02,0.02,0.02) );
		gpcl_defaultmat->setSpecular( Color3f(0.78,0.78,0.78) );
		gpcl_defaultmat->setShininess( 128 );
		// add fat border chunk
        if ( !gb_nofatborders )
        {
            gpcl_defaultmat->addChunk( gpcl_fb_chunk );
        }
	}
    endEditCP(gpcl_defaultmat);
}

NodePtr makeScene( void )
{
    setupDefaultMaterial();
    
    // Let's create two untrimmed surfaces that lie beside each other.
    // Even if the tessellation error is set to be the same for
    // both surfaces, due to numerical instabilities and sampling errors
    // small one pixel gaps will appear. By reducing the error you can 
    // make most gaps disappear, but there will be still some left, even
    // if you reduce the error to be extremely small -- and as a sideeffect
    // the tessellation time plus the triangle count will explode.
    // You can try this by supplying the '-nofb' switch and
    // reducing the error by the 'g' key during rendering.
    // Of course if you set different tessellation errors (generally the
    // case when using view-dependent LOD algorithms) the gaps
    // will be a lot more visible. Try the '-nofb' and '-de' switches, and
    // play around with different errors using the 'f' and 'g'
    // keys for the first surface, and the 'h' and 'j' keys for the
    // second surface.
    //
    // Note that this is not a very good example for the Fat Borders as
    // the surfaces are untrimmed, and they are also very nice numerically
    // (real world models are usually much worse) and a basic uniform
    // tessellation would probably get rid of the gaps (which are not very
    // visible in the first place due to the nice properties of these
    // surfaces). Note also that if you set too high errors or 
    // radically different errors, the spike-through artifacts of the 
    // Fat Borders will appear.
    // We will hopefully come up with a better example later. :-)
    
    NodePtr root = Node::create();
    NodePtr surf1 = Node::create();
    NodePtr surf2 = Node::create();
	addRefCP( root );
    addRefCP( surf1 );
    addRefCP( surf2 );
    beginEditCP( root );
    {
        root->setCore( Group::create() );
        root->addChild( surf1 );
        root->addChild( surf2 );
    }
    endEditCP( root );
    
    SurfacePtr surface1 = Surface::create();
    GeoPositions3fPtr cps1 = GeoPositions3f::create();
    beginEditCP( cps1, GeoPositions3f::GeoPropDataFieldMask );
    {
        cps1->clear();
        cps1->push_back( Pnt3f(  1, -1,  0 ));
        cps1->push_back( Pnt3f(  1,  0,  0 ));
        cps1->push_back( Pnt3f(  1,  0,  1 ));
        cps1->push_back( Pnt3f(  1,  1,  1 ));

        cps1->push_back( Pnt3f(  0, -1,  0 ));
        cps1->push_back( Pnt3f(  0,  0,  0 ));
        cps1->push_back( Pnt3f(  0,  0,  1 ));
        cps1->push_back( Pnt3f(  0,  1,  1 ));

        cps1->push_back( Pnt3f(  0, -1,  1 ));
        cps1->push_back( Pnt3f(  0,  0,  1 ));
        cps1->push_back( Pnt3f(  0,  0,  0 ));
        cps1->push_back( Pnt3f(  0,  1,  0 ));

        cps1->push_back( Pnt3f( -1, -1,  1 ));
        cps1->push_back( Pnt3f( -1,  0,  1 ));
        cps1->push_back( Pnt3f( -1,  0,  0 ));
        cps1->push_back( Pnt3f( -1,  1,  0 ));
    }
    endEditCP( cps1, GeoPositions3f::GeoPropDataFieldMask );

    SurfacePtr surface2 = Surface::create();
    GeoPositions3fPtr cps2 = GeoPositions3f::create();
    beginEditCP( cps2, GeoPositions3f::GeoPropDataFieldMask );
    {
        cps2->clear();
        cps2->push_back( Pnt3f(  5, -2,  2 ));
        cps2->push_back( Pnt3f(  4, -1,  2 ));
        cps2->push_back( Pnt3f(  3,  0,  0 ));
        cps2->push_back( Pnt3f(  5,  1,  0 ));

        cps2->push_back( Pnt3f(  2, -1,  1 ));
        cps2->push_back( Pnt3f(  2,  0,  1 ));
        cps2->push_back( Pnt3f(  2,  0,  0 ));
        cps2->push_back( Pnt3f(  2,  1,  0 ));

        cps2->push_back( Pnt3f(  2, -1,  0 ));
        cps2->push_back( Pnt3f(  2,  0,  0 ));
        cps2->push_back( Pnt3f(  2,  0,  1 ));
        cps2->push_back( Pnt3f(  2,  1,  1 ));

        cps2->push_back( Pnt3f(  1, -1,  0 ));
        cps2->push_back( Pnt3f(  1,  0,  0 ));
        cps2->push_back( Pnt3f(  1,  0,  1 ));
        cps2->push_back( Pnt3f(  1,  1,  1 ));

    }
    endEditCP( cps2, GeoPositions3f::GeoPropDataFieldMask );
        
    std::vector<Real64> knots1;
    std::vector<Pnt2f> points;
    knots1.clear();
    knots1.push_back(0);
    knots1.push_back(0);
    knots1.push_back(1);
    knots1.push_back(1);
            
    beginEditCP( surface1 );
    {
        // first, let's clear the trimming
        surface1->removeCurves();

        // add simple outer trimming around the domain
        points.clear();
        points.push_back( Pnt2f(0,0) );
        points.push_back( Pnt2f(1,0) );
        surface1->addCurve( 1, knots1, points, true );
        points.clear();
        points.push_back( Pnt2f(1,0) );
        points.push_back( Pnt2f(1,1) );
        surface1->addCurve( 1, knots1, points, false );
        points.clear();
        points.push_back( Pnt2f(1,1) );
        points.push_back( Pnt2f(0,1) );
        surface1->addCurve( 1, knots1, points, false );
        points.clear();
        points.push_back( Pnt2f(0,1) );
        points.push_back( Pnt2f(0,0) );
        surface1->addCurve( 1, knots1, points, false );
        
        // set up dimensions and knot vectors:
        surface1->setDimU( 3 );
        surface1->setDimV( 3 );
        surface1->getKnotsU().clear();
        surface1->getKnotsU().push_back( 0 );
        surface1->getKnotsU().push_back( 0 );
        surface1->getKnotsU().push_back( 0 );
        surface1->getKnotsU().push_back( 0 );
        surface1->getKnotsU().push_back( 1 );
        surface1->getKnotsU().push_back( 1 );
        surface1->getKnotsU().push_back( 1 );
        surface1->getKnotsU().push_back( 1 );
        surface1->getKnotsV().clear();
        surface1->getKnotsV().push_back( 0 );
        surface1->getKnotsV().push_back( 0 );
        surface1->getKnotsV().push_back( 0 );
        surface1->getKnotsV().push_back( 0 );
        surface1->getKnotsV().push_back( 1 );
        surface1->getKnotsV().push_back( 1 );
        surface1->getKnotsV().push_back( 1 );
        surface1->getKnotsV().push_back( 1 );
        
        // set control points
        surface1->setControlPoints( cps1 );

        // set error
        surface1->setError( g_error1 );
        
        // and finally set the material
        surface1->setMaterial( gpcl_defaultmat );
    }
    endEditCP( surface1 );

    
    beginEditCP( surface2 );
    {
        // first, let's clear the trimming
        surface2->removeCurves();
        // add simple outer trimming around the domain
        points.clear();
        points.push_back( Pnt2f(1,0) );
        points.push_back( Pnt2f(2,0) );
        surface2->addCurve( 1, knots1, points, true );
        points.clear();
        points.push_back( Pnt2f(2,0) );
        points.push_back( Pnt2f(2,1) );
        surface2->addCurve( 1, knots1, points, false );
        points.clear();
        points.push_back( Pnt2f(2,1) );
        points.push_back( Pnt2f(1,1) );
        surface2->addCurve( 1, knots1, points, false );
        points.clear();
        points.push_back( Pnt2f(1,1) );
        points.push_back( Pnt2f(1,0) );
        surface2->addCurve( 1, knots1, points, false );

        // set up dimensions and knot vectors:
        surface2->setDimU( 3 );
        surface2->setDimV( 3 );
        surface2->getKnotsU().clear();
        surface2->getKnotsU().push_back( 1 );
        surface2->getKnotsU().push_back( 1 );
        surface2->getKnotsU().push_back( 1 );
        surface2->getKnotsU().push_back( 1 );
        surface2->getKnotsU().push_back( 2 );
        surface2->getKnotsU().push_back( 2 );
        surface2->getKnotsU().push_back( 2 );
        surface2->getKnotsU().push_back( 2 );
        surface2->getKnotsV().clear();
        surface2->getKnotsV().push_back( 0 );
        surface2->getKnotsV().push_back( 0 );
        surface2->getKnotsV().push_back( 0 );
        surface2->getKnotsV().push_back( 0 );
        surface2->getKnotsV().push_back( 1 );
        surface2->getKnotsV().push_back( 1 );
        surface2->getKnotsV().push_back( 1 );
        surface2->getKnotsV().push_back( 1 );
        
        // set control points
        surface2->setControlPoints( cps2 );
        
        // set error
        surface2->setError( g_error2 );
        
        // and finally set the material
        surface2->setMaterial( gpcl_defaultmat );
    }
    endEditCP( surface2 );
        
    
    beginEditCP( surf1 );
    {
        surf1->setCore( surface1 );
    }
    endEditCP( surf1 );
    beginEditCP( surf2 );
    {
        surf2->setCore( surface2 );
    }
    endEditCP( surf2 );
    gpcl_surface1 = surface1;
    gpcl_surface2 = surface2;

    return root;
}

void processArgs( int argc, char **argv )
{
    gb_nofatborders = false;
    gb_differenterrors = false;

    for( int i = 1; i < argc; ++i )
	{
        if( !strcmp(argv[i], "-de") )
        {
            gb_differenterrors = true;
            std::cerr<< "Enabling different errors..." <<std::endl;
        }
        if( !strcmp(argv[i], "-nofb") )
        {
            gb_nofatborders = true;
            std::cerr<< "Disabling Fat Borders..." <<std::endl;
        }
        if (!strcmp(argv[i], "-error") )
        {
			g_error1 = atof( argv[ ++i ] );
            if ( g_error1 < 0.001 )
            {
                g_error1 = 0.001;
            }            
			g_error2  = g_error1;
			std::cerr << "Setting initial error to " << g_error1  << std::endl;
        }
    
    } // for i
    
}
int main(int argc, char **argv)
{
    g_error1 = 0.01;
    g_error2 = g_error1;

    processArgs( argc, argv );
      
    osgInit(argc,argv);
    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    GLUTWindowPtr gwin = GLUTWindow::create();
	beginEditCP(gwin);
	{
	    gwin->setId(winid);
	}
    endEditCP(gwin);
    gwin->init();

    // create the scene
    NodePtr scene;
    scene = makeScene( );
    
    if ( scene == NullFC )
    {
        std::cerr<<"makeScene returned NullFC, exiting..."<<std::endl;
        return -1;
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow( gwin );
    // tell the manager what to manage
    mgr->setRoot  ( scene );
    
    // show the whole scene
    mgr->showAll();
    mgr->redraw();
	SolidBackgroundPtr bgr = SolidBackground::create();
    beginEditCP( bgr );
    bgr->setColor( Color3f( 1.0, 1.0, 1.0 ));
    endEditCP( bgr );
    mgr->getWindow()->getPort(0)->setBackground( bgr );
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

