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
     fmt = logging.Formatter(fmt='OmronFinsTcpModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

#保存注册句柄信息
SessionHandle = bytes()

def HandShake(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可
    Register = b'\x46\x49\x4E\x53\x00\x00\x00\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
    return Register

def HandShakeParase(paramlist,RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
    if len(RecvData) != 24:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    if RecvData[0:1] != b'\x46':
        log.error("handshake recv data command error.")
        return ""

    if RecvData[12:13] != b'\x00' or RecvData[13:14] != b'\x00' or RecvData[14:15] != b'\x00' or RecvData[15:16] != b'\x00':
        log.error("handshake recv data error.")
        return ""

    global SessionHandle
    SessionHandle = b''

    SessionHandle += RecvData[19:20]
    SessionHandle += RecvData[23:24]
    #loginfo = ""
    #for index in range(2):
    #    loginfo += str(SessionHandle[index])
    #    loginfo += ' '

    #log.debug("session value = [%s]",loginfo)
    
    return "ok"

def ReadAssembly(paramlist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nSoftElementAddress = int(paramlist[1])
    nSoftElementNum = int(paramlist[2])

    ####################### FINS/TCP帧 16 字节
    global SessionHandle
    if len(SessionHandle) != 2:
        log.error("the handshake not success")
        return ""

    package = bytearray(b'\x46\x49\x4E\x53') #TCP FINS header头标识
    package += b'\x00\x00\x00\x1A'#cmd length 长度
    package += b'\x00\x00\x00\x02'#frame command 命令吗
    package += b'\x00\x00\x00\x00'#错误代码
    ####################### FINS/TCP帧 end


    ####################### FINS 命令帧 start
    #10字节头部
    package += b'\x80\x00\x02\x00'
    package += SessionHandle[1:2] #目标节点地址，PLC IP地址最后一位，比如PLC IP为192.168.0.128 则填写0x80
    package += b'\x00\x00'
    package += SessionHandle[0:1]#源节点地址，PC IP地址最后一位，比如PLC IP为192.168.0.127 则填写0x7F
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
    if len(RecvData) < 30:
        log.error("recv data error.len = %d",len(RecvData))
        return ""


    if RecvData[28:29] != b'\x00':# or RecvData[29] != b'\x00':
        log.error("recv data end data error.")
        return ""

    #package = RecvData[30:len(RecvData)]

    #loginfo = ""
    #for index in range(len(package)):
    #    loginfo += '{:02X}'.format(package[index])
    #    loginfo += ' '

    #log.debug("readpackage %s",loginfo)
    return RecvData[30:len(RecvData)]





def WriteArrayAssembly(paramlist,datalist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nSoftElementAddress = int(paramlist[1])
    nSoftElementNum = int(paramlist[2])
    IntDataType = int(paramlist[0])
    nFloatSequence    = int(paramlist[3])
    ####################### FINS/TCP帧 16 字节
    global SessionHandle
    if len(SessionHandle) != 2:
        log.error("the handshake not success")
        return ""

    package = bytearray(b'\x46\x49\x4E\x53') #TCP FINS header头标识
    package += b'\x00\x00\x00\x0A'#cmd length 长度,长度最后重新赋值
    package += b'\x00\x00\x00\x02'#frame command 命令吗
    package += b'\x00\x00\x00\x00'#错误代码
    ####################### FINS/TCP帧 end


    ####################### FINS 命令帧 start
    #10字节头部
    package += b'\x80\x00\x02\x00'
    package += SessionHandle[1:2] #目标节点地址，PLC IP地址最后一位，比如PLC IP为192.168.0.128 则填写0x80
    package += b'\x00\x00'
    package += SessionHandle[0:1]#源节点地址，PC IP地址最后一位，比如PLC IP为192.168.0.127 则填写0x7F
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
                    else:
                        package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                        package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                else:
                    if 1 == nFloatSequence or 4 == nFloatSequence:
                        package += ord(info[index*2]).to_bytes(2,byteorder = 'big')
                    else:
                        package += ord(info[index*2]).to_bytes(2,byteorder = 'little')
                nWriteNum += 1

        elif bytes == type(info):
            nLoop = int(len(info) / 2) + (len(info) % 2)
            for index in range(nLoop):
                if index * 2 + 1 < len(info):
                    package += info[index * 2 + 1 : index * 2 + 2]
                    package += info[index * 2 : index * 2 + 1]
                else:
                    package += b'\x00'
                    package += info[index * 2 : index * 2 + 1]
                nWriteNum += 1

        if nWriteNum > int(nSoftElementNum):#实际的数据长度大于设置的软元件点数
            package = ""
            break

    #寄存器个数
    fTempReal = nWriteNum.to_bytes(2,byteorder = 'big')#具体数据
    package[32] = fTempReal[0]
    package[33] = fTempReal[1]

    #整体长度
    fTempRealLen = (nWriteNum *2 + 26).to_bytes(4,byteorder = 'big')#具体数据
    package[4] = fTempRealLen[0]
    package[5] = fTempRealLen[1]
    package[6] = fTempRealLen[2]
    package[7] = fTempRealLen[3]
    

    
    loginfo = ""
    for index in range(len(package)):
        loginfo += '{:02X}'.format(package[index])
        loginfo += ' '

    log.debug("readpackage %s",loginfo)
    return bytes(package)


def WritePrase(paramlist,RecvData):
    log.debug("recvdata is %s",RecvData)
    if len(RecvData) < 30:
        log.error("recv data error.len = %d",len(RecvData))
        return ""


    if RecvData[28:29] != b'\x00':# or RecvData[29] != b'\x00':
        log.error("recv data end data error.")
        return ""
    return "ok"
