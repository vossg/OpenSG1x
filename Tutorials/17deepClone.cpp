// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGBaseFunctions.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

GeometryPtr _geo = NullFC;
GeoPositions3fPtr _pos = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

Action::ResultE changeGeo(NodePtr& node)
{   
    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    
    if(geo == NullFC)
        return Action::Continue;


    GeoColors3fPtr colors = GeoColors3fPtr::dcast(geo->getColors());
    if(colors == NullFC)
    {
        colors = GeoColors3f::create();

        colors->resize(geo->getPositions()->getSize());
        
        // Change the geometry to use the new colors
        beginEditCP(geo, Geometry::ColorsFieldMask);
            geo->setColors(colors);
            // If multi-indexed, make the colors use the same index as
            // the geometry
            if(geo->getIndexMapping().size() > 0)
            {
                Int16 pind = geo->calcMappingIndex(Geometry::MapPosition);
                
                if(pind < 0)
                {
                    FFATAL(("Multi-indexed, but no positions index???\n"));
                    return Action::Continue; 
                }
                
                // This makes the colors use the same indices as the positions
                geo->getIndexMapping()[pind] |= Geometry::MapColor;
            }
        endEditCP  (geo, Geometry::ColorsFieldMask);
    }
    

    beginEditCP(geo, Geometry::ColorsFieldMask);
    beginEditCP(colors);
    Real32 size = colors->getSize();
    for(UInt32 i=0;i<size;++i)
    {
        Color3f c;
        c[0] = ((Real32) i) / size;
        c[1] = 0.0f;
        c[2] = 0.0f;
        colors->setValue(c, i);
    }
    endEditCP(colors);
    endEditCP(geo, Geometry::ColorsFieldMask);
    
    return Action::Continue; 
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

    // load the scene
    NodePtr scene = NullFC;
    
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the().getSuffixList(suffixes, SceneFileType::OSG_READ_SUPPORTED);
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        scene = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        /*
            All scene file loading is handled via the SceneFileHandler.
        */
        scene = SceneFileHandler::the().read(argv[1]);
    }
    
    // calc size of the scene
    Vec3f min, max;
    DynamicVolume vol;
    scene->getWorldVolume(vol);
    vol.getBounds(min, max);

    Vec3f d = max - min;
    Real32 offset = d.length() / 2.0f;
    
    // now create a deep clone
    // we share the GenericAtt from the wrl loader without it crashes in deepClone setAbstrValue ...
    NodePtr sceneClone = deepCloneTree(scene, "GenericAtt");
    // this clones all nodes but the cores of type Material and Transform are shared.
    //NodePtr sceneClone = deepCloneTree(scene, "Material, Transform");
    
    // now change all geometries from the cloned scene just to show
    // that it is a real deep copy.
    traverse(sceneClone, 
             osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
                                             NodePtr        >(changeGeo));
    
    // create a small scene graph with two transformation nodes.
    NodePtr root = makeCoredNode<Group>();
    ComponentTransformPtr t1;
    NodePtr tn1 = makeCoredNode<ComponentTransform>(&t1);
    ComponentTransformPtr t2;
    NodePtr tn2 = makeCoredNode<ComponentTransform>(&t2);
    
    beginEditCP(t1);
        t1->setTranslation(Vec3f(- offset, 0.0f, 0.0f));
    endEditCP(t1);
    beginEditCP(t2);
        t2->setTranslation(Vec3f(offset, 0.0f, 0.0f));
    endEditCP(t2);
    
    beginEditCP(tn1);
        tn1->addChild(scene);
    endEditCP(tn1);
    
    beginEditCP(tn2);
        tn2->addChild(sceneClone);
    endEditCP(tn2);
    
    beginEditCP(root);
        root->addChild(tn1);
        root->addChild(tn2);
    endEditCP(root);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (root);

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
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
