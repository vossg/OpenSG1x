#include <GL/glut.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGForeground.h>
#include <OpenSG/OSGFileGrabForeground.h>
#include <OpenSG/OSGStateChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

// --------------------
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Tools/Kernel_OSG/TriMesh_OSGArrayKernelT.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModNormalFlippingT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

#include <map>
#include <iostream>
#include <string>

using namespace std;


/*---------------------------------------------------------------*\
    globals
\*---------------------------------------------------------------*/


// -------------------------------------------------------------- OpenMesh ----

struct MeshTraits : public OpenMesh::Kernel_OSG::Traits
{
  VertexAttributes  ( OpenMesh::Attributes::Normal       );
  FaceAttributes    ( OpenMesh::Attributes::Normal       );  
};

OM_Merge_Traits( MeshTraits, 
		 OpenMesh::Decimater::DefaultTraits,
		 MyTraits );

typedef OpenMesh::Kernel_OSG::TriMesh_OSGArrayKernelT<MyTraits> mesh_t;
typedef OpenMesh::Decimater::DecimaterT<mesh_t>                 Decimater;
typedef OpenMesh::Decimater::ModQuadricT< Decimater >           ModQuadric;
typedef OpenMesh::Decimater::ModNormalFlippingT< Decimater >    ModNF;

#if defined(__GNUC__) &&  __GNUC__ >= 3
typedef std::auto_ptr<mesh_t>     MeshObj;
typedef std::auto_ptr<Decimater>  DecimaterObj;
typedef std::auto_ptr<ModQuadric> ModQuadricObj;
typedef std::auto_ptr<ModNF>      ModNFObj;
#else
typedef mesh_t*     MeshObj;
typedef Decimater*  DecimaterObj;
typedef ModQuadric* ModQuadricObj;
typedef ModNF*      ModNFObj;
#endif

// ----------------------------------------------------------------------------

typedef struct
{
  SimpleSceneManager* mgr;
  bool                flag_initSpecial;
  float               motionFactor;
  GeometryPtr         geocore;
  unsigned long       mode;

  GeometryPtr         meshGeoPtr;
  MeshObj             mesh;
  DecimaterObj        decimater;
  ModQuadricObj       modQuadric;
  ModNFObj            modNF;

} Globals;


enum
{
  STATISTIC= 0x0001,
  FLYMODE=   0x0002,
  LOGO=      0x0008,
};

typedef enum
{
  GEOCORE= 1,
  MGROUPCORE= 2,
} CoreMode;

typedef enum
{
  SIMPLEMATERIAL= 1,
  CHUNKMATERIAL= 2,
} MaterialMode;


typedef struct SaveChunk_
{
  NodePtr      node;
  NodeCorePtr  core;
  CoreMode     coremode;
  MaterialPtr  material;
  MaterialMode materialmode;

  SaveChunk_() : node(NullFC), core(NullFC), material(NullFC) { };
} SaveChunk;

typedef std::map<NodePtr, SaveChunk> SaveChunkMap;
typedef SaveChunkMap::iterator       SaveChunkMapIterator;



static Globals g= { NULL, false, 1.0f, NullFC, 0 };

// // stores for all blended nodeptrs the core and the old material
// static SaveChunkMap          BlendContainer;
// typedef SaveChunkMapIterator BlendIterator;

static NodePtr           lastHighlightParent= NullFC;
static NodePtr           lastHighlightNode=   NullFC;

static NodePtr           lastBlendNode= NullFC;
static MaterialPtr       lastBlendMaterial= NullFC;

static NodePtr           highlightNode= NullFC;

static PolygonChunkPtr   polychunk= NullFC;


// ----------------------------------------------------------------------------

int setupHighLight ( NodePtr& parent, NodePtr& node )
{
  lastHighlightParent= parent;
  lastHighlightNode= node;

  beginEditCP(highlightNode);
    highlightNode->addChild(node);
  endEditCP(highlightNode);

  beginEditCP(parent);
    parent->addChild(highlightNode);
  endEditCP(parent);

  return 1;
}

int cleanUpHighLight ( void )
{
  if ( lastHighlightParent == NullFC )
    return 1;

  // highlight abtrennen
  beginEditCP(lastHighlightParent);
    lastHighlightParent->subChild(highlightNode);
  endEditCP(lastHighlightParent);

  beginEditCP(highlightNode);
    highlightNode->subChild(lastHighlightNode);
  endEditCP(highlightNode);

  lastHighlightParent= NullFC;
  lastHighlightNode= NullFC;

  return 1;
}


// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
  // OSG init
  osgInit(argc,argv);

  // GLUT init
  int winid = setupGLUT(&argc, argv);

  // the connection between GLUT and OpenSG
  GLUTWindowPtr gwin= GLUTWindow::create();
  gwin->setId(winid);
  gwin->init();

  // load the scene

  NodePtr scene= Node::create();
  beginEditCP(scene);
    scene->setCore(Group::create());
  endEditCP(scene);

  NodePtr data= NullFC;

  if(argc < 2)
  {
      FWARNING(("No file given!\n"));
      return 1;   
  }
  else
  {
    g.mesh       = MeshObj(new mesh_t);

    OpenMesh::IO::Options opt;

    if (OpenMesh::IO::read_mesh( *g.mesh, argv[1], opt ))
    {
      g.mesh->update_face_normals();
      if ( !opt.check( OpenMesh::IO::Options::VertexNormal ) )
      {
	g.mesh->update_vertex_normals();
      }

      // ---------------------------------------- prepare decimater
      std::cout << "prepare decimater\n" << std::endl;
      g.decimater  = DecimaterObj (new Decimater ( *(g.mesh) ));
      g.modQuadric = ModQuadricObj(new ModQuadric( *(g.decimater) ));
      g.modNF      = ModNFObj     (new ModNF     ( *(g.decimater) ));
      g.decimater->initialize();

      // ---------------------------------------- osg geometry core
      std::cout << "create GeometryPtr\n" << std::endl;
      g.meshGeoPtr = g.mesh->createGeometryPtr();

      beginEditCP(g.meshGeoPtr, Geometry::MaterialFieldMask  );
      {
	g.meshGeoPtr->setMaterial (getDefaultMaterial());   
      }
      endEditCP  (g.meshGeoPtr, Geometry::MaterialFieldMask  );
      
      osg::NodePtr geoNode = Node::create();
      beginEditCP(geoNode);
      geoNode->setCore(g.meshGeoPtr);
      endEditCP(geoNode);

      beginEditCP(scene);
      scene->addChild(geoNode);
      endEditCP(scene);
    }
    else
    {
      cerr << "Cannot load file '" << argv[1] << "'\n";
      return 1;
    }
  }

    
    // nice looking material
  MaterialChunkPtr hlmatchunk= MaterialChunk::create();
  hlmatchunk->setLit(GL_TRUE);  

  polychunk= PolygonChunk::create();
  {
    polychunk->setOffsetFactor(-0.002f);
    polychunk->setOffsetLine(GL_TRUE);
    polychunk->setFrontMode(GL_LINE);
    polychunk->setBackMode(GL_LINE);
    polychunk->setSmooth(GL_TRUE);
  }
  
  ChunkMaterialPtr hlmat= ChunkMaterial::create();
  
  beginEditCP(hlmat);
  {
    hlmat->addChunk(hlmatchunk);
    hlmat->addChunk(polychunk);
  }
  endEditCP(hlmat);
  
  MaterialGroupPtr mgroup= MaterialGroup::create();
  beginEditCP(mgroup);
    mgroup->setMaterial(hlmat);
  endEditCP(mgroup);
  
  highlightNode= Node::create();
  beginEditCP(highlightNode);
    highlightNode->setCore(mgroup);
  endEditCP(highlightNode);
  
  addRefCP(highlightNode);
      
  // create the SimpleSceneManager helper
  g.mgr = new SimpleSceneManager;
  
  // tell the manager what to manage
  g.mgr->setWindow(gwin );
  g.mgr->setRoot  (scene);
  
  // show the whole scene
  g.mgr->showAll();
  
  // GLUT main loop
  glutMainLoop();
  
  return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    g.mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    g.mgr->resize(w, h);
    glutPostRedisplay();
}

void idle( void )
{
  g.mgr->idle();
  glutPostRedisplay(); 
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
    {
      g.mgr->mouseButtonRelease(button, x, y);
      if ( g.mode & FLYMODE )
      {
        glutIdleFunc(NULL); 
      }
    }
    else
    {
      g.mgr->mouseButtonPress(button, x, y);
      if ( g.mode & FLYMODE )
      {
        glutIdleFunc(idle); 
      }
    }
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    g.mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 27:
      exit(1);
      break;
    
    case 's':
    {
      ( g.mode & STATISTIC ) ? g.mode&= ~STATISTIC : g.mode|= STATISTIC;
      g.mgr->setStatistics(g.mode & STATISTIC);
      glutPostRedisplay();
    }
    break;
    
    case 'l':
      g.mgr->useOpenSGLogo();
      glutPostRedisplay();
      break;
      
    case 'r':  
      g.mgr->showAll();
      glutPostRedisplay();
      break;
      
    case 'p':
    {
      Line l;
      
      l= g.mgr->calcViewRay(x, y);
      
      IntersectAction *act = IntersectAction::create();
      
      act->setLine(l);
      act->apply(g.mgr->getRoot());
	
      // did we hit something?
      if (act->didHit())
      {
	char*   nodeName;
	NodePtr hitNode= act->getHitObject();
	NodePtr twNode= hitNode;
	  
	g.mgr->setHighlight(hitNode);
          
	for ( nodeName= const_cast<char*>(OSG::getName(twNode));
	      twNode != g.mgr->getRoot();
	      twNode = twNode->getParent(), 
		nodeName = const_cast<char*>(OSG::getName(twNode))
              )
	{
	  if ( nodeName )
	  {
	    cerr << " hit : " << nodeName << endl;
              
	    break;
	  }
	}
          
	if ( lastHighlightNode.getCPtr() != hitNode.getCPtr() )
	{
	  NodePtr clone= cloneTree(hitNode);
	  cleanUpHighLight();  
	  setupHighLight(twNode, clone);
	}                   
          
      }
      else
      {
	g.mgr->setHighlight(NullFC);
	cleanUpHighLight();
      }
    }
    glutPostRedisplay();
    break;      
                
    case '?':
      cout << endl;      
      cout << " keys :" << endl;
      cout << "  ?  help" << endl;
      cout << "  s  statistics" << endl;
      cout << "  l  logo" << endl;
      cout << "  r  reset" << endl;
      cout << "  p  pick" << endl;
      cout << "  d  do a decimation step" << endl;
      cout << "  M  openmesh stats" << endl;
      cout << "  S  save current mesh to 'result.off'" << endl;
      cout << endl;
      break;

    case 'd':
    {      
      int rc;
      beginEditCP( g.meshGeoPtr );
      if ( (rc=g.decimater->decimate(100)) )
      {
	g.decimater->mesh().garbage_collection();
      }
      std::cout << rc << " vertices removed!" << std::endl;
      endEditCP( g.meshGeoPtr );
      glutPostRedisplay();
    }
    break;

    case 'M':
    {
      std::cout << "# Vertices: " << g.mesh->n_vertices() << std::endl;
      std::cout << "# Edges   : " << g.mesh->n_edges() << std::endl;
      std::cout << "# Faces   : " << g.mesh->n_faces() << std::endl;
    }
    break;

    case 'S':
    {
      OpenMesh::IO::Options opt;

      opt += OpenMesh::IO::Options::Binary;

      if (OpenMesh::IO::write_mesh( *g.mesh, "result.off", opt ))
	std::cout << "mesh saved in 'result.off'\n";
    }
    break;

    case '-':
    {
      glutPostRedisplay();
    }
    break;
     
    case '+':
    {
      glutPostRedisplay();
    }
    break;
  }  
  return;    
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenMesh within OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    
    glEnable(GL_BLEND);
    
    return winid;
}
