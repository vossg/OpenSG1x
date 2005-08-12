
#include <algorithm>
#include <string.h>
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGTime.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGComponentTransform.h>

#include <OSGSimpleTexturedMaterial.h>
#include <OSGBlendChunk.h>
#include <OSGImage.h>
#include <OSGParticles.h>
#include <OSGRefPtr.h>

#include <OSGParticleBSP.h>

//#include <iostream.h>
//#include <OSGWriter.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );

Vec3f *velocities;
RefPtr<ParticlesPtr> particles;
RefPtr<GeoPositions3fPtr> pnts,secpnts;
MFInt32 *indices;
UInt32 numParticles;

bool doMotion=true;
bool doIndices=false;
bool runBench=false;
bool testSet=false;


#ifdef __sgi
#include <sys/fpu.h>
#include <signal.h>

void sighand(int sig)
{
    printf("caught signal %x\n", sig);
    
    
}

int matherr(struct math_exception *x)
{
	char sterr[50];
	int argc=1;
	
	switch (x->type)
	{
	case DOMAIN:	strcpy(sterr, "domain error");
					break;
	case SING:		strcpy(sterr, "singularity");
					break;
	case OVERFLOW:	strcpy(sterr, "overflow");
					break;
	case UNDERFLOW:	strcpy(sterr, "underflow");
					break;
	case TLOSS:		strcpy(sterr, "total loss of significance");
					break;
	case PLOSS:		strcpy(sterr, "partial loss of significance");
					break;					
	}
	
	if (!strcmp(x->name, "atan2") || !strcmp(x->name, "atan2f") || 
		!strcmp(x->name, "pow"  ) || !strcmp(x->name, "powf") || 
		!strcmp(x->name, "modff") || !strcmp(x->name, "modf") || 
		!strcmp(x->name, "atan2") || !strcmp(x->name, "ldexp"))
		argc=2;
	
	if (argc==1)
		fprintf(stderr, "%s in %s(%lf), res %lf\n", sterr, x->name, 
				x->arg1, x->retval);
	else
		fprintf(stderr, "%s in %s(%lf, %lf), res %lf\n", sterr, x->name, 
				x->arg1, x->arg2, x->retval);

	return(1);
}

void enableFPE(void)
{
	union fpc_csr csr;
	
	csr.fc_word = get_fpc_csr();

	csr.fc_struct.en_divide0 = 
	csr.fc_struct.en_overflow = 
	csr.fc_struct.en_underflow = 1;

	csr.fc_struct.se_divide0 = 0;

	fprintf(stderr, "Enabling floating point exceptions.\n");

	set_fpc_csr( csr.fc_word );		
}
#else
void enableFPE(void)
{
}
#endif

int main(int argc, char **argv)
{
//    enableFPE();

#ifdef __sgi 	
	signal(SIGSEGV, (void (*)(int))sighand);
	signal(SIGTRAP, (void (*)(int))sighand);
	signal(SIGBUS, (void (*)(int))sighand);
#endif
   
    // OSG init
    osgInit(argc,argv);

    if (argc > 1 && ! strcmp(argv[1],"-bench"))
    {
        runBench = true;
        argc--;
        argv++;
        glutInitWindowPosition(0,0);
        glutInitWindowSize(600,600);
    }

    if (argc > 1 && ! strcmp(argv[1],"-test"))
    {
        testSet = true;
        doMotion = false;
        argc--;
        argv++;
    }

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
    NodePtr scene = Node::create();    
    NodePtr pnode = Node::create();
    
    ComponentTransformPtr trans = ComponentTransform::create();
    beginEditCP(scene);
    scene->setCore(trans);
    scene->addChild(pnode);
    endEditCP(scene);
    
    beginEditCP(trans);
    trans->setTranslation(Vec3f(2,0,0));
    trans->setRotation(Quaternion(Vec3f(0,1,0),Pi/2));
    trans->setScale(Vec3f(2,2,2));
    endEditCP(trans);
    
    
    particles = Particles::create();
    beginEditCP(pnode);
    pnode->setCore(particles);
    endEditCP(pnode);

    numParticles = 100;
    
    if (argc > 1)
    {
        numParticles=atoi(argv[1]);
    }
    
    beginEditCP(particles);

    pnts=GeoPositions3f::create();
    secpnts=GeoPositions3f::create();
    GeoColors3fPtr  cols  = GeoColors3f::create();
    GeoNormals3fPtr norms = GeoNormals3f::create();

    MFPnt3f* p=pnts->getFieldPtr();
    MFPnt3f* sp=secpnts->getFieldPtr();
    MFVec3f *size=particles->getMFSizes();

    indices = particles->getMFIndices();
    
    velocities=new Vec3f [numParticles];
    
    beginEditCP(pnts);
    beginEditCP(secpnts);
    beginEditCP(cols);
    if(!testSet)
    {
        for(UInt32 i=0; i < numParticles; ++i)
        {
            Pnt3f pnt(osgrand(),osgrand(),osgrand());
            indices->push_back(i);  
            p->push_back(pnt);  
            sp->push_back(pnt);  
            velocities[i].setValues(osgrand()/30.f/2, osgrand()/30.f/2, osgrand()/30.f/2);
            cols->getFieldPtr()->push_back( 
                Color3f(osgrand()/2.f + .5f,osgrand()/2.f + .5f,osgrand()/2.f + .5f) );
            size->push_back(
                Vec3f(osgrand()/20.f+0.05,osgrand()/20.f+0.05,osgrand()/20.f+0.05));
            particles->getTextureZs().push_back(osgrand());
        }
    }
    else
    {
        Pnt3f   tpos[] = 
        { Pnt3f(.5,.5,.5), Pnt3f (.5,.5,.7), Pnt3f(.5,.5,.9), Pnt3f(.7,.5,.5), 
          Pnt3f(.5,.7,.5), Pnt3f (-1000,-1000,-1000) };
        
        Pnt3f   tsecpos[] = 
        { Pnt3f(0,0,0), Pnt3f(0,0,0), Pnt3f(0,0,0), Pnt3f(0,0,0), 
          Pnt3f(0,0,0) };
        
        Vec3f   tvel[] = 
        { Vec3f(0,0,0), Vec3f(0,0,0), Vec3f(0,0,0), Vec3f(0,0,0), 
          Vec3f(0,0,0) };
        
        Color3f tcol[] = 
        { Color3f(1,0,0), Color3f(0,1,0), Color3f(0,0,1), Color3f(1,1,0), 
          Color3f(1,0,1), Color3f(0,1,1), Color3f(1,1,1) };
        
        Vec3f   tsize[] = 
        { Vec3f(.1,0,0), Vec3f(.1,0,0), Vec3f(.1,0,0), Vec3f(.1,0,0), 
          Vec3f(.1,0,0) };

        for(UInt32 i=0; tpos[i][0] > -1000; ++i)
        {
            indices->push_back(i);  
            p->push_back(tpos[i]);  
            sp->push_back(tsecpos[i]);  
            velocities[i].setValue(tvel[i]);
            cols->getFieldPtr()->push_back(tcol[i]);
            size->push_back(tsize[i]);
            particles->getTextureZs().push_back(0);
        }
       
    }
    endEditCP(pnts);
    endEditCP(secpnts);
    endEditCP(cols);

    beginEditCP(norms);
    norms->push_back(Vec3f(0,1,0));
    endEditCP(norms);

    particles->setPositions( pnts );
    particles->setSecPositions( secpnts );
    particles->setColors( cols );
    particles->setNormals( norms );
                    
    endEditCP(particles);
 
    // set volume static to prevent constant update
    beginEditCP(pnode, Node::VolumeFieldMask);
    Volume &v=pnode->getVolume(false).getInstance();
    v.setEmpty();
    v.extendBy(Pnt3f(0,0,0));
    v.extendBy(Pnt3f(1,1,1));
    v.setStatic();
    ((DynamicVolume&)pnode->getVolume()).instanceChanged();
    endEditCP  (pnode, Node::VolumeFieldMask);
  
    SimpleTexturedMaterialPtr tm;

    tm = SimpleTexturedMaterial::create();

    UChar8 imgdata[] =
        {  255,255,0,  255,0,0,  
           0,255,0,    0,0,0,  
           255,255,255,  255,0,255,  
           0,255,255,    0,0,255,  
            };
    ImagePtr pImage = Image::create();

    if (argc > 2)
    {
        pImage->read(argv[2]);
    }
    else
    {
        pImage->set(Image::OSG_RGB_PF, 2, 2, 2, 1, 1, 0, imgdata);
    }
    
    beginEditCP(tm);
    tm->setDiffuse( Color3f( 1,1,1 ) );
    tm->setLit( false );

    tm->setImage( pImage );
    tm->setEnvMode( GL_MODULATE );
    tm->setMagFilter( GL_NEAREST );
    
    BlendChunkPtr bl=BlendChunk::create();
    
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    //bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    bl->setDestFactor(GL_ONE);
#if 0
    bl->setAlphaFunc(GL_EQUAL);
    bl->setAlphaValue(1);   
#endif
    endEditCP(bl);
   
    tm->addChunk(bl);
    
    endEditCP(tm);

    particles->setMaterial( tm );

#if 0
    // write it, just for testing

    std::ofstream out("test.osg");
    OSGWriter w(out);
    
    w.write(scene);
    
#endif

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    //mgr->setHighlight(scene);
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}


// move the particles
void idle(void)
{
    if(doMotion)
    {    
        beginEditCP(pnts);
        beginEditCP(secpnts);

        MFPnt3f *p=pnts->getFieldPtr();
        MFPnt3f *sp=secpnts->getFieldPtr();

        for(UInt32 i=0; i<p->size(); ++i)
        {
            Pnt3f pos=(*p)[i];

            pos+=velocities[i];

            if(pos[0]<0 || pos[0]>1)
            {
                pos[0]-=velocities[i][0];
                velocities[i][0]=-velocities[i][0];
            }
            if(pos[1]<0 || pos[1]>1)
            {
                pos[1]-=velocities[i][1];
                velocities[i][1]=-velocities[i][1];
            }
            if(pos[2]<0 || pos[2]>1)
            {
                pos[2]-=velocities[i][2];
                velocities[i][2]=-velocities[i][2];
            }

            (*sp)[i] = pos;
        }

        endEditCP(pnts);
        endEditCP(secpnts);

        beginEditCP(particles,
                    Particles::PositionsFieldMask|Particles::SecPositionsFieldMask);
        particles->setPositions(secpnts);
        particles->setSecPositions(pnts);   
        endEditCP  (particles,
                    Particles::PositionsFieldMask|Particles::SecPositionsFieldMask);

        std::swap(pnts,secpnts);    
    }
    
    if(doIndices)
    {
        beginEditCP(particles, Particles::IndicesFieldMask);
        indices->resize(pnts->getSize() / 2);
        for(UInt32 i = 0; i < pnts->getSize() / 2; ++i)
        {
            (*indices)[i] = (UInt32)(osgrand() * 2 - 1) * pnts->getSize();
        }
        endEditCP  (particles, Particles::IndicesFieldMask);     
    }
     
    glutPostRedisplay();
}


//
// GLUT callback functions
//

// redraw the window
void display(void)
{
       
    if(runBench)
    {
        static Int32 preframes = 5; // some drivers don't like to be swamped early
        
        if(--preframes < 0)
        {
            Time start,stop;

            start = getSystemTime();
            for(UInt32 i = 0; i < 100; i++)
            {
                mgr->redraw();
            }
            stop = getSystemTime();
            FLOG(( "100 frames a %d parts in %.2f secs (%.0f parts/sec)\n",
                    numParticles, stop-start, 100 * numParticles / (stop-start) ));
            exit(0);
        }
    }
    
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
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


class TestHandler:public OSG::BinaryDataHandler
{
public:
    TestHandler(FILE *file):OSG::BinaryDataHandler(5),_file(file) {
        unsigned int i;
        _memory.resize(7*2);
        for(i=0;i<_memory.size();i+=2)
        {
            _memory[i  ].resize(5);
            _memory[i+1].resize(5);
            readBufAdd (&_memory[i  ][0],_memory[i  ].size());
            writeBufAdd(&_memory[i+1][0],_memory[i+1].size());
        }
    }
    void read(OSG::MemoryHandle mem,OSG::UInt32 size) {
        fprintf(stderr,"direct read %d bytes\n",size);
        fread(mem,size,1,_file);
    }
    void write(OSG::MemoryHandle mem,OSG::UInt32 size) {
        fprintf(stderr,"direct write %d bytes\n",size);
        fwrite(mem,size,1,_file);
    }
private:
    std::vector<std::vector<OSG::UInt8> > _memory;
    FILE *_file;
};

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:    exit(1);
    case '0':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::Points);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to Points mode\n"));
                break;
    case '1':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::Lines);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to Lines mode\n"));
                break;
    case '2':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::ViewDirQuads);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to ViewDirQuads mode\n"));
                break;
    case '3':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::ViewerQuads);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to ViewerQuads mode\n"));
                break;
    case '4':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::Arrows);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to Arrows mode\n"));
                break;
    case '5':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::ViewerArrows);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to ViewerArrows mode\n"));
                break;
    case '6':   beginEditCP(particles, Particles::ModeFieldMask);
                particles->setMode(Particles::Rectangles);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to Rectangles mode\n"));
                break;
    case 'q':   beginEditCP(particles, Particles::DrawOrderFieldMask);
                particles->setDrawOrder(Particles::BackToFront);
                endEditCP  (particles, Particles::DrawOrderFieldMask);
                FLOG(("Draw order switched to BackToFront mode\n"));
                break;
    case 'w':   beginEditCP(particles, Particles::DrawOrderFieldMask);
                particles->setDrawOrder(Particles::Any);
                endEditCP  (particles, Particles::DrawOrderFieldMask);
                FLOG(("Draw order switched to Any mode\n"));
                break;
    case 'a':   beginEditCP(particles, Particles::DynamicFieldMask);
                particles->setDynamic(!particles->getDynamic());
                endEditCP  (particles, Particles::DynamicFieldMask);
                FLOG(("Dynamic switched %s\n", particles->getDynamic()?"on":"off"));
                break;
    case ' ':   doMotion=!doMotion;
                FLOG(("Motion %s\n",doMotion?"started":"stopped"));
                break;
    case 'i':   doIndices=!doIndices;
                FLOG(("Indices %s\n",doIndices?"on":"off"));
                indices->resize(0);
                break;
    case 'b':   {
                ParticleBSPTree bsp;
                bsp.build(particles.get().getCPtr());
                bsp.dump();
                
                // ASCII
                std::string s;
                FieldDataTraits<ParticleBSPTree>::putToString(bsp,s);
                PLOG << s << std::endl;
                const Char8 *c=s.c_str();
                FieldDataTraits<ParticleBSPTree>::getFromString(bsp,c);
                bsp.dump();
                Pnt3f ref(0.5,0.5,0.5);
                UInt32 length = pnts->getSize();
                Int32 *order = bsp.traverse(ref,length);
                for(UInt32 i = 0; i < length; i++)
                {
                    std::cout << order[i] << " ";
                }
                std::cout << std::endl;
                delete [] order;
                
                // Bin
                std::cout << "BIN:" 
                     << FieldDataTraits<ParticleBSPTree>::getBinSize(bsp) 
                     << std::endl;
                
                FILE* wfile=fopen("binfile","w");
                TestHandler w(wfile);               
                FieldDataTraits<ParticleBSPTree>::copyToBin(w,bsp);
                w.flush();
                fclose(wfile);
                
                ParticleBSPTree bsp2;
                FILE *rfile=fopen("binfile","r");
                TestHandler r(rfile);
                FieldDataTraits<ParticleBSPTree>::copyFromBin(r,bsp2);
                fclose(rfile);
                
                bsp.dump();
                }
                break;
   }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | (runBench?0:GLUT_DOUBLE) );
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
