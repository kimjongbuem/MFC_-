
// MFC PROJECT SEHDADlg.h: 헤더 파일
//
#include <atlimage.h>
#pragma once
// 로딩 버튼 //
#define BTN_PLAY 12000
#define BTN_OUTPUT_SCORE 12001
#define BTN_EXIT 12002

// 게임 버튼 //
#define BTN_CALL 12003
#define BTN_HALF 12004
#define BTN_DOUBLE 12005
#define BTN_DIE 12006
#define BTN_BACK 12007
// CMFCPROJECTSEHDADlg 대화 상자
class CMFCPROJECTSEHDADlg : public CDialogEx
{
public:
	bool selected[1][10] = { false };
public:
	CImage loadingImage; // 로딩화면 이미지 
	CImage userPicture;  // 유저 이미지
	CImage com1Picture;  // com1 이미지
	CImage com2Picture;  // com2 이미지
	CImage reversePae;   // 뒤집힌 패
// 생성입니다.
public:
	CMFCPROJECTSEHDADlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CButton** pButton;
	bool IsPlay = false; // 게임플레그
	bool IsOutput = false;
	int Lcount = 3; // 로딩버튼개수
	int gameButtonCount = 5; // 메인게임버튼개수

	afx_msg void OnButtonEvent(UINT ID); // 버튼이벤트
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECTSEHDA_DIALOG };
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
	void NotPlayImage();
	void PlayImage();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void MakeGameingButton();
	void GamingButtonDestroy();
	void MakeLoadingButton();
	void LoaingButtonDestroy();
};
