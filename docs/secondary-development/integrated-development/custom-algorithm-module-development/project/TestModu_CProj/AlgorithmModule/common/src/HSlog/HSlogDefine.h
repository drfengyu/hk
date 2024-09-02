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

#ifndef _HIK_SPEED_LOG_ASYNC_DEFINE_H_
#define _HIK_SPEED_LOG_ASYNC_DEFINE_H_


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN  //解决winsock.h和winsock2.h类型重定义问题
#include <windows.h>
#include <string>
#endif

#ifdef _UNICODE
#define HSLOG_CHAR                 wchar_t/*WCHAR*/
#define HSLOG_string               std::wstring
#define HSLOG_PATH_DIVIDE_STRING   L"\\"  //路径分隔符（Unicode）
#define HSLOG_PATH_POSTFIX         L"."  //后缀标识（Unicode）
#define HSLOG_STRING_PREFIX(s)     L##s
#else
#define HSLOG_CHAR                 char
#define HSLOG_string               std::string
#define HSLOG_PATH_DIVIDE_STRING   "/"
#define HSLOG_PATH_POSTFIX         "."
#define HSLOG_STRING_PREFIX(s)     s
#endif


enum HSlog_Level
{
    HSlog_trace = 0,
    HSlog_debug,
    HSlog_info,
    HSlog_warn,
    HSlog_err,
    HSlog_critical,
    HSlog_off,
};



//获取模块名称类，该类在头文件中定义，但不是导出类。
//使用该日志库的模块会直接将该类实现编译到代码中，能够在运行时获取模块的动态库名称
class CHSlogModuleName
{
public:
    CHSlogModuleName()
    {
    }

    ~CHSlogModuleName()
    {
    }

    //静态获取模块名称接口，保证一个模块只有第一次打日志时执行
    static std::string& GetModuleName()
    {
        //模块名称
        static std::string HSlog_s_strModuleName = GetDllFileNameUtf8();
        return HSlog_s_strModuleName;
    }

    static std::string GetDllFileNameUtf8()
    {
        //OutputDebugStringA("TEST  ");
        HSLOG_string strTmp;
        GetDllFileName(strTmp);
        std::string strName = HSlog_ToUtf8(strTmp);
        //std::string strddd = "TEST  " + strName;
        //OutputDebugStringA(strddd.c_str());
        return strName;
    }

    //内部接口，获取dll文件名称
    static const HSLOG_CHAR* GetDllFileName(HSLOG_string& strModuleName)
    {
        //HSLOG_string strModuleName;
        strModuleName.clear();
#if _WIN32
        wchar_t chszModuleName[MAX_PATH] = { 0 };
        HMODULE hModule = NULL;
        GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)&CHSlogModuleName::GetDllFileName, //这是函数名，强转
            &hModule);
        DWORD len = GetModuleFileName(hModule, chszModuleName, MAX_PATH);
        strModuleName = chszModuleName;

#else
        Dl_info dl_info;
        dladdr((void*)GetDllFilePath, &dl_info);
        strModuleName = dl_info.dli_fname;
        //注：如果库放在可执行程序同级目录或子目录下调用，则得到路径是相对于可执行程序，否则得到从根目录起的绝对路径

#endif

        do
        {
            size_t nn = strModuleName.rfind(HSLOG_PATH_DIVIDE_STRING);
            if (strModuleName.npos == nn)
            {
                break;
            }
            strModuleName = strModuleName.substr(nn + 1);

            //去除后缀
            nn = strModuleName.rfind(HSLOG_PATH_POSTFIX);
            if (strModuleName.npos == nn)
            {
                break;
            }
            strModuleName = strModuleName.substr(0, nn);
        } while (0);
        return strModuleName.c_str();
    }

    //内部接口，Unicode转成utf8
    static std::string HSlog_ToUtf8(const HSLOG_string str)
    {
#ifdef UNICODE
        if (str.length() == 0)
        {
            return "";
        }

        int  nCodePage = CP_UTF8;
        char*  pOutBuff = NULL;
        std::string strRst = "";
        const  int nTmpBuffLen = 256;
        char   pTmpBuff[nTmpBuffLen] = { 0 };
        bool   bHeapMem = false;

        try
        {
            do
            {
                int nOutLen = WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
                if (nOutLen <= 0)
                {
                    break;
                }

                // 对于小字符串，优先使用栈内存
                if (nOutLen <= nTmpBuffLen)
                {
                    pOutBuff = pTmpBuff;
                }
                else
                {
                    pOutBuff = new char[nOutLen];
                    bHeapMem = true;
                }

                nOutLen = WideCharToMultiByte(nCodePage, 0, str.c_str(), -1, pOutBuff, nOutLen, NULL, NULL);
                if (nOutLen <= 0)
                {
                    break;
                }
                strRst = pOutBuff;

            } while (false);
        }
        catch (...)
        {
           
        }

        if (bHeapMem && pOutBuff != NULL)
        {
            delete[] pOutBuff;
        }
        return strRst;
#else
        return str;
#endif
    }


};

//定义宏，获取模块的动态库名称，便于日志中搜索查看
#define  HSlog_ModuleName   CHSlogModuleName::GetModuleName().c_str()

//算法模块/逻辑模块printf格式打印日志，必须传递模块ID
//举例：LOG_INFO(m_nModuId, "test log: cmd[%d] out[%s] file[%s]", nCmd, chTmp, strTmp.c_str());
#if (defined _WIN32 || defined _WIN64)
#pragma   warning(error:4003)//如果不输入moduID报错
#define MLOG_ERROR(mid, fmt, ...)        if(HSlog_ShouldLog(HSlog_err))   HSlog_LogPrint(HSlog_err,  "[%s] [ModuId:%d] [%s@%d] "fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define MLOG_WARN(mid, fmt, ...)         if(HSlog_ShouldLog(HSlog_warn))  HSlog_LogPrint(HSlog_warn, "[%s] [ModuId:%d] [%s@%d] "fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##__VA_ARGS__)    
#define MLOG_INFO(mid, fmt, ...)         if(HSlog_ShouldLog(HSlog_info))  HSlog_LogPrint(HSlog_info, "[%s] [ModuId:%d] [%s@%d] "fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##__VA_ARGS__)    
#define MLOG_DEBUG(mid, fmt, ...)        if(HSlog_ShouldLog(HSlog_debug)) HSlog_LogPrint(HSlog_debug,"[%s] [ModuId:%d] [%s@%d] "fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##__VA_ARGS__)    
#define MLOG_TRACE(mid, fmt, ...)        if(HSlog_ShouldLog(HSlog_trace)) HSlog_LogPrint(HSlog_trace,"[%s] [ModuId:%d] [%s@%d] "fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##__VA_ARGS__)   
#else
#define MLOG_ERROR(mid, fmt, args...)    if(HSlog_ShouldLog(HSlog_err))   HSlog_LogPrint(HSlog_err,  "[%s] [ModuId:%d] [%s@%d] " fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##args)
#define MLOG_WARN(mid, fmt, args...)     if(HSlog_ShouldLog(HSlog_warn))  HSlog_LogPrint(HSlog_warn, "[%s] [ModuId:%d] [%s@%d] " fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##args)
#define MLOG_INFO(mid, fmt, args...)     if(HSlog_ShouldLog(HSlog_info))  HSlog_LogPrint(HSlog_info, "[%s] [ModuId:%d] [%s@%d] " fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##args)
#define MLOG_DEBUG(mid, fmt, args...)    if(HSlog_ShouldLog(HSlog_debug)) HSlog_LogPrint(HSlog_debug,"[%s] [ModuId:%d] [%s@%d] " fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##args)
#define MLOG_TRACE(mid, fmt, args...)    if(HSlog_ShouldLog(HSlog_trace)) HSlog_LogPrint(HSlog_trace,"[%s] [ModuId:%d] [%s@%d] " fmt, HSlog_ModuleName, mid, __FUNCTION__, __LINE__, ##args)
#endif

#define LOG_ERROR(fmt, ...)         MLOG_ERROR(-1, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)          MLOG_WARN(-1, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)          MLOG_INFO(-1, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)         MLOG_DEBUG(-1, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)         MLOG_TRACE(-1, fmt, ##__VA_ARGS__)

#endif //end of _HIK_SPEED_LOG_ASYNC_DEFINE_H_
