/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleMaterial.h>
#include <OSGChunkMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGBlendChunk.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>
#include <OSGSceneFileHandler.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#include "OSGOSGWriter.h"

#include "OSGImage.h"
#include "OSGSlices.h"

//#include "OSGUniformBackground.h"

#include "OSGTrackball.h"
#include "OSGNavigator.h"


/**---added stuff------------------------------------------------------------------*/

/**---end of added stuff-----------------------------------------------------------*/

using namespace OSG;

DrawAction * ract;

NodePtr  root;
Vec3f   size;

PerspectiveCameraPtr cam;
ViewportPtr vp;
WindowPtr win;

SlicesPtr slicesCore;
TransformPtr cam_trans;
float sliceDistance = 1;

BlendChunkPtr blendChunkPtr;

Navigator navigator;

int mouseb = 0;
int lastx=0, lasty=0;

bool cullFace = true;
bool buttonPressed;

void
display(void)
{
    Matrix m1, m2, m3;

    if ( buttonPressed ) navigator.moveTo(lastx,lasty);

    m1=navigator.getMatrix();
//    m1.transpose();

//    m2.setTranslate(0,0,8);
//    m1.mult(m2);

    cam_trans->getSFMatrix()->setValue( m1 );

    win->draw( ract );
}

void reshape( int w, int h )
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void
animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void
motion(int x, int y)
{
/*  Real32 w = win->getWidth(), h = win->getHeight();


    Real32  a = 2. * ( lastx / w - .5 ),
                b = 2. * ( .5 - lasty / h ),
                c = 2. * ( x / w - .5 ),
                d = 2. * ( .5 - y / h );

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
    }*/
    lastx = x;
    lasty = y;

    if ( buttonPressed ) navigator.moveTo(x,y);


}

void
mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  navigator.buttonPress(Navigator::LEFT_MOUSE,x,y);
                                break;
        case GLUT_MIDDLE_BUTTON:navigator.buttonPress(Navigator::MIDDLE_MOUSE,x,y);
                                break;
        case GLUT_RIGHT_BUTTON: navigator.buttonPress(Navigator::RIGHT_MOUSE,x,y);
                                break;
        case 3:
          navigator.buttonPress(Navigator::UP_MOUSE,x,y);
          break;
        case 4:
          navigator.buttonPress(Navigator::DOWN_MOUSE,x,y);
          break;
        }
        mouseb |= 1 << button;
        buttonPressed=true;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  navigator.buttonRelease(Navigator::LEFT_MOUSE,x,y);
                                break;
        case GLUT_MIDDLE_BUTTON:navigator.buttonRelease(Navigator::MIDDLE_MOUSE,x,y);
                                break;
        case GLUT_RIGHT_BUTTON: navigator.buttonRelease(Navigator::RIGHT_MOUSE,x,y);
                                break;
        }
        mouseb &= ~(1 << button);
        buttonPressed=false;
    }
    lastx = x;
    lasty = y;
}

void
vis(int visible)
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

void key(unsigned char key, int x, int y)
{
  switch ( key )
    {
    case 27:    osgExit(); exit(0);      
    case 'b':
      cullFace = !cullFace;
      if (cullFace)
        glEnable(GL_CULL_FACE);
      else
        glDisable(GL_CULL_FACE);
      std::cout << "cullFace: " << cullFace << std::endl;
      break;
    case 's':      
    case 'S':
      {
        float f = (key == 's') ? 0.9 : 1.1;
        sliceDistance *= f;
        beginEditCP(slicesCore);
        {
          slicesCore->setSliceDistance(sliceDistance);
        }
        endEditCP(slicesCore);
        std::cout << "sliceDistance: " << sliceDistance << std::endl;
        std::cout << "obj size:      " << size.x() << "x" 
		                       << size.y() << "x" 
				       << size.z() << std::endl;
      }
      break;
    case 'q':     
                beginEditCP(slicesCore);
                {
                  Real32 s = size.length();
                  slicesCore->setSize(Vec3f(s,s,s));
                }
                endEditCP(slicesCore);

                break;                  
    case 'w':     
                beginEditCP(slicesCore);
                {
                  slicesCore->setSize(size);
                }
                endEditCP(slicesCore);

                break;                  
    case 'p':   {
                SceneFileHandler::the().write(root,"test.osb" );
                std::cerr << "File dumped." << std::endl;
                }
                break;                  
    case 'a':   // Additive blending
                if(blendChunkPtr->getDestFactor() == GL_ONE_MINUS_SRC_ALPHA)
                {
                    beginEditCP (blendChunkPtr);
                    {
                      blendChunkPtr->setSrcFactor  ( GL_SRC_ALPHA           );
                      blendChunkPtr->setDestFactor ( GL_ONE );
                    }
                    endEditCP   (blendChunkPtr);
                }
                else
                {
                    beginEditCP (blendChunkPtr);
                    {
                      blendChunkPtr->setSrcFactor  ( GL_SRC_ALPHA           );
                      blendChunkPtr->setDestFactor ( GL_ONE_MINUS_SRC_ALPHA );
                    }
                    endEditCP   (blendChunkPtr);
                }
                break;                
    case 'L':   glDisable( GL_LIGHTING );
      std::cerr << "Lighting disabled." << std::endl;
      break;
    case 'l':   glEnable( GL_LIGHTING );
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
    case 'r':   std::cerr << "Sending ray through " << x << "," << y << std::endl;
    {
      Line l;
      cam->calcViewRay( l, x, y, *vp );
      std::cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << std::endl;
    }
      break;
    case 'd':
        if(SceneFileHandler::the().write(root, "volume.osb", true))
            std::cerr << "Wrote volume.osb" << std::endl;
        break;
    }
}


int main (int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutIdleFunc(display);

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // OSG

    // create the graph

    // beacon for camera and light
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);

    // transformation
    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    endEditCP(t1n);

    cam_trans = t1;

    // light

    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();

    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);

    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    endEditCP(dl);

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    endEditCP(root);

    // create the slice node
    
    slicesCore = Slices::create();

    NodePtr slicesNode = Node::create();
    beginEditCP(slicesNode);
    slicesNode->setCore(slicesCore);
    endEditCP(slicesNode);

    ImagePtr imageP = NullFC;

    if (argc > 1) 
      {
          imageP = Image::create();
        if (imageP->read(argv[1]))
          {
            if (imageP->getFrameCount() > 1) 
              imageP->flipDepthFrameData();
            size.setValues( imageP->getWidth(), 
                            imageP->getHeight(), 
                            imageP->getDepth() );
            imageP->dump();
            imageP->scaleNextPower2();
            if (imageP->hasAlphaChannel() == false) {
              switch (imageP->getPixelFormat()) {
              case Image::OSG_L_PF:
                imageP->reformat(Image::OSG_LA_PF);
                break;
              case Image::OSG_RGB_PF:
                imageP->reformat(Image::OSG_RGBA_PF);
                break;
              default:
                std::cerr << "Can not reformat image\n" << std::endl;
                break;
              }
            }
            imageP->dump();
          }
        else
          {
            FWARNING(("Couldn't load file %s!\n", argv[1]));
            return -1;
          }
      }
    
    
    if(imageP == NullFC)
      {
        imageP = Image::create();
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
        
        size.setValues( imageP->getWidth(), 
                        imageP->getHeight(), 
                        imageP->getDepth() );        
     }

    MaterialPtr matPtr;
    
    if (imageP!=NullFC) 
      {
        std::cout << "Create ChunkMaterial" << std::endl;
        ChunkMaterialPtr  texMatPtr     = ChunkMaterial::create();
        TextureChunkPtr   texChunkPtr   = TextureChunk::create();
        
        blendChunkPtr = BlendChunk::create();
        beginEditCP (texChunkPtr);
        {
          texChunkPtr->setImage     ( imageP);

          texChunkPtr->setWrapS     ( GL_CLAMP );
          texChunkPtr->setWrapT     ( GL_CLAMP );
          texChunkPtr->setWrapR     ( GL_CLAMP );

          texChunkPtr->setMinFilter ( GL_LINEAR );
          texChunkPtr->setMagFilter ( GL_LINEAR );
          //texChunkPtr->setMinFilter ( GL_NEAREST );
          //texChunkPtr->setMagFilter ( GL_NEAREST );
        }
        endEditCP   (texChunkPtr);
        beginEditCP (blendChunkPtr);
        {
          blendChunkPtr->setSrcFactor  ( GL_SRC_ALPHA           );
          blendChunkPtr->setDestFactor ( GL_ONE_MINUS_SRC_ALPHA );
        }
        endEditCP   (blendChunkPtr);
        beginEditCP (texMatPtr);
        {
          texMatPtr->addChunk(texChunkPtr);
          texMatPtr->addChunk(blendChunkPtr);
        }
        endEditCP   (texMatPtr);
        matPtr = texMatPtr;
        sliceDistance = size.length() / 3;
        size.normalize();
      }
    else 
      {
        std::cout << "Create SimpleMaterial" << std::endl;
        SimpleMaterialPtr colMatPtr = SimpleMaterial::create();
        beginEditCP (colMatPtr);
        {
          colMatPtr->setDiffuse( Color3f( 1,0,0 ) );
          colMatPtr->setAmbient( Color3f( 1,0,0 ) );
          colMatPtr->setSpecular( Color3f( 1,1,1 ) );
          colMatPtr->setShininess( 10 );
        }
        endEditCP   (colMatPtr);
        matPtr = colMatPtr;
        size.setValues(1,1,1);
        sliceDistance = 1;
      }
    
    sliceDistance = size.length() / 100;
    std::cout << "size:          " << size << std::endl;
    std::cout << "sliceDistance: " << sliceDistance << std::endl;
    
    beginEditCP(slicesCore);
    {
      slicesCore->setMaterial       (matPtr);
      slicesCore->setSize           (size);
      slicesCore->setSliceDistance  (sliceDistance);
    }
    endEditCP(slicesCore);
    
    slicesNode->updateVolume();
    
    Vec3f min,max;
    slicesNode->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;
    
    beginEditCP(dlight);
    dlight->addChild( slicesNode );
    endEditCP(dlight);

    // Camera

    cam = PerspectiveCamera::create();
    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 45 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

    // Viewport

    vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    glCullFace (GL_BACK);

    gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

    win->init();

    // Action

    ract = DrawAction::create();

    // tball

    // navigation speed
    Vec3f dim(max - min);

    std::cout << "dim: " << dim.length() << std::endl;
    navigator.set( Pnt3f ( dim.length() * 2, 0, 0),
                   Pnt3f ( 0,0,0),
                   Vec3f ( 0,1,0) );
    navigator.setMotionFactor ( dim.length() * 0.1 );
    navigator.setMode(Navigator::TRACKBALL);

    navigator.setViewport(vp);

    // run...

    glutMainLoop();

    return 0;
}

