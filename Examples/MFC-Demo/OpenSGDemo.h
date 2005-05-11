// OpenSGDemo.h : main header file for the OpenSGDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// COpenSGDemoApp:
// See OpenSGDemo.cpp for the implementation of this class
//

class COpenSGDemoApp : public CWinApp
{
public:
	COpenSGDemoApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenSGDemoApp theApp;