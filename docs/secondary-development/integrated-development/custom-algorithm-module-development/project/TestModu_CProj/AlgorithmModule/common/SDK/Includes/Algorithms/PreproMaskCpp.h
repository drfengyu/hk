/***************************************************************************************************
* File：PreproMaskCpp.h
* Note：Interface for the mask image creating tool.
*
* Version：3.4.0.3
* Date：2021-01-05
***************************************************************************************************/
#ifndef _PREPRO_MASK_CPP_H_
#define _PREPRO_MASK_CPP_H_

#include <string>
#include "MVDImageCpp.h"
#include "MVDShapeCpp.h"


namespace VisionDesigner
{
    namespace PreproMask
    {
        /*  Note: This is the class for the PreproMaskTool. The PreproMaskTool encapsulates all of
            the classes required to perform a mask creating process.  */
        class IPreproMaskTool
        {
        protected:
            ///< Constructor and Destructor
            explicit IPreproMaskTool() {}
            virtual ~IPreproMaskTool() {}

        public:
            /**
             * @par 说明
             * 输入图像，默认值NULL
             * @par 权限
             * 读写
             */
            virtual IMvdImage* GetInputImage() = 0;
            /**
             * @par 说明
             * 输入图像
             * @par 权限
             * 读写
             */
            virtual void SetInputImage(IMvdImage *pInputImage) = 0;

            /**
             * @par 说明
             * 结果图像，默认值NULL
             * @par 权限
             * 只读
             */
            virtual IMvdImage* GetOutputImage() = 0;

            /**
             * @brief 执行算子处理
             * @param 无
             * @return 无，出错时抛出异常
             * @par 注解
             * 无
             */
            virtual void Run() = 0;

            /**
             * @brief 添加单个区域
             * @param pRegion [IN] 拟增加的区域范围图形
             * @param bRegionInterest [IN] 该区域的保留\屏蔽属性;设true时为感兴趣区域，否则为屏蔽区域
             * @return 无，出错时抛出异常
             * @par 注解
             * 仅支持矩形、圆、扇环和多边形
             */
             virtual void AddRegion(IMvdShape* pRegion, bool bRegionInterest) = 0;
            /**
             * @brief 获取已添加区域数量
             * @return 区域图形数量;出错时抛出异常
             * @par 注解
             * 无
             */
            virtual unsigned int GetNumOfRegions() = 0;
            /**
             * @brief 根据索引查询已添加区域图形信息
             * @param nIndex [IN] 图形索引，范围[0, NumOfRegions)
             * @param ppRegion [IN][OUT] 该区域图形信息
             * @param pRegionInterest [IN][OUT] 该区域的保留\屏蔽属性
             * @return 无，出错时抛出异常
             * @par 注解
             * ppRegion指向内部该图形实例,内部buffer
             */
            virtual void GetRegionAt(unsigned int nIndex, IMvdShape** ppRegion, bool* pRegionInterest) = 0;
            /**
             * @brief 根据索引更新已添加区域图形信息
             * @param nIndex [IN] 图形索引，范围[0, NumOfRegions)
             * @param pRegion [IN] 拟更新为的区域图形信息
             * @param bRegionInterest [IN] 该区域的保留\屏蔽属性;设true时为感兴趣区域，否则为屏蔽区域
             * @return 无，出错时抛出异常
             * @par 注解
             * 支持修改图形类型
             */
            virtual void UpdateRegionAt(unsigned int nIndex, IMvdShape* pRegion, bool bRegionInterest) = 0;
            /**
             * @brief 根据索引移除已添加区域图形
             * @param nIndex [IN] 图形索引，范围[0, NumOfRegions)
             * @return 无，出错时抛出异常
             * @par 注解
             * 无
             */
            virtual void RemoveRegionAt(unsigned int nIndex) = 0;
            /**
             * @brief 清理所有已添加区域
             * @return 无，出错时抛出异常
             * @par 注解
             * 无
             */
            virtual void ClearRegions() = 0;
            /**
            * @par 说明
            * 掩膜图像，默认值NULL
            * @par 权限
            * 读写
            */
            virtual IMvdImage* GetMaskImage() = 0;
            /**
            * @par 说明
            * 掩膜图像
            * @par 权限
            * 读写
            */
            virtual void SetMaskImage(IMvdImage *pMaskImage) = 0;

        private:
            IPreproMaskTool(IPreproMaskTool&);
            IPreproMaskTool& operator=(IPreproMaskTool&);
        };
    }
}


/*  Note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif

    /*  Note: Create tool instance for PreproMaskTool tool.  */
    MVD_CPP_API int __stdcall CreatePreproMaskToolInstance(VisionDesigner::PreproMask::IPreproMaskTool** ppToolInstance);
    /*  Note: Destroy tool instance for PreproMaskTool tool.  */
    MVD_CPP_API int __stdcall DestroyPreproMaskToolInstance(VisionDesigner::PreproMask::IPreproMaskTool* pToolInstance);

#ifdef __cplusplus
}
#endif 


#endif    ///< _PREPRO_MASK_CPP_H_
