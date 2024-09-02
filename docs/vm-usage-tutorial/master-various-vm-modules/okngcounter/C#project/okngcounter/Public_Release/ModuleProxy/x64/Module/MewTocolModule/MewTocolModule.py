import struct
import logging
import ctypes

# output "logging" messages to DbgView via OutputDebugString (Windows only!)
OutputDebugString = ctypes.windll.kernel32.OutputDebugStringW

class DbgViewHandler(logging.Handler):
 def emit(self, record):
  OutputDebugString(self.format(record))

log = logging.getLogger("output.debug.string.example")

def config_logging():
    # format
     fmt = logging.Formatter(fmt='MewTocolModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

def GetBCC(data):
    BCC = ord(data[0])
    for index in range(1,len(data)):
        BCC ^= ord(data[index])
    return BCC

def ReadAssembly(paramlist):

    package=""
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    StarionNum = int(paramlist[0])
    SoftElementType = int(paramlist[1])
    IntDataType = int(paramlist[2])
    SoftElementAddress = int(paramlist[3])
    SoftElementNum = int(paramlist[4])

    package = '%'#起始符(1Byte)
    package += '{:02X}'.format(StarionNum)#站号(2Byte)
    package += '#RD'#  "#"+指令代码(RD)
    package += 'D'#  数据代码(D)
    package += '{:05d}'.format(SoftElementAddress)#起始数据编码(5字符)
    package += '{:05d}'.format(SoftElementAddress + SoftElementNum -1)#结束数据编码(5字符)
    package += '{:02X}'.format(GetBCC(package))#校验
    package += chr(0x0D)
    #log.debug("get package is %s",package)
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
    if len(RecvData) > 4 and b'$' == RecvData[3:4]:
        nDataLen = len(RecvData) - 9
        return RecvData[6:6+nDataLen]

    return ""




def WriteArrayAssembly(paramlist,datalist):
    #FrameFormat,DataCode,SoftElementType,IntDataType,SoftElementAddress,SoftElementNum
    package=""
    
    if len(paramlist) < 7:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    StarionNum = int(paramlist[0])
    SoftElementType = int(paramlist[1])
    IntDataType = int(paramlist[2])
    SoftElementAddress = int(paramlist[3])
    SoftElementNum = int(paramlist[4])

    nWriteNum = 0;
    #计算下需要的寄存器个数
    for info in datalist:
        if int == type(info):
            if IntDataType == 1:#int 占16位
                nWriteNum += 1
            elif IntDataType == 2:#int 占32位
                nWriteNum += 2
        elif float == type(info):#float数据
                nWriteNum += 2
        elif str == type(info):#字符串数据
                nWriteNum += (int(len(info) / 2) + int(len(info) % 2))
        elif bytes == type(info):#字符串数据
                nWriteNum += (int(len(info) / 2) + int(len(info) % 2))

    if nWriteNum > SoftElementNum:
        log.error("softnum is not enough  %d-%d",nWriteNum,SoftElementNum)
        return ""


    package = '%'#起始符(1Byte)
    package += '{:02X}'.format(StarionNum)#站号(2Byte)
    package += '#WD'#  "#"+指令代码(WD)
    package += 'D'#  数据代码(D)
    package += '{:05d}'.format(SoftElementAddress)#起始数据编码(5字符)
    package += '{:05d}'.format(SoftElementAddress + nWriteNum -1)#结束数据编码(5字符)

    #写入数据
    for info in datalist:
        if int == type(info):
            if IntDataType == 1:#int 占16位
                if info > 65535 or info < -32768:
                    package = ""
                    return package
                fTemp = int(info & 0xFFFF).to_bytes(length=2,byteorder='little')

                package +=  '{:02X}'.format(fTemp[0])
                package +=  '{:02X}'.format(fTemp[1])

            elif IntDataType ==2:#int 占32位
                fTemp = int(info& 0xFFFFFFFF).to_bytes(length=4,byteorder='little')

                package +=  '{:02X}'.format(fTemp[0])
                package +=  '{:02X}'.format(fTemp[1])
                package +=  '{:02X}'.format(fTemp[2])
                package +=  '{:02X}'.format(fTemp[3])

        elif float == type(info):#float数据
                fTemp = struct.pack('f', info)
                package +=  '{:02X}'.format(fTemp[0])
                package +=  '{:02X}'.format(fTemp[1])
                package +=  '{:02X}'.format(fTemp[2])
                package +=  '{:02X}'.format(fTemp[3])
        elif str == type(info):#字符串数据
                nLoop = int(len(info) / 2) + (len(info) % 2)
                for index in range(nLoop):
                    if index*2 + 1 < len(info):
                        package += '{:02X}'.format(ord(info[index*2]))
                        package += '{:02X}'.format(ord(info[index*2+1]))
                    else:
                        package += '{:0<4X}'.format(ord(info[index*2]))

        elif bytes == type(info):
            nLoop = int(len(info) / 2) + (len(info) % 2)
            for index in range(nLoop):
                if index * 2 + 1 < len(info):
                    package += '{:02X}'.format(info[index * 2])
                    package += '{:02X}'.format(info[index * 2 + 1])
                else:
                    package += '{:0<4X}'.format(info[index * 2])
                    


    package += '{:02X}'.format(GetBCC(package))#校验
    package += chr(0x0D)
    #log.debug("get package is %s",package)
    return package


def WritePrase(paramlist,RecvData):
    package=""
    #log.debug("recvdata is %s",RecvData)

    if len(paramlist) < 7:
        return ""
    if len(RecvData) > 4 and b'$' == RecvData[3:4]:
        return "ok"

    return ""