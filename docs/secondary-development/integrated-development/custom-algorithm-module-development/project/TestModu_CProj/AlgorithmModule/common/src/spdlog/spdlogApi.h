/**	@file       spdlogApi.h
 *	@note       HangZhou Hikrobot Technology Co., Ltd. All Right Reserved.
 *	@brief      spdlog封装接口
 *
 *	@author		songzhenlong
 *	@date		2019/06/06   11:53
 *
 *	@note       Create
 *
 *	@warning    <No waining>
 */
#ifndef __SPDLOG_API_H__
#define __SPDLOG_API_H__

#include "HSlog/HSlog.h"
#include <vector>
#include <io.h>

//使用宽字节打开文件
#ifdef _WIN32

#ifdef _UNICODE
#define SPDLOG_WCHAR_FILENAMES 
#endif
#endif  //end win32



#ifndef LOG_BUFFER_LENGTH
#define  LOG_BUFFER_LENGTH                  (1024)  //日志内容缓冲区大小
#endif



#include <string.h>
#if defined(SPDLOG_WCHAR_FILENAMES)
#define SPD_CHAR                 WCHAR
#define SPD_STRING              std::wstring
#define SPD_STRING_PREFIX(s)    L##s
#define SPD_vsnprintf           _vsnprintf
#else
#define SPD_CHAR                 char
#define SPD_STRING              std::string
#define SPD_STRING_PREFIX(s)    s
#if (defined _WIN32 || defined _WIN64)
#define SPD_vsnprintf           _vsnprintf
#else
#define SPD_snprintf            snprintf
#define SPD_vsnprintf           vsnprintf
#endif//end win32
#endif//end SPDLOG_WCHAR_FILENAMES



#define    SPD_LEVEL              HSlog_Level

#define    Spdlog_ResetLevel      HSlog_ResetLevel


#define    Spdlog_GetCurrentLevel HSlog_GetCurrentLevel


#define LOG_ERROR(fmt, ...)         MLOG_ERROR(-1, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)          MLOG_WARN(-1, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)          MLOG_INFO(-1, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)         MLOG_DEBUG(-1, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)         MLOG_TRACE(-1, fmt, ##__VA_ARGS__)



#endif//end __SPDLOG_API_H__
