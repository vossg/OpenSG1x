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

/*! testNodes is a simple test program for creation of the basic node types 
 */

#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGThread.h>
#include <OSGMFVecTypes.h>

#include <OSGGroup.h>
#include <OSGTransform.h>

using namespace OSG;

int main (int argc, char **argv)
{
    osgInit( argc, argv );

//    osgLog().setLogLevel(OSG::LOG_DEBUG);

    NodePtr  p1 = Node::create();
    GroupPtr g1 = Group::create();
    TransformPtr t1 = Transform::create();

    FieldContainerPtr pb1 = p1;
    FieldContainerPtr gb1 = g1;
    FieldContainerPtr tb1 = t1;

    std::cout << "Types:" << std::endl;

    std::cout << "Node (NodePtr):           " << p1->getType().getId() << std::endl
         << "(Node::getStaticType()) : " << Node::getClassType().getId() << std::endl
         << "(FieldContainerPtr)     : " << pb1->getType().getId() << std::endl
         << "Fields: " << std::endl;
    p1->getType().dump();
    std::cout << std::endl;

    std::cout << "Nodes:" << std::endl;

    std::cout << "Group (GroupPtr):           " << g1->getType().getId() << std::endl
         << "(GroupPtr::getStaticType()):" << Group::getClassType().getId() << std::endl
         << "(FieldContainerPtr):        " << gb1->getType().getId() << std::endl
         << "Fields: " << std::endl;
    g1->getType().dump();
    std::cout << std::endl;

    std::cout << "Transform (TransformPtr):       " << t1->getType().getId() << std::endl
         << "(TransformPtr::getStaticType()):" << Transform::getClassType().getId() << std::endl
         << "(FieldContainerPtr):            " << tb1->getType().getId() << std::endl
         << "Fields: " << std::endl;
    t1->getType().dump();
    std::cout << std::endl;

    // create a test tree

    NodePtr  p2 = Node::create();
    NodePtr  p3 = Node::create();
    NodePtr  p4 = Node::create();
    NodePtr  p5 = Node::create();

    TransformPtr t2 = Transform::create();
    GroupPtr g2 = Group::create();
    
    p1->setCore( g1 );
    p2->setCore( t1 );
    p3->setCore( g2 );
    p4->setCore( t2 );
    p5->setCore( t2 );

    p1->addChild( p2 );
    p2->addChild( p3 );
    p2->addChild( p4 );
    p4->addChild( p5 );

    Matrix m1,m2;

    m1.setIdentity();
    m1.setScale( 2,2,2 );
    m2.setIdentity();
    m2.setTranslate( 1,1,1 );

    t1->getSFMatrix()->setValue( m1 );  
    t2->getSFMatrix()->setValue( m2 );  

    std::cout << "Testtree:" << std::endl;

    p1->dump();

    std::cout << "ToWorlds:" << std::endl;

    std::cout << "p1:" << std::endl << p1->getToWorld() << std::endl;
    std::cout << "p2:" << std::endl << p2->getToWorld() << std::endl;
    std::cout << "p3:" << std::endl << p3->getToWorld() << std::endl;
    std::cout << "p4:" << std::endl << p4->getToWorld() << std::endl;
    std::cout << "p5:" << std::endl << p5->getToWorld() << std::endl;

    p1 = NullFC;

    p1.dump();

    p1 = FieldContainerFactory::the()->createNode("Node");

    p1.dump();

    p1 = FieldContainerFactory::the()->createNode("Transform");

    p1.dump();

    NodeCorePtr nc1 = NullFC;

    nc1.dump();

    nc1 = FieldContainerFactory::the()->createNodeCore("Transform");

    nc1.dump();

    // double children

    std::cout << "Double add: before:" << std::endl;

    p2->dump();

    p2->addChild( p5 );

    std::cout << "Double add: after:" << std::endl;

    p2->dump();

    return 0;
}

