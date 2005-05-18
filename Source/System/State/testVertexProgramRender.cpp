#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGSimpleMaterial.h>
#include <OSGChunkMaterial.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGVertexProgramChunk.h>
#include <OSGFragmentProgramChunk.h>

OSG_USING_NAMESPACE

// some globals
SimpleSceneManager *mgr;

VertexProgramChunkPtr vp;
FragmentProgramChunkPtr fp;
ChunkMaterialPtr chMat;


// redraw the window
void display(void)
{      
    // render
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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

// react to keys
void keyboard(unsigned char k, int, int)
{
	static Real32 scale=0, lod=0;
    switch(k)
    {
	case '+':
		scale += 0.25;
		beginEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		  vp->setParameter("scale", Vec4f(0.5+scale,1,1,0));
		endEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		break;
	case '-':
		scale -= 0.25;
		beginEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		  vp->setParameter("scale", Vec4f(0.5+scale,1,1,0));
		endEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		break;
	case ',':
		lod += 1;
		beginEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		  vp->setParameter("lod", Vec4f(1+lod,1,0,0));
		endEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		break;
	case '.':
		lod -= 1;
		beginEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		  vp->setParameter("lod", Vec4f(1+lod,1,0,0));
		endEditCP(vp, ProgramChunk::ParamValuesFieldMask);
		break;
	case 27: 
		exit(1);
	default:
		printf("Use [+|-] to scale, [,|.] for lod.\n");
		break;
    }
}

int main(int argc, char **argv)
{
    osgInit(argc, argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();

    // create the shader program chunks
    vp = VertexProgramChunk::create();
    fp = FragmentProgramChunk::create();
    
    beginEditCP(vp);
		vp->read("simple.vp");
		vp->addParameter("scale", 0, Vec4f(0.5,1,1,0));
		vp->addParameter("lod", 1, Vec4f(1,1,0,0));
    endEditCP(vp);

	beginEditCP(fp);
		fp->read("simple.fp");
    endEditCP(fp);
    
    // create the two textures
    TextureChunkPtr tx1 = TextureChunk::create();
    TextureChunkPtr tx2 = TextureChunk::create(); 
          
    ImagePtr pImg1 = Image::create();
    ImagePtr pImg2 = Image::create();

	char *iHeight = "OpenSGLogo_height.png",
		 *iColor  = "OpenSGLogo.png";

	if (argc >= 3)
	{
		iHeight = argv[1];
		iColor  = argv[2];
	}
	else
	{
		FNOTICE(("Usage %s Displacementmap Colormap\n", argv[0]));
	}
    
	pImg1->read(iHeight);
	pImg1->reformat(Image::OSG_L_PF);

    pImg2->read(iColor);
    
    beginEditCP(tx1);
        tx1->setImage(pImg1);
        tx1->setInternalFormat(GL_LUMINANCE32F_ARB);
        tx1->setMinFilter(GL_NEAREST_MIPMAP_NEAREST);
        tx1->setMagFilter(GL_NEAREST);
    endEditCP(tx1);
   
    beginEditCP(tx2);
        tx2->setImage(pImg2);
        tx2->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
        tx2->setMagFilter(GL_LINEAR);
    endEditCP(tx2);
    
    // create the material
    chMat = ChunkMaterial::create();
    beginEditCP(chMat);
	{
		chMat->addChunk(tx2);
		chMat->addChunk(tx1);
		chMat->addChunk(vp);
		chMat->addChunk(fp);
	}
    endEditCP(chMat);
    
	// create scene
    NodePtr scene = makePlane( 4, 4, 64, 64);
    GeometryPtr geoPtr = osg::GeometryPtr::dcast(scene->getCore());
    geoPtr->setMaterial(chMat);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);

    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // show the whole scene
    mgr->showAll();
    mgr->redraw();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
