// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGGeometry.h>

#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>

OSG_USING_NAMESPACE

// this will specify the resolution of the mesh
#define N   100

//[TODO: remove this counter later]
Int32 counter = 0;

//the two dimensional array that will store all height values
Real32 wMesh[N][N];

//the origin of the water mesh
Pnt3f wOrigin = Pnt3f(0,0,0);

//width and length of the mesh
UInt16 width = 100;
UInt16 length = 100;

SimpleSceneManager *mgr;
NodePtr scene;

int setupGLUT( int *argc, char *argv[] );

void updateMesh(Real32 time){
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            wMesh[x][z] = 10*cos(time/1000.f + (x+z)/10.f);
}

NodePtr createScenegraph(){
    // the scene must be created here
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++)
            wMesh[x][z] = 0;
            
    // GeoPTypes will define the types of primitives to be used
    GeoPTypesPtr type = GeoPTypesUI8::create();
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
	// we want to use quads ONLY 
	type->addValue(GL_QUADS);
    endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    
    // GeoPLength will define the number of vertices of
    // the used primitives
    GeoPLengthsPtr length = GeoPLengthsUI32::create();
    beginEditCP(length, GeoPLengthsUI32::GeoPropDataFieldMask);
	// the length of our quads is four ;-)
	length->addValue((N-1)*(N-1)*4);
    endEditCP(length, GeoPLengthsUI32::GeoPropDataFieldMask);

    // GeoPositions3f stores the positions of all vertices used in 
    // this specific geometry core
    GeoPositions3fPtr pos = GeoPositions3f::create();
    beginEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
	// here they all come
	for (int x = 0; x < N; x++)
            for (int z = 0; z < N; z++)
		pos->addValue(Pnt3f(x, wMesh[x][z], z));
    endEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);

    //GeoColors3f stores all color values that will be used
    GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
        for (int x = 0; x < N; x++)
            for (int z = 0; z < N; z++)
		colors->addValue(Color3f(0,0,1));
    endEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
    
    GeoNormals3fPtr norms = GeoNormals3f::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
        for (int x = 0; x < N; x++)
            for (int z = 0; z < N; z++)
		// As initially all heights are set to zero thus yielding a plane,
		// we set all normals to (0,1,0) parallel to the y-axis
		norms->addValue(Vec3f(0,1,0));
    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
    
    SimpleMaterialPtr mat = SimpleMaterial::create();
    beginEditCP(mat);
        mat->setDiffuse(Color3f(0,0,1));
    endEditCP(mat);
    
    // GeoIndicesUI32 points to all relevant data used by the 
    // provided primitives
    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);
        for (int x = 0; x < N-1; x++)
            for (int z = 0; z < N-1; z++){
		// points to four vertices that will
		// define a single quad
		indices->addValue(z*N+x);	
		indices->addValue((z+1)*N+x);
		indices->addValue((z+1)*N+x+1);
		indices->addValue(z*N+x+1);
            }
    endEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);

        GeometryPtr geo = Geometry::create();
    beginEditCP(geo,
        Geometry::TypesFieldMask	|
	Geometry::LengthsFieldMask	|
	Geometry::IndicesFieldMask	|
	Geometry::PositionsFieldMask	|
	Geometry::NormalsFieldMask      |
        Geometry::MaterialFieldMask     |
	Geometry::ColorsFieldMask	|
        Geometry::DlistCacheFieldMask
	);
	
	geo->setTypes(type);
	geo->setLengths(length);
	geo->setIndices(indices);
	geo->setPositions(pos);
	geo->setNormals(norms);
        geo->setMaterial(mat);
	//geo->setColors(colors);
        geo->setDlistCache(false);

    endEditCP(geo,
        Geometry::TypesFieldMask	|
	Geometry::LengthsFieldMask	|
	Geometry::IndicesFieldMask	|
	Geometry::PositionsFieldMask	|
	Geometry::NormalsFieldMask	|
        Geometry::MaterialFieldMask     |
	Geometry::ColorsFieldMask	|
        Geometry::DlistCacheFieldMask
	);
    
    DirectionalLightPtr pLight = DirectionalLight::create();
    NodePtr root = Node::create();
    NodePtr water = Node::create();
    NodePtr pLightTransformNode = Node::create();
    TransformPtr pLightTransform = Transform::create();
    NodePtr pLightNode = Node::create();
    
    beginEditCP(pLightNode);
        pLightNode->setCore(Group::create());
    endEditCP(pLightNode);
    
    Matrix m;
    m.setIdentity();
    m.setTranslate(50,25,50);
    
    beginEditCP(pLightTransform);
        pLightTransform->setMatrix(m);
    endEditCP(pLightTransform);
    
    //we add a little spehere that will represent the light source
    GeometryPtr sphere = makeSphereGeo(2,2);

    SimpleMaterialPtr sm = SimpleMaterial::create();

    beginEditCP(sm, SimpleMaterial::DiffuseFieldMask |
                    SimpleMaterial::LitFieldMask);
    {
        sm->setLit(false);
        sm->setDiffuse(Color3f(1,1,1));
    }
    endEditCP  (sm, SimpleMaterial::DiffuseFieldMask |
                    SimpleMaterial::LitFieldMask);

    beginEditCP(sphere, Geometry::MaterialFieldMask);
    {
        sphere->setMaterial(sm);
    }
    endEditCP  (sphere, Geometry::MaterialFieldMask);
    
    NodePtr sphereNode = Node::create();
    beginEditCP(sphereNode);
        sphereNode->setCore(sphere);
    endEditCP(sphereNode);

    beginEditCP(pLightTransformNode);
        pLightTransformNode->setCore(pLightTransform);
        pLightTransformNode->addChild(pLightNode);
        pLightTransformNode->addChild(sphereNode);
    endEditCP(pLightTransformNode);

    beginEditCP(pLight);
        pLight->setDirection (Vec3f(0,1,0));
        //color information
        pLight->setDiffuse(Color4f(1,1,1,1));
        pLight->setAmbient(Color4f(0.2,0.2,0.2,1));
        pLight->setSpecular(Color4f(1,1,1,1));
        
        //set the beacon
        pLight->setBeacon(pLightNode);
    endEditCP  (pLight);

    
    beginEditCP(water);
        water->setCore(geo);
    endEditCP(water);
    
    beginEditCP(root);
        root->setCore(pLight);
        root->addChild(water);
        root->addChild(pLightTransformNode);
    endEditCP(root);    
    return root;
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    scene =createScenegraph();

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->showAll();
    mgr->setHeadlight(false);
    
    Navigator * nav = mgr->getNavigator();
    nav->setFrom(nav->getFrom()+Vec3f(0,50,0));
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    Real32 time = glutGet(GLUT_ELAPSED_TIME);
    updateMesh(time);
    
    // we extract the core out of the root node
    // as we now this is a geometry node
    GeometryPtr geo = GeometryPtr::dcast(scene->getChild(0)->getCore());
    
    //now modify it's content
    
    // first we need a pointer to the position data field
    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(geo->getPositions());
    
    //get the data field the pointer is pointing at
    GeoPositions3f::StoredFieldType *posfield = pos->getFieldPtr();
    //get some iterators
    GeoPositions3f::StoredFieldType::iterator last, it;

    // set the iterator to the first data
    it = posfield->begin();
    
    beginEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
    //now simply run over all entires in the array
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++){
            (*it) = Pnt3f(x, wMesh[x][z], z);
            it++;
        }
    endEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
    
    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    //glEnable(GL_LIGHT1);
    return winid;
}

