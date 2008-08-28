// OpenSG Tutorial Example: Identification buffer
//
// This tutorial shows how to use the identification color technique so as to
// identify objects in a fast way. ( get his NodePtr )
//
//  - This method is view dependant (we do picking only from the viewpoint), but you can specify
//      your viewpoint with setCamera(). 
//  - This method doesn't handle transprency.
//  - This method doesn't handle anti-aliasing, this can lead to some imperfections in 
//      identification.
//
// If you need more, it is possible to retreive the 3D point by using Z-buffer information.
// It's also possible to send a ray throught the geometry of the identified object so as to
// retrieve the corresponding triangle. (Sending ray through the whole scene is really 
// computationaly expensive in OpenSG).
//
// To do that we add a switchMaterial to each geometry. In this way, we can choose between
// the normal material, and the color identification one. Then when requested, we render
// the scene to a RAM-buffer (with the GrabForeground method), and call the getObject() 
// method on it.
//
// Note that this method is suitable for high amount of getObject() calls over a single
// frame.
//
// Use Space to pick.
//

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGGrabForeground.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSwitchMaterial.h>

#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGChunkMaterial.h>

#include <map>
#include <list>

OSG_USING_NAMESPACE
using namespace std;

struct color_compare {
  bool operator()(Color4ub s1, Color4ub s2) const  {
      return (unsigned int)s1.getRGBA() < (unsigned int)s2.getRGBA();
  }
};


class IDbuffer
{
public:
    IDbuffer(void)
    {
        _ID_buffer=NULL;
        
        // We fix the Sky color to black
        SolidBackgroundPtr _solidBkg = SolidBackground::create();
        beginEditCP(_solidBkg);
            _solidBkg->setColor(Color3f(0,0,0));
        endEditCP(_solidBkg);

        _ID_viewport = Viewport::create();
        beginEditCP(_ID_viewport);
            _ID_viewport->setBackground(_solidBkg);
            _ID_viewport->setSize(0,0,1,1);
        endEditCP(_ID_viewport);

        _window = PassiveWindow::create();
        _window->addPort(_ID_viewport);

        _ID_renderAction = RenderAction::create();

        // These parameters depends of your implementation. Use the sames as in your project.
        _ID_renderAction->setAutoFrustum(true);
        _ID_renderAction->setOcclusionCulling(true);
        _ID_renderAction->setOcclusionCullingMode(RenderAction::OcclusionHierarchicalMultiFrame);

        initColors();
    }

    ~IDbuffer(void){
    }

    void    setRoot (const NodePtr &value)
    {
        _switchs.clear();
        convertToColorIdentificationSwitchable(value);
        beginEditCP(_ID_viewport);
            _ID_viewport->setRoot(value);
        endEditCP(_ID_viewport);
    }

    void     setCamera (const CameraPtr &value)
    {
        beginEditCP(_ID_viewport);
            _ID_viewport->setCamera(value);
        endEditCP(_ID_viewport);
    }

    NodePtr    getSky(void) 
    {
        return _sky;
    }

    NodePtr    get_object(int x, int y)
    {
        if(x>=_w || y >=_h || _ID_buffer==NULL)
            return NullFC;
        y = _h - y;
        // Once rendered, we check in the buffer to get the Object ID color.
        Color4ub c = Color4ub(    _ID_buffer[4*(y*_w+x)],
                                _ID_buffer[4*(y*_w+x)+1],
                                _ID_buffer[4*(y*_w+x)+2],
                                _ID_buffer[4*(y*_w+x)+3] );
        // And we find the corresponding NodePtr.
        map<Color4ub, NodePtr,color_compare>::iterator i = _node_index.find(c);
        if( i != _node_index.end() ){
            return (*i).second;
        }else{
            return NullFC;
        }
    }

    void reshape(int x, int y)
    {
        _w=x;
        _h=y;
        _window->resize(x,y);
    }

    void    update_render_GrabForeGround()
    {
        // Setup the GrabForeground
        _grabber = GrabForeground::create();
        beginEditCP(_grabber);
            ImagePtr img = Image::create();
            beginEditCP(img);
                img->set(GL_RGBA,_w,_h);
            endEditCP(img);
            _grabber->setImage(img);
            _grabber->setAutoResize(false);
            _grabber->setActive(false);
        endEditCP(_grabber);

        // Putting it to the viewport
        _window->getPort(0)->editMFForegrounds()->push_back(_grabber);

        // We toggle the switch material so as to render identification colors.
        switchToIDbuffer();

        beginEditCP(_grabber);
            _grabber->setActive(true);
        endEditCP(_grabber);

        // We render to the grabber
        _window->render(_ID_renderAction);

        beginEditCP(_grabber);
            _grabber->setActive(false);
        endEditCP(_grabber);
        
        // We get the data back
        if(_grabber->getImage()->getData() != NULL){
            _ID_buffer = _grabber->getImage()->editData();
        }

        // We toggle to standard materials
        switchToNormal();

        // we remove the Grabber
        MFForegroundPtr::iterator i =_window->getPort(0)->editMFForegrounds()->find(_grabber);
        if( i != _window->getPort(0)->editMFForegrounds()->end() ){
            _window->getPort(0)->editMFForegrounds()->erase(i);
        }
    }

private:
    // Methods
    void        initColors()
    {
        ci = 255;
        cj = 255;
        ck = 255;

        _sky = Node::create();
        addRefCP(_sky);
        Color4ub c = Color4ub(0,0,0,255);
        _node_index[c] = _sky;
    }

    Color4ub    create_new_color()
    {
        // With this, we are ready for 255^3 objects.
        if(ci > 1)
        {
            ci--;
        }
        else if(cj > 1)
        {
            cj--;
            ci = 255;
        }
        else if(ck > 1)
        {
            ck--;
            ci = cj = 255;
        }
        else
        {
            cerr << "Cdrawing::create_new_color()  NO MORE COLOR FREE !!!! TOO MANY OBJECTS ... Gloups " << endl;
            // Note that we can extend to 255^4 objects with the alpha channel
        }
        return Color4ub(ci,cj,ck,255);
        // Note that the color (0,0,0,255) is reserved so as to identify the sky
    }

    void        convertToColorIdentificationSwitchable(const NodePtr root)
    {
        // This is a recursive traversal of the Scene Graph, so as to replace
        // each material by a SwitchMaterial, in wich we put the normal one on one
        // side, and the color identification one in other side.
        UInt32 children = root->getNChildren();

        if( root->getCore()->getType().isDerivedFrom(MaterialGroup::getClassType()) )
        {
            // Need to turn off material groups, as they would override our
            // geo-specific materials
            // Just record them here.
            
            MaterialGroupPtr mg = MaterialGroupPtr::dcast(root->getCore());

            _mgswitchs.push_back(pair<MaterialGroupPtr,MaterialPtr>(mg,NullFC));            
        }
        
        if( root->getCore()->getType().isDerivedFrom(Geometry::getClassType()) )
        {

            GeometryPtr geo = GeometryPtr::dcast(root->getCore());

            // If we get a Geometry, we replace it by a switch, 
            // we add this geometry a SwitchMaterial, with its original material
            // in one case, and a chunkmaterial corresponding to the node ID in the other.
            Color4ub c = create_new_color();
            Color4f cf;
            cf.setRGBA(c.getRGBA());
            // We add the associated pair color/node to the map
            //_node_index[c] = root;
            _node_index [c] = root;

            PolygonChunkPtr   pc = PolygonChunk::create();
            beginEditCP(pc);
                pc->setSmooth(false);
            endEditCP(pc);

            MaterialChunkPtr  mc = MaterialChunk::create();
            beginEditCP(mc);
                mc->setLit(false);    
                mc->setEmission(cf);
                mc->setDiffuse(cf);
            endEditCP(mc);

            ChunkMaterialPtr  cm = ChunkMaterial::create();
            beginEditCP(cm);
                cm->addChunk(pc);
                cm->addChunk(mc);
            endEditCP(cm);

            MaterialPtr mat = geo->getMaterial();

            SwitchMaterialPtr sw = SwitchMaterial::create();

            beginEditCP(sw);
                sw->addMaterial(mat);        // Choice 0
                sw->addMaterial(cm);        // Choice 1
            endEditCP(sw);        

            beginEditCP(geo, Geometry::MaterialFieldMask);
                geo->setMaterial(sw);
            endEditCP(geo, Geometry::MaterialFieldMask);

            _switchs.push_back(sw);
        }
        
        // check all children
        for (int i = 0; i < children; i++)
        {
            convertToColorIdentificationSwitchable(root->getChild(i));
        }
    }

    // Toggles to color identification
    void        switchToIDbuffer(void)
    {
        list<SwitchMaterialPtr>::iterator i = _switchs.begin();
        while(i!=_switchs.end()){
            beginEditCP((*i), SwitchMaterial::ChoiceFieldMask);
            (*i)->setChoice(1);
            endEditCP((*i), SwitchMaterial::ChoiceFieldMask);
            i++;
        }
        list<pair<MaterialGroupPtr,MaterialPtr> >::iterator j = _mgswitchs.begin();
        while(j!=_mgswitchs.end()){
            (*j).second = (*j).first->getMaterial();
            beginEditCP((*j).first, MaterialGroup::MaterialFieldMask);
            (*j).first->setMaterial(NullFC);
            endEditCP((*j).first, MaterialGroup::MaterialFieldMask);
            j++;
        }
    }

    // Toggles to normal materials.
    void        switchToNormal(void)
    {
        list<SwitchMaterialPtr>::iterator i = _switchs.begin();
        while(i!=_switchs.end()){
            beginEditCP((*i), SwitchMaterial::ChoiceFieldMask);
            (*i)->setChoice(0);
            endEditCP((*i), SwitchMaterial::ChoiceFieldMask);
            i++;
        }
        list<pair<MaterialGroupPtr,MaterialPtr> >::iterator j = _mgswitchs.begin();
        while(j!=_mgswitchs.end()){;
            beginEditCP((*j).first, MaterialGroup::MaterialFieldMask);
            (*j).first->setMaterial((*j).second);
            endEditCP((*j).first, MaterialGroup::MaterialFieldMask);
            j++;
        }
    }

    // Variables
    GrabForegroundPtr        _grabber;
    ViewportPtr                _ID_viewport;
    RenderAction*            _ID_renderAction;
    PassiveWindowPtr        _window;
    SolidBackgroundPtr        _solidBkg;        // Sky color is black
    NodePtr                    _sky;

    list<SwitchMaterialPtr> _switchs;        // Switchs to change from normal to ID material
    list<pair<MaterialGroupPtr,MaterialPtr> > _mgswitchs;

    // List of used colors for Identification
    map<Color4ub, NodePtr,color_compare>    _node_index;    

    UInt8*                    _ID_buffer;        // Ram version of the ID buffer
    int                        _w, _h;            // buffer size    

    int ci,cj,ck;    // for colors generations
};

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
// The file root node, needed for intersection
NodePtr fileroot;
// The points used for visualising the ray and hit object
GeoPositions3fPtr isectPoints;
// The visualisation geometry, needed for update.
GeometryPtr testgeocore;

IDbuffer*    _idbuff;



// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            OSG::osgExit();
            exit(0);
        }
        break;

        case ' ':   // check the object under the clicked pixel
                {
                    _idbuff->update_render_GrabForeGround();
                    NodePtr    found = _idbuff->get_object(x,y);  

                    if( found == _idbuff->getSky() )
                    {
                        std::cout<<"Picking : Sky found"<<std::endl;
                    }
                    else if( found != NullFC )
                    {
                        const Char8 *n = getName(found);
                        if(n == NULL)
                            n = "Unnamed";
                            
                        std::cout <<"Picking : Object found : " 
                            << n << " (node="<< found << ")" << std::endl;
                    }
                    else
                    {
                        std::cerr<<"Problem..."<< std::endl;
                    }

                }
                break;
    }
}

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

    // The scene group
    
    NodePtr  scene = Node::create();
    GroupPtr g     = Group::create();
    
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    scene->setCore(g);
    
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the().getSuffixList(suffixes);
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        fileroot = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        fileroot = SceneFileHandler::the().read(argv[1]);
        /*
            All scene file loading is handled via the SceneFileHandler.
        */
    }

    scene->addChild(fileroot);
    
    // Create a small geometry to show the ray and what was hit
    // Contains a line and a single triangle.
    // The line shows the ray, the triangle whatever was hit.
    
    SimpleMaterialPtr red = SimpleMaterial::create();
    
    beginEditCP(red);
    {
        red->setDiffuse     (Color3f( 1,0,0 ));   
        red->setTransparency(0.5);   
        red->setLit         (false);   
    }
    endEditCP  (red);

    isectPoints = GeoPositions3f::create();
    beginEditCP(isectPoints);
    {
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
        isectPoints->addValue(Pnt3f(0,0,0));
    }
    endEditCP(isectPoints);

    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();     
    beginEditCP(index);
    {
        index->addValue(0);
        index->addValue(1);
        index->addValue(2);
        index->addValue(3);
        index->addValue(4);
    }
    endEditCP(index);

    GeoPLengthsUI32Ptr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens);
    {
        lens->addValue(2);
        lens->addValue(3);
    }
    endEditCP(lens);
    
    GeoPTypesUI8Ptr type = GeoPTypesUI8::create();  
    beginEditCP(type);
    {
        type->addValue(GL_LINES);
        type->addValue(GL_TRIANGLES);
    }
    endEditCP(type);

    testgeocore = Geometry::create();
    beginEditCP(testgeocore);
    {
        testgeocore->setPositions(isectPoints);
        testgeocore->setIndices(index);
        testgeocore->setLengths(lens);
        testgeocore->setTypes(type);
        testgeocore->setMaterial(red);
    }
    endEditCP(testgeocore);   
    
    NodePtr testgeo = Node::create();
    beginEditCP(testgeo);
    {
        testgeo->setCore(testgeocore);
    }
    endEditCP(testgeo);
    
    scene->addChild(testgeo);
    endEditCP(scene);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    mgr->getCamera()->setNear(mgr->getCamera()->getNear() / 10);

    // Show the bounding volumes? Not for now
    mgr->getAction()->setVolumeDrawing(false);

    _idbuff = new IDbuffer();
    _idbuff->setCamera(mgr->getCamera());
    _idbuff->setRoot(scene);
    
    // GLUT main loop
    glutMainLoop();

    return 0;

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
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    _idbuff->reshape(w,h);

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

    return winid;
}

