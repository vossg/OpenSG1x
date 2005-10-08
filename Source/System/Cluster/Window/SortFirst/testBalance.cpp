#include <OSGGLUT.h>
#include <OSGGL.h>
#include <OSGConfig.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleGeometry.h>
#include <OSGTileLoadBalancer.h>
#include <OSGTileCameraDecorator.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGTime.h>
#include <OSGSceneFileHandler.h>
#include <OSGRenderNode.h>
#include <OSGSimpleMaterial.h>
#include <OSGSkyBackground.h>
#include <OSGStatCollector.h>
#include <OSGStatElemTypes.h>
#include <OSGImage.h>
#include <OSGImageFileType.h>
#include <OSGImageFileHandler.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

bool            doSave=false;
TileLoadBalancer *tileLoadBalancer;
char           *dumpImage="balance";
int             dumpImageNr=0;
bool            useFaceDistribution=false;
bool            viewVolume=false;
bool            simulateRendering=false;
int             serverCount=10;
int             startLoop,loop=0;
char            *resultfile="result";
FILE            *resultio=NULL;
bool            navigate=false;
bool            loopbin=false;
bool            useCrossCut=false;
bool            useFixCrossRegions=false;
bool            useFixSliceRegions=false;
std::vector<Quaternion>  animOri;
std::vector<Vec3f     >  animPos;
std::string              animName="animation.txt";
bool                     animate=false;
double                   animTime=0;
bool                     setRegionStatistics=true;
Time tmin    ,tmax    ,tbalance;
Time sum_tmin=0,sum_tmax=0,sum_tbalance=0;
float sum_faces=0,sum_culledFaces=0,sum_pixel=0,sum_culledNodes=0;
float facemax,fcullmax,pmax;
float sum_facemax=0,sum_fcullmax=0,sum_pmax=0;
int                      animFrames=4;
RenderAction             *raction;
StatCollector            stats;
float                    sum_travTime;
float                    sum_drawTime;
TransformPtr             cart;

void setFixCrossRegions( Int32 count,
                         UInt32 x1,
                         UInt32 y1,
                         UInt32 x2,
                         UInt32 y2,
                         bool   cutX,
                         TileLoadBalancer::ResultT &region )
{
    Int32 c1,c2;
    UInt32 nxA,nxB,nyA,nyB;

    if(count==1)
    {
        TileLoadBalancer::Region r;
        r.x1=x1;
        r.y1=y1;
        r.x2=x2;
        r.y2=y2;
        region.push_back(r);
        return;
    }
    c1=count/2;
    c2=count-c1;
    if(cutX)
    {
        nyA=y2;
        nyB=y1;
        nxA=x1+UInt32((x2-x1)*c1/(float)count);
        nxB=nxA+1;
    }
    else
    {
        nxA=x2;
        nxB=x1;
        nyA=y1+UInt32((y2-y1)*c1/(float)count);
        nyB=nyA+1;
    }
    setFixCrossRegions(c1,x1,y1,nxA,nyA,cutX^1,region);
    setFixCrossRegions(c2,nxB,nyB,x2,y2,cutX^1,region);
}

void setFixSliceRegions( Int32 count,
                         UInt32 width,
                         UInt32 height,
                         TileLoadBalancer::ResultT &region )
{
    Int32 from=0;
    Int32 to=0;
    Int32 i;
    for(i=0;i<count;i++)
    {
        to=Int32((i+1)*width/float(count));
        TileLoadBalancer::Region r;
        r.x1=from;
        r.y1=0;
        r.x2=to;
        r.y2=height;
        region.push_back(r);
        from=to+1;
    }
}

bool first=true;

class MySceneManager:public SimpleSceneManager
{
public:
    MySceneManager(){}
    virtual void redraw( void ) {
        cart=_cart;
        static RenderNode rn;
        static int currentServers=0;
        size_t i;
        Real32 travTime;
        Real32 drawTime;
        TileLoadBalancer::ResultT region;
        if (_internalRoot == NullFC)
        {
            initialize();
            showAll();
        }
        if(animate && animPos.size()>1)
        {
            Real32 a;
            UInt32 i;
            Vec3f v;
            i=(UInt32)animTime;
            a=animTime-i;
            v=animPos[i] + (animPos[i+1] - animPos[i]) * a; 
            _cart->getMatrix().setTranslate(v[0],v[1],v[2]);
            _cart->getMatrix().setRotate(
                Quaternion::slerp(animOri[i],animOri[i+1],a));
        }
        else
        {
            _cart->getSFMatrix()->setValue(_navigator.getMatrix());    
        }
        updateHighlight();
        if(navigate)
        {
            _win->render(_action);
            return;
        }
        _win->activate();
        _win->frameInit();
        if(first)
        {
            tileLoadBalancer=new TileLoadBalancer(useFaceDistribution,
                                                  !useCrossCut);
            first=false;
            rn.determinePerformance(_win);
            rn.dump();
            currentServers=0;
            _win->getPort().resize(1);
        }
        if(currentServers < serverCount)
        {
            ViewportPtr vp,ovp=_win->getPort(0);
            addRefCP(ovp);
            addRefCP(ovp);
            TileCameraDecoratorPtr deco;
            for(int i=_win->getPort().size()-1;i<serverCount;i++)
            {
                currentServers++;
                tileLoadBalancer->addRenderNode(rn,i);
                if(simulateRendering)
                {
                    beginEditCP(_win);
                    deco=TileCameraDecorator::create();
                    beginEditCP(deco);
                    deco->setFullWidth ( _win->getWidth() );
                    deco->setFullHeight( _win->getHeight() );
                    deco->setDecoratee( ovp->getCamera() );
                    vp=Viewport::create();
                    beginEditCP(vp);
                    vp->setRoot      ( ovp->getRoot()       );
                    vp->setBackground( ovp->getBackground() );
                    vp->getMFForegrounds()->setValues( ovp->getForegrounds() );
                    vp->setCamera(deco);
                    _win->addPort(vp);
                    endEditCP(_win);
                    endEditCP(vp);
                    endEditCP(deco);
                }
            }
        }
        tbalance = -getSystemTime();
        tileLoadBalancer->update(_win->getPort()[0]->getRoot());
        if(useFixCrossRegions)
        {
            setFixCrossRegions( serverCount,
                                0,
                                0,
                                _win->getWidth()-1,
                                _win->getHeight()-1,
                                true,
                                region );
        }
        else
        {
            if(useFixSliceRegions)
            {
                setFixSliceRegions( serverCount,
                                    _win->getWidth()-1,
                                    _win->getHeight()-1,
                                    region );
            }
            else
            {
                tileLoadBalancer->balance(_win->getPort()[0],false,region);
            }
        }
        tbalance += getSystemTime();
        if(simulateRendering)
        {
            ViewportPtr vp;
            TileCameraDecoratorPtr deco;
            for(i=0;i<region.size();++i)
            {
                vp=_win->getPort()[i+1];
                deco=TileCameraDecoratorPtr::dcast(vp->getCamera());
                beginEditCP(deco);
                beginEditCP(vp);
                vp->setSize(region[i].x1,
                            region[i].y1,
                            region[i].x2,
                            region[i].y2);
                deco->setSize(region[i].x1/(float)_win->getWidth(),
                              region[i].y1/(float)_win->getHeight(),
                              region[i].x2/(float)_win->getWidth(),
                              region[i].y2/(float)_win->getHeight());
                endEditCP(deco);
                endEditCP(vp);
            }
        }
        Time t;
        if(setRegionStatistics)
        {
            tileLoadBalancer->setRegionStatistics(_win->getPort()[0],
                                                  region);
            for(i=0;i<region.size();++i)
            {
                if(i==0)
                {
                    facemax=region[i].faces;
                    fcullmax=region[i].culledFaces;
                    pmax=region[i].pixel;
                }
                else
                {
                    if(region[i].faces>facemax) 
                        facemax=region[i].faces;
                    if(region[i].culledFaces>fcullmax) 
                        fcullmax=region[i].culledFaces;
                    if(region[i].pixel>pmax) 
                        pmax=region[i].pixel;
                }
                sum_faces+=region[i].faces;
                sum_culledFaces+=region[i].culledFaces;
                sum_pixel+=region[i].pixel;
            }
            sum_facemax +=facemax;
            sum_fcullmax+=fcullmax;
            sum_pmax    +=pmax;

        }
        for(i=0;i<_win->getPort().size();++i)
        {
            if(i==0 && _win->getPort().size() >1)
                continue;
            _action->setWindow( _win.getCPtr() );
            _action->setStatistics( &stats );
            _win->getPort(i)->render( _action );
            _action->setStatistics( NULL );
            StatElem *statElem;
            statElem=stats.getElem(DrawActionBase::statTravTime);
            travTime=statElem->getValue();
            statElem=stats.getElem(RenderAction::statDrawTime);
            drawTime=statElem->getValue();
            glFinish();
            t=-getSystemTime();
            _win->getPort(i)->render( _action );
            glFinish();
            t+=getSystemTime();
            if(i==0)
                continue;
            if(i==1)
            {
                tmin=tmax=t;
            }
            else
            {
                if(t<tmin) tmin=t;
                if(t>tmax) tmax=t;
            }
            sum_travTime+=travTime-drawTime;
            sum_drawTime+=drawTime;
        }
        sum_tmin+=tmin;
        sum_tmax+=tmax;
        sum_tbalance+=tbalance;
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_SCISSOR_TEST);
        glViewport(0,0,
                   _win->getWidth(),
                   _win->getHeight());
        if(viewVolume)
            tileLoadBalancer->drawVolumes(_win);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0,_win->getWidth(),
                   0,_win->getHeight());
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        for(i=0;i<region.size();++i)
        {
#if 0
            std::cout << "Region: ";
            std::cout << region[i].x1 << " ";
            std::cout << region[i].y1 << " ";
            std::cout << region[i].x2 << " ";
            std::cout << region[i].y2 << std::endl;
#endif
            glBegin(GL_LINE_LOOP);
            glColor3f(1, 1, 0);
            glVertex3f(region[i].x1,region[i].y1,0);
            glVertex3f(region[i].x2,region[i].y1,0);
            glVertex3f(region[i].x2,region[i].y2,0);
            glVertex3f(region[i].x1,region[i].y2,0);
            glEnd();
        }
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();

        if(doSave)
        {
            Int32 w,h;
            w=_win->getPort(0)->getPixelWidth();
            h=_win->getPort(0)->getPixelHeight();
            ImagePtr pImage = Image::create();
            pImage->set(Image::OSG_RGB_PF,
                        w,h,1,
                        1,1,0.0,
                        NULL);
            ImageFileType *imgTransType=ImageFileHandler::the().getFileType("JPEG");
            char filename[256];
            if(imgTransType==NULL)
            {
                std::cerr << "Unknown image trans type" << std::endl;
                return;
            }
            sprintf(filename,"%s_%d.jpg",dumpImage,dumpImageNr++);
            // read buffer data into image
            glPixelStorei(GL_PACK_ALIGNMENT,1);
            glReadPixels(0,0,w,h,
                         GL_RGB,GL_UNSIGNED_BYTE,
                         pImage->getData());
            imgTransType->write(pImage,filename);

            subRefCP(pImage);
        }
        _win->swap();
        _win->frameExit();
    }
};

void loadAnim()
{
    Real32 ax,ay,az,r,x,y,z;
    FILE *file=fopen(animName.c_str(),"r");
    
    animOri.clear();
    animPos.clear();
    if(!file)
        return;
    while(fscanf(file,"%f %f %f %f,%f %f %f",&ax,&ay,&az,&r,&x,&y,&z)==7)
    {
        animOri.push_back(Quaternion(Vec3f(ax,ay,az),r));
        animPos.push_back(Vec3f(x,y,z));
    }
    fclose(file);
}

SimpleSceneManager *mgr;
NodePtr             scene;

// Standard GLUT callback functions
void display( void )
{
    mgr->redraw();
    if(!navigate)
    {
        if(animate)
        {
            animTime+=animPos.size()/(double)animFrames;
            if(animTime<(animPos.size()-1))
                return;
            animTime=0;
        }
        if(simulateRendering)
        {
            if(!resultio)
                resultio=fopen(resultfile,"w");
            fprintf(resultio,
                    "%5d %10.6f %10.6f %10.6f "
                    "%10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n",
                    serverCount,
                    sum_tmin,
                    sum_tmax,
                    sum_tbalance,
                    sum_faces,
                    sum_culledFaces,
                    sum_pixel,
                    sum_facemax,
                    sum_fcullmax,
                    sum_pmax,
                    sum_travTime,
                    sum_drawTime);
            sum_tmin=sum_tmax=sum_tbalance=0;
            sum_travTime=sum_drawTime=sum_faces=sum_culledFaces=sum_pixel=0;
            sum_pmax=sum_travTime=sum_drawTime=0;
        }
        if(loop)
        {
            loop--;
            if(loopbin)
                serverCount*=2;
            else
                serverCount++;
            if(!loop)
            {
                if(resultio)
                    fclose(resultio);
                exit(0);
            }
        }
    }
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

void key(unsigned char key, int , int )
{
    switch(key)
    {
        case 27:    exit(1);
        case 'm':   doSave=!doSave;
            break;
        case 'r':   navigate=false;
            break;
        case 'a':   mgr->setHighlight(scene);
            break;
        case 'd':
            first=true;
            useFaceDistribution=!useFaceDistribution;
            break;
        case 'c':
            first=true;
            useCrossCut=!useCrossCut;
            break;
/*
        case 's':   mgr->setHighlight(NullFC);
            break;
*/
        case 'l':   mgr->useOpenSGLogo();
            break;
        case 'f':   mgr->setNavigationMode(Navigator::FLY);
            break;
        case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
            break;
//        case  'c': glutSetCursor(GLUT_CURSOR_NONE); break;
//        case  'C': glutSetCursor(GLUT_CURSOR_CYCLE); break;
        case 'v': 
            viewVolume=!viewVolume; 
//            mgr->getAction()->setVolumeDrawing(viewVolume);
            break;
        case  'W': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case  'F': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;

        case 's':
        {
            FILE *file=fopen(animName.c_str(),"a");
            Matrix m=cart->getMatrix();
            Quaternion q(m);
            Real32 ax,ay,az,r;
            animPos.push_back(Vec3f(m[3][0],
                                    m[3][1],
                                    m[3][2]));
            animOri.push_back(q);
            q.getValueAsAxisRad(ax,ay,az,r);
            fprintf(file,"%f %f %f %f,%f %f %f\n",ax,ay,az,r,
                    m[3][0],
                    m[3][1],
                    m[3][2]);
            fclose(file);
            break;
        }
        case 'S':
        {
            FILE *file=fopen((animName+".wrl").c_str(),"w");
            std::vector<Quaternion>::iterator qit;
            
            fprintf(file,"DEF OriInter OrientationInterpolator {\n\tkey [");
            for(size_t i = 0; i < animOri.size(); ++i)
            {               
                fprintf(file, "%f", i / (Real32)(animOri.size() - 1) );
                if(i < animOri.size() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n\tkeyValue [");
            for(qit = animOri.begin(); qit != animOri.end(); ++qit)
            {
                Real32 ax,ay,az,r;
                (*qit).getValueAsAxisRad(ax,ay,az,r);
                
                fprintf(file, "%f %f %f %f", ax, ay, az, r );
                if(qit < animOri.end() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n}\n\n");

            std::vector<Vec3f>::iterator vit;
            
            fprintf(file,"DEF PosInter PositionInterpolator {\n\tkey [");
            for(size_t i = 0; i < animPos.size(); ++i)
            {               
                fprintf(file, "%f", i / (Real32)(animPos.size() - 1) );
                if(i < animPos.size() - 1)
                    fprintf(file,", ");
            }
            fprintf(file,"]\n\tkeyValue [");
            for(vit = animPos.begin(); vit != animPos.end(); ++vit)
            {
                Vec3f v = *vit;
                
                fprintf(file, "%f %f %f, ", v[0], v[1], v[2] );
            }
            fprintf(file,"]\n}\n\n");

            fclose(file);
            break;
        }


    }
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    int i;
    float ca=-1,cb=-1,cc=-1;
    // OSG init
    osgInit(argc,argv);
    char *filename=NULL;

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
    gwin->setSize(1024,768);

    // create the scene
    float x,y,z;
    scene = Node::create();
    beginEditCP(scene);
    scene->setCore(Group::create());
    endEditCP(scene);

    NodePtr file;

    for(i=1;i<argc;++i)
    {
        if(argv[i][0] =='-')
        {
            switch(argv[i][1])
            {
                case 'f':
                    if(argv[i][2]=='s')
                        useFixSliceRegions=true;
                    else
                        useFixCrossRegions=true;
                    break;
                case 'd':
                    useFaceDistribution=true;
                    break;
                case 'c':
                    useCrossCut=true;
                    break;
                case 'v':
                    viewVolume=true;
                    break;
                case 's':
                    serverCount=atoi(&argv[i][2]);
                    break;
                case 'l':
                    startLoop=loop=atoi(&argv[i][2]);
                    break;
                case 'S':
                    simulateRendering=true;
                    break;
                case 'r':
                    resultfile=argv[i]+2;
                    break;
                case 'a':
                    animName=argv[i]+2;
                    loadAnim();
                    animate=true;
                    break;
                case 'A':
                    animFrames=atoi(&argv[i][2]);
                    break;
                case 'n':
                    navigate=true;
                    break;
                case 'b':
                    loopbin=true;
                    break;
            }
        }
        else
        {
            if(argv[i][0] >='0' &&
               argv[i][0] <='9')
            {
                if(ca==-1)
                    ca=atoi(argv[i]);
                else
                    if(cb==-1)
                        cb=atoi(argv[i]);
                    else
                        if(cc==-1)
                            cc=atoi(argv[i]);
            }
            else
            {
                filename=argv[i];
            }
        }
    }
    if(ca == -1 && filename)
    {
        file = OSG::SceneFileHandler::the().read(filename);
        beginEditCP(scene);
        scene->addChild(file);
        endEditCP(scene);
    }
    else
    {
        if(ca==-1)
            ca=4;
        if(cb==-1)
            cb=ca;
        if(cc==-1)
            cc=cb;
        if(file == NullFC)
        {
            GeometryPtr geo=makeBoxGeo(.6,.6,.6,20,20,20);
            beginEditCP(geo);
            SimpleMaterialPtr mat=SimpleMaterial::create();
            beginEditCP(mat);
            mat->setAmbient(Color3f(.4,.4,.4));
            mat->setSpecular(Color3f(0,0,0));
            mat->setDiffuse(Color3f(1,1,1));
            endEditCP(mat);
            geo->setMaterial(mat);
            endEditCP(geo);
            NodePtr node;
            NodePtr geoNode;
            TransformPtr trans;
            for(x=-ca/2 ; x<ca/2 ; x++)
                for(y=-cb/2 ; y<cb/2 ; y++)
                    for(z=-cc/2 ; z<cc/2 ; z++)
                    {
                        trans=Transform::create();
                        node=Node::create();
                        geoNode=Node::create();
                        
                        beginEditCP(geoNode);
                        beginEditCP(trans);
                        beginEditCP(node);
                        
                        node->setCore(trans);
                        trans->getMatrix().setTranslate(x,y,z);
                        if(!filename)
                        {
                            geoNode=Node::create();
                            geoNode->setCore(geo);
                        }
                        else
                        {
                            geoNode = OSG::SceneFileHandler::the().read(filename);
                        }
                        node->addChild( geoNode );
                        beginEditCP(scene);
                        scene->addChild(node);
                        
                        endEditCP(geoNode);
                        endEditCP(scene);
                        endEditCP(trans);
                        endEditCP(node);
                    }
        }
    }
    // create the SimpleSceneManager helper
    mgr = new MySceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    if(loop)
        glutIdleFunc(display);
//    glutReshapeWindow(720,576);
    glutReshapeWindow(gwin->getWidth(),gwin->getHeight());
    glutMainLoop();

    return 0;
}

