#include <OSGConfig.h>

#include <iostream>

#include <ctype.h>
#include <OSGGLUT.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>

#include <OSGChunkMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGMaterialChunk.h>

#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGImage.h>

#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGFaceIterator.h"

OSG_USING_NAMESPACE

DrawAction * dact;
GLUTWindowPtr win;

const int nobjects = 8;
NodePtr  objects[nobjects];
NodePtr  normalobjects[nobjects];

bool autoswitch = true;
bool autowire = true;
bool shownormals = true;
int obj = 0;

void 
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    win->frameInit();
    
    if ( autowire )
        switch ( (int) ( a / 2000 ) % 3 )   
        {
        case 0:     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); break;
        case 1:     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); break;
        case 2:     glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ); break;
        }

    if ( autoswitch )
        obj = (int) ( a / 5000 ) % nobjects ;  

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glPushMatrix();
    glRotatef( a / 36, 0,0,1 );

    dact->apply( objects[ obj ] );
    if ( shownormals )
        dact->apply( normalobjects[ obj ] );

    glPopMatrix();

    glutSwapBuffers();

    win->frameExit();
}

void key( unsigned char key, int, int )
{
    switch ( tolower( key ) )
    {
    case 27:    exit(0);
    case ' ':   autoswitch = ! autoswitch;
                std::cerr << "autoswitch " << (autoswitch?"on":"off") << std::endl;
                break;
    case 'w':   autowire = ! autowire;
                std::cerr << "autowire " << (autowire?"on":"off") << std::endl;
                break;
    case 'a':   obj = ( ++ obj ) % nobjects;
                std::cerr << "object now " << obj << std::endl;
                break;
    case 'n':   shownormals = ! shownormals;
                std::cerr << "shownormals " << (shownormals?"on":"off") << std::endl;
                break;
    case 's':   obj = ( -- obj + nobjects ) % nobjects;
                std::cerr << "object now " << obj << std::endl;
                break;

    case 'c':   if ( glIsEnabled( GL_CULL_FACE ) )
                {
                    glDisable( GL_CULL_FACE );
                    std::cerr << "cullface disabled" << std::endl;
                }
                else
                {
                    glEnable( GL_CULL_FACE );
                    std::cerr << "cullface enabled" << std::endl;
                }
    }
}

void resize( int w, int h )
{
    glViewport( 0,0,w,h);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, w / (float)h, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );   
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);

    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(true);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    UInt32 id = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);       
    // glutMouseFunc(mouse);   
    // glutMotionFunc(motion); 
    
    glutIdleFunc(display);
    
    // create a material (need that to test textures)
    
    ChunkMaterialPtr mat;  

    beginEditCP(mat);
    
    mat = ChunkMaterial::create();
   
    MaterialChunkPtr mc = MaterialChunk::create();  
 
    beginEditCP(mc);
    mc->setDiffuse( Color4f( 1,.8,.8,1 ) );
    mc->setAmbient( Color4f( 0.1,0.1,0.1,1 ) );
    mc->setSpecular( Color4f( 1,1,1,1 ) );
    mc->setShininess( 20 );
 
    mc->setBackMaterial(true);
    mc->setBackColorMaterial(GL_DIFFUSE);
    mc->setBackDiffuse( Color4f( 1,0,0,1 ) );
    mc->setBackAmbient( Color4f( 0.1,0.1,0.1,1 ) );
    mc->setBackSpecular( Color4f( 0,1,0,1 ) );
    mc->setBackShininess( 10 );
    mc->setLit(true);
 
    endEditCP(mc);

    mat->addChunk(mc);

    // Texture chunk
    
    UChar8 imgdata[] = 
        {  255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 };
    ImagePtr pImage = Image::create();
    pImage->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );

    if ( argc > 1 )
        pImage->read( argv[1] );
    
    TextureChunkPtr xchunk;
    xchunk = TextureChunk::create();
    xchunk->setImage( pImage );
    xchunk->setMinFilter( GL_NEAREST );
    xchunk->setMagFilter( GL_NEAREST );
    xchunk->setWrapS( GL_REPEAT );
    xchunk->setWrapT( GL_REPEAT );
    xchunk->setEnvMode( GL_MODULATE );

    mat->addChunk( xchunk );

    endEditCP(mat);

    // create the objects

    objects[0] = makePlane( 1, 1, 2, 2 );
    GeometryPtr::dcast(objects[0]->getCore())->setMaterial( mat );
    std::cerr << "Plane Node: " << std::hex << objects[0] << std::endl;
 
    unsigned int ntris = 0;
    unsigned int nquads = 0;
    unsigned int ngons = 0;

    for(OSG::FaceIterator fi = 
            GeometryPtr::dcast(objects[0]->getCore())->beginFaces();
          fi != GeometryPtr::dcast(objects[0]->getCore())->endFaces(); ++ fi )
    {
        if ( fi.getLength() == 3 )
            ntris ++ ;
        else 
            if ( fi.getLength() == 4 )
                nquads ++ ;
            else
                ngons ++ ;
    }

    fprintf(stderr, "ntris %d nquads %d ngons %d\n", ntris, nquads, ngons);


    objects[1] = makeCone( 2.5, 2, 20, true, true );
    GeometryPtr::dcast(objects[1]->getCore())->setMaterial( mat );
    std::cerr << "Cone Node: " << std::hex << objects[1] << std::endl;

    objects[2] = makeTorus( .6, 2, 8, 16 );
    GeometryPtr::dcast(objects[2]->getCore())->setMaterial( mat );
    std::cerr << "Torus Node: " << std::hex << objects[2] << std::endl;

    objects[3] = makeSphere( 3, 1 );
    GeometryPtr::dcast(objects[3]->getCore())->setMaterial( mat );
    std::cerr << "Sphere Node: " << std::hex << objects[3] << std::endl;

    
    objects[4] = makeCylinder( 3, 2, 20, true, true, true );
    GeometryPtr::dcast(objects[4]->getCore())->setMaterial( mat );
    std::cerr << "Cylinder Node: " << std::hex << objects[4] << std::endl;
    
    objects[5] = makeConicalFrustum( 3, 2, 1, 3, true, true, true );
    GeometryPtr::dcast(objects[5]->getCore())->setMaterial( mat );
    std::cerr << "Frustum Node: " << std::hex << objects[5] << std::endl;

    objects[6] = makeBox( 4, 3, 2, 4, 3, 2 );
    GeometryPtr::dcast(objects[6]->getCore())->setMaterial( mat );
    std::cerr << "Box Node: " << std::hex << objects[6] << std::endl;

    objects[7] = makeLatLongSphere( 16, 32, 1 );
    GeometryPtr::dcast(objects[7]->getCore())->setMaterial( mat );
    std::cerr << "LatLongSphere Node: " << std::hex << objects[7] << std::endl;
    
    // try the vertex normal calc
    //OSG::GeometryPtr pGeo = dcast<GeometryPtr>(objects[3]->getCore());
    //calcVertexNormals(pGeo);

    // Normals
    
    // normals material
    
    SimpleMaterialPtr nmat;     
    
    nmat = SimpleMaterial::create();
    beginEditCP(nmat);
    nmat->setEmission( Color3f( 0,1,0 ) );
    endEditCP(nmat);
    
    for ( UInt16 i = 0; i < nobjects; i++ )
    {
        normalobjects[i] = calcVertexNormalsGeo(
            GeometryPtr::dcast(objects[i]->getCore()), .5);

        GeometryPtr::dcast(normalobjects[i]->getCore())->setMaterial(nmat);
    }
    
    // 
    // The action

    win = GLUTWindow::create();
    win->setId(id);
    win->init();

    glEnable( GL_LIGHT0 );
    float p[4]={0,0,1,0};
    glLightfv(GL_LIGHT0, GL_POSITION, p);
    float c[4]={1,1,1,1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, c);
    glLightfv(GL_LIGHT0, GL_SPECULAR, c);
    
    glPointSize( 3 );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glClearColor( .3, .3, .8, 1 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );
   
    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );
    dact->setFrustumCulling( false );

    glutMainLoop();
    
    return 0;
}

