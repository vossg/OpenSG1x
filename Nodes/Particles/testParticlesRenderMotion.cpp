
#include <algorithm>
#include <string.h>
#include <GL/glut.h>
#include <OSGConfig.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGComponentTransform.h>

#include <OSGSimpleTexturedMaterial.h>
#include <OSGBlendChunk.h>
#include <OSGParticles.h>

#include <OSGParticleBSP.h>

#include <ostream>
//#include <OSGWriter.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );

Vec3f *velocities;
ParticlesPtr particles;
GeoPositions3fPtr pnts,secpnts;
MFInt32 *indices;

Bool doMotion=true;
Bool doIndices=false;

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    // create the scene
    NodePtr scene = Node::create();    
    NodePtr pnode = Node::create();
    
    ComponentTransformPtr trans = ComponentTransform::create();
    beginEditCP(scene);
    scene->setCore(trans);
    scene->addChild(pnode);
    endEditCP(scene);
    
    // transforsm don't work yet, ignore for now
    beginEditCP(trans);
    trans->setTranslation(Vec3f(0,0,0));
    trans->setRotation(Quaternion(Vec3f(0,1,0),0));
    endEditCP(trans);
    
    
    particles = Particles::create();
    beginEditCP(pnode);
    pnode->setCore(particles);
    endEditCP(pnode);

    UInt32 count = 100;
    
    if (argc > 1)
    {
        count=atoi(argv[1]);
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
    
    velocities=new Vec3f [count];
    
    beginEditCP(pnts);
    beginEditCP(secpnts);
    beginEditCP(cols);
    for(UInt32 i=0; i < count; ++i)
    {
        Pnt3f pnt(osgrand(),osgrand(),osgrand());
        p->addValue(pnt);  
        sp->addValue(pnt);  
        velocities[i].setValues(osgrand()/30.f/2, osgrand()/30.f/2, osgrand()/30.f/2);
        cols->getFieldPtr()->addValue( 
            Color3f(osgrand()/2.f + .5f,osgrand()/2.f + .5f,osgrand()/2.f + .5f) );
        size->addValue(
            Vec3f(osgrand()/20.f+0.05,osgrand()/20.f+0.05,osgrand()/20.f+0.05));
    }
    endEditCP(pnts);
    endEditCP(secpnts);
    endEditCP(cols);

    beginEditCP(norms);
    norms->addValue(Vec3f(0,1,0));
    endEditCP(norms);

    particles->setPositions( pnts );
    particles->setSecPositions( secpnts );
    particles->setColors( cols );
    particles->setNormals( norms );
    
    endEditCP(particles);
 
    // set volume static to prevent constant update
    beginEditCP(scene, Node::VolumeFieldMask);
    Volume &v=scene->getVolume().getInstance();
    v.setEmpty();
    v.extendBy(Pnt3f(0,0,0));
    v.extendBy(Pnt3f(1,1,1));
    v.setStatic();
    endEditCP  (scene, Node::VolumeFieldMask);
  
    SimpleTexturedMaterialPtr tm;

    tm = SimpleTexturedMaterial::create();

    UChar8 imgdata[] =
        {  255,255,255,  255,0,0,  255,0,255,
           255,0,0,  255,0,0,  255,255,255 };
    Image image;

    if (argc > 2)
    {
        image.read(argv[2]);
    }
    else
    {
        image.set(Image::OSG_RGB_PF, 3, 2, 1, 1, 1, 0, imgdata);
    }
    
    beginEditCP(tm);
    tm->setDiffuse( Color3f( 1,1,1 ) );
    tm->setLit( false );

    tm->setImage( &image );
    tm->setEnvMode( GL_MODULATE );
    
    BlendChunkPtr bl=BlendChunk::create();
    
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
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

    mgr->setHighlight(scene);
        
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
            Pnt3f pos=p->getValue(i);

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

            sp->setValue(pos,i);
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
            indices->setValue( (osgrand() * 2 - 1) * pnts->getSize() , i);
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

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:    exit(1);
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
                particles->setMode(Particles::Arrows);
                endEditCP  (particles, Particles::ModeFieldMask);
                FLOG(("Particles switched to Arrows mode\n"));
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
                bsp.build(particles.getCPtr());
                bsp.dump();
                string s;
                FieldDataTraits<ParticleBSPTree>::putToString(bsp,s);
                PLOG << s << endl;
                const Char8 *c=s.c_str();
                FieldDataTraits<ParticleBSPTree>::getFromString(bsp,c);
                bsp.dump();
                Pnt3f ref(0.5,0.5,0.5);
                UInt32 length = pnts->getSize();
                Int32 *order = bsp.traverse(ref,length);
                for(UInt32 i = 0; i < length; i++)
                {
                    cout << order[i] << " ";
                }
                cout << endl;
                delete [] order;
                }
                break;
   }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
