/************************************************************************
* 版权信息：版权所有(c) 2022, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：HSlog.h
* 摘   要: hik spdlog 异步日志库
*
* 作   者:  songzhenlong
* 日   期： 2022-06-15
* 备   注：
************************************************************************/

#ifndef _HIK_SPEED_LOG_ASYNC_H_
#define _HIK_SPEED_LOG_ASYNC_H_
#include "HSlogDefine.h"

#ifdef _WIN32

#ifdef  HIK_SPDLOG_EXPORTS
#    define HSLOG_API __declspec(dllexport)
#else
#    define HSLOG_API __declspec(dllimport)
#endif
#else
#    define HSLOG_API __attribute__((visibility("default")))
#    define __stdcall
#endif

#ifndef LOG_FILE_SIZE_MAX
#define  LOG_FILE_SIZE_MAX                  (1048576 * 10)  //日志文件大小
#endif // !LOG_FILE_SIZE_MAX

#ifndef LOG_FILE_ROTATE_COUNT_DEFAULT
#define  LOG_FILE_ROTATE_COUNT_DEFAULT      (10)             //默认日志文件回滚数量
#endif


#ifdef __cplusplus
extern "C"
{
#endif 

    /** @fn:    HSlog_Init_Module
    * @brief:   模块异步日志初始化，该接口目前在模块代理中调用。VM模块中不要使用。模块直接使用下方的日志打印宏
    * @param:   pchFileName   日志文件绝对路径
    * @return:  int 成功返回0，错误返回其他值
    */
    HSLOG_API int __stdcall HSlog_Init_Module(const HSLOG_CHAR* pchFileName, bool bFlushOnTimer = true, unsigned int nFileSize = LOG_FILE_SIZE_MAX, unsigned int nRotateCount = LOG_FILE_ROTATE_COUNT_DEFAULT);

    /** @fn:    HSlog_Deinit_Module
    * @brief:   模块异步日志反初始化，该接口目前在模块代理中调用。VM模块中不要使用
    * @param:   pchFileName   日志文件绝对路径
    * @return:  int 成功返回0，错误返回其他值
    */
    HSLOG_API int __stdcall HSlog_Deinit_Module();

    /** @fn:    HSlog_ShouldLog
    * @brief:   判断是否需要打印日志
    * @param:   nlogLevel   日志等级
    * @return:  bool 需要返回true，否则false
    */
    HSLOG_API bool __stdcall HSlog_ShouldLog(HSlog_Level nlogLevel);

    /** @fn:    HSlog_LogPrint
    * @brief:   日志打印接口，模块不需调用，直接使用下方的日志打印宏
    * @param:   pchFileName   日志文件绝对路径
    * @return:  int 成功返回0，错误返回其他值
    */
    HSLOG_API void __stdcall HSlog_LogPrint(HSlog_Level nlogLevel, const char* format, ...);

    /** @fn:    HSlog_GetCurrentLevel
    * @brief:   获取当前日志等级
    * @return:  返回当前日志等级
    */
    HSLOG_API HSlog_Level __stdcall HSlog_GetCurrentLevel();

    /** @fn:    HSlog_ResetLevel
    * @brief:   重置日志等级，模块中不要调用。模块代理后续可动态整体调整等级
    * @param:   pchFileName   日志文件绝对路径
    * @return:  int 成功返回0，错误返回其他值
    */
    HSLOG_API void __stdcall HSlog_ResetLevel(HSlog_Level nlogLevel);

#ifdef __cplusplus
};
#endif 


#endif //end of _HIK_SPEED_LOG_ASYNC_H_
