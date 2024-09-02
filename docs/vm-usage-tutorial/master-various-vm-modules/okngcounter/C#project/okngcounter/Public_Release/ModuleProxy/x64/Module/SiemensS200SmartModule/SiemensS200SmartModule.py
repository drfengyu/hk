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
     fmt = logging.Formatter(fmt='SiemensS200SmartModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

#保存注册句柄信息
bRegister = False

def HandShake(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可
    if len(paramlist) < 10:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nRack = int(paramlist[7])
    nSlot = int(paramlist[8])
    Register = b'\x03\x00\x00\x16' #TPKT
    Register += b'\x11' #COTP Header Length
    Register += b'\xE0' #Connect Request 
    Register += b'\x00\x00' #Destination Reference


    Register += b'\x00\x01' #Source Reference源引用
    Register += b'\x00' #Flags 扩展格式/流控制
    Register += b'\xC1' #Parameter Code (src-tasp) 参数代码TPDU-Size
    Register += b'\x02' #Parameter Length 参数长度

    Register += b'\x10' #Source TASP S71200 TPDU大小
    Register += b'\x00' #Source TASP S71200 TPDU大小
    
    Register += b'\xC2' #Parameter Code (dst-tasp) 参数代码SRC-TASP
    Register += b'\x02' #参数长度
    
    Register += b'\x03\x00' #
  
    Register += b'\xC0' #Parameter Code (tpdu-size)
    Register += b'\x01' #Parameter Length
    Register += b'\x0A' #TPDU Size (2^10 = 1024)
    global bRegister
    bRegister = False

    return Register

def HandShakeParase(paramlist,RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
    if len(paramlist) < 10:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    nRack = int(paramlist[7])
    nSlot = int(paramlist[8])

    if len(RecvData) != 22:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    if RecvData[5:6] != b'\xD0':
        log.error("handshake recv data command error.")
        return ""

    return "ok"

def HandShakeSecond(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可
    if len(paramlist) < 10:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    nRack = int(paramlist[7])
    nSlot = int(paramlist[8])
    Register =  b'\x03\x00\x00\x19\x02\xF0\x80\x32'
    Register += b'\x01\x00\x00\xCC\xC1\x00\x08\x00'
    Register += b'\x00\xF0\x00\x00\x01\x00\x01\x03\xC0'
    #Register += nSlot.to_bytes(1,byteorder = 'little')
    return Register

def HandShakeParaseSecond(paramlist,RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
    if len(paramlist) < 10:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    nRack = int(paramlist[7])
    nSlot = int(paramlist[8])

    if len(RecvData) != 27:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    global bRegister
    bRegister = True

    return "ok"

def ReadAssembly(paramlist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    global bRegister
    if bRegister == False:
        return ""

    nIntDataType = int(paramlist[0])
    nSoftElementAddress = int(paramlist[1])
    nOffsetNum = int(paramlist[2])
    nDataLen = int(paramlist[3])
    

    package = bytearray(b'\x03\x00\x00\x1F') #TPKT（第五层：会话层）

    #COTP（第六层：表示层）
    package += b'\x02' #长度
    package += b'\xF0' #PDU类型（DT Data）
    package += b'\x80' #目标引用


    #S7Communication（第七层：应用层）该层总用占24个字节，并且分两部分

    #Header
    package += b'\x32' #协议ID（Protocol ID）7
    package += b'\x01' #Ack_Data
    package += b'\x00\x00' #预留
    package += b'\x00\x01' #协议数据单元引用
    package += b'\x00\x0E' #参数长度
    package += b'\x00\x00' #数据长度 15 16

    #Parameter
    package += b'\x04' #功能码Read Var
    package += b'\x01' #通信项数
    #通信项1：
    package += b'\x12' #变量指定
    package += b'\x0A' #地址长度
    package += b'\x10' #SyntaxID
    package += b'\x02' #传输数据类型byte
    #通信项Param
    package += nDataLen.to_bytes(2,byteorder = 'big')
    #package += b'\x00\x04' #读取长度,2byte 23 24 
    package += nSoftElementAddress.to_bytes(2,byteorder = 'big')
    #package += b'\x01\x00' #DB号,2byte 25 26
    package += b'\x84' #存储区类型DB存储区 27
    package += (nOffsetNum * 8).to_bytes(3,byteorder = 'big')
    #package += b'\x000000' #开始字节 读取偏移量offset(bit为单位) )

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
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""


    if len(RecvData) < 24:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""


    if RecvData[21:22] !=  b'\xFF':
        log.error("handshake recv data error.")
        return ""

    byDataLen = bytes()
    byDataLen += RecvData[23:24]
    byDataLen += RecvData[24:25]

    nDataLen = int(int.from_bytes(byDataLen,'big') / 8)
    if nDataLen < 1:
        return ""

    if (nDataLen + 25) != len(RecvData):
        return ""


    return RecvData[25 : len(RecvData)]


#偏移是bit数为单位,长度是以字节为单位
def WriteArrayAssembly(paramlist,datalist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    global bRegister
    if bRegister == False:
        return ""

    nIntDataType = int(paramlist[0])
    nSoftElementAddress = int(paramlist[1])
    nOffsetNum = int(paramlist[2])
    nDataLen = int(paramlist[3])
    

    package = bytearray(b'\x03\x00') 

    package += b'\x00\x00' #长度，后续填写
    package += b'\x02\xF0' #PDU类型（DT Data）
    package += b'\x80' #目标引用
    package += b'\x32' #协议ID（Protocol ID）7


    package += b'\x01' #Ack_Data
    package += b'\x00\x00' #预留
    package += b'\x00\x01' #协议数据单元引用 11 12
    package += b'\x00\x0E' #参数长度
    package += b'\x00\x00' #数据长度 15 16  后续填写

    #Parameter
    package += b'\x05' #功能码Read Var
    package += b'\x01' #通信项数
    #通信项1：
    package += b'\x12' #变量指定
    package += b'\x0A' #地址长度
    package += b'\x10' #SyntaxID
    package += b'\x02' #传输数据类型byte 22
    #通信项Param
    #package += nDataLen.to_bytes(2,byteorder = 'big')
    package += b'\x00\x00' #长度,2byte 后续填写 23 24 
    package += nSoftElementAddress.to_bytes(2,byteorder = 'big')
    #package += b'\x01\x00' #DB号,2byte 25 26
    package += b'\x84' #存储区类型DB存储区 27
    package += (nOffsetNum*8).to_bytes(3,byteorder = 'big')
    #package += b'\x000000' #开始字节 读取偏移量offset(bit为单位) )

    package += b'\x00\x04' #写入方式为Byte
    package += b'\x00\x00' #写入byte的个数(bit为单位) 后续填写

    nWriteNum = 0
    for info in datalist:
        if int == type(info):
            if nIntDataType == 1:#int 占16位
                if info > 65535 or info < -32768:
                    package = ""
                    return package
                package += int(info & 0xFFFF).to_bytes(2,byteorder = 'big') 
                nWriteNum += 16
            elif nIntDataType == 2:#int 占32位
                package += int(info& 0xFFFFFFFF).to_bytes(4,byteorder = 'big') 
                nWriteNum += 32
        elif float == type(info):#float数据
            fTempByte = struct.pack('<f',info)
            package += fTempByte[3].to_bytes(length=1,byteorder='big')
            package += fTempByte[2].to_bytes(length=1,byteorder='big')
            package += fTempByte[1].to_bytes(length=1,byteorder='big')
            package += fTempByte[0].to_bytes(length=1,byteorder='big')
            nWriteNum += 32
        elif str == type(info):#string数据
            nLoop = int(len(info))
            for index in range(nLoop):
                package += ord(info[index]).to_bytes(1, byteorder='little')
                nWriteNum += 8

    if int(nWriteNum / 8) > nDataLen:  # 实际的数据长度大于设置的软元件点数
        return  ""

    byLen1 = nWriteNum.to_bytes(2,byteorder = 'big')
    package[33] = byLen1[0]
    package[34] = byLen1[1]

    byLen2 = int(nWriteNum/8).to_bytes(2,byteorder = 'big')
    package[23] = byLen2[0]
    package[24] = byLen2[1]

    byLen3 = int(int(nWriteNum/8) + 4).to_bytes(2,byteorder = 'big')
    package[15] = byLen3[0]
    package[16] = byLen3[1]

    byLen4 = (len(package)).to_bytes(2,byteorder = 'big')
    package[2] = byLen4[0]
    package[3] = byLen4[1]



    return bytes(package)


def WritePrase(paramlist,RecvData):
    #log.debug("recvdata is %s",RecvData)

    if len(RecvData) != 22:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    if RecvData[21:22] !=  b'\xFF' :
        log.error("handshake recv data error.")
        return ""

    return "ok"
