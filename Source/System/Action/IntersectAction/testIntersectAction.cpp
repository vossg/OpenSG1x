#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGLine.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGAction.h>
#include <OSGFieldContainerPtr.h>

#include <OSGTriangleIterator.h>

#include "OSGIntersectAction.h"

using namespace OSG;

// test functions
// !!!these are to be moved into the respective nodes once this works!!!


// Group: traverse all children

Action::ResultE groupEnter(CNodePtr& node, Action * action) 
{ 
    std::cerr << "groupEnter: " << node << " " << action << std::endl;
    return Action::Continue; 
}

// Geometry: test all triangles

Action::ResultE geometryEnter(CNodePtr& node, Action * action) 
{ 
    std::cerr << "geometryEnter: " << node << " " << action << std::endl;
    
    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Geometry* core =  dynamic_cast<Geometry*>(n->getCore().getCPtr());

    TriangleIterator it;
    Real32 t;
    Vec3f norm;
    
    for ( it = core->beginTriangles(); it != core->endTriangles(); ++it )
    {
        if ( ia->getLine().intersect(   it.getPosition(0), 
                                        it.getPosition(1),
                                        it.getPosition(2), t, &norm ) )
        {
           ia->setHit( t, NodePtr(node), it.getIndex(), norm );
        }
    }
    
    return Action::Continue; 
}

// Transform: transform the ray and test all children

Action::ResultE transformEnter(CNodePtr& node, Action * action) 
{ 
    std::cerr << "transformEnter: " << node << " " << action << std::endl;

    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Transform* core =  dynamic_cast<Transform*>(n->getCore().getCPtr());
    Matrix m = core->getMatrix();
    m.invert();
    
    Pnt3f pos;
    Vec3f dir;
    m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
    m.multMatrixVec( ia->getLine().getDirection(), dir );
    
    ia->setLine( Line( pos, dir ), ia->getMaxDist() );
    return Action::Continue; 
}

Action::ResultE transformLeave(CNodePtr& node, Action * action) 
{ 
    std::cerr << "transformLeave: " << node << " " << action << std::endl;

    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Transform* core =  dynamic_cast<Transform*>(n->getCore().getCPtr());
    Matrix &m = core->getMatrix();
    
    Pnt3f pos;
    Vec3f dir;
    m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
    m.multMatrixVec( ia->getLine().getDirection(), dir );
    
    ia->setLine( Line( pos, dir ), ia->getMaxDist() );
    return Action::Continue; 
}



int main (int argc, char **argv)
{
    osgInit(argc, argv);

    // for testing only: register Node type functions

#if 0
    IntersectAction::registerEnterDefault(Group::getStaticType(), 
                               osgFunctionFunctor2(groupEnter));
    IntersectAction::registerEnterDefault(Geometry::getStaticType(), 
                               osgFunctionFunctor2(geometryEnter));
    IntersectAction::registerEnterDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(transformEnter));
    IntersectAction::registerLeaveDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(transformLeave));
#endif  
    // create test scene
  
    //  g1->(g2->g3->p1,t1->p2)
    NodePtr  p1 = makePlane( 2,2,2,2 );
    NodePtr  p2 = makePlane( 2,2,2,2 );
    
    // doesn't work !?!?!?  
    // NodePtr gr1 = FieldContainerFactory::the().createNode("Group");
    // NodePtr gr2 = FieldContainerFactory::the().createNode("Group");
    // NodePtr gr3 = FieldContainerFactory::the().createNode("Group");
    
    NodePtr g4 = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1);
    t1->getMatrix().setTranslate( 2,0,0 );
    endEditCP(t1);
    beginEditCP(g4);
    g4->setCore( t1 );
    g4->addChild( p2 );
    endEditCP(g4);

    NodePtr g3 = Node::create();
    GroupPtr g3c = Group::create();
    beginEditCP(g3);
    g3->setCore( g3c );
    g3->addChild( p1 );
    endEditCP(g3);
    
    NodePtr g2 = Node::create();
    GroupPtr g2c = Group::create();
    beginEditCP(g2);
    g2->setCore( g2c );
    g2->addChild( g3 );
    endEditCP(g2);

    NodePtr g1 = Node::create();
    GroupPtr g1c = Group::create();
    beginEditCP(g1);
    g1->setCore( g1c );
    g1->addChild( g2 );
    g1->addChild( g4 );
    endEditCP(g1);

    // Intersect
    
    IntersectAction *act = IntersectAction::create();
    
    Pnt3f pnts[] = { Pnt3f( 0,0,1 ), Pnt3f( 1,0,1),  Pnt3f( 2,0,1), 
            Pnt3f( 3,0,1) , 
            Pnt3f(-Inf,-Inf,-Inf) };
    Vec3f dirs[] = { Vec3f( 0,0,-1), Vec3f( 0,0,-1), Vec3f( 0,0,-1),  
            Vec3f( 0,0,-1), 
            Vec3f(-Inf,-Inf,-Inf) };
    
    for ( int i = 0; pnts[i][0] != -Inf; i++ )
    {
        act->setLine( Line( pnts[i], dirs[i]) );

        act->apply( g1 );

        std::cerr << "Line " << act->getLine().getPosition() << " dir " 
             << act->getLine().getDirection() << " hit: " << act->didHit() << " ";

        if ( act->didHit() )
        {
            std::cerr << " object " << act->getHitObject() 
                 << " tri " << act->getHitTriangle() 
                 << " at " << act->getHitPoint();
        }

        std::cerr << std::endl;
    }
    
    return 0;
}

