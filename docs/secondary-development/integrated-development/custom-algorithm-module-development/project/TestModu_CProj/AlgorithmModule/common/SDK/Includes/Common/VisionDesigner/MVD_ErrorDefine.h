/***************************************************************************************************
* File:  MVD_ErrorDefine.h
* Note:  ch: 算法包SDK层相关的状态码定义。
         En: SDK-related status code definition in namespace VisionDesigner.
*
* Version:  V3.2.0.3
****************************************************************************************************/


#ifndef _MVD_ERROR_DEFINE_H_
#define _MVD_ERROR_DEFINE_H_

#include "MVD_ErrorDefine_Exp.h"
#include "MVD_ErrorDefine_Algo.h"
#include "MVD_ErrorDefine_Cam.h"


// ch:正确码定义 | en:Definition of correct code
const static int MVD_OK                      = 0x00000000;    ///< 成功，无错误 | en:Successed, no error
const static int MVD_E_MIN                   = 0x80100000;    ///< 算法包SDK的错误码最小值 | en:Minimum value of the SDK-releated error code.
const static int MVD_E_MAX                   = 0x8010FFFF;    ///< 算法包SDK的错误码最大值 | en:Maximum value of the SDK-releated error code.

//算法包通用错误码定义:范围0x80100000-0x801000FF | en:Common error 
const static int MVD_E_HANDLE                = 0x80100000;    ///< 错误或无效的句柄 | en:Error or invalid handle
const static int MVD_E_SUPPORT               = 0x80100001;    ///< 不支持的功能 | en:Not supported function
const static int MVD_E_OVER_ABILITY          = 0x80100002;    ///< 超出限制的能力范围 | en: Beyond the limits of capacity
const static int MVD_E_CALLORDER             = 0x80100003;    ///< 函数调用顺序错误 | en:Function calling order error
const static int MVD_E_PRECONDITION          = 0x80100004;    ///< 前置条件有误 | en:Precondition error
const static int MVD_E_PARAMETER_RANGE       = 0x80100005;    ///< 参数超出范围限制 | en:Parameter out of range limit
const static int MVD_E_PARAMETER_ILLEGAL     = 0x80100006;    ///< 参数非法 | en:Illegal parameter. Such as a null pointer
const static int MVD_E_PARAMETER_MATCH       = 0x80100007;    ///< 参数互相不匹配 | en:Parameters do not match each other
const static int MVD_E_PARAMETER_GENERIC     = 0x80100008;    ///< 通用参数错误 | en:General parameter error
const static int MVD_E_RESOURCE              = 0x80100009;    ///< 资源申请失败 | en:Applying resource failed
const static int MVD_E_BUFOVER               = 0x8010000A;    ///< 缓存已满 | en:Out of memory
const static int MVD_E_NOOUTBUF              = 0x8010000B;    ///< 没有可输出的缓存 | en:No Avaliable Buffer
const static int MVD_E_NOENOUGH_BUF          = 0x8010000C;    ///< 传入的内存空间不足 | en:Insufficient memory prepared
const static int MVD_E_FILE_PATH             = 0x8010000D;    ///< 不支持的文件路径 | en: Unsupported file path
const static int MVD_E_FILE_FORMAT           = 0x8010000E;    ///< 不支持的文件格式 | en: Unsupported file format
const static int MVD_E_FILE_CORRUPTED        = 0x8010000F;    ///< 文件损坏 | en: Corrupted file
const static int MVD_E_FILE_GENERIC          = 0x80100010;    ///< 通用文件错误 | en: General file error
const static int MVD_E_NODATA                = 0x80100011;    ///< 无数据 | en:No data
const static int MVD_E_ABNORMAL_IMAGE        = 0x80100012;    ///< 异常图像 | en:Abnormal image
const static int MVD_E_VERSION               = 0x80100013;    ///< 版本不匹配 | en:Version mismatches
const static int MVD_E_LOAD_LIBRARY          = 0x80100014;    ///< 动态导入DLL失败 | en:Load library failed
const static int MVD_E_RUNTIME               = 0x80100015;    ///< 运行环境错误 | en: Wrong with running environment
const static int MVD_E_NO_AVAILABLE_DEVICE   = 0x80100016;    ///< 没有可用设备，不存在可用的显卡或者显卡驱动未更新| en: No avaliable device
const static int MVD_E_UNKNOW                = 0x801000FF;    ///< 未知的错误 | en:Unknown error

// 算法处理流程相关:范围0x80100200-0x801002FF
const static int MVD_ALGORITHM_E_ALGORITHM   = 0x80100201;    ///< ch: 算法版本错误 | en:Unknown error on algorithms
const static int MVD_ALGORITHM_E_CONFIG      = 0x80100202;    ///< ch: 算法配置错误 | en: Wrong configuration
const static int MVD_ALGORITHM_E_UNKNOW      = 0x80100203;    ///< ch: 算法未知错误 | en:Unknown error on algorithm SDK

// 字符缺陷检测算法相关
const static int MVD_ALGORITHM_E_MKINSP_ROUGH_MATCH_FAILED          = 0x80100204;    ///< ch: 字符缺陷检测粗定位失败
const static int MVD_ALGORITHM_E_MKINSP_MODEL_VERSION_NOT_SUPPORT   = 0x80100205;    ///< ch: 字符缺陷检测模板版本号不支持

#endif //_MVD_ERROR_DEFINE_H_

