/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OSGBaseTypes.h>
#include <OSGFunctors.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class OSGNode;
class OSGAction;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \defgroup Action
 *  The tree traversals.
 */

/*! \defgroup ActionFunctions
 *  \ingroup Action
 *  The functions used to execute the actions
 */

/*! \ingroup Action
 *  \brief 
 *
 *  detailed
 */

class OSGAction 
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

	typedef enum {	Continue,	// continue with my children
					Skip,		// skip my children
					// really needed? Cancel, // skip my brothers, go one step up
					Quit		// forget it, you're done
	} ResultE;

	typedef OSGFunctor2Base<ResultE, OSGCNodePtr &, OSGAction *> Functor;

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGAction"; }

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGAction(void);

    virtual ~OSGAction(void);

    /*------------------------- your_category -------------------------------*/
	
	// default registration. static, so it can be called during static init
	
	static void registerEnterDefault(	const OSGFieldContainerType &type, 
										const Functor               &func);
	
	static void registerLeaveDefault(	const OSGFieldContainerType &type, 
										const Functor               &func);

	// instance registration
	
	void registerEnterFunction(	const OSGFieldContainerType &type, 
								const Functor               &func);
	
	void registerLeaveFunction(	const OSGFieldContainerType &type, 
								const Functor               &func);

	// application

	virtual ResultE apply(vector<OSGNodePtr>::iterator begin, 
                          vector<OSGNodePtr>::iterator end);

	virtual ResultE apply(OSGNodePtr node);

	
	// the node being traversed. Might be needed by the traversed core
	
	inline OSGNodePtr getActNode( void );


	// Node access: 
	// the number of active nodes 
	
	OSGUInt32 getNNodes( void ) const;
	
	// you can access a single node by getNode
	
	const OSGNodePtr getNode( int index );
	
	// per default all child nodes are traversed. If addNode is called, only the 
	// added nodes will be traversed.
	
	void addNode( OSGNodePtr node );

	// Common case: going through the children list and picking up some of them,
	// but it's not clear if any at all. Not clear how to do that nicely. 

	// 

	// for debugging
	
	void printTable( void );
	
    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGAction &other);
    
	OSGBool operator == (const OSGAction &other);
	OSGBool operator != (const OSGAction &other);

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

	// call the single node. used for cascading actions
	
	inline ResultE callEnter( OSGNodePtr node );	
	inline ResultE callLeave( OSGNodePtr node );

	// start/stop functions for the action.
	// called at the very beginning/end, can return a list of nodes
	// via addNode() which is traversed before/after the traversal is done
	// main use: collecting actions use stop() to emit their collection
	
	virtual ResultE start( void );	
	virtual ResultE stop( ResultE res ); // res is the exit code of the action
	
	// recurse through the node
	
	ResultE recurse( OSGNodePtr node );
	
	// call the _newList list of nodes
	
	ResultE callNewList( void );

	// default function
	
	static ResultE _defaultFunction( OSGCNodePtr &node, OSGAction *action);

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

	// default functors for instantiation
	static vector<Functor> *_defaultEnterFunctors;
	static vector<Functor> *_defaultLeaveFunctors;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	OSGNodePtr _actNode;			// the node being traversed right now
	
	vector<OSGNodePtr>* _actList;	// list of active objects for this level
									// if empty, use the actNode's children

	vector<OSGNodePtr> _newList;	// list of active object for this level
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
	
	// helper functions for start/stop, that also call the results of start/stop
	
	ResultE callStart( void );
	ResultE callStop( ResultE res );

	// prohibit default functions (move to 'public' if you need one)

    OSGAction(const OSGAction &source);
    OSGAction& operator =(const OSGAction &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGAction *OSGActionP;

OSG_END_NAMESPACE

#include "OSGAction.inl"

#endif /* _CLASSNAME_H_ */


