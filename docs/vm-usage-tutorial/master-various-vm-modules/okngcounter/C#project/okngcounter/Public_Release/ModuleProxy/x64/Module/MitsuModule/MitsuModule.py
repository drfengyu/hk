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
     fmt = logging.Formatter(fmt='MitsuModule %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()


def ReadAssembly(paramlist):

    package=""
    if len(paramlist) < 8:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    FrameFormat = int(paramlist[0])
    DataCode = int(paramlist[1])
    SoftElementType = int(paramlist[2])
    IntDataType = int(paramlist[3])
    SoftElementAddress = int(paramlist[4])
    SoftElementNum = int(paramlist[5])
    while True:
        if FrameFormat == 1:#3E帧格式
            if DataCode == 1:#ASCII码通信
                #副头部+网络编号+PLC编号+请求目标模块IO编号+请求目标模块站号+请求数据长度+CPU监视定时器
                package = "500000FF03FF00****0010"
                 #指令、子指令、软元件代码
                if DataCode == 1:#ASCII码通信


                    if SoftElementType == 1:#软元件代码
                        package += "04010000";
                        package += "D*"
                    elif SoftElementType == 2:
                        package += "04010001";
                        package += "M*"
                    elif SoftElementType == 3:
                        package += "X*"
                    elif SoftElementType == 4:
                        package += "Y*"

                    package += str(SoftElementAddress).zfill(6)#起始元软件
                    package += '{:04x}'.format(SoftElementNum)#元软件点数
                    package = package.replace('****','{:04X}'.format(4+8+2+6+4))#长度赋值
                    break
#########################################################################
            elif DataCode == 2:#二进制通信
                package = [0x50, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x0C, 0x00, 0x10, 0x00]
                if SoftElementType == 1:#软元件代码
                    package += b'\x01\x04\x00\x00';
                elif SoftElementType == 2:
                    package += b'\x01\x04\x01\x00';



                package +=SoftElementAddress.to_bytes(3,byteorder = 'little')#起始元软件
                if SoftElementType == 1:#软元件代码
                    package += b"\xA8"
                elif SoftElementType == 2:
                    package += b"\x90"
                elif SoftElementType == 3:
                    package += b"\x9C"
                elif SoftElementType == 4:
                    package += b"\x9D"

                package += SoftElementNum.to_bytes(2,byteorder = 'little')#元软件点数
                
                byLen = (2+4+3+1+2).to_bytes(2,byteorder = 'little')#长度赋值
                package[7] = byLen[0]
                package[8] = byLen[1]
                return struct.pack('B'*len(package), *package)
                break
#########################################################################
        elif FrameFormat == 2:#3C格式3
            if DataCode == 1:#ASCII码通信
                package += chr(0x02)
                package += "F90000FF00"
                 #指令、子指令、软元件代码
                #package += "04010000";

                if SoftElementType == 1:#软元件代码
                    package += "04010000";
                    package += "D*"
                elif SoftElementType == 2:
                    package += "04010001";
                    package += "M*"
                elif SoftElementType == 3:
                    package += "X*"
                elif SoftElementType == 4:
                    package += "Y*"

                package += str(SoftElementAddress).zfill(6)#起始元软件
                package += '{:04X}'.format(SoftElementNum)#元软件点数
                package += chr(0x03)
                break
#########################################################################
            else:
                package = ""
                break

        elif FrameFormat == 3:#4C格式5
            if DataCode == 2:#二进制通信
                package = [0x10, 0x02, 0x15, 0x00, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00]
                if SoftElementType == 1:  # 软元件代码
                    package += b'\x01\x04\x00\x00';
                elif SoftElementType == 2:
                    package += b'\x01\x04\x01\x00';

                package +=SoftElementAddress.to_bytes(3,byteorder = 'little')#起始元软件
                if SoftElementType == 1:#软元件代码
                    package += b"\xA8"
                elif SoftElementType == 2:
                    package += b"\x90"
                elif SoftElementType == 3:
                    package += b"\x9C"
                elif SoftElementType == 4:
                    package += b"\x9D"

                package += SoftElementNum.to_bytes(2,byteorder = 'little')#元软件点数
                package += b'\x10\x03';
                byLen = (8+4+3+1+2).to_bytes(2,byteorder = 'little')#长度赋值
                package[2] = byLen[0]
                package[3] = byLen[1]
                break

            else:
                package = ""
                break
#########################################################################
        else:
            package = ""
            break
        break

    return package


def GetData(Valuelist,nStart,nEnd):
    
    if len(Valuelist) < nEnd:
        return ""
    package = Valuelist[nStart]
    for i in range(nStart+1,nEnd):
        package += Valuelist[i]

    return package



def ReadPrase(paramlist,RecvData):

    package=""
    #log.debug("recvdata is %s",RecvData)
    if len(paramlist) < 8:
        log.error("paramlist num is %d",len(paramlist))
        return ""

    FrameFormat = paramlist[0]
    DataCode = paramlist[1]
    SoftElementType = paramlist[2]
    IntDataType = paramlist[3]
    SoftElementAddress = paramlist[4]
    SoftElementNum = paramlist[5]

    if FrameFormat == '1':#3E帧格式
        if DataCode == '1':#ASCII码通信
            if len(RecvData) < 22:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[18:22]
            if endstr != b'0000':
                return""
            return RecvData[22:len(RecvData)]
        elif DataCode == '2':#二进制
            if len(RecvData) < 11:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[9:11]
            if endstr != b'\x00\x00':
                return""
            if SoftElementType == '1':
                return RecvData[11:len(RecvData)]
            else:
                return RecvData[11:len(RecvData)].hex()
    elif FrameFormat == '2':#3C格式3
        if DataCode == '1':#ASCII码通信
            if len(RecvData) < 15:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[11:15]
            if endstr != b'QACK':
                return""
            return RecvData[15:(len(RecvData) - 1)]
    elif FrameFormat == '3':#4C格式5
        if DataCode == '2':#二进制
            if len(RecvData) < 16:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[14:16]
            if endstr != b'\x00\x00':
                return""
            if SoftElementType == '1':
                return RecvData[16:(len(RecvData)-2)]
            else:
                return RecvData[16:(len(RecvData)-2)].hex()
           
    return package





def WriteArrayAssembly(paramlist,datalist):
    #FrameFormat,DataCode,SoftElementType,IntDataType,SoftElementAddress,SoftElementNum
    package=""

    nWriteNum = 0
    print(paramlist)
    if len(paramlist) < 8:
        log.error("paramlist num is %d",len(paramlist))
        return ""
    FrameFormat = paramlist[0]
    DataCode = paramlist[1]
    SoftElementType = paramlist[2]
    IntDataType = paramlist[3]
    SoftElementAddress = paramlist[4]
    SoftElementNum = paramlist[5]

    while True:
        if FrameFormat == '1':#3E帧格式
            if DataCode == '1':#ASCII码通信
                #副头部+网络编号+PLC编号+请求目标模块IO编号+请求目标模块站号+请求数据长度+CPU监视定时器
                package = "500000FF03FF00****0010";
                ##3E、ASCII字单位读取
                if SoftElementType == '1':#软元件代码
                    package += "14010000";
                    package += "D*"
                elif SoftElementType == '2':
                    package += "14010001";
                    package += "M*"
                package += SoftElementAddress.zfill(6)#起始元软件
                package += "$$$$"
                #package += '{:04x}'.format(SoftElementNum)#元软件点数
                nDataSize = 4+8+2+6+4

                #对输入的数据进行拆分
                for info in datalist:
                    print(package)
                    if int == type(info):
                        if SoftElementType == '1':  #D寄存器
                           if IntDataType == '1':#int 占16位
                              if info > 65535 or info < -32768:
                                   package = ""
                                   return package
                              package += '{:04X}'.format(int(info) & 0xFFFF)#具体数据
                              nDataSize += 4
                              nWriteNum += 1
                           elif IntDataType == '2':#int 占32位
                              strData = '{:08X}'.format(int(info) & 0xFFFFFFFF)
                              package += strData[4:8]#具体数据
                              package += strData[0:4]#具体数据
                              nDataSize += 8
                              nWriteNum += 2
                        elif SoftElementType == '2':      #M寄存器
                            if int(info) == 0:
                                package += "0"
                                nDataSize += 1
                                nWriteNum += 1
                            else:
                                package += "1"
                                nDataSize += 1
                                nWriteNum += 1
                    elif float == type(info):#float数据
                       if SoftElementType == '2':
                           return ""
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
                       fTemp = struct.pack('f', info)
                       package +=  '{:02X}'.format(fTemp[1])
                       package +=  '{:02X}'.format(fTemp[0])
                       package +=  '{:02X}'.format(fTemp[3])
                       package +=  '{:02X}'.format(fTemp[2])
                       nDataSize += 8
                       nWriteNum += 2
                    elif str == type(info):#string数据
                       if SoftElementType == '2':
                           return ""
                       nLoop = int(len(info) / 2) + (len(info) % 2)
                       for index in range(nLoop):
                           if index*2 + 1 < len(info):
                               package += '{:02X}'.format(ord(info[index*2+1]))
                               package += '{:02X}'.format(ord(info[index*2]))
                           else:
                               package += '{:04X}'.format(ord(info[index*2]))
                           nDataSize += 4
                           nWriteNum += 1
                    elif bytes == type(info):
                        nLoop = int(len(info) / 2) + (len(info) % 2)
                        for index in range(nLoop):
                            if index * 2 + 1 < len(info):
                                package += '{:02X}'.format(info[index * 2 + 1])
                                package += '{:02X}'.format(info[index * 2])
                            else:
                                package += '{:04X}'.format(info[index * 2])
                            nDataSize += 4
                            nWriteNum += 1

                if nWriteNum > int(SoftElementNum):#实际的数据长度大于设置的软元件点数
                    package = ""
                    break

                package = package.replace('****','{:04X}'.format(nDataSize))#长度赋值
                package = package.replace('$$$$','{:04X}'.format(nWriteNum))#元软件点数
                break

#########################################################################
            elif DataCode == '2':#二进制通信
                package = [0x50, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x0C, 0x00, 0x10, 0x00]

                if SoftElementType == '1':#软元件代码
                    package += b"\x01\x14\x00\x00";
                elif SoftElementType == '2':
                    package += b"\x01\x14\x01\x00";

                package += int(SoftElementAddress).to_bytes(3,byteorder = 'little')#起始元软件
                if SoftElementType == '1':#软元件代码
                    package += b"\xA8"
                elif SoftElementType == '2':
                    package += b"\x90"


                package += int(SoftElementNum).to_bytes(2,byteorder = 'little')#元软件点数
                nDataSize = 2+4+3+1+2
                #对输入的数据进行拆分

                for info in datalist:
                    if int == type(info):
                        if SoftElementType == '1':  # D寄存器
                           if IntDataType == '1':#int 占16位
                              if info > 65535 or info < -32768:
                                   package = ""
                                   return package
                              package += (int(info) & 0xFFFF).to_bytes(2,byteorder = 'little')#具体数据
                              nDataSize += 2
                              nWriteNum += 1
                           elif IntDataType == '2':#int 占32位
                              package += (int(info) & 0xFFFFFFFF).to_bytes(4,byteorder = 'little')#具体数据
                              nDataSize += 4
                              nWriteNum += 2
                        elif SoftElementType == '2':      #M寄存器
                            if int(info) == 0:
                                if nWriteNum % 2 == 0:
                                    package += b"\x00"
                                #nDataSize += 1
                                nWriteNum += 1
                            else:
                                if nWriteNum % 2 == 0:
                                    package += b"\x10"
                                else:
                                    if package[len(package) - 1] != 0x00:
                                        package[len(package) - 1] = 0x11

                                #nDataSize += 1
                                nWriteNum += 1
                    elif float == type(info):#float数据
                       if SoftElementType == '2':
                           return ""
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
                       package += struct.pack('<f',info) #二进制是正常的顺序
                       #fTemp = struct.pack('f', info)
                       #package +=  fTemp[1].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[0].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[3].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[2].to_bytes(1,byteorder = 'little')
                       nDataSize += 4
                       nWriteNum += 2
                    elif str == type(info):#string数据
                       if SoftElementType == '2':
                           return ""
                       nLoop = int(len(info) / 2) + (len(info) % 2)
                       for index in range(nLoop):
                           if index*2 + 1 < len(info):
                               package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                               package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                           else:
                               package += ord(info[index*2]).to_bytes(2,byteorder = 'little')
                           nDataSize += 2
                           nWriteNum += 1

                    elif bytes == type(info):
                        nLoop = int(len(info) / 2) + (len(info) % 2)
                        for index in range(nLoop):
                            if index * 2 + 1 < len(info):
                                package += info[index * 2 : index * 2 + 1]
                                package += info[index * 2 + 1 : index * 2 + 2]
                            else:
                                package += info[index * 2 : index * 2 + 1]
                                package += int(0).to_bytes(1,byteorder = 'little')
                            nDataSize += 2
                            nWriteNum += 1

                if SoftElementType == '2':  # D寄存器
                    nDataSize += int(nWriteNum / 2) + nWriteNum % 2
                if nWriteNum > int(SoftElementNum):#实际的数据长度大于设置的软元件点数
                    package = ""
                    break
                byLen = nWriteNum.to_bytes(2,byteorder = 'little')#元软件点数
                package[19] = byLen[0]
                package[20] = byLen[1]
                #请求数据长度
                package[7] = nDataSize.to_bytes(2,byteorder = 'little')[0]
                package[8] = nDataSize.to_bytes(2,byteorder = 'little')[1]
                return struct.pack('B'*len(package), *package)
                break
#########################################################################
        elif FrameFormat == '2':#3C格式3
            if DataCode == '1':#ASCII码通信
                package += chr(0x02)
                package += "F90000FF00"
                if SoftElementType == '1':  # 软元件代码
                    package += "14010000";
                    package += "D*"
                elif SoftElementType == '2':
                    package += "14010001";
                    package += "M*"
                package += SoftElementAddress.zfill(6)#起始元软件
                package += "$$$$"
                #package += '{:04x}'.format(SoftElementNum)#元软件点数
                nDataSize = 4+8+2+6+4
                #对输入的数据进行拆分
                for info in datalist:
                    print(package)
                    if int == type(info):
                        if SoftElementType == '1':  # D寄存器
                            if IntDataType == '1':  # int 占16位
                                if info > 65535 or info < -32768:
                                    package = ""
                                    return package
                                package += '{:04X}'.format(int(info) & 0xFFFF)  # 具体数据
                                nDataSize += 4
                                nWriteNum += 1
                            elif IntDataType == '2':  # int 占32位
                                strData = '{:08X}'.format(int(info) & 0xFFFFFFFF)
                                package += strData[4:8]  # 具体数据
                                package += strData[0:4]  # 具体数据
                                nDataSize += 8
                                nWriteNum += 2
                        elif SoftElementType == '2':  # M寄存器
                            if int(info) == 0:
                                package += "0"
                                nDataSize += 1
                                nWriteNum += 1
                            else:
                                package += "1"
                                nDataSize += 1
                                nWriteNum += 1
                    elif float == type(info):#float数据
                       if SoftElementType == '2':
                           return ""
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
                       fTemp = struct.pack('f', info)
                       package +=  '{:02X}'.format(fTemp[1])
                       package +=  '{:02X}'.format(fTemp[0])
                       package +=  '{:02X}'.format(fTemp[3])
                       package +=  '{:02X}'.format(fTemp[2])
                       nDataSize += 8
                       nWriteNum += 2
                    elif str == type(info):#string数据
                       if SoftElementType == '2':
                           return ""
                       nLoop = int(len(info) / 2) + (len(info) % 2)
                       for index in range(nLoop):
                           if index*2 + 1 < len(info):
                               package += '{:02X}'.format(ord(info[index*2+1]))
                               package += '{:02X}'.format(ord(info[index*2]))
                           else:
                               package += '{:04X}'.format(ord(info[index*2]))
                           nDataSize += 4
                           nWriteNum += 1

                    elif bytes == type(info):
                        nLoop = int(len(info) / 2) + (len(info) % 2)
                        for index in range(nLoop):
                            if index * 2 + 1 < len(info):
                                package += '{:02X}'.format(info[index * 2 + 1])
                                package += '{:02X}'.format(info[index * 2])
                            else:
                                package += '{:04X}'.format(info[index * 2])
                            nDataSize += 4
                            nWriteNum += 1

                if nWriteNum > int(SoftElementNum):#实际的数据长度大于设置的软元件点数
                    package = ""
                    break
                package += chr(0x03)
                package = package.replace('$$$$','{:04X}'.format(nWriteNum))#元软件点数
                break
            else:
                package = ""
                break
#########################################################################
        elif FrameFormat == '3':#4C格式5
            if DataCode == '2':#二进制通信
                package = [0x10, 0x02, 0x15, 0x00, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00]
                if SoftElementType == '1':  # 软元件代码
                    package += b"\x01\x14\x00\x00";
                elif SoftElementType == '2':
                    package += b"\x01\x14\x01\x00";
                package += (int(SoftElementAddress)).to_bytes(3,byteorder = 'little')#起始元软件
                if SoftElementType == '1':#软元件代码
                    package += b"\xA8"
                elif SoftElementType == '2':
                    package += b"\x90"
                elif SoftElementType == '3':
                    package += b"\x9C"
                elif SoftElementType == '4':
                    package += b"\x9D"

                package += SoftElementNum.to_bytes(2,byteorder = 'little')#元软件点数
                #对输入的数据进行拆分
                for info in datalist:
                    if int == type(info):
                        if SoftElementType == '1':  # D寄存器
                            if IntDataType == '1':  # int 占16位
                                if info > 65535 or info < -32768:
                                    package = ""
                                    return package
                                package += (int(info) & 0xFFFF).to_bytes(2, byteorder='little')  # 具体数据
                                nDataSize += 2
                                nWriteNum += 1
                            elif IntDataType == '2':  # int 占32位
                                package += (int(info) & 0xFFFFFFFF).to_bytes(4, byteorder='little')  # 具体数据
                                nDataSize += 4
                                nWriteNum += 2
                        elif SoftElementType == '2':  # M寄存器
                            if int(info) == 0:
                                if nWriteNum % 2 == 0:
                                    package += b"\x00"
                                # nDataSize += 1
                                nWriteNum += 1
                            else:
                                if nWriteNum % 2 == 0:
                                    package += b"\x10"
                                else:
                                    if package[len(package) - 1] != 0x00:
                                        package[len(package) - 1] = 0x11

                                # nDataSize += 1
                                nWriteNum += 1
                    elif float == type(info):#float数据
                       if SoftElementType == '2':
                           return ""
                       #package +=float2byte(info).hex()   struct.unpack('<f',bytes.fromhex(info))[0]
                       package += struct.pack('<f',info) #二进制是正常的顺序
                       #fTemp = struct.pack('f', info)
                       #package +=  fTemp[1].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[0].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[3].to_bytes(1,byteorder = 'little')
                       #package +=  fTemp[2].to_bytes(1,byteorder = 'little')
                       nDataSize += 4
                       nWriteNum += 2
                    elif str == type(info):#string数据
                       if SoftElementType == '2':
                           return ""
                       nLoop = int(len(info) / 2) + (len(info) % 2)
                       for index in range(nLoop):
                           if index*2 + 1 < len(info):
                               package += ord(info[index*2]).to_bytes(1,byteorder = 'little')
                               package += ord(info[index*2+1]).to_bytes(1,byteorder = 'little')
                           else:
                               package += ord(info[index*2]).to_bytes(2,byteorder = 'little')
                           nDataSize += 2
                           nWriteNum += 1

                    elif bytes == type(info):
                        nLoop = int(len(info) / 2) + (len(info) % 2)
                        for index in range(nLoop):
                            if index * 2 + 1 < len(info):
                                package += info[index * 2 : index * 2 + 1]
                                package += info[index * 2 + 1 : index * 2 + 2]
                            else:
                                package += info[index * 2 : index * 2 + 1]
                                package += int(0).to_bytes(2,byteorder = 'little')
                            nDataSize += 2
                            nWriteNum += 1

                if SoftElementType == '2':  # D寄存器
                    nDataSize += int(nWriteNum / 2) + nWriteNum % 2
                if nWriteNum > int(SoftElementNum):#实际的数据长度大于设置的软元件点数
                    package = ""
                    break
                byLen = nWriteNum.to_bytes(2,byteorder = 'little')#元软件点数
                package[20] = byLen[0]
                package[21] = byLen[1]
                package += b"\x10\x03";
                return struct.pack('B'*len(package), *package)
                break
            else:
                package = ""
                break
        else:
            package = ""
            break
#########################################################################
    return package


def WritePrase(paramlist,RecvData):
    package=""
    #log.debug("recvdata is %s",RecvData)

    if len(paramlist) < 8:
        return ""
    FrameFormat = paramlist[0]
    DataCode = paramlist[1]
    SoftElementType = paramlist[2]
    IntDataType = paramlist[3]
    SoftElementAddress = paramlist[4]
    SoftElementNum = paramlist[5]
    if FrameFormat == '1':#3E帧格式
        if DataCode == '1':#ASCII码通信
            if len(RecvData) < 22:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[18:22]
            #print(endstr)
            #endstr = RecvData[18:22]
            if endstr != b'0000':
                return""
            return "ok"
        elif DataCode == '2':#二进制
            if len(RecvData) < 11:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[9:11]
            #endstr = RecvData[9]
            #endstr += RecvData[10]
            print(endstr)
            if endstr != b'\x00\x00':
                return""
            return "ok"
    elif FrameFormat == '2':#3C格式3
        if DataCode == '1':#ASCII码通信
            if len(RecvData) < 15:#返回值太小，直接返回错误
              return ""
            #endstr = RecvData[11:15]
            endstr = RecvData[11:15]
            if endstr != b'QACK':
                return""
            return "ok"
    elif FrameFormat == '3':#4C格式5
        if DataCode == '2':#二进制
            if len(RecvData) < 16:#返回值太小，直接返回错误
              return ""
            endstr = RecvData[14:16]
            #endstr = GetData(RecvData,14,16)
            if endstr != b'\x00\x00':
                return""
            return "ok"
    return package
