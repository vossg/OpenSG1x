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
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>

#include <OSGMaterialChunk.h>

#include "OSGMaterial.h"
#include "OSGChunkMaterial.h"
#include "OSGSimpleMaterial.h"


OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr plane,torus;
ChunkMaterialPtr pm;
SimpleMaterialPtr tmat;
Material::DrawFunctor pfunc,tfunc;

void
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    if ( (int) ( a / 2000 ) & 1 )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( a / 20, 0,0,1 );
    
    pm->draw(pfunc, dact);
    
    glPushMatrix();
    glTranslatef( 0,0,fabs(osgsin(a/3000 * Pi))*2 );
    glRotatef( (a/3000) * 360 / 2, 1,0,0 );

    tmat->draw(tfunc, dact);

    // do some OpenGL rendering

    StatePtr st = pm->makeState();

    addRefCP( st );

    st->activate( dact );
    glutSolidSphere( .4, 8, 8 );
    st->deactivate( dact );

    subRefCP( st );

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
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
    // glutKeyboardFunc(key);
    // glutReshapeFunc(resize);
    glutDisplayFunc(display);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);

    glutIdleFunc(display);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // OSG

    plane = makePlane( 2, 2, 8, 8 );
    torus = makeTorus( .2, 1, 16, 8 );

    GeometryPtr plane_geo, torus_geo;
    plane_geo = GeometryPtr::dcast(plane->getCore());
    torus_geo = GeometryPtr::dcast(torus->getCore());

    pfunc=osgTypedMethodFunctor1ObjPtr(&(*plane_geo), &Geometry::drawPrimitives);
    tfunc=osgTypedMethodFunctor1ObjPtr(&(*torus_geo), &Geometry::drawPrimitives);

    pm = ChunkMaterial::create();

    MaterialChunkPtr pmc = MaterialChunk::create();
    pmc->setDiffuse( Color4f( 1,0,0,0 ) );
    pmc->setAmbient( Color4f( 1,0,0,0 ) );
    pmc->setSpecular( Color4f( 1,1,1,0 ) );
    pmc->setShininess( 20 );

    pm->addChunk( pmc );

    plane_geo->setMaterial( pm );


    tmat = SimpleMaterial::create();

    tmat->setDiffuse( Color3f( 0,1,0 ) );
    tmat->setAmbient( Color3f( 0,1,0 ) );

    torus_geo->setMaterial( tmat );


    dact = DrawAction::create();

    glutMainLoop();

    return 0;
}

