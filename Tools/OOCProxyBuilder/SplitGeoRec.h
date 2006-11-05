// A very simple GeoReceiver that counts points and calculates the
// bounding box

#ifndef _SPLITGEOREC_H
#define _SPLITGEOREC_H

#include <ostream>
#include <istream>
#include <string>
#include <vector>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

#include <map>

#include "GeoReceiver.h"
#include "RAFile.h"

class VGrid;

class SplitGeoRec : public GeoReceiver
{
  public:
  
    enum { PNT_RECORD = 1, TRI_RECORD };
    
    SplitGeoRec(OSG::UInt32 nparts, VGrid * grid,
                std::string basename);
    
    static void splitPnts(GeoReceiver *obj, const OSG::Pnt3f &pnt);
   
    // cleanup stuff after all points are done
    void finishPnts(OSG::UInt32 pagesize = 512, OSG::UInt32 npages = 1024);
    
    static void splitTris(GeoReceiver *obj, 
                          OSG::UInt32 i1, OSG::UInt32 i2, OSG::UInt32 i3, 
                          OSG::UInt32 mat);
    
    static void fixPnts(GeoReceiver *obj, const OSG::Pnt3f &pnt);
   
    // cleanup stuff after all fixups are done
    void finishFixups(void);
       
    // Result access
    void feedResults(OSG::UInt32 part, GeoReceiver *obj, 
                     pntRec pntfunc, triRec trifunc);
    
    // Cleanup
    void finish(void);
     
    void print(std::ostream &str);

  private:

    // Definition data
    OSG::UInt32 _nparts;
    VGrid *_grid;
    std::string _basename;
    
    // Work data
    std::ofstream *_clind;
    std::ifstream *_clind_in;
    RAFile *_clind_raf;
    
    OSG::UInt32 _nvert;
    OSG::UInt32 _index;
    
    std::vector<std::ostream*> _outfiles;
    std::vector<OSG::UInt32>   _outmats;    // Current material of outfile
 
    struct FixupRec
    {
        FixupRec() : part(0), offset(0), index(0) 
        {}
        
        FixupRec(OSG::UInt32 p, long o, OSG::UInt32 i) : 
            part(p), offset(o), index(i) 
        {}
        
        OSG::UInt32 part;
        long offset;
        OSG::UInt32 index;
    };

    typedef std::multimap<OSG::UInt32, FixupRec> FixupMap;
     
    FixupMap _fixups;
    
    // Helper methods
    
    void writePnt(std::ostream &str, OSG::UInt32 ind, const OSG::Pnt3f& pnt);
    void writeTri(std::ostream &str, OSG::UInt32 i1, OSG::UInt32 i2,
                  OSG::UInt32 i3, OSG::UInt32 mat);
    void addFixup(OSG::UInt32 part, std::ostream &s, OSG::UInt32 ind);
    
};


#endif
