
#include <fstream>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGLog.h>

#include "SplitGeoRec.h"
#include "VGrid.h"

OSG_USING_NAMESPACE

SplitGeoRec::SplitGeoRec(OSG::UInt32 nparts, VGrid * grid,
                         std::string basename) :
    _basename(basename), _nparts(nparts), _grid(grid)
{
    _outfiles.resize(nparts);
    
    for(UInt16 i = 0; i < nparts; ++i)
    {
        char name[basename.size() + 20];
        
        sprintf(name, "%s_%d.ooc", basename.c_str(), i);
        
        _outfiles[i] = new std::ofstream(name, 
                            std::ios::out|std::ios::binary); 
                            
        if(!_outfiles[i]->good())
        {
            FWARNING(("Problem opening file %s!\n", name));
        }
    }
    
    _clind = new std::ofstream((basename + "_clind.ooc").c_str(), 
                            std::ios::out|std::ios::binary); 
                            
    _nvert = 0;
}

void SplitGeoRec::print(std::ostream &str)
{
    str << "SplitGeoRec: " << _nvert << " points for " << _nparts 
        << " files. " << _fixups.size() << " fixups. ";
    if(_clind_raf)
        _clind_raf->print(str);
}

void SplitGeoRec::finish(void)
{   
    for(UInt16 i = 0; i < _nparts; ++i)
    {
        _outfiles[i]->flush();
        
       delete _outfiles[i];
    }
    
    if (_clind) 
        delete _clind;
    
    if (_clind_in) 
        delete _clind_in;
}

void SplitGeoRec::splitPnts(GeoReceiver *obj, const Pnt3f &pnt)
{
    SplitGeoRec *me = reinterpret_cast<SplitGeoRec *>(obj);

    UInt32 cell = me->_grid->map(pnt);
    UInt32 part = me->_grid->part(cell);
    
    std::ostream &s = *me->_outfiles[part];

    me->writePnt(s, me->_nvert, pnt);

    FDEBUG(("SplitGeoRec::splitPnts: writing %d (cell %d) to part %d\n", 
            me->_nvert, cell, part));
    
    if(!s.good())
    {
        FWARNING(("Problem writing to file for partition %d!\n", part));
    }
    
    // Write index mapping to cluster index file
    me->_clind->write(reinterpret_cast<const char*>(&cell), sizeof(cell));

    if(!me->_clind->good())
    {
        FWARNING(("Problem writing to clind file!\n"));
    }
    
    me->_nvert++;
}

void SplitGeoRec::finishPnts(OSG::UInt32 pagesize, OSG::UInt32 npages)
{       
    delete _clind;
    _clind = NULL;
    
    _clind_in = new std::ifstream((_basename + "_clind.ooc").c_str(), 
                            std::ios::in|std::ios::binary); 
    
    _clind_raf = new RAFile(*_clind_in, pagesize, npages);
    
    _fixups.clear();
    _index = 0;
}

void SplitGeoRec::splitTris(GeoReceiver *obj, 
                            OSG::UInt32 i1, OSG::UInt32 i2, OSG::UInt32 i3,
                            OSG::UInt32 mat)
{
    SplitGeoRec *me = reinterpret_cast<SplitGeoRec *>(obj);

    // Clusters of the triangle vertices
    OSG::UInt32 c1,c2,c3;

    c1 = me->_clind_raf->read(i1 * sizeof(OSG::UInt32));
    c2 = me->_clind_raf->read(i2 * sizeof(OSG::UInt32));
    c3 = me->_clind_raf->read(i3 * sizeof(OSG::UInt32));
   
    // All vertices in one partition?
    UInt32 part, p1, p2, p3;
    
    p1 = me->_grid->part(c1);
    p2 = me->_grid->part(c2);
    p3 = me->_grid->part(c3);
    
    if(p1 == p2 && p2 == p3)
    {
        // All points available, just output them
        part = p1;
    }
    else
    {
        // Pick lowest partition
        part = p1;
        
        if(p2 < part) part = p2;
        if(p3 < part) part = p3;
        
        // Find file
        std::ostream &s = *me->_outfiles[part];
        
        // Write Verts, if necessary
        if(p1 != part)
        {
            me->addFixup(part, s, i1);
        }
        if(p2 != part)
        {
            me->addFixup(part, s, i2);
        }
        if(p3 != part)
        {
            me->addFixup(part, s, i3);
        }
    }
 
    FDEBUG(("SplitGeoRec::splitTris: writing %d (%d,%d) %d (%d,%d) %d (%d,%d) to part %d\n", 
            i1,p1,c1, i2,p2,c2, i3,p3,c3, part));
   
    std::ostream &s = *me->_outfiles[part];
    me->writeTri(s, i1,i2,i3,mat);
}

void SplitGeoRec::fixPnts(GeoReceiver *obj, const Pnt3f &pnt)
{
    SplitGeoRec *me = reinterpret_cast<SplitGeoRec *>(obj);

    FixupMap::iterator it;
    if((it = me->_fixups.lower_bound(me->_index)) != me->_fixups.end())
    {
        FixupMap::iterator end = me->_fixups.upper_bound(me->_index);
        for(it; it != end; ++it)
        {
            UInt32 part = it->second.part;

            std::ostream &s = *me->_outfiles[part];

            s.seekp(it->second.offset, std::ios::beg);

            FDEBUG(("SplitGeoRec::fixPnts: fixing %d in partition %d "
                "at %d to (%.3f, %.3f, %.3f).\n", 
                me->_index, part, it->second.offset, pnt[0], pnt[1], pnt[2]));

            me->writePnt(s, me->_index, pnt);
        }
    }
    
    me->_index++;
}

void SplitGeoRec::finishFixups(void)
{       
    for(UInt16 i = 0; i < _nparts; ++i)
    {
        _outfiles[i]->flush();
    }
    _fixups.clear();
    delete _clind_raf;
    _clind_raf = NULL;
}

void SplitGeoRec::feedResults(OSG::UInt32 part, GeoReceiver *obj, 
                              pntRec pntfunc, triRec trifunc)
{
    char name[_basename.size() + 20];

    sprintf(name, "%s_%d.ooc", _basename.c_str(), part);

    std::ifstream s(name, std::ios::in|std::ios::binary);

    OSG::UInt32 vcnt = 0, tcnt = 0;

#ifdef OSG_STL_HAS_HASH_MAP
    typedef
       OSG_STDEXTENSION_NAMESPACE::hash_map<OSG::UInt32, OSG::UInt32> IndexMap;
#else
    typedef
       std::map<OSG::UInt32, OSG::UInt32> IndexMap;
#endif
    
    IndexMap indexMap;
    
    while(s.good() && ! s.eof())
    {
        OSG::UInt8 rec;
        
        s.read(reinterpret_cast<char*>(&rec), sizeof(rec));
        
        if(rec == PNT_RECORD)
        {
            OSG::Pnt3f pnt;
            OSG::UInt32 ind;
            
            s.read(reinterpret_cast<char*>(&ind), sizeof(ind));
            s.read(reinterpret_cast<char*>(&pnt), sizeof(Pnt3f));  
            
            pntfunc(obj, pnt);
            
            FDEBUG(("SplitGeoRec::feedResults: PNT(%d): added as %d\n",
                        vcnt, ind));
                        
            indexMap[ind] = vcnt++;
        }
        else if (rec == TRI_RECORD)
        {
            OSG::UInt32 i1,i2,i3,mat;
            
            s.read(reinterpret_cast<char*>(&i1), sizeof(i1));
            s.read(reinterpret_cast<char*>(&i2), sizeof(i2));
            s.read(reinterpret_cast<char*>(&i3), sizeof(i3));
            s.read(reinterpret_cast<char*>(&mat), sizeof(mat));
           
            FDEBUG(("SplitGeoRec::feedResults: TRI(%d): adding "
                    "%d(%d) %d(%d) %d(%d) (mat %d)\n",
                        tcnt, 
                        i1, (indexMap.find(i1)!=indexMap.end())?indexMap[i1]:888888888, 
                        i2, (indexMap.find(i2)!=indexMap.end())?indexMap[i2]:888888888, 
                        i3, (indexMap.find(i3)!=indexMap.end())?indexMap[i3]:888888888, 
                        mat
                    ));
             
            if(indexMap.find(i1) == indexMap.end())
            {
                FWARNING(("SplitGeoRec::feedResults: TRI(%d): Couldn't "
                    "find %d in the indexMap!\n", tcnt, i1));
            }
            if(indexMap.find(i2) == indexMap.end())
            {
                FWARNING(("SplitGeoRec::feedResults: TRI(%d): Couldn't "
                    "find %d in the indexMap!\n", tcnt, i2));
            }
            if(indexMap.find(i3) == indexMap.end())
            {
                FWARNING(("SplitGeoRec::feedResults: TRI(%d): Couldn't "
                    "find %d in the indexMap!\n", tcnt, i3));
            }
            
            trifunc(obj, indexMap[i1], indexMap[i2], indexMap[i3], mat);
            
            tcnt++;
        }
        else
        {
            FWARNING(("SplitGeoRec::feedResult: unknown record type '%d'!\n",
                        rec));
        }
    }
}
 

void SplitGeoRec::writePnt(std::ostream &s, OSG::UInt32 ind, const OSG::Pnt3f& pnt)
{
    static UInt8 rec = PNT_RECORD;   
    s.write(reinterpret_cast<const char*>(&rec), sizeof(rec));   
    s.write(reinterpret_cast<const char*>(&ind), sizeof(ind));
    s.write(reinterpret_cast<const char*>(&pnt), sizeof(Pnt3f));  
}

void SplitGeoRec::writeTri(std::ostream &s, OSG::UInt32 i1, OSG::UInt32 i2,
              OSG::UInt32 i3, OSG::UInt32 mat)
{
    static UInt8 rec = TRI_RECORD;   
    s.write(reinterpret_cast<const char*>(&rec), sizeof(rec));   
    s.write(reinterpret_cast<const char*>(&i1), sizeof(OSG::UInt32));   
    s.write(reinterpret_cast<const char*>(&i2), sizeof(OSG::UInt32));   
    s.write(reinterpret_cast<const char*>(&i3), sizeof(OSG::UInt32));   
    s.write(reinterpret_cast<const char*>(&mat), sizeof(OSG::UInt32));   
}

void SplitGeoRec::addFixup(OSG::UInt32 part, std::ostream &s, OSG::UInt32 ind)
{
    static Pnt3f dummy;
    
    // Do we already have this index and partition in the fixup list?
    FixupMap::iterator it;
    if((it = _fixups.lower_bound(ind)) != _fixups.end())
    {
        FixupMap::iterator end = _fixups.upper_bound(ind);
        for(it; it != end; ++it)
        {
            if(it->second.part == part)
                return;
        }
    }

    long o = s.tellp();

    FDEBUG(("SplitGeoRec::addFixup: adding fixup for %d in partition %d "
            "at %d.\n", ind, part, o));
    
    _fixups.insert(
        std::pair<OSG::UInt32, FixupRec>(ind, FixupRec(part, o, ind)));   

    writePnt(s, ind, dummy);
}
