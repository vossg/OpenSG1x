// RAFile: an efficient random access file wrapper

#include <algorithm>

#include "RAFile.h"

#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGBaseFunctions.h>

using namespace std;

OSG_USING_NAMESPACE;

UInt32 RAFile::_invalidPage = TypeTraits<UInt32>::getMax();

RAFile::RAFile(std::ifstream &str, 
        OSG::UInt32 pagesize, OSG::UInt32 npages) 
    : _str(str), _pagesize(pagesize), _npages(npages),
      _uses(1), _pages()
{
    str.seekg(0, std::ios::end);
    _size = str.tellg();
    
    _pages.resize(_npages);
    _lru.resize(_npages);
    _ordered.resize(_npages);
    
    for(UInt32 i = 0; i < _npages; ++i)
    {
        _pages[i].reset(this);
        
        _lru[i]     = &_pages[i];
        _ordered[i] = &_pages[i];        
    }
    
    _hits = _misses = 0;
    _loads = _used = 0;
}

RAFile::~RAFile()
{
}

void RAFile::read(unsigned long offset, OSG::UInt8 *data, unsigned int size)
{
    if(offset + size > _size)
    {
        FWARNING(("RAFile::read: trying to read beyond EOF (offset %d, "
                    "size %d)!\n", offset, size));
        return;
    }
    UInt32 page, poffset;
    
    split(offset, page, poffset);
    
    Page *pg = findPage(page);

    _used += size;
    
    OSG::UInt8 *src = pg->get(this, poffset);
    
    do
    {
        *data++ = *src++;
        
        if(++poffset >= _pagesize)
        {
            poffset = 0;
            pg = findPage(++page);
            src = pg->get(this, poffset);
        }
    }
    while(--size > 0);
}

UInt32 RAFile::read(unsigned long offset)
{
    UInt32 val;
    
    read(offset, (OSG::UInt8 *)&val, sizeof(UInt32));
    
    return val;
}

// Page Management

RAFile::Page *RAFile::findPage(OSG::UInt32 page)
{
    PageVector::iterator it;
    Page p(page);
    
    it = lower_bound(_ordered.begin(), _ordered.end(), &p, 
                        &RAFile::Page::pagePageLess);

    // Do we have that page?
    if(it != _ordered.end() && (*it)->getPage() == page)
    {
        _hits++;
        return *it;
    }

    _misses++;
    
    //std::cout << "RAFile::findPage: Can't find page " << page << std::endl;
    //dump(std::cout);
    
    // Nope, need to allocate it
    // Find LRU page
    
    sort(_lru.begin(), _lru.end(), &RAFile::Page::pageLRULess);
    
    // Move LRU page
    
    _lru[0]->move(this, page);
    
    _loads += _pagesize;
    
    // Resort ordered
    sort(_ordered.begin(), _ordered.end(), &RAFile::Page::pagePageLess);
    
    return _lru[0];
}

void RAFile::print(std::ostream &str)
{
    str << "RAFile: " << _npages << " pages a " << _pagesize
        << " bytes each. "<< _hits << " cache hits, " << _misses 
        << " misses. Loaded " << _loads << " bytes, used " << _used 
        << ".";
}

void RAFile::dump(std::ostream &str)
{
    str << "RAFile: " << _npages << " pages a " << _pagesize << " bytes each"
        << std::endl;
    
    for(UInt32 i = 0; i < _npages; ++i)
    {
        str << "Page " << i << " ";
        _pages[i].dump(str);
        str << std::endl;
    }

    str << "Ordered: ";
     
    for(UInt32 i = 0; i < _npages; ++i)
    {
        Page *p = _ordered[i];
        
        str << p - &_pages[0] << " (" << p->getPage() << ") ";
    }

    str << std::endl << "LRU: ";
     
    for(UInt32 i = 0; i < _npages; ++i)
    {
        Page *p = _lru[i];
        
        str << p - &_pages[0] << " (" << p->getLastUse() << ") ";
    }
   
    str << std::endl;
}

// Page helper class

void RAFile::Page::reset(RAFile *parent)
{
    _page = _invalidPage;
    _data.resize(parent->getPagesize());
    _lastuse = 0;
}

OSG::UInt8 *RAFile::Page::get(RAFile *parent, OSG::UInt32 offset)
{
    _lastuse = parent->_uses++;   
    return &_data[offset];
}

void RAFile::Page::move(RAFile *parent, OSG::UInt32 newpage)
{
    _page = newpage;
    parent->_str.seekg(newpage * parent->_pagesize, std::ios::beg);
    parent->_str.read((char*)&_data[0], 
                      osgMin((unsigned long)parent->_pagesize, 
                             parent->_size - newpage * parent->_pagesize));
    _lastuse = parent->_uses++;   
}

void RAFile::Page::dump(std::ostream &str)
{
    str << "Page " << _page << " Used: " << _lastuse;
}

bool RAFile::Page::pagePageLess(Page *p1, Page *p2)
{
    if(p1->_page < p2->_page) return true;
    
    return false;
}

bool RAFile::Page::pageLRULess(Page *p1, Page *p2)
{
    if(p1->_lastuse < p2->_lastuse) return true;
    
    return false;
}
