
// MFC PROJECT SEHDADlg.h: 헤더 파일
//

#pragma once
#include "GameManager.h"
//#include "Flags.h"


// CMFCPROJECTSEHDADlg 대화 상자
class CMFCPROJECTSEHDADlg : public CDialogEx
{
public:
	bool selected[2][10] = { false };
public:

// 생성입니다.
public:
	GameManager* manager;
	CMFCPROJECTSEHDADlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	// 변수 //
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
	
	afx_msg void OnButtonEvent(UINT ID); // 버튼이벤트
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 타이머

	
	void ResetNotSelected(); // 선택 패 리셋
};

