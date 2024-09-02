/**	@file       imvs_types.h
 *	@note       HangZhou Hikrobot Technology Co., Ltd. All Right Reserved.
 *	@brief      这里填写本文件的摘要
 *
 *	@author		songzhenlong
 *	@date		2020/12/17   18:36
 *
 *	@note       Create
 *
 *	@warning    <No waining>
 */

#ifndef _VM_ALG_MODULE_DEFINES_H_
#define _VM_ALG_MODULE_DEFINES_H_
#include "hka_defs.h"
#include "hka_types.h"
#include "mvb_defs.h"
#include "mvb_types.h"
#include <string>

#ifndef IMVS_NULL
#define IMVS_NULL    0
#endif

//无效的模块ID
#define  MODULE_ID_INVALID       (-1)


#define IMVS_CHAR_SET_NUMBER         (0x00000001) // 数字集
#define IMVS_CHAR_SET_SMALL_ALPHABET (0x00000010) // 小写字母集
#define IMVS_CHAR_SET_BIG_ALPHABET   (0x00000100) // 大写字母集
#define IMVS_CHAR_SET_SPECIAL_CHAR   (0x00001000) // 特殊字符集
#define IMVS_CHAR_SET_USER_STRING    (0x00010000) // 用户字符集
#define IMVS_CHAR_SET_ALG            (0x00100000) // 算法特定字符集

//多边形个数
#define IMVS_ROI_POLYGOPN_COUNT_MAX                 (8)          // 模块支持多边形个数，暂时由16改为8个
#define IMVS_ROI_POLYGOPN_POINT_COUNT_MAX      (32)       // 单个多边形最大点数
#define IMVS_COMMON_POLYGON_LEN_MAX              (1024)    // 多边形字符串长度

#define IMVS_MULTIPLE_ROI_COUNT_MAX              (64)    // 多ROI最大个数

#define IMVS_MAX_CALIPER_NUMBER           (1000)  //卡尺最大个数

#define  MAX_FILE_PATH          (260)         // 文件最大长度
#define  MAX_FILE_PATH_UTF8     (260*3)       // 文件最大长度
#define  MAX_POLYGON_POINT_NUM  32


#define IMVS_ROI_FROM_ERROR (0)
#define IMVS_ROI_FROM_UI    (1)
#define IMVS_ROI_FROM_INPUT (2)
#define IMVS_ROI_FROM_MASK (3)

//图像结构体最大通道数
#define MAX_IMAGE_CHANNEL_NUM (4)

#define IMVS_MAX_MATCH_NUM           (1000)  //最大匹配个数

//算法模块导出/导入符号
#ifdef _WIN32
	#ifdef IMVSALGMODU_EXPORTS
		#define IMVSALGMODU_API __declspec(dllexport)
	#else
		#define IMVSALGMODU_API __declspec(dllimport)
	#endif
#else
	#define IMVSALGMODU_API __attribute__((visibility("default")))
	#define __stdcall
#endif // _WIN32


// ROI类型
typedef enum _IMVS_ROI_TYPE {
	IMVS_ROI_TYPE_NULL = 0, // 空ROI
	IMVS_ROI_TYPE_IMAGE = 1, // 全图ROI
    IMVS_ROI_TYPE_BOX = 2, // 矩形ROI
    IMVS_ROI_TYPE_ANNULUS = 3, // 扇环ROI
    IMVS_ROI_TYPE_POLYGON = 4, // 多边形ROI
	IMVS_ROI_TYPE_LINECALIPER = 5, // 直线卡尺ROI
	IMVS_ROI_TYPE_CIRCLECALIPER = 6, // 圆形卡尺ROI
	IMVS_ROI_TYPE_MULTIPLE = 7, //多个混合ROI
	IMVS_ROI_TYPE_SECTORCALIPER = 10, //圆弧卡尺ROI
    IMVS_ROI_TYPE_MATRIXCIRCLE = 11, //阵列圆ROI
	IMVS_ROI_TYPE_DEFAULT = 255, //默认ROI
    IMVS_ROI_TYPE_NUM
}IMVS_ROI_TYPE;

/** @enum IMVS_MODU_STATUS
 *  @brief  
 */
typedef enum IMVS_MODU_STATUS__
{
    IMVS_MODU_ENUM_STATUS_ERROR = 0,            // 通信不正确, 通信消息出现严重错误
    IMVS_MODU_ENUM_STATUS_OK = 1,            // 通信正确, 已经订阅, 且获取订阅的值正确
    IMVS_MODU_ENUM_STATUS_INPUT_INVALID = 2,            // 通信正确, 已经订阅, 但获取订阅的值无效(比如上个模块没有找到圆结果)
    IMVS_MODU_ENUM_STATUS_NOSUBSCRIBE = 3,            // 通信正确, 但未订阅, 无须判断值,做相应处理即可(一般使用默认值或者用户自定义参数值)
} IMVS_MODU_STATUS;

//参数校验直接跳出循环
#define HKA_CHECK_BREAK(flag)        \
{                                     \
	if (flag)                         \
        	{                                 \
		break;                       \
        	}                                 \
}

#define HKA_CHECK_BREAK_EX(flag,loginfo)        \
    {                                     \
	if (flag)                         \
                	{                                 \
            MLOG_ERROR(m_nModuleId,loginfo);        \
		break;                       \
            	}                                 \
    }

#pragma   warning(error:4003)//如果不输入moduID报错
#pragma   warning(error:4002)//如果不输入moduID报错
#define HKA_CHECK_BREAK_LOG(flag, nret, funName)        \
	    {                                     \
	if (flag)                         \
	                	{                                 \
            MLOG_ERROR(m_nModuleId,"%s return [%x]", funName, nret);        \
		break;                       \
	            	}                                 \
	    }

//参数校验return
#define HKA_MODU_CHECK_ERROR(flag, ret)    \
        {                                     \
	if (flag)                         \
                	{                                 \
	return ret;                 \
            	}                                 \
    }

#pragma   warning(error:4003)//如果不输入moduID报错
#pragma   warning(error:4002)//如果不输入moduID报错
#define HKA_CHECK_ERROR_LOG(flag, nret, funName)    \
    {                                     \
    if (flag)                         \
        {                                 \
        MLOG_ERROR(m_nModuleId, "%s return [%x]", funName, nret); \
        return (nret);                 \
        }                                 \
    }



#define  MVDSDK_TRY  try

#define  MVDSDK_CATCH  catch (int nErrCode)\
        {\
        MLOG_ERROR(m_nModuleId, "MVDSDK catch int exception! nErrCode[%x]", nErrCode);\
        nRet = nErrCode;\
        }\
	catch (unsigned int nErrCode)\
	    {\
        MLOG_ERROR(m_nModuleId, "MVDSDK catch unsigned int exception! nErrCode[%x]", nErrCode);\
        nRet = nErrCode;\
	    }\
    catch (IMVDException &ex)\
        {\
        MLOG_ERROR(m_nModuleId, "MVDSDK catch IMVDException exception! nErrCode[%x], description[%s]", ex.GetErrorCode(), ex.GetDescription());\
        nRet = ex.GetErrorCode();\
        }\
    catch (...)\
        {\
        MLOG_ERROR(m_nModuleId, "MVDSDK catch other exception!");\
        nRet = IMVS_EC_UNKNOWN;\
        }

//参数校验返回状态码
#define MVDSDK_THROW_ERROR(flag, sts, fun)							\
    {																\
    if (flag)													\
            	{															\
		MLOG_ERROR(m_nModuleId, "%s nRet = %#X\r\n",fun, (sts)); \
		throw (sts);											\
            	}															\
    }

// ROI版本号
typedef enum _IMVS_ROI_VERSION {
    IMVS_ROI_VERSION_V0 = 0,
    IMVS_ROI_VERSION_V1 = 1,
    IMVS_ROI_VERSION_NUM
}IMVS_ROI_VERSION;

// Box
typedef struct _IMVS_ROI_BOX {
    float               fRoiCenterX;
    float               fRoiCenterY;
    float               fRoiWidth;
    float               fRoiHeight;
    float               fRoiAngle;
} IMVS_ROI_BOX;

typedef struct _IMVS_ROI_BOX_EXTEND {
    IMVS_ROI_BOX stRoiValue;
    unsigned int nVersion;
    unsigned int nReserved[4];
} IMVS_ROI_BOX_EXTEND;

// 圆环
typedef struct _IMVS_ANNULUS {
    HKA_POINT_F center;        // 中心点
    HKA_F32     inner_radius;  // 内圆半径
    HKA_F32     outer_radius;  // 外圆半径
    HKA_F32     start_angle;   // 圆环起始角度
    HKA_F32     end_angle;     // 圆环角度范围
}IMVS_ANNULUS;

typedef struct _IMVS_ANNULUS_EXTEND {
    IMVS_ANNULUS stRoiValue;
    unsigned int nVersion;
    unsigned int nReserved[4];
} IMVS_ANNULUS_EXTEND;

//多边形
typedef struct _IMVS_POLYGON
{
	unsigned int       vertex_num;      //顶点数
	HKA_POINT_F   vertex_points[IMVS_ROI_POLYGOPN_POINT_COUNT_MAX];   //顶点
}IMVS_POLYGON;

typedef struct _IMVS_MATRIXCIRCLE
{
    IMVS_ROI_BOX stMatrixBox; // 阵列外框
    int nNumX; // X轴列数
    int nNumY; // Y轴行数
    float fOuterRadius; // 圆外径
    float fInnerRadius; // 圆内径
    //unsigned int nReserved[4];
}IMVS_MATRIXCIRCLE;

// 浮点型参数判断
typedef struct _IMVS_PARAM_LIMIT_F32 {
    HKA_S32        is_valid;   // 是否有效
    HKA_F32        min_val;    // 参数最小值
    HKA_F32        max_val;    // 参数最大值
} IMVS_PARAM_LIMIT_F32;

// 浮点型参数判断
typedef struct _IMVS_PARAM_LIMIT_F64 {
	HKA_S32        is_valid;   // 是否有效
	HKA_F64        min_val;    // 参数最小值
	HKA_F64        max_val;    // 参数最大值
} IMVS_PARAM_LIMIT_F64;

// 整型参数判断
typedef struct _IMVS_PARAM_LIMIT_S32 {
    HKA_S32        is_valid;   // 是否有效
    HKA_S32        min_val;    // 参数最小值
    HKA_S32        max_val;    // 参数最大值
} IMVS_PARAM_LIMIT_S32;

// 字符串参数判断
typedef struct _IMVS_PARAM_LIMIT_STRING {
    HKA_S32        is_valid;   // 是否有效
    char           user_char[256]; // 用户定义字符串
} IMVS_PARAM_LIMIT_STRING;

// 字符验证信息
typedef struct _IMVS_CHAR_VERIFY {
    HKA_S32  is_valid;       // 是否使能
    HKA_S32  char_set;       // 字符集
    char     user_char[256]; // 用户定义字符集
    char     alg_char[256];  // 算法特定字符集
}IMVS_CHAR_VERIFY;

//多边形ROI列表
typedef struct _IMVS_Polygon_ROI_LIST {
    int                   nCount;
    MVB_POLYGON_F         szstShieldedPolygon[IMVS_ROI_POLYGOPN_COUNT_MAX];
    MVB_POLYGON_F         szstShieldedRoiPolygon[IMVS_ROI_POLYGOPN_COUNT_MAX];
    MVB_POLYGON_F         szstShieldedFixPolygon[IMVS_ROI_POLYGOPN_COUNT_MAX];
    MVB_POLYGON_F         szstShieldedPolygonBasis[IMVS_ROI_POLYGOPN_COUNT_MAX];
    int                   nReserved[4];
}IMVS_Polygon_ROI_LIST;

//多边形屏蔽区列表
typedef struct _IMVS_POLYGON_MASK_LIST {
	int                   nCount;
	IMVS_POLYGON         stMaskNormalized[IMVS_ROI_POLYGOPN_COUNT_MAX];
	IMVS_POLYGON         stMaskPixel[IMVS_ROI_POLYGOPN_COUNT_MAX];
	int                 nReserved[4];
}IMVS_POLYGON_MASK_LIST;

// 轮廓点信息
typedef struct _IMVS_CONTOUR_POINT_INFO
{
    HKA_F32 ContourX;
    HKA_F32 ContourY;
    HKA_F32 ContourScore;
    HKA_S32 ContourIndex;
}IMVS_CONTOUR_POINT_INFO;

typedef struct _MY_LINECALIPERBOX
{
	float      fStartX;
	float      fStartY;
	float      fEndX;
	float      fEndY;
	float      fWidth;
	float      fHeight;
	float      fAngle;
	int        nNum;
} MY_LINECALIPERBOX;

typedef struct _MY_CIRCLECALIPERBOX
{
	float      fCenterX;
	float      fCenterY;
	float      fOutterRadius;
	float      fStartAngle;
	float      fEndAngle;
	float      fWidth;
	float      fHeight;
	int        nNum;
} MY_CIRCLECALIPERBOX;

typedef struct _MY_SECTORCALIPERBOX
{
	float      fStartX;
	float      fStartY;
	float      fEndX;
	float      fEndY;
	float      fRadius;
	float      fWidth;
	float      fHeight;
	int        nNum;
	int        nLargeArc;
	int        nClockWise;
}MY_SECTORCALIPERBOX;

// 匹配信息
typedef struct _IMVS_PAT_MATCH_INFO
{
	MVBI_BOX_F     match_box;    // 模板匹配区域包围框
	HKA_POINT_F    match_point;  // 模板匹配点
	HKA_F32        match_scale;  // 模板匹配尺度
	HKA_F32		   match_scale_x;// 模板匹配x尺度
	HKA_F32		   match_scale_y;// 模板匹配y尺度
	HKA_F32        match_score;  // 相似分数
	HKA_F32		   match_rms;	 // 结果拟合误差
} IMVS_PAT_MATCH_INFO;

// 模板匹配结果
typedef struct _IMVS_CONTOUR_POINT_LIST
{
	IMVS_CONTOUR_POINT_INFO *pstPointInfo;
	HKA_S32					nPointNums;
} IMVS_CONTOUR_POINT_LIST;

// 模板匹配结果
typedef struct _IMVS_PAT_MATCH_RESULT
{
	IMVS_PAT_MATCH_INFO		stMatchInfo;  // 匹配结果
	IMVS_CONTOUR_POINT_INFO *pstPointInfo;
	HKA_S32					nPointNums;
	HKA_S32					nModelIndex;
} IMVS_PAT_MATCH_RESULT;

// 算法运行参数，范围值
typedef struct _IMVS_ALG_PARAM_LIMIT {
	std::string        strMinVal;    // 参数最小值
	std::string        strMaxVal;    // 参数最大值
} IMVS_ALG_PARAM_LIMIT;

#endif//_VM_ALG_MODULE_DEFINES_H_

