/************************************************************************
* 版权信息：版权所有(c) 2018, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：VmModuleBase.h
* 摘   要:  接口定义，供开发自定义模块使用。
*
* 作   者:  fenghuapeng5
* 日   期： 2018-09-10

*************************************************************************/


/* 开发自定义模块须知：

1、自定义模块以动态库的形式存在（.dll文件）
2、模块必须实现以下两个导出函数，且调用约定为 __stdcall。
   a) CAbstractUserModule* __stdcall CreateModule(void* hModule);
   b) void __stdcall DestroyModule(void* hModule, CAbstractUserModule* pUserModule);
3、若采用C++开发，请在工程中新建 .def 文件，并在其中增加导出接口描述。



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~导出接口说明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @fn     CreateModule
 * @brief  [必须实现] 创建模块实例，模块负责实现，由SDK调用。
 * @param  hModule    模块实例句柄
 * @remark 该接口由SDK调用。同一模块被SDK加载后，可能会创建多个实例。hModule表示每个实例的句柄，
           请妥善保存该句柄，调用SDK相关接口时会用到此值。

 CAbstractUserModule* __stdcall CreateModule(void* hModule);


 * @fn     DestroyModule
 * @brief  [必须实现] 销毁模块实例，模块负责实现，由SDK调用。
 * @param  hModule    模块实例句柄
 * @param  pUserModule CreateModule返回的用户模块实例
 * @remark 该接口由SDK调用。同一模块被SDK加载后，可能会创建多个实例。当某个实例需要销毁时，SDK会
           会调用此接口，使得模块有机会释放该实例所占用的资源。

 void __stdcall DestroyModule(void* hModule, CAbstractUserModule* pUserModule);



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~示例~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef _VM_MODULE_BASE_H_
#define _VM_MODULE_BASE_H_
#include "VmModuleDef.h"

#ifdef _WIN32
#ifdef  VMMODULEFRAME_EXPORTS
#    define VMMODULEFRAME_API __declspec(dllexport)
#else
#    define VMMODULEFRAME_API __declspec(dllimport)
#endif
#else
#    define VMMODULEFRAME_API  __attribute__((visibility("default")))
#    define __stdcall
#endif

class VMMODULEFRAME_API CAbstractUserModule
{
public:
	CAbstractUserModule();
	virtual ~CAbstractUserModule();

public:
	/** @fn     CAbstractUserModule::Process
     *  @brief  [必须实现] 处理模块业务逻辑。
     *  @param  hInput     获取输入句柄
     *  @param  hOutput    设置输出句柄
     *  @remark 1、获取输入，参见VM_M_GetString、VM_M_GetInt、VM_M_GetFloat、VM_M_GetImage；
                2、设置输出，参见VM_M_SetString、VM_M_SetInt、VM_M_SetFloat、VM_M_SetImage；
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int Process(IN void* hInput, IN void* hOutput) = 0;


    /** @fn     CAbstractUserModule::GetParam
     *  @brief  [可选实现]   获取参数值，默认实现不做任何事情，简单返回 IMVS_EC_NOT_IMPLEMENTED。
     *  @param  szParamName  参数名
     *  @param  pBuff        输出缓冲区指针
     *  @param  nBuffSize    输出缓冲区大小
     *  @param  pDataLen     实际数据长度
     *  @remark 实现时需注意，当nBuffSize过小时，错误码必须返回IMVS_EC_PARAM_BUF_LEN，且将实际大小赋值于pDataLen，
	            SDK将以pDataLen指定的大小重新分配空间，再次调用该接口取值。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int GetParam(IN const char* szParamName, OUT char* pBuff, IN int nBuffSize, OUT int* pDataLen);


    /** @fn     CAbstractUserModule::SetParam
     *  @brief  [可选实现]   设置参数值，默认实现不做任何事情，简单返回 IMVS_EC_NOT_IMPLEMENTED。
     *  @param  szParamName  参数名
     *  @param  pData        数据
     *  @param  nDataLen     数据长度
     *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int SetParam(IN const char* szParamName, IN const char* pData, IN int nDataLen);


	/** @fn     CAbstractUserModule::GetAllParamList
     *  @brief  [可选实现]   获取所有关键字参数列表值，默认实现不做任何事情，简单返回 IMVS_EC_NOT_IMPLEMENTED。
     *  @param  pParamValueList  参数列表
     *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int GetAllParamList(OUT PARAM_VALUE_INFO_LIST* pParamValueList);


    /** @fn     CAbstractUserModule::SaveModuleData
     *  @brief  [可选实现] 保存模块数据，默认实现会调用 GetAllParamList 获取所有参数值，并将其填充在
	            SAVE_MODULE_DATA_PARAM->struModuleData->struParamValueList之中。若想在保存方案时，修改
				关键字参数数据、或增加保存二进制块数据，可重写该函数。
     *  @param  pModuleData  模块数据

     *  @remark 1、设置pModuleData->struModuleData->struCustomUserData，可以保存二进制数据；
	            2、设置SAVE_MODULE_DATA_PARAM中的成员 pFnSigFinishedCallback，可使得当前SDK调用该接口获
				取模块数据、且使用完毕时，有机会通知模块该操作已完成，使模块有机会释放资源。

     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int SaveModuleData(OUT SAVE_MODULE_DATA_PARAM* pModuleData);


    /** @fn     CAbstractUserModule::LoadModuleData
     *  @brief  [可选实现]  加载模块数据，默认实现不做任何操作。子类请重写该函数用以获取模块数据。
     *  @param  pModuleData 模块数据
     
	 *  @remark 若方案中存在自定义二进制数据，请重写该函数，二进制数据存储在
	            pModuleData->struModuleData->struCustomUserData中。

     *  @return 错误码，参见ErrorCodeDefine.h
     */
	virtual int LoadModuleData(IN const LOAD_MODULE_DATA_PARAM* pModuleData);

public:
	void* m_hModule;   // 模块句柄, 调用VM_M_ReportData、VM_M_TryRunProcedureOnce等接口时使用
};



#ifdef __cplusplus
extern "C" 
{
#endif 

	/** @fn     VM_M_GetString
     *  @brief  获取输入字符数据
     *  @param  [IN]  hInput    输入句柄
                [IN]  szName    变量名称
				[IN]  nIndex    变量索引
				[IN]  pBuff     输出缓冲区指针
				[IN]  nBuffLen  输出缓冲区大小
				[OUT] pDataLen  返回实际数据大小
				[OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	 *  @remark 若缓冲区pBuff太小，SDK返回 IMVS_EC_PARAM_BUF_LEN，此时可用pDataLen指向的大小，重新分配空间并再次调用该接口取值。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetString(IN const void* hInput, IN const char* szName, IN int nIndex, 
		OUT char* pBuff, IN int nBuffLen, OUT int* pDataLen, OUT int* pCount);



    /** @fn     VM_M_GetInt
     *  @brief  获取输入整数值
     *  @param  [IN]  hInput    输入句柄
                [IN]  szName    变量名称
				[IN]  nIndex    变量索引
				[OUT] pValue    输出变量指针
				[OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetInt(IN const void* hInput, IN const char* szName, IN int nIndex, 
		OUT int* pValue, OUT int* pCount);



    /** @fn     VM_M_GetFloat
     *  @brief  获取输入浮点值
     *  @param  [IN]  hInput    输入句柄
                [IN]  szName    变量名称
				[IN]  nIndex    变量索引
				[OUT] pValue    输出变量指针
				[OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetFloat(IN const void* hInput, IN const char* szName, IN int nIndex, 
		OUT float* pValue, OUT int* pCount);



	/** @fn     VM_M_GetImage
     *  @brief  获取输入图像数据
     *  @param  [IN]  hInput     输入句柄
                [IN]  szName     变量名称
				[IN]  nIndex     变量索引
				[OUT] pImageData 图像数据信息，图像数据由SDK分配空间，调用时简单传入IMAGE_DATA空结构体即可。
				[OUT] pCount     若变量存在多个值（即为数组的情况下），返回值的个数
	 *  @remark IMAGE_DATA 中的图像数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该图像所占内存。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetImage(IN const void* hInput, IN const char* szName, IN int nIndex, 
		OUT IMAGE_DATA* pImageData, OUT int* pCount);


    /** @fn     VM_M_GetImageEx
     *  @brief  获取输入图像数据指针和共享内存标识
     *  @param  [IN]  hInput     输入句柄
                [IN]  szName     变量名称
                [IN]  nIndex     变量索引
                [OUT] pImageData 图像数据信息，图像数据由SDK分配空间，调用时简单传入IMAGE_DATA空结构体即可。
                [OUT] pCount     若变量存在多个值（即为数组的情况下），返回值的个数
     *  @remark IMAGE_DATA 中的图像数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该图像所占内存。
     *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_GetImageEx(IN const void* hInput, IN const char* szName, IN int nIndex,
        OUT IMAGE_DATA_V2* pImageData, OUT int* pCount);


	/** @fn     VM_M_GetPointset
     *  @brief  获取输入点集数据。定义此接口主要是为了兼容多进程版本sdk，pData指向的点集数据结构由算法模块定义，
	            一般指向IMVS_CONTOUR_POINT_INFO结构体数组。
     *  @param  [IN]  hInput   输入句柄
                [IN]  szName   变量名称
				[IN]  nIndex   变量索引
				[OUT] pData    点集数据
				[OUT] nDataLen 数据大小
				[OUT] pCount   若变量存在多个值（即为数组的情况下），返回值的个数
	 *  @remark pData中的数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该变量所占内存。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetPointset(IN const void* hInput, IN const char* szName, IN int nIndex,
		OUT void** pData, OUT int* pDataLen, OUT int* pCount);


	/** @fn     VM_M_GetBytes
	 *  @brief  获取二进制数据输入
	 *  @param  [IN]  hInput   输入句柄
	            [IN]  szName   变量名称
	            [IN]  nIndex   变量索引
	            [OUT] pData    二进制数据块指针地址
	            [OUT] nDataLen 数据大小
	            [OUT] pCount   若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark pData中的数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该变量所占内存。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetBytes(IN const void* hInput, IN const char* szName, IN int nIndex,
		OUT void** pData, OUT int* pDataLen, OUT int* pCount);


    /** @fn    VM_M_BatchGetString
    *  @brief  批量获取输入字符数据
    *  @param  [IN]  hInput    输入句柄
               [IN]  szName    变量名称
               [OUT] pBuff     输出缓冲区指针
               [IN]  nBuffLen  输出缓冲区个数
               [IN]  pDataLen  每个缓冲区长度，返回每个缓冲区实际长度
               [OUT] pCount    返回数据的数量，若该值小于获取的数据大小，则只能获取到pCount数量的数据
    *  @remark 若缓冲区pBuff太小，SDK返回 IMVS_EC_PARAM_BUF_LEN，此时可用pBuffLen指向的大小，重新分配空间并再次调用该接口取值。
    *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_BatchGetString(IN const void* hInput, IN const char* szName, OUT char** pBuff, 
        IN int nBuffCount, IN int* pBuffLen, OUT int* pCount);


    /** @fn    VM_M_BatchGetInt
    *  @brief  批量获取输入整数值
    *  @param  [IN]  hInput    输入句柄
               [IN]  szName    变量名称
               [IN]  nCount    读取个数
               [OUT] pValue    输出数组
               [OUT] pCount    返回数据的数量，若该值小于获取的数据大小，则只能获取到pCount数量的数据
    *  @remark 无
    *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_BatchGetInt(IN const void* hInput, IN const char* szName, IN int nCount,
        OUT int* pValue, OUT int* pCount);



    /** @fn    VM_M_BatchGetFloat
    *  @brief  批量获取输入浮点值
    *  @param  [IN]  hInput    输入句柄
               [IN]  szName    变量名称
               [IN]  nCount    变量索引
               [OUT] pValue    输出数组
               [OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
               [OUT] pCount    返回数据的数量，若该值小于获取的数据大小，则只能获取到pCount数量的数据
    *  @remark 无
    *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_BatchGetFloat(IN const void* hInput, IN const char* szName, IN int nCount,
        OUT float* pValue, OUT int* pCount);



	/** @fn     VM_M_SetString
     *  @brief  设置输出字符数据
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  nIndex      变量索引
				[IN]  pValue      变量值，须以'\0'字符结尾
	 *  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetString(IN const void* hOutput, IN const char* szName, IN int nIndex, IN const char* pValue);



	/** @fn     VM_M_SetInt
     *  @brief  设置输出整数数据
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  nIndex      变量索引
				[IN]  nValue      变量值
	 *  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetInt(IN const void* hOutput, IN const char* szName, IN int nIndex, IN int nValue);



	/** @fn     VM_M_SetFloat
     *  @brief  设置输出浮点数据
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  nIndex      变量索引
				[IN]  fValue      变量值
	 *  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetFloat(IN const void* hOutput, IN const char* szName, IN int nIndex, IN float fValue);

	/** @fn     VM_M_SetImage
     *  @brief  设置输出图像数据
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  nIndex      变量索引，置0
				[IN]  pImageData  图像数据
	 *  @remark 图像不支持数组格式输出，nIndex无效，置为0即可
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetImage(IN const void* hOutput, IN const char* szName, IN int nIndex,
		IN const IMAGE_DATA* pImageData);

    /** @fn     VM_M_SetImageEx
    *  @brief  设置输出图像数据与共享内存
    *  @param  [IN]  hOutput     输出句柄
               [IN]  szName      变量名称
               [IN]  nIndex      变量索引，置0
               [IN]  pImageData  图像数据
               [IN]  szSharedMemoryName 共享内存名称
    *  @remark 图像不支持数组格式输出，nIndex无效，置为0即可
    *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_SetImageEx(IN const void* hOutput, IN const char* szName, IN int nIndex,
        IN const IMAGE_DATA* pImageData, IN const char* szSharedMemoryName);

	/** @fn     VM_M_SetPointset
     *  @brief  设置输出点集数据。定义此接口主要是为了兼容多进程版本sdk，pData指向的点集数据结构由算法模块定义，
	            一般指向IMVS_CONTOUR_POINT_INFO结构体数组。
     *  @param  [IN]  hOutput  输出句柄
                [IN]  szName   变量名称
				[IN]  nIndex   变量索引，置0
				[IN]  pData    点集数据
				[IN]  nDataLen 数据大小
	 *  @remark 点集不支持数组格式输出，nIndex无效，置为0即可
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetPointset(IN const void* hOutput, IN const char* szName, IN int nIndex,
		IN void* pData, IN int nDataLen);


	/** @fn     VM_M_SetBytes
	 *  @brief  设置二进制数据输出
	 *  @param  [IN]  hOutput  输出句柄
	            [IN]  szName   变量名称
	            [IN]  nIndex   变量索引，置0
	            [IN]  pData    二进制数据块指针地址
	            [IN]  nDataLen 数据大小
	*  @remark 二进制数据不支持数组格式输出，nIndex无效，置为0即可
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_SetBytes(IN const void* hOutput, IN const char* szName, IN int nIndex,
		IN void* pData, IN int nDataLen);



	/** @fn     VM_M_BatchSetString
     *  @brief  设置输出字符串数据，支持同时设置多个值
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  pArryValue  字符串数组，即多个char*指向的字符串数组，须以'\0'结尾
				[IN]  nCount      字符串数量，即数组大小
	 *  @remark 多次调用时，后设置的值会覆盖先前值。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_BatchSetString(IN const void* hOutput, IN const char* szName, IN char** pArryValue, IN int nCount);



	/** @fn     VM_M_BatchSetInt
     *  @brief  设置输出整型数据，支持同时设置多个值
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  pArryValue  整数数组
				[IN]  nCount      数组大小
	 *  @remark 多次调用时，后设置的值会覆盖先前值。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_BatchSetInt(IN const void* hOutput, IN const char* szName, IN int* pArryValue, IN int nCount);



	/** @fn     VM_M_BatchSetFloat
     *  @brief  设置输出浮点数据，支持同时设置多个值
     *  @param  [IN]  hOutput     输出句柄
                [IN]  szName      变量名称
				[IN]  pArryValue  浮点数组
				[IN]  nCount      数组大小
	 *  @remark 多次调用时，后设置的值会覆盖先前值。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
    VMMODULEFRAME_API int __stdcall VM_M_BatchSetFloat(IN const void* hOutput, IN const char* szName, IN float* pArryValue, IN int nCount);



	/** @fn     VM_M_TryRunProcedureOnce
     *  @brief  触发一次流程执行，主要提供给流程首模块调用。
     *  @param  [IN]  hModule        模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [IN]  pszTriggerCmd  触发字符串
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_TryRunProcedureOnce(IN const void* hModule, IN const char* pszTriggerCmd, void* pNotUsed = 0);



	/** @fn     VM_M_TryRunProcedureOnceById
	 *  @brief  根据流程ID，触发一次流程执行
	 *  @param  [IN]  nProcedureId  流程ID
	            [IN]  pszTriggerCmd 触发字符串
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_TryRunProcedureOnceById(IN int nProcedureId, IN const char* pszTriggerCmd, void* pNotUsed = 0);



	/** @fn     VM_M_GetNextModuleList
     *  @brief  获取当前模块的后继节点列表，主要供分支模块使用
     *  @param  [IN]  hModule              模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [OUT] pNextModuleInfoList  后继模块节点列表
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetNextModuleList(IN const void* hModule, OUT NEXT_MODULE_INFO_LIST* pNextModuleInfoList);
	VMMODULEFRAME_API int __stdcall VM_M_GetNextModuleListEx(IN const void* hModule, OUT NEXT_MODULE_INFO_LIST_EX* pNextModuleInfoList);



	/** @fn     VM_M_SetNextModuleList
     *  @brief  设置当前模块的后继节点列表，主要供分支模块使用
     *  @param  [IN] hModule             模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [IN] pNextModuleInfoList 后继模块节点列表
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetNextModuleList(IN const void* hModule, IN const NEXT_MODULE_INFO_LIST* pNextModuleInfoList);
	VMMODULEFRAME_API int __stdcall VM_M_SetNextModuleListEx(IN const void* hModule, IN const NEXT_MODULE_INFO_LIST_EX* pNextModuleInfoList);



	/** @fn     VM_M_ReportData
     *  @brief  模块上报自定数据，SDK只做透传
     *  @param  [IN]  hModule   模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [IN]  nType     数据类型，自定义
				[IN]  szData    自定义数据，最大2K字节
				[IN]  nDataLen  自定义数据长度
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_ReportData(IN const void* hModule, IN int nType, IN const char* szData, IN int nDataLen);



	/** @fn     VM_M_EnableForceProcess
     *  @brief  无论前驱节点是否存在异常，都可正常进行process调用。俗称格式化合并。
     *  @param  [IN]  hModule   模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [IN]  bForce    是否开启
	 *  @remark 默认情况下，当某一模块执行出现异常时，后继模块不会再进入process执行，
	            调用此接口，可使得无论是否有异常发生，都可进入process执行流程。
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_EnableForceProcess(IN const void* hModule, IN bool bForce);



    /** @fn     VM_M_SetModuleRuntimeInfo
     *  @brief  记录模块时运行的一些信息，如算法时间、get及set时间等。
     *  @param  [IN]  hModule       模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [IN]  pRuntimeInfo  运行时记录信息
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_SetModuleRuntimeInfo(IN const void* hModule, IN const MODULE_RUNTIME_INFO* pRuntimeInfo);



	/** @fn     VM_M_GetModuleRuntimeInfo
     *  @brief  获取模块运行时一些信息，如算法时间、模块开始及结束执行时间。
     *  @param  [IN]  hModule       模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [OUT] pRuntimeInfo  运行时记录信息
	 *  @remark 无
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleRuntimeInfo(IN const void* hModule, OUT MODULE_RUNTIME_INFO* pRuntimeInfo);


	/** @fn     VM_M_GetModuleId
     *  @brief  获取模块ID
     *  @param  [IN]  hModule    模块句柄，由SDK分配，调用CreateModule时作为参数传入
                [OUT] pModuleId  模块ID
	 *  @remark 
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleId(IN const void* hModule, OUT int* pModuleId);


	/** @fn     VM_M_GetModuleHandleById
     *  @brief  根据模块ID获取模块句柄
     *  @param  [IN]  nModuleId     模块ID
                [OUT] pModuleHandle 模块句柄
	 *  @remark 
     *  @return 错误码，参见ErrorCodeDefine.h
     */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleHandleById(IN int nModuleId, OUT void** pModuleHandle);


	/** @fn    VM_M_SetLastError
	*  @brief  设置模块错误码
	*  @param  [IN]  hModule      模块句柄，由SDK分配，调用CreateModule时作为参数传入
	           [IN]  nLastErrCode 错误码
	*  @remark
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_SetLastError(IN const void* hModule, IN int nLastErrCode);


	/** @fn     VM_M_GetCreateModuleCause
	 *  @brief  获取当前创建模块的原因
	 *  @param  [IN]  hModule      模块句柄，由SDK分配，调用CreateModule时作为参数传入
	 *  @param  [OUT] pCreateCause 模块创建原因，参见 eCREATE_MODULE_CAUSE
	 *  @remark
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetCreateModuleCause(IN const void* hModule, OUT int* pCreateCause);



	/** @fn     VM_M_SetGlobalVarInt
	 *  @brief  设置模块全局整型输出
	 *  @param  [IN]  hModule  模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName   变量名称
	            [IN]  nIndex   变量索引
	            [IN]  nValue   变量值
	 *  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_SetGlobalVarInt(IN const void* hModule, IN const char* szName, IN int nIndex, IN int nValue);



	/** @fn     VM_M_SetGlobalVarFloat
	 *  @brief  设置模块全局浮点输出
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	            [IN]  nIndex  变量索引
	            [IN]  fValue  变量值
	 *  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_SetGlobalVarFloat(IN const void* hModule, IN const char* szName, IN int nIndex, IN float fValue);


	/** @fn     VM_M_SetGlobalVarString
	 *  @brief  设置模块全局字符串输出
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	            [IN]  nIndex  变量索引
	            [IN]  pValue  变量值，须以'\0'字符结尾
	*  @remark 单一输出变量可能存在多个值，当索引index已有值时，会覆盖先前值；否则SDK会忽略索引，将该值添加至列表末尾。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_SetGlobalVarString(IN const void* hModule, IN const char* szName, IN int nIndex, IN const char* pValue);



	/** @fn     VM_M_GetGlobalVarInt
	 *  @brief  获取模块全局整型输出
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	            [IN]  nIndex  变量索引
	            [OUT] pValue  输出变量指针
	            [OUT] pCount  若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetGlobalVarInt(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT int* pValue, OUT int* pCount);



	/** @fn     VM_M_GetGlobalVarFloat
	 *  @brief  获取模块全局浮点输出
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	            [IN]  nIndex  变量索引
	            [OUT] pValue  输出变量指针
	            [OUT] pCount  若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetGlobalVarFloat(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT float* pValue, OUT int* pCount);



	/** @fn     VM_M_GetGlobalVarString
	 *  @brief  获取模块全局字符串输出
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	            [IN]  nIndex  变量索引
	            [OUT] pValue  输出变量指针
	            [OUT] pCount  若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetGlobalVarString(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT char* pBuff, IN int nBuffLen, OUT int* pDataLen, OUT int* pCount);



	/** @fn     VM_M_DelGlobalVar
	 *  @brief  删除模块全局变量
	 *  @param  [IN]  hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szName  变量名称
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_DelGlobalVar(IN const void* hModule, IN const char* szName);


	/** @fn     VM_M_GetOwnerProcedureRunningPolicy
	 *  @brief  获取模块所属流程运行策略参数
	 *  @param  [IN]  hModule        模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [OUT] pRunningPolicy 模块所属流程运行策略
	 *  @remark  无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetOwnerProcedureRunningPolicy(IN const void* hModule, OUT MODULE_OWNER_PROCEDURE_RUNNING_POLICY* pRunningPolicy);



	/** @fn     VM_M_GetBinayData
	 *  @brief  获取指定模块参数
	 *  @param  [IN]  nModuleId    模块ID
	            [IN]  pszName      参数名称
				[OUT] pDataBuf     输入缓冲区
				[IN]  nDataBuffLen 输入缓冲区大小
				[OUT] pRealDataLen 实际数据大小
	 *  @remark 当返回错误码为 IMVS_EC_PARAM_BUF_LEN时，pRealDataLen存储实际数据长度。此时可为pDataBuf重新分配内存，再次调用。
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetBinayData(IN int nModuleId, IN const char* pszName, IN char* pDataBuf, IN int nDataBuffLen, OUT int* pRealDataLen);



	/** @fn     VM_M_SetBinayData
	 *  @brief  设置指定模块参数
	 *  @param  [IN]  nModuleId    模块ID
	            [IN]  pszName      参数名称
	            [IN]  pData        实际数据
	            [IN]  nDataLen     数据大小
	*  @remark  无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_SetBinayData(IN int nModuleId, IN const char* pszName, IN const char* pData, IN int nDataLen);


	/** @fn     VM_M_GetModuleNodeInfo
	 *  @brief  获取模块信息
	 *  @param  [IN]  nModuleId    模块ID
	            [OUT] pModuleInfo  模块信息
	 *  @remark  无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleNodeInfo(IN int nModuleId, OUT MODULE_INFO* pModuleInfo);



	/** @fn     VM_M_SetNotifyEventCallback
	 *  @brief  设置事件通知回调
	 *  @param  [IN] hModule 模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN] pEventCallback 事件回调
				[IN] pUserData      用户自定义数据
	 *  @remark  无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_SetNotifyEventCallback(IN const void* hModule, IN pFnNotifyEventCallback pEventCallback, IN void* pUserData);


	/** @fn     VM_M_SetModuleParam
	 *  @brief  设置指定模块参数
	 *  @param  [IN]  nModuleId       模块ID
	            [IN]  pParamValueList 参数值列表
	 *  @remark  无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_SetModuleParam(IN int nModuleId, IN const PARAM_VALUE_INFO_LIST* pParamValueList);


	/** @fn     VM_M_GetModuleParam
	 *  @brief  获取指定模块参数
	 *  @param  [IN]  nModuleId       模块ID
	            [IN]  pParamInfoList  参数名列表
	            [OUT] pParamValueList 参数值列表
	 *  @remark  无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleParam(IN int nModuleId, IN const PARAM_INFO_LIST* pParamInfoList, OUT PARAM_VALUE_INFO_LIST* pParamValueList);


	/** @fn     VM_M_GetOwnerProcedureRunningParam
	 *  @brief  获取模块所属流程运行参数
	 *  @param  [IN]  hModule        模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [OUT] pRunningParam  流程运行参数
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetOwnerProcedureRunningParam(IN const void* hModule, OUT PROCEDURE_RUNNING_PARAM* pRunningParam);


	/** @fn     VM_M_StopOwnerProcedure
	 *  @brief  模块请求当前流程停止运行
	 *  @param  [IN]  hModule        模块句柄，由SDK分配，调用CreateModule时作为参数传入
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_StopOwnerProcedure(IN const void* hModule);


	/** @fn     VM_M_GetModuleHandleByName
	 *  @brief  根据模块名称获取模块句柄
	 *  @param  [IN]  hModule         模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  pModuleNamePath 模块名称路径。数组中每一个元素表示一个路径，最后一个元素置必须为NULL。
	            [OUT] pModuleHandle   要获取的指定名称的模块句柄
	 *  @remark V3.4新增，模块名称使用显示名称。
	            1）若模块不存在于嵌套结构中，若显示名称为 Module1,那么：
				   pModuleNamePath[0] = "Module1"
				   pModuleNamePath[1] = NULL.
				2）若模块存在于嵌套Group中，其路径为Group1-->Group2-->Module1,那么：
				   pModuleNamePath[0] = "Group1",
				   pModuleNamePath[1] = "Group2"
				   pModuleNamePath[2] = "Module1"
				   pModuleNamePath[3] = NULL.
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleHandleByName(IN const void* hModule, IN char** pModuleNamePath, OUT void** pModuleHandle);


	/** @fn     VM_M_GetOutputString
	 *  @brief  获取输入字符数据
	 *  @param  [IN]  hModule   模块句柄
	            [IN]  szName    变量名称
	            [IN]  nIndex    变量索引
	            [IN]  pBuff     输出缓冲区指针
	            [IN]  nBuffLen  输出缓冲区大小
	            [OUT] pDataLen  返回实际数据大小
	            [OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 若缓冲区pBuff太小，SDK返回 IMVS_EC_PARAM_BUF_LEN，此时可用pDataLen指向的大小，重新分配空间并再次调用该接口取值。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputString(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT char* pBuff, IN int nBuffLen, OUT int* pDataLen, OUT int* pCount);



	/** @fn      VM_M_GetOutputInt
	  *  @brief  获取输入整数值
	  *  @param  [IN]  hModule   模块句柄
	             [IN]  szName    变量名称
	             [IN]  nIndex    变量索引
	             [OUT] pValue    输出变量指针
	             [OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputInt(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT int* pValue, OUT int* pCount);



	/** @fn    VM_M_GetOutputFloat
	*  @brief  获取输入浮点值
	*  @param  [IN]  hModule   模块句柄
	           [IN]  szName    变量名称
	           [IN]  nIndex    变量索引
	           [OUT] pValue    输出变量指针
	           [OUT] pCount    若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark 无
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputFloat(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT float* pValue, OUT int* pCount);


	/** @fn     VM_M_GetOutputImage
	*  @brief  获取输入图像数据
	*  @param  [IN]  hModule    模块句柄
	           [IN]  szName     变量名称
	           [IN]  nIndex     变量索引
	           [OUT] pImageData 图像数据信息，图像数据由SDK分配空间，调用时简单传入IMAGE_DATA空结构体即可。
	           [OUT] pCount     若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark IMAGE_DATA 中的图像数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该图像所占内存。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputImage(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT IMAGE_DATA* pImageData, OUT int* pCount);


	/** @fn     VM_M_GetOutputPointset
	 *  @brief  获取输入点集数据。定义此接口主要是为了兼容多进程版本sdk，pData指向的点集数据结构由算法模块定义，
	一般指向IMVS_CONTOUR_POINT_INFO结构体数组。
	*  @param  [IN]  hModule  模块句柄
	           [IN]  szName   变量名称
	           [IN]  nIndex   变量索引
	           [OUT] pData    点集数据
	           [OUT] nDataLen 数据大小
	           [OUT] pCount   若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark pData中的数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该变量所占内存。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputPointset(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT void** pData, OUT int* pDataLen, OUT int* pCount);


	/** @fn     VM_M_GetOutputBytes
	*  @brief  获取二进制数据输入
	*  @param  [IN]  hModule  模块句柄
	           [IN]  szName   变量名称
	           [IN]  nIndex   变量索引
	           [OUT] pData    二进制数据块指针地址
	           [OUT] nDataLen 数据大小
	           [OUT] pCount   若变量存在多个值（即为数组的情况下），返回值的个数
	*  @remark pData中的数据，由SDK分配空间，外部调用时请尽快使用，process退出时SDK会回收该变量所占内存。
	*  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_GetOutputBytes(IN const void* hModule, IN const char* szName, IN int nIndex,
		OUT void** pData, OUT int* pDataLen, OUT int* pCount);

    /** @fn     VM_M_GetFreePort
    *  @brief  获取可用端口
    *  @param  [IN]  hModule  模块句柄
    *  @param  [out] nFreePort  可用端口号
    *  @remark
    *  @return 错误码，参见ErrorCodeDefine.h
    */
    VMMODULEFRAME_API int __stdcall VM_M_GetFreePort(IN const void* hModule, int& nFreePort);

#ifdef __cplusplus
};
#endif 

#endif //end of _VM_MODULE_BASE_H_
