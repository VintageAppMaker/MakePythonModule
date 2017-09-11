# MakePythonModule

[원본블로그](http://blog.naver.com/adsloader/50142012166)

### 목적
 
윈도우에서는 Windows Management Instrumentation (WMI)라는 Interface를 제공한다. WMI를 짧게 설명하자면 윈도우 관리에 관련된 전반의 기능을 SQL과 같은 질의문으로 처리할 수 있도록 한, COM 엔진이라고 보면 된다. 예상외로 상당히 방대한 내용의 윈도우 정보(OS에서 관리하는 HW에서 SW의 많은 부분)를 DB처럼 사용할 수 있다.
 
[WMI 관련 Query 예제 사이트](http://www.scribd.com/doc/52635557/35/-InstanceCreationEvent)
 
[MSDN 예제 사이트 - 1](http://msdn.microsoft.com/en-us/library/windows/desktop/aa394582(v=vs.85).aspx)
[MSDN 예제 사이트 - 2](http://msdn.microsoft.com/en-us/library/windows/desktop/aa390424(v=vs.85).aspx)
 
WMI를 이용하여 Process의 실행/중지를 이벤트를 통하여 감시할 수도 있다.
 
물론 process 감시를 위해 FindWindow나 EnumProcess같은 API를 사용 할 수도 있다.
그러나 몇 가지 예외 상황에서는 WMI를 사용하는 것이 무척 효율적이고 강력하다.
 
이 글에서는 WMI를 이용하여 Process를 감시하는 예제를 구현할 것이다.


