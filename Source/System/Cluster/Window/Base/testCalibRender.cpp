// Minimalistic OpenSG program

#include <fstream>

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

#include <OSGSolidBackground.h>

#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>

#include <OSGSceneFileHandler.h>
#include <OSGGraphOpSeq.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGStripeGraphOp.h>

#include <OSGDisplayCalibration.h>
#include <OSGMultiDisplayWindow.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

int mode;
SimpleSceneManager *mgr;
DisplayCalibrationPtr calib;
NodePtr scene = NullFC;
bool showTestImage = false;

void cushion(float from[2],float to[2],
             float center[2],
             float distortion,
             int resX=50,int resY=50)
{
    float x,y,sx,sy,arg;
    float v,rr,xp,yp,phi;
    float width  = to[0] - from[0];
    float height = to[1] - from[1];
    int cx,cy;

    calib->setGridWidth(resX);
    calib->setGridHeight(resY);
    for(sy=from[1],cy=resY ; cy ; sy += height / (resY-1),cy--)
    {
        for(sx=from[0],cx=resX ; cx ; sx += width / (resX-1),cx--)
        {
            x = sx - center[0];
            y = sy - center[1];
            
            // arg := Abstand von optischer Achse/distortion
            arg = sqrt(x*x + y*y) / distortion;  
            // Bei Optiken mit Tonnen-Verzerrung stuende hier v:=tan(arg)
            v = atan(arg);
            // rr : Neu berechneter Abstand von optischer Achse
            rr = distortion * v; 
            // Bestimmung des Winkels zur
            if(x != 0) 
                phi = atan(y/x);
            // in rechtwinkelige Koordinaten
            if(x < 0) 
                phi = phi + Pi;
            if(x == 0) 
            {
                if(y > 0) 
                    phi = Pi / 2;
                else
                    phi = -Pi / 2;
            }
            //xp,yp: Koordinaten des abgebildeten Punktes
            xp = rr * cos(phi) + center[0];
            yp = rr * sin(phi) + center[1];

            calib->getGrid().push_back(Vec2f(xp,yp));
        }
    }
}

// Standard GLUT callback functions
void display( void )
{
    mgr->getNavigator()->updateCameraTransformation();
    mgr->getWindow()->activate();
    mgr->getWindow()->frameInit();

    if(showTestImage)
    {
        int w=mgr->getWindow()->getWidth();
        int h=mgr->getWindow()->getHeight();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,w,0,h);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);   
        glVertex2f(w-1,0);   
        glVertex2f(w-1,h-1);   
        glVertex2f(0,h-1);   
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(w/2,0);   
        glVertex2f(w-1,h/2);   
        glVertex2f(w/2,h-1);   
        glVertex2f(0,h/2);   
        glEnd();
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(w/2+h/6, h/2+h/6);
        glVertex2f(w/2+h/6, h/2-h/6);
        glVertex2f(w/2-h/6, h/2-h/6);
        glVertex2f(w/2-h/6, h/2+h/6);
        glEnd();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,1,0,1);
        glMatrixMode(GL_MODELVIEW);
        float step,x,y;
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        step = 1.0/16;
        for(y=step ; y < 1-step/2 ; y+=step)
        {
            glVertex2f(0,y);   
            glVertex2f(1.0,y);   
        }
        for(x=step ; x < 1-step/2 ; x+=step)
        {
            glVertex2f(x,0);   
            glVertex2f(x,1.0);   
        }
        glEnd();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        step = 1.0/8;
        for(y=step ; y < 1-step/2 ; y+=step)
        {
            glVertex2f(0,y);   
            glVertex2f(1.0,y);   
        }
        for(x=step ; x < 1-step/2 ; x+=step)
        {
            glVertex2f(x,0);   
            glVertex2f(x,1.0);   
        }
        glEnd();
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        step = 1.0/4;
        for(y=step ; y < 1-step/2 ; y+=step)
        {
            glVertex2f(0,y);   
            glVertex2f(1.0,y);   
        }
        for(x=step ; x < 1-step/2 ; x+=step)
        {
            glVertex2f(x,0);   
            glVertex2f(x,1.0);   
        }
        glEnd();
    }
    else
    {
        mgr->getWindow()->renderAllViewports((RenderActionBase*)mgr->getAction());
    }

    calib->calibrate(mgr->getWindow()->getPort()[0],(RenderActionBase*)mgr->getAction());
    mgr->getWindow()->swap();
    mgr->getWindow()->frameExit();

    if(mode==4)
    {
        beginEditCP(calib);
        Vec2f pos = calib->getGrid()[4];
        pos[0] = fmod(pos[0]+.01,1);
        pos[1] = fmod(pos[1]+.01,1);
        calib->getGrid()[4] = pos;
        endEditCP(calib);
    }
}

void reshape( int w, int h )
{
    printf("%d %d\n",w,h);
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
key(unsigned char key, int , int )
{
    switch(key)
    {
    case 27:    exit(1);
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
    case 'q':   mgr->setStatistics(true);
                break;
    case 'w':   mgr->setStatistics(false);
                break;
    case '1':   
        mode=1;
        beginEditCP(calib);
        calib->setGridWidth(2);
        calib->setGridHeight(2);
        calib->getGrid().clear();
        calib->getGrid().push_back(Vec2f(0,0));
        calib->getGrid().push_back(Vec2f(1,0));
        calib->getGrid().push_back(Vec2f(0,1));
        calib->getGrid().push_back(Vec2f(1,1));
        endEditCP(calib);
        break;
    case '2':   
        mode=2;
        beginEditCP(calib);
        calib->setGridWidth(2);
        calib->setGridHeight(2);
        calib->getGrid().clear();
        calib->getGrid().push_back(Vec2f(0.1,0.1));
        calib->getGrid().push_back(Vec2f(0.9,0.1));
        calib->getGrid().push_back(Vec2f(0.1,0.9));
        calib->getGrid().push_back(Vec2f(0.9,0.9));
        endEditCP(calib);
        break;
    case '3':
    {
        mode=3;
        beginEditCP(calib);
        calib->setGridWidth(201);
        calib->setGridHeight(201);
        calib->getGrid().clear();
        int x,y;
        float xx,yy;
        for(y=-100 ; y<=100 ; ++y)
            for(x=-100 ; x<=100 ; ++x)
            {
                xx = x/200.0*sqrtf(100.0f*100.0f-y*y)/100.0f + .5f;
                yy = (y+100.0f)/200.0f;
                calib->getGrid().push_back(Vec2f(xx,yy));
            }
        endEditCP(calib);
    }
    break;
    case '4':
    {
        mode=4;
        beginEditCP(calib);
        calib->setGridWidth(3);
        calib->setGridHeight(3);
        calib->getGrid().clear();
        int x,y;
        float xx,yy;
        for(y=0 ; y<=2 ; ++y)
            for(x=0 ; x<=2 ; ++x)
                calib->getGrid().push_back(Vec2f(x/2.0,y/2.0));
        endEditCP(calib);
    }
    break;
    case 'd':
        beginEditCP(calib);
        calib->setScaleDown(.1);
        endEditCP(calib);
        break;
    case 'D':
        beginEditCP(calib);
        calib->setScaleDown(1);
        endEditCP(calib);
        break;
    case 'c':
        beginEditCP(calib);
        calib->setColorMatrix(Matrix(0,0,1,0,
                                     1,0,0,0,
                                     0,1,0,0,
                                     0,0,0,1));
        endEditCP(calib);
        break;
     case 'C':
        beginEditCP(calib);
        calib->setColorMatrix(Matrix(1,0,0,0,
                                     0,1,0,0,
                                     0,0,1,0,
                                     0,0,0,1));
        endEditCP(calib);
        break;
     case ' ':
         showTestImage = !showTestImage;         
    }
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    float from[2]       = { 100,100 };
    float to[2]         = { 1180,924 };
    float center[2]     = { 640,512 };
    float distortion    = 5250;
    int   resX=20,resY=20;
    MultiDisplayWindowPtr clusterWindow;

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutFullScreen();

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
    clusterWindow = MultiDisplayWindow::create();
    calib = DisplayCalibration::create();
    for(int a=1 ; a<argc ; ++a)
    {
        if(strcmp(argv[a] + strlen(argv[a]) - 4,".xml") == 0 ||
           strcmp(argv[a] + strlen(argv[a]) - 4,".XML") == 0)
        {
            std::ifstream in(argv[a]);
            if(in) 
                clusterWindow->loadCalibration(in);
            continue;
        }
        if(argv[a][0] != '-')
        {
            scene = SceneFileHandler::the().read(argv[a]);
            continue;
        }        
        switch(argv[a][1])
        {
            case 'c':
                if(sscanf(argv[a]+2,"%f,%f,%f,%f,%f,%f,%f",
                          &from[0],&from[1],
                          &to[0],&to[1],
                          &center[0],&center[1],
                          &distortion) < 7)
                {
                    printf("%s fromX,fromY,toX,toY,centerX,centerY,distortion\n",argv[0]);
                    printf("%s 35,81,1365,969,699,368,5250\n",argv[0]);
                    printf("%s 35,81,1365,969,699,687,5250\n",argv[0]);
                }
                else
                {
                    printf("cushion\n");
                    beginEditCP(calib);
                    cushion(from,to,
                            center,
                            distortion,
                            resX,resY);
                    endEditCP(calib);
                }
        }
    }        
    if(scene == NullFC)
    {
        std::cerr << "Error loading scene!" << std::endl;
        scene = makeTorus( .5, 2, 16, 16 );
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );
    mgr->showAll();

    WindowPtr win = mgr->getWindow();
    endEditCP(win);

    if(clusterWindow->getCalibration().size() > 0)
        calib = clusterWindow->getCalibration()[0];
    
    // GLUT main loop
    glutMainLoop();
    
    return 0;
}
