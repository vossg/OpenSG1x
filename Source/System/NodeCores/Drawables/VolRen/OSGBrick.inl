
OSG_BEGIN_NAMESPACE

inline
BrickSet::BrickSet(void) : 
    m_pBricks(0), 
    m_nNumBricks(0), 
    m_nOrientation(UNDEF) 
{
}

inline
Brick *Brick::getNext(void) 
{
    return next;
}


OSG_END_NAMESPACE
