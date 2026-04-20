
// Test_CSCColorPickerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_CSCColorPicker.h"
#include "Test_CSCColorPickerDlg.h"
#include "afxdialogex.h"

#include "Common/Functions.h"
#include "Common/MemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestCSCColorPickerDlg 대화 상자



CTestCSCColorPickerDlg::CTestCSCColorPickerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_CSCCOLORPICKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCSCColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MODAL, m_button_modal);
	DDX_Control(pDX, IDC_BUTTON_MODELESS, m_button_modeless);
}

BEGIN_MESSAGE_MAP(CTestCSCColorPickerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestCSCColorPickerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestCSCColorPickerDlg::OnBnClickedCancel)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(Message_CSCColorPicker, &CTestCSCColorPickerDlg::on_message_CSCColorPicker)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MODAL, &CTestCSCColorPickerDlg::OnBnClickedButtonModal)
	ON_BN_CLICKED(IDC_BUTTON_MODELESS, &CTestCSCColorPickerDlg::OnBnClickedButtonModeless)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTestCSCColorPickerDlg 메시지 처리기

BOOL CTestCSCColorPickerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_button_modal.set_round(4, Gdiplus::Color::Gray);// , m_cr_back);
	m_button_modeless.set_round(4, Gdiplus::Color::Gray);// , m_cr_back);

	m_color_picker.create(this, _T("Color Picker"), false);
	m_color_picker.set_use_shared_color();

	RestoreWindowPosition(&theApp, this, _T(""), false, false);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestCSCColorPickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestCSCColorPickerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc1(this);
		CRect rc;

		GetClientRect(rc);

		CMemoryDC dc(&dc1, &rc);
		Gdiplus::Graphics g(dc.GetSafeHdc());

		if (m_cr_back.GetA() < 255)
		{
			Gdiplus::TextureBrush tb(CSCGdiplusBitmap::checker_bmp(6), Gdiplus::WrapModeTile);
			g.FillRectangle(&tb, CRect_to_gpRect(rc));
		}

		g.FillRectangle(&Gdiplus::SolidBrush(m_cr_back), CRect_to_gpRect(rc));
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestCSCColorPickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestCSCColorPickerDlg::OnBnClickedOk()
{
	bool modal_test = false;

	if (modal_test)
	{
	}
	else
	{
	}
}

void CTestCSCColorPickerDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CTestCSCColorPickerDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}

void CTestCSCColorPickerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_show_picker)
	{
		KillTimer(timer_show_picker);
		OnBnClickedOk();
	}

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CTestCSCColorPickerDlg::on_message_CSCColorPicker(WPARAM wParam, LPARAM lParam)
{
	auto msg = (CSCColorPickerMessage*)wParam;
	m_cr_back = msg->cr_selected;
	m_button_modal.set_parent_back_color(m_cr_back);
	m_button_modeless.set_parent_back_color(m_cr_back);
	Invalidate();
	return 0;
}

void CTestCSCColorPickerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnBnClickedOk();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CTestCSCColorPickerDlg::OnBnClickedButtonModal()
{
	CSCColorPicker picker;
	picker.set_use_shared_color();

	if (picker.DoModal(this, Gdiplus::Color(128, 211, 222, 33), _T("Color Picker")) == IDCANCEL)
		return;

	m_cr_back = picker.get_selected_color();
	m_button_modal.set_parent_back_color(m_cr_back);
	m_button_modeless.set_parent_back_color(m_cr_back);

	TRACE(_T("sel color = %s\n"), get_color_str(m_cr_back));
	Invalidate();
}

void CTestCSCColorPickerDlg::OnBnClickedButtonModeless()
{
	m_color_picker.ShowWindow(m_color_picker.IsWindowVisible() ? SW_HIDE : SW_SHOW);
}

BOOL CTestCSCColorPickerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
