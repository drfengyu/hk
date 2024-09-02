/************************************************************************
* 版权信息：版权所有(c) 2018, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：VmModuleDef.h
* 摘   要:  定义SDK公共数据结构
*
* 作   者:  fenghuapeng5
* 日   期： 2018-09-10
* 备   注： 
************************************************************************/ 

#ifndef _VM_MODULE_DEF_H_
#define _VM_MODULE_DEF_H_

#ifdef _MSC_VER
typedef __int32          int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64          int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#ifndef _WIN32
#define __stdcall
#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifndef NULL
#define NULL 0
#endif

//输入输出名称长度
#define MAX_IO_NAME_LEN  128

//关键字名称长度
#define MAX_KEY_NAME_LEN 260

//模块参数值最大长度
#define PARAM_VALUE_LEN 1024

//模块参数最大数量
#define MAX_PARAM_NUM  256

//流程名称长度
#define PROCEDURE_NAME_LEN 64

//模块名称长度
#define MODULE_NAME_LEN 64

//模块显示名称长度
#define MODULE_DISPLAY_NAME_LEN 64

//模块显示名称长度
#define MODULE_DISPLAY_NAME_LEN_EX 256

//模块后继节点最大数目
#define MAX_SUCCESSOR_NUM 256

//常量订阅值最大长度
#define MAX_CONSTANT_VALUE_LEN 256

//自定义命令行参数长度
#define MAX_ARG_STRING_LEN 256

//用户二进制数据块最大数量
#define MAX_USER_BINARY_BLOCK_BUM 128

//单次订阅数组长度
#define SUBSCRIBE_NUM 128

//自定义输出字段列表大小
#define CUSTOM_OUTPUT_PAGE_SIZE 10

//模块错误信息列表大小
#define MODULE_ERRLIST_SIZE 128

//最大CPU核心个数
#define MAX_CORE_NUM 64

//流程运行策略数组大小
#define MAX_RUN_POLICY_NUM 32

//GUID数组长度
#define GUID_LEN 40

// 每次查询的历史结果数量
#define HISTORY_RST_PAGE_SIZE 50

// 流程触发命令长度
#define TRIGGER_CMD_LEN 16

// 共享内存名称长度
#define SHARED_MEM_NAME_LEN 64

typedef struct
{
	char byParamName[MAX_KEY_NAME_LEN]; // 参数名
	char byReserve[128];                // 保留
}PARAM_INFO;

//VM版本信息
enum eVmVersion : int
{
	VM_VERSION_INVALID = 0,
	VM_VERSION_310     = 1,
	VM_VERSION_320     = 2,
	VM_VERSION_330     = 3,
	VM_VERSION_331     = 4,
	VM_VERSION_340     = 5,
	VM_VERSION_400     = 6,
	VM_VERSION_420     = 7,
    VM_VERSION_421     = 8,
    VM_VERSION_4220    = 9,
    VM_VERSION_430     = 10,
	VM_VERSION_DEFAULT = 127
};

//VM进程模式
enum eVmProcessMode : int
{
    VM_PROCESS_MODE_MULTI  = 0,     //多进程模式
    VM_PROCESS_MODE_SINGLE = 1      //单进程模式
};

typedef struct
{
	char         byModulePath[512]; // 模块存放目录。为空时，则默认在当前SDK路径：SDK_PATH/Module下查找模块。
	char         byLogPath[512];    // 日志存放目录。为空时，则默认在当前SDK路径下。
	char         byCharset;         // 0-ansi字符，1-utf8字符。
    char         byVersion;         // 迭代版本，参见eVmVersion。非VM应用,置VM_VERSION_DEFAULT即可。
    char         byPreload;         // 预加载模块，0-不启用，1-启用。非特别关注模块创建时间情形下不要开启，否则会多消耗一些内存。
    char         byProcessMode;     // 进程模式，参见eVmProcessMode
    char         byMinCoreNum;      // 启用高性能的最小核数
    const char*  szLoadModuleDataTempPath;    // 模块加载数据临时文件路径，放临时图像、深度学习模型
    char         byLogMode;         // 日志模式 1-异步 0-同步
    char         byReserve[239];    // 保留
}INITIALIZE_PARAM;


typedef struct
{   
	int nNum;                                // 有效参数个数
	PARAM_INFO struParamList[MAX_PARAM_NUM]; // 参数列表
	char byReserve[128];                     // 保留
}PARAM_INFO_LIST;


typedef struct
{
	char byParamName[MAX_KEY_NAME_LEN]; // 参数名
	char byParamValue[PARAM_VALUE_LEN]; // 参数值
	char byReserve[128];                // 保留
}PARAM_VALUE_INFO;


typedef struct
{   
	int nNum;                                       // 有效参数个数
	PARAM_VALUE_INFO paramValueList[MAX_PARAM_NUM]; // 参数列表
	char byReserve[128];                            // 保留
}PARAM_VALUE_INFO_LIST;


enum eCUSTOM_USERDATA_TYPE : int
{
	USERDATA_INVALID = 0, // 无效
	USERDATA_BINARY  = 1, // 二进制数据
};


typedef struct 
{
	char  byName[MAX_KEY_NAME_LEN]; // 数据块名称
	char* pUserData;                // 二进制数据           
	int   nDataLen;                 // 二进制数据长度
}USER_BINARY_DATA;


typedef struct  
{
	int nNum;                                                    // 数据块数量
	USER_BINARY_DATA struBinaryData[MAX_USER_BINARY_BLOCK_BUM];  // 用户自定义二进制数据块
	char byReserve[64];                                          // 保留
}USER_BINARY_DATA_LIST;


// 保存方案数据结束时，通知回调
typedef int (__stdcall *pFnSigFinishedCallback)(void* pUserData);

typedef struct 
{
	eCUSTOM_USERDATA_TYPE eUserDataType; // 用户自定义数据格式，取值参见CUSTOM_USERDATA_TYPE。若没有自定义数据，置为USERDATA_INVALID。
	union
	{
        USER_BINARY_DATA_LIST struBinaryDataList;  // 用户自定义二进制数据
		char byReserved[34372];                    // 联合体大小
	}uUserData;
}CUSTOM_USER_DATA;


typedef struct
{   
	PARAM_VALUE_INFO_LIST struParamValueList;   // 算法参数列表
	CUSTOM_USER_DATA      struCustomUserData;   // 用户自定义数据
	char*                 pszAttachmentsDir;    // 方案中的附件文件路径。如保存时可将图片等其他文件拷贝至此目录下，
	                                            // 加载时可再从此目录下读取保存的文件。注意判断是否为NULL，为NULL时，
	                                            // 请将文件数据保存至struCustomUserData标识的自定义数据块参数中。
	char                  byReserved[56];       // 保留
}MODULE_DATA;


typedef struct  
{
	MODULE_DATA struModuleData;            // 模块数据
	pFnSigFinishedCallback pfnSigCallback; // 保存方案完成时，通知回调。可以在此函数中释放因保存方案而申请的资源。若不用，置为NULL即可。
	void* pSigUserData;                    // 为回调函数传入的自定义数据。若不用，置为NULL即可。
	char byReserved[128];                  // 保留
}SAVE_MODULE_DATA_PARAM;


typedef struct  
{
	MODULE_DATA struModuleData;  // 模块数据
	char byReserved[128];        // 保留
}LOAD_MODULE_DATA_PARAM;


typedef struct
{
	char*        pImgData;        // 图片数据
	unsigned int nImgDataLen;     // 图片长度
	char         byCopyMode;      // 0-深拷贝，1-浅拷贝
	char         byReserved[127]; // 保留     
}IMAGE_DATA;

typedef struct
{
    char*        pImgData;        // 图片数据
    unsigned int nImgDataLen;     // 图片长度
    char         byCopyMode;      // 0-深拷贝，1-浅拷贝
    char         chSharedMemoryName[SHARED_MEM_NAME_LEN];
    char         byReserved[127]; // 保留     
}IMAGE_DATA_V2;

typedef struct 
{
	int  nProcedureId;                        // 流程ID
	char byProcedureName[PROCEDURE_NAME_LEN]; // 流程名称
	char byReserve[256];                      // 保留
}CREATE_PROCEDURE_PARAM;


typedef struct 
{
	char byProcedureName[PROCEDURE_NAME_LEN]; // 流程名称
	char byExcludeFromAll;                    // 流程屏蔽，0-关闭，1-开启
	char byReserve[255];                      // 保留
}UPDATE_PROCEDURE_PARAM;


typedef struct 
{
	int  nProcedureId;                           // 流程ID
	int  nModuleId;                              // 模块ID
	char byModuleName[MODULE_NAME_LEN];          // 模块名称
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 模块显示名称
	char byGuid[GUID_LEN];                       // guid信息
	char byReserve[472];                         // 保留
}ADD_MODULE_PARAM;


typedef struct
{
	int  nProcedureId;                           // 流程ID
	int  nModuleId;                              // 模块ID
	char byModuleName[MODULE_NAME_LEN];          // 模块名称
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 模块显示名称
	char byReserve[512];                         // 保留
}MODULE_INFO;


typedef struct 
{
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 模块显示名称
	char byReserve[256];                         // 保留
}UPDATE_MODULE_PARAM;

typedef struct
{
	char byEnable;        // 模块是否可用，0-禁用，非0-启用  
	char byUploadRst;     // 是否上报结果，0-禁用，非0-上报
	char byReserve[254];  // 保留
}MODULE_STATE;

typedef struct  
{
	ADD_MODULE_PARAM struModuleParam; // 模块参数
	MODULE_STATE     struModuleState; // 模块状态
	char             byReserve[256];  // 保留
}BATCH_ADD_MODULE_PARAM;

typedef struct  
{
	int  nProcedureId;     // 流程Id
	int  nLoopId;          // 循环Id
	char byEnable;         // 启用性，0-禁用，非0-启用  
	char byGuid[GUID_LEN]; // GUID
	char byReserve[215];   // 保留
}BATCH_ADD_LOOP_PARAM;

typedef struct
{
	int  nProcedureId;     // 流程Id
	int  nLoopId;          // 循环Id
	char byGuid[GUID_LEN]; // GUID
	char byReserve[512];   // 保留
}ADD_LOOP_PARAM_EX;

typedef struct
{
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 模块显示名称
	int  nType;                                  // 模块类型
	char byReserve[256];                         // 保留
}MODULE_CONFIG_PARAM;


typedef enum : int
{
	FIELD_TYPE_INVALID   = 0,  // 无效
	FIELD_TYPE_INT       = 1,  // 整形
	FIELD_TYPE_FLOAT     = 2,  // 浮点
	FIELD_TYPE_STRING    = 3,  // 字符串
	FIELD_TYPE_IMAGE     = 4,  // 图像
	FIELD_TYPE_POINTSET  = 5,  // 点集
	FIELD_TYPE_BYTEARRAY = 6   // 二进制块
}eFIELD_TYPE;


struct  MODULE_PARAM
{  
	int  nModuleId;                     // 模块ID
	char byParamName[MAX_IO_NAME_LEN];  // 参数名
	char byReserve[64];                 // 保留
};

typedef MODULE_PARAM MODULE_SRC_PARAM;


// 被订阅模块变量的索引类型
enum eVAR_INDEX_TYPE : int
{
	VAR_INDEX_INVALID  = 0,  // 无效
	VAR_INDEX_ALL      = 1,  // 常量全部
	VAR_INDEX_CONSTANT = 2,  // 常量索引
	VAR_INDEX_VARIABLE = 3   // 变量
};

// 被订阅变量值类型
enum eVAR_TYPE_TYPE : int
{
	VAR_VALUE_INVAlID  = 0,  // 无效
	VAR_VALUE_CONSTANT = 1,  // 常量
	VAR_VALUE_GLOBAL   = 2,  // 全局字符串
	VAR_VALUE_VARIABLE = 3   // 变量
};

typedef struct
{   
	eVAR_INDEX_TYPE eIndexType;    // 索引类型，数组订阅时有效。当为VAR_INDEX_INVALID时，表示非数组订阅，字段uVarIndex无效。
	union
	{
		int nConstant;            // 常量索引值
		MODULE_PARAM indexVar;    // 变量索引值
	}uVarIndex;
	MODULE_PARAM struModuleParam; // 被订阅模块变量
}VARIABLE_VALUE;


typedef struct
{
	eVAR_TYPE_TYPE eVarType;                           // 被订阅变量类型
	union
	{
		char szConstantValue[MAX_CONSTANT_VALUE_LEN]; // 常量
		VARIABLE_VALUE struVariableValue;             // 变量
	}uVarValue;
	char byReserve[64];                               // 保留
}MODULE_DST_PARAM;


typedef struct  
{
	MODULE_SRC_PARAM struSrcParam; // 源变量
	MODULE_DST_PARAM struDstParam; // 被订阅变量
	char byReserve[64];            // 保留
}SUBSCRIBE_PARAM;


typedef struct  
{
	int nNum;                                             // 有效订阅的字段个数
	SUBSCRIBE_PARAM subscribeParamList[SUBSCRIBE_NUM];    // 订阅字段列表
	char byReserve[128];                                  // 保留
}SUBSCRIBE_PARAM_LIST;


typedef struct  
{
	int nNum;                             // 有效ID数量
	int nModuleIdList[MAX_SUCCESSOR_NUM]; // 模块ID列表
	char byReserve[64];                   // 保留
}LOOP_NODE_LIST;


typedef struct
{
	int nParentLoopId;                    // 父循环ID
	int nStartIndex;                      // 起始索引，从0开始
	int nStopIndex;                       // 结束索引
	int nInterval;                        // 循环运行间隔（单位：毫秒）
	LOOP_NODE_LIST struInnerHeadList;     // 循环内部首节点列表
	LOOP_NODE_LIST struInnerTailList;     // 循环内部首节点列表
	LOOP_NODE_LIST struOuterHeadList;     // 循环外部首节点列表
	LOOP_NODE_LIST struOuterTailList;     // 循环外部尾节点列表
	char byReserve[128];                  // 保留
}LOOP_INFO;


typedef struct 
{
	int  nModuleId;                              // 模块ID
	char byModuleName[MODULE_NAME_LEN];          // 模块名称
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 模块显示名称
}NEXT_MODULE_INFO;


typedef struct  
{
	int nNum;                                           // 有效个数
	NEXT_MODULE_INFO struModuleList[MAX_SUCCESSOR_NUM]; // 后继模块列表
	char byReserve[128];                                // 保留
}NEXT_MODULE_INFO_LIST;


typedef struct
{
	char byValid;           // 是否有效。0-无效，1-有效
	char byReserve1[3];     // 保留
	int  nLoopIndex;        // 循环当前已执行次数
	int  nLoopTimes;        // 循环总次数，当nLoopIndex=nLoopTimes时表示循环结束
	char byReserve2[128];   // 保留           
}LOOP_RUN_INFO;


typedef struct  
{
	float fAlgorithmTime;       // 算法时间
	float fGetTime;             // Process get时间
	float fSetTime;             // Process set时间
	double fRunBeginTime;       // 模块开始运行时间戳，单位：毫秒（只读，获取时有效）
	double fRunEndTime;         // 模块结束运行时间戳，单位：毫秒（只读，获取时有效）
	LOOP_RUN_INFO struLoopInfo; // 模块直属循环信息（只读，获取时有效）
	unsigned int nExecuteId;    // 当前流程执行ID(只读）
	char  byReserve[512];       // 保留
}MODULE_RUNTIME_INFO;


typedef struct
{
	int  nProcedureId;                           // 模块所属流程ID
	int  nModuleId;                              // 模块ID
	char szModuleName[MODULE_NAME_LEN];          // 模块名称
	char szDisplayName[MODULE_DISPLAY_NAME_LEN]; // 显示名称
	char szGuid[GUID_LEN];                       // GUID
	char byReserve1[216];                        // 保留
	int  nType;                                  // 模块类型
	int  nErrCode;                               // 模块初始化完成，错误码
	char byReserve2[128];                        // 保留
}ADD_MODULE_FINISHED_PARAM;


typedef struct 
{
	int  nErrCode;                       // 错误码
	int  nModuleId;                      // 模块ID
	char byModuleName[MODULE_NAME_LEN];  // 模块名称
	char byReserve[128];                 // 保留
}MODULE_ERR_INFO;

typedef struct  
{
	int nNum;                                          // 有效信息个数
	MODULE_ERR_INFO struErrInfo[MODULE_ERRLIST_SIZE];  // 错误信息列表;
	char byReserve[128];                               // 保留
}MODULE_ERR_INFO_LIST;


typedef struct  
{
	int                  nFrameErrCode;      // 模块框架错误码，非0时表示不可继续的错误。模块具体出错信息请查阅成员struModuleErrList
	MODULE_ERR_INFO_LIST struModuleErrList;  // 模块错误信息列表
	char                 byReserve[256];     // 保留
}BATCH_ADD_MODULE_FINISHED_PARAM;


enum ePROCEDURE_STATUS : int
{
	PROCEDURE_STATUS_INVALID   = 0, // 无效，未知
	PROCEDURE_STATUS_FREE      = 1, // 空闲
	PROCEDURE_STATUS_BUSY      = 2, // 忙碌
	PROCEDURE_STATUS_STOPPED   = 3  // 停止
};

enum ePROCEDURE_STOP_ACTION : int
{
	PROCEDURE_STOPPED_INVALID   = 0, //  无效
	PROCEDURE_STOPPED_NORMAL    = 1, //  正常停止
	PROCEDURE_STOPPED_NG        = 2, //  流程NG
	PROCEDURE_STOPPED_BYMODULE  = 3  //  模块请求停止流程
};

typedef struct  
{
	int nProcedureId;                   // 流程ID
	ePROCEDURE_STATUS nProcedureStatus; // 流程状态
	float  fProcedureTime;              // 流程执行耗时，单位：毫秒（当nProcedureStatus为 PROCEDURE_STATUS_FREE 时有效）
	unsigned int nExecuteCount;         // 流程执行次数
	ePROCEDURE_STOP_ACTION nStopAction; // 流程停止的原因（当nProcedureStatus为 PROCEDURE_STATUS_STOPPED 时有效）
	char byTriggerCmd[TRIGGER_CMD_LEN]; // 流程触发命令
	char byReserve[104];                // 保留
}PROCEDURE_STATUS_PARAM;


typedef struct
{
	int   nModuleId;       // 模块ID
	int   nType;           // 数据类型，由用户定义，SDK透传
	char* pData;           // 用户数据，空间由SDK分配
	int   nDataLen;        // 用户数据长度
	char  byReserve[128];  // 保留
}MODULE_REPORT_DATA_PARAM;

typedef struct
{
	int  nInterval;       // 流程运行间隔（单位：毫秒）
	char byContinuousRun; // 是否在连续运行，1-是，0-否(只读)
	char byStopWhenNG;    // 流程NG时停止运行,1-是，0-否
	int  nFlag;           // 表示哪些值有效，按位取或值。0x00-表示所有，0x01-nInterval有效，0x02-byContinuousRun有效，0x04-byStopWhenNG有效，0x08-nWaitTime有效。
	int  nWaitTime;       // 流程超时时间（单位：毫秒），默认为0表示不设超时限定
	char byReserve[502];  // 保留
}PROCEDURE_RUNNING_PARAM;

typedef struct  
{
	int  nModuleId;                      // 模块ID
	char szModuleName[MODULE_NAME_LEN];  // 模块名称
	int  nErrCode;                       // 错误码
	char byReserve[256];                 // 保留
}LOAD_MODULE_FINISHED_PARAM;

typedef struct  
{
	int  nModuleId;                      // 模块ID
	char szModuleName[MODULE_NAME_LEN];  // 模块名称
	int  nErrCode;                       // 错误码
	char byReserve[256];                 // 保留
}SAVE_MODULE_FINISHED_PARAM;


typedef struct  
{
	int  nErrCode;                       // 错误码
	char byReserve[256];                 // 保留
}LOAD_SOLUTION_FINISHED_PARAM;

//导出文件时的参数数据
typedef struct
{
    char     szName[256]; // 名称，内部使用的是wchar[128]
    char*    pData;       // 二进制数据
    int      nDataLen;    // 数据长度
}EXPORT_DATA_IN_FILE;

typedef struct  
{
	int                  nErrCode;       // 错误码
    char                 szHeader[8];    // 头信息，包括版本和数量
    int                  nDataNum;       // 数据个数
    EXPORT_DATA_IN_FILE* pstData;        // 二进制数据指针
	char byReserve[236];                 // 保留
}SAVE_SOLUTION_FINISHED_PARAM;

typedef EXPORT_DATA_IN_FILE IMPORT_DATA_IN_FILE;

typedef struct
{
    int nSolVersion;
    int nModuleNum;
    IMPORT_DATA_IN_FILE* pstData;
    char byReserve[128];
}FILE_IMPORT_DATA;

typedef struct
{
	int  nErrCode;                       // 错误码
	char byReserve[256];                 // 保留
}IMPORT_GROUP_FINISHED_PARAM;

typedef struct
{
    int                  nErrCode;       // 错误码
    char                 szHeader[8];    // 头信息，包括版本和数量
    int                  nDataNum;       // 数据个数
    EXPORT_DATA_IN_FILE* pstData;        // 二进制数据指针
    char byReserve[236];                 // 保留
}EXPORT_GROUP_FINISHED_PARAM;


typedef struct
{
	int  nErrCode;                       // 错误码
	char byReserve[256];                 // 保留
}IMPORT_PROCEDURE_FINISHED_PARAM;

typedef struct
{
    int                  nErrCode;       // 错误码
    char                 szHeader[8];    // 头信息，包括版本和数量
    int                  nDataNum;       // 数据个数
    EXPORT_DATA_IN_FILE* pstData;        // 二进制数据指针
    char byReserve[236];                 // 保留
}EXPORT_PROCEDURE_FINISHED_PARAM;

enum eCLOSE_SOLUTION_STATE : int
{
	CLOSE_SOLUTION_INVALID = 0,          // 无效
	CLOSE_SOLUTION_BEIGN   = 1,          // 关闭开始
	CLOSE_SOLUTION_FINISH  = 2           // 关闭完成
};

enum eCREATE_MODULE_CAUSE : int
{
	CREATE_CAUSE_INVALID  = 0,  // 无效
	CREATE_CAUSE_ADDONE   = 1,  // 普通添加
	CREATE_CAUSE_LOADSOL  = 2   // 加载方案
};

typedef struct  
{
	eCLOSE_SOLUTION_STATE nState;       // 关闭方案状态
	char byReserve[256];                // 保留
}CLOSE_SOLUTION_STATE_PARAM;

typedef struct 
{
	eFIELD_TYPE nOutputType;             // 输出字段类型
	char byOutputName[MAX_IO_NAME_LEN];  // 输出字段名
	MODULE_DST_PARAM  struDstParam;      // 订阅值
	char byReserve[64];                  // 保留
}CUSTOM_OUTPUT_RECORD;

typedef struct
{
	int nNum;                                                     // 有效个数
	CUSTOM_OUTPUT_RECORD struOutputList[CUSTOM_OUTPUT_PAGE_SIZE]; // 自定义输出字段列表
}CUSTOM_OUTPUT_RECORD_LIST;

typedef struct
{
	char byEnableUploadRst; // 是否上传模块结果，0-否，1-是
	char byEnableBranch;    // 是否启用分支功能，0-否，1-是
	char byReserve1[6];     // 保留1
	char byReserve2[1024];  // 保留2
}RUNNING_CONTROL_PARAM;

typedef struct
{
	char* pszTriggerCmd;   // 触发字符串
	char  byReserve[256];  // 保留
}RUN_PROCEDURE_INPUT;

typedef struct
{
	unsigned int nExecuteCount; // 当前流程执行次数
	char  byReserve[256];       // 保留
}RUN_PROCEDURE_OUTPUT;

typedef struct
{
	char byCpuCore[MAX_CORE_NUM]; // CPU核数组，0-无效，1-有效。
	                              // byCpuCore[0]表示cpu0、byCpuCore[1]表示cpu1, byCpuCore[2]表示cpu2...
	char byReserve[32];           // 保留
}CPU_AFFINITY;

typedef struct
{
	int          nProcedureId;     // 流程id
	int          nThreadNum;       // 针对流程(id=nProcedureId),指定其执行线程数目
	CPU_AFFINITY struCpuAffinity;  // 针对流程(id=nProcedureId),指定运行的CPU核心。
	char         byReserve[64];    // 保留
}PROCEDURE_CUSTOM_RUNNING_POLICY;

typedef struct
{
	int nNum;                                           // 有效个数
	PROCEDURE_CUSTOM_RUNNING_POLICY struPolicyList[MAX_RUN_POLICY_NUM]; // 运行配置
	char byReserve[256];                                // 保留
}PROCEDURE_CUSTOM_RUNNING_POLICY_LIST;


enum ePROCEDURE_RUN_POLICY : int
{
	PROCEDURE_RUN_POLICY_INVALID         = 0, // 无效
	PROCEDURE_RUN_POLICY_HIGH_SPEED      = 1, // 快速运行模式（默认）
	PROCEDURE_RUN_POLICY_CUSTOM          = 2, // 用户自定义运行方式
	PROCEDURE_RUN_POLICY_TIME_STABILITY  = 3  // 保证耗时稳定性
};

typedef struct  
{
	ePROCEDURE_RUN_POLICY nRunPolicy; // 流程运行方式
	union
	{
		PROCEDURE_CUSTOM_RUNNING_POLICY_LIST struCustom; // 当nRunPolicy为 PROCEDURE_RUN_POLICY_CUSTOM 时有效
	}uPolicy;
	int  nCustomIndex;   // 当nRunPolicy为 PROCEDURE_RUN_POLICY_CUSTOM时有效。获取时，当流程数量大于MAX_RUN_POLICY_NUM时，指定取值起始索引
	char byReserve[252]; // 保留
}PROCEDURE_RUNNING_POLICY;


typedef struct
{
	ePROCEDURE_RUN_POLICY nRunPolicy; // 流程运行方式
	union
	{
		PROCEDURE_CUSTOM_RUNNING_POLICY struCustom; // 当nRunMode为 PROCEDURE_RUN_POLICY_CUSTOM 时有效
	}uPolicy;
	char byReserve[256]; // 保留
}MODULE_OWNER_PROCEDURE_RUNNING_POLICY;


typedef struct  
{
	int  nLogicProcessorNum; // 逻辑处理器个数
	char byReserve1[4];      // 保留
	char byReserve2[512];    // 保留
}PROCESSOR_INFO;


typedef struct
{
	int  nProcedureId;                           // 流程ID
	int  nGroupId;                               // Group ID
	char byDisplayName[MODULE_DISPLAY_NAME_LEN]; // 显示名称
	char byGuid[GUID_LEN];                       // guid信息
	char byReserve[512];                         // 保留
}ADD_GROUP_PARAM;


typedef struct
{
	ADD_GROUP_PARAM  struGroupParam; // Group参数
	MODULE_STATE     struGroupState; // Group状态
	char             byReserve[256];  // 保留
}BATCH_ADD_GROUP_PARAM;

typedef struct 
{
	int nGlobalModuleId;                    // 全局变量模块ID
	eFIELD_TYPE nGlobalVarType;             // 全局变量类型
	char byGlobalVarName[MAX_IO_NAME_LEN];  // 全局变量名称
	MODULE_DST_PARAM struDstValue;          // 全局变量绑定值
	char byReserve[256];                    // 保留
}BIND_GLOBALVAR_PARAM;

typedef struct  
{
	int nGlobalModuleId;                    // 全局变量模块ID
	eFIELD_TYPE nGlobalVarType;             // 全局变量类型
	char byGlobalVarName[MAX_IO_NAME_LEN];  // 全局变量名称
	char byReserve[256];                    // 保留
}UNBIND_GLOBALVAR_PARAM;

typedef struct  
{
	eFIELD_TYPE nVarType;   // IO类型
	char byName[MAX_IO_NAME_LEN]; // IO名称
	char byReserve[256];          // 保留
}GROUP_IO_FIELD_PARAM;

typedef GROUP_IO_FIELD_PARAM PROCEDURE_IO_FIELD_PARAM;


typedef struct
{
	int  nSize;          // 分配内存大小,字节数
	int  nAlignment;     // 按多少字节对齐(4 / 8 / 16 / 32 / 64 / 128 / 256)
	int  nAttrs;         // 按算法库定义取值：0-可复用内存, 1-不可复用内存, 2-动态内存Dynamic DDR
	int  nPlat;          // 按算法库定义取值：1-CPU内存,2-GPU内存
	char byReserve[256]; // 保留
}ALLOC_MEM_IN_POOL_INPUT;


typedef struct
{
	int  nProcedureId;                              // 流程ID
	int  nModuleId;                                 // 模块ID
	char byModuleName[MODULE_NAME_LEN];             // 模块名称
	char byGuid[GUID_LEN];                          // guid信息
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 模块显示名称
	char byReserve[512];                            // 保留
}ADD_MODULE_PARAM_EX;


typedef struct
{
	ADD_MODULE_PARAM_EX struModuleParam; // 模块参数
	MODULE_STATE        struModuleState; // 模块状态
	char                byReserve[256];  // 保留
}BATCH_ADD_MODULE_PARAM_EX;


typedef struct
{
	int  nProcedureId;                              // 流程ID
	int  nModuleId;                                 // 模块ID
	char byModuleName[MODULE_NAME_LEN];             // 模块名称
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 模块显示名称
	char byReserve[512];                            // 保留
}MODULE_INFO_EX;


typedef struct
{
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 模块显示名称
	char byReserve[256];                            // 保留
}UPDATE_MODULE_PARAM_EX;

typedef struct
{
	int  nType;                                     // 模块类型
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 模块显示名称
	char byReserve[256];                            // 保留
}MODULE_CONFIG_PARAM_EX;


typedef struct
{
	int  nModuleId;                                 // 模块ID
	char byModuleName[MODULE_NAME_LEN];             // 模块名称
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 模块显示名称
	char byReserve[256];                            // 保留
}NEXT_MODULE_INFO_EX;

typedef struct
{
	int nNum;                                              // 有效个数
	NEXT_MODULE_INFO_EX struModuleList[MAX_SUCCESSOR_NUM]; // 后继模块列表
	char byReserve[128];                                   // 保留
}NEXT_MODULE_INFO_LIST_EX;


typedef struct
{
	int  nProcedureId;                              // 模块所属流程ID
	int  nModuleId;                                 // 模块ID
	char szModuleName[MODULE_NAME_LEN];             // 模块名称
	int  nType;                                     // 模块类型
	char szGuid[GUID_LEN];                          // GUID
	char szDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 显示名称
	int  nErrCode;                                  // 模块初始化完成，错误码
	char byReserve[512];                            // 保留
}ADD_MODULE_FINISHED_PARAM_EX;


typedef struct
{
	int  nProcedureId;                              // 流程ID
	int  nGroupId;                                  // Group ID
	char byGuid[GUID_LEN];                          // guid信息
	char byDisplayName[MODULE_DISPLAY_NAME_LEN_EX]; // 显示名称
	char byReserve[512];                            // 保留
}ADD_GROUP_PARAM_EX;

typedef struct
{
	ADD_GROUP_PARAM_EX  struGroupParam; // Group参数
	MODULE_STATE        struGroupState; // Group状态
	char                byReserve[256];  // 保留
}BATCH_ADD_GROUP_PARAM_EX;

typedef struct
{
	int  nErrCode;                                   // 错误码
	int  nModuleId;                                  // 模块ID
	char byModuleName[MODULE_NAME_LEN];              // 模块名称
	char byDispalyName[MODULE_DISPLAY_NAME_LEN_EX];  // 显示名称
	char byReserve[128];                             // 保留
}MODULE_ERR_INFO_EX;

typedef struct
{
	int nNum;                                          // 有效信息个数
	MODULE_ERR_INFO_EX struErrInfo[MODULE_ERRLIST_SIZE];  // 错误信息列表;
	char byReserve[128];                               // 保留
}MODULE_ERR_INFO_LIST_EX;


typedef struct
{
	int                     nFrameErrCode;      // 模块框架错误码，非0时表示不可继续的错误。模块具体出错信息请查阅成员struModuleErrList
	MODULE_ERR_INFO_LIST_EX struModuleErrList;  // 模块错误信息列表
	char                    byReserve[256];     // 保留
}BATCH_ADD_MODULE_FINISHED_PARAM_EX;


typedef struct  
{
	int  nModuleId;      // 当前模块Id
	int  nOriModuleId;   // 映射前模块Id
	char byReserve[128]; // 保留 
}MODULE_MAPPING;


typedef struct
{
	int  nModuleId;     // 模块ID
	char byReserve[4];  // 保留
}SELECTED_MODULE;


typedef struct
{
	int  nIndex;         // 起始索引
	int  nRequestNum;    // 请求数量，每次不要超过HISTORY_RST_PAGE_SIZE大小
    bool bRetImageData;  // 查询是是否返回图像数据
    char byReserve[28];  // 保留
}MODULE_HISTORY_INPUT;

typedef struct
{
	char* pData;         // 结果数据
	int   nLen;          // 长度
	char  byReserve[4];  // 保留
}SINGLE_MODULE_RESULT;

typedef struct
{
	SINGLE_MODULE_RESULT struModuleRst[HISTORY_RST_PAGE_SIZE]; // 历史结果数组
	int   nReturnNum;        // 返回的结果数量
	int   nTotalNum;         // 结果总数
    bool  bRetImageData;     // 是否返回Image数据内容
    char  byReserve[28];     // 保留
}MODULE_HISTORY_RESULT;


// 定义模块的执行结果
enum eMODULE_STATE : int
{
	MODULE_STATE_OK           = 0, // 执行完成，OK
	MODULE_STATE_ERROR        = 1, // 执行完成，ERROR
	MODULE_STATE_BRACH_IGNORE = 2, // 因分支逻辑未执行
	MODULE_STATE_DISABLED     = 3  // 禁用
};

typedef struct
{
	int   nModuleId;             // 模块ID
	eMODULE_STATE nProcessState; // 模块执行状态
	int   nModuleStatus;         // 模块结果状态
	float fAlgorithmTime;        // 算法时间
	float fProcessTime;          // 模块process时间
	float fModuleTime;           // 模块总耗时
	char  byRunFlag;             // 0-流程执行,1-自执行
	char  byReserve[15];         // 保留
}MODULE_STATE_INFO;

typedef struct 
{
    int nProcedureId;// 模块所属流程ID
	int nNum; // 数组大小
	MODULE_STATE_INFO* pModuleInfoList; // 模块状态信息数组，数组大小为nNum指定大小
}MODULE_STATE_INFO_LIST;


typedef struct  
{
	char szInputName[MAX_IO_NAME_LEN]; // 输入名称
	char byUserSet;                    // 0-外部未设置取值; 1-取值由外部设置
	char byReserve[15];
}MODULE_INPUT_STATE;


typedef struct 
{
	char szSolPath[1024]; // 方案路径
	char szSolPwd[64];    // 方案密码
	char byReserve[128];  // 保留
}REQUEST_CHANGE_SOL_PARAM;


typedef struct
{
	int  nDogStatus;    // 0-正常，其它值异常
	int  nCameraLimit;  // 相机数量上限
	char byReserve[32]; // 保留
}CHECK_RUNNING_STATUS;


typedef struct  
{
	int nCameraNum;         // 相机数量
	int cameraIdList[256];  // 相机id列表
}GLOBAL_CAMERA_LIST;


typedef struct
{
	int nModuleId;                      // 模块ID
	char byParamName[MAX_IO_NAME_LEN];  // 参数名称
	eFIELD_TYPE nDstValueType;          // 参数字段类型
	MODULE_DST_PARAM struDstValue;      // 关联绑定值
	char byReserve[64];                 // 保留
}MODULE_PARAM_BINDING;


typedef struct
{
	int nModuleId;                      // 模块ID
	char byParamName[MAX_IO_NAME_LEN];  // 参数名称
	char byReserve[64];                 // 保留
}MODULE_PARAM_UNBINDING;

typedef struct 
{
    int nModuleID;
    int nModuleStatus;
}MODULE_EXECUTE_STATUS;

typedef struct 
{
    int nModuleNum;
    MODULE_EXECUTE_STATUS struModuleStatus[MAX_PARAM_NUM];
    char byReserve[16];                 // 保留
}BATCH_RUN_SELF_STATUS;

typedef struct
{
    char*           pMappingView;
    void*           hMapping;
    unsigned int    uiMappingSize;
    char            chMappingName[SHARED_MEM_NAME_LEN];
}SharedMemoryMappingInfo;

struct SHARED_MEM_HEADER
{
    uint64_t       nSize;          // 实际数据大小，如图片长度
    unsigned char  byLightCopy;     // 0-深拷贝，1-浅拷贝
    unsigned char  byReserve1[5];  // 保留
    unsigned short nHeaderLen;     // 头长度
    char           szSharedMemName[SHARED_MEM_NAME_LEN]; // 共享内存名称
    char           byReserve2[48]; // 保留
};


struct VARPARAM_BESUBJECT_MODULES_RUNPARAM_LIST
{
    int             nTotalNums;                             //总个数
    MODULE_PARAM*   pSubjectInfo;                           //运行参数订阅信息
    char            byReserve2[128]; // 保留
};


// 日志等级
enum eLOG_LEVEL : int
{
	LOG_LEVEL_NONE    = 0,
	LOG_LEVEL_FATAL   = 1,
	LOG_LEVEL_ERROR   = 2,
	LOG_LEVEL_WARNING = 3,
	LOG_LEVEL_INFO    = 4,
	LOG_LEVEL_DEBUG   = 5,
	LOG_LEVEL_VERBOSE = 6
};


// 事件类型
enum eEVENT_TYPE : int
{
	EVENT_INVALID                      = 0,  // 无效
	EVENT_ADD_MODULE_FINISHED          = 1,  // 添加模块完成，事件参数为ADD_MODULE_FINISHED_PARAM_EX
	EVENT_LOAD_MODULE_FINISHED         = 2,  // 加载模块完成，事件参数为LOAD_MODULE_FINISHED_PARAM
	EVENT_SAVE_MODULE_FINISHED         = 3,  // 保存模块完成，事件参数为SAVE_MODULE_FINISHED_PARAM
	EVENT_LOAD_SOLUTION_FINISHED       = 4,  // 加载方案完成，事件参数为LOAD_SOLUTION_FINISHED_PARAM
	EVENT_SAVE_SOLUTION_FINISHED       = 5,  // 保存方案完成，事件参数为SAVE_SOLUTION_FINISHED_PARAM
	EVENT_PROCEDURE_STATUS             = 6,  // 上报流程状态，事件参数为PROCEDURE_STATUS_PARAM
	EVENT_MODULE_REPORT_DATA           = 7,  // 模块数据透传接口，事件参数为MODULE_REPORT_DATA_PARAM
	EVENT_CLOSE_SOLUTION_STATE         = 8,  // 关闭方案状态，事件参数为CLOSE_SOLUTION_STATE_PARAM
	EVENT_BATCH_ADD_MODULE_FINISHED    = 9,  // 批量添加模块完成，事件参数为BATCH_ADD_MODULE_FINISHED_PARAM_EX
	EVENT_IMPORT_GROUP_FINISHED        = 10, // 导入Group完成，事件参数为IMPORT_GROUP_FINISHED_PARAM
	EVENT_EXPORT_GROUP_FINISHED        = 11, // 导出Group完成，事件参数为EXPORT_GROUP_FINISHED_PARAM
	EVENT_IMPORT_PROCEDURE_FINISHED    = 12, // 导入流程完成，事件参数为IMPORT_PROCEDURE_FINISHED_PARAM
	EVENT_EXPORT_PROCEDURE_FINISHED    = 13, // 导出流程完成，事件参数为EXPORT_PROCEDURE_FINISHED_PARAM
	EVENT_REPORT_MODULE_STATE          = 14, // 上报模块状态信息，事件参数为MODULE_STATE_INFO_LIST
	EVENT_REQUEST_CHANGE_SOL           = 15, // 模块请求切换方案，事件参数为REQUEST_CHANGE_SOL_PARAM
    EVENT_BATCH_RUN_MODULE_FINISHED    = 16, // 批量执行模块
    EVENT_REQUEST_FREE_PORT            = 17, // 获取可用端口号
};


// 事件类型
enum eNOTIFY_EVENT_TYPE : int
{
	NOTIFY_EVENT_INVALID          = 0,  // 无效
	NOTIFY_EVENT_SERVICE_READY    = 1,  // 底层服务已就绪
	NOTIFY_EVENT_PROCEDURE_STATUS = 2   // 流程状态，数据为PROCEDURE_STATUS_PARAM
};


// 模块执行结果回调
typedef int (__stdcall *pFnResultCallback)(void* pRstData, int nRstDataLen, void* pUserData);

// 事件通知回调，针对调度框架。pEventData为事件参数，取值具体参见 eEVENT_TYPE 说明。
typedef int (__stdcall *pFnEventCallback)(int nEventType, void* pEventData, void* pUserData);

// 事件通知回调，针对普通模块。pEventData为事件参数，取值具体参见 NOTIFY_EVENT_TYPE 说明。
typedef int(__stdcall *pFnNotifyEventCallback)(int nEventType, void* pEventData, void* pUserData);

// 模块自定义数据透传回调，针对调度框架。
typedef int(__stdcall *pFnCustomDataTransCallback)(int nDataType, void* pCustomData, void* pUserData);

#endif
