// PythonExtends.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "PythonExtends.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <Python.h>
#include "display.h"

// CPythonExtendsApp
BEGIN_MESSAGE_MAP(CPythonExtendsApp, CWinApp)
END_MESSAGE_MAP()

// CPythonExtendsApp ����
CDisplay m_dlg;
CPythonExtendsApp::CPythonExtendsApp()
{
}


// ������ CPythonExtendsApp ��ü�Դϴ�.
CPythonExtendsApp theApp;

// CPythonExtendsApp �ʱ�ȭ
BOOL CPythonExtendsApp::InitInstance()
{
    //TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	AfxInitRichEdit2();	

	CWinApp::InitInstance();
    return TRUE;
}

static PyObject * debug_logout(PyObject *self, PyObject *args);
static PyObject * debug_openwindow(PyObject *self, PyObject *args);
static PyObject * debug_closewindow(PyObject *self, PyObject *args);
static PyMethodDef DebugMethods[] = {
    {"dout",        debug_logout,      METH_VARARGS,"write message"},
    {"openwindow",  debug_openwindow,  METH_VARARGS,"open  window"},
	{"closewindow", debug_closewindow, METH_VARARGS,"close window"},
 
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


// WaitForSingleObject() ����ϱ����� �ڵ�
static HANDLE hWait = NULL;

void DebugOut(char* str, int spec)
{
	HWND hWnd = FindWindow(NULL, L"python debug view");
		
	if( hWnd != NULL)
	{
		const int MAX_SIZE = 1024 * 5;
		TCHAR szSend [MAX_SIZE];
        ZeroMemory(szSend, MAX_SIZE);

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), szSend, MAX_SIZE);
		m_dlg.WriteMessage(szSend, spec);
	} 
}

UINT ThreadFunc(LPVOID lpParam)
{
	m_dlg.SetHandle(hWait);
    m_dlg.DoModal();
	return 0L;
}

static PyObject* debug_openwindow(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    
	HWND hWnd = FindWindow(NULL, L"python debug view");
	if( hWnd != NULL) return Py_BuildValue("i", 1);
	
	AfxBeginThread(ThreadFunc, NULL);
	WaitForSingleObject(hWait, INFINITE);

	return Py_BuildValue("i", 0);
}

static PyObject* debug_logout(PyObject *self, PyObject *args)
{
    char *message;
	int  spec;
    if (!PyArg_ParseTuple(args, "si", &message, &spec))
        return NULL;
    
	DebugOut(message, spec);

	return Py_BuildValue("i", 0);
}

static PyObject * debug_closewindow(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    
	HWND hWnd = FindWindow(NULL, L"python debug view");
	if( hWnd == NULL) return Py_BuildValue("i", 1);
	
	SendMessage(hWnd, WM_CLOSE,0, 0);

	return Py_BuildValue("i", 0);
	
}

// Python �Լ� �ʱ�ȭ
PyMODINIT_FUNC initdlog() 
{
    Py_InitModule3("dlog", DebugMethods, "Debug log module");
	hWait = CreateEvent(NULL, TRUE, FALSE, NULL);
}


