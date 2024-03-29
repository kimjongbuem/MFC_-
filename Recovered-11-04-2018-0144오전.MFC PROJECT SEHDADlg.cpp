
// MFC PROJECT SEHDADlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC PROJECT SEHDA.h"
#include "MFC PROJECT SEHDADlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MOVE_MONEY 4
#define TIMEOUT 7
#define COM_TURN 6
#define USER_TURN 5
#define WAIT 3
#define MOVE_PAE 2
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
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()

CMFCPROJECTSEHDADlg::CMFCPROJECTSEHDADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECTSEHDA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	ON_WM_TIMER()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

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
void CMFCPROJECTSEHDADlg::OnButtonEvent(UINT ID)
{
	HWND hwnd = this->GetSafeHwnd();
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	switch (ID)
	{
	case BTN_PLAY:
		manager->CallButton()->LoaingButtonDestroy();
		manager->isPlay = true;
		Invalidate(false);
		break;
	case BTN_OUTPUT_SCORE:
		break;
	case BTN_EXIT:
		exit(1); // 종료 //
		break;
	case BTN_CALL:
		manager->isButtonClick = true;
		break;
	case BTN_HALF:
		manager->isButtonClick = true;
		break;
	case BTN_DOUBLE:
		manager->isButtonClick = true;
		break;

	case BTN_DIE:
		break;
	case BTN_BACK:
		manager->CallProgress()->DeleteProgressControl();
		manager->CallButton()->GamingButtonDestroy();
		manager->isPlay = false;
		manager->isReLoadButton = true;
		manager->isMovePae = true;
		manager->isButtonClick = false;
		manager->isTurn[0] = false;
		manager->isTurn[1] = false;
		manager->isTurn[2] = false;
		manager->printMoney = false;
		Invalidate(false);
		break;

	}
}
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
		HWND hwnd = this->GetSafeHwnd();
		CWnd* pWnd = CWnd::FromHandle(hwnd);
		CPaintDC dc(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		CString caption;
		CRect rect;
		GetClientRect(&rect);
		CBitmap bitmap;
		CBitmap* pBitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		pBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
		if (!manager->isPlay) // 로딩 //
		{
			manager->CallButton()->MakeLoadingButton(pWnd,hwnd);
			manager->CallpImage()->LoadingImage(&memDC,hwnd);
			
		}
		else // 게임 //
		{
			if (manager->isReLoadButton)
			{
				manager->CallProgress()->MakeProgressControl(pWnd);
				manager->CallButton()->MakeGameingButton(pWnd, hwnd);
				manager->isReLoadButton = false;
			}
				manager->CallpImage()->PlayingImage(&memDC, hwnd);
				if (manager->printMoney)
				{
					manager->OutputMoney(&memDC, hwnd);
				}
			if (!manager->isWaiting)
			{
				if (manager->countPae == 0)
				{
					
					manager->MoveComputerReversePae(&memDC, hwnd, 0);
					manager->MoveUserPae(&memDC, hwnd, 0);
				}
				else
				{
					manager->MoveComputerReversePae(&memDC, hwnd, manager->countPae);
					manager->MoveUserPae(&memDC, hwnd, manager->countPae);
					if (manager->isPrintWin)
						manager->PrintWinEmage(&memDC, hwnd);
				}
			}
			
		}
		CDialogEx::OnPaint();
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pBitmap);
		ReleaseDC(&memDC);
		DeleteDC(memDC);
		DeleteObject(bitmap);

	}
}

BOOL CMFCPROJECTSEHDADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	manager = new GameManager();
	
	
	SetTimer(TIMEOUT, 1000, NULL);
	SetTimer(USER_TURN, 100, NULL);
	SetTimer(COM_TURN, 1500, NULL);
	SetTimer(MOVE_PAE, 110, NULL); // 패의 이동 초
	SetTimer(WAIT, 3000, NULL); //결과초	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
HCURSOR CMFCPROJECTSEHDADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCPROJECTSEHDADlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIMEOUT:
		
		if (manager->isTurn[0] && !manager->isButtonClick)
		{
			int pos = manager->CallProgress()->GetPos();
			if(pos>0)
				pos--;
			manager->CallProgress()->SetPos(pos);
		}
		
		break;
	case USER_TURN:
		if (manager->isTurn[0]) // 
		{
			if (manager->isButtonClick)
			{
				manager->printMoney = true;
				manager->isTurn[0] = false;
				manager->isWaiting = true;
				manager->CallProgress()->SetPos(5);
				manager->moneyCount++;
			}
		}
	break;
	case WAIT:
		if (manager->isPlay && manager->isWaiting && !manager->isOutPutCheck && !manager->isTurn[0]) //  플레이하고 3초 대기 했다면~
		{
			
			manager->isWaiting = false; // 대기 안함으로 바꿈
			manager->isPicked = true;
			if (manager->countPae == 2)
			{
				manager->isOutPutCheck = true;
				manager->isPrintWin = true;
				manager->isMovePae = false;
			}
			Invalidate(false);
			
			break;
		}
		//else if (manager->isOutPutCheck && !manager->isPrintWin) // 결과가 끝난후 
		//{			
		//	break;
		//}
		else if (manager->isPrintWin)
		{
			manager->isOutPutCheck = false;
			manager->isPrintWin = false;
			manager->ResetWinFlag();
			manager->ResetCalibrateValue();
			manager->ResetNotSelected();
			manager->countPae = 0;
			manager->isWaiting = true;
			manager->isMovePae = true;
			manager->printMoney = false;
			manager->moneyCount = 0;
		}
		break;							
	
	case MOVE_PAE:
		
		if (manager->isPlay && !manager->isWaiting && manager->isMovePae && !manager->isTurn[0]) //  플레이하고 패를 나눌때~
		{
			
				if (manager->countPae<=1 &&manager->calibrateValue[manager->countPae][0][1] <= 200)
				{
					manager->calibrateValue[manager->countPae][0][0] += 10;
					manager->calibrateValue[manager->countPae][0][1] += 20;

					manager->calibrateValue[manager->countPae][1][0] += 10;
					manager->calibrateValue[manager->countPae][1][1] += 20;

					manager->calibrateValue[manager->countPae][2][0] += 3;
					manager->calibrateValue[manager->countPae][2][1] += 2;
					Invalidate(false); // 해당이동부분만 변화게하므로 ㅋ
					break;
				}
				manager->isButtonClick = false;
				manager->isTurn[0] = true;
				if (manager->countPae <= 1)
				{
					manager->countPae++;
				}
		}
		
		break;
		CDialogEx::OnTimer(nIDEvent);
	}
}
