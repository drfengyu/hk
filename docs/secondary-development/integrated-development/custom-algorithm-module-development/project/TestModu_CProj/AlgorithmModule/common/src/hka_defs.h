/***************************************************************************************************
* 
* 版权信息：版权所有 (c) 2010-2018, 杭州海康威视软件有限公司, 保留所有权利
*
* 文件名称：hka_defs.h
* 摘    要：HKA图像处理库内部的结构体、宏定义、数据类型等
*
* 当前版本：1.0.1
* 作    者：申琳
* 日    期：2015年8月6日
* 备    注：1 删除无符号数的最大最小值U后缀
*           2 增加S16取绝对值定义
*
* 历史版本：1.0.0
* 作    者：申琳
* 日    期：2015年5月26日
* 备    注：1 删除HKA_EPS23及HKA_EPS52宏定义
*           2 增加相关数据详细注释
*
* 历史版本：0.9.0
* 作    者：申琳 武晓阳 戚红命 蔡巍伟
* 日    期：2015年5月20日
* 备    注：1 删除外部依赖头文件，并删除和math.h相关联的宏定义
*           2 删除inline定义
*
* 历史版本：0.2.0
* 作    者：蔡巍伟
* 日    期：2015年4月21日
* 备    注：以vca_base.h为基础，考虑数据结构的复用性定义初始版本
*
* 历史版本：0.1.0
* 作    者：武晓阳
* 日    期：2012年10月26日
* 备    注：初始版本
***************************************************************************************************/
#ifndef _HKA_DEFS_H_
#define _HKA_DEFS_H_


#include "hka_types.h"


#ifdef __cplusplus        
extern "C" 
{
#endif


/***************************************************************************************************
* 空指针、true、false宏定义
***************************************************************************************************/
#ifndef HKA_NULL
#define HKA_NULL    0
#endif


#ifndef HKA_TRUE
#define HKA_TRUE    1
#endif

#ifndef HKA_FALSE
#define HKA_FALSE   0
#endif


/***************************************************************************************************
* 基本常数定义
***************************************************************************************************/
//数据最大最小值
#define HKA_MIN_U08     ( 0 )                           // 最小8位无符号整型值
#define HKA_MAX_U08     ( 0xFFU )                        // 最大8位无符号整型值
#define HKA_MIN_U16     ( 0 )                           // 最小16位无符号整型值
#define HKA_MAX_U16     ( 0xFFFFU )                      // 最大16位无符号整型值
#define HKA_MIN_U32     ( 0 )                           // 最小32位无符号整型值
#define HKA_MAX_U32     ( 0xFFFFFFFFU )                  // 最大32位无符号整型值
#define HKA_MIN_S08     (-128 )                         // 最小8位有符号整型值
#define HKA_MAX_S08     ( 127 )                         // 最大8位有符号整型值
#define HKA_MIN_S16     (-32768 )                       // 最小16位有符号整型值
#define HKA_MAX_S16     ( 32767 )                       // 最大16位有符号整型值
#define HKA_MIN_S32     (-2147483647 - 1 )              // 最小32位有符号整型值
#define HKA_MAX_S32     ( 2147483647 )                  // 最大32位有符号整型值

#if defined(_WIN32) || defined (_WIN64)
#   define HKA_MAX_S64  ( 9223372036854775807i64)       // 最小64位有符号整型值(windows平台)
#   define HKA_MIN_S64  (-9223372036854775807i64 - 1)   // 最大64位有符号整型值(windows平台)
#else
#   define HKA_MAX_S64  ( 9223372036854775807LL )       // 最小64位有符号整型值(非windows平台)
#   define HKA_MIN_S64  (-9223372036854775807LL - 1 )   // 最大64位有符号整型值(非windows平台)
#endif

#define HKA_MINABS_F32  ( 1.175494351e-38f )            // 绝对值最小单精度值
#define HKA_MAXABS_F32  ( 3.402823466e+38f )            // 绝对值最大单精度值
#define HKA_EPS_F32     ( 1.192092890e-07f )            // 单精度浮点标准中最小差值
#define HKA_MINABS_F64  ( 2.2250738585072014e-308 )     // 绝对值最小双精度值
#define HKA_MAXABS_F64  ( 1.7976931348623158e+308 )     // 绝对值最大双精度值
#define HKA_EPS_F64     ( 2.2204460492503131e-016 )     // 双精度浮点标准中最小差值

//数学常数
#define HKA_PI    ( 3.14159265358979323846 )  // ANSI C 不支持 M_PI
#define HKA_2PI   ( 6.28318530717958647692 )  // 2*pi
#define HKA_PI2   ( 1.57079632679489661923 )  // pi/2
#define HKA_PI4   ( 0.78539816339744830961 )  // pi/4
#define HKA_PI180 ( 0.01745329251994329577 )  // pi/180
#define HKA_RPI   ( 0.31830988618379067154 )  // 1/pi
#define HKA_SQRT2 ( 1.41421356237309504880 )  // sqrt(2)
#define HKA_SQRT3 ( 1.73205080756887729353 )  // sqrt(3)
#define HKA_LN2   ( 0.69314718055994530942 )  // ln(2)
#define HKA_LN3   ( 1.09861228866810969139 )  // ln(3)
#define HKA_E     ( 2.71828182845904523536 )  // e
#define HKA_RE    ( 0.36787944117144232159 )  // 1/e


/***************************************************************************************************
* 基本数学运算
***************************************************************************************************/
#define HKA_ABS(x)                (((HKA_S32)(x) < 0) ? (-(HKA_S32)(x)) : (HKA_S32)(x))
#define HKA_SABS(x)               (((HKA_S16)(x) < 0) ? (-(HKA_S16)(x)) : (HKA_S16)(x))
#define HKA_LABS(x)               (((HKA_S64)(x) < 0) ? (-(HKA_S64)(x)) : (HKA_S64)(x))
#define HKA_FABS(x)               (((HKA_F32)(x) < 0) ? (-(HKA_F32)(x)) : (HKA_F32)(x))
#define HKA_DABS(x)               (((HKA_F64)(x) < 0) ? (-(HKA_F64)(x)) : (HKA_F64)(x))
#define HKA_MAX(a, b)             (((a) < (b)) ? (b) : (a))
#define HKA_MIN(a, b)             (((a) > (b)) ? (b) : (a))
#define HKA_CLIP(v, minv, maxv)   HKA_MIN((maxv), HKA_MAX((v), (minv)))
#define HKA_ROUND(x)              (((x) < 0.0) ? (HKA_S32)((x) - 0.5) : (HKA_S32)((x) + 0.5))


/***************************************************************************************************
* 基本参数校验宏
***************************************************************************************************/
//参数校验返回状态码
#define HKA_CHECK_ERROR(flag, sts)    \
{                                     \
    if (flag)                         \
    {                                 \
        return (sts);                 \
    }                                 \
}

//参数校验直接返回
#define HKA_CHECK_RETURN(flag)        \
{                                     \
    if (flag)                         \
    {                                 \
        return;                       \
    }                                 \
}


/***************************************************************************************************
* 对齐计算
***************************************************************************************************/
#define HKA_SIZE_ALIGN(size, align)  (((size) + ((align) - 1)) & (~((align) - 1)))
#define HKA_SIZE_ALIGN_4(size)       HKA_SIZE_ALIGN(size, 4)
#define HKA_SIZE_ALIGN_8(size)       HKA_SIZE_ALIGN(size, 8)
#define HKA_SIZE_ALIGN_16(size)      HKA_SIZE_ALIGN(size, 16)
#define HKA_SIZE_ALIGN_32(size)      HKA_SIZE_ALIGN(size, 32)
#define HKA_SIZE_ALIGN_64(size)      HKA_SIZE_ALIGN(size, 64)
#define HKA_SIZE_ALIGN_128(size)     HKA_SIZE_ALIGN(size, 128)

//最大内存
#if defined (_HKA_SYS64)
#define HKA_MAX_MEM_SIZE   HKA_MAX_S64
#else
#define HKA_MAX_MEM_SIZE   (4294966272U)  // 2^32 - 2^10
#endif//(_HKA_SYS64)

#ifdef __cplusplus        
}
#endif


#endif//_HKA_DEFS_H_




