
// MFC PROJECT SEHDADlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC PROJECT SEHDA.h"
#include "MFC PROJECT SEHDADlg.h"
#include "afxdialogex.h"


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
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCPROJECTSEHDADlg 대화 상자



CMFCPROJECTSEHDADlg::CMFCPROJECTSEHDADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECTSEHDA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pButton = NULL;
}



void CMFCPROJECTSEHDADlg::OnButtonEvent(UINT ID)
{
	switch (ID)
	{
	case BTN_PLAY:
		LoaingButtonDestroy();
		MakeGameingButton();
		loadingImage.Destroy();
		Invalidate();
		IsPlay = true;
		break;
	case BTN_OUTPUT_SCORE:
		break;
	case BTN_EXIT:
		exit(1); // 종료 //
		break;
	case BTN_CALL:
		break;
	case BTN_HALF:
		break;
	case BTN_DOUBLE:
		
		break;

	case BTN_DIE:
		break;
	case BTN_BACK:
		reversePae.Destroy();
		userPicture.Destroy();
		com1Picture.Destroy();
		com2Picture.Destroy();
		GamingButtonDestroy();
		MakeLoadingButton();
		Invalidate();
		IsPlay = false;
		
		break;
	
	}
}

void CMFCPROJECTSEHDADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCPROJECTSEHDADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(BTN_PLAY, BTN_BACK, OnButtonEvent)
	/*ON_COMMAND_RANGE(BTN_PLAY, BTN_OUTPUT_SCORE, OnBtnClick)*/
END_MESSAGE_MAP()


// CMFCPROJECTSEHDADlg 메시지 처리기

BOOL CMFCPROJECTSEHDADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetTimer(0, 200, NULL); // 패의 이동
	SetTimer(1, 3000, NULL); // user 대기
	MakeLoadingButton();
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCPROJECTSEHDADlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCPROJECTSEHDADlg::OnPaint()
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
		if (IsPlay != true) // 로딩 //
		{
			NotPlayImage();
			
		}
		else // 게임 //
		{
			PlayImage();
		}
		CDialogEx::OnPaint();
	}
}
void CMFCPROJECTSEHDADlg::NotPlayImage()
{
	CPaintDC dc(this);
	CString caption;
	CRect rect;
	GetClientRect(&rect);
	
	loadingImage.Load(_T("C:\\Users\\user\\loading2.PNG"));
	loadingImage.BitBlt(dc.m_hDC, rect.right / 3 + 80, 80);
	caption.Format(_T("PLAY"));
	pButton[0]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(70, 3 * rect.bottom / 5, 3 * rect.right / 10 - 70, 4 * rect.bottom / 5), this, BTN_PLAY);

	caption.Format(_T("Score OutPut"));
	pButton[1]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1 * rect.right / 3 + 90, 3 * rect.bottom / 5, 6 * rect.right / 10 - 10, 4 * rect.bottom / 5), this, BTN_OUTPUT_SCORE);

	caption.Format(_T("GAME - EXIT"));
	pButton[2]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(2 * rect.right / 3 + 100, 3 * rect.bottom / 5, 9 * rect.right / 10 + 28, 4 * rect.bottom / 5), this, BTN_EXIT);
}
void CMFCPROJECTSEHDADlg::PlayImage()
{
	CPaintDC dc(this);
	CString caption;
	CRect rect;
	GetClientRect(&rect);

	reversePae.Load(_T("C:\\Users\\user\\RP.PNG"));
	reversePae.BitBlt(dc.m_hDC, rect.right / 2 - 30, rect.bottom / 2 - 50);

	userPicture.Load(_T("C:\\Users\\user\\user.PNG"));
	userPicture.BitBlt(dc.m_hDC, -30,  3 * rect.bottom / 4 - 70);

	com1Picture.Load(_T("C:\\Users\\user\\computer1.PNG"));
	com1Picture.BitBlt(dc.m_hDC, -30,  0);


	com2Picture.Load(_T("C:\\Users\\user\\computer2.PNG"));
	com2Picture.BitBlt(dc.m_hDC, 2 * rect.right / 3 + 100, 0);


	caption.Format(_T("콜"));
	pButton[0]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(12 * rect.right / 15, 7 * rect.bottom / 10 - 50, 13 * rect.right / 15, 8 * rect.bottom / 10 - 50), this, BTN_CALL);
	caption.Format(_T("하프"));
	pButton[1]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(13 * rect.right / 15 + 10, 7 * rect.bottom / 10 - 50, 14 * rect.right / 15 + 10, 8 * rect.bottom / 10 - 50), this, BTN_HALF);
	caption.Format(_T("따블"));
	pButton[2]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(12 * rect.right / 15, 7 * rect.bottom / 10 - 50 + rect.right/15, 13 * rect.right / 15, 8 * rect.bottom / 10 - 50 + rect.right / 15), this, BTN_DOUBLE);
	caption.Format(_T("다이"));
	pButton[3]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(13 * rect.right / 15 + 10, 7 * rect.bottom / 10 - 50 + rect.right / 15, 14 * rect.right / 15 + 10, 8 * rect.bottom / 10 - 50 + rect.right / 15), this, BTN_DIE);

	caption.Format(_T("뒤로가기"));
	pButton[4]->Create(caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(12 * rect.right / 15 , 7 * rect.bottom / 10 - 50 + 2 * rect.right / 15, 14 * rect.right / 15 + 10, 8 * rect.bottom / 10 - 50 + 2* rect.right / 15), this, BTN_BACK);
	

}
// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCPROJECTSEHDADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCPROJECTSEHDADlg::MakeGameingButton()
{
	pButton = new CButton*[gameButtonCount];

	for (int i = 0; i < gameButtonCount; i++)
	{
		pButton[i] = new CButton();
	}
}

void CMFCPROJECTSEHDADlg::GamingButtonDestroy()
{
	if (pButton != NULL)
	{
		for (int i = 0; i < gameButtonCount; i++)
		{
			delete pButton[i];
			pButton[i] = NULL;
		}
		delete pButton;
		pButton = NULL;
	}
}

void CMFCPROJECTSEHDADlg::MakeLoadingButton()
{
	pButton = new CButton*[Lcount];

	for (int i = 0; i < Lcount; i++)
	{
		pButton[i] = new CButton();
	}
}

void CMFCPROJECTSEHDADlg::LoaingButtonDestroy()
{
	if (pButton != NULL)
	{
		for (int i = 0; i < Lcount ; i++)
		{
			delete pButton[i];
			pButton[i] = NULL;
		}
		delete pButton;
		pButton = NULL;
	}
}


void CAboutDlg::OnTimer(UINT_PTR nIDEvent)
{
	//*********************************************// 
	//패에대한 이동, 배팅 대기시간 ***************//

	/*SetTimer(1394, 1000, NULL);


	파라매터

		1) Timer의 ID값

		2) SetTimer후 몇 millisecond후 마다 실행(반복실행)

		3) 함수명, NULL 사용시 오버라이드 함수 'OnTimer()'로 작동됩니다.

		반환값 : 핸들러

		[출처] MFC Timer(SetTimer, OnTimer, KillTimer, ON_WM_TIMER) | */


	CDialogEx::OnTimer(nIDEvent);
}
