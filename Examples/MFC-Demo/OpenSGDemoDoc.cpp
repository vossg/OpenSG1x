// OpenSGDemoDoc.cpp : implementation of the COpenSGDemoDoc class
//

#include "stdafx.h"
#include "OpenSGDemo.h"

#include "OpenSGDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenSGDemoDoc

IMPLEMENT_DYNCREATE(COpenSGDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenSGDemoDoc, CDocument)
END_MESSAGE_MAP()


// COpenSGDemoDoc construction/destruction

COpenSGDemoDoc::COpenSGDemoDoc()
{
	// TODO: add one-time construction code here

}

COpenSGDemoDoc::~COpenSGDemoDoc()
{
}

BOOL COpenSGDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// COpenSGDemoDoc serialization

void COpenSGDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// COpenSGDemoDoc diagnostics

#ifdef _DEBUG
void COpenSGDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenSGDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpenSGDemoDoc commands
