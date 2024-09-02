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
     fmt = logging.Formatter(fmt='OmronCIPModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
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
    Register = b'\x65\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00'
    return Register

def HandShakeParase(paramlist,RecvData):#解析注册返回的数据，如果成功则返回ok，失败返回空
    if len(RecvData) != 28:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    if RecvData[0:1] != b'\x65':
        log.error("handshake recv data command error.")
        return ""

    if RecvData[8:9] != b'\x00' or RecvData[9:10] != b'\x00' or RecvData[10:11] != b'\x00' or RecvData[11:12] != b'\x00':
        log.error("handshake recv data error.")
        return ""

    global SessionHandle
    SessionHandle = b''

    loginfo = ""
    for index in range(0,4):
        SessionHandle += RecvData[4 + index:5 + index]
        #loginfo += str(RecvData[4 + index])
        #loginfo += ' '

    #log.debug("session value = [%s]",loginfo)
    
    return "ok"

def ReadAssembly(paramlist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nSlot = int(paramlist[0])
    nIntDataType = int(paramlist[1])
    strTagName = paramlist[2]
    nDataLen = int(paramlist[3])

    #######################head 24 字节
    global SessionHandle
    if len(SessionHandle) != 4:
        log.error("the handshake not success")
        return ""


    package = bytearray(b'\x6F\x00\x00\x00')
    package += SessionHandle#session handle 会话句柄

    loginfo = ""
    for index in range(len(package)):
        loginfo += '{:02X}'.format(package[index])
        loginfo += ' '

    package += b'\x00\x00\x00\x00' #status 会话状态
    package += b'\x00\x00\x00\x00\x00\x00\x00\x00' #sender context 发送方固定描述
    package += b'\x00\x00\x00\x00' #options

     #######################head end

     ####################### command data start
    package += b'\x00\x00\x00\x00' #接口句柄，默认0是CIP
    package += b'\x01\x00' #超时 0~65535
    package += b'\x02\x00' #项目的数量，最小2
    package += b'\x00\x00' #地址项目,空地址项
    package += b'\x00\x00' #地址项目,空地址项长度

    package += b'\xB2\x00' #未连接数据项
    package += b'\x00\x00' #数据长度,指后边的数据长度（字节）,先填充，最后重新整理

    package += b'\x52' #请求服务代码
    package += b'\x02' #请求路径长度
    package += b'\x20\x06\x24\x01' #请求路径默认
    package += b'\x0A\xF0' #默认超时,245760ms

    package += b'\x00\x00' #长度 从服务标识开始  到  写入的值结束

    package += b'\x4C' #服务标识

    nNameLen = int((int)(len(strTagName) / 2) + (int)(len(strTagName) % 2)) + 1
    package += nNameLen.to_bytes(1,byteorder = 'little') #CIP长度多少字


    package += b'\x91' #固定
    package += int(len(strTagName)).to_bytes(1,byteorder = 'little') #标签长度

    #package += str.encode(strTagName) #bytes(strTagName, encoding = "utf8") #标签名  TAG1
    for index in range(len(strTagName)):
        package += ord(strTagName[index]).to_bytes(1,byteorder = 'little')

    if (len(strTagName) % 2):
        package += b'\x00'

    package += b'\x01\x00' #读取长度
    package += b'\x01\x00\x01' #槽号
    package += nSlot.to_bytes(1,byteorder = 'little') #槽号

    byLen1 = (len(package) - 24).to_bytes(2,byteorder = 'little')
    package[2] = byLen1[0]
    package[3] = byLen1[1]

    byLen2 = (len(package) - 40).to_bytes(2,byteorder = 'little')
    package[38] = byLen2[0]
    package[39] = byLen2[1]

    byLen3 = (len(package) - 54).to_bytes(2,byteorder = 'little')
    package[48] = byLen3[0]
    package[49] = byLen3[1]
     ####################### command data end

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
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    if RecvData[0:1] != b'\x6F':
        log.error("handshake recv data command error.")
        return ""

    
    if len(RecvData) < 24:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    byDataLen = bytes()
    byDataLen += RecvData[2:3]
    byDataLen += RecvData[3:4]

    nDataLen = int.from_bytes(byDataLen,'little')

    if len(RecvData) != (nDataLen + 24):
        log.error("handshake recv error.len = %d,realdatalen = %d",len(RecvData),nDataLen)

    if RecvData[42:43] !=  b'\x00' or RecvData[43:44] !=  b'\x00':
        log.error("handshake recv data error.")
        return ""

    #nReturnLen = nDataLen + 24 -46

    #package = bytes()
    #for index in range(nReturnLen):
    #    package += RecvData[index + 46]

    #loginfo = ""
    #for index in range(len(package)):
    #    loginfo += '{:02X}'.format(package[index])
    #    loginfo += ' '

    #log.debug("readpackage %s",loginfo)
    return RecvData[46 : nDataLen + 24]





def WriteArrayAssembly(paramlist,datalist):
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    nSlot = int(paramlist[0])
    nIntDataType = int(paramlist[1])
    strTagName = paramlist[2]

    #######################head 24 字节
    global SessionHandle
    if len(SessionHandle) != 4:
        log.error("the handshake not success")
        return ""

    package = bytearray(b'\x6F\x00\x00\x00')
    package += SessionHandle#session handle 会话句柄

    #loginfo = ""
    #for index in range(len(package)):
    #    loginfo += '{:02X}'.format(package[index])
    #    loginfo += ' '

    package += b'\x00\x00\x00\x00' #status 会话状态
    package += b'\x00\x00\x00\x00\x00\x00\x00\x00' #sender context 发送方固定描述
    package += b'\x00\x00\x00\x00' #options

     #######################head end

     ####################### command data start
    package += b'\x00\x00\x00\x00' #接口句柄，默认0是CIP
    package += b'\x01\x00' #超时 0~65535
    package += b'\x02\x00' #项目的数量，最小2
    package += b'\x00\x00' #地址项目,空地址项
    package += b'\x00\x00' #地址项目,空地址项长度

    package += b'\xB2\x00' #未连接数据项
    package += b'\x00\x00' #数据长度,指后边的数据长度（字节）,先填充，最后重新整理

    package += b'\x52' #请求服务代码
    package += b'\x02' #请求路径长度
    package += b'\x20\x06\x24\x01' #请求路径默认
    package += b'\x0A\xF0' #默认超时,245760ms

    package += b'\x00\x00' #长度 从服务标识开始  到  写入的值结束

    package += b'\x4D' #服务标识
    nNameLen = int((int)(len(strTagName) / 2) + (int)(len(strTagName) % 2)) + 1
    package += nNameLen.to_bytes(1,byteorder = 'little') #CIP长度多少字

    package += b'\x91' #固定
    package += int(len(strTagName)).to_bytes(1,byteorder = 'little') #标签长度

    #package += str.encode(strTagName) #bytes(strTagName, encoding = "utf8") #标签名  TAG1
    for index in range(len(strTagName)):
        package += ord(strTagName[index]).to_bytes(1,byteorder = 'little')

    if (int)(len(strTagName) % 2) == 1:
        package += b'\x00'

    #########数据类型,0x00C3(195) 为整型，0x00CA(202)为实型,0x00C1(193)为布尔型,long 型为0x00C4，BYTE为0x00C2

    #此协议只支持单类型数据
    for info in datalist:
        if int == type(info):
            if nIntDataType == 1:#int 占16位
                package += b'\xC7'
            elif nIntDataType == 2:#int 占32位
                package += b'\xC3'
            elif nIntDataType == 3:#int 占32位
                package += b'\xC4'
            elif nIntDataType == 4:#int 占32位
                package += b'\xC8'
        elif float == type(info):#float数据
                package += b'\xCA'
        elif str == type(info):#string数据
                package += b'\xD0'

        break

    package += b'\x00\x01\x00' 
    ############# 数据填充
    #写入数量

    #package += (int(nDataLength/2)).to_bytes(2,byteorder = 'little')
    #只能有一个数据类型
    nInt = 0
    nFloat = 0
    nStr = 0
    for info in datalist:
        if int == type(info):
            nInt = 1
            if nIntDataType == 1 or nIntDataType == 2:#int 占16位
                package += int(info).to_bytes(2,byteorder = 'little',signed=True)
            elif nIntDataType == 3 or nIntDataType == 4:#int 占32位
                package += int(info).to_bytes(4,byteorder = 'little',signed=True)
        elif float == type(info):#float数据
            nFloat = 1
            package += struct.pack('<f',info)
        elif str == type(info):#string数据
            nStr = 1
            package += (len(info)+len(info) % 2).to_bytes(2,byteorder = 'little')
            for index in range(len(info)):
                package += ord(info[index]).to_bytes(1,byteorder = 'little')
            if(len(info) % 2 == 1):
                package += b'\x00' 

    if (nInt + nFloat + nStr) != 1:
        log.error("omron only can send one typ")
        return ""



    package += b'\x01\x00\x01' #槽号
    package += nSlot.to_bytes(1,byteorder = 'little') #槽号
    byLen1 = (len(package) - 24).to_bytes(2,byteorder = 'little')
    package[2] = byLen1[0]
    package[3] = byLen1[1]

    byLen2 = (len(package) - 40).to_bytes(2,byteorder = 'little')
    package[38] = byLen2[0]
    package[39] = byLen2[1]

    byLen3 = (len(package) - 54).to_bytes(2,byteorder = 'little')
    package[48] = byLen3[0]
    package[49] = byLen3[1]
     ####################### command data end
    #loginfo = ""
    #for index in range(len(package)):
        #loginfo += '{:02X}'.format(package[index])
        #loginfo += ' '

    #log.debug("readpackage %s",loginfo)
    return bytes(package)


def WritePrase(paramlist,RecvData):
    #log.debug("recvdata is %s",RecvData)
    if len(paramlist) < 5:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    if RecvData[0:1] != b'\x6F':
        log.error("handshake recv data command error.")
        return ""

    
    if len(RecvData) != 44:
        log.error("handshake recv error.len = %d",len(RecvData))
        return ""

    if RecvData[42:43] !=  b'\x00' or RecvData[43:44] !=  b'\x00':
        log.error("handshake recv data error.")
        return ""
    return "ok"
