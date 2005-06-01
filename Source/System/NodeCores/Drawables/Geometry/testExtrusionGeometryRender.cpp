#include <OSGConfig.h>

#include <iostream>
#include <ctype.h>
#include <OSGGLUT.h>

#include <OSGSimpleSceneManager.h>

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
#include "OSGExtrusionGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGFaceIterator.h"

OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

GLUTWindowPtr win;

const int nobjects = 1;
NodePtr  objects[nobjects];
NodePtr  normalobjects[nobjects];

bool autoswitch = false;
bool autowire = false;
bool shownormals = true;
int obj = 0;

std::vector<Pnt2f> section;
std::vector<Pnt3f> spine;
std::vector<Quaternion> orientation;
std::vector<Vec2f> scale;

void
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

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

    mgr->redraw();
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

// react to size changes
void resize( int w, int h )
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

int main (int argc, char **argv)
{
    // check arguments
    UInt32 subdivs = 0;
    if(argc > 1)
    {
        sscanf(argv[1], "%d", &subdivs);
    }

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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
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



#define RIGHT   1.f
#define LEFT   -1.f
#define CENTER  0.f
#define TOP     1.f
#define BOTTOM -1.f

    section.push_back(Pnt2f(RIGHT,  CENTER));
    section.push_back(Pnt2f(CENTER, TOP));
    section.push_back(Pnt2f(LEFT,   CENTER));
    section.push_back(Pnt2f(CENTER, BOTTOM));
    section.push_back(Pnt2f(RIGHT,  CENTER));

    spine.push_back(Pnt3f(0.f, -4.f, 0.f));
    spine.push_back(Pnt3f(0.f, -3.f, 0.f));
    spine.push_back(Pnt3f(0.f, -2.f, 0.f));
    spine.push_back(Pnt3f(0.f, -1.f, 0.f));
    spine.push_back(Pnt3f(0.f,  0.f, 0.f));
    spine.push_back(Pnt3f(0.f,  1.f, 0.f));
    spine.push_back(Pnt3f(0.f,  2.f, 0.f));
    spine.push_back(Pnt3f(0.f,  3.f, 0.f));
    spine.push_back(Pnt3f(0.f,  4.f, 0.f));

    
#undef RIGHT
#undef LEFT
#undef CENTER
#undef TOP
#undef BOTTOM
    
    Quaternion q(Vec3f(0.f, 1.f, 0.f), 0.f);
    orientation.push_back(q);
    
    scale.push_back(Vec2f(1.f, 1.f));
    scale.push_back(Vec2f(2.f, 1.f));
    scale.push_back(Vec2f(1.f, 1.f));
    scale.push_back(Vec2f(1.f, 2.f));
    scale.push_back(Vec2f(1.f, 1.f));
    scale.push_back(Vec2f(2.f, 2.f));
    scale.push_back(Vec2f(1.f, 1.f));
    scale.push_back(Vec2f(1.f, 2.f));

    
    objects[0] = makeExtrusion(section,
				               orientation, 
                               scale,
                               spine,
							   0.f,
                               true,   // bool _beginCap
                               true,   // bool _endCap
                               false,  // bool _ccw
                               true,   // bool _convex
                               true,   // bool _buildNormal
                               true,   // bool _buildTexCoord
                               subdivs);     // UInt32 _numOfSubdivision

    GeometryPtr::dcast(objects[0]->getCore())->setMaterial( mat );
    std::cerr << "Extrusion Node: " << std::hex << objects[0] << std::endl;
 
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

    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(win);
    mgr->setRoot  (objects[0]);

    // show the whole scene
    mgr->showAll();

    glutMainLoop();
    
    return 0;
}

