#ifndef TESSELATION_HANDLER_H
#define TESSELATION_HANDLER_H

#include <OSGConfig.h>


  /** TesselationCallbacks  **/

#ifdef _WIN32 // pdaehne
# define CALLINGCONV __stdcall
#else
# define CALLINGCONV
#endif

OSG_BEGIN_NAMESPACE class VectorFontGlyph;  OSG_END_NAMESPACE


extern osg::VectorFontGlyph *tmTesselator;

OSG_BEGIN_NAMESPACE extern void CALLINGCONV tessBegin(GLenum); OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE extern void CALLINGCONV tessEdgeFlag(GLboolean); OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE extern void CALLINGCONV tessVertex(void *); OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE extern void CALLINGCONV tessEnd(void); OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE extern void CALLINGCONV tessError(GLenum); OSG_END_NAMESPACE

		  
#endif

