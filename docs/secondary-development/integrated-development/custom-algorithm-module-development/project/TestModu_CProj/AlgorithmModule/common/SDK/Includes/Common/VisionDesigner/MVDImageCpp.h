/***************************************************************************************************
* File:  MVDImageCpp.h
* Note:  Interface definition of image module.
****************************************************************************************************/
 
#ifndef _MVD_IMAGE_CPP_H__
#define _MVD_IMAGE_CPP_H__
 
#include "MVD_Export.h"
#include "MVD_ErrorDefine.h"
#include "MVD_ImageParamDefine.h"
 
namespace VisionDesigner
{
    /* Class that represents an image. */
    class IMvdImage
    {
    //Constructor and Destructor
    public:
        explicit IMvdImage() {}
        virtual ~IMvdImage() {}
 
    public:
        /**
         * @brief 克隆图像描述类
         * @param 无
         * @return 成功，返回图像描述类信息;失败，抛出异常。
         * @par 注解
         * 无
         */
        /* Returns a deep copy of this class instance. Derived classes that implement 
           Clone should override this method. Other clients who wish to clone this instance 
           should call IMvdImage.Clone. */
        virtual IMvdImage* Clone() = 0;
         
    public:
        /**
         * @par 说明
         * 图像宽
         * @par 权限
         * 只读
         */
        /* note: Get width of this image. */
        virtual unsigned int GetWidth() = 0;
        /**
         * @par 说明
         * 图像高
         * @par 权限
         * 只读
         */
        /* note: Get height of this image. */
        virtual unsigned int GetHeight() = 0;
        /**
         * @par 说明
         * 像素格式
         * @par 权限
         * 只读
         */
        /* note: Get pixel format of this image. */
        virtual MVD_PIXEL_FORMAT GetPixelFormat() = 0;
         
    public:
        /**
         * @brief 获取图像指定通道的数据
         * @param nIndex [IN] 通道索引值
         * @return 成功，返回图像指定通道数据;失败，抛出异常。
         * @par 注解
         * (a)索引值从0开始编号。</br>
         * (b)获取的对应索引号的图像数据信息。
         */
        /* note: Get data of specified channel of this image. Index values start numbering from 0. */
        virtual MVD_DATA_CHANNEL_INFO* GetImageData(unsigned int nIndex) = 0;
        /**
         * @brief 获取图像全部数据
         * @param 无
         * @return 成功，返回图像信息;失败，抛出异常。
         * @par 注解
         * 获取的是整张图像全部数据信息。
         */
         
        /* note: Get whole data of this image. */
        virtual MVD_IMAGE_DATA_INFO* GetImageData() = 0;
         
        /**
         * @brief 初始化图像资源
         * @param nWidth [IN] 图像的宽
         * @param nHeight [IN] 图像的高
         * @param enPixelFormat [IN] 像素格式
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * (a)需要在构造函数之后立即调用InitImage函数。</br>
         * (b)基于指定的宽、高和像素格式初始化图像资源，每个像素的值将被设置为0。
         */
        /* note: InitImage method must be called immediately after the constructor */
        /* note: Init image resources based on the specified width, height and pixel format. Value of each pixel will be set to zero. */
        virtual void InitImage(unsigned int nWidth, unsigned int nHeight, MVD_PIXEL_FORMAT enPixelFormat) = 0;
        /**
         * @brief 初始化图像资源
         * @param nWidth [IN] 图像的宽
         * @param nHeight [IN] 图像的高
         * @param enPixelFormat [IN] 像素格式
         * @param stImageDataInfo [IN] 图像信息结构体
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * (a)需要在构造函数之后立即调用InitImage函数。</br>
         * (b)基于指定的宽、高和像素格式初始化图像资源，内部不对图像数据做拷贝，而是直接引用传入的图像信息buffer。
         */
        /* note: Init image resources based on the specified width, height and pixel format. 'pImageData' will be referenced directly without deep copy. */
        virtual void InitImage(unsigned int nWidth, unsigned int nHeight, MVD_PIXEL_FORMAT enPixelFormat, MVD_IMAGE_DATA_INFO stImageDataInfo) = 0;
        /**
         * @brief 从本地文件初始化图像资源
         * @param pcFileName [IN] 文件名称
         * @param nPixelFormat [IN] 像素格式
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * (a)需要在构造函数之后立即调用InitImage函数。</br>
         * (b)基于指定的像素格式和文件名初始化图像资源。</br>
         * 内部会自动转化为目标像素格式；若是不支持的转换关系，则抛出异常。
         */
        /* note: Init image resources based on the specified pixel format and filename. */
        virtual void InitImage(const char* const pcFileName, MVD_PIXEL_FORMAT enPixelFormat = MVD_PIXEL_NULL) = 0;
         
        /**
         * @brief 保存图像
         * @param pcFileName [IN] 文件名称
         * @param nFileFormat [IN] 文件格式
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * (a)使用默认参数保存本地图像，例如jpg的压缩比例默认是75%。</br>
         * (b)如果用户指定文件格式，则以目标格式存储；若没有，则存储格式由文件名后缀决定。
         */
        /* note: Save the image locally with default parameters, e.g. Jpeg Quality default 75. */
        /* If the user specifies a file format, it is stored in the target format. Otherwise judged by file name suffix. */
        virtual void SaveImage(const char* const pcFileName, MVD_FILE_FORMAT enFileFormat = MVD_FILE_AUTO) = 0;
        /**
         * @brief 保存Jpg格式图片
         * @param JpegQuality [IN] jpg编码质量
         * @param pcFileName [IN] 文件名称
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 保存的图片为jpg格式。
         */
        /* note: Save Jpeg locally. */
        virtual void SaveJpeg(unsigned int nJpegQuality, char* pcFileName) = 0;
         
        /**
         * @brief 更新指定像素的值
         * @param nRowId [IN] 行号，即该像素处于第几行
         * @param nColId [IN] 列号，即该像素处于第几列
         * @param pcDstVal[4] [IN] 设置的目标值
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 行和列都是从0开始编号的。
         */
        /* note: Update the value of the specified pixel. Numbered from 0. */
        virtual void SetPixel(unsigned int nRowId, unsigned int nColId, unsigned char pcDstVal[4]) = 0;
         
        /**
         * @brief 选择插值算法调整图像大小
         * @param nDstWidth [IN] 目标宽度
         * @param nDstHeight [IN] 目标高度
         * @param enInterpolationType [IN] 插值类型
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 无
         */
        /* note: Choose interpolation algorithm to resize image. */
        virtual void ResizeImage(unsigned int nDstWidth, unsigned int nDstHeight, MVD_IMG_INTERPOLATION_TYPE enInterpolationType) = 0;
         
        /**
         * @brief 像素格式转换
         * @param nDstPixelFormat [IN] 目标像素格式
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 格式转换成功后，图像的属性会进行同步更新。
         */
        /* Transform this image to the specified pixel format. Attributes will be updated at the same time. */
        virtual void ConvertImagePixelFormat(MVD_PIXEL_FORMAT enDstPixelFormat) = 0;
         
        /**
         * @brief 获取私有数据
         * @param ppcPvtData [IN] 用于存储数据的buffer
         * @param pnPvtDataLen [IN][OUT] 用于存储数据的buffer长度
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 当传入长度不足时，接口会返回真实所需长度。
         */
        virtual void GetPrivateData(unsigned char **ppcPvtData, unsigned int *pnPvtDataLen) = 0;
        /**
         * @brief 设置私有数据
         * @param pcPvtData [IN] 输入数据buffer
         * @param nPvtDataLen [IN] 输入数据长度，字节;设长度0则会清除私有数据
         * @return 成功，无返回;失败，抛出异常。
         * @par 注解
         * 以jpeg格式存图时，该数据会一并记录;深拷贝
         */
        /* Set private data. When saving the image in Jpeg format, the data will also be written to the file. */
        virtual void SetPrivateData(unsigned char* pcPvtData, unsigned int nPvtDataLen) = 0;
         
        /**
        * @brief 裁剪图像
        * @param nClipX [IN] 裁剪图像的起始X坐标
        * @param nClipY [IN] 裁剪图像的起始Y坐标
        * @param nClipWidth [IN] 裁剪图像的宽度
        * @param nClipHeight [IN] 裁剪图像的高度
        * @return 成功，无返回;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: Choose rectangle to clip image. */
        virtual void ClipImage(unsigned int nClipX,unsigned int nClipY,unsigned int nClipWidth,unsigned int nClipHeight)=0;
        /**
        * @brief 旋转图像
        * @param MVD_IMG_ROTATION_ANGLE [IN] 图像旋转角度
        * @return 成功，无返回;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: Choose angle to rotate image. */
        virtual void RotateImage(MVD_IMG_ROTATION_ANGLE enRotationAngle)=0;
        /**
        * @brief 翻转图像
        * @param MVD_IMG_FLIP_TYPE [IN] 图像翻转类型
        * @return 成功，无返回;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: Choose flip type to flip image. */
        virtual void FlipImage(MVD_IMG_FLIP_TYPE enFlipType)=0;
        /**
        * @brief 更新指定像素的值
        * @param nX [IN] 像素坐标X
        * @param nY [IN] 像素坐标Y
        * @param stPixelValue [IN] 设置的像素值
        * @return 成功，无返回;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: Set Pixel by position. */
        virtual void SetPixel(int nX, int nY, MVD_SCALAR stPixelValue) = 0;
        /**
        * @brief 获取指定像素的值
        * @param nX [IN] 像素坐标X
        * @param nY [IN] 像素坐标Y
        * @return 成功，返回像素值;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: Get Pixel by position. */
        virtual MVD_SCALAR GetPixel(int nX, int nY) = 0;
        /**
        * @brief 释放图像资源
        * @return 无;失败，抛出异常。
        * @par 注解
        * 无
        */
        /* note: release image data. */
        virtual void Release() = 0;
       /**
        * @brief 内部保留
        * @par 注解
        * 无
        */
        /* note: Get name of shared memory. */
        virtual char* GetData(const char* pKey) = 0;
         /**
        * @brief 内部保留
        * @par 注解
        * 无
        */
        /* note: Set open or close shared memory. */
        virtual void SetData(const char* pKey, const char* pValue) = 0;
        /**
        * @brief 判断图像是否为空
        * @return 图像为空时，返回true;否则返回false
        * @par 注解
        * 无
        */
        /* note: Check whether the image is empty or not. */
        virtual bool IsEmpty() = 0;
    };
}
 
 
/*  note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif
     
    /**
     * @brief 创建图像实例
     * @param ppImageInstance [in\out] 图像实例地址
     * @return 返回状态码（成功为MVD_OK）。
     * @par 注解
     * C++图像实例通过标准C接口形式来创建。
     */
    /* note: Create object of IMvdImage. Image resources will not be created until the 'InitImage' function be called. */
    MVD_CPP_API int __stdcall CreateImageInstance(VisionDesigner::IMvdImage** ppImageInstance);
     
	/**
     * @brief 销毁图像实例
     * @param pImageInstance [IN] 图像实例地址
     * @return 返回状态码（成功为MVD_OK）。
     * @par 注解
     * C++图像实例通过标准C接口形式来创建，与CreateImageInstance请配对使用。
     */
    /* note: Destroy object of IMvdImage. */
    MVD_CPP_API int __stdcall DestroyImageInstance(VisionDesigner::IMvdImage* pImageInstance);
     
#ifdef __cplusplus
}
#endif 
 
 
#endif    ///<_MVD_IMAGE_CPP_H__
