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

	OSGAction::ResultE enter(OSGCNodePtr &node, OSGAction * action)
	{ 
		cerr << "Group enter: " << node << " action " 
			 << action << " for group " << this << endl;
		return OSGAction::Continue; 
	}

	OSGAction::ResultE leave(OSGCNodePtr &node, OSGAction * action)
	{ 
		cerr << "Group leave: " << node << " action " 
			 << action << " for group " << this << endl;
		return OSGAction::Continue; 
	}
};


// Transform: use simple functions

OSGAction::ResultE transEnter(OSGCNodePtr& node, OSGAction * action) 
{ 
	cerr << "Transform enter: " << node 
         << " action " << action << endl;

	return OSGAction::Continue; 
}

OSGAction::ResultE transLeave(OSGCNodePtr& node, OSGAction * action) 
{ 
	cerr << "Transform leave: " << node 
         << " action " << action << endl;

	return OSGAction::Continue; 
}


// traverse only the first node

OSGAction::ResultE firstOnly(OSGCNodePtr& node, OSGAction * action) 
{ 
	cerr << "Group (first only) enter: " << node << " action " << action 
		 << endl;

	const OSGNodePtr p = action->getNode( 0 );

	if ( p != OSGNullNode )
		action->addNode( p );

	return OSGAction::Continue; 
}

// default function

OSGAction::ResultE defenter(OSGCNodePtr& node, OSGAction * action) 
{ 
	cerr << "Default enter called: " << node 
         << " action " << action << endl;

	return OSGAction::Continue; 
}

OSGAction::ResultE defleave(OSGCNodePtr& node, OSGAction * action) 
{ 
	cerr << "Default leave called: " << node 
         << " action " << action << endl;

	return OSGAction::Continue; 
}

// call a node method on the traversed node


int main( int argc, char *argv[] )
{
    osgInit(argc, argv);

	// register a default function. Should be copied at 
	// instantiation time

	OSGAction::registerEnterDefault(OSGGroup::getStaticType(), 
                               osgFunctionFunctor2(defenter));
	OSGAction::registerLeaveDefault(OSGGroup::getStaticType(), 
                               osgFunctionFunctor2(defleave));
	OSGAction::registerEnterDefault(OSGTransform::getStaticType(), 
                               osgFunctionFunctor2(defenter));
	OSGAction::registerLeaveDefault(OSGTransform::getStaticType(), 
                               osgFunctionFunctor2(defleave));


	// build simple tree: g1|((g2|t2),t1)

    OSGNodePtr g1 = OSGNode::create();
    OSGGroupPtr g1c = OSGGroup::create();
	g1->setCore( g1c );
    OSGNodePtr g2 = OSGNode::create();
    OSGGroupPtr g2c = OSGGroup::create();
	g2->setCore( g2c );
    OSGNodePtr t1 = OSGNode::create();
    OSGTransformPtr t1c = OSGTransform::create();
	t1->setCore( t1c );
    OSGNodePtr t2 = OSGNode::create();
    OSGTransformPtr t2c = OSGTransform::create();
	t2->setCore( t2c );

	g2->addChild( t2 );

	g1->addChild( g2 );
	g1->addChild( t1 );


	// set to hex for all the pointers coming
	cerr << hex;

	// the actions to use
	OSGAction act1,act2;

	// two instances
	GroupAction gf1,gf2;


	// call without assigned functors, should use defaults
	cerr << "Apply (unset):" << endl;

	act1.apply(g2->getMFChildren()->begin(), g2->getMFChildren()->end());	


	// assign functors
    act1.registerEnterFunction(OSGGroup::getStaticType(), 
                         osgMethodFunctor2Ptr(&gf1, &GroupAction::enter));
    act1.registerLeaveFunction(OSGGroup::getStaticType(), 
                         osgMethodFunctor2Ptr(&gf2, &GroupAction::leave));

	act1.registerEnterFunction(OSGTransform::getStaticType(), 
                               osgFunctionFunctor2(transEnter));
	act1.registerLeaveFunction(OSGTransform::getStaticType(), 
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
	act1.registerEnterFunction(OSGGroup::getStaticType(), 
                         osgFunctionFunctor2(firstOnly));

	cerr << "Apply(single child traversal):" << endl;

	act1.apply( g1 );

	// call on node with single child:

	cerr << "Apply(list):" << endl;
	act1.apply( g1->getMFChildren()->begin(), g1->getMFChildren()->end() );

	// try the error checks

	// NULL nodes

	vector<OSGNodePtr> nullvec;
	nullvec.push_back( OSGNullNode );

	cerr << "Apply(list) Null:" << endl;
	act1.apply( nullvec.begin(), nullvec.end() );

	cerr << "Apply(node) Null:" << endl;
	act1.apply( OSGNullNode );

	OSGNodePtr g3 = OSGNode::create();
	cerr << "Apply(node) without core:" << endl;
	act1.apply( g3 );

	

}
