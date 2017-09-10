# -*- coding: cp949 -*-
import dlog 
import os
import time

dlog.openwindow()
dlog.openwindow()

findlist = os.listdir("c:\\windows\\")
i = 0
for f in findlist:
    dlog.dout(f, i)
    i = i + 1

raw_input("아무키나 누르세요 - 윈도우 종료")
dlog.closewindow()
raw_input("아무키나 누르세요 - 윈도우 시작")

dlog.openwindow()
dlog.openwindow()

findlist = os.listdir("c:\\windows\\")
i = 0
for f in findlist:
    dlog.dout(f, i)
    i = i + 1

dlog.closewindow()
time.sleep(2)
