/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

/*! testTransformRender is the basic test program to check the Transform 
 *  node's functionality.
 */

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


OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr  root;

TransformPtr tr;

void 
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    if ( (int) ( a / 2000 ) & 1 )   
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Matrix m;

    m.setTranslate( 0,0,sin(a/1500) * 2 );

    beginEditCP(tr);
    tr->getSFMatrix()->setValue( m );
    endEditCP(tr);
    

    dact->apply( root );

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
    // glEnable( GL_LIGHTING );

    // OSG

    NodePtr g1;
    g1 = makePlane( 2, 2, 2, 2 );

    
    NodePtr g2 = Node::create();
    beginEditCP(g2);
    g2->setCore( g1->getCore() );
    endEditCP(g2);

    // Transform

    NodePtr tnode = Node::create();
    tr = Transform::create();
    beginEditCP(tnode);
    tnode->setCore( tr );
    tnode->addChild( g2 );
    endEditCP(tnode);

/*
    NodeCorePtr tcr = 
        FieldContainerFactory::the().createNodeCore("Group");

    NodePtr pcr = 
        FieldContainerFactory::the().createNode("Node");
*/

    //

    root = Node::create();
    GroupPtr gr = Group::create();
    beginEditCP(root);
    root->setCore( gr );
    root->addChild( g1 );
    root->addChild( tnode );
    endEditCP(root);

    dact = DrawAction::create();

    dact->setFrustumCulling(false);

    
    glutMainLoop();
    
    return 0;
}

