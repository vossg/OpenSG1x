#pragma once
#include "afxwin.h"
#include "Resource.h"
#include <vector>
#include <string>

class SelectCameraDialog : public CDialog {
	DECLARE_DYNAMIC(SelectCameraDialog)

private:
  std::vector<std::string> cameras;
  CComboBox selectionControl;
  int selection;

public:
  SelectCameraDialog(const std::vector<std::string> &cameras, CWnd* pParent = NULL);   // standard constructor
	virtual ~SelectCameraDialog();

  BOOL OnInitDialog();

  int getSelection();

	enum { IDD = IDD_SELECT_CAMERA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedOk();
};
