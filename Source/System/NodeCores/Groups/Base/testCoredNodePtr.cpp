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
#include <OSGWindow.h>

using namespace OSG;
using namespace std;

#define DO_EXPECT_FAILx


int main (int argc, char **argv)
{
    osgInit( argc, argv );
   
    NodeRefPtr np(Node::create());
    TransformRefPtr tp(Transform::create());
    beginEditCP(np);
    np->setCore(tp);
    endEditCP(np);

    // Default constructor
    TransformNodePtr t;

    cout << "Default const(t): " << endl << t << endl << endl;
    
    // Core Assignment constructor
    GroupNodePtr g(Group::create());
 
    cout << "Core Assignment constructor (g): " << endl << g << endl << endl;
    
    // Copy constructor
    GroupNodePtr g2(g);
 
    cout << "Copy constructor (g2): " << endl << g2 << endl << endl;
    
    // Create
    GroupNodePtr g3 = GroupNodePtr::create();
 
    cout << "Create (g3): " << endl << g3 << endl << endl;    
   
    // Core Assignment
    g = Group::create();
 
    cout << "Core Assignment(g): " << endl << g << endl << endl;
    
    // Node Assignment
    t = np;
 
    cout << "Node Assignment(t): " << endl << t << endl << endl;
  
    // Core Access
    
    g2.coreChanged(); // g = Group::create(); changed it
    cout << "Core access (g2): " << g2.core() << endl << endl;
   
    // -> operator 
    
    cout << "-> operator (t): " << t->getMatrix() << endl << endl;
   
    // NodePtr operator 
    
    NodePtr nn = t;
    
    cout << "NodePtr operator (t): " << nn << endl << endl;
   
    // CorePtr operator 
    
    TransformPtr tt = t;
    
    cout << "CorePtr operator (tt): " << tt << endl << endl;
   
    // Assign NullFC 
    
    tt = NullFC;
    
    cout << "CorePtr operator =NullFC(tt): " << tt << endl << endl;
   
    
#ifdef DO_EXPECT_FAIL

    // Create instance of non-NodeCorePtr
    WindowNodePtr w;
    
#endif
   
 
    return 0;
}

