#include <OSGConfig.h>

#include <iostream>
#include <OSGGLUT.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGDirectionalLight.h>
#include <OSGViewport.h>
#include <OSGCamera.h>
#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGSolidBackground.h>
#include <OSGDistanceLOD.h>
#include <OSGMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGTrackball.h>
#include <OSGGeoFunctions.h>


OSG_USING_NAMESPACE

DrawAction *drAct;
NodePtr root;
PerspectiveCameraPtr camera;
ViewportPtr viewp;
WindowPtr window;
TransformPtr cam_trans;
Trackball tball;

const int numObj = 4;
NodePtr objects[numObj];
NodePtr normals[numObj];

int mouseb = 0;
int lastX=0, lastY=0;
Int32 activeObj = 0;
Int32 activeNorm = 0;
int activeIndex = 0;

void display(void)
{
  Matrix m1, m2, m3;
  Quaternion q1;
  
  tball.getRotation().getValue(m3);
  q1.setValue(m3);
  m1.setRotate(q1);
  m2.setTranslate( tball.getPosition() );
  m1.mult( m2 );
  cam_trans->getSFMatrix()->setValue( m1 );
  window->draw( drAct );
}

void animate(void)
{
  glutPostRedisplay();
}

void key(unsigned char key, int, int)
{
    switch ( key )
    {
        case 27:    osgExit(); exit(0);
        case 'a':   glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':   glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'z':   glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            std::cerr << "PolygonMode: Point." << std::endl;
            break;
        case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            std::cerr << "PolygonMode: Line." << std::endl;
            break;
        case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            std::cerr << "PolygonMode: Fill." << std::endl;
            break;
    case 'q': 
      if( activeIndex != 0 )
        {
          beginEditCP(root);
          root->replaceChild( activeObj, objects[0] );
          root->replaceChild( activeNorm, normals[0] );
          activeObj = root->findChild( objects[0] );
          activeNorm = root->findChild( normals[0] );
          endEditCP(root);
          activeIndex = 0;
        }
      break;
    case 'w':
      if( activeIndex != 1 )
        {
          beginEditCP(root);
          root->replaceChild( activeObj, objects[1] );
          root->replaceChild( activeNorm, normals[1] );
          activeObj = root->findChild( objects[1] );
          activeNorm = root->findChild( normals[1] );
          endEditCP(root);
          activeIndex = 1;
        }
      break;
    case 'e':
      if( activeIndex != 2 )
        {
          beginEditCP(root);
          root->replaceChild( activeObj, objects[2] );
          root->replaceChild( activeNorm, normals[2] );
          activeObj = root->findChild( objects[2] );
          activeNorm = root->findChild( normals[2] );
          endEditCP(root);
          activeIndex = 2;
        }
      break;
    case 'r':
      if( activeIndex != 3 )
        {
          beginEditCP(root);
          root->replaceChild( activeObj, objects[3] );
          root->replaceChild( activeNorm, normals[3] );
          activeObj = root->findChild( objects[3] );
          activeNorm = root->findChild( normals[3] );
          endEditCP(root);
          activeIndex = 3;
        }
      break;
    }
}


void resize(int w, int h )
{
  window->resize( w, h );
}

void motion(int x, int y)
{   
  Real32 w = window->getWidth(), h = window->getHeight();
  
  
  Real32    a = -2. * ( lastX / w - .5 ),
    b = -2. * ( .5 - lastY / h ),
    c = -2. * ( x / w - .5 ),
    d = -2. * ( .5 - y / h );
  
  if ( mouseb & ( 1 << GLUT_LEFT_BUTTON ) )
    {
      tball.updateRotation( a, b, c, d );   
    }
  else if ( mouseb & ( 1 << GLUT_MIDDLE_BUTTON ) )
    {
      tball.updatePosition( a, b, c, d );   
    }
  else if ( mouseb & ( 1 << GLUT_RIGHT_BUTTON ) )
    {
      tball.updatePositionNeg( a, b, c, d );    
    }
  lastX = x;
  lastY = y;
}


void mouse(int button, int state, int x, int y)
{
  if ( state == 0 )
    {
      switch ( button )
    {
    case GLUT_LEFT_BUTTON:  break;
    case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
      break;
    case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(true);
      break;
    }
      mouseb |= 1 << button;
    }
  else if ( state == 1 )
    {
      switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(false);
          break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(false);
          break;
        }       
      mouseb &= ~(1 << button);
    }
  lastX = x;
  lastY = y;
}

void vis(int visible)
{
  if (visible == GLUT_VISIBLE) 
    {
      glutIdleFunc(animate);
    } 
  else 
    {
      glutIdleFunc(NULL);
    }
}





int main (int argc, char **argv)
{
  osgInit( argc, argv );
  
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
  int winID = glutCreateWindow("OpenSG");
  
  glutKeyboardFunc(key);
  glutVisibilityFunc(vis);
  glutReshapeFunc(resize);
  glutDisplayFunc(display);       
  glutMouseFunc(mouse);   
  glutMotionFunc(motion); 
  
  glutIdleFunc(display);
  
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glClearColor( .1, .6, .2, 1 );
  //glCullFace( GL_BACK );
  //glEnable( GL_CULL_FACE );

  //BEACON
  NodePtr beaconNode = Node::create();
  GroupPtr beaconCore = Group::create();
  beginEditCP( beaconNode );
  beaconNode->setCore( beaconCore );
  endEditCP( beaconNode );

  //TRANSFORM
  NodePtr transNode = Node::create();
  TransformPtr transCore = Transform::create();
  beginEditCP( transNode );
  transNode->setCore( transCore );
  transNode->addChild( beaconNode );
  endEditCP( transNode );
  cam_trans = transCore;
  
  //OBJECT0: Plane
  objects[0] = makeBox( 3,3,2, 2,2,1 );
  calcFaceNormals( GeometryPtr::dcast(objects[0]->getCore()) );
  normals[0] = calcFaceNormalsGeo( GeometryPtr::dcast(objects[0]->getCore()), 0.5 );
  
  //OBJECT1: Sphere
  objects[1] = makeSphere( 2, 2 );
  calcFaceNormals( GeometryPtr::dcast(objects[1]->getCore()) );
  normals[1] = calcFaceNormalsGeo( GeometryPtr::dcast(objects[1]->getCore()), 0.5 );
  
  //OBJECT2: Cone
  objects[2] = makeConicalFrustum( 1.5, 0.75, 2, 8, true, true, true );
  calcFaceNormals( GeometryPtr::dcast(objects[2]->getCore()) );
  normals[2] = calcFaceNormalsGeo( GeometryPtr::dcast(objects[2]->getCore()), 0.5 );
    
  //OBJECT3: Custom Single Indexed Geometry
  objects[3] = Node::create();
  GeometryPtr obj3Core= Geometry::create();
  GeoIndicesUI32Ptr obj3Index = GeoIndicesUI32::create();
  GeoPositions3f::PtrType obj3Pnts = GeoPositions3f::create();
  GeoColors3f::PtrType obj3Colors = GeoColors3f::create();
  GeoPTypesPtr obj3Types = GeoPTypesUI8::create();
  GeoPLengthsPtr obj3Lengths = GeoPLengthsUI32::create();
 
  beginEditCP( obj3Pnts );
  obj3Pnts->addValue( Pnt3f(0, 0,0) );
  obj3Pnts->addValue( Pnt3f(1,-1,0) );
  obj3Pnts->addValue( Pnt3f(1, 1,0) );
  
  obj3Pnts->addValue( Pnt3f(1, 1,0) );
  obj3Pnts->addValue( Pnt3f(1,-1,0) );
  obj3Pnts->addValue( Pnt3f(3,-1.3,0) );
  obj3Pnts->addValue( Pnt3f(3, 1.3,0) );
  
  obj3Pnts->addValue( Pnt3f(3, 1.3,0) );
  obj3Pnts->addValue( Pnt3f(3,-1.3,0) );
  obj3Pnts->addValue( Pnt3f(4, 0,0) );
  endEditCP( obj3Pnts );
  
  beginEditCP( obj3Types );
  //obj3Types->addValue( GL_TRIANGLES );
  //obj3Types->addValue( GL_QUADS );
  //obj3Types->addValue( GL_TRIANGLES );
  obj3Types->addValue( GL_POLYGON );
  endEditCP( obj3Types );
  
  beginEditCP( obj3Lengths );
  //obj3Lengths->addValue( 3 );
  //obj3Lengths->addValue( 4 );
  //obj3Lengths->addValue( 3 );
  
  obj3Lengths->addValue( 6 );
  endEditCP( obj3Lengths );
   
  beginEditCP( obj3Colors );
  for( UInt32 i=0; i<obj3Pnts->getSize(); ++i )
  {
      obj3Colors->addValue( Color3f(.7,.7,.7) );
  }
  endEditCP( obj3Colors );
  
  beginEditCP( obj3Index );
  //for( UInt32 i=0; i<obj3Pnts->getSize(); ++i )
  //{
  // obj3Index->addValue( i );
  //}
  obj3Index->addValue( 0 );
  obj3Index->addValue( 1 );
  obj3Index->addValue( 5 );
  obj3Index->addValue( 9 );
  obj3Index->addValue( 6 );
  obj3Index->addValue( 2 );
  endEditCP( obj3Index );
  
  beginEditCP( obj3Core );
  obj3Core->setIndices( obj3Index );
  obj3Core->setPositions( obj3Pnts );
  obj3Core->setTypes( obj3Types );
  obj3Core->setLengths( obj3Lengths );
  obj3Core->setColors( obj3Colors );
  endEditCP( obj3Core );
  
  beginEditCP( objects[3] );
  objects[3]->setCore( obj3Core );
  endEditCP( objects[3] );
  calcFaceNormals( GeometryPtr::dcast(objects[3]->getCore()) );
  normals[3] = calcFaceNormalsGeo( GeometryPtr::dcast(objects[3]->getCore()), 0.5 );
    
  //ROOT
  root = Node::create();
  GroupPtr rootCore = Group::create();
  beginEditCP(root);
  root->setCore(rootCore);
  root->addChild(transNode);
  root->addChild(objects[0]);
  root->addChild(normals[0]);
  activeObj = root->findChild( objects[0] );
  activeNorm = root->findChild( normals[0] );
  endEditCP(root);
  
  camera = PerspectiveCamera::create();
  camera->setBeacon( beaconNode );
  camera->setFov( 90 );
  camera->setNear( 0.1 );
  camera->setFar( 10000 );
  
  SolidBackgroundPtr background = SolidBackground::create();
  
  viewp = Viewport::create();
  viewp->setCamera( camera );
  viewp->setBackground( background );
  viewp->setRoot( root );
  viewp->setSize( 0,0, 1,1 );
  
  GLint glVP[4];
  glGetIntegerv( GL_VIEWPORT, glVP );
  
  GLUTWindowPtr gwin = GLUTWindow::create();
  gwin->setId(winID);
  gwin->setSize(glVP[2], glVP[3]);
  
  window = gwin;
  window->addPort( viewp );
  window->init();
  
  drAct = DrawAction::create();
  
  Vec3f pos( 0, 0, 3 );
  tball.setMode( Trackball::OSGObject );
  tball.setStartPosition( pos, true );
  tball.setSum( true );
  tball.setTranslationMode( Trackball::OSGFree );
  
  glutMainLoop();
  return 0;
}





