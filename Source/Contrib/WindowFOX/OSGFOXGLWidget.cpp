#define OSG_COMPILEWINDOWFOXINST

#include "OSGFOXGLWidget.h"
#include <GL/gl.h>
#include <GL/glu.h>

OSG_USING_NAMESPACE

#ifdef WIN32
#pragma warning (disable : 698 47 373 383 171)
#endif

// Object implementation
FXIMPLEMENT(FOXGLWidget, FXGLCanvas, NULL, 0)

FOXGLWidget::FOXGLWidget ()
{
}

FOXGLWidget::FOXGLWidget (FXComposite* p, FXGLVisual* vis, 
			FXObject* tgt, FXSelector sel, FXuint opts, 
			FXint x, FXint y, FXint w, FXint h)
   : FXGLCanvas(p, vis, tgt, sel, opts, x, y, w, h)
{
}
FOXGLWidget::~FOXGLWidget ()
{
}

void FOXGLWidget::create ( void )
{
   FXGLCanvas::create();
   if (makeCurrent()) {
      // Window::setupGL()
      glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
      glPixelStorei( GL_PACK_ALIGNMENT, 1 );
      glDepthFunc( GL_LEQUAL );
      glEnable( GL_DEPTH_TEST );
      glLineWidth(2.0f);
   }
}

void FOXGLWidget::position(FXint x, FXint y, FXint w, FXint h) 
{
   FXGLCanvas::position(x, y, w, h);
   if (makeCurrent()) {
      m_win->resize( w, h );
      m_win->resizeGL();
   }
}

void FOXGLWidget::resize (FXint w, FXint h)
{   
   FXGLCanvas::resize(w, h);
   if (makeCurrent()) {
      m_win->resize( w, h );
      m_win->resizeGL();
   }
}

#ifdef WIN32
#pragma warning (error   : 698 47 373 171)
#pragma warning (default : 383)
#endif

