#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGImage.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );

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
    NodePtr scene = makePlane( 2, 2, 2, 2 );

    GeometryPtr plane_geo = GeometryPtr::dcast(scene->getCore());
    SimpleTexturedMaterialPtr pm = SimpleTexturedMaterial::create();
    beginEditCP(pm);
    pm->setDiffuse( Color3f( 1,0,0 ) );
    pm->setAmbient( Color3f( 1,0,0 ) );
    pm->setSpecular( Color3f( 1,1,1 ) );
    pm->setShininess( 10 );

    UChar8 imgdata[512*256*4];
    UChar8 *data=&imgdata[0];

    for(int l=8; l >= 0; l--)
    {
        int size=1<<l;
        for(int x=0;x<size;x++)
            for(int y = 0; y < size; y++)
            {
                *data++ = ((l>>3)&1)*255;
                *data++ = ((l>>2)&1)*255;
                *data++ = ((l>>1)&1)*255;
                *data++ = 128;
            }
    }

    ImagePtr pImage = Image::create();
    if(argc>1)
    {
        pImage->read(argv[1]);
    }
    else
    {
        pImage->set( Image::OSG_RGBA_PF, 256, 256, 1, 9, 1, 0, imgdata );
//        pImage->write("xxx.mtd");
    }
    if(pImage->getMipMapCount()==1)
        pImage->createMipmap(-1);
    if(argc>2)
    {
        pImage->write(argv[2]);
    }
    pImage->dump();
    pm->setImage( pImage ); 
    pm->setMinFilter( GL_NEAREST_MIPMAP_NEAREST );
    pm->setMagFilter( GL_NEAREST );
    endEditCP(pm);

    plane_geo->setMaterial( pm );

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
void keyboard(unsigned char k, 
              int /* x */,
              int /* y */)
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

    return winid;
}
