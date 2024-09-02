#include "VmModuleSharedMemoryBase.h"
#include "ErrorCodeDefine.h"
#include <objbase.h>
#include "HSlog/HSlog.h"
#include "HSlog/HSlogDefine.h"
#include "SharedMemory.h"
#include "VmModuleInternal.h"


CModuleSharedMemoryBase::CModuleSharedMemoryBase()
    :m_nNodeNum(SHAREDMEMORY_NODE_NUM)
{
    GetGuidStr();
}

CModuleSharedMemoryBase::~CModuleSharedMemoryBase()
{
    for (auto itUseType : m_mapSharedMemoryInfo)
    {
        for (auto it : itUseType.second)
        {
            CloseMapping(-1, it.get());
        }
        itUseType.second.clear();
    }
}

int CModuleSharedMemoryBase::AllocateSharedMemory(int nModuleId, unsigned int nLen, char** pMemory, char** pSharedName, int nUsageType)
{
    if (nLen < 1)
    {
        return IMVS_EC_PARAM;
    }

    try
    {
        CMappingInfoList& listModuleShared = m_mapSharedMemoryInfo[nUsageType];
        size_t iSize = listModuleShared.size();
        CMappingInfoPtr spSharedMemory = NULL;
        int nGlobalNodeNum = 0;

        VM_M_GetBufferNodeNum(&nGlobalNodeNum);

        //检查节点数
        if (listModuleShared.size() >0 && listModuleShared.front()->uiMappingSize == 0)
        {
            spSharedMemory = listModuleShared.front();
            listModuleShared.pop_front();
        }
        else if (iSize < max(nGlobalNodeNum, m_nNodeNum))
        {
            spSharedMemory = std::make_shared<SharedMemoryMappingInfo>();
            memset(spSharedMemory.get(), 0, sizeof(SharedMemoryMappingInfo));
            _snprintf_s(spSharedMemory->chMappingName, sizeof(spSharedMemory->chMappingName) - 1, _TRUNCATE, "{%d-%d-%d-%s-%d}",
                nModuleId, nUsageType, static_cast<int>(GetCurrentProcessId()), m_chGuid, static_cast<int>(iSize));

            MLOG_DEBUG(nModuleId, "Map view of file, name=%s", spSharedMemory->chMappingName);
        }
        else
        {
            spSharedMemory = listModuleShared.front();
            listModuleShared.pop_front();
        }        
        
        //判断大小
        if (spSharedMemory->uiMappingSize < nLen)
        {
            if (spSharedMemory->uiMappingSize != 0)
            {
                CloseMapping(nModuleId,spSharedMemory.get());
            }

            spSharedMemory->uiMappingSize = nLen;

            if (IMVS_EC_OK != CreateOpenMapping(nModuleId, spSharedMemory.get()))
            {
                CloseMapping(nModuleId, spSharedMemory.get());
                return IMVS_EC_OPEN_FILEMAPPING;
            }

            SHARED_MEM_HEADER* pMemoryHeader = (SHARED_MEM_HEADER*)(spSharedMemory->pMappingView);
            pMemoryHeader->nSize = nLen;
            pMemoryHeader->nHeaderLen = IMAGE_MAPPING_HEADER_LEN;
			pMemoryHeader->byLightCopy = 0;

            memcpy_s(pMemoryHeader->szSharedMemName, sizeof(pMemoryHeader->szSharedMemName),
                spSharedMemory->chMappingName, sizeof(spSharedMemory->chMappingName));

        }

        SHARED_MEM_HEADER* pMemoryHeader = (SHARED_MEM_HEADER*)(spSharedMemory->pMappingView);
        pMemoryHeader->nSize = nLen;

        *pMemory = spSharedMemory->pMappingView + IMAGE_MAPPING_HEADER_LEN;
        *pSharedName = spSharedMemory->chMappingName;

        //切换下一节点 
        listModuleShared.push_back(spSharedMemory);

        return IMVS_EC_OK;
    }
    catch (...)
    {
        MLOG_ERROR(nModuleId, "catch exception");
        return IMVS_EC_OPEN_FILEMAPPING;
    }
}

int CModuleSharedMemoryBase::ReleaseSharedMemory(int nModuleId, char* pSharedName)
{
    if (pSharedName == NULL)
    {
        return IMVS_EC_PARAM;
    }

    int nParseModuleId;
    int nUsageType;
    int nRet = ParseSharedName(pSharedName, nParseModuleId, nUsageType);

    if (nRet != IMVS_EC_OK)
    {
        return nRet;
    }

    if (nModuleId != nParseModuleId)
    {
        MLOG_ERROR(nModuleId, "Module[%d] want release sharedmemory[%s]", nModuleId, pSharedName);
        return IMVS_EC_PARAM;
    }

    CMappingInfoPtr spTarget = NULL;
    size_t iSize = 0;

    CMappingInfoList& listModuleShared = m_mapSharedMemoryInfo[nUsageType];

    if (strcmp(listModuleShared.back()->chMappingName, pSharedName) == 0)
    {
        spTarget = listModuleShared.back();
        listModuleShared.pop_back();
    }
    else
    {
        for (auto it = listModuleShared.begin(); it != listModuleShared.end(); it++)
        {
            if (strcmp((*it)->chMappingName, pSharedName) == 0)
            {
                spTarget = *it;
                listModuleShared.erase(it);
                break;
            }
        }
    }

    if (spTarget != NULL)
    {
        CloseMapping(-1, spTarget.get());
        listModuleShared.push_front(spTarget);
    }
    

    return IMVS_EC_OK;
}

int CModuleSharedMemoryBase::SetNodeNum(IN const char* pData, IN int nDataLen)
{
    if (pData == NULL)
    {
        return IMVS_EC_PARAM;
    }

    int nNodeNum = 0;
    if (sscanf_s(pData, "%d", &nNodeNum) == 0)
    {
        MLOG_ERROR(-1,"Parse node num fail ,data[%s]", pData);
        return IMVS_EC_PARAM;
    }

    if (m_nNodeNum < nNodeNum)
    {
        m_nNodeNum = nNodeNum;
        MLOG_WARN(-1, "Set node num [%d]", nNodeNum);
    }
    else
    {
        MLOG_WARN(-1, "The current num of nodes [%d] exceeds the set num [%d]", m_nNodeNum, nNodeNum);
    }
    return IMVS_EC_OK;
}

int CModuleSharedMemoryBase::GetNodeNum(IN OUT char** pData, IN OUT int* pDataLen)
{
    if (pData == NULL)
    {
        return IMVS_EC_PARAM;
    }

    int nGlobalNodeNum = 0;
    int nRet = VM_M_GetBufferNodeNum(&nGlobalNodeNum);
    if (nRet != IMVS_EC_OK)
    {
        MLOG_ERROR(-1, "Get global node num fail");
    }

    sprintf_s(m_chNodeNum, "%d", max(nGlobalNodeNum, m_nNodeNum));
    *pData = m_chNodeNum;
    if (pDataLen != NULL)
    {
        *pDataLen = strlen(*pData);
    }

    return IMVS_EC_OK;
}

int CModuleSharedMemoryBase::CreateOpenMapping(int nModuleId, void* pMappingInfo)
{
    if (pMappingInfo == NULL)
    {
        return IMVS_EC_PARAM;
    }

    SharedMemoryMappingInfo* pMapping = (SharedMemoryMappingInfo*)pMappingInfo;
    if (pMapping->uiMappingSize == 0 || strlen(pMapping->chMappingName) == 0)
    {
        MLOG_ERROR(nModuleId, "CreateOpenMapping fail,size=%d, len=%d", pMapping->uiMappingSize, pMapping->chMappingName);
        return IMVS_EC_PARAM;
    }

    int iErr = IMVS_EC_OK;
    int iSize = pMapping->uiMappingSize*1.1 + IMAGE_MAPPING_HEADER_LEN;
    pMapping->hMapping = SHM_CreateMapping(pMapping->chMappingName, iSize);
    pMapping->uiMappingSize = iSize;
    if (pMapping->hMapping == NULL)
    {
        MLOG_ERROR(nModuleId, "Create file mapping, name=%s, size=%llu, error=%d", pMapping->chMappingName, iSize, iErr);
        CloseMapping(nModuleId, pMapping);
        return IMVS_EC_OPEN_FILEMAPPING;
    }

    pMapping->pMappingView = (char*)SHM_WriteMapView(pMapping->hMapping, pMapping->uiMappingSize);
    
    if (pMapping->pMappingView == NULL)
    {
        MLOG_ERROR(nModuleId, "Map view of file failed, name=%s, sys error=%d", pMapping->chMappingName, iErr);
        CloseMapping(nModuleId, pMapping);
        return IMVS_EC_OPEN_FILEMAPPING;
    }

    return IMVS_EC_OK;
}

int CModuleSharedMemoryBase::CloseMapping(int nMdouleId, void* pMappingInfo)
{
    if (pMappingInfo == NULL)
    {
        return IMVS_EC_PARAM;
    }

    SharedMemoryMappingInfo* pMapping = (SharedMemoryMappingInfo*)pMappingInfo;
    int iUnMapViewErr = 0;
    int iCloseMappingErr = 0;

    if (pMapping->uiMappingSize == 0)
    {
        return IMVS_EC_PARAM;
    }

    iUnMapViewErr = SHM_UnMapView(pMapping->pMappingView, pMapping->uiMappingSize);
    if (iUnMapViewErr != IMVS_EC_OK)
    {
        MLOG_ERROR(nMdouleId, "Unmap view of file failed, name=%s, sys error=%d", pMapping->chMappingName, iUnMapViewErr);
    }

    if (pMapping->hMapping != NULL)
    {
        iCloseMappingErr = SHM_DestroyWriteMapping(pMapping->hMapping, pMapping->chMappingName);
        if (IMVS_EC_OK != iCloseMappingErr)
        {
            MLOG_ERROR(nMdouleId, "Close file mapping failed, name=%s, sys error=%d", pMapping->chMappingName, iCloseMappingErr);
        }
    }

    pMapping->hMapping = NULL;
    pMapping->pMappingView = NULL;
    pMapping->uiMappingSize = 0;

    return iCloseMappingErr == IMVS_EC_OK ? iUnMapViewErr : iCloseMappingErr;
}

char* CModuleSharedMemoryBase::GetGuidStr()
{
    GUID guid;
    CoCreateGuid(&guid);
    sprintf_s(m_chGuid, sizeof(m_chGuid), "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        static_cast<unsigned int>(guid.Data1), guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    return m_chGuid;
}

int CModuleSharedMemoryBase::ParseSharedName(char* pSharedName, int& nModuleId, int& nUseType)
{
    if (pSharedName == NULL)
    {
        return IMVS_EC_PARAM;
    }

    int  nRet = IMVS_EC_OK;
    if (sscanf_s(pSharedName, "{%d-%d-*}", &nModuleId, &nUseType) != 2)
    {
        MLOG_ERROR(-1, "%s parse fail", pSharedName);
        nRet = IMVS_EC_DATA_ERROR;
    }
    return nRet;
}
