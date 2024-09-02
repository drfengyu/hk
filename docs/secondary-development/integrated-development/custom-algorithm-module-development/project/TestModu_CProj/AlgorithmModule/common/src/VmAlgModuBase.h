/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2020, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：VmAlgModuBase.h
* 摘    要：算法模块基类
*
* 当前版本：
* 作    者:  视觉平台小组
* 日    期：2020-10-14
* 备    注：新建
****************************************************************************************************/

#ifndef _IMVS_MVDSDK_BASE_MODU_SDK_H_
#define _IMVS_MVDSDK_BASE_MODU_SDK_H_

#include "VmAlgModuTypes.h"
#include "VmModuleBase.h"
#include "ErrorCodeDefine.h"
#include "VmAlgModuCommon.h"
#include "VmModule_IO.h"
#include "VmModuleInternal.h"

#define LOG_STRING_SIZE (1024) // 日志信息长度
//#define DEFAULT_ROI_MSG_DATA ("") // 默认ROI信息二进制数据 [0][0][0.50.51.01.00.0]
//#define DEFAULT_ROI_MSG_LENGTH (0) // 默认ROI信息数据长度

using namespace std;
using namespace VisionDesigner;

/** @class CMyAlgorithmManager
*  @brief
*/
class CVmAlgModuleBase : public CAbstractUserModule
{
protected:

	// 模块ROI数据综合 界面归一化数据
	typedef struct _BASE_MODU_ROI_DATA
	{
		IMVS_ROI_TYPE iRoiTypeIndex; // ROI类型索引

		vector<IMVS_ROI_BOX_EXTEND> stRoiBox; // 矩形ROI
        vector<IMVS_ANNULUS_EXTEND> stRoiAnnulus; // 扇环ROI
		vector<IMVS_POLYGON> stRoiPolygon; // 多边形ROI
		MY_LINECALIPERBOX stLineCaliperBox;   //直线卡尺框结构体
		MY_CIRCLECALIPERBOX stCircleCaliperBox; //圆卡尺框结构体
        IMVS_MATRIXCIRCLE stMatrixCircle; //阵列圆ROI

		_BASE_MODU_ROI_DATA()
		{
            IMVS_ROI_BOX_EXTEND roiBox = { { 0.0f } };

			roiBox.stRoiValue.fRoiCenterX = 0.5f;
            roiBox.stRoiValue.fRoiCenterY = 0.5f;
            roiBox.stRoiValue.fRoiHeight = 1.0f;
            roiBox.stRoiValue.fRoiWidth = 1.0f;
            roiBox.stRoiValue.fRoiAngle = 0.0f;
            roiBox.nVersion = 0;

			stRoiBox.push_back(roiBox);

			iRoiTypeIndex = IMVS_ROI_TYPE_IMAGE;

			memset(&stLineCaliperBox, 0, sizeof(stLineCaliperBox));
			memset(&stCircleCaliperBox, 0, sizeof(stCircleCaliperBox));
            memset(&stMatrixCircle, 0, sizeof(stMatrixCircle));
		}
	}BASE_MODU_ROI_DATA;

	// 模块基类原始输入
	typedef struct _MVDSDK_BASE_MODU_INPUT_INNER
	{
		HKA_S32 nImageInputStatus; //输入图像获取状态
		HKA_S32 nROIInputStatus; //输入ROI获取状态
		HKA_S32 nFixInputStatus; //修正信息获取状态

		HKA_IMAGE stImageIn; //输入图像
        HKA_IMAGE stImageMask; //掩膜图像

		IMVS_ROI_TYPE iRoiTypeIndex; // ROI类型索引
		vector<MVBI_BOX_F> stRoiBox; // 矩形ROI
		vector<MVBI_ANNULUS_F> stRoiAnnulus; // 扇环ROI
		vector<IMVS_POLYGON> stRoiPolygon; // 多边形ROI
		vector<MVBI_BOX_F>  stLineCaliperBox; //直线卡尺框集合
		vector<MVBI_BOX_F>  stCircleCaliperBox; //圆卡尺框集合
        IMVS_MATRIXCIRCLE stRoiMatrixCircle; //阵列圆ROI

		MVBI_FIDUCIAL_POSE stFixInit; // 位置修正基准点
		MVBI_FIDUCIAL_POSE stFixRun; // 位置修正运行点

		_MVDSDK_BASE_MODU_INPUT_INNER()
		{
			nImageInputStatus = false;
			nROIInputStatus = IMVS_ROI_FROM_ERROR;
			nFixInputStatus = IMVS_MODU_ENUM_STATUS_ERROR;

			memset(&stImageIn, 0, sizeof(stImageIn));
            memset(&stImageMask, 0, sizeof(stImageMask));

			iRoiTypeIndex = IMVS_ROI_TYPE_NULL;

			memset(&stFixInit, 0, sizeof(stFixInit));
			memset(&stFixRun, 0, sizeof(stFixRun));
            memset(&stRoiMatrixCircle, 0, sizeof(IMVS_MATRIXCIRCLE));
		}
	}MVDSDK_BASE_MODU_INPUT_INNER;

	// 模块基类处理后输入 包含位置修正 转换算子SDK结构等处理
	typedef struct _MVDSDK_BASE_MODU_INPUT
	{
		HKA_S32 nImageInputStatus; //输入图像获取状态
		HKA_S32 nROIInputStatus; //输入ROI获取状态
		HKA_S32 nFixInputStatus; //修正信息获取状态

		//HKA_IMAGE struInputImg; //输入图像 去除该对象 统一使用 pImageInObj
		IMvdImage* pImageInObj; //输入图像对象

		IMVS_ROI_TYPE iRoiTypeIndex; // ROI类型索引
		vector<IMvdShape*> vtFixRoiShapeObj; // 修正后的ROI对象列表
		vector<IMvdShape*> vctfixShieldedPolygon; // 修正后的多边形屏蔽区
		vector<IMvdShape*> vctFixLineCaliperObj;     //修正后直线卡尺框BOX对象集合
		vector<IMvdShape*> vctFixCircleCaliperObj;   //修正后圆卡尺框BOX对象集合
        IMVS_MATRIXCIRCLE stFixRoiMatrixCircle; // 修正后的阵列圆ROI

		MVBI_BOX_F struDetectBox; // 实际检测区域外接矩形

		MVD_FIDUCIAL_POINT_F stFixInit; // 位置修正基准点
		MVD_FIDUCIAL_POINT_F stFixRun; // 位置修正运行点

		HKA_S32 bUseMask; // 是否已生成掩膜图像
		IMvdImage* pImageMaskObj; // 掩膜图像对象
        char*      pMaskObjSharedName;

		_MVDSDK_BASE_MODU_INPUT()
		{
			nImageInputStatus = false;
			nROIInputStatus = IMVS_ROI_FROM_ERROR;
			nFixInputStatus = IMVS_MODU_ENUM_STATUS_ERROR;

			//memset(&struInputImg, 0, sizeof(struInputImg));
			pImageInObj = NULL;

			iRoiTypeIndex = IMVS_ROI_TYPE_NULL;

			memset(&struDetectBox, 0, sizeof(struDetectBox));

			memset(&stFixInit, 0, sizeof(stFixInit));
			memset(&stFixRun, 0, sizeof(stFixRun));
            memset(&stFixRoiMatrixCircle, 0, sizeof(stFixRoiMatrixCircle));
			bUseMask = false;
			pImageMaskObj = NULL;
            pMaskObjSharedName = NULL;
		}
	}MVDSDK_BASE_MODU_INPUT;

public:
	// 构造
	explicit CVmAlgModuleBase();

	// 析构
	virtual ~CVmAlgModuleBase();

	// 进行算法
	virtual int Process(IN void* hInput, IN void* hOutput);

	// 进行算法
	virtual int Process(IN void* hInput, IN void* hOutput, IN MVDSDK_BASE_MODU_INPUT* pModuInput) = 0;

	// 获取算法参数
	virtual int GetParam(IN const char* szParamName, OUT char* pBuff, IN int nBuffSize, OUT int* pDataLen) override;

	// 设置算法参数
	virtual int SetParam(IN const char* szParamName, IN const char* pData, IN int nDataLen) override;

	// 获取所有参数
	virtual int GetAllParamList(OUT PARAM_VALUE_INFO_LIST* pParamValueList);

	// 保存模块数据
	virtual int SaveModuleData(OUT SAVE_MODULE_DATA_PARAM* pModuleData);

	// 加载模块数据
	virtual int LoadModuleData(IN const LOAD_MODULE_DATA_PARAM* pModuleData);

private:
	CVmAlgModuleBase(const CVmAlgModuleBase &);
	CVmAlgModuleBase & operator=(const CVmAlgModuleBase &);

protected:
	// 获取算法处理输入
	virtual int GetProcessInput(IN const void * const hInput, OUT MVDSDK_BASE_MODU_INPUT_INNER *pModuInput);

	// 进行掩膜生成算法
    virtual int GenerateMaskImage(IN MVDSDK_BASE_MODU_INPUT* pModuInput, IN vector<IMvdShape*> vctROIShape, IN vector<IMvdShape*> vctShieldedShape, IN bool bCheckDiff = false);

	// 清理模块ROI数据
	virtual int ClearRoiData(OUT BASE_MODU_ROI_DATA* stBaseModuROIData);

	// 重置模块默认ROI
	virtual int ResetDefaultRoi(OUT BASE_MODU_ROI_DATA* stBaseModuROIData);

    // 重置模块默认参数
    virtual int ResetDefaultParam();

	// 设置所有参数
	virtual int SetAllParamList(IN const PARAM_VALUE_INFO_LIST* pParamValueList);

	// 动态IO数据处理
    virtual int DynamicIOInit();

	//解析动态IO中额外增加的输出信息
	int AnalyzeExtraIO();

	//动态IO额外增加的信息输出
	int OutputExtra(IN void* hInput, IN void* hOutput);
	
    int UpdataDynamicIO(char** pDynamicIn, int* nDynamicInLen, bool bEnableIn, char** pDynamicOut, int* nDynamicOutLen, bool bEnableOut);
    int UpdataDynamicIO(char** pDynamicIO, int* nDynamicIOLen, void* pXmlElement, bool bCompare);

private:
	// 初始化
	int Init();

	// 反初始化
	void DeInit();

	// 重置成员变量
	void ResetMember();

	// 初始化位置修正算子
    int InitPosFixInstance(IN IPositionFixTool*& pPosFixInstance, IN MVBI_FIDUCIAL_POSE stFixInit, IN MVBI_FIDUCIAL_POSE stFixRun, IN MVD_SIZE_I stImgSize);

	// 位置修正算法处理并转换算子SDK数据结构
	int ProcessFix(IN MVDSDK_BASE_MODU_INPUT_INNER *pModuInput, OUT MVDSDK_BASE_MODU_INPUT* pFixInput);

	// 算法处理结果输出
	int ProcessOutput(IN const void * const hOutput, MVDSDK_BASE_MODU_INPUT &pModuInput);

	// 解析界面绘制ROI信息
	int AnalyzeMultipleROIMsg(IN const char * pData, IN int nDataLen, OUT BASE_MODU_ROI_DATA* const pBaseModuROIData);

	// 生成界面绘制ROI信息
	int GenerateMultipleROIMsg(IN BASE_MODU_ROI_DATA* const stBaseModuROIData, OUT char* const pBuff, IN int nBuffSize, OUT unsigned int& nDataLen);
	
	// 解析界面屏蔽区信息
	int AnalyzePlygonShieldMsg(IN const char * pData, IN int nDataLen, OUT IMVS_POLYGON_MASK_LIST* const pShieldedPolygon);

	// 生成界面屏蔽区信息
	int GeneratePlygonShieldMsg(IN IMVS_POLYGON_MASK_LIST* const stShieldedPolygon, OUT char* const pBuff, IN int nBuffSize, OUT unsigned int& nDataLen);

	void GenerateCircleCenter(float fStartX, float fStartY, float fEndX, float fEndY, float fRadius, int nLargeArc, int nClockwise, float& fCenterX, float& fCenterY);

	double CalYCoordinate(double x, double y, double k, double x0);

	void GenerateAngleInfo(float fStartX, float fStartY, float fEndX, float fEndY, float fCenterX, float fCenterY, int nClockwise, float& fStartAngle, float& fEndAngle);
	
	void GenerateSector(MY_CIRCLECALIPERBOX * inCircle, MY_SECTORCALIPERBOX * outSector);

protected:

	//算子SDK相关对象
	IPositionFixTool*       m_pPosFixProceInstance;          //处理时位置修正对象
    IPositionFixTool*       m_pPosFixParamInstance;          //参数时位置修正对象
	IPreproMaskTool*        m_pPreproMaskInstance;           //掩膜生成对象

	//模块逻辑相关数据
    int                    m_nROIAreaType; //ROI区域类型 0-图形 1-图像
    bool                   m_bOutputMaskImage; //输出掩膜图像 True-输出 False-不输出
	bool                   m_bRoiChanged; //绘制ROI变化标记位 True-改变 False-未改变
	bool                   m_bShieldedChanged; //屏蔽区变化标记位 True-改变 False-未改变
	bool                   m_bInheritMultipleROI; //模块支持继承多ROI标记位 True-支持 False-不支持
	bool                   m_bModuProMask; //子类内部处理掩膜生成标记位  True-子类处理 False-基类处理
	int                    m_nModuleId; // 模块ID

	//算法处理相关数据
	BASE_MODU_ROI_DATA        m_stBaseModuROIData;         //绘制ROI情况下的数据
	IMVS_POLYGON_MASK_LIST    m_stShieldedPolygon;         // 多边形屏蔽区
	MVBI_FIDUCIAL_POSE        m_stFixInit;                // 绘制ROI时的位置修正基准点
	MVBI_FIDUCIAL_POSE        m_stFixRun;                 // 绘制ROI时的位置修正运行点
    MVD_SIZE_I               m_stDrawImageSize;           // 绘制ROI/屏蔽区时的图像尺寸
	MVD_SIZE_I               m_stLastImageSize;           // 上次执行的图像尺寸
	int						 m_nUserDataIndex;            // 保存方案中用户自定义数据基类中解析的个数

protected:
	char * m_pDynamicInData;                          // 输入动态IO数据
	int m_pDynamicInDataLen;                       // 输入动态IO数据长度

	char * m_pDynamicOutData;                         // 输出动态IO数据
	int m_pDynamicOutDataLen;                      // 输出动态IO数据长度

private:

	//算子SDK相关对象
	IMvdImage*             m_pInputImageInstance;           //输入图像对象
    IMvdImage*             m_pMaskImageInstance;           //掩膜图像对象

	//基类运行所需变量
	IMvdRectangleF*         m_pRectROIObj[IMVS_MULTIPLE_ROI_COUNT_MAX];//ROI矩形数据运行缓存
	IMvdAnnularSectorF*     m_pAnnuROIObj[IMVS_MULTIPLE_ROI_COUNT_MAX];//ROI扇环数据运行缓存
	IMvdPolygonF*           m_pPolyROIObj[IMVS_MULTIPLE_ROI_COUNT_MAX];//ROI多边形数据运行缓存
	IMvdPolygonF*           m_pPolyMaskObj[IMVS_ROI_POLYGOPN_COUNT_MAX];//多边形屏蔽区数据运行缓存
	IMvdRectangleF*         m_pRectCaliperObj[IMVS_MAX_CALIPER_NUMBER];//ROI卡尺数据运行缓存
	unsigned int            m_nMultipleROILen;//ROI数据交互缓存数据长度
	char                   m_szMultipleROIBuf[IMVS_COMMON_POLYGON_LEN_MAX * IMVS_MULTIPLE_ROI_COUNT_MAX]; //ROI数据交互缓存
	unsigned int            m_nPolygonMaskLen;//ROI数据交互缓存数据长度
	char                   m_szPolygonMaskBuf[IMVS_COMMON_POLYGON_LEN_MAX * IMVS_ROI_POLYGOPN_COUNT_MAX]; //多边形屏蔽区数据交互缓存
	char                   m_chszLog[LOG_STRING_SIZE]; //日志信息
    char                   m_chMaskImageSharedName[SHARED_MEM_NAME_LEN];//掩膜图像共享内存


	int m_nSectorCaliperClockwise;                 //记录圆弧卡尺的顺逆时针方向
	vector<pair<string, string>> m_vecExtraIO;//内容是:名称-类型
};

#endif // _IMVS_MVDSDK_BASE_MODU_SDK_H_
