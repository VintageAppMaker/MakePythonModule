#pragma once
#include "afxcmn.h"


// CDisplay 대화 상자입니다.

class CDisplay : public CDialog
{
	DECLARE_DYNAMIC(CDisplay)

public:
	CDisplay(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDisplay();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_display;
	
	// 라인넘버
	int nLineNum;
	void WriteMessage(TCHAR* msg, int spec = 0);
	HANDLE hWait;
	inline void SetHandle(HANDLE h){hWait = h;}

	bool bEnableResize;
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
