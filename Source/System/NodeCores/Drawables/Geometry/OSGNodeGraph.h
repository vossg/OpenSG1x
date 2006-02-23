/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

class NodeGraph
{
    /*==========================  PRIVATE  ================================*/
  private:

    enum WalkCase { START = -2, NEW = -1, LEFT = 0, RIGHT = 1, FINISH = 10 };

    class Edge;
    friend class Edge;

    class NodeList;
    friend class NodeList;

    class Node;
    friend class Node;

    class Edge
    {
        /*========================  PUBLIC  ===============================*/
      public:
        int     vertexStart;
        int     vertexEnd;
        Node   *node;
        Edge   *brotherEdge;
        int     edgeSide;
        
        /*-----------------------------------------------------------------*/
        /*! \name                 Constructors                             */
        /*! \{                                                             */
        
        Edge (void) {;}
        Edge (int vS, int vE, Node &n, int eS)
            : vertexStart(vS), vertexEnd(vE), node(&n), 
              brotherEdge(0), edgeSide(eS) {;}
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                     Set                                  */
        /*! \{                                                             */
        
        inline void set (int vS, int vE, Node &n, int eS) 
        {
            vertexStart = vS; vertexEnd = vE; node = &n; edgeSide = eS;
            brotherEdge = 0;
        }
        /*! \}                                                             */        
    };

    class NodeList
    {
        friend class Node;
        
        int           _degree;
        Node         *_first;
        Node         *_last;
        int           _size;
        NodeList     *_down;
        
        /*========================  PUBLIC  ===============================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name                 Constructors                             */
        /*! \{                                                             */
              
        NodeList (void)
            : _degree(0), _first(0), _last(0), _size(0), _down(0) {;}
      
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                     Class Specific                       */
        /*! \{                                                             */
      
        inline int          size        (void)           { return _size; }
        inline bool         empty       (void)           { return _size ? 
                                                           false : true; }
        inline NodeList    *down        (void)           { return _down; }
        inline void         setDown     (NodeList *down) { _down = down; }
        inline int          degree      (void)           { return _degree; }
        inline void         setDegree   (int degree)     { _degree = degree; }
        inline Node        *first       (void)           { return _first; }
        inline Node        *last        (void)           { return _last; }
        
        inline void push_back (Node &node)
        {
            node.release();
            if (_last) 
            {
                _last->next = &node;
                node.prev = _last;
                _last = &node;
            }
            else 
            {
                _last = &node;
                _first = &node;
            }
            _size++;
            node.list = this;
        }
        void push_front (Node &node)
        {
            node.release();
            if (_first)
            {
                _first->prev = &node;
                node.next = _first;
                _first = &node;
            }
            else
            {
                _last = &node;
                _first = &node;
            }
            _size++;
            node.list = this;
        }
        inline void add (Node &node, bool back)
            { back ? push_back(node) : push_front(node); }
        /*! \}                                                             */        
    };

    class Node 
    {
        /*========================  PUBLIC  ===============================*/
      public:
        int       index;      
        int       degree;     
        Node     *next;
        Node     *prev;
        NodeList *list;
        Edge     *edgeVec[3];
        int       vertex[3];  
        
        /*-----------------------------------------------------------------*/
        /*! \name                 Constructors                             */
        /*! \{                                                             */
        
        Node(void) : index(-1), degree(0), next(0), prev(0), list(0)
        {
            vertex[0] = vertex[1] = vertex[2] = 0;
            edgeVec[0] = edgeVec[1] = edgeVec[2] = 0;
        }
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                 Construction                             */
        /*! \{                                                             */
        
        
        inline void init (int i, int d, int v0, int v1, int v2)
        {
            index = i;
            degree = d;
            vertex[0] = v0;
            vertex[1] = v1;
            vertex[2] = v2;
        }
        
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                 Class Specific                           */
        /*! \{                                                             */

        inline void release(void)
        {
            if (list)
            {
                if (next)
                {
                    if (prev)
                    {
                        next->prev = prev;
                        prev->next = next;
                    }
                    else
                    {
                        next->prev = 0;
                        list->_first = next;
                    }
                }
                else
                {
                    if (prev)
                    {
                        prev->next = 0;
                        list->_last = prev;
                    }
                    else
                    {
                        list->_first = 0;
                        list->_last = 0;
                    }
                }
                list->_size--;
                next = prev = 0;
                list = 0;
            }
        }
        inline void drop (bool back)
        {
            if (list && list->_down)
                list->_down->add(*this,back);
        }
        inline void dropNeighbors (bool back)
        {
            int i;
            Edge *edge;
            for (i = 0; i < 3; i++)
                if ((edge = edgeVec[i]->brotherEdge))
                    edge->node->drop(back);
        };
        /*! \}                                                             */
    };

    typedef std::vector<Edge *> EdgeMap;

    std::vector<Node> _nodeVec;
    std::vector<EdgeMap> _edgeMapVec;
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Graph Specific                             */
    /*! \{                                                                 */
          
    inline Edge * getEdge (int vS, int vE)
    {
        EdgeMap &edgeMap = _edgeMapVec[vS];
        EdgeMap::iterator eI;
        Edge *edge = 0;

        for (eI = edgeMap.begin(); eI != edgeMap.end(); eI++)
            if ((*eI)->vertexEnd == vE)
            {
                edge = *eI;
                break;
            }

        return edge;
    }

    inline Edge & addEdge (int vS, int vE, Node &node, int eS )
    {
        Edge *edge = new Edge (vS,vE,node,eS);
        Edge *brotherEdge = getEdge(vE, vS);

        _edgeMapVec[vS].push_back(edge);

        if (brotherEdge)
        {
            edge->brotherEdge = brotherEdge;
            edge->node->degree++;
            brotherEdge->brotherEdge = edge;
            brotherEdge->node->degree++;
        }
        return *edge;
     }
     
    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    NodeGraph (void);
    NodeGraph (const NodeGraph &obj);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~NodeGraph (void);
    
    /*! \}                                                                 */    
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */
    void init(int vertexNum, int nodeNum, int reserveEdges );

    inline
    bool setNode (int index, int v0, int v1, int v2)
    {
        if (v0 != v1 && v1 != v2 && v2 != v0)
        {
            if (!getEdge(v0,v1) && !getEdge(v1,v2) && !getEdge(v2,v0))
            {                
                _nodeVec[index].init(index,0,v0,v1,v2);
                _nodeVec[index].edgeVec[0] = &addEdge(v0,v1,_nodeVec[index],0);
                _nodeVec[index].edgeVec[1] = &addEdge(v1,v2,_nodeVec[index],1);
                _nodeVec[index].edgeVec[2] = &addEdge(v2,v0,_nodeVec[index],2);
            }
            else 
            {
                _nodeVec[index].init(index,-1,v0,v1,v2);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    /*! \}                                                                 */        

    bool verify (bool printNotice = false );

    class Path
    {
        /*========================  PUBLIC  ===============================*/
      public:
        int            type;
        bool           flip;
        std::list<int> path;
        
        /*-----------------------------------------------------------------*/
        /*! \name                 Constructors                             */
        /*! \{                                                             */
        
        inline Path(void)
            : type(0), flip(false) {;}
        inline Path(const Path &obj)
            : type(obj.type),flip(obj.flip),path(obj.path) {;}

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                 Class Specific                           */
        /*! \{                                                             */
        
        inline void add( int elem)
            { flip ? path.push_front(elem) : path.push_back(elem); }
        inline void clear (void)
            { path.clear(); flip = false; type = 0;}
        inline void operator= (const Path &obj)
            { type = obj.type; flip = obj.flip; path = obj.path; }
        /*! \}                                                             */
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */
    
    int createPathVec (std::vector<Path> &stripVec,
                       bool createStrips = true, bool createFans = true,
                       int minFanEdgeCount = 8);
    
    /*! \}                                                                 */    

    class IndexEdge
    {
        /*========================  PUBLIC  ===============================*/        
      public:
        int v1;
        int v2;
        
        /*-----------------------------------------------------------------*/
        /*! \name                 Constructors                             */
        /*! \{                                                             */        
        
        IndexEdge  ( void) : v1(0), v2(0) {;}
        IndexEdge  ( int iv1, int iv2) : v1(iv1), v2(iv2) {;}
        IndexEdge  ( const IndexEdge &obj) : v1(obj.v1), v2(obj.v2) {;}
        
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                 Destructors                              */
        /*! \{                                                             */
        
        ~IndexEdge ( void) {;}
        
        /*! \}                                                             */        
    };

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */
    
    int getPrimitive  (     Path               &path, 
                       std::vector <int      > &primitive );        
    int getEdges      (std::list   <IndexEdge> &edgeList  );
    int getStartOfEdge(     int                 index, 
                            int                 side      )
    { 
        return _nodeVec[index].edgeVec[side]->vertexStart; 
    }
    int getEndOfEdge  (     int                 index, 
                            int                 side      )
    {
        return _nodeVec[index].edgeVec[side]->vertexEnd; 
    }
    
    /*! \}                                                                 */
    
    void clear        (void                               );
};

typedef NodeGraph* NodeGraphP;

#endif  // remove from all but dev docs

OSG_END_NAMESPACE

#endif // _OSGNODEGRAPH_H_
