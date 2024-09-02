/************************************************************************
* 版权信息：版权所有(c) 2019, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：VmModuleInternal.h
* 摘   要:  内部接口定义，不对外。此处提供的接口只是为了满足算法模块、
            代理进程等特殊的要求提供。
*
* 作   者:  fenghuapeng5
* 日   期： 2019-12-18
* 备   注：
************************************************************************/
#ifndef _VMMODULE_INTERNAL_H_
#define _VMMODULE_INTERNAL_H_

#ifdef _WIN32
#ifdef  VMMODULEFRAME_EXPORTS
#    define VMMODULEFRAME_API __declspec(dllexport)
#else
#    define VMMODULEFRAME_API __declspec(dllimport)
#endif
#else
#    define VMMODULEFRAME_API __attribute__((visibility("default")))
#    define __stdcall
#endif

#ifdef __cplusplus
extern "C"
{
#endif 

	/** @fn     VM_M_GetDefaultConfigByFile
	 *  @brief  通过参数文件，获取模块默认的参数配置

	            注：此接口仅仅是为了统一解析配置文件提供，根据实际需要可选使用；
	            可通过该接口在模块初始化成功后，获取模块默认参数。

	 *  @param  [IN]  hModule         模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szAlgFile       含有参数名、参数默认值的文件。此接口仅从文件中读取参数名、默认值
	            [OUT] pParamValueList 参数配置信息
	 *  @remark  szAlgFile指定的文件必须符合格式约束。
	            若szAlgFile仅为文件名（不包含路径）时，SDK默认会在模块dll路径下查找此文件。其余情况下，请指定绝对路径。
	 *  @return  错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetDefaultConfigByFile(IN const void* hModule, IN const char* szAlgFile, OUT PARAM_VALUE_INFO_LIST* pParamValueList, void* pNotUsed = 0);



	/** @fn    VM_M_GetCurrentConfigByFile
	 *  @brief 通过参数文件，获取模块当前的参数配置。

	           注：此接口仅仅是为了统一解析配置文件提供，根据实际需要可选使用；
	           目前只在CAbstractUserModule::GetAllParamList会使用到。

	 *  @param  [IN]  hModule         模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  szAlgFile       含有参数名、参数默认值的文件。此接口从文件中获取参数名后，会从模块中获取当前配置值
	            [OUT] pParamValueList 参数配置信息
	 *  @remark szAlgFile指定的文件必须符合格式约束。
	            若szAlgFile仅为文件名（不包含路径）时，SDK默认会在模块dll路径下查找此文件。其余情况下，请指定绝对路径。
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetCurrentConfigByFile(IN const void* hModule, IN const char* szAlgFile, OUT PARAM_VALUE_INFO_LIST* pParamValueList, void* pNotUsed = 0);


	/** @fn     VM_M_AllocateAlgMemory
	 *  @brief  仅分配算法运行内存，其他通用内存分配请勿使用此接口
	 *  @param  [IN]  hModule     模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  nSize       含有参数名、参数默认值的文件。此接口从文件中获取参数名后，会从模块中获取当前配置值
	            [IN]  nAlignment  按多少字节对齐(4/8/16/32/64/128/256)
	            [OUT] pData       分配内存块首地址
	 *  @remark 必须在重写CAbstractUserModule::Process函数中调用，勿在其他线程中使用
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_AllocateAlgMemory(IN const void* hModule, IN int nSize, IN int nAlignment, OUT void** pData);
	VMMODULEFRAME_API int __stdcall VM_M_AllocateAlgMemory64(IN const void* hModule, IN uint64_t nSize, IN int nAlignment, OUT void** pData);


	/** @fn     VM_M_ReleaseAlgMemory
	 *  @brief  释放已分配的算法运行内存，其他通用内存释放请勿使用此接口
	 *  @param  [IN]  hModule    模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  pData      分配内存块首地址
	 *  @remark 必须在重写CAbstractUserModule::Process函数中调用，勿在其他线程中使用
	 *  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_ReleaseAlgMemory(IN const void* hModule, IN const void* pData);



	/** @fn     VM_M_AllocateMemoryInPool
	 *  @brief  在全局内存池中分配内存
	 *  @param  [IN]  hModule   模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  pInput    分配内存参数
	            [OUT] pBaseAddr 分配内存块首地址
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_AllocateMemoryInPool(IN const void* hModule, IN const ALLOC_MEM_IN_POOL_INPUT* pInput, OUT void** pBaseAddr);



	/** @fn     VM_M_ReleaseMemoryInPool
	 *  @brief  在全局内存池中释放内存
	 *  @param  [IN]  hModule    模块句柄，由SDK分配，调用CreateModule时作为参数传入
	            [IN]  pBaseAddr  分配内存块首地址
	 *  @remark 无
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_ReleaseMemoryInPool(IN const void* hModule, IN void* pBaseAddr);



	/**  @fn     VM_M_ReleaseSolSharedMemory
	  *  @brief  释放方案相关的共享内存
	  *  @param  
	  *  @remark 
	  *  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_ReleaseSolSharedMemory();
    VMMODULEFRAME_API int __stdcall VM_M_ReleaseSolSharedMemorySp();



	/**  @fn    VM_M_ReleaseGroupDataSharedMemory
	 *  @brief  释放Group相关的共享内存
	 *  @param  [IN] nGroupId       模块Id
	            [IN] pSharedMemName 共享内存名称
	 *  @remark
	 *  @return 错误码，参见ErrorCodeDefine.h
	*/
    VMMODULEFRAME_API int __stdcall VM_M_ReleaseGroupDataSharedMemory(IN int nGroupId, const char* pSharedMemName);
    VMMODULEFRAME_API int __stdcall VM_M_ReleaseGroupDataSharedMemorySp(IN int nGroupId, const char* pSharedMemName);



	/**  @fn    VM_M_ReleaseProcedureDataSharedMemory
	 *  @brief  释放流程相关的共享内存
	 *  @param  [IN] nProcedureId   流程Id
	            [IN] pSharedMemName 共享内存名称
	 *  @remark
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
    VMMODULEFRAME_API int __stdcall VM_M_ReleaseProcedureDataSharedMemory(IN int nProcedureId, const char* pSharedMemName);
    VMMODULEFRAME_API int __stdcall VM_M_ReleaseProcedureDataSharedMemorySp(IN int nProcedureId, const char* pSharedMemName);



	/**  @fn    VM_M_ResetModuleNodeAlgParam
	 *  @brief  重置模块关键字参数
	 *  @param  nModuleId 模块Id
	 *  @remark
	 *  @return 错误码，参见ErrorCodeDefine.h
	*/
	VMMODULEFRAME_API int __stdcall VM_M_ResetModuleNodeAlgParam(IN int nModuleId);



	/** @fn     VM_M_NotifyEvent
	 *  @brief  告知通知事件
	 *  @param  nNotifyEvent 通知事件类型，参见eNOTIFY_EVENT_TYPE
	 *  @param  pData        事件数据，置为NULL
	 *  @remark
	 *  @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_NotifyEvent(IN int nNotifyEvent, IN void* pData);



	/**  @fn     IsUploadRstEnabled
	 *   @brief  判断当前上传结果是否启用
	 *   @param  
	 *   @remark 若模块结果不经过模块框架，可使用此接口判断是否发送结果。
	 *   @return true or false
	 */
	VMMODULEFRAME_API bool __stdcall VM_M_IsUploadRstEnabled();



	/**  @fn     VM_M_RunModuleById
	 *   @brief  在模块中执行其他模块
	 *   @param  [IN] hModule    模块句柄，由SDK分配，调用CreateModule时作为参数传入
	             [IN] nModuleId  要运行的模块ID
				 [IN] pErrCode   被执行的模块process返回值
	 *   @remark 此操作为同步执行，此接口只有在被执行模块完成后才返回
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_RunModuleById(IN const void* hModule, IN int nRunModuleId, IN int* pErrCode);


	/**  @fn     VM_M_GetModuleMapping
	 *   @brief  在模块中执行其他模块
	 *   @param  [IN]  hModule             模块句柄，由SDK分配，调用CreateModule时作为参数传入
	             [OUT] pArryModuleMapping  模块映射信息数组
	             [IN]  nArrySize           pArryModuleMapping数据大小
				 [OUT] nRealNum            返回真实数据长度。
	 *   @remark 当pArryModuleMapping为NULL或nArrySize小于真实数组大小时，返回IMVS_EC_PARAM_BUF_LEN，其中nRealNum返回真实大小。请重新分配内存后再次调用。
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleMapping(IN const void* hModule, OUT MODULE_MAPPING* pArryModuleMapping, IN int nArrySize, OUT int* pRealNum);


	/**  @fn     VM_M_ExportModuleDataToSharedMem
	 *   @brief  导出模块数据
	 *   @param  [IN] pSharedMemName 共享内存名称
	             [IN] pArryModuleId  导出的模块Id
	             [IN] nSize          数组pArryModuleId大小
	 *   @remark 
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_ExportModuleDataToSharedMem(IN const char* pSharedMemName, IN const int* pArryModuleId, IN int nSize);


	/**  @fn     VM_M_ImportModuleDataFromSharedMem
	 *   @brief  导入模块数据
	 *   @param  [IN] pData    模块数据
	 *   @param  [IN] nDataLen 数据长度
	 *   @remark
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_ImportModuleDataFromSharedMem(IN const char* pData, IN int nDataLen, IN const int* pArryModuleId, IN int nSize);


	/**  @fn     VM_M_RelaseSharedMemory
	 *   @brief  释放共享内存
	 *   @param  [IN] pSharedMemName 共享内存名称
	 *   @remark
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_RelaseSharedMemory(IN const char* pSharedMemName);


	// ***设置流程、模块输入值（nId可为普通模块id、流程id）***
	VMMODULEFRAME_API int __stdcall VM_M_SetInputString(IN int nId, IN const char* szName, IN int nIndex, IN const char* pValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputInt(IN int nId, IN const char* szName, IN int nIndex, IN int nValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputFloat(IN int nId, IN const char* szName, IN int nIndex, IN float fValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputImage(IN int nId, IN const char* szName, IN int nIndex, IN const IMAGE_DATA* pImageData);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputPointset(IN int nId, IN const char* szName, IN int nIndex, IN void* pData, IN int nDataLen);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputBytes(IN int nId, IN const char* szName, IN int nIndex, IN void* pData, IN int nDataLen);


	/**  @fn     VM_M_RequestChangeSol
	 *   @brief  模块主动请求切换方案
	 *   @param  [IN]  hModule         模块句柄，由SDK分配，调用CreateModule时作为参数传入
	             [IN]  pChangeSolParam 切换方案参数
	 *   @remark
	 *   @return 错误码，参见ErrorCodeDefine.h
	 */
	VMMODULEFRAME_API int __stdcall VM_M_RequestChangeSol(IN const void* hModule, IN const REQUEST_CHANGE_SOL_PARAM* pChangeSolParam);

	// ***维护全局相机数量***
	VMMODULEFRAME_API int __stdcall VM_M_NotifyIncGlobalCameraNum(IN const void* hModule, IN int nNum, IN int nFlag);
	VMMODULEFRAME_API int __stdcall VM_M_NotifyDecGlobalCameraNum(IN const void* hModule, IN int nNum, IN int nFlag);
	VMMODULEFRAME_API int __stdcall VM_M_GetGlobalCameraList(OUT GLOBAL_CAMERA_LIST* pGlobalCameraList);


	// ***设置运行检测状态***
	VMMODULEFRAME_API int __stdcall VM_M_SetCheckRunningStatus(IN const CHECK_RUNNING_STATUS* pCheckRunningStatus);


	// ***获取方案中模块的关键字参数配置信息***
	VMMODULEFRAME_API int __stdcall VM_M_GetCurrentConfigOfSolution(IN char* pDataBuf, IN int nDataBuffLen, OUT int* pRealDataLen);


	//***将模块执行结果与模块运行参数绑定***
	VMMODULEFRAME_API int __stdcall VM_M_SetModuleParamBinding(IN const MODULE_PARAM_BINDING* pArryBinding, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_DelModuleParamBinding(IN const MODULE_PARAM_UNBINDING* pArryUnBinding, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleParamBindingList(IN int nModuleId, IN int nIndex, IN int nArrySize, OUT MODULE_PARAM_BINDING* pArryBindList, OUT int* pReturnCount, OUT int* pTotalNum);

	//***批量导入导出流程, pArryProcedureId表示流程id数组，nProcedureNum表示数组大小***
	VMMODULEFRAME_API int __stdcall VM_M_BatchExportProcedureData(IN const int* pArryProcedureId, int nProcedureNum, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_BatchImportProcedureData(IN const int* pArryProcedureId, int nProcedureNum, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_BatchCancelExportProcedureData(void* pReserved = NULL);
	VMMODULEFRAME_API int __stdcall VM_M_BatchCancelImportProcedureData(void* pReserved = NULL);
	VMMODULEFRAME_API int __stdcall VM_M_BatchReleaseProcedureDataSharedMemory(void* pReserved = NULL);

	//***流程间联动***
	VMMODULEFRAME_API int __stdcall VM_M_ConnectProcedure(IN int nSrcProcedureId, IN int nDstProcedureId);
	VMMODULEFRAME_API int __stdcall VM_M_DisConnectProcedure(IN int nSrcProcedureId, IN int nDstProcedureId);

	//***启用可重入***
	VMMODULEFRAME_API int __stdcall VM_M_EnableReentrant(IN bool bEnable);

	//***设置不支持可重入的模块列表***
	VMMODULEFRAME_API int __stdcall VM_M_SetUnsupportReentrantModules(IN const char* pData);

	//***设置最大可重入次数***
	VMMODULEFRAME_API int __stdcall VM_M_SetReentrantMaxTimes(IN int nMaxTimes);

	//***设置内部缓存节点数量***
	VMMODULEFRAME_API int __stdcall VM_M_SetBufferNodeNum(IN int nBufferNum);

    //***获取内部缓存节点数量***
    VMMODULEFRAME_API int __stdcall VM_M_GetBufferNodeNum(IN int* nBufferNum);

	//***查询模块状态, 可批量查询，nArrySize表示pArryModuleId及pArryStateInfo指定的数组大小***
	VMMODULEFRAME_API int __stdcall VM_M_QueryModuleRunningState(IN const int* pArryModuleId, IN int nArrySize, OUT MODULE_STATE_INFO* pArryStateInfo);

	// ***保持上次结果不变，即本次模块不会被执行***
	VMMODULEFRAME_API int __stdcall VM_M_KeepLastResultUnchange(IN int nNodeId, IN bool bKeep);

	// ***设置图像缓存节点数量，勿在流程运行时调用***
	VMMODULEFRAME_API int __stdcall VM_M_SetImageBufferNodeNum(IN int nNodeId, IN int nNum);

	// ***强制深拷贝***
	VMMODULEFRAME_API int __stdcall VM_M_ForceDeepCopyImage(IN bool bForce);

};

#endif
