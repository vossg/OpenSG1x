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
#include <OSGGLUTWindow.h>

#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>

#include "OSGMaterial.h"
#include "OSGChunkMaterial.h"
#include "OSGSimpleMaterial.h"


OSG_USING_NAMESPACE


DrawAction * dact;

WindowPtr win;

NodePtr plane,torus;
ChunkMaterialPtr pm;
SimpleMaterialPtr tmat;

void
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    if ( (int) ( a / 2000 ) & 1 )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    win->frameInit();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( a / 20, 0,0,1 );

    dact->apply( plane );

    glPushMatrix();
    glTranslatef( 0,0,fabs(osgsin(a/3000 * Pi))*2 );
    glRotatef( (a/3000) * 360 / 2, 1,0,0 );

    dact->apply( torus );

    // do some OpenGL rendering

    StatePtr st = pm->makeState();

    addRefCP( st );

    st->activate( dact );
    glutSolidSphere( .4, 8, 8 );
    st->deactivate( dact );

    subRefCP( st );

    glPopMatrix();

    glPopMatrix();

    win->frameExit();

    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);

    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }

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


    // OSG

    plane = makePlane( 2, 2, 8, 8 );
    torus = makeTorus( .2, 1, 16, 8 );

    GeometryPtr plane_geo, torus_geo;
    plane_geo = GeometryPtr::dcast(plane->getCore());
    torus_geo = GeometryPtr::dcast(torus->getCore());


    TextureChunkPtr tx2 = TextureChunk::create();
   
   
    const UInt16 p2size = 128;
    const UInt16 t2size = 16;
    
    ImagePtr pImg2 = Image::create();
    pImg2->set(Image::OSG_RGB_PF, p2size, p2size );
    
    beginEditCP(pImg2);
    UInt8 *d = pImg2->getData();
    
    for(UInt16 y = 0; y < p2size; ++y)
    {
        for(UInt16 x = 0; x < p2size; ++x)
        {
            if((x / t2size + y / t2size) & 1)
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
            }
            else
            {
                *d++ = 64;
                *d++ = 128;
                *d++ = 255;
            }
        }
    }
    endEditCP(pImg2);
    
    beginEditCP(tx2);
    tx2->setImage(pImg2);
    tx2->setMinFilter(GL_LINEAR);
    tx2->setMagFilter(GL_LINEAR);
    tx2->setWrapS(GL_REPEAT);
    tx2->setWrapT(GL_REPEAT);
    
    endEditCP(tx2);

    pm = ChunkMaterial::create();

    beginEditCP(pm);
    
    MaterialChunkPtr pmc = MaterialChunk::create();
    beginEditCP(pmc);
    pmc->setDiffuse( Color4f( 1,0,0,0 ) );
    pmc->setAmbient( Color4f( 1,0,0,0 ) );
    pmc->setSpecular( Color4f( 1,1,1,0 ) );
    pmc->setShininess( 20 );
    endEditCP(pmc);

    pm->addChunk( pmc );
    pm->addChunk( tx2, 1 );
    endEditCP(pm);

    pm->dump();
    
    std::cout << pm->getMFChunks()->size() << " " 
              << pm->getMFSlots()->size() << std::endl;
    
    plane_geo->setMaterial( pm );

    BlendChunkPtr bl = BlendChunk::create();
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP(bl);
    
    tmat = SimpleMaterial::create();

    beginEditCP(tmat);
    tmat->setDiffuse( Color3f( 0,1,0 ) );
    tmat->setAmbient( Color3f( 0,1,0 ) );
    tmat->addChunk(bl );
    endEditCP(tmat);

    torus_geo->setMaterial( tmat );

    tmat->dump();
    
    FLOG(("TorusMat is trans: %d\n", tmat->isTransparent() ));

    // the window is needed for the chunks that access GLObjects

    win = GLUTWindow::create();
    win->frameInit(); // test for preliminary calls not messing up GLexts
    win->init();

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );

    win->init();

    glutMainLoop();

    return 0;
}

