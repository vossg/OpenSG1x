
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGPerspectiveCamera.h>
#include <OSGStereoBufferViewport.h>
#include <OSGProjectionCameraDecorator.h>

#include <OSGSimpleTexturedMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGBlendChunk.h>
#include <OSGGrabForeground.h>
#include <OSGGroup.h>
#include <OSGMatrixUtility.h>
#include <OSGStereoBufferViewport.h>
#include <OSGImage.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

Real32 ed = 10;

TransformPtr viewtrans,usertrans;
Matrix usermatrix;

const int maxplanes = 12;
const int nplanes = 1;

ProjectionCameraDecoratorPtr decos[maxplanes];
TextureChunkPtr textures[maxplanes];

PerspectiveCameraPtr viewcam, usercam;

int width,height;
    
int nports = nplanes;

// redraw the window
void display(void)
{   
    // notify the textures of image changes
    
    for(UInt16 i = 0; i < nports; i++)
    {
        beginEditCP(textures[i]);
        textures[i]->setImage(textures[i]->getImage());
        endEditCP(textures[i]);
    }
    
    // HACK   
    beginEditCP(usertrans);
    usertrans->setMatrix(Matrix::identity());
    endEditCP  (usertrans);
    
    
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    width = w;
    height = h;
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
    switch(k)
    {
    case 27:    exit(1);
    case 'z':   ed /= 1.1;
                break;
    case 'x':   ed *= 1.1;
                break;         
    }
    
    std::cout << " ED:" << ed << std::endl;
    
    for (int i = 0; i < nports; ++i)
    {
        beginEditCP(decos[i]);
        decos[i]->setEyeSeparation(ed);
        endEditCP  (decos[i]);
    }
 }

void addPort(Pnt3f *vpproj, 
             Pnt4f vppos,
             bool left,
             ViewportPtr v,
             NodePtr projgeo,
             NodePtr tnode,
             NodePtr root,
             BackgroundPtr back,
             ProjectionCameraDecoratorPtr &deco,
             TextureChunkPtr &tex
            )
{
        ProjectionCameraDecoratorPtr d = ProjectionCameraDecorator::create();
        
        deco = d;
        
        beginEditCP(d);
        d->setEyeSeparation(ed);
        d->setLeftEye(left);  
        d->setUser(tnode);  
        d->setDecoratee(usercam);  
        d->getSurface().push_back(vpproj[0]);
        d->getSurface().push_back(vpproj[1]);
        d->getSurface().push_back(vpproj[2]);
        d->getSurface().push_back(vpproj[3]);
        endEditCP  (d);

        UInt32 imgw,imgh;
        
        imgw = osgnextpower2((UInt32)(vppos[2] - vppos[0]));
        imgh = osgnextpower2((UInt32)(vppos[3] - vppos[1]));
        
        ImagePtr image = Image::create();
        image->set(Image::OSG_RGB_PF, imgw, imgh);
        
        GrabForegroundPtr fg = GrabForeground::create();
        beginEditCP(fg);
        fg->setImage(image);        
        endEditCP  (fg);      
        
        beginEditCP(v);
        v->setLeft(vppos[0]);
        v->setRight(vppos[2]);
        v->setBottom(vppos[1]);
        v->setTop(vppos[3]);
        v->setCamera(d);
        v->setBackground(back);
        v->getForegrounds().push_back(fg);
        v->setRoot(root);        
        endEditCP  (v);
        
        // create the projection geometry
        
        tex = TextureChunk::create();
        beginEditCP(tex);  
        tex->setImage(image);
        tex->setScale(false);
        tex->setMagFilter(GL_NEAREST);
        tex->setEnvMode  (GL_REPLACE);            
        endEditCP  (tex);        
        
        BlendChunkPtr bl = BlendChunk::create();
        beginEditCP(bl);        
        bl->setSrcFactor(GL_ONE);
#if GL_EXT_blend_color
        bl->setDestFactor(GL_CONSTANT_ALPHA);
        bl->setColor(Color4f(0,0,0,.5));
#else
        bl->setDestFactor(GL_ONE);
#endif
        endEditCP(bl);
        
        SimpleMaterialPtr mat = SimpleMaterial::create();
        beginEditCP(mat);        
        mat->setLit(false);
        // mat->addChunk(bl);
        mat->addChunk(tex);
        endEditCP(mat);

        NodePtr gnode = Node::create();
        GeometryPtr geo = Geometry::create();

        beginEditCP(gnode);
        gnode->setCore( geo );
        endEditCP(gnode);

        GeoPositions3fPtr pnts = GeoPositions3f::create();

        beginEditCP(pnts);
        pnts->getFieldPtr()->push_back(vpproj[0]);
        pnts->getFieldPtr()->push_back(vpproj[1]);
        pnts->getFieldPtr()->push_back(vpproj[2]);
        pnts->getFieldPtr()->push_back(vpproj[3]);
        endEditCP(pnts);

        GeoTexCoords2fPtr texs = GeoTexCoords2f::create();
        beginEditCP(texs);
        texs->push_back( Vec2f( 0, 0 ) );
        texs->push_back( Vec2f( (vppos[2] - vppos[0])/(Real32)imgw, 0 ) );
        texs->push_back( Vec2f( (vppos[2] - vppos[0])/(Real32)imgw, 
                               (vppos[3] - vppos[1])/(Real32)imgh ) );
        texs->push_back( Vec2f( 0, (vppos[3] - vppos[1])/(Real32)imgh ) );
        endEditCP(texs);

        GeoPTypesPtr type = GeoPTypesUI8::create();     
        beginEditCP(type);
        type->push_back( GL_QUADS );
        endEditCP(type);

        beginEditCP(geo);
        geo->setTexCoords(texs);
        geo->setPositions(pnts);
        geo->setTypes(type);
        geo->setMaterial(mat);
        endEditCP(geo);

        projgeo->addChild(gnode);
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    bool stereobuffer = false;
    if(argc >= 2 && !strcmp(argv[1],"-s"))
    {
        stereobuffer = true;
        argc--;
        argv++;
    }
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
                        (stereobuffer?GLUT_STEREO:0) );
    
    glutInitWindowSize(540,500);
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();

    // create the scene
    NodePtr scene;
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        scene = makeTorus(.5, 3, 16, 16);
    }
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // now crete the other vps
    ViewportPtr vp = pwin->getPort(0);
    
    // camera to define viewer position/orientation
    usercam = PerspectiveCameraPtr::dcast(vp->getCamera());
       
    Navigator *nav = mgr->getNavigator();
    nav->setAt(Pnt3f(0,0,0));
    nav->setDistance(1.5);
    
    // create the decorators and the second viewport

    Pnt4f vppos[6] = {  Pnt4f(0,0,179,164),  // left
                        Pnt4f(360,0,539,164),  // right
                        Pnt4f(180,0,359,164),  // middle
                     };
                     
    Pnt4f resultview(0,165,1,1);  // result view
    
#if 0
    Pnt3f vpproj[3][4] = { 
        { Pnt3f(-337.739, -146.218, -36.4828), 
          Pnt3f(-143.808, -146.218, -307.763), 
          Pnt3f(-118.215, 140.118, -289.467), 
          Pnt3f(-312.146, 140.118, -18.187)},
        { Pnt3f(-166.735, -146.218, -295.97), 
          Pnt3f(166.735, -146.218, -295.97), 
          Pnt3f(166.735, 140.118, -264.509), 
          Pnt3f(-166.735, 140.118, -264.509)},
        { Pnt3f(143.808, -146.218, -307.763), 
          Pnt3f(337.739, -146.218, -36.4828), 
          Pnt3f(312.146, 140.118, -18.187), 
          Pnt3f(118.215, 140.118, -289.467)}
        };
#else

    Pnt3f vpproj[3][4] = 
    { 
        { Pnt3f(-166.735, -146.218, -264.509), 
          Pnt3f(166.735, -146.218, -264.509), 
          Pnt3f(166.735, 140.118, -295.97), 
          Pnt3f(-166.735, 140.118, -295.97)},
        { Pnt3f(118.215, -146.218, -289.467), 
          Pnt3f(312.146, -146.218, -18.187), 
          Pnt3f(337.739, 140.118, -36.4828), 
          Pnt3f(143.808, 140.118, -307.763)},
        { Pnt3f(-312.146, -146.218, -18.187), 
          Pnt3f(-118.215, -146.218, -289.467), 
          Pnt3f(-143.808, 140.118, -307.763), 
          Pnt3f(-337.739, 140.118, -36.4828)},
    };
#endif

    // the camera to move the user
    
    usermatrix = Matrix::identity();

    usertrans = Transform::create();   
    beginEditCP(usertrans);
    usertrans->setMatrix(Matrix::identity());
    endEditCP  (usertrans);
    
    NodePtr tnode = Node::create();
    beginEditCP(tnode);
    tnode->setCore(usertrans);
    endEditCP  (tnode);
    
    beginEditCP(usercam->getBeacon());
    usercam->getBeacon()->addChild(tnode);
    endEditCP  (usercam->getBeacon());    
 
    // now create the viewports/geometries/textures
    
    NodePtr projgeoleft = Node::create(),
            projgeoright = Node::create();
    
    GroupPtr glcore = Group::create();
    beginEditCP(projgeoleft);
    projgeoleft->setCore(glcore);
    
    GroupPtr grcore = Group::create();
    beginEditCP(projgeoright);
    projgeoright->setCore(grcore);
    
    beginEditCP(pwin); 
    pwin->subPort(vp);  
    
    UInt16 i, ideco;
    
    if(!stereobuffer)
    {
        for(i = 0, ideco = 0; i < nplanes; ++i, ++ideco)
        {    
            ViewportPtr v = Viewport::create();

            addPort(vpproj[i], vppos[i], true, v,
                    projgeoleft, tnode, vp->getRoot(), vp->getBackground(), 
                    decos[ideco], textures[ideco]);

            pwin->addPort(v);
        }
    }
    else
    {
        for(i = 0, ideco = 0; i < nplanes; ++i, ++ideco)
        {    
            StereoBufferViewportPtr v = StereoBufferViewport::create();

            addPort(vpproj[i], vppos[i], true, v,
                    projgeoleft, tnode, vp->getRoot(), vp->getBackground(), 
                    decos[ideco], textures[ideco]);
            
            beginEditCP(v);
            v->setLeftBuffer(true);
            v->setRightBuffer(false);         
            endEditCP(v);
            
            pwin->addPort(v);
            
            ++ideco;
            
            v = StereoBufferViewport::create();

            addPort(vpproj[i], vppos[i], false, v,
                    projgeoright, tnode, vp->getRoot(), vp->getBackground(), 
                    decos[ideco], textures[ideco]);
            
            beginEditCP(v);
            v->setLeftBuffer(false);
            v->setRightBuffer(true);         
            endEditCP(v);
            
            pwin->addPort(v);
        }
    }
    
    nports = ideco;
    
    endEditCP(projgeoleft);
    endEditCP(projgeoright);
 
    // the camera to move the view of the projection system

    viewcam = PerspectiveCamera::create();
    beginEditCP(viewcam);
    viewcam->setNear(1);
    viewcam->setFar(2000);
    viewcam->setFov(90);  
    endEditCP(viewcam);
    
    viewtrans = Transform::create();   
    beginEditCP(viewtrans);
    Matrix m;
    MatrixLookAt(m, 0,0,-100, 0,0,-200, 0,1,0);
    viewtrans->setMatrix(m);
    endEditCP  (viewtrans);
    
    tnode = Node::create();
    beginEditCP(tnode);
    tnode->setCore(viewtrans);
    endEditCP  (tnode);
    
    beginEditCP(viewcam);
    viewcam->setBeacon(tnode);
    endEditCP  (viewcam);
    
    // and the result viewport
   
    if(!stereobuffer)
    {
        ViewportPtr v = Viewport::create();

        beginEditCP(v);
        v->setLeft(resultview[0]);
        v->setRight(resultview[2]);
        v->setBottom(resultview[1]);
        v->setTop(resultview[3]);
        v->setCamera(viewcam);
        v->setBackground(vp->getBackground());
        v->setRoot(projgeoleft);
        endEditCP  (v);

        pwin->addPort(v);  
    }
    else
    {
        StereoBufferViewportPtr v = StereoBufferViewport::create();

        beginEditCP(v);
        v->setLeft(resultview[0]);
        v->setRight(resultview[2]);
        v->setBottom(resultview[1]);
        v->setTop(resultview[3]);
        v->setCamera(viewcam);
        v->setBackground(vp->getBackground());
        v->setRoot(projgeoleft);
        v->setLeftBuffer(false);
        v->setRightBuffer(true);         
        endEditCP  (v);

        pwin->addPort(v);  
 
        v = StereoBufferViewport::create();

        beginEditCP(v);
        v->setLeft(resultview[0]);
        v->setRight(resultview[2]);
        v->setBottom(resultview[1]);
        v->setTop(resultview[3]);
        v->setCamera(viewcam);
        v->setBackground(vp->getBackground());
        v->setRoot(projgeoright);
        v->setLeftBuffer(true);
        v->setRightBuffer(false);         
        endEditCP  (v);

        pwin->addPort(v);  
    }
    
    endEditCP  (pwin);
    
    // make it notice the changes
    mgr->setWindow(pwin );
    
    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
