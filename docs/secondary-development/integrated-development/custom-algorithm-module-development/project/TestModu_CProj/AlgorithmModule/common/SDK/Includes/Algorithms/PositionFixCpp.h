/***************************************************************************************************
* File：PositionFix.h
* Note：Interface for the Position Fix tool.
*
* Version：3.4.0.3
* Date：2021-01-05
***************************************************************************************************/
#ifndef _POSITION_FIX_H__
#define _POSITION_FIX_H__

#include "MVDShapeCpp.h"
#include "MVD_AlgoParamDefine.h"

namespace VisionDesigner
{
    namespace PositionFix
    {
        /** @struct MVD_FIDUCIAL_POINT_F
         *  @brief  fiducial pose point Info - float type
         */
        typedef _MVD_FIDUCIAL_POINT_F__ MVD_FIDUCIAL_POINT_F;

        /** @struct MVD_POSFIX_MODE
         *  @brief  Position Fix Mode - enum type
         */
        typedef _MVD_POSFIX_MODE__ MVD_POSFIX_MODE;

        /*  Note: Interface Classes for describing position fixture basic param information.  */
        class IPositionFixBasicParam
        {
        protected:
            ///< Constructor and Destructor
            explicit IPositionFixBasicParam() {}
            virtual ~IPositionFixBasicParam() {}

        public:
            /**
             * @par 说明
             * 运行图像尺寸
             * @par 权限
             * 只读
             */
            virtual MVD_SIZE_I GetRunImageSize() = 0;
            /**
             * @par 说明
             * 运行图像尺寸
             * @par 权限
             * 只读
             */
            virtual void SetRunImageSize(MVD_SIZE_I stRunImageSize) = 0;
            /**
             * @par 说明
             * 基准点
             * @par 权限
             * 只读
             */
            virtual MVD_FIDUCIAL_POINT_F GetBasePoint() = 0;
            /**
             * @par 说明
             * 基准点
             * @par 权限
             * 只读
             */
            virtual void SetBasePoint(MVD_FIDUCIAL_POINT_F stBasePoint) = 0;
            /**
             * @par 说明
             * 运行点
             * @par 权限
             * 只读
             */
            virtual MVD_FIDUCIAL_POINT_F GetRunningPoint() = 0;
            /**
             * @par 说明
             * 运行点
             * @par 权限
             * 只读
             */
            virtual void SetRunningPoint(MVD_FIDUCIAL_POINT_F stRunningPoint) = 0;
            /**
             * @par 说明
             * 位置修正模式
             * @par 权限
             * 只读
             */
            virtual MVD_POSFIX_MODE GetFixMode() = 0;
            /**
             * @par 说明
             * 位置修正模式
             * @par 权限
             * 只读
             */
            virtual void SetFixMode(MVD_POSFIX_MODE enFixMode) = 0;
            /**
             * @par 说明
             * 初始形状
             * @par 权限
             * 只读
             */
            virtual IMvdShape* GetInitialShape() = 0;
            /**
             * @par 说明
             * 初始形状
             * @par 权限
             * 只读
             */
            virtual void SetInitialShape(IMvdShape* pstInitialShape) = 0;
        };

        /*  Note: Interface Classes of the result of the PositionFixTool.  */
        class IPositionFixResult
        {
        protected:
            ///< Constructor and Destructor
            explicit IPositionFixResult() {}
            virtual ~IPositionFixResult() {}

        public:
            /**
             * @par 说明
             * 修正后图形
             * @par 权限
             * 只读
             */
            virtual IMvdShape* GetCorrectedShape() = 0;
            /**
             * @par 说明
             * 输出是否有效标志
             * @par 权限
             * 只读
             */
            virtual int GetStatus() = 0;
        };

        /*  Note: This is the class for the PositionFixTool. The PositionFixTool encapsulates all of
            the classes required to finish position fixture of a shape.  */
        class IPositionFixTool
        {
        protected:
            ///< Constructor and Destructor
            explicit IPositionFixTool() {}
            virtual ~IPositionFixTool() {}

        public:
            /**
             * @par 说明
             * 基本参数,内部管理，获取后更新设置。
             * @par 权限
             * 读写
             */
            virtual IPositionFixBasicParam* GetBasicParam() = 0;
            /**
             * @par 说明
             * 运行结果，未执行或执行失败返回NULL
             * @par 权限
             * 只读
             */
            virtual IPositionFixResult* GetResult() = 0;
            /**
             * @brief 执行算子处理
             * @param 无
             * @return 无，出错时抛出异常
             * @par 注解
             * 每个AlgorTool都必须有且只有一个Run方法
             */
            virtual void Run() = 0;

        private:
            IPositionFixTool(IPositionFixTool&);
            IPositionFixTool& operator=(IPositionFixTool&);
        };
    }
}

/*  Note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif

    /*  Note: Create tool instance for PositionFix tool.  */
    MVD_CPP_API int __stdcall CreatePositionFixToolInstance(VisionDesigner::PositionFix::IPositionFixTool** ppToolInstance);
    /*  Note: Destroy tool instance for PositionFix tool.  */
    MVD_CPP_API int __stdcall DestroyPositionFixToolInstance(VisionDesigner::PositionFix::IPositionFixTool* pToolInstance);

#ifdef __cplusplus
}
#endif

#endif    ///< _POSITION_FIX_H__