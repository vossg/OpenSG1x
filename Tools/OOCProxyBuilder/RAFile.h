// RAFile: an efficient random access file class. 

#ifndef _RAFILE_H
#define _RAFILE_H

#include <fstream>
#include <vector>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>

class RAFile
{
  public:
  
    RAFile(std::ifstream &str, OSG::UInt32 pagesize = 512, 
                               OSG::UInt32 npages = 1024);
  
    ~RAFile();
    
    void read(unsigned long offset, OSG::UInt8 *data, unsigned int size);
    
    // Pure convenience function...
    OSG::UInt32 read(unsigned long offset);
    
    inline OSG::UInt32 getPagesize(void);  
    inline OSG::UInt32 getNPages(void);
        
    void print(std::ostream &str);
    
  private:
  
    inline bool split(unsigned long offset, 
                      OSG::UInt32 &page, OSG::UInt32 &poffset);
    
    class Page;
    
    Page *findPage(OSG::UInt32 page);
  
    void dump(std::ostream &str);
    
    // Size of file
    std::ifstream &_str;
    unsigned long _size;    

    OSG::UInt32 _pagesize;
    OSG::UInt32 _npages;
    
    static OSG::UInt32 _invalidPage;
    
    class Page
    {
      public:
      
        inline Page(void);
      
        inline Page(OSG::UInt32 page);
        
        void reset(RAFile *parent);
        
        OSG::UInt8 *get(RAFile *parent, OSG::UInt32 offset);
        
        void move(RAFile *parent, OSG::UInt32 newpage);
        
        void dump(std::ostream &str);
      
        inline OSG::UInt32 getPage(void);
        inline OSG::UInt32 getLastUse(void);

        // Comparison functions for STL
        static bool pagePageLess(Page *p1, Page *p2);
        static bool pageLRULess (Page *p1, Page *p2);
      
      private:
      
        OSG::UInt32 _lastuse;
        OSG::UInt32 _page;
        std::vector<OSG::UInt8> _data;
    };
    
    friend class Page;
    
    std::vector<Page> _pages;
    
    typedef std::vector<Page *> PageVector;
    
    PageVector _lru;
    PageVector _ordered;
    
    OSG::UInt32 _uses;
    
    // A little statistics, just for fun
    OSG::UInt32 _hits;
    OSG::UInt32 _misses;
    OSG::UInt64 _loads;
    OSG::UInt64 _used;
    
};

#include <RAFile.inl>

#endif
