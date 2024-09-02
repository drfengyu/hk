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

def float2byte(f):
    bs = struct.pack("f", f)
    return (bs[3], bs[2], bs[1], bs[0])

def HandShake(paramlist):#如果需要註冊，則填充註冊请求命令,如果不需要，直接返回空即可,此处只是做为传递IP数据方便之后的写和读使用
    return ""


def HandShakeParase(paramlist, RecvData):  # 解析注册返回的数据，如果成功则返回ok，失败返回空
    return ""

def WriteArrayAssembly(paramlist,pData):
    log.error("pclink: WriteArrayAssembly start")
    dataLen = len(pData)
    if len(paramlist) < 6:
        log.error("pclink: paramlist num is %d",len(paramlist))
        return b""

    nCpuNo            = int(paramlist[0])
    nProtocolType     = int(paramlist[1])
    nIntType          = int(paramlist[2])
    nSoftElementType  = int(paramlist[3])
    #nFloatSequence    = int(paramlist[4])
    nRegisterAddress  = int(paramlist[4])
    nRegisterNum      = int(paramlist[5])

    package = b""
    count = b""
    data = b""
    log.error("pclink: WriteAssembly start")
    if 1 == int(nProtocolType): #RTU
        log.error("pclink: 1 == int(nProtocolType): #RTU")
        package += int(0x12).to_bytes(length=1, byteorder='big', signed=False)
        package += int(nCpuNo).to_bytes(length=1, byteorder='big', signed=False)

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
                    data += int(bs[2]).to_bytes(length=1, byteorder='big', signed=False)
                    data += int(bs[3]).to_bytes(length=1, byteorder='big', signed=False)
                    data += int(bs[0]).to_bytes(length=1, byteorder='big', signed=False)
                    data += int(bs[1]).to_bytes(length=1, byteorder='big', signed=False)
                    nCount += 2
            elif float == type(value):
                bs = float2byte(value)
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
                    data += value[i:i + 1]
                    i += 1
                    if i < len(value):
                        data += value[i:i + 1]
                    else:
                        data += int(0).to_bytes(length=1, byteorder='big', signed=False)
                    i += 1
                    nCount += 1
        log.error("pclink: data= %s", data)
        count += int(8+nCount*2).to_bytes(length=2, byteorder='big', signed=False)
        package += count
        package += int(4).to_bytes(length=2, byteorder='big', signed=False)
        package += int(nRegisterAddress).to_bytes(length=4, byteorder='big', signed=False)
        package += int(nCount).to_bytes(length=2, byteorder='big', signed=False)
        package += data
        log.error("pclink: package= %s", package)
        if nRegisterNum < nCount:
            return ""

    elif 2 == int(nProtocolType): #ascii
        log.error("pclink: 2 == int(nProtocolType): #ascii")
        package += ('{:02}'.format(nCpuNo)).encode()
        package += b"WWR"
        if nSoftElementType == 1:
            package += b"D"
        elif nSoftElementType == 2:
            package += b"M"
        elif nSoftElementType == 3:
            package += b"X"
        elif nSoftElementType == 4:
            package += b"Y"
        package += ('{:05}'.format(nRegisterAddress)).encode()
        package += b","
        nCount = 0
        for value in pData:
            if int == type(value):
                if 1 == nIntType:  # int16
                    if value > 65535 or value < -32768:
                        package = b""
                        return package
                    data += ('{:04X}'.format((int(value) & 0xffff))).encode()
                    nCount += 1
                else: # int32
                    bs = (int(value) & 0xffffffff).to_bytes(length=4, byteorder='big', signed=False)
                    data += ('{:02X}'.format(bs[2])).encode()
                    data += ('{:02X}'.format(bs[3])).encode()
                    data += ('{:02X}'.format(bs[0])).encode()
                    data += ('{:02X}'.format(bs[1])).encode()
                    nCount += 2
            elif float == type(value):
                bs = float2byte(value)
                data += ('{:02X}'.format(bs[2])).encode()
                data += ('{:02X}'.format(bs[3])).encode()
                data += ('{:02X}'.format(bs[0])).encode()
                data += ('{:02X}'.format(bs[1])).encode()
                nCount += 2
            elif str == type(value):
                i = 0
                while i < len(value):
                    data += ('{:02X}'.format(ord(value[i]))).encode()
                    i += 1
                    if i < len(value):
                        data += ('{:02X}'.format(ord(value[i]))).encode()
                    else:
                        data += ('{:02X}'.format(0)).encode()
                    i += 1
                    nCount += 1
            elif bytes == type(value):
                i = 0
                while i < len(value):
                    # log.error("bytes index=%d ", i)
                    data += ('{:02X}'.format(value[i])).encode()
                    i += 1
                    if i < len(value):
                        # log.error("bytes index=%d ", i)
                        data += ('{:02X}'.format(value[i])).encode()
                    else:
                        # log.error("bytes index=%d ", i)
                        data += ('{:02X}'.format(0)).encode()
                    i += 1
                    nCount += 1
        count += ('{:02}'.format(nCount)).encode()
        package += count
        package += b","
        package += data
        package += b"\r\n"
        if nRegisterNum < nCount:
            return ""

        # if nCount > nRegisterNum:
        #     package = b""
        #     return package

    #struct.pack('B' * len(package), *package)
    log.error("pclink: package=%s", package)
    return package



def ReadAssembly(paramlist):#(nSlaveMode, nCommunicationMode, nProtocolType, chDeviceId, chFunctionCode, chRegisterAddress, nRegisterNum):
    log.error("pclink: WriteArrayAssembly start")

    if len(paramlist) < 6:
        log.error("pclink: paramlist num is %d", len(paramlist))
        return b""

    nCpuNo = int(paramlist[0])
    nProtocolType = int(paramlist[1])
    nIntType = int(paramlist[2])
    nSoftElementType = int(paramlist[3])
    # nFloatSequence    = int(paramlist[4])
    nRegisterAddress = int(paramlist[4])
    nRegisterNum = int(paramlist[5])

    package = b""
    count = b""
    data = b""
    log.error("pclink: WriteAssembly start")
    if 1 == int(nProtocolType):  # RTU
        log.error("pclink: 1 == int(nProtocolType): #RTU")
        package += int(0x11).to_bytes(length=1, byteorder='big', signed=False)
        package += int(nCpuNo).to_bytes(length=1, byteorder='big', signed=False)
        package += int(8).to_bytes(length=2, byteorder='big', signed=False)
        package += int(4).to_bytes(length=2, byteorder='big', signed=False)
        package += int(nRegisterAddress).to_bytes(length=4, byteorder='big', signed=False)
        package += int(nRegisterNum).to_bytes(length=2, byteorder='big', signed=False)
        log.error("pclink: package = %s", package)

    elif 2 == int(nProtocolType):  # ascii
        log.error("pclink: 2 == int(nProtocolType): #ascii")
        package += ('{:02}'.format(nCpuNo)).encode()
        package += b"WRD"
        if nSoftElementType == 1:
            package += b"D"
        elif nSoftElementType == 2:
            package += b"M"
        elif nSoftElementType == 3:
            package += b"X"
        elif nSoftElementType == 4:
            package += b"Y"
        package += ('{:05}'.format(nRegisterAddress)).encode()
        package += b","
        package += ('{:02}'.format(nRegisterNum)).encode()
        package += b"\r\n"

    # struct.pack('B' * len(package), *package)
    log.error("pclink: package=%s", package)
    return package

def WritePrase(paramlist, pData):
    log.error("pclink: WritePrase start %s", pData)
    dataLen = len(pData)
    log.error("pclink: dataLen = %d", dataLen)
    if len(paramlist) < 6:
        log.error("pclink: paramlist num is %d", len(paramlist))
        return ""
    nCpuNo = int(paramlist[0])
    nProtocolType = int(paramlist[1])
    nIntType = int(paramlist[2])
    nSoftElementType = int(paramlist[3])
    # nFloatSequence    = int(paramlist[4])
    nRegisterAddress = int(paramlist[4])
    nRegisterNum = int(paramlist[5])

    if 1 == int(nProtocolType):  # RTU
        log.error("pclink: 1 == int(nProtocolType): #RTU")
        if pData[0] != 0x92:
            return ""
        if pData[1] != 0x00:
            return ""
        if pData[2] != 0x00 and pData[3] != 0x00:
            return ""
        return "ok"

    elif 2 == int(nProtocolType):  # ascii
        log.error("pclink: 2 == int(nProtocolType): #ascii")
        cpuvalue = int(pData[1])
        ovalue = int(pData[2])
        kvalue = int(pData[3])
        if cpuvalue != (nCpuNo+48):
            return ""
        if ovalue != 79:
            return ""
        if kvalue != 75:
            return ""
    return "ok"

def ReadPrase(paramlist, pData):
    log.error("pclink: ReadPrase start %s", pData)
    dataLen = len(pData)
    log.error("pclink: dataLen = %d", dataLen)
    if len(paramlist) < 6:
        log.error("pclink: paramlist num is %d", len(paramlist))
        return ""
    nCpuNo = int(paramlist[0])
    nProtocolType = int(paramlist[1])
    nIntType = int(paramlist[2])
    nSoftElementType = int(paramlist[3])
    # nFloatSequence    = int(paramlist[4])
    nRegisterAddress = int(paramlist[4])
    nRegisterNum = int(paramlist[5])

    if 1 == int(nProtocolType):  # RTU
        log.error("pclink: 1 == int(nProtocolType): #RTU")
        if pData[0] != 0x91:
            return ""
        if pData[1] != 0x00:
            return ""
        return pData[4:4 + 2 * nRegisterNum]

    elif 2 == int(nProtocolType):  # ascii
        log.error("pclink: 2 == int(nProtocolType): #ascii")
        cpuvalue = int(pData[1])
        ovalue = int(pData[2])
        kvalue = int(pData[3])
        if cpuvalue != (nCpuNo + 48):
            return ""
        if ovalue != 79:
            return ""
        if kvalue != 75:
            return ""
        package = pData[4:-2]
        return package