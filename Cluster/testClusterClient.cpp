#include <GL/glut.h>
#include <GL/glu.h>
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

Trackball             tball;
int                   mouseb = 0;
int                   lastx=0, lasty=0;
int                   winwidth=0, winheight=0;
NodePtr		          root;
TransformPtr          cam_trans;
PerspectiveCameraPtr  cam;
ClusterWindowPtr      clusterWindow;
RenderAction         *ract,*ract1,*ract2;
GLUTWindowPtr         clientWindow;
SortFirstWindowPtr    sortfirst;
MultiDisplayWindowPtr multidisplay;
bool                  animate=false;
bool                  multiport=false;
float                 ca=-1,cb=-1,cc=-1;
bool                  doStereo=false;
float                 eyedistance=1,zeroparallax=10;

void showText(int x, int y, char *string)
{
  int len, i;
#ifdef WIN32
  void *font = 6;
#else
  void *font = GLUT_BITMAP_TIMES_ROMAN_24;
#endif
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_COLOR_MATERIAL);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0,clientWindow->getWidth(),0,clientWindow->getHeight());
  glDisable(GL_DEPTH_TEST);  
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPopAttrib();
}

void display(void)
{
    static int  count=0;
    static Time start;

    if(count==0)
        start=getSystemTime();

	beginEditCP( cam_trans );
    cam_trans->getSFMatrix()->setValue( tball.getFullTrackballMatrix() );
	endEditCP( cam_trans );
    try
    {
        clusterWindow->render( ract );	
        // clear changelist from prototypes
        OSG::Thread::getCurrentChangeList()->clearAll();
	}
    catch(exception &e)
    {
        cout << e.what() << endl;
        exit(0);
    }
    
    count++;
    if(count==10)
    {
        if(animate)
            printf("FPS %8.3f\n",count/(getSystemTime() - start));
        count=0;
    }
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
        case 27:	// should kill the clients here
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

void init(vector<char *> &filenames)
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
            cerr << "Couldn't load file, ignoring " << filenames[i] << endl;
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

    cout << "Volume: from " << min << " to " << max << endl;

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
    clusterWindow->setSize( glvp[2], glvp[3] );
    clusterWindow->addPort( vp1 );
    if(multiport || doStereo)
        clusterWindow->addPort( vp2 );
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
    cout << size.length() << endl;
    cam->setFar (size.length() * 100.0);
    cam->setNear(size.length() * 100.0 / 10000.0);
}

int main(int argc,char **argv)
{
    int i,winid;
    vector<char *> filenames;
    string connectionType = "StreamSock";
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
                    case 'h':
                        cout << argv[0] 
                             << "-ffile -m -rrows -C -M"
                             << endl;
                        cout << "-m  use multicast" << endl
                             << "-M  multi display" << endl
                             << "-r  number of display rows" << endl
                             << "-C  sort-first and compose" << endl
                             << "-F  sort-first" << endl
                             << "-h  this msg" << endl
                             << "-s  stereo" << endl
                             << "-e  eye distance" << endl
                             << "-z  zero parallax" << endl
                             << "-d  disable client rendering" << endl
                             << "-v  use two viewports" << endl;
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
    catch(exception &e)
    {
        SLOG << e.what() << endl;
    }
    return 0;
}







