#ifndef TESSELATION_HANDLER_H
#define TESSELATION_HANDLER_H

#ifndef WIN32

#include <OSGConfig.h>
#include <OSGSystemDef.h>


  /** TesselationCallbacks  **/

OSG_BEGIN_NAMESPACE 

class VectorFontGlyph;

extern VectorFontGlyph *tmTesselator;

extern OSG_SYSTEMLIB_DLLMAPPING void tessBegin(GLenum);

extern OSG_SYSTEMLIB_DLLMAPPING void tessEdgeFlag(GLboolean);

extern OSG_SYSTEMLIB_DLLMAPPING void tessVertex(void *);

extern OSG_SYSTEMLIB_DLLMAPPING void tessEnd(void);

extern OSG_SYSTEMLIB_DLLMAPPING void tessError(GLenum); 

OSG_END_NAMESPACE


#endif		  
#endif

