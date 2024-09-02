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
     fmt = logging.Formatter(fmt='OmronFinsUdpModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

g_nHostIpLast = 0
g_nTargetIpLast = 0

def HandShake(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可,此处只是做为传递IP数据方便之后的写和读使用
    if len(paramlist) < 8:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    global g_nHostIpLast
    global g_nTargetIpLast

    strHostIp = paramlist[3]
    strTargetIp = paramlist[5]

    HostList = strHostIp.split('.')
    g_nHostIpLast = int(HostList[len(HostList) - 1])

    TargetList = strTargetIp.split('.')
    g_nTargetIpLast = int(TargetList[len(TargetList) - 1])
    return ""

def HandShakeParase(paramlist,RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
        return ""

def ReadAssembly(paramlist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nSoftElementAddress = int(paramlist[1])
    nSoftElementNum = int(paramlist[2])

    global g_nHostIpLast
    global g_nTargetIpLast

    ####################### FINS 命令帧 start
    #10字节头部
    package = bytearray(b'\x80\x00\x02\x00')
    package += g_nTargetIpLast.to_bytes(length=1,byteorder='big') #目标节点地址，PLC IP地址最后一位，比如PLC IP为192.168.0.128 则填写0x80
    package += b'\x00\x00'
    package += g_nHostIpLast.to_bytes(length=1,byteorder='big')#源节点地址，PC IP地址最后一位，比如PLC IP为192.168.0.127 则填写0x7F
    package += b'\x00\x00'

    #2字节命令
    package += b'\x01\x01' #读寄存器
    #1字节寄存器标识
    package += b'\x82' #DM寄存器
    #3字节寄存器起始地址
    fTemp = int(nSoftElementAddress).to_bytes(length=3,byteorder='big')
    package += fTemp[1].to_bytes(length=1,byteorder='big')
    package += fTemp[2].to_bytes(length=1,byteorder='big')
    package += fTemp[0].to_bytes(length=1,byteorder='big')
    #package += int(nSoftElementAddress).to_bytes(2,byteorder = 'big')#起始元软件
    #package += b'\x00'

    #2字节寄存器个数
    package += int(nSoftElementNum).to_bytes(2,byteorder = 'big')#起始元软件
    #N字节 内容

    loginfo = ""
    for index in range(len(package)):
        loginfo += '{:02X}'.format(package[index])
        loginfo += ' '

    log.debug("readpackage %s",loginfo)
    return bytes(package)


#def GetData(Valuelist,nStart,nEnd):
    
#    if len(Valuelist) < nEnd:
#        return ""
#    package = Valuelist[nStart]
#    for i in range(nStart+1,nEnd):
#        package += Valuelist[i]

#    return package



def ReadPrase(paramlist,RecvData):

    #log.debug("recvdata is %s",RecvData)
    if len(RecvData) < 14:
        log.error("recv data error.len = %d",len(RecvData))
        return ""


    if RecvData[12:13] != b'\x00':# or RecvData[29] != b'\x00':
        log.error("recv data end data error.")
        return ""

    #package = RecvData[14:len(RecvData)]

    #loginfo = ""
    #for index in range(len(package)):
    #    loginfo += '{:02X}'.format(package[index])
    #    loginfo += ' '

    #log.debug("readpackage %s",loginfo)
    return RecvData[14:len(RecvData)]





def WriteArrayAssembly(paramlist,datalist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    IntDataType = int(paramlist[0])
    nSoftElementAddress = int(paramlist[1])
    nSoftElementNum = int(paramlist[2])
    nFloatSequence    = int(paramlist[3])
    
    global g_nHostIpLast
    global g_nTargetIpLast

    ####################### FINS 命令帧 start
    #10字节头部
    package = bytearray(b'\x80\x00\x02\x00')
    package += g_nTargetIpLast.to_bytes(length=1,byteorder='big') #目标节点地址，PLC IP地址最后一位，比如PLC IP为192.168.0.128 则填写0x80
    package += b'\x00\x00'
    package += g_nHostIpLast.to_bytes(length=1,byteorder='big')#源节点地址，PC IP地址最后一位，比如PLC IP为192.168.0.127 则填写0x7F
    package += b'\x00\x00'
    #2字节命令
    package += b'\x01\x02' #写寄存器
    #1字节寄存器标识
    package += b'\x82' #DM寄存器
    #3字节寄存器起始地址
    fTemp = int(nSoftElementAddress).to_bytes(length=3,byteorder='big')
    package += fTemp[1].to_bytes(length=1,byteorder='big')
    package += fTemp[2].to_bytes(length=1,byteorder='big')
    package += fTemp[0].to_bytes(length=1,byteorder='big')
    #2字节寄存器个数
    package += b'\x00\x00'#个数   最后赋值
    #package += int(nSoftElementNum).to_bytes(2,byteorder = 'big')#个数   最后赋值
    #N字节 内容
    nWriteNum = 0
    for info in datalist:
        if int == type(info):
            if IntDataType == 1:#int 占16位
                if info > 65535 or info < -32768:
                    package = ""
                    return package

                if 1 == nFloatSequence or 4 == nFloatSequence:
                    package += int(info& 0xFFFF).to_bytes(2,byteorder = 'big')#具体数据
                else:
                    package += int(info& 0xFFFF).to_bytes(2,byteorder = 'little')#具体数据
                nWriteNum += 1
            elif IntDataType == 2:#int 占32位
                fTempByte = int(info& 0xFFFFFFFF).to_bytes(4,byteorder = 'big')#具体数据
                if 1 == nFloatSequence:
                    package += fTempByte[0].to_bytes(length=1,byteorder='big')
                    package += fTempByte[1].to_bytes(length=1,byteorder='big')
                    package += fTempByte[2].to_bytes(length=1,byteorder='big')
                    package += fTempByte[3].to_bytes(length=1,byteorder='big')
                if 2 == nFloatSequence:
                    package += fTempByte[1].to_bytes(length=1,byteorder='big')
                    package += fTempByte[0].to_bytes(length=1,byteorder='big')
                    package += fTempByte[3].to_bytes(length=1,byteorder='big')
                    package += fTempByte[2].to_bytes(length=1,byteorder='big')
                if 3 == nFloatSequence:
                    package += fTempByte[3].to_bytes(length=1,byteorder='big')
                    package += fTempByte[2].to_bytes(length=1,byteorder='big')
                    package += fTempByte[1].to_bytes(length=1,byteorder='big')
                    package += fTempByte[0].to_bytes(length=1,byteorder='big')
                if 4 == nFloatSequence:
                    package += fTempByte[2].to_bytes(length=1,byteorder='big')
                    package += fTempByte[3].to_bytes(length=1,byteorder='big')
                    package += fTempByte[0].to_bytes(length=1,byteorder='big')
                    package += fTempByte[1].to_bytes(length=1,byteorder='big')

                nWriteNum += 2
        elif float == type(info):#float数据
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
            #package += struct.pack('<f',info) #二进制是正常的顺序
            fTempByte = struct.pack('<f',info) #DCBA
            if 1 == nFloatSequence:
                package += fTempByte[3].to_bytes(length=1,byteorder='big')
                package += fTempByte[2].to_bytes(length=1,byteorder='big')
                package += fTempByte[1].to_bytes(length=1,byteorder='big')
                package += fTempByte[0].to_bytes(length=1,byteorder='big')
            if 2 == nFloatSequence:
                package += fTempByte[2].to_bytes(length=1,byteorder='big')
                package += fTempByte[3].to_bytes(length=1,byteorder='big')
                package += fTempByte[0].to_bytes(length=1,byteorder='big')
                package += fTempByte[1].to_bytes(length=1,byteorder='big')
            if 3 == nFloatSequence:
                package += fTempByte[0].to_bytes(length=1,byteorder='big')
                package += fTempByte[1].to_bytes(length=1,byteorder='big')
                package += fTempByte[2].to_bytes(length=1,byteorder='big')
                package += fTempByte[3].to_bytes(length=1,byteorder='big')
            if 4 == nFloatSequence:
                package += fTempByte[1].to_bytes(length=1,byteorder='big')
                package += fTempByte[0].to_bytes(length=1,byteorder='big')
                package += fTempByte[3].to_bytes(length=1,byteorder='big')
                package += fTempByte[2].to_bytes(length=1,byteorder='big')

            nWriteNum += 2
        elif str == type(info):#string数据
            nLoop = int(len(info) / 2) + (len(info) % 2)
            for index in range(nLoop):
                if index*2 + 1 < len(info):
                    if 1 == nFloatSequence or 4 == nFloatSequence:
                        package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                        package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                    if 2 == nFloatSequence or 3 == nFloatSequence:
                        package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                        package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                else:
                    package += ord(info[index*2]).to_bytes(2,byteorder = 'little')
                nWriteNum += 1

        elif bytes == type(info):
            nLoop = int(len(info) / 2) + (len(info) % 2)
            for index in range(nLoop):
                if index * 2 + 1 < len(info):
                    if 1 == nFloatSequence or 4 == nFloatSequence:
                        package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                        package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                    else:
                        package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                        package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                else:
                    if 1 == nFloatSequence or 4 == nFloatSequence:
                        package += ord(info[index*2]).to_bytes(2,byteorder = 'big')
                    else:
                        package += ord(info[index*2]).to_bytes(2,byteorder = 'little')
                nWriteNum += 1

        if nWriteNum > int(nSoftElementNum):#实际的数据长度大于设置的软元件点数
            package = ""
            
            break

    #寄存器个数
    fTempReal = nWriteNum.to_bytes(2,byteorder = 'big')#具体数据
    package[16] = fTempReal[0]
    package[17] = fTempReal[1]

    
    loginfo = ""
    for index in range(len(package)):
        loginfo += '{:02X}'.format(package[index])
        loginfo += ' '

    log.debug("readpackage %s",loginfo)
    return bytes(package)


def WritePrase(paramlist,RecvData):
    #log.debug("recvdata is %s",RecvData)
    if len(RecvData) < 14:
        log.error("recv data error.len = %d",len(RecvData))
        return ""


    if RecvData[12:13] != b'\x00':# or RecvData[29] != b'\x00':
        log.error("recv data end data error.")
        return ""
    return "ok"
