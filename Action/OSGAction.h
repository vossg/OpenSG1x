/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGACTION_H_
#define _OSGACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainerType.h>
#include <OSGNodePtr.h>

#ifndef OSG_NOFUNCTORS
#include <OSGFunctors.h>
#endif

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class Node;
class Action;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \brief Action base class
 */

class OSG_SYSTEMLIB_DLLMAPPING Action 
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum ResultE
    {	
        Continue,	// continue with my children
	    Skip,		// skip my children
	    // really needed? Cancel, // skip my brothers, go one step up
	    Quit		// forget it, you're done
    };

#ifdef OSG_NOFUNCTORS
    typedef ResultE (*FunctorFunc)(CNodePtr &, Action *);

    struct Functor
    {
       public:

        FunctorFunc _func;

        virtual ResultE call(CNodePtr &cnode, Action *action)
        {
            return _func(cnode, action);
        }
    };

    static Functor osgFunctionFunctor2(FunctorFunc func)
    {
        Functor result;

        result._func = func;

        return result;
    }
#else
	typedef Functor2Base<ResultE, CNodePtr &, Action *> Functor;
#endif

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Action"; }

	// create a new action by cloning the prototype
	static Action * create( void );
	
	// prototype access
	// after setting the prototype all new actions are clones of it
	static void    setPrototype( Action * proto );
	static Action *getPrototype( void );
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~Action(void);

    /*------------------------- your_category -------------------------------*/
	
	// default registration. static, so it can be called during static init
	
	static void registerEnterDefault(	const FieldContainerType &type, 
										const Functor               &func);
	
	static void registerLeaveDefault(	const FieldContainerType &type, 
										const Functor               &func);

	// instance registration
	
	void registerEnterFunction(	const FieldContainerType &type, 
								const Functor               &func);
	
	void registerLeaveFunction(	const FieldContainerType &type, 
								const Functor               &func);

	// application

	virtual ResultE apply(vector<NodePtr>::iterator begin, 
                          vector<NodePtr>::iterator end);

	virtual ResultE apply(NodePtr node);

	
	// the node being traversed. Might be needed by the traversed core
	
	inline NodePtr getActNode( void );


	// Node access: 
	// the number of active nodes 
	
	UInt32 getNNodes( void ) const;
	
	// you can access a single node by getNode
	
	const NodePtr getNode( int index );
	
	// per default all child nodes are traversed. If addNode is called, only the 
	// added nodes will be traversed.
	
	void addNode( NodePtr node );

	// Common case: going through the children list and picking up some of them,
	// but it's not clear if any at all. Call useNodeList() and then
	// addNode() for every node to traverse, or not at all. 

	void useNodeList( void ); 

	// for debugging
	
	void printTable( void );
	
    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const Action &other);
    
	Bool operator == (const Action &other);
	Bool operator != (const Action &other);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// protected to allow derived access
    Action(void);
    Action(const Action &source);

	// call the single node. used for cascading actions
	
	inline ResultE callEnter( NodePtr node );	
	inline ResultE callLeave( NodePtr node );

	// start/stop functions for the action.
	// called at the very beginning/end, can return a list of nodes
	// via addNode() which is traversed before/after the traversal is done
	// main use: collecting actions use stop() to emit their collection
	
	virtual ResultE start( void );	
	virtual ResultE stop( ResultE res ); // res is the exit code of the action
	
	// recurse through the node
	
	ResultE recurse( NodePtr node );
	
	// call the _newList list of nodes
	
	ResultE callNewList( void );

	// access default functors

	virtual vector<Functor>* getDefaultEnterFunctors( void );
	virtual vector<Functor>* getDefaultLeaveFunctors( void );

	// default function
	
	static ResultE _defaultEnterFunction( CNodePtr &node, Action *action);
	static ResultE _defaultLeaveFunction( CNodePtr &node, Action *action);

	// functors
	// just protected, so that derived actions can access them
	
	vector<Functor> _enterFunctors;
	vector<Functor> _leaveFunctors;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	// the prototype which is copied to create new actions
	static Action * _prototype;
	
	// default functors for instantiation
	static vector<Functor> *_defaultEnterFunctors;
	static vector<Functor> *_defaultLeaveFunctors;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	NodePtr _actNode;			// the node being traversed right now
	
	vector<NodePtr>* _actList;	// list of active objects for this level
									// if empty, use the actNode's children

	bool 			_useNewList;// set by clearNodeList
	vector<NodePtr> _newList;	// list of active object for this level
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
	
	// helper functions for start/stop, that also call the results of start/stop
	
	ResultE callStart( void );
	ResultE callStop( ResultE res );

    Action& operator =(const Action &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Action *ActionP;

/*---------------------------------------------------------------------*/
/*! \name                    Traversal Functions                       */
/*! \{                                                                 */

#ifndef OSG_NOFUNCTORS

typedef Functor1Base<Action::ResultE, NodePtr &> TraverseFunctor;

OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE traverse(   NodePtr root, 
                            TraverseFunctor &func );
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE traverse(   vector<NodePtr> &list, 
                            TraverseFunctor &func );
                            
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE traverse(   NodePtr root, 
                            TraverseFunctor &enter, 
                            TraverseFunctor &leave );
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE traverse(   vector<NodePtr> &list, 
                            TraverseFunctor &enter, 
                            TraverseFunctor &leave );
#endif
                            
/*! \}                                                                 */

OSG_END_NAMESPACE

#include "OSGAction.inl"

#endif /* _OSGACTION_H_ */


