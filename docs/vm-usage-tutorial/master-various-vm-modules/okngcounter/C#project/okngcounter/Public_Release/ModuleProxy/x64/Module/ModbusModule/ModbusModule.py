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
    fmt = logging.Formatter(
        fmt='ModbusModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s',
        datefmt='%Y:%m:%d %H:%M:%S')

    log.setLevel(logging.DEBUG)

    # "OutputDebugString\DebugView"
    ods = DbgViewHandler()
    ods.setLevel(logging.DEBUG)
    ods.setFormatter(fmt)
    log.addHandler(ods)


config_logging()

def byte2float(b):
    return f

def float2byte(f):
    bs = struct.pack("f", f)
    return (bs[3], bs[2], bs[1], bs[0])

def crc16(bytes):
    crc = 0xFFFF
    for pos in bytes:
        crc ^= pos
        for i in range(8):
            if ((crc & 1) != 0):
                crc >>= 1
                crc ^= 0xA001
            else:
                crc >>= 1
    return [((crc & 0xff)) , (crc >> 8)]

def calcLRC(input):
    lrc = 0
    for b in input:
        lrc += b
    lrc = lrc % 256
    lrc = 256 - lrc
    return lrc

def ASCToHex(inputASCII, inputlen):
    #log.error("modbus: ASCToHex begin")
    #log.error("modbus: inputASCII = %s", inputASCII)
    #log.error("modbus: inputlen = %d", inputlen)
    ret = b""

    dataAscHi = 0
    dataAscLo = 0
    dataAsc = 0
    dataHexLen = inputlen / 2
    dataTransNum = 0
    i = 0
    while (i < inputlen):
        log.error("modbus: i = %d", i)
        dataAscHi = ord(inputASCII[i : i + 1])
        dataAscLo = ord(inputASCII[i + 1 : i + 2])
        #log.error("modbus: before ascii high = %d", dataAscHi)
        #log.error("modbus: before ascii low = %d", dataAscLo)
        #高字节解码
        if (dataAscHi >= ord('A')) and (dataAscHi <= ord('F')):
            dataAscHi -= 0x37
        elif (dataAscHi >= ord('a')) and (dataAscHi <= ord('f')):
            dataAscHi -= 0x57
        elif (dataAscHi >= ord('0')) and (dataAscHi <= ord('9')):
            dataAscHi -= 0x30

         # 低字节解码
        if (dataAscLo >= ord('A')) and (dataAscLo <= ord('F')):
            dataAscLo -= 0x37
        elif (dataAscLo >= ord('a')) and (dataAscLo <= ord('f')):
            dataAscLo -= 0x57
        elif (dataAscLo >= ord('0')) and (dataAscLo <= ord('9')):
            dataAscLo -= 0x30

        dataAscHi = dataAscHi << 4 #ASCII码转字节高4位
        dataAscLo = dataAscLo & 0x0F #取ASCII码低4位
        #log.error("modbus: after ascii high = %d", dataAscHi)
        #log.error("modbus: after ascii low = %d", dataAscLo)

        ret += int(dataAscHi | dataAscLo).to_bytes(length=1, byteorder='big', signed=False)
        dataTransNum += 1

        i += 2
    #log.error("modbus: dataTransNum = %d", dataTransNum)
    #log.error("modbus: dataHexLen = %d", dataHexLen)
    if dataTransNum != dataHexLen:
        ret = b""

    #log.error("modbus: ret = %s", ret)
    return ret

def DecodeRecvRTU(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress):
    #log.error("modbus: pdata = %s", pData)
    #log.error("modbus: datalen = %d", dataLen)
    strRep = ""
    # 检测异常码
    #log.error("modbus: excepCode")
    excepCode = 0xff
    excepHead = 0x80
    excepHead = excepHead | chFunctionCode
    if excepHead == pData[1]:
        excepCode = pData[2]
    if 0xff != excepCode:
        strRep = ""
        return strRep
    # 长度判断
    #log.error("modbus: length check")
    dataLenFun = 0
    if 0x03 == chFunctionCode:
        dataLenFun = 3 + (nRegisterNum * 2) + 2
    if 0x04 == chFunctionCode:
        dataLenFun = 3 + (nRegisterNum * 2) + 2
    if 0x06 == chFunctionCode:
        dataLenFun = 8
    if 0x10 == chFunctionCode:
        dataLenFun = 8

    if dataLen != dataLenFun:
        strRep = ""
        return strRep

    # 检测设备号
    #log.error("modbus: chDeviceId check")
    if pData[0] != chDeviceId:
        strRep = ""
        return strRep

    # 检测功能码
    #log.error("modbus: chFunctionCode check")
    if pData[1] != chFunctionCode:
        strRep = ""
        return strRep

    # 检测数据中长度信息
    #log.error("modbus: data length check")
    if ((0x03 == chFunctionCode) or (0x04 == chFunctionCode)):
        if pData[2] != (nRegisterNum * 2):
            strRep = ""
            return strRep

    # 检测校验码
    #log.error("modbus: crc lrc check")
    tempBytes = pData[0:dataLen - 2]
    crc = crc16(tempBytes)
    if crc[0] != pData[-2] or crc[1] != pData[-1]:
        strRep = ""
        return strRep

    # 提取数据
    #log.error("modbus: get data")
    if ((0x03 == chFunctionCode) or (0x04 == chFunctionCode)):
        return pData[3:3+2*nRegisterNum]
        # dataRevTemp = 0
        # for i in range(nRegisterNum):
        #     dataRevTemp = pData[3 + (2 * i)];
        #     dataRevTemp = (dataRevTemp << 8);
        #     dataRevTemp = dataRevTemp | pData[3 + (2 * i) + 1];
        #     if i == 0:
        #         strRep += "0X" + '{:02X}'.format(dataRevTemp)
        #     else:
        #         strRep += "," + "0X" + '{:02X}'.format(dataRevTemp)
    elif 0x10 == chFunctionCode:
        # 检测地址
        dataRevTemp = 0;
        dataRevTemp = pData[2];
        dataRevTemp = (dataRevTemp << 8);
        dataRevTemp = dataRevTemp | pData[3];
        if dataRevTemp != chRegisterAddress:
            strRep = ""
            return strRep
        strRep = "ok"
    return strRep

def DecodeRecvASCII(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress):
    #log.error("modbus: pdata = %s", pData)
    #log.error("modbus: datalen = %d", dataLen)
    strRep = ""

    # 检测报文头尾
    #log.error("modbus: check head and tail")
    if pData[0] != 0x3A or pData[-2] != 0x0D or pData[-1] != 0x0A:
        strRep = ""
        return strRep

    # 将ASCII数据转化成byte数组
    #log.error("modbus: turn ASCII to bytes")
    dataBuf = pData[1:-2]
    #log.error("modbus: dataBuf = %s", dataBuf)
    length = dataLen - 3
    byteBuf = ASCToHex(dataBuf, length)
    #log.error("modbus: byteBuf = %s", byteBuf)

    # 检测异常码
    #log.error("modbus: excepCode")
    excepCode = 0xff
    excepHead = 0x80
    excepHead = excepHead | chFunctionCode
    if excepHead == byteBuf[1]:
        excepCode = byteBuf[2]
    if 0xff != excepCode:
        strRep = ""
        return strRep
    # 长度判断
    #log.error("modbus: length check")
    dataLenFun = 0
    if 0x03 == chFunctionCode:
        dataLenFun = 3 + (nRegisterNum * 2) + 1
    if 0x04 == chFunctionCode:
        dataLenFun = 3 + (nRegisterNum * 2) + 1
    if 0x06 == chFunctionCode:
        dataLenFun = 7
    if 0x10 == chFunctionCode:
        dataLenFun = 7

    if (length / 2) != dataLenFun:
        strRep = ""
        return strRep

    # 检测设备号
    #log.error("modbus: chDeviceId check")
    if byteBuf[0] != chDeviceId:
        strRep = ""
        return strRep

    # 检测功能码
    #log.error("modbus: chFunctionCode check")
    if byteBuf[1] != chFunctionCode:
        strRep = ""
        return strRep

    # 检测数据中长度信息
    #log.error("modbus: data length check")
    if ((0x03 == chFunctionCode) or (0x04 == chFunctionCode)):
        if byteBuf[2] != (nRegisterNum * 2):
            strRep = ""
            return strRep

    # 检测校验码
    #log.error("modbus: crc lrc check")
    tempBytes = byteBuf[0:-1]
    lrc = calcLRC(tempBytes)
    #log.error("modbus: lrc = %d", lrc)
    #log.error("modbus: byteBuf[-1] = %d", byteBuf[-1])
    if lrc != byteBuf[-1]:
        strRep = ""
        return strRep

    # 提取数据
    #log.error("modbus: get data")
    if ((0x03 == chFunctionCode) or (0x04 == chFunctionCode)):
        return byteBuf[3:3+2*nRegisterNum]
        # dataRevTemp = 0
        # for i in range(nRegisterNum):
        #     dataRevTemp = byteBuf[3 + (2 * i)];
        #     dataRevTemp = (dataRevTemp << 8);
        #     dataRevTemp = dataRevTemp | byteBuf[3 + (2 * i) + 1];
        #     if i == 0:
        #         strRep += "0X" + '{:02X}'.format(dataRevTemp)
        #     else:
        #         strRep += "," + "0X" + '{:02X}'.format(dataRevTemp)
    elif 0x10 == chFunctionCode:
        # 检测地址
        dataRevTemp = 0;
        dataRevTemp = byteBuf[2];
        dataRevTemp = (dataRevTemp << 8);
        dataRevTemp = dataRevTemp | byteBuf[3];
        if dataRevTemp != chRegisterAddress:
            strRep = ""
            return strRep
        strRep = "ok"
    return strRep

def CharToShort(byte):
    temp = 0
    temp = byte[0]
    temp = (temp << 8) | byte[1]
    return temp

nCommunicationMode = 0

def HandShake(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可,此处只是做为传递IP数据方便之后的写和读使用
    #log.error("modbud: HandShake %d",len(paramlist))
    if len(paramlist) < 4:
        log.error("modbus: paramlist num is %d",len(paramlist))
        return ""
    global nCommunicationMode
    #log.error("modbud: HandShake %s", paramlist[2])
    nCommunicationMode = int(paramlist[2])
    #log.error("modbud: nCommunicationMode = %d", nCommunicationMode)
    return ""


def HandShakeParase(paramlist, RecvData):  # 解析注册返回的数据，如果成功则返回ok，失败返回空
    return ""

def WriteArrayAssembly(paramlist,pData):#(pData, nSlaveMode, nCommunicationMode, nProtocolType, nValueType, nIntType, nFloatSequence, chDeviceId, chFunctionCode, chRegisterAddress, nRegisterNum):
    log.error("modbus: WriteArrayAssembly start")
    dataLen = len(pData)
    if len(paramlist) < 9:
        log.error("modbus: paramlist num is %d",len(paramlist))
        return b""
    # nFunctionCode = int(paramlist[0])
    chFunctionCode = 0x10
    # if nFunctionCode == 1:
    #     chFunctionCode = 0x03
    # elif nFunctionCode == 2:
    #     chFunctionCode = 0x04
    # elif nFunctionCode == 3:
    #     chFunctionCode = 0x10
    log.error("chFunctionCode = %d", chFunctionCode)
    nSlaveMode        = int(paramlist[1])
    #nCommunicationMode = int(paramlist[2])
    nProtocolType     = int(paramlist[3])
    nIntType          = int(paramlist[4])
    nFloatSequence    = int(paramlist[5])
    chDeviceId        = int(paramlist[6])
    chRegisterAddress = int(paramlist[7])
    nRegisterNum      = int(paramlist[8])

    global nCommunicationMode
    log.error("modbus: nCommunicationMode = %d", nCommunicationMode)

    package = b""
    count = b""
    data = b""
    log.error("modbus: WriteAssembly start")
    if 1 == nSlaveMode: #主机模式
        log.error("modbus: 1 == nSlaveMode")
        if 4 == int(nCommunicationMode): #串口通信
            log.error("modbus: 1 == int(nCommunicationMode)")
            if 1 == int(nProtocolType): #RTU
                log.error("modbus: 1 == int(nProtocolType): #RTU")
                package += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=True)
                package += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=True)
                package +=  int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)

                nCount = 0
                for value in pData:
                    if int == type(value):
                        if 1 == int(nIntType):  # int16
                            if value > 65535 or value < -32768:
                                package = b""
                                return package
                            data += (int(value) & 0xffff).to_bytes(length=2, byteorder='big', signed=False)
                            nCount += 1
                        else:  # int32
                            bs = (int(value) & 0xffffffff).to_bytes(length=4, byteorder='big', signed=False)
                            if 1 == nFloatSequence:
                                data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            elif 2 == nFloatSequence:
                                data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            elif 3 == nFloatSequence:
                                data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            elif 4 == nFloatSequence:
                                data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            nCount += 2
                    elif float == type(value):
                        bs = float2byte(value)
                        if 1 == nFloatSequence:
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 2 == nFloatSequence:
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 3 == nFloatSequence:
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 4 == nFloatSequence:
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                        nCount += 2
                    elif str == type(value):
                        i = 0
                        while i < len(value):
                            data += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                            i += 1
                            if i < len(value):
                                data += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                            else:
                                data += int(0).to_bytes(length=1, byteorder='big', signed=False)
                            i += 1
                            nCount += 1
                        # for index in range(len(value)):
                        #     data += int(ord(value[index])).to_bytes(length=2, byteorder='big', signed=False)
                        #     nCount += 1
                    elif bytes == type(value):
                        i = 0
                        while i < len(value):
                            data += value[i:i+1]
                            i += 1
                            if i < len(value):
                                data += value[i:i+1]
                            else:
                                data += int(0).to_bytes(length=1, byteorder='big', signed=False)
                            i += 1
                            nCount += 1
                log.error("mosbus: package=")
                count += int(nCount).to_bytes(length=2, byteorder='big', signed=False) #寄存器个数
                datalen = int(nCount*2).to_bytes(length=1, byteorder='big', signed=False)  # 字节个数
                package = package + count + datalen + data
                crc = crc16(package)
                package += int(crc[0]).to_bytes(length=1, byteorder='big', signed=False)
                package += int(crc[1]).to_bytes(length=1, byteorder='big', signed=False)
                #log.error("mosbus: package=%s", package)
                if nCount > nRegisterNum:
                    package = b""
                    return package

            elif 2 == nProtocolType: #ASCII
                log.error("modbus: 2 == nProtocolType: #ASCII")
                bytLRC = b""
                nCount = 0
                dataLRC = b""

                package += b":"
                package += ('{:02X}'.format(chDeviceId)).encode()
                package += ('{:02X}'.format(chFunctionCode)).encode()
                package += ('{:04X}'.format(chRegisterAddress)).encode()

                bytLRC += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=True)
                bytLRC += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=True)
                bytLRC += int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)

                nCount = 0
                for value in pData:
                    if int == type(value):
                        if 1 == nIntType:  # int16
                            if value > 65535 or value < -32768:
                                package = b""
                                return package
                            dataLRC += (int(value) & 0xffff).to_bytes(length=2, byteorder='big', signed=False)
                            data += ('{:04X}'.format((int(value) & 0xffff))).encode()
                            nCount += 1
                        else:  # int32
                            bs = (int(value) & 0xffffffff).to_bytes(length=4, byteorder='big', signed=False)
                            if 1 == nFloatSequence:
                                dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(bs[0])).encode()
                                data += ('{:02X}'.format(bs[1])).encode()
                                data += ('{:02X}'.format(bs[2])).encode()
                                data += ('{:02X}'.format(bs[3])).encode()
                            elif 2 == nFloatSequence:
                                dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(bs[1])).encode()
                                data += ('{:02X}'.format(bs[0])).encode()
                                data += ('{:02X}'.format(bs[3])).encode()
                                data += ('{:02X}'.format(bs[2])).encode()
                            elif 3 == nFloatSequence:
                                dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(bs[3])).encode()
                                data += ('{:02X}'.format(bs[2])).encode()
                                data += ('{:02X}'.format(bs[1])).encode()
                                data += ('{:02X}'.format(bs[0])).encode()
                            elif 4 == nFloatSequence:
                                dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                                dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(bs[2])).encode()
                                data += ('{:02X}'.format(bs[3])).encode()
                                data += ('{:02X}'.format(bs[0])).encode()
                                data += ('{:02X}'.format(bs[1])).encode()
                            nCount += 2
                    elif float == type(value):
                        bs = float2byte(value)
                        if 1 == nFloatSequence:
                            dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += ('{:02X}'.format(bs[0])).encode()
                            data += ('{:02X}'.format(bs[1])).encode()
                            data += ('{:02X}'.format(bs[2])).encode()
                            data += ('{:02X}'.format(bs[3])).encode()
                        elif 2 == nFloatSequence:
                            dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += ('{:02X}'.format(bs[1])).encode()
                            data += ('{:02X}'.format(bs[0])).encode()
                            data += ('{:02X}'.format(bs[3])).encode()
                            data += ('{:02X}'.format(bs[2])).encode()
                        elif 3 == nFloatSequence:
                            dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += ('{:02X}'.format(bs[3])).encode()
                            data += ('{:02X}'.format(bs[2])).encode()
                            data += ('{:02X}'.format(bs[1])).encode()
                            data += ('{:02X}'.format(bs[0])).encode()
                        elif 4 == nFloatSequence:
                            dataLRC += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            dataLRC += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += ('{:02X}'.format(bs[2])).encode()
                            data += ('{:02X}'.format(bs[3])).encode()
                            data += ('{:02X}'.format(bs[0])).encode()
                            data += ('{:02X}'.format(bs[1])).encode()
                        nCount += 2
                    elif str == type(value):
                        i = 0
                        while i < len(value):
                            dataLRC += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                            data += ('{:02X}'.format(ord(value[i]))).encode()
                            i += 1
                            if i < len(value):
                                dataLRC += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(ord(value[i]))).encode()
                            else:
                                dataLRC += int(0).to_bytes(length=1, byteorder='big', signed=False)
                                data += ('{:02X}'.format(0)).encode()
                            i += 1
                            nCount += 1
                        # for index in range(len(value)):
                        #     dataLRC += int(ord(value[index])).to_bytes(length=2, byteorder='big', signed=False)
                        #     data += ('{:04X}'.format(ord(value[index]))).encode()
                        #     nCount += 1
                    elif bytes == type(value):
                        #log.error("type == bytes")
                        #log.error("len(value) = %d", len(value))
                        i = 0
                        while  i< len(value):
                            #log.error("bytes index=%d ", i)
                            dataLRC += value[i:i+1]
                            data += ('{:02X}'.format(value[i])).encode()
                            i += 1
                            if i < len(value):
                                #log.error("bytes index=%d ", i)
                                dataLRC += value[i:i+1]
                                data += ('{:02X}'.format(value[i])).encode()
                            else:
                                #log.error("bytes index=%d ", i)
                                dataLRC += value[i:i+1]
                                data += ('{:02X}'.format(0)).encode()
                            i += 1
                            nCount += 1
                countLRC = int(nCount).to_bytes(length=2, byteorder='big', signed=False)  # 寄存器个数
                datalenLRC = int(nCount * 2).to_bytes(length=1, byteorder='big', signed=False)  # 字节个数
                bytLRC = bytLRC + countLRC + datalenLRC + dataLRC
                lrc = '{:02X}'.format(calcLRC(bytLRC))

                count += ('{:04X}'.format(nCount)).encode()
                datalen = ('{:02X}'.format(nCount*2)).encode()
                package = package + count + datalen + data + lrc.encode() + b"\r\n"

                if nCount > nRegisterNum:
                    package = b""
                    return package

        elif 1 == nCommunicationMode or 2 == nCommunicationMode: #tcp通信
            log.error("modbus: tcp")
            package += int(0).to_bytes(length=2, byteorder='big', signed=True)
            package += int(0).to_bytes(length=2, byteorder='big', signed=True)
            log.error("modbus: %s", package)

            nCount = 0
            for value in pData:
                if int == type(value):
                    #log.error("modbus: int")
                    if 1 == nIntType:  # int16
                        if value > 65535 or value < -32768:
                            package = b""
                            return package
                        #log.error("modbus: value=%d", int(value))
                        #log.error("modbus: new value=%d", (int(value) & 0xffff))
                        data += (int(value) & 0xffff).to_bytes(length=2, byteorder='big', signed=False)
                        nCount += 1
                    else:  # int32
                        #log.error("modbus: value=%d", int(value))
                        #log.error("modbus: new value=%d", (int(value) & 0xffffffff))
                        bs = (int(value) & 0xffffffff).to_bytes(length=4, byteorder='big', signed=False)
                        if 1 == nFloatSequence:
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 2 == nFloatSequence:
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 3 == nFloatSequence:
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                        elif 4 == nFloatSequence:
                            data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                            data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                        nCount += 2
                elif float == type(value):
                    #log.error("modbus: float")
                    bs = float2byte(value)
                    if 1 == nFloatSequence:
                        data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                    elif 2 == nFloatSequence:
                        data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                    elif 3 == nFloatSequence:
                        data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                    elif 4 == nFloatSequence:
                        data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                        data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                    nCount += 2
                elif str == type(value):
                    #log.error("modbus: string = %s",value)
                    i = 0
                    while i < len(value):
                        data += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                        i += 1
                        if i < len(value):
                            data += int(ord(value[i])).to_bytes(length=1, byteorder='big', signed=False)
                        else:
                            data += int(0).to_bytes(length=1, byteorder='big', signed=False)
                        i += 1
                        nCount += 1

                    # for index in range(len(value)):
                    #     data += int(ord(value[index])).to_bytes(length=2, byteorder='big', signed=False)
                    #     nCount += 1
                elif bytes == type(value):
                    #log.error("modbus: string = %s", value)
                    i = 0
                    while i < len(value):
                        data += value[i:i+1]
                        i += 1
                        if i < len(value):
                            data += value[i:i+1]
                        else:
                            data += int(0).to_bytes(length=1, byteorder='big', signed=False)
                        i += 1
                        nCount += 1

            package += int(7+nCount*2).to_bytes(length=2, byteorder='big', signed=False) #datalen单元标识符之后的报文长度
            package += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=False) #设备ID
            package += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=False)  # 功能码
            package += int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)  # 起始地址
            count += int(nCount).to_bytes(length=2, byteorder='big', signed=False)  # 寄存器个数
            count += int(nCount * 2).to_bytes(length=1, byteorder='big', signed=False)  # 字节个数
            package = package + count + data
            if nCount > nRegisterNum:
                package = b""
                return package
            log.error("modbus: package=%s", package)

    #struct.pack('B' * len(package), *package)
    log.error("modbus: package=%s", package)
    return package

def RecvParse(pData, dataLen, nSlaveMode, nCommunicationMode, nProtocolType, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress):
    strRep = ""
    #pData = pData.encode('utf-8')
    #log.error("modbus: ")
    if 1 == nSlaveMode: #主机
        if 1 == nCommunicationMode: #串口通信
            if 1 == nProtocolType: #RTU
                strRep = DecodeRecvRTU(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

            elif 2 == nProtocolType: #ASCII
                strRep = DecodeRecvASCII(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

        elif 2 == nCommunicationMode: #TCP通信
            #log.error("modbus: TCP")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                length = 3 + nRegisterNum * 2
            else:
                length = 6
            #log.error("modbus: length check")

            tempBytes1 = pData[0:2]
            #log.error("modbus: tempBytes1 = [%s]", tempBytes1)
            if 0x0000 != CharToShort(tempBytes1):
                strRep = ""
                return strRep
            tempBytes2 = pData[2:4]
            #log.error("modbus: tempBytes2 = [%s]", tempBytes2)
            if 0x0000 != CharToShort(tempBytes2):
                strRep = ""
                return strRep

            #获取PDU数据
            dataBytes = pData[7:]
            #log.error("modbus: dataBytes = [%s]", dataBytes)

            #异常码校验
            #log.error("modbus: excepcode check")
            excepCode = 0xff
            excepHead = 0x80
            excepHead = excepHead | chFunctionCode
            if excepHead == pData[1]:
                excepCode = pData[2]
            if 0xff != excepCode:
                strRep = ""
                return strRep

            #数据长度校验
            #log.error("modbus: length check")
            if length != len(dataBytes) + 1:
                strRep = ""
                return strRep

            #功能码校验
            #log.error("modbus: funccode check")
            if chFunctionCode != dataBytes[0]:
                strRep = ""
                return strRep

            #提取数据
            #log.error("modbus: get pdu data")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                if dataBytes[1] != nRegisterNum *2:
                    strRep = ""
                    return strRep
                dataRevTemp = 0
                for i in range(nRegisterNum):
                    dataRevTemp = dataBytes[2 + (2 * i)];
                    dataRevTemp = (dataRevTemp << 8);
                    dataRevTemp = dataRevTemp | dataBytes[2 + (2 * i) + 1];
                    if i == 0:
                        strRep += str(dataRevTemp)
                    else:
                        strRep += "," + str(dataRevTemp)
            else:
                strRep = "OK"

    return strRep

def ReadAssembly(paramlist):#(nSlaveMode, nCommunicationMode, nProtocolType, chDeviceId, chFunctionCode, chRegisterAddress, nRegisterNum):
    #log.error("modbus: ReadAssembly start")
    if len(paramlist) < 9:
        log.error("modbus: paramlist num is %d", len(paramlist))
        return b""
    # nFunctionCode = int(paramlist[0])
    chFunctionCode = 0x03
    # if nFunctionCode == 1:
    #     chFunctionCode = 0x03
    # elif nFunctionCode == 2:
    #     chFunctionCode = 0x04
    # elif nFunctionCode == 3:
    #     chFunctionCode = 0x10
    log.error("chFunctionCode = %d", chFunctionCode)
    nSlaveMode = int(paramlist[1])
    # nCommunicationMode = int(paramlist[2])
    nProtocolType = int(paramlist[3])
    nIntType = int(paramlist[4])
    nFloatSequence = int(paramlist[5])
    chDeviceId = int(paramlist[6])
    chRegisterAddress = int(paramlist[7])
    nRegisterNum = int(paramlist[8])

    global nCommunicationMode

    package = b""
    #log.error("ReadAssembly start")
    if 1 == nSlaveMode: #主机
        if 4 == nCommunicationMode: #串口通信
            if 1 == nProtocolType: #RTU
                if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                    package += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=True)
                    package += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=True)
                    package += int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)
                    package += int(nRegisterNum).to_bytes(length=2, byteorder='big', signed=False)
                    crc = crc16(package)
                    package += int(crc[0]).to_bytes(length=1, byteorder='big', signed=False)
                    package += int(crc[1]).to_bytes(length=1, byteorder='big', signed=False)

            elif 2 == nProtocolType: #ASCII
                if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                    packageLRC = b""
                    packageLRC += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=True)
                    packageLRC += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=True)
                    packageLRC += int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)
                    packageLRC += int(nRegisterNum).to_bytes(length=2, byteorder='big', signed=False)
                    lrc = '{:02X}'.format(calcLRC(packageLRC))

                    package += b":"
                    package += ('{:02X}'.format(chDeviceId)).encode()
                    package += ('{:02X}'.format(chFunctionCode)).encode()
                    package += ('{:04X}'.format(chRegisterAddress)).encode()
                    package += ('{:04X}'.format(nRegisterNum)).encode()
                    log.error("modbus: nRegisterNum = %d", nRegisterNum)
                    package += lrc.encode()
                    package += b"\r\n"
                    log.error("modbus: package = %s", package)

        elif 1 == nCommunicationMode or 2 == nCommunicationMode: #TCP通信
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                package += int(0).to_bytes(length=2, byteorder='big', signed=True)
                package += int(0).to_bytes(length=2, byteorder='big', signed=True)
                package += int(6).to_bytes(length=2, byteorder='big', signed=True) #长度固定为6
                package += int(chDeviceId).to_bytes(length=1, byteorder='big', signed=False)
                package += int(chFunctionCode).to_bytes(length=1, byteorder='big', signed=False)
                package += int(chRegisterAddress).to_bytes(length=2, byteorder='big', signed=False)
                package += int(nRegisterNum).to_bytes(length=2, byteorder='big', signed=False)

    return package

def WritePrase(paramlist, pData):
    log.error("modbus: ReadAssembly start %s", pData)
    dataLen = len(pData)
    if len(paramlist) < 9:
        #log.error("modbus: paramlist num is %d", len(paramlist))
        return b""
    # nFunctionCode = int(paramlist[0])
    chFunctionCode = 0x10
    # if nFunctionCode == 1:
    #     chFunctionCode = 0x03
    # elif nFunctionCode == 2:
    #     chFunctionCode = 0x04
    # elif nFunctionCode == 3:
    #     chFunctionCode = 0x10
    #log.error("chFunctionCode = %d", chFunctionCode)
    nSlaveMode = int(paramlist[1])
    # nCommunicationMode = int(paramlist[2])
    nProtocolType = int(paramlist[3])
    nIntType = int(paramlist[4])
    nFloatSequence = int(paramlist[5])
    chDeviceId = int(paramlist[6])
    chRegisterAddress = int(paramlist[7])
    nRegisterNum = int(paramlist[8])

    global nCommunicationMode

    strRep = ""
    # pData = pData.encode('utf-8')
    #log.error("modbus: ")
    if 1 == nSlaveMode:  # 主机
        if 4 == nCommunicationMode:  # 串口通信
            if 1 == nProtocolType:  # RTU
                strRep = DecodeRecvRTU(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

            elif 2 == nProtocolType:  # ASCII
                strRep = DecodeRecvASCII(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

        elif 1 == nCommunicationMode or 2 == nCommunicationMode:  # TCP通信
            #log.error("modbus: TCP")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                length = 3 + nRegisterNum * 2
            else:
                length = 6
            #log.error("modbus: length check")

            tempBytes1 = pData[0:2]
            #log.error("modbus: tempBytes1 = [%s]", tempBytes1)
            if 0x0000 != CharToShort(tempBytes1):
                strRep = ""
                return strRep
            tempBytes2 = pData[2:4]
            #log.error("modbus: tempBytes2 = [%s]", tempBytes2)
            if 0x0000 != CharToShort(tempBytes2):
                strRep = ""
                return strRep

            # 获取PDU数据
            dataBytes = pData[7:]
            #log.error("modbus: dataBytes = [%s]", dataBytes)

            # 异常码校验
            #log.error("modbus: excepcode check")
            excepCode = 0xff
            excepHead = 0x80
            excepHead = excepHead | chFunctionCode
            if excepHead == pData[1]:
                excepCode = pData[2]
            if 0xff != excepCode:
                strRep = ""
                return strRep

            # 数据长度校验
            #log.error("modbus: length check")
            if length != len(dataBytes) + 1:
                strRep = ""
                return strRep

            # 功能码校验
            #log.error("modbus: funccode check")
            if chFunctionCode != dataBytes[0]:
                strRep = ""
                return strRep

            # 提取数据
            #log.error("modbus: get pdu data")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                if dataBytes[1] != nRegisterNum * 2:
                    strRep = ""
                    return strRep
                dataRevTemp = 0
                for i in range(nRegisterNum):
                    dataRevTemp = dataBytes[2 + (2 * i)];
                    dataRevTemp = (dataRevTemp << 8);
                    dataRevTemp = dataRevTemp | dataBytes[2 + (2 * i) + 1];
                    if i == 0:
                        strRep += str(dataRevTemp)
                    else:
                        strRep += "," + str(dataRevTemp)
            else:
                strRep = "ok"

    return strRep

def ReadPrase(paramlist, pData):
    #log.error("modbus: ReadAssembly start")
    dataLen = len(pData)
    if len(paramlist) < 9:
        log.error("modbus: paramlist num is %d", len(paramlist))
        return b""
    # nFunctionCode = int(paramlist[0])
    chFunctionCode = 0x03
    # if nFunctionCode == 1:
    #     chFunctionCode = 0x03
    # elif nFunctionCode == 2:
    #     chFunctionCode = 0x04
    # elif nFunctionCode == 3:
    #     chFunctionCode = 0x10
    #log.error("chFunctionCode = %d", chFunctionCode)
    nSlaveMode = int(paramlist[1])
    # nCommunicationMode = int(paramlist[2])
    nProtocolType = int(paramlist[3])
    nIntType = int(paramlist[4])
    nFloatSequence = int(paramlist[5])
    chDeviceId = int(paramlist[6])
    chRegisterAddress = int(paramlist[7])
    nRegisterNum = int(paramlist[8])

    global nCommunicationMode

    strRep = b""
    # pData = pData.encode('utf-8')
    #log.error("modbus: ")
    if 1 == nSlaveMode:  # 主机
        if 4 == nCommunicationMode:  # 串口通信
            if 1 == nProtocolType:  # RTU
                return DecodeRecvRTU(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

            elif 2 == nProtocolType:  # ASCII
                return DecodeRecvASCII(pData, dataLen, chDeviceId, chFunctionCode, nRegisterNum, chRegisterAddress)

        elif 1 == nCommunicationMode or 2 == nCommunicationMode:  # TCP通信
            #log.error("modbus: TCP")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                length = 3 + nRegisterNum * 2
            else:
                length = 6
            #log.error("modbus: length check")

            tempBytes1 = pData[0:2]
            #log.error("modbus: tempBytes1 = [%s]", tempBytes1)
            if 0x0000 != CharToShort(tempBytes1):
                strRep = ""
                return strRep
            tempBytes2 = pData[2:4]
            #log.error("modbus: tempBytes2 = [%s]", tempBytes2)
            if 0x0000 != CharToShort(tempBytes2):
                strRep = ""
                return strRep

            # 获取PDU数据
            dataBytes = pData[7:]
            #log.error("modbus: dataBytes = [%s]", dataBytes)

            # 异常码校验
            #log.error("modbus: excepcode check")
            excepCode = 0xff
            excepHead = 0x80
            excepHead = excepHead | chFunctionCode
            if excepHead == pData[1]:
                excepCode = pData[2]
            if 0xff != excepCode:
                strRep = ""
                return strRep

            # 数据长度校验
            #log.error("modbus: length check")
            if length != len(dataBytes) + 1:
                strRep = ""
                return strRep

            # 功能码校验
            #log.error("modbus: funccode check")
            if chFunctionCode != dataBytes[0]:
                strRep = ""
                return strRep

            # 提取数据
            #log.error("modbus: get pdu data")
            if 0x03 == chFunctionCode or 0x04 == chFunctionCode:
                return dataBytes[2:2+2*nRegisterNum]
                # if dataBytes[1] != nRegisterNum * 2:
                #     strRep = ""
                #     return strRep
                # dataRevTemp = 0
                # for i in range(nRegisterNum):
                #     dataRevTemp = dataBytes[2 + (2 * i)];
                #     dataRevTemp = (dataRevTemp << 8);
                #     dataRevTemp = dataRevTemp | dataBytes[2 + (2 * i) + 1];
                #     if i == 0:
                #         strRep += str(dataRevTemp)
                #     else:
                #         strRep += "," + str(dataRevTemp)
            else:
                strRep = "ok"

    return strRep
