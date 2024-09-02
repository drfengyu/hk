#if (defined _WIN32 || defined _WIN64)
#define WIN32_LEAN_AND_MEAN  //解决winsock.h和winsock2.h类型重定义问题
#include <Windows.h>
#include <tchar.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif
#include "SharedMemory.h"
#include "HSlog/HSlog.h"
#include <io.h>
#include "ErrorCodeDefine.h"
#include "string.h"

#ifdef _UNICODE
    #define _T(x) L##x
#else
	#define _T(x) x
#endif

#pragma warning(disable:4996)
/** @fn:    SHM_CreateMapping
* @brief:   创建共享内存
* @param:   const char * pName   共享内存名称
* @param:   int nMappingLen      共享内存长度
* @return:  SHM_HANDLE 共享内存句柄
*/
SHM_HANDLE SHM_CreateMapping(const char* pName, size_t nMappingLen)
{
	SHM_HANDLE hMapping = INVALID_SHM_HANDLE;
    if (nMappingLen <= 0)
    {
        return hMapping;
    }
#ifdef _WIN32
    DWORD dLow = (DWORD)(nMappingLen & 0xffffffff);
    DWORD dHigh = (DWORD)(nMappingLen >> 32);
    hMapping = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, dHigh, dLow, pName);
    //nError = GetLastError();
#else
	hMapping = shm_open(pName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	int nRet = ftruncate(hMapping, nMappingLen);
    //nError = errno;
    if (IMVS_EC_OK != nRet)
    {
        SHM_DestroyWriteMapping(hMapping, pName);
        return INVALID_SHM_HANDLE;
    }
#endif
	return hMapping;
}


/** @fn:    SHM_OpenMapping
* @brief:   打开共享内存
* @param:   const char * pName  共享内存名称
* @return:  SHM_HANDLE 共享内存句柄
*/
SHM_HANDLE SHM_OpenMapping(const char* pName)
{
	SHM_HANDLE hMapping = INVALID_SHM_HANDLE;
#ifdef _WIN32
	hMapping = OpenFileMappingA(FILE_MAP_ALL_ACCESS, 0, pName);
#else
	hMapping = shm_open(pName, O_RDWR, S_IRUSR | S_IWUSR);
#endif
	return hMapping;
}


/** @fn:    SHM_WriteMapView
* @brief:   写共享内存时，获取映射指针
* @param:   SHM_HANDLE hMapping   共享内存句柄
* @param:   int nMappingLen       映射长度
* @return:  void* 映射指针
*/
void*  SHM_WriteMapView(SHM_HANDLE hMapping, size_t nMappingLen)
{
	void* pView = NULL;
#ifdef _WIN32
	pView = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
#else
	pView = mmap(NULL, nMappingLen, PROT_READ | PROT_WRITE, MAP_SHARED, hMapping, 0);
#endif
	return pView;
}

/** @fn:    SHM_ReadMapView
* @brief:   读数据时，获取映射指针
* @param:   SHM_HANDLE hMapping
* @return:  void* 映射指针
*/
void*  SHM_ReadMapView(SHM_HANDLE hMapping)
{
    void* pView = NULL;
#ifdef _WIN32
    pView = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
#else
    //1、Linux先读一个头的长度
    pView = mmap(NULL, SHARED_MEMORY_HEADER_LEN, PROT_READ, MAP_SHARED, hMapping, 0);
    SHM_uint64 nTotalLen = *((SHM_uint64 *)pView) + SHARED_MEMORY_HEADER_LEN;//需要加上头
    size_t nLen = (size_t)nTotalLen;
    int nRet = SHM_UnMapView(pView, SHARED_MEMORY_HEADER_LEN);
    if (0 != nRet)
    {
        return NULL;
    }
    //2、Linux按长度获取映射指针
    pView = mmap(NULL, nLen, PROT_READ, MAP_SHARED, hMapping, 0);
    if (NULL == pView)
    {
        LOG_ERROR("mmap fail, error[%d]", SYSTEM_ERROR);
    }
#endif
    return pView;
}


/** @fn:    SHM_UnMapView
* @brief:   取消映射
* @param:   void * pView
* @param:   int nMappingLen
* @return:  int 成功返回0，错误返回其他值
*/
int SHM_UnMapView(void* pView, size_t nMappingLen)
{
    if (NULL == pView)
    {
        return 0;
    }
	int nRst = 0;
#ifdef _WIN32
	if (!UnmapViewOfFile(pView))
	{
		nRst = GetLastError();
	}
#else
	if (munmap(pView, nMappingLen) != 0)
	{
		nRst = errno;
	}
#endif
	return nRst;
}


/** @fn:    SHM_CloseMapping
* @brief:   关闭共享内存句柄
* @param:   SHM_HANDLE hMapping
* @param:   const char * pName
* @return:  int 成功返回0，错误返回其他值
*/
int SHM_CloseReadMapping(SHM_HANDLE hMapping)
{
    if (INVALID_SHM_HANDLE == hMapping)
    {
        return 0;
    }
	int nRst = 0;
#ifdef _WIN32
	if (!CloseHandle(hMapping))
	{
		nRst = GetLastError();
	}
#else
    close(hMapping);
#endif
	return nRst;
}

//关闭读资源
void SHM_CloseReadShm(SHM_HANDLE& hMapping, void*& pBuffView)
{
#if (defined _WIN32 || defined _WIN64)
    if (pBuffView != NULL)
    {
        UnmapViewOfFile(pBuffView);
        pBuffView = NULL;
    }

    if (hMapping != NULL)
    {
        CloseHandle(hMapping);
        hMapping = NULL;
    }
#else
    if (pBuffView != NULL)
    {
        SHM_uint64 nImageLenTmp = *((SHM_uint64 *)pBuffView) + SHARED_MEMORY_HEADER_LEN;
        size_t nImageLen = (size_t)nImageLenTmp;
        SHM_UnMapView(pBuffView, nImageLen);
        pBuffView = NULL;
    }

    if (INVALID_SHM_HANDLE != hMapping)
    {
        SHM_CloseReadMapping(hMapping);
        hMapping = INVALID_SHM_HANDLE;
    }
#endif
}

//删除共享内存
int SHM_DestroyWriteMapping(SHM_HANDLE hMapping, const char* pName)
{
    int nRst = 0;
#ifdef _WIN32
    if (!CloseHandle(hMapping))
    {
        nRst = GetLastError();
    }
#else
    if (shm_unlink(pName) == 0)
    {
        close(hMapping);
    }
    else
    {
        nRst = errno;
    }
#endif
    return nRst;
}



//销毁写资源
void SHM_DestroyWriteShm(SHM_HANDLE& hMapping, void*& pBuffView, const char* pShmName/* = NULL*/)
{
#if (defined _WIN32 || defined _WIN64)
    if (pBuffView != NULL)
    {
        UnmapViewOfFile(pBuffView);
        pBuffView = NULL;
    }

    if (hMapping != NULL)
    {
        CloseHandle(hMapping);
        hMapping = NULL;
    }
#else
    if (pBuffView != NULL)
    {
        SHM_uint64 nImageLenTmp = *((SHM_uint64 *)pBuffView) + SHARED_MEMORY_HEADER_LEN;
        size_t nImageLen = (size_t)nImageLenTmp;
        SHM_UnMapView(pBuffView, nImageLen);
        pBuffView = NULL;
    }

    if (INVALID_SHM_HANDLE != hMapping)
    {
        SHM_DestroyWriteMapping(hMapping, pShmName);
        hMapping = INVALID_SHM_HANDLE;
    }
#endif
}


int SharedMemory2Data(const std::string& strSm, std::string& strData)
{
	//打开文件映射
	SHM_HANDLE hFileMapping = SHM_OpenMapping(strSm.c_str());
	if (INVALID_SHM_HANDLE == hFileMapping)
	{
		LOG_ERROR("SharedMemory2Data fail, OpenFileMapping error[%d]", SYSTEM_ERROR);
		return IMVS_EC_RESOURCE_CREATE;
	}

	//映射视图，获得共享内存地址
	void * hMapView = SHM_ReadMapView(hFileMapping);
	if (NULL == hMapView)
	{
		LOG_ERROR("SharedMemory2Data fail, MapViewOfFile error[%d]", SYSTEM_ERROR);
		if (INVALID_SHM_HANDLE != hFileMapping)
		{
			SHM_CloseReadMapping(hFileMapping);
		}
		return IMVS_EC_RESOURCE_CREATE;
	}

	//从共享内存拷贝数据
    SHM_uint64 nImageLenTmp = *((SHM_uint64 *)hMapView);
    size_t nImageLen = nImageLenTmp;

	try
	{//赋值
		strData.assign((char *)hMapView + SHARED_MEMORY_HEADER_LEN, nImageLen);//可能抛异常
	}
	catch (...)
	{
		LOG_ERROR("SharedMemory2Data catch exception.");
		if (hMapView)
		{
			SHM_UnMapView(hMapView, nImageLen);
			hMapView = NULL;
		}

		if (INVALID_SHM_HANDLE != hFileMapping)
		{
            SHM_CloseReadMapping(hFileMapping);
			hFileMapping = INVALID_SHM_HANDLE;
		}
		return IMVS_EC_OUTOFMEMORY;
	}


	if (hMapView)
	{
		SHM_UnMapView(hMapView, nImageLen);
		hMapView = NULL;
	}

	if (INVALID_SHM_HANDLE != hFileMapping)
	{
        SHM_CloseReadMapping(hFileMapping);
		hFileMapping = INVALID_SHM_HANDLE;
	}
	return IMVS_EC_OK;
}

//共享内存中的数据写到文件
int ShareMemory2File(const char* pszShareMemName, const SHM_tchar* pszFileName, bool bFlush/* = true*/)
{
	if (NULL == pszShareMemName || NULL == pszFileName)
	{
		return IMVS_EC_PARAM;
	}
	int nRet = IMVS_EC_OK;
	SHM_HANDLE hFileMapping = INVALID_SHM_HANDLE;
	void * hMapView = NULL;
	size_t nImageLen = 0;
	FILE* pFile = NULL;
	do
	{
		//打开文件映射
		hFileMapping = SHM_OpenMapping(pszShareMemName);
		if (INVALID_SHM_HANDLE == hFileMapping)
		{
			LOG_ERROR("ShareMemory2File fail, OpenFileMapping error[%d]", SYSTEM_ERROR);
			nRet = IMVS_EC_RESOURCE_CREATE;
			break;
		}

		//映射视图，获得共享内存地址
		hMapView = SHM_ReadMapView(hFileMapping);
		if (NULL == hMapView)
		{
			LOG_ERROR("ShareMemory2File fail, MapViewOfFile error[%d]", SYSTEM_ERROR);
			nRet = IMVS_EC_RESOURCE_CREATE;
			break;
		}

		//从共享内存拷贝数据
        SHM_uint64 nImageLenTmp = *((SHM_uint64 *)hMapView);
        nImageLen = (size_t)nImageLenTmp;
		char* pData = (char *)hMapView + SHARED_MEMORY_HEADER_LEN;//数据起始地址
#if (defined _WIN32 || defined _WIN64)
		pFile = _tfopen(pszFileName, _T("wb"));
#else
		pFile = fopen(pszFileName, _T("wb"));
#endif
		if (NULL == pFile)
		{
			//LOG_ERROR("Open file[%s] fail, err[%d]", ToMultibyte(pszFileName).c_str(), SYSTEM_ERROR);
            LOG_ERROR("Open file fail, err[%d]", SYSTEM_ERROR);
			nRet = IMVS_EC_FILE_OPEN;
			break;
		}

		const size_t nOnceWriteLen = 16 * 1024;//每次写入大小
		size_t nDataLen = nImageLen;
		while (nDataLen > 0)
		{
			if (nDataLen < nOnceWriteLen)
			{
				if (nDataLen != fwrite(pData, 1, nDataLen, pFile))
				{
					//LOG_ERROR("fwrite[%s] fail, len[%lu] err[%d]", ToMultibyte(pszFileName).c_str(), nDataLen, SYSTEM_ERROR);
                    LOG_ERROR("fwrite fail, len[%lu] err[%d]", nDataLen, SYSTEM_ERROR);
                    nRet = IMVS_EC_FILE_SAVE;
					break;
				}
				else
				{
					//写完跳出
					break;
				}
			}
			else
			{//每次写入nOnceWriteLen
				if (nOnceWriteLen != fwrite(pData, 1, nOnceWriteLen, pFile))
				{
					//LOG_ERROR("fwrite[%s] fail, len[%lu] err[%d]", ToMultibyte(pszFileName).c_str(), nOnceWriteLen, SYSTEM_ERROR);
                    LOG_ERROR("fwrite fail, len[%lu] err[%d]", nOnceWriteLen, SYSTEM_ERROR);
                    nRet = IMVS_EC_FILE_SAVE;
					break;
				}
				else
				{
					nDataLen -= nOnceWriteLen;
					pData += nOnceWriteLen;
				}
			}//end else

		}//end while

		if (bFlush)
		{
			fflush(pFile);
#if (defined _WIN32 || defined _WIN64)
			//确保文件从系统缓存中写入到磁盘文件
			_commit(_fileno(pFile));
#else
			::fsync(::fileno(pFile));
#endif
		}

	} while (0);

	if (hMapView)
	{
		SHM_UnMapView(hMapView, nImageLen);
		hMapView = NULL;
	}

	if (INVALID_SHM_HANDLE != hFileMapping)
	{
        SHM_CloseReadMapping(hFileMapping);
		hFileMapping = INVALID_SHM_HANDLE;
	}

	if (NULL != pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}

	return nRet;
}



/** @fn     Data2ShareMemory()
*  @brief  将数据写入共享内存，要保证每次共享内存的名称与hMapping一致
*  @return 成功,返回IMVS_EC_OK;失败,返回错误码
*/
int Data2ShareMemory(const char* pData, const size_t nSize, const char* strShareMemName, SHM_HANDLE& hMapping, void*& pBuffView)
{
	int nRet = IMVS_EC_UNKNOWN;
	try
	{
		if ((NULL == pData) || (0 >= nSize) || (NULL == strShareMemName))
		{
			nRet = IMVS_EC_PARAM;
			throw nRet;
		}

		// 预留
        const size_t CM_RESERVER_LEN = 0;

		// 映射总长度
		size_t nMappingLen = nSize + SHARED_MEMORY_HEADER_LEN + CM_RESERVER_LEN;

		SHM_DestroyWriteShm(hMapping, pBuffView, strShareMemName);

		// 创建共享映射
		hMapping = SHM_CreateMapping(strShareMemName, nMappingLen);
		if (INVALID_SHM_HANDLE == hMapping)
		{
			LOG_ERROR("CreateFileMapping fail, Len[%d]. LastError:[%d]", nMappingLen, SYSTEM_ERROR);
			nRet = IMVS_EC_OPEN_FILEMAPPING;
			throw nRet;
		}

		// 映射共享区域到进程内
		pBuffView = SHM_WriteMapView(hMapping, nMappingLen);
		if (NULL == pBuffView)
		{
			LOG_ERROR("MapViewOfFile fail. LastError:[%d]", SYSTEM_ERROR);
			nRet = IMVS_EC_OPEN_FILEMAPPING;
			throw nRet;
		}

		// 前8字节为点集数据大小
        *(SHM_uint64*)(pBuffView) = (SHM_uint64)nSize;
		// 拷贝界面数据
		memcpy((char*)pBuffView + SHARED_MEMORY_HEADER_LEN, pData, nSize);
	}
	catch (...)
	{
		LOG_ERROR("catch... nRet = [%x]", nRet);
		SHM_DestroyWriteShm(hMapping, pBuffView, strShareMemName);
		return nRet;
	}

	return IMVS_EC_OK;
}

int File2ShareMemory(const SHM_tchar* pszFileName, const char* strShareMemName, SHM_HANDLE& hMapping, void*& pBuffView)
{
	if ((NULL == pszFileName) || (NULL == strShareMemName))
	{
		return IMVS_EC_PARAM;
	}

	FILE* pFile = NULL;
	char* pBuffer = NULL;
	size_t nFileLen = 0;//文件长度
	size_t nReadLen = 0;//文件长度
	const size_t nOnceReadLen = 8 * 1024;//每次读取长度
#if (defined _WIN32 || defined _WIN64)
	pFile = _tfopen(pszFileName, _T("rb"));
#else
	pFile = fopen(pszFileName, _T("rb"));
#endif
	if (NULL == pFile)
	{
		//LOG_ERROR("Open file[%s] fail, err[%u]", ToMultibyte(pszFileName).c_str(), SYSTEM_ERROR);
        LOG_ERROR("Open file fail, err[%u]", SYSTEM_ERROR);
        return IMVS_EC_FILE_OPEN;
	}

	int nRet = IMVS_EC_OK;
	try
	{
		pBuffer = new(std::nothrow) char[nOnceReadLen];
		if (NULL == pBuffer)
		{
			LOG_ERROR("New buffer[%u] fail.", nOnceReadLen);
			nRet = IMVS_EC_OUTOFMEMORY;
			throw nRet;
		}

		SHM_DestroyWriteShm(hMapping, pBuffView, strShareMemName);

        //if (fseek(pFile, 0, SEEK_END) < 0)
#ifdef _WIN32
        if (_fseeki64(pFile, 0, SEEK_END) < 0)
#else
        if (fseeko64(pFile, 0, SEEK_END) < 0)
#endif
		{
			LOG_ERROR("SEEK_END fail[%u].", SYSTEM_ERROR);
			nRet = IMVS_EC_FILE_OPEN;
			throw nRet;
		}
		//nFileLen = ftell(pFile);//文件长度
#ifdef _WIN32
        nFileLen = _ftelli64(pFile);
#else
        nFileLen = ftello64(pFile);
#endif
		if (nFileLen < 0)
		{
			LOG_ERROR("ftell fail[%u].", SYSTEM_ERROR);
			nRet = IMVS_EC_FILE_OPEN;
			throw nRet;
		}

		//if (fseek(pFile, 0, SEEK_SET) < 0)
#ifdef _WIN32
        if (_fseeki64(pFile, 0, SEEK_SET) < 0)
#else
        if (fseeko64(pFile, 0, SEEK_SET) < 0)
#endif
		{
			LOG_ERROR("fseek SEEK_SET fail, error[%d].", SYSTEM_ERROR);
			nRet = IMVS_EC_FILE_OPEN;
			throw nRet;
		}

		// 将界面数据存入共享内存
		const size_t CM_RESERVER_LEN = 0;//预留长度

		// 映射总长度
		size_t nMappingLen = nFileLen + SHARED_MEMORY_HEADER_LEN + CM_RESERVER_LEN;
		// 创建共享映射
		hMapping = SHM_CreateMapping(strShareMemName, nMappingLen);
		if (INVALID_SHM_HANDLE == hMapping)
		{
			LOG_ERROR("CreateFileMapping fail, Len[%d]. LastError:[%d]", nMappingLen, SYSTEM_ERROR);
			nRet = IMVS_EC_OPEN_FILEMAPPING;
			throw nRet;
		}

		// 映射共享区域到进程内
		pBuffView = SHM_WriteMapView(hMapping, nMappingLen);
		if (NULL == pBuffView)
		{
			LOG_ERROR("MapViewOfFile fail. LastError:[%d]", SYSTEM_ERROR);
			nRet = IMVS_EC_OPEN_FILEMAPPING;
			throw nRet;
		}

		// 前4字节为点集数据大小
        *(SHM_uint64*)(pBuffView) = (SHM_uint64)nFileLen;
		char* pDestView = (char*)pBuffView + SHARED_MEMORY_HEADER_LEN;
		size_t nOffset = 0;

		do
		{
			nReadLen = fread(pBuffer, 1, nOnceReadLen, pFile);
			// 拷贝界面数据
			memcpy(pDestView + nOffset, pBuffer, nReadLen);
			nOffset += nReadLen;
		} while (nReadLen == nOnceReadLen && !feof(pFile));

		if (nFileLen != nOffset)
		{
			LOG_ERROR("File len[%d] read len[%d]", nFileLen, nOffset);
		}
	}
	catch (...)
	{
		LOG_ERROR("catch... nRet = [%x]", nRet);
		SHM_DestroyWriteShm(hMapping, pBuffView, strShareMemName);
	}

	if (NULL != pFile)
	{
		fclose(pFile);
	}

	if (NULL != pBuffer)
	{
		delete[] pBuffer;
	}

	return IMVS_EC_OK;
}



