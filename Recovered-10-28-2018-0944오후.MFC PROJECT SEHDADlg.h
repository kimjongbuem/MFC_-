
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
	// FLAG //
	bool IsPlay = false; // 게임 시작플레그
	bool IsOutput = false;
	bool isLashing = false; // 패를 돌것인가에 대한 플레그
	//bool isCalibrate = true; //
	bool isWaiting = true; // 대기 플레그
	bool isReLoadButton = true; // 버튼메모리관리 플래그
	// bool isMovePae = true; //  패를 돌릴때 움직일것인가에 대한 플레그
public:
	bool selected[2][10] = { false };
public:
	// IMAGE //
	CImage loadingImage; // 로딩화면 이미지 
	CImage userPicture;  // 유저 이미지
	CImage com1Picture;  // com1 이미지
	CImage com2Picture;  // com2 이미지
	CImage reversePae;   // 뒤집힌 패
	CImage movingPae[2][3]; // 움직이는 패 6개 ( 1번째패 2번째패 분배시)

// 생성입니다.
public:
	
	CMFCPROJECTSEHDADlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	// 변수 //
	CButton** pButton;
	int countPae = 0; // 패 개수 3개 이상이면 패돌리지않게~
	int Lcount = 3; // 로딩버튼개수
	int gameButtonCount = 5; // 메인게임버튼개수
	int calibrateValue[3][2] = { 0 }; // 3은 각 패, idx[0]은 페의 x 보정값 idx[1]은 패의 y보정값임
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
	virtual BOOL OnInitDialog();//
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint(); // 여기다 로직
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void NotPlayImage(); // 로딩화면
	void PlayImage(); // 플레이화면
	afx_msg void OnButtonEvent(UINT ID); // 버튼이벤트
	void PicturePlayDestory(CPaintDC dc);
	void MakeGameingButton(); // 플레이시 만드는 버튼들
	void GamingButtonDestroy(); // 플레이버튼파괴
	void MakeLoadingButton(); // 로딩시 버튼 만들기
	void LoaingButtonDestroy(); // 로딩 버튼 파괴
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 타이머
	void RemovePaeImage(); // 패이미지 삭제-> 다시 그리기위함
	void PaintMovingPaeImage(int);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
