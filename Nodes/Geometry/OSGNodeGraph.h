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


#ifndef _OSGNODEGRAPH_H_
#define _OSGNODEGRAPH_H_
#ifdef __sgi
#pragma once
#endif

#include <list>
#include <vector>
#include <map>  
#include <iterator>

#include <OSGConfig.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE;


class NodeGraph {

private:

	enum WalkCase { START = -2, NEW = -1, LEFT = 0, RIGHT = 1, FINISH = 10 };     
	class Node;

	class Edge {
	public:
		int vertexStart;
		int vertexEnd;
		Node *node;
		Edge *brotherEdge;
		int edgeSide;
		Edge (void) {;}
		Edge (int vS, int vE, Node &n, int eS)
			: vertexStart(vS), vertexEnd(vE), node(&n), brotherEdge(0), edgeSide(eS)
			{;}
		inline void set (int vS, int vE, Node &n, int eS) {
			vertexStart = vS; vertexEnd = vE; node = &n; edgeSide = eS;
			brotherEdge = 0;
		}
	};                           

	class NodeList {
		friend class Node;
		int _degree;
		Node *_first;
		Node *_last;
		int _size;
		NodeList *_down;
	public:
		NodeList (void)
			: _degree(0), _first(0), _last(0), _size(0), _down(0) {;}
		inline int size(void) { return _size; }
		inline bool empty(void) { return _size ? false : true; }
		inline NodeList * down(void) { return _down; }
		inline void setDown (NodeList *down) { _down = down; }
		inline int degree(void) { return _degree; }
		inline void setDegree (int degree) { _degree = degree; }
		inline Node *first(void) { return _first; }
		inline Node *last(void) { return _last; }
		inline void push_back (Node &node) {
			node.release();
			if (_last) {
				_last->next = &node;
				node.prev = _last;
				_last = &node;
			}
			else {
				_last = &node;
				_first = &node;
			}
			_size++;
			node.list = this;
		}
		void push_front (Node &node) {
			node.release();
			if (_first) {
				_first->prev = &node;
				node.next = _first;
				_first = &node;
			}
			else {
				_last = &node;
				_first = &node;
			}
			_size++;
			node.list = this;
		}
		inline void add (Node &node, bool back ) 
			{ back ? push_back(node) : push_front(node); }
		
	};
	
	class Node {
	public:
		int index;
		int degree;
		Node *next;
		Node *prev;
		NodeList *list;
		Edge * edgeVec[3];
		Node(void) : index(-1), degree(0), next(0), prev(0), list(0) 
			{ edgeVec[0] = edgeVec[1] = edgeVec[2] = 0; }
		inline void release(void) {
			if (list) {
				if (next) {
					if (prev) {
						next->prev = prev;
						prev->next = next;
					}
					else {
						next->prev = 0;
						list->_first = next;
					}
				}
				else {
					if (prev) {
						prev->next = 0;
						list->_last = prev;
					}
					else {
						list->_first = 0;
						list->_last = 0;
					}
				}
				list->_size--;
				next = prev = 0;
				list = 0;
			}
		}
		inline void drop (bool back) {
			if (list && list->_down) 
				list->_down->add(*this,back);
		}
		inline void dropNeighbors (bool back) {
			int i;
			Edge *edge;
			for (i = 0; i < 3; i++)
				if ((edge = edgeVec[i]->brotherEdge))
					edge->node->drop(back);
		};
	};

	typedef std::vector<Edge *> EdgeMap;        

	std::vector<Node> _nodeVec;
	std::vector<EdgeMap> _edgeMapVec;     

protected:

	inline Edge * getEdge (int vS, int vE) {
		EdgeMap &edgeMap = _edgeMapVec[vS];
		EdgeMap::iterator eI;
		Edge *edge = 0;

		for (eI = edgeMap.begin(); eI != edgeMap.end(); eI++)
			if ((*eI)->vertexEnd == vE) {
				edge = *eI;
				break;
			}
		
		return edge;
	}
	
	inline Edge & addEdge (int vS, int vE, Node &node, int eS ) {
		Edge *edge = new Edge (vS,vE,node,eS);
		Edge *brotherEdge = getEdge(vE, vS);

		_edgeMapVec[vS].push_back(edge);
		
		if (brotherEdge) {
			edge->brotherEdge = brotherEdge;
			edge->node->degree++;
			brotherEdge->brotherEdge = edge;
      brotherEdge->node->degree++;
		}
		
		 return *edge;
	 }   
                             
public:

  /** Default Constructor */
  NodeGraph (void);

  /** Copy Constructor */
  NodeGraph (const NodeGraph &obj);

  /** Destructor */
  virtual ~NodeGraph (void);

	/**  */
	void init(int vertexNum, int nodeNum, int reserveEdges );

  /**  */
	inline 
    void addNode (int index, int v0, int v1, int v2)
		{
      if (v0 != v1 && v1 != v2 && v2 != v1) {
        if (!getEdge(v0,v1) && !getEdge(v1,v2) && !getEdge(v2,v0)) {
          _nodeVec[index].index = index;
          _nodeVec[index].edgeVec[0] = &addEdge(v0,v1,_nodeVec[index],0);
          _nodeVec[index].edgeVec[1] = &addEdge(v1,v2,_nodeVec[index],1);
          _nodeVec[index].edgeVec[2] = &addEdge(v2,v0,_nodeVec[index],2);
        }
        else {
          FWARNING (("nonManifold mesh \n"));
        }
      }
      else {
        FWARNING (("Invalid triangle: %d/%d/%d\n", v0,v1,v2));
      }
    }

  /**  */
  bool verify (void);

	class Path {
	public:
		std::list<int> path;
		bool flip;
		Path(void) { clear();}
		inline void add( int elem) { flip ? path.push_front(elem) :
			path.push_back(elem); }
		inline void clear (void) { path.clear(); flip = false; }			
	};        
		
  /**  */
  int createPathVec ( std::vector<Path> &stripVec, bool randomize = false );
	
	/**  */
	int getPrimitive ( Path &path, std::vector <int> &primitive );
                                                      
	/**  */
	class IndexEdge {
	public:
		int v1;
		int v2;
		IndexEdge  ( void) : v1(0), v2(0) {;}
		IndexEdge  ( int iv1, int iv2) : v1(iv1), v2(iv2) {;}
		IndexEdge  ( const IndexEdge &obj) : v1(obj.v1), v2(obj.v2) {;}
		~IndexEdge ( void) {;}
	};
			
	int getEdges (std::list <IndexEdge> & edgeList);

	inline int getStartOfEdge (int index, int side) 
		{ return _nodeVec[index].edgeVec[side]->vertexStart; }

	inline int getEndOfEdge (int index, int side) 
		{ return _nodeVec[index].edgeVec[side]->vertexEnd; }

	void clear (void);

};

typedef NodeGraph* NodeGraphP;

OSG_END_NAMESPACE;

#endif // _OSGNODEGRAPH_H_
