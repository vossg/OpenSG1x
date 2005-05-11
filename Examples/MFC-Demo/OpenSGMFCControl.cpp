#include "stdafx.h"
#include "OpenSGMFCControl.h"

// COpenSGMFCControl

IMPLEMENT_DYNAMIC(COpenSGMFCControl, CWnd)
COpenSGMFCControl::COpenSGMFCControl()
{
	// Creation of the SimpleSceneManager
    mgr = new SimpleSceneManager;

	WNDCLASS c;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, "OpenSGMFCControl", &c)))
	{
		// otherwise we need to register a new class
		c.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		c.lpfnWndProc      = ::DefWindowProc;
		c.cbClsExtra       = c.cbWndExtra = 0;
		c.hInstance        = hInst;
		c.hIcon            = NULL;
		c.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		c.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		c.lpszMenuName     = NULL;
		c.lpszClassName    = "OpenSGMFCControl";
		 
		if (!AfxRegisterClass(&c))
		{
			AfxThrowResourceException();
			return;
		}
	}
}

COpenSGMFCControl::~COpenSGMFCControl()
{
	// Destroy the SimpleSceneManager
	delete mgr;

	// Question: Anything else?
}

void COpenSGMFCControl::RenderScene()
{
	mgr->redraw();
}

BEGIN_MESSAGE_MAP(COpenSGMFCControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COpenSGMFCControl message handlers
int COpenSGMFCControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	// OSG Initialization
	osgInit(0,NULL);

	// Win32Window Creation and setHWND
	win = WIN32Window::create();
	win->setHwnd (GetSafeHwnd());

	// Set the Pixel Format
	int iPixelFormat;
    PIXELFORMATDESCRIPTOR   pfd;  
	memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 16;            

	iPixelFormat = ChoosePixelFormat(GetDC()->m_hDC, &pfd);
    SetPixelFormat(GetDC()->m_hDC, iPixelFormat, &pfd);    
    
	// Window Initialization
    win->init();
    win->deactivate();

	// Scene Creation
	NodePtr scene = makeTorus(.5, 3, 16, 16);

	// SimpleSceneManager setWindow
	mgr->setWindow(win);	

	// Tell the scene root
    mgr->setRoot(scene);

	// Show all
    mgr->showAll();

	return 0;
}

void COpenSGMFCControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	RenderScene();
}

BOOL COpenSGMFCControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
    mgr->mouseButtonPress(
		zDelta > 0 ? SimpleSceneManager::MouseUp : SimpleSceneManager::MouseDown, 
		pt.x, pt.y);    
	RenderScene();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void COpenSGMFCControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here and/or call default
	mgr->resize(cx, cy);
	RenderScene();
}

void COpenSGMFCControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mgr->mouseMove(point.x, point.y);
	RenderScene();

	CWnd::OnMouseMove(nFlags, point);
} 

void COpenSGMFCControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    mgr->mouseButtonRelease(SimpleSceneManager::MouseLeft, point.x, point.y);
	RenderScene();

	CWnd::OnLButtonUp(nFlags, point);
}

void COpenSGMFCControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

    mgr->mouseButtonPress(SimpleSceneManager::MouseLeft, point.x, point.y);
	RenderScene();

	CWnd::OnLButtonDown(nFlags, point);
}
void COpenSGMFCControl::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    mgr->mouseButtonRelease(SimpleSceneManager::MouseMiddle, point.x, point.y);
	RenderScene();

	CWnd::OnMButtonUp(nFlags, point);
}

void COpenSGMFCControl::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    mgr->mouseButtonPress(SimpleSceneManager::MouseMiddle, point.x, point.y);
	RenderScene();

	CWnd::OnMButtonDown(nFlags, point);
}

void COpenSGMFCControl::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mgr->mouseButtonRelease(SimpleSceneManager::MouseRight, point.x, point.y);
	RenderScene();
	
	CWnd::OnRButtonUp(nFlags, point);
}

void COpenSGMFCControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    mgr->mouseButtonPress(SimpleSceneManager::MouseRight, point.x, point.y);
	RenderScene();

	CWnd::OnRButtonDown(nFlags, point);
}