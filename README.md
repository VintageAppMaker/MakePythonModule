# MakePythonModule

[원본블로그](http://blog.naver.com/adsloader/50138205442)

### 목적
 
  1. 파이썬 모듈을 Visual C++로 만들기
  2. Windows 파이썬에서 console로 로그를 출력하다 보면 나중에 캡쳐하기가 불편해진다. 그러한 이유로 console out을 할 때, 윈도우
형태의 GUI가 필요할 때가 있다.

![원본블로그](http://postfiles10.naver.net/20120404_281/adsloader_1333515006113ppfFi_PNG/1.PNG?type=w2)

Windows에서 파이썬 프로그램을 개발할 때, 로그 출력을 위한 GUI 부분을 Visual C++로
쉽게 만들어 사용하고자 하는 것이 목적이다. wxPython이나 기타 GUI 라이브러리들이 있으나 자신
이 원하는 형태로 만드는 데까지는 학습이 필요하므로 빠르게 GUI를 적용할 경우는 위와 같은 방
법도 효율적이다.

### 개발환경
- Visual C++(2008)
- Python2.7(화면은 설정은 2.5)

다음은 프로젝트 설정은 파이썬 2.5가 c:\python25에 설치되었다는 가정이다. 만약 python2.7이 설치되어 있고 c:\python27에 설치되었다면
~~~
- 링커: 추가라이브러리 디렉터리 -> c:\python27\libs
- C/C++: 추가포함 디렉터리 -> c:\python27\inlclude
~~~
로 설정해주면 된다.

![원본블로그](http://postfiles14.naver.net/20120404_173/adsloader_1333515047457AbJSr_PNG/3.PNG?type=w2)
![원본블로그](http://postfiles8.naver.net/20120404_167/adsloader_1333515048839WD9jp_PNG/2.PNG?type=w2)

*) 개발하는 PC에 설치된 python의 경로를 입력해야 한다.
 
- #include <python.h>를 소스에 적용한다.
-  프로젝트는 release로 한다(debug시에는 python_d.lib이 필요함)=
- 출력파일은 $(OutDir)\dlog.pyd와 같이 한다(import하는 모듈명과 동일해야 함).

### Python extend 함수 구현

- 모듈초기화 함수
DLL(.pyd)의 파일명과 동일한 함수가 초기화 함수다. 이곳에서는 python에서 사용할 함수테이블을 등록하는 기능을 수행한다. 네이밍룰은 “init + 모듈명”이다.

~~~C++

// Python 함수초기화
PyMODINIT_FUNC initdlog()
{
    Py_InitModule3("dlog", DebugMethods, "Debug log module");
    hWait = CreateEvent(NULL, TRUE, FALSE, NULL);
}

~~~

- Function 등록
 
~~~C++

Py_InitModule3() 함수는 첫번째 파라메터는 모듈명이다. 그리고 두번째 파라메터는 사용할 함수들을 정의한 function table이다.
 
static PyMethodDef DebugMethods[] = {
    {"dout",        debug_logout,      METH_VARARGS,"write message"},
    {"openwindow",  debug_openwindow,  METH_VARARGS,"open  window"},
    {"closewindow", debug_closewindow, METH_VARARGS,"close window"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};
~~~

- openwindow
Windows 프로그램의 특성상 Form은 DoModal()이 실행되는 순간, 같은 문맥(context)에서는 Form이 종료되지 않는 한, 다음코드들이 진행될 수 없다. 그러므로 “폼을 제어하는 함수”를 다른 문맥에서 처리하기 위해서 다음과 같은 방법을 사용한다.
 
목적: openwinow() 함수를 block 방식으로 구현한다. 그러나 python에서는 무한대기하지 않고 Dialog 생성 후에도 Dialog의 메소드를 호출하여 사용할 수 있도록 한다.
 
-    모듈 초기화 때(initdlog)에 Event를 하나 등록한다.
-    openwindow() 함수 호출하면 thread 생성하고 WaitForSingleObject()로 대기한다.
-    Thread에서 Dialog에 이벤트 핸들을 넘기고 DoModal()로 화면에 보인다.
-    Dialog에서 initDialog 이벤트에서 실행 결과를 SetEvent()로 알려준다.
-    openwindow() 함수에서 대기가 풀린다.  
-    Dialog가 화면에 나타났고 Dialog에 관련 메소드를 사용할 수 있다.

![원본블로그](http://postfiles13.naver.net/20120404_220/adsloader_1333515076579LSfvK_PNG/4.PNG?type=w2)

- closewindow
다른 문맥에서 Form을 종료해야 하므로 다음과 같이 종료 메시지를 보낸다.

~~~c++
SendMessage(hWnd, WM_CLOSE,0, 0);
~~~ 

참고로 종료메시지가 처리되는 순간 Python이 종료되면 윈도우에서 abnormal terminated 에러가 발생하므로 python에서는 closewindow()를 실행 후, 몇 초간 대기해주는 코드를 작성하는 것이 좋다.



