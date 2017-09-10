// Display.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PythonExtends.h"
#include "Display.h"

#define BACK_COLOR RGB(0xDF, 0xED, 0xCF)
#define SEL_BACK_COLOR RGB(0xFF, 0xFF, 0x0)

// CDisplay ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDisplay, CDialog)

CDisplay::CDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplay::IDD, pParent)
{

}

CDisplay::~CDisplay()
{
}

void CDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_display);
}


BEGIN_MESSAGE_MAP(CDisplay, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CDisplay::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	// ��ġ������ ��漳��
	m_display.SetBackgroundColor(FALSE, BACK_COLOR);

	// �����찡 ����� ���� Python ȣ���Լ��� �˷��ش�.
	SetEvent(hWait);

	bEnableResize = true;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CDisplay::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDisplay::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDisplay::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���ڿ� ���
void CDisplay::WriteMessage(TCHAR* msg, int spec)
{
	
	COLORREF cr[] = {
		RGB(10, 100, 55),
		RGB(255, 55, 11),
		RGB(0, 111, 255),
		RGB(12, 24, 48),
		RGB(48, 24, 112),
		RGB(0, 71, 255),
		RGB(0, 255, 155)
	};

	spec = spec % sizeof(cr);

	CHARFORMAT2 ufFontNormal;
	memset(&ufFontNormal, 0, sizeof(CHARFORMAT2));
	ufFontNormal.crTextColor = RGB(11, 22, 11);

	ufFontNormal.crBackColor = (spec == 0) ? SEL_BACK_COLOR : BACK_COLOR; 

	ufFontNormal.dwMask      = CFM_EFFECTS2;
	ufFontNormal.dwEffects   = CFE_BOLD  | CFE_STRIKEOUT | CFM_BACKCOLOR;
	ufFontNormal.yHeight     = 180; 
	_tcscpy(ufFontNormal.szFaceName, L"����ü");

	// �ڵ� ��ũ���� ���� ���
	m_display.HideSelection(FALSE,FALSE);

	// �� ���������� ĳ���� �ű��
	CHARRANGE rng;
	rng.cpMax = m_display.GetTextLength();	 
	rng.cpMin = rng.cpMax;
	m_display.SetSel( rng );
	m_display.SetSelectionCharFormat(ufFontNormal);

	// ���γѹ�ġȯ
	CString str =L"";
	str.Format(L"%04d:", nLineNum);
	m_display.ReplaceSel( str.GetBuffer() );
    
	// �ڵ� ��ũ���� ���� ���
	m_display.HideSelection(FALSE,FALSE);

	// �� ���������� ĳ���� �ű��
	ufFontNormal.crTextColor = cr[spec];
	ufFontNormal.dwEffects   = (spec == 0) ? (CFE_ITALIC) : 0; 
	rng.cpMax = m_display.GetTextLength();	 
	rng.cpMin = rng.cpMax;
	m_display.SetSel( rng );
	m_display.SetSelectionCharFormat(ufFontNormal);

	m_display.ReplaceSel( msg );
	m_display.ReplaceSel( L"\r\n" );
	nLineNum++;

}

void CDisplay::OnSize(UINT nType, int cx, int cy)
{
	// TODO: Add your message handler code here

	//bEnableResize is enabled in ::OnInitDialog()
	if ( bEnableResize ) //To avoid problem in OnSize
	{
		RECT * lpRect = new RECT();
		GetClientRect (lpRect);
        
		m_display.SetWindowPos( &wndBottom, lpRect->left, lpRect->top, cx, cy, SWP_SHOWWINDOW);

		Invalidate (TRUE);
	}

	CDialog::OnSize(nType, cx, cy);

}
