#include "CrossPlatformFunc.h"

#ifndef _WIN32

int GetLastError()
{
	return errno;
}

FILE* _tfopen(const tchar* file, const tchar* mode)
{
	return fopen(file, mode);
}

int fopen_s(FILE** pFile, const char *filename, const char *mode)
{
	*pFile = fopen(filename, mode);
	if (NULL == *pFile)
	{
		return errno;
	}

	return 0;
}



int _ftime64_s(struct __timeb64 *tp)
{
	timespec ts;
	int ret = clock_gettime(CLOCK_REALTIME, &ts);
	if (ret == 0)
	{
		tp->time    = ts.tv_sec;
		tp->millitm = double(ts.tv_nsec / 1000000);
	}
	return ret;
}


// int _taccess_s(const tchar *path, int mode)
// {
// 	struct stat st;
// 	return lstat(UnicodeToUTF8(path).c_str(), &st);
// 	return 0;
// }

int _access(const char *path, int mode)
{
	int nRet = 0;
	struct stat st;
	nRet = lstat(path, &st);
	if (0 == nRet)
	{
		return 0; 
	}
	else 
	{
		return -1;
	}
}

int _access_s(const char *path, int mode)
{
	return _access(path, mode);
}

int _waccess_s(const tchar *path, int mode)
{
	int nRet = 0;
	struct stat st;
#ifdef _UNICODE
	nRet = lstat(UnicodeToUTF8(path).c_str(), &st);
#else
	nRet = lstat(path, &st);
#endif // _UNICODE

	if (0 == nRet)
	{
		return 0; 
	}
	else 
	{
		return -1;
	}
}


// int _tmkdir(const tchar *path)
// {
// 	return mkdir(UnicodeToUTF8(path).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
// 	return 0;
// }

int _mkdir(const char *path)
{
	return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}


int _stricmp(const char * dst, const char * src)
{
	return strcasecmp(dst, src);
}

int stricmp(const char * dst, const char * src)
{
	return strcasecmp(dst, src);
}


void Sleep(int nMillisecond)
{
	usleep(nMillisecond * 1000);
}


int GetCurrentProcessId()
{
	return getpid();
}

char *strcpy_s(char *dst, unsigned int size, const char *src)
{
	dst[size - 1] = '\0';
	return strncpy(dst, src, size - 1);
}

char* strncpy_s(char *dst, unsigned int detSize, const char *src,unsigned int srcSize)
{
	dst[detSize - 1] = '\0';
	return strncpy(dst, src, detSize - 1);
}

int memcpy_s(void *det, size_t detSize, const void * src, size_t srcSize)
{
	int errorcode = 0;
	if (srcSize > detSize || src == NULL || det == NULL)
	{
		return -1;
	}
	else
	{
		memcpy(det, src, srcSize);
	}

	return 1;
}

void OutputDebugStringA(char* _chszLog)
{

}

#endif