/************************************************************************
* 版权信息：版权所有(c) 2018, 杭州海康机器人技术有限公司.保留所有权利.
*
* 文件名称：VmModuleFrame.h
* 摘   要:  SDK框架接口定义，供驱动整个框架运行。
*
* 作   者:  fenghuapeng5
* 日   期： 2018-09-10
* 备   注： 
************************************************************************/ 

#ifndef _VM_MODULE_FRAME_H_
#define _VM_MODULE_FRAME_H_
#include "VmModuleDef.h"

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

	//***初始化、反初始化***
	VMMODULEFRAME_API int __stdcall VM_M_Initialize(IN INITIALIZE_PARAM* pInitParam = NULL);
	VMMODULEFRAME_API int __stdcall VM_M_UnInitialize();

	
	//***流程相关***
	VMMODULEFRAME_API int __stdcall VM_M_CreateProcedure(IN const CREATE_PROCEDURE_PARAM* pCreateParam);
	VMMODULEFRAME_API int __stdcall VM_M_UpdateProcedure(IN int nProcedureId, IN const UPDATE_PROCEDURE_PARAM* pUpdateParam);
	VMMODULEFRAME_API int __stdcall VM_M_DeleteProcedure(IN int nProcedureId);
	// 获取当前流程状态，pStatus取值为ePROCEDURE_STATUS
	VMMODULEFRAME_API int __stdcall VM_M_GetProcedureStatus(IN int nProcedureId, OUT int* pStatus);
	VMMODULEFRAME_API int __stdcall VM_M_ExportProcedureData(IN int nProcedureId, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_ImportProcedureData(IN int nProcedureId, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_CancelExportProcedureData(IN int nProcedureId);
	VMMODULEFRAME_API int __stdcall VM_M_CancelImportProcedureData(IN int nProcedureId);
    

	//***模块操作***
	// 此操作为异步操作，操作结果以事件EVENT_ADD_MODULE_FINISHED上报
	VMMODULEFRAME_API int __stdcall VM_M_AddModuleNode(IN const ADD_MODULE_PARAM* pAddModuleParam);
	VMMODULEFRAME_API int __stdcall VM_M_AddModuleNodeEx(IN const ADD_MODULE_PARAM_EX* pAddModuleParam);
	VMMODULEFRAME_API int __stdcall VM_M_AddModuleNodeSync(IN const ADD_MODULE_PARAM_EX* pAddModuleParam);

	// 此操作为异步操作，操作结果以事件EVENT_BATCH_ADD_MODULE_FINISHED上报
	VMMODULEFRAME_API int __stdcall VM_M_BatchAddModuleNode(IN const BATCH_ADD_MODULE_PARAM* pArryModuleParam, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_BatchAddModuleNodeEx(IN const BATCH_ADD_MODULE_PARAM_EX* pArryModuleParam, IN int nArrySize);

	VMMODULEFRAME_API int __stdcall VM_M_UpdateModuleNode(IN int nModuleId, IN const UPDATE_MODULE_PARAM* pUpdateModuleParam);
	VMMODULEFRAME_API int __stdcall VM_M_UpdateModuleNodeEx(IN int nModuleId, IN const UPDATE_MODULE_PARAM_EX* pUpdateModuleParam);
	VMMODULEFRAME_API int __stdcall VM_M_DeleteModuleNode(IN int nModuleId);
	VMMODULEFRAME_API int __stdcall VM_M_SetModuleNodeState(IN int nModuleId, IN const MODULE_STATE* pModuleState);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleNodeState(IN int nModuleId, OUT MODULE_STATE* pModuleState);
	VMMODULEFRAME_API int __stdcall VM_M_CopyModuleNodeParam(IN int nSrcModuleId, IN int nDstModuleId);
	VMMODULEFRAME_API int __stdcall VM_M_CopyModuleNodeAlgParam(IN int nSrcModuleId, IN int nDstModuleId);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleNodeInfo(IN int nModuleId, OUT MODULE_INFO* pModuleInfo);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleNodeInfoEx(IN int nModuleId, OUT MODULE_INFO_EX* pModuleInfo);


	//***模块参数配置***
	VMMODULEFRAME_API int __stdcall VM_M_SetModuleParam(IN int nModuleId, IN const PARAM_VALUE_INFO_LIST* pParamValueList);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleParam(IN int nModuleId, IN const PARAM_INFO_LIST* pParamInfoList, OUT PARAM_VALUE_INFO_LIST* pParamValueList);
	VMMODULEFRAME_API int __stdcall VM_M_GetModuleAllParam(IN int nModuleId, OUT PARAM_VALUE_INFO_LIST* pParamValueList);

	
	//***二进制块参数配置***
	VMMODULEFRAME_API int __stdcall VM_M_SetBinayData(IN int nModuleId, IN const char* pszName, IN const char* pData, IN int nDataLen);

	
	// 当返回错误码为 IMVS_EC_PARAM_BUF_LEN时，pRealDataLen存储实际数据长度。此时可为pDataBuf重新分配内存，再次调用。
    VMMODULEFRAME_API int __stdcall VM_M_GetBinayData(IN int nModuleId, IN const char* pszName, IN char* pDataBuf, IN int nDataBuffLen, OUT int* pRealDataLen);
	

	//***连接模块***
	VMMODULEFRAME_API int __stdcall VM_M_ConnectModule(IN int nSrcModuleId, IN int nDstModuleId);
	VMMODULEFRAME_API int __stdcall VM_M_DisConnectModule(IN int nSrcModuleId, IN int nDstModuleId);

   
	//***订阅***
	VMMODULEFRAME_API int __stdcall VM_M_SubScribe(IN const SUBSCRIBE_PARAM_LIST* pSubscribeParam);
	VMMODULEFRAME_API int __stdcall VM_M_UnSubScribe(IN int nModuleId, IN char* pszInputName, void* pNotUsed = 0);
    

	//***执行流程***
	VMMODULEFRAME_API int __stdcall VM_M_RunProcedureOnce(IN int nProcedureId, IN const char* pszTriggerCmd);
	VMMODULEFRAME_API int __stdcall VM_M_RunProcedureContinuously(IN int nProcedureId, IN int nInterval, IN const char* pszTriggerCmd);
	VMMODULEFRAME_API int __stdcall VM_M_StopRunProcedure(IN int nProcedureId);
	VMMODULEFRAME_API int __stdcall VM_M_RunModuleSelf(IN int nModuleId);
    VMMODULEFRAME_API int __stdcall VM_M_BatchRunModuleSelf(IN int* pModuleIds, IN int nModuleNum);
	VMMODULEFRAME_API int __stdcall VM_M_SetProcedureRunningParam(IN int nProcedureId, IN const PROCEDURE_RUNNING_PARAM* pRunningParam);
	VMMODULEFRAME_API int __stdcall VM_M_GetProcedureRunningParam(IN int nProcedureId, OUT PROCEDURE_RUNNING_PARAM* pRunningParam);
	//pInput为触发流程输入参数，pOutput为反馈输出信息，不用时置为NULL即可。
	VMMODULEFRAME_API int __stdcall VM_M_RunProcedureOnceEx(IN int nProcedureId, IN const RUN_PROCEDURE_INPUT* pInput = NULL, OUT RUN_PROCEDURE_OUTPUT* pOutput = NULL);
	
	//***方案***
	VMMODULEFRAME_API int __stdcall VM_M_SaveSolutionToFile(const char* szFilePath);
	VMMODULEFRAME_API int __stdcall VM_M_LoadSolutionFromFile(const char* szFilePath);
	VMMODULEFRAME_API int __stdcall VM_M_CancelLoadSolution();
	VMMODULEFRAME_API int __stdcall VM_M_CancelSaveSolution();
	VMMODULEFRAME_API int __stdcall VM_M_CloseSolution();
	VMMODULEFRAME_API int __stdcall VM_M_AsyncCloseSolution();
	//nLoadState: 0-未加载方案，1-处于加载方案状态
	VMMODULEFRAME_API int __stdcall VM_M_SetLoadSolutionState(int nLoadState);
    
	
	//***循环操作***
	VMMODULEFRAME_API int __stdcall VM_M_AddLoop(IN int nProcedureId, IN int nLoopId);
	VMMODULEFRAME_API int __stdcall VM_M_UpdateLoop(IN int nLoopId, IN const LOOP_INFO* pLoopInfo);
	VMMODULEFRAME_API int __stdcall VM_M_DeleteLoop(IN int nLoopId);
	VMMODULEFRAME_API int __stdcall VM_M_BatchAddLoop(IN const BATCH_ADD_LOOP_PARAM* pArryLoopParam, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_AddLoopEx(IN const ADD_LOOP_PARAM_EX* pAddLoopParam);


	//***Group组操作***
	VMMODULEFRAME_API int __stdcall VM_M_AddGroup(IN const ADD_GROUP_PARAM* pAddGroupParam);
	VMMODULEFRAME_API int __stdcall VM_M_AddGroupEx(IN const ADD_GROUP_PARAM_EX* pAddGroupParam);
	VMMODULEFRAME_API int __stdcall VM_M_AddGroupSync(IN const ADD_GROUP_PARAM_EX* pAddGroupParam);
	VMMODULEFRAME_API int __stdcall VM_M_MoveIntoGroup(IN int nGroupId, IN int nNodeId);
	VMMODULEFRAME_API int __stdcall VM_M_MoveOutFromGroup(IN int nGroupId, IN int nNodeId);
	VMMODULEFRAME_API int __stdcall VM_M_DeleteGroup(IN int nGroupId);
	VMMODULEFRAME_API int __stdcall VM_M_ExportGroupData(IN int nGroupId, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_ImportGroupData(IN int nGroupId, IN const char* pPath);
	VMMODULEFRAME_API int __stdcall VM_M_CancelExportGroupData(IN int nGroupId);
	VMMODULEFRAME_API int __stdcall VM_M_CancelImportGroupData(IN int nGroupId);
	VMMODULEFRAME_API int __stdcall VM_M_BatchAddGroup(IN const BATCH_ADD_GROUP_PARAM* pArryAddGroupParam, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_BatchAddGroupEx(IN const BATCH_ADD_GROUP_PARAM_EX* pArryAddGroupParam, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_BatchMoveIntoGroup(IN int nGroupId, IN const int* pArryNodeId, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_BatchMoveOutFromGroup(IN int nGroupId, IN const int* pArryNodeId, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_SetGroupIO(IN int nGroupId, IN const GROUP_IO_FIELD_PARAM* pArryGroupInput, IN int nInputSize, IN const GROUP_IO_FIELD_PARAM* pArryGroupOutput, IN int nOutputSize);

	
	//***执行结果回调***
	VMMODULEFRAME_API int __stdcall VM_M_SetResultCallback(IN pFnResultCallback fResultCallback, IN void* pUserData);


	//***结果过滤，在流程级别配置自定义输出，可选择性整合流程内各个模块的结果***
	VMMODULEFRAME_API int __stdcall VM_M_SetCustomOutput(IN int nProcedureId, IN const CUSTOM_OUTPUT_RECORD* pCustomOutput);
	VMMODULEFRAME_API int __stdcall VM_M_GetCustomOutput(IN int nProcedureId, IN int nIndex, OUT CUSTOM_OUTPUT_RECORD_LIST* pCustomOutputList, OUT int* pTotalNum);
	VMMODULEFRAME_API int __stdcall VM_M_DelCustomOutput(IN int nProcedureId, IN const char* pOutputName);
	VMMODULEFRAME_API int __stdcall VM_M_ClearCustomOutput(IN int nProcedureId);


	//***事件通知回调***
	VMMODULEFRAME_API int __stdcall VM_M_SetEventCalBack(IN pFnEventCallback pEventCallback, IN void* pUserData);

    //***模块自定义数据回调***
    VMMODULEFRAME_API int __stdcall VM_M_SetCustomDataCallBack(IN pFnCustomDataTransCallback pDataCallback, IN void* pUserData);

	//***查询模块配置信息***
    VMMODULEFRAME_API int __stdcall VM_M_QueryModuleConfigParam(IN char* szModuleName, OUT MODULE_CONFIG_PARAM* pModuleConfigParam);
	VMMODULEFRAME_API int __stdcall VM_M_QueryModuleConfigParamEx(IN char* szModuleName, OUT MODULE_CONFIG_PARAM_EX* pModuleConfigParam);

	
	//***设置日志参数***
	VMMODULEFRAME_API int __stdcall VM_M_SetLogLevel(IN eLOG_LEVEL nLogLevel);


	//***设置运行时控制参数***
	VMMODULEFRAME_API int __stdcall VM_M_SetRunningControlParam(IN const RUNNING_CONTROL_PARAM* pRunControlParam);


	//***流程运行策略***
	VMMODULEFRAME_API int __stdcall VM_M_SetProcedureRunningPolicy(IN const PROCEDURE_RUNNING_POLICY* pRunPolicy);
	VMMODULEFRAME_API int __stdcall VM_M_GetProcedureRunningPolicy(OUT PROCEDURE_RUNNING_POLICY* pRunPolicy);


	// ***获取处理器信息***
	VMMODULEFRAME_API int __stdcall VM_M_GetProcessorInfo(OUT PROCESSOR_INFO* pProcessorInfo);


	// ***全局变量***
	VMMODULEFRAME_API int __stdcall VM_M_BindGlobalVar(IN const BIND_GLOBALVAR_PARAM* pArryBindGlobaVar, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_UnBindGlobalVar(IN const UNBIND_GLOBALVAR_PARAM* pArryUnBindGlobalVar, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_GetGlobalVarBindingList(IN int nGlobalModuleId, IN int nIndex, IN int nArrySize, OUT BIND_GLOBALVAR_PARAM* pArryBindList, OUT int* pReturnCount, OUT int* pTotalNum);


	// ***共享内存名是否增加global前缀***
	VMMODULEFRAME_API int __stdcall VM_M_EnableSharedMemGlobalPrefix(IN bool bEnable);


	// ***设置流程输入输出***
	VMMODULEFRAME_API int __stdcall VM_M_SetProcedureIO(IN int nProcedureId, IN const PROCEDURE_IO_FIELD_PARAM* pArryInput, IN int nInputSize, IN const PROCEDURE_IO_FIELD_PARAM* pArryOutput, IN int nOutputSize);
	

	// ***设置流程、模块输入值（nId可为普通模块id、流程id）***
	VMMODULEFRAME_API int __stdcall VM_M_SetInputString(IN int nId, IN const char* szName, IN int nIndex, IN const char* pValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputInt(IN int nId, IN const char* szName, IN int nIndex, IN int nValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputFloat(IN int nId, IN const char* szName, IN int nIndex, IN float fValue);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputImage(IN int nId, IN const char* szName, IN int nIndex, IN const IMAGE_DATA* pImageData);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputPointset(IN int nId, IN const char* szName, IN int nIndex, IN void* pData, IN int nDataLen);
	VMMODULEFRAME_API int __stdcall VM_M_SetInputBytes(IN int nId, IN const char* szName, IN int nIndex, IN void* pData, IN int nDataLen);


	// pArryName表示要获取的模块输入名称数组，pArryInputState数组元素个数必须与pArryName数组一致，且都为nSize
	VMMODULEFRAME_API int __stdcall VM_M_GetInputState(IN int nModuleId, IN const char** pArryName, int nSize, OUT MODULE_INPUT_STATE* pArryInputState);


	// ***选择上传指定的模块结果***
	VMMODULEFRAME_API int __stdcall VM_M_SelectModuleResult(IN const SELECTED_MODULE* pArrySelectModules, IN int nArrySize);
	VMMODULEFRAME_API int __stdcall VM_M_SelectAllModuleResult();
	VMMODULEFRAME_API int __stdcall VM_M_SelectNoneModuleResult();

	// ***查询/清空模块结果。每次查询之间会共享缓存，不要多线程调用***
	VMMODULEFRAME_API int __stdcall VM_M_QueryModuleHistoryResult(IN int nModuleId, IN const MODULE_HISTORY_INPUT* pInput, OUT MODULE_HISTORY_RESULT* pHistoryRst);
	VMMODULEFRAME_API int __stdcall VM_M_ClearModuleHistoryResult(IN int nModuleId);


    // * 
    VMMODULEFRAME_API int __stdcall VM_M_GetModuleIOBeSubjectByModulesRunParam(IN int nModuleId, IN const char* pszVarParamName, IN OUT VARPARAM_BESUBJECT_MODULES_RUNPARAM_LIST* pRunParamModulesList);
    VMMODULEFRAME_API int __stdcall VM_M_DelModuleIOBeSubectByRunParamRelation(IN int nModuleId, IN const char* pszVarParamName);

    VMMODULEFRAME_API int __stdcall VM_M_SetExcludeModuleName(IN const char* szModuleName);
    VMMODULEFRAME_API int __stdcall VM_M_SetGlobalProcedureDelayTime(IN int nDelayTime);

#ifdef __cplusplus
};
#endif 

#endif //end of _VM_MODULE_FRAME_H_