/////////////////////////////////////////////////////////////////////////////
// Name:        wxOpenSGtest.cpp
// Purpose:     example for using OpenSG with wxWidgets
//              based on isosurf from the wxWidgets distribution
// Author:      Julian Smart
// Modified by: Dirk Reiners
// Created:     09/09/04
// RCS-ID:      $Id: wxOpenSGtest.cpp,v 1.1 2004/09/11 22:27:43 dirk Exp $
// Copyright:   (c) Dirk Reiners
// Licence:     wxWindows & OpenSG licences
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation
#pragma interface
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/timer.h"
#include "wx/glcanvas.h"

#include <OpenSG/OSGGLU.h>

#include "wxOpenSGtest.h"

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE;

static bool Args(int argc, wxChar **argv)
{
    GLint i;

    for (i = 1; i < argc; i++)
    {
        wxString msg = _T("Bad option: ");
        msg += argv[i];
        wxMessageBox(msg);
        return false;
    }

    return true;
}

// The following part was written for wxWidgets 1.66
MyFrame *frame = NULL;

IMPLEMENT_APP(MyApp)

// `Main program' equivalent, creating windows and returning main app frame
bool MyApp::OnInit()
{
    Args(argc, argv);

    // Create the main frame window
    frame = new MyFrame(NULL, wxT("wxWidgets OpenSG Test"),
        wxDefaultPosition, wxDefaultSize);

    // Give it an icon
    frame->SetIcon(wxIcon(_T("mondrian")));

    // Make a menubar
    wxMenu *fileMenu = new wxMenu;

    fileMenu->Append(wxID_EXIT, _T("E&xit"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, _T("&File"));
    frame->SetMenuBar(menuBar);

  // Make a TestOpenSGCanvas

  // JACS
#ifdef __WXMSW__
    int *gl_attrib = NULL;
#else
    int gl_attrib[20] = { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
        WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
        WX_GL_DOUBLEBUFFER,
#  ifdef __WXMAC__
        GL_NONE };
#  else
        None };
#  endif
#endif

    frame->m_canvas = new TestOpenSGCanvas(frame, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, 0, _T("TestOpenSGCanvas"), gl_attrib );

    // Show the frame
    frame->Show(true);

    frame->m_canvas->SetCurrent();

    return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
END_EVENT_TABLE()

// My frame constructor
MyFrame::MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style)
    : wxFrame(frame, wxID_ANY, title, pos, size, style)
{
    m_canvas = NULL;
}

MyFrame::~MyFrame()
{
    if (m_canvas)
    {
        delete m_canvas; m_canvas = NULL;
    }
}

// Intercept menu commands
void MyFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
    // true is to force the frame to close
    Close(true);
}

/*
 * TestOpenSGCanvas implementation
 */

BEGIN_EVENT_TABLE(TestOpenSGCanvas, wxGLCanvas)
    EVT_SIZE(TestOpenSGCanvas::OnSize)
    EVT_PAINT(TestOpenSGCanvas::OnPaint)
    EVT_CHAR(TestOpenSGCanvas::OnChar)
    EVT_MOUSE_EVENTS(TestOpenSGCanvas::OnMouseEvent)
    EVT_ERASE_BACKGROUND(TestOpenSGCanvas::OnEraseBackground)
END_EVENT_TABLE()

TestOpenSGCanvas::TestOpenSGCanvas(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style,
    const wxString& name, int* gl_attrib)
    : wxGLCanvas(parent, id, pos, size, style, name, gl_attrib),
      mgr(NULL)
{
    static bool inited=false;
    // Initialize OpenSG   
    if(!inited)
    {
        inited = true;
        osgInit(0, NULL); // If you want to pass command line args, you have
                          // to do this in the app init 
    }
    
    // Handle wx
    parent->Show(true);
    SetCurrent();
 
    // Create the OpenSG parts    
    PassiveWindowPtr pwin= PassiveWindow::create();
    pwin->init();

    // create the scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(pwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    int w, h;
    GetClientSize(&w, &h);
    mgr->resize(w, h);

    Refresh(false);
}


TestOpenSGCanvas::~TestOpenSGCanvas()
{
}

void TestOpenSGCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    // This is a dummy, to avoid an endless succession of paint messages.
    // OnPaint handlers must always create a wxPaintDC.
    wxPaintDC dc(this);

#ifndef __WXMOTIF__
    if (!GetContext()) return;
#endif

    SetCurrent();

    if(mgr)
        mgr->redraw();

    SwapBuffers();
}

void TestOpenSGCanvas::OnSize(wxSizeEvent& event)
{
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);
#ifndef __WXMOTIF__
    if (GetContext())
#endif
    {
        SetCurrent();
        if(mgr)
            mgr->resize(w,h);
    }
}

void TestOpenSGCanvas::OnChar(wxKeyEvent& event)
{
    switch( event.GetKeyCode() )
    {
    case WXK_ESCAPE:
        wxTheApp->ExitMainLoop();
        return;

    default:
        event.Skip();
        return;
    }

    Refresh(false);
}

void TestOpenSGCanvas::OnMouseEvent(wxMouseEvent& event)
{
    Int16 x = event.GetX(),
          y = event.GetY();
          
    if(event.ButtonDown())
    {
        if(event.LeftDown())
            mgr->mouseButtonPress(SimpleSceneManager::MouseLeft, x, y);
        if(event.MiddleDown())
            mgr->mouseButtonPress(SimpleSceneManager::MouseMiddle, x, y);
        if(event.RightDown())
            mgr->mouseButtonPress(SimpleSceneManager::MouseRight, x, y);
    }
    if(event.ButtonUp())
    {
        if(event.LeftUp())
            mgr->mouseButtonRelease(SimpleSceneManager::MouseLeft, x, y);
        if(event.MiddleUp())
            mgr->mouseButtonRelease(SimpleSceneManager::MouseMiddle, x, y);
        if(event.RightUp())
            mgr->mouseButtonRelease(SimpleSceneManager::MouseRight, x, y);
    }

    if(event.GetButton() == wxMOUSE_BTN_NONE)
        mgr->mouseMove(x, y);

    Refresh(false);
}

void TestOpenSGCanvas::OnEraseBackground( wxEraseEvent& WXUNUSED(event) )
{
    // Do nothing, to avoid flashing.
}

