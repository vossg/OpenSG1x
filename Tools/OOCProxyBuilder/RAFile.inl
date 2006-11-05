


inline OSG::UInt32 RAFile::getPagesize(void)
{
    return _pagesize;
}

inline OSG::UInt32 RAFile::getNPages(void)
{
    return _npages;
}


inline bool RAFile::split(unsigned long offset, 
                  OSG::UInt32 &page, OSG::UInt32 &poffset)
{

    poffset = offset % _pagesize;
    page = offset / _pagesize;
}
      
inline RAFile::Page::Page(void) : _lastuse(0), _page(RAFile::_invalidPage)
{}
      
inline RAFile::Page::Page(OSG::UInt32 page) : _lastuse(0), _page(page)
{}
    
inline OSG::UInt32 RAFile::Page::getPage(void)
{
    return _page;
}
  
inline OSG::UInt32 RAFile::Page::getLastUse(void)
{
    return _lastuse;
}
