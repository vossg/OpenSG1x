#include <OSGGLUT.h>

#ifndef GL_ARB_multitexture
#include <stdio.h>

int main(int argc, char *argv[])
{
    fprintf(stderr,"%s: only works with multi-texture support!\n", argv[0]);
    return 0;
}

#else

#include <OSGLog.h>

#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGDrawAction.h>

#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGBlendChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGLineChunk.h"

OSG_USING_NAMESPACE

TransformChunkPtr tchunk1, tchunk2;
MaterialChunkPtr mchunk1, mchunk2;
TextureChunkPtr xchunk1, xchunk2;
BlendChunkPtr blchunk;
TextureTransformChunkPtr txchunk,txchunk2;

Image *pImage;

GLint dlid, dlid2;

WindowPtr win;

DrawAction *dact;

void
display(void)
{
    float t = glutGet( GLUT_ELAPSED_TIME );

    win->frameInit();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Matrix m;
    Quaternion q;
    q.setValueAsAxisDeg( 0,1,0, -t/20 );
    m.setRotate( q );
    tchunk1->setMatrix( m );

    tchunk1->activate( dact );
    mchunk1->activate( dact );

//    glCallList( dlid );

    m.setIdentity();
    m.setTranslate( cos(t/1000), 0, sin(t/1000) );
    tchunk2->setMatrix( m );


    tchunk2->changeFrom( dact, tchunk1.getCPtr() );
    mchunk2->changeFrom( dact, mchunk1.getCPtr() );
    blchunk->activate( dact );

    glCallList( dlid );

    tchunk2->deactivate( dact );
    mchunk2->deactivate( dact );
    blchunk->deactivate( dact );

    xchunk1->activate( dact, 0 );
    xchunk2->activate( dact, 1 );
    txchunk->activate( dact, 0 );
    txchunk2->activate( dact, 1 );

    glCallList( dlid2 );

    xchunk1->deactivate( dact, 0 );
    xchunk2->deactivate( dact, 1 );
    txchunk->deactivate( dact, 0 );
    txchunk2->deactivate( dact, 1 );

    win->frameExit();

    glutSwapBuffers();
}

void key(unsigned char key, int , int)
{
    switch ( key )
    {
    case 27:    exit(0);
    case 'a':   UChar8 imgdata[32];
                for ( int i = 0; i < 32; i++ )
                    imgdata[i] = (UChar8) rand();
                pImage->set( Image::OSG_RGB_PF, 2, 2, 2, 1, 1, 0, imgdata );
                xchunk1->imageContentChanged();
                break;
    case 'b':   {
                UChar8 imgdata[16];
                for ( int i = 0; i < 16; i++ )
                    imgdata[i] = (UChar8) rand();
                pImage->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );
                beginEditCP( xchunk1 );
                xchunk1->setImage( pImage );
                endEditCP( xchunk1 );
                }
                break;
    case 'c':   {
                beginEditCP( xchunk1 );
                xchunk1->setMinFilter( GL_LINEAR_MIPMAP_LINEAR );
                xchunk1->setMagFilter( GL_LINEAR );
                endEditCP( xchunk1 );
                }
                break;
    case 'd':   {
                beginEditCP( xchunk1 );
                xchunk1->setMinFilter( GL_NEAREST );
                xchunk1->setMagFilter( GL_NEAREST );
                endEditCP( xchunk1 );
                }
                break;
    }
}

int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    // glutReshapeFunc(resize);
    glutDisplayFunc(display);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);

    glutIdleFunc(display);

    // create the dummy structures

    // the window is needed for the chunks that access GLObjects

    win = GLUTWindow::create();
    win->frameInit(); // test for preliminary calls not messing up GLexts
    win->init();
    
    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );

    win->init();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 1, 0 );

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    dlid = glGenLists( 1 );
    glNewList( dlid, GL_COMPILE );
    glutSolidSphere( .8, 8, 8 );
    glEndList();

    dlid2 = glGenLists( 1 );
    glNewList( dlid2, GL_COMPILE );
    glBegin( GL_POLYGON );
    glNormal3f( 0, 1, 0 );
    glColor3f( 1, 1, 1 );
    glTexCoord2f( 0, 0 );
    glMultiTexCoord2fARB( GL_TEXTURE1_ARB, 0, 0 );
    glVertex3f( -1.5, -1, -1.5 );
    glTexCoord2f( 2, 0 );
    glMultiTexCoord2fARB( GL_TEXTURE1_ARB, 2, 0 );
    glVertex3f(  1.5, -1, -1.5 );
    glTexCoord2f( 2, 2 );
    glMultiTexCoord2fARB( GL_TEXTURE1_ARB, 2, 2 );
    glVertex3f(  1.5, -1,  1.5 );
    glTexCoord2f( 0, 2 );
    glMultiTexCoord2fARB( GL_TEXTURE1_ARB, 0, 2 );
    glVertex3f( -1.5, -1,  1.5 );
    glEnd();
    glEndList();


    Matrix m;

    pImage = new Image;

    tchunk1 = TransformChunk::create();
    m.setTranslate( 0, 1, 0 );
    tchunk1->setMatrix( m );

    tchunk2 = TransformChunk::create();
    tchunk2->setMatrix( Matrix::identity() );


    mchunk1 = MaterialChunk::create();
    mchunk1->setDiffuse( Color4f( 1,0,0,0 ) );
    mchunk1->setAmbient( Color4f( 1,0,0,0 ) );
    mchunk1->setShininess( 20 );

    mchunk2 = MaterialChunk::create();
    mchunk2->setDiffuse( Color4f( 0,1,0,0 ) );
    mchunk2->setAmbient( Color4f( 0,1,0,0 ) );
    mchunk2->setShininess( 50 );

    // Texture chunk

//  UChar8 imgdata[] =
//      {  255,0,0,0,  0,255,0,0,  0,0,255,255,  255,255,255,255 };
    UChar8 imgdata[] =
        {  255,0,0,  255,0,0,  255,0,255,
           255,0,0,  255,0,0,  255,0,255,
           255,255,0,  255,255,0,  255,255,255,
           255,255,0,  255,255,0,  255,255,255, };
//  UChar8 limgdata[] =
//      {  0, 128, 64, 255 };
    pImage->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata );

    if ( argc > 1 )
        pImage->read( argv[1] );

    xchunk1 = TextureChunk::create();
    beginEditCP(xchunk1);
    xchunk1->setImage( pImage ); // NOTE: the image is NOT copied, the variable
                                 // needs to be kept around as long as the 
                                 // texture is used
    xchunk1->setMinFilter( GL_LINEAR );
    xchunk1->setMagFilter( GL_NEAREST );
    xchunk1->setWrapS( GL_REPEAT );
    xchunk1->setWrapT( GL_REPEAT );
    xchunk1->setEnvMode( GL_REPLACE );
    xchunk1->setScale( false );
    endEditCP(xchunk1);

    xchunk1->imageContentChanged();

    beginEditCP(xchunk1);
    xchunk1->setImage( pImage );
    endEditCP(xchunk1);

    UChar8 imgdata2[] =
    {  255,0,0,  0,255,0,  0,0,255,  255,255,255 };


    Image *pImage2 = new Image(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata2);

    xchunk2 = TextureChunk::create();
    beginEditCP(xchunk2);
    xchunk2->setImage( pImage2 );
    xchunk2->setMinFilter( GL_LINEAR );
    xchunk2->setMagFilter( GL_LINEAR );
    xchunk2->setWrapS( GL_REPEAT );
    xchunk2->setWrapT( GL_REPEAT );
    xchunk2->setEnvMode( GL_MODULATE );
    endEditCP(xchunk2);
    
    // blend chunk

    blchunk = BlendChunk::create();
#ifndef WIN32
//    blchunk->setSrcFactor( GL_CONSTANT_ALPHA );
//    blchunk->setDestFactor( GL_ONE_MINUS_CONSTANT_ALPHA );
#endif
    blchunk->setColor( Color4f( 1,1,1,0.1 ) );

    // texture transform chunk

    txchunk = TextureTransformChunk::create();
    beginEditCP(txchunk);
    txchunk->setMatrix( Matrix(4,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1) );
    endEditCP(txchunk);

    txchunk2 = TextureTransformChunk::create();
    beginEditCP(txchunk2);
    Quaternion q;
    q.setValueAsAxisDeg(0,0,1, 45);
    m.setTransform(q);
    txchunk2->setMatrix(m);
    endEditCP(txchunk2);

    glutMainLoop();

    return 0;
}

#endif
