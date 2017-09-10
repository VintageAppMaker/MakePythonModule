# -*- coding: cp949 -*-
#-------------------------------------------------------------------------------
# Name:        logcat 
# Purpose:     android logcat 정리 
#
# Author:      snake
#
# Created:     26/11/2011
# Copyright:   (c) snake 2011
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python
import sys
import os
import os.path
import stat
import re
import os, sys, re, StringIO
import ctypes
from threading import Thread
import time
import dlog
import time

helpString = """
---------------------------------------------------------------------
>>>> 로그 메시지 중 검색 원하는 단어를 입력 후, 엔터<<<<
---------------------------------------------------------------------
"""   
class Display(Thread):
    
    def AddKeyFilter(self, key):
	self.keylist.append(key)
	print self.keylist

    # key filter
    def IsKeywordLooking(self, key):
        count = 0 
        for i in self.keylist: 
            count = count + 1
            if key.find(i) > -1:
                return True 
        return False  
   
    # tag filter
    def IsTagLooking(self, tag):
        #list = ("kt_push", "PING", "System.err", "System.out")
        list = ("kt_push",  "System.out")
        count = 0 
        for i in list: 
            count = count + 1
            if tag.strip() == i:
                return count
        return 0  
   
    def WriteLog(self, str):
        f = open ("history", "a")
        f.write(str + "\r\n")
        f.close()
    
    def run(self):

        self.keylist = ["Start",  "Stop"]

	try:
            dlog.openwindow() 
            os.unlink("history")
        except:
            pass

        retag = re.compile("^([A-Z])/([^\(]+)\(([^\)]+)\): (.*)$")

        # 로그 clear
        input = os.popen("adb logcat -c")
        input = os.popen("adb logcat")
         
        dlog.dout("log capture를 시작했습니다", 0)
        while True:
            try:
                line = input.readline()
            except KeyboardInterrupt:
                break


            match = retag.match(line)
            if not match is None:
                tagtype, tag, owner, message = match.groups()
                
                count = self.IsTagLooking(tag)
                if count == 0:
                    continue
                now     = time.localtime()
                strTime = "%d-%d-%d %02d:%02d:%02d" % (now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec)

                bKeyword = self.IsKeywordLooking(message)
                if bKeyword == 0:
	            str = "[" + strTime + "] " + message[:-1]
                    self.WriteLog(str)
                    dlog.dout( str  , 2 )
                else:
                    str = "[" + strTime + "] " + message[:-1]
                    self.WriteLog(str)
                    dlog.dout( str  , 0 )
                
                

            # 입력 종료 
            if len(line) == 0: break
       
	dlog.closewindow()
        print """
        Program이 종료되었습니다.
        """
def main():
    f = Display()
    f.start()
 
    print helpString 

    b = True
    while b:
        sCMD =raw_input('명령을 입력하세요>')
        if sCMD == "q":
	    print "종료합니다"
	    dlog.closewindow()
            time.sleep(3)
            b = False

	else:
	    f.AddKeyFilter(sCMD)
            print sCMD + "가 추가되었습니다"
	    print helpString

if __name__ == '__main__':
    main()
