/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

// Minimalistic OpenSG program

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


#include <OSGSceneFileHandler.h>
#include <OSGGeoFunctions.h>
#include <OSGPointLight.h>
#include <OSGTransform.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

NodePtr scene;

Real32 speed = 1.;

// Standard GLUT callback functions
void display( void )
{
    mgr->idle();
    mgr->redraw();
}

void reshape( int w, int h )
{
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
key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:    exit(1);
    case 'a':   mgr->setHighlight( scene );
                break;
    case 's':   mgr->setHighlight( NullFC );
                break;
    case 'l':   mgr->useOpenSGLogo();
                break;
    case 'f':   mgr->setNavigationMode(Navigator::FLY);
                break;
    case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
                break;
    case 'w':   mgr->setNavigationMode(Navigator::WALK);
                break;                
    case 'x':   mgr->getNavigator()->set(
                    Pnt3f(0,0,2),Pnt3f(0,0,0),Vec3f(0,1,0));
                break;
    case 'c':   mgr->getNavigator()->set(
                    Pnt3f(0,0,2),Pnt3f(2,2,1),Vec3f(0,1,0));
                break;
    case 'v':   speed *= .9;
                FLOG(("Speed set to %f\n", speed ));
                mgr->getNavigator()->setMotionFactor(speed);
                break;
    case 'b':   speed *= 1.1;
                FLOG(("Speed set to %f\n", speed ));
                mgr->getNavigator()->setMotionFactor(speed);
                break;
    }
    mgr->key(key,x,y);
    glutPostRedisplay();
}

GeometryPtr _makePlaneGeo(Real32 xsize, Real32 ysize, 
                               UInt16 hor,   UInt16 vert)
{
    if(! hor || ! vert)
    {
        SWARNING << "makePlane: illegal parameters hor=" << hor << ", vert="
                 << vert << std::endl;
        return NullFC;
    }
    
    GeoPositions3fPtr    pnts  = GeoPositions3f::create();
    GeoTexCoords2fPtr    tex   = GeoTexCoords2f::create();
    GeoIndicesUI32Ptr    index = GeoIndicesUI32::create();   
    GeoPLengthsUI32Ptr   lens  = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr      types = GeoPTypesUI8::create();     
    
    UInt16 x,y;
    Real32 xstep,ystep;
    xstep=xsize / hor;
    ystep=ysize / vert;

    // calc the vertices

    GeoPositions3f::StoredFieldType  * p  = pnts->getFieldPtr();
    GeoTexCoords2f::StoredFieldType  * tx = tex->getFieldPtr();

    beginEditCP(pnts);
    beginEditCP(tex);
    
    for(y = 0; y <= vert; y++)
    {
        for(x = 0; x <= hor; x++)
        {
            p->push_back(Pnt3f(x * xstep - xsize / 2, ((x+y)%5) , y * ystep - ysize / 2));
            tx->push_back(Vec2f(x / (Real32) hor, y / (Real32) vert));
        }
    }

    endEditCP(pnts); 
    endEditCP(tex);

    // create the faces
    
    GeoIndicesUI32::StoredFieldType    * i = index->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType   * l = lens->getFieldPtr();
    GeoPTypesUI8::StoredFieldType      * t = types->getFieldPtr();

    beginEditCP(index);
    beginEditCP(lens);
    beginEditCP(types);

    for(y = 0; y < vert; y++)
    {
        t->push_back(GL_TRIANGLE_STRIP);
        l->push_back(2 * (hor + 1));
        
        for(x = 0; x <= hor; x++)
        {
            i->push_back((y + 1) * (hor + 1) + x);
            i->push_back( y      * (hor + 1) + x);
        }
    }

    endEditCP(index);
    endEditCP(lens);
    endEditCP(types);
    
    // create the geometry
    
    GeometryPtr geo = Geometry::create();

    beginEditCP(geo);
    geo->setMaterial(getDefaultMaterial());
    geo->setPositions(pnts);
    geo->setTexCoords(tex);
    geo->setIndices(index);
    geo->getIndexMapping().push_back(Geometry::MapPosition | 
                                    Geometry::MapNormal   |
                                    Geometry::MapTexCoords);
    geo->setTypes(types);
    geo->setLengths(lens);
    endEditCP(geo);
    calcVertexNormals(geo);
    
    return geo;
}

NodePtr _makePlane(Real32 xsize, Real32 ysize, UInt16 hor, UInt16 vert)
{
    GeometryPtr pGeo = _makePlaneGeo(xsize, ysize, hor, vert);
 
    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    SimpleMaterialPtr m1 = SimpleMaterial::create();
    
    // when everything is changed, not setting the mask is ok
    beginEditCP(m1);
    {
        m1->setAmbient      (Color3f(0.2,0.2,0.2));
        m1->setDiffuse      (Color3f(0.8,0.5,0.2));
        m1->setEmission     (Color3f(0.0,0.0,0.0));
        m1->setSpecular     (Color3f(1.0,1.0,1.0));
        m1->setShininess    (10);
        
        /*
            Transparent objects are rendered last and sorted from back to
            front, but only objectwise. Thus transparecy within an object is
            not handled correctly.
        */
        m1->setTransparency (0);
        
        /*
            The SimpleGeometry objects do not contain colors, turn
            ColorMaterial off.
        */
        m1->setColorMaterial(GL_NONE);
        
    }
    endEditCP  (m1);
    
    // assign the material to the geometry
    beginEditCP(pGeo, Geometry::MaterialFieldMask );
    {
        pGeo->setMaterial(m1);
    }
    endEditCP  (pGeo, Geometry::MaterialFieldMask );
    

    NodePtr g2;
    g2 = makePlane( 10, 10, 1, 1 );

    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(pGeo);
    endEditCP    (node);
    
    // Transform

    NodePtr tnode = Node::create();
    TransformPtr tr = Transform::create();
    Matrix m;
    m.setTranslate(0,0,4);
    beginEditCP(tr);
    tr->setMatrix(m);
    endEditCP(tr);
    beginEditCP(tnode);
    tnode->setCore( tr );
    tnode->addChild( g2 );
    endEditCP(tnode);
    
    NodePtr plight = Node::create();
    PointLightPtr pl = PointLight::create();
    addRefCP( plight ); // add a reference to keep it alive when removing from tree

    beginEditCP(plight);
    plight->setCore( pl );
    plight->addChild(node);
    endEditCP(plight);

    beginEditCP(pl);
    pl->setPosition(0,-16,0);
    pl->setBeacon( node );
    endEditCP(pl);

    return plight;
}


// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutIdleFunc(display);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene

    NodePtr scene;
    
    if(argc < 2)
    {
        scene = _makePlane(100,100,20,20);
    }
    else
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );
    
    WalkNavigator *walker=mgr->getNavigator()->getWalkNavigator();
    walker->setGroundDistance(1);
    walker->setPersonDimensions(3,1,1);

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
