/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

// Minimalistic OpenSG program

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>


#include <OSGSceneFileHandler.h>
#include <OSGGeoFunctions.h>
#include <OSGPointLight.h>
#include <OSGTransform.h>
#include <OSGTiledTerrain.h>
#include <OSGImageFileHandler.h>
#include <OSGTextureChunk.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

NodePtr scene;
TiledTerrainPtr terrain;

Real32 speed = 1.;

static UInt32 frame = 0;
// Standard GLUT callback functions
void display( void )
{
    mgr->idle();
    mgr->redraw();
    //SLOG << "frametime=" << mgr->getWindow()->getPort(0)->getDrawTime() << " ms" << std::endl;

    if (terrain->getUpdateTerrain()) {
       beginEditCP(terrain, TiledTerrain::UpdateTerrainFieldMask);
       terrain->setUpdateTerrain(false);
       endEditCP(terrain, TiledTerrain::UpdateTerrainFieldMask);
    }
}

void idle( void )
{
   if (frame%10 == 0) {
     frame = 0;
     beginEditCP(terrain, TiledTerrain::UpdateTerrainFieldMask);
     terrain->setUpdateTerrain(true);
     endEditCP(terrain, TiledTerrain::UpdateTerrainFieldMask);
   } else {
     ++frame;
   }
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

void
key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:    exit(1);
    case 'a':   mgr->setHighlight( scene );
                break;
    case 's':   mgr->setHighlight( NullFC );
                break;
    case ' ': {
      GLint current = GL_LINE;
      glGetIntegerv(GL_POLYGON_MODE, &current);
      if (current == GL_FILL) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      } else {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      break;
    }
    case 'l':   mgr->useOpenSGLogo();
                break;
    case 'f':   mgr->setNavigationMode(Navigator::FLY);
                break;
    case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
                break;
    case 'w':   mgr->setNavigationMode(Navigator::WALK);
                break;                
    case 'u': {
      beginEditCP(terrain, TiledTerrain::UpdateFieldMask);
      terrain->setUpdate(!terrain->getUpdate());
      endEditCP(terrain, TiledTerrain::UpdateFieldMask);
      SLOG << "update tiling " << (terrain->getUpdate() ? "on" : "off") << std::endl;
      break;
    }
    case 'x': {
      beginEditCP(terrain, TiledTerrain::GeoMorphingFieldMask);
      terrain->setGeoMorphing(!terrain->getGeoMorphing());
      SLOG << "geomorphing " << (terrain->getGeoMorphing() ? "on" : "off") << std::endl;
      endEditCP(terrain, TiledTerrain::GeoMorphingFieldMask);
      break;
    }
    case 'v':   speed *= .9;
                FLOG(("Speed set to %f\n", speed ));
                mgr->getNavigator()->setMotionFactor(speed);
                break;
    case 'b':   speed *= 1.1;
                FLOG(("Speed set to %f\n", speed ));
                mgr->getNavigator()->setMotionFactor(speed);
                break;
    }
    mgr->key(key,x,y);
    glutPostRedisplay();
}

MaterialPtr makeTexture (const char* texname)
{
   ImagePtr image = ImageFileHandler::the().read(texname);

   SLOG << "Create ChunkMaterial" << std::endl;
   ChunkMaterialPtr  texMatPtr     = ChunkMaterial::create();
   TextureChunkPtr   texChunkPtr   = TextureChunk::create();
   BlendChunkPtr     blendChunkPtr = BlendChunk::create();
   MaterialChunkPtr  phongChunk = MaterialChunk::create();
   beginEditCP(phongChunk);
   {
     phongChunk->setDiffuse (Color4f(1.0f, 1.0f, 1.0f, 1.0f));
     phongChunk->setAmbient (Color4f(0.1f, 0.1f, 0.1f, 1.0f));
     phongChunk->setSpecular(Color4f(0.2f, 0.2f, 0.2f, 1.0f));
     phongChunk->setShininess(6);
   }
   endEditCP  (phongChunk);
   beginEditCP (texChunkPtr);
   {
      texChunkPtr->setImage     ( image);
      
      texChunkPtr->setWrapS     ( GL_CLAMP );
      texChunkPtr->setWrapT     ( GL_CLAMP );
      texChunkPtr->setWrapR     ( GL_CLAMP );
      
      texChunkPtr->setMinFilter ( GL_LINEAR );
      texChunkPtr->setMagFilter ( GL_LINEAR );
      texChunkPtr->setEnvMode(GL_MODULATE);
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
     texMatPtr->addChunk(texChunkPtr, 0);
     texMatPtr->addChunk(phongChunk);
     //texMatPtr->addChunk(blendChunkPtr);
   }
   endEditCP   (texMatPtr);
   return texMatPtr;
}


// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    // VERY IMPORTANT: artifacts if not ignoring GL_EXT_compiled_vertex_array
    Window::ignoreExtensions("GL_EXT_compiled_vertex_array");

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // create the scene
    terrain = TiledTerrain::create();
    scene = Node::create();
    beginEditCP(scene);
    scene->setCore(terrain);
    endEditCP  (scene);
    beginEditCP(terrain);//, ~(TiledTerrain::MaterialFieldMask | TiledTerrain::PerPixelLightingFieldMask));
    for (Int32 i=2; i>=0; --i) {
      for (UInt32 j=0; j<6; ++j) {
	char filename[255];
	sprintf(filename, "HeightMap_%03d_%03d.png", j+1, i+1);
	SINFO << "load " << filename << std::endl;
	ImagePtr    height = ImageFileHandler::the().read(filename);
	terrain->getMFHeightTiles()->push_back(height);
      }
    }
    terrain->setVertexSpacing(50.0f/128.0f);
    terrain->setDetail(10.0f);
    terrain->setHeightScale  (10.0f);
    terrain->setGeoMorphing(true);
    terrain->setSizeROI(2);
    terrain->setSizeX(6);
    terrain->setSizeY(3); 
    //endEditCP  (terrain, ~(TiledTerrain::MaterialFieldMask | TiledTerrain::PerPixelLightingFieldMask));
    //beginEditCP(terrain, TiledTerrain::MaterialFieldMask | TiledTerrain::PerPixelLightingFieldMask);
    MaterialPtr mat = makeTexture("WorldMap.png");
    terrain->setMaterial(mat);
//    terrain->setPerPixelLighting(true); 
    terrain->setPerPixelLighting(false); 
    endEditCP  (terrain); //, TiledTerrain::MaterialFieldMask | TiledTerrain::PerPixelLightingFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );
    mgr->getAction()->setFrustumCulling(false);

    WalkNavigator *walker=mgr->getNavigator()->getWalkNavigator();
    walker->setGroundDistance(1);
    walker->setPersonDimensions(3,1,1);

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
