
# hex data parsing demo 
# 接收事件脚本文件示例
import struct
import logging
import ctypes
########################
# 
########################


# output "logging" messages to DbgView via OutputDebugString (Windows only!)
OutputDebugString = ctypes.windll.kernel32.OutputDebugStringW

class DbgViewHandler(logging.Handler):
 def emit(self, record):
  OutputDebugString(self.format(record))

log = logging.getLogger("output.debug.string.example")

def config_logging():
    # format
     fmt = logging.Formatter(fmt='RecvEventTest %(asctime)s.%(msecs)03d [%(thread)5s] %(levelname)-8s %(funcName)-20s %(lineno)d %(message)s', datefmt='%Y:%m:%d %H:%M:%S')
 
     log.setLevel(logging.DEBUG)

     # "OutputDebugString\DebugView"
     ods = DbgViewHandler()
     ods.setLevel(logging.DEBUG)
     ods.setFormatter(fmt)
     log.addHandler(ods)

config_logging()

def getOutputParam():
    """
    definition output params,this params will be displayed on interface of VM
    : return:the dict of params,the key value is parameter name,the length of parameter name does not exceed 32.
            the value of dict is parameter type.the parameter type only support string，int，float.
    eg：definition three params
	获取输出参数
    : return:返回输出参数字典，字典的key值为输出参数名称，大小不超过32个字符长度
            value值为类型，只支持string，int，float,byte，四种类型
    示例：定义三个输出参数
    """
    params = {}
    params['outPut1'] = 'int'
    params['outPut2'] = 'float'
    params['outPut3'] = 'string'
    params['outPut4'] = 'byte'
    
    return params 


def handleMessage(info):
    '''
	处理数据函数
    ：param info: 待处理的数据块，数据类型为bytes
    ：return: 输出参数为列表，其中的数据和getOutputParam中的数据顺序一致，且数据类型要一致
    示例: #分割出数据，并分别对应getOutputParam的类型，然后把数据按照顺序列表输出
    '''
    #log.debug('start handlemessage')
    returnlist = []
    splitdata = '#'.encode() #分割符
    if info[len(info) - 1] != splitdata:
        info += splitdata#最后一个数据不是分割符，人为增加一个

    nCount = info.count(splitdata)#计算分割后数据个数
    str = info.split(splitdata)#进行数据分割

    for nIndex in range(nCount):
        if nIndex == 0:
            returnlist.append(struct.pack('i',int(bytes.decode(str[nIndex]))))#根据getOutputParam的数据得知第一个数据为int,先把bytes转为str,再转为int分割后的数据存入list
        elif nIndex == 1:
            returnlist.append(struct.pack('f',float(bytes.decode(str[nIndex]))))
        elif nIndex == 2:
            returnlist.append(str[nIndex])
        elif nIndex == 3:
            returnlist.append(str[nIndex])


    return returnlist


