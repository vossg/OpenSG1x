// -----------------------------------------------------------------------------
// OSGViewer.h
// (c) 2001 Christoph Fuenfzig  <c.fuenfzig@cg.cs.tu-bs.de>  
//          Institute for ComputerGraphics, TU Braunschweig 
// -----------------------------------------------------------------------------
//

#ifndef OSGFOXGLWIDGET_H
#define OSGFOXGLWIDGET_H

#include "OSGWindowFOXDef.h"
#include "OSGFOXWindow.h"

#ifdef WIN32
#pragma warning (disable : 698 47 373 383 171)
#endif

#include "fox/fxkeys.h"
#include "fox/fx.h"
#include "fox/fx3d.h"

#ifdef WIN32
#pragma warning (error   : 698 47 373 171)
#pragma warning (default : 383)
#endif

OSG_BEGIN_NAMESPACE

class OSG_WINDOWFOXLIB_DLLMAPPING FOXGLWidget : public FXGLCanvas
{
   FXDECLARE(FOXGLWidget)

public:
    FOXGLWidget (FXComposite* p, FXGLVisual* vis, 
		FXObject* tgt=NULL, FXSelector sel=0, FXuint opts=0, 
		FXint x=0, FXint y=0, FXint w=0, FXint h=0);
   ~FOXGLWidget ();

   inline void         setWindow (FOXWindowPtr win);
   inline FOXWindowPtr getWindow () const;

   // FOX interface
   virtual void create   ();
   virtual void resize   (FXint w, FXint h);
   virtual void position (FXint x, FXint y, FXint w, FXint h);

   // no messages
   enum {
      ID_LAST=FXGLCanvas::ID_LAST
   };

protected:
   FOXGLWidget ();

   FOXWindowPtr m_win;
};

inline void FOXGLWidget::setWindow (FOXWindowPtr win)
{
   m_win = win;
}
inline FOXWindowPtr FOXGLWidget::getWindow () const
{
   return m_win;
}
OSG_END_NAMESPACE

#endif
