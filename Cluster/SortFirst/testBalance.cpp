#include <GL/glut.h>
#include <GL/gl.h>
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
int             loop=0;
bool            cache;

class MySceneManager:public SimpleSceneManager
{
public:
    MySceneManager(){}
    virtual void redraw( void ) {
        static bool first=true;
        static RenderNode rn;
        static int currentServers=0;
        int i;
        double tbalance;
        TileLoadBalancer::ResultT region;
        if (_internalRoot == NullFC)
        {
            initialize();
            showAll();
        }
        _cart->getSFMatrix()->setValue(_navigator.getMatrix());    
        updateHighlight();
        _win->activate();
        _win->frameInit();
        if(first)
        {
            tileLoadBalancer=new TileLoadBalancer(useFaceDistribution);
            first=false;
            rn.determinePerformance(_win);
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
        tileLoadBalancer->balance(_win->getPort()[0],false,region);
        tbalance += getSystemTime();
        if(simulateRendering)
        {
            ViewportPtr vp;
            TileCameraDecoratorPtr deco;
            for(i=0;i<region.size();i+=4)
            {
#if 1
                cout << "Region: " << i << " ";
                cout << region[i+0] << " ";
                cout << region[i+1] << " ";
                cout << region[i+2] << " ";
                cout << region[i+3] << endl;
                if(region[i+0] >= region[i+2]) {
                    cout << "!!!" << endl;
                    region[i+2]++;
                }
                if(region[i+1] >= region[i+3]) {
                    cout << "!!!" << endl;
                    region[i+3]++;
                }
#endif
                vp=_win->getPort()[i/4+1];
                deco=TileCameraDecoratorPtr::dcast(vp->getCamera());
                beginEditCP(deco);
                beginEditCP(vp);
                vp->setSize(region[i+0],
                            region[i+1],
                            region[i+2],
                            region[i+3]);
                deco->setSize(region[i+0]/(float)_win->getWidth(),
                              region[i+1]/(float)_win->getHeight(),
                              region[i+2]/(float)_win->getWidth(),
                              region[i+3]/(float)_win->getHeight());
                endEditCP(deco);
                endEditCP(vp);
            }
        }
        Time t,tmin,tmax;
        for(i=0;i<_win->getPort().size();++i)
        {
            t=-getSystemTime();
            _action->setWindow( _win.getCPtr() );
            _win->getPort(i)->render( _action );
            glFlush();
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
        }
        if(!cache && simulateRendering)
            printf("speed %5d %10.6f %10.6f %10.6f\n",_win->getPort().size()-1,
                   tmin,
                   tmax,
                   tbalance);
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
        for(i=0;i<region.size();i+=4)
        {
#if 0
            cout << "Region: ";
            cout << region[i+0] << " ";
            cout << region[i+1] << " ";
            cout << region[i+2] << " ";
            cout << region[i+3] << endl;
#endif
            glBegin(GL_LINE_LOOP);
            glColor3f(1, 1, 0);
            glVertex3f(region[i+0],region[i+1],0);
            glVertex3f(region[i+2],region[i+1],0);
            glVertex3f(region[i+2],region[i+3],0);
            glVertex3f(region[i+0],region[i+3],0);
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
            Image image(Image::OSG_RGB_PF,
                        w,h,1,
                        1,1,0.0,
                        NULL,true);
            ImageFileType *imgTransType=ImageFileHandler::the().getFileType("JPEG");
            char filename[256];
            if(imgTransType==NULL)
            {
                cerr << "Unknown image trans type" << endl;
                return;
            }
            sprintf(filename,"%s_%d.jpg",dumpImage,dumpImageNr++);
            // read buffer data into image
            glPixelStorei(GL_PACK_ALIGNMENT,1);
            glReadPixels(0,0,w,h,
                         GL_RGB,GL_UNSIGNED_BYTE,
                         image.getData());
            imgTransType->write(image,filename);
        }
        _win->swap();
        _win->frameExit();
    }
};

SimpleSceneManager *mgr;
NodePtr             scene;

// Standard GLUT callback functions
void display( void )
{
    cache=true;
    mgr->redraw();
    cache=false;
    mgr->redraw();
    if(loop)
    {
        SLOG << loop << endl;
        loop--;
        serverCount++;
        if(!loop)
            exit(0);
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
        case 'a':   mgr->setHighlight(scene);
            break;
        case 's':   mgr->setHighlight(NullFC);
            break;
        case 'l':   mgr->useOpenSGLogo();
            break;
        case 'f':   mgr->setNavigationMode(Navigator::FLY);
            break;
        case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
            break;
        case  'c': glutSetCursor(GLUT_CURSOR_NONE); break;
        case  'C': glutSetCursor(GLUT_CURSOR_CYCLE); break;
        case 'v': viewVolume=!viewVolume; break;
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
                case 'd':
                    useFaceDistribution=true;
                    break;
                case 'v':
                    viewVolume=true;
                    break;
                case 's':
                    serverCount=atoi(&argv[i][2]);
                    break;
                case 'l':
                    loop=atoi(&argv[i][2]);
                    break;
                case 'S':
                    simulateRendering=true;
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
                filename=argv[1];
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
    glutReshapeWindow(1152,864);
    glutMainLoop();

    return 0;
}

