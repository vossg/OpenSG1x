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
#include <OSGImage.h>

#include "OSGSimpleTexturedMaterial.h"
#include "OSGBlendChunk.h"
#include <OSGParticles.h>


OSG_USING_NAMESPACE


DrawAction * dact;
WindowPtr win;
NodePtr plane,parts;

void
display(void)
{
    // do the motion in OpenGl, to stay independent of the ransform node
    // use the draw action to check the material

    float a = glutGet( GLUT_ELAPSED_TIME );

    win->frameInit();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( a / 20, 0,0,1 );

    dact->apply( plane );

    glPushMatrix();
    glTranslatef( 0,0,fabs(osgsin(a/3000 * Pi))*2+.5 );
    glRotatef( (a/3000) * 360 / 2, 1,0,0 );

    dact->apply( parts );

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

    GeometryPtr plane_geo;
    plane_geo = GeometryPtr::dcast(plane->getCore());

    // create the scene
    parts = Node::create();
    ParticlesPtr particles = Particles::create();

    beginEditCP(parts);
    parts->setCore( particles );
    endEditCP(parts);

    beginEditCP(particles);

    GeoPositions3fPtr pnts = GeoPositions3f::create();
    particles->setPositions( pnts );

    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    p->push_back( Pnt3f( -.5, -.5, -0.5) );
    p->push_back( Pnt3f(  .5, -.5, -0.5) );
    p->push_back( Pnt3f(  .5,  .5, -0.5) );
    p->push_back( Pnt3f( -.5,  .5, -0.5) );
    p->push_back( Pnt3f( -.5, -.5,  0.5) );
    p->push_back( Pnt3f(  .5, -.5,  0.5) );
    p->push_back( Pnt3f(  .5,  .5,  0.5) );
    p->push_back( Pnt3f( -.5,  .5,  0.5) );
    endEditCP(pnts);


    GeoColors3fPtr cols = GeoColors3f::create();
    particles->setColors( cols );
    beginEditCP(cols);
    cols->getFieldPtr()->push_back( Color3f( 255, 255, 255) );
    cols->getFieldPtr()->push_back( Color3f(   0, 255, 255) );
    cols->getFieldPtr()->push_back( Color3f( 255,   0, 255) );
    cols->getFieldPtr()->push_back( Color3f( 255, 255,   0) );
    cols->getFieldPtr()->push_back( Color3f( 255,   0,   0) );
    cols->getFieldPtr()->push_back( Color3f(   0, 255,   0) );
    cols->getFieldPtr()->push_back( Color3f( 255,   0,   0) );
    cols->getFieldPtr()->push_back( Color3f(   0, 255,   0) );
    endEditCP(cols);

    MFVec3f *size = particles->getMFSizes();
    size->push_back( Vec3f(.3,0,0) );
    size->push_back( Vec3f(.3,0,0) );
    size->push_back( Vec3f(.3,0,0) );
    size->push_back( Vec3f(.3,0,0) );
    size->push_back( Vec3f(.2,0,0) );
    size->push_back( Vec3f(.2,0,0) );
    size->push_back( Vec3f(.2,0,0) );
    size->push_back( Vec3f(.2,0,0) );

     
    endEditCP(particles);



    SimpleTexturedMaterialPtr pm, tm;

    pm = SimpleTexturedMaterial::create();

    beginEditCP(pm);
    pm->setDiffuse( Color3f( 1,0,0 ) );
    pm->setAmbient( Color3f( 1,0,0 ) );
    pm->setSpecular( Color3f( 1,1,1 ) );
    pm->setShininess( 10 );
    pm->setMagFilter( GL_NEAREST );
    endEditCP(pm);

    plane_geo->setMaterial( pm );


    tm = SimpleTexturedMaterial::create();

    UChar8 imgdata[] =
        {  255,0,0,  255,0,0,  255,0,255,
           255,0,0,  255,0,0,  255,0,255 };
    ImagePtr pImage = Image::create();

    if (argc > 1)
    {
        pImage->read(argv[1]);
    }
    else
    {
        pImage->set(Image::OSG_RGB_PF, 3, 2, 1, 1, 1, 0, imgdata);
    }
    
    beginEditCP(tm);
    tm->setDiffuse( Color3f( 1,1,1 ) );
    tm->setLit( false );

    tm->setImage( pImage );
    tm->setEnvMode( GL_MODULATE );
    
    BlendChunkPtr bl=BlendChunk::create();
    
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    bl->setAlphaFunc(GL_NOTEQUAL);
    bl->setAlphaValue(0);   
    endEditCP(bl);
   
    tm->addChunk(bl);
    
    endEditCP(tm);

    particles->setMaterial( tm );

    //
    // The action

    win = GLUTWindow::create();

    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );

    glutMainLoop();

    return 0;
}

