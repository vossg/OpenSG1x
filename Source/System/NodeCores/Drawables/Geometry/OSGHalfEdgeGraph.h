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

#ifndef _OSGHALFEDGEGRAPH_H_
#define _OSGHALFEDGEGRAPH_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <iterator>

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include <OSGBaseTypes.h>

#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

class OSG_SYSTEMLIB_DLLMAPPING HalfEdgeGraph
{
  public:

    typedef UInt32 IndexT;

  private:

    enum TriangleState { INVALID = -30, FAN_PART = -20, STRIP_PART = -10,
                         DEGREE_0 = 0, DEGREE_1 = 1, DEGREE_2 = 2,
                         DEGREE_3 = 3 };

    enum WalkCase { START, LEFT, RIGHT, FINISH };

    class HalfEdge;
    class Triangle;
    class TriangleList;
    class TrianglePool;
    
    friend class HalfEdge;
    friend class Triangle;
    friend class TriangleList;
    friend class TrianglePool;
    
    class HalfEdge
    {
        IndexT _vertexIndex;

      public:

        Triangle *triangle;
        HalfEdge *twin;
        HalfEdge *next;

        inline void     setVertex(IndexT startVertexIndex,
                                  IndexT endVertexIndex);
        inline IndexT   vertexStart(void);
        inline IndexT   vertexEnd(void);
    };

    class Triangle
    {
      public:

        Int32 state;
        Triangle *next;
        Triangle *prev;
        HalfEdge halfEdgeVec[3];

        inline void init(void);
        inline bool valid (void);
        inline void resetDegreeState (const Int32 type);
        inline void drop(void);
        bool verify (void);
    };

    class TriangleList
    {

      public:

        Triangle *first;
        Triangle *last;

        inline TriangleList(void);

        inline void     reset(void);
        inline bool     empty(void);
        inline UInt32 countElem(void);

        inline void     release(Triangle &node);
        inline void     add (Triangle &triangle);
        inline void     paste (TriangleList &list);
    };

    inline void dropOutTriangle(Triangle &triangle,
                                TriangleList *degreeBag);

    class TrianglePool
    {
      public:

        class Chunk;

        inline TrianglePool (UInt32 chunkSize = DEFAULT_CHUNK_SIZE);
        inline ~TrianglePool(void);

        inline Triangle *createTriangle(void);
        inline void clear(void);
        inline UInt32 countElem (void);
        inline void setChunkSize(UInt32 chunkSize = DEFAULT_CHUNK_SIZE);
    
      private:
      
        enum { DEFAULT_CHUNK_SIZE = 2048 };
        
        UInt32 _defaultChunkSize;
        Chunk *_first;
        Chunk *_last;   

 
    };

    friend class TrianglePool::Chunk;
    
    // temporary vector data structure
    typedef std::vector < std::pair<UInt32,HalfEdge *> > HalfEdgeLink;
    std::vector<HalfEdgeLink> _edgeLinkVec;

    // Triangle Data Pool
    TrianglePool _trianglePool;

    // Input
    TriangleList _validTriangleBag;
    TriangleList _invalidTriangleBag;

    // Output
    typedef std::pair<IndexT,TriangleList*> Primitive;
    std::vector<Primitive> _stripBag;
    std::vector<Primitive> _fanBag;
    std::vector<Primitive> _triBag;

  protected:

    inline HalfEdge *getHalfEdge(UInt32 startVertexIndex,
                                 UInt32 endVertexIndex);
    inline void     addHalfEdge(HalfEdge &halfEdge, UInt32 startVertexIndex,
                                UInt32 endVertexIndex);
    inline HalfEdge *findGateEdge(Triangle *triangleOut,
                                  Triangle *triangleIn);

    Int32 calcStripCost(TriangleList &strip, bool reverse);
    Int32 fillIndexFromFan(std::vector<IndexT> &indexVec, HalfEdge &firstEdge);
    Int32 fillIndexFromStrip(std::vector<IndexT> &indexVec, TriangleList &strip, 
                             bool reverse );

 public:

    HalfEdgeGraph(void);

    HalfEdgeGraph(const HalfEdgeGraph &obj);
 
    virtual ~HalfEdgeGraph (void);

    void reserve(UInt32 vertexNum, UInt32 triangleNum, 
                 UInt32 reserveEdges = 8 );

    inline bool     addTriangle(IndexT v0, IndexT v1, IndexT v2);
    inline UInt32 triangleCount(void);

    bool verify (bool verbose = false);

    UInt32 calcOptPrim(UInt32 iteration = 1, bool doStrip = true,
                       bool doFan = true, UInt32 minFanTriangleCount = 16, bool stripifyIsolatedTris = false);

    inline UInt32 primitiveCount(void);

    Int32 getPrimitive(std::vector<IndexT> & indexVec, Int32 type = 0);
    Int32 calcEgdeLines(std::vector<IndexT> & indexVec, bool codeBorder = false);

    void clear(void);

};

class HalfEdgeGraph::TrianglePool::Chunk
{
    public:
    const UInt32 _size;
    UInt32 _freeElem;
    Chunk *_next;
    Triangle *_data;

    inline Chunk (const UInt32 size);
    inline ~Chunk (void);
    inline UInt32 countElem(void);
};

typedef HalfEdgeGraph* HalfEdgeGraphP;

#endif  // remove from all but dev docs

OSG_END_NAMESPACE

#include "OSGHalfEdgeGraph.inl"

#endif // _OSGHALFEDGEGRAPH_H_
