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

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGFaceIterator.h"

#include "OSGVRMLWriteAction.h"
#include <OSGSceneFileHandler.h>
#include <fstream>
#include <string>

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

//Double Eight Square (not well oriented)
//This one is known to be broken!
double doubleEight[][3] = 
  {
    { 0.0, 0.0,-1.0 },
    {-1.0, 1.0,-1.0 },
    {-2.0, 0.0,-1.0 },
    {-1.0,-1.0,-1.0 },
    { 0.0, 0.0,-1.0 },
    { 1.0,-1.0,-1.0 },
    { 2.0, 0.0,-1.0 },
    { 1.0, 1.0,-1.0 },
    { 0.0, 0.0,-1.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 1.0, 1.0 },
    {-2.0, 0.0, 1.0 },
    {-1.0,-1.0, 1.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0,-1.0, 1.0 },
    { 2.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 0.0, 0.0, 1.0}
  }; 

//  A star (ccw orientation)
double star[][3] = 
  {
    { 1.0, 0.0, 1.0 },
    { 0.2, 0.2, 1.0 },
    { 0.0, 1.0, 1.0 },
    {-0.2, 0.2, 1.0 },
    {-1.0, 0.0, 1.0 },
    {-0.2,-0.2, 1.0 },
    { 0.0,-1.0, 1.0 },
    { 0.2,-0.2, 1.0 }
  }; 

// counter clockwise oriented Square
double ccwSquare[][3] = 
  {
    { 1.0, 1.0, 1.0 },
    {-1.0, 1.0, 1.0 },
    {-1.0,-1.0, 1.0 },
    { 1.0,-1.0, 1.0 }
  };

// clockwise oriented Square
double cwSquare[][3] = 
  {
    { 1.0, 1.0, 1.0 },
    { 1.0,-1.0, 1.0 },
    {-1.0,-1.0, 1.0 },
    {-1.0, 1.0, 1.0 },
  }; 

OSG::NodePtr makePolygon(double pntData[][3], int numPoints) {

  OSG::GeometryPtr geoPtr  = OSG::Geometry::create();
  OSG::NodePtr     nodePtr = OSG::Node::create();

  GeoPositions3fPtr    pnts    = GeoPositions3f::create();
  GeoNormals3fPtr      norms   = GeoNormals3f::create();
  GeoTexCoords2fPtr    tex     = GeoTexCoords2f::create();
  GeoIndicesUI32Ptr    indices = GeoIndicesUI32::create();   
  GeoPLengthsUI32Ptr   lens    = GeoPLengthsUI32::create();  
  GeoPTypesUI8Ptr      types   = GeoPTypesUI8::create();     

  //Set up the properties according to the geometry defined above
  beginEditCP(pnts);
  beginEditCP(norms);
  
  for(int i = 0; i < numPoints; i++) 
    {
      pnts->push_back(Pnt3f(pntData[i][0],
                            pntData[i][1], 
                            pntData[i][2]));

      indices->push_back(2*i);

      norms->push_back(Vec3f(0.0, 0.0, pntData[i][2]));
      indices->push_back(2*i + 1);
    }

  endEditCP(pnts);
  endEditCP(norms);

  beginEditCP(types);
  beginEditCP(lens);
  types->push_back(GL_POLYGON);
  lens->push_back(numPoints);
  endEditCP(types);
  endEditCP(lens);

  beginEditCP(geoPtr);
  
  geoPtr->setMaterial(getDefaultMaterial());
  geoPtr->setPositions(pnts);
  geoPtr->setNormals(norms);
  geoPtr->setIndices(indices);
  
  geoPtr->getIndexMapping().push_back(Geometry::MapPosition | 
                                      Geometry::MapNormal);
  
  geoPtr->setTypes(types);
  geoPtr->setLengths(lens);
  
  endEditCP(geoPtr);

  nodePtr->setCore(geoPtr);
  return nodePtr;
}

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
    osgLog().setLogLevel ( OSG::LOG_DEBUG );

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

    objects[0] = makePolygon(ccwSquare, 
                             sizeof(ccwSquare)/sizeof(double[3]));
    objects[1] = makePolygon(ccwSquare, 
                             sizeof(ccwSquare)/sizeof(double[3]));
    
    objects[2] = makePolygon(star,
                             sizeof(star)/sizeof(double[3]));
    objects[3] = makePolygon(star,
                             sizeof(star)/sizeof(double[3]));
    
    objects[4] = makePolygon(cwSquare, 
                             sizeof(cwSquare)/sizeof(double[3]));
    objects[5] = makePolygon(cwSquare, 
                             sizeof(cwSquare)/sizeof(double[3]));
    
    objects[6] = makePolygon(doubleEight, 
                             sizeof(doubleEight)/sizeof(double[3]));
    objects[7] = makePolygon(doubleEight, 
                             sizeof(doubleEight)/sizeof(double[3]));

    //tesselate every second object
    for(int i = 1; i < nobjects; i+=2) {

      GeometryPtr::dcast(objects[i]->getCore())->setMaterial( mat );
      std::cerr << "Polygon Node: " << std::hex << objects[i] << std::endl;

      // try to create convex primitives
      OSG::GeometryPtr pGeo = GeometryPtr::dcast(objects[i]->getCore());

      std::cerr << "Tesselating polygon : "
                << i
                << std::endl;

      createConvexPrimitives(pGeo);
    }

    // normal material
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

