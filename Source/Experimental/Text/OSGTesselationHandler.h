#ifndef TESSELATION_HANDLER_H
#define TESSELATION_HANDLER_H

#include <OSGConfig.h>
#include <OSGSystemDef.h>

/** TesselationCallbacks  **/
OSG_BEGIN_NAMESPACE 

class VectorFontGlyph;

extern VectorFontGlyph *tmTesselator;

void OSG_APIENTRY tessBegin   (GLenum   );
void OSG_APIENTRY tessEdgeFlag(GLboolean);
void OSG_APIENTRY tessVertex  (void    *);
void OSG_APIENTRY tessEnd     (void     );
void OSG_APIENTRY tessError   (GLenum   );

OSG_END_NAMESPACE

#endif
