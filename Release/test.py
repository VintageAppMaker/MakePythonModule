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

raw_input("�ƹ�Ű�� �������� - ������ ����")
dlog.closewindow()
raw_input("�ƹ�Ű�� �������� - ������ ����")

dlog.openwindow()
dlog.openwindow()

findlist = os.listdir("c:\\windows\\")
i = 0
for f in findlist:
    dlog.dout(f, i)
    i = i + 1

dlog.closewindow()
time.sleep(2)
