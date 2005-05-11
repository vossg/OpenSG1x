#pragma once

#include <OpenSG/OSGConfig.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>
#include <winsock.h>

#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGWIN32Window.h>

OSG_USING_NAMESPACE

// CStaticRender
class COpenSGMFCControl : public CWnd
{
	DECLARE_DYNAMIC(COpenSGMFCControl)

public:
	COpenSGMFCControl();
	virtual ~COpenSGMFCControl();

protected:

	SimpleSceneManager *mgr;
    PassiveWindowPtr    pwin;
	WIN32WindowPtr		win;

	void RenderScene();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};