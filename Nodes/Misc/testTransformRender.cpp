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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

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


OSGDrawAction * dact;

OSGNodePtr  root;

OSGTransformPtr tr;

void 
display(void)
{
    float a = glutGet( GLUT_ELAPSED_TIME );

    if ( (int) ( a / 2000 ) & 1 )   
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    OSGMatrix m;

    m.setTranslate( 0,0,sin(a/1500) * 2 );

    osgBeginEditCP(tr);
    tr->getSFMatrix()->setValue( m );
    osgEndEditCP(tr);
    

    dact->apply( root );

    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);

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

    OSGNodePtr g1;
    g1 = osgMakePlane( 2, 2, 2, 2 );

    
    OSGNodePtr g2 = OSGNode::create();
    osgBeginEditCP(g2);
    g2->setCore( g1->getCore() );
    osgEndEditCP(g2);

    // Transform

    OSGNodePtr tnode = OSGNode::create();
    tr = OSGTransform::create();
    osgBeginEditCP(tnode);
    tnode->setCore( tr );
    tnode->addChild( g2 );
    osgEndEditCP(tnode);


    //

    root = OSGNode::create();
    OSGGroupPtr gr = OSGGroup::create();
    osgBeginEditCP(root);
    root->setCore( gr );
    root->addChild( g1 );
    root->addChild( tnode );
    osgEndEditCP(root);

    dact = new OSGDrawAction;
    
    glutMainLoop();
    
    return 0;
}

