
#include <OSGConfig.h>

// System declarations
#include <iostream>
#include <stdlib.h>

#include <OSGGL.h>

// Application declarations


// Class declarations
#include "OSGNodeGraph.h"


using namespace std;

OSG_USING_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)


// Static Class Variable implementations: 


//----------------------------------------------------------------------
// Method: NodeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Default Constructor
//----------------------------------------------------------------------
NodeGraph::NodeGraph (void)
{
    ;
}          

//----------------------------------------------------------------------
// Method: NodeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
NodeGraph::NodeGraph (const NodeGraph &obj )
    : _nodeVec(obj._nodeVec), _edgeMapVec(obj._edgeMapVec)
{
    return;
}

//----------------------------------------------------------------------
// Method: ~NodeGraph
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
NodeGraph::~NodeGraph (void )
{
    clear();
}

//----------------------------------------------------------------------
// Method: init
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
void NodeGraph::init ( int vertexNum, int nodeNum, int reserveEdges )
{
  int i;

    _nodeVec   .resize(nodeNum  ); 
    _edgeMapVec.resize(vertexNum); 

  if(reserveEdges > 0) 
  {
      for(i = 0; i < vertexNum; i++) 
      {
          _edgeMapVec[i].reserve(reserveEdges);
      }
  }
}


//----------------------------------------------------------------------
// Method: verify
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
bool NodeGraph::verify (bool printInfo )
{
    bool retCode = true;
    int i, n = _nodeVec.size(); 
    vector<int> nodeDegree(5,0);
    int edgeCount = 0;
    map< int, int > connectionMap;
    map< int, int >::iterator connectionI;
    unsigned nonManifoldCount = 0;

    for (i = 0; i < n; i++)
        if (_nodeVec[i].index == i)
        {
            if(_nodeVec[i].degree >= 0 && _nodeVec[i].degree < 4)
            {
                nodeDegree[_nodeVec[i].degree]++;
            }
            else
            {
              if (_nodeVec[i].degree == -1)
                nonManifoldCount++;
              else
              {
                FFATAL (( "Invalid degree %d in node %d\n", 
                          _nodeVec[i].degree, i ));
              }
            }
        }
        else
            if (_nodeVec[i].index == -1)
                nodeDegree[4]++;
            else {
        FFATAL (( "Invalid node index %d for face %d\n",
                  _nodeVec[i].index, i ));
                retCode = false;
            }

    if (printInfo) {
      FNOTICE (( "NodeDegree Count:  %d %d %d %d (%d)\n",
                 nodeDegree[0], nodeDegree[1], nodeDegree[2], nodeDegree[3],
                 nodeDegree[4] ));

      n = _edgeMapVec.size();
      for (i = 0; i < n; i++) 
        edgeCount += _edgeMapVec[i].size();

      FNOTICE (( "NonManifold split: %d\n", nonManifoldCount ));
      FNOTICE (( "HalfEdgeCount:     %d\n", edgeCount ));
    }
 
    return retCode;
}

// macro to compile randomization in and out -- just for debuging
#ifndef WIN32
#define RANDBOOL (random() & 1)
#else
#define RANDBOOL (rand() & 1)
#endif

//#define RANDBOOL true

//----------------------------------------------------------------------
// Method: createPathVec
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
int NodeGraph::createPathVec (vector<Path> &pathVec,
                              bool OSG_CHECK_ARG(createStrips   ), 
                              bool OSG_CHECK_ARG(createFans     ),
                              int  OSG_CHECK_ARG(minFanEdgeCount))
{
    NodeList nodeList[4], nonManifoldList, *down = 0;
  int i,n = _nodeVec.size();
    int frontToBackCost, backToFrontCost, cost = 0, nodeLeft = 0;
    WalkCase walkCase = START, firstTurn = START;
    int degree, lowDegree, entrySide, exitSide;
    int pathI = -1;
    Node *currentNode = 0, *nextNode = 0;
    Edge *firstEdge = 0, *lastEdge = 0, *brotherEdge = 0;
    bool tryFlip = true;
    int stayCounter = 0, reverseCounter = 0;
    list<int>::iterator listI;
    list<int>::reverse_iterator listRI;
    int pathCost = 0;
    int pathEntrySide, pathExitSide;
    bool pathWalkRight;

    down = 0;
    for (i = 0; i < 4; i++) {
        nodeList[i].setDown(down);
        nodeList[i].setDegree(i);
        down = &nodeList[i];
    }

  for (i = 0; i < n; i++)
    if (_nodeVec[i].index >= 0) {
      degree = _nodeVec[i].degree;
      if (degree >= 0) {
        nodeList[degree].add( _nodeVec[i], RANDBOOL );
        nodeLeft++;
      }
      else {
        nonManifoldList.push_back( _nodeVec[i] );
      }
    }

    if ((nodeList[1].size() + nodeList[2].size() + nodeList[3].size()) == 0) {
        FINFO (("Geometry without any shared vertex, skipping opt.\n"));
        nodeLeft = 0;
    }

    while(nodeLeft || (walkCase == NEW) || (walkCase == FINISH)) {
        switch (walkCase) {
        case START:
            pathI++;
            tryFlip = true;
            pathVec[pathI].clear();
            // find first node
            for (lowDegree = 0; lowDegree < 4; lowDegree++)
                if ((currentNode = nodeList[lowDegree].first()))
                    break;
            // write node
            pathVec[pathI].add(currentNode->index);
            currentNode->release();
            currentNode->dropNeighbors( RANDBOOL );
            cost += 3;
            walkCase = NEW;
            nodeLeft--;
            break;
        case NEW:
          nextNode = 0;
            for (i = 0; i < 3; i++) {
                brotherEdge = currentNode->edgeVec[i]->brotherEdge;
                if (brotherEdge)
                    if ( brotherEdge->node->list &&
                             (!nextNode || (nextNode->list->degree() 
                                                            > brotherEdge->node->list->degree()))) {
                        nextNode = brotherEdge->node;
                        lastEdge = brotherEdge;
                        firstEdge = lastEdge->brotherEdge;
                    }
            }
            if (nextNode) {
        // triangle strip
        pathVec[pathI].type = GL_TRIANGLE_STRIP;
                pathVec[pathI].add(firstEdge->edgeSide);    
                pathVec[pathI].add(lastEdge->edgeSide);                     
                pathVec[pathI].add(nextNode->index);
                nextNode->release();
                nextNode->dropNeighbors( RANDBOOL );
                cost++;
                walkCase = RIGHT;
                nodeLeft--;
                firstTurn = START;
            }
            else {
        // single triangle 
        pathVec[pathI].type = GL_TRIANGLES;
                walkCase = START;
            }
            break;          
        case LEFT:
        case RIGHT:
            currentNode = lastEdge->node;
            entrySide = lastEdge->edgeSide;
            for (i = 0; i < 2; i++) {
                exitSide = ( entrySide + 1 + ((i + int(walkCase)) & 1)  ) % 3;
                if ( (brotherEdge = currentNode->edgeVec[exitSide]->brotherEdge) &&
                         (nextNode = brotherEdge->node) && nextNode->list ) {
                    // write node
                    lastEdge = currentNode->edgeVec[exitSide]->brotherEdge;
                    pathVec[pathI].add(exitSide);
                    pathVec[pathI].add(lastEdge->edgeSide);
                    pathVec[pathI].add(nextNode->index);
                    nextNode->release();
                    nextNode->dropNeighbors( RANDBOOL );
                    walkCase = i ? walkCase : WalkCase((int(walkCase)+1) & 1);
                    nodeLeft--;
                    if (firstTurn == START) 
                        firstTurn = ((exitSide+2)%3 == entrySide) ? LEFT : RIGHT;
                    break;
                }
            }       
            if (i == 2) {
                if (tryFlip) {
                    walkCase = firstTurn;
                    lastEdge = firstEdge;
                    pathVec[pathI].flip = true;
                    tryFlip = false;
                }
                else 
                    walkCase = FINISH;
            }
            else 
                if (!nodeLeft)
                    walkCase = FINISH;
            break;
        case FINISH:
            // check front to back
            pathCost = 0;
            listI = pathVec[pathI].path.begin();
            listI++;
            listI++;
            pathEntrySide = *listI++;
            listI++;
            pathWalkRight = true;
            pathCost += 3;
            while ( listI != pathVec[pathI].path.end()) {
                pathCost++;
                pathExitSide = *listI++;
                if (pathWalkRight == true) {
                    if (((pathEntrySide+1)%3 == pathExitSide)) 
                        pathCost++;
                    else
                        pathWalkRight = false;
                }
                else {
                    if ((pathEntrySide+1)%3 == pathExitSide) 
                        pathWalkRight = true;
                    else 
                        pathCost++;
                }
                pathEntrySide = *listI++;
                *listI++;
            }
            frontToBackCost = ++pathCost;
            
            // check back to front
            pathCost = 0;
            listRI = pathVec[pathI].path.rbegin();
            listRI++;
            listRI++;
            pathEntrySide = *listRI++;
            listRI++;
            pathWalkRight = true;
            pathCost += 3;
            while ( listRI != pathVec[pathI].path.rend()) {
                pathCost++;
                pathExitSide = *listRI++;
                if (pathWalkRight == true) {
                    if (((pathEntrySide+1)%3 == pathExitSide)) 
                        pathCost++;
                    else 
                        pathWalkRight = false;
                }
                else {
                    if ((pathEntrySide+1)%3 == pathExitSide) 
                        pathWalkRight = true;
                    else 
                        pathCost++;
                }
                pathEntrySide = *listRI++;
                *listRI++;
            }
            backToFrontCost = ++pathCost;
            
            // select the best direction
            if (frontToBackCost > backToFrontCost) {
                reverseCounter++;
                pathVec[pathI].flip = true;
                //pathVec[pathI].reverse();
                cost += backToFrontCost - 4;
            }
            else {
                stayCounter++;
                pathVec[pathI].flip = false;
                cost += frontToBackCost - 4;
            }
            walkCase = START;
            break;
        default:
            break;
        }
    }

  if (cost) {
    if ((currentNode = nonManifoldList.first())) {
      FNOTICE (( "Optimize nonmanifold mesh: buffer %d triangles\n",
                 nonManifoldList.size() ));
      pathVec[++pathI].type = GL_TRIANGLES;
      for ( ; currentNode; currentNode = currentNode->next ) {
        cost += 3;
        pathVec[pathI].path.push_back(currentNode->index);
      }
    }
    pathVec[++pathI].clear();
  }

  return cost;
}                                                  

//----------------------------------------------------------------------
// Method: getPrimitive
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         return the cost of the face vec
//----------------------------------------------------------------------
int NodeGraph::getPrimitive ( Path &path, vector< int > & primitive )
{
    int pi;
    unsigned j, cost = 0;
    int index, firstIndex, firstSide, entrySide, exitSide;
    Node *node;
    bool walkRight;
    list<int>::iterator listI;
    list<int>::reverse_iterator listRI;

  primitive.clear();

  if (path.path.empty())
    cost = 0;
  else {

    if (path.type == GL_TRIANGLES) {
      // triangle

      for (listI = path.path.begin(); listI != path.path.end(); ++listI) {
        node = &(_nodeVec[*listI]);
        primitive.push_back(node->vertex[0]);
        primitive.push_back(node->vertex[1]);
        primitive.push_back(node->vertex[2]);
        cost += 3;
      }
    }
    else { 
      // triangle strip

      if (path.flip) {
        listRI = path.path.rbegin();
        firstIndex = *listRI++;
        firstSide = *listRI++; 
        entrySide = *listRI++;
        index = *listRI++;
        walkRight = true;
        cost += 3;
        for (j = 0; j < 3; j++) {
          pi = getEndOfEdge(firstIndex,(firstSide+1+j) % 3);
          primitive.push_back(pi);
        }
        while ( listRI != path.path.rend()) {
          exitSide = *listRI++;
          if (walkRight == true) {
            if (((entrySide+1)%3 == exitSide)) {
              pi = getEndOfEdge(index,entrySide);
              primitive.push_back(pi);
              pi = getEndOfEdge(index,exitSide);
              primitive.push_back(pi);
              cost += 2;
            }
            else
              if (((entrySide+2)%3 == exitSide)) {
                walkRight = false;
                pi = getStartOfEdge(index,exitSide);
                primitive.push_back(pi);
                cost++;
              }
              else
                cerr << "ERROR: entrySide == exitSide" << endl;
          }
          else {
            if ((entrySide+1)%3 == exitSide) {
              walkRight = true;
              pi = getEndOfEdge(index,exitSide);
              primitive.push_back(pi);
              cost++;
            }
            else 
              if ((entrySide+2)%3 == exitSide) {
                pi = getStartOfEdge(index,entrySide);
                primitive.push_back(pi);
                pi = getStartOfEdge(index,exitSide);
                primitive.push_back(pi);
                cost += 2;
              }
              else
                cerr << "ERROR: entrySide == exitSide" << endl;
          }
          entrySide = *listRI++;
          index = *listRI++;
        }
        pi = getEndOfEdge(index,(entrySide+1)%3);
        primitive.push_back(pi);
        cost++;
      }
      else {
        listI = path.path.begin();
        firstIndex = *listI++;
        firstSide = *listI++; 
        entrySide = *listI++;
        index = *listI++;
        walkRight = true;
        cost += 3;
        for (j = 0; j < 3; j++) {
          pi = getEndOfEdge(firstIndex,(firstSide+1+j) % 3);
          primitive.push_back(pi);
        }
        while ( listI != path.path.end()) {
          exitSide = *listI++;
          if (walkRight == true) {
            if (((entrySide+1)%3 == exitSide)) {
              pi = getEndOfEdge(index,entrySide);
              primitive.push_back(pi);
              pi = getEndOfEdge(index,exitSide);
              primitive.push_back(pi);
              cost += 2;
            }
            else
              if (((entrySide+2)%3 == exitSide)) {
                walkRight = false;
                pi = getStartOfEdge(index,exitSide);
                primitive.push_back(pi);
                cost++;
              }
              else
                cerr << "ERROR: entrySide == exitSide" << endl;
          }
          else {
            if ((entrySide+1)%3 == exitSide) {
              walkRight = true;
              pi = getEndOfEdge(index,exitSide);
              primitive.push_back(pi);
              cost++;
            }
            else 
              if ((entrySide+2)%3 == exitSide) {
                pi = getStartOfEdge(index,entrySide);
                primitive.push_back(pi);
                pi = getStartOfEdge(index,exitSide);
                primitive.push_back(pi);
                cost += 2;
              }
              else
                cerr << "ERROR: entrySide == exitSide" << endl;
          }
          entrySide = *listI++;
          index = *listI++;
        }
        pi = getEndOfEdge(index,(entrySide+1)%3);
        primitive.push_back(pi);
        cost++;
      }
    }
  }
  
    return cost;
}


//----------------------------------------------------------------------
// Method: getEdges
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description
//         
//----------------------------------------------------------------------
int NodeGraph::getEdges (list <IndexEdge> & edgeList)
{
    int i, n;
    EdgeMap::iterator eMI;
    int vs, ve;
    n = _edgeMapVec.size();
    int edgeCount = 0;

    for (i = 0; i < n; i++)
        for ( eMI = _edgeMapVec[i].begin(); eMI != _edgeMapVec[i].end(); ++eMI) {
            vs = (*eMI)->vertexStart;
            ve = (*eMI)->vertexEnd;

            if (!(*eMI)->brotherEdge || (ve < vs)) {
                edgeList.push_back ( IndexEdge(ve,vs) );
                edgeCount++;
            }
        }

    return edgeCount;
}

//----------------------------------------------------------------------
// Method: clear
// Author: jbehr
// Date:   Tue Feb 15 18:16:59 2000
// Description:
//         
//----------------------------------------------------------------------
void NodeGraph::clear (void)
{
  EdgeMap::iterator eI;
  int i, n = _edgeMapVec.size();

  for (i = 0; i < n; i++) {
    for (eI = _edgeMapVec[i].begin(); eI != _edgeMapVec[i].end(); ++eI)
      delete (*eI);
  }                

    _edgeMapVec.clear();
    _nodeVec.clear();
}


#endif  // remove from all but dev docs
