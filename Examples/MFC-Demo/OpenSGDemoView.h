// OpenSGDemoView.h : interface of the COpenSGDemoView class
//
#pragma once
#include "afxwin.h"

#include "OpenSGMFCControl.h"

class COpenSGDemoView : public CFormView
{
protected: // create from serialization only
	COpenSGDemoView();
	DECLARE_DYNCREATE(COpenSGDemoView)

public:
	enum{ IDD = IDD_OPENSGDEMO_FORM };

// Attributes
public:
	COpenSGDemoDoc* GetDocument() const;

// Operations
public:

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~COpenSGDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	//CStatic m_RenderStatic;
	//CStatic m_RenderStatic2;
	COpenSGMFCControl m_RenderStatic;
	COpenSGMFCControl m_RenderStatic2;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

};

#ifndef _DEBUG  // debug version in OpenSGDemoView.cpp
inline COpenSGDemoDoc* COpenSGDemoView::GetDocument() const
   { return reinterpret_cast<COpenSGDemoDoc*>(m_pDocument); }
#endif

