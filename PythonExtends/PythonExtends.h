// PythonExtends.h : PythonExtends DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPythonExtendsApp
// �� Ŭ������ ������ ������ PythonExtends.cpp�� �����Ͻʽÿ�.
//

class CPythonExtendsApp : public CWinApp
{
public:
	CPythonExtendsApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
