

#include "SelectCameraDialog.h"

IMPLEMENT_DYNAMIC(SelectCameraDialog, CDialog)
SelectCameraDialog::SelectCameraDialog(const std::vector<std::string> &cameras, CWnd* pParent)
        : CDialog(SelectCameraDialog::IDD, pParent), selection(0) {
  this->cameras = cameras;
}          

SelectCameraDialog::~SelectCameraDialog() {
}

BOOL SelectCameraDialog::OnInitDialog() {
  if (CDialog::OnInitDialog()) {
    int size = int(cameras.size());
    for (int i = 0; i < size; ++i) {
      selectionControl.AddString(_T(cameras[i].c_str()));
    }
    if (size) {
      selectionControl.SetCurSel(0);
    }
    return true;
  }
  return false;
}

int SelectCameraDialog::getSelection() {
  return selection;
}

void SelectCameraDialog::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SELECT_CAMERA_COMBO, selectionControl);
}

BEGIN_MESSAGE_MAP(SelectCameraDialog, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

void SelectCameraDialog::OnBnClickedOk() {
  selection = selectionControl.GetCurSel();
  OnOK();
}
