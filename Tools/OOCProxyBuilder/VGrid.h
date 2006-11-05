// Vertex Grid Structure
// Stores a regular space grid keeping the number of vertices in
// the grid cells

#ifndef _VGRID_H
#define _VGRID_H

#include <ostream>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

#include "GeoReceiver.h"

OSG_USING_NAMESPACE;

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

class VGrid : public GeoReceiver
{
  public:
  
    VGrid(const Vec3f &bblow, const Vec3f &bbhigh, 
          UInt16 xdiv, UInt16 ydiv, UInt16 zdiv);
  
    VGrid(const Vec3f &bblow, const Vec3f &bbhigh, UInt32 nnodes);
    
    static void insert(GeoReceiver *rec, const Pnt3f &pnt);
    
    // Pnt-Grid mapping
    inline UInt32 map(const Pnt3f &pnt);
    inline Pnt3f unmap(UInt32 ind);

    // Grid node value access
    inline UInt32 nvert(UInt32 ind);
    inline UInt32 part(UInt32 ind);

    // Run partitioning
    void partition(int nparts);

    virtual void print(std::ostream &str);
    
  private:
                   
    struct VGNode
    {
        UInt32 nvert;   // number of vertices in this grid node
        UInt32 part;    // partition this grid node is part of
    };

#ifdef OSG_STL_HAS_HASH_MAP
    typedef
       OSG_STDEXTENSION_NAMESPACE::hash_map<UInt32, VGNode> NodeMap;
#else
    typedef
       std::map<UInt32, VGNode> NodeMap;
#endif
  
  
    void initialize(const Vec3f &bblow, const Vec3f &bbhigh, 
                    UInt16 xdiv, UInt16 ydiv, UInt16 zdiv);
     
    // Definition data: bbbox, ncells in x,y,z
    Vec3f _bblow, _bbhigh;
    UInt16 _xdiv, _ydiv, _zdiv;
    
    // Storage data
    NodeMap _map;
    
    // Derived data to speed up mapping
    Real32 _xbase,  _ybase,  _zbase;
    Real32 _xscale, _yscale, _zscale;
    UInt32 _ystep, _zstep;
    
};


#include "VGrid.inl"

#endif
