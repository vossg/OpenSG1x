/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <OSGTriangleIterator.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

NodePtr scene,wire_scene,wire_scene2;
GeometryPtr geometry;

const UInt32 POINTER_SIZE=3;

// given a frustum , a line, near and far, sets the planes of the frustum so
// that its near and far planes are parallel to the screen and pass through
// near and far. The other four planes are set symmetrically.

NodePtr setFrustumPlanes(FrustumVolume &frustum,Line *view_rays,Pnt3f center,Real32 dist)
{
    Plane pnear(view_rays[0].getDirection(),center-view_rays[0].getDirection()*dist);
    Plane pfar(view_rays[0].getDirection(),center+view_rays[0].getDirection()*dist);
    
    Pnt3f nlefttop,nleftbottom,nrighttop,nrightbottom;
    Pnt3f flefttop,fleftbottom,frighttop,frightbottom;
    
    pnear.intersectInfinite(view_rays[1],nleftbottom);
    pfar.intersectInfinite(view_rays[1],fleftbottom);
    
    std::cout << "nleftbottom: " << nleftbottom[0] << " : " << nleftbottom[1] << " : " << nleftbottom[2] << std::endl;
    std::cout << "fleftbottom: " << fleftbottom[0] << " : " << fleftbottom[1] << " : " << fleftbottom[2] << std::endl;    

    pnear.intersectInfinite(view_rays[2],nrightbottom);
    pfar.intersectInfinite(view_rays[2],frightbottom);
    
    std::cout << "nrightbottom: " << nrightbottom[0] << " : " << nrightbottom[1] << " : " << nrightbottom[2] << std::endl;
    std::cout << "frightbottom: " << frightbottom[0] << " : " << frightbottom[1] << " : " << frightbottom[2] << std::endl;    
    
    pnear.intersectInfinite(view_rays[3],nrighttop);
    pfar.intersectInfinite(view_rays[3],frighttop);

    std::cout << "nrighttop: " << nrighttop[0] << " : " << nrighttop[1] << " : " << nrighttop[2] << std::endl;
    std::cout << "frighttop: " << frighttop[0] << " : " << frighttop[1] << " : " << frighttop[2] << std::endl;    
    
    pnear.intersectInfinite(view_rays[4],nlefttop);
    pfar.intersectInfinite(view_rays[4],flefttop);
                
    std::cout << "nlefttop: " << nlefttop[0] << " : " << nlefttop[1] << " : " << nlefttop[2] << std::endl;
    std::cout << "flefttop: " << flefttop[0] << " : " << flefttop[1] << " : " << flefttop[2] << std::endl;    

    Plane pleft(nleftbottom,nlefttop,flefttop);    
    Plane pright(nrightbottom,nrighttop,frighttop);
    Plane ptop(nlefttop,nrighttop,frighttop);
    Plane pbottom(nleftbottom,nrightbottom,frightbottom);
    
    frustum.setPlanes(pnear,pfar,pleft,pright,ptop,pbottom);
    
/*    
    GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);    
    UInt32 len=0;
       
    pnts->addValue(nleftbottom);
    pnts->addValue(nrightbottom);
    
    pnts->addValue(nrightbottom);
    pnts->addValue(nrighttop);
    
    pnts->addValue(nrighttop);
    pnts->addValue(nlefttop);
    
    pnts->addValue(nlefttop);
    pnts->addValue(nleftbottom);
    
    pnts->addValue(fleftbottom);
    pnts->addValue(frightbottom);
    
    pnts->addValue(frightbottom);
    pnts->addValue(frighttop);
    
    pnts->addValue(frighttop);
    pnts->addValue(flefttop);
    
    pnts->addValue(flefttop);
    pnts->addValue(fleftbottom);
    
    pnts->addValue(nleftbottom);
    pnts->addValue(fleftbottom);
    
    pnts->addValue(nrightbottom);
    pnts->addValue(frightbottom);
    
    pnts->addValue(nrighttop);
    pnts->addValue(frighttop);
    
    pnts->addValue(nlefttop);
    pnts->addValue(flefttop);
    
    len=24;
                
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_LINES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);
    
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(len);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);    
    
    // create the geometry
    
    GeometryPtr new_geo=Geometry::create();
    beginEditCP(new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    {
        new_geo->setTypes    (type);
        new_geo->setLengths  (lens);
        new_geo->setPositions(pnts);

        new_geo->setMaterial(getDefaultUnlitMaterial());   
    }
    endEditCP  (new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    
*/    
    NodePtr node = Node::create();

/*    beginEditCP  (node);
    node->setCore(new_geo);
    endEditCP    (node);*/

    return node;
    
} 

// iterates through all triangles of a geometry and intersects the vertices
// of all triangles with the frustum. Creates the corresponding new geometry

NodePtr makeGeoFrustumIntersectionWires(FrustumVolume &frustum,GeometryPtr geo)
{
    GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);    
    UInt32 len=0;
       
    TriangleIterator ti;
    Pnt3f minp,maxp;
    frustum.getBounds(minp,maxp);    
    BoxVolume box(minp,maxp);
    
    for (ti=geo->beginTriangles(); ti!=geo->endTriangles(); ++ti)
        for (int i=0; i<3; i++)
        {
            Pnt3f enter_point=ti.getPosition(i);
            Pnt3f exit_point =ti.getPosition((i+1)%3);
            
            Line line1(enter_point,exit_point);
            Line line2(exit_point,enter_point);

            Pnt3f _pos1=line1.getPosition();
            Vec3f _dir1=line1.getDirection();

            Pnt3f _pos2=line2.getPosition();
            Vec3f _dir2=line2.getDirection();
            
            Real32 enter1 = 0;
            Real32 exit1;
            Real32 a;
            if ((a=(exit_point  - _pos1).dot(_dir1))!=0)
                exit1 = ((exit_point  - _pos1).dot(exit_point  - _pos1))/a;
            else
                exit1=0;

            Real32 enter2 = 0;
            Real32 exit2;
            if ((a=(enter_point  - _pos2).dot(_dir2))!=0)
                exit2 = ((enter_point  - _pos2).dot(enter_point  - _pos2))/a;
            else
                exit2=0;
            
            Real32 l_en1,l_ex1,l_en2,l_ex2;
            bool first;            
                        
            bool boxline=false;
            
            if ( (first=box.intersect(line1,l_en1,l_ex1)) )
            {
                if (first && l_en1>=enter1 && l_en1<=exit1 && l_ex1>=enter1 && l_ex1<=exit1)
                {
                    boxline=true;
                }
                else
                if (box.intersect(line2,l_en2,l_ex2) && l_en2>=enter2 && l_en2<=exit2 && l_ex2>=enter2 && l_ex2<=exit2)
                {
                    boxline=true;
                }
            }
            
            if (!boxline) continue;
          
            if ((first=line1.intersect(frustum,l_en1,l_ex1)) )
            {
//                std::cout << "en-ex : l_en-l_ex :" << enter << ":" << exit << ":" << l_en << ":" << l_ex <<std::endl;
                
                if (first && l_en1>=enter1 && l_en1<=exit1 && l_ex1>=enter1 && l_ex1<=exit1)
                {

//                    Pnt3f Pnt1=line1.getPosition() + line1.getDirection()*l_en1;
//                    Pnt3f Pnt2=line1.getPosition() + line1.getDirection()*l_ex1;
//                    pnts->addValue(Pnt1);
//                    pnts->addValue(Pnt2);
                    pnts->addValue(enter_point);
                    pnts->addValue(exit_point);
                    len+=2;
                }
                else
                if (line2.intersect(frustum,l_en2,l_ex2) && l_en2>=enter2 && l_en2<=exit2 && l_ex2>=enter2 && l_ex2<=exit2)
                {

//                    Pnt3f Pnt1=line2.getPosition() + line2.getDirection()*l_en2;
//                    Pnt3f Pnt2=line2.getPosition() + line2.getDirection()*l_ex2;
//                    pnts->addValue(Pnt1);
//                    pnts->addValue(Pnt2);
                    pnts->addValue(enter_point);
                    pnts->addValue(exit_point);                    
                    len+=2;
                }
            }
            else
            {
/*                pnts->addValue(enter_point);
                pnts->addValue(exit_point);
                len+=2;                */
            }
        }                   
        
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    std::cout << "Added lines: " << len/2 << std::endl;
    
    GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_LINES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);
    
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(len);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);    
    
    // create the geometry
    
    SimpleMaterialPtr myMaterial=SimpleMaterial::create();
    beginEditCP(myMaterial);
    myMaterial->setDiffuse(Color3f(.5,1,1));
    myMaterial->setLit(false);
    endEditCP(myMaterial);
    
    GeometryPtr new_geo=Geometry::create();
    beginEditCP(new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    {
        new_geo->setTypes    (type);
        new_geo->setLengths  (lens);
        new_geo->setPositions(pnts);
        
        
        new_geo->setMaterial(myMaterial);   
    }
    endEditCP  (new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(new_geo);
    endEditCP    (node);

    return node;
}

NodePtr makeFrustumWireScene(FrustumVolume &frustum)
{
    const Plane *_planeVec=frustum.getPlanes();
    
//    const int faces[6][4]={{0,1,3,2},{4,5,7,6},{0,4,5,1},
//                           {2,6,7,3},{2,6,4,0},{1,5,7,3}};
    
    Pnt3f vertices[8];
    Line lines[4];
    _planeVec[5].intersect(_planeVec[3], lines[3]); 
    _planeVec[3].intersect(_planeVec[4], lines[2]); 
    _planeVec[4].intersect(_planeVec[2], lines[0]); 
    _planeVec[2].intersect(_planeVec[5], lines[1]); 
    
    for (int i=0; i<4; i++)
    {
        _planeVec[0].intersectInfinite(lines[i], vertices[i]);
        _planeVec[1].intersectInfinite(lines[i], vertices[4+i]);
    }    
           
    GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);    
    UInt32 len=0;
       
    pnts->addValue(vertices[0]);
    pnts->addValue(vertices[1]);
    
    pnts->addValue(vertices[1]);
    pnts->addValue(vertices[3]);
    
    pnts->addValue(vertices[3]);
    pnts->addValue(vertices[2]);
    
    pnts->addValue(vertices[2]);
    pnts->addValue(vertices[0]);
    
    pnts->addValue(vertices[4]);
    pnts->addValue(vertices[5]);
    
    pnts->addValue(vertices[5]);
    pnts->addValue(vertices[7]);
    
    pnts->addValue(vertices[7]);
    pnts->addValue(vertices[6]);
    
    pnts->addValue(vertices[6]);
    pnts->addValue(vertices[4]);
    
    pnts->addValue(vertices[0]);
    pnts->addValue(vertices[4]);
    
    pnts->addValue(vertices[1]);
    pnts->addValue(vertices[5]);
    
    pnts->addValue(vertices[2]);
    pnts->addValue(vertices[6]);
    
    pnts->addValue(vertices[3]);
    pnts->addValue(vertices[7]);
    len=24;
                
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_LINES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);
    
    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(len);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);    
    
    // create the geometry
    
    GeometryPtr new_geo=Geometry::create();
    beginEditCP(new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    {
        new_geo->setTypes    (type);
        new_geo->setLengths  (lens);
        new_geo->setPositions(pnts);

        new_geo->setMaterial(getDefaultUnlitMaterial());   
    }
    endEditCP  (new_geo, Geometry::TypesFieldMask     |
                         Geometry::LengthsFieldMask   |
                         Geometry::PositionsFieldMask |
                         Geometry::MaterialFieldMask  );
    
    NodePtr node = Node::create();

    beginEditCP  (node);
    node->setCore(new_geo);
    endEditCP    (node);

    return node;
    
}

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
    case 'p':   {
                    //make the frustum
                    Line view_rays[5];
                    
                    view_rays[0]=mgr->calcViewRay(x,y);
                    view_rays[1]=mgr->calcViewRay(x-POINTER_SIZE,y+POINTER_SIZE);
                    view_rays[2]=mgr->calcViewRay(x+POINTER_SIZE,y+POINTER_SIZE);
                    view_rays[3]=mgr->calcViewRay(x+POINTER_SIZE,y-POINTER_SIZE);
                    view_rays[4]=mgr->calcViewRay(x-POINTER_SIZE,y-POINTER_SIZE);                                                                                
                    
                    Pnt3f p;
                    IntersectAction * act=IntersectAction::create();
                    act->setLine(view_rays[0]);
                    act->apply(mgr->getRoot());
                    if (act->didHit())
                    {
                        p=act->getHitPoint();
                        std::cout << "we did a hit: " << p[0] << ":" << p[1] << ":" << p[2] << std::endl;
                    }
                    else
                    {
                        p=Pnt3f(0,0,0);
                        std::cout << "no hit, developing around (0,0,0)" << std::endl;
                    }
                    
                    FrustumVolume frustum;

                    setFrustumPlanes(frustum,view_rays,p,0.005);
                    wire_scene=makeFrustumWireScene(frustum);
                    addRefCP(wire_scene);
                    mgr->getRoot()->addChild(wire_scene);

                    //make the wire scene
                    wire_scene2=makeGeoFrustumIntersectionWires(frustum,geometry);
                    addRefCP(wire_scene2);
                    mgr->getRoot()->addChild(wire_scene2);
                } break;

    }
    mgr->key(key,x,y);
    glutPostRedisplay();
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

    NodePtr scene=Node::create();
    
    if(argc < 2)
    {
        geometry = makeTorusGeo(.5, 2, 16, 16);
        //geometry = makePlaneGeo(5,5,2,1);
        
        beginEditCP  (scene);
        scene->setCore(geometry);
        endEditCP    (scene);
    }
    else
    {
        scene = SceneFileHandler::the().read(argv[1]);
        geometry=GeometryPtr::dcast(scene->getCore());
        if (geometry==NullFC) return 0;
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
