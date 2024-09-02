/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2020, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：VmModuleSharedMemoryBase.h
* 摘    要：共享内存基类
*
* 当前版本：
* 作    者:  视觉平台小组
* 日    期：2022-08-14
* 备    注：新建
****************************************************************************************************/

#ifndef _IMVS_MVDSDK_SHARED_MEMORY_BASE_H_
#define _IMVS_MVDSDK_SHARED_MEMORY_BASE_H_

#include "VmModuleDef.h"
#include <map>
#include <memory>
#include <list>
#include <string>

#define IMAGE_MAPPING_HEADER_LEN  (sizeof(SHARED_MEM_HEADER))  // 共享内存映射信息头长度,与算子保持一致
#define SHAREDMEMORY_NODE_NUM     1

typedef std::shared_ptr<SharedMemoryMappingInfo> CMappingInfoPtr;
typedef std::list<CMappingInfoPtr> CMappingInfoList;
typedef std::map<int, CMappingInfoList> CMappingInfoMap;

class CModuleSharedMemoryBase
{
public:
    CModuleSharedMemoryBase();
    virtual ~CModuleSharedMemoryBase();

protected:

    /**  @fn    AllocateSharedMemory
    *   @brief  模块主动申请共享内存
    *   @param  [IN]  nModuleId       模块ID
                [IN]  nLen            所需内存长度
                [OUT] pMemory         用于接收内存指针的变量，指向共享内存的数据，需传入空指针
                [OUT] chSharedName    共享内存名称
                [IN]  nUsageType      使用类型，由模块定义，同一模块相同类型的申请会在数个共享内存中交替使用
    *   @remark
    *   @return 错误码，参见ErrorCodeDefine.h
    */
    virtual int AllocateSharedMemory(IN int nModuleId, IN unsigned int nLen, IN OUT char** pMemory, IN OUT char** pSharedName, IN int nUsageType = 0);

    /**  @fn    ReleaseSharedMemory
    *   @brief  根据名称释放共享内存,模块删除时会自动是否该模块申请的共享内存
    *   @param  [IN]  nModuleId       模块ID
                [IN]  chSharedName    共享内存名称
    *   @remark
    *   @return 错误码，参见ErrorCodeDefine.h
    */
    virtual int ReleaseSharedMemory(IN int nModuleId, IN char* pSharedName);

    /**  @fn    SetNodeNum
    *   @brief  设置共享内存节点数
    *   @param  [IN]  pData       数量
                [IN]  nDataLen    数据长度
    *   @remark
    *   @return 错误码，参见ErrorCodeDefine.h
    */
    virtual int SetNodeNum(IN const char* pData, IN int nDataLen);

    /**  @fn    SetNodeNum
    *   @brief  获取共享内存节点数
    *   @param  [IN][OUT]  pData       数量
                [IN][OUT]  pDataLen    数据长度
    *   @remark
    *   @return 错误码，参见ErrorCodeDefine.h
    */
    virtual int GetNodeNum(IN OUT char** pData, IN OUT int* pDataLen);

private:
    int   CloseMapping(int nMdouleId, void* spMapping);
    int   CreateOpenMapping(int nMdouleId, void* spMapping);
    char* GetGuidStr();
    int   ParseSharedName(char* pSharedName, int& nModuleId, int& nUseType);

private:
    int   m_nNodeNum;
    char  m_chGuid[64];
    char  m_chNodeNum[16];
    CMappingInfoMap m_mapSharedMemoryInfo;
};

#endif
