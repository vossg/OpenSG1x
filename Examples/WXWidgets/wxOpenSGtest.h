/////////////////////////////////////////////////////////////////////////////
// Name:        wxOpenSGtest.h
// Purpose:     example for using OpenSG with wxWidgets
//              based on isosurf from the wxWidgets distribution
// Author:      Julian Smart
// Modified by: Dirk Reiners
// Created:     09/09/04
// RCS-ID:      $Id: wxOpenSGtest.h,v 1.1 2004/09/11 22:27:43 dirk Exp $
// Copyright:   (c) Dirk Reiners
// Licence:     wxWindows & OpenSG licences
/////////////////////////////////////////////////////////////////////////////

#ifndef _WXOPENSGTEST_H_
#define _WXOPENSGTEST_H_

#if not(wxUSE_GLCANVAS)
#error "Need wxWdiegts with GLCanvas"
#endif

#include <OpenSG/OSGSimpleSceneManager.h>

// Define a new application type
class MyApp: public wxApp
{
public:
    bool OnInit();
};

class TestOpenSGCanvas: public wxGLCanvas
{
public:
    TestOpenSGCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0,
        const wxString& name = _T("TestOpenSGCanvas"), int *gl_attrib = NULL);

   ~TestOpenSGCanvas();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnChar(wxKeyEvent& event);
    void OnMouseEvent(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()

private:

    OSG::SimpleSceneManager *mgr;
};


class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
        const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

    virtual ~MyFrame();

    TestOpenSGCanvas *m_canvas;

private :

    void OnExit(wxCommandEvent& event);

DECLARE_EVENT_TABLE()
};

#endif // #ifndef _WXOPENSGTEST_H_

