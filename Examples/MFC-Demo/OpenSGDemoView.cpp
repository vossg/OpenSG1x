#include "stdafx.h"
#include "OpenSGDemo.h"

#include "OpenSGDemoDoc.h"
#include "OpenSGDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(COpenSGDemoView, CFormView)

BEGIN_MESSAGE_MAP(COpenSGDemoView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// COpenSGDemoView construction/destruction
COpenSGDemoView::COpenSGDemoView()
	: CFormView(COpenSGDemoView::IDD)
{
	// TODO: add construction code here
 	EnableActiveAccessibility();
}

COpenSGDemoView::~COpenSGDemoView()
{
}

void COpenSGDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDERSTATIC, m_RenderStatic);
	DDX_Control(pDX, IDC_RENDERSTATIC2, m_RenderStatic2);
}

void COpenSGDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// Recalculate the correct dimensions of the control
	RECT rectControl, rectDlg;
	m_RenderStatic.GetWindowRect(&rectControl);
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectDlg);

	rectDlg.left-=rectControl.left;
	rectDlg.right-=rectControl.left;
	rectDlg.top-=rectControl.top;
	rectDlg.bottom-=rectControl.top;

	m_RenderStatic.MoveWindow(&rectDlg);

	/////////////////////////////////////////////
	m_RenderStatic2.GetWindowRect(&rectControl);
	GetDlgItem(IDC_STATIC2)->GetWindowRect(&rectDlg);

	rectDlg.left-=rectControl.left;
	rectDlg.right-=rectControl.left;
	rectDlg.top-=rectControl.top;
	rectDlg.bottom-=rectControl.top;

	m_RenderStatic2.MoveWindow(&rectDlg);

}


// COpenSGDemoView diagnostics

#ifdef _DEBUG
void COpenSGDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void COpenSGDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

COpenSGDemoDoc* COpenSGDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenSGDemoDoc)));
	return (COpenSGDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenSGDemoView message handlers
int COpenSGDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	// Create the renderStatic with dummy dimensions.
	m_RenderStatic.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,100,100), this, AFX_IDW_PANE_FIRST, NULL);
	
	m_RenderStatic2.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,100,100), this, AFX_IDW_PANE_FIRST, NULL);

	// The correct position will be set in the OnInitialUpdate

	return 0;
}