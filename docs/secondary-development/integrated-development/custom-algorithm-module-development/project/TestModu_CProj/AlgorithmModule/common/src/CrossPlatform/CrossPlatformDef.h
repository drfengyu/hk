/************************************************************************
* 版权信息：版权所有(c) 2021, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称 CrossPlatformDef.h
* 摘   要:  涉及跨平台的一些值、宏定义
*
* 作   者:  
* 日   期： 2021-10-20
* 备   注：
************************************************************************/
#ifndef _CROSSPLATFORM_DEF_H_
#define _CROSSPLATFORM_DEF_H_

#include <string>

#ifndef WAIT_OBJECT_0
    #define WAIT_OBJECT_0 0
#endif

#ifndef INFINITE
	#define INFINITE 0xFFFFFFFF
#endif

#define T_D_FOTMAT   _T("%d")
#define T_SEP_FOTMAT _T("/")


#ifdef _UNICODE
typedef  std::wstring tstring;
typedef  wchar_t      tchar;
#else
typedef std::string   tstring;
typedef char          tchar;
#endif

#ifdef _WIN32
    #define SHARED_MODULE_HANDLE HMODULE
    #ifndef snprintf
        #define snprintf sprintf_s
        #define T_S_FORMAT   _T("%s")
    #endif

#define PATH_PARTITION      '\\'

#else

typedef char				CHAR;
typedef unsigned long long	ULONGLONG;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef void*				HANDLE;

#ifndef __int64
#define  __int64   long long
#endif


#define MAX_PATH       260

#define PATH_PARTITION      '/'

	#define __stdcall
    #define SHARED_MODULE_HANDLE void* 
#ifdef _UNICODE
    #define _T(x) L##x
#else
	#define _T(x) x
#endif
    #define T_S_FORMAT   _T("%ls")

#ifndef _snprintf
    #define _snprintf snprintf 
#endif

    #ifndef sprintf_s
        #define sprintf_s snprintf 
    #endif

    #ifndef sscanf_s
        #define sscanf_s sscanf 
    #endif

    #ifndef _snprintf_s
        #define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)
    #endif

    #ifndef _countof
        #define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
    #endif

    #ifndef _sntprintf_s
        #define _sntprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__) 
    #endif

	#ifndef _snwprintf_s
		#define _snwprintf_s(a,b,c,...) swprintf(a,b,__VA_ARGS__) 
	#endif

	#ifndef _TCHAR
		#define _TCHAR char
	#endif

	#ifndef _tmain
		#define _tmain main
	#endif

	#ifndef CP_ACP
		#define CP_ACP 0
	#endif

	struct __timeb64
	{
		time_t time;
		unsigned short millitm;
		short timezone;
		short dstflag;
	};

	typedef struct
	{
		char szName[512];
		int  nType;
	}findfile_data;
#endif

#endif
