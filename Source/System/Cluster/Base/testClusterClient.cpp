#include <OSGGLUT.h>
#include <OSGGLU.h>
#include <OSGConfig.h>
#include <iostream>
#include <OSGLog.h>
#include <OSGStreamSockConnection.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGNode.h>
#include <OSGClusterWindow.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>
#include <OSGSimpleGeometry.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGPerspectiveCamera.h>
#include <OSGSolidBackground.h>
#include <OSGGradientBackground.h>
#include <OSGTrackball.h>
#include <OSGVolumeDraw.h>
#include <OSGGLUTWindow.h>
#include <OSGRenderAction.h>
#include <OSGDrawAction.h>
#include <OSGMultiDisplayWindow.h>
#include <OSGSortFirstWindow.h>
#include <OSGShearedStereoCameraDecorator.h>

OSG_USING_NAMESPACE

Trackball                tball;
int                      mouseb = 0;
int                      lastx=0, lasty=0;
int                      winwidth=0, winheight=0;
NodePtr		             root;
TransformPtr             cam_trans;
PerspectiveCameraPtr     cam;
ClusterWindowPtr         clusterWindow;
RenderAction            *ract,*ract1,*ract2;
GLUTWindowPtr            clientWindow;
SortFirstWindowPtr       sortfirst;
MultiDisplayWindowPtr    multidisplay;
bool                     animate=false;
bool                     multiport=false;
float                    ca=-1,cb=-1,cc=-1;
bool                     doStereo=false;
float                    eyedistance=1,zeroparallax=10;
int                      serverx=-1,servery=-1;
std::vector<Quaternion>  animOri;
std::vector<Vec3f     >  animPos;
std::string              animName="animation.txt";
Real32                   animTime=0;
std::string              broadcastAddress;
bool                     broadcastAddressValid = false;

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

void display(void)
{
    Time t;

    t=-getSystemTime();

    beginEditCP( cam_trans );
    if(animate && animPos.size()>1)
    {
        Real32 a;
        UInt32 i;
        Vec3f v;
        animTime=fmod(animTime+(1.0/30.0),(animPos.size()-1));
        i=(UInt32)animTime;
        a=animTime-i;
        v=animPos[i] + (animPos[i+1] - animPos[i]) * a; 
        cam_trans->getMatrix().setTranslate(v[0],v[1],v[2]);
        cam_trans->getMatrix().setRotate(
            Quaternion::slerp(animOri[i],animOri[i+1],a));
    }
    else
    {
        cam_trans->getSFMatrix()->setValue( tball.getFullTrackballMatrix() );
    }
    endEditCP( cam_trans );
    try
    {
        clusterWindow->render( ract );	
        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clearAll();
	}
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }
    
    t+=getSystemTime();
    if(animate)
        printf("Frame %8.3f %8.5f %8.3f\n",
               animTime,
               t,1/t);
}

void reshape( int width, int height )
{
    glViewport(0, 0, width, height);
    beginEditCP(clientWindow);
	clientWindow->resize( width, height );
    endEditCP(clientWindow);
	glutPostRedisplay();
}

void motion(int x, int y)
{
    OSG::Real32 w = clientWindow->getWidth(), h = clientWindow->getHeight();


    OSG::Real32 a = -2. * ( lastx / w - .5 ),
                b = -2. * ( .5 - lasty / h ),
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
    lastx = x;
    lasty = y;
	glutPostRedisplay();
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
        case GLUT_RIGHT_BUTTON: tball.setAutoPositionNeg(true);
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
        case GLUT_RIGHT_BUTTON: tball.setAutoPositionNeg(false);
                                break;
        }
        mouseb &= ~(1 << button);
    }
    lastx = x;
    lasty = y;
	glutPostRedisplay();
}

void key(unsigned char key, int /*x*/, int /*y*/)
{
	switch ( key )
	{
        case 'l':
        {
            loadAnim();
            break;
        }
        case 'c':
        {
            FILE *file=fopen(animName.c_str(),"w");
            fclose(file);
            animOri.clear();
            animPos.clear();
            break;
        }
        case 's':
        {
            FILE *file=fopen(animName.c_str(),"a");
            Matrix m=cam_trans->getMatrix();
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
            for(int i = 0; i < animOri.size(); ++i)
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
            for(int i = 0; i < animPos.size(); ++i)
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
         case 'b':	// switch wire frame
            if(ract==ract1)
                ract=ract2;
            else
                ract=ract1;
            break;
        case 'j':
            if(sortfirst!=NullFC)
            {
                beginEditCP(sortfirst);
                sortfirst->setCompression("JPEG");
                endEditCP(sortfirst);
            }
            break;
        case 'r':
            if(sortfirst!=NullFC)
            {
                beginEditCP(sortfirst);
                sortfirst->setCompression("RLE");
                endEditCP(sortfirst);
            }
            break;
        case 'n':
            if(sortfirst!=NullFC)
            {
                beginEditCP(sortfirst);
                sortfirst->getCompression().erase();
                endEditCP(sortfirst);
            }
            break;
        case 'a':
            if(animate)
            {
                glutIdleFunc(NULL);       
                animate=false;
            }
            else
            {
                glutIdleFunc(display);       
                animate=true;
            }
            break;
        case 'd':
            // remove tree
            beginEditCP(root);
            while(root->getNChildren())
            {
                root->subChild(0);
            }
            endEditCP(root);
            break;
        case 27:	// should kill the clients here
            // exit
            subRefCP(clusterWindow);
            osgExit(); 
            exit(0);
	}
	
	glutPostRedisplay();
}


Action::ResultE wireDraw( CNodePtr &, Action * action )
{
    NodePtr node = action->getActNode();
    node->updateVolume();
    bool l = glIsEnabled( GL_LIGHTING );
    glDisable( GL_LIGHTING );
    glColor3f( .8,.8,.8 );
    drawVolume( node->getVolume() );
    if ( l )
        glEnable( GL_LIGHTING );
    return Action::Continue;
}

Action::ResultE ignore( CNodePtr &, Action * )
{	
    return Action::Continue;
}

void init(std::vector<char *> &filenames)
{
    int i;
    OSG::DirectionalLightPtr dl;
    Real32 x,y,z;

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // create the graph

    // beacon for camera and light
    OSG::NodePtr b1n = OSG::Node::create();
    OSG::GroupPtr b1 = OSG::Group::create();
    OSG::beginEditCP(b1n);
    b1n->setCore( b1 );
    OSG::endEditCP(b1n);

    // transformation
    OSG::NodePtr t1n = OSG::Node::create();
    OSG::TransformPtr t1 = OSG::Transform::create();
    OSG::beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    OSG::endEditCP(t1n);

    cam_trans = t1;
    addRefCP(t1n);

    // light

    OSG::NodePtr dlight = OSG::Node::create();
    dl = OSG::DirectionalLight::create();

    OSG::beginEditCP(dlight);
    dlight->setCore( dl );
    OSG::endEditCP(dlight);

    OSG::beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    OSG::endEditCP(dl);

    // root
    root = OSG::Node::create();
    addRefCP(root);
    OSG::GroupPtr gr1 = OSG::Group::create();
    OSG::beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    OSG::endEditCP(root);

    // Load the file

    NodePtr file;
    OSG::beginEditCP(dlight);
    for(i=0;i<filenames.size();i++)
    {
        file = SceneFileHandler::the().read(filenames[i],0);
        if(file != NullFC)
            dlight->addChild(file);
        else
            std::cerr << "Couldn't load file, ignoring " << filenames[i] << std::endl;
    }
	if ( filenames.size()==0 )
	{
        if(ca>0)
        {
            if(cb==-1)
                cb=ca;
            if(cc==-1)
                cc=cb;
            GeometryPtr geo=makeBoxGeo(.6,.6,.6,5,5,5);
            
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
                        geoNode=Node::create();
                        geoNode->setCore(geo);
                        node->addChild( geoNode );
                        beginEditCP(dlight);
                        dlight->addChild(node);

                        endEditCP(geoNode);
                        endEditCP(dlight);
                        endEditCP(trans);
                        endEditCP(node);
                    }
        }
        else
        {
            file = makeTorus( .5, 2, 16, 16 );
            beginEditCP(file->getCore());
            endEditCP(file->getCore());
            dlight->addChild(file);
        }
	}

    dlight->invalidateVolume();
    OSG::endEditCP(dlight);

    dlight->updateVolume();

    // should check first. ok for now.
    const OSG::BoxVolume *vol = (OSG::BoxVolume *)&dlight->getVolume();

    OSG::Vec3f min,max;
    OSG::Vec3f size;
    OSG::Pnt3f center;

    vol->getBounds(min, max);
    vol->getCenter(center);

    size = max - min;

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    // Camera

    OSG::PerspectiveCameraPtr cam = OSG::PerspectiveCamera::create();
    beginEditCP(cam);
    cam->setBeacon( b1n );
    cam->setFov( OSG::deg2rad( 60 ) );
    cam->setNear( 10 );
    cam->setFar( 50000 );
    endEditCP(cam);

    // Solid Background
    OSG::SolidBackgroundPtr bkgnd = OSG::SolidBackground::create();
    beginEditCP(bkgnd);
    bkgnd->setColor( OSG::Color3f(0,0,0) );
    endEditCP(bkgnd);

    // Viewport
    OSG::ViewportPtr vp1;
    OSG::ViewportPtr vp2;
    if(!doStereo)
    {
        vp1 = OSG::Viewport::create();
        beginEditCP(vp1);
        vp1->setCamera    ( cam );
        vp1->setBackground( bkgnd );
        vp1->setRoot      ( root );
        vp1->setSize      ( 0,0, 1,1 );
        endEditCP(vp1);
        if(multiport)
        {
            vp2 = OSG::Viewport::create();
            beginEditCP(vp2);
            vp2->setCamera    ( cam );
            vp2->setBackground( bkgnd );
            vp2->setRoot      ( root );
            vp2->setSize      ( .1, .55, .7,.95 );
            endEditCP(vp2);
        }
    }
    else
    {
        OSG::ShearedStereoCameraDecoratorPtr deco;
        // left
        deco=OSG::ShearedStereoCameraDecorator::create();
        beginEditCP(deco);
        deco->setLeftEye(true);
        deco->setEyeSeparation(eyedistance);
        deco->setDecoratee(cam);
        deco->setZeroParallaxDistance(zeroparallax);
        vp1 = OSG::Viewport::create();
        beginEditCP(vp1);
        vp1->setCamera    ( deco );
        vp1->setBackground( bkgnd );
        vp1->setRoot      ( root );
        vp1->setSize      ( 0,0, .5,1 );
        endEditCP(vp1);
        endEditCP(deco);
        // right
        deco=OSG::ShearedStereoCameraDecorator::create();
        beginEditCP(deco);
        deco->setLeftEye(false);
        deco->setEyeSeparation(eyedistance);
        deco->setDecoratee(cam);
        deco->setZeroParallaxDistance(zeroparallax);
        vp2 = OSG::Viewport::create();
        beginEditCP(vp2);
        vp2->setCamera    ( deco );
        vp2->setBackground( bkgnd );
        vp2->setRoot      ( root );
        vp2->setSize      ( .5,0,1,1 );
        endEditCP(vp2);
        endEditCP(deco);
    }

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );
    
	beginEditCP(clusterWindow);
    if(serverx>0 && servery>0)
        clusterWindow->setSize( serverx, servery );
    else
        clusterWindow->setSize( glvp[2], glvp[3] );
    clusterWindow->addPort( vp1 );

    if(multiport || doStereo)
        clusterWindow->addPort( vp2 );

    if(broadcastAddressValid == true)
    {
        clusterWindow->setBroadcastAddress(broadcastAddress);

        fprintf(stderr, "tcclient use ba %s\n", broadcastAddress.c_str());
    }

	endEditCP(clusterWindow);

    // tball

    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5),
                   min[1] + ((max[1] - min[1]) * 0.5),
                   max[2] + ( max[2] - min[2] ) * 1.5 );

    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(center);
    tball.setTranslationGen(OSG::Trackball::OSGAbsoluteTranslation);

    // run...
    std::cout << size.length() << std::endl;
    cam->setFar (size.length() * 100.0);
    cam->setNear(size.length() * 100.0 / 10000.0);
}

int main(int argc,char **argv)
{
    int i,winid;
    std::vector<char *> filenames;
    std::string connectionType = "StreamSock";
    int rows=1;
    char type='M';
    bool clientRendering=true;
    
    try
    {
        for(i=1;i<argc;i++)
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
                continue;
            }
            if(strlen(argv[i])>1 && argv[i][0]=='-')
            {
                switch(argv[i][1])
                {
                    case 'b':
                        broadcastAddress.assign(argv[i]+2);
                        broadcastAddressValid = true;
                        break;
                    case 'f':
                        filenames.push_back(argv[i]+2);
                        break;
                    case 'm':
                        connectionType="Multicast";
                        break;
                    case 'r':
                        rows=atoi(argv[i]+2);
                        break;
                    case 'C':
                        type='C';
                        break;
                    case 'F':
                        type='F';
                        break;
                    case 'P':
                        type='P';
                        break;
                    case 'M':
                        type='M';
                        break;
                    case 's':
                        doStereo=true;
                        break;
                    case 'e':
                        sscanf(argv[i]+2,"%f",&eyedistance);
                        break;
                    case 'z':
                        sscanf(argv[i]+2,"%f",&zeroparallax);
                        break;
                    case 'd':
                        clientRendering=false;
                        break;
                    case 'v':
                        multiport=true;
                        break;
                    case 'x':
                        sscanf(argv[i]+2,"%d",&serverx);
                        break;
                    case 'y':
                        sscanf(argv[i]+2,"%d",&servery);
                        break;
                    case 'a':
                        if(*(argv[i]+2))
                        {
                            animName=argv[i]+2;
                            loadAnim();
                        }
                        glutIdleFunc(display);       
                        animate=true;
                        break;
                    case 'h':
                        std::cout << argv[0] 
                                  << "-ffile -m -rrows -C -M"
                                  << std::endl;
                        std::cout << "-m  use multicast" << std::endl
                                  << "-M  multi display" << std::endl
                                  << "-r  number of display rows" << std::endl
                                  << "-C  sort-first and compose" << std::endl
                                  << "-F  sort-first" << std::endl
                                  << "-h  this msg" << std::endl
                                  << "-s  stereo" << std::endl
                                  << "-e  eye distance" << std::endl
                                  << "-z  zero parallax" << std::endl
                                  << "-d  disable client rendering"<<std::endl
                                  << "-v  use two viewports" << std::endl
                                  << "-x  server x resolution" << std::endl
                                  << "-y  server y resolution" << std::endl;
                        return 0;
                }
            }
        }
        osgInit(argc, argv);
        glutInit(&argc, argv);
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
        winid = glutCreateWindow("OpenSG Cluster Client");
        glutKeyboardFunc(key);
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);       
        glutMouseFunc(mouse);   
        glutMotionFunc(motion); 
        ract1 = RenderAction::create();
        ract2 = RenderAction::create();
        // just draw the group's volumes as wireframe, ignore geometries
        ract1->registerEnterFunction( OSG::Group::getClassType(),
                                      OSG::osgTypedFunctionFunctor2CPtrRef<
                                      OSG::Action::ResultE, 
                                      OSG::CNodePtr,
                                      OSG::Action *                       >(
                                         wireDraw));
        ract1->registerEnterFunction( OSG::Geometry::getClassType(),
                                      OSG::osgTypedFunctionFunctor2CPtrRef<
                                      OSG::Action::ResultE, 
                                      OSG::CNodePtr,
                                      OSG::Action *                       >(
                                         ignore));
        ract=ract2;

        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clearAll();
        
        // create cluster window
        switch(type)
        {
            case 'M': 
                multidisplay=MultiDisplayWindow::create();
                clusterWindow=multidisplay;
                break;
            case 'C':
                sortfirst=SortFirstWindow::create();
                beginEditCP(sortfirst);
                sortfirst->setCompose(true);
                endEditCP(sortfirst);
                clusterWindow=sortfirst;
                break;
            case 'F':
                sortfirst=SortFirstWindow::create();
                beginEditCP(sortfirst);
                sortfirst->setCompose(false);
                endEditCP(sortfirst);
                clusterWindow=sortfirst;
                break;
            case 'P':
                sortfirst=SortFirstWindow::create();
                beginEditCP(sortfirst);
                sortfirst->setCompose(false);
                endEditCP(sortfirst);
                clusterWindow=sortfirst;
                break;
        }
        beginEditCP(clusterWindow);
        {
            // set servers
            for(i=1;i<argc;i++)
            {
                if(argv[i][0]!='-' && 
                   (argv[i][0]<'0' || argv[i][0]>'9'))
                {
                    clusterWindow->getServers().push_back(argv[i]);
                }
            }
            switch(type)
            {
                case 'M': 
                    multidisplay->setHServers(
                        clusterWindow->getServers().size()/rows);
                    multidisplay->setVServers(
                        rows);
                    break;
            }
        }
        endEditCP(clusterWindow);

        // create client window
        clientWindow=GLUTWindow::create();
        clientWindow->setId(winid);
        clientWindow->init();

        // init scene graph
        init(filenames);

        // init client
        clusterWindow->setConnectionType(connectionType);
        if(clientRendering)
        {
            clusterWindow->setClientWindow(clientWindow);
        }
        clusterWindow->init();

        glutMainLoop();
    } 
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SLOG << e.what() << std::endl;
    }
    return 0;
}







