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
        fmt='MitsuModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s',
        datefmt='%Y:%m:%d %H:%M:%S')

    log.setLevel(logging.DEBUG)

    # "OutputDebugString\DebugView"
    ods = DbgViewHandler()
    ods.setLevel(logging.DEBUG)
    ods.setFormatter(fmt)
    log.addHandler(ods)


config_logging()

def WriteArrayAssembly(paramlist,datalist):
    #log.error("keyence: WriteArrayAssembly start")
    package = ""
    data = ""
    nWriteNum = 0

    if len(paramlist) < 7:
        return package
    OrderType = int(paramlist[0])
    IntDataType = int(paramlist[1])
    SoftElementType = int(paramlist[2])
    SoftElementAddress = int(paramlist[3])
    SoftElementNum = int(paramlist[4])

    package += "WRS "
    if SoftElementType == 1:  # 软元件D
        package += "D" + str(SoftElementAddress)
        for value in datalist:
            if int == type(value):
                #log.error("keyence: int")
                if IntDataType == 1:  # 16位
                    if value > 65535 or value < -32768:
                        package = ""
                        return package
                    #log.error("keyence: value = %d", value)
                    #log.error("keyence: newvalue = %d", int(value) & 0xffff)
                    data += ' ' + str(int(value) & 0xffff)
                    nWriteNum += 1
                elif IntDataType == 2:  # 32位，需要两个寄存器
                    byte = struct.pack('i', value)
                    nTemp1 = (byte[0] & 0x000000ff) | ((byte[1] & 0x000000ff) << 8)
                    nTemp2 = (byte[2] & 0x000000ff) | ((byte[3] & 0x000000ff) << 8)
                    data += " " + str(nTemp1) + " " + str(nTemp2)
                    nWriteNum += 2
            elif float == type(value):
                #log.error("keyence: float")
                byte = struct.pack('f', value)
                nTemp1 = (byte[0] & 0x000000ff) | ((byte[1] & 0x000000ff) << 8)
                nTemp2 = (byte[2] & 0x000000ff) | ((byte[3] & 0x000000ff) << 8)
                data += " " + str(nTemp1) + " " + str(nTemp2)
                nWriteNum += 2

            elif str == type(value):
                #log.error("keyence: string")
                # for index in range(len(value)):
                #     temp = ord(value[index])
                #     data += ' ' + str(temp)
                #     nWriteNum += 1
                i = 0
                while( i < len(value)):
                    #log.error("keyence: i = %d", i)
                    temp1 = ord(value[i:i+1])
                    #log.error("keyence: temp1 = %d", temp1)
                    i += 1
                    if i < len(value):
                        temp2 = ord(value[i:i+1])
                    else:
                        temp2 = 0
                    #log.error("keyence: temp2 = %d", temp2)
                    temp = temp1 | (temp2 << 8)
                    #log.error("keyence: temp = %d", temp)
                    data += ' ' + str(temp)
                    i += 1
                    nWriteNum += 1

            elif bytes == type(value):
                #log.error("keyence: bytes")
                i = 0
                while (i < len(value)):
                    #log.error("keyence: i = %d", i)
                    temp1 = value[i]
                    #log.error("keyence: temp1 = %d", temp1)
                    i += 1
                    if i < len(value):
                        temp2 = value[i]
                    else:
                        temp2 = 0
                    #log.error("keyence: temp2 = %d", temp2)
                    temp = temp1 | (temp2 << 8)
                    #log.error("keyence: temp = %d", temp)
                    data += ' ' + str(temp)
                    i += 1
                    nWriteNum += 1


        if nWriteNum > SoftElementNum:
            package = ""
            return package

        package = package + " " + str(nWriteNum) + data


    package += "\r"
    #log.error("keyence: package = %s", package)
    return package

def ReadAssembly(paramlist):
    package = ""

    if len(paramlist) < 7:
        return package
    OrderType = int(paramlist[0])
    IntDataType = int(paramlist[1])
    SoftElementType = int(paramlist[2])
    SoftElementAddress = int(paramlist[3])
    SoftElementNum = int(paramlist[4])

    package += "RDS D" + str(SoftElementAddress) + " " + str(SoftElementNum) + "\r"
    #log.error("keyence: %s", package)
    return package

def WritePrase(paramlist,RecvData):
    #log.error("keyence: %s", RecvData)
    if(RecvData== b"OK\r\n"):
        return "ok"
    else:
        return ""

def ReadPrase(paramlist,RecvData):
    #log.error("keyence: %s", RecvData)
    if (RecvData == b"E0\r\n") or (RecvData == b"E1\r\n"):
        return ""
    else:
        #log.error("keyence: before package")
        package = RecvData[0: -2]
        #log.error("keyence: after package")
        return package