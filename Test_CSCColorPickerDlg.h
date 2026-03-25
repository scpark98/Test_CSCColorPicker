
// Test_CSCColorPickerDlg.h: 헤더 파일
//

#pragma once

#include "Common/CDialog/CSCColorPicker/SCColorPicker.h"
#include "Common/CButton/GdiButton/GdiButton.h"

// CTestCSCColorPickerDlg 대화 상자
class CTestCSCColorPickerDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestCSCColorPickerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSCColorPicker	m_color_picker;
	LRESULT			on_message_CSCColorPicker(WPARAM wParam, LPARAM lParam);

	Gdiplus::Color	m_cr_back;

	enum TIMER_ID
	{
		timer_show_picker = 1,
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_CSCCOLORPICKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonModal();
	afx_msg void OnBnClickedButtonModeless();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CGdiButton m_button_modal;
	CGdiButton m_button_modeless;
};
