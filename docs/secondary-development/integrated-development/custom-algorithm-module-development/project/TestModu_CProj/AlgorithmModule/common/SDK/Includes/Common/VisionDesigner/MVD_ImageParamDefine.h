/***************************************************************************************************
* File:  MVDImageDefine.h
* Note:  Parameter and data struct definition of image module in namespace VisionDesigner.
*
* Version:  V3.1.0.0
* Date:  201901
****************************************************************************************************/

#ifndef _MVD_IMAGE_PARAM_DEFINE_H__
#define _MVD_IMAGE_PARAM_DEFINE_H__

namespace VisionDesigner
{
    /** @enum   MVD_PIXEL_FORMAT
     *  @brief  pixel format
     */
    typedef enum _MVD_PIXEL_FORMAT_
    {
        MVD_PIXEL_NULL               = 0,
        //----------------------------------//----------------------------------------------------------
        //MONO (0~99)                       //| bit  |   store position    |        step        |
        //Mono8                             //----------------------------------------------------------
        MVD_PIXEL_MONO_08             = 1,    //| 8b   |        D0           |         S0         |
        //Mono12                            //----------------------------------------------------------
        MVD_PIXEL_MONO_12             = 2,    //| 12b  |        D0           |         S0         |
        //Mono16                            //----------------------------------------------------------
        MVD_PIXEL_MONO_16             = 3,    //| 16b  |        D0           |         S0         |
        MVD_PIXEL_MONO_10 = 4,    //| 16b   |        D0           |         S0         |
        MVD_PIXEL_MONO_10_Packed = 5,    //|  10b  |        D0           |         S0         |
        MVD_PIXEL_MONO_12_Packed = 6,    //| 12b  |        D0           |         S0         |

        //----------------------------------//----------------------------------------------------------
        //YUV (100~199)                     //| bit  |   store position    |        step        |
        //YUV420 I420                       //----------------------------------------------------------
        MVD_PIXEL_YUV_I420            = 100,  //| 8b   |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2    |
        //YUV420 YV12                       //----------------------------------------------------------
        MVD_PIXEL_YUV_YV12            = 101,  //| 8b   |    Y:D0,V:D1,U:D2   |  Y:S0,V:S1,U:S2    |
        //YUV420 NV12                       //----------------------------------------------------------
        MVD_PIXEL_YUV_NV12            = 102,  //| 8b   |    Y:D0,UV:D1       |  Y:S0,UV:S1        |
        //YUV422 3 plane                    //----------------------------------------------------------
        MVD_PIXEL_YUV_422             = 103,  //| 8b   |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2    |
        //YUV422 UYVY                       //----------------------------------------------------------
        MVD_PIXEL_YUV_UYVY            = 104,  //| 8b   |    YUV:D0           |  YUV:S0            |
        //YUV444 3 plane                    //----------------------------------------------------------
        MVD_PIXEL_YUV_444             = 105,  //| 8b   |    Y:D0,U:D1,V:D2   |  Y:S0,U:S1,V:S2    |
        MVD_PIXEL_YUV_422_Packed = 106,  //| 16b   |    YUV:D0   |  YUV:S0    |
        MVD_PIXEL_YUV_YUYV_Packed = 107,  //| 16b   |    YUV:D0   |  YUV:S0    |

        //----------------------------------//----------------------------------------------------------
        //RGB (200~299)                     //| bit  |   store position    |        step        |
        //RBG 3 plane                       //----------------------------------------------------------
        MVD_PIXEL_RGB_RGB24_P3        = 200,  //| 8b   |    R:D0,G:D1,B:D2   |  R:S0,G:S1,B:S2    |
        //RGB 3 RGBRGB...                   //----------------------------------------------------------
        MVD_PIXEL_RGB_RGB24_C3        = 201,  //| 8b   |    RGB:D0           |  RGB:S0            |
        //RGB 4 plane(alpha)                //----------------------------------------------------------
        MVD_PIXEL_RGB_RGBA_P4         = 202,  //| 8b   | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3|
        //RGB 4 RGBARGBA...(alpha)          //----------------------------------------------------------
        MVD_PIXEL_RGB_RGBA_C4         = 203,  //| 8b   |    RGBA:D0          |  RGBA:S0           |
        //RGB 4 plane(depth)                //----------------------------------------------------------
        MVD_PIXEL_RGB_RGBD_P4         = 204,  //| 8b   | R:D0,G:D1,B:D2,A:D3 | R:S0,G:S1,B:S2,A:S3|
        //RGB 4 RGBDRGBD...(depth)          //----------------------------------------------------------
        MVD_PIXEL_RGB_RGBD_C4         = 205,  //| 8b   |    RGBA:D0          |  RGBA:S0           |
        //BGR 3 BGRBGR...
        MVD_PIXEL_BGR_BGR24_C3 = 206,  //| 24b   |    BGR:D0           |  BGR:S0            |
        //BGR 4 BGRABGRA...(alpha)
        MVD_PIXEL_BGR_BGRA_C4 = 207,  //| 32b   |    BGRA:D0           |  BGRA:S0            |

        //----------------------------------//----------------------------------------------------------
        //bayer (300~399)                   //| bit  |   store position    |        step        |
        //bayer GRGB 10bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_GRBG_10       = 300,  //| 10b  |    GRBG:D0          |  GRBG:S0           |
        //bayer RGGB 10bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_RGGB_10       = 301,  //| 10b  |    RGGB:D0          |  RGGB:S0           |
        //bayer BGGR 10bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_BGGR_10       = 302,  //| 10b  |    BGGR:D0          |  BGGR:S0           |
        //bayer GBRG 10bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_GBRG_10       = 303,  //| 10b  |    GBRG:D0          |  GBRG:S0           |
        //bayer GRBG 10bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_GRBG_12       = 304,  //| 12b  |    GRBG:D0          |  GRBG:S0           |
        //bayer RGGB 12bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_RGGB_12       = 305,  //| 12b  |    RGGB:D0          |  RGGB:S0           |
        //bayer BGGR 12bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_BGGR_12       = 306,  //| 12b  |    BGGR:D0          |  BGGR:S0           |
        //bayer GBRG 12bit                  //----------------------------------------------------------
        MVD_PIXEL_BAYER_GBRG_12       = 307,  //| 12b  |    GBRG:D0          |  GBRG:S0           |
        MVD_PIXEL_BAYER_GRBG_08 = 308,  //| 8b  |    GRBG:D0          |  GRBG:S0           |
        MVD_PIXEL_BAYER_RGGB_08 = 309,  //| 8b  |    RGGB:D0          |  RGGB:S0           |
        MVD_PIXEL_BAYER_BGGR_08 = 310,  //| 8b  |    BGGR:D0          |  BGGR:S0           |
        MVD_PIXEL_BAYER_GBRG_08 = 311,  //| 8b  |    GBRG:D0          |  GBRG:S0           |
        MVD_PIXEL_BAYER_GRBG_10_Packed = 312,  //| 10b  |    GRBG:D0          |  GRBG:S0           |
        MVD_PIXEL_BAYER_RGGB_10_Packed = 313,  //| 10b  |    RGGB:D0          |  RGGB:S0           |
        MVD_PIXEL_BAYER_BGGR_10_Packed = 314,  //| 10b  |    BGGR:D0          |  BGGR:S0           |
        MVD_PIXEL_BAYER_GBRG_10_Packed = 315,  //| 10b  |    GBRG:D0          |  GBRG:S0           |
        MVD_PIXEL_BAYER_GRBG_12_Packed = 316,  //| 12b  |    GRBG:D0          |  GRBG:S0           |
        MVD_PIXEL_BAYER_RGGB_12_Packed = 317,  //| 12b  |    RGGB:D0          |  RGGB:S0           |
        MVD_PIXEL_BAYER_BGGR_12_Packed = 318,  //| 12b  |    BGGR:D0          |  BGGR:S0           |
        MVD_PIXEL_BAYER_GBRG_12_Packed = 319,  //| 12b  |    GBRG:D0          |  GBRG:S0           |
        //----------------------------------//----------------------------------------------------------
    }MVD_PIXEL_FORMAT;

    /** @enum   MVD_IMAGE_TYPE
    *  @brief  image type
    */
    typedef enum _MVD_IMAGE_TYPE_
    {
        MvdImageTypeUndefined=0,
        MvdMaskImage,
    }MVD_IMAGE_TYPE;

    /** @enum   MVD_SAVE_TYPE
    *  @brief  image save type
    */
    typedef enum _MVD_SAVE_TYPE_
    {
        MVD_SAVE_ORIGIANAL_IMAGE=1,//保存原始图像
        MVD_SAVE_RESULT_IMAGE=2,//保存结果图像
    }MVD_SAVE_TYPE;

    /** @enum   MVD_FILE_FORMAT
     *  @brief  image file format
     */
    typedef enum _MVD_FILE_FORMAT_
    {
        MVD_FILE_AUTO  = 0,    // 根据文件名后缀自动解析
        MVD_FILE_BMP  = 1,
        MVD_FILE_JPEG = 2,
        MVD_FILE_TIFF = 3,
        MVD_FILE_PNG  = 4,
    }MVD_FILE_FORMAT;

    /** @enum   MVD_IMG_INTERPOLATION_TYPE
     *  @brief  Interpolation type
     */
    typedef enum _MVD_IMG_INTERPOLATION_TYPE__
    {
        MVD_IMG_INTERPOLATION_BILINEAR = 1,
        MVD_IMG_INTERPOLATION_BICUBIC  = 2,
        MVD_IMG_INTERPOLATION_AREA     = 3,
        MVD_IMG_INTERPOLATION_GAUSS    = 4,
        MVD_IMG_INTERPOLATION_LANCZOS  = 5 
    }MVD_IMG_INTERPOLATION_TYPE;
    //旋转角度定义
    typedef enum _MVD_IMG_ROTATION_ANGLE_
    {
        MVD_IMG_ROTATION_MIN = 1,
        MVD_IMG_ROTATION_90  = 1,
        MVD_IMG_ROTATION_180 = 2,
        MVD_IMG_ROTATION_270 = 3,
        MVD_IMG_ROTATION_MAX = 3,
    }MVD_IMG_ROTATION_ANGLE;

    //翻转类型类型定义
    typedef enum _MVD_IMG_FLIP_TYPE_
    {
        MVD_IMG_FLIP_MIN = 1,
        MVD_IMG_FLIP_VERTICAL = 1,
        MVD_IMG_FLIP_HORIZONTAL = 2,
        MVD_IMG_FLIP_MAX = 2,
    }MVD_IMG_FLIP_TYPE;
    /** @struct MVD_DATA_CHANNEL_INFO
     *  @brief  data channel info
     */
    typedef struct _MVD_DATA_CHANNEL_INFO_
    {
        unsigned char*  pData;
        unsigned int    nSize;
        unsigned int    nLen;
        unsigned int    nRowStep;

        unsigned int    nReserved[4];
    }MVD_DATA_CHANNEL_INFO;

    /** @struct MVD_IMAGE_DATA_INFO
     *  @brief  image data info
     */
    typedef struct _MVD_IMAGE_DATA_INFO_
    {
        MVD_DATA_CHANNEL_INFO stDataChannel[4];

        unsigned int    nReserved[4];
    }MVD_IMAGE_DATA_INFO;

    /** @struct MVD_SCALAR
    *  @brief  pixel info
    */
    typedef struct _MVD_SCALAR_
    {
        unsigned char pVal[4];///< 像素值,具体含义取决于像素格式，例如MONO8以pVal[0]表示灰度值，RGBC3分别以pVal[0],pVal[1],pVal[2]表示R,G,B分量
        int nCount;           ///< 单个像素占用字节数
    }MVD_SCALAR;
}

#endif    ///< _MVD_IMAGE_PARAM_DEFINE_H__
