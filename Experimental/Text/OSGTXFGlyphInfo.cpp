#ifdef __sgi
# include <stdlib.h>
#else
# include <cstdlib>
#endif

#include "OSGTXFGlyphInfo.h"

OSG_USING_NAMESPACE




bool TXFGlyphInfo::setTextureCoords(int corner, float x, float y)
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


bool TXFGlyphInfo::setVertexCoords(int corner, float x, float y)
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


float *TXFGlyphInfo::getTextureCoords(int corner)
{
  if(corner > 3) return NULL;

  return _tCoords[corner];
}

	  
float *TXFGlyphInfo::getVertexCoords(int corner)
{
  if(corner > 3) return NULL;

  return _vCoords[corner];
}

