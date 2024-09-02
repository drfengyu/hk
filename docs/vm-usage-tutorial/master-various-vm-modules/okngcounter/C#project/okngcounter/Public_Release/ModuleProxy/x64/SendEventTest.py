

import struct
import logging
import ctypes
########################
# 此协议的输入数据由getInputParam产生，最终输出数据为数据块
########################


# output "logging" messages to DbgView via OutputDebugString (Windows only!)
OutputDebugString = ctypes.windll.kernel32.OutputDebugStringW

class DbgViewHandler(logging.Handler):
 def emit(self, record):
  OutputDebugString(self.format(record))

log = logging.getLogger("output.debug.string.example")

def config_logging():
    # format
     fmt = logging.Formatter(fmt='SendEventTest %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

def getInputParam():
    """
    definition output params,this params will be displayed on interface of VM
    : return:the dict of params,the key value is parameter name,the length of parameter name does not exceed 32.
            the value of dict is parameter type.the parameter type only support string，int，float.
    eg：definition three params
	获取输出参数
    : return:返回输出参数字典，字典的key值为输出参数名称，大小不超过32个字符长度
            value值为类型，只支持string，int，float,byte，4种类型
    示例：定义三个输出参数
    """
    params = {}
    params['SendoutPut1'] = 'int'
    params['SendoutPut2'] = 'float'
    params['SendoutPut3'] = 'string'
    params['SendoutPut4'] = 'byte'
    return params 


def handleMessage(list):#此Demo是把输入数据全部加1后进行输出,各个数据用#分割,最终此接口输出一个数据块
    returnbuf = b''
    nIndex = 0
    for info in list:
        if nIndex == 0:#输入数据的顺序和getInputParam的数据顺序一致
            returnbuf += struct.pack('i',info+1)
        elif nIndex == 1:
            returnbuf += struct.pack('f',info+1.0)
        elif nIndex == 2:
            returnbuf += 'vmtest'.encode()
        elif nIndex == 3:
            returnbuf += info
            returnbuf += b'\xff'

        returnbuf += '#'.encode()
        nIndex += 1
    #loginfo = returnbuf.hex()
    #log.error("%s",loginfo)
    return returnbuf


