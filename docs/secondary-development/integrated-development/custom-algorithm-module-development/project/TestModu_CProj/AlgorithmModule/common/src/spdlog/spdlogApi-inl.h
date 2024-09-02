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
#ifndef __SPDLOG_API_INL_H__
#define __SPDLOG_API_INL_H__

#if (defined _WIN32 || defined _WIN64)
#pragma warning(disable:4996)
#else
#include <pthread.h>
#include <semaphore.h>
#endif



#define  LOG_FILE_ROTATE_COUNT_MODULE       (1)             //算法模块日志文件回滚数量

#define  LOG_FLUSH_EVERY_SECOND             (5*1000)        //定时刷新时间

#if (defined _WIN32 || defined _WIN64)
#define  LOG_FILE_MODU_RELATIVE_TIER        (3)             //模块日志文件相对路径层级
#else
#define  LOG_FILE_MODU_RELATIVE_TIER        (2)             //模块日志文件相对路径层级
#endif



//可变输入格式化，最后换行
#define SPD_msgFormatA(buf, fmt) \
    do { \
    va_list ap; \
    va_start(ap, fmt); \
    int ntmp = SPD_vsnprintf(buf, LOG_BUFFER_LENGTH-2, fmt, ap); \
    va_end(ap); \
    ntmp < 0 ? (buf[LOG_BUFFER_LENGTH-2] = '\n', buf[LOG_BUFFER_LENGTH-1] = 0) : (buf[ntmp] = '\n', buf[ntmp+1] = 0);\
       } while (0)



//单例
class FUNC_LOCAL CspdlogApi
{
public:
    ~CspdlogApi()
    {
        //OutputDebugStringA("spdlog: ~CspdlogApi begin");
        try
        {
            Deinit();
        }
        catch (...)
        {
        	
        }
        //OutputDebugStringA("spdlog: ~CspdlogApi end");
    }

	FUNC_LOCAL inline static CspdlogApi* Instance();
    
    inline int LogInitComm(const SPD_CHAR* pchFileName, bool bFlushOnTimer = true, unsigned int nFileSize = LOG_FILE_SIZE_MAX, unsigned int nRotateCount = LOG_FILE_ROTATE_COUNT_DEFAULT);
    inline int LogInit4Module(const SPD_CHAR* pchModuleName);

    inline void Deinit();

    inline void SetLogger(std::shared_ptr<spdlog::logger>& plogger);

    inline std::shared_ptr<spdlog::logger>& GetLogger();

    inline void LogPrint(SPD_LEVEL nlogLevel, const char* format, ...);

#if (defined _WIN32 || defined _WIN64)
	static inline unsigned __stdcall FlushLogThread(LPVOID pParam);
#else
	static inline void* FlushLogThread(void * pParam);
#endif

    inline int StartFlushThread();

    inline void StopThread();

    inline void DoFlushLog();

private:
    CspdlogApi()
    {
        //OutputDebugStringA("spdlog: CspdlogApi begin");
#if (defined _WIN32 || defined _WIN64)
        m_hFlushThread = nullptr;
        m_hFlushEvent = nullptr;
#else
        m_iEvt = 1;
#endif
        m_bConstructEnd = true;
        //OutputDebugStringA("spdlog: CspdlogApi end");
    }
    
    inline bool IsExistDir(const SPD_CHAR* path);
    inline bool MakeDir(const SPD_CHAR* path);
    //初始化模块的日志路径
    inline int InitModuleLogDirectory(SPD_STRING& strProcDir);

    
private:
    bool   m_bConstructEnd = false;
    std::shared_ptr<spdlog::logger> m_logger;
    

#if (defined _WIN32 || defined _WIN64)
    void*       m_hFlushThread;//定时刷新线程
    HANDLE      m_hFlushEvent;//定时刷新事件
#else
    pthread_t   m_hFlushThread;//定时刷新线程
    sem_t       m_hFlushEvent;//定时刷新事件
    int         m_iEvt;//停止信号有效标记（0，信号有效，非0 ，无效）
#endif
};

FUNC_LOCAL CspdlogApi* CspdlogApi::Instance()
{
    //OutputDebugStringA("spdlog: Instance begin");
    static CspdlogApi s_olog;
    //OutputDebugStringA("spdlog: Instance end");
    return &s_olog;
}

#if (defined _WIN32 || defined _WIN64)
unsigned __stdcall CspdlogApi::FlushLogThread(LPVOID pParam)
{
    if (NULL != pParam)
    {
        CspdlogApi* pThis = (CspdlogApi*)pParam;
        pThis->DoFlushLog();
    }
    return 0;
}
#else
void* CspdlogApi::FlushLogThread(void * pParam)
{
    if (NULL == pParam)
    {
        return NULL;
    }
    CspdlogApi* pThis = reinterpret_cast<CspdlogApi*>(pParam);
    pThis->DoFlushLog();

    return NULL;
}

#endif

int CspdlogApi::StartFlushThread()
{
    int nRet = 0;
#if (defined _WIN32 || defined _WIN64)
    do
    {
        m_hFlushEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//自动复位，初始为无信号
        if (NULL == m_hFlushEvent)
        {
            LOG_ERROR("CreateEvent error[%d]", GetLastError());
            nRet = 0xE0000002;
            break;
        }

        m_hFlushThread = (void *)::_beginthreadex(NULL, 0, FlushLogThread, Instance(), 0, NULL);
        if (NULL == m_hFlushThread)
        {
            LOG_ERROR("_beginthreadex error[%d]", GetLastError());
            nRet = 0xE0000002;
            break;
        }
    } while (0);
#else
    do 
    {
        nRet = pthread_create(&m_hFlushThread,NULL,FlushLogThread,(void*)this);
        if (0 != nRet)
        {
            printf("pthread_create error[%d]", nRet);
            nRet = 0xE0000002;
            break;
        }

        m_iEvt = sem_init(&m_hFlushEvent,0,0);
        if (0 != m_iEvt)
        {
            nRet = 0xE0000002;
            break;
        }
    } while (0);

#endif

    if (0 != nRet)
    {
        StopThread();
    }

    return nRet;
}

void CspdlogApi::DoFlushLog()
{
#if (defined _WIN32 || defined _WIN64)
    if (NULL == m_hFlushEvent)
    {
        return;
    }

    while (WAIT_OBJECT_0 != WaitForSingleObject(m_hFlushEvent, LOG_FLUSH_EVERY_SECOND))
    {
        if (m_logger == nullptr)
        {
            continue;
        }
        m_logger->flush();
    }

#else
    if (0 != m_iEvt)
    {
        return;
    }

    while(1)
    {
        struct timespec stTimeOut;
        if (clock_gettime(CLOCK_REALTIME, &stTimeOut) == -1)
        {
            //获取实时时间失败
        }
        stTimeOut.tv_sec += LOG_FLUSH_EVERY_SECOND / 1000;
		sem_timedwait(&m_hFlushEvent, &stTimeOut);
        if (ETIMEDOUT == errno)
        {//等待超时
            if (m_logger != nullptr)
            {
                m_logger->flush();
            }
        }
        else
        {
            return;
        }
    }

#endif
    
}

void CspdlogApi::StopThread()
{
#if (defined _WIN32 || defined _WIN64)
    if (NULL != m_hFlushEvent)
    {
        SetEvent(m_hFlushEvent);//设置事件信号
        WaitForSingleObject(m_hFlushThread, INFINITE);
        CloseHandle(m_hFlushThread);//关闭线程句柄
        CloseHandle(m_hFlushEvent);//关闭事件句柄
        m_hFlushThread = NULL;
        m_hFlushEvent = NULL;
    }
#else
    if (0 == m_iEvt)
    {
        sem_post(&m_hFlushEvent);

        pthread_join(m_hFlushThread, NULL);

        sem_destroy(&m_hFlushEvent);
        m_iEvt = 1;
    }
    
#endif
}

//通用初始化接口，调用者需保证日志文件夹存在，否则返回错误
int CspdlogApi::LogInitComm(const SPD_CHAR* pchFileName, bool bFlushOnTimer/* = true*/, unsigned int nFileSize/* = LOG_FILE_SIZE_MAX*/, unsigned int nRotateCount/* = LOG_FILE_ROTATE_COUNT_DEFAULT*/)
{
    if (nullptr == pchFileName)
    {
        return 0xE0000001;//参数错误
    }

    //初始化前判断，多个模块并发初始化时，会存在单例接口返回后，但构造尚未结束
    if (!m_bConstructEnd)
    {
#if (defined _WIN32 || defined _WIN64)
		Sleep(1);//等待构造完成
#else
		usleep(1000);
#endif
        if (!m_bConstructEnd)
        {//仍然没有完成，则返回错误
            return 0xE0000008;
        }
    }
        
    try
    {
        std::shared_ptr<spdlog::logger> plogger;
        //使用回滚日志，线程安全
#if (defined _WIN32 || defined _WIN64)
        std::string strLogName = "default_logger";
#else
        //linux中两个库日志名称相同时会抛异常
        std::string strLogName = pchFileName;
        size_t nn = strLogName.rfind("/");
        if (std::string::npos != nn)
        {
            strLogName = strLogName.substr(nn+1);
        }
        nn = strLogName.find(".");
        if (std::string::npos != nn)
        {
            strLogName = strLogName.substr(0,nn);
        }
        printf("spdlog--name[%s] \n", strLogName.c_str());
#endif
        plogger = spdlog::rotating_logger_mt(strLogName.c_str(), pchFileName, nFileSize, nRotateCount);
        if (plogger == nullptr)
        {
            throw 0xE0000203;//文件不存在
        }
        //默认日志等级为info
        plogger->set_level(SPD_DEFAULT_LEVEL);

        //%-5L等级，%t线程号，%#%!打印函数和行号，%v日志内容
        //m_logger->set_pattern("%Y-%m-%d %H:%M:%S.%e %-5L [%t] %#%! %v"); 
        plogger->set_pattern("%Y-%m-%d %H:%M:%S.%e %-5L [%t] %v");

        SetLogger(plogger);

        //默认情况下，开启刷新间隔，内部会开启线程刷新。算法模块中不开启
        if (bFlushOnTimer)
        {
            int nRet = StartFlushThread();
            if (0 != nRet)
            {
                throw nRet;
            }
        }
        else
        {
            //不开启刷新间隔时，默认日志等级时，刷新磁盘
            plogger->flush_on(SPD_DEFAULT_LEVEL);
        }
        
    }
    catch (...)
    {
        return 0xE0000203;//文件不存在
    }
    
    return 0;
}

//模块日志初始化，不需要关心日志文件夹是否存在，内部负责创建
int CspdlogApi::LogInit4Module(const SPD_CHAR* pchModuleName)
{
    if (nullptr == pchModuleName)
    {
        return 0xE0000001;//参数错误
    }

    //初始化前判断，多个模块并发初始化时，会存在单例接口返回后，但构造尚未结束
    if (!m_bConstructEnd)
    {
        //OutputDebugStringA("spdlog: !m_bConstructEnd");
#if (defined _WIN32 || defined _WIN64)
		Sleep(1);//等待构造完成
#else
		usleep(1000);
#endif
        if (!m_bConstructEnd)
        {//仍然没有完成，则返回错误
            //OutputDebugStringA("spdlog: sleep !m_bConstructEnd");
            return 0xE0000008;
        }
    }
    //OutputDebugStringA("spdlog: init first");

    try
    {
        //获取log文件夹路径
        SPD_STRING strLogDir;
        int nRet = InitModuleLogDirectory(strLogDir);
        if (0 != nRet)
        {
            throw nRet;
        }
#if (defined _WIN32 || defined _WIN64)
        strLogDir = strLogDir + SPD_STRING_PREFIX("\\") + pchModuleName + SPD_STRING_PREFIX(".log");
#else
        strLogDir = strLogDir + SPD_STRING_PREFIX("/") + pchModuleName + SPD_STRING_PREFIX(".log");
#endif
#if (defined _WIN32 || defined _WIN64)
        std::string strLogName = "default_logger";
#else
        std::string strLogName = pchModuleName;
#endif
        std::shared_ptr<spdlog::logger> plogger;
        plogger = spdlog::rotating_logger_mt(strLogName.c_str(), strLogDir.c_str(), LOG_FILE_SIZE_MAX, LOG_FILE_ROTATE_COUNT_MODULE);
        if (plogger == nullptr)
        {
            throw 0xE0000203;//文件不存在
        }
        
        //算法模块的日志等级为error
        plogger->set_level(spdlog::level::err);

        plogger->set_pattern("%Y-%m-%d %H:%M:%S.%e %-5L [%t] %v");
        //error日志立即写磁盘
        plogger->flush_on(spdlog::level::err);
        SetLogger(plogger);
    }
    catch (...)
    {
        return 0xE0000203;//文件不存在
    }
    return 0;
}

void CspdlogApi::Deinit()
{
    StopThread();
    if (m_logger != nullptr)
    {
        //正常退出时，将缓存中的日志写入磁盘
        m_logger->flush();
        m_logger = nullptr;
    }
}



void CspdlogApi::SetLogger(std::shared_ptr<spdlog::logger>& plogger)
{
    m_logger = plogger;
}

std::shared_ptr<spdlog::logger>& CspdlogApi::GetLogger()
{
    return m_logger;
}

//打印日志
void CspdlogApi::LogPrint(SPD_LEVEL nlogLevel, const char* format, ...)
{
    try
    {
        if (m_logger == nullptr)
        {
            return;
        }

        if (!m_logger->should_log(nlogLevel))
        {
            return;
        }

        char szMsg[LOG_BUFFER_LENGTH];//提高效率，不需memset为0，msgFormatA能保证格式化为字符串
        SPD_msgFormatA(szMsg, format);
        m_logger->log(nlogLevel, szMsg);
    }
    catch (...)
    {
        return;
    }    
}

//判断路径是否存在
bool CspdlogApi::IsExistDir(const SPD_CHAR* path)
{
    if (nullptr == path)
    {
        return false;
    }

#if (defined _WIN32 || defined _WIN64)
    #if defined(SPDLOG_WCHAR_FILENAMES)
        if (_waccess(path, 0) != -1)
    #else
        if (_access(path, 0) != -1)
    #endif
#else
	struct stat st;
	if (lstat(path, &st) == 0)
#endif
    {
        return true;
    }

    return false;
}

//创建路径
bool CspdlogApi::MakeDir(const SPD_CHAR* path)
{
#if (defined _WIN32 || defined _WIN64)
    if (nullptr == path)
    {
        return false;
    }

    if (CreateDirectory(path, NULL))
    {
        return true;
    }

    DWORD dwErr = GetLastError();
    if (ERROR_ALREADY_EXISTS == dwErr)
    {
        return true;
    }
        
    if (ERROR_PATH_NOT_FOUND == dwErr)
    {
        SPD_STRING strNewpath = path;
        size_t npos = strNewpath.rfind(SPD_STRING_PREFIX("\\"));
        strNewpath = strNewpath.substr(0, npos);
     
        if (MakeDir(strNewpath.c_str()))
        {
            if (CreateDirectory(path, NULL) || (ERROR_ALREADY_EXISTS == GetLastError()))
            {
                return true;
            }
        }
    }
#else
    if ((0 == mkdir(path, 0777)) || (EEXIST == errno))
        return true;

    if (ENOENT == errno)
    {
        char newpath[PATH_MAX] = { 0 };
        char *p = nullptr;
        strcpy(newpath, path);
        p = strrchr(newpath, '/');
        if (p == nullptr)
            return false;

        *p = '\0';
        if (MakeDir(newpath))
        {
            if ((0 == mkdir(path, 0777)) || (EEXIST == errno))
                return true;
        }
    }
#endif

    return false;
}

//初始化模块日志路径
int CspdlogApi::InitModuleLogDirectory(SPD_STRING& strProcDir)
{
#if (defined _WIN32 || defined _WIN64)
    SPD_CHAR chModuleName[MAX_PATH] = { 0 };
    //F:\01MyCode\C++\hikRobotics\VisionMaster\trunk\Public_Release\VmModuleProxy\x64\VmModuleProxy.exe
	//D:\SVN_Project\VisionMaster\trunk_v4x\linux_release\ubuntu_x64\vmModuleProxy\VmModuleProxy.out
    unsigned int nLength = GetModuleFileName(NULL, chModuleName, MAX_PATH);
    if (0 == nLength || nLength >= (MAX_PATH-1))
    {
        printf("GetModuleFileName fail, error[%d]. \n", GetLastError());
        return 0xE00000FF;
    }
#else
    SPD_CHAR chModuleName[PATH_MAX] = { 0 };
	size_t nLen = PATH_MAX;
	ssize_t c = readlink("/proc/self/exe", chModuleName, nLen);
    if (c <= 0 || c >= (PATH_MAX-1))
    {
        return 0xE00000FF;
    }
        
    chModuleName[c] = '\0';
#endif

    int n = LOG_FILE_MODU_RELATIVE_TIER;
    strProcDir = chModuleName;
    size_t nnp = 0;
    while (n > 0)
    {
#if (defined _WIN32 || defined _WIN64)
        nnp = strProcDir.rfind(SPD_STRING_PREFIX("\\"));
#else
        nnp = strProcDir.rfind(SPD_STRING_PREFIX("/"));
#endif
        if (strProcDir.npos == nnp)
        {
            return 0xE00000FF;
        }
        strProcDir = strProcDir.substr(0, nnp);
        n--;
    }
    
    //算法模块日志输出路径
#if (defined _WIN32 || defined _WIN64)
    strProcDir += SPD_STRING_PREFIX("\\log\\Module");
#else
    strProcDir += SPD_STRING_PREFIX("/log/Module");
#endif

    if (IsExistDir(strProcDir.c_str()))
    {
        return 0;
    }

    if (!MakeDir(strProcDir.c_str()))
    {
        return 0xE0000203;
    }
    return 0;
}

/** @fn:    Spdlog_InitComm
* @brief:   通用初始化接口，打印日志前调用。不需要反初始化
* @param:   pchFileName    日志文件绝对路径，只创建日志文件，不创建文件夹
                           调用者需保证日志文件夹存在，否则返回错误

                           该接口默认日志等级为SPD_DEFAULT_LEVEL（info），需要修改日志等级时，可以调用Spdlog_ResetLevel接口

* @param:   bFlushOnTimer  是否开启定时刷新日志文件。
                           不开启时，遇到≥SPD_DEFAULT_LEVEL的日志等级时，自动刷新日志文件。
                           开启时日志不会立即写磁盘，每隔5s刷新一次（开启线程）。
                           默认开启。
* @return:  int 成功返回0，错误返回其他值
*/
FUNC_LOCAL int Spdlog_InitComm(const SPD_CHAR* pchFileName, bool bFlushOnTimer/* = true*/, unsigned int nFileSize/* = LOG_FILE_SIZE_MAX*/, unsigned int nRotateCount/* = LOG_FILE_ROTATE_COUNT_DEFAULT*/)
{
    static std::atomic_flag    g_spdlogInitComm = ATOMIC_FLAG_INIT;//初始化原子操作
    if (g_spdlogInitComm.test_and_set())
    {
        return 0;
    }
    int nRet = CspdlogApi::Instance()->LogInitComm(pchFileName, bFlushOnTimer, nFileSize, nRotateCount);
    if (0 != nRet)
    {
        g_spdlogInitComm.clear();
    }
    return nRet;
}

/** @fn:    Spdlog_Init4Module
* @brief:   算法模块/逻辑模块调用此接口，打印日志前调用。不需要反初始化
* @param:   pchModuleName   模块名称，如"IMVSBlobFindModu"
                            不需要关心日志文件夹是否存在，内部负责创建
* @return:  int 成功返回0，错误返回其他值
*/
FUNC_LOCAL int Spdlog_Init4Module(const SPD_CHAR* pchModuleName)
{
    //OutputDebugStringA("spdlog: Spdlog_Init4Module begin");
    static std::atomic_flag    g_spdlogInit4Module = ATOMIC_FLAG_INIT;//初始化原子操作，不用静态锁（dll并发时会崩溃）
    if (g_spdlogInit4Module.test_and_set())
    {
        //OutputDebugStringA("spdlog: Spdlog_Init4Module return");
        return 0;
    }
    int nRet = CspdlogApi::Instance()->LogInit4Module(pchModuleName);
    if (0 != nRet)
    {
        g_spdlogInit4Module.clear();
    }
    return nRet;
}

FUNC_LOCAL void Spdlog_DeInit()
{
    CspdlogApi::Instance()->Deinit();
}

/** @fn:    Spdlog_ResetLevel
* @brief:   更新日志打印等级
* @param:   nlogLevel    日志等级，参考SPD_LEVEL
                         critical、off暂不支持
* @param:   bOnFlush     实时Flush等级，开启后会将nlogLevel以上（含）的日志实时刷新磁盘
                         调试时可以设置为ture，发布时需要关闭，否则影响执行效率。
* @return:  void 成功返回0，错误返回其他值
*/
FUNC_LOCAL void Spdlog_ResetLevel(SPD_LEVEL nlogLevel, bool bOnFlush/* = false*/)
{
    std::shared_ptr<spdlog::logger> plogger = CspdlogApi::Instance()->GetLogger();
    if (plogger == nullptr)
    {
        return;
    }
    plogger->set_level(nlogLevel);

    if (bOnFlush)
    {
        plogger->flush_on(nlogLevel);
    }
}

/** @fn:    Spdlog_GetCurrentLevel
* @brief:   获取当前的日志等级
* @return:  SPD_LEVEL
*/
FUNC_LOCAL SPD_LEVEL Spdlog_GetCurrentLevel()
{
    std::shared_ptr<spdlog::logger> plogger = CspdlogApi::Instance()->GetLogger();
    if (plogger == nullptr)
    {
        return SPD_DEFAULT_LEVEL;
    }
    return plogger->level();
}


#endif//end __SPDLOG_API_INL_H__
