// VGrid.inl: inline functions for VGrid

inline UInt32 VGrid::map(const Pnt3f &pnt)
{
    return static_cast<UInt32>((pnt.z() - _zbase) * _zscale) * _zstep +
           static_cast<UInt32>((pnt.y() - _ybase) * _yscale) * _ystep +
           static_cast<UInt32>((pnt.x() - _xbase) * _xscale);
            
}

inline Pnt3f VGrid::unmap(UInt32 ind)
{
    Pnt3f p;
     
    p[0] = UInt32((ind % _ystep)          ) / _xscale + _xbase;
    p[1] = UInt32((ind % _zstep)  / _ystep) / _yscale + _ybase;
    p[2] = UInt32( ind            / _zstep) / _zscale + _zbase;
    
    return p;
}

inline UInt32 VGrid::nvert(UInt32 ind)
{
    return _map[ind].nvert;
}

inline UInt32 VGrid::part(UInt32 ind)
{
    return _map[ind].part;
}
