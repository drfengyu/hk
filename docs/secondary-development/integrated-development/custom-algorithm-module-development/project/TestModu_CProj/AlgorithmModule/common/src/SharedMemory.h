/************************************************************************
* 版权信息：版权所有(c) 2020, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：SharedMemory.h
* 摘   要:  支持跨平台操作共享内存数据。
*
* 作   者:  fenghuapeng5
* 日   期： 2020-09-18
* 备   注： 为了简化接口定义，默认都以RW权限创建或打开共享内存。
************************************************************************/

#ifndef _SHARED_MEMORY_H_
#define _SHARED_MEMORY_H_

#include <string>
#ifdef _WIN32
#define SHM_HANDLE HANDLE
#define INVALID_SHM_HANDLE NULL

#ifndef SYSTEM_ERROR
#define SYSTEM_ERROR     GetLastError()
#endif//SYSTEM_ERROR
typedef unsigned __int64         SHM_uint64;
#else
#define SHM_HANDLE int
#define INVALID_SHM_HANDLE -1
#ifndef SYSTEM_ERROR
#define SYSTEM_ERROR     errno
#endif//SYSTEM_ERROR
typedef unsigned long long       SHM_uint64;
#endif

#ifdef _UNICODE
typedef  wchar_t  SHM_tchar;
#else
typedef  char     SHM_tchar;
#endif

//共享内存头长度
#define   SHARED_MEMORY_HEADER_LEN    16

// 创建或打开已有的共享内存，操作成功时返回映射句柄，失败时返回INVALID_SHM_HANDLE
SHM_HANDLE SHM_CreateMapping(const char* pName, size_t nMappingLen);
SHM_HANDLE SHM_OpenMapping(const char* pName);

// 映射至内存区域，操作成功时返回映射地址，失败时返回NULL
void* SHM_WriteMapView(SHM_HANDLE hMapping, size_t nMappingLen);
void* SHM_ReadMapView(SHM_HANDLE hMapping);

// 取消内存映射、关闭映射句柄。操作成功时返回0，失败时返回对应的系统错误码
int SHM_UnMapView(void* pView, size_t nMappingLen);
int SHM_CloseReadMapping(SHM_HANDLE hMapping);
//关闭读资源
void SHM_CloseReadShm(SHM_HANDLE& hMapping, void*& pBuffView);

//删除共享内存
int SHM_DestroyWriteMapping(SHM_HANDLE hMapping, const char* pName);

//销毁写资源
void SHM_DestroyWriteShm(SHM_HANDLE& hMapping, void*& pBuffView, const char* pShmName/* = NULL*/);

//共享内存转数据
int SharedMemory2Data(const std::string& strSm, std::string& strData);

//共享内存中的数据写到文件
int ShareMemory2File(const char* pszShareMemName, const SHM_tchar* pszFileName, bool bFlush = true);


//文件转共享内存
int File2ShareMemory(const SHM_tchar* pszFileName, const char* strShareMemName, SHM_HANDLE& hMapping, void*& pBuffView);

//数据写入共享内存
int Data2ShareMemory(const char* pData, const size_t nSize, const char* strShareMemName, SHM_HANDLE& hMapping, void*& pBuffView);



#endif
