// Display.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PythonExtends.h"
#include "Display.h"

#define BACK_COLOR RGB(0xDF, 0xED, 0xCF)
#define SEL_BACK_COLOR RGB(0xFF, 0xFF, 0x0)

// CDisplay 대화 상자입니다.

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

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	// 리치에디터 배경설정
	m_display.SetBackgroundColor(FALSE, BACK_COLOR);

	// 윈도우가 실행된 것을 Python 호출함수에 알려준다.
	SetEvent(hWait);

	bEnableResize = true;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDisplay::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDisplay::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDisplay::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 문자열 출력
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
	_tcscpy(ufFontNormal.szFaceName, L"굴림체");

	// 자동 스크롤을 위한 편법
	m_display.HideSelection(FALSE,FALSE);

	// 맨 마지막으로 캐럿을 옮기고
	CHARRANGE rng;
	rng.cpMax = m_display.GetTextLength();	 
	rng.cpMin = rng.cpMax;
	m_display.SetSel( rng );
	m_display.SetSelectionCharFormat(ufFontNormal);

	// 라인넘버치환
	CString str =L"";
	str.Format(L"%04d:", nLineNum);
	m_display.ReplaceSel( str.GetBuffer() );
    
	// 자동 스크롤을 위한 편법
	m_display.HideSelection(FALSE,FALSE);

	// 맨 마지막으로 캐럿을 옮기고
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
