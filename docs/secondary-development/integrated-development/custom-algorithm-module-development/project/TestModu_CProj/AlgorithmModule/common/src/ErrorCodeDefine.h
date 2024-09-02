/***************************************************************************************************
 *
 * 版权信息：版权所有 (c) 2020, 保留所有权利
 *
 * 文件名称：ErrorCodeDefine.h
 * 摘    要：错误码头文件
 *
 * 作    者：视觉平台组
 * 日    期：2020-01-17 11:09:05
 * 备    注：新建

 * Copyright information: All Right Reserved.
 *
 * File name: ErrorCodeDefine.h
 * Brief: Error code definition
 *
 * Author: VisionMaster Team
 * Date: 2020-01-17 11:09:05
 * Note: New
 ****************************************************************************************************/

#ifndef _IMVS_6000_ERROR_CODE_DEFINE_H_
#define _IMVS_6000_ERROR_CODE_DEFINE_H_

// CH: 错误码 | EN: Error code
#define   IMVS_EC_OK                                        0x00000000  // CH: 无错误 | EN: No error

/****************************************************************************
 * 通用错误 0xE0000000~0xE00000FF
 * Universal errors 0xE0000000~0xE00000FF
 ****************************************************************************/
#define   IMVS_EC_VERSION                                   0xE0000000  // CH: 版本错误 | EN: Incorrect version No.
#define   IMVS_EC_PARAM                                     0xE0000001  // CH: 参数错误 | EN: Incorrect parameter
#define   IMVS_EC_RESOURCE_CREATE                           0xE0000002  // CH: 资源创建失败 | EN: Applying for resource failed
#define   IMVS_EC_OUTOFMEMORY                               0xE0000003  // CH: 内存不足 | EN: Insufficient memory
#define   IMVS_EC_POINTER_CAST                              0xE0000004  // CH: 指针转换错误 | EN: Pointer conversion failed
#define   IMVS_EC_MEMORY_BEYOND_THRESHOLD                   0xE0000005  // CH: 系统内存使用率超过阈值 | EN: The CPU usage is too high
#define   IMVS_EC_INVALID_HANDLE                            0xE0000006  // CH: 句柄无效 | EN: Invalid or incorrect handle
#define   IMVS_EC_NOT_SUPPORT                               0xE0000007  // CH: 操作不支持 | EN: This operation is not supported
#define   IMVS_EC_NOT_READY                                 0xE0000008  // CH: 资源未初始化或未准备好 | EN: Initializing resource failed
#define   IMVS_EC_WAIT_TIMEOUT                              0xE0000009  // CH: 等待超时 | EN: Waiting timed out
#define   IMVS_EC_NULL_PTR                                  0xE000000A  // CH: 指针为空 | EN: Null pointer
#define   IMVS_EC_PROCESS_START_FAIL                        0xE000000B  // CH: 进程启动失败 | EN: Starting up process failed
#define   IMVS_EC_PROCESS_ALREADY_START                     0xE000000C  // CH: 客户端程序已启动 | EN: The client is already started up
#define   IMVS_EC_SOLUTION_LOADING                          0xE000000D  // CH: 正在加载方案 | EN: Solution is loading
#define   IMVS_EC_SOLUTION_SAVING                           0xE000000E  // CH: 正在保存方案 | EN: Solution is saving
#define   IMVS_EC_CALL_ORDER                                0xE000000F  // CH: 接口调用顺序错误 | EN: Incorrect API call sequence
#define   IMVS_EC_LOAD_LIBRARY                              0xE0000010  // CH: 动态库加载失败 | EN: Loading dynamic library failed
#define   IMVS_EC_GET_FUN_ADDRESS                           0xE0000011  // CH: 获取函数地址失败 | EN: Getting function address failed
#define   IMVS_EC_PARAM_BUF_LEN                             0xE0000012  // CH: 参数缓冲区长度不足 | EN: Insufficient buffer size
#define   IMVS_EC_GETTING_PLAT_INFO                         0xE0000013  // CH: 正在获取底层信息 | EN: Getting underlying information
#define   IMVS_EC_INDEX_OUT_OF_BOUNDARY                     0xE0000014  // CH: 索引值越界 | EN: The index No. is out of limit
#define   IMVS_EC_OPEN_FILEMAPPING                          0xE0000015  // CH: 打开共享内存失败 | EN: Opening sharing memory failed
#define   IMVS_EC_THREAD_START_FAIL                         0xE0000016  // CH: 开启线程失败 | EN: Starting thread failed
#define   IMVS_EC_PROTOCOL                                  0xE0000017  // CH: 协议解析错误 | EN: Parsing protocol failed
#define   IMVS_EC_DATA_ERROR                                0xE0000018  // CH: 数据错误 | EN: Incorrect data
#define   IMVS_EC_NOT_IMPLEMENTED                           0xE0000019  // CH: 操作未实现 | EN: No operation is done
#define   IMVS_EC_DATA_OVER_SIZE                            0xE000001A  // CH: 数据大小超过上限 | EN: No more data is allowed
#define   IMVS_EC_PRECONDITION                              0xE000001B  // CH: 前置条件有误 | EN: Pre-condition is wrong
#define   IMVS_EC_RUNTIME                                   0xE000001C  // CH: 运行环境错误 | EN: Running environment error
#define   IMVS_EC_SOLUTION_CLOSING                          0xE000001D  // CH: 正在关闭方案 | EN: Closing solution
#define   IMVS_EC_SILENT_EXEC_STATUS                        0xE000001E  // CH: 静默执行中   | EN: In silent execution
#define   IMVS_EC_DYNAMICIO_PARAM_NOT_FOUND                 0xE000001F  // CH: 动态IO参数无法找到   | EN: No dynamicIO param found
#define   IMVS_EC_CLOSE_FILEMAPPING                         0xE0000020  // CH: 关闭共享内存失败 | EN: Close sharing memory failed
#define   IMVS_EC_UNKNOWN                                   0xE00000FF  // CH: 未知错误 | EN: Unknown error


/****************************************************************************
 * 通信相关错误 0xE0000100~0xE00001FF
 * Communication-related errors 0xE0000100~0xE00001FF
 ****************************************************************************/
#define   IMVS_EC_COMMU_SOCKET_CREAT                        0xE0000100  // CH: socket创建失败 | EN: Creating socket failed
#define   IMVS_EC_COMMU_SOCKET_INVALID                      0xE0000101  // CH: socket无效 | EN: Invalid socket
#define   IMVS_EC_COMMU_SERIAL_OPEN                         0xE0000102  // CH: 打开串口失败 | EN: Connecting to serial port failed
#define   IMVS_EC_COMMU_INVALID_ADDRESS                     0xE0000103  // CH: 地址无效 | EN: Invalid address
#define   IMVS_EC_COMMU_ADDRESS_INUSE                       0xE0000104  // CH: 地址已被使用 | EN: Unavailable address
#define   IMVS_EC_COMMU_CONNECT                             0xE0000105  // CH: 连接失败 | EN: Connection failed
#define   IMVS_EC_COMMU_DISCONNECT                          0xE0000106  // CH: 断开连接失败 | EN: Disconnection failed
#define   IMVS_EC_COMMU_SEND_FAIL                           0xE0000107  // CH: 发送失败 | EN: Sending data failed
#define   IMVS_EC_COMMU_RECV_TIMEOUT                        0xE0000108  // CH: 接收超时 | EN: Response timed out
#define   IMVS_EC_COMMU_MESSAGE_FORMAT                      0xE0000109  // CH: 消息格式错误 | EN: Incorrect protocol format
#define   IMVS_EC_COMMU_MSG_TOO_LONG                        0xE000010A  // CH: 报文长度超出限制 | EN: Maximum message length reached
#define   IMVS_EC_COMMU_HEARTBEAT                           0xE000010B  // CH: 心跳异常 | EN: Heartbeat exception


/****************************************************************************
 * 文件相关错误 0xE0000200~0xE00002FF
 * File-related errors 0xE0000200~0xE00002FF
 ****************************************************************************/
#define   IMVS_EC_FILE_MKDIR                                0xE0000200  // CH: 创建路径错误 | EN: Incorrect file path
#define   IMVS_EC_FILE_OPEN                                 0xE0000201  // CH: 文件无法打开 | EN: Opening file failed
#define   IMVS_EC_FILE_SAVE                                 0xE0000202  // CH: 保存文件数据失败 | EN: Saving file failed
#define   IMVS_EC_FILE_NOT_FOUND                            0xE0000203  // CH: 文件不存在 | EN: The file does not exist
#define   IMVS_EC_FILE_FORMAT                               0xE0000204  // CH: 文件格式错误 | EN: Incorrect file format
#define   IMVS_EC_FILE_COMPRESS                             0xE0000205  // CH: 文件压缩失败 | EN: Compressing file failed
#define   IMVS_EC_FILE_DECOMPRESS                           0xE0000206  // CH: 文件解压失败 | EN: Decompressing file failed
#define   IMVS_EC_FILE_XML_ELEMENT                          0xE0000207  // CH: xml中element不存在 | EN: The "element" does not exist in the XML file
#define   IMVS_EC_FILE_XML_ATTRIBUTE                        0xE0000208  // CH: xml中Attribute不存在 | EN: The "attribute" does not exist in the XML file
#define   IMVS_EC_FILE_PATH_TOO_LONG                        0xE0000209  // CH: 文件路径长度超过系统最大值 | EN: The file path is too long
#define   IMVS_EC_FILE_BE_OCCUPIED                          0xE000020A  // CH: 文件被占用 | EN: The file is already occupied
#define   IMVS_EC_FILE_PATH_EMPTY                           0xE000020B  // CH: 目标路径为空 | EN: The target path is empty
#define   IMVS_EC_FILE_INSUFFICIENT_DISK_SPACE              0xE000020C  // CH: 磁盘空间不足 | EN: Insufficient disk space
#define   IMVS_EC_FILE_UI_NOT_FOUND                         0xE000020D  // CH: 界面文件不存在 | EN: Interface file does not exist
#define   IMVS_EC_FILE_BACKUP                               0xE000020E  // CH: 文件备份失败 | EN: Backup file failed
#define   IMVS_EC_FILE_PATH_INVALID                         0xE000020F  // CH: 目标路径无效 | EN: The target path is invalid


/****************************************************************************
 * 模块操作错误 0xE0000300~0xE00003FF
 * Module operation errors 0xE0000300~0xE00003FF
 ****************************************************************************/
#define   IMVS_EC_MODULE_BUSY                               0xE0000300  // CH: 流程处于忙碌状态 | EN: The procedure is busy
#define   IMVS_EC_MODULE_COUNT_BEYOND                       0xE0000301  // CH: 模块个数超出限制 | EN: Maximum number of modules reached
#define   IMVS_EC_MODULE_NOT_FOUND                          0xE0000302  // CH: 模块不存在 | EN: The module does not exist
#define   IMVS_EC_MODULE_ALREADY_EXIST                      0xE0000303  // CH: 模块已存在 | EN: The module already exists
#define   IMVS_EC_MODULE_EMPTY                              0xE0000304  // CH: 模块数量为0 | EN: No module
#define   IMVS_EC_MODULE_NOT_REGISTER                       0xE0000305  // CH: 模块未注册 | EN: The module is not registered
#define   IMVS_EC_MODULE_SUBSCRIBE_FAIL                     0xE0000306  // CH: 模块订阅失败 | EN: Subscribing module failed
#define   IMVS_EC_MODULE_PROC_CTRL_EXCEPT                   0xE0000307  // CH: 流程控制模块出现异常（崩溃） | EN: Procedure control module exception
#define   IMVS_EC_MODULE_INPUT_CFG_UNDONE                   0xE0000308  // CH: 模块输入未配置完成 | EN: The module input parameter is not configured
#define   IMVS_EC_MODULE_INPUT_NOT_FOUND                    0xE0000309  // CH: 模块输入无法找到 | EN: No module input found
#define   IMVS_EC_MODULE_INPUT_STATUS                       0xE000030A  // CH: 模块输入状态错误 | EN: Module input status error
#define   IMVS_EC_MODULE_INPUT_COUNT                        0xE000030B  // CH: 模块输入个数错误 | EN: Incorrect number of module inputs
#define   IMVS_EC_MODULE_INPUT_BUF_LEN                      0xE000030C  // CH: 模块输入缓冲区长度太小 | EN: The buffer size of module input is too small
#define   IMVS_EC_MODULE_PARAM_NOT_SUPPORT                  0xE000030D  // CH: 参数不支持 | EN: This parameter is not supported
#define   IMVS_EC_MODULE_PARAM_VALUE_ILLEGAL                0xE000030E  // CH: 参数值无效 | EN: Invalid parameter value
#define   IMVS_EC_MODULE_PARAM_TYPE                         0xE000030F  // CH: 参数类型错误 | EN: Incorrect parameter type
#define   IMVS_EC_MODULE_IMPORT_DATA                        0xE0000310  // CH: 导入数据格式错误 | EN: The imported data format is incorrect
#define   IMVS_EC_MODULE_CONTINUE_EXECUTE                   0xE0000311  // CH: 正在连续执行 | EN: Continuously executing
#define   IMVS_EC_MODULE_PROCEDURE_EMPTY                    0xE0000312  // CH: 流程内的模块数量为0 | EN: No module in the procedure
#define   IMVS_EC_MODULE_HEARTBEAT_EXCEPTION                0xE0000313  // CH: 模块心跳出现异常 | EN: Module heartbeat exception
#define   IMVS_EC_MODULE_SUB_RST_NOT_FOUND                  0xE0000314  // CH: 未找到订阅结果值 | EN: No subscription result found
#define   IMVS_EC_MODULE_OUT_NOT_FOUND                      0xE0000315  // CH: 模块输出无法找到 | EN: No module output found
#define   IMVS_EC_MODULE_PROCEDURE_NOT_FOUND                0xE0000316  // CH: 流程不存在 | EN: The procedure does not exist
#define   IMVS_EC_MODULE_PROCEDURE_ALREADY_EXIST            0xE0000317  // CH: 流程已存在 | EN: The procedure already exists
#define   IMVS_EC_MODULE_CREATE_ALG_MODULE_FAILED           0xE0000318  // CH: 创建算法模块失败 | EN: Creating algorithm module failed
#define   IMVS_EC_MODULE_LOOP_ALREADY_EXIST                 0xE0000319  // CH: 循环已存在 | EN: The loop already exists
#define   IMVS_EC_MODULE_LOOP_NOT_FOUND                     0xE000031A  // CH: 循环不存在 | EN: The loop does not exist
#define   IMVS_EC_MODULE_SUB_RECORD_NOT_FOUND               0xE000031B  // CH: 未找到订阅记录 | EN: No subscription record found
#define   IMVS_EC_MODULE_SUB_PARAM_ERROR                    0xE000031C  // CH: 订阅参数有误 | EN: Incorrect subscription parameter
#define   IMVS_EC_MODULE_PROCEDURE_DISABLED                 0xE000031D  // CH: 流程处于禁用状态 | EN: Process is disabled
#define   IMVS_EC_MODULE_TRIGGERSTRING_NOT_MATCH            0xE000031E  // CH: 触发字符不匹配 | EN: Trigger string mismatch
#define   IMVS_EC_MODULE_GLOBALSCRIPT_PROCESSING            0xE000031F  // CH: 全局脚本流程正在执行中 | EN: Global scripting process is executing
#define   IMVS_EC_MODULE_GLOBALSCRIPT_COMPILE_FAIL          0xE0000320  // CH: 全局脚本编译失败 | EN: Global script compilation failed
#define   IMVS_EC_MODULE_GROUP_ALREADY_EXIST                0xE0000321  // CH: 分组已存在 | EN: Group already exists
#define   IMVS_EC_MODULE_GROUP_NOT_FOUND                    0xE0000322  // CH: 分组不存在 | EN: Group does not exist
#define   IMVS_EC_MODULE_GROUP_EXPORTING                    0xE0000323  // CH: 正在导出Group | EN: Exporting group
#define   IMVS_EC_MODULE_GROUP_IMPORTING                    0xE0000324  // CH: 正在导入Group | EN: Importing group
#define   IMVS_EC_MODULE_BEYOND_NESTED_LAYER                0xE0000325  // CH: 超出嵌套层级 | EN: Beyond module nested layer
#define   IMVS_EC_PROCESS_COUNT_BEYOND                      0xE0000326  // CH: 流程数量超出限制  | EN: Maximum number of process reached
#define   IMVS_EC_MODULE_NAME_DUPLICATED                    0xE0000327  // CH: 名称重复  | EN: Name duplicated
#define   IMVS_EC_PROCESS_IN_VMFILE_SOL                     0xE0000328  // CH: 流程包含在方案的界面文件中  | EN: The procedure is contained within interface file of solution
#define   IMVS_EC_MODULE_PROCEDURE_EXPORTING                0xE0000329  // CH: 正在导出流程 | EN: Exporting procedure
#define   IMVS_EC_MODULE_PROCEDURE_IMPORTING                0xE000032A  // CH: 正在导入流程 | EN: Importing procedure
#define   IMVS_EC_MODULE_ROUGH_MATCH_FAIL                   0xE000032B  // CH: 字符缺陷粗定位失败 | EN: Character defect coarse positioning failed
#define   IMVS_EC_MODULE_COARSE_OVER_SCORE                  0xE000032C  // CH: 速度阈值大于最小匹配分数 | EN: The speed threshold is greater than the minimum match score
#define   IMVS_EC_MODULE_SUB_CONNECTION_ERROR               0xE000032D  // CH: 两模块存在订阅关系但连线不可达 | EN: Subscribe one module output but connection does not exist
#define   IMVS_EC_MODULE_SCALE_VALUE_OVERFLOW               0xE000032E  // CH: 位置修正XY尺度值超出范围(0~10000) | EN： The value of scale X or Y is too big
#define   IMVS_EC_MODULE_EXACT_MATCH_FAIL                   0xE000032F  // CH: 字符缺陷精定位失败 | EN: Character defect fine positioning failed
#define   IMVS_EC_MODULE_EXACT_MATCH_CHANGED                0xE0000330  // CH: 精定位信息改变 重新进行统计训练 | EN: Resume statistical training due to fine position change
#define   IMVS_EC_MODULE_PARAM_INPUT                        0xE0000331  // CH: 模块输入IO个数为0 | EN: No input
#define   IMVS_EC_MODULE_SUB_GLOBAL_VARIABLE                0xE0000332  // CH: 订阅了全局变量 | EN: Subscribe global variable
#define   IMVS_EC_MODULE_HAS_LOAD_FAIL                      0xE0000333  // CH: 存在加载失败模块 | EN: There are modules that failed to load
#define   IMVS_EC_MODULE_OVERRUN_IMAGECOUNT                 0xE0000334  // CH: 单一图像源存图数量大于120 | EN： The number of saved imaged of the imagesource is greater than 120 
#define   IMVS_EC_MODULE_INPECT_MATCH_FAIL                  0xE0000335  // ch: 未匹配到目标或匹配个数异常 | EN： The target is not matched or the number of matches is abnormal
#define   IMVS_EC_MODULE_GROUP_OUTPUT_MODULE_FAILED         0xE0000336  // CH: group输出关联模块执行失败 | EN:  


/****************************************************************************
 * 相机错误 0xE0000400~0xE00004FF
 * Camera errors 0xE0000400~0xE00004FF
 ****************************************************************************/
#define   IMVS_EC_CAMERA_RUNTIME                            0xE0000400  // CH: 运行环境有问题 | EN: Running environment exception
#define   IMVS_EC_CAMERA_NOT_IMPLEMENTED                    0xE0000401  // CH: 命令不被设备支持 | EN: This command is not supported by the device
#define   IMVS_EC_CAMERA_ACCESS_DENIED                      0xE0000402  // CH: 设备无访问权限 | EN: No permission for this device to access to
#define   IMVS_EC_CAMERA_BUSY                               0xE0000403  // CH: 设备忙，或网络断开 | EN: Device is busy or network is disconnected
#define   IMVS_EC_CAMERA_PACKET                             0xE0000404  // CH: 网络包数据错误 | EN: Network data packet error
#define   IMVS_EC_CAMERA_USB_READ                           0xE0000405  // CH: 读USB出错 | EN: Reading from USB failed
#define   IMVS_EC_CAMERA_USB_WRITE                          0xE0000406  // CH: 写USB出错 | EN: Writing to USB failed
#define   IMVS_EC_CAMERA_USB_DEVICE                         0xE0000407  // CH: 设备异常 | EN: USB device exception
#define   IMVS_EC_CAMERA_USB_BANDWIDTH                      0xE0000408  // CH: USB带宽不足 | EN: Insufficient USB bandwidth
#define   IMVS_EC_CAMERA_NODATA                             0xE0000409  // CH: 相机无数据 | EN: No data in the camera
#define   IMVS_EC_CAMERA_EMPTY                              0xE0000410  // CH: 未连接相机 | EN: Camera not connected
#define   IMVS_EC_CAMERA_TYPE_NOT_MATCH                     0xE0000411  // CH: 相机类型不匹配 | EN: Camera type mismatch


/****************************************************************************
 * 算法错误 0xE0000500~0xE00005FF
 * Algorithm errors 0xE0000500~0xE00005FF
 ****************************************************************************/
#define   IMVS_EC_ALGORITHM_IMG_DATA_NULL                   0xE0000500  // CH: 图像数据存储地址为空（某个分量） | EN: Image data storage path is empty (a component)
#define   IMVS_EC_ALGORITHM_IMG_STEP                        0xE0000501  // CH: 图像宽高与step参数不匹配 | EN: The image width/height and step parameter mismatches
#define   IMVS_EC_ALGORITHM_IMG_SIZE                        0xE0000502  // CH: 图像宽高不正确或者超出范围 | EN: The image width/height is incorrect or out of limit
#define   IMVS_EC_ALGORITHM_IMG_FORMAT                      0xE0000503  // CH: 图像格式不正确或者不支持 | EN: The image format is incorrect or not supported
#define   IMVS_EC_ALGORITHM_MEM_SIZE_ALIGN                  0xE0000504  // CH: 内存空间大小不满足对齐要求 | EN: The memory size does not meet with the alignment requirement
#define   IMVS_EC_ALGORITHM_MEM_LACK                        0xE0000505  // CH: 内存空间大小不够 | EN: Insufficient memory size
#define   IMVS_EC_ALGORITHM_MEM_ALIGN                       0xE0000506  // CH: 内存对齐不满足要求 | EN: The memory alignment does not meet with the requirement
#define   IMVS_EC_ALGORITHM_ABILITY_ARG                     0xE0000507  // CH: ABILITY存在无效成员变量 | EN: Invalid variable member exists in the ABILITY
#define   IMVS_EC_ALGORITHM_CPUID                           0xE0000508  // CH: cpu不支持优化代码中的指令集 | EN: Optimizing command set of code is not supported by CPU
#define   IMVS_EC_ALGORITHM_DATA_SIZE                       0xE0000509  // CH: 数据大小不正确 | EN: Incorrect data size
#define   IMVS_EC_ALGORITHM_CALL_BACK                       0xE000050A  // CH: 回调函数出错 | EN: Callback function error
#define   IMVS_EC_ALGORITHM_OVER_MAX_MEM                    0xE000050B  // CH: 超过HKA限定最大内存 | EN: Maximum HKA memory reached
#define   IMVS_EC_ALGORITHM_STEP_ERR                        0xE000050C  // CH: 数据STEP错误 | EN: Data STEP error
#define   IMVS_EC_ALGORITHM_PARAM_INDEX                     0xE000050D  // CH: 参数index错误 | EN: Parameter "index" error
#define   IMVS_EC_ALGORITHM_PARAM_NUM                       0xE000050E  // CH: 参数个数错误 | EN: Incorrect number of parameters
#define   IMVS_EC_ALGORITHM_NOT_INIT                        0xE000050F  // CH: 算法库未初始化 | EN: Algorithm library is not initialized
#define   IMVS_EC_ALGORITHM_INPUT_IMAGE_ERROR               0xE0000510  // CH: 获取输入图像失败 | EN: Failed to get input image
#define   IMVS_EC_ALGORITHM_INPUT_ROI_ERROR	                0xE0000511	// CH: 获取输入ROI失败 | EN: Failed to get input ROI
#define   IMVS_EC_ALGORITHM_INPUT_FIXTUREINFO_ERROR	        0xE0000512	// CH: 获取位置修正信息失败 | EN: Failed to get position correction information
#define   IMVS_EC_ALGORITHM_MODEL_EMPTY			            0xE0000513	// CH: 模型数据为空 | EN: Model data is empty
#define   IMVS_EC_ALGORITHM_ROITYPE_UNKNOWN		            0xE0000514	// CH: 未定义的ROI类型 | EN: Undefined ROI type
#define   IMVS_EC_ALGORITHM_IMG_PATH                        0xE0000515  // CH: 不支持含中文的路径 | EN: Paths with Chinese are not supported 
#define   IMVS_EC_ALGORITHM_TEACH_NOREADY                   0xE0000516  // CH: 未发送示教信息 | EN:  
#define   IMVS_EC_ALGORITHM_CALIB_NOREADY                   0xE0000517  // CH: 标定流程未完成 | EN: 
#define   IMVS_EC_ALGORITHM_NOT_SUPPORT_INVERT_SELECT       0xE0000518  // CH: 最小值和最大值相等，不支持反选 | EN: Inversion failed. The Max. value is the same with the Min. value.

/****************************************************************************
 * 服务操作错误 0xE0000600~0xE00006FF
 * Service operation errors 0xE0000600~0xE00006FF
 ****************************************************************************/
#define   IMVS_EC_SERVICE_CREATE                            0xE0000600  // CH: 创建服务失败 | EN: Creating service failed
#define   IMVS_EC_SERVICE_DELETE                            0xE0000601  // CH: 删除服务失败 | EN: Deleting service failed
#define   IMVS_EC_SERVICE_OPEN                              0xE0000602  // CH: 打开服务失败 | EN: Opening service failed
#define   IMVS_EC_SERVICE_START                             0xE0000603  // CH: 服务启动失败 | EN: Starting service failed
#define   IMVS_EC_SERVICE_STOP                              0xE0000604  // CH: 服务停止失败 | EN: Stopping service failed
#define   IMVS_EC_SERVICE_GET_PATH                          0xE0000605  // CH: 服务路径获取失败 | EN: Getting service path failed
#define   IMVS_EC_SERVICE_FIND_FILE                         0xE0000606  // CH: 服务文件查找失败 | EN: Finding service file failed
#define   IMVS_EC_SERVICE_LOAD_LIBRARY                      0xE0000607  // CH: 服务库加载失败 | EN: Loading service library failed
#define   IMVS_EC_SERVICE_RETRIEVES_FUNC                    0xE0000608  // CH: 服务函数检索失败 | EN: Retrieving service function failed


/****************************************************************************
 * 软件授权相关错误 0xE0000700~0xE00007FF
 * Software licensing-related errors 0xE0000700~0xE00007FF
 ****************************************************************************/
#define   IMVS_EC_ENCRYPT_DONGLE_OUTDATE                    0xE0000700  // CH: 加密狗未检测到或检测异常 | EN: No dongle detected or detection exception
#define   IMVS_EC_ENCRYPT_DONGLE_OLD_EXPIRE                 0xE0000701  // CH: 加密狗需重新插拔一次 | EN: Try to insert it again
#define   IMVS_EC_ENCRYPT_ALGORITHM_CHECK_FAIL              0xE0000702  // CH: 算法库检测授权失败 | EN: Detecting algorithm library license failed
#define   IMVS_EC_ENCRYPT_ALGORITHM_EXPIRE                  0xE0000703  // CH: 算法库使用期已过 | EN: The algorithm library license is expired
#define   IMVS_EC_ENCRYPT_SOFT_OUTDATE                      0xE0000704  // CH: 软锁未检测到或检测异常 | EN: Soft lock not detected or detected exception
#define   IMVS_EC_ENCRYPT_SOFT_NOT_ACTIVATED                0xE0000705  // CH: 产品授权未激活 | EN: Product authorization not activated
#define   IMVS_EC_ENCRYPT_SOFT_NOT_SUPPORT                  0xE0000706  // CH: 软锁不支持的功能ID | EN: Feature ID not supported by soft lock
#define   IMVS_EC_ENCRYPT_SOFT_FEATURE_EXPIRE               0xE0000707  // CH: 授权的功能已过期 | EN: The authorized feature has expired
#define   IMVS_EC_ENCRYPT_SOFT_ACCESS_DENIED                0xE0000708  // CH: 访问被拒绝 | EN: Access denied
#define   IMVS_EC_ENCRYPT_SOFT_NO_TIME                      0xE0000709  // CH: 时钟不可用 | EN: Clock is not available
#define   IMVS_EC_ENCRYPT_SOFT_NO_DRIVER                    0xE000070A  // CH: 未安装软加密RTE | EN: Soft encryption RTE not installed
#define   IMVS_EC_ENCRYPT_SOFT_TS_DETECTED                  0xE000070B  // CH: 程序在终端运行 | EN: The program is running at the terminal
#define   IMVS_EC_ENCRYPT_SOFT_RDP_DETECTED                 0xE000070C  // CH: 程序在远程端运行 | EN: The program is running on the remote side
#define   IMVS_EC_ENCRYPT_SOFT_VM_DETECTED                  0xE000070D  // CH: 程序在虚拟机运行 | EN: The program is running in a virtual machine
#define   IMVS_EC_ENCRYPT_SOFT_FEATURE_NOT_FOUND            0xE000070E  // CH: 功能未找到 | EN: Feature not found
#define   IMVS_EC_ENCRYPT_SOFT_INNERIMPL_ERROR              0xE000070F  // CH: 内部实现错误 | EN: Internal implementation errors
#define   IMVS_EC_ENCRYPT_SOFT_PRODUCT_NOT_FOUND            0xE0000710  // CH: 产品未找到 | EN: The product was not found
#define   IMVS_EC_ENCRYPT_SOFT_RESULTS_EMPTY                0xE0000711  // CH: 查询结果为空 | EN: The query result is empty
#define   IMVS_EC_ENCRYPT_SOFT_ABILITY_OR_RESOURCE          0xE0000712  // CH: 因超出能力集或可用内存资源不足导致获取许可信息失败 | EN: Get license information failure because of beyond the limits of capacity or applying resource failed
#define   IMVS_EC_ENCRYPT_SOFT_FEATURE_FORBIDDEN            0xE0000713  // CH: 机器不满足授权要求而被禁用 | EN: The feature is forbiddened for the machine not satisfied with authorization requirement
#define   IMVS_EC_ENCRYPT_SOFT_HASP_NOT_FOUND               0xE0000714  // CH: 未找到可用的保护锁 | EN: No available production key were found
#define   IMVS_EC_ENCRYPT_SOFT_BROKEN_SESSION               0xE0000715  // CH: 会话已断开，如超时 | EN: Session is disconnected, such as timeout
#define   IMVS_EC_ENCRYPT_SOFT_COMM_ERR                     0xE0000716  // CH: 通信错误 | EN: Communication error
#define   IMVS_EC_ENCRYPT_WITHOUT_DEVELOP_AUTH              0xE0000717  // CH: 没有开发狗权限 | EN: Without development authority  
#define   IMVS_EC_ENCRYPT_CAMERA_COUNT_BEYOND               0xE0000718  // CH: 相机模块数量超出限制 | EN: The number of camera modules is out of limit  
#define   IMVS_EC_ENCRYPT_KEY_INDOG_WRONG                   0xE0000719  // CH: 校验加密狗中密码失败
#define   IMVS_EC_ENCRYPT_DECRYPT_FAIL_WITH_DOG             0xE000071A  // CH: 使用加密狗解密文件失败
#define   IMVS_EC_ENCRYPT_REMOTE_DONGLE_CHECK               0xE000071B  // CH: 网络锁校验失败 | EN: Failed to verify remote dongle
#define   IMVS_EC_ENCRYPT_REMOTE_DONGLE_MAX_CONNECTION      0xE000071C  // CH: 网络锁已达到最大并发授权 | EN: Maximum connections of remote dongle is reached


/****************************************************************************
 * 用户权限错误 0xE0000800~0xE00008FF
 * User authority errors 0xE0000800~0xE00008FF
 ****************************************************************************/
#define   IMVS_EC_AUTH_SOLU_PASSWORD                        0xE0000800  // CH: 方案密码错误 | EN: Incorrect solution password
#define   IMVS_EC_AUTH_USER_PASSWORD                        0xE0000801  // CH: 用户或密码错误(预留) | EN: Incorrect user name or password (reserved)
#define   IMVS_EC_AUTH_REMOTE_NO_PASSWORD                   0xE0000802  // CH: 远程连接需设置密码
#define   IMVS_EC_AUTH_REMOTE_PASSWORD_INVALID              0xE0000803  // CH: 远程连接密码错误
#define   IMVS_EC_AUTH_ORIGINAL_PASSWORD_INVALID            0xE0000804  // CH: 原密码错误
#define   IMVS_EC_AUTH_ASSWORD_IS_EXIST                     0xE0000805  // CH: 密码已存在
#define   IMVS_EC_AUTH_USER_LOCKOUT	                        0xE0000806  // CH: 用户锁定
#define   IMVS_EC_AUTH_NO_LOGINUSER_DATABASE_FILE           0xE0000807  // CH: 没有登录用户数据文件


/****************************************************************************
 * 警告信息 0xE0000900~0xE00009FF
 * Warning message errors 0xE0000900~0xE00009FF
 ****************************************************************************/
#define   IMVS_EC_WARN_MODULE_INPUT_SUB                     0xE0000900  // CH: 模块输入未订阅 | EN: The module input is not subscribed
#define   IMVS_EC_WARN_ALGORITHM                            0xE0000901  // CH: 算法库中出现警告 | EN: Warning occurred in algorithm library


/****************************************************************************
 * 模块数据上报 0xE0001000~0xE00010FF
 * Module data escalation errors 0xE0001000~0xE00010FF
 ****************************************************************************/
#define   IMVS_EC_MODULE_ALGORITHM_INIT                     0xE0001000  // CH: 模块算法类初始化结果 | EN: Algorithmic initialization result of module
#define   IMVS_EC_MODULE_REPORT_CODE						0xE0001001  // CH: 模块错误码上报 | EN: Report Error Code

/****************************************************************************
 * 模型相关错误 0xE0001100~0xE00011FF
 * Model-related errors 0xE0001100~0xE00011FF
 ****************************************************************************/
#define   IMVS_EC_MODEL_OPEN                                0xE0001100  // CH: 模型无法打开 | EN: Model can't be opened
#define   IMVS_EC_MODEL_NOT_FOUND                           0xE0001101  // CH: 模型不存在 | EN: Model does not exist
#define   IMVS_EC_MODEL_FORMAT                              0xE0001102  // CH: 模型格式错误 | EN: Model format is wrong
#define   IMVS_EC_MODEL_BE_OCCUPIED                         0xE0001103  // CH: 模型文件被占用 | EN: Model file is occupied
#define   IMVS_EC_MODEL_DATA                                0xE0001104  // CH: 模型数据异常 | EN: Model data anomalies
#define   IMVS_EC_MODEL_DATA_LENGTH                         0xE0001105  // CH: 模型数据长度异常 | EN: The length of model data is abnormal
#define   IMVS_EC_GET_ROI_FROM_MODEL_FAIL                   0xE0001106  // CH: 从模型中获取ROI失败 | EN: Failed to get ROI from the model file

/****************************************************************************
* 代理相关错误 0xE0001200~0xE00012FF
* Model-related errors 0xE0001100~0xE00011FF
****************************************************************************/
#define   IMVS_EC_PROXY_LACK_BINARYDATA                     0xE0001200  // CH: 缺少二进制数据(需要外部输入数据) | EN: Lack the binary data
#define   IMVS_EC_PROXY_LACK_BINARYMEMORY                   0xE0001201  // CH: 缺少二进制内存(需要外部申请内存) | EN: Lack the binary memory

#endif//end _IMVS_6000_ERROR_CODE_DEFINE_H_
