#ifndef WIN32

#ifdef __sgi
# include <stdlib.h>
#else
# include <cstdlib>
#endif

#include "OSGTXFGlyphInfo.h"

OSG_USING_NAMESPACE




bool TXFGlyphInfo::setTextureCoords(Int8 corner, Real32 x, Real32 y)
{
  bool retCode;

  if ( (corner < 0) || (corner > 3 ))
    retCode = false;
  else {
    _tCoords[corner][0]  = x;
    _tCoords[corner][1]  = y;
    retCode = true;
  }
  
  return retCode;
}


bool TXFGlyphInfo::setVertexCoords(Int8 corner, Real32 x, Real32 y)
{
  bool retCode;

  if ( (corner < 0) || (corner > 3 ))
    retCode = false;
  else {
    _vCoords[corner][0]  = x;
    _vCoords[corner][1]  = y;
    retCode = true;
  }
  
  return retCode;
}


Real32 *TXFGlyphInfo::getTextureCoords(Int8 corner)
{
  if(corner > 3) return NULL;

  return _tCoords[corner];
}

	  
Real32 *TXFGlyphInfo::getVertexCoords(Int8 corner)
{
  if(corner > 3) return NULL;

  return _vCoords[corner];
}

#endif
