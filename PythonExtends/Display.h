#pragma once
#include "afxcmn.h"


// CDisplay ��ȭ �����Դϴ�.

class CDisplay : public CDialog
{
	DECLARE_DYNAMIC(CDisplay)

public:
	CDisplay(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDisplay();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_display;
	
	// ���γѹ�
	int nLineNum;
	void WriteMessage(TCHAR* msg, int spec = 0);
	HANDLE hWait;
	inline void SetHandle(HANDLE h){hWait = h;}

	bool bEnableResize;
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
