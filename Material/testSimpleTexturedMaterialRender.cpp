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
#include <OSGDrawAction.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGFaceIterator.h>
#include <OSGGLUTWindow.h>

#include "OSGSimpleTexturedMaterial.h"


OSG_USING_NAMESPACE


DrawAction * dact;
WindowPtr win;
NodePtr plane,torus;

void
display(void)
{
    // do the motion in OpenGl, to stay independent of the ransform node
    // use the draw action to check the material

    float a = glutGet( GLUT_ELAPSED_TIME );
#if 0
    if ( (int) ( a / 2000 ) & 1 )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
#endif

    win->frameInit();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( a / 20, 0,0,1 );

    dact->apply( plane );

    glPushMatrix();
    glTranslatef( 0,0,fabs(osgsin(a/3000 * Pi))*2 );
    glRotatef( (a/3000) * 360 / 2, 1,0,0 );

    dact->apply( torus );

    glPopMatrix();

    glPopMatrix();

    win->frameExit();

    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    // glutKeyboardFunc(key);
    // glutReshapeFunc(resize);
    glutDisplayFunc(display);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);

    glutIdleFunc(display);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHT0 );

    // OSG

    plane = makePlane( 2, 2, 2, 2 );
    torus = makeTorus( .2, 1, 16, 8 );

    GeometryPtr plane_geo, torus_geo;
    plane_geo = GeometryPtr::dcast(plane->getCore());
    torus_geo = GeometryPtr::dcast(torus->getCore());


    SimpleTexturedMaterialPtr pm, tm;

    pm = SimpleTexturedMaterial::create();

    beginEditCP(pm);
    pm->setDiffuse( Color3f( 1,0,0 ) );
    pm->setAmbient( Color3f( 1,0,0 ) );
    pm->setSpecular( Color3f( 1,1,1 ) );
    pm->setShininess( 10 );

    UChar8 imgdata[] =
        {  255,0,0,128,  255,0,0,255,  255,0,255,0,
           255,0,0,128,  255,0,0,255,  255,0,255,0 };
    Image image( Image::OSG_RGBA_PF, 3, 2, 1, 1, 1, 0, imgdata );

    pm->setImage( &image ); // NOTE: the image is NOT copied, the variable
                            // needs to be kept around as long as the texture
                            // is used
    pm->setMagFilter( GL_NEAREST );
    endEditCP(pm);

    plane_geo->setMaterial( pm );


    tm = SimpleTexturedMaterial::create();

    beginEditCP(tm);
    tm->setDiffuse( Color3f( 0,1,0 ) );
    tm->setAmbient( Color3f( 0,1,0 ) );

    UChar8 imgdata2[] =
        {  255,0,0,  255,0,0,  255,0,255,
           255,0,0,  255,0,0,  255,0,255 };
    Image image2( Image::OSG_RGB_PF, 3, 2, 1, 1, 1, 0, imgdata2 );

    tm->setImage( &image2 );
    tm->setEnvMode( GL_MODULATE );
    tm->setEnvMap( true );
    endEditCP(tm);

    torus_geo->setMaterial( tm );

    //
    // The action

    win = GLUTWindow::create();

    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );

    glutMainLoop();

    return 0;
}

