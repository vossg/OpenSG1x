#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include <OSGGLUTWindow.h>

#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>


OSG_USING_NAMESPACE

using namespace std;

DrawAction * dact;

NodePtr  root;
NodePtr dlight, plight, slight;
NodePtr dlight2, plight2, slight2;
NodePtr g1;

DirectionalLightPtr dl;
PointLightPtr pl;
SpotLightPtr sl;

TransformPtr tr;

WindowPtr win;

void 
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    win->frameInit();

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Matrix m;

    m.setTranslate( sin(a/1500), cos(a/1500), sin(a/1000) + 1 );

    beginEditCP(tr);
    tr->getSFMatrix()->setValue( m );
    endEditCP(tr);
    

    dact->apply( root );

    win->frameExit();

    glutSwapBuffers();
}

void key( unsigned char key, int, int )
{
    switch (key )
    {
    case 27:    exit(1);    
                break;
    case 'z':   beginEditCP(root);
                root->replaceChild( 1, dlight );
                endEditCP(root);
                beginEditCP(dlight);
                dlight->addChild( slight2 );
                endEditCP(dlight);
                cout << "Switch moving light to Directional" << endl;
                // root->dump();
                break;
    case 'x':   beginEditCP(root);
                root->replaceChild( 1, plight );
                endEditCP(root);
                beginEditCP(plight);
                plight->addChild( slight2 );
                endEditCP(plight);
                cout << "Switch moving light to Point" << endl;
                // root->dump();
                break;
    case 'c':   beginEditCP(root);
                root->replaceChild( 1, slight );
                endEditCP(root);
                beginEditCP(slight);
                slight->addChild( slight2 );
                endEditCP(slight);
                cout << "Switch moving light to Spot" << endl;
               // root->dump();
                break;
    case 'a':   beginEditCP(dl);
                dl->setOn( ! dl->getOn() );
                endEditCP(dl);
                cout << "Static Directional light is " << (dl->getOn()?"on":"off")
                     << endl;
                break;
    case 's':   beginEditCP(pl);
                pl->setOn( ! pl->getOn() );
                endEditCP(pl);
                cout << "Static Point light is " << (pl->getOn()?"on":"off")
                     << endl;
                break;
    case 'd':   beginEditCP(sl);
                sl->setOn( ! sl->getOn() );
                endEditCP(sl);
                cout << "Static Spot light is " << (sl->getOn()?"on":"off")
                     << endl;
                break;    
    default:    cout << "Key:" << key << endl;
                break;            
    }
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);

    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    // glutReshapeFunc(resize);
    glutDisplayFunc(display);       
    // glutMouseFunc(mouse);   
    // glutMotionFunc(motion); 
    
    glutIdleFunc(display);

    // the window is needed for the chunks that access GLObjects

    win = GLUTWindow::create();
    win->frameInit(); // test for preliminary calls not messing up GLexts
    win->init();
    
    dact = DrawAction::create();
    dact->setWindow( win.getCPtr() );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );

    // the root node
    root = Node::create();

    // Geometry

    g1 = makePlane( 3, 3, 20, 20 );
    addRefCP( g1 ); // add a ref to prevent its disappearing when subtracted
    
    // Light Position Inidcator
    NodePtr g2;
    g2 = makePlane( .2, .2, 1, 1 );

    // Transform

    NodePtr tnode = Node::create();
    tr = Transform::create();
    beginEditCP(tnode);
    tnode->setCore( tr );
    tnode->addChild( g2 );
    endEditCP(tnode);

    // Create Lights

    dlight = Node::create();
    dl = DirectionalLight::create();
    addRefCP( dlight ); // add a reference to keep it alive when removing from tree

    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .2, .2, .2, .2 );
    dl->setDiffuse( 1, 0, 0, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( tnode );
    endEditCP(dl);


    plight = Node::create();
    pl = PointLight::create();
    addRefCP( plight ); // add a reference to keep it alive when removing from tree

    beginEditCP(plight);
    plight->setCore( pl );
    endEditCP(plight);
    
    beginEditCP(pl);
    pl->setAmbient( .2, .2, .2, .2 );
    pl->setDiffuse( 0, 1, 0, 1 );
    pl->setConstantAttenuation(.5);
    pl->setLinearAttenuation(.5);
    pl->setQuadraticAttenuation(2);     
    pl->setPosition(0,0,0);
    pl->setBeacon( tnode );
    endEditCP(pl);


    slight = Node::create();
    sl = SpotLight::create();
    addRefCP( slight ); // add a reference to keep it alive when removing from tree

    beginEditCP(slight);
    slight->setCore( sl );
    endEditCP(slight);
    
    beginEditCP(sl);
    sl->setAmbient( .2, .2, .2, .2 );
    sl->setDiffuse( 0, 0, 1, 1 );
    sl->setPosition(0,0,0);
    sl->setSpotDirection(0,0,-1);
    sl->setSpotExponent(10);
    sl->setSpotCutOffDeg(45);
    sl->setBeacon( tnode );
    endEditCP(sl);


    // Second set of Lights

    dlight2 = Node::create();
    dl = DirectionalLight::create();
    addRefCP( dlight2 ); // add a reference to keep it alive when removing from tree

    beginEditCP(dlight2);
    dlight2->setCore( dl );
    dlight2->addChild( g1 );
    endEditCP(dlight2);
    
    beginEditCP(dl);
    dl->setAmbient( 0,0,0,0 );
    dl->setDiffuse( .5, .5, 0, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( root );
    dl->setOn( false );
    endEditCP(dl);


    plight2 = Node::create();
    pl = PointLight::create();
    addRefCP( plight2 ); // add a reference to keep it alive when removing from tree

    beginEditCP(plight2);
    plight2->setCore( pl );
    plight2->addChild( dlight2 );
    endEditCP(plight2);
    
    beginEditCP(pl);
    pl->setAmbient( 0,0,0,0 );
    pl->setDiffuse( 0, .5, .5, 1 );
    pl->setPosition(1,1,1);
    pl->setBeacon( root );
    pl->setOn( false );
    endEditCP(pl);


    slight2 = Node::create();
    sl = SpotLight::create();
    addRefCP( slight2 ); // add a reference to keep it alive when removing from tree

    beginEditCP(slight2);
    slight2->setCore( sl );
    slight2->addChild( plight2 );
    endEditCP(slight2);
    
    beginEditCP(sl);
    sl->setAmbient( 0,0,0,0 );
    sl->setDiffuse( 0, .5, .5, 1 );
    sl->setPosition(1,1,1);
    sl->setSpotDirection(-1,-1,-1);
    sl->setSpotExponent(10);
    sl->setSpotCutOffDeg(45);
    sl->setBeacon( root );
    sl->setOn( false );
    endEditCP(sl);


    //

    beginEditCP(dlight);
    dlight->addChild( slight2 );
    endEditCP(dlight);

    GroupPtr gr = Group::create();
    beginEditCP(root);
    root->setCore( gr );
    root->addChild( tnode );
    root->addChild( dlight );
    endEditCP(root);
    
 
    dact->setFrustumCulling(false);
    
    glutMainLoop();
    
    return 0;
}

