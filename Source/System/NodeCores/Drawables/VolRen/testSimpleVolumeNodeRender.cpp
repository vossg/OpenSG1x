// OpenSG Testprogram: Direct Volume Rendering Node
//
// It demonstrates some of the capabilities of the OpenSG Volume Rendering Node
// in an interactive scene viewer.
//

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// For loading files
#include <OSGSceneFileHandler.h>

// Includes for the volume rendering library
#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRAppearance.h>
#include <OSGDVRSimpleShader.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// The Scene
NodePtr scene = NullFC;

DVRVolumePtr vol;

// forward declaration of the volume node construction function
NodePtr makeVolume( const char * datFile);
NodePtr makeVolume( ImagePtr datImage);

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Find volume node
Action::ResultE findVolume(NodePtr& node)
{   
    if(node->getCore()->getType().isDerivedFrom( DVRVolume::getClassType()))
    {
        vol = DVRVolumePtr::dcast(node->getCore());
        return Action::Skip;
    }   
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

    // create the scene or load it from a .osg-file
    if (argc == 1)
    {
        scene = makeVolume("00_data64x64x64.dat");
    }
    else if(!strcmp(argv[1], "RGBA"))
    {
        ImagePtr imageP = Image::create();
        const int res=64;
        Real32 rres = res;
        beginEditCP(imageP);
        imageP->set(Image::OSG_RGBA_PF,res,res,res);

        UInt8 *d = imageP->getData();
        for(Int16 z = 0; z < res; ++z)         
        for(Int16 y = 0; y < res; ++y)         
        for(Int16 x = 0; x < res; ++x)
        {
            Real32 dx = x/rres - .5f;
            Real32 dy = y/rres - .5f;
            Real32 dz = z/rres - .5f;

            Real32 dsq = (dx*dx + dy*dy + dz*dz);

            int  bx = (x<2 || x >=res-2),
                 by = (y<2 || y >=res-2),
                 bz = (z<2 || z >=res-2);
            if(bx + by + bz >=2)
            {
                *d++ = 0;
                *d++ = 255;
                *d++ = 0;
                *d++ = 64;
            } 
            else if (osgabs(dx) < .2 && osgabs(dy) < .2)
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;              
            }
            else if(dsq <= .25f)
            {
                *d++ = static_cast<UInt8>(x/rres * 255.f);
                *d++ = static_cast<UInt8>(y/rres * 255.f);
                *d++ = static_cast<UInt8>(z/rres * 255.f);
                *d++ = static_cast<UInt8>((.3f-dsq*dsq*dsq) * 255.f);
            }
            else
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
            }
        }      

        endEditCP(imageP);  
        
        imageP->setAttachmentField( "SliceThickness", "1 1 1" );
        scene = makeVolume(imageP);        
    }
    else if(!strcmp(argv[1], "RGB"))
    {
        ImagePtr imageP = Image::create();
        const int res=64;
        Real32 rres = res;
        beginEditCP(imageP);
        imageP->set(Image::OSG_RGB_PF,res,res,res);

        UInt8 *d = imageP->getData();
        for(Int16 z = 0; z < res; ++z)         
        for(Int16 y = 0; y < res; ++y)         
        for(Int16 x = 0; x < res; ++x)
        {
            Real32 dx = x/rres - .5f;
            Real32 dy = y/rres - .5f;
            Real32 dz = z/rres - .5f;

            Real32 dsq = (dx*dx + dy*dy + dz*dz);

            int  bx = (x<2 || x >=res-2),
                 by = (y<2 || y >=res-2),
                 bz = (z<2 || z >=res-2);
            if(bx + by + bz >=2)
            {
                *d++ = 0;
                *d++ = 255;
                *d++ = 0;
            } 
            else if (osgabs(dx) < .2 && osgabs(dy) < .2)
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
            }
            else if(dsq <= .25f)
            {
                *d++ = static_cast<UInt8>(x/rres * 255.f);
                *d++ = static_cast<UInt8>(y/rres * 255.f);
                *d++ = static_cast<UInt8>(z/rres * 255.f);
            }
            else
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
            }
        }      

        endEditCP(imageP);  
        
        imageP->setAttachmentField( "SliceThickness", "1 1 1" );
        scene = makeVolume(imageP);        
    }
    else if(!strcmp(argv[1], "LA16"))
    {
        ImagePtr imageP = Image::create();
        const int res=64;
        Real32 rres = res;
        beginEditCP(imageP);
        imageP->set(Image::OSG_LA_PF,res,res,res,1,1,0,0,
                    Image::OSG_UINT16_IMAGEDATA);

        UInt16 *d = reinterpret_cast<UInt16 *>(imageP->getData());
        for(Int16 z = 0; z < res; ++z)         
        for(Int16 y = 0; y < res; ++y)         
        for(Int16 x = 0; x < res; ++x)
        {
            Real32 dx = x/rres - .5f;
            Real32 dy = y/rres - .5f;
            Real32 dz = z/rres - .5f;

            Real32 dsq = (dx*dx + dy*dy + dz*dz);

            int  bx = (x<2 || x >=res-2),
                 by = (y<2 || y >=res-2),
                 bz = (z<2 || z >=res-2);
            if(bx + by + bz >=2)
            {
                *d++ = 65535;
                *d++ = 16384;
            } 
            else if (osgabs(dx) < .2 && osgabs(dy) < .2)
            {
                *d++ = 0;
                *d++ = 0;              
            }
            else if(dsq <= .25f)
            {
                *d++ = static_cast<UInt16>(z/rres * 65535.f);
                *d++ = static_cast<UInt16>((.3f-dsq*dsq*dsq) * 65535.f);
            }
            else
            {
                *d++ = 0;
                *d++ = 0;
            }
        }      

        endEditCP(imageP);  
        
        imageP->setAttachmentField( "SliceThickness", "1 1 1" );
        scene = makeVolume(imageP);        
    }
    else if(!strcmp(argv[1], "LA"))
    {
        ImagePtr imageP = Image::create();
        const int res=64;
        Real32 rres = res;
        beginEditCP(imageP);
        imageP->set(Image::OSG_LA_PF,res,res,res);

        UInt8 *d = imageP->getData();
        for(Int16 z = 0; z < res; ++z)         
        for(Int16 y = 0; y < res; ++y)         
        for(Int16 x = 0; x < res; ++x)
        {
            Real32 dx = x/rres - .5f;
            Real32 dy = y/rres - .5f;
            Real32 dz = z/rres - .5f;

            Real32 dsq = (dx*dx + dy*dy + dz*dz);

            int  bx = (x<2 || x >=res-2),
                 by = (y<2 || y >=res-2),
                 bz = (z<2 || z >=res-2);
            if(bx + by + bz >=2)
            {
                *d++ = 32;
                *d++ = 64;
            } 
            else if (osgabs(dx) < .2 && osgabs(dy) < .2)
            {
                *d++ = 0;
                *d++ = 0;              
            }
            else if(dsq <= .25f)
            {
                *d++ = static_cast<UInt8>(z/rres * 255.f);
                *d++ = static_cast<UInt8>((.3f-dsq*dsq*dsq) * 255.f);
            }
            else
            {
                *d++ = 0;
                *d++ = 0;
            }
        }      

        endEditCP(imageP);  
        
        imageP->setAttachmentField( "SliceThickness", "1 1 1" );
        scene = makeVolume(imageP);        
    }
    else if(!strcmp(argv[1], "L"))
    {
        ImagePtr imageP = Image::create();
        const int res=64;
        Real32 rres = res;
        beginEditCP(imageP);
        imageP->set(Image::OSG_L_PF,res,res,res);

        UInt8 *d = imageP->getData();
        for(Int16 z = 0; z < res; ++z)         
        for(Int16 y = 0; y < res; ++y)         
        for(Int16 x = 0; x < res; ++x)
        {
            Real32 dx = x/rres - .5f;
            Real32 dy = y/rres - .5f;
            Real32 dz = z/rres - .5f;

            Real32 dsq = (dx*dx + dy*dy + dz*dz);

            int  bx = (x<2 || x >=res-2),
                 by = (y<2 || y >=res-2),
                 bz = (z<2 || z >=res-2);
            if(bx + by + bz >=2)
            {
                *d++ = 32;
            } 
            else if (osgabs(dx) < .2 && osgabs(dy) < .2)
            {
                *d++ = 0;
            }
            else if(dsq <= .25f)
            {
                *d++ = static_cast<UInt8>(z/rres * 255.f);
            }
            else
            {
                *d++ = 0;
            }
        }      

        endEditCP(imageP);  
        
        imageP->setAttachmentField( "SliceThickness", "1 1 1" );
        scene = makeVolume(imageP);        
    }
    else
    {
        scene = SceneFileHandler::the().read(argv[1]);
        if (scene == NullFC)
        {
	        SLOG << "Could not read file " << argv[1] << std::endl;
	        exit(-1);
        }
        traverse(scene, 
             osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
                                             NodePtr        >(findVolume));

    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    Pnt3f from = mgr->getNavigator()->getFrom();
    from[2] = 3 * from[2];
    mgr->getNavigator()->setFrom(from);
    
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
void keyboard(unsigned char k, int OSG_CHECK_ARG(x), int OSG_CHECK_ARG(y))
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        break;
        case 'a':
        {
            OSG::beginEditCP(vol, OSG::DVRVolume::SamplingFieldMask);
            vol->setSampling(vol->getSampling() * 1.1);
            OSG::endEditCP(vol, OSG::DVRVolume::SamplingFieldMask);
            std::cout << "Sampling set to " << vol->getSampling() 
                      << std::endl;
            glutPostRedisplay();
        }
        break;
        case 'z':
        {
            OSG::beginEditCP(vol, OSG::DVRVolume::SamplingFieldMask);
            vol->setSampling(vol->getSampling() * 0.9);
            OSG::endEditCP(vol, OSG::DVRVolume::SamplingFieldMask);
            std::cout << "Sampling set to " << vol->getSampling() 
                      << std::endl;
            glutPostRedisplay();
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG Simple VolRen Test");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

// Create a volume rendering node with all desired attachments
NodePtr makeVolume( const char * datFile)
{  
    // Load the 3D-image and store it in the volume texture attachment
    ImagePtr datImage = Image::create();
    if (false == datImage->read(datFile)) {
        SLOG << "File: " << datFile << " not found" << std::endl;
	exit (-1);
    }
    
    return makeVolume(datImage);
}

// Create a volume rendering node with all desired attachments
NodePtr makeVolume(ImagePtr datImage)
{  
    vol         = DVRVolume::create();
    DVRAppearancePtr     app         = DVRAppearance::create(); 
    DVRVolumeTexturePtr  tex         = DVRVolumeTexture::create();

    beginEditCP(tex);
    tex->setImage(datImage);
    endEditCP(tex);

    // Attach the volume texture to the appearance
    beginEditCP(app, Node::AttachmentsFieldMask);
    app->addAttachment(tex);
    endEditCP  (app, Node::AttachmentsFieldMask);

    // Assign the appearance to the volume core
    beginEditCP(vol);
    vol->setAppearance(app);
    vol->setShader(DVRSimpleShader::create());
    endEditCP(vol);

    // Create a node for the volume core
    NodePtr newGeom = Node::create();
    beginEditCP(newGeom);
    newGeom->setCore(vol);
    endEditCP(newGeom);
    
    return newGeom;
}
