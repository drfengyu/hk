#ifdef EXAMPLEMODULE_EXPORTS
#define LINEMODULE_API __declspec(dllexport)
#else
#define LINEMODULE_API __declspec(dllimport)
#endif
#include "VmModuleBase.h"
#include "VmAlgModuBase.h"
#include "ErrorCodeDefine.h"
#include "VmModuleSharedMemoryBase.h"

// This class is exported from the LineModule.dll
class LINEMODULE_API CAlgorithmModule : public CVmAlgModuleBase, public CModuleSharedMemoryBase
{
public:
	// 构造
	explicit CAlgorithmModule();
	
	// 析构
	virtual ~CAlgorithmModule();

public:

	// 初始化
	int Init();

	// 进行算法
	int Process(IN void* hInput, IN void* hOutput, IN MVDSDK_BASE_MODU_INPUT* modu_input);

	// 获取算法参数
	int GetParam(IN const char* szParamName, OUT char* pBuff, IN int nBuffSize, OUT int* pDataLen);

	// 设置算法参数
	int SetParam(IN const char* szParamName, IN const char* pData, IN int nDataLen);

public:
	//void* m_hModule;   // 模块句柄 - 4.3 在基类中定义了


private:

	//======自定义变量======//

};


/////////////////////////////模块须导出的接口（实现开始）//////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif
    
    // 采用__stdcall调用约定，且须在.def文件中增加接口描述。
	LINEMODULE_API CAbstractUserModule* __stdcall CreateModule(void* hModule);
	LINEMODULE_API void __stdcall DestroyModule(void* hModule, CAbstractUserModule* pUserModule);

#ifdef __cplusplus
};
#endif
/////////////////////////////模块须导出的接口（实现结束）//////////////////////////////////////////
//////======文件尾======//