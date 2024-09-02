import struct
import logging
import ctypes
########################
# 此协议只支持单类型数据写入
########################


# output "logging" messages to DbgView via OutputDebugString (Windows only!)
OutputDebugString = ctypes.windll.kernel32.OutputDebugStringW

class DbgViewHandler(logging.Handler):
 def emit(self, record):
  OutputDebugString(self.format(record))

log = logging.getLogger("output.debug.string.example")

def config_logging():
    # format
     fmt = logging.Formatter(fmt='InovanceH2UModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

#保存注册句柄信息
#SessionHandle = bytes()

#def HandShake():#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可
#    return 

#def HandShakeParase(RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
#    return 

def ReadACK(RecvData):#读取到数据后返回给PLC的确认信息，目前只有汇川有
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nStationNum = int(paramlist[0])

    package = chr(0x06)
    package += '{:02d}'.format(nStationNum)
    package += 'FF'
    return package

def ReadAssembly(paramlist):
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nStationNum = int(paramlist[0])
    nSoftElementType = int(paramlist[1])
    nIntDataType = int(paramlist[2])
    nSoftElementAddress = int(paramlist[3])
    nSoftElementNum = int(paramlist[4])
    nOverTime= int(paramlist[6])


    #global SessionHandle

    package = chr(0x05)
    package += '{:02d}'.format(nStationNum)
    if nSoftElementType == 1:
        package += 'FFWR'
    else:
        package += 'FFBR'

    package += 'E'

    if nSoftElementType == 1:#软元件代码
        package += "D"
    elif SoftElementType == 2:
        package += "M"
    elif SoftElementType == 3:
        package += "X"
    elif SoftElementType == 4:
        package += "Y"

    package += '{:04d}'.format(nSoftElementAddress)
    package += '{:02X}'.format(nSoftElementNum)


    #log.debug("readpackage %s",package)
    return package


#def GetData(Valuelist,nStart,nEnd):
    
#    if len(Valuelist) < nEnd:
#        return ""
#    package = Valuelist[nStart]
#    for i in range(nStart+1,nEnd):
#        package += Valuelist[i]

#    return package



def ReadPrase(paramlist,RecvData):

    #log.debug("recvdata is %s",RecvData)
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    nSoftElementType = int(paramlist[1])
    nSoftElementNum = int(paramlist[4])

    if RecvData[0:1] != b'\x02':
        log.error("ReadPrase recv data command error.")
        return ""

    
    if len(RecvData) < 5:
        log.error("ReadPrase recv error.len = %d",len(RecvData))
        return ""

    nDataSize = 0
    if nSoftElementType == 1:#软元件代码
        nDataSize = nSoftElementNum *4
    else:
        nDataSize = nSoftElementNum

    if (5 + nDataSize) < len(RecvData):
        return ""

    package = RecvData[5:len(RecvData)]
    #log.debug("readpackage %s",package)
    return package



def WriteArrayAssembly(paramlist,datalist):
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nStationNum = int(paramlist[0])
    nSoftElementType = int(paramlist[1])
    nIntDataType = int(paramlist[2])
    nSoftElementAddress = int(paramlist[3])
    nSoftElementNum = int(paramlist[4])
    nOverTime= int(paramlist[6])
    nWriteNum = 0

    #global SessionHandle

    package = chr(0x05)
    package += '{:02d}'.format(nStationNum)
    if nSoftElementType == 1:
        package += 'FFWW'
    else:
        package += 'FFBW'

    package += 'E'

    if nSoftElementType == 1:#软元件代码
        package += "D"
    elif SoftElementType == 2:
        package += "M"
    elif SoftElementType == 3:
        package += "X"
    elif SoftElementType == 4:
        package += "Y"

    package += '{:04d}'.format(nSoftElementAddress)
    package += '**'

    for info in datalist:
        if int == type(info):
            if nIntDataType == 1:#int 占16位
                if info > 65535 or info < -32768:
                    package = ""

                    return package
                package += '{:04X}'.format(int(info & 0xFFFF))#具体数据
                nWriteNum += 1
            elif nIntDataType == 2:#int 占32位
                strData = '{:08X}'.format(int(info & 0xFFFFFFFF))
                nWriteNum += 2
        elif float == type(info):#float数据
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
                fTemp = struct.pack('f', info)
                package +=  '{:02X}'.format(fTemp[3])
                package +=  '{:02X}'.format(fTemp[2])
                package +=  '{:02X}'.format(fTemp[1])
                package +=  '{:02X}'.format(fTemp[0])
                nWriteNum += 2
        elif str == type(info):#string数据
                nLoop = int(len(info) / 2) + (len(info) % 2)
                for index in range(nLoop):
                    if index*2 + 1 < len(info):
                        package += '{:02X}'.format(ord(info[index*2+1]))
                        package += '{:02X}'.format(ord(info[index*2]))
                    else:
                        package += '{:04X}'.format(ord(info[index*2]))
                    nWriteNum += 1

        elif bytes == type(info):
                nLoop = int(len(info) / 2) + (len(info) % 2)
                for index in range(nLoop):
                    if index * 2 + 1 < len(info):
                        package += '{:02X}'.format(info[index * 2 + 1])
                        package += '{:02X}'.format(info[index * 2])
                    else:
                        package += '{:04X}'.format(info[index * 2])
                    nWriteNum += 1
    package = package.replace('**','{:02X}'.format(nWriteNum))#长度赋值
    #log.debug("readpackage %s",package)
    return package


def WritePrase(paramlist,RecvData):
    #log.debug("recvdata is %s",RecvData)
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    if RecvData[0:1] != b'\x06':
        log.error("ReadPrase recv data command error.")
        return ""

    
    if len(RecvData) < 5:
        log.error("ReadPrase recv error.len = %d",len(RecvData))
        return ""

    #nStationNum = int(paramlist[0])
    return "ok"
