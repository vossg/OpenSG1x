#include <OSGConfig.h>

#include <iostream>

#include <OSGBaseFunctions.h>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include "OSGAction.h"

using namespace OSG;

// derive two NodeCores so that we have something to work on.
// As simple as possible. This is not how to do it right!

class Core1;
typedef FCPtr<NodeCorePtr, Core1> Core1Ptr;

class Core1 : public NodeCore
{
  public:
    static const char *getClassname(void) { return "Core1"; };

    OSG_FIELD_CONTAINER_DECL(Core1Ptr)

    Core1(void) {}
    virtual ~Core1(void) {}

   Action::ResultE enter(Action * action )
   {
        std::cerr << "Core1::enter: " << this << " action " 
             << action << std::endl;
        return Action::Continue;        
   }
   
   Action::ResultE leave(Action * action )
   {
        std::cerr << "Core1::leave: " << this << " action " 
             << action << std::endl;
        return Action::Continue;        
   }
    
  virtual void execBeginEdit(const osg::BitVector&, osg::UInt32, osg::UInt32)
  {
    std::cerr << "Core1::execBeginEdit: " << this << std::endl;
  }
  
  private:

    typedef NodeCore Inherited;

    friend class FieldContainer;

    static FieldContainerType _type;    
};

OSG_FIELD_CONTAINER_INL_DEF(Core1, Core1Ptr)
OSG_FIELD_CONTAINER_DEF(Core1, Core1Ptr)

FieldContainerType Core1::_type(
    "Core1",
    "NodeCore",
    0,
    (PrototypeCreateF) &Core1::createEmpty
);


// Core2: derived from Core1, to test inheritance following

class Core2;
typedef FCPtr<Core1Ptr, Core2> Core2Ptr;

class Core2 : public Core1
{
  public:
    static const char *getClassname(void) { return "Core2"; };

    OSG_FIELD_CONTAINER_DECL(Core2Ptr)

    Core2(void) {}
    virtual ~Core2(void) {}

  private:

    typedef NodeCore Inherited;

    friend class FieldContainer;

    static FieldContainerType _type;    
};

OSG_FIELD_CONTAINER_INL_DEF(Core2, Core2Ptr)
OSG_FIELD_CONTAINER_DEF(Core2, Core2Ptr)

FieldContainerType Core2::_type(
    "Core2",
    "Core1",
    0,
    (PrototypeCreateF) &Core2::createEmpty
);





// call a method of a class instance

class Core1Action
{
public:
    Core1Action() {}

    Action::ResultE enter(CNodePtr &node, Action * action)
    { 
        std::cerr << "Core1 enter: " << node << " action " 
             << std::hex << action << " for Core1 " << this << std::endl;
        return Action::Continue; 
    }

    Action::ResultE leave(CNodePtr &node, Action * action)
    { 
        std::cerr << "Core1 leave: " << node << " action " 
             << std::hex << action << " for Core1 " << this << std::endl;
        return Action::Continue; 
    }
};


// Core2: use simple functions

Action::ResultE Core2Enter(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Core2 enter: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}

Action::ResultE Core2Leave(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Core2 leave: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}


// traverse only the first node

Action::ResultE firstOnly(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Core1 (first only) enter: " << node << " action " << std::hex << action 
         << std::endl;

    const NodePtr p = action->getNode( 0 );

    if ( p != NullFC )
        action->addNode( p );

    return Action::Continue; 
}

// default function

Action::ResultE defenter1(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Default enter 1 called: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}

Action::ResultE defleave1(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Default leave 1 called: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}

Action::ResultE defenter2(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Default enter 2 called: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}

Action::ResultE defleave2(CNodePtr& node, Action * action) 
{ 
    std::cerr << "Default leave 2 called: " << node 
         << " action " << std::hex << action << std::endl;

    return Action::Continue; 
}


Action::ResultE traventer(NodePtr& node) 
{ 
    std::cerr << "traventer called: " << node << std::endl;

    return Action::Continue; 
}

Action::ResultE travleave(NodePtr& node, Action::ResultE res) 
{ 
    std::cerr << "travleave called: " << node << " " << res << std::endl;

    return Action::Continue; 
}

struct TravActor
{
    Action::ResultE enter(NodePtr& n)
    {
        std::cerr << "TravActor::enter " << this << " Node " << n << std::endl;
        return Action::Continue;
    }
    Action::ResultE leave(NodePtr& n, Action::ResultE res)
    {
        std::cerr << "TravActor::leave " << this << " Node " << n 
             << " Res " << res << std::endl;
        return Action::Continue;
    }
};


int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

    // build simple tree: g1|((g2|t2),t1)

    NodePtr g1 = Node::create();
    Core1Ptr g1c = Core1::create();
    g1->setCore( g1c );
    NodePtr g2 = Node::create();
    Core1Ptr g2c = Core1::create();
    g2->setCore( g2c );
    NodePtr t1 = Node::create();
    Core2Ptr t1c = Core2::create();
    t1->setCore( t1c );
    NodePtr t2 = Node::create();
    Core2Ptr t2c = Core2::create();
    t2->setCore( t2c );

    g2->addChild( t2 );

    g1->addChild( g2 );
    g1->addChild( t1 );

    
    // two instances for check instance calling
    Core1Action gf1,gf2;

    // register a default function. Should be copied at 
    // instantiation time

    Action::registerEnterDefault(Core1::getClassType(), 
                                 osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                   >(defenter1));

    Action::registerLeaveDefault(Core1::getClassType(), 
                                 osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                   >(defleave1));

    Action *act1;
    act1 = Action::create();

    std::cerr << "Apply (c2 unset):" << std::endl;
    act1->apply(g2);    

    Action::registerEnterDefault(Core2::getClassType(), 
                                 osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                   >(defenter2));
    Action::registerLeaveDefault(Core2::getClassType(), 
                                 osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                   >(defleave2));


    std::cerr << "Apply (c2 unset, pickup from default):" << std::endl;
    act1->apply(g2);    


    Action *act2;
    act2 = Action::create();

    std::cerr << "Apply (c2 set):" << std::endl;
    act2->apply(g2);    

    // assign functors
    act1->registerEnterFunction(Core1::getClassType(), 
                                osgTypedMethodFunctor2ObjPtrCPtrRef<
                                    Action::ResultE,
                                    Core1Action,
                                    CNodePtr,
                                    Action     *>(&gf1, &Core1Action::enter));

    act1->registerLeaveFunction(Core1::getClassType(), 
                                osgTypedMethodFunctor2ObjPtrCPtrRef<
                                    Action::ResultE,
                                    Core1Action,
                                    CNodePtr,
                                    Action     *>(&gf2, &Core1Action::leave));
    
    act1->registerEnterFunction(Core2::getClassType(), 
                                osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                  >(Core2Enter));
    act1->registerLeaveFunction(Core2::getClassType(), 
                                osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                  >(Core2Leave));

    // set act1 as the prototype
    
    Action::setPrototype( act1 );
    
    // call on single node

    std::cerr << "Apply(leaf):" << std::endl;
    act1->apply( t1 );

    // call on single node

    std::cerr << "Apply(leaf), second action :" << std::endl;
    act2->apply( t1 );
    
    // call on single node
    // act2 should now have the same functions
    
    delete act2;
    act2 = Action::create();

    std::cerr << "Apply(leaf), second action from prototype:" << std::endl;
    act2->apply( t1 );

    // call on node with single child:

    std::cerr << "Apply(node):" << std::endl;
    act1->apply( g2 );

    // call on tree:

    std::cerr << "Apply(tree):" << std::endl;
    act1->apply( g1 );

    //use a function that only traverses the first node (if any)
    act1->registerEnterFunction(Core1::getClassType(), 
                                osgTypedFunctionFunctor2CPtrRef<
                                     Action::ResultE, 
                                     CNodePtr,
                                     Action *                  >(firstOnly));

    std::cerr << "Apply(single child traversal):" << std::endl;

    act1->apply( g1 );

    // call on node with single child:

    std::cerr << "Apply(list):" << std::endl;
    act1->apply( g1->getMFChildren()->begin(), g1->getMFChildren()->end() );


    {
    
    TravActor tact1,tact2;
    // traversal function test
    std::cerr << "Traverse(node,enter):" << std::endl;
    traverse(g1, 
             osgTypedMethodFunctor1ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr        >(&tact1, &TravActor::enter));    

    std::cerr << "Traverse(node,enter):" << std::endl;
    traverse(g1, 
             osgTypedMethodFunctor1ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr        >(&tact1, &TravActor::enter));    
    
    std::cerr << "Traverse(list,enter):" << std::endl;
    traverse(g1->getMFChildren()->getValues(), 
             osgTypedMethodFunctor1ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr        >(&tact2, &TravActor::enter) );

    
    std::cerr << "Traverse(node,enter&leave):" << std::endl;
    traverse(g1, 
             osgTypedMethodFunctor1ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr        >(&tact1, &TravActor::enter), 

             osgTypedMethodFunctor2ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr,
                 Action::ResultE>(&tact1, &TravActor::leave) );
    
    std::cerr << "Traverse(list,enter&leave):" << std::endl;
    traverse(g1->getMFChildren()->getValues(), 
             osgTypedMethodFunctor1ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr        >(&tact2, &TravActor::enter), 
             osgTypedMethodFunctor2ObjPtrCPtrRef<
                 Action::ResultE,
                 TravActor,
                 NodePtr,
                 Action::ResultE>(&tact2, &TravActor::leave) );
 
    
    std::cerr << "Traverse(node,enter):" << std::endl;
    traverse(g1, 
             osgTypedFunctionFunctor1CPtrRef<
                 Action::ResultE, 
                 NodePtr        >(traventer));    
    
    std::cerr << "Traverse(list,enter):" << std::endl;
    traverse(g1->getMFChildren()->getValues(), 
             osgTypedFunctionFunctor1CPtrRef<
                 Action::ResultE, 
                 NodePtr        >(traventer) );
    
    std::cerr << "Traverse(node,enter&leave):" << std::endl;
    traverse(g1, 
             osgTypedFunctionFunctor1CPtrRef<
                 Action::ResultE, 
                 NodePtr        >(traventer), 
             osgTypedFunctionFunctor2CPtrRef<
                 Action::ResultE,
                 NodePtr,
                 Action::ResultE>(travleave) );
    
    std::cerr << "Traverse(list,enter&leave):" << std::endl;
    traverse(g1->getMFChildren()->getValues(), 
             osgTypedFunctionFunctor1CPtrRef<
                 Action::ResultE, 
                 NodePtr        >(traventer), 
             osgTypedFunctionFunctor2CPtrRef<
                 Action::ResultE,
                 NodePtr,
                 Action::ResultE>(travleave) );
    }

    // try the error checks

    // NULL nodes

    std::vector<NodePtr> nullvec;
    nullvec.push_back( NullFC );

    std::cerr << "Apply(list) Null:" << std::endl;
    act1->apply( nullvec.begin(), nullvec.end() );

    std::cerr << "Apply(node) Null:" << std::endl;
    act1->apply( NullFC );

    NodePtr g3 = Node::create();
    std::cerr << "Apply(node) without core:" << std::endl;
    act1->apply( g3 );

}
