#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGBaseFunctions.h>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include "OSGAction.h"

using namespace OSG;

// call a method of a class instance

class GroupAction
{
public:
	GroupAction() {}

	Action::ResultE enter(CNodePtr &node, Action * action)
	{ 
		cerr << "Group enter: " << node << " action " 
			 << action << " for group " << this << endl;
		return Action::Continue; 
	}

	Action::ResultE leave(CNodePtr &node, Action * action)
	{ 
		cerr << "Group leave: " << node << " action " 
			 << action << " for group " << this << endl;
		return Action::Continue; 
	}
};


// Transform: use simple functions

Action::ResultE transEnter(CNodePtr& node, Action * action) 
{ 
	cerr << "Transform enter: " << node 
         << " action " << action << endl;

	return Action::Continue; 
}

Action::ResultE transLeave(CNodePtr& node, Action * action) 
{ 
	cerr << "Transform leave: " << node 
         << " action " << action << endl;

	return Action::Continue; 
}


// traverse only the first node

Action::ResultE firstOnly(CNodePtr& node, Action * action) 
{ 
	cerr << "Group (first only) enter: " << node << " action " << action 
		 << endl;

	const NodePtr p = action->getNode( 0 );

	if ( p != NullNode )
		action->addNode( p );

	return Action::Continue; 
}

// default function

Action::ResultE defenter(CNodePtr& node, Action * action) 
{ 
	cerr << "Default enter called: " << node 
         << " action " << action << endl;

	return Action::Continue; 
}

Action::ResultE defleave(CNodePtr& node, Action * action) 
{ 
	cerr << "Default leave called: " << node 
         << " action " << action << endl;

	return Action::Continue; 
}

// call a node method on the traversed node


int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

	// register a default function. Should be copied at 
	// instantiation time

	Action::registerEnterDefault(Group::getStaticType(), 
                               osgFunctionFunctor2(defenter));
	Action::registerLeaveDefault(Group::getStaticType(), 
                               osgFunctionFunctor2(defleave));
	Action::registerEnterDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(defenter));
	Action::registerLeaveDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(defleave));


	// build simple tree: g1|((g2|t2),t1)

    NodePtr g1 = Node::create();
    GroupPtr g1c = Group::create();
	g1->setCore( g1c );
    NodePtr g2 = Node::create();
    GroupPtr g2c = Group::create();
	g2->setCore( g2c );
    NodePtr t1 = Node::create();
    TransformPtr t1c = Transform::create();
	t1->setCore( t1c );
    NodePtr t2 = Node::create();
    TransformPtr t2c = Transform::create();
	t2->setCore( t2c );

	g2->addChild( t2 );

	g1->addChild( g2 );
	g1->addChild( t1 );


	// set to hex for all the pointers coming
	cerr << hex;

	// the actions to use
	Action act1,act2;

	// two instances
	GroupAction gf1,gf2;


	// call without assigned functors, should use defaults
	cerr << "Apply (unset):" << endl;

	act1.apply(g2->getMFChildren()->begin(), g2->getMFChildren()->end());	


	// assign functors
    act1.registerEnterFunction(Group::getStaticType(), 
                         osgMethodFunctor2Ptr(&gf1, &GroupAction::enter));
    act1.registerLeaveFunction(Group::getStaticType(), 
                         osgMethodFunctor2Ptr(&gf2, &GroupAction::leave));

	act1.registerEnterFunction(Transform::getStaticType(), 
                               osgFunctionFunctor2(transEnter));
	act1.registerLeaveFunction(Transform::getStaticType(), 
                               osgFunctionFunctor2(transLeave));

	// call on single node

	cerr << "Apply(leaf):" << endl;
	act1.apply( t1 );

	// call on single node

	cerr << "Apply(leaf),second action:" << endl;
	act2.apply( t1 );

	// call on node with single child:

	cerr << "Apply(node):" << endl;
	act1.apply( g2 );

	// call on tree:

	cerr << "Apply(tree):" << endl;
	act1.apply( g1 );

	//use a function that only traverses the first node (if any)
	act1.registerEnterFunction(Group::getStaticType(), 
                         osgFunctionFunctor2(firstOnly));

	cerr << "Apply(single child traversal):" << endl;

	act1.apply( g1 );

	// call on node with single child:

	cerr << "Apply(list):" << endl;
	act1.apply( g1->getMFChildren()->begin(), g1->getMFChildren()->end() );

	// try the error checks

	// NULL nodes

	vector<NodePtr> nullvec;
	nullvec.push_back( NullNode );

	cerr << "Apply(list) Null:" << endl;
	act1.apply( nullvec.begin(), nullvec.end() );

	cerr << "Apply(node) Null:" << endl;
	act1.apply( NullNode );

	NodePtr g3 = Node::create();
	cerr << "Apply(node) without core:" << endl;
	act1.apply( g3 );

	

}
